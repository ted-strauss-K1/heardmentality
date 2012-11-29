<?php

/*
 * Administer UserPoint Extension Actions Form
 */
function up_actions_admin()
{
  $form = array();

  $actions = up_actions();
  foreach ($actions as $mname => $action) {
    $form[$mname] = array(
      "#type" => "fieldset",
      "#collapsible" => true,
      "#collapsed" => false,
    );
    $form_item = _up_actions_admin_row($mname, $action);
    foreach ($form_item as $key => $value) {
      $form[$mname][$key] = $value;
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    "#name" => 'form_save',
  );

  return $form;
}

/*
 * Row for  Administer UserPoint Extension Actions Form
 */
function _up_actions_admin_row($mname, $action)
{
  $form = array();

  $form['mname-' . $mname] = array(
    "#type" => "hidden",
    "#value" => $mname,
  );
  $form['name-' . $mname] = array(
    "#type" => "textfield",
    "#title" => t("Name"),
    "#value" => $action['name'],
    "#size" => 40,
    '#prefix' => '<table><tr><td>',
    '#suffix' => '</td>'
  );
  $form['reputation-' . $mname] = array(
    "#type" => "textfield",
    "#title" => t("Reputation limit"),
    "#value" => $action['reputation'],
    "#size" => 12,
    '#prefix' => '<td>',
    '#suffix' => '</td>'
  );
  $form['type-' . $mname] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#value' => $action['type'],
    '#options' => up_actions_types(),
    '#prefix' => '<td>',
    '#suffix' => '</td>'
  );
  $form['points-' . $mname] = array(
    "#type" => "textfield",
    "#title" => t("Points"),
    "#value" => $action['points'],
    "#size" => 12,
    '#prefix' => '<td>',
    '#suffix' => '</td>'
  );
  $form['status-' . $mname] = array(
    '#type' => 'select',
    '#title' => t('Status'),
    '#value' => $action['status'],
    '#options' => up_actions_statuses(),
    '#prefix' => '<td>',
    '#suffix' => '</td>'
  );
  $form['default-' . $mname] = array(
    '#type' => 'submit',
    '#value' => t('Default values'),
    "#name" => 'default-' . $mname,
    '#prefix' => '<td>',
    '#suffix' => '</td>'
  );

  return $form;
}

/*
 * Administer UserPoint Extension Actions Form Validate
 */
function up_actions_admin_validate($form, $form_state)
{
  $post = $form_state["clicked_button"]["#post"];
  $actions = up_actions_defined();
  foreach ($actions as $mname => $action) {
    if (empty($post['name-' . $mname])) {
      form_set_error('up_actions_wrong_name', t('Names should not be empty'));
    }
    if (!is_numeric($post['reputation-' . $mname]) || $post['reputation-' . $mname] < 0
      || !is_numeric($post['points-' . $mname]) || $post['points-' . $mname] < 0
    ) {
      form_set_error('up_actions_wrong_numbers', t('Reputation value and Points should be numeric and not negative'));
    }
  }
}

/*
 * Administer UserPoint Extension Actions Form Submit
 */
function up_actions_admin_submit($form, $form_state)
{
  $post = $form_state["clicked_button"]["#post"];
  $button_clicked = $form_state["clicked_button"]["#name"];
  if ($button_clicked != 'form_save') {
    $mname = preg_replace('/default-/', '', $button_clicked);
    up_actions_cache_clean($mname);
    return;
  }

  $actions = up_actions_defined();
  $cache = array();
  foreach ($actions as $mname => $action) {
    $_action = array(
      'name' => $post['name-' . $mname],
      'reputation' => $post['reputation-' . $mname],
      'type' => $post['type-' . $mname],
      'points' => $post['points-' . $mname],
      'status' => $post['status-' . $mname],
    );
    if (!up_actions_compare($action, $_action)) {
      $cache[$mname] = $_action;
    }
  }
  up_actions_cache($cache);
}

/*
 * UserPoint Extension Actions Export Form
 */
function up_actions_export()
{
  $form = array();

  $form['export'] = array(
    "#type" => "textarea",
    "#title" => t("Export"),
    "#value" => json_encode(up_actions()),
    "#size" => 80,
  );

  return $form;
}

/*
 * UserPoint Extension Actions Import Form
 */
function up_actions_import()
{
  $form = array();

  $form['import'] = array(
    "#type" => "textarea",
    "#title" => t("Import"),
    "#value" => '',
    "#size" => 80,
  );

  $form["submit"] = array(
    "#type" => "submit",
    "#value" => t("Run Import"),
  );

  return $form;
}

/*
 * UserPoint Extension Actions Import Form Validate
 */
function up_actions_import_validate($form, $form_state)
{
  $post = $form_state["clicked_button"]["#post"];
  $value = $post['import'];
  $data = json_decode($value);
  if (json_last_error() != JSON_ERROR_NONE || !is_array($data)) {
    form_set_error('up_actions_wrong_import', t('Wrong input'));
  }
}

/*
 * UserPoint Extension Actions Import Form Submit
 */
function up_actions_import_submit($form, $form_state)
{
  $post = $form_state["clicked_button"]["#post"];
  $value = $post['import'];
  $data = json_decode($value);
  up_actions_cache($data);
}











