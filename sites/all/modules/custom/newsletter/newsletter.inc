<?php

/**
 * @param $uid
 * @param $date
 *
 * @return bool|string
 */
function newsletter_hash($uid, $date) {
  $max = 9; // unlikely integer
  $i = 0;
  while ($i <= $max) {
    $hash = md5($uid . ':' . $date . ':' . $i);
    if (FALSE !== newsletter_load($hash)) {
      return $hash;
    }
  }
  return FALSE;
}

/**
 * @param $hash
 *
 * @return array|bool
 */
function newsletter_load($hash) {
  $result = db_query("SELECT hash, uid, date_added date, sent FROM {newsletter} WHERE hash = '%s'", $hash);
  if ($newsletter = db_fetch_array($result)) {
    return $newsletter;
  }
  return FALSE;
}

/**
 * @param      $uid
 * @param      $date
 * @param bool $hash
 */
function newsletter_save($uid, $date, $hash = FALSE) {
  if (FALSE === $hash) {
    $hash = newsletter_hash($uid, $date);
  }
  if (FALSE !== $hash) {
    db_query("REPLACE INTO {newsletter} SET hash = '%s', uid = '%s', send_date = '%s'", $hash, $uid, $date);
    return TRUE;
  }
  return FALSE;
}

/**
 * @param $hash
 */
function newsletter_delete($hash) {
  db_query("DELETE FROM {newsletter} WHERE hash = '%s'", $hash);
  db_query("DELETE FROM {newsletter_nodes} WHERE hash = '%s'", $hash);
}

/**
 * @param      $hash
 * @param bool $sent
 */
function newsletter_set_sent($hash, $sent = TRUE) {
  db_query("UPDATE {newsletter} SET sent = '%d' WHERE hash = '%s'", $sent ? 1 : 0, $hash);
}

/**
 * Frequencies
 */
define('NEWSLETTER_NEVER', 0);
define('NEWSLETTER_MONTHLY', 1);
define('NEWSLETTER_WEEKLY', 2);

/**
 * @param $uid
 *
 * @return int
 */
function newsletter_frequency_get($uid) {
  $result = db_query("SELECT code FROM {newsletter_frequency} WHERE uid = '%s'", $uid);
  if (FALSE !== ($code = db_result($result))) {
    return intval($code);
  }
  return NEWSLETTER_WEEKLY;
}

/**
 * @param     $uid
 * @param int $code
 */
function newsletter_frequency_set($uid, $code = NEWSLETTER_WEEKLY) {
  db_query("DELETE FROM {newsletter_frequency} WHERE uid = '%s'", $uid);
  db_query("INSERT INTO {newsletter_frequency} SET uid = '%s', code = '%s'", $uid, $code);
}

/**
 * @param $hash
 *
 * @return array
 */
function newsletter_save_nodes($hash, $nids = array()) {
  $params = array();
  $values = array();
  foreach ($nids as $nid) {
    $params[] = $hash;
    $params[] = $nid;
    $values[] = "('%s', '%s')";
  }

  db_query("DELETE FROM {newsletter_nodes} WHERE hash = '%s'", $hash);
  db_query("INSERT INTO {newsletter_nodes} VALUES " . implode(', ', $values), $params);
}

/**
 * @param $hash
 *
 * @return array
 */
function newsletter_load_nodes($hash) {
  $nids = array();
  $result = db_query("SELECT nid FROM {newsletter_nodes} WHERE hash = '%s'", $hash);
  while ($nid = db_result($result)) {
    $nids[] = $nid;
  }
  return $nids;
}



