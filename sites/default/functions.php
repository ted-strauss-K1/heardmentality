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
function drupal_set_subtitle($title = NULL)
{
  static $stored_title;

  if (isset($title)) {
    $stored_title = $title;
  }

  return $stored_title;
}

/**
 * Converts time to string like "3 hour(s) ago"
 *
 * @param $time
 * @return string
 */
function time_interval($time)
{
  # dates/interval
  $date_now = new DateTime("now");
  $date = new DateTime($time);
  $interval = $date->diff($date_now);
  # convert to string
  if ($interval->y != 0) {
    return $interval->y . ' year' . ($interval->y > 1 ? 's' : '') . ' ago';
  }
  if ($interval->m != 0) {
    return $interval->m . ' month' . ($interval->m > 1 ? 's' : '') . ' ago';
  }
  if ($interval->d != 0) {
    return $interval->d . ' day' . ($interval->d > 1 ? 's' : '') . ' ago';
  }
  if ($interval->h != 0) {
    return $interval->h . ' hour' . ($interval->h > 1 ? 's' : '') . ' ago';
  }
  if ($interval->i != 0) {
    return $interval->i . ' minute' . ($interval->i > 1 ? 's' : '') . ' ago';
  }
  return 'just now';
}