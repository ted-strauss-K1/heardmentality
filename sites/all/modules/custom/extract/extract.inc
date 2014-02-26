<?php

//include "extract.install";
//extract_install();


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
    case 'update' :
    case 'insert' :

      //
      break;
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
  $vocabularies = taxonomy_get_vocabularies('issue');
  foreach ($vocabularies as $vocabulary) {
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
}

/**
 * @param $form
 * @param $form_state
 */
function extract_cache_profile() {
  global $user;
  $uid = $user->uid;

  // query building
  $query = "REPLACE INTO extract_cache_profile SET uid = '%s'";
  $params = array($uid);

  // fields
  $result = db_query("SELECT * FROM profile_fields pf LEFT JOIN profile_values pv ON pf.fid = pv.fid AND pv.uid = '%s'", $uid);
  while ($field = db_fetch_object($result)) {
    $query .= ", " . $field->name . " = '%s'";

    if ('selection' == $field->type) {
      if ('' == $field->value) {
        $params[] = 'undefined';
      }
      else {
        $options = explode("\n", $field->options);
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

extract_cache_profile();
