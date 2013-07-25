<?php

/**
 * @param $uid
 * @param $badges
 */
function badges_queue($uid = FALSE, $badges = FALSE) {
  if (isset($_REQUEST['uid'])) {
    $uid = $_REQUEST['uid'];
  }
  if (!$uid) {
    return;
  }
  if (!is_array($badges)) {
    $badges = array($badges);
  }
  foreach ($badges as $badge) {
    // todo check duplicate queueing
    db_query("INSERT INTO {badges_queue} SET uid = '%s', badge = '%s', date_added = '%s'", $uid, $badge, date("y-m-d H:i:s"));
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
    // todo response
    return;
  }
  $item = db_fetch_object(db_query("SELECT * FROM {badges_queue} WHERE locked <> 1 ORDER BY (CASE uid WHEN 3 THEN 1 ELSE 0 END) DESC, date_added ASC"));
  if ($item) {
    db_query("UPDATE {badges_queue} SET locked = 1 WHERE id = '%d'", $item->id);
    badges_grant($uid, $item->badge);
    db_query("DELETE FROM {badges_queue} WHERE id = '%d'", $item->id);
  }
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