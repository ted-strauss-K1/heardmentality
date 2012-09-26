<?php

/*
 * "issue/create" page callback
 */
function issue_create() {
  return drupal_get_form('issue_create_form');
}

/*
 * "issue/create" form
 */
function issue_create_form(&$form_state) {
  $form = array();

  if (isset($form_state['action'])) {
    $form['#action'] = $form_state['action'];
  }
  $form['issue_cont'] = array(
    '#type' => 'markup',
    '#value' => '
      <div class="grey-box">
        <h2 class="din">' . t('Add an Issue') . '</h2>
        <div class="new-issue">
          <hr class="short2">
    '
  );
  $form['title_div'] = array(
    '#type' => 'markup',
    '#value' => '
      <label for="" class="add-on">
        <div class="number dinbold">1</div>
        <span class="title ">' . t('Question') . '</span>
        <br>
        <span class="guides">' . t('Max 140 chars.') . '</span>
      </label>
    '
  );
  $form['q_quest'] = array(
    '#type' => 'textarea',
    '#id' => 'q_quest',
    '#ahah' => array(
      'path' => 'issue/related',
      'wrapper' => 'related-issues',
      'effect' => 'fade'
    ),
    '#attributes' => array('onkeyup' => 'limitChars()', 'rows' => 0, 'cols' => 0),
    '#suffix' => '<hr class="short2">',
  );
  $form['desc_div'] = array(
    '#type' => 'markup',
    '#value' => '
      <label for="" class="add-on">
        <div class="number dinbold">2</div>
        <span class="title ">' . t('Context') . '</span>
        <br>
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
          <br>
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
  $form['exist_check'] = array(
    '#type' => 'hidden',
    '#value' => '',
    '#id' => 'exist_check'
  );
  $form['related_issues'] = array(
    '#title' => t("Related Issues"),
    '#prefix' => '<div id="related-issues">',
    '#suffix' => '</div>',
    '#type' => 'fieldset',
  );
  # check if the question is edited through this form
  if ($form_state['values']['q_quest']) {
    $question = $form_state['values']['q_quest'];
    $related = issue_get_related($question);
    if (empty($related)) {
      $form['related_issues']['no_rel'] = array(
        '#type' => 'markup',
        '#value' => 'No Related Issues'
      );
    } else {
      $options = array();
      foreach ($related as $nid => $title) {
        $options[$nid] = strlen($title) > 50 ? substr($title, 0, 50).'...' : $title;
      }
      $form['related_issues']['rel_iss_check'] = array(
        '#type' => 'checkboxes',
        '#options' => $options
      );
    }
  }
  $form['dupe_count'] = array(
    '#type' => 'hidden',
    '#id' => 'dupe_count',
    '#default_value' => 0
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#attributes' => array('class' => 'submit-issue'),
    '#value' => t('SUBMIT NEW ISSUE'),
    '#id' => 'save_issue',
    '#prefix' => '<label class="before-submit">Your issue will go live immediately, but a moderator will edit it soon to assign categories, look for duplicates, or make format changes</label>',
    '#suffix' => ' <div class="clear"></div>'
  );
  $form['issue_cont_close'] = array(
    '#type' => 'markup',
    '#value' => '</div></div>'
  );
  $form['#cache'] = TRUE;
  return $form;
}

/*
 * "issue/create/ahah/answer" callback
 */
function _issue_create_form_answer_textfield($delta, $value = '', $votes = 0) {
  if ($delta < 4) {
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

/*
 * "issue/create/ahah/answer" callback
 */
function issue_create_ahah_answer() {
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
  drupal_json($ahah);
}

/*
 * "issue/related" callback
 */
function issue_related() {
  $form_state = array(
    'storage' => NULL,
    'submitted' => FALSE
  );
  $form_build_id = $_POST['form_build_id'];
  $form = form_get_cache($form_build_id, $form_state);
  $delta = count($_POST['answer']);
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form_state['post'] = $form['#post'] = $_POST;
  $form['#programmed'] = $form['#redirect'] = FALSE;
  $form_state['action'] = $form['#action'];
  $form_state['rebuild'] = TRUE;
  $form_state['choice_count'] = $delta;
  drupal_process_form($form_id, $form, $form_state);
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);
  unset($_SESSION['messages']);
  $textfields = $form['related_issues'];
  $output = drupal_render($textfields);

  drupal_json(array('status' => TRUE, 'data' => $output));
}

/*
 * Get related issues by question
 *
 * TODO -- something strange we have here - this search doesn't make sense at all
 */
function issue_get_related($question) {
  $output = array();
  $language = i18n_get_lang();
  # get words from question
  $words = explode(" ", $question);
  $words = array_filter($words, 'word_array_filter');
  $words = array_filter($words);
  //
  if (!empty($question) && !empty($words)) {
    $result = db_query("
      SELECT nr.nid, nr.title
      FROM {node_revisions} nr
      INNER JOIN {node} n ON nr.nid = n.nid AND nr.vid = n.vid
      WHERE n.status <> 0
        AND n.type = 'poll'
        AND MATCH(nr.body, nr.title) AGAINST ('%s')
        AND n.language = '%s'
      GROUP BY n.nid
      ORDER BY n.nid DESC, nr.vid DESC LIMIT 0,10",
        $question, $language
    );
    while ($row = db_fetch_array($result)) {
      $output[] = $row;
    }
  }
  return $output;
}

/*
 * "issue/create" form validation
 */
function issue_create_form_validate($form, &$form_state) {
  if ($form_state['values']['q_quest'] == '') {
    form_set_error('error', t('Please enter your question'));
  }
  if ($form_state['values']['answer'][0] == '' || $form_state['values']['answer'][1] == '') {
    form_set_error('error', t('You must enter atleast two answers'));
  }
}

/*
 * "issue/create" form submission
 */
function issue_create_form_submit($form, &$form_state) {
  global $user, $base_url;

  $node = new StdClass();
  $node->type       = 'poll';
  $node->create     = time();
  $node->title      = $form_state['values']['q_quest'];
  $node->body       = $form_state['values']['q_context'];
  $node->uid        = $user->uid;
  $node->status     = 1;
  $node->active     = 1;
  # $node->path       =
  $language         = ugc_detect_language($form_state['values']['q_quest']);
  $node->language   = $language;
  $node->field_mod_status[0]['value'] = 0;
  if (!user_access('administer nodes')) {
    # uncomment it if you want to moderate the contents
    # $node->active = 0;
  }
  $count = count($form_state['values']['answer']);
  for ($i = 0; $i < $count; $i++) {
    $node->choice[$i]['chtext']  = $form_state['values']['answer'][$i];
    $node->choice[$i]['chorder'] = $i;
    $node->choice[$i]['chvotes'] = 0;
  }
  node_save($node);
  # @rules: Create new content fired

  // New SET NOTIFY LOG
  $variable = array('qid' => $node->nid, 'q_title' => $node->title, 'uid' => $user->uid);
  set_notify_log($user->uid, $node->nid, 'add_question', $variable);
  // New SET NOTIFY LOG

  # add alias TODO - why the hell do we need pathauto anyway?!
  $dst = clean_url(myTruncate($node->title, 100, ''), '', '-', $node->nid);
  $url = 'node/' . $node->nid;
  path_set_alias($url, $dst, '', $language);

  # related issues
  if (!empty($form_state['values']['rel_iss_check'])) {
    $related = array(
      'nid'           => $node->nid,
      'content_types' => array('content_types' => array('poll' => 'poll')),
      'taxonomy'      => array(''),
      'manual'        => array(
        'enable' => 1,
        'nodes' => array(
          'poll' => array(
            'nids' => array_combine(
              $form_state['values']['rel_iss_check'],
              $form_state['values']['rel_iss_check']
            ),
          ),
        ),
      ),
      'sort'          => array('criteria' => 'none'),
    );
    issue_noderecommendation($node->nid, $related);
  }
  cache_clear_all();

  /*
  drupal_set_message(t('Your issue has been added.  It will be reviewed by 3 moderators but is available immediately.
'), $type = 'success');
  */

  # don't know what this means
  $_SESSION['post'] = '';

  $path = drupal_lookup_path('alias', 'node/'.$node->nid, $language);
  if ($path === false) {
    $path = 'node/'.$node->nid;
  }

  drupal_goto($base_url . '/' . $language . '/' . $path);
}

/*
 * Add values to noderecommendation table
 *
 * @nid     : Node Id
 * @related : Associative array containing
 */
function issue_noderecommendation($nid, $related) {
  if (module_exists("noderecommendation")) {
    db_query("INSERT INTO {noderecommendation_node} (nid, data) VALUES (%d, '%s')", $nid, serialize($related));
  }
}










/*****************************************
******************************************
******************************************
******************************************/



// issue search form
function issue_search_form(&$form_state) {
//$form['#method'] = 'get';
  $key = arg(1) == '0' ? '' : check_plain(arg(1));
  $subject = check_plain(arg(2));
  $area = check_plain(arg(3));
  $detail = check_plain(arg(4));
  $getcountry = check_plain(arg(5));
  $getState = check_plain(arg(6));
  $getCity = check_plain(arg(7));

  $inline = 'function clrForm(thisform){jQuery(":input", "#issue-search-form").not(":button, :submit, :hidden").val("").removeAttr(":selected");}';
  drupal_add_js($inline, 'inline');


  $form['issue_key'] = array(
    '#type' => 'textfield',
    '#size' => 40,
    '#default_value' => $key
  );
  $form['category_mark'] = array(
    '#type' => 'markup',
    '#value' => t('FILTER BY CATEGORY') . '<br /><div class="clr"></div>'
  );
  /* categories */
  $vid = db_result(db_query("SELECT vid FROM {vocabulary} WHERE name = '%s' AND module = '%s'", 'Sections', 'taxonomy'));
  $client_select = db_query("SELECT t.tid AS cat_id, t.name AS cat_name FROM term_data t RIGHT JOIN term_hierarchy h ON t.tid = h.tid where h.parent='0' AND t.vid = '$vid'");
  $options[''] = t('SUBJECT');
  while ($list = db_fetch_object($client_select)) {
    $cnt = taxonomy_term_count_nodes($list->cat_id);
    if ($cnt != 0) {
      $options[$list->cat_id] = t(stripslashes($list->cat_name));
    }
  }
  $form['subject'] = array('#type' => 'select',
    '#options' => $options,
    '#prefix' => '<div style="float:left;">',
    '#suffix' => '</div>',
    '#ahah' => array('wrapper' => 'sub-cat-wrapper',
      'event' => 'change',
      'path' => 'issue/ahah/category/scat',
      'effect' => 'fade',
      'method' => 'replace'),
    '#attributes' => array('class' => 'selectbox-sm'),
    '#default_value' => $subject,
    '#id' => 'subject');
// get first level category
  $form['defarea'] = array(
    '#type' => 'hidden',
    '#default_value' => $area
  );
  $form['defdetail'] = array(
    '#type' => 'hidden',
    '#default_value' => $detail
  );
  $form['sub_categories'] = array(
    '#type' => 'markup',
    '#value' => '<div id="sub-cat-wrapper" style="float:left"></div>',
  );
  $form['sub_sub_categories'] = array(
    '#type' => 'markup',
    '#value' => '<div id="sub-sub-cat-wrapper" style="float:left">
                                                </div>',
    '#suffix' => '<br /><div class="clr"></div>');
  $form['location_mark'] = array(
    '#type' => 'markup',
    '#value' => t('FILTER BY LOCATION') . '<br /><div class="clr"></div>'
  );
// location
  $countries[''] = t('COUNTRY');


  /*   * Ralldev : 481* */
  global $language;
  $curLanguage = $language->language;
  $cck_country = db_query("select cc.field_issue_country_value from content_field_issue_country cc, node n where cc.nid = n.nid and n.language = '$curLanguage' group by field_issue_country_value");
  /*   * */

  while ($ccklist = db_fetch_object($cck_country)) {
    if (!empty($ccklist->field_issue_country_value))
      $countries[$ccklist->field_issue_country_value] = $ccklist->field_issue_country_value;
  }
//  array_filter($countries, 'strlen');
  $form['country'] = array('#type' => 'select',
    '#options' => $countries,
    '#prefix' => '<div style="float:left;">',
    '#suffix' => '</div>',
    '#ahah' => array('wrapper' => 'state-wrapper',
      'path' => 'issue/ahah/location/state',
      'effect' => 'fade',
      'event' => 'change',),
    '#attributes' => array('class' => 'selectbox-sm'),
    '#default_value' => $getcountry,
    '#id' => 's_country');

// default state, city
  $form['defstate'] = array(
    '#type' => 'hidden',
    '#default_value' => $getState
  );
  $form['defcity'] = array(
    '#type' => 'hidden',
    '#default_value' => $getCity
  );
  $form['cur_language'] = array(
    '#type' => 'hidden',
    '#value' => $curLanguage
  );
  $form['state_div'] = array(
    '#type' => 'markup',
    '#value' => '<div id="state-wrapper" style="float:left"></div>'
  );
  $form['city_div'] = array(
    '#type' => 'markup',
    '#value' => '<div id="city-wrapper" style="float:left"></div>',
    '#suffix' => '<br /><div class="clr"></div>'
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('SUBMIT'),
    '#attributes' => array(
      'class' => 're-submit light floatleft')
  );
  $form['search'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#attributes' => array('class' => 'search-button')
  );
  $form['reset_btn'] = array(
    '#type' => 'markup',
    '#value' => '<input type="button" value="' . t('CLEAR OPTIONS') . '" name="reset" onclick="javascript:clrForm(this.form)" class="re-submit light floatleft" />');
  return $form;
}

// issue search form submit
function issue_search_form_submit($form, &$form_state) {
//echo '<pre>';print_r($form_state);exit;
  $key = $form_state['values']['issue_key'];
  $key = $key != "" ? $key : 0;

  $subject = $form_state['values']['subject'];
  $subject = $subject != "" ? $subject : 0;
  $area = $form_state['clicked_button']['#post']['area'];
  $area = $area != "" ? $area : 0;
  $detail = $form_state['clicked_button']['#post']['detail'];
  $detail = $detail != "" ? $detail : 0;

  $country = $form_state['values']['country'];
  $country = $country != "" ? $country : 0;
  $state = $form_state['clicked_button']['#post']['state'];
  $state = $state != "" ? $state : 0;
  $city = $form_state['clicked_button']['#post']['city'];
  $city = $city != "" ? $city : 0;

// $path = 'issues/?key='.$key.'&subject='.$subject.'&area='.$area.'&detail='.$detail.'&country='.$country.'&state='.$state.'&city='.$city;
  $path = 'issues/' . $key . '/' . $subject . '/' . $area . '/' . $detail . '/' . $country . '/' . $state . '/' . $city;
  drupal_goto($path);
}

function issue_ajax($task = '', $nid = '') {
  global $base_url, $user;
  switch ($task) {
    case 'debate_statistics':
      $result = '<div id="debate_statistic" width="520" height="360">
        <div id="container" class="highcharts-container" style="height:400px; width: 100%; margin: 0 auto; clear:both"></div>
        <div id="resource" style="height:auto; width: 400px; margin: 0 auto; clear:both"></div>
</div>';
      break;

  }
  echo $result;
}
