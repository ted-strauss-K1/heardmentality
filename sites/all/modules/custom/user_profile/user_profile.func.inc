<?php

function get_user_privacy_settings($uid) {
  $userSettings = checkPrivacySettings($uid);
  return get_user_privacy_values($userSettings, $uid);
}

function checkPrivacySettings($uid = null) {
  $ques_query = "SELECT * FROM {privacy_settings} where uid='" . $uid . "'";
  $list = ExecuteQuery($ques_query, "select");
  $userFields = array();
  $i = 0;

  $columns = db_query("SHOW COLUMNS FROM {privacy_settings}");

  while ($res = db_fetch_array($columns)) {
    $userFields[$res['Field']] = $list[$i][$res['Field']];
  }
  if (isset($userFields) && count($userFields) > 0) {
    return $userFields;
  }
}

function get_user_privacy_values($userSettings, $uid) {
  global $base_url, $user;
  $settings = array();
  //Checking settings and displaying the field
  $get_cn = db_query("select * from {user_profile} where uid='$uid'");
  $result = db_fetch_array($get_cn);
  $getuser = user_load(array('uid' => $result['uid']));
  $is_follow_follower = checkFollowStatus($user->uid, $uid);

  if (is_array($result))
    extract($result);

  if (($userSettings['real_name'] == 1) || ($userSettings['real_name'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['real_name'] == 3 && $is_follow_follower == TRUE) && ($userSettings['real_name'] != 4)) {
    $settings['real_name'] = $result['real_name'];
  }
  else {
    $settings['real_name'] = '';
  }

  if (($userSettings['mail'] == 1) || ($userSettings['mail'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['mail'] == 3 && $is_follow_follower == TRUE) && ($userSettings['mail'] != 4)) {
    $settings['email'] = $getuser->mail;
  }
  else {
    $settings['email'] = '';
  }
  if (($userSettings['bio'] == 1) || ($userSettings['bio'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['bio'] == 3 && $is_follow_follower == TRUE) && ($userSettings['bio'] != 4)) {
    $settings['bio'] = $result['bio'];
  }
  else {
    $settings['bio'] = '';
  }
  if (($userSettings['zip'] == 1) || ($userSettings['zip'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['zip'] == 3 && $is_follow_follower == TRUE) && ($userSettings['zip'] != 4)) {
    $country1 .= $result['country'];

    if (!empty($state)) {
      $country1.='(' . $result['state'] . ',' . $result['city'] . ').';
    }
    $settings['location'] = $country1;
  }
  else {
    $settings['location'] = "";
  }
  if (($userSettings['religion'] == 1) || ($userSettings['religion'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['religion'] == 3 && $is_follow_follower == TRUE) && ($userSettings['religion'] != 4)) {
    $settings['religion'] = $result['religion'];
  }
  else {
    $settings['religion'] = "";
  }



  if (($userSettings['image'] == 1) || ($userSettings['image'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['image'] == 3 && $is_follow_follower == TRUE) && ($userSettings['image'] != 4)) {
    $img_path1 = $base_url . '/' . drupal_get_path('module', 'profiles') . '/snap/' . $result['image'];
    $PROFILE_IMAGE = '<img src="' . $img_path1 . '" align="absmiddle" alt="Profile image" >';
  }

  if (($userSettings['dob'] == 1) || ($userSettings['dob'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['dob'] == 3 && $is_follow_follower == TRUE) && ($userSettings['dob'] != 4)) {
    $settings['dob'] = $age;
  }if ($settings['dob'] == 0) {
    $dob1 = "";
  }
  else {
    $rem_value = $settings['dob'] % 5;
    $rem_first = $settings['dob'] - $rem_value;
    $rem_second = $rem_first + 5;
    $settings['dob'] = $rem_first . ' - ' . $rem_second . ' ' . t('Years Old');
  }
  if (($userSettings['sorient'] == 1) || ($userSettings['sorient'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['sorient'] == 3 && $is_follow_follower == TRUE) && ($userSettings['sorient'] != 4)) {
    $settings['sorient'] = $result['sorient'];
  }
  else {
    $settings['sorient'] = "";
  }
  if (($userSettings['edu'] == 1) || ($userSettings['edu'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['edu'] == 3 && $is_follow_follower == TRUE) && ($userSettings['edu'] != 4)) {
    $settings['edu'] = $result['edu'];
  }
  else {
    $settings['edu'] = "";
  }
  if (($userSettings['ethnic'] == 1) || ($userSettings['ethnic'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['ethnic'] == 3 && $is_follow_follower == TRUE) && ($userSettings['ethnic'] != 4)) {
    $settings['ethnic'] = $result['ethnic'];
  }
  else {
    $settings['ethnic'] = "";
  }

  if (($userSettings['income'] == 1) || ($userSettings['income'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['income'] == 3 && $is_follow_follower == TRUE) && ($userSettings['income'] != 4)) {
    $settings['income'] = $result['income'];
  }
  else {
    $settings['income'] = "";
  }
  if (($userSettings['marital'] == 1) || ($userSettings['marital'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['marital'] == 3 && $is_follow_follower == TRUE) && ($userSettings['marital'] != 4)) {
    $settings['marital'] = $result['marital'];
  }
  else {
    $settings['marital'] = "";
  }

  if (($userSettings['gender'] == 1) || ($userSettings['gender'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['gender'] == 3 && $is_follow_follower == TRUE) && ($userSettings['gender'] != 4)) {
    $settings['gender'] = $result['gender'];
    $settings['gender'] = $settings['gender'] == 1 ? 'Male' : 'Female';
  }
  else {
    $settings['gender'] = "";
  }


  if (($userSettings['mywebsite'] == 1) || ($userSettings['mywebsite'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['mywebsite'] == 3 && $is_follow_follower == TRUE) && ($userSettings['mywebsite'] != 4)) {
    $settings['mywebsite'] = $result['urls'];
  }
  else {
    $settings['mywebsite'] = "";
  }
  list($facebook, $twitter) = explode("||", $result['social']);
  if (($userSettings['facebook'] == 1) || ($userSettings['facebook'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['facebook'] == 3 && $is_follow_follower == TRUE) && ($userSettings['facebook'] != 4)) {
    $settings['facebook'] = $facebook;
  }
  else {
    $settings['facebook'] = "";
  }
  if (($userSettings['twitter'] == 1) || ($userSettings['twitter'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['twitter'] == 3 && $is_follow_follower == TRUE) && ($userSettings['twitter'] != 4)) {
    $settings['twitter'] = $twitter;
  }
  else {
    $settings['twitter'] = "";
  }


  if (($userSettings['answers'] == 1) || ($userSettings['answers'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['answers'] == 3 && $is_follow_follower == TRUE) && ($userSettings['answers'] != 4)) {
    $settings['answers'] = $ins_ans;
  }
  else {
    $settings['answers'] = '';
  }
  if (($userSettings['questions'] == 1) || ($userSettings['questions'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['questions'] == 3 && $is_follow_follower == TRUE) && ($userSettings['questions'] != 4)) {
    $settings['questions'] = $inc_qns;
  }
  else {
    $settings['questions'] = '';
  }
  // other website links
  $othQuery = db_query("SELECT name, url FROM {follow_links} WHERE uid = '$uid'");
  $link_privacies = unserialize($userSettings['personal_links']);


  while ($otherLinks = db_fetch_object($othQuery)) {
    if (($link_privacies[$otherLinks->name] == 1) || ($link_privacies[$otherLinks->name] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($link_privacies[$otherLinks->name] == 3 && $is_follow_follower == TRUE) && ($link_privacies[$otherLinks->name] != 4)) {
      $others[$otherLinks->name] = $otherLinks->url;
    }
    else {
      $others = array();
    }
  }
  $settings['other_links'] = $others;

  return $settings;
}

// to check only follower or followee will see the profile
function checkFollowStatus($login_user_id = null, $profile_user_id = null) {

  $ques_query = "SELECT *  from {follower}  where uid='" . $login_user_id . "'  AND follower_status='1' AND  follower_id='" . $profile_user_id . "' UNION
	SELECT *  from {follower}  where uid='" . $profile_user_id . "'  AND follower_status='1' AND  follower_id='" . $login_user_id . "'
	";
  $list = ExecuteQuery($ques_query, "select");
  $isfollow = FALSE;
  if (isset($list) && count($list) > 0) {
    $isfollow = TRUE;
    return $isfollow;
  }
  return $isfollow;
}