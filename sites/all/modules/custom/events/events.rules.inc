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
    'events_del_rules_action' => array(
      'label' => t('Remove previous records from event stream'),
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
function events_add_rules_action($type, $user, $settings = array())
{
//  var_dump($settings); exit;

  # vars come urlencoded state "content_id=35&content_type=node"
  $pairs = explode("&", $settings['vars']);
  $vars = array();
  foreach ($pairs as $pair) {
    $pair = explode("=", $pair, 2);
    $vars[$pair[0]] = $pair[1];
  }

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

/**
 * @param $type
 * @param $user
 * @param array $vars
 * @param array $settings
 */
function events_del_rules_action($type, $user, $settings = array())
{
//  var_dump($settings); exit;

  # vars come urlencoded state "content_id=35&content_type=node"
  $pairs = explode("&", $settings['vars']);
  $vars = array();
  foreach ($pairs as $pair) {
    $pair = explode("=", $pair, 2);
    $vars[$pair[0]] = $pair[1];
  }

  $p = array(
    'uid' => $user->uid,
    'type' => $type,
  ) + $vars;

  events_del($p);
}

/**
 * Settings form
 */
function events_del_rules_action_form($settings = array(), &$form)
{
  $form['settings']['vars'] = array(
    '#type' => 'textfield',
    '#title' => t('Variables'),
    '#default_value' => isset($settings['vars']) ? $settings['vars'] : '',
  );
}
