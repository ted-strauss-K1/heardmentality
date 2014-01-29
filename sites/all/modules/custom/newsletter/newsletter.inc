<?php

/**
 * @param      $email
 * @param bool $reset
 *
 * @return subscription
 */
function newsletter_subscription($email, $reset = FALSE) {
  static $cache = array();

  if (is_null($cache[$email]) || $reset) {
    // get subscription
    $account = (object) array('mail' => $email);
    $subscription = simplenews_get_subscription($account);

    // subscription does not exist
    if ($subscription->snid == 0) {
      global $language;
      $account = _simplenews_user_load($email);
      if (variable_get('language_count', 1) > 1) {
        if ($account->uid) {
          $preferred_language = $account->language;
        }
        else {
          $preferred_language = isset($preferred_language) ? $preferred_language : $language->language;
        }
      }
      db_query("
        INSERT INTO {simplenews_subscriptions}
        (mail, uid, language, activated, timestamp)
        VALUES ('%s', %d, '%s', %d, %d)", $email, $account->uid, $preferred_language, 1, time());
    }

    // cache
    $cache[$email] = $subscription;
  }

  return $cache[$email];
}

/**
 * Frequencies
 */
define('NEWSLETTER_NEVER', 0);
define('NEWSLETTER_MONTHLY', 1);
define('NEWSLETTER_WEEKLY', 2);

/**
 * @param $email
 *
 * @return int
 */
function newsletter_frequency_get($email) {
  $subscription = newsletter_subscription($email);
  return intval($subscription->freq);
}

/**
 * @param     $email
 * @param int $code
 */
function newsletter_frequency_set($email, $code = NEWSLETTER_WEEKLY) {
  $subscription = newsletter_subscription($email);
  db_query("UPDATE {simplenews_subscriptions} SET freq = '%d' WHERE snid = '%s'", $code, $subscription->snid);
  newsletter_subscription($email, TRUE);
}

/**
 * @param $snid
 * @param $send_date
 *
 * @return bool|string
 */
function newsletter_hash($snid, $send_date, $max = 9) {
  $i = 0;
  while ($i <= intval($max)) {
    $hash = md5($snid . ':' . $send_date . ':' . $i);
    if (FALSE === newsletter_load($hash)) {
      return $hash;
    }
    $i++;
  }
  return FALSE;
}

/**
 * @param $hash
 *
 * @return array|bool
 */
function newsletter_load($hash) {
  $result = db_query("SELECT * FROM {newsletter} WHERE hash = '%s'", $hash);
  if ($newsletter = db_fetch_array($result)) {
    return $newsletter;
  }
  return FALSE;
}

/**
 * @param      $snid
 * @param      $send_date
 * @param bool $hash
 */
function newsletter_save($snid, $send_date, $hash = FALSE) {
  if (FALSE === $hash) {
    $hash = newsletter_hash($snid, $send_date);
  }
  if (FALSE !== $hash) {
    db_query("REPLACE INTO {newsletter} SET hash = '%s', snid = '%s', send_date = '%s'", $hash, $snid, $send_date);
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
  db_query("UPDATE {newsletter} SET status = '%d' WHERE hash = '%s'", $sent ? 1 : 0, $hash);
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
