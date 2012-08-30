<?php

/*
 * Form for adding/editing the Issues' votes
 */
function issue_vote_form($form, $node) {
  global $user;
  $form = array();

  # get translated node
  $tnode = issue_get_translated_node($node->nid);
  $form['#nid'] = $tnode->tnid;
 
  
  # check if it's a search page
  $is_search = arg(0) == 'issues_solr2'; # TODO -- check if it's right way to do this

  # get user's vote for both regular and suggested answers
  $vote_regular = $tnode->vote ? $tnode->vote : -1;
  # get suggested answers
  $vote_suggested = -1;
  if (!$is_search) {
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
      '#suffix' => '</div>'
    );
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
  if (!$is_search) {
    $form['add_vote'] = array(
      '#type' => 'fieldset',
      '#title' => t('...Or submit a different answer'),
      '#collapsible' => TRUE,
      '#collapsed' => $vote_suggested == -1,
      '#tree' => TRUE,
    );

    # suggested answers
    if (!empty($sa)) {
      $form['add_vote']['suggested_answers'] = array(
        '#type' => 'radios',
        '#options' => $sa_options,
        '#default_value' => $vote_suggested,
        '#prefix' => '<div class="choices suggested">',
        '#suffix' => '</div>'
      );
    }
    if (!$sa_added) {
      $form['add_vote']['new_suggest_answer'] = array(
        '#type' => 'textfield',
        '#size' => 38,
        '#description' => t('(Answers must not exceed 140 carachters in length)'),
        '#attributes' => array('class' => 'floatleft'),
        '#maxlength' => 140,
        '#prefix' => '<div class="nsa-wrapper"><table><tr><td class="first">',
        '#suffix' => '</td><td>',
      );
      $form['add_vote']['submit_suggest_answer'] = array(
        '#type' => 'submit',
        '#value' => t('Add Answer'),
        '#attributes' => array('class' => 'add-answer2 light'),
        '#suffix' => '</td></tr></table></div>',
        '#id' => 'answer-add',
      );
    }

  } else {
    # something
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
      '#type' => 'submit',
      '#value' => t('Login to vote'),
      '#attributes' => array('class' => 'button vote floatright openlogin_box'),
      '#id' => 'vote-login',
    );
  }

  $form['#cache'] = TRUE;
  $form['#theme'] = 'poll_vote';
  return $form;
}

/*
 * Form for adding/editing the Issues' votes
 *
 * Validation
 */
function issue_vote_form_validate($form, &$form_state) {
  $post = $form_state['values'];
  switch ($form_state['clicked_button']['#id']) {
    case 'answer-add' :
      if (empty($post['add_vote']['new_suggest_answer'])) {
        form_set_error('suggest_answer', t('Your suggestions should not be empty.'));
      }
    break;
    case 'vote-add' :
    case 'vote-change' :
      $vote_regular = $post['choice'];
      $vote_suggested = $post['add_vote']['suggested_answers'];
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
function issue_vote_form_submit($form, &$form_state) {
  global $user;
  $nid = $form['#nid'];
  $post = $form_state['values'];

  switch ($form_state['clicked_button']['#id']) {
    case 'answer-add' :
      $chid = poll_suggest_add($nid, $post['add_vote']['new_suggest_answer']);
      poll_suggest_vote_add($chid, $user->uid);
      break;
    case 'vote-add' :
    case 'vote-change' :
      $vote_regular = $post['choice'];
      $vote_suggested = $post['add_vote']['suggested_answers'];
      $vote_suggested = empty($vote_suggested) ? -1 : $vote_suggested;

      # @warning
      # since we're so cool to use two sets of radiobuttons with only one resulting vote let's clean values up
      if ($post['vote_regular'] == $vote_regular && $vote_regular != -1) {
        $vote_regular = -1;
      }
      if ($post['vote_suggested'] == $vote_suggested && $vote_suggested != -1) {
        $vote_suggested = -1;
      }

      # check if there were changes in form
      if ($post['vote_suggested'] != $vote_suggested || $post['vote_regular'] != $vote_regular) {
        # remove previous values if any
        if ($post['vote_regular'] != -1) {
          db_query("UPDATE {poll_choices} SET chvotes = chvotes-1 WHERE nid = '%d' AND chorder = '%d'", $nid, $post['vote_regular']);
          db_query("DELETE FROM {poll_votes} WHERE nid = '%d' AND chorder = '%d' AND uid = '%d'", $nid, $post['vote_regular'], $user->uid);
          db_query("UPDATE {poll_votes_history} SET status = 0 WHERE nid = '%d' AND chorder = '%d' AND uid = '%d'", $nid, $post['vote_regular'], $user->uid);
        }
        if ($post['vote_suggested'] != -1) {
          poll_suggest_vote_remove($post['vote_suggested'], $user->uid);
        }
        # add new values
        if ($vote_regular != -1) {
          db_query("UPDATE {poll_choices} SET chvotes = chvotes+1 WHERE nid = '%d' AND chorder = '%d'", $nid, $vote_regular);
          db_query('INSERT INTO {poll_votes} (nid, chorder, uid) VALUES (%d, %d, %d)', $nid, $vote_regular, $user->uid);
          db_query('INSERT INTO {poll_votes_history} (nid, chorder, uid, date_voted, status) VALUES (%d, %d, %d, "%s", %d)', $nid, $vote_regular, $user->uid, date("y-m-d H:i:s"), 1);
        }
        if ($vote_suggested != -1) {
          poll_suggest_vote_add($vote_suggested, $user->uid);
        }
      }

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