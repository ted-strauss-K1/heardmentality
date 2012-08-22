<?php
/*
 * This file is to contain only rules' hooks.
 */

/*
 * Implementation of hook_rules_event_info()
 */
function up_rules_event_info() {
  return array(
    'up_user_followed' => array(
      'label' => t('User Followed Another One'),
      'arguments' => array(
        'follower'    => array('type' => 'user', 'label' => t('Follower')),
        'followed'    => array('type' => 'user', 'label' => t('Followed User')),
      ),
      'module' => 'UserPoints Extension',
    ),
    'up_user_unfollowed' => array(
      'label' => t('User Unfollowed Another One'),
      'arguments' => array(
        'follower'    => array('type' => 'user', 'label' => t('Follower')),
        'followed'    => array('type' => 'user', 'label' => t('Followed User')),
      ),
      'module' => 'UserPoints Extension',
    ),
    'up_user_shared' => array(
      'label' => t('User Shared Content'),
      'arguments' => array(
        'user'    => array('type' => 'user', 'label' => t('Acting User')),
        'node'    => array('type' => 'node', 'label' => t('Shared Content')),
      ),
      'module' => 'UserPoints Extension',
    ),
  );
}




/*
 * Implementation of hook_rules_condition_info()
 */
function up_rules_condition_info() {
  return array(
    'up_user_logged_in_today' => array(
      'label' => t('User Logged In Today'),
      'arguments' => array(
        'user'    => array('type' => 'user', 'label' => t('Acting user')),
      ),
      'module' => 'UserPoints Extension',
    ),
    'up_user_visited_node_today' => array(
      'label' => t('User Visited Node Today'),
      'arguments' => array(
        'user'    => array('type' => 'user', 'label' => t('Acting user')),
        'node'    => array('type' => 'node', 'label' => t('Content')),
      ),
      'module' => 'UserPoints Extension',
    ),
    'up_user_shared_posts_today' => array(
      'label' => t('User Shared Posts Today'),
      'arguments' => array(
        'user'    => array('type' => 'user', 'label' => t('Acting user')),
      ),
      'module' => 'UserPoints Extension',
    ),
  );

  /*
  array(
    'up_user_reputation' => array(
      'label' => t('Reputation Limit'),
      'arguments' => array(
        'user'    => array('type' => 'user', 'label' => t('Acting user')),
        'action'  => array('type' => 'string', 'label' => t('The type of the purchased package is')),
      ),
      'module' => 'up',
    ),
  );
  */
}


/*
 * Condition: up_user_logged_in_today
 */
function up_user_logged_in_today($user) {
  return up_check_operation_today('login', $user->uid);
}

/*
 * Condition: up_user_visited_node_today
 */
function up_user_visited_node_today($user, $node) {
  if (arg(0) == 'node' && arg(1) == $node->nid) {
    return false != db_result(db_query("SELECT COUNT(*) FROM {userpoints_txn} WHERE uid = '%d' AND entity_type = '%s' AND operation = '%s' AND entity_id = '%d'", $user->uid, 'node', 'visit', $node->nid));
  } else {
    return true;
  }
}

/*
 * Condition: up_user_shared_posts_today
 */
function up_user_shared_posts_today($user, $settings = array()) {
  return $settings['number'] == 0 || (up_userpoints_today($user->uid, 'share') < $settings['number']);
}

/**
 * Condition: up_user_shared_posts_today
 */
function up_user_shared_posts_today_form($settings = array(), &$form) {
  $form['settings']['number'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of points for shares per day'),
    '#default_value' => isset($settings['number']) ? $settings['number'] : 0,
    '#required' => TRUE,
  );
}

/**
 * Condition: up_user_shared_posts_today
 */
function up_user_shared_posts_today_form_validate(&$form, &$form_state) {
  $post = $form_state["clicked_button"]["#post"];
  if (!is_numeric($post['number'])) {
    form_set_error('up_user_shared_posts_today_form_numeric', t('Number of shares should be numeric'));
  }
}

