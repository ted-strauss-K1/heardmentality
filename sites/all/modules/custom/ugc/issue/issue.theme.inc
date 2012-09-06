<?php
/*
 * This file contains all the functions related to theming
 */

/*
 * Highchart Filter
 *
 * @see issue_results_graph_highchart_filter_data()
 * @see issue_results_graph_highchart_filter_form()
 */
function theme_issue_results_graph_highchart_filter($node) {
  issue_results_graph_highchart_filter_data($node);
  drupal_add_js(drupal_get_path('module', 'issue') . "/js/highcharts/highcharts.js");
  drupal_add_js(drupal_get_path('module', 'issue') . "/js/chart.highchart.js");
  return drupal_get_form('issue_results_graph_highchart_filter_form');
}

/*
 * Highchart Filter Categories
 */
function issue_results_graph_highchart_filter_categories() {
  $cat = array();

  $cat[''] = array(
    '#name' => t('Total Votes'),
    '#options' => array(
      'Total Votes',
    ),
  );
  $cat['age'] = array(
    '#name' => t('Age'),
    '#options' => array(
      '18-30', '30-50', '50 above', 'undefined',
    ),
  );
  $cat['gender'] = array(
    '#name' => t('Gender'),
    '#options' => array(
      'male', 'female', 'undefined',
    ),
  );
  $cat['religion'] = array(
    '#name' => t('Religion'),
    '#options' => array(
      'Christian', 'Muslim', 'Jewish', 'Hindu', 'Buddhist', 'Other', 'undefined',
    ),
  );
  $cat['ethnicity'] = array(
    '#name' => t('Ethnicity'),
    '#options' => array(
      'Caucasian', 'Black', 'Asian', 'Indian', 'Semetic', 'Latin', 'Aborigines', 'undefined',
    ),
  );
  $cat['income'] = array(
    '#name' => t('Income'),
    '#options' => array(
      '$0-$9,999', '$10,000 - $19,999', '$20,000 - $39,999', '$40,000 - $69,999', '$70,000 - $99,999', '$100,000 - $149,999', '$150,000 - $299,999', '>$300,000', 'undefined',
    ),
  );
  $cat['marital'] = array(
    '#name' => t('Marital'),
    '#options' => array(
      'Single', 'Married', 'Divorced', 'Widow', 'undefined',
    ),
  );
  $cat['sex_orient'] = array(
    '#name' => t('Sexual Orientation'),
    '#options' => array(
      'Straight', 'Gay', 'Bisexual', 'Transgender', 'undefined',
    ),
  );
  $cat['education'] = array(
    '#name' => t('Education Level'),
    '#options' => array(
      'No High School', 'High School', 'Technical College', 'University', 'Masters Degree', 'undefined',
    ),
  );

  return $cat;
}

/*
 * Highchart Filter Data Collector
 *
 * @see issue_results_graph_highchart_filter_categories
 * TODO - get back when Profiles module is fixed
 */
function issue_results_graph_highchart_filter_data($node) {
  $nid = $node->nid;
  $choices = issue_choices($nid);

  # template for vote count
  $pattern = array();
  foreach ($choices as $i => $choice) {
    $pattern[$i] = array();
  }

  # Get votes
  $votes = array();
  $result = db_query("SELECT * FROM {poll_votes} AS pv INNER JOIN {user_profile} AS up ON up.uid = pv.uid WHERE  pv.nid='%d'", $nid);
  while ($row = db_fetch_array($result)) {
    $votes[] = $row;
  }

  # Get categories
  $cat = issue_results_graph_highchart_filter_categories();

  # Initialize statistics
  foreach ($cat as $key => &$data) {

    if ( $key == '' ) {
      $data['#results'] = array();
      $data['#options'] = array();
      foreach ($choices as $i => $choice) {
        $data['#options'][] = $choice['short_answer'];
      }
    }
    $data['#results'] = $pattern;
    foreach ($data['#results'] as $choice_key => &$results) {
      foreach ($data['#options'] as $optkey => $option) {
        $results[$optkey] = 0;
      }
    }
  }

  # Collect statistics
  foreach ($votes as $vote) {
    foreach ($cat as $key => &$data) {
      $counts = &$data['#results'][$vote['chorder']];
      // var_dump($results);die();
      switch ($key) {
        case '' :
          $counts[$vote['chorder']]++;
        break;
        case 'age' :
          if ($vote['age'] == 0) {
            $counts[3]++;
          } elseif ($vote['age'] >= 51) {
            $counts[2]++;
          } elseif ($vote['age'] >= 31) {
            $counts[1]++;
          } else {
            $counts[0]++;
          }
        break;
        case 'gender' :
          if ($vote['gender'] == 1) {
            $counts[0]++;
          } elseif ($vote['gender'] == 2) {
            $counts[1]++;
          } else {
            $counts[2]++;
          }
        break;
        case 'religion' :
          $index = array_search($vote['religion'], $data['#options']);
          if (false !== $index) {
            $counts[$index]++;
          } else {
            $counts[sizeof($counts)-1]++;
          }
        break;
        case 'ethnicity' :
          $index = array_search($vote['ethnic'], $data['#options']);
          if (false !== $index) {
            $counts[$index]++;
          } else {
            $counts[sizeof($counts)-1]++;
          }
        break;
        case 'income' :
          $index = array_search($vote['income'], $data['#options']);
          if (false !== $index) {
            $counts[$index]++;
          } else {
            $counts[sizeof($counts)-1]++;
          }
        break;
        case 'marital' :
          $index = array_search($vote['marital'], $data['#options']);
          if (false !== $index) {
            $counts[$index]++;
          } else {
            $counts[sizeof($counts)-1]++;
          }
        break;
        case 'sex_orient' :
          $index = array_search($vote['sorient'], $data['#options']);
          if (false !== $index) {
            $counts[$index]++;
          } else {
            $counts[sizeof($counts)-1]++;
          }
        break;
        case 'education' :
          $index = array_search($vote['edu'], $data['#options']);
          if (false !== $index) {
            $counts[$index]++;
          } else {
            $counts[sizeof($counts)-1]++;
          }
        break;
      }
    }
  }
  drupal_add_js(array('charts' => array('highchart' => $cat)), 'setting');
}

/*
 * Highchart Filter Form
 */
function issue_results_graph_highchart_filter_form() {
  $form = array();

  $form['filter'] = array(
    '#type'     => 'select',
    '#options'  => array(
      //
    ),
    '#prefix'   => '<div id="contentr1"><div>',
    '#suffix'   => '</div><div id="chart_div" style="width:300px; min-width:300px; min-height: 280px;"></div></div>',
    '#id'       => 'filter',
  );
  $cat = issue_results_graph_highchart_filter_categories();
  foreach ($cat as $key => $data) {
    $form['filter']['#options'][$key] = $data['#name'];
  }

  return $form;
}

/*
 * Quick facts
 *
 * TODO -
 */

/*
 * Graphs' page Legend
 */
function theme_issue_results_graph_legend($node) {
  $output = '<dl>';
  $pattern = '<dd>%s:</dd><dt style="background-color:%s;">color</dt>';
  $choices = issue_choices($node->nid);
  foreach ($choices as $index => $answer) {
    $output .= sprintf($pattern, $answer['short_answer'], issue_colors($index));
  }
  $output .= '</dl>';
  return $output;
}

/*
 * Highstock History
 *
 * @see issue_results_graph_highstock_history_data()
 */
function theme_issue_results_graph_highstock_history($node) {
  issue_results_graph_highstock_history_data($node);
  drupal_add_js(drupal_get_path('module', 'issue') . "/js/highstock/highstock.js");
  drupal_add_js(drupal_get_path('module', 'issue') . "/js/chart.highstock.js");
  return '
    <div id="container_graph" class="highcharts-container" style="min-height:280px; width: 100%;"></div>
    <div id="resource" style="height:auto; width: 100%; margin: 0 auto; clear:both"></div>
  ';
}

/*
 * Highstock History Data Collector
 */
function issue_results_graph_highstock_history_data($node) {
  $nid = $node->nid;
  $choices = issue_choices($nid);

  # Get the vote history
  $votes = array();
  $mindate = time();
  $maxdate = date('Y-m-d');
  $result = db_query("SELECT pvh.*, DATE(pvh.date_voted) AS date FROM {poll_votes_history} pvh WHERE pvh.nid = '%d' ORDER BY date_voted ASC", $nid);
  while ($row = db_fetch_array($result)) {
    $row['time'] = strtotime($row['date']);
    if ($row['time'] < $mindate) {
      $mindate = $row['time'];
    }
    $votes[] = $row;
  }
  # Get the date range of the votes
  $date_range = dates_range(date('Y-m-d',$mindate), $maxdate);
  $week = count($date_range) > 6;
  if (!$week) {
    $date_range = dates_range(date('Y-m-d',strtotime('-6 days',strtotime($maxdate))), $maxdate);
  }
  # Get the starting date for graph
  $mindate = array(
    'year' => date('Y', $mindate),
    'month' => date('m', $mindate) - 1,
    'day' => $week ? date('d', $mindate) : date("d") - 6,
  );
  # Initialize statistics array
  $stats = array();
  $stats_patt = array();
  foreach ($choices as $i => $choice) {
    $stats_patt[$i] = 0;
  }
  foreach ($date_range as $date) {
    $stats[$date] = $stats_patt;
  }
  # Collect statistics
  $cdate = $date_range[0];
  $ctime = strtotime($cdate);
  $votes_count = count($votes);
  for ($i=0; $i<$votes_count; $i++) {
    $vote = $votes[$i];
    # Copy prev results
    if ($vote['time'] > $ctime) {
      $tmp_date = strtotime('+1 day', $ctime);
      while ($tmp_date <= $vote['time']) {
        $stats[date('Y-m-d', $tmp_date)] = $stats[$cdate];
        $tmp_date = strtotime('+1 day', $tmp_date);
      }
      $ctime = $vote['time'];
      $cdate = date('Y-m-d', $ctime);
    }
    $m = $vote['status'] == 1 ? 1 : -1;
    $stats[$cdate][$vote['chorder']] += $m;
  }
  # Create a response arrays
  $list = array();
  foreach ($stats as $stat) {
    foreach ($choices as $i => $choice) {
      $list[$i][] = $stat[$i];
    }
  }

  # Put the data to Drupal.settings
  drupal_add_js(array('charts' => array('highstock' => array(
    'date' => $mindate,
  ))), 'setting');
  foreach ($choices as $i => $choice) {
    drupal_add_js(array('charts' => array('highstock' => array(
      'choice'.$i => array(
      'name' => $choices[$i]['short_answer'],
      'data' => $list[$i],
    )))), 'setting');
  }
}

/*
 * Graphs' pages Google Map
 */
function theme_issue_results_graph_gmap($node){
  $gmap = array();
  $result = db_query("
    SELECT up.latitude, up.longitude
    FROM {user_profile} AS up INNER JOIN {poll_votes} pv ON pv.uid = up.uid
    WHERE up.latitude <> '' AND up.longitude <> '' AND pv.nid = '%d'",
    $node->nid
  );
  while ($row = db_fetch_object($result)) {
    $gmap[] = array($row->latitude, $row->longitude, issue_colors());
  }
  drupal_add_js(array('charts' => array('gmap' => $gmap)), 'setting');
  drupal_add_js(drupal_get_path('module', 'issue') . '/js/chart.gmap.js');
  return '
    <script type="text/javascript" src="https://maps.google.com/maps/api/js?sensor=false"></script>
    <div id="map_div" style="width: 100%; min-height: 280px"></div>
  ';
}

/*
 * Arguments List
 *
 * @see arguments.forms.inc
 */
function theme_issue_arguments($node) {
  if (user_is_logged_in()) {
    $arguments_form = drupal_get_form('arguments_form', $node->nid);
  } else {
    $arguments_form =
      '<div class="'.ugc_loginbox_class(true).'" align="center"><b>' .
        t('Please log in to participate in the debate') .
      '</b></div>';
  }

  $dr = arguments_get_list($node->nid);

  return theme('issue_debate_area',
    $arguments_form,
    $dr['#count'][TYPE_DEBATE],
    $dr['#count'][TYPE_RESOURCE],
    issue_choices($node->nid),
    $node->nid
  );
}


























/*
 * Like/Dislike bar
 *
 * @pro    - agree count
 * @con    - disagree count
 */
function theme_like_dislike_bar($pro, $con) {
  $total = $pro + $con;
  $pro_perc = $total != 0 ? ($pro*100)/$total : 0;
  $con_perc = $total != 0 ? ($con*100)/$total : 0;
  return
    '<span id="like-percent-area" class="like-per" style="width:'.$pro_perc.'%;"></span>'.
    '<span id="dislike-percent-area" class="dislike-per" style="width:'.$con_perc.'%;"></span>';
}







/*
 * Sub Loader Image
 */
function theme_sub_loader( $styles ) {
  global $base_url, $theme;
  return
    '<span id="sub_loader" style="'.$styles.'">
      <img src="'.$base_url.'/'.drupal_get_path('theme', $theme).'/images/loading_min.gif" alt="loading">
    </span>';
}

