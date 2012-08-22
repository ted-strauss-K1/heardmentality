<?php

/*
 * Add the rank
 */
function rank_add($name, $points) {
  db_query("INSERT INTO {module_ranks} SET name = '%s', points = '%d'", $name, $points);
}

/*
 * Delete the rank
 */
function rank_delele($id) {
  db_query("DELETE FROM {module_ranks} WHERE id = '%d'", $id);
}

/*
 * Update the rank
 */
function rank_update($id, $name, $points) {
  db_query("UPDATE {module_ranks} SET name = '%s', points = '%d' WHERE id = '%d'", $name, $points, $id);
}


/*
 * Form for ranks management
 */
function ranks_form() {
  $form = array();

  $ranks = ranks_get();
  $ranks[] = array();
  foreach( $ranks as $i => $rank ) {
    $form['rank-name-'.$i] = array(
      "#type" => "textfield",
      "#title" => t("Rank name"),
      "#description" => t("Leave empty to delete"),
      "#value" => $rank['name'],
      "#size" => 40,
      '#prefix' => ($i==0?'<table>':'').'<tr><td>',
      '#suffix' => '</td>'
    );
    $form['rank-points-'.$i] = array(
      "#type" => "textfield",
      "#title" => t("Points"),
      "#value" => $rank['points'],
      "#size" => 12,
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>'.($i==count($ranks)-1 ? '</table>' : '')
    );
    $form['rank-id-'.$i] = array(
      "#type" => "hidden",
      "#value" => $rank['id'],
    );
  }
  $form["Save"] = array(
    "#type" => "submit",
    "#value" => t("Save"),
  );

  return $form;
}
/*
 * Validation of ranks_form
 */
function ranks_form_validate($form, $form_state) {
  $post = $form_state["clicked_button"]["#post"];
  $points = array();
  for( $i=0; $i>=0; $i++ ) {
    if( isset($post['rank-id-'.$i]) ) {
      if( in_array($post['rank-points-'.$i], $points) ) {
        form_set_error('duplicate_points', t('There should be no duplicate points values'));
      }
      $points[] = $post['rank-points-'.$i];
      if( !empty($post['rank-name-'.$i]) && !is_numeric($post['rank-points-'.$i]) ) {
        form_set_error('numeric_points', t('Points values should be numeric'));
      }
    } else break;
  }
}

/*
 * Submission of ranks_form
 */
function ranks_form_submit($form, $form_state) {
  $post = $form_state["clicked_button"]["#post"];
  for( $i=0; $i>=0; $i++ ) {
    if( isset($post['rank-id-'.$i]) ) {
      if( empty($post['rank-id-'.$i]) ) {
        if( !empty($post['rank-name-'.$i]) ) { # new
          rank_add($post['rank-name-'.$i], $post['rank-points-'.$i]);
        }
      } else {
        if( empty($post['rank-name-'.$i]) ) { # delete
          rank_delele($post['rank-id-'.$i]);
        } else { # update
          rank_update($post['rank-id-'.$i], $post['rank-name-'.$i], $post['rank-points-'.$i]);
        }
      }
    } else break;
  }
  users_ranks_update();
}