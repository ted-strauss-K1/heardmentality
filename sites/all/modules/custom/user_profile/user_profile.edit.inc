<?php

/**
 * Define newsletter period values
 */
define('SUBSCRIPTION_NEVER', 0);
define('SUBSCRIPTION_MONTHLY', 1);
define('SUBSCRIPTION_WEEKLY', 2);

/**
 * User Profile form
 *
 * @param $form_state
 * @return array
 */
function user_profile_edit_form()
{
  $form = array();

  global $user;

  geocode_js();

  $form['#attributes']['enctype'] = "multipart/form-data";

  $form['username'] = array(
    '#type' => 'textfield',
    '#title' => t(''),
    '#maxlength' => 20,
    '#description' => t(' '),
    '#value' => $user->name,
    '#default_value' => t('Username'),
    '#id' => 'username',
    '#required' => TRUE,
    '#attributes' => array('class' => 'info validate validate-username', 'blurtext' => t('Username')),
  );
  $form['password'] = array(
    '#type' => 'textfield',
    '#title' => t(''),
    '#maxlength' => 20,
    '#description' => t(' '),
    '#value' => '',
    '#default_value' => t('Password'),
    '#id' => 'username',
    '#required' => FALSE,
    '#attributes' => array('class' => 'info validate validate-username', 'blurtext' => t('Password')),
  );
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t(''),
    '#maxlength' => 50,
    '#description' => t(' '),
    '#value' => $user->mail,
    '#default_value' => t('Email'),
    '#id' => 'email',
    '#attributes' => array('class' => 'info validate validate-email', 'blurtext' => t('Email')),
    '#disabled' => TRUE,
  );

  # add privacy values
  $privacy = user_profile_profile_privacy_values();
  $privacy_options = array();
  foreach ($privacy as $key => $value) {
    $privacy_options[$key] = '';
  }

  # privacy
  $form['private_profile_email'] = array(
    '#type' => 'radios',
    '#default_value' => $user->{'private_profile_email'} ? $user->{'private_profile_email'} : 'private',
    '#options' => $privacy_options,
    '#checked' => TRUE,
  );

  # profile fields
  $result = _profile_get_fields('profile');
  while ($field = db_fetch_object($result)) {
    switch ($field->type) {
      case 'selection' :
        $options = array('-1' => t($field->title));
        if ($field->name == 'profile_country') {
          $options += location_get_iso3166_list();
        } else {
          $options += explode("\n", $field->options);
        }
        $form[$field->name] = array(
          '#type' => 'select',
          '#title' => t(''),
          '#options' => $options,
          '#description' => t(' '),
          '#value' => $user->{$field->name},
          '#default_value' => -1,
          '#id' => $field->name,
          '#attributes' => array('class' => 'info'),
        );
        break;
      case 'textfield' :
        $form[$field->name] = array(
          '#type' => 'textfield',
          '#title' => t(''),
          '#maxlength' => 64,
          '#description' => t(' '),
          '#value' => $user->{$field->name},
          '#default_value' => t($field->title),
          '#id' => $field->name,
          '#attributes' => array('class' => 'info', 'blurtext' => t($field->title)),
        );

        break;
      case 'textarea' :
        $form[$field->name] = array(
          '#type' => 'textarea',
          '#title' => t(''),
          '#value' => $user->{$field->name},
          '#default_value' => t($field->title),
          '#cols' => '',
          '#rows' => 1,
          '#description' => t(''),
          '#id' => $field->name,
          '#attributes' => array('class' => 'info', 'blurtext' => t($field->title)),
          '#resizable' => FALSE,
        );
        break;
    }
    # privacy
    $form[USER_PROFILE_PRIVACY_PREFIX . $field->name] = array(
      '#type' => 'radios',
      '#default_value' => $user->{USER_PROFILE_PRIVACY_PREFIX . $field->name} ?
        $user->{USER_PROFILE_PRIVACY_PREFIX . $field->name} : 'private',
      '#options' => $privacy_options,
      '#checked' => TRUE,
    );
  }

  # profile fields - links
  $result = _profile_get_fields('links');
  while ($field = db_fetch_object($result)) {
    switch ($field->type) {
      case 'textfield' :
        $form[$field->name] = array(
          '#type' => 'textfield',
          '#title' => t(''),
          '#maxlength' => 64,
          '#description' => t(' '),
          '#value' => $user->{$field->name},
          '#default_value' => t($field->title),
          '#id' => $field->name,
          '#attributes' => array('class' => 'info', 'blurtext' => t($field->title)),
        );
        break;
    }
    # privacy
    $form[USER_PROFILE_PRIVACY_PREFIX . $field->name] = array(
      '#type' => 'radios',
      '#default_value' => $user->{USER_PROFILE_PRIVACY_PREFIX . $field->name} ?
        $user->{USER_PROFILE_PRIVACY_PREFIX . $field->name} : 'private',
      '#options' => $privacy_options,
      '#checked' => TRUE,
    );
  }

  # profile fields - hidden
  $result = _profile_get_fields('hidden');
  while ($field = db_fetch_object($result)) {
    $form[$field->name] = array(
      '#type' => 'hidden',
      '#value' => $user->{$field->name},
      '#id' => $field->name,
    );
  }

  # location
  $form['location'] = array(
    '#type' => 'markup',
    '#value' => user_profile_location_format($user->profile_city, $user->profile_state, $user->profile_country),
  );

  # subscription info
  $form['subscription_notify'] = array(
    '#type' => 'radios',
    '#default_value' => $user->subscription_notify ? $user->subscription_notify : SUBSCRIPTION_NEVER,
    '#options' => array(
      SUBSCRIPTION_NEVER => '',
      SUBSCRIPTION_MONTHLY => '',
      SUBSCRIPTION_WEEKLY => ''
    ),
  );
  $form['subscription_email'] = array(
    '#type' => 'textfield',
    '#title' => t(''),
    '#maxlength' => 50,
    '#default_value' => $user->subscription_email ? $user->subscription_email : $user->mail,
    '#id' => 'subscription_email',
    '#required' => TRUE,
  );
  $form['subscription_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#id' => 'subscription_submit',
    '#name' => 'subscription_submit',
    '#attributes' => array('class' => 'submit-issue leftfloat'),
  );

  # language info
  $languages = i18n_language_list();
  $form['language'] = array(
    '#type' => 'select',
    '#options' => $languages,
    '#default_value' => empty($user->language) ? 'en' : $user->language,
  );
  $form['language_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#id' => 'language_submit',
    '#name' => 'language_submit',
    '#attributes' => array('class' => 'submit-issue leftfloat'),
  );

  # avatar
  $form['image_upload'] = array(
    '#type' => 'file',
    '#size' => '10',
    '#prefix' => '
      <div id="al-msg"></div>
      <div class="avatar-left">
        <img id="image-avatar-pic" src="' . user_profile_image($user) . '" />
        <p>' . t('Select an image file from your computer.<br />(2MBs max)') . '</p>',
    '#suffix' => '</div>',
  );
  $form['image_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#id' => 'submit_brow-avat',
    '#name' => 'image_submit',
    '#attributes' => array('class' => 'submit-issue leftfloat'),
  );
  $form['image_avatar'] = array(
    '#type' => 'hidden',
    '#value' => '',
    '#id' => 'image_avatar',
  );

  # submit
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Changes'),
    '#id' => 'submit',
    '#name' => 'submit',
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
 * @return string
 */
function user_profile_location_format($city, $province, $country)
{
  $location = array();

  if (!empty($country)) {
    $location[] = location_country_name($country);
    if (!empty($city)) {
      $location[] = location_city_name($country, $province, $city);
    } else if (!empty($province)) {
      $location[] = location_province_name($country, $province);
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
function user_profile_edit_form_validate(&$form, &$form_state)
{
  $id = $form_state["clicked_button"]["#name"];

  switch ($id) {
    case 'submit' :
      user_profile_edit_form_validate_profile($form, $form_state);
      break;
    case 'subscrpition_submit' :
      user_profile_edit_form_validate_subscriptions($form, $form_state);
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
function user_profile_edit_form_validate_profile(&$form, &$form_state)
{
  global $user;
  $post = &$form_state["clicked_button"]["#post"];

  # username
  if ($post['username'] != $user->name) {
    if (!preg_match('/^[A-Za-z0-9_]{5,20}$/i', $post['username'])) {
      form_set_error('username', t('Username should be Alphabets, numbers and no special characters min 5 and max 20 allowed'));
      $form_state['rebuild'] = TRUE;
    } elseif (0 !== (int)db_result(db_query("SELECT COUNT(*) FROM {users} WHERE name = '%s' AND uid != '%d'", $post['username'], $user->uid))) {
      form_set_error('username', t('Sorry username already exists. Try any other combination'));
      $form_state['rebuild'] = TRUE;
    }
  } else {
    unset($post['username']);
  }

  # password
//  if ($post['password'] == '' || $post['password'] == $form['password']['#default_value']) {
//    form_set_error('password', t('Password cannot be empty'));
//    $form_state['rebuild'] = TRUE;
//  }

  # Year of Birth
  if (!empty($post['profile_yob']) && ($post['profile_yob'] != $form['profile_yob']['#default_value']) && !preg_match('/^\d{4}$/i', $post['profile_yob'])) {
    form_set_error('profile_yob', t('Year Of Birth should be Numeric & Proper Format Ex : 1986'));
    $form_state['rebuild'] = TRUE;
  }

  # Zip
  if (!empty($post['profile_zip']) && !empty($post['profile_country']) &&
    !user_profile_edit_form_validate_zip($post['profile_zip'], $post['profile_country'])
  ) {
    form_set_error('profile_zip', t('Cannot determine your location with provided country and zip code'));
    $form_state['rebuild'] = TRUE;
  }

  # facebook || twitter
  foreach (array('facebook', 'twitter') as $provider) {
    $input = $post['profile_'.$provider];
    if (!empty($input)) {
      $input = trim($input);
      if (preg_match('/^https?:\/\//', $input)) {
        $parse = parse_url($input);
        if (!in_array($parse['host'], array($provider.'.com', 'www.'.$provider.'.com'))) {
          form_set_error('profile_'.$provider, t('The URL you entered does not seem to be a !provider URL', array('!provider' => $provider)));
        }
      }
      else {
        form_set_error('profile_'.$provider, t('The input should be a !provider profile URL', array('!provider' => $provider)));
      }
    }
    $post['profile_'.$provider] = $input;
  }

  # website
  if (!empty($post['profile_website'])) {
    $post['profile_website'] = trim($post['profile_website']);
    if (!filter_var($post['profile_website'], FILTER_VALIDATE_URL)) {
      form_set_error('profile_website', t('The input is not a valid URL'));
    }
  }

}

/**
 * Validate zip
 *
 * @param $zip
 * @param $country
 * @return bool
 */
function user_profile_edit_form_validate_zip($zip, $country)
{
  return true;
}

/**
 * Validate subscriptions
 *
 * @param $form
 * @param $form_state
 */
function user_profile_edit_form_validate_subscriptions(&$form, &$form_state)
{
  $post = $form_state["clicked_button"]["#post"];

  # email
  if (!empty($post['subscription_email']) && !filter_var($post['subscription_email'], FILTER_VALIDATE_EMAIL)) {
    form_set_error('subscription_email', t('Email is not correct'));
    $form_state['rebuild'] = TRUE;
  }
}

/**
 * Validate image
 *
 * @param $form
 * @param $form_state
 */
function user_profile_edit_form_validate_image(&$form, &$form_state)
{
  $post = $form_state["clicked_button"]["#post"];
  $validators = array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
    'file_validate_size' => array(512 * 1024),
  );
  $upload_dir = file_directory_path() . '/userpics';
  if ($file = file_save_upload('image_upload', $validators, $upload_dir)) {
    file_set_status($file, FILE_STATUS_PERMANENT);
    $form_state['values']['image_upload'] = $file;
  } elseif (empty($post['image_avatar'])) {
    form_set_error('image_upload', 'File was not uploaded. Either the file extension or the size is incorrect.');
  }
}

/**
 * Common Submission of the form
 *
 * @param $form
 * @param $form_state
 */
function user_profile_edit_form_submit(&$form, &$form_state)
{
  $id = $form_state["clicked_button"]["#name"];
  switch ($id) {
    case 'submit' :
      user_profile_edit_form_submit_profile($form, $form_state);
      break;
    case 'subscrition_submit' :
      user_profile_edit_form_submit_subscriptions($form, $form_state);
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
function user_profile_edit_form_submit_profile($form, &$form_state)
{
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
 * Submit subscriptions
 *
 * @param $form
 * @param $form_state
 */
function user_profile_edit_form_submit_subscriptions(&$form, &$form_state)
{
  $post = $form_state["clicked_button"]["#post"];
  global $user;

  $user->subscription_notify = $post['subscription_notify'];
  $user->subscription_email = $post['subscription_email'];
  user_save($user, array(
    'subscription_notify' => $post['subscription_notify'],
    'subscription_email' => $post['subscription_email'],
  ));
}

/**
 * Submit language
 *
 * @param $form
 * @param $form_state
 */
function user_profile_edit_form_submit_language(&$form, &$form_state)
{
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
function user_profile_edit_form_submit_image(&$form, &$form_state)
{
  global $user;
  $post = $form_state["clicked_button"]["#post"];
  $file = $form_state['values']['image_upload'];

  $dest = false;
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
  } else {
    // image avatar
    $dest = $post['image_avatar'];
  }

  $user->picture = $dest;
  user_save($user, array('picture' => $dest));
}

/**
 * Theme user_profile_avatar_selection
 *
 * @param $user
 * @return string
 */
function theme_user_profile_avatar_selection($user)
{
  drupal_add_css(drupal_get_path('module', 'user_profile') . '/user_profile.css');
  $output = '<div id="user_profile_avatar_selection"><p>' . t('Pick a profile photo') . '</p>';
  $avatars = _avatar_selection_image_list($user);
  foreach ($avatars['avatars'] as $avatar) {
    $output .= $avatar;
  }
  $output .= '</div>';
  return $output;
}
