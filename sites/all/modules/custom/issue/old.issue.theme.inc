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

function theme_issue_results_graph_highchart_filter($node)
{
  issue_results_graph_highchart_filter_data($node);
  drupal_add_js(drupal_get_path('module', 'issue') . "/js/highcharts/highcharts.js");
  drupal_add_js(drupal_get_path('module', 'issue') . "/js/chart.highchart.js");
  return drupal_get_form('issue_results_graph_highchart_filter_form');
}

/*
 * get default value for field
 */

function issue_profile_field_default_value($field)
{
  return $field->type == 'selection' ? '-1' : '';
}

/*
 * get the fields for statistics
 */

function issue_profile_fields()
{
  return array('profile_yob', 'profile_gender', 'profile_religion', 'profile_ethnicity', 'profile_sorient', 'profile_education', 'profile_income');
}

/*
 * Highchart Filter Categories
 */

function issue_results_graph_highchart_filter_categories()
{
  static $cat = array();
  if (!empty($cat)) {
    return $cat;
  }

  $stat_fields = issue_profile_fields();
  foreach ($stat_fields as &$field) {
    $field = "'" . $field . "'";
  }
  $fields = array();
  $result = db_query("SELECT * FROM {profile_fields} WHERE name IN (" . implode(',', $stat_fields) . ")");
  while ($row = db_fetch_object($result)) {
    $fields[] = $row;
  }

  $cat[''] = array(
    '#name' => t('Total Votes'),
    '#options' => array(
      'Total Votes',
    ),
  );

  foreach ($fields as $field) {

    switch ($field->name) {
      case 'profile_yob' :
        $cat['age'] = array(
          '#name' => t('Age'),
          '#options' => array(
            '18-30', '30-50', '50 above', 'undefined',
          ),
        );
        break;
      default:
        $name = str_replace('profile_', '', $field->name);
        $cat[$name] = array(
          '#name' => t($field->title),
          '#options' => explode("\n", $field->options),
        );
        $cat[$name]['#options'][] = 'undefined';
        break;
    }
  }

  return $cat;
}

/*
 * Quick facts
 */

function theme_issue_results_insightview($node)
{
  # get the data
  $data = issue_results_graph_highchart_filter_data($node);

  $choices = issue_choices($node->nid);

  $totals_all = 0;
  $totals = &$data['']['#results'];
  foreach ($totals as $i => &$total) {
    $total = $total[$i];
    $totals_all += $total;
  }

  $list_total = array();
  $list_choices = array();
  foreach ($data as $key => &$dataset) {
    if ($key == '') {
      continue;
    }
    $results = $dataset['#results'];

    # get "27% of voters make between $150,000 - $299,999"
    # get "57% of votes for rumor are Hindu"
    $tmp_total = array();
    foreach ($results as $chorder => $counts) {
      foreach ($counts as $optkey => $count) {
        $tmp_total[$optkey] += $count;
        if ($dataset['#options'][$optkey] != 'undefined' && $count != 0) {
          $list_choices[$chorder . '-' . $optkey . '-' . $key] = round(100 * $count / $totals[$chorder], 0);
        }
      }
    }

    foreach ($tmp_total as $optkey => $count) {
      if ($dataset['#options'][$optkey] != 'undefined' && $count != 0) {
        $list_total[$key . '-' . $optkey] = round(100 * $count / $totals_all, 0);
      }
    }
  }
  arsort($list_total);
  arsort($list_choices);

  # output
  $output = array();
  #1
  $i = 0;
  foreach ($list_total as $key => $percent) {
    $key = explode('-', $key);
    $optkey = $key[1];
    $key = $key[0];

    switch ($key) {
      case 'age' :
        $output[] = $percent . '% ' . t('of voters are') . ' <span class="highlight">' . t($data[$key]['#options'][$optkey]) . ' ' . t('yo') . '</span>';
        break;
      case 'income' :
        $output[] = $percent . '% ' . t('of voters make') . ' <span class="highlight">' . t($data[$key]['#options'][$optkey]) . '</span>';
        break;
      case 'gender' :
      case 'ethnicity' :
      case 'marital' :
      case 'sorient' :
      case 'education' :
      case 'religion' :
      default :
        $output[] = $percent . '% ' . t('of voters are') . ' <span class="highlight">' . t($data[$key]['#options'][$optkey]) . '</span>';
        break;
    }
    if (++$i > 1) {
      break;
    }
  }

  $i = 0;
  foreach ($list_choices as $key => $percent) {
    $key = explode('-', $key);
    $chorder = $key[0];
    $optkey = $key[1];
    $key = $key[2];

    $text = '';
    foreach ($choices as $choice) {
      if ($choice['chorder'] == $chorder) {
        $text = $choice['short_answer'];
      }
    }
    $output[] = $percent . '% ' . t('of votes for') . ' <span class="highlight">' . t($text) . '</span> ' . t('are') . ' ' .
      ($data[$key]['#options'][$optkey]);

    if (++$i > 3) {
      break;
    }
  } # get "57% of votes for rumor are Hindu"

  return '<span>' . implode('</span></br><span>', $output) . '</span></br>';
}

/*
 * Highchart Filter Data Collector
 *
 * @see issue_results_graph_highchart_filter_categories
 */

function issue_results_graph_highchart_filter_data($node)
{
  static $dataset = array();
  if (empty($dataset)) {
    $nid = $node->nid;
    $choices = issue_choices($nid);

    # Get categories
    $cat = issue_results_graph_highchart_filter_categories();

    # template for vote count
    $pattern = array();
    foreach ($choices as $i => $choice) {
      $pattern[$i] = array();
    }

    # Initialize statistics
    foreach ($cat as $key => &$data) {
      if ($key == '') {
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

    # get total votes
    $counts = &$cat['']['#results'];
    $result = db_query("SELECT chorder, COUNT(*) count FROM poll_votes WHERE nid = '%d' GROUP BY chorder", $nid);
    while ($vote = db_fetch_array($result)) {
      $counts[$vote['chorder']][$vote['chorder']] = (int)$vote['count'];
    }

    # get other votes
//    $votes = array();
//    $stat_fields = issue_profile_fields();
//    foreach ($stat_fields as &$field) {
//      $field = "'" . $field . "'";
//    }
//    $result = db_query("SELECT pf.name, pval.value, pv.chorder FROM {poll_votes} AS pv INNER JOIN {profile_values} pval ON pv.uid = pval.uid INNER JOIN {profile_fields} pf ON pf.fid = pval.fid AND pf.name IN (" . implode(',', $stat_fields) . ") WHERE pv.nid = '%d'", $nid);
//    while ($row = db_fetch_array($result)) {
//      $votes[] = $row;
//    }

    # Collect statistics
    $y = date('Y');
    $stat_fields = issue_profile_fields();
    foreach ($stat_fields as $field) {
      $result = db_query("SELECT pval.value, pv.chorder FROM {poll_votes} pv LEFT JOIN {profile_values} pval ON pv.uid = pval.uid AND pval.fid = (SELECT fid FROM {profile_fields} WHERE name = '%s') WHERE pv.nid = '%d'", $field, $nid);
      while ($vote = db_fetch_array($result)) {
        switch ($field) {
          case 'profile_yob' :
            $counts = &$cat['age']['#results'][$vote['chorder']];
            if ($vote['value'] == '') {
              $counts[3]++;
            } else {
              $age = $y - $vote['value'];
              if ($age >= 51) {
                $counts[2]++;
              } elseif ($age >= 31) {
                $counts[1]++;
              } else {
                $counts[0]++;
              }
            }
            break;
          default:
            $name = str_replace('profile_', '', $field);
            $counts = &$cat[$name]['#results'][$vote['chorder']];
            if (isset($cat[$name]['#options'][$vote['value']])) {
              $counts[$vote['value']]++;
            } else {
              $counts[sizeof($counts) - 1]++;
            }
            break;
        }
      }
    }

//    foreach ($votes as $vote) {
//      $totals[$vote['name']]++;
//      switch ($vote['name']) {
//        case 'profile_yob' :
//          $counts = &$cat['age']['#results'][$vote['chorder']];
//          if ($vote['value'] == '') {
//            $counts[3]++;
//          }
//          else {
//            $age = $y - $vote['value'];
//            if ($age >= 51) {
//              $counts[2]++;
//            }
//            elseif ($age >= 31) {
//              $counts[1]++;
//            }
//            else {
//              $counts[0]++;
//            }
//          }
//          break;
//        default:
//          $name = str_replace('profile_', '', $vote['name']);
//          $counts = &$cat[$name]['#results'][$vote['chorder']];
//          if (isset($cat[$name]['#options'][$vote['value']])) {
//            $counts[$vote['value']]++;
//          }
//          else {
//            $counts[sizeof($counts) - 1]++;
//          }
//        break;
//      }
//    }

//    foreach (issue_profile_fields() as $key) {
//      switch ($key) {
//        case 'profile_yob' :
//          $counts = &$cat['age']['#results'][$vote['chorder']];
//          $counts[3] = $totals['#all'] - $totals[$key];
//        break;
//        default:
//          $name = str_replace('profile_', '', $vote['name']);
//          $counts = &$cat[$name]['#results'][$vote['chorder']];
//          $counts[sizeof($counts) - 1] = $totals['#all'] - $totals[$key];
//          break;
//      }
//    }

    drupal_add_js(array('charts' => array('highchart' => $cat)), 'setting');
    $dataset = $cat;
  }
  return $dataset;
}

/*
 * Highchart Filter Form
 */

function issue_results_graph_highchart_filter_form()
{
  $form = array();

  $form['filter'] = array(
    '#type' => 'select',
    '#options' => array( //
    ),
    '#prefix' => '<div id="contentr1"><div>',
    '#suffix' => '</div><div id="chart_div" style="width:100%; min-height: 280px;"></div></div>',
    '#id' => 'filter',
  );
  $cat = issue_results_graph_highchart_filter_categories();
  foreach ($cat as $key => $data) {
    $form['filter']['#options'][$key] = $data['#name'];
  }

  return $form;
}

/*
 * Graphs' page Legend
 */

function theme_issue_results_graph_legend($node)
{
  $output = '';
  $pattern = '<dl><dd>%s:</dd><dt style="background-color:%s;">color</dt></dl>';
  $choices = issue_choices($node->nid);
  foreach ($choices as $index => $answer) {
    $output .= sprintf($pattern, $answer['short_answer'], issue_colors($index));
  }
  return $output;
}

/*
 * Highstock History
 *
 * @see issue_results_graph_highstock_history_data()
 */

function theme_issue_results_graph_highstock_history($node)
{
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
 *
 * TODO dependency FROM poll_ext
 */

function issue_results_graph_highstock_history_data($node)
{
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
  $date_range = dates_range(date('Y-m-d', $mindate), $maxdate);
  $week = count($date_range) > 6;
  if (!$week) {
    $date_range = dates_range(date('Y-m-d', strtotime('-6 days', strtotime($maxdate))), $maxdate);
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
  for ($i = 0; $i < $votes_count; $i++) {
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

  // fix the lail of data
  $stats_last = $stats[$cdate];
  while ($ctime < time()) {
    $ctime = strtotime('+1 day', $ctime);
    $cdate = date('Y-m-d', $ctime);
    $stats[$cdate] = $stats_last;
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
    'stats' => $stats,
    'cdate' => $cdate,
  ))), 'setting');
  foreach ($choices as $i => $choice) {
    drupal_add_js(array('charts' => array('highstock' => array(

      'choice' . $i => array(
        'name' => $choices[$i]['short_answer'],
        'data' => $list[$i],
      )))), 'setting');
  }
}

/*
 * Graphs' pages Google Map
 */

function theme_issue_results_graph_gmap($node)
{
  $gmap = array();
  $result = db_query("
    SELECT up.latitude, up.longitude
    FROM {user_profile} AS up INNER JOIN {poll_votes} pv ON pv.uid = up.uid
    WHERE up.latitude <> '' AND up.longitude <> '' AND pv.nid = '%d'", $node->nid
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

function theme_issue_arguments($node)
{
  if (user_is_logged_in()) {
    $arguments_form = drupal_get_form('arguments_form', $node->nid);
  } else {
    $arguments_form =
      '<div class="' . (!module_exists('user_login_modal') ? "" : user_login_modal_class(true)) . '" align="center"><b>' .
        t('Please log in to participate in the debate') .
        '</b>
      </div>';
  }

  # TODO there should be special field for that
  $dr = arguments_get_list($node->nid);

  # Prepare the data for the debate analysis
  $data = array();
  $choices = issue_choices($node->nid);
  foreach ($choices as $choice) {
    $data[] = array(
      'name' => t('Strength'),
      'color' => '#C2499B',
      'y' => 0,
    );
  }

  $result = db_query("
    SELECT ao.chorder, SUM(vv.value)*ao.val AS value
    FROM {content_type_forum} ctf
    INNER JOIN {arguments_options} ao ON ao.nid = ctf.nid
    LEFT JOIN {votingapi_vote} vv ON vv.content_id = ctf.nid AND vv.content_type = 'node'
    WHERE ctf.field_ref_qid_nid = '%d'
    GROUP BY ctf.nid, ao.chorder
    ORDER BY ao.chorder
  ", $node->nid);
  $args = array();
  while ($row = db_fetch_array($result)) {
    $args[$row['chorder']] += $row['value'];
  }
  foreach ($choices as $i => $choice) {
    $value = $args[$choice['chorder']];
    $data[$i]['color'] = $value > 0 ? '#55BA59' : '#C2499B';
    $data[$i]['y'] = (float)$value;
  }

  // SELECT 1 AS str, ctf.*, ao.* FROM `content_type_forum` ctf INNER JOIN arguments_options ao ON ao.nid = ctf.nid WHERE ctf.field_ref_qid_nid = 36981
  drupal_add_js(array('charts' => array('strength' => $data)), 'setting');
  drupal_add_js(drupal_get_path('module', 'issue') . "/js/chart.strength.js");

  return theme('issue_debate_area', $arguments_form, $dr['#count'][TYPE_DEBATE], $dr['#count'][TYPE_RESOURCE], issue_choices($node->nid), $node->nid
  );
}

/*
 * Sub Loader Image
 */

function theme_sub_loader($styles)
{
  global $base_url, $theme;
  return
    '<span id="sub_loader" style="' . $styles . '">
      <img src="' . $base_url . '/' . drupal_get_path('theme', $theme) . '/images/loading_min.gif" alt="loading">
    </span>';
}



/*
 * Theme issue_popular_categories
 */

function theme_issue_popular_categories()
{
  $list = array();
  $result = db_query("
    SELECT
      COUNT(*) AS count,
      td.name,
      tn.tid AS tid,
      IFNULL(th1.parent,0) AS pid,
      IFNULL(th2.parent,0) AS ppid
    FROM poll_votes pv
    INNER JOIN term_node tn ON tn.nid = pv.nid
    INNER JOIN term_data AS td ON td.tid = tn.tid
    LEFT JOIN term_hierarchy th1 ON th1.tid = tn.tid AND th1.parent <> 0
    LEFT JOIN term_hierarchy th2 ON th2.tid = th1.parent AND th2.parent <> 0
    GROUP BY tn.tid ORDER by count DESC LIMIT 15");
  while ($item = db_fetch_array($result)) {
    $list[] = $item;
  }
  if (empty($list)) {
    return '';
  }
  $output = '
    <ul class="tags">
      <div class="icon cat2 text"></div>
      <label for="" class="tags-on">' . t('POPULAR CATEGORIES') . '</label>
  ';
//  $pattern = '<li><a href="/issues/0/%d/%d/%d/0/0/0/alltime">%s</a></li>';
  $href = 'issues';
  foreach ($list as $item) {
    $output .= '<li>' . l($item['name'], $href, array('query' => array('tid' => $item['tid']))) . '</li>';
  }
  $output .= '</ul>';
  return $output;
}
