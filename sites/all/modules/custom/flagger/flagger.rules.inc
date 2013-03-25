<?php

/**
 * @file
 * Rules integration for the Flagger module.
 */

/**
 * Implementation of hook_rules_event_info().
 */
function flagger_rules_event_info()
{
  $items = array();

  $arguments = array(
    // First, define ubiquitous arguments.
    'flag' => array(
      'type' => 'flag',
      'label' => t('flag'),
    ),
    'flag_content_id' => array(
      'type' => 'number',
      'hidden' => TRUE,
    ),
    'flagging_user' => array(
      'type' => 'user',
      'label' => t('flagging user'),
    ),
  );

  $items['flag_flagged'] = array(
    'module' => 'Flag',
    'label' => t('Content has been flagged'),
    'arguments' => $arguments,
  );
  $items['flag_unflagged'] = array(
    'module' => 'Flag',
    'label' => t('Content has been unflagged'),
    'arguments' => $arguments,
  );

  $items['flagger_user_flags'] = array(
    'module' => 'Flagger',
    'label' => t('User Flags Content'),
    'arguments' => array(
      'user' => array(
        'type' => 'user',
        'label' => t('Flagging user'),
      ),
      'content_type' => array(
        'type' => 'string',
        'label' => t('Content type'),
      ),
      'content_id' => array(
        'type' => 'number',
        'label' => t('Content id'),
      ),
    ),
  );

  return $items;
}

/**
 * Implementation of hook_rules_action_info()
 *
 * @return array
 */
function flagger_rules_action_info()
{
  return array(
    'flagger_rules_action' => array(
      'label' => t('Invoke event "User Flags Content"'),
      'arguments' => array(
        'content_type' => array(
          'type' => 'string',
          'label' => t('Content type'),
        ),
        'content_id' => array(
          'type' => 'number',
          'label' => t('Content id'),
        ),
      ),
      'module' => 'Flagger',
    ),
  );
}

/**
 * @param $type
 * @param $user
 * @param array $vars
 * @param array $settings
 */
function flagger_rules_action($content_type, $content_id, $settings = array())
{
  if ($flags = flag_get_content_flags($content_type, $content_id)) {
    foreach (array_keys($flags) as $uid) {
      rules_invoke_event('flagger_user_flags', user_load($uid), $content_type, $content_id);
    }
  }
}