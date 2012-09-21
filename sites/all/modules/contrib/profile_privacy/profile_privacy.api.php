<?php

/**
 * @file
 * Hooks exposed by profile_privacy.
 */

/**
 * Access settings available to Profile Privacy.
 *
 * @return array
 *   An associative array keyed by unique name of the searcher. Each searcher is
 *   an associative array containing:
 *   - label: The name of the setting displayed to the user in the profile form.
 *   - description: A brief description of the setting.
 *   - access callback: A function that returns a boolean flagging whether the
 *     user has access to view the field.
 */
function hook_profile_privacy_access_info() {
  return array(
    'private' => array(
      'label' => t('Private'),
      'description' => t('Private to everyone except to the user whose profile the field belongs to.'),
      'access callback' => 'profile_privacy_access_callback',
    ),
  );
}
