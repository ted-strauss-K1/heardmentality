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
    'poll_voted' => array(
      'label' => t('Poll is Voted'),
      'module' => 'Poll',
      'arguments' => array(
        'acting_user' => array(
          'type' => 'user',
          'label' => t('Poll owner')
        ),
        'node' => array(
          'type' => 'node',
          'label' => t('Node')
        ),
      ),
    ),
    'poll_content' => array(
      'label' => t('Issue got new Argument/Comment'),
      'module' => 'Issue',
      'arguments' => array(
        'acting_user' => array(
          'type' => 'user',
          'label' => t('Acting user')
        ),
        'content_owner' => array(
          'type' => 'user',
          'label' => t('Issue Creator')
        ),
        'node' => array(
          'type' => 'node',
          'label' => t('Node')
        ),
      ),
    ),
  );
}

/**
 * Implementation of hook_rules_action_info()
 *
 * @return array
 */
function issue_rules_action_info()
{
  return array(
    'issue_content_rules_action' => array(
      'label' => t('Invoke "Issue got new Argument/Comment"'),
      'arguments' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Argument')
        ),
      ),
      'module' => 'Issue',
    ),
  );
}

/**
 * @param $type
 * @param $user
 * @param array $vars
 * @param array $settings
 */
function issue_content_rules_action($node, $settings = array())
{
  global $user;
  rules_invoke_event('poll_content', $user, user_load($node->uid), $node);
}