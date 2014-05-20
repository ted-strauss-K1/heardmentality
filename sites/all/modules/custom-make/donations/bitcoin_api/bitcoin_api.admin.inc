<?php

/**
 * Implementation of hook_menu()
 */
function bitcoin_api_menu() {
  $menu = array();

  $menu['admin/settings/donations/bitcoin_api'] = array(
    'title'            => t('Bitcoin API'),
    'page callback'    => 'drupal_get_form',
    'page arguments'   => array('bitcoin_api_form'),
    'access arguments' => array(DONATIONS_ADMIN),
    'type'             => MENU_LOCAL_TASK,
    'weight'           => -8,
  );

  return $menu;
}

/**
 * Admin form for Bitcoin API Credentials
 */
function bitcoin_api_form() {
  $form = array();

  $form['bitcoin_api_apikey'] = array(
    "#type"          => "textfield",
    "#title"         => t("Bitcoin API Key"),
    "#default_value" => variable_get('bitcoin_api_apikey', ''),
  );

  return system_settings_form($form);
}
