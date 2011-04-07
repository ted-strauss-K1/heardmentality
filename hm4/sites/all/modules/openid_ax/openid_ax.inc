<?php
// $Id: openid_ax.inc,v 1.11 2008/07/04 08:52:14 anshuprateek Exp $

/**
 * @file
 * OpenID Attribute Exchange utility functions.
 */

/**
 * openid_ax_request() could be a redundant function
 * TODO ANSHU Check at the end of code if we need this function
 */
function openid_ax_required($request) {
  if(in_array('http://openid.net/srv/ax/1.0',$request))
  return TRUE;
  else
  return FALSE;
}

/**
 * Process the $request to filter out the AX elements
 * Check if its a fetch or a store request
 *
 * @param $request
 *   Associative array of requests send to the OP
 * @return array
 *   The corresponding response message or nothing if openid.ax.mode is not set
 */
function openid_ax_process($request) {
  $alias = _openid_ax_namespace_alias($request);
  $request_ax = _openid_ax_namespace_request($request);
  if(isset($request_ax[openid.$alias.mode])) {
    	switch($request_ax[openid.$alias.mode]) {
    	  case 'fetch_request':
            $response_ax = openid_ax_fetch_request($request_ax);
            module_load_include('pages.inc','openid_ax');
            return drupal_get_form('openid_ax_form',$response_ax);
            break;
          case 'store_request':
            return openid_ax_store_request($request_ax);
            break;
    	}
  }
  //if openid.ax.mode is not set, do nothing
  return;
}

/**
 * Find out the AX namespace alias used by the Relying Party
 * @param $request
 *   Associative array of requests send to the OP
 * @return .alias.
 *   A string containing initial and trailing dots.
 */
function _openid_ax_namespace_alias($request) {
  foreach($request as $key => $val) {
  	$request[$key] = urldecode($val);
  }	
  $alias_key = array_search('http://openid.net/srv/ax/1.0',$request);
  if(isset($request['openid.return_to'])) {
    $_SESSION['openid_ax']['return_to'] = $request['openid.return_to'];
  }
  $alias = strrchr($alias_key,'.');//returns .alias
  $alias .= '.';
  return $alias;
}

/**
 * Separate the AX requests from the rest of $request
 * @param $request
 *   Associative array of requests send to the OP
 * @return
 *   Associative array with only requests containing openid.ns.axalias
 */
function _openid_ax_namespace_request($request) {
  foreach($request as $key => $val) {
  	$request[$key] = urldecode($val);
  }	
  $alias_key = array_search('http://openid.net/srv/ax/1.0',$request);
  $request_ax = array();
  $request_ax[$alias_key] = $request[$alias_key];
  $alias = _openid_ax_namespace_alias($request);
  foreach($request as $var=>$val) {
    if(strpos($var,$alias)) {
      $request_ax[$var] = $val;
    }
  }
  return $request_ax;
}

/**
 * Get the list of attribute identifiers from $request_ax
 * @param $request_ax
 *   Associative array with only requests containing openid.ns.axalias
 * @return
 *   Array containing placeholder URI of the identifiers.
 *   It has been escaped here otherwise difficult to escape and form a proper SQL query
 *   later using inbuilt drupal functions.
 * */
function _openid_ax_identifiers($request_ax) {
  $alias = _openid_ax_namespace_alias($request_ax);
  $identifier = array();
  foreach($request_ax as $var=>$val) {
  	if(strpos($var,'type')) {
  	  $identifier[] = mysql_escape_string($val);
  	}
  }
  return $identifier;
}

/**
 * Get the ax_id from table openid_ax_attributes
 * @param $identifier
 *   Array containing placeholder URI of the identifiers
 * @return
 *   Associative array containing requested identifers=>ax_id
 * */
function _openid_ax_id($identifier) {
  $identifiers = (implode("','",$identifier));
  $identifiers_id = db_query("SELECT * FROM {openid_ax_attributes} WHERE identifier IN ('$identifiers')");
  while($row = db_fetch_array($identifiers_id)) {
  	$attr_axid[$row['identifier']] = $row['ax_id'];
  }

  return $attr_axid;
}

/**
 *Process the fetch_request calls.
 * @param array $request
 *   Request array containing the fetch_request
 * @return array
 *   fetch_response
 */
function openid_ax_fetch_request($request_ax) {
  global $user;

  // If the user is not yet logged in, redirect to the login page before continuing.
  if (!$user->uid) {
    $_SESSION['openid_ax']['request'] = $request_ax;
    drupal_goto('user/login', 'destination=openid/ax/continue');
  }
  $attr_axid = _openid_ax_id(_openid_ax_identifiers($request_ax));
  $values = db_query("SELECT a.ax_values, ax_id FROM {openid_ax_values} a WHERE uid=%d AND ax_id IN (".implode(",",$attr_axid).")",$user->uid);
  $axid_value = array();
  while($axvalues = db_fetch_array($values)) {
  	$axid_value[] = $axvalues['ax_id'];
  	$attribute_value[] = $axvalues['ax_values'];
  }
  $ax_response = array();
  $alias = _openid_ax_namespace_alias($request_ax);
  $alias_key = array_search('http://openid.net/srv/ax/1.0',$request_ax);
  $ax_response[$alias_key] = $request_ax[$alias_key];
  $ax_response['openid'.$alias.'mode'] = 'fetch_response';
  $count_alias = array();
  foreach($request_ax as $var=>$val) {
    if(strpos($var,'type')) {
  	  $ax_response[$var] = $val;
  	}
  	elseif(strpos($var,'count')) {
  	  $count_alias[strrchr($var,'.')] = $val;
  	}
  }
  foreach($request_ax as $var=>$val) {
  	$response_val = array();
  	$key_value = (str_replace('type','value',$var));
  	$key_count = (str_replace('type','count',$var));
  	$axid_keys = array_keys($axid_value,$attr_axid[$val]);
  	if(count($axid_keys)>1) {
  	  foreach($axid_keys as $key) {
  	    $response_val[] = $attribute_value[$key];
  	  }
  	}
  	else {
  	  $response_val[] = $attribute_value[$axid_keys[0]];
  	}
  	if(strpos($var,'type')) {
  	  $attr_alias = strrchr($var,'.');
  	  //If a value was not supplied or available from the user,
  	  //the associated "openid.ax.value.<alias>" field SHOULD NOT be included by the OP in the fetch response.
  	  //An "openid.ax.count.<alias>" with a value of "0" together with its corresponding
  	  //"openid.ax.type.<alias>" field MAY be included to explicitly state
  	  //that no values are provided for an attribute.
  	  if($response_val[0] != ''||1) {//TODO Check what conditions to be used here!
	  	//The name of array_key_exists() function is key_exists() in PHP 4.0.6. Drupal requires min 4.3.3
	  	if((array_key_exists($attr_alias,$count_alias))===FALSE) {
		  $ax_response[$key_value] = $response_val[0];
	  	}
	  	else {
	  	  $num = count($response_val);
	  	  //OpenID Providers MAY return less than or the exact number of values speficied by this field
	  	  //for the associated attribute,
	  	  //but MUST NOT return more than the number of requested values for the attribute.
	 	  if($count_alias[$attr_alias] != 'unlimited') {
	  	    ($num>($count_alias[$attr_alias]))?$num = $count_alias[$attr_alias]:$num;
	 	  }
	 	  $ax_response[$key_count] = $num;
	 	  for($i=0;$i<$num;$i++) {
	 		$ax_response[$key_value.'.'.($i+1)] = $response_val[$i];
	 	  }
	  	}
  	  }
  	  else {
  	  	$ax_response[$key_count] = 0;
  	  }
    }
  }
  return $ax_response;
}

/**
 * Process the store_request
 * @param $request_ax
 *   http request only containing the AX namespace alias
 * @return $ax_response
 *   store_response
 */
function openid_ax_store_request($request_ax) {
  global $user;
  // If the user is not yet logged in, redirect to the login page before continuing.
  if (!$user->uid) {
    $_SESSION['openid_ax']['request'] = $request_ax;
    drupal_goto('user/login', 'destination=openid/ax/continue');
  }
  return drupal_get_form('openid_store_info_form',$request_ax);
}

function openid_store_info_form(&$form_state, &$request_ax) {
  $form = array();
  $realm = $form_state['post']['openid_realm'];
  $form['intro'] = array(
    '#type' => 'markup',
    '#value' => t('%site is requesting to store the following information into your profile. You want to continue?', array('%site' => $realm))  
  );
  foreach($request_ax as $key => $value) {
  	if(strstr($key,'value')){
	  $form[$key] = array(
	    '#type' => 'textfield',
	    '#title' => t(substr(strrchr($key,'value.'),6)),
	    '#value' => $value,
	    '#size' => 14,
	    '#maxlength' => 100
	  );
    }
    else {
      $form[$key] = array(
	    '#type' => 'hidden',
	    '#title' => $key,
	    '#value' => $value
	  );
    }
  }
  $essentials = array(
    'openid.return_to' => $form_state['post']['openid.return_to'],
    'openid.realm' => $realm
  );
  foreach($essentials as $key => $value) {
  	$form[$key] = array (
      '#type' => 'hidden',
      '#name' => $key,
      '#value' => $value
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#submit' => array('openid_store_info_form_submit')
  );
  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#submit' => array('openid_store_info_form_submit_cancel')
  );
  return $form;
}

function openid_store_info_form_submit(&$form, $form_state) {
  return openid_ax_store_process($form_state['values']);
}

function openid_store_info_form_submit_cancel(&$form, $form_state) {
  $user_agreed = FALSE;
  return openid_ax_store_process($form_state['values'], $user_agreed);
}

function openid_ax_store_process($form_state, $user_agreed = TRUE) {
  global $user;
  $request_ax = $form_state;
  $alias = _openid_ax_namespace_alias($request_ax);
  if($user_agreed){  
    $attr_axid = _openid_ax_id(_openid_ax_identifiers($request_ax));
    foreach($request_ax as $var=>$val) {
  	  $attr_alias = strrchr($var,'.');
  	  if(strpos($var,'type')) {
  	    $ax_values[$attr_axid[$val]] = $attr_alias;
  	  }
  	  elseif(strpos($var,'count')) {
  	    $count_alias[$attr_alias] = $val;
  	  }
  	  elseif(strpos($var,'value')) {
	    if(!(strpos(substr(strstr($var,'value.'),6),'.'))) {
          $ax_values[array_search($attr_alias,$ax_values)] = $val;
  	    }
  	    else {
  	  	  $attr_alias_count = $attr_alias;
  	  	  $count_pos = strrpos($var,$attr_alias);
  	  	  $var1 = substr($var,0,$count_pos);
  	  	  $attr_alias = strrchr($var1,'.');
  	  	  $ax_values[array_search($attr_alias,$ax_values).$attr_alias_count] = $val;
  	  	  $to_remove[] = array_search($attr_alias,$ax_values);
  	    }
  	  }
    }
    foreach($to_remove as $del) {
  	  unset($ax_values[$del]);
    }
    foreach($ax_values as $ax_id=>$value) {
  	  $value = trim($value);
  	  if($value != '') {
  	   $res = db_query("INSERT INTO {openid_ax_values} (ax_id, uid, ax_values) VALUES ('%d','%d','%s')",$ax_id,$user->uid,$value);
  	   if($res) {
  	 	  $result[] = $res;
  	   }
  	  }
    }
    $alias_key = array_search('http://openid.net/srv/ax/1.0',$request_ax);
    $ax_store_response[$alias_key] = $request_ax[$alias_key];
    if(count($result) == count($ax_values)) {
      $ax_store_response['openid'.$alias.'mode'] = 'store_response_success';
    }
    else {
      $ax_store_response['openid'.$alias.'mode'] = 'store_response_failure';
    }
  }
  else {
  	$alias_key = array_search('http://openid.net/srv/ax/1.0',$request_ax);
    $ax_store_response[$alias_key] = $request_ax[$alias_key];
  	$ax_store_response['openid'.$alias.'mode'] = 'store_response_failure';
  }
  $destination = ($request_ax['openid.return_to'] != '')?$request_ax['openid.return_to']:$request_ax['openid.realm'];
  drupal_goto($destination, $ax_store_response) ;
  
}

function openid_ax_fetch_response($response) {
  $alias = _openid_ax_namespace_alias($response);
  $ax_user_response = _openid_ax_namespace_request($response);
  /*foreach($ax_user_response as $var => $val) {
  	if($val == '') {
  		$ax_key = substr(strstr($var,'value.'),6);
  		if(!(strpos($ax_key,'.'))) {
  		  unset($ax_user_response[$var]);
  		  $ax_user_response[str_replace('value','count',$var)] = 0;
  		}
  		else {
  		  $request_process[$var] = $ax_key;
  		}
  	}
  }
  if(is_array($request_process)) {
    foreach($request_process as $key => $value) {
      $count_key = str_replace('value','count',$key);
      $count_key = substr($count_key,0,strrpos($count_key,'.'));
		$keybase = substr($key,0,strrpos($key,'.'));
		while(array_key_exists($key,$ax_user_response)&&($ax_user_response[$key]==''))
		{
			$count = $ax_user_response[$count_key];
			$ax_user_response[$key] = $ax_user_response[$keybase.'.'.$count];
			unset($ax_user_response[$keybase.'.'.$count]);
			$ax_user_response[$count_key] = $count-1;
		}
    }
  }*/
  foreach($ax_user_response as $key => $val) {
	if(strpos($key,'value.')) {
	  //value.alias.1 or value.alias format
	  $var_name = substr(strstr($key,'value.'),6);
	  if(strpos($var_name,'.')) {
	    $var_name_pure = substr($var_name,0,strpos($var_name,'.'));
	  }
	  else {
	    $var_name_pure = $var_name;
	  }
	  $property_count[$var_name_pure]++;
	}
  }
  if(strstr($response['op'],'No')) {
  	foreach($property_count as $property => $value) {
	  if($value == 1) {
        unset($ax_user_response['openid'.$alias.'value.'.$property]);
		$ax_user_response['openid'.$alias.'count.'.$property] = 0;
	  }
	  else {
		for($key=0;$key<$value;$key++) {
		  unset($ax_user_response['openid'.$alias.'value.'.$property.'.'.($key+1)]);
		}
	    $ax_user_response['openid'.$alias.'count.'.$property] = 0;
	  }
  	}
  }
  else{
	foreach($property_count as $property => $value) {
	  if($value == 1) {
		if($ax_user_response['openid'.$alias.'value.'.$property]=='') {
		  unset($ax_user_response['openid'.$alias.'value.'.$property]);
		  $ax_user_response['openid'.$alias.'count.'.$property] = 0;
	    }
	  }
	  else {
		//$property_set_indexes = indexes of all value.alias.num's which are != ''
		$new_key=0;$old_key=0;
		for(;$old_key<=$value;$old_key++) {
		  if(trim($ax_user_response['openid'.$alias.'value.'.$property.'.'.$old_key]) != '') {
		    $property_set_indexes[$new_key]=$old_key;
		    $new_key++;
		  }
		}
		if($new_key != $old_key) {
		  for($key=0;$key<$new_key;$key++) {
			$ax_user_response['openid'.$alias.'value.'.$property.'.'.($key+1)] = $ax_user_response['openid'.$alias.'value.'.$property.'.'.$property_set_indexes[$key]];
		  }
		  for($key=0;$key<$old_key-$new_key;$key++) {
		    unset($ax_user_response['openid'.$alias.'value.'.$property.'.'.($new_key+$key+1)]);
		  }
	      $ax_user_response['openid'.$alias.'count.'.$property] = $new_key;
	    }
	  }
	}
  }
  return $ax_user_response;
}
?>