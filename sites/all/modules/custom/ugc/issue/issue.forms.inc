<?php



/*
 * Form for adding/editing the Issues' votes
 */
function issue_vote_form($form, $node) {
  global $user;
  $form = array();

  # get translated node
  $tnode = issue_get_translated_node($node->nid);
  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $tnode->nid,
  );
    
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
      if ($voted) {
        $form['add_vote']['suggested_answers'] += array(
          '#after_build' => array('issue_vote_form_radios_suggested'),
        );
      }
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
  $post = $form_state['values'];
  $nid = $post['nid'];

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
          # convert
          issue_sa_convert($nid, $vote_suggested);
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

/*
 * Suggested answer conversion
 */
function issue_sa_convert($nid, $chid) {
  $votes_s = poll_suggest_get_votes($nid);
  if ($votes_s[$chid] >= 10) { # more than 10 votes
    $votes_r = issue_get_votes($nid);
    $votes_r_count = count($votes_r) - 1;
    if (2 * $votes_r_count * $votes_s[$chid] >= $votes_r['#all'] + $votes_s['#all'] ) {
      # more than half of average regular answer's votes
      $sa = poll_suggest_get($nid);
      $chtext = false;
      foreach ($sa as $s) {
        if ($s['chid'] == $chid) {
          $chtext = $s['chtext'];
          break;
        }
      }
      if ($chtext !== false) {
        $chorder = db_result(db_query("SELECT MAX(pc.chorder) + 1 FROM {poll_choices} pc WHERE pc.nid = '%d'", $nid));
        # add ne choice
        db_query("INSERT INTO {poll_choices} SET nid = '%d', chtext = '%s', chvotes = '%d', chorder = '%d'", $nid, $chtext, $votes_s[$chid], $chorder);
        # transfer votes
        db_query("INSERT INTO {poll_votes} (nid, uid, chorder, date_voted) SELECT '%d', psv.uid, '%d', psv.date FROM {poll_suggest_votes} psv WHERE psv.chid = '%d'", $nid, $chorder, $chid);
        # transfer vote history
        db_query("INSERT INTO {poll_votes_history} (nid, uid, chorder, status, date_voted) SELECT '%d', psv.uid, '%d', 1, psv.date FROM {poll_suggest_votes} psv WHERE psv.chid = '%d'", $nid, $chorder, $chid);
        # delete suggested votes
        db_query("DELETE FROM {poll_suggest_votes} WHERE chid = '%d'", $chid);
        # delete suggested answer
        poll_suggest_remove(array('chid' => $chid));
      }
    }
  }
}
