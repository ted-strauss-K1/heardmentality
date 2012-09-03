<?php

function theme_issue_results_graph_quick_facts($node) {
  return;



  $nid = $node->nid;


  $nid = get_tnid($nid);
  $ans = issue_choices($nid);
  $colors = _load_colors_array();
  foreach ($ans as $key => $list) {
    $short_answers[$list['chorder']] = get_short_answer($nid, $list['chorder']);
  }
  // calculation
  // total votes a issue
  $insight = '';
  $totalVotes = db_result(db_query("SELECT COUNT(chorder) FROM {poll_votes} WHERE nid = '%d'", $nid));
  if ($totalVotes >= 10) {
    #$insight .= '<span>' . by_possible_answers_votes($nid, $short_answers, $colors) . '</span></br>';
    #$insight .= '<span>' . by_demographic_votes($nid, $short_answers, $colors) . '</span></br>';
    #$insight .= '<span>' . by_total_votes($nid) . '</span></br>';
  }
  else {
    $insight .= t('Insight view cannot be calculated until 10 votes have been received.');
  }
  return $insight;
}

function by_possible_answers_votes($nid = '', $short_answers, $colors) {
  $byPossible = array();
  foreach ($short_answers as $key => $value) {
    $short_ans_colors[$value] = $colors[$key];
  }

  $totalVotes = db_result(db_query("SELECT COUNT(chorder) FROM {poll_votes} WHERE nid = '%d'", $nid));


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
          $query = "select * from {poll_votes} as p inner join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND u.gender='" . $gen . "' ";
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
          $query = "select * from {poll_votes} as p inner join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' " . $query_ins;
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
          $query = "select * from {poll_votes} as p inner join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND religion='" . $reg . "'";
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
          $query = "select * from {poll_votes} as p inner join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND ethnic='" . $reg . "'";
          $tcnt = ExecuteQuery($query, "norows");
          $answer_cnt[$ab][$key] = $tcnt;
        }
      }

      break;
    case 'income':
      $answer['divide'] = array('$0-$9,999', '$10,000 - $19,999', '$20,000 - $39,999', '$40,000 - $69,999', '$70,000 - $99,999', '$100,000 - $149,999', '$150,000 - $299,999', '>$300,000', 'undefined');

      foreach ($answer['divide'] as $key => $list) {
        if ($list == 'undefined') {
          $reg = '0';
        }
        else {
          $reg = $list;
        }
        for ($ab = 0; $ab < count($vlist); $ab++) {
          $query = "select * from {poll_votes} as p inner join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND income='" . $reg . "'";
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
          $query = "select * from {poll_votes} as p inner join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND marital='" . $reg . "'";
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
          $query = "select * from {poll_votes} as p inner join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND sorient='" . $reg . "'";
          $tcnt = ExecuteQuery($query, "norows");
          $answer_cnt[$ab][$key] = $tcnt;
        }
      }

      break;
    case 'education':
      $answer['divide'] = array('No High School', 'High School', 'Technical College', 'University', 'Masters Degree', 'undefined');

      foreach ($answer['divide'] as $key => $list) {
        if ($list == 'undefined')
          $reg = '0';
        else
          $reg = $list;
        for ($ab = 0; $ab < count($vlist); $ab++) {
          $query = "select * from {poll_votes} as p inner join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND edu='" . $reg . "'";
          $tcnt = ExecuteQuery($query, "norows");
          $answer_cnt[$ab][$key] = $tcnt;
        }
      }

      break;

    default:
      $answer['divide'] = array('Total Votes');
      foreach ($vlist as $key => $chvote) {
        $query = "select * from {poll_votes} as p inner join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $chvote['chorder'] . "'";
        $total_votes[] = (int) ExecuteQuery($query, "norows");
      }

      $answer_cnt[] = $total_votes;
      break;
  }

  $answer['cnt'] = $answer_cnt;
  return $answer;
}