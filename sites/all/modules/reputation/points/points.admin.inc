<?php

/*
 * Form for points management
 */
function points_form() {
  $form = array();

  $form['#description'] =
    '<div>
      <ul>
        <li> Machine Name - this value is to be used in other modules.
        <li> Name - this is human-readable name
        <li> Points - this is points value required to be able to perform the action
        <li> Type
        <li> Cost
      </ul>
    </div>';

  $points = points_get();
  $points[] = array();

  $points_used_actions = points_get_used_actions();

  $i = 0;
  foreach( $points as $mname => $point ) {
    $form['point-mname-'.$i] = array(
      "#type" => "textfield",
      "#title" => t("Machine Name"),
      "#value" => $point['mname'],
      "#size" => 12,
      '#prefix' => ($i==0?'<table>':'').'<tr><td>',
      '#suffix' => '</td>'
    );
    $used = in_array($point['mname'], $points_used_actions);
    $form['point-used-'.$i] = array(
      "#type" => "markup",
      "#value" => $used ? 'Used' : 'Not used',
      "#size" => 4,
      '#prefix' => '<td style="font-weight:bold; color:'.($used ? 'green' : 'red').'">',
      '#suffix' => '</td>',
      '#disabled' => true,
    );

    $form['point-name-'.$i] = array(
      "#type" => "textfield",
      "#title" => t("Action Name"),
      "#value" => $point['name'],
      "#size" => 20,
      '#prefix' => '<td>',
      '#suffix' => '</td>'
    );
    $form['point-points-'.$i] = array(
      "#type" => "textfield",
      "#title" => t("Required reputation"),
      "#value" => $point['points'],
      "#size" => 12,
      '#prefix' => '<td>',
      '#suffix' => '</td>'
    );
    $form['point-type-'.$i] = array(
      '#type' => 'select',
      '#title' => t('Type'),
      '#value' => $point['type'],
      '#options' => array(
        '0' => t('Lose'),
        '1' => t('Earn'),
      ),
      '#prefix' => '<td>',
      '#suffix' => '</td>'
    );
    $form['point-cost-'.$i] = array(
      "#type" => "textfield",
      "#title" => t("Reputation change"),
      "#value" => $point['cost'],
      "#size" => 12,
      '#prefix' => '<td>',
      '#suffix' => '</td>'
    );
    $form['point-id-'.$i] = array(
      "#type" => "hidden",
      "#value" => $point['mname'],
      '#prefix' => '<td>',
      '#suffix' => '</td>'
    );
    if( $i == count($points)-1 ) {
      $form["add"] = array(
        "#type" => "submit",
        "#value" => t("Add"),
        "#name" => 'add',
        '#prefix' => '<td colspan="2">',
        '#suffix' => '</td></tr></table>'
      );
    } else {
      $form["point-update-".$i] = array(
        "#type" => "submit",
        "#value" => t("Update"),
        "#name" => "point-update-".$i,
        '#prefix' => '<td>',
        '#suffix' => '</td>'
      );
      if( !$used ) {
        $form["point-delete-".$i] = array(
          "#type" => "submit",
          "#value" => t("Delete"),
          "#name" => "point-delete-".$i,
          '#prefix' => '<td>',
          '#suffix' => '</td></tr>'
        );
      } else {
        $form["point-update-".$i]['#prefix'] = '<td colspan="2">';
        $form["point-update-".$i]['#suffix'] = '</td></tr>';
      }
      $form['point-mname-'.$i]['#disabled'] = true;
    }
    $i++;
  }

  return $form;
}

/*
 * Validation of points_form
 */
function points_form_validate($form, $form_state) {
  $post = $form_state["clicked_button"]["#post"];
  if( $form_state["clicked_button"]["#name"] == 'add' ) {
    $points = points_get();
    $i = count($points);
    if( empty($post['point-mname-'.$i]) || isset($points[$post['point-mname-'.$i]]) ) {
      form_set_error('wrong_mname', t('Machine name should not be empty or duplicate'));
    }
  } else {
    if( preg_match('/-(\w+)-(\d+)$/', $form_state["clicked_button"]["#name"], $m) ) {
      $i = $m[2];
      if( $m[1] == 'delete' ) {
        $points_used_actions = points_get_used_actions();
        $used = in_array($post['point-mname-'.$i], $points_used_actions);
        if( $used ) {
          form_set_error('used_mname', t('Cannot delete used Action'));
        }
      }
    }
  }
  if( isset($i) ) {
    if( empty($post['point-name-'.$i]) ) {
      form_set_error('wrong_name', t('Name should not be empty'));
    }
    if( !is_numeric($post['point-points-'.$i]) ) {
      form_set_error('wrong_points', t('Reputation should be numeric'));
    }
    if( !is_numeric($post['point-cost-'.$i]) ) {
      form_set_error('wrong_price', t('Reputation change should be numeric'));
    }
  }
}

/*
 * Submission of points_form
 */
function points_form_submit($form, $form_state) {
  $post = $form_state["clicked_button"]["#post"];
  if( $form_state["clicked_button"]["#name"] == 'add' ) {
    $points = points_get();
    $i = count($points);
    point_add($post['point-mname-'.$i], $post['point-name-'.$i], $post['point-points-'.$i], $post['point-type-'.$i], $post['point-cost-'.$i]);
  } else {
    if( preg_match('/-(\w+)-(\d+)$/', $form_state["clicked_button"]["#name"], $m) ) {
      $i = $m[2];
      if( $m[1] == 'update' ) {
        point_update($post['point-id-'.$i], $post['point-name-'.$i], $post['point-points-'.$i], $post['point-type-'.$i], $post['point-cost-'.$i]);
      } else {
        point_delete($post['point-id-'.$i]);
      }
    }
  }
}