<?php
// $Id: template.php,v 1.1 2009/07/22 18:24:01 proxiss Exp $

/**
 * @file
 * The theme system, which controls the output of Drupal.
 *
 * Provide different arrays for local task levels.
 */

?><?php

function adarkproxisstheme_menu_item_link($link) {
  if (empty($link['localized_options'])) {
    $link['localized_options'] = array();
  }
  
  // firep($link, "Theme Link");
  if (($link['menu_name'] == 'primary-links') || isset($link['tab_parent'])) {
    $opt = $link['localized_options'];
    $opt['html'] = TRUE; 
    return l('<span>'. $link['title'] .'</span>', $link['href'], $opt);
  } 
  else {
    return l($link['title'], $link['href'], $link['localized_options']);
  }
}

/**
 * Override or insert PHPTemplate variables into the templates.
 */
function phptemplate_preprocess_page(&$vars) {
  $vars['tabs2'] = menu_secondary_local_tasks();

  // Hook into color.module
  if (module_exists('color')) {
    _color_page_alter($vars);
  }
}

/**
 * Returns the rendered local tasks. The default implementation renders
 * them as tabs. Overridden to split the secondary tasks.
 *
 * @ingroup themeable
 */
function phptemplate_menu_local_tasks() {
  return menu_primary_local_tasks();
}

