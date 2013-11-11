<?php

define('BADGES_ACTION_PREFIX', 'badge:');

/**
 * Implements custom hook_invoke_action()
 *
 * @param $timestamp
 * @param $params
 */
function badges_invoke_action($timestamp, $params) {
  $output = array('status' => FALSE);
  if (isset($params['operation'])) {
    $params['time_stamp'] = $timestamp;

    if ('badge' == $params['entity_type']) {
      $uid = $params['uid'];
      $badge = str_replace(BADGES_ACTION_PREFIX, '', $params['operation']);
      $output = badges_dequeue_badge($uid, $badge);
    }
    else {
      badges_queue_action($params);
      $output = array('status' => TRUE);
    }
  }
  return $output + array('params' => $params);
}

/**
 * Attempts
 *
 * @param $params
 */
function badges_queue_action($params) {
  foreach (module_implements('queue_action') as $module) {
    if ('badges' == $module) {
      continue;
    }
    $function = $module . '_queue_action';
    if (function_exists($function)) {
      $function($params);
    }
  }
}

/**
 * @param null $params
 */
function badges_queue_badge($params = NULL) {
  $uid = $params['uid'];
  $badge = str_replace(BADGES_ACTION_PREFIX, '', $params['operation']);

  // user badges
  $userbadges = badges_userbadges($uid);
  $userbadges = $userbadges['#list'];

  // check if badge can be assigned to user
  if (isset($userbadges[$badge])) {
    if ((TRUE !== $userbadges[$badge]['count']) && ($userbadges[$badge]['#count'] >= $userbadges[$badge]['count'])) {
      db_query("DELETE FROM {action_queue} WHERE uid = '%s' AND op = '%s'", $uid, $params['operation']);
      return FALSE;
    }
  }

  // check if badge is already queued
  $queued = (int) db_result(db_query("SELECT COUNT(*) FROM {action_queue} WHERE uid = '%s' AND op = '%s'", $uid, $params['operation']));
  $badges = isset($userbadges[$badge]) ? $userbadges[$badge]['#count'] : 0;
  $limit = isset($userbadges[$badge]) ? $userbadges[$badge]['count'] : (($badge_data = badges_list($badge)) ? $badge_data['count'] : 0);
  if ((TRUE !== $limit) && ($limit <= $badges + $queued)) {
    return FALSE;
  }

  // queue
  action_queue($params);
}

/**
 * @param $uid
 * @param $badge
 */
function badges_dequeue_badge($uid, $badge) {
  $output = badges_grant($uid, $badge);

  if (!empty($output)) {
    $badge = badges_list($badge);

    // to give pennies
    action_queue(array(
      'uid'         => $uid,
      'operation'   => 'badge',
      'entity_id'   => $uid,
      'entity_type' => 'user',
      'badge'       => $badge,
    ));

    return array(
      'status'     => TRUE,
      'message'    => t('You have got the badge') . ' "' . $badge['name'] . '"',
      'message_to' => $uid,
    );
  }
  else {
    return array('status' => FALSE);
  }
}
