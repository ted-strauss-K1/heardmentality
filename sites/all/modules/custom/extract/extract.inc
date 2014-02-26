<?php

/**
 *
 */
function extract_rebuild() {
  module_load_include('install', 'extract', 'extract');

  // drop tables
  extract_uninstall();

  // create tables
  extract_install();

  //
  db_query("UPDATE {profile_fields} SET type = 'selection' WHERE name = 'profile_city'");
  db_query("UPDATE {profile_fields} SET type = 'selection' WHERE name = 'profile_state'");

  // init taxonomy
  extract_cache_taxonomy();

  // init user profiles
  $result = db_query("SELECT uid FROM {users} WHERE uid > 0");
  while ($uid = db_result($result)) {
    extract_cache_profile($uid);
  }

  // init meta
  $result = db_query("SELECT nid FROM {node} WHERE type = '%s'", 'issue');
  while ($nid = db_result($result)) {
    extract_cache_cpoll_meta($nid);
  }

  drupal_set_message(t('Caches were rebuilt'));

  drupal_goto();
}

/**
 * @file extract.inc
 *
 * That file keeps caching data for users/issues
 */

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
 * @param $form
 * @param $form_state
 * @param $form_id
 */
function extract_form_alter(&$form, &$form_state, $form_id) {
  // cache taxonomy hierarchy
  if ('taxonomy_form_term' == $form_id || 'taxonomy_overview_terms' == $form_id) {
    $form['#submit'][] = 'extract_cache_taxonomy';
  }

  //
  if ('user_profile_edit_form' == $form_id) {
    $form['#submit'][] = 'extract_cache_profile';
  }
}

/**
 * @param $form
 * @param $form_state
 */
function extract_cache_taxonomy() {
  // clean up
  db_query("TRUNCATE TABLE {extract_cache_taxonomy}");

  //
  for ($depth = 0; $depth <= 2; $depth++) {
    if (0 == $depth) {
      db_query("
        INSERT INTO {extract_cache_taxonomy}
        SELECT
          th.tid AS tid,
          th.tid AS code,
          0 AS depth
        FROM {term_hierarchy} th
        WHERE th.parent = 0;");
    }
    else {
      db_query("
        INSERT INTO {extract_cache_taxonomy}
        SELECT
          th.tid AS tid,
          CONCAT(ect.code,',',th.tid) AS code,
          '%d' AS depth
        FROM {term_hierarchy} th, {extract_cache_taxonomy} ect
        WHERE th.parent = ect.tid AND ect.depth = '%d';", $depth, $depth - 1);
    }
  }
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
 * @param $nid
 */
function extract_cache_cpoll_meta($nid) {
  //
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
