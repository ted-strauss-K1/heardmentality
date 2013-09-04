<?php

/**
 * @param $node
 * @return array
 */
function charts_chtexts($node)
{
  static $chtexts = NULL;

  if (is_null($chtexts)) {
    $chtexts = array();
    if ($node->choices) {
      foreach ($node->choices as $choice) {
        $chtexts[] = $choice['chtext_short'];
      }
    }
  }

  return $chtexts;
}

/**
 * Colors
 *
 * @param bool $index
 * @return array
 */
function charts_colors($index = FALSE)
{
  static $i = 0;
  static $colors = array();
  if (empty($colors)) {
    $colors += array(
      '#934d9e',
      '#ff7f00',
      '#50c0ac',
      '#0c6926',
      '#ef4c8d',
      '#362750',
      '#e1e43c',
      '#ef3d3b',
      '#3cc7f4',
      '#589a1c',
      '#c2499b',
      '#f89521',
      '#cc2027',
      '#55ba59',
      '#d5bc29',
      '#6ccbd5',
      '#43b649',
      '#f6eb16'
    );
  }
  if ($index === TRUE) {
    return $colors;
  }
  if ($index !== FALSE && isset($colors[$index])) {
    return $colors[$index];
  } else {
    $color = $colors[$i];
    $i = ($i + 1) % count($colors);
    return $color;
  }
}

/**
 * Range of dates - Y-m-d
 *
 * @param $date1
 * @param $date2
 * @return array
 */
function dates_range($date1, $date2)
{
  $range = array();
  if (!empty($date1) && !empty($date2) && $date1 < $date2) {
    $date1 = strtotime($date1);
    $date2 = strtotime($date2);
    $range[] = date('Y-m-d', $date1);
    while ($date1 < $date2) {
      $date1 = strtotime('+1 day', $date1);
      $range[] = date('Y-m-d', $date1);
    }
  }
  return $range;
}

