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
      badges_dequeue_badge($uid, $badge, $timestamp);
    }
    else {
      badges_queue_action($params);
    }

    $output = events_add($params);
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
  if (isset($userbadges[$badge]) && (TRUE !== $userbadges[$badge]['count'])) {
    if ($queued = (int)db_query("SELECT COUNT(*) FROM {action_queue} WHERE uid = '%s' AND op = '%s'", $uid, $params['operation'])) {
      if ($userbadges[$badge]['count'] - $userbadges[$badge]['#count'] <= $queued) {
        return FALSE;
      }
    }
  }

  // queue
  action_queue($params);
}

/**
 * @param $uid
 * @param $badge
 */
function badges_dequeue_badge($uid, $badge, $timestamp = FALSE) {
  $output = badges_grant($uid, $badge);
  if (!empty($output)) {
    $badge = badges_list($item->badge);
    exit(json_encode(array(
      'status'  => $uid == $item->uid,
      'message' => t('You have got the badge') . ' "' . $badge['name'] . '"',
      'data'    => array(
        'uid'   => $item->uid,
        'badge' => $item->badge,
      ),
    )));
  }


  db_query("DELETE FROM {badges_queue} WHERE id = '%d'", $item->id);
  if (!empty($output)) {
    $badge = badges_list($item->badge);
    exit(json_encode(array(
      'status'  => $uid == $item->uid,
      'message' => t('You have got the badge') . ' "' . $badge['name'] . '"',
      'data'    => array(
        'uid'   => $item->uid,
        'badge' => $item->badge,
      ),
    )));
  }
  else {
    exit(json_encode(array(
      'status'  => FALSE,
      'message' => t('Badge is not granted'),
      'data'    => array(
        'uid'   => $item->uid,
        'badge' => $item->badge,
      ),
    )));
  }


  // todo put the badge to the queue
}
