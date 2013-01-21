<?php

/**
 * Theme argument_tab
 *
 * @param $nodes
 * @return string
 */
function theme_argument_tab($nodes)
{
  $output = '';
  foreach ($nodes as $node) {
    $output .= theme('argument_item', $node);
  }
  if (empty($output)) {
    $output = '<div class="messages warning">' . t('No arguments posted yet') . '</div>';
  }
  return $output;
}

/**
 * Theme argument_result_ball
 *
 * @param $count
 * @return string
 */
function theme_argument_result_ball($count)
{
  $value = abs($count);
  if ($value >= 100) {
    $class = 'large';
  } elseif ($value >= 10) {
    $class = 'middle';
  } else {
    $class = 'small';
  }
  $type = $count > 0 ? 'positive' : ($count < 0 ? 'negative' : 'null');
  return sprintf('<span class="sum %s"><span class="%s">%d</span></span>', $class, $type, $count);
}

/**
 * Theme time_interval
 *
 * Converts time to string like "3 hour(s) ago
 *
 * @param $timestamp
 */
function theme_time_interval($timestamp)
{
  # dates/interval
  $date_now = new DateTime("now");
  $date = new DateTime(date("F d Y H:i:s", $timestamp));
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

/**
 * Theme argument_delete
 *
 * @param $content_type
 * @param $content_id
 * @return string
 */
function theme_argument_delete($content_type, $content_id)
{
  global $user;
  if (user_access('moderation', $user) || argument_check_owner($content_type, $content_id)) {
    return l(t('Delete'), '#', array('attributes' => array(
      'class' => 'flag2 delete argument-delete',
      'title' => t('Delete'),
      'name' => $content_type . '/' . $content_id,
      'original-title' => t('delete'),
    )));
  }
}