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
    $node->iid = $node->reference[0]['nid'];
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
    return l(t('Delete'), '', array('attributes' => array(
      'class' => 'flag2 delete argument-delete',
      'title' => t('Delete'),
      'name' => $content_type . '/' . $content_id,
      'original-title' => t('delete'),
    )));
  }
}