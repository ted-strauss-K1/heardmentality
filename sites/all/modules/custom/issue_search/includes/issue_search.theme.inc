<?php

/**
 * Search results output.
 *
 * @param array $results
 *  Search results.
 *
 * @return string
 *  Output.
 */
function theme_issue_search_results($results = array()) {
  $output = '';
  foreach ($results as $result) {
    $node = node_load($result['node']->entity_id);
    $output .= node_view($node, TRUE);
  }

  return $output;
}

/**
 * @param      $page
 * @param      $page_active
 * @param bool $anchor
 *
 * @return string
 */
function theme_issue_search_pager_link($page, $page_active, $anchor = FALSE) {
  return sprintf('<a href="#issue-search-form" name="%s" class="search-pager-link %s">%s</a>', $page, $page == $page_active ? 'mod-active' : '', FALSE == $anchor ? $page : $anchor);
}

/**
 * Search filter for Issues.
 *
 * @return string
 *  Output.
 */
function theme_issue_search_filter() {
  $issues_count = '<i class="icon cat text icon-binoculars-searchalt"></i><label class="tags-on search_issues" for="count_results-wrapper">' . t('Search Issues') . '</label><div id="count_results-wrapper" class="form-item"><span>0</span> ' . t('issues') . '</div>';
  return '<div class="filter_search grey-box poll-box issues_search">' . $issues_count . drupal_get_form('issue_search_filter_form') . '</div>';
}

/**
 * A form with Issues search filters.
 *
 * @global type $user
 *  Current Drupal user.
 *
 * @param type  $form_state
 *  Form state.
 *
 * @return string
 *  A set of form elements and their definitions.
 */
function issue_search_filter_form($form_state) {
  global $user;
  $form = array();

  // cookie settings
  $settings = isset($_COOKIE['search_arguments']) ? (array) json_decode($_COOKIE['search_arguments']) : array();

  // Gather info: taxonomy.
  $tft_codes = array();
  for ($i = 0; $i >= 0; $i++) {
    if (empty($data['taxonomy-' . $i])) {
      break;
    }
    foreach ($data['taxonomy-' . $i] as $tid => $tname) {
      $tft_codes[] = (int) $tid;
    }
  }
  // Get codes.
  if ($settings['taxonomy']) {
    $tft_codes = explode(";", $settings['taxonomy']);
  }
  if (isset($_GET['tids']) && empty($data['taxonomy-0'])) {
    $tft_codes = explode(",", $_GET['tids']);
  }

  $tft = tft_list('issue', $tft_codes, TRUE);

  // Gather info: location.
  $tfl_codes0 = array();
  $tfl_codes1 = array();
  $tfl_codes2 = array();
  for ($i = 0; $i <= 2; $i++) {
    $name = 'tfl_codes' . $i;
    $$name = empty($data['location-' . $i]) ? array() : array_keys($data['location-' . $i]);
  }

  // If logged in & country set.
  if ('false' != $settings['my_region']) {
    $tfl_codes0 = array($user->profile_country);
    $tfl_codes1 = array();
    $tfl_codes2 = array();
  }
  elseif ($settings['location1']) {
    $tfl_codes0 = explode(';', $settings['location1']);
    $tfl_codes1 = explode(';', $settings['location2']);
    $tfl_codes2 = explode(';', $settings['location3']);
  }

  // my_region
  drupal_add_js(array('tfl_user' => $user->profile_country), 'setting');

  $tfl = tfl_list($tfl_codes0, $tfl_codes1, $tfl_codes2, TRUE);

  // Lists: taxonomy.
  for ($i = 0; $i < 3 /*count($tft['list'])*/; $i++) {
    $options = $tft['list'][$i];
    $checked = $tft['checked'][$i];

    if (empty($options)) {
      $options = array();
    }

    $form['taxonomy-' . $i] = array(
      '#type'          => 'select',
      '#multiple'      => TRUE,
      '#options'       => $options,
      '#default_value' => $checked,
      '#size'          => '4',
      '#attributes'    => array('class' => 'solr-block-form tft chzn-select'),
    );

    if ($i == 0) {
      $form['taxonomy-' . $i]['#title'] = t('Narrow by');
      $form['taxonomy-' . $i]['#size'] = count($options);
    }
    else {
      $form['taxonomy-' . $i]['#attributes']['class'] .= ' hideable';
    }
  }

  // Lists: locations.
  if (!isset($data2['region']) || !$data2['region']) {
    for ($i = 0; $i < 3 /*count($tfl['list'])*/; $i++) {
      $options = $tfl['list'][$i];
      $checked = $tfl['checked'][$i];

      if (empty($options)) {
        $options = array();
      }

      $form['location-' . $i] = array(
        '#type'          => 'select',
        '#multiple'      => TRUE,
        '#options'       => $options,
        '#default_value' => $checked,
        '#size'          => '4',
        '#attributes'    => array(
          'class' => 'solr-block-form tfl chzn-select',
          'width' => '190px',
        ),
      );

      if ($i == 0) {
        $form['location-' . $i]['#title'] = t('Location');
      }
      else {
        $form['location-' . $i]['#attributes']['class'] .= ' hideable';
      }
    }
  }

  // User region.
  if (user_is_logged_in()) {
    if (isset($user->profile_country)) {
      $form['region'] = array(
        '#type'          => 'checkbox',
        '#title'         => t('My region'),
        '#id'            => 'my_region',
        '#default_value' => $settings['my_region'] && 'false' != $settings['my_region'],
      );
    }
    else {
      $form['region'] = array(
        '#type'  => 'item',
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
    '#type'          => 'checkbox',
    '#default_value' => $settings['not_voted'] && 'false' != $settings['not_voted'],
    '#title'         => t('Show only not voted'),
  );
  $form['search_text'] = array(
    '#type'  => 'textfield',
    '#title' => t('Keyword'),
    '#value' => $settings['keywords'],
  );
  $form['search'] = array(
    '#type'  => 'submit',
    '#value' => t('Search'),
    '#id'    => 'search-solr-block',
  );

  // Main container.
  $form['page'] = array(
    '#type'  => 'hidden',
    '#value' => isset($settings['page']) ? intval($settings['page']) : 1,
  );

  return $form;
}
