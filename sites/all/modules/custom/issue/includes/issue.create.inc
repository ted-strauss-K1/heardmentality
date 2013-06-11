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
 * "issue/create" form
 *
 * @param $form_state
 * @return array
 */
function issue_create_form(&$form_state)
{
  $form = array();

  $form['#attributes'] = array('onsubmit' => 'return limitChars(true)');

  if (isset($form_state['action'])) {
    $form['#action'] = $form_state['action'];
  }
  $form['issue_cont'] = array(
    '#type' => 'markup',
    '#value' => '
      <div class="grey-box full" id="create_box">
        <div class="new-issue clearfix">
    '
  );
  $form['title_div'] = array(
    '#type' => 'markup',
    '#value' => '
      <label for="" class="add-on">
        <div class="number dinbold">1</div>
        <span class="title ">' . t('Question') . '</span>
        <span class="guides"><span id="q_counter"></span> ' . t('chars left.') . '</span>
      </label>
    '
  );
  $form['q_quest'] = array(
    '#type' => 'textarea',
    '#id' => 'q_quest',
    '#attributes' => array('onkeyup' => 'limitChars(false)', 'rows' => 0, 'cols' => 0),
    '#suffix' => '<hr class="short2">',
  );
  $form['desc_div'] = array(
    '#type' => 'markup',
    '#value' => '
      <label for="" class="add-on">
        <div class="number dinbold">2</div>
        <span class="title ">' . t('Context') . '</span>
        <span class="guides">' . t('Enter a brief description or backstory to provide context. You may include links.') . '</span>
      </label>
    '
  );
  $form['q_context'] = array(
    '#type' => 'textarea',
    '#rows' => 4,
    '#id' => 'Question',
    '#suffix' => '<hr class="short2">',
    '#attributes' => array('rows' => 0, 'cols' => 0)
  );
  if (isset($form_state['choice_count'])) {
    $choice_count = $form_state['choice_count'];
  } else {
    $choice_count = 2;
  }
  $form['choice_wrapper'] = array(
    '#tree' => FALSE,
    '#prefix' => '<div class="clear-block" id="poll-choice-wrapper">',
    '#suffix' => '</div>',
  );
  $form['choice_wrapper']['answer'] = array(
    '#prefix' => '
      <div id="poll-choices">
        <label for="" class="add-on">
          <div class="number dinbold">3</div>
          <span class="title ">' . t('Answers') . '</span>
          <span class="guides">' . t('Enter at least two answers.') . '</span>
        </label>
    ',
    '#suffix' => '</div><div class="clear"></div>',
  );
  for ($delta = 0; $delta < $choice_count; $delta++) {
    $form['choice_wrapper']['answer'][$delta] = _issue_create_form_answer_textfield($delta);
  }
  $form['choice_wrapper']['poll_more'] = array(
    '#type' => 'submit',
    '#value' => '+ ' . t('Add another answer'),
    '#description' => t("If the amount of boxes above isn't enough, click here to add more choices."),
    '#weight' => 1,
    '#ahah' => array(
      'path' => 'issue/create/ahah/answer',
      'wrapper' => 'poll-choices',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#attributes' => array('class' => 'add-answer light'),
    '#suffix' => '<div class="clear"></div><hr class="bottom">',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#attributes' => array('class' => 'submit-issue'),
    '#value' => t('SUBMIT NEW ISSUE'),
    '#id' => 'save_issue',
    '#prefix' => '<label class="before-submit">' . t('Your issue will go live immediately, but a moderator will edit it soon to assign categories, look for duplicates, or make format changes') . '</label>',
    '#suffix' => ' <div class="clear"></div>'
  );
  $form['issue_cont_close'] = array(
    '#type' => 'markup',
    '#value' => '</div></div>'
  );
  $form['#cache'] = TRUE;
  return $form;
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
 * "issue/create/ahah/answer" callback
 */
function _issue_create_form_answer_textfield($delta, $value = '')
{
  if ($delta < 10) {
    $form = array(
      '#tree' => TRUE,
    );
    $form['chtext'] = array(
      '#type' => 'textfield',
      '#default_value' => $value,
      '#parents' => array('answer', $delta),
      '#id' => 'Answer',
    );
    return $form;
  }
  return false;
}

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