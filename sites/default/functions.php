<?php

/**
 * Set the title of the current page, for display on the page and in the title bar.
 *
 * @param $title
 *   Optional string value to assign to the page title; or if set to NULL
 *   (default), leaves the current title unchanged.
 *
 * @return
 *   The updated title of the current page.
 */
function drupal_set_subtitle($title = NULL) {
  static $stored_title;

  if (isset($title)) {
    $stored_title = $title;
  }

  return $stored_title;
}