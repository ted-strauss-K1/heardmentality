<?php

/**
 * List of badges types
 *
 * @return array
 */
function badges_types($type = FALSE)
{
  static $types = NULL;

  if (is_null($types)) {
    $types = module_invoke_all('badges_types');
  }

  if ($type !== FALSE) {
    return $types[$type];
  }

  return $types;
}

/**
 * Implementation of hook_badges_types()
 *
 * @return array
 */
function badges_badges_types()
{
  return array(
    'bronze' => t('Bronze'),
    'silver' => t('Silver'),
    'gold' => t('Gold'),
  );
}

/**
 * Badge add
 *
 * @param $uid
 * @param $badge
 */
function badges_add($uid, $badge)
{
  db_query("INSERT INTO {badges} SET uid = '%d', badge = '%s', date_added = '%s'", $uid, $badge, date("y-m-d H:i:s"));

  static $users = array();

  if (is_null($users[$uid])) {
    $users[$uid] = user_load($uid);
    if (module_exists('rules')) {
      rules_invoke_event('badges_grant', $users[$uid], $badge);
    }
  }
}

/**
 * @param array $p
 */
function badges_del($p = array())
{
  if (empty($p)) {
    return;
  }
  $query = "DELETE FROM {badges} WHERE 1";
  $params = array();

  foreach ($p as $key => $val) {
    if (in_array($key, array('id', 'uid', 'badge'))) {
      $query .= " AND " . $key . " = '%s'";
      $params[] = $val;
    }
  }

  db_query($query, $params);
}

/**
 * List of badges
 *
 * @return array
 */
function badges_list($badge = FALSE)
{
  static $badges = NULL;

  if (is_null($badges)) {
    $badges = array();
    // to check types
    $types = badges_types();
    $types_names = array_keys($types);
    $types_default = array_shift($types_names);

    foreach (module_invoke_all('badges') as $name => $info) {
      $badges[$name] = $info + array(
        'function' => '_badges_check',
        'count' => 1,
        'info' => '',
        'arguments' => array(),
      );
      // name
      if (!isset($info['name']) || empty($info['name'])) {
        $badges[$name]['name'] = ucwords(str_replace('_', ' ', $name));
      }
      // to check types
      $type = $badges[$name]['type'];
      if (!isset($types[$type])) {
        $badges[$name]['type'] = $types_default;
      }
    }
  }

  // get specific badge
  if ($badge !== FALSE) {
    return isset($badges[$badge]) ? $badges[$badge] : FALSE;
  }

  return $badges;
}

/**
 * Default function to check the badge permission
 *
 * @param int $uid
 * @return bool
 */
function _badges_check($uid = 0)
{
  return FALSE;
}

/**
 * Default function to check the badge permission for multiple users
 *
 * @param array $uids
 * @return array
 */
function _badges_check_multiple($uids = array(), $arguments = array())
{
  $output = array();

  $function = isset($arguments['function']) && function_exists($arguments['function']) ? $arguments['function'] : '_badges_check';

  foreach ($uids as $uid) {
    $output[$uid] = $function($uid);
  }

  return $output;
}

/**
 * Count the number of the badges granted to user
 *
 * @param $badge
 */
function badges_count($badge, $uid = FALSE)
{
  static $counts = array();

  if (!isset($counts[$badge])) {
    $counts[$badge] = array();

    $result = db_query("SELECT u.uid, IFNULL(COUNT(*),0) AS count FROM {users} u INNER JOIN {badges} b ON b.uid = u.uid AND b.badge = '%s' GROUP BY u.uid", $badge);
    while ($row = db_fetch_object($result)) {
      $counts[$badge][$row->uid] = $row->count;
    }
  }
  // count for specific user
  if ($uid !== FALSE) {
    return isset($counts[$badge][$uid]) ? $counts[$badge][$uid] : 0;
  }

  return $counts[$badge];
}

/**
 * @param $item
 * @param $badge
 * @return bool
 */
function badges_grant($item, $badge)
{
  // get badge
  $badge_data = badges_list($badge);
  if ($badge_data === FALSE) {
    return FALSE;
  }

  $output = array();

  if (is_array($item)) {
    $function = $badge_data['function multiple'];
    $arguments = $badge_data['arguments'];
    if (!$function || !function_exists($function)) {
      $function = '_badges_check_multiple';
      $arguments['function'] = $badge_data['function'];
    }
    $results = $function($item, $arguments);
    foreach ($results as $uid => $result) {
      if ($result && (($badge_data['count'] === TRUE) || ($badge_data['count'] > badges_count($badge, $uid)))) {
        badges_add($uid, $badge);
        $output[] = array('uid' => $uid, 'badge' => $badge);
      }
    }
  } else {
    $function = $badge_data['function'];
    $arguments = $badge_data['arguments'];
    $result = !function_exists($function) ? FALSE : $function($item, $arguments);
    $uid = $item;
    if ($result && (($badge_data['count'] === TRUE) || ($badge_data['count'] > badges_count($badge, $uid)))) {
      badges_add($uid, $badge);
      $output[] = array('uid' => $uid, 'badge' => $badge);
    }
  }

  return $output;
}