<?php include "old.issue.pages.inc";

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
  if ($form_element !== false) {
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
  if ($form_element === false) {
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
      'status' => false,
      'message' => t('Please log in'),
    ));
    exit;
  }

  # proper nid
  $nid = $post['nid'];
  if (empty($nid) || !is_numeric($nid)) {
    print json_encode(array(
      'status' => false,
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
        'status' => false,
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
      'status' => false,
      'message' => t('Unexpected error happened while saving your vote'),
    ));
    exit;
  } else {
    $content = drupal_get_form('issue_vote_form', node_load($nid, null, true), $vars['full'] == 1, true);
    print json_encode(array(
      'status' => true,
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
      'status' => false,
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
        'status' => false,
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
      'status' => false,
      'message' => t('Unexpected error happened while adding your suggestion'),
    ));
    exit;
  } else {
    $content = drupal_get_form('issue_vote_form', node_load($nid, null, true), $vars['full'] == 1, true);
    print json_encode(array(
      'status' => true,
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
  if ($vote_r == $vote_r_old && $vote_s == $vote_s_old) return false;
  global $user;
  if ($vote_r_old != -1) {
    db_query("UPDATE {poll_choices} SET chvotes = chvotes-1 WHERE nid = '%d' AND chorder = '%d'", $nid, $vote_r_old);
    db_query("DELETE FROM {poll_votes} WHERE nid = '%d' AND uid = '%d'", $nid, $user->uid);
  }
  if ($vote_s_old != -1) {
    poll_suggest_vote_remove($vote_s_old, $user->uid);
  }
  # add new values
  if ($vote_r != -1) {
    db_query("UPDATE {poll_choices} SET chvotes = chvotes+1 WHERE nid = '%d' AND chorder = '%d'", $nid, $vote_r);
    db_query('INSERT INTO {poll_votes} (nid, chorder, uid) VALUES (%d, %d, %d)', $nid, $vote_r, $user->uid);

    if (module_exists('rules')) {
      rules_invoke_event('poll_vote', $user, node_load($nid));
    }
  }
  if ($vote_s != -1) {
    poll_suggest_vote_add($vote_s, $user->uid);
  }

  return true;
}