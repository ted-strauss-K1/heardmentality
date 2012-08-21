<?php
/*
 * This file is to contain only rules' hooks.
 */

/*
 * Implementation of hook_rules_condition_info()
 */
function up_rules_condition_info() {
  return array(
    'up_user_reputation' => array(
      'label' => t('Reputation Limit'),
      'arguments' => array(
        'user'    => array('type' => 'user', 'label' => t('Acting user')),
        'action'  => array('type' => 'string', 'label' => t('The type of the purchased package is')),
      ),
      'module' => 'up',
    ),
  );
}