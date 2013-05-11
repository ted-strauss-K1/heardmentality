<?php

/**
 * "issue/create" menu callback
 *
 * @return null|string
 */
function issue_create()
{
  return drupal_get_form('issue_create_form');
}

/**
 * "issue/create/ahah/answer" menu callback
 */
function issue_create_ahah_answer()
{
  $delta = count($_POST['answer']);
  # build form element
  $form_element = _issue_create_form_answer_textfield($delta);
  # build new form
  $form_state = array('storage' => NULL, 'submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  # add element
  $form = form_get_cache($form_build_id, $form_state);
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  if ($form_element !== FALSE) {
    $form['choice_wrapper']['answer'][$delta] = $form_element;
  }
  form_set_cache($form_build_id, $form, $form_state);
  $form += array(
    '#post' => $_POST,
    '#programmed' => FALSE,
  );
  $form_state['post'] = $_POST;
  # Build, validate and if possible, submit the form.
  $form_state['action'] = $form['#action'];
  $form_state['rebuild'] = TRUE;
  drupal_process_form($form_id, $form, $form_state);
  # Rebuild the form.
  $form = form_builder($form_id, $form, $args, $form_state);
  # Render the new output.
  unset($_SESSION['messages']);
  $choice_form = $form['choice_wrapper']['answer'];
  //unset($choice_form['#prefix'], $choice_form['#suffix']); // Prevent duplicate wrappers.
  $choice_form[$delta]['#attributes']['class'] =
    empty($choice_form[$delta]['#attributes']['class']) ?
      'ahah-new-content' : $choice_form[$delta]['#attributes']['class'] . ' ahah-new-content';
  $output = drupal_render($choice_form);

  $ahah = array('status' => TRUE, 'data' => $output);
  if ($form_element === FALSE) {
    $ahah['js'] = array('func' => 'issue_create_ahah_answer_error');
  }
  print json_encode($ahah);
}

/**
 * Function to handle "issue/ajax" calls
 *
 * @warning Not to mix things up - use it only for poll votes, answer suggestions
 */
function issue_ajax()
{
  $post = & $_POST;

  # suppress form submission
  unset($post['form_build_id']);
  unset($post['form_id']);
  unset($post['form_token']);

  # logged in user validation
  if (user_is_anonymous()) {
    print json_encode(array(
      'status' => FALSE,
      'message' => t('Please log in'),
    ));
    exit;
  }

  # proper nid
  $nid = $post['nid'];
  if (empty($nid) || !is_numeric($nid)) {
    print json_encode(array(
      'status' => FALSE,
      'message' => t('Wrong issue ID'),
    ));
    exit;
  }

  switch ($post['action']) {
    case 'vote' :
      _issue_ajax_vote($post);
      break;
    case 'suggest' :
      _issue_ajax_suggest($post);
      break;
    default :
      print json_encode(array(
        'status' => FALSE,
        'vars' => $post,
        'message' => t('Unknown error happened'),
      ));
      exit();
  }
}

/**
 * Function to handle "issue/ajax" poll votes
 */
function _issue_ajax_vote($vars)
{
  $nid = $vars['nid'];
  $vote_r = is_null($vars['choice']) ? -1 : $vars['choice'];
  $vote_r_old = is_null($vars['vote_regular']) ? -1 : $vars['vote_regular'];
  $vote_s = is_null($vars['suggest']['suggest_choice']) ? -1 : $vars['suggest']['suggest_choice'];
  $vote_s_old = is_null($vars['vote_suggested']) ? -1 : $vars['vote_suggested'];

  if ($vote_r_old == $vote_r && $vote_r != -1) {
    $vote_r = -1;
  }
  if ($vote_s_old == $vote_s && $vote_s != -1) {
    $vote_s = -1;
  }

  # saving the vote
  $result = issue_poll_vote((int)$nid, (int)$vote_r, (int)$vote_r_old, (int)$vote_s, (int)$vote_s_old);
  if (!$result) {
    print json_encode(array(
      'status' => FALSE,
      'message' => t('Your vote was not changed'),
    ));
    exit;
  } else {
    $content = drupal_get_form('issue_vote_form', node_load($nid, NULL, TRUE), $vars['full'] == 1, TRUE);
    print json_encode(array(
      'status' => TRUE,
      'message' => t('Your vote was successfully saved'),
      'content' => $content,
    ));
    exit;
  }
}

/**
 * Function to handle "issue/ajax" answer suggestions
 */
function _issue_ajax_suggest($vars)
{
  $answer = $vars['suggest']['suggest_answer'];
  $nid = $vars['nid'];

  # empty answer validation
  if (empty($answer)) {
    print json_encode(array(
      'status' => FALSE,
      'message' => t('Cannot add empty answer'),
    ));
    exit;
  }
  # duplicate answer validation
  $node = node_load($nid);
  $choices = array_merge($node->choice, poll_suggest_get($nid));
  foreach ($choices as $choice) {
    if (($choice['chtext'] == $answer) || ($choice['chtext_short'] == $answer)) {
      print json_encode(array(
        'status' => FALSE,
        'message' => t('Cannot add duplicate answer'),
      ));
      exit;
    }
  }
  # add the suggested answer then
  $chid = poll_suggest_add($nid, $answer);
  # add the suggested
  $result = issue_poll_vote((int)$nid, -1, (int)$vars['vote_regular'], (int)$chid, (int)$vars['vote_suggested']);
  if (!$result) {
    print json_encode(array(
      'status' => FALSE,
      'message' => t('Your vote was not changed'),
    ));
    exit;
  } else {
    $content = drupal_get_form('issue_vote_form', node_load($nid, NULL, TRUE), $vars['full'] == 1, TRUE);
    print json_encode(array(
      'status' => TRUE,
      'message' => t('Your suggestion was successfully added'),
      'content' => $content,
    ));
    exit;
  }
}

/**
 * Poll vote change
 */
function issue_poll_vote($nid, $vote_r, $vote_r_old, $vote_s = -1, $vote_s_old = -1)
{
  if ($vote_r == -1 && $vote_s == -1) return FALSE;
  if ($vote_r == $vote_r_old && $vote_s == $vote_s_old) return FALSE;
  global $user;
  if ($vote_r_old != -1) {
    db_query("DELETE FROM {poll_votes} WHERE nid = '%d' AND uid = '%d'", $nid, $user->uid);
  }
  if ($vote_s_old != -1) {
    poll_suggest_vote_remove($vote_s_old, $user->uid);
  }
  # add new values
  if ($vote_r != -1) {
    db_query('INSERT INTO {poll_votes} (nid, chorder, uid) VALUES (%d, %d, %d)', $nid, $vote_r, $user->uid);

    if (module_exists('rules')) {
      $node = node_load($nid);
      rules_invoke_event('poll_vote', $user, $node);
      rules_invoke_event('poll_voted', user_load($node->uid), $node);
    }
  }
  if ($vote_s != -1) {
    poll_suggest_vote_add($vote_s, $user->uid);
  }

  // update stats
  db_query("UPDATE {poll_choices} SET {poll_choices}.chvotes = (SELECT COUNT(*) FROM {poll_votes} WHERE {poll_votes}.nid = {poll_choices}.nid AND {poll_votes}.chorder = {poll_choices}.chorder) WHERE {poll_choices}.nid = '%d'", $nid);

  // reindex
  if (module_exists('issue_search')) {
    issue_search_index_node($nid);
  }

  return TRUE;
}

/**
 *
 */
function issue_share($nid)
{
  if (user_is_logged_in() && module_exists('rules')) {
    global $user;
    rules_invoke_event('poll_share', $user, node_load($nid));
  }
}

/**
 *
 */
function issue_subscribe() {
  $hierarchy = $_REQUEST['hierarchy'];
  $tid = preg_replace('/-.*$/', '', $hierarchy);
  $term = taxonomy_get_term($tid);

  if (!$term) {
    print json_encode(array(
      'status' => false,
      'message' => t('Unknown error'),
    ));
    exit;
  }

  // write the record
  global $user;
  $exists = (bool)subscriptions_get_subscription($user->uid, 'node', 'tid', $term->tid);
  if (!$exists) {
    subscriptions_write_subscription('node', 'tid', $term->tid, -1, $user->uid);
  } else {
    db_query(
      "DELETE FROM {subscriptions}
      WHERE
        module = '%s' AND
        field = '%s' AND
        value = '%s' AND
        author_uid = %d AND
        recipient_uid = %d",
      'node', 'tid', $term->tid, -1, $user->uid);
  }
  // output
  print json_encode(array(
    'status' => true,
    'message' => t('You have '.($exists ? 'un' : '').'subscribed '.($exists ? 'from' : 'to').' !name', array('!name' => $term->name)),
    'result' => !$exists,
  ));

  exit;
}