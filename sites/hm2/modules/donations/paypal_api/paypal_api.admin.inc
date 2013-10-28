<?php

/**
 * Define permissions
 */
define('PAYPAL_ADMIN', 'Administer Paypal API Credentials');

/**
 * Implementation of hook_perm()
 */
function paypal_api_perm()
{
  return array(PAYPAL_ADMIN);
}

/**
 * Implementation of hook_menu()
 */
function paypal_api_menu()
{
  $menu = array();

  $menu['admin/settings/donations/paypal_api'] = array(
    'title' => t('Paypal API'),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('paypal_api_form'),
    'access arguments' => array(PAYPAL_ADMIN),
    'type'              => MENU_LOCAL_TASK,
    'weight'            => -9,
  );

  return $menu;
}

/**
 * Admin form for Paypal API Credentials
 */
function paypal_api_form()
{
  $form = array();

  $form['user'] = array(
    "#type" => "textfield",
    "#title" => t("PayPal API user name"),
    "#value" => variable_get('paypal_api_user', ''),
  );
  $form['pwd'] = array(
    "#type" => "textfield",
    "#title" => t("PayPal API password"),
    "#value" => variable_get('paypal_api_pwd', ''),
  );
  $form['signature'] = array(
    "#type" => "textfield",
    "#title" => t("PayPal API signature string"),
    "#value" => variable_get('paypal_api_signature', ''),
  );
  $form['live'] = array(
    '#type' => 'checkbox',
    '#title' => t('Live mode'),
    '#value' => variable_get('paypal_api_live', FALSE),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

/**
 * Admin form for Paypal API Credentials - Submission
 */
function paypal_api_form_submit($form, $form_state)
{
  $post = $form_state["clicked_button"]["#post"];
  variable_set('paypal_api_user', $post['user']);
  variable_set('paypal_api_pwd', $post['pwd']);
  variable_set('paypal_api_signature', $post['signature']);
  variable_set('paypal_api_live', (bool)$post['live']);
}