<?php

/**
 * API function : add event
 *
 * @param $type
 * @param $vars
 * @param bool $uid
 */
function events_add($type, $vars, $uid = false)
{
  if ($uid === false) {
    global $user;
    $uid = $user->uid;
  }
  $query = "INSERT INTO {events} SET uid = '%d', type = '%s', vars = '%s', date_added = '%s'";
  $params = array(
    $uid,
    $type,
    serialize($vars),
    date('Y-m-d H:i:s')
  );
  foreach (array('content_id', 'content_type') as $pname) {
    if (isset($vars[$pname])) {
      $query .= ", " . $pname . " = '%s'";
      $params[] = $vars[$pname];
    }
  }
  db_query($query, $params);
}

/**
 * API function : delete events
 *
 * @param array $p
 */
function events_del($p = array())
{
  $query = "DELETE FROM {events} WHERE 1";
  $params = array();
  foreach (array('uid', 'type', 'content_id', 'content_type') as $key) {
    if (isset($p[$key])) {
      $query .= " AND " . $key . " = '%s'";
      $params[] = $p[$key];
    }
  }
  // time in hours
  if (isset($p['time'])) {
    $query .= " AND date_added > ADDDATE('" . date('Y-m-d H:i:s') . "', INTERVAL -" . addslashes($p['time']) . " HOUR)";
  }
  db_query($query, $params);
}

/**
 * API function : get events
 *
 * @param int $count
 * @param array $p
 * @return array
 */
function events_get($p = array(), $count = 30)
{
  $items = array();

  # build query
  if (!isset($p['q'])) {
    $p['q'] = $p;
  }

  # query parts
  $query = "SELECT DISTINCT * FROM (";
  $params = array();

  # merge queries into one union query
  $union = '';
  if (1 == count($p['q'])) {
    $union = $p['q'][0]['query'];
    $params = $p['q'][0]['params'];
  } else {
    foreach ($p['q'] as $i => $q) {
      if (false === $q) continue;
      if (0 != $i) {
        $union .= " UNION ";
      }
      $union .= "(" . $q['query'] . ")";
      foreach ($q['params'] as $param) {
        $params[] = $param;
      }
    }
  }
  $query .= $union;
  $query .= ") merge";
  if ($p['update']) {
    $query .= " WHERE id > %d";
    $params[] = $p['update'];
  }
  $query .= " ORDER BY date_added DESC";
  if (false !== $count) {
    $query .= " LIMIT %d";
    $params[] = $count;
  }

  # fetch results
  static $users = array();

  $result = db_query($query, $params);
  while ($item = db_fetch_array($result)) {
    $item['vars'] = unserialize($item['vars']);
    if (!$users[$item['uid']]) {
      $users[$item['uid']] = user_load($item['uid']);
    }
    $item['account'] = $users[$item['uid']];
    $item['timestamp'] = strtotime($item['date_added']);
    if (function_exists('time_interval')) {
      $item['date_added'] = time_interval($item['date_added']);
    }
    $items[$item['id']] = $item;
  }

  return $items;
}

/**
 * Build query for regular filtering search
 *
 * @param array $p
 * @return array
 */
function events_build_query($p = array()) {
  $query = "SELECT * FROM {events} WHERE 1";
  $params = array();
  foreach (array('uid', 'type', 'content_id', 'content_type') as $key) {
    if (isset($p[$key])) {
      if (is_array($p[$key])) {
        if (!empty($p[$key])) {
          $query .= " AND " . $key . " IN (" . db_placeholders($p[$key], 'varchar') . ")";
          $params = array_merge($params, $p[$key]);
        }
      } else {
        $query .= " AND " . $key . " = '%s'";
        $params[] = $p[$key];
      }
    }
  }
  if (isset($p['exclude'])) {
    $p = $p['exclude'];
    foreach (array('uid', 'type', 'content_id', 'content_type') as $key) {
      if (isset($p[$key])) {
        if (is_array($p[$key])) {
          if (!empty($p[$key])) {
            $query .= " AND " . $key . " NOT IN (" . db_placeholders($p[$key], 'varchar') . ")";
            $params = array_merge($params, $p[$key]);
          }
        } else {
          $query .= " AND " . $key . " <> '%s'";
          $params[] = $p[$key];
        }
      }
    }
  }

  return array(
    'query' => $query,
    'params' => $params,
  );
}

/**
 * @param bool $uid
 * @return array
 */
function events_subscriptions_build_query($uid = FALSE) {
  if (!module_exists('subscriptions')) {
    return false;
  }

  # uid
  if ($uid === FALSE) {
    global $user;
    $uid = $user->uid;
  }

  # build query
  $params = array();
  $query = "
    SELECT e.*
    FROM {node} n
    INNER JOIN {events} e ON e.content_id = n.nid AND e.content_type = 'node'
    INNER JOIN {term_node} tn ON tn.nid = n.nid
    INNER JOIN {subscriptions} s ON s.module = 'node' AND s.field = 'tid' AND s.value = tn.tid
    WHERE n.type = 'poll' AND s.recipient_uid = '%d'";
  $params[] = $uid;

  return array(
    'query' => $query,
    'params' => $params,
  );
}



//var_dump(
//
//  events_get(array(
//    'q' => array(
////      0 => events_build_query(array('content_type' => 'node')),
////      1 => events_subscriptions_build_query()
//    ),
//  ))
//
//); exit;