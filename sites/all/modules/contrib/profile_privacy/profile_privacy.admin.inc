<?php

/**
 * @file
 * Admin settings for Profile Privacy.
 */

/**
 * Administrative settings for Profile Privacy.
 *
 * @param &$form_state
 *   A keyed array containing the current state of the form.
 *
 * @return
 *   A FAPI array passed through system_settings_form().
 */
function profile_privacy_admin_settings_form(&$form_state) {
  $form = array('weight' => array());

  // Adds description of what this form does.
  $form['description'] = array(
    '#value' => t('<p>This page provides a drag-and-drop interface for the site administrator to sort the access settings as they will be displayed to the user in the dropbox.</p>'),
    '#weight' => -1,
  );

  // Gets privacy settings, which are the dropbox options.
  $settings = profile_privacy_get_access_info();
  $form['settings_data'] = array('#type' => 'value', '#value' => $settings);

  // Adds the dropbox to the fields.
  foreach ($settings as $name => $info) {
    $variable = sprintf('profile_privacy:%s:weight', $name);
    $form['weight'][$variable] = array(
      '#type' => 'weight',
      '#title' => '',
      '#delta' => 50,
      '#default_value' => variable_get($variable, 0),
      '#attributes' => array('class' => 'profile-privacy-weight'),
    );
  }

  // Finalizes the form and returns.
  $form = system_settings_form($form);
  $form['#theme'] = 'profile_privacy_admin_settings_form';
  return $form;
}

/**
 * Themes the facet form into a draggable table.
 *
 * @param $form
 *   A FAPI array containing a fieldset.
 *
 * @return
 *   A themed form element.
 */
function theme_profile_privacy_admin_settings_form($form) {
  $output = '';

  // Initializes table headers.
  $headers = array(t('Access setting'), t('Description'), t('Weight'));

  // Adds the facets weights and sorts.
  $settings = $form['settings_data']['#value'];
  $weighted = array();
  foreach ($settings as $name => $info) {
    $variable = sprintf('profile_privacy:%s:weight', $name);
    $form['weight'][$variable]['#weight'] = variable_get($variable, 0);
    $weighted[$name]['#weight'] = $form['weight'][$variable]['#weight'];
  }
  uasort($weighted, 'element_sort');

  // If there are facets defined for this module, adds them.
  $rows = array();
  foreach (array_keys($weighted) as $name) {
    $variable = sprintf('profile_privacy:%s:weight', $name);

    // Makes the realm's facet table draggable.
    $table_id = 'profile-privacy-table';
    drupal_add_tabledrag($table_id, 'order', 'sibling', 'profile-privacy-weight');

    $rows[] = array(
      'class' => 'draggable',
      'data' => array(
        array(
          'data' => check_plain($settings[$name]['label']),
        ),
        array(
          'data' => filter_xss_admin($settings[$name]['description']),
        ),
        array(
          'data' => drupal_render($form['weight'][$variable]),
          'class' => 'dropbox'
        ),
      ),
    );
  }

  // Formats the table for the facets, the table will have dragable rows.
  $form['weight']['table']['#value'] = theme(
    'table', $headers, $rows, array('id' => $table_id)
  );

  $output .= drupal_render($form);
  return $output;
}
