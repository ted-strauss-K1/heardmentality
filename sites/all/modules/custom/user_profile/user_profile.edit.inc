<?php

/**
 * User Profile form
 *
 * @param $form_state
 *
 * @return array
 */
function user_profile_edit_form() {
  $form = array();

  global $user;

  geocode_js();

  $form['#attributes']['enctype'] = "multipart/form-data";

  $form['username'] = array(
    '#type'          => 'textfield',
    '#title'         => '',
    '#maxlength'     => 20,
    '#description'   => ' ',
    '#value'         => $user->name,
    '#default_value' => __('Username', array('@code' => 'user_profile-01')),
    '#id'            => 'username',
    '#required'      => TRUE,
    '#attributes'    => array('class' => 'info validate validate-username', 'blurtext' => __('Username', array('@code' => 'user_profile-01'))),
  );
  $form['password'] = array(
    '#type'          => 'textfield',
    '#title'         => '',
    '#maxlength'     => 20,
    '#description'   => ' ',
    '#value'         => '',
    '#default_value' => __('Password', array('@code' => 'user_profile-02')),
    '#id'            => 'username',
    '#required'      => FALSE,
    '#attributes'    => array('class' => 'info validate validate-username', 'blurtext' => __('Password', array('@code' => 'user_profile-02'))),
  );
  $form['email'] = array(
    '#type'          => 'textfield',
    '#title'         => '',
    '#maxlength'     => 50,
    '#description'   => ' ',
    '#value'         => $user->mail,
    '#default_value' => __('Email', array('@code' => 'user_profile-03')),
    '#id'            => 'email',
    '#attributes'    => array('class' => 'info validate validate-email', 'blurtext' => __('Email', array('@code' => 'user_profile-03'))),
    '#disabled'      => TRUE,
  );

  # add privacy values
  $privacy = user_profile_profile_privacy_values();
  $privacy_options = array();
  foreach ($privacy as $key => $value) {
    $privacy_options[$key] = '';
  }

  # privacy
  $form['private_profile_email'] = array(
    '#type'          => 'radios',
    '#default_value' => $user->{'private_profile_email'} ? $user->{'private_profile_email'} : 'private',
    '#options'       => $privacy_options,
    '#checked'       => TRUE,
  );

  # profile fields
  $result = _profile_get_fields('profile');
  while ($field = db_fetch_object($result)) {
    $field_title = __($field->title, array('@code' => 'user_profile-field-' . $field->name));
    switch ($field->type) {
      case 'selection' :
        $options = array('-1' => $field_title);
        if ($field->name == 'profile_country') {
          $options += location_get_iso3166_list();
        }
        else {
          $options += explode("\n", $field->options);
        }
        $form[$field->name] = array(
          '#type'          => 'select',
          '#title'         => '',
          '#options'       => $options,
          '#description'   => ' ',
          '#value'         => $user->{$field->name},
          '#default_value' => -1,
          '#id'            => $field->name,
          '#attributes'    => array('class' => 'info'),
        );
        break;
      case 'textfield' :
        $form[$field->name] = array(
          '#type'          => 'textfield',
          '#title'         => '',
          '#maxlength'     => 64,
          '#description'   => ' ',
          '#value'         => $user->{$field->name},
          '#default_value' => $field_title,
          '#id'            => $field->name,
          '#attributes'    => array('class' => 'info', 'blurtext' => $field_title),
        );

        break;
      case 'textarea' :
        $form[$field->name] = array(
          '#type'          => 'textarea',
          '#title'         => '',
          '#value'         => $user->{$field->name},
          '#default_value' => $field_title,
          '#cols'          => '',
          '#rows'          => 1,
          '#description'   => '',
          '#id'            => $field->name,
          '#attributes'    => array('class' => 'info', 'blurtext' => $field_title),
          '#resizable'     => FALSE,
        );
        break;
    }
    # privacy
    $form[USER_PROFILE_PRIVACY_PREFIX . $field->name] = array(
      '#type'          => 'radios',
      '#default_value' => $user->{USER_PROFILE_PRIVACY_PREFIX . $field->name} ? $user->{USER_PROFILE_PRIVACY_PREFIX . $field->name} : 'private',
      '#options'       => $privacy_options,
      '#checked'       => TRUE,
    );
  }

  # profile fields - links
  $result = _profile_get_fields('links');
  while ($field = db_fetch_object($result)) {
    $field_title = __($field->title, array('@code' => 'user_profile-field-' . $field->name));
    switch ($field->type) {
      case 'textfield' :
        $form[$field->name] = array(
          '#type'          => 'textfield',
          '#title'         => '',
          '#maxlength'     => 64,
          '#description'   => ' ',
          '#value'         => $user->{$field->name},
          '#default_value' => $field_title,
          '#id'            => $field->name,
          '#attributes'    => array('class' => 'info', 'blurtext' => $field_title),
        );
        break;
    }
    # privacy
    $form[USER_PROFILE_PRIVACY_PREFIX . $field->name] = array(
      '#type'          => 'radios',
      '#default_value' => $user->{USER_PROFILE_PRIVACY_PREFIX . $field->name} ? $user->{USER_PROFILE_PRIVACY_PREFIX . $field->name} : 'private',
      '#options'       => $privacy_options,
      '#checked'       => TRUE,
    );
  }

  # profile fields - hidden
  $result = _profile_get_fields('hidden');
  while ($field = db_fetch_object($result)) {
    $form[$field->name] = array(
      '#type'  => 'hidden',
      '#value' => $user->{$field->name},
      '#id'    => $field->name,
    );
  }

  # location
  $form['location'] = array(
    '#type'  => 'markup',
    '#value' => user_profile_location_format($user->profile_city, $user->profile_state, $user->profile_country),
  );

  # language info
  $languages = i18n_language_list();
  $form['language'] = array(
    '#type'          => 'select',
    '#options'       => $languages,
    '#default_value' => empty($user->language) ? 'en' : $user->language,
  );
  $form['language_submit'] = array(
    '#type'       => 'submit',
    '#value'      => __('Submit', array('@code' => 'user_profile-04')),
    '#id'         => 'language_submit',
    '#name'       => 'language_submit',
    '#attributes' => array('class' => 'submit-issue leftfloat'),
  );

  # avatar
  $form['image_upload'] = array(
    '#type'   => 'file',
    '#size'   => '10',
    '#prefix' => '
      <div id="al-msg"></div>
      <div class="avatar-left">
        <img id="image-avatar-pic" src="' . user_profile_image($user) . '" />
        <p>' . __('Select an image file from your computer.<br />(2MBs max)', array('@code' => 'user_profile-05')) . '</p>',
    '#suffix' => '</div>',
  );
  $form['image_submit'] = array(
    '#type'       => 'submit',
    '#value'      => __('Submit', array('@code' => 'user_profile-06')),
    '#id'         => 'submit_brow-avat',
    '#name'       => 'image_submit',
    '#attributes' => array('class' => 'submit-issue leftfloat'),
  );
  $form['image_avatar'] = array(
    '#type'  => 'hidden',
    '#value' => '',
    '#id'    => 'image_avatar',
  );

  # submit
  $form['submit'] = array(
    '#type'       => 'submit',
    '#value'      => __('Save Changes', array('@code' => 'user_profile-07')),
    '#id'         => 'submit',
    '#name'       => 'submit',
    '#attributes' => array('class' => 'submit-issue'),
  );

  return $form;
}

/**
 * user_profile_location_format
 *
 * @param $city
 * @param $state
 * @param $country
 *
 * @return string
 */
function user_profile_location_format($city, $province, $country) {
  $location = array();

  if (!empty($country)) {
    $location[] = location_country_name($country);
    if (!empty($city)) {
      $location[] = location_city_name($country, $province, $city);
    }
    else {
      if (!empty($province)) {
        $location[] = location_province_name($country, $province);
      }
    }
  }

  return implode(', ', $location);
}

/**
 * Common Validation of the form
 *
 * @param $form
 * @param $form_state
 */
function user_profile_edit_form_validate(&$form, &$form_state) {
  $id = $form_state["clicked_button"]["#name"];

  switch ($id) {
    case 'submit' :
      user_profile_edit_form_validate_profile($form, $form_state);
      break;
    case 'language_submit' :
      //
      break;
    case 'image_submit' :
      user_profile_edit_form_validate_image($form, $form_state);
      break;
  }
}

/**
 * Validate profile
 *
 * @param $form
 * @param $form_state
 */
function user_profile_edit_form_validate_profile(&$form, &$form_state) {
  global $user;
  $post = & $form_state["clicked_button"]["#post"];

  # username
  if ($post['username'] != $user->name) {
    if (!preg_match('/^[A-Za-z0-9_]{5,20}$/i', $post['username'])) {
      form_set_error('username', __('Username should be Alphabets, numbers and no special characters min 5 and max 20 allowed', array('@code' => 'user_profile-08')));
      $form_state['rebuild'] = TRUE;
    }
    elseif (0 !== (int) db_result(db_query("SELECT COUNT(*) FROM {users} WHERE name = '%s' AND uid != '%d'", $post['username'], $user->uid))) {
      form_set_error('username', __('Sorry username already exists. Try any other combination', array('@code' => 'user_profile-09')));
      $form_state['rebuild'] = TRUE;
    }
  }
  else {
    unset($post['username']);
  }

  # password
  //  if ($post['password'] == '' || $post['password'] == $form['password']['#default_value']) {
  //    form_set_error('password', t('Password cannot be empty'));
  //    $form_state['rebuild'] = TRUE;
  //  }

  # Year of Birth
  if (!empty($post['profile_yob']) && ($post['profile_yob'] != $form['profile_yob']['#default_value']) && !preg_match('/^\d{4}$/i', $post['profile_yob'])) {
    form_set_error('profile_yob', __('Year Of Birth should be Numeric & Proper Format Ex : 1986', array('@code' => 'user_profile-10')));
    $form_state['rebuild'] = TRUE;
  }

  # Zip
  if (!empty($post['profile_zip']) && !empty($post['profile_country']) && !user_profile_edit_form_validate_zip($post['profile_zip'], $post['profile_country'])
  ) {
    form_set_error('profile_zip', __('Cannot determine your location with provided country and zip code', array('@code' => 'user_profile-11')));
    $form_state['rebuild'] = TRUE;
  }

  # facebook || twitter
  foreach (array('facebook', 'twitter') as $provider) {
    $input = $post['profile_' . $provider];
    if (!empty($input)) {
      $input = trim($input);
      if (preg_match('/^https?:\/\//', $input)) {
        $parse = parse_url($input);
        if (!in_array($parse['host'], array($provider . '.com', 'www.' . $provider . '.com'))) {
          form_set_error('profile_' . $provider, __('The URL you entered does not seem to be a !provider URL', array('@code' => 'user_profile-12', '!provider' => $provider)));
        }
      }
      else {
        form_set_error('profile_' . $provider, __('The input should be a !provider profile URL', array('@code' => 'user_profile-13', '!provider' => $provider)));
      }
    }
    $post['profile_' . $provider] = $input;
  }

  # website
  if (!empty($post['profile_website'])) {
    $post['profile_website'] = trim($post['profile_website']);
    if (!filter_var($post['profile_website'], FILTER_VALIDATE_URL)) {
      form_set_error('profile_website', __('The input is not a valid URL', array('@code' => 'user_profile-14')));
    }
  }

}

/**
 * Validate zip
 *
 * @param $zip
 * @param $country
 *
 * @return bool
 */
function user_profile_edit_form_validate_zip($zip, $country) {
  return TRUE;
}

/**
 * Validate image
 *
 * @param $form
 * @param $form_state
 */
function user_profile_edit_form_validate_image(&$form, &$form_state) {
  $post = $form_state["clicked_button"]["#post"];
  $validators = array(
    'file_validate_is_image'   => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
    'file_validate_size'       => array(512 * 1024),
  );
  $upload_dir = file_directory_path() . '/userpics';
  if ($file = file_save_upload('image_upload', $validators, $upload_dir)) {
    file_set_status($file, FILE_STATUS_PERMANENT);
    $form_state['values']['image_upload'] = $file;
  }
  elseif (empty($post['image_avatar'])) {
    form_set_error('image_upload', 'File was not uploaded. Either the file extension or the size is incorrect.');
  }
}

/**
 * Common Submission of the form
 *
 * @param $form
 * @param $form_state
 */
function user_profile_edit_form_submit(&$form, &$form_state) {
  $id = $form_state["clicked_button"]["#name"];
  switch ($id) {
    case 'submit' :
      user_profile_edit_form_submit_profile($form, $form_state);
      break;
    case 'language_submit' :
      user_profile_edit_form_submit_language($form, $form_state);
      break;
    case 'image_submit' :
      user_profile_edit_form_submit_image($form, $form_state);
      break;
  }

  # actions
  global $user;
  function_exists('action_queue') && action_queue(array(
    'uid'         => $user->uid,
    'operation'   => 'user_update',
    'entity_id'   => $user->uid,
    'entity_type' => 'user',
  ));
}

/**
 * Profile submission
 *
 * @param $form
 * @param $form_state
 */
function user_profile_edit_form_submit_profile($form, &$form_state) {
  $post = $form_state["clicked_button"]["#post"];

  global $user;

  $user->profile_email = $user->mail;

  $defaults = array();
  $result = _profile_get_fields('profile');
  while ($field = db_fetch_object($result)) {
    $defaults[$field->name] = $field;
  }
  $result = _profile_get_fields('links');
  while ($field = db_fetch_object($result)) {
    $defaults[$field->name] = $field;
  }
  $result = _profile_get_fields('hidden');
  while ($field = db_fetch_object($result)) {
    $defaults[$field->name] = $field;
  }

  $edit = array();

  foreach ($defaults as $fname => $field) {
    if ($post[$fname] == $field->title || $post[$fname] == $form[$fname]['#default_value']) {
      $post[$fname] = '';
    }
    $pname = USER_PROFILE_PRIVACY_PREFIX . $fname;

    $edit[$fname] = $post[$fname];
    $edit[$pname] = isset($post[$pname]) && !empty($post[$pname]) ? $post[$pname] : 'private';

    $user->{$fname} = $edit[$fname];
    $user->{$pname} = $edit[$pname];
  }

  # additional fields
  foreach (array('city', 'state', 'lat', 'lng') as $code) {
    $edit['profile_' . $code] = $post['profile_' . $code];
    $user->{'profile_' . $code} = $post['profile_' . $code];
  }

  if ($post['password'] != '' && $post['password'] != $form['password']['#default_value']) {
    $edit['pass'] = $post['password'];
  }
  if ($post['username']) {
    $edit['name'] = $post['username'];
  }


  user_save($user, $edit);
  user_save($user, $edit, 'profile');
  user_save($user, $edit, 'hidden');
  user_save($user, $edit, 'links');
}

/**
 * Submit language
 *
 * @param $form
 * @param $form_state
 */
function user_profile_edit_form_submit_language(&$form, &$form_state) {
  $post = $form_state["clicked_button"]["#post"];
  global $user;

  $langcode = $post['language'];
  $user->language = $langcode;
  user_save($user, array('language' => $langcode));

  global $base_url;
  drupal_goto($base_url . '/user/profile/edit');
}

/**
 * Submit image
 *
 * @param $form
 * @param $form_state
 */
function user_profile_edit_form_submit_image(&$form, &$form_state) {
  global $user;
  $post = $form_state["clicked_button"]["#post"];
  $file = $form_state['values']['image_upload'];

  $dest = FALSE;
  if ($file) {
    $upload_dir = file_directory_path() . '/userpics';
    $extension = '';
    switch ($file->filemime) {
      case 'image/jpeg':
        $extension = 'jpg';
        break;
      case 'image/png':
        $extension = 'png';
        break;
      case 'image/gif':
        $extension = 'gif';
        break;
    }
    $dest = $upload_dir . '/picture-' . $user->uid . '.' . $extension;
  }
  if ($dest && file_move($file, $dest, FILE_EXISTS_RENAME)) {
    $dest = $file->filepath;
    // images upload
    if (strpos($dest, 'http://') !== 0) {
      $dest = '/' . $dest;
    }
  }
  else {
    // image avatar
    $dest = $post['image_avatar'];
  }

  $dest = str_replace(file_directory_path(), '', $dest);
  $dest = preg_replace('@^/+@', '', $dest);

  $user->picture = $dest;
  user_save($user, array('picture' => $dest));
}

/**
 * Theme user_profile_avatar_selection
 *
 * @param $user
 *
 * @return string
 */
function theme_user_profile_avatar_selection($user) {
  drupal_add_css(drupal_get_path('module', 'user_profile') . '/user_profile.css');
  $output = '<div id="user_profile_avatar_selection"><p>' . __('Pick a profile photo', array('@code' => 'user_profile-15')) . '</p>';
  $avatars = _avatar_selection_image_list($user);
  foreach ($avatars['avatars'] as $avatar) {
    $output .= $avatar;
  }
  $output .= '</div>';
  return $output;
}
