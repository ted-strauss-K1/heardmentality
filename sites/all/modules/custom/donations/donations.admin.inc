<?php

/**
 * Define permissions
 */
define('DONATIONS_ADMIN', 'Administer Donations');

/**
 * @return array
 */
function donations_admin_menu() {
  $menu = array();

  $menu['admin/settings/donations'] = array(
    'title'            => t('Donations'),
    'page callback'    => 'drupal_get_form',
    'page arguments'   => array('donations_admin_form'),
    'access arguments' => array(DONATIONS_ADMIN),
    'type'             => MENU_NORMAL_ITEM,
  );
  $menu['admin/settings/donations/settings'] = array(
    'title'  => t('Donations'),
    'type'   => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10,
  );

  return $menu;
}

/**
 * @return array
 */
function donations_admin_perm() {
  return array(DONATIONS_ADMIN);
}

/**
 * Donation Admin form
 */
function donations_admin_form() {
  $form = array();

  $form['prefix'] = array(
    "#type"  => "textarea",
    "#title" => t("Prefix text"),
    "#value" => variable_get('donations_prefix', ''),
  );

  $values = variable_get('donations_values', array());
  $tmp = array();
  foreach ($values as $item => $string) {
    $tmp[] = $item . '|' . $string;
  }

  $form['values'] = array(
    "#type"        => "textarea",
    "#title"       => t("Values"),
    "#value"       => implode("\n", $tmp),
    '#description' => t('On value per row in format "50|50$"')
  );

  $form['suffix'] = array(
    "#type"  => "textarea",
    "#title" => t("Suffix text"),
    "#value" => variable_get('donations_suffix', ''),
  );

  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Donation Admin form - Submission
 */
function donations_admin_form_submit($form, $form_state) {
  $post = $form_state["clicked_button"]["#post"];
  $values = explode("\n", $post['values']);
  $list = array();
  foreach ($values as $item) {
    if (!empty($item)) {
      $item = explode("|", $item, 2);
      $list[$item[0]] = empty($item[1]) ? $item[0] : $item[1];
    }
  }
  variable_set('donations_values', $list);
  variable_set('donations_prefix', $post['prefix']);
  variable_set('donations_suffix', $post['suffix']);
}
