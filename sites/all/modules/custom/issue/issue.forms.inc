<?php





/**
 * "issue/create" form validation
 *
 * @param $form
 * @param $form_state
 */
function issue_create_form_validate($form, &$form_state)
{
  $post = $form_state['clicked_button']['#post'];
  if ($post['q_quest'] == '') {
    form_set_error('error', t('Please enter your question'));
  }
  if ($post['answer'][0] == '' && $post['answer'][1] == '') {
    form_set_error('error', t('You must enter at least two answers'));
  }
}

/**
 * "issue/create" form submission
 *
 * @param $form
 * @param $form_state
 */
function issue_create_form_submit($form, &$form_state)
{
  $post = $form_state['clicked_button']['#post'];
  global $user, $language;

  $node = new StdClass();
  $node->type = 'poll';
  $node->language = !empty($user->language) ? $user->language : $language->language; // TODO check language detection
  $node->uid = $user->uid;
  $node->status = 1;
  $node->moderate = 1;
//  $node->created = time();
//  $node->tnid = 0;
  $node->title = preg_replace('/\?$/', '', trim($post['q_quest']));
  $node->field_description[0]['value'] = $post['q_context'];
  $node->name = $user->name;
  $count = count($post['answer']);
  for ($i = 0; $i < $count; $i++) {
    $node->choice[$i]['chtext'] = $post['answer'][$i];
    $node->choice[$i]['chorder'] = $i;
    $node->choice[$i]['chvotes'] = 0;
  }
  $node->active = 1;

  node_save($node);

  // reindex
  if (module_exists('issue_search')) {
    issue_search_index_node($node->nid);
  }

  drupal_set_message(t('Your issue has been added.  It will be reviewed by 3 moderators but is available immediately.
'), 'success');

  drupal_goto($node->path);
}

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

  if ($vote) {
    $form['choice']['#after_build'] = array('issue_vote_form_radios');
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
      if ($s['uid']) {
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
      if ($vote) {
        $form['suggest']['suggest_choice']['#after_build'] = array('issue_vote_form_radios_suggested');
      }
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
<span>' . $vote_number . '</span>' . $vote_string . '</span>';
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
<span>' . $vote_number . '</span>' . $vote_string . '</span>';
    $form_element[$i]['#suffix'] = '</div>';
  }
  return $form_element;
}