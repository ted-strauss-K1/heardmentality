<?php













function inc_avatar_form($form, &$form_state) {


  global $user, $_GET, $theme;
  //avatar
  $form = array();
  // We find out the current page number.
  $page = 0;
  if (isset($_GET['page']) && is_numeric($_GET['page'])) {
    $page = $_GET['page'];
  }
  $anon_user = drupal_anonymous_user();
  $force_choose = variable_get('avatar_selection_force_user_avatar_reg', 0);
  $avatars_per_page = variable_get('avatar_selection_avatar_per_page', 30);
  $selects = _avatar_selection_image_list($anon_user, "", 0, $page * $avatars_per_page, $avatars_per_page);

  $udetails = load_user($user->uid);

  $avatar = (!empty($udetails->avatar)) ? $udetails->avatar : '';

  if (count($selects['avatars'])) {

    $form['picture']['select_avatar'] = array(
      '#type' => 'radios',
      '#title' => ($upload == 0 ? t('Select an avatar') : t('Or simply select an icon')),
      '#description' => $upload ? '' : t(''),
      '#options' => $selects['avatars'],
      '#required' => $force_choose ? TRUE : FALSE,
      '#default_value' => $avatar,
      '#attributes' => array('class' => 'user-avatar-select'),
      '#prefix' => '<div id="avatar-selection-loading"></div>',
      '#suffix' => theme('avatar_selection_pager', 'form#user-register', 'div.user-avatar-select', $selects['total'], $avatars_per_page, '/' . $js_file),
    );
  }


  //avatar
  return $form;
}









function user_profile_edit_privacy_options() {

}

function user_profile_edit_form_privacy() {
  $form = array();



  return $form;
}




function get_avatar_form() {
  global $user, $apikey, $theme;
  $form = array();
  drupal_add_js(drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection.js');
  drupal_add_js(drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection_pager.js');
  drupal_add_css(drupal_get_path('module', 'avatar_selection') . '/avatar_selection.css');
  drupal_add_js(drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection_pager.js');
  drupal_set_html_head('<script src="http://cdn.gigya.com/JS/socialize.js?apikey=' . $apikey . '" type="text/javascript"></script>');
  drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection.js';
  $account = load_user($user->uid);
  $data = '
	    var conf =
        {
            APIKey: \'' . $apikey . '\'
        };
var avtar=\'' . $account->avatar . '\';
';
  drupal_add_js($data, 'inline');

  // set the form encoding type

  $form['#attributes']['enctype'] = "multipart/form-data";
  $options = array('1' => t('weekly'), '2' => t('monthly'), '0' => t('never'));
  // add a file upload file
  $form['file_upload'] = array(
    '#type' => 'file',
    '#size' => '10',
    '#prefix' => '<div id="al-msg"></div><div class="avatar-left"><img src="' . UserPicture_small_src($user->uid, 0) . '" /><p>' . t('Select an image file from your computer.<br />(2MBs max)') . '</p>',
    '#suffix' => '</div>',
  );

  $form['oldimg'] = array(
    '#type' => 'hidden',
    '#default_value' => variable_get('oldimg', $user->picture),
    '#id' => 'oldimg',
  );
  $form['avatar_div_close'] = array('#type' => 'markup', '#value' => '<div class="clr"></div>
    </div><div class="clr"></div>');
  return $form;
}







function _user_profile_edit_form_submit($form, &$form_state) {
  global $user;
  krumo($form_state);
  // translate back country code to country name
  $countries = geonames_query('countryinfo');
  $contriesOptions = array();
  foreach ($countries->results as $country) {
    $contriesOptions[$country['countrycode']] = $country['countryname'];
  }
  $form_state['values']['country'] = $contriesOptions[$form_state['values']['country']];

  //profile fields update
  _basic_submit($form, $form_state);
  //privacy update
  _privacy_submit($form, $form_state);
  //avatar update
  _avatar_submit($form, $form_state);
  // follow links update
  //  follow_links_form_submit($form, $form_state);


  /* New SET NOTIFY LOG */
  $variable = array();
  set_notify_log($user->uid, '', 'update_profile', $variable);
  /* New SET NOTIFY LOG */


  drupal_set_message(t('Your profile info has been updated'), 'success');
}


function _basic_submit($form, &$form_state) {

  global $base_url, $user;
  $account = user_load($user->uid);
  $age = age($form_state['values']['dob']);

  // Load Latitude Longitude Ralldev DE544
  $doc = new DOMDocument();
  if ($form_state['values']['state'] != '' && $form_state['values']['country'] != '') {
    $doc->load('http://maps.googleapis.com/maps/api/geocode/xml?address=' . $form_state['values']['city'] . ',+' . $form_state['values']['state'] . ',+' . $form_state['values']['country'] . '&sensor=true');
    $locations = $doc->getElementsByTagName("location");
    foreach ($locations as $location) {
      $latitude = $location->getElementsByTagName("lat");
      $lat[] = $latitude->item(0)->nodeValue;

      $longitude = $location->getElementsByTagName("lng");
      $long[] = $longitude->item(0)->nodeValue;
    }
    $latitude = $lat[0];
    $longitude = $long[0];
  }
  else {
    $latitude = '';
    $longitude = '';
  }
  // Location data ends

  $chk = db_query("select * from {user_profile} where uid='$user->uid'");
  $chk_result = db_result($chk);
  if ($chk_result) {
    $query = "UPDATE {user_profile} set real_name='%s',gender='%s',bio='%s',zip='%s',country='%s',state='%s',city='%s',religion='%s',ethnic='%s',dob='%d',age='%d',income='%s',marital='%s',sorient='%s',edu='%s', latitude = '%s', longitude = '%s' where uid='%d' ";
  }
  else {
    $query = "INSERT INTO {user_profile} set real_name='%s',gender='%s',bio='%s',zip='%s',country='%s',state='%s',city='%s',religion='%s',ethnic='%s',dob='%d',age='%d',income='%s',marital='%s',sorient='%s',edu='%s', latitude = '%s', longitude = '%s', uid='%d' ";
  }
  $result = db_query($query, $form_state['values']['fname'], $form_state['values']['gender'], $form_state['values']['bio'], $form_state['values']['zip'], $form_state['values']['country'], $form_state['values']['state'], $form_state['values']['city'], $form_state['values']['religion'], $form_state['values']['ethnic'], $form_state['values']['dob'], $age, $form_state['values']['income'], $form_state['values']['marital'], $form_state['values']['sorient'], $form_state['values']['education'], $latitude, $longitude, $user->uid);
  //update username
  db_query("update {users} set name='%s',mail='%s',prompt='%d',language='%s' where uid='%d'", $form_state['values']['username'], $form_state['values']['email'], '0', $form_state['values']['default_language'], $user->uid);
  //drupal_set_message(t('Your profile has been updated', 'success'));
  $edit = array('profile_gender' => $form_state['values']['gender'], 'real_name' => $form_state['values']['fname'], 'profile_bio' => $form_state['values']['bio'], 'profile_zip' => $form_state['values']['zip'], 'profile_country' => $form_state['values']['country'], 'profile_state' => $form_state['values']['state'], 'profile_city' => $form_state['values']['city'], 'profile_religion' => $form_state['values']['religion'], 'profile_ethnic' => $form_state['values']['ethnic'], 'profile_dob' => $form_state['values']['dob'], 'profile_income' => $form_state['values']['income'], 'profile_marital' => $form_state['values']['marital'], 'profile_sorient' => $form_state['values']['sorient']);
  user_save($account, $edit, 'Profile');
  return true;
}


function _privacy_submit($form, &$form_state) {

  global $base_url, $user;
  //prepopulate the settings
  foreach (element_children($form) as $child) {
    if ($form[$child]['#type'] == 'radios') {
      $$child = $form_state['values'][$child];
    }
  }
  $personal_privacies = $form_state['values']['follow_links'];
  foreach ($personal_privacies as $link => $privacy) {
    if ($privacy['url'] != '' && $privacy['privacy']) {
      $peronal_privacies[$link] = $privacy['privacy'];
    }
  }
  $link_privacies = serialize($peronal_privacies);
  $chk = db_query("select * from {privacy_settings} where uid='$user->uid'");
  $chk1 = db_result($chk);
  if ($chk1) {
    $query = "UPDATE {privacy_settings} set real_name='%d',mail='%s',gender='%d',bio='%d',zip='%d',religion='%d',ethnic='%d',income='%d',marital='%d',sorient='%d',edu='%d',dob='%d', mywebsite='%d', facebook='%d', twitter='%d', personal_links='%s'  where uid='%d' ";
  }
  else {
    $query = "INSERT INTO {privacy_settings} set real_name='%d',mail='%s',gender='%d',bio='%d',zip='%d',religion='%d',ethnic='%d',income='%d',marital='%d',sorient='%d',edu='%d',dob='%d',mywebsite='%d', facebook='%d', twitter='%d', personal_links = '%s',uid='%d'";
  }

  db_query($query, $real_name_privacy, $mail_privacy, $gender_privacy, $bio_privacy, $zip_privacy, $religion_privacy, $ethnic_privacy, $income_privacy, $marital_privacy, $sorient_privacy, $edu_privacy, $dob_privacy, $mywebsite_privacy, $facebook_privacy, $twitter_privacy, $link_privacies, $user->uid);
  db_query("update {user_profile} set question_privacy='%d' where uid='%d'", $activity_privacy, $user->uid);
  //drupal_set_message(t('Your form has been saved.', 'success'));
  return true;
}