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
function extract_user ($op, &$edit, &$account, $category = NULL) {
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
function extract_form_alter (&$form, &$form_state, $form_id) {
  // cache taxonomy hierarchy
  if ('taxonomy_form_term' == $form_id) {
    $form['#submit'][] = 'extract_cache_taxonomy';
  }

  if ('user_profile_edit_form' == $form_id) {
    $form['#submit'][] = 'extract_cache_user';
  }
}

/**
 * @param $form
 * @param $form_state
 */
function extract_cache_taxonomy () {
  // clean up
  db_query("TRUNCATE TABLE {extract_cache_taxonomy}");

  //
  $vocabularies = taxonomy_get_vocabularies('issue');
  foreach ($vocabularies as $vocabulary) {
    for ($depth=0; $depth<=2; $depth++) {
      if (0 == $depth) {
        db_query("
          INSERT INTO extract_cache_taxonomy
          SELECT
            th.tid AS tid,
            th.tid AS code,
            0 AS depth
          FROM term_hierarchy th
          WHERE th.parent = 0;");
      } else {
        db_query("
          INSERT INTO extract_cache_taxonomy
          SELECT
            th.tid AS tid,
            th.tid AS code,
            '%d' AS depth
          FROM term_hierarchy th, extract_cache_taxonomy ect
          WHERE th.parent = ect.tid AND ect.depth = '%d';", $depth, $depth-1);
      }
    }

    $depth++;


    db_query("CREATE VIEW th1 AS SELECT term_hierarchy.tid AS tid, term_hierarchy.tid AS code FROM term_hierarchy WHERE term_hierarchy.parent = 0;");
    db_query("CREATE VIEW th2 AS SELECT th.tid AS tid, CONCAT(th1.code,',',th.tid) AS code FROM term_hierarchy th INNER JOIN th1 ON th.parent = th1.tid;");
    db_query("CREATE VIEW th3 AS SELECT th.tid AS tid, CONCAT(th2.code,',',th.tid) AS code FROM term_hierarchy th INNER JOIN th2 ON th.parent = th2.tid;");
  }
}

extract_cache_taxonomy ();
/**
 * @param $form
 * @param $form_state
 */
function extract_cache_user (&$form, &$form_state) {
  // todo
}
