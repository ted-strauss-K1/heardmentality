<?php

/**
 * @file
 * Views integration with the Profile Privacy module.
 */

/**
 * @todo
 *  - Better theme integration.
 *    - Class for private fields even when they're rendered. So that
 *      they can stand out to admins, for example.
 */

/**
 * Implementation of hook_views_data_alter()
 */
function profile_privacy_views_data_alter(&$data) {
  $keys = array_keys($data);
  foreach ($data as $key => $value) {
    if (0 === strpos($key, 'profile_values_')) {
      $new_handler = 'profile_privacy_' . $data[$key]['value']['field']['handler'];
      $data[$key]['value']['field']['handler'] = $new_handler;
      $data[$key]['value']['field']['profile_privacy_field_name'] = substr($key, 15);
    }
  }
}

/**
 * Implementation of hook_views_handlers()
 */
function profile_privacy_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'profile_privacy') .'/views/handlers',
    ),
    'handlers' => array(
      'profile_privacy_views_handler_field' => array(
        'parent' => 'views_handler_field',
      ),
      'profile_privacy_views_handler_field_user' => array(
        'parent' => 'views_handler_field_user',
      ),
      'profile_privacy_views_handler_field_boolean' => array(
        'parent' => 'views_handler_field_boolean',
      ),
      'profile_privacy_views_handler_field_profile_date' => array(
        'parent' => 'views_handler_field_profile_date',
      ),
      'profile_privacy_views_handler_field_markup' => array(
        'parent' => 'views_handler_field_markup',
      ),
      'profile_privacy_views_handler_field_url' => array(
        'parent' => 'views_handler_field_url',
      ),
      'profile_privacy_views_handler_field_profile_list' => array(
        'parent' => 'views_handler_field_profile_list',
      ),
    ),
  );
}


/**
 * Helper function to add field options.
 *
 * @return
 *   Options array.
 *
 * @see views_handler_field
 */
function _profile_privacy_views_options_definition() {
  $options['profile_privacy_replacement_text'] = array('default' => '', 'translatable' => TRUE);
  $options['profile_privacy_show_hidden'] = array('default' => FALSE);
  return $options;
}

/**
 * Helper function to add field options form elements.
 *
 * @param $form
 *   Forms API form definition.
 *
 * @param $form_state
 *   Forms API form state definition.
 *
 * @param $handler
 *   Views field handler object.  Handler whose options_form() method
 *   called this function.
 *
 * @see profile_privacy_views_handler_field_user
 */
function _profile_privacy_views_options_form(&$form, &$form_state, $handler) {
  $form['profile_privacy_replacement_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Privacy replacement text'),
    '#default_value' => $handler->options['profile_privacy_replacement_text'],
    '#description' => t('If the field is hidden from the viewer, display this text instead.'),
  );
  if (user_access('administer users')) {
    $form['profile_privacy_show_hidden'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show field even if configured as "Hidden profile field"'),
      '#default_value' => $handler->options['profile_privacy_show_hidden'],
      '#description' => t('Use with caution.  If checked, the field will display for non-admin users even if it is set as "Hidden profile field" in the Profile module configuration.  Users cannot override this setting or alter the information displayed.'),
    );
  }
}

/**
 * Helper function to determine user's access to view a profile field
 * within a view.
 *
 * @param $uid
 *   User ID to which the field being tested belongs.
 * @param $field_alias
 *   Profile module internal name for the field being tested.
 * @param $handler
 *   Views field handler object.  Handler whose render() method
 *   called this function.
 *
 * @return boolean
 *   TRUE if user has access to the field, FALSE otherwise.
 *
 * @todo Move static caching to an API function in the core module.
 */
function _profile_privacy_views_field_access($uid, $field_alias, $handler) {
  static $cache = array();
  global $user;

  // Checks the static cache to see if we already checked this field.
  // @todo Figure out why the $uid can be NULL.
  if (NULL !== $uid) {
    if (isset($cache[$user->uid][$uid][$field_alias])) {
      return $cache[$user->uid][$uid][$field_alias];
    }
    else {
      $cache[$user->uid][$uid][$field_alias] = TRUE;
      $access = &$cache[$user->uid][$uid][$field_alias];
    }
  }
  else {
    return TRUE;
  }

  if (NULL === $uid || user_access('administer users') || $uid == $user->uid) {
    return $access;
  }

  // Loads user account, returns FALSE on errors.
  if (!$account = user_load($uid)) {
    $access = FALSE;
    return $access;
  }

  // Makes sure the field is valid.
  $profile_fields = profile_privacy_get_fields();
  if (isset($profile_fields[$field_alias])) {
    $field = $profile_fields[$field_alias];
  }
  else {
    $access = FALSE;
    return $access;
  }

  // The user's overridden settings always take precedence.
  if (isset($account->{'private_' . $field->name}) && $field->privacy) {
    $access = profile_privacy_get_field_access($account, $field);
  }
  elseif (PROFILE_PRIVATE == $field->visibility) {
    // Field was set as PROFILE_HIDDEN in Profile module config, so check
    // whether it's overridden in the view.
    if ($handler->options['profile_privacy_show_hidden']) {
      $access = TRUE;
    }
    else {
      $access = FALSE;
    }
  }
  else {
    // There are no profile privacy settings for this field
    // and the field is public
    $access = TRUE;
  }

  return $access;
}
