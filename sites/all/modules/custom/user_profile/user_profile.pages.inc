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
function user_profile_edit_form(&$form_state) {
  $form = array();

  global $user;

  $form['#attributes']['enctype'] = "multipart/form-data";

  $form['username'] = array(
    '#type'           => 'textfield',
    '#title'          => t(''),
    '#maxlength'      => 20,
    '#description'    => t(' '),
    '#value'          => $user->name,
    '#default_value'  => t('Username'),
    '#id'             => 'username',
    '#required'       => TRUE,
    '#attributes'     => array('class' => 'info validate validate-username', 'blurtext' => t('Username')),
//    '#disabled'       => TRUE,
  );
  $form['password'] = array(
    '#type'           => 'textfield',
    '#title'          => t(''),
    '#maxlength'      => 20,
    '#description'    => t(' '),
    '#value'          => '',
    '#default_value'  => t('Password'),
    '#id'             => 'username',
    '#required'       => FALSE,
    '#attributes'     => array('class' => 'info validate validate-username', 'blurtext' => t('Password')),
//    '#disabled'       => TRUE,
  );
  $form['email'] = array(
    '#type'           => 'textfield',
    '#title'          => t(''),
    '#maxlength'      => 50,
    '#description'    => t(' '),
    '#value'          => $user->mail,
    '#default_value'  => t('Email'),
    '#id'             => 'email',
//    '#required'       => 1,
    '#attributes'     => array('class' => 'info validate validate-email', 'blurtext' => t('Email')),
    '#disabled'       => TRUE,
  );

  # add privacy values
  $privacy = user_profile_profile_privacy_values();
  $privacy_options = array();
  foreach ($privacy as $key => $value) {
    $privacy_options[$key] = '';//$value['label'];
  }

  # privacy
  $form['private_profile_email'] = array(
    '#type'           => 'radios',
    '#default_value'  => $user->{'private_profile_email'} ? $user->{'private_profile_email'} : 'private',
    '#options'        => $privacy_options,
    '#checked'        => TRUE,
  );

//  Here the fields defined in Profile Module go
  $result = _profile_get_fields('profile');
  while ($field = db_fetch_object($result)) {
    switch ($field->type) {
      case 'selection' :
        $options = array('-1' => t($field->title));
        if ($field->name != 'profile_country') {
          $options += explode("\n", $field->options);
        } else {
          $countries = geonames_query('countryinfo');
          $countries_options = array();
          if ($countries) {
            foreach ($countries->results as $country) {
              $countries_options[$country['countrycode']] = $country['countryname'];
            }
          }
          asort($countries_options);
          $options += $countries_options;
        }
        $form[$field->name] = array(
          '#type'           => 'select',
          '#title'          => t(''),
          '#options'        => $options,
          '#description'    => t(' '),
          '#value'          => $user->{$field->name},
          '#default_value'  => -1,
          '#id'             => $field->name,
          '#attributes'     => array('class' => 'info'),
        );
      break;
      case 'textfield' :
        $form[$field->name] = array(
          '#type'           => 'textfield',
          '#title'          => t(''),
          '#maxlength'      => 64,
          '#description'    => t(' '),
          '#value'          => $user->{$field->name},
          '#default_value'  => t($field->title),
          '#id'             => $field->name,
          '#attributes'     => array('class' => 'info', 'blurtext' => t($field->title)),
        );

      break;
      case 'textarea' :
        $form[$field->name] = array(
          '#type'           => 'textarea',
          '#title'          => t(''),
          '#value'          => $user->{$field->name},
          '#default_value'  => t($field->title),
          '#cols'           => '',
          '#rows'           => 1,
          '#description'    => t(''),
          '#id'             => $field->name,
          '#attributes'     => array('class' => 'info', 'blurtext' => t($field->title)),
          '#resizable'      => FALSE,
        );
      break;
    }
    # privacy
    $form[USER_PROFILE_PRIVACY_PREFIX.$field->name] = array(
      '#type'           => 'radios',
      '#default_value'  => $user->{USER_PROFILE_PRIVACY_PREFIX.$field->name} ?
        $user->{USER_PROFILE_PRIVACY_PREFIX.$field->name} : 'private',
      '#options'        => $privacy_options,
      '#checked'        => TRUE,
    );
  }

  $result = _profile_get_fields('links');
  while ($field = db_fetch_object($result)) {
    switch ($field->type) {
      case 'textfield' :
        $form[$field->name] = array(
          '#type'           => 'textfield',
          '#title'          => t(''),
          '#maxlength'      => 64,
          '#description'    => t(' '),
          '#value'          => $user->{$field->name},
          '#default_value'  => t($field->title),
          '#id'             => $field->name,
          '#attributes'     => array('class' => 'info', 'blurtext' => t($field->title)),
        );
      break;
    }
    # privacy
    $form[USER_PROFILE_PRIVACY_PREFIX.$field->name] = array(
      '#type'           => 'radios',
      '#default_value'  => $user->{USER_PROFILE_PRIVACY_PREFIX.$field->name} ?
        $user->{USER_PROFILE_PRIVACY_PREFIX.$field->name} : 'private',
      '#options'        => $privacy_options,
      '#checked'        => TRUE,
    );
  }

  $result = _profile_get_fields('hidden');
  while ($field = db_fetch_object($result)) {
    $form[$field->name] = array(
      '#type'           => 'hidden',
      '#value'          => $user->{$field->name},
      '#id'             => $field->name,
    );
  }

  $form['location'] = array(
    '#type'           => 'markup',
    '#value'          => user_profile_location_format($user->profile_city, $user->profile_state, $user->profile_country),
  );

  $form['social'] = array(
    '#type'       => 'markup',
    '#value'      => '
      <div id="divConnect"></div>
      <script type="text/javascript">gigya.services.socialize.showAddConnectionsUI(conf, {height:65, width:175 ,showTermsLink:false, hideGigyaLink:true, useHTML:true, containerID: "divConnect"});</script>
    ',
  );

  $form['subscription_notify'] = array(
    '#type'           => 'radios',
    '#default_value'  => $user->subscription_notify ? $user->subscription_notify : SUBSCRIPTION_NEVER,
    '#options'        => array(
      SUBSCRIPTION_NEVER => '',
      SUBSCRIPTION_MONTHLY => '',
      SUBSCRIPTION_WEEKLY => ''
    ),
  );
  $form['subscription_email'] = array(
    '#type'           => 'textfield',
    '#title'          => t(''),
    '#maxlength'      => 50,
    '#default_value'  => $user->subscription_email ? $user->subscription_email : $user->mail,
    '#id'             => 'subscription_email',
    '#required'       => TRUE,
  );
  $form['subscription_submit'] = array(
    '#type'           => 'submit',
    '#value'          => t('Submit'),
    '#id'             => 'subscription_submit',
    '#name'           => 'subscription_submit',
    '#attributes'     => array('class' => 'submit-issue leftfloat'),
//    '#validate'       => array('user_profile_edit_form_validate_subscriptions'),
//    '#submit'         => array('user_profile_edit_form_submit_subscriptions'),
  );

  $languages = i18n_language_list();
  $form['language'] = array(
    '#type'           => 'select',
    '#options'        => $languages,
    '#default_value'  => $user->language,
  );
  $form['language_submit'] = array(
    '#type'           => 'submit',
    '#value'          => t('Submit'),
    '#id'             => 'language_submit',
    '#name'             => 'language_submit',
    '#attributes'     => array('class' => 'submit-issue leftfloat'),
//    '#submit'         => array('user_profile_edit_form_submit_language'),
  );

  $form['image_upload'] = array(
    '#type'     => 'file',
    '#size'     => '10',
    '#prefix'   => '
      <div id="al-msg"></div>
      <div class="avatar-left">
        <img id="image-avatar-pic" src="' . user_profile_image($user) . '" />
        <p>' . t('Select an image file from your computer.<br />(2MBs max)') . '</p>',
    '#suffix' => '</div>',
  );
  $form['image_submit'] = array(
    '#type'           => 'submit',
    '#value'          => t('Submit'),
    '#id'             => 'submit_brow-avat',
    '#name'             => 'image_submit',
    '#attributes'     => array('class' => 'submit-issue leftfloat'),
//    '#validate'       => array('user_profile_edit_form_validate_image'),
//    '#submit'         => array('user_profile_edit_form_submit_image'),
  );
  $form['image_avatar'] = array(
    '#type'           => 'hidden',
    '#value'          => '',
    '#id'             => 'image_avatar',
  );

  $form['submit'] = array(
    '#type'           => 'submit',
    '#value'          => t('Save Changes'),
    '#id'             => 'submit',
    '#name'           => 'submit',
    '#attributes'     => array('class' => 'submit-issue'),
//    '#validate'       => array('user_profile_edit_form_validate'),
//    '#submit'         => array('user_profile_edit_form_submit'),
);

//  $form['#submit'] = array();

  return $form;
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
function user_profile_edit_form_validate_profile(&$form, &$form_state) {
  global $user;
  $post = $form_state["clicked_button"]["#post"];

  # username
  if ($post['username'] != $user->name) {
    if (!preg_match('/^[A-Za-z0-9_]{5,20}$/i', $post['username'])) {
      form_set_error('username', t('Username should be Alphabets, numbers and no special characters min 5 and max 20 allowed'));
      $form_state['rebuild'] = TRUE;
    } elseif ( false !== db_result(db_query("SELECT COUNT(*) FROM {users} WHERE name = '%s' AND uid != '%d'", $post['username'], $user->uid)) ) {
      form_set_error('username', t('Sorry username already exists. Try any other combination'));
      $form_state['rebuild'] = TRUE;
    }
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
}

/**
 * Validate zip
 *
 * @param $zip
 * @param $country
 * @return bool
 */
function user_profile_edit_form_validate_zip($zip, $country) {
  return true;
}

/**
 * Validate subscriptions
 *
 * @param $form
 * @param $form_state
 */
function user_profile_edit_form_validate_subscriptions(&$form, &$form_state) {
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
function user_profile_edit_form_validate_image(&$form, &$form_state) {
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
function user_profile_edit_form_submit(&$form, &$form_state) {
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
  $output = user_profile_geocode($user->profile_country, $user->profile_zip);
  if (!empty($output)) {
    foreach (array('city', 'state', 'lat', 'lng') as $code) {
      $edit['profile_'.$code] = $output[$code];
      $user->{'profile_'.$code} = $output[$code];
    }
  }

  if ($post['password'] != '' && $post['password'] != $form['password']['#default_value']) {
    $edit['pass'] = $post['password'];
  }
  user_save($user, $edit);
  user_save($user, $edit, 'profile');
  user_save($user, $edit, 'links');

  // TODO
  if (module_exists('activity_stream')) {
    activity_stream_add_activity(ACTIVITY_STREAM_PROFILE_UPDATE, array());
  }
}

/**
 * Submit subscriptions
 *
 * @param $form
 * @param $form_state
 */
function user_profile_edit_form_submit_subscriptions(&$form, &$form_state) {
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
    // images upload
    if (strpos($dest, 'http://') !== 0) {
      $dest = '/' . $dest;
    }
  } else {
    // image avatar
    $dest = $post['image_avatar'];
  }
//  var_Dump($dest); die();
  $user->picture = $dest;
  user_save($user, array('picture' => $dest));

  if (module_exists('activity_stream')) {
    activity_stream_add_activity(ACTIVITY_STREAM_PROFILE_UPDATE, array());
  }

}












