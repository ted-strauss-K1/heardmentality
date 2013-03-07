<?php

/**
 * Colors
 *
 * @param bool $index
 * @return array
 */
function charts_colors($index = false)
{
  static $i = 0;
  static $colors = array();
  if (empty($colors)) {
    $colors += array(
      '#934d9e',
      '#FF7F00',
      '#50c0ac',
      '#0c6926',
      '#ef4c8d',
      '#362750',
      '#e1e43c',
      '#ef3d3b',
      '#3cc7f4',
      '#589a1c',
      '#C2499B',
      '#f89521',
      '#CC2027',
      '#55ba59',
      '#d5bc29',
      '#6ccbd5',
      '#43B649',
      '#F6EB16'
    );
  }
  if ($index === true) {
    return $colors;
  }
  if ($index !== false && isset($colors[$index])) {
    return $colors[$index];
  } else {
    $color = $colors[$i];
    $i = ($i + 1) % count($colors);
    return $color;
  }
}

/**
 * Implementation of hook_theme()
 *
 * @return array
 */
function charts_theme()
{
  $theme = array();

  $theme['issue_charts'] = array(
    'arguments' => array('node' => NULL),
    'template' => 'templates/issue-charts',
    'preprocess functions' => array('issue_charts_preprocess'),
  );
  $theme['issue_charts_inner'] = array(
    'arguments' => array('node' => NULL),
    'template' => 'templates/issue-charts-inner',
    'preprocess functions' => array('issue_charts_common_preprocess', 'issue_charts_inner_preprocess'),
  );

  # chart parts
  $theme['issue_charts_filter'] = array(
    'arguments' => array('node' => NULL),
  );
  $theme['issue_charts_quickfacts'] = array(
    'arguments' => array('node' => NULL),
  );
  $theme['issue_charts_legend'] = array(
    'arguments' => array('node' => NULL),
  );
  $theme['issue_charts_history'] = array(
    'arguments' => array('node' => NULL),
  );
  $theme['issue_charts_gmap'] = array(
    'arguments' => array('node' => NULL),
  );

  $theme['issue_charts_strength'] = array(
    'arguments' => array('node' => NULL),
  );

  return $theme;
}

/**
 * Preprocess function for issue_charts
 *
 * @param $vars
 */
function issue_charts_preprocess(&$vars)
{
  $node = $vars['node'];

  # vote count
  $count = 0;
  if ($node->choice) {
    foreach ($node->choice as $choice) {
      $count += $choice['chvotes'];
    }
  }
  $node->votecount = $count;

  # voted or not
  $voted = $node->vote != -1;
  if (module_exists('poll_suggest')) {
    $voted = $voted || ($node->vote_suggest != -1);
  }

  if (!$voted) {
    $vars['charts'] = '<span class="no_show">' . t('Vote now to show results.') . '</span>';
//  } elseif ($count < 10) {
//    $vars['charts'] = '<span class="no_show">' . t('We need 10 votes to show the results goodies, use the share links above  to let your peeps know.') . '</span>';
  } else {
    $vars['charts'] = theme('issue_charts_inner', $node);
  }
}

function issue_charts_chtexts($node)
{
  static $chtexts = null;

  if (is_null($chtexts)) {
    $chtexts = array();
    if ($node->choice) {
      foreach ($node->choice as $choice) {
        $chtexts[] = empty($choice['chtext_short']) ? $choice['chtext'] : $choice['chtext_short'];
      }
    }
  }

  return $chtexts;
}

  /**
   * Preprocess function for issue_charts_inner
   *
   * @param $vars
   */
function issue_charts_common_preprocess($vars)
{
  // run once
  static $js;
  if (!is_null($js)) {
    return;
  }
  $js = true;

  $node = $vars['node'];
  # short names for choices
  $chtexts = issue_charts_chtexts($node);
  # save to js settings
  drupal_add_js(array('charts' => array('choices' => $chtexts)), 'setting');
  drupal_add_js(array('charts' => array('count' => count($chtexts))), 'setting');
  drupal_add_js(array('charts' => array('colors' => charts_colors(true))), 'setting');
}

/**
 * Preprocess function for issue_charts_inner
 *
 * @param $vars
 */
function issue_charts_inner_preprocess(&$vars)
{
  $node = $vars['node'];

  # short names for choices
  $chtexts = issue_charts_chtexts($node);

  # Highchart Filter
  $vars['filter'] = theme('issue_charts_filter', $node);
  # Quick facts
  $vars['quickfacts'] = $node->votecount <= 10 ? t('We need 10 votes to show the results goodies, use the share links above  to let your peeps know.') : theme('issue_charts_quickfacts', $node);
  # Legend
  $vars['legend'] = theme('issue_charts_legend', $chtexts);
  # Highchart History
  $vars['history'] = theme('issue_charts_history', $node);
  # Google map
  $vars['gmap'] = theme('issue_charts_gmap', $node);
}

/**
 * Filter (Highchart)
 *
 * @param $node
 * @return null|string
 */
function theme_issue_charts_filter($node)
{
  issue_charts_filter_preprocess($node);
  drupal_add_js(drupal_get_path('module', 'issue') . "/charts/highcharts/highcharts.js");
  drupal_add_js(drupal_get_path('module', 'issue') . "/charts/chart.filter.js");
  return drupal_get_form('issue_charts_filter_form');
}

/**
 * Preprocess for Filter (Highcharts)
 *
 * @param $node
 * @return mixed
 */
function issue_charts_filter_preprocess($node)
{
  static $dataset = null;

  if (is_null($dataset)) {
    $dataset = array();

    $chtexts = issue_charts_chtexts($node);

    # Get categories
    $cat = issue_charts_filter_categories();

    # template for vote count
    $pattern = array();
    foreach ($chtexts as $i => $choice) {
      $pattern[$i] = array();
    }

    # Initialize statistics
    foreach ($cat as $key => &$data) {
      if ($key == '') {
        $data['#results'] = array();
        $data['#options'] = $chtexts;
      }
      $data['#results'] = $pattern;
      foreach ($data['#results'] as &$results) {
        foreach ($data['#options'] as $optkey => $option) {
          $results[$optkey] = 0;
        }
      }
    }

    # get total votes
    $counts = & $cat['']['#results'];
    $result = db_query("SELECT chorder, COUNT(*) count FROM poll_votes WHERE nid = '%d' GROUP BY chorder", $node->nid);
    while ($vote = db_fetch_array($result)) {
      $counts[$vote['chorder']][$vote['chorder']] = (int)$vote['count'];
    }

    # Collect statistics
    $y = date('Y');
    $stat_fields = issue_charts_filter_fields();
    foreach ($stat_fields as $field) {
      $result = db_query("SELECT pval.value, pv.chorder FROM {poll_votes} pv LEFT JOIN {profile_values} pval ON pv.uid = pval.uid AND pval.fid = (SELECT fid FROM {profile_fields} WHERE name = '%s') WHERE pv.nid = '%d'", $field, $node->nid);
      while ($vote = db_fetch_array($result)) {
        switch ($field) {
          case 'profile_yob' :
            $counts = & $cat['age']['#results'][$vote['chorder']];
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
            $counts = & $cat[$name]['#results'][$vote['chorder']];
            if (isset($cat[$name]['#options'][$vote['value']])) {
              $counts[$vote['value']]++;
            } else {
              $counts[sizeof($counts) - 1]++;
            }
            break;
        }
      }
    }

    drupal_add_js(array('charts' => array('filter' => $cat)), 'setting');
    $dataset = $cat;
  }
  return $dataset;
}


/**
 * Filter (Highcharts) -- form
 * @return array
 */
function issue_charts_filter_form()
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
  $cat = issue_charts_filter_categories();
  foreach ($cat as $key => $data) {
    $form['filter']['#options'][$key] = $data['#name'];
  }

  return $form;
}

/**
 * Filter (Highcharts) -- categories
 *
 * @return mixed
 */
function issue_charts_filter_categories()
{
  static $cat = null;

  if (is_null($cat)) {
    $cat = array();

    $stat_fields = issue_charts_filter_fields();
    $fields = array();
    $result = db_query("SELECT * FROM {profile_fields} WHERE name IN (" . db_placeholders($stat_fields, 'varchar') . ")", $stat_fields);
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
  }


  return $cat;
}

/**
 * Filter (Highcharts) -- profile fields
 *
 * @return array
 */
function issue_charts_filter_fields()
{
  return array('profile_yob', 'profile_gender', 'profile_religion', 'profile_ethnicity', 'profile_sorient', 'profile_education', 'profile_income');
}

/**
 * Quick facts
 *
 * @param $node
 * @return string
 */
function theme_issue_charts_quickfacts($node)
{
  # get the data
  $data = issue_charts_filter_preprocess($node);

  $totals_all = 0;
  $totals = & $data['']['#results'];
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

  $chtexts = issue_charts_chtexts($node);

  $i = 0;
  foreach ($list_choices as $key => $percent) {
    $key = explode('-', $key);
    $chorder = $key[0];
    $optkey = $key[1];
    $key = $key[2];

    $text = $chtexts[$chorder];

    $output[] = $percent . '% ' . t('of votes for') . ' <span class="highlight">' . t($text) . '</span> ' . t('are') . ' ' .
      ($data[$key]['#options'][$optkey]);

    if (++$i > 3) {
      break;
    }
  } # get "57% of votes for rumor are Hindu"

  return '<span>' . implode('</span></br><span>', $output) . '</span></br>';
}


/**
 * Graphs' page Legend
 *
 * @param $chtexts
 * @return string
 */
function theme_issue_charts_legend($chtexts)
{
  $output = '';
  $pattern = '<dl><dd>%s:</dd><dt style="background-color:%s;">color</dt></dl>';
  foreach ($chtexts as $index => $answer) {
    $output .= sprintf($pattern, $answer, charts_colors($index));
  }
  return $output;
}

/**
 * History (Highstorck)
 *
 * @param $node
 * @return string
 */
function theme_issue_charts_history($node)
{
  if (!module_exists('poll_ext')) {
    return '';
  }
  issue_charts_history_preprocess($node);
  drupal_add_js(drupal_get_path('module', 'issue') . "/charts/highstock/highstock.js");
  drupal_add_js(drupal_get_path('module', 'issue') . "/charts/chart.history.js");
  return '
    <div id="container_graph" class="highcharts-container" style="min-height:280px; width: 100%;"></div>
    <div id="resource" style="height:auto; width: 100%; margin: 0 auto; clear:both"></div>
  ';
}

/**
 * Range of dates - Y-m-d
 *
 * @param $date1
 * @param $date2
 * @return array
 */
function dates_range($date1, $date2)
{
  $range = array();
  if (!empty($date1) && !empty($date2) && $date1 < $date2) {
    $date1 = strtotime($date1);
    $date2 = strtotime($date2);
    $range[] = date('Y-m-d', $date1);
    while ($date1 < $date2) {
      $date1 = strtotime('+1 day', $date1);
      $range[] = date('Y-m-d', $date1);
    }
  }
  return $range;
}

/**
 * Preprocess function for issue_charts_history
 *
 * @param $vars
 */
function issue_charts_history_preprocess($node)
{
  # short names for choices
  $chtexts = issue_charts_chtexts($node);

  # Get the vote history
  $votes = array();
  $mindate = time();
  $maxdate = date('Y-m-d');
  $result = db_query("SELECT pvh.*, DATE(pvh.date_voted) AS date FROM {poll_votes_history} pvh WHERE pvh.nid = '%d' ORDER BY date_voted ASC", $node->nid);
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
  foreach ($chtexts as $i => $choice) {
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
    foreach ($chtexts as $i => $choice) {
      $list[$i][] = $stat[$i];
    }
  }

  # Put the data to Drupal.settings
  drupal_add_js(array('charts' => array('history' => array(
    'date' => $mindate,
    'stats' => $stats,
    'cdate' => $cdate,
  ))), 'setting');
  foreach ($chtexts as $i => $choice) {
    drupal_add_js(array('charts' => array('history' => array(
      'choice' . $i => array(
        'name' => $choice,
        'data' => $list[$i],
      )))), 'setting');
  }
}

/**
 * Graphs' pages Google Map
 *
 * @param $node
 * @return string
 */
function theme_issue_charts_gmap($node)
{
  $gmap = array();

  $fieldmap = variable_get(PROFILE_FIELDMAP, array());

  $result = db_query("
    SELECT pv1.value lat, pv2.value lng
    FROM {poll_votes} pv
    INNER JOIN {users} u ON u.uid = pv.uid
    INNER JOIN {profile_values} pv1 ON pv1.fid = '%s' AND pv1.uid = u.uid
    INNER JOIN {profile_values} pv2 ON pv2.fid = '%s' AND pv2.uid = u.uid
    WHERE pv.nid = '%d' AND pv1.value <> '' AND pv2.value <> ''",
    $fieldmap['profile_lat']->fid, $fieldmap['profile_lng']->fid, $node->nid
  );

  while ($row = db_fetch_object($result)) {
    $gmap[] = array($row->lat, $row->lng, charts_colors());
  }
  drupal_add_js(array('charts' => array('gmap' => $gmap)), 'setting');
  drupal_add_js(array('charts' => array('gmap_icons' => drupal_get_path('module', 'issue') . '/charts/icons')), 'setting');
  drupal_add_js(drupal_get_path('module', 'issue') . '/charts/chart.gmap.js');
  return '
    <script type="text/javascript" src="https://maps.google.com/maps/api/js?sensor=false"></script>
    <div id="map_div" style="width: 100%; min-height: 280px"></div>
  ';
}

/**
 * Strength chart
 *
 * @param $node
 * @return string
 */
function theme_issue_charts_strength($node)
{
  // preprocess
  issue_charts_common_preprocess(array('node' => $node));

  # Prepare the data for the debate analysis
  $data = array();
  $choices = ($node->choice) ? $node->choice : array();
  foreach ($node->choice as $choice) {
    $data[] = array(
      'name' => t('Strength'),
      'color' => '#C2499B',
      'y' => 0,
    );
  }

  $result = db_query("
    SELECT ao.chorder, IFNULL(SUM(vv.value)*ao.val,0) AS value
    FROM {content_type_forum} ctf
    INNER JOIN {argument_options} ao ON ao.nid = ctf.nid
    LEFT JOIN {votingapi_vote} vv ON vv.content_id = ctf.nid AND vv.content_type = 'node'
    WHERE ctf.field_issue_nid = '%d'
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

  # settings
  drupal_add_js(array('charts' => array('strength' => $data)), 'setting');
  drupal_add_js(drupal_get_path('module', 'issue') . "/charts/highcharts/highcharts.js");
  drupal_add_js(drupal_get_path('module', 'issue') . "/charts/chart.strength.js");

  return '<div class="expanding stat"><h6 class="button" id="deb-ana">' . t('Stats') . '</h6></div>';
}