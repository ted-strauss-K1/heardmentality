<?php

// This file is only for the rules

/**
 * Implementation of hook_rules_action_info()
 *
 * @return array
 */
function log_rules_action_info()
{
  return array(
    'log_add_rules_action' => array(
      'label' => t('Add record to log'),
      'arguments' => array(
        'acting_user' => array(
          'type' => 'user',
          'label' => t('Acting user')
        ),
        'type' => array(
          'type' => 'string',
          'label' => t('Log event type'),
        ),
      ),
      'module' => 'Log',
    ),
  );
}

/**
 * @param $user
 * @param $type
 */
function log_add_rules_action($user, $type)
{
  log_add($user->uid, $type);
}