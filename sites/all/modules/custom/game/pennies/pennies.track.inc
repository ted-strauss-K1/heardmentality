<?php

/**
 * Implementation of hook_preprocess_page()
 *
 * @param $vars
 */
function pennies_preprocess_page(&$vars) {
  drupal_add_js(drupal_get_path('module', 'pennies') . '/pennies.track.js');
}

/**
 * @param      $op
 * @param      $edit
 * @param      $account
 * @param null $category
 */
function pennies_user($op, &$edit, &$account, $category = NULL) {
  if ('insert' == $op) {
    action_queue(array(
      'uid'         => $account->uid,
      'operation'   => 'register',
      'entity_id'   => $account->uid,
      'entity_type' => 'user',
    ));
  }
}

define('PENNIES_CRON', 'pennies_cron');

/**
 * Implements hook_cron()
 */
function pennies_cron() {
  set_time_limit(0);

  if (($time = strtotime('Monday this week')) > variable_get(PENNIES_CRON, 0)) {
    # remove old
    db_query("DELETE FROM {action_queue} WHERE op = 'weekly_pennies'");

    # add new
    variable_set(PENNIES_CRON, $time);
    $result = db_query("SELECT uid FROM {users} WHERE status = 1 AND uid > 0");
    while ($uid = db_result($result)) {
      action_queue(array(
        'uid'         => $uid,
        'operation'   => 'weekly_pennies',
        'entity_id'   => $uid,
        'entity_type' => 'user',
        'logged'      => TRUE,
      ));
    }
  }
}

/**
 * Implementation of hook_nodeapi()
 *
 * @param      $node
 * @param      $op
 * @param null $a3
 * @param null $a4
 */
function pennies_nodeapi(&$node, $op, $a3 = NULL, $a4 = NULL) {

  switch ($op) {
    case 'insert' :
      if (in_array($node->type, array('resource', 'argument'))) {
        action_queue(array(
          'uid'         => $node->uid,
          'operation'   => 'debate',
          'entity_id'   => $node->nid,
          'entity_type' => 'node',
          'type'        => $node->type,
        ));
      }
      break;
  }
}

/**
 * Implementation of hook_comment()
 *
 * @param $a1
 * @param $op
 */
function pennies_comment(&$comment, $op) {
  switch ($op) {
    case 'insert' :
      action_queue(array(
        'uid'         => $comment->uid,
        'operation'   => 'reply',
        'entity_id'   => $comment->cid,
        'entity_type' => 'comment',
      ));
      break;
  }
}
