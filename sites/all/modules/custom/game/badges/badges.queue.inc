<?php

/**
 * @param $uid
 * @param $badges
 */
function badges_queue($uid = FALSE, $badges = FALSE) {
  # get uid
  if (isset($_REQUEST['uid'])) {
    $uid = $_REQUEST['uid'];
  }
  # with no uid - skip
  if (!$uid) {
    return;
  }
  # get badges
  if (isset($_REQUEST['badges'])) {
    $badges = $_REQUEST['badges'];
  }
  # array of badges
  if (!is_array($badges)) {
    $badges = array($badges);
  }
  # userbadges
  $userbadges = badges_userbadges($uid);
  $userbadges = $userbadges['#list'];
  # userqueue
  $userqueue = @explode(",", db_result(db_query("
    SELECT GROUP_CONCAT(badge) badges
    FROM badges_queue
    WHERE uid = '%d'", $uid)));
  # through the list of badges
  foreach ($badges as $badge) {
    if (isset($userbadges[$badge])) {
      if ((true !== $userbadges[$badge]['count']) && ($userbadges[$badge]['#count'] >= $userbadges[$badge]['count'])) {
        continue;
      }
    }
    if (in_array($badge, $userqueue)) {
      continue;
    }
    db_query("
      INSERT INTO {badges_queue}
      SET uid = '%s', badge = '%s', date_added = '%s'",
        $uid, $badge, date("y-m-d H:i:s"));
  }
}

/**
 * @param $uid
 */
function badges_dequeue($uid = FALSE) {
  # default uid
  if (isset($_REQUEST['uid'])) {
    $uid = $_REQUEST['uid'];
  }
  if (!$uid) {
    global $user;
    $uid = $user->uid;
  }
  if (!$uid) {
    exit(json_encode(array(
      'status' => false,
      'message' => t('No uid provided or user is anonymous'),
    )));
  }
  $item = db_fetch_object(db_query("SELECT * FROM {badges_queue} WHERE locked <> 1 ORDER BY (CASE uid WHEN 3 THEN 1 ELSE 0 END) DESC, date_added ASC"));
  if ($item) {
    db_query("UPDATE {badges_queue} SET locked = 1 WHERE id = '%d'", $item->id);
    $output = badges_grant($item->uid, $item->badge);
    db_query("DELETE FROM {badges_queue} WHERE id = '%d'", $item->id);
    if (!empty($output)) {
      $badge = badges_list($item->badge);
      exit(json_encode(array(
        'status' => $uid == $item->uid,
        'message' => t('You have got the badge') . ' "'.$badge['name'].'"',
        'data' => array(
          'uid' => $item->uid,
          'badge' => $item->badge,
        ),
      )));
    } else {
      exit(json_encode(array(
        'status' => false,
        'message' => t('Badge is not granted'),
        'data' => array(
          'uid' => $item->uid,
          'badge' => $item->badge,
        ),
      )));
    }
  }
  exit(json_encode(array(
    'status' => false,
    'message' => t('Queue is empty'),
  )));
}

/**
 * Implementation of hook_menu()
 *
 * @return array
 */
function badges_queue_menu()
{
  $menu = array();

  $menu['badges/queue'] = array(
    'page callback' => 'badges_queue',
    'page arguments' => array(),
    'access callback' => TRUE,
  );
  $menu['badges/dequeue'] = array(
    'page callback' => 'badges_dequeue',
    'page arguments' => array(),
    'access callback' => TRUE,
  );

  return $menu;
}