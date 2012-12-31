<?php

// This file is only for the rules

/*
 * Implementation of hook_rules_event_info()
 */
function issue_rules_event_info()
{
  return array(
    'poll_vote' => array(
      'label' => t('User Voted on Poll'),
      'module' => 'Poll',
      'arguments' => array(
        'acting_user' => array(
          'type' => 'user',
          'label' => t('Acting user')
        ),
        'node' => array(
          'type' => 'node',
          'label' => t('Node')
        ),
      ),
    ),
  );
}