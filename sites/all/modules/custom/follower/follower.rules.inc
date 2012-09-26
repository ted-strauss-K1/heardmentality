<?php

/**
 * Implementation of hook_rules_event_info()
 */
function follower_rules_event_info() {
  return array(
    'follower_user_followed' => array(
      'label' => t('User Followed Another One'),
      'arguments' => array(
        'follower'    => array('type' => 'user', 'label' => t('Follower')),
        'followed'    => array('type' => 'user', 'label' => t('Followed User')),
      ),
      'module' => 'Follower',
    ),
    'follower_user_unfollowed' => array(
      'label' => t('User Unfollowed Another One'),
      'arguments' => array(
        'follower'    => array('type' => 'user', 'label' => t('Follower')),
        'followed'    => array('type' => 'user', 'label' => t('Followed User')),
      ),
      'module' => 'Follower',
    ),
  );
}