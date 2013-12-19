<?php

/*
 * Implementation of hook_rules_event_info()
 */
function core_rules_event_info() {
  return array(
    'issue_view' => array(
      'label'     => t('User Viewed Issue'),
      'module'    => 'Core',
      'arguments' => array(
        'acting_user' => array(
          'type'  => 'user',
          'label' => t('User')
        ),
      ),
    ),
  );
}
