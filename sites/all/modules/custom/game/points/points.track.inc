<?php



/**
 * @param      $op
 * @param      $edit
 * @param      $account
 * @param null $category
 */
function points_user($op, &$edit, &$account, $category = NULL) {
  if ('login' == $op) {
    action_queue(array(
      'uid'       => $account->uid,
      'operation' => 'login',
    ));
  }
}

/**
 * Implementation of hook_preprocess_page()
 *
 * @param $vars
 */
function points_preprocess_page(&$vars) {
  drupal_add_js(drupal_get_path('module', 'points') . '/points.track.js');
}

/**
 * Implementation of hook_preprocess_node()
 *
 * @param $vars
 */
function points_preprocess_node(&$vars) {
  $node = $vars['node'];
  if (is_node_page() && $node && ('issue' == $node->type)) {
    if (user_is_logged_in()) {
      global $user;
      action_queue(array(
        'uid'         => $user->uid,
        'operation'   => 'view',
        'entity_id'   => $node->nid,
        'entity_type' => 'node',
      ));
    }
  }
}
