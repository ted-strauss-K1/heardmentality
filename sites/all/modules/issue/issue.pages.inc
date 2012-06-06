<?php

// $Id: issue.pages.inc,v 1.1.2.2 2010/06/22 11:33:06 mirodietiker Exp $

/**
 * @file
 * Page callbacks for the issue module.
 */

/**
 * List all issue as a page.
 */
function report_percent($nid='') {
  global $base_url, $user, $base_root, $base_path;
  $output = '';
  $filter = '';
  $incflt = '';
  $opt = '';
  if (!is_numeric($nid))
    return 'No Data Found';

  $vans = "select * from {poll_choices} where  nid='" . $nid . "' ORDER BY chorder";

  $vlist = ExecuteQuery($vans, "select");
  $cnt_ans = count($vlist); //кол-во ответов
  //drupal_add_js(drupal_get_path('module', 'issue') . "/js/highcharts/highcharts.js");

  $inline = "var example = 'bar-stacked',
            theme = 'skies'";
  drupal_add_js($inline, 'inline');

  $ans_array = array();
  for ($ab = 0; $ab < $cnt_ans; $ab++) {
    $short_answer = get_short_answer($nid, $vlist[$ab]['chorder']);
    $answer = $short_answer != '' ? $short_answer : $vlist[$ab]['chtext'];
    $answer = substr(t(addslashes($answer)), 0, 16);
    array_push($ans_array, $answer);
  }
  $result = report_percent_broken($nid, '', $_REQUEST);
  //$ans = $result['divide'];
  if ($_REQUEST['dochg'] == '') {
    $ans = $result['divide'];
    $xtitle = "'" . "'";
  }
  else {
    $ans = $ans_array;
    $ans_array = $result['divide'];
    $xtitle = "'" . $_REQUEST['dochg'] . "'";
  }

  $cnt = $result['cnt'];

  foreach ($ans as $key => $value) {
    $ins_script .= "{name: '" . t(addslashes($ans[$key])) . "',data: " . $cnt[$key] . "},";
  }

  $per = json_encode($result);
  $inc = rtrim($ins_script, ',');

  $filter = (!empty($_REQUEST['dochg'])) ? $_REQUEST['dochg'] : '';

  if (!empty($filter)) {

    $incflt = '<script>jQuery(document).ready(function() {jQuery("#dochg").val(\'' . $filter . '\');});</script>';
  }


  $output .= '
<div id="contentr1">
	' . $incflt . '
     <div>
     <form id="form1" name="form1" method="post" action="' . request_uri() . '#results">
  <select name="dochg" id="dochg">
	<option value="">' . t('Filter') . '</option>
	<option value="age">' . t('Age') . '</option>
	<option value="gender">' . t('Gender') . '</option>
    <option value="religion">' . t('Religion') . '</option>
    <option value="ethnicity">' . t('Ethnicity') . '</option>
    <option value="income">' . t('Income') . '</option>
    <option value="marital">' . t('Marital') . '</option>
    <option value="sex_orient">' . t('Sexual Orientation') . '</option>
    <option value="education">' . t('Education Level') . '</option>

  </select>
  <span id="fopt" ></span>
 </form></div>
    <div id="chart_div" style=" width:300px; min-height: 280px;">
    </div>
</div>';
  return $output;
}

function report_percent_broken($nid = '', $aid = '', $array = '') {
  global $user, $base_root, $base_path;
  $filter = '';
  $filter = (!empty($array['dochg'])) ? $array['dochg'] : '';
  $vans = "select * from {poll_choices} where  nid='" . $nid . "'  order by chorder";

  $vlist = ExecuteQuery($vans, "select");
  // IMPORTANT get translate nid (tnid) for current node
  $nid = get_tnid($nid);

  switch ($filter) {
    case 'gender':
      $answer['divide'] = array('male', 'female', 'undefined');
      foreach ($answer['divide'] as $key => $list) {
        if ($list == 'male')
          $gen = 1;
        elseif ($list == 'female')
          $gen = 2;
        else
          $gen = '0';

        for ($ab = 0; $ab < count($vlist); $ab++) {
          $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND u.gender='" . $gen . "' ";
          $tcnt = ExecuteQuery($query, "norows");
          $answer_cnt[$ab][$key] = $tcnt;
        }
      }

      break;
    case 'age':
      $answer['divide'] = array('18-30', '30-50', '50 above', 'undefined');

      foreach ($answer['divide'] as $key => $value) {
        if ($key == 0) {
          $query_ins = "AND u.age BETWEEN '18' AND '30' ";
        }
        elseif ($key == 1) {
          $query_ins = "AND u.age BETWEEN '31' AND '50'";
        }
        elseif ($key == 2) {
          $query_ins = "AND u.age>='51' ";
        }
        else {
          $query_ins = "AND u.age='0' ";
        }

        for ($ab = 0; $ab < count($vlist); $ab++) {
          $query = "select * from {poll_votes} as p left join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' " . $query_ins;
          $tcnt = ExecuteQuery($query, "norows");
          $answer_cnt[$ab][$key] = $tcnt;
        }
      }

      break;
    case 'religion':
      $answer['divide'] = array('Christian', 'Muslim', 'Jewish', 'Hindu', 'Buddhist', 'Other', 'undefined');

      foreach ($answer['divide'] as $key => $list) {
        if ($list == 'undefined') {
          $reg = '0';
        }
        else {
          $reg = $list;
        }
        for ($ab = 0; $ab < count($vlist); $ab++) {
          $query = "select * from {poll_votes} as p left join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND religion='" . $reg . "'";
          $tcnt = ExecuteQuery($query, "norows");
          $answer_cnt[$ab][$key] = $tcnt;
        }
      }

      break;
    case 'ethnicity':
      $answer['divide'] = array('Caucasian', 'Black', 'Asian', 'Indian', 'Semetic', 'Latin', 'Aborigines', 'undefined');

      foreach ($answer['divide'] as $key => $list) {
        if ($list == 'undefined')
          $reg = '0';
        else
          $reg = $list;

        for ($ab = 0; $ab < count($vlist); $ab++) {
          $query = "select * from {poll_votes} as p left join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND ethnic='" . $reg . "'";
          $tcnt = ExecuteQuery($query, "norows");
          $answer_cnt[$ab][$key] = $tcnt;
        }
      }

      break;
    case 'income':
      $answer['divide'] = array('$0-$9,999', '$10,000 - $19,999', '$20,000 - $39,999', '$40,000 - $69,999', '$70,000 - $99,999', '$100,000 - $149,999', '$150,000 - $299,999', '$300,000', 'undefined');

      foreach ($answer['divide'] as $key => $list) {
        if ($list == 'undefined') {
          $reg = '0';
        }
        else {
          $reg = $list;
        }
        for ($ab = 0; $ab < count($vlist); $ab++) {
          $query = "select * from {poll_votes} as p left join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND income='" . $reg . "'";
          $tcnt = ExecuteQuery($query, "norows");
          $answer_cnt[$ab][$key] = $tcnt;
        }
      }

      break;
    case 'marital':
      $answer['divide'] = array('Single', 'Married', 'Divorced', 'Widow', 'undefined');

      foreach ($answer['divide'] as $key => $list) {
        if ($list == 'undefined')
          $reg = '0';
        else
          $reg = $list;

        for ($ab = 0; $ab < count($vlist); $ab++) {
          $query = "select * from {poll_votes} as p left join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND marital='" . $reg . "'";
          $tcnt = ExecuteQuery($query, "norows");

          $answer_cnt[$ab][$key] = $tcnt;
        }
      }

      break;
    case 'sex_orient':
      $answer['divide'] = array('Straight', 'Gay', 'Bisexual', 'Transgender', 'undefined');
      foreach ($answer['divide'] as $key => $list) {
        if ($list == 'undefined')
          $reg = '0';
        else
          $reg = $list;
        for ($ab = 0; $ab < count($vlist); $ab++) {
          $query = "select * from {poll_votes} as p left join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND sorient='" . $reg . "'";
          $tcnt = ExecuteQuery($query, "norows");
          $answer_cnt[$ab][$key] = $tcnt;
        }
      }

      break;
    case 'education':
      $answer['divide'] = array('No High School', 'High School', 'Technical College', 'Masters Degree', 'PhD', 'undefined');

      foreach ($answer['divide'] as $key => $list) {
        if ($list == 'undefined')
          $reg = '0';
        else
          $reg = $list;
        for ($ab = 0; $ab < count($vlist); $ab++) {
          $query = "select * from {poll_votes} as p left join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND edu='" . $reg . "'";
          $tcnt = ExecuteQuery($query, "norows");
          $answer_cnt[$ab][$key] = $tcnt;
        }
      }

      break;

    default:
      $answer['divide'] = array('Total Votes');
      foreach ($vlist as $key => $chvote) {
        $total_votes[] = (int) $chvote['chvotes'];
      }

      $answer_cnt[] = $total_votes;
      break;
  }

  $answer['cnt'] = $answer_cnt;
  return $answer;
}

function report_get_ans_range($nid='', $range='') {
  switch ($range) {
    case 'start':
      $query = "select date(date_voted) as dat from {poll_votes} where nid='" . $nid . "' ORDER BY date_voted ASC LIMIT 0,1 ";
      $answer = ExecuteQuery($query, "select");
      break;
    case 'end':
      $query = "select date(date_voted) as dat from poll_votes where nid='" . $nid . "' ORDER BY date_voted DESC LIMIT 0,1 ";
      $answer = ExecuteQuery($query, "select");
      break;
    default:
      $query = "select count(*) as cnt from poll_votes where nid='" . $nid . "' ";
      $answer = ExecuteQuery($query, "select");
      break;
  }
  return $answer[0];
}

function report_answer_details($nid = '', $aid = '', $action = '', $date = '') {
  switch ($action) {
    case 'percent':
      if ($_REQUEST['fopt']) {
        $opt = filter_opt($_REQUEST);

        $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $aid . "' $opt ";
        $answer = ExecuteQuery($query, "norows");
      }
      else {

        $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $aid . "' ";
        $answer = ExecuteQuery($query, "norows");
      }

      return $answer;
      break;
    case 'timeline':
      $query = "select count(*) as cnt from {poll_votes} where nid='" . $nid . "' and chorder='" . $aid . "'AND date(date_voted)<='" . $date . "' ";
      $answer = ExecuteQuery($query, "select");

      return $answer ? $answer[0]['cnt'] : 'null';

      break;
  }
}

function report_graph($nid='') {

  global $base_url, $user, $base_path;
  $qid = $nid;
  $nid = get_tnid($nid);
  $output = '';

  $vans = "select * from {poll_choices} where  nid=$qid order by chorder";
  $vlist = ExecuteQuery($vans, "select");
  $cnt_ans = count($vlist);

  drupal_add_js(drupal_get_path('module', 'issue') . "/js/highstock/highstock.js");

  drupal_add_js(drupal_get_path('module', 'issue') . "/js/charts.js");
  //$output.= "<script type='text/javascript' language='javascript'>";

  $query = "select date(date_voted) as dat from {poll_votes} where nid='" . $nid . "' ORDER BY date_voted DESC";
  $list = ExecuteQuery($query, "select");
  $s1 = array();
  $grid = array();

  $srange = report_get_ans_range_history($nid, 'start');
  $erange = report_get_ans_range_history($nid, 'end');
  $count = report_get_ans_range_history($nid);

  $query = "select DATEDIFF(date(now()),'" . $srange['dat'] . "') as diff,date(now()) as today";
  $overall_range = ExecuteQuery($query, "select");
  $frange = $overall_range[0]['diff'];
  $drange = dates_range($srange['dat'], $overall_range[0]['today']);
  $drange = array_reverse($drange);

  for ($ab = 0; $ab < $cnt_ans; $ab++) {
    // short answers
    $short_answer = get_short_answer($qid, $vlist[$ab]['chorder']);
    $answer = $short_answer != '' ? $short_answer : $vlist[$ab]['chtext'];
    $answer = substr(t(addslashes($answer)), 0, 16);
    $i = $ab + 1;
    $ans = array();

    if (count($drange) > 6) {
      for ($mn = $frange; $mn >= 0; $mn--) {
        $date = $drange[$mn];
        $inc_this = report_answer_details_history($nid, $vlist[$ab]['chorder'], 'timeline', $date);
        array_push($ans, $inc_this);
      }
      $ins_sc = '[' . implode(',', $ans) . ']';
      array_push($grid, "'" . $answer . "'");
      $insdata.="{name :'" . $answer . "', data: " . $ins_sc . "},";

      $dexp = explode('-', $srange['dat']);
      $year = $dexp[0];
      $month = $dexp[1] - 1;
      $dat = $dexp[2];
      $sdate = "Date.UTC(" . $year . "," . $month . "," . $dat . ", 0, 0, 0)";
      $tickint = "";
    }
    else {
      for ($mn = 6; $mn >= 0; $mn--) {
        $year = date("Y");
        $month = date("m");
        $dat = date("d") - $mn;
        $date = date('Y, m, d', mktime(0, 0, 0, $month, $dat, $year));
        $inc_this = report_answer_details_history($nid, $vlist[$ab]['chorder'], 'timeline', $date);
        array_push($ans, '[Date.UTC(' . $date . ')' . ', ' . $inc_this . ']');
      }
      $ins_sc = '[' . implode(',', $ans) . ']';
      array_push($grid, "'" . $answer . "'");
      $output2[$ab]['data'] = $ins_sc;
      $output2[$ab]['name'] = $answer;
      $insdata.="{name :'" . $answer . "', data: " . $ins_sc . "},";
      $sdate = "Date.UTC(" . $year . "," . ($month - 1) . "," . (date("d") - 6) . ")";
      $tickint = ",tickInterval: 24 * 3600 * 1000 // one day";
    }
  }

  $year = date("Y");
  $month = date("m") - 1;
  $dat = date("d");
  $edate = "Date.UTC(" . $year . "," . $month . "," . $dat . ")";
  // $script.=$ins_sc;

  $output.='<div id="container_graph" class="highcharts-container" style="min-height:280px; width: 100%; "></div>
        <div id="resource" style="height:auto; width: 100%; margin: 0 auto; clear:both"></div>';
  return $output;
}

function report_map($nid='') {
  drupal_add_js(drupal_get_path('module', 'issue') . '/js/google_map.js');

  $output = '<script type="text/javascript"
    src="https://maps.google.com/maps/api/js?sensor=false">
    </script>';
  $output .= '<div id="map_div" style="width: 100%; min-height: 280px"></div>';

  return $output;
}

// report vote percent(redesign)
function report_vote_percent() {
  $perc .= '<p>90% of the voters are between the ages of 20 and 30.</p>';
  $perc .= '<p>65% of Christians voted Yes.</p>';
  $perc .= '<p>Users with Masters Degrees are 2 times as likely to vote No.</p>';
  $perc .= '<p>65% of Christians voted Yes.</p>';
  $perc .= '<p>74% Income Range between $40,000 - $69,000 are voted No.</p>';
  $perc .= '<p>15% Asian people voted Yes.</p>';
  return $perc;
}

function report_get_zip($code = '', $ccode = '') {

  $query = array('postalcode' => $code, 'maxrows' => 1);
  $result = geonames_query('postalcodesearch', $query);

  return $result;
}

// add new issue

function issue_create() {
  $issueForm = drupal_get_form('issue_create_form');
  return $issueForm;
}

function issue_create_form(&$form_state) {
  //drupal_add_js( drupal_get_path('module', 'question') . '/scripts/post_list.js');
  if (isset($form_state['action'])) {
    $form['#action'] = $form_state['action'];
  }
  //$form['#attributes'] = array('onsubmit' => 'return validate_question()');
  $form['issue_cont'] = array(
    '#type' => 'markup',
    '#value' => '<div class="grey-box">
                                        <h2 class="din">' . t('Add an Issue') . '</h2>
                                        <div class="new-issue">
                                        <hr class="short2">');
  $form['title_div'] = array(
    '#type' => 'markup',
    '#value' => '<label for="" class="add-on"><div class="number dinbold">1</div><span class="title ">' . t('Question') . '</span><br>
                                                                <span class="guides">' . t('Max 140 chars.') . '</span></label>');
  $form['q_quest'] = array(
    '#type' => 'textarea',
    '#suffix' => '<hr class="short2">', '#id' => 'q_quest',
    '#ahah' => array('path' => 'issue/get_related_issues', 'wrapper' => 'related-issues', 'effect' => 'fade'),
    '#attributes' => array('onkeyup' => 'CountlimitChars()', 'rows' => 0, 'cols' => 0),
  );
  $form['desc_div'] = array(
    '#type' => 'markup',
    '#value' => '<label for="" class="add-on"><div class="number dinbold">2</div><span class="title ">' . t('Context') . '</span><br><span class="guides">' . t('Enter a brief description or backstory to provide context. You may include links.') . '</span></label>');
  $form['q_context'] = array(
    '#type' => 'textarea',
    '#rows' => 4,
    '#suffix' => '<hr class="short2">',
    '#id' => 'Question',
    '#attributes' => array('rows' => 0, 'cols' => 0));

  if (isset($form_state['choice_count'])) {
    $choice_count = $form_state['choice_count'];
  }
  else {
    $choice_count = 2;
  }

  $form['choice_wrapper'] = array(
    '#tree' => FALSE,
    '#prefix' => '<div class="clear-block" id="poll-choice-wrapper">',
    '#suffix' => '</div>',
  );


// Container for just the poll choices.
  $form['choice_wrapper']['answer'] = array(
    '#prefix' => '<div id="poll-choices">
                        <label for="" class="add-on"><div class="number dinbold">3</div><span class="title ">' . t('Answers') . '</span> <br><span class="guides">' . t('Enter at least two answers.') . '</span></label>',
    '#suffix' => '</div><div class="clear"></div>',
    '#theme' => 'issue_answer',
  );


// Add the current choices to the form.
  for ($delta = 0; $delta < $choice_count; $delta++) {
    $form['choice_wrapper']['answer'][$delta] = _issue_answer_form($delta);
  }


// We name our button 'poll_more' to avoid conflicts with other modules using
  // AHAH-enabled buttons with the id 'more'.
  $form['choice_wrapper']['poll_more'] = array(
    '#type' => 'submit',
    '#value' => t('+ Add another answer'),
    '#description' => t("If the amount of boxes above isn't enough, click here to add more choices."),
    '#weight' => 1,
    '#ahah' => array(
      'path' => 'issue/autotextfields/callback',
      'wrapper' => 'poll-choices',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#attributes' => array('class' => 'add-answer light'),
    '#suffix' => '<div class="clear"></div>
                                <hr class="bottom">',
  );



  $form['exist_check'] = array('#type' => 'hidden', '#value' => '', '#id' => 'exist_check');


  $form['related_issues'] = array(
    '#title' => t("Related Issues"),
    '#prefix' => '<div id="related-issues">',
    '#suffix' => '</div>',
    '#type' => 'fieldset',
  );

  if ($form_state['values']['q_quest']) {

    $question = $form_state['values']['q_quest'];

    // define a string variable to contain callback output
    $output = "";

    // loop through the taxonomy tree and fetch child taxonomies
    $options = array();

    $res = get_releated_issues($question);

    if (!empty($res)) {
      $nids = $res['nid'];
      $contents = $res['content'];
      $i = 0;
      if (!empty($contents)) {
        foreach ($contents as $key => $result) {
          $array[$nids[$key]] = $result;

          $i++;
        }

        $form['related_issues']['rel_iss_check'] = array(
          '#type' => 'checkboxes',
          '#options' => $array);
      }
      else {
        $form['related_issues']['no_rel'] = array(
          '#type' => 'markup',
          '#value' => 'No Related Issues');
      }
    }
    else {
      $form['related_issues']['no_rel'] = array(
        '#type' => 'markup',
        '#value' => 'No Related Issues');
    }
  }

  $form['dupe_count'] = array(
    '#type' => 'hidden',
    '#id' => 'dupe_count',
    '#default_value' => 0);
  //$form['#validate'][] = 'issue_create_form_validate';

  $form['submit'] = array(
    '#type' => 'submit',
    '#attributes' => array('class' => 'submit-issue'),
    '#value' => t('SUBMIT NEW ISSUE'),
    '#id' => 'save_issue',
    '#prefix' => '<label class="before-submit">Your issue will go live immediately, but a moderator will edit it soon to assign categories, look for duplicates, or make format changes</label>',
    '#suffix' => ' <div class="clear"></div>');
  //$form['#redirect'] = '';
  $form['issue_cont_close'] = array(
    '#type' => 'markup',
    '#value' => '</div></div>');
  $form['#validate'][] = 'validate_issue_add';
  $form['#cache'] = TRUE;
  return $form;
}

function issue_form_validate($form, &$form_state) {
  if ($form['form_id']['#post']['answer'][0] == '' || $form['form_id']['#post']['answer'][1] == '') {
    $error = 'You must fill in at least two choices.';
  }
  return $error;
}

function issue_autotextfields_callback() {
  $delta = count($_POST['answer']);

  // Build our new form element.
  $form_element = _issue_answer_form($delta);
  // drupal_alter('form', $form_element, array(), 'issue/autotextfields/callback');
  // Build the new form.
  $form_state = array('storage' => NULL, 'submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];

  // Add the new element to the stored form. Without adding the element to the
  // form, Drupal is not aware of this new elements existence and will not
  // process it. We retreive the cached form, add the element, and resave.
  $form = form_get_cache($form_build_id, $form_state);
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form['choice_wrapper']['answer'][$delta] = $form_element;
  form_set_cache($form_build_id, $form, $form_state);
  $form += array(
    '#post' => $_POST,
    '#programmed' => FALSE,
  );
  $form_state['post'] = $_POST;
  // Build, validate and if possible, submit the form.
  $form_state['action'] = $form['#action'];
  $form_state['rebuild'] = TRUE;
  drupal_process_form($form_id, $form, $form_state);
  // Rebuild the form.
  $form = form_builder($form_id, $form, $args, $form_state);

//  $validate = issue_form_validate($form, $form_state);
//  if($validate){$delta = 1;}
  // Render the new output.
  unset($_SESSION['messages']);
  $choice_form = $form['choice_wrapper']['answer'];
  unset($choice_form['#prefix'], $choice_form['#suffix']); // Prevent duplicate wrappers.
  $choice_form[$delta]['#attributes']['class'] = empty($choice_form[$delta]['#attributes']['class']) ? 'ahah-new-content' : $choice_form[$delta]['#attributes']['class'] . ' ahah-new-content';
  //$choice_form[$delta]['chvotes']['#value'] = 0;
  $output = drupal_render($choice_form);

  drupal_json(array('status' => TRUE, 'data' => $output));
}

function _issue_answer_form($delta, $value = '', $votes = 0) {
  $form = array(
    '#tree' => TRUE,
  );

  // We'll manually set the #parents property of these fields so that
  // their values appear in the $form_state['values']['choice'] array.
  // limited fields 10 (0 to 9)
  if ($delta == 0 || $delta == 1) {
    // $req = TRUE;
  }
  else {
    //$req = FALSE;
  }
  if ($delta < 10) {
    $form['chtext'] = array(
      '#type' => 'textfield',
      '#default_value' => $value,
      '#parents' => array('answer', $delta),
      '#required' => $req,
      '#id' => 'Answer',
    );
  }
  else {
    $form['error_msg'] = array(
      '#type' => 'markup',
      '#value' => 'Maximum Fields Exceeded',
    );
  }
  return $form;
}

function issue_related_callback() {

  $form_state = array('storage' => NULL, 'submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  $form = form_get_cache($form_build_id, $form_state);
  $delta = count($_POST['answer']);

  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form_state['post'] = $form['#post'] = $_POST;
  $form['#programmed'] = $form['#redirect'] = FALSE;
// Stash original form action to avoid overwriting with drupal_rebuild_form().
  $form_state['action'] = $form['#action'];
  $form_state['rebuild'] = TRUE;
  $form_state['choice_count'] = $delta;
  drupal_process_form($form_id, $form, $form_state);
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);

  //$form = form_builder($form_id, $form, $form_state);
  unset($_SESSION['messages']);
  $textfields = $form['related_issues'];
  $output = drupal_render($textfields);


// Final rendering callback.
  print drupal_json(array('status' => TRUE, 'data' => $output));
  exit();
}

function issue_create_form_submit($form, &$form_state) {
  //echo '<pre>'; print_r($form_state); exit;
  global $user, $base_url;


  $account = user_load(array('uid' => $user->uid));
  $node = new StdClass();
  $node->type = 'poll';
  $node->create = time();
  $node->title = $form_state['values']['q_quest'];
  $node->body = $form_state['values']['q_context'];
  $node->uid = $account->uid;
  $node->status = 1;
  $node->active = 1;
  //$node->path=
  // LANGUAGE DETECTION
  // detect language from inputs using googleapis
  $inputLanguage = get_input_language($form_state['values']['q_quest']);

  $node->language = $inputLanguage; // set user input language
  $node->field_mod_status[0]['value'] = 0;
  if (!user_access('administer nodes')) {
    $node->active = 1;
  }
  $count = count($form_state['values']['answer']);
  for ($i = 0; $i < $count; $i++) {
    $node->choice[$i]['chtext'] = $form_state['values']['answer'][$i];
    $node->choice[$i]['chorder'] = $i;
    // Make sure all votes are 0 initially
    $node->choice[$i]['chvotes'] = 0;
  }

  node_save($node);

  /* New SET NOTIFY LOG */
  //set_notify_log($uid , $message_id, $nid, $variable)
  $qid = $node->nid;
  $qtitle = $node->title;
  $variable = array('qid' => $qid, 'q_title' => $qtitle, 'uid' => $user->uid);
  set_notify_log($user->uid, $qid, 'add_question', $variable);
  /* New SET NOTIFY LOG */
  //url alias
  $dst = clean_url(myTruncate($node->title, 100, ''), '', '-', $node->nid);
  $url = 'node/' . $node->nid;
  // db_query("INSERT INTO {url_alias} (src, dst, language) VALUES ('%s', '%s', '%s')", $url, $dst, $inputLanguage);

  path_set_alias($url, $dst, '', $inputLanguage);



  //Related Issues
  if (!empty($form_state['values']['rel_iss_check'])) {
    $cont_type = array('content_types' => array('poll' => 'poll'));
    $relatedissues = array_combine($form_state['values']['rel_iss_check'], $form_state['values']['rel_iss_check']);
    $arrayid = array('nids' => $relatedissues);
    $manual = array('enable' => 1, 'nodes' => array('poll' => $arrayid));
    $related = array('nid' => $node->nid, 'content_types' => $cont_type, 'taxonomy' => array(''), 'manual' => $manual, 'sort' => array('criteria' => 'none'));
    db_query("INSERT INTO {noderecommendation_node} (nid, data) VALUES (%d, '%s')", $node->nid, serialize($related));
  }

  cache_clear_all();
  $output = drupal_set_message(t('Your issue has been added.  It will be reviewed by 3 moderators but is available immediately.
'), $type = 'success');
  unset($_SESSION['post']);
  $_SESSION['post'] = '';
  $path = db_result(db_query("SELECT dst FROM {url_alias} WHERE src = 'node/%d' LIMIT 1", $node->nid));
  if (empty($path))
    $path = drupal_get_path_alias(getPathAlias($node->nid));

  increasepoints('1', $node->nid, '0');
  //_send_qnotify($node->nid);
  //drupal_goto($path);

  drupal_goto($base_url . '/' . $inputLanguage . '/' . $path);
}

function getPathAlias($nid) {
  $alias = 'node/' . $nid;

  //check for an alias using drupal_lookup_path()
  if ((drupal_lookup_path('alias', 'node/' . $nid) !== false))
    $alias = drupal_lookup_path('alias', 'node/' . $nid);

  return $alias;
}

function get_releated_issues($question = '', $cat_id = '', $context = '') {
  //$form = array('#tree'=>TRUE);

  $currLanguage = i18n_get_lang();
  $where_condition = '';
  $words = explode(" ", $question);
  $words = array_filter($words, 'word_array_filter');
  $words = array_filter($words);
  for ($i = 0; $i < count($words); $i++) {
    $wheres2 = array();
    if ($words[$i] != '') {
      $wheres2[] = "  q.title  LIKE CONVERT(_utf8 '%$words[$i]%' USING latin1 ) COLLATE latin1_swedish_ci";
      $wheres[] = implode(' OR ', $wheres2);
    }
  }
  $where_condition = '((' . implode(($match == 'all' ? ') AND (' : ') OR ('), $wheres) . '))';

  if ($context != '') {
    $words = explode(" ", $context);
    for ($i = 0; $i < count($words); $i++) {
      $wheres2 = array();
      if ($words[$i] != '') {
        $wheres2[] = "  q.context  LIKE CONVERT(_utf8 '%$words[$i]%' USING latin1 ) COLLATE latin1_swedish_ci";
        $wheres1[] = implode(' OR ', $wheres2);
      }
    }
    $where_condition .= ' and ((' . implode(($match == 'all' ? ') AND (' : ') OR ('), $wheres1) . '))';
  }
  if ($cat_id != 0) {
    $where_condition .= " and qc.cat in ($cat_id)";
  }
  $text = "$question $context";
  $text = trim($text);
  //printf("SELECT r.nid,r.title FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' AND MATCH(r.body, r.title) AGAINST ('%s') AND n.language = '%s' GROUP BY n.nid  ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10",$text, $currLanguage);
//printf("SELECT count(MATCH(r.body, r.title) AGAINST ('%s')) FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' GROUP BY n.nid ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10",$text,0);
  $count = db_result(db_query("SELECT COUNT(n.nid) FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' GROUP BY n.nid AND MATCH(r.body, r.title) AGAINST ('%s') AND n.language = '%s' ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10", $text, $currLanguage));
  $rel_output.= '<div class="innerbox" style="width:auto;height:auto; overflow:auto; min-height:150px;"><ul>';
  if (($count != 0) && ($question != '')) {
    $rel_count = 1;
    $rel_query = db_query("SELECT r.nid,r.title FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' AND MATCH(r.body, r.title) AGAINST ('%s') AND n.language = '%s' GROUP BY n.nid  ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10", $text, $currLanguage);
    //$sql = "SELECT r.nid,r.title FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' AND n.title LIKE '%$question%' GROUP BY n.nid  ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10";
    //$rel_query = db_query($sql);
    while ($rel_options = db_fetch_object($rel_query)) {

      $form['mycheck_' . $rel_count] = array('#type' => 'checkbox', '#default_value' => $rel_count, '#title' => substr($rel_options->title, 0, 50));


      $rel_output .= substr($rel_options->title, 0, 50) . '...</li>';
      $content[] = substr($rel_options->title, 0, 50);
      $ids[] = $rel_options->nid;
      $rel_count++;
    }
  }
  else {
    $rel_output.= t('No Releated issues available');
  }

  $rel_output.= '</ul></div>';
  $quest = array($rel_count, $content);
  $conResult = array('content' => $content, 'nid' => $ids);
  return $conResult;
  //return $form;
//echo "SELECT q.qid, q.question FROM {question} q  left join question_cat qc on qc.qid=q.qid  WHERE $where_condition  group by q.qid ";
}

// issue list here
function issues_list() {
  $output = '';
  $output .= search_issue_results();
  $output .= '';
  return $output;
}

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


  $form['issue_key'] = array('#type' => 'textfield',
    '#size' => 40,
    '#default_value' => $key);
  $form['category_mark'] = array('#type' => 'markup', '#value' => t('FILTER BY CATEGORY') . '<br /><div class="clr"></div>');
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
  $form['defarea'] = array('#type' => 'hidden', '#default_value' => $area);
  $form['defdetail'] = array('#type' => 'hidden', '#default_value' => $detail);
  $form['sub_categories'] = array('#type' => 'markup',
    '#value' => '<div id="sub-cat-wrapper" style="float:left"></div>',
  );

  $form['sub_sub_categories'] = array('#type' => 'markup',
    '#value' => '<div id="sub-sub-cat-wrapper" style="float:left">
                                                </div>',
    '#suffix' => '<br /><div class="clr"></div>');
  $form['location_mark'] = array('#type' => 'markup', '#value' => t('FILTER BY LOCATION') . '<br /><div class="clr"></div>');
  // location
  $countries[''] = t('COUNTRY');
  // $countryList = geonames_query('countryinfo',NULL);
  //foreach($countryList->results as $country){
  //   $countries[$country['countryname']] = $country['countryname'];
  //}
  //list only the country the issue is
  //$cck_country=db_query("select field_issue_country_value from {content_field_issue_country} group by field_issue_country_value ");

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
  $form['defstate'] = array('#type' => 'hidden', '#default_value' => $getState);
  $form['defcity'] = array('#type' => 'hidden', '#default_value' => $getCity);
  $form['cur_language'] = array('#type' => 'hidden', '#value' => $curLanguage);

  $form['state_div'] = array('#type' => 'markup',
    '#value' => '<div id="state-wrapper" style="float:left"></div>');
  $form['city_div'] = array('#type' => 'markup',
    '#value' => '<div id="city-wrapper" style="float:left"></div>',
    '#suffix' => '<br /><div class="clr"></div>');
  $form['submit'] = array('#type' => 'submit', '#value' => t('SUBMIT'), '#attributes' => array('class' => 're-submit light floatleft'));
  $form['search'] = array('#type' => 'submit', '#value' => t('Search'), '#attributes' => array('class' => 'search-button'));
  $form['reset_btn'] = array('#type' => 'markup', '#value' => '<input type="button" value="' . t('CLEAR OPTIONS') . '" name="reset" onclick="javascript:clrForm(this.form)" class="re-submit light floatleft" />');
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

// search issue results
function search_issue_results__problamatic() {
  global $language;
  $issue = '';
  $curLanguage = $language->language;

  $key = arg(1) != '0' ? arg(1) : '';
  $subject = arg(2) != '0' ? arg(2) : '';
  $area = arg(3) != '0' ? arg(3) : '';
  $detail = arg(4) != '0' ? arg(4) : '';
  $country = arg(5) != '0' ? arg(5) : '';
  $state = arg(6) != '0' ? arg(6) : '';
  $city = arg(7) != '0' ? arg(7) : '';

  $sortValue = arg(8) != '' ? arg(8) : 'all';
  $where = '';
  $groupBy = '';

  $rec_per_page = 5;

  $val = array();
  // conditions key
  if (!empty($key)) {
    $where .= " AND MATCH(nr.title, nr.body) AGAINST('%s*' IN BOOLEAN MODE)";
    $val[] = $key;
  }
  // categories
  if (!empty($detail)) {
    $where .= " AND tn.tid = '%d'";
    $val[] = $detail;
  }
  elseif (!empty($area)) {
    $where .= " AND tn.tid = '%d'";
    $val[] = $area;
  }
  elseif (!empty($subject)) {
    $where .= " AND tn.tid = '%d'";
    $val[] = $subject;
  }
  // locations
  if (!empty($country)) {
    $where .= "AND cc.field_issue_country_value = '%s'";
    $val[] = $country;
  }
  if (!empty($state)) {
    $where .= "AND cs.field_issue_state_value = '%d'";
    $val[] = $state;
  }
  if (!empty($city)) {
    $where .= "AND ct.field_issue_city_value = '%d'";
    $val[] = $city;
  }

  // filter with default language if issue key is empty
  //if($key!=''){
  if ($curLanguage == 'en') {
    $langFilter = "AND (n.language = '$curLanguage' OR n.language = '')";
  }
  else {
    $langFilter = "AND n.language = '$curLanguage'";
  }
  //}
  //$langFilter = $key==''?"AND n.language = '$curLanguage'":'';


  switch ($sortValue) {
    case 'alltime':
      $sortBy = 'ORDER BY COUNT(pv.nid) DESC';
      $groupBy = 'GROUP BY pv.nid';

      $sql = "SELECT pv.nid FROM {poll_votes} AS pv JOIN
                (SELECT DISTINCT(n.nid) FROM {node} AS n
                JOIN {content_field_issue_country} AS cc ON n.nid = cc.nid
                JOIN {content_field_issue_state} AS cs ON n.nid = cs.nid
                JOIN {content_field_issue_city} AS ct ON n.nid = ct.nid
                LEFT JOIN {term_node} AS tn ON n.nid = tn.nid 
                WHERE n.type = 'poll' $langFilter $where) AS temp ON pv.nid = temp.nid $groupBy $sortBy";
      break;
    case '7days':
      $where .= 'AND pv.date_voted >= DATE_SUB(CURDATE(), INTERVAL 7 DAY)';
      $sortBy = 'ORDER BY SUM(pc.chvotes) DESC';
      $groupBy = 'GROUP BY pc.nid';

      $sql = "SELECT DISTINCT(n.nid) FROM {node} AS n JOIN {node_revisions} AS nr ON n.nid = nr.nid
            JOIN {content_field_issue_country} AS cc ON n.nid = cc.nid
            JOIN {content_field_issue_state} AS cs ON n.nid = cs.nid
            JOIN {content_field_issue_city} AS ct ON n.nid = ct.nid
            JOIN {poll_choices} AS pc ON n.nid = pc.nid
            LEFT JOIN {poll_votes} AS pv ON n.nid = pv.nid
            LEFT JOIN {term_node} AS tn ON n.nid = tn.nid
            WHERE n.type = 'poll' $langFilter $where $groupBy $sortBy";

      break;
    case 'views':
      $sortBy = 'ORDER BY COUNT(qv.qid) DESC';
      $groupBy = 'GROUP BY iss.nid';

      $sql = "SELECT iss.nid as nid FROM
                     (SELECT DISTINCT(n.nid) FROM {node} AS n
                    JOIN {content_field_issue_country} AS cc ON n.nid = cc.nid
                    JOIN {content_field_issue_state} AS cs ON n.nid = cs.nid
                    JOIN {content_field_issue_city} AS ct ON n.nid = ct.nid
                    LEFT JOIN {term_node} AS tn ON n.nid = tn.nid
                   WHERE n.type = 'poll' $langFilter $where) AS iss LEFT JOIN {qviews} AS qv ON iss.nid = qv.qid $groupBy $sortBy";

      break;
    default:
      $sortBy = 'ORDER BY n.nid DESC';
      $groupBy = '';

      $sql = "SELECT DISTINCT(n.nid) FROM {node} AS n JOIN {node_revisions} AS nr ON n.nid = nr.nid
            JOIN {content_field_issue_country} AS cc ON n.nid = cc.nid
            JOIN {content_field_issue_state} AS cs ON n.nid = cs.nid
            JOIN {content_field_issue_city} AS ct ON n.nid = ct.nid
            LEFT JOIN {term_node} AS tn ON n.nid = tn.nid
            WHERE n.type = 'poll' $langFilter $where $groupBy $sortBy";

      break;
  }


//echo $sql; exit;

  $sqlcount = ExecuteQuery($sql, 'norows');

  $final = call_user_func_array('sprintf', array_merge((array) $sql, $val));
  $sqlcount = ExecuteQuery($final, 'norows');

  $query = pager_query_new($final, $rec_per_page, 0, $sqlcount);

  $count = db_affected_rows($query);
  if ($sqlcount) {
    while ($result = db_fetch_object($query)) {
      $nid = $result->nid;
      $node = node_load($nid);
      $issue .= node_view(node_load($node->nid), 1);
    }
    $issue .= '<div class="pagination">' . theme('pager', array(), $rec_per_page) . '</div><br class="clear">';
  }
  else {
    $issue .= t('No Issues Found');
  }
  return $issue;
}

/* * ******NEW - Need to make proper****** */

// search issue results
function search_issue_results() {
  global $language;
  $issue = '';
  $curLanguage = $language->language;

  $key = arg(1) != '0' ? arg(1) : '';
  $subject = arg(2) != '0' ? arg(2) : '';
  $area = arg(3) != '0' ? arg(3) : '';
  $detail = arg(4) != '0' ? arg(4) : '';
  $country = arg(5) != '0' ? arg(5) : '';
  $state = arg(6) != '0' ? arg(6) : '';
  $city = arg(7) != '0' ? arg(7) : '';

  $sortValue = arg(8) != '' ? arg(8) : 'all';
  $where = '';
  $groupBy = '';


  $rec_per_page = 5;


  $val = array();
  // conditions key
  if (!empty($key)) {
    $where .= "AND ( nr.title like '%%$key%%' OR  nr.body like '%%$key%%'  OR  (MATCH(nr.title, nr.body) AGAINST('$key*' IN BOOLEAN MODE)) ) ";
  }
  // categories
  if (!empty($detail)) {
    $where .= " AND tn.tid = '$detail' ";
    $val[] = $detail;
  }
  elseif (!empty($area)) {
    $where .= " AND tn.tid = '$area' ";
    $val[] = $area;
  }
  elseif (!empty($subject)) {
    $where .= " AND tn.tid = '$subject' ";
    $val[] = $subject;
  }
  // locations
  if (!empty($country)) {
    $where .= "AND cc.field_issue_country_value = '$country' ";
    $val[] = $country;
  }
  if (!empty($state)) {
    $where .= "AND cs.field_issue_state_value = '$state' ";
    $val[] = $state;
  }
  if (!empty($city)) {
    $where .= "AND ct.field_issue_city_value = '$city' ";
    $val[] = $city;
  }

  // filter with default language if issue key is empty
  //if($key!=''){
  if ($curLanguage == 'en') {
    $langFilter = "AND (n.language = '$curLanguage' OR n.language = '')";
  }
  else {
    $langFilter = "AND n.language = '$curLanguage'";
  }

  switch ($sortValue) {
    case 'alltime':
      $sortBy = 'ORDER BY COUNT(pv.nid) DESC';
      $groupBy = 'GROUP BY pv.nid';

      $sql = "SELECT pv.nid FROM {poll_votes} AS pv JOIN
                (SELECT DISTINCT(n.nid) FROM {node} AS n
                JOIN {content_field_issue_country} AS cc ON n.nid = cc.nid
                JOIN {content_field_issue_state} AS cs ON n.nid = cs.nid
                JOIN {content_field_issue_city} AS ct ON n.nid = ct.nid
                LEFT JOIN {term_node} AS tn ON n.nid = tn.nid 
                WHERE n.type = 'poll' $langFilter $where) AS temp ON pv.nid = temp.nid $groupBy $sortBy";
      break;
    case '7days':
      $where .= 'AND pv.date_voted >= DATE_SUB(CURDATE(), INTERVAL 7 DAY)';
      $sortBy = 'ORDER BY SUM(pc.chvotes) DESC';
      $groupBy = 'GROUP BY pc.nid';

      $sql = "SELECT DISTINCT(n.nid) FROM {node} AS n JOIN {node_revisions} AS nr ON n.nid = nr.nid
            JOIN {content_field_issue_country} AS cc ON n.nid = cc.nid
            JOIN {content_field_issue_state} AS cs ON n.nid = cs.nid
            JOIN {content_field_issue_city} AS ct ON n.nid = ct.nid
            JOIN {poll_choices} AS pc ON n.nid = pc.nid
            LEFT JOIN {poll_votes} AS pv ON n.nid = pv.nid
            LEFT JOIN {term_node} AS tn ON n.nid = tn.nid
            WHERE n.type = 'poll' $langFilter $where $groupBy $sortBy";

      break;
    case 'views':
      $sortBy = 'ORDER BY COUNT(qv.qid) DESC';
      $groupBy = 'GROUP BY iss.nid';

      $sql = "SELECT iss.nid as nid FROM
                     (SELECT DISTINCT(n.nid) FROM {node} AS n
                    JOIN {content_field_issue_country} AS cc ON n.nid = cc.nid
                    JOIN {content_field_issue_state} AS cs ON n.nid = cs.nid
                    JOIN {content_field_issue_city} AS ct ON n.nid = ct.nid
                    LEFT JOIN {term_node} AS tn ON n.nid = tn.nid
                   WHERE n.type = 'poll' $langFilter $where) AS iss LEFT JOIN {qviews} AS qv ON iss.nid = qv.qid $groupBy $sortBy";

      break;
    default:
      $sortBy = 'ORDER BY n.nid DESC';
      $groupBy = '';

      $sql = "SELECT DISTINCT(n.nid) FROM {node} AS n JOIN {node_revisions} AS nr ON n.nid = nr.nid
            JOIN {content_field_issue_country} AS cc ON n.nid = cc.nid
            JOIN {content_field_issue_state} AS cs ON n.nid = cs.nid
            JOIN {content_field_issue_city} AS ct ON n.nid = ct.nid
            LEFT JOIN {term_node} AS tn ON n.nid = tn.nid
            WHERE n.type = 'poll' $langFilter $where $groupBy $sortBy";

      break;
  }

  $sqlcount = ExecuteQuery($sql, 'norows');

  /*   * Rally dev :498* */
  variable_set('hm_search_results_count', $sqlcount);
  /*   * *************** */

  $final = $sql;
  //echo $final; 

  $query = pager_query_new($final, $rec_per_page, 0, $sqlcount);


  $count = db_affected_rows($query);
  if ($sqlcount) {
    while ($result = db_fetch_object($query)) {
      $nid = $result->nid;
      $node = node_load($nid);
      $issue .= node_view(node_load($node->nid), 1);
    }
    $issue .= '<div class="pagination">' . theme('pager', array(), $rec_per_page) . '</div><br class="clear">';
  }
  else {
    $issue .= t('No Issues Found');
  }
  return $issue;
}

/* * *************************** */

function issue_debates($qid='', $type='', $sort = null) {
  global $user, $language, $theme;
  $curLanguage = $language->language;
  $wave = '';
  $click = '';
  $debate_theme = '';

  //drupal_add_js( drupal_get_path('module', 'debate') . '/scripts/debate.js');
  // load debate
  $sup = isset($_GET['sup']) ? $_GET['sup'] : '';
  $ans = isset($_GET['ans']) ? $_GET['ans'] : '';
  if (!isset($sort)) {
    $sort = isset($_GET['sort']) ? $_GET['sort'] : '';
  }

  $sorting = 'ORDER BY f.nid DESC';
  $cond = '';
  extract($_REQUEST);
  if (isset($sort) && $sort == 1) {
    $sorting = 'ORDER BY n.created DESC';
  }
  elseif (isset($sort) && $sort == 2) {
    $sorting = ' ORDER BY c.field_strength_value DESC';
  }
  elseif (isset($sort) && $sort == 0) {
    $sorting = 'ORDER BY n.created ASC';
  }
  if (isset($ans) && !empty($ans)) {
    $cond.=" AND do.chorder='$ans'";
  }
  if (isset($sup) && $sup > 0) {
    $cond.=" AND do.ans_val='$sup'";
  }
  $tid = get_taxonomy_id('forum', 'Debate');
  //$sql = "SELECT f.nid FROM {forum} as f LEFT JOIN {content_type_forum} as c ON f.nid = c.nid JOIN {node} as n ON f.nid = n.nid WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' $cond $sorting";

  if (empty($cond))
    $sql = "SELECT DISTINCT(f.nid) FROM {forum} as f LEFT JOIN {content_type_forum} as c ON f.nid = c.nid JOIN {node} as n ON f.nid = n.nid JOIN {debate_options} as do ON n.nid = do.nid WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' $sorting";
  else
    $sql = "SELECT DISTINCT(f.nid) FROM  {debate_options} as do  JOIN  {forum} as f ON f.nid = do.nid LEFT JOIN {content_type_forum} as c ON f.nid = c.nid JOIN {node} as n ON f.nid = n.nid  WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' $cond $sorting";

  // forum for translated languages
  $issueId = $qid;
  $tnid = get_tnid($qid);
  $qid = $tnid;

  $nodes = db_query($sql, $tid, $qid);
  $count = db_result(db_query($sql, $tid, $qid));

  if ($count > 0) {
    $i = 0;
    while ($node = db_fetch_object($nodes)) {

      $items = load_debate_datas($node->nid, $issueId, $tnid);

      // anwers strength
      $strnth = $items['strength'];
      //echo '<pre>';print_r($strnth);exit;
      $strength = '';
      foreach ($strnth as $list) {
        $short_answer = get_short_answer($items['issue_id'], $list['chorder']);
        $tranAns = db_result(db_query("SELECT chtext FROM {poll_choices} WHERE nid = '" . $items['issue_id'] . "' AND chorder = '" . $list['chorder'] . "'"));
        $ans = $short_answer != '' ? $short_answer : $tranAns;

        switch ($list['ans_val']) {

          case 1:
            $strength.='<p class="position-plus"><strong>+</strong>&nbsp;' . $ans . '</p>';
            break;
          case 2:
            $strength.='<p class="position-minus"><strong>-</strong>&nbsp;' . $ans . '</p>';
            break;
        }
      }

      // reply
      $reply_box = drupal_get_form('forum_reply_form', $items['debate_id'], $items['debate_tnid'], $items['issue_id']);
      $comments = forum_replies($items['debate_tnid'], 0);
      $reply_count = db_result(db_query("SELECT COUNT(cid) FROM {comments} WHERE nid = '" . $items['debate_tnid'] . "'"));
      // delete
      if (is_moderator() || $items['uid'] == $user->uid) {
        $delete = '<h6 value="Delete" id="reply" class="add-comment button light" onclick="delete_thread(\'own_forum_' . $items['debate_tnid'] . '\', \'debate\')">' . t('Delete') . '</h6>';
      }
      else {
        $delete = '';
      }
      // ratings
      // allow rating check
      $ratings = get_rating_buttons($items, 'is_debate');

      //$debate_theme .= theme('single_debate_template', $items);

      $date1 = new DateTime($items['posted']);
      $date2 = new DateTime("now");
      $interval = $date1->diff($date2);
      $years = $interval->format('%y');
      $months = $interval->format('%m');
      $days = $interval->format('%d');
      $hours = $interval->format('%h');
      $minutes = $interval->format('%i');
      if ($years != 0) {
        $ago = $years . ' year(s) ago';
      }
      else {
        if ($months != 0) {
          $ago = ($months . ' month(s) ago');
        }
        else {
          if ($days != 0) {
            $ago = ($days . ' day(s) ago');
          }
          else {
            if ($hours != 0) {
              $ago = ($hours . ' hour(s) ago ');
            }
            else {
              $ago = ($minutes . ' minute(s) ago');
            }
          }
        }
      }
      $items['ago'] = $ago;
      $debate_theme .= theme('debate_parent_template', $items, $strength, $comments, $reply_box, $reply_count, $ratings, $delete);
      // update points
      $tForumId = get_tnid($node->nid);
      debate_roundup($tForumId);
    }
  }
  else {
    $debate_theme .= '<div class="messages warning no_debate">' . t('No Debate Posted Yet!!') . '</div>';
  }

  return $debate_theme;
}

// forum replies
function forum_replies($debate_tnid, $pid = '') {
  global $user, $language, $theme;
  $curLanguage = $language->language;
  $comments = '';

  $query = "SELECT * FROM {comments} as c where c.nid='$debate_tnid' and c.status='0' and c.pid='$pid' AND (c.cid = c.tcid OR c.tcid = 0) ORDER BY c.cid DESC";
  $list = ExecuteQuery($query, "select");

  if (count($list) > 0) {
    foreach ($list as $forum) {
      $cid = $forum['cid'];
      if (!empty($forum['comment'])) {
        $items = forum_reply_datas($cid);
        // ratings
        // allow rating check
        $ratings = get_rating_buttons($items, 'is_debate_reply');

        //delete
        if (is_moderator() || $items['uid'] == $user->uid) {
          $delete = '<h6 value="Delete" id="reply" class="add-comment button light" onclick="delete_thread(\'own_reply_' . $items['cid'] . '\', \'reply\')">' . t('Delete') . '</h6>';
        }
        else {
          $delete = '';
        }
        $userPicture = UserPicture_small_src($items['uid']);
        $comments .= theme('forum_child_reply_template', $items, $userPicture, $ratings, $delete);
      }
    }
  }
  else {
    
  }
  return $comments;
}

// delete forum, comments
function issue_thread_delete($type = '', $tnid = '', $source = '') {
  if ($type == 'forum') {
    if ($source == 'debate') {
      $tlists = translation_node_get_translations($tnid);
      foreach ($tlists as $list) {
        node_delete($list->nid);
      }
      node_delete($tnid);
      db_query("DELETE FROM {debate_options} WHERE nid = '$tnid'");
      print t('Your argument removed from list');
      exit;
    }
    elseif ($source == 'resource') {
      node_delete($tnid);
      db_query("DELETE FROM {resource_options} WHERE nid = '$tnid'");
      print t('Your reference removed from list');
      exit;
    }
  }
  if ($type == 'reply') {
    $tcid = $tnid;
    $comment = db_fetch_object(db_query('SELECT c.*, u.name AS registered_name, u.uid FROM {comments} c INNER JOIN {users} u ON u.uid = c.uid WHERE c.cid = %d', $tcid));

    if ($comment->translate == 1) {
      $trans = db_query('SELECT c.*, u.name AS registered_name, u.uid FROM {comments} c INNER JOIN {users} u ON u.uid = c.uid WHERE c.tcid = %d', $comment->cid);
      while ($translations = db_fetch_object($trans)) {
        delete_replies($translations);
      }
    }
    else {
      delete_replies($comment);
    }
    print t('Your reply removed from list');
    exit;
  }
}

function delete_replies($comment) {
  // Delete the comment:
  db_query('DELETE FROM {comments} WHERE cid = %d', $comment->cid);
  watchdog('content', 'Comment: deleted %subject.', array('%subject' => $comment->subject));

  comment_invoke_comment($comment, 'delete');
  // update comment statistics
  _comment_update_node_statistics($comment->nid);
}

function issue_ajax($task = '', $nid = '') {
  global $base_url, $user;
  switch ($task) {
    case 'insightview':
      $result = insight_view($nid);
      break;

    case 'debate_statistics':
      $result = '<div id="debate_statistic" width="520" height="350">
        <div id="container" class="highcharts-container" style="height:auto; width: 100%; margin: 0 auto; clear:both"></div>
        <div id="resource" style="height:auto; width: 400px; margin: 0 auto; clear:both"></div>
</div>';
      break;
    case 'resource_statistics':
      $result = '<iframe src="' . $base_url . '/debate/ajax/' . $nid . '?action=resanalysis" width="520" height="350" frameborder=0 scrolling="no"></iframe>';
      break;
    case 'getForumFlagForm':
      // abuse flag form ############
      $tnid = $nid;
      $flagType = $_GET['flag_type'];
      $object = _abuse_load($flagType, $tnid);
      // echo '<pre>'; print_r($object);exit;
      $reported = db_result(db_query("SELECT COUNT(*) FROM {abuse} WHERE type='%s' AND oid=%d AND uid=%d", $flagType, $tnid, $user->uid));
      if ($reported > 0) {
        $flagForm = t('We have already received your report.  Thank you very much!');
      }
      else if ($user->uid == $object->uid) {
        $flagForm = t('Sorry, you cannot flag your own content');
      }
      else {
        $flagForm = drupal_get_form('abuse_report_form', $object, $user);
      }
      // abuse flag form ############
      $result = $flagForm;
  }
  echo $result;
}

function insight_view($nid='') {

//    1.  Demographics by possible answer to total votes
//   Sum of votes for a possible answer by each demographic / total votes.
//ex: sum votes for possible answer A where demographic = male / total number of votes (not including changed votes)
//
//2.  Demographics by possible answer by total demographic votes
//   Sum of votes for a possible answer by each demographic / total votes for the same demographic
//ex: sum votes for possible answer A where demographic = age group X / total votes for age group X
//
//3. Demographics total votes by total votes
//   Sum of all votes by a demographic / total votes
//ex: Sum all votes by hindus (regardless of possible answer) / total votes

  if (is_numeric($nid)) {
    $nid = get_tnid($nid);
    $ans = load_options($nid);
    $colors = _load_colors_array();
    foreach ($ans as $key => $list) {
      $short_answers[$list['chorder']] = get_short_answer($nid, $list['chorder']);
    }
    // calculation
    // total votes a issue
    $insight = '';
    $totalVotes = db_result(db_query("SELECT COUNT(chorder) FROM {poll_votes} WHERE nid = '%d'", $nid));
    if ($totalVotes >= 10) {
      $insight .= '<span>' . by_possible_answers_votes($nid, $short_answers, $colors) . '</span></br>';
      $insight .= '<span>' . by_demographic_votes($nid, $short_answers, $colors) . '</span></br>';
      $insight .= '<span>' . by_total_votes($nid) . '</span></br>';
    }
    else {
      $insight .= t('Insight view cannot be calculated until 10 votes have been received.');
    }
    return $insight;
  }
  
}

function by_possible_answers_votes($nid = '', $short_answers, $colors) {
  $byPossible = array();
  foreach ($short_answers as $key => $value) {
    $short_ans_colors[$value] = $colors[$key];
  }

  $totalVotes = db_result(db_query("SELECT COUNT(chorder) FROM {poll_votes} WHERE nid = '%d'", $nid));
  $node = node_load($nid);

  // DEMOGRAPHICS
  $demographics = array('gender', 'age', 'religion', 'ethnicity', 'income', 'marital', 'sorient', 'edu');
  foreach ($demographics as $demographic) {
    $demo = report_percent_broken($nid, '', array('dochg' => $demographic));

    $divides = $demo['divide'];
    $cnts = $demo['cnt'];

    foreach ($divides as $key => $divide) {
      // removed undefined from results
      if ($divide == 'undefined') {
        unset($key);
      }
      $divide = $divide == 'undefined' ? 'undefined_' . $demographic : $divide;
      $count = $cnts[$key];

      $choices = $count;
      foreach ($choices as $choice => $cCount) {
        $percent = ($cnts[$choice][$key] / $totalVotes) * 100;
        $byPossible[$divide][$short_answers[$choice]] = $percent;
      }
      unset($choices);
    }
  }
  $temp = $byPossible;
  $first_key = max_key($byPossible);
  unset($byPossible[$first_key]);
  $second_key = max_key($byPossible);

  $first = $temp[$first_key];
  $second = $temp[$second_key];

  $fmax = max($first);
  $smax = max($second);
  foreach ($first as $ch => $val) {
    if ($val == $fmax) {
      $fChoice['name'] = $ch;
      $fChoice['color'] = $short_ans_colors[$ch];
    }
  }
  foreach ($second as $ch => $val) {
    if ($val == $smax) {
      $sChoice['name'] = $ch;
      $sChoice['color'] = $short_ans_colors[$ch];
    }
  }
  //special wordings for each demographic
  $age = report_percent_broken($nid, '', array('dochg' => 'age'));
  $income = report_percent_broken($nid, '', array('dochg' => 'income'));
  if (in_array($first_key, $age['divide'])) {
    $extraStr1 = " aged people";
  }
  else if (in_array($first_key, $income['divide'])) {
    $extraStr1 = " salaried people";
  }
  if (in_array($second_key, $age['divide'])) {
    $extraStr2 = " aged people";
  }
  else if (in_array($second_key, $income['divide'])) {
    $extraStr2 = " salaried people";
  }
  $str .= ceil($fmax) . '% ' . t('of ' . $first_key . $extraStr1 . ' voted for ' . '<span class="highlight" style="background-color:' . $fChoice['color'] . '">' . $fChoice['name'] . '</span>') . '<br />';
  $str .= ceil($smax) . '% ' . t('of ' . $second_key . $extraStr2 . ' voted for ' . '<span class="highlight" style="background-color:' . $sChoice['color'] . '">' . $sChoice['name'] . '</span>');
  return $str;
}

function by_demographic_votes($nid = '', $short_answers, $colors) {
  $byDemographic = array();
  //$node = node_load($nid);
  // DEMOGRAPHICS

  foreach ($short_answers as $key => $value) {
    $short_ans_colors[$value] = $colors[$key];
  }

  $demographics = array('gender', 'age', 'religion', 'ethnicity', 'income', 'marital', 'sorient', 'edu');
  foreach ($demographics as $demographic) {
    $demo = report_percent_broken($nid, '', array('dochg' => $demographic));

    $divides = $demo['divide'];
    $cnts = $demo['cnt'];

    // total votes per demographic
    $val = 0;

    foreach ($divides as $key => $divide) {
      // removed undefined from results
      if ($divide == 'undefined') {
        unset($key);
      }
      $divide = $divide == 'undefined' ? 'undefined_' . $demographic : $divide;
      $count = $cnts[$key];
      //  $choices = json_decode($count);
      $choices = $count;
      // total counts for group x in each demographic
      $demoVotes = array_sum($choices);

      foreach ($choices as $choice => $cCount) {
        $percent = ($cnts[$choice][$key] / $demoVotes) * 100;
        $byDemographic[$divide][$short_answers[$choice]] = $percent;
      }
      unset($choices);
    }
  }
  $temp = $byDemographic;

  $first_key = max_key($byDemographic);
  unset($byDemographic[$first_key]);
  $second_key = max_key($byDemographic);

  $first = $temp[$first_key];
  $second = $temp[$second_key];

  $fmax = max($first);
  $smax = max($second);
  foreach ($first as $ch => $val) {
    if ($val == $fmax) {
      $fChoice['name'] = $ch;
      $fChoice['color'] = $short_ans_colors[$ch];
    }
  }
  foreach ($second as $ch => $val) {
    if ($val == $smax) {
      $sChoice['name'] = $ch;
      $sChoice['color'] = $short_ans_colors[$ch];
    }
  }

  //special wordings for each demographic
  $age = report_percent_broken($nid, '', array('dochg' => 'age'));
  $income = report_percent_broken($nid, '', array('dochg' => 'income'));
  if (in_array($first_key, $age['divide'])) {
    $extraStr1 = "between the ages of ";
  }
  else if (in_array($first_key, $income['divide'])) {
    $extraStr1 = "salaried between ";
  }
  if (in_array($second_key, $age['divide'])) {
    $extraStr2 = "between the ages of ";
  }
  else if (in_array($second_key, $income['divide'])) {
    $extraStr2 = "salaried between ";
  }
  $str .= ceil($fmax) . '% ' . t('of the voters are ' . $extraStr1 . $first_key) . ' voted for ' . '<span class="highlight" style="background-color:' . $fChoice['color'] . '">' . $fChoice['name'] . '</span><br />';
  $str .= ceil($smax) . '% ' . t('of the voters are ' . $extraStr2 . $second_key) . ' voted for ' . '<span class="highlight" style="background-color:' . $sChoice['color'] . '">' . $sChoice['name'] . '</span>';
  return $str;
}

function by_total_votes($nid = '') {
  $bytotalVotes = array();
  $totalVotes = db_result(db_query("SELECT COUNT(chorder) FROM {poll_votes} WHERE nid = '%d'", $nid));
  $node = node_load($nid);
  // DEMOGRAPHICS
  $demographics = array('gender', 'age', 'religion', 'ethnicity', 'income', 'marital', 'sex_orient', 'education');
  foreach ($demographics as $demographic) {
    $demo = report_percent_broken($nid, '', array('dochg' => $demographic));
    $divides = $demo['divide'];
    $cnts = $demo['cnt'];
    // total votes per demographic
    $val = 0;

    $demoVotes = $val;
    foreach ($divides as $key => $divide) {
      $count = $cnts[$key];
      //$choices = json_decode($count);
      $choices = $count;
      // total counts for group x in each demographic
      $demoVotes = array_sum($choices);
      $percent = ($demoVotes / $totalVotes) * 100;
      $bytotalVotes[$divide] = $percent;
    }
  }
  $temp = $bytotalVotes;
  $fmax = max($bytotalVotes);
  foreach ($bytotalVotes as $vkey => $byVotes) {
    if ($fmax == $byVotes) {
      $first_key = $vkey;
      break;
    }
  }
  unset($bytotalVotes[$first_key]);
  $smax = max($bytotalVotes);
  foreach ($bytotalVotes as $vkey => $byVotes) {
    if ($smax == $byVotes) {
      $second_key = $vkey;
      break;
    }
  }

  //special wordings for each demographic
  $age = report_percent_broken($nid, '', array('dochg' => 'age'));
  $income = report_percent_broken($nid, '', array('dochg' => 'income'));
  if (in_array($first_key, $age['divide'])) {
    $extraStr1 = "between the ages of ";
  }
  else if (in_array($first_key, $income['divide'])) {
    $extraStr1 = "salaried between ";
  }
  if (in_array($second_key, $age['divide'])) {
    $extraStr2 = "between the ages of ";
  }
  else if (in_array($second_key, $income['divide'])) {
    $extraStr2 = "salaried between ";
  }
  $str .= ceil($fmax) . '% ' . t('of the voters are ' . $extraStr1 . $first_key) . '</br>';
  $str .= ceil($smax) . '% ' . t('of the voters are ' . $extraStr2 . $second_key);
  return $str;
}

function max_key($array) {
  foreach ($array as $key => $val) {
    if ($val == max($array))
      return $key;
  }
}

// debate filter options
function filter_options($form, $nid) {
  $form = '';
  $ans = load_options($nid);
  $filterBy[''] = t('Answer');
  foreach ($ans as $list) {
    $short_answer = get_short_answer($nid, $list['chorder']);
    $answer = $short_answer != '' ? $short_answer : $list['chtext'];
    $filterBy[$list['chorder']] = $answer;
  }
  $sortBy = array('0' => t('Sort By'), '1' => t('Most Recent'), '2' => t('Most Support'));

  $panOptions = array('0' => '+/-', '1' => '+', '2' => '-');

  $dSup = $_GET['sup'];
  $dans = $_GET['ans'];
  $dSort = $_GET['sort'];

  $form['nid'] = array('#type' => 'hidden', '#value' => $nid);

  $form['dfilt_sup'] = array('#type' => 'select',
    '#options' => $panOptions,
    '#default_value' => $dSup,
    '#prefix' => '<span class="select-cat">',
    '#suffix' => '</span>');
  $form['dfilt_ans'] = array('#type' => 'select',
    '#options' => $filterBy,
    '#default_value' => $dans,
    '#prefix' => '<span class="select-cat">',
    '#suffix' => '</span>');
  $form['dfilt_sort'] = array('#type' => 'select',
    '#options' => $sortBy,
    '#default_value' => $dSort,
    '#prefix' => '<span class="select-cat">',
    '#suffix' => '</span>');
  $form['debate_filter'] = array('#type' => 'submit',
    '#value' => t('Filter'));

  return $form;
}

function filter_options_submit($form, &$form_state) {
  global $base_url, $language, $theme;
  $nid = $form_state['values']['nid'];
  $sup = $form_state['values']['dfilt_sup'];
  $ans = $form_state['values']['dfilt_ans'];
  $sort = $form_state['values']['dfilt_sort'];
  $ids = '?sup=' . $sup . '&ans=' . $ans . '&sort=' . $sort;
  $path = $base_url . '/' . $language->language . '/' . drupal_get_path_alias('node/' . $nid) . $ids;
  drupal_goto($path);
}


// ISSUE RESOURCES
function issue_resources_list($qid = '') {
  //$inline = 'jQuery(document).ready(function(){res_type_tab(1,\'resource\',' . $qid . ')})';
  $inline = 'jQuery(document).ready(function(){res_type_tab(4,\'all\',' . $qid . ')})';
  drupal_add_js($inline, 'inline');
  $resources = '';

  return $resources;
}

// resources in news
function issue_resources($qid, $rtype = '', $sup='', $ans='', $sort='') {
  global $base_url, $user, $language, $theme;
  $wave = '';
  $click = '';
  $sortin = 'ORDER BY rid DESC';
  $cond = '';

  // load resources
  $sup = $sup != 'n' ? $sup : '';
  $ans = $ans != 'n' ? $ans : '';
  $sort = $sort != 'n' ? $sort : '';

  // site url with default language
  $path = '<front>';
  $sitelink = url($path, array('absolute' => TRUE)) . '/';

  extract($_REQUEST);

  $sorting = 'ORDER BY f.nid DESC';
  $cond = '';
  extract($_REQUEST);
  if (isset($sort) && $sort == 1) {
    $sorting = 'ORDER BY n.created DESC';
  }
  elseif (isset($sort) && $sort == 2) {
    $sorting = ' ORDER BY c.field_strength_value DESC';
  }
  if (isset($ans) && !empty($ans)) {
    $cond.=" AND do.chorder='$ans'";
  }
  if (isset($sup) && $sup > 0) {
    $cond.=" AND do.ans_val='$sup'";
  }

  // resource type
  switch ($rtype) {
    case '1':
      $resType = 'news';
      break;

    case '2':
      $resType = 'multimedia';
      break;

    case '3':
      $resType = 'facts';
      break;

    default:
      $resType = 'news';
      break;
  }


  $tid = get_taxonomy_id('forum', 'Resource');
  if ($rtype == 4) {
    if (empty($cond)) {
      $sql = "SELECT DISTINCT(f.nid), c.field_rtype_value FROM {forum} as f JOIN {node} as n ON f.nid = n.nid RIGHT JOIN {content_type_forum} as c ON f.nid = c.nid WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' $sorting";
    }
    else {
      $sql = "SELECT DISTINCT(f.nid), c.field_rtype_value FROM  {resource_options} as do  JOIN  {forum} as f ON f.nid = do.nid LEFT JOIN {content_type_forum} as c ON f.nid = c.nid JOIN {node} as n ON f.nid = n.nid  WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' $cond $sorting";
    }

    // forum for translated languages
    $issueId = $qid;
    $tnid = get_tnid($qid);
    $qid = $tnid;

    $nodes = db_query($sql, $tid, $qid);
    $count = db_result(db_query($sql, $tid, $qid));
  }
  else {
    if (empty($cond))
      $sql = "SELECT DISTINCT(f.nid) FROM {forum} as f JOIN {node} as n ON f.nid = n.nid RIGHT JOIN {content_type_forum} as c ON f.nid = c.nid WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' AND c.field_rtype_value = '%s' $sorting";
    else
      $sql = "SELECT DISTINCT(f.nid) FROM  {resource_options} as do  JOIN  {forum} as f ON f.nid = do.nid LEFT JOIN {content_type_forum} as c ON f.nid = c.nid JOIN {node} as n ON f.nid = n.nid  WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' AND c.field_rtype_value = '%s' $cond $sorting";

    // forum for translated languages
    $issueId = $qid;
    $tnid = get_tnid($qid);
    $qid = $tnid;

    $nodes = db_query($sql, $tid, $qid, $resType);
    $count = db_result(db_query($sql, $tid, $qid, $resType));
  }
  if ($count > 0) {
    $i = 0;

    while ($node = db_fetch_object($nodes)) {
      if ($rtype == 4) {
        $items = load_resource_datas($node->nid, $issueId, $tnid, $node->field_rtype_value);
      }
      else {
        $items = load_resource_datas($node->nid, $issueId, $tnid, $resType);
      }
      $strnth = $items['strength'];
      $strength = '';
      foreach ($strnth as $list) {
        $short_answer = get_short_answer($items['issue_id'], $list['chorder']);
        $tranAns = db_result(db_query("SELECT chtext FROM {poll_choices} WHERE nid = '" . $items['issue_id'] . "' AND chorder = '" . $list['chorder'] . "'"));
        $ans = $short_answer != '' ? $short_answer : $tranAns;

        switch ($list['ans_val']) {
          case 1:
            $strength.='<div><span class="green-box">+</span>' . $ans . '</div>';
            break;
          case 2:
            $strength.='<div><span class="red-box">-</span>' . $ans . '</div>';
            break;
        }
      }

      // delete
      if (is_moderator() || $items['uid'] == $user->uid) {
        $delete = '<h6 value="Delete" id="reply" class="add-comment button light" onclick="delete_thread(\'own_forum_' . $items['resource_id'] . '\', \'resource\')">' . t('Delete') . '</h6>';
      }
      else {
        $delete = '';
      }

      // reply box
      $reply_box = drupal_get_form('forum_reply_form', $items['resource_id'], $items['resource_id'], $items['issue_id']);
      $comments = forum_replies($items['resource_id'], 0);
      $reply_count = db_result(db_query("SELECT COUNT(cid) FROM {comments} WHERE nid = '" . $items['resource_id'] . "'"));

      // ratings
      // allow rating check
      $ratings = get_rating_buttons($items, 'is_resource');


      $resouce_theme .= theme('reference_parent_template', $items, $strength, $comments, $reply_box, $reply_count, $ratings, $delete);
      $tForumId = get_tnid($node->nid);
      resource_roundup($tForumId);
    }
  }
  else {
    $resouce_theme = '<div class="messages warning">' . t('No Resource Posted Yet!!') . '</div>';
  }
  //return $resouce_theme;
  if (isAjax()) {
    print $resouce_theme;
  }
  else {
    return $resouce_theme;
  }
}

// validate issue create form
function validate_issue_add($form, &$form_state) {
  //echo '<pre>';print_r($form_state); exit;
  if ($form_state['values']['q_quest'] == '') {
    form_set_error('error', t('Please enter your question'));
  }
  if ($form_state['values']['answer'][0] == '' || $form_state['values']['answer'][1] == '') {
    form_set_error('error', t('You must enter atleast two answers'));
  }
}

function report_answer_details_history($nid = '', $aid = '', $action = '', $date = '') {
  switch ($action) {
    case 'percent':
      if ($_REQUEST['fopt']) {
        $opt = filter_opt($_REQUEST);

        $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $aid . "' $opt ";
        $answer = ExecuteQuery($query, "norows");
      }
      else {

        $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $aid . "' ";
        $answer = ExecuteQuery($query, "norows");
      }


      return $answer;
      break;
    case 'timeline':
      $query1 = "select count(*) as cnt from {poll_votes_history} where nid='" . $nid . "' and chorder='" . $aid . "'AND date(date_voted)<='" . $date . "' and status=1";
      $query2 = "select count(*) as cnt from {poll_votes_history} where nid='" . $nid . "' and chorder='" . $aid . "'AND date(date_voted)<='" . $date . "' and status=0";
      $result1 = db_result(db_query($query1));
      $result2 = db_result(db_query($query2));
      if ((!is_null($result1)) and (!is_null($result2))) {
        $result = $result1 - $result2;
      }
      else {
        $result = 'null';
      }

      return $result;
      break;
  }
}

function report_get_ans_range_history($nid='', $range='') {
  switch ($range) {
    case 'start':
      $query = "select date(date_voted) as dat from {poll_votes_history} where nid='" . $nid . "' ORDER BY date_voted ASC LIMIT 0,1 ";
      $answer = ExecuteQuery($query, "select");
      break;
    case 'end':
      $query = "select date(date_voted) as dat from poll_votes_history where nid='" . $nid . "' ORDER BY date_voted DESC LIMIT 0,1 ";
      $answer = ExecuteQuery($query, "select");
      break;
    default:
      $query = "select count(*) as cnt from poll_votes_history where nid='" . $nid . "' ";
      $answer = ExecuteQuery($query, "select");
      break;
  }
  return $answer[0];
}

function issue_ajax_tab_content($qid, $type, $sort = null, $print = null) {

  global $user, $language, $theme;
  $curLanguage = $language->language;
  $wave = '';
  $click = '';
  $debate_theme = '';
  // load debate
  $sorting = 'ORDER BY f.nid DESC';
  $third = ',n.created ';

  $cond = '';
  if (isset($sort) && $sort == 1) {
    $sorting = 'ORDER BY n.created DESC';
    $third = ',n.created ';
    $order_sort = 'DESC';
  }
  elseif (isset($sort) && $sort == 2) {
    $sorting = ' ORDER BY c.field_strength_value DESC';
    $third = ',c.field_strength_value ';
    $order_sort = 'DESC';
  }
  elseif (isset($sort) && $sort == 0) {
    $sorting = 'ORDER BY n.created ASC';
    $third = ',n.created ';
    $order_sort = 'ASC';
  }

  $issueId = $qid;
  $tnid = get_tnid($qid);
  $qid = $tnid;
  if (isset($_GET['class'])) {
    switch ($_GET['class']) {
      case 'neutral':
        $ans_val = 0;
        break;
      case 'positive':
        $ans_val = 1;
        break;
      case 'negative':
        $ans_val = 2;
        break;
    }
    $and = 'and  do.chorder = "%d" and do.ans_val = "%d"';
    $sql = "SELECT DISTINCT(f.nid),f.tid $third FROM forum as f
    LEFT JOIN content_type_forum as c ON f.nid = c.nid
    JOIN node as n ON f.nid = n.nid
    LEFT JOIN debate_options as do ON f.nid = do.nid
    WHERE c.field_ref_qid_nid = '%d' $and
UNION
    SELECT DISTINCT(f.nid),f.tid $third FROM forum as f
    LEFT JOIN content_type_forum as c ON f.nid = c.nid
    JOIN node as n ON f.nid = n.nid
    WHERE c.field_ref_qid_nid = %d and f.tid = 7
    ORDER by 3 $order_sort
    ";
    $nodes = db_query($sql, $qid, $_GET['chorder'], $ans_val, $qid);
    $count = db_result(db_query($sql, $qid, $_GET['chorder'], $ans_val, $qid));
  }
  else {
    $sql = "SELECT DISTINCT(f.nid),f.tid FROM {forum} as f
    LEFT JOIN {content_type_forum} as c ON f.nid = c.nid
    JOIN {node} as n ON f.nid = n.nid
    WHERE c.field_ref_qid_nid = '%d' $sorting";
    $nodes = db_query($sql, $qid);
    $count = db_result(db_query($sql, $qid));
  }
  // forum for translated languages



  if ($count > 0) {
    $i = 0;
    while ($node = db_fetch_object($nodes)) {
      if ($node->tid == 6) {
        $items = load_debate_datas($node->nid, $issueId, $tnid);
      }
      else {
        $items = load_resource_datas($node->nid, $issueId, $tnid, $node->field_rtype_value);
      }

      // anwers strength
      $strnth = $items['strength'];
      $strength = '';
      foreach ($strnth as $list) {
        $short_answer = get_short_answer($items['issue_id'], $list['chorder']);
        $tranAns = db_result(db_query("SELECT chtext FROM {poll_choices} WHERE nid = '" . $items['issue_id'] . "' AND chorder = '" . $list['chorder'] . "'"));
        $ans = $short_answer != '' ? $short_answer : $tranAns;

        switch ($list['ans_val']) {
          case 1:
            $strength.='<p class="position-plus"><strong>+</strong>&nbsp;' . $ans . '</p>';
            break;
          case 2:
            $strength.='<p class="position-minus"><strong>-</strong>&nbsp;' . $ans . '</p>';
            break;
        }
      }
      // reply
      $reply_box = drupal_get_form('forum_reply_form', $items['debate_id'], $items['debate_tnid'], $items['issue_id']);
      $comments = forum_replies($items['debate_tnid'], 0);
      $reply_count = db_result(db_query("SELECT COUNT(cid) FROM {comments} WHERE nid = '" . $items['debate_tnid'] . "'"));
      // delete
      if (is_moderator() || $items['uid'] == $user->uid) {
        if (isset($items['debate_tnid'])) {
          $id = $items['debate_tnid'];
          $arg = 'debate';
        }
        else {
          $id = $items['resource_id'];
          $arg = 'resource';
        }
        $delete = '<h6 value="Delete" id="reply" class="add-comment button light" 
          onclick="delete_thread(\'own_forum_' . $id . '\', \'' . $arg . '\')">' . t('Delete') . '</h6>';
        //(\'own_reply_' . $items['cid'] . '\', \'reply\')
      }
      else {
        $delete = '';
      }
      // ratings
      // allow rating check
      $ratings = get_rating_buttons($items, 'is_debate');
      $debate_theme .= theme('debate_parent_template', $items, $strength, $comments, $reply_box, $reply_count, $ratings, $delete);
      // update points
      $tForumId = get_tnid($node->nid);
      debate_roundup($tForumId);
    }
  }
  else {
    $debate_theme .= '<div class="messages warning no_debate">' . t('No Debate Posted Yet!!') . '</div>';
  }

  if ($print == 1) {
    return $debate_theme;
  }
  else {
    print $debate_theme;
  }
}

function issue_ajax_highstock_graph($nid, $number) {
  global $base_url, $user, $base_path;
  $qid = $nid;
  $nid = get_tnid($nid);
  $output = '';

  $vans = "select * from {poll_choices} where  nid=$qid order by chorder";
  $vlist = ExecuteQuery($vans, "select");
  $cnt_ans = count($vlist);

  $query = "select date(date_voted) as dat from {poll_votes} where nid='" . $nid . "' ORDER BY date_voted DESC";
  $list = ExecuteQuery($query, "select");
  $s1 = array();
  $grid = array();

  $srange = report_get_ans_range_history($nid, 'start');
  $erange = report_get_ans_range_history($nid, 'end');
  $count = report_get_ans_range_history($nid);

  $query = "select DATEDIFF(date(now()),'" . $srange['dat'] . "') as diff,date(now()) as today";
  $overall_range = ExecuteQuery($query, "select");
  $frange = $overall_range[0]['diff'];
  $drange = dates_range($srange['dat'], $overall_range[0]['today']);
  $drange = array_reverse($drange);
  for ($ab = 0; $ab < $cnt_ans; $ab++) {

    // short answers
    $short_answer = get_short_answer($qid, $vlist[$ab]['chorder']);
    $answer = $short_answer != '' ? $short_answer : $vlist[$ab]['chtext'];
    $answer = substr(t(addslashes($answer)), 0, 16);
    $i = $ab + 1;
    $ans = array();

    if (count($drange) > 6) {
      for ($mn = $frange; $mn >= 0; $mn--) {
        $date = $drange[$mn];
        $inc_this = report_answer_details_history($nid, $vlist[$ab]['chorder'], 'timeline', $date);
        array_push($ans, $inc_this);
      }
      $ins_sc = '[' . implode(',', $ans) . ']';
      array_push($grid, "'" . $answer . "'");
      $insdata.="{name :'" . $answer . "', data: " . $ins_sc . "},";
      $json[$ab]['data'] = $ans;
      $json[$ab]['name'] = $answer;
      $dexp = explode('-', $srange['dat']);

      $sdate_arr['year'] = $dexp[0];
      $sdate_arr['month'] = $dexp[1] - 1;
      $sdate_arr['day'] = $dexp[2];
    }
    else {
      for ($mn = 6; $mn >= 0; $mn--) {
        $year = date("Y");
        $month = date("m");
        $dat = date("d") - $mn;
        $date = date('Y-m-d', mktime(0, 0, 0, $month, $dat, $year));
        $inc_this = report_answer_details_history($nid, $vlist[$ab]['chorder'], 'timeline', $date);
        array_push($ans, $inc_this);
      }

      $json[$ab]['data'] = $ans;
      $json[$ab]['name'] = $answer;

      $sdate_arr['year'] = $year;
      $sdate_arr['month'] = $month - 1;
      $sdate_arr['day'] = date("d") - 6;
    }
  }
  print drupal_json(array(
            'name' => $json[$number]['name'],
            'data' => $json[$number]['data'],
            'date' => $sdate_arr,
          ));
}

function issue_ajax_highchart_result($nid, $param) {
  global $base_url, $user, $base_root, $base_path;
  $output = '';
  $filter = '';
  $incflt = '';
  $opt = '';
  if (!is_numeric($nid))
    return 'No Data Found';

  $vans = "select * from {poll_choices} where  nid='" . $nid . "' ORDER BY chorder";

  $vlist = ExecuteQuery($vans, "select");
  $cnt_ans = count($vlist); //кол-во ответов

  $inline = "var example = 'bar-stacked',
            theme = 'skies'";
  drupal_add_js($inline, 'inline');

  $ans_array = array();
  for ($ab = 0; $ab < $cnt_ans; $ab++) {
    $short_answer = get_short_answer($nid, $vlist[$ab]['chorder']);
    $answer = $short_answer != '' ? $short_answer : $vlist[$ab]['chtext'];
    $answer = substr(t(addslashes($answer)), 0, 16);
    array_push($ans_array, $answer);
  }
  $result = report_percent_broken($nid, '', $_REQUEST);
  if ($_REQUEST['dochg'] == '') {
    $json['name'] = $result['divide'];
    $json['categories'] = $ans_array;
    $xtitle = "'" . "'";
  }
  else {
    // $ans = $ans_array;
    $json['name'] = $ans_array;
    $xtitle = "'" . $_REQUEST['dochg'] . "'";
    $json['categories'] = $result['divide'];
  }
  $cnt = $result['cnt'];

  $json['data'] = $result['cnt'];

  foreach ($json['name'] as $key => $value) {
    $js_arr[$key]['name'] = $json['name'][$key];
    $js_arr[$key]['data'] = $json['data'][$key];
    $js_arr['categories'] = $json['categories'];
  }
  $colors = _load_colors_array();

  if ($_REQUEST['dochg'] == '') {
    foreach ($js_arr[0]['data'] as $key => $value) {
      $new_js_arr[0]['data'][$key]['y'] = $value;
      $new_js_arr[0]['data'][$key]['name'] = $js_arr[0]['name'];
      $new_js_arr[0]['data'][$key]['color'] = $colors[$key];
    }
    $new_js_arr['categories'] = $js_arr['categories'];
    $new_js_arr[0]['name'] = $js_arr[0]['name'];
    $js_arr = $new_js_arr;
  }

  print drupal_json(array('name' => $js_arr[$param]['name'],
            'data' => $js_arr[$param]['data'],
            'categories' => $js_arr['categories'],
            'xtitle' => t($_REQUEST['dochg'])
                  )
          );
}

function issue_ajax_gmap_result($nid) {
  $colors = _load_colors_array();

  $query = "select count(nid) from {poll_choices} where  nid=$nid  order by chorder";
  $result = db_result(db_query($query));
  for ($i = 0; $i < $result; $i++) {
    $pans = db_query("select u.latitude, u.longitude from {poll_votes} as pav 
     left join {user_profile} as u on u.uid=pav.uid 
     where pav.chorder='" . $i . "' AND pav.nid='$nid'");
    while ($coordinates = db_fetch_object($pans)) {

      if ((!is_null($coordinates->latitude)) and ($coordinates->latitude != '')) {
        $coordinates->color = $colors[$i];
        $getresult[] = $coordinates;
      }
    }
  }
  print drupal_json(array(
            'data' => $getresult));
}