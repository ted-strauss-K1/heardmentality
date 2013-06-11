<?php

/**
 * Form for adding/editing the Issues' votes
 *
 * @param $form
 * @param $node
 * @param bool $full
 * @param bool $nowrap
 * @return array
 */
function issue_vote_form($form, $node, $full = true, $nowrap = false)
{
  global $user;
  $form = array();

  $form['#attributes'] = array('class' => 'issue-vote-form');

  if (!$nowrap) {
    $form['#prefix'] = sprintf('<div id="voteform-%d" class="voteform">', $node->nid);
    $form['#suffix'] = '</div>';
  }

  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );
  $form['full'] = array(
    '#type' => 'hidden',
    '#value' => $full ? 1 : 0,
  );

  # display language & translation
  $translation = poll_translate_translation($node);

  # votes
  $vote_r = is_null($node->vote) ? -1 : $node->vote;
  $form['vote_regular'] = array(
    '#type' => 'hidden',
    '#value' => $vote_r,
  );
  # add choices
  if ($node->choice) {
    $list = array();
    foreach ($node->choice as $i => $choice) {
      $list[$i] = '<span class="ch">' .
        check_plain(
          !empty($translation['choice'][$choice['chorder']]) ?
            $translation['choice'][$choice['chorder']] :
            $choice['chtext']
        ) .
        '</span>';
    }
    $form['choice'] = array(
      '#type' => 'radios',
      '#default_value' => $vote_r,
      '#options' => $list,
      '#prefix' => '<div class="choices regular">',
      '#suffix' => '</div>',
    );
  }

  $vote = $vote_r != -1;
  if (module_exists('poll_suggest')) {
    $vote_s = $node->vote_suggest;
    $form['vote_suggested'] = array(
      '#type' => 'hidden',
      '#value' => $vote_s,
    );
    $vote = $vote || ($vote_s != -1);
  }

  $form['choice']['#after_build'] = array('issue_vote_form_radios');

  # login warning
  if (!user_is_logged_in()) {
    $form['login_error'] = array(
      '#type' => 'markup',
      '#prefix' => '<div class="login-error">',
      '#value' => t('You should login to vote or post suggest answers.'),
      '#suffix' => '</div>',
    );
  }

  if (module_exists('poll_suggest')) {
    $sa_added = false;
    $sa_options = array();
    foreach ($node->choice_suggest as $s) {
      $sa_options[$s['chid']] = '<span class="ch">' .
        check_plain(
          !empty($translation['choice_suggest'][$s['chid']]) ?
            $translation['choice_suggest'][$s['chid']] :
            $s['chtext']
        )
        . '</span>';
      if ($s['uid'] == $user->uid) {
        $sa_added = true;
      }
    }
    # add suggested answers
    $form['suggest'] = array(
      '#type' => 'fieldset',
      '#title' => !$full || $sa_added ? t('') : t('...Or submit a different answer'),
      '#collapsible' => TRUE,
      '#collapsed' => empty($node->choice_suggest),
      '#tree' => TRUE,
    );

    if (!empty($node->choice_suggest)) {
      $form['suggest']['suggest_choice'] = array(
        '#type' => 'radios',
        '#options' => $sa_options,
        '#default_value' => $vote_s,
        '#prefix' => '<div class="choices suggested">',
        '#suffix' => '</div>'
      );
      $form['suggest']['suggest_choice']['#after_build'] = array('issue_vote_form_radios_suggested');
    }

    if ($full && user_is_logged_in() && !$sa_added) {
      $form['suggest']['suggest_answer'] = array(
        '#type' => 'textfield',
        '#size' => 38,
        '#description' => t('(Answers must not exceed 140 carachters in length)'),
        '#attributes' => array('class' => 'floatleft'),
        '#maxlength' => 140,
        '#prefix' => '<div class="nsa-wrapper"><table><tr><td class="first">',
        '#suffix' => '</td><td>',
      );
      $form['suggest']['submit_suggest_answer'] = array(
        '#type' => 'submit',
        '#value' => t('Add Answer'),
        '#attributes' => array('class' => 'add-answer2 light'),
        '#suffix' => '</td></tr></table></div>',
        '#id' => 'answer-add',
      );
    }

    if (!$node->allowsuggestions) {
      unset($form['suggest']['suggest_answer']);
      unset($form['suggest']['submit_suggest_answer']);
      if (empty($node->choice_suggest)) {
        unset($form['suggest']);
      }
    }
  }

  # not-voted
  if (!$vote) {
    $form['#attributes']['class'] .= ' not-voted';
  }
  $form['#attributes']['class'] .= ' voteform-'.$node->nid;


  # add vote submit button
  if (user_is_logged_in()) {
    if ($vote) {
      $form['main_submit'] = array(
        '#type' => 'submit',
        '#value' => t('Change vote'),
        '#attributes' => array('class' => 'button vote floatright'),
        '#id' => 'vote-change',
      );
    } else {
      $form['main_submit'] = array(
        '#type' => 'submit',
        '#value' => t('Vote'),
        '#attributes' => array('class' => 'button vote floatright'),
        '#id' => 'vote-add',
      );
    }
  } else {
    $form['main_submit'] = array(
      '#type' => 'button',
      '#value' => t('Login to vote'),
      '#attributes' => array('class' => 'button vote floatright ' . theme('user_login_modal_class', true)),
      '#id' => 'vote-login',
    );
  }

  // for ajax callbacks
  $form['action'] = array(
    '#type' => 'hidden',
    '#value' => 'vote',
  );

  $form['#cache'] = TRUE;
  $form['#theme'] = 'poll_vote';

  return $form;
}

/*
 * Afterbuild for issue_vote_form
 */
function issue_vote_form_radios($form_element, &$form_state)
{
  $node = node_load($form_state['values']['nid']);
  $count = count($form_element['#options']);

  if ($count != count($node->choice)) {
    return $form_element;
  }

  if ($node->choice) {
    foreach ($node->choice as $i => $choice) {
      $vote_number = (int)$choice['chvotes'];
      $vote_string = 'vote' . ($vote_number == 1 ? '' : 's');
      $form_element[$i]['#prefix'] = '<div class="radio_wrapper clearfix"><span class="teaser_count_vote">
<span class="vote-result-r-'.$i.'">' . $vote_number . '</span>' . $vote_string . '</span>';
      $form_element[$i]['#suffix'] = '</div>';
    }
  }

  return $form_element;
}

/*
 * Afterbuild for issue_vote_form
 */
function issue_vote_form_radios_suggested($form_element, &$form_state)
{
  $nid = $form_state['values']['nid'];
  $votes = poll_suggest_get_votes($nid);
  foreach ($votes as $i => $vote_number) {
    $vote_string = 'vote' . ($vote_number == 1 ? '' : 's');
    $form_element[$i]['#prefix'] = '<div class="radio_wrapper clearfix"><span class="teaser_count_vote">
<span class="vote-result-s-'.$i.'">' . $vote_number . '</span>' . $vote_string . '</span>';
    $form_element[$i]['#suffix'] = '</div>';
  }
  return $form_element;
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
      'message2' => $post,
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

  # doublecheck input
  $node = node_load($nid);
  if ( ($vars['vote_regular'] != $node->vote) || ($vars['vote_suggested'] != $node->vote_suggest) ) {
    exit(json_encode(array(
      'status' => FALSE,
      'message' => t('Illegal choice detected'),
      'reload' => true,
    )));
  }

  $vote_r = ('s' != $vars['vote_type']) ? $vars['vote'] : -1;
  $vote_s = ('s' == $vars['vote_type']) ? $vars['vote'] : -1;
  $vote_r_old = is_null($vars['vote_regular']) ? -1 : $vars['vote_regular'];
  $vote_s_old = is_null($vars['vote_suggested']) ? -1 : $vars['vote_suggested'];

  if ($vote_r_old == $vote_r && $vote_r != -1) {
    $vote_r = -1;
  }
  if ($vote_s_old == $vote_s && $vote_s != -1) {
    $vote_s = -1;
  }

  # saving the vote
  $result = issue_poll_vote((int)$nid, (int)$vote_r, (int)$vote_r_old, (int)$vote_s, (int)$vote_s_old);
  $node = node_load($nid, NULL, TRUE);
  $output = array(
    'nid' => $node->nid,
    'choice_r' => $node->choice,
    'choice_s' => poll_suggest_get_votes($nid),
    'vote_r' => $node->vote,
    'vote_s' => $node->vote_suggest,
  );
  if (!$result) {
    exit(json_encode(array(
      'status' => FALSE,
      'message' => t('Your vote was not changed'),
      'content' => $output,
    )));
  } else {
    exit(json_encode(array(
      'status' => TRUE,
      'message' => t('Your vote was successfully saved'),
      'content' => $output,
    )));
  }
}

/**
 * Function to handle "issue/ajax" answer suggestions
 */
function _issue_ajax_suggest($vars)
{
  $answer = $vars['suggest']['suggest_answer'];
  $nid = $vars['nid'];


//  print json_encode(array(
//    'status' => FALSE,
//    'message' => $vars,
//  ));
//  exit;

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