<?php
// $Id: openid_ax.pages.inc,v 1.8 2008/07/04 05:44:58 anshuprateek Exp $

/**
 * @file
 * Page callbacks for OpenID AX.
 */

/**
 * Primary endpoint callback - serves op_endpoint.
 *
 * @param array $request (Optional) request parameters.
 */
function openid_ax_endpoint($request = array()) {
  module_load_include('inc', 'openid');
  module_load_include('inc', 'openid_ax');
  if (count($request) == 0) {
    $request = _openid_response();
  }
  $ax_request = openid_ax_process($request);
  return $ax_request;
}

/**
 * Menu callback to continue authentication process after user login. This
 * callback is encountered when a user tries to login to an RP but does not yet
 * have a valid local session
 */
function openid_ax_continue() {
  if (isset($_SESSION['openid_ax']['request'])) {
    $request_ax = $_SESSION['openid_ax']['request'];
    unset($_SESSION['openid_ax']['request']);
    return openid_ax_endpoint($request_ax);
  }
  else {
    drupal_set_message(t('Session expired'));
    drupal_goto();
  }
}

/**
 * Page callback for processing openid_ax_send.
 */
function openid_ax_send() {
  module_load_include('inc', 'openid');
  module_load_include('inc', 'openid_ax');
  $response = _openid_response();
  $ax_response = openid_ax_fetch_response($response);
  drupal_goto($_SESSION['openid_ax']['return_to'],$ax_response);
}

/**
 *Form for user interaction before sending AX values to RP
 */
function openid_ax_form(&$form_state,&$ax_response) {
  global $user;
  $form_state['ax_response'] = $ax_response;
  $realm = $form_state['post']['openid_realm'];
  $form = array();
  $form['intro'] = array(
    '#type' => 'markup',
    '#value' => '<p>'. t('Your following details are being send to %site, would you like to continue?', array('%site' => $realm)) . '</p>'
  );
  foreach($ax_response as $name=>$value) {
  	if(strstr($name,'value')){
	  $form[$name] = array(
	    '#type' => 'textfield',
	    '#title' => t(substr(strrchr($name,'value.'),6)),
	    '#value' => $value,
	    '#size' => 14,
	    '#maxlength' => 100
	  );
    }
    else {
      $form[$name] = array(
	    '#type' => 'hidden',
	    '#title' => $name,
	    '#value' => $value
	  );
    }
  }

  $form['#action'] = url('openid/ax/send');

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Yes; Send my data'),
  );
  
  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('No! Don\'t send my data'),
    '#submit' => array('openid_ax_form_submit_cancel')
  );

  return $form;


}

function openid_ax_persona() {
  return drupal_get_form('openid_ax_persona_form');
}

/**
 *Form for creating/editing a persona
 */
function openid_ax_persona_form() {
  global $user;
  $form = array();
  $identifiers = db_query("SELECT * FROM {openid_ax_attributes}");
  $ax_values = db_query("SELECT * FROM {openid_ax_values} WHERE uid=%d",$user->uid );
  while($row = db_fetch_array($ax_values)) {
  	$persona_value[$row['ax_id']] = $row['ax_values'];
  }

  while($row = db_fetch_array($identifiers)) {
  	$form[$row['ax_id']] = array(
	    '#type' => 'textfield',
	    '#title' => t($row['identifier']),
	    '#default_value' => $persona_value[$row['ax_id']],
	    '#size' => 25,
	    '#maxlength' => 100
	);
	if(isset($persona_value[$row['ax_id']])) {
	  $form['has_value'.$row['ax_id']] = array(
		'#type' => 'hidden',
	  );
	  $form['intro'] = array(
	    '#type' => 'markup',
	    '#value' => t('To delete a value, delete the value in the particular field and then submit'),
	    '#weight' => -1
      );
	}

  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

function openid_ax_persona_form_submit(&$form, $form_state) {
  global $user;
  $result = db_query("SELECT ax_id FROM {openid_ax_attributes}");
  //difficult to use INSERT ... ON DUPLICATE KEY UPDATE
  // as there is no unique key
  static $success;
  while($ax_id = db_fetch_array($result)) {
    $ax_value = trim($form_state['values'][$ax_id['ax_id']]);
    if($ax_value != ''||(isset($form_state['values'][has_value.$ax_id['ax_id']]))){
	  if(!db_result(db_query("SELECT * FROM {openid_ax_values} WHERE uid=%d AND ax_id=%d", $user->uid,$ax_id['ax_id']))) {//TODO add persona support
	    $success = db_query("INSERT INTO {openid_ax_values} (uid,ax_id,ax_values) VALUES ('%d','%d','%s')", $user->uid,$ax_id['ax_id'],$ax_value);
	  }
	  else {
	  	if($ax_value != '') {
          $success = db_query("UPDATE {openid_ax_values} SET ax_values='%s' WHERE ax_id=%d AND uid=%d",$form_state['values'][$ax_id['ax_id']],$ax_id['ax_id'],$user->uid);
	  	}
	  	else {
	  	  $success = db_query("DELETE FROM {openid_ax_values} WHERE ax_id=%d AND uid=%d",$ax_id['ax_id'],$user->uid);
	  	}
  	  }
    }
  }
  if($success) {
  	drupal_set_message("Your persona values have been saved.");
  }
}
