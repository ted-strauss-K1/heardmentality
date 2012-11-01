<?php

/*
 * Form for adding/editing the Issues' votes
 */
function issue_vote_form($form, $node, $full = true, $nowrap = false) {
  global $user;
  $form = array();

  $form['#attributes'] = array('class' => 'issue-vote-form');

  if (!$nowrap) {
    $form['#prefix'] = sprintf('<div id="voteform-%d" class="voteform">', $node->nid);
    $form['#suffix'] = '</div>';
  }

  # get translated node
  $tnode = issue_get_translated_node($node->nid);
//  var_dump($tnode); die();
  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $tnode->nid,
  );
  $form['full'] = array(
    '#type' => 'hidden',
    '#value' => $full ? 1 : 0,
  );

  # get user's vote for both regular and suggested answers
  $vote_regular = !is_null($tnode->vote) ? $tnode->vote : -1;

  # get suggested answers
  $vote_suggested = -1;
  $sa = poll_suggest_get($node->nid);
  $sa_added = false;
  $sa_options = array();
  foreach ($sa as $s) {
    $sa_options[$s['chid']] = '<span class="ch">' . $s['chtext'] . '</span>';
    if ($s['uservote'] != 0) {
      $vote_suggested = $s['chid'];
    }
    if ($s['uid']) {
      $sa_added = true;
    }
  }

  $vote = $vote_regular != -1 ? $vote_regular : $vote_suggested;
  $voted = $vote != -1;

  # save the values
  $form['vote_regular'] = array(
    '#type' => 'hidden',
    '#value' => $vote_regular,
  );
  $form['vote_suggested'] = array(
    '#type' => 'hidden',
    '#value' => $vote_suggested,
  );

  # add choices
  if ($node->choice) {
    $list = array();
    foreach ($node->choice as $i => $choice) {
      $list[$i] = '<span class="ch">' . check_plain($choice['chtext']) . '</span>';
    }
    $form['choice'] = array(
      '#type' => 'radios',
      '#default_value' => $vote_regular,
      '#options' => $list,
      '#prefix' => '<div class="choices regular">',
      '#suffix' => '</div>',
    );
    if ($voted) {
      $form['choice']['#after_build'] = array('issue_vote_form_radios');
    }
  }

  # login warning
  if (!user_is_logged_in()) {
    $form['login_error'] = array(
      '#type' => 'markup',
      '#prefix' => '<div class="login-error">',
      '#value' => t('You should login to vote or post suggest answers.'),
      '#suffix' => '</div>',
    );
  }

  # add suggested answers
  $form['suggest'] = array(
    '#type' => 'fieldset',
    '#title' => !$full || $sa_added ? t('') : t('...Or submit a different answer'),
    '#collapsible' => TRUE,
    '#collapsed' => empty($sa),// $vote_suggested == -1,
    '#tree' => TRUE,
  );

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

  if (!empty($sa)) {
    $form['suggest']['suggest_choice'] = array(
      '#type' => 'radios',
      '#options' => $sa_options,
      '#default_value' => $vote_suggested,
      '#prefix' => '<div class="choices suggested">',
      '#suffix' => '</div>'
    );
    if ($voted) {
      $form['suggest']['suggest_choice'] += array(
        '#after_build' => array('issue_vote_form_radios_suggested'),
      );
    }
  }

  # add vote submit button
  if (user_is_logged_in()) {
    if ($voted) {
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
      '#attributes' => array('class' => 'button vote floatright '.user_profile_login_class(true)),
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
function issue_vote_form_radios($form_element, &$form_state) {
  $nid = $form_state['values']['nid'];
  $count = count($form_element['#options']);
  $votes = issue_get_votes($nid);
  for ($i = 0; $i < $count; $i++) {
    $vote_number = ($votes[$i] ? $votes[$i] : 0);
    $vote_string = 'vote' . ($vote_number == 1 ? '' : 's');
    $form_element[$i]['#prefix'] = '<div class="radio_wrapper clearfix"><span class="teaser_count_vote">
<span>' . $vote_number . '</span>' . $vote_string . '</span>';
    $form_element[$i]['#suffix'] = '</div>';
  }
  return $form_element;
}

/*
 * Afterbuild for issue_vote_form
 */
function issue_vote_form_radios_suggested($form_element, &$form_state) {
  $nid = $form_state['values']['nid'];
  $votes = poll_suggest_get_votes($nid);
  foreach ($votes as $i => $vote_number) {
    $vote_string = 'vote' . ($vote_number == 1 ? '' : 's');
    $form_element[$i]['#prefix'] = '<div class="radio_wrapper clearfix"><span class="teaser_count_vote">
<span>' . $vote_number . '</span>' . $vote_string . '</span>';
    $form_element[$i]['#suffix'] = '</div>';
  }
  return $form_element;
}

/*
 * Form for adding/editing the Issues' votes
 *
 * Validation
 */
function _issue_vote_form_validate($form, &$form_state) {
  $post = $form_state['values'];
  switch ($form_state['clicked_button']['#id']) {
    case 'answer-add' :
      if (empty($post['suggest']['suggest_answer'])) {
        form_set_error('suggest_answer', t('Your suggestions should not be empty.'));
      }
    break;
    case 'vote-add' :
    case 'vote-change' :
      $vote_regular = $post['choice'];
      $vote_suggested = $post['suggest']['suggest_choice'];
      $vote_suggested = empty($vote_suggested) ? -1 : $vote_suggested;
      $vote = $vote_regular != -1 ? $vote_regular : $vote_suggested;
      $voted = $vote != -1;

      if (!$voted) {
        form_set_error('choice', t('Your vote could not be recorded because you did not select any of the choices.'));
      }
    break;
    case 'vote-login' :
      # nothing
    break;
    default :
      # nothing
    break;
  }
}

/*
 * Form for adding/editing the Issues' votes
 *
 * Submission
 */
function _issue_vote_form_submit($form, &$form_state) {
  global $user;
  $post = $form_state['values'];
  $nid = $post['nid'];

  switch ($form_state['clicked_button']['#id']) {
    case 'answer-add' :
      $chid = poll_suggest_add($nid, $post['suggest']['suggest_answer']);
      poll_suggest_vote_add($chid, $user->uid);

      # find old regular vote
      $chorder = db_result(db_query("SELECT chorder FROM {poll_votes} WHERE nid = '%d' AND uid = '%d'", $nid, $user->uid));
      if ($chorder) {
        db_query("UPDATE {poll_choices} SET chvotes = chvotes-1 WHERE nid = '%d' AND chorder = '%d'", $nid, $chorder);
        db_query("DELETE FROM {poll_votes} WHERE nid = '%d' AND chorder = '%d' AND uid = '%d'", $nid, $chorder, $user->uid);
//        db_query("UPDATE {poll_votes_history} SET status = 0 WHERE nid = '%d' AND chorder = '%d' AND uid = '%d'", $nid, $chorder, $user->uid);
      }

      break;
    case 'vote-add' :
    case 'vote-change' :
      $vote_r = $post['choice'];
      $vote_suggested = $post['suggest']['suggest_choice'];
      $vote_s = empty($vote_suggested) ? -1 : $vote_suggested;
      $vote_r_old = $post['vote_regular'];
      $vote_s_old = $post['vote_suggested'];

      # @warning
      # since we're so cool to use two sets of radiobuttons with only one resulting vote let's clean values up
      if ($vote_r_old == $vote_r && $vote_r != -1) {
        $vote_r = -1;
      }
      if ($vote_s_old == $vote_s && $vote_s != -1) {
        $vote_s = -1;
      }

      issue_poll_vote($nid, $vote_r, $vote_r_old, $vote_s, $vote_s_old);
      drupal_set_message(t('Your vote was recorded.'));
    break;
    case 'vote-login' :
      # nothing
    break;
    default :
      # nothing
    break;
  }
}