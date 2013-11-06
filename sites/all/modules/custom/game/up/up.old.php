<?php

/**
 * Implementation of hook_nodeapi()
 *
 * @param      $node
 * @param      $op
 * @param null $a3
 * @param null $a4
 */
function up_nodeapi(&$node, $op, $a3 = NULL, $a4 = NULL) {
  switch ($op) {
    case 'delete' :
      up_cleanup($node->nid, 'node');
      break;
  }
}

/**
 * Implementation of hook_comment()
 *
 * @param $a1
 * @param $op
 */
function up_comment(&$a1, $op) {
  switch ($op) {
    case 'delete' :
      up_cleanup($a1->cid, 'comment');
      break;
  }
}

/**
 * Remove all the userpoints for that
 *
 * @param $content_id
 * @param $content_type
 */
function up_cleanup($content_id, $content_type) {
  //
}

/**
 * Get the number of userpoints
 *
 * @param string $uid
 * @param string $operation
 * @param bool   $reset
 *
 * @return bool
 */
function up_userpoints_get($uid = FALSE, $operation = '', $reset = FALSE) {
  static $cache = array();

  if ($uid === FALSE) {
    global $user;
    $uid = $user->uid;
  }

  # if array of uids is passed then return TRUE but cache values
  if (is_array($uid)) {
    $query = "SELECT uid, SUM(points) AS count FROM {userpoints_txn} WHERE uid IN (" . db_placeholders($uid) . ")";
    if (!empty($operation)) {
      $query .= " AND operation = '%s'";
    }
    $uid[] = $operation;
    $result = db_query($query, $uid);
    while ($row = db_fetch_array($result)) {
      $cache[$row['uid']][$operation] = (int) $row['count'];
    }
  }
  else { # otherwise
    if (!isset($cache[$uid][$operation]) || $reset) {
      if (empty($operation)) {
        $cache[$uid][$operation] = (int) userpoints_get_current_points($uid, 'all');
      }
      else {
        $cache[$uid][$operation] = (int) db_result(db_query("SELECT SUM(points) FROM {userpoints_txn} WHERE uid = '%d' AND operation = '%s'", $uid, $operation));
      }
    }
    return $cache[$uid][$operation];
  }

  return TRUE;
}

/**
 * Max userpoints per day
 */
define('UP_REPUTATION_PER_DAY', 200);

/**
 * Get the number of userpoints today (!)
 *
 * @param string $uid
 * @param string $operation
 *
 * @return int
 */
function up_userpoints_today($uid = FALSE, $operation = '') {
  if ($uid === FALSE) {
    global $user;
    $uid = $user->uid;
  }
  $query = "SELECT SUM(points) FROM {userpoints_txn} WHERE uid = '%d' AND time_stamp > CURDATE()";
  if (!empty($operation)) {
    $query .= " AND operation = '%s'";
  }
  return (int) db_result(db_query($query, $uid, $operation));
}

/**
 * Check if operation was made today
 *
 * @param        $operation
 * @param string $uid
 *
 * @return bool
 */
function up_check_operation_today($operation, $uid = FALSE) {
  if ($uid === FALSE) {
    global $user;
    $uid = $user->uid;
  }
  return FALSE != db_result(db_query("SELECT txn_id FROM {userpoints_txn} WHERE uid = '%d' AND time_stamp > CURDATE() AND operation = '%s'", $uid, $operation));
}

/**
 * Implementation of hook_form_alter()
 *
 * @param $form
 * @param $form_state
 * @param $form_id
 */
function up_form_alter(&$form, $form_state, $form_id) {
  # for "UR-API" module
  if ($form_id == 'user_relationships_ui_request') {
    $form['#submit'][] = 'up_userpoints_follow';
  }
  if ($form_id == 'user_relationships_ui_remove') {
    $form['#submit'][] = 'up_userpoints_unfollow';
  }
}

/**
 * Form user_relationships_ui_request additional submitter
 *
 * @param $form
 * @param $form_state
 */
function up_userpoints_follow(&$form, $form_state) {
  if (module_exists('rules') && module_exists('UR-API')) {
    global $user;
    $followed = user_load(arg(1));
    rules_invoke_event('up_user_followed', $user, $followed);
  }
}

/**
 * Form user_relationships_ui_remove additional submitter
 *
 * @param $form
 * @param $form_state
 */
function up_userpoints_unfollow(&$form, $form_state) {
  if (module_exists('rules') && module_exists('UR-API')) {
    global $user;
    $relationship = user_relationships_load(arg(3));
    $followed = user_load($relationship->requestee_id);
    rules_invoke_event('up_user_unfollowed', $user, $followed);
  }
}

// Userpoints for sharing


/**
 * Implementation of hook_rules_condition_info()
 */
function up_rules_condition_info() {
  return array(
    'up_userpoints_limit' => array(
      'label'     => t('User Hit the Userpoints Limit Today'),
      'arguments' => array(
        'user' => array('type' => 'user', 'label' => t('Acting user')),
      ),
      'module'    => 'UserPoints Extension',
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
 * @param       $user
 * @param array $settings
 *
 * @return bool
 */
function up_userpoints_limit($user, $settings = array()) {
  return ($settings['number'] != 0) && (up_userpoints_today($user->uid) >= $settings['number']);
}

/**
 * @param $settings
 * @param $form
 */
function up_userpoints_limit_form($settings, &$form) {
  $form['settings']['number'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Number of Points'),
    '#default_value' => isset($settings['number']) ? $settings['number'] : 0,
    '#required'      => TRUE,
  );
}

/**
 * Condition: up_user_shared_posts_today
 */
function up_userpoints_limit_form_validate(&$form, &$form_state) {
  $post = $form_state["clicked_button"]["#post"];
  if (!is_numeric($post['number'])) {
    form_set_error('up_userpoints_limit', t('Number of Points should be numeric'));
  }
}


/**
 * Condition: up_user_logged_in_today
 */
function up_user_logged_in_today($user) {
  return up_check_operation_today('login', $user->uid);
}

/**
 * Condition: up_user_visited_node_today
 */
function up_user_visited_node_today($user, $node) {
  if (arg(0) == 'node' && arg(1) == $node->nid) {
    return FALSE != db_result(db_query("SELECT COUNT(*) FROM {userpoints_txn} WHERE uid = '%d' AND entity_type = '%s' AND operation = '%s' AND entity_id = '%d'", $user->uid, 'node', 'visit', $node->nid));
  }
  else {
    return TRUE;
  }
}

/**
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
    '#type'          => 'textfield',
    '#title'         => t('Number of points for shares per day'),
    '#default_value' => isset($settings['number']) ? $settings['number'] : 0,
    '#required'      => TRUE,
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

