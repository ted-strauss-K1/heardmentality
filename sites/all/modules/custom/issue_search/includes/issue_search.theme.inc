<?php

/**
 * @file
 *  Theming callbacks.
 */

/**
 * Search results output.
 *
 * @param array $results
 *  Search results.
 *
 * @return string
 *  Output.
 */
function theme_issue_search_results($results = array())
{
  $output = '';
  foreach ($results as $result) {
    $node = node_load($result['node']->entity_id);
    $output .= node_view($node, true);
  }

  return $output;
}

/**
 * Search filter for Issues.
 *
 * @return string
 *  Output.
 */
function theme_issue_search_filter()
{
  $issues_count = '<i class="icon cat text icon-binoculars-searchalt"></i><label class="tags-on search_issues" for="count_results-wrapper">Search Issues</label><div id="count_results-wrapper" class="form-item"><span>0</span> issues</div>';
  return '<div class="filter_search grey-box poll-box issues_search">' . $issues_count . drupal_get_form('issue_search_filter_form') . '</div>';
}

/**
 * A form with Issues search filters.
 *
 * @global type $user
 *  Current Drupal user.
 *
 * @param type $form_state
 *  Form state.
 *
 * @return string
 *  A set of form elements and their definitions.
 */
function issue_search_filter_form($form_state)
{
  $form = array();

  global $user;

  // get search state
  $search_state = isset($_COOKIE['search']) ? unserialize($_COOKIE['search']) : null;
  $search_state2 = isset($_COOKIE['search2']) ? unserialize($_COOKIE['search2']) : array();

  // clean search state
  if (isset($_GET['tids'])) {
    $search_state = null;
    $search_state2 = null;
  }

  ahah_helper_register($form, $form_state);

  // Main container.
  $form['block'] = array(
    '#type' => 'fieldset',
    '#prefix' => '<div id="block-wrapper">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  // Data.
  $data2 = $form_state['storage'];
  $data = $form_state['storage']['block'];

  if (is_null($data) && is_array($search_state)) { // open the blank page
    $data2 = $search_state;
    $data = $data2['block'] ? $data2['block'] : null;
  } else { // ahah-reload, have the data inside
    $search_state = $data2;
    if (!empty($form_state['post'])) {
      $search_state2 = array();
      foreach (array("region", "voted_status", "search_text", "filter_time", "filter_type") as $key) {
        $search_state2[$key] = $form_state['post'][$key];
      }
    }
  }

  // save search_state to cookies
  setcookie("search", serialize($search_state), time() + 60*60*24, "/");
  setcookie("search2", serialize($search_state2), time() + 60*60*24, "/");

  // Gather info.
  $info_items = array();

  // Gather info: taxonomy.
  $tft_codes = array();
  for ($i = 0; $i >= 0; $i++) {
    if (empty($data['taxonomy-' . $i])) {
      break;
    }
    foreach ($data['taxonomy-' . $i] as $tid => $tname) {
      $tft_codes[] = (int)$tid;
    }
  }

  // Get codes.
  if (isset($_GET['tids']) && empty($data['taxonomy-0'])) {
    $tft_codes = explode(",", $_GET['tids']);
  }
  $tft = tft_list('poll', $tft_codes);

  // Gather info: taxonomy. Show only terms having nodes listed under
  $tft_exist = array();
  $result = db_query("SELECT DISTINCT tn.tid, td.name FROM {term_node} tn INNER JOIN {term_data} td ON td.tid = tn.tid");
  while ($row = db_fetch_array($result)) {
    $tft_exist[$row['tid']] = $row['name'];
  }
  //
  $tft_count = count($tft['list']);
  for ($i = 0; $i < $tft_count; $i++) {
    $tft['list'][$i] = array_intersect_assoc($tft['list'][$i], $tft_exist);
  }

  // Gather info: location.
  $tfl_codes0 = array();
  $tfl_codes1 = array();
  $tfl_codes2 = array();
  for ($i = 0; $i <= 2; $i++) {
    $name = 'tfl_codes' . $i;
    $$name = empty($data['location-' . $i]) ? array() : array_keys($data['location-' . $i]);
  }

  // If logged in & country set.
  if (isset($data2['region']) && $data2['region']) {
    $tfl_codes0 = array($user->profile_country);
    $tfl_codes1 = array();
    $tfl_codes2 = array();
  }

  $tfl = tfl_list($tfl_codes0, $tfl_codes1, $tfl_codes2);

  // Gather info: location. Show only locations having nodes listed under
  $tfl_exist = array();
  $result = db_query("(SELECT DISTINCT city code FROM location) UNION (SELECT DISTINCT CONCAT(country, '_', province) code FROM location) UNION (SELECT DISTINCT country code FROM location)");
  while ($row = db_fetch_array($result)) {
    $tfl_exist[$row['code']] = 1;
  }
  //
  $tfl_count = count($tfl['list']);
  for ($i = 0; $i < $tfl_count; $i++) {
    $keys = array_keys($tfl['list'][$i]);
    foreach ($keys as $key) {
      if (!isset($tfl_exist[$key])) {
        unset($tfl['list'][$i][$key]);
      }
    }
//    $tfl['list'][$i] = array_intersect_assoc($tfl['list'][$i], $tfl_exist);
  }

  // Gather info: info_values.
  foreach (array('tft' => 'taxonomy', 'tfl' => 'location') as $varname => $type) {
    $tf = $$varname;
    for ($i = 0; $i < count($tf['list']); $i++) {
      $options = $tf['list'][$i];
      $checked = $tf['checked'][$i];
      if (!empty($checked)) {
        foreach ($checked as $code) {
          $info_items[] = array(
            'type' => $type . '-' . $i,
            'value' => $code,
            'text' => $options[$code],
          );
        }
      }
    }
  }

  // Container: info.
  global $user;
  drupal_add_js(drupal_get_path('module', 'issue') . "/issue.categories.js");
  $subscriptions = array();
  if (module_exists('subscriptions')) {
    $data = subscriptions_get(array(
      'recipient_uid' => $user->uid,
      'module' => 'node',
      'field' => 'tid',
      'author_uid' => -1,
    ));
    if ($data)
      foreach ($data[$user->uid]['node']['tid'] as $tid => $items) {
        $subscriptions[] = $tid;
      }
  }

//  return  (
//  module_exists('subscriptions') ?
//    sprintf('<input type="checkbox" class="issue_category" title="%s" name="%s" %s>',
//      t('Check to subscribe'), $hierarchy, in_array(preg_replace('/-.*$/', '', $hierarchy), $subscriptions) ? 'checked' : '') : '')

  $info = t('Issues about') . ':<br />';
  foreach ($info_items as $item) {
    if (preg_match('/taxonomy/', $item['type'])) {
      $info .= sprintf('<span>
    <input type="checkbox" class="issue_category" title="%s" name="%s" %s>
    <input type="hidden" name="#edit-block-%s" value="%s">%s<span class="del-item">x</span></span>',
        t('Check to subscribe'), issue_term_parents(taxonomy_get_term($item['value'])), in_array($item['value'], $subscriptions) ? 'checked' : '', $item['type'], $item['value'], $item['text']);
    } else {
      $info .= sprintf('<span><input type="hidden" name="#edit-block-%s" value="%s">%s<span class="del-item">x</span></span>', $item['type'], $item['value'], $item['text']);
    }


  }
  $form['block']['information'] = array(
    '#value' => $info,
    '#type' => 'item',
    '#id' => 'item_results'
  );

  // Lists: taxonomy.
  for ($i = 0; $i < count($tft['list']); $i++) {
    $options = $tft['list'][$i];
    $checked = $tft['checked'][$i];
    $form['block']['taxonomy-' . $i] = array(
      '#type' => 'select',
      '#multiple' => TRUE,
      '#options' => $options,
      '#default_value' => $checked,
      '#size' => '4',
      '#attributes' => array('class' => 'solr-block-form'),
      '#ahah' => array(
        'event' => 'change',
        'path' => ahah_helper_path(array('block')),
        'wrapper' => 'block-wrapper',
      ),
    );
    if ($i == 0) {
      $form['block']['taxonomy-' . $i]['#title'] = t('Narrow by');
      $form['block']['taxonomy-' . $i]['#size'] = count($options);
    }
  }

  // Lists: locations.
  if (!isset($data2['region']) || !$data2['region']) {
    for ($i = 0; $i < count($tfl['list']); $i++) {
      $options = $tfl['list'][$i];
      $checked = $tfl['checked'][$i];

      if (!empty($options)) {
        $form['block']['location-' . $i] = array(
          '#type' => 'select',
          '#multiple' => TRUE,
          '#options' => $options,
          '#default_value' => $checked,
          '#size' => '4',
          '#attributes' => array('class' => 'solr-block-form'),
          '#ahah' => array(
            'event' => 'change',
            'path' => ahah_helper_path(array('block')),
            'wrapper' => 'block-wrapper',
          ),
        );
      }

      if ($i == 0) {
        $form['block']['location-' . $i]['#title'] = t('Location');
      }
    }
  }

  // User region.
  if (user_is_logged_in()) {
    if (isset($user->profile_country)) {
      $form['region'] = array(
        '#type' => 'checkbox',
        '#title' => t('My region'),
        '#id' => 'my_region',
        '#default_value' => $search_state2['region'] && ('false' != $search_state2['region']),
        '#ahah' => array(
          'event' => 'change',
          'path' => ahah_helper_path(array('block')),
          'wrapper' => 'block-wrapper',
        ),
      );
    } else {
      $form['region'] = array(
        '#type' => 'item',
        '#value' => l(t('Add location to your profile'), 'user/profile/edit/', array('fragment' => 'profile-country-wrapper')),
      );
    }
  }

//  $form['my_language'] = array(
//    '#type' => 'checkbox',
//    '#default_value' => TRUE,
//    '#title' => t('Show issues of my language'),
//  );
  $form['voted_status'] = array(
    '#type' => 'checkbox',
    '#default_value' => $search_state2['voted_status'],
    '#title' => t('Show only not voted'),
  );
  $form['search_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Keyword'),
    '#value' => $search_state2['search_text'],
  );
  $form['search'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#id' => 'search-solr-block',
  );


  $form['filter_time'] = array(
    '#type' => 'hidden',
    '#value' => $search_state2['filter_time'],
  );
  $form['filter_type'] = array(
    '#type' => 'hidden',
    '#value' => $search_state2['filter_type'],
  );
  $form['block']['filter_page'] = array(
    '#type' => 'hidden',
    '#value' => $search_state2['filter_page'],
  );

  unset($form_state['storage']['block']);

  return $form;
}