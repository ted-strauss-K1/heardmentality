<?php

/**
 * Define a permission name
 */
define('BADGES_ADMIN', 'Administer Badges');

/**
 * Implementation of hook_perm()
 *
 * @return array
 */
function badges_perm()
{
  return array(BADGES_ADMIN);
}

/**
 * Implementation of hook_menu()
 *
 * @return array
 */
function badges_admin_menu()
{
  $menu = array();

  $menu['admin/settings/badges'] = array(
    'title' => t('Badges'),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('badges_form'),
    'access arguments' => array(BADGES_ADMIN),
  );

  return $menu;
}

/**
 * @return array
 */
function badges_form()
{
  return array(
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Rebuild Badges List'),
    ),
  );
}

/**
 *
 */
function badges_form_submit()
{
  db_query("DELETE FROM {badges} WHERE uid <= 0");
  foreach (badges_list() as $name => $info) {
    badges_add(-1, $name);
  }
}