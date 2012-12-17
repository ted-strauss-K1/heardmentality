<?php

// This file is only for the rules

/**
 * Implementation of hook_rules_action_info()
 *
 * @return array
 */
function events_rules_action_info()
{
  return array(
    'events_add_rules_action' => array(
      'label' => t('Add record to event stream'),
      'arguments' => array(
        'type' => array(
          'type' => 'string',
          'label' => t('Event type'),
        ),
        'acting_user' => array(
          'type' => 'user',
          'label' => t('Acting user')
        ),
      ),
      'module' => 'Events',
      'eval input' => array('vars'),
    ),
  );
}

/**
 * @param $type
 * @param $user
 * @param array $vars
 * @param array $settings
 */
function events_add_rules_action($type, $user, $vars = array(), $settings = array())
{
  events_add($type, $vars, $user->uid);
}

/**
 * Settings form
 */
function events_add_rules_action_form($settings = array(), &$form)
{
  $form['settings']['vars'] = array(
    '#type' => 'textfield',
    '#title' => t('Variables'),
    '#default_value' => isset($settings['vars']) ? $settings['vars'] : '',
  );
}