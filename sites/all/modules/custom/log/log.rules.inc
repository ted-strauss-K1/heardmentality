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
      ),
      'module' => 'Log',
    ),
  );
}

/**
 * @param $user
 * @param $type
 */
function log_add_rules_action($user, $settings = array())
{
  log_add($user->uid, $settings['type']);
}

/**
 * Settings form
 */
function log_add_rules_action_form($settings = array(), &$form)
{
  $form['settings']['type'] = array(
    '#type' => 'textfield',
    '#title' => t('Log record type'),
    '#default_value' => $settings['type'],
  );
}


/**
 * Implementation of hook_rules_condition_info()
 */
function log_rules_condition_info()
{
  return array(
    'log_rules_condition_multiple_times' => array(
      'label' => t('Log contains multiple records'),
      'arguments' => array(
        'user' => array('type' => 'user', 'label' => t('Acting user')),
      ),
      'module' => 'Log',
    ),
  );
}

/**
 * Condition: ranks_user_new_rank
 */
function log_rules_condition_multiple_times($user, $settings)
{
  $count = db_result(db_query("SELECT IFNULL(COUNT(*),0) FROM {log} WHERE type = '%s' AND uid = '%d'", $settings['type'], $user->uid));

  return ($count != 0) && ($settings['number'] != 0) ? $count%(int)$settings['number'] == 0 : false;
}

/**
 * @param array $settings
 * @return array
 */
function log_rules_condition_multiple_times_form($settings = array(), &$form) {
  $form['settings']['type'] = array(
    '#type' => 'textfield',
    '#title' => t('Log Type'),
    '#default_value' => $settings['type'],
  );
  $form['settings']['number'] = array(
    '#type' => 'select',
    '#title' => t('Records multiple %%'),
    '#options' => array(1=>1,5=>5,10=>10,20=>20,50=>50),
    '#default_value' => $settings['number'],
  );
}