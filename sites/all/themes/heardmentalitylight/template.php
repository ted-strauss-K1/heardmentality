<?php

/**
 * Preprocess Drupal Status Messages
 *
 * @author odyachenko
 *
 * @param null $display
 * @return bool
 */
function heardmentalitylight_status_messages($display = NULL) {
  $noty = array();
//  $noty_pattern = "$.hrd.noty({'text':'%s','type':'%s'});";
  $noty_pattern = "$.hrd.noty(%s);";
  foreach (drupal_get_messages($display) as $type => $messages) {
    $noty_type = FALSE;
    switch ($type) {
      case 'status' :
        $noty_type = 'success';
      break;
      case 'warning' :
        $noty_type = 'warning';
      break;
      case 'error' :
        $noty_type = 'error';
      break;
    }
    if ($noty_type !== FALSE) {
      foreach ($messages as $message) {
//        $noty[] = sprintf($noty_pattern, addslashes($message), $noty_type);
        $noty[] = sprintf($noty_pattern, json_encode(array(
          'text' => $message,
          'type' => $noty_type,
        ) + ($noty_type == 'error' && preg_match('/password/', $message) ?
          array('timeout' => FALSE) : array()
        )));
      }
    }
  }
  drupal_add_js('$(document).ready(function(){'.implode('',$noty).'});', 'inline');
  return FALSE;
}


/**
 * Preprocess Pages
 *
 * @param $vars
 */
function heardmentalitylight_preprocess_page(&$vars) {
  if ($_GET['q'] == variable_get('site_403', '') || $_GET['q'] == variable_get('site_404', '')) {
    array_push($vars['template_files'], 'page-error');
  }

  if ((arg(0)=='node') && is_numeric(arg(1))) {
    if ($node = $vars['node']) {
      switch ($node->type) {
        case 'issue' :
          # set specific page templates
          drupal_set_subtitle(t('Issue'));
          array_push($vars['template_files'], 'page_12_4');
          $vars['content_class'] = 'poll-box';
        break;
        case 'static' :
          drupal_set_subtitle(drupal_get_title());
          array_push($vars['template_files'], 'page_12_4');
        break;
      }
    }
  }

  # js setting for all modules to use
  global $language;
  drupal_add_js(array('language' => $language->language), 'setting');
  drupal_add_js(array('language_prefix' => $language->prefix ? '/'.$language->prefix : ''), 'setting');

  # user
  global $user;
  drupal_add_js(array('user' => array(
    'uid' => $user->uid,
  )), 'setting');
}

/**
 * Preprocess Node Pages
 *
 * @param $vars
 */
function heardmentalitylight_preprocess_node(&$vars) {
  $node = &$vars['node'];

  # js setting for all modules to use
  drupal_add_js(array('node' => array(
    'nid' => $node->nid,
    'uid' => $node->uid,
  )), 'setting');
}

/**
 * @return array
 */
function heardmentalitylight_theme(){
  $theme = array();

  $theme['expander'] = array(
    'arguments' => array(
      'text' => '',
      'chars' => 1000,
    ),
  );

  $theme['moderation_pager'] = array(
    'arguments' => array(
      'page' => 1,
      'pages' => 1,
      'pattern' => NULL,
    ),
  );

  $theme['gpager'] = array(
    'arguments' => array(
      'page' => 1,
      'pages' => 1,
      'count' => 0,
      'perpage' => 5,
    ),
  );
  $theme['gpager_link'] = array(
    'arguments' => array(
      'page' => 1,
      'page_active' => 1,
      'anchor' => FALSE,
    ),
  );

  $theme['sub_loader'] = array(
    'arguments' => array('styles' => NULL),
  );

  return $theme;
}

/**
 * @param $text
 * @param int $chars
 * @return string
 */
function heardmentalitylight_expander($text, $chars = 1000, $tags = '<p><a><b><br />') {
  return '<div class="expander" data-chars="'.$chars.'">' . strip_tags($text, $tags) . '</div>';
}

/**
 * @param $page
 * @param $pages
 * @param $count
 * @param $perpage
 * @param string $theme_callback
 * @return string
 */
function heardmentalitylight_gpager($page, $pages, $count, $perpage, $theme_callback = 'gpager_link') {
  if (is_null($pages)) {
    $pages = ceil($count/$perpage);
  }
  if ($pages <= 0) {
    $pages = 1;
  }
  if (($page <= 0) || ($page > $pages)) {
    $page = 1;
  }
  if (1 == $pages) return '';

  $show_l = min(5,$page-1);
  $show_r = min(9-$show_l, $pages-$page);
  $output = '<div class="mod-pager"><span class="mod-text">PAGE</span> &nbsp;';
  if ($page - $show_l > 1) {
    $output .= theme($theme_callback, $page-1, $page, '<');
    $output .= '<span class="mod-spacer">&nbsp;</span>';
  }
  for ($i = $page-$show_l; $i <= $page-1; $i++) {
    $output .= theme($theme_callback, $i, $page);
  }
  $output .= theme($theme_callback, $page, $page);
  for ($i = $page+1; $i <= $page+$show_r; $i++) {
    $output .= theme($theme_callback, $i, $page);
  }
  if ($page + $show_r < $pages) {
    $output .= '<span class="mod-spacer">&nbsp;</span>';
    $output .= theme($theme_callback, $page+1, $page, '>');
  }
  $output .= '</div>';
  return $output;
}

/**
 * @param $page
 * @param $page_active
 * @param bool $anchor
 * @return string
 */
function heardmentalitylight_gpager_link($page, $page_active, $anchor = FALSE) {
  return sprintf('<a href="?page=%d" class="%s">%s</a>',
    $page,
    $page == $page_active ? 'mod-active' : '',
    FALSE == $anchor ? $page : $anchor
  );
}

/**
 * Theme for pager
 *
 * @param $page
 * @param $pages
 * @param $pattern
 * @return string
 */
function heardmentalitylight_moderation_pager($page, $pages, $pattern)
{
  if ($pages == 1) return '';
  if ($page > $pages) $page = $pages;
  $output = '<div class="mod-pager"><span class="mod-text">PAGE</span> &nbsp;';
  $a = '<a href="/%s" class="%s">%d</a>';
  $showpages = array_unique(array(1, 2, $page - 1, $page, $page + 1, $pages - 1, $pages));
  $flag = TRUE;
  for ($i = 1; $i <= $pages; $i++) {
    if (in_array($i, $showpages)) {
      $output .= sprintf($a, sprintf($pattern, $i), $page == $i ? 'mod-active' : '', $i);
      $flag = TRUE;
    } elseif ($i == 3 || $i == $pages - 2) {
      if ($flag) $output .= '<span class="mod-spacer">&nbsp;</span>';
      $flag = FALSE;
    }
  }
  $output .= '</div>';
  return $output;
}

/**
 * @param string $styles
 * @return string
 */
function heardmentalitylight_sub_loader($styles = '') {
  global $theme;
  return '<span id="sub_loader" style="'. $styles .'">
    <img src="/'.drupal_get_path('theme', $theme).'/images/loading_min.gif" alt="loading">
  </span>';
}
