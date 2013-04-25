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

# development function

function mtime($msg = false) {
  static $time, $data = array();

  if (false === $msg) {
    $time = round(microtime(true), 4);
    return;
  }

  if (true === $msg) {
    $output = "<table>";
    foreach ($data as $item) {
      $output .= sprintf("<tr><td>%s</td><td>%s</td></tr>", $item["time"], $item["msg"]);
    }
    $output .= "</table>";
    return $output;
  }

  $time2 = round(microtime(true), 4);
  $data[] = array(
    'msg' => $msg,
    'time' => $time2 - $time,
  );
  $time = $time2;
}