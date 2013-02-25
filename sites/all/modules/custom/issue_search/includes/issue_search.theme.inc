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
function theme_issue_search_results($results = array()) {
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
function theme_issue_search_filter() {
    return '<div class="filter_search grey-box poll-box issues_search">' . drupal_get_form('issue_search_filter_form') . '</div>';
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
function issue_search_filter_form($form_state) {
    $form = array();

    global $user;

    ahah_helper_register($form, $form_state);

    // Main container.
    $form['block'] = array(
        '#type' => 'fieldset',
        '#prefix' => '<div id="block-wrapper">',
        '#suffix' => '</div>',
        '#tree' => TRUE,
    );

    // Container: count.
    $form['block']['results'] = array(
        '#value' => '<span>0</span>' . ' issues',
        '#type' => 'item',
        '#id' => 'count_results'
    );

    // Data.
    $data = $form_state['storage']['block'];
    $data2 = $form_state['storage'];

    // Gather info.
    $info_items = array();

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
    if (isset($_GET['tids']) && empty($data['taxonomy-0'])) {
        $tft_codes = explode(",", $_GET['tids']);
    }
    $tft = tft_list('poll', $tft_codes);

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
    $info = t('Issues about') . ':<br />';
    foreach ($info_items as $item) {
        $info .= sprintf('<span><input type="hidden" name="#edit-block-%s" value="%s">%s<span class="del-item">x</span></span>', $item['type'], $item['value'], $item['text']);
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
                '#default_value' => FALSE,
                '#ahah' => array(
                    'event' => 'change',
                    'path' => ahah_helper_path(array('block')),
                    'wrapper' => 'block-wrapper',
                ),
            );
        } else {
            $form['region'] = array(
                '#type' => 'item',
                '#value' => l(t('Add location to your profile'), $user->editlink),
            );
        }
    }

    $form['voted_status'] = array(
        '#type' => 'checkbox',
        '#default_value' => TRUE,
        '#title' => t('Show only not voted'),
    );
    $form['search_text'] = array(
        '#type' => 'textfield',
        '#title' => t('Keyword'),
    );
    $form['search'] = array(
        '#type' => 'submit',
        '#value' => t('Search'),
        '#id' => 'search-solr-block',
    );


    $form['filter_time'] = array(
        '#type' => 'hidden',
        '#value' => 0,
    );
    $form['filter_type'] = array(
        '#type' => 'hidden',
        '#value' => 0,
    );
    $form['block']['filter_page'] = array(
        '#type' => 'hidden',
        '#value' => 0,
    );

    unset($form_state['storage']['block']);

    return $form;
}