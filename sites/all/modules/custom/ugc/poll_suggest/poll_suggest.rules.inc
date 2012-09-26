<?php

/**
 * Implementation of hook_rules_event_info()
 */
function poll_suggest_rules_event_info() {
  return array(
    'poll_suggest_add' => array(
      'label' => t('User Suggested an Answer'),
      'arguments' => array(
        'user'    => array('type' => 'user', 'label' => t('Acting User')),
        'node'    => array('type' => 'node', 'label' => t('Node')),
      ),
      'module' => 'Poll Suggestions',
    ),
  );
}