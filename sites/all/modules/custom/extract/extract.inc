<?php

/**
 * @file extract.inc
 *
 * That file keeps caching data for users/issues
 */

/**
 *
 */
function extract_rebuild() {
  set_time_limit(0);

  $action = $_REQUEST['action'];

  if (!in_array($action, array('install', 'uninstall', 'reinstall'))) {
    echo '<ul>';
    echo '<li><a href="?action=reinstall">Reinstall</a>';
    echo '<li><a href="?action=install">Install</a>';
    echo '<li><a href="?action=uninstall">Uninstall</a>';
    echo '</ul>';
    exit;
  }

  module_load_include('install', 'extract', 'extract');

  // drop tables
  if ($action != 'install') {
    extract_uninstall();
  }

  if ($action == 'uninstall') {
    exit("All views and cache tables were uninstalled.");
  }

  // create tables
  extract_install();

  // init taxonomy
  extract_cache_taxonomy();

  // init locations
  // extract_cache_location();

  // init user profiles
  extract_cache_profiles();

  // init meta
  extract_cache_cpoll_metas();

  drupal_set_message(t('Extract caches were rebuilt'));

  drupal_goto();
}

/**
 * @param $form
 * @param $form_state
 * @param $form_id
 */
function extract_form_alter(&$form, &$form_state, $form_id) {
  // cache taxonomy hierarchy
  if ('taxonomy_form_term' == $form_id || 'taxonomy_overview_terms' == $form_id) {
    $form['#submit'][] = 'extract_cache_taxonomy';
  }

  // cache user profile
  if ('user_profile_edit_form' == $form_id) {
    $form['#submit'][] = 'extract_cache_profile';
  }

  // cache issue meta
  if ('moderation_issue_view_form' == $form_id) {
    $form['save']['#submit'][] = 'extract_cache_cpoll_meta_submit';
  }
}

/**
 *
 */
function extract_cache_taxonomy() {
  $mtime = microtime(TRUE);

  // clean up
  db_query("TRUNCATE TABLE {extract_cache_taxonomy}");

  //  depth 1 (parents)
  $depth = 1;
  db_query("
    INSERT INTO {extract_cache_taxonomy}
    SELECT
      th.tid AS tid,
      th.tid AS code,
      '%d' AS depth,
      th.tid AS category1,
      0 AS category2,
      0 AS category3,
      td.name AS category1_name,
      '' AS category2_name,
      '' AS category3_name
    FROM
      {term_hierarchy} th,
      {term_data} td
    WHERE
      th.parent = 0 AND
      td.tid = th.tid;", $depth);

  // depth 2
  $depth++;
  db_query("
    INSERT INTO {extract_cache_taxonomy}
    SELECT
      td.tid,
      CONCAT(ect.code,',',th.tid) AS code,
      '%d' AS depth,
      ect.category1,
      td.tid AS category2,
      0 AS category3,
      ect.category1_name,
      td.name AS category2_name,
      '' AS category3_name
    FROM
      {extract_cache_taxonomy} ect,
      {term_hierarchy} th,
      {term_data} td
    WHERE
      ect.depth = '%d' AND
      th.parent = ect.category_id AND
      td.tid = th.tid;", $depth, $depth - 1);

  // depth 3
  $depth++;
  db_query("
    INSERT INTO {extract_cache_taxonomy}
    SELECT
      td.tid,
      CONCAT(ect.code,',',th.tid) AS code,
      '%d' AS depth,
      ect.category1,
      ect.category2,
      td.tid AS category3,
      ect.category1_name,
      ect.category2_name,
      td.name AS category3_name
    FROM
      {extract_cache_taxonomy} ect,
      {term_hierarchy} th,
      {term_data} td
    WHERE
      ect.depth = '%d' AND
      th.parent = ect.category_id AND
      td.tid = th.tid;", $depth, $depth - 1);

  drupal_set_message(t('Taxonomy cache was rebuilt (' . round(microtime(TRUE) - $mtime, 4) . ' sec)'));
}

/**
 *
 */
function extract_cache_location() {
  $mtime = microtime(TRUE);

  // clean up
  db_query("TRUNCATE TABLE {extract_cache_location}");

  $locations = array();

  // countries
  $countries = location_get_iso3166_list();
  foreach ($countries as $location1 => $location1_name) {
    $locations[] = array(
      location_code($location1),
      1,
      $location1,
      '',
      '',
      $location1_name,
      '',
      '',
    );
    foreach (location_get_provinces($location1) as $location2 => $location2_name) {
      $locations[] = array(
        location_code($location1, $location2),
        2,
        $location1,
        $location2,
        '',
        $location1_name,
        $location2_name,
        '',
      );
      foreach (location_get_cities($location1, $location2) as $location3 => $location3_name) {
        $locations[] = array(
          location_code($location1, $location2, $location3),
          3,
          $location1,
          $location2,
          $location3,
          $location1_name,
          $location2_name,
          $location3_name,
        );
      }
    }
  }

  foreach ($locations as $location) {
    db_query("INSERT INTO {extract_cache_location} VALUES ('%s','%d','%s','%s','%s','%s','%s','%s')", $location);
  }

  drupal_set_message(t('Location cache was rebuilt (' . count($locations) . ' items for ' . round(microtime(TRUE) - $mtime, 4) . ' sec)'));
}

/**
 *
 */
function extract_cache_profiles() {
  $mtime = microtime(TRUE);

  $result = db_query("SELECT uid FROM {users} WHERE uid > 0");
  while ($uid = db_result($result)) {
    extract_cache_profile($uid);
  }

  drupal_set_message(t('User demographics cache was rebuilt (' . round(microtime(TRUE) - $mtime, 4) . ' sec)'));
}

/**
 * @param $form
 * @param $form_state
 */
function extract_cache_profile($uid = FALSE) {
  //
  if (FALSE === $uid) {
    global $user;
    $uid = $user->uid;
  }

  // inc
  module_load_include('inc', 'location', 'location');

  // query building
  $query = "REPLACE INTO extract_cache_profile SET uid = '%s'";
  $params = array($uid);

  // locations
  $country = '';
  $state = '';

  // fields
  $result = db_query("
    SELECT *
    FROM profile_fields pf
    LEFT JOIN profile_values pv
    ON pf.fid = pv.fid AND pv.uid = '%s'
    ORDER BY (CASE name WHEN 'profile_city' THEN 3 WHEN 'profile_state' THEN 2 WHEN 'profile_country' THEN 1 ELSE 0 END)", $uid);
  while ($field = db_fetch_object($result)) {
    $query .= ", " . $field->name . " = '%s'";

    if ('selection' == $field->type) {
      if ('' == $field->value) {
        $params[] = 'undefined';
      }
      else {
        switch ($field->name) {
          case 'profile_city' :
            if ($state) {
              $cities = location_get_cities($country, $state);
              $options = $cities;
            }
            break;
          case 'profile_state' :
            if ($country) {
              $state = $field->value;
              $states = location_get_provinces($country);
              $options = $states;
            }
            break;
          case 'profile_country' :
            $country = $field->value;
            $countries = location_get_iso3166_list();
            $options = $countries;
            break;
          default :
            $options = explode("\n", $field->options);
            break;
        }
        $params[] = isset($options[$field->value]) ? trim($options[$field->value]) : 'undefined';
      }
    }
    else {
      $params[] = $field->value;
    }
  }

  // params
  db_query($query, $params);
}

/**
 * Implementation of hook_user()
 *
 * @param      $op
 * @param      $edit
 * @param      $account
 * @param null $category
 */
function extract_user($op, &$edit, &$account, $category = NULL) {
  switch ($op) {
    case 'delete' :
      db_query("DELETE FROM {extract_cache_taxonomy} WHERE uid = '%s'", $account->uid);
      break;
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
function extract_nodeapi(&$node, $op, $a3 = NULL, $a4 = NULL) {
  if ('issue' == $node->type) {
    switch ($op) {
      case 'delete' :
        if (isset($node->choices) && $node->choices) {
          $chids = array_keys($node->choices);
          db_query("DELETE FROM {extract_cache_cpoll_meta} WHERE chid IN (" . db_placeholders($chids) . ")", $chids);
        }
        break;
      case 'insert' :
      case 'update' :
        extract_cache_cpoll_meta($node->nid);
        break;
    }
  }
}

/**
 *
 */
function extract_cache_cpoll_metas() {
  $mtime = microtime(TRUE);

  $result = db_query("SELECT nid FROM {node} WHERE type = '%s'", 'issue');
  while ($nid = db_result($result)) {
    extract_cache_cpoll_meta($nid);
  }

  drupal_set_message(t('Issue meta cache was rebuilt (' . round(microtime(TRUE) - $mtime, 4) . ' sec)'));
}

/**
 * @param $nid
 */
function extract_cache_cpoll_meta($nid) {
  $choices = cpoll_load_choices($nid);
  foreach ($choices as $chid => $choice) {
    $query = "REPLACE INTO extract_cache_cpoll_meta SET chid = '%s'";
    $params = array($chid);

    $result = db_query("
      SELECT cm.*, AVG(value) val
      FROM cpoll_meta_values cmv
      INNER JOIN cpoll_meta cm ON cm.cid = cmv.cid
      WHERE cmv.chid = '%s'
      GROUP BY cm.cid", $chid);
    while ($meta = db_fetch_object($result)) {
      $query .= ", " . cpoll_meta_code($meta->chtext) . " = '%s'";
      $params[] = $meta->val;
    }

    db_query($query, $params);
  }
}

/**
 * @param $form
 */
function extract_cache_cpoll_meta_submit($form) {
  extract_cache_cpoll_meta($form['content_id']['#value']);
}
