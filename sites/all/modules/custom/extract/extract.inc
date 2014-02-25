<?php

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
      exit('extract');


      break;
  }
}

/**
 * @param $form
 * @param $form_state
 * @param $form_id
 */
function extract_form_alter(&$form, &$form_state, $form_id) {
  if ('user_profile_edit_form' == $form_id) {
    $form['#submit'][] = 'extract_cache_user';
  }
}

/**
 * @param $form
 * @param $form_state
 */
function extract_cache_user(&$form, &$form_state) {
  // todo
}
