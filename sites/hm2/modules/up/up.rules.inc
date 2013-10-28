<?php

/**
 * Implementation of hook_rules_event_info()
 */
function up_rules_event_info()
{
  return array(
    'up_user_shared' => array(
      'label' => t('User Shared Content'),
      'arguments' => array(
        'user' => array('type' => 'user', 'label' => t('Acting User')),
        'node' => array('type' => 'node', 'label' => t('Shared Content')),
      ),
      'module' => 'UserPoints Extension',
    ),
  );
}


/**
 * Implementation of hook_rules_condition_info()
 */
function up_rules_condition_info()
{
  return array(
    'up_userpoints_limit' => array(
      'label' => t('User Hit the Userpoints Limit Today'),
      'arguments' => array(
        'user' => array('type' => 'user', 'label' => t('Acting user')),
      ),
      'module' => 'UserPoints Extension',
    ),
  );
  // todo not used
//  return array(
//    'up_user_logged_in_today' => array(
//      'label' => t('User Logged In Today'),
//      'arguments' => array(
//        'user' => array('type' => 'user', 'label' => t('Acting user')),
//      ),
//      'module' => 'UserPoints Extension',
//    ),
//    'up_user_visited_node_today' => array(
//      'label' => t('User Visited Node Today'),
//      'arguments' => array(
//        'user' => array('type' => 'user', 'label' => t('Acting user')),
//        'node' => array('type' => 'node', 'label' => t('Content')),
//      ),
//      'module' => 'UserPoints Extension',
//    ),
//    'up_user_shared_posts_today' => array(
//      'label' => t('User Shared Posts Today'),
//      'arguments' => array(
//        'user' => array('type' => 'user', 'label' => t('Acting user')),
//      ),
//      'module' => 'UserPoints Extension',
//    ),
//  );

}

/**
 * @param $user
 * @param array $settings
 * @return bool
 */
function up_userpoints_limit($user, $settings = array())
{
  return ($settings['number'] != 0) && (up_userpoints_today($user->uid) >= $settings['number']);
}

/**
 * @param $settings
 * @param $form
 */
function up_userpoints_limit_form($settings, &$form)
{
  $form['settings']['number'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of Points'),
    '#default_value' => isset($settings['number']) ? $settings['number'] : 0,
    '#required' => TRUE,
  );
}

/**
 * Condition: up_user_shared_posts_today
 */
function up_userpoints_limit_form_validate(&$form, &$form_state)
{
  $post = $form_state["clicked_button"]["#post"];
  if (!is_numeric($post['number'])) {
    form_set_error('up_userpoints_limit', t('Number of Points should be numeric'));
  }
}


/**
 * Condition: up_user_logged_in_today
 */
function up_user_logged_in_today($user)
{
  return up_check_operation_today('login', $user->uid);
}

/**
 * Condition: up_user_visited_node_today
 */
function up_user_visited_node_today($user, $node)
{
  if (arg(0) == 'node' && arg(1) == $node->nid) {
    return false != db_result(db_query("SELECT COUNT(*) FROM {userpoints_txn} WHERE uid = '%d' AND entity_type = '%s' AND operation = '%s' AND entity_id = '%d'", $user->uid, 'node', 'visit', $node->nid));
  } else {
    return true;
  }
}

/**
 * Condition: up_user_shared_posts_today
 */
function up_user_shared_posts_today($user, $settings = array())
{
  return $settings['number'] == 0 || (up_userpoints_today($user->uid, 'share') < $settings['number']);
}

/**
 * Condition: up_user_shared_posts_today
 */
function up_user_shared_posts_today_form($settings = array(), &$form)
{
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
function up_user_shared_posts_today_form_validate(&$form, &$form_state)
{
  $post = $form_state["clicked_button"]["#post"];
  if (!is_numeric($post['number'])) {
    form_set_error('up_user_shared_posts_today_form_numeric', t('Number of shares should be numeric'));
  }
}

