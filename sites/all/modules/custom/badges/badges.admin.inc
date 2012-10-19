<?php

/*
 * Badge add
 */
function badge_add($name, $info, $type, $status) {
  db_query("
    INSERT INTO {module_badges}
    SET name = '%s', info = '%s', type = '%d', status = '%d'",
    $name, $info, $type, $status
  );
}

/*
 * Badge update
 */
function badge_update($id, $name, $info, $type, $status) {
  db_query("
    UPDATE {module_badges}
    SET name = '%s', info = '%s', type = '%d', status = '%d' WHERE id = '%d'",
    $name, $info, $type, $status, $id
  );
}

/*
 * Badge delete
 */
function badge_delete($id) {
  db_query("DELETE FROM {module_badges} WHERE id = '%d'", $id);
}

/*
 * Form for badges management
 */
function badges_form() {
  $form = array();

  $badges = badges_get();
  $badge_types = badges_types();

  $badges[] = array();

  foreach( $badges as $i => $badge ) {
    $form['badge-fname-'.$i] = array(
      "#type" => "markup",
      "#value" => t('Processing function').": ".($badge['fname']?$badge['fname'].'()':'Not defined'),
      "#size" => 10,
      '#prefix' => ($i==0?'<table>':'').'<tr><td>',
      '#suffix' => '</td>'
    );
    $form['badge-used-'.$i] = array(
      "#type" => "markup",
      "#value" => $badge['implemented'] ? 'Exists' : 'Doesn\'t exist',
      "#size" => 4,
      '#prefix' => '<td style="font-weight:bold; color:'.($badge['implemented'] ? 'green' : 'red').'">',
      '#suffix' => '</td>',
      '#disabled' => true,
    );
    $form['badge-name-'.$i] = array(
      "#type" => "textfield",
      "#title" => t("Badge Name"),
      "#value" => $badge['name'],
      "#size" => 20,
      '#prefix' => '<td>',
      '#suffix' => '</td>'
    );
    $form['badge-info-'.$i] = array(
      "#type" => "textfield",
      "#title" => t("Badge Info"),
      "#value" => $badge['info'],
      "#size" => 40,
      '#prefix' => '<td>',
      '#suffix' => '</td>'
    );
    $form['badge-type-'.$i] = array(
      '#type' => 'select',
      '#title' => t('Type'),
      '#value' => $badge['type'],
      '#options' => $badge_types,
      '#prefix' => '<td>',
      '#suffix' => '</td>'
    );
    $form['badge-status-'.$i] = array(
      '#type' => 'select',
      '#title' => t('Status'),
      '#value' => $badge['status'] === 0 ? 0 : 1,
      '#options' => array(
        0 => 'Off',
        1 => 'On',
      ),
      '#default_value' => 1,
      '#prefix' => '<td>',
      '#suffix' => '</td>'
    );
    $form['badge-id-'.$i] = array(
      "#type" => "hidden",
      "#value" => $badge['id'],
      '#prefix' => '<td>',
      '#suffix' => '</td>'
    );
    if( $i == count($badges)-1 ) {
      $form["add"] = array(
        "#type" => "submit",
        "#value" => t("Add"),
        "#name" => 'add',
        '#prefix' => '<td colspan="2">',
        '#suffix' => '</td></tr></table>'
      );
    } else {
      $form["badge-update-".$i] = array(
        "#type" => "submit",
        "#value" => t("Update"),
        "#name" => "badge-update-".$i,
        '#prefix' => '<td>',
        '#suffix' => '</td>'
      );
      $form["badge-delete-".$i] = array(
        "#type" => "submit",
        "#value" => t("Delete"),
        "#name" => "badge-delete-".$i,
        '#prefix' => '<td>',
        '#suffix' => '</td></tr>'
      );
    }
  }

  return $form;
}

/*
 * Validation of badges_form
 */
function badges_form_validate($form, $form_state) {
  $post = $form_state["clicked_button"]["#post"];
  $badges = badges_get();
  $fnames = array();
  foreach($badges as $badge) {
    $fnames[] = $badge['fname'];
  }
  if( $form_state["clicked_button"]["#name"] == 'add' ) {
    $i = count($badges);
    if( empty($post['badge-name-'.$i]) ) {
      form_set_error('wrong_name', t('Name should not be empty'));
    }
    if( in_array($fname = badge_process_fn($post['badge-name-'.$i]), $fnames) ) {
      form_set_error('wrong_fname', t('Process function name '.$fname.'() cannot be used twice'));
    }
  } else {
    if( preg_match('/-(\w+)-(\d+)$/', $form_state["clicked_button"]["#name"], $m) ) {
      $i = $m[2];
      if( $m[1] == 'update' ) {
        if( empty($post['badge-name-'.$i]) ) {
          form_set_error('wrong_name', t('Name should not be empty'));
        }
        unset($fnames[$i]);
        if( in_array($fname = badge_process_fn($post['badge-name-'.$i]), $fnames) ) {
          form_set_error('wrong_fname', t('Process function name '.$fname.'() cannot be used twice'));
        }
      }
    }
  }
}

/*
 * Submission of badges_form
 */
function badges_form_submit($form, $form_state) {
  $post = $form_state["clicked_button"]["#post"];
  if( $form_state["clicked_button"]["#name"] == 'add' ) {
    $badges = badges_get();
    $i = count($badges);
    badge_add($post['badge-name-'.$i], $post['badge-info-'.$i], $post['badge-type-'.$i], $post['badge-status-'.$i]);
  } else {
    if( preg_match('/-(\w+)-(\d+)$/', $form_state["clicked_button"]["#name"], $m) ) {
      $i = $m[2];
      if( $m[1] == 'update' ) {
        badge_update($post['badge-id-'.$i], $post['badge-name-'.$i], $post['badge-info-'.$i], $post['badge-type-'.$i], $post['badge-status-'.$i]);
      } else {
        badge_delete($post['badge-id-'.$i]);
      }
    }
  }
}


/*
 * Badges Export Form
 */
function badges_export() {
  $form = array();

  $form['export'] = array(
    "#type" => "textarea",
    "#title" => t("Export"),
    "#value" => json_encode(badges_get()),
    "#size" => 80,
  );

  return $form;
}

/*
 * Badges Import Form
 */
function badges_import() {
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
 * Badges Import Form Validate
 */
function badges_import_validate($form, $form_state) {
  $post = $form_state["clicked_button"]["#post"];
  $value = $post['import'];
  $data = json_decode($value);
  if (json_last_error() != JSON_ERROR_NONE || !is_array($data)) {
    form_set_error('badges_wrong_import', t('Wrong input'));
  }
}

/*
 * Badges Import Form Submit
 */
function badges_import_submit($form, $form_state) {
  $post = $form_state["clicked_button"]["#post"];
  $value = $post['import'];
  $data = json_decode($value);
  # Run inport
  $badges = badges_get();
  foreach ($badges as $badge) {
     badge_delete($badge['id']);
  }
  foreach ($data as $badge) {
    badge_add( $badge['name'], $badge['info'], $badge['type'], $badge['status'] );
  }
}