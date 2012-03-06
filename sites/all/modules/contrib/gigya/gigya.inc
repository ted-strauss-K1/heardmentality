<?php

/**
 * @file
 */

/**
 * Undocumented Function!
 */
function gigya_execute_replacement(&$value, $key, $params) {
  extract($params);

  switch ($type) {
    case 'node':
      $full_object = node_load($object->nid);
      break;
    case 'comment':
      $full_object = _comment_load($object->cid);
      break;
    case 'user':
      $full_object = user_load($object->uid);
      break;
  }

  if (is_string($value)) {
    if (module_exists('token')) {
      foreach ($token_types as $token_type) {
        if ($type == 'comment' && $token_type == 'node') {
          $the_object = node_load($object->nid);
        }
        else {
          $the_object = $full_object;
        }
        $value = token_replace($value, $token_type, $the_object);
      }
    }
    $value = strtr($value, $replacements);
  }
}

/**
 * Callback for array_walk.
 *
 * Receives form items and assesses whether or not they're input fields.
 * If so, then it tries to set the default value based on the
 * profile mappings.
 *
 * @see gigya_form_alter() in gigya.module.
 */
function gigya_apply_profile_mapping(&$field, $key) {
  if (module_exists('token')) {
    if (is_array($field)) {
      // Check for some key elements. We do this explicitly to make sure the
      // indexes are defined and avoid PHP notices.
      $type = isset($field['#type']) ? $field['#type'] : '';
      $field_name = isset($field['#field_name']) ? $field['#field_name'] : '';
      $theme = isset($field['#theme']) ? $field['#theme'] : '';

      // Is it a standard type to replace?
      if (in_array($type, array('checkbox', 'checkboxes', 'date', 'radio', 'radios', 'select', 'textarea', 'textfield'))) {
        $field['#default_value'] = token_replace(variable_get('gigya_map_' . $key, $field['#default_value']), 'gigya');
      }
      // If it isn't and we have a #field_name, just go for it.
      elseif ($field_name && $type) {
        $field['#default_value']['value'] = token_replace(variable_get('gigya_map_' . $field['#field_name'], ''), 'gigya');
      }
      // If it is a fieldset or multi-value field, drill in.
      elseif ($type == 'fieldset' || $theme == 'content_multiple_values') {
        array_walk($field, 'gigya_apply_profile_mapping');
      }
    }
  }
}

/**
 * Undocumented Function!
 */
function gigya_delete_profile($uid) {
  gigya_unlink_accounts($uid, $uid);
  return TRUE;
}

/**
 * Undocumented Function!
 */
function gigya_get_loginprovider($uid) {
  return FALSE;
}

/**
 * Undocumented Function!
 */
function gigya_avatar_check($uid) {
  $bio = gigya_get_user_info($uid);
  if ($bio['thumbnailURL'])
    return $bio['thumbnailURL'];
  elseif ($bio['photoURL'])
    return $bio['photoURL'];
  else {
    return FALSE;
  }
}

/**
 * Undocumented Function!
 */
function gigya_save_userpic($uid) {
  // Get Facebook user picture's url.
  if ($avatar = gigya_avatar_check($uid)) {
    $result = drupal_http_request($avatar);

    if ($result->code != 200) {
      watchdog('gigya', 'Failed importing user avatar for @uid, code : @code',
      array('@uid' => $uid, '@code' => $result->code));
      return FALSE;
    }

    $filename = 'picture-gigya_'. $uid .'.jpg';
    $dest = file_directory_path();
    if (variable_get('user_picture_path', '')) {
      $dest .= '/' . variable_get('user_picture_path', '');
    }
    $dest .= '/' . $filename;

    $file = file_save_data($result->data, $dest, FILE_EXISTS_REPLACE);
    // Resizing
    list($width, $height) = sscanf(variable_get('user_picture_dimensions', '85x85'), '%dx%d');
    image_scale_and_crop($file, $dest, $width, $height);
    drupal_set_message('User picture saved successfully!');

    return $file;
  }
  else {
    drupal_set_message('Your social network does not have a profile picture');
    return FALSE;
  }
}

/*
 *  Gigya parameter functions below
 */

/**
 * Retrieves services available on this account.
 */
function gigya_get_capabilities() {
  $services = array(
    'login' => 'login',
    'friends' => 'friends',
  );
  return $services;
}

/**
 * Undocumented Function!
 */
function gigya_status_form($account = NULL) {
  global $user;
  drupal_add_js(drupal_get_path('module', 'gigya') . '/gigya_updatestatus.js', 'module');

  if (empty($account)) {
    global $user;
    $account = $user;
  }

  if ($capabilities = $user->gigya->getCapabilities()) {
    if (array_search('Status', $capabilities)) {
      $form = array();
      $form['status'] = array(
        '#type' => 'textfield',
        '#id' => 'gigya-textfield',
      );
      return $form;
    }
  }
}

/**
 * Gets the list of services which can be connected to.
 *
 * @return array
 *  An array of services names.
 */
function gigya_get_networks() {
  $services = array(
    'facebook' => 'Facebook',
    'myspace' => 'MySpace',
    'twitter' => 'Twitter',
    'google' => 'Google',
    'yahoo' => 'Yahoo',
    'aol' => 'AOL',
    'blogger' => 'blogger',
    'wordpress' => 'WordPress',
    'typepad' => 'typepad',
    'liveJournal' => 'liveJournal',
    'hyves' =>  'hyves' ,
    'veriSign' => 'veriSign',
    'linkedin' =>  'LinkedIn',
    'liveid' => 'Windows Live ID',
    'openid' => 'OpenID',
    'orkut' => 'Orkut',
  );
  return $services;
}

/**
 * Retrieve the human-readable display name for a service.
 */
function gigya_get_network_display_name($network) {
  $networks = gigya_get_networks();
  if (array_key_exists($network, $networks)) {
    return $networks[$network];
  }
  return $network;
}

/**
 * Undocumented Function!
 *
 * @Undocumented Function! add the ability to specify the field type.
 */
function _gigya_get_profile_fields() {
  return array(
    'nickname' => t('Nickname'),
    'photoURL' => t('Gigya Profile photo URL'),
    'thumbnailURL' => t('Thumbnail profile photo URL'),
    'profileURL' => t('Profile URL'),
    'firstName' => t('First name'),
    'lastName' => t('Last name'),
    'gender' => t('Gender'),
    'age' => t('Age'),
    'birthDay' => t('Birth day'),
    'birthMonth' => t('Birth month'),
    'birthYear' => t('Birth year'),
    'email' => t('Email'),
    'country' => t('Country'),
    'state' => t('State'),
    'city' => t('City'),
    'zip' => t('Zip'),
  );
}

/**
 * Undocumented Function!: is this used anywhere?
 */
function _gigya_get_user_capabilities($uid) {
  if (empty($uid)) {
    return;
  }
  if ($bio = gigya_get_user_info($uid)) {
    $capabilities = split(', ', $bio['capabilities']);
    array_walk($capabilities, '_gigya_trim_value');
    return $capabilities;
  }
  else {
    return FALSE;
  }
}


/**
 * Helper function for trimming.
 */
function _gigya_trim_value(&$value) {
  $value = trim($value);
}

/**************************************************
 *  Internal Gigya signature verification functions
 **************************************************/

/**
 * _gigya_validate_sig
 * A helper function that validates the  SDK response
 * @param mixed $response the SDK response
 * @param mixed $gig_uid the gigya user id that initiate the SDK call
 * @return ture if response signature is valid false if not
 */
function _gigya_validate_sig($response, $gig_uid) {
  $secretkey = variable_get('gigya_SecretKey', '');
  $valid = SigUtils::validateUserSignature($response->getString("UID",""), $response->getString("signatureTimestamp",""), $secretkey, $response->getString("UIDSignature",""));
  if ($valid) {
    return TRUE;
  }
  else {
    watchdog('gigya', t('response signature is not valid'), NULL, WATCHDOG_WARNING);
    return FALSE;
  }
}

function _gigya_verify_signature($timestamp, $user_id) {
  $base_str = $timestamp . '_' . $user_id;
  $key = variable_get('gigya_SecretKey', FALSE);
  $sig = SigUtils::calcSignature($base_str, $key);
  return $sig;
}

/**
 * Validates the Gigya session keys.
 *
 * We use the site 'admin' username to find out the status. If it shows the
 * user logged out, thats good, if it returns an error then our keys are
 * most likely bad.
 */
function gigya_validate($apikey, $secretkey, $update = FALSE) {

  $orig_validate_state = variable_get('gigya_validate', FALSE);
  //$apikey = variable_get('gigya_APIKey', '');
  //$secretkey = variable_get('gigya_SecretKey', '');
  $request = new GSRequest($apikey,$secretkey, 'getUserInfo');
  $request->setParam('uid', 'admin');
  $gig_uid = 'admin';
  $response = $request->send();
  $error = $response->getErrorCode();
  if (!$update) {
    switch ($error) {
      case '400093':
        drupal_set_message($response->getErrorMessage());
        variable_set('gigya_validate', FALSE);
        return FALSE;
        break;
      case '403010':
        drupal_set_message($response->getErrorMessage());
        variable_set('gigya_validate', FALSE);
        return FALSE;
        break;
      case '400120':
        drupal_set_message($response->getErrorMessage());
        variable_set('gigya_validate', FALSE);
        return FALSE;
        break;
      case '400092':
        drupal_set_message($response->getErrorMessage());
        variable_set('gigya_validate', FALSE);
        return FALSE;
        break;
      case '403003':
        drupal_set_message($response->getErrorMessage());
        variable_set('gigya_validate', FALSE);
        return FALSE;
        break;
      default:
        drupal_set_message(t('Gigya validated properly. This site is authorized to use Gigya services'));
        variable_set('need_validation_msg', TRUE);
        variable_set('gigya_validate', TRUE);
        return TRUE;
        break;
    }
  }
  if (!$orig_validate_state || variable_get('need_validation_msg', FALSE)) {
    drupal_set_message(t('Gigya validated properly. This site is authorized to use Gigya services'));
    variable_set('need_validation_msg', TRUE);
    variable_set('gigya_validate', TRUE);
    return TRUE;
  }

}

/****************************
 * Gigya API functions
 ****************************/

 /*
 * Delete user from Gigya's DB
 */
function gigya_delete_account($uid) {
  if (empty($uid))
    return FALSE;

  $params = array(
    'uid' => $uid
  );

  return _gigya_api('deleteAccount',$params);
}

/*
 * Notifies Gigya that we've completed registering this user
 */
function gigya_notify_registration($old_uid, $new_uid) {
  if (empty($old_uid) || empty($new_uid))
    return FALSE;

  $params = array(
    'uid' => $old_uid,
    'siteUID' => $new_uid
  );

  return _gigya_api('notifyRegistration',$params);
}


/*
 * Sets the Gigya UID to match the Drupal UID
 */
function gigya_set_uid($old_uid, $new_uid) {
  if (empty($old_uid) || empty($new_uid))
    return FALSE;

  $params = array(
    'uid' => $old_uid,
    'siteUID' => $new_uid
  );

  return _gigya_api('setUID',$params);
}

/**
 * Fetches information about users following a given Gigya account.
 */
function gigya_get_user_info($gigya_uid) {
  if (empty($gigya_uid))
    return FALSE;

  $params = array(
    'uid' => $gigya_uid,
  );

  return _gigya_api('getUserInfo',$params);
}

/**
 * Undocumented Function!
 */
function gigya_get_friends_info($gigya_uid, $params) {
  if (empty($gigya_uid))
    return FALSE;

  $params += array(
    'uid' => $gigya_uid,
  );
  return _gigya_api('getFriendsInfo',$params);
}

/**
 * Undocumented Function!
 */
function gigya_set_status($gigya_uid, $status) {
  if (empty($gigya_uid))
    return FALSE;

  $params = array(
    'uid' => $gigya_uid,
    'status' => $status
  );

  return _gigya_api('setStatus',$params);
}

/**
 * Undocumented Function!
 */
function gigya_publish_user_action($gigya_uid, $content) {
  if (empty($gigya_uid))
    return FALSE;

  $params = array(
    'uid' => $gigya_uid,
    'userAction' => _gigya_get_useraction_xml($content)
  );

  return _gigya_api('publishUserAction',$params);
}


/**
 * DEPRECATED - use setUID
 * Create a linkage in Gigya Socialize between the current Drupal user and gigya user (Drupal uid<->Gigya uid)
 */
function gigya_link_accounts_rest($gigya_uid,$drupalUid) {
  if (empty($gigya_uid))
    return FALSE;

  $params = array(
    'uid' => $gigya_uid,
    'siteUID' => $drupalUid
  );

  return _gigya_api('linkAccounts',$params);
}

/**
 * DEPRECATED - use deleteAccount
 * Break the linkage in Gigya Socialize between the current Drupal user and gigya user (Drupal uid != Gigya uid)
 */
function gigya_unlink_accounts($gigya_uid,$drupalUid) {
  if (empty($gigya_uid))
    return FALSE;

  $params = array(
    'uid' => $gigya_uid,
    'siteUID' => $drupalUid
  );

  return _gigya_api('unlinkAccounts',$params);
}

/*
 * Handles all calls to the Gigya API
 */

require_once(drupal_get_path('module', 'gigya') . '/GSSDK.php');

/**
 * _gigya_api
 * helper function that handles gigya api calls
 * @param mixed $method the gigya api method
 * @param mixed $params the method parmeters
 * @access protected
 * @return an array of the gigya responce
 */
function _gigya_api($method, $params){
  $apikey = variable_get('gigya_APIKey', '');
  $secretkey = variable_get('gigya_SecretKey', '');
  $request = new GSRequest($apikey,$secretkey,$method);
  $uinfo = in_array('getUserInfo', $params);
  foreach ($params as $param => $val) {
    $request->setParam($param, $val);
  }
  $gig_uid = $params['uid'];
  $response = $request->send();


  if (_gigya_request_failure($response, $gig_uid, $uinfo)) {
    return FALSE;
  }

  return _gigya_convert_json_to_array($response->getResponseText());
}

/**
 * Undocumented Function!
 */
function _gigya_get_useraction_xml($content) {
  $template = $content['template'];
  $action = $content['action'];
  $title = htmlspecialchars($content['title']);
  $path = htmlspecialchars(url($content['path'], array('absolute' => TRUE)));
  $xml = '<userAction><template>$template</template><actionName>$action</actionName><templateFields><templateField><name>thing</name><text>$title</text><href>$path</href></templateField></templateFields></userAction>';
  return $xml;
}


/**
  * Internal helper function to deal cleanly with various HTTP response codes.
  */
function _gigya_request_failure($response, $gig_uid, $uinfo, $return_error = FALSE) {
  $code = $response->getErrorCode();
  if(variable_get('gigya_debug', 0)) {
    watchdog('gigya_debug', $response->getLog(), NULL, WATCHDOG_WARNING);
  }
  switch ($code) {
  case '0':
    if($uinfo) {
      if (_gigya_validate_sig($response, $gig_uid)) {
        return FALSE;
      }
      else {
        return (isset($return_error)) ? $code : TRUE;
      }
    }
    else {
      return (isset($return_error)) ? $code : TRUE;
    }
      break;
    case '403005':
      if (variable_get('gigya_validate', FALSE)) {
        return FALSE;
      }
      else {
        watchdog('gigya',  $response->getErrorMessage(), NULL, WATCHDOG_WARNING);
        return (isset($return_error)) ? $code : TRUE;
      }
      break;
    default:
      return (isset($return_error)) ? $code : TRUE;
      break;
  }
}


/**
 * convert JSON response to a php array
 */
function _gigya_convert_json_to_array($data) {
  $array =  json_decode($data, TRUE);
  return $array;
}
