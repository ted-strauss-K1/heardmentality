<?php

/**
 * Implementation of hook_user()
 *
 * @param $op
 * @param $edit
 * @param $account
 * @param null $category
 */
function user_profile_user($op, &$edit, &$account, $category = NULL)
{
  switch ($op) {

    case 'login' :

      drupal_goto($_GET['q']);

    break;

    case 'load' :

      # user links
      $account->viewlink = 'user/profile/view/' . $account->name;
      $account->editlink = 'user/profile/edit';

    break;

    case 'insert' :

      # random avatar selection
      if (!$account->picture) {
        $picture = avatar_selection_get_random_image($account);
        $account->picture = $picture;
        db_query("UPDATE {users} SET picture = '%s' WHERE uid = '%d'", $picture, $account->uid);
      }

      # ulogin data collection
      if (module_exists('ulogin')) {
        global $ulogin_data;
        if (!empty($ulogin_data)) {

          # user name
          if (!empty($ulogin_data['nickname'])) {
            if (0 == (int)db_result(db_query("SELECT COUNT(*) FROM {users} WHERE name = '%s'", $ulogin_data['nickname']))) {
              if (db_query("UPDATE {users} SET name = '%s' WHERE uid = '%d'", $ulogin_data['nickname'], $account->uid)) {
                $edit['name'] = $ulogin_data['nickname']; // update in the user array for access by other modules
                $account->name = $ulogin_data['nickname']; // update in the user array for access by other modules
              }
            }
          }

          # user picture
          if (!empty($ulogin_data['photo_big']) || !empty($ulogin_data['photo'])) {
            $photo = ($ulogin_data['photo_big']) ? $ulogin_data['photo_big'] : $ulogin_data['photo'];
            if (db_query("UPDATE {users} SET picture = '%s' WHERE uid = '%d'", $photo, $account->uid)) {
              $edit['picture'] = $photo; // update in the user array for access by other modules
              $account->picture = $photo; // update in the user array for access by other modules
            }
          }

          # generic fields
          $profile_fields = array();

          # real name
          if (($profile_name = implode(" ", array($ulogin_data['first_name'], $ulogin_data['last_name'])))) {
            $profile_fields['profile_name'] = $profile_name;
          }
          # gender
          if (in_array($ulogin_data['sex'], array(1, 2))) {
            $profile_fields['profile_gender'] = $ulogin_data['sex'] == 2 ? 0 : 1;
          }
          # year of birth
          if (!empty($ulogin_data['bdate']) && preg_match('@(\d{2})\.(\d{2})\.(\d{4})@', $ulogin_data['bdate'], $m)) {
            $profile_fields['profile_yob'] = $m[3];
          }
          # attempt to get a country
          if (!empty($ulogin_data['country'])) {
            $countries = location_get_iso3166_list();
            foreach ($countries as $iso => $country) {
              if ($country == $ulogin_data['country']) {
                $profile_fields['profile_country'] = $iso;
                break;
              }
            }
          }
          if ($ulogin_data['network']) {
            switch ($ulogin_data['network']) {
              case 'facebook':
              case 'twitter':
                $profile_fields['profile_' . $ulogin_data['network']] =
                  ('facebook' == $ulogin_data['network'] ? 'https://www.facebook.com/' : 'https://twitter.com/') .
                    preg_replace('@.*\/@', '', $ulogin_data['identity']);
                break;
            }
          }

          # save generic fields
          foreach ($profile_fields as $key => $value) {
            db_query("REPLACE INTO {profile_values} (value, fid, uid) SELECT '%s', pf.fid, '%d' FROM {profile_fields} pf WHERE pf.name = '%s'",
              $value, $account->uid, $key
            );
          }

        }
      }

    break;

    case 'logout':

      # handle redirects
      if (
        (arg(0, $_REQUEST['destination']) == 'user') &&
        (arg(1, $_REQUEST['destination']) == 'profile')
      ) {
        $uid = arg(3, $_REQUEST['destination']);
        $_REQUEST['destination'] = 'user/profile/view';
        if (is_numeric($uid)) {
          $_REQUEST['destination'] .= '/' . $uid;
        } else {
          $_REQUEST['destination'] .= '/' . $account->uid;
        }
        drupal_goto();
      }

    break;
  }
}

/**
 * Define permission to edit profile
 */
define('USER_PROFILE_EDIT', 'Edit User Profile');

/**
 * Define permission to view profile
 */
define('USER_PROFILE_VIEW', 'View User Profile');

/**
 * Implementation of hook_perm()
 *
 * @return array
 */
function user_profile_perm()
{
  return array(USER_PROFILE_EDIT, USER_PROFILE_VIEW);
}

/**
 * Implementation of hook_menu()
 *
 * @return array
 */
function user_profile_menu()
{
  $menu = array();

  # view page
  $menu['user/profile/view'] = array(
    'title' => t('View Profile'),
    'page callback' => 'theme',
    'page arguments' => array('user_profile_view'),
    'access callback' => 'user_profile_access_user_profile',
    'access arguments' => array(USER_PROFILE_VIEW, 3),
    'type' => MENU_CALLBACK,
  );

  # edit page
  $menu['user/profile/edit'] = array(
    'title' => t('Edit Profile'),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('user_profile_edit_form'),
    'access arguments' => array(USER_PROFILE_EDIT),
    'file' => 'user_profile.edit.inc',
    'type' => MENU_CALLBACK,
  );


  $menu['user/profile/follow/%/%'] = array(
    'title callback' => 'user_profile_follow_title',
    'title arguments' => array(4, TRUE),
    'page callback' => 'theme',
    'page arguments' => array('user_profile_follow', 3, 4),
    'access callback' => 'user_profile_access_user_profile',
    'access arguments' => array(USER_PROFILE_VIEW, 3),
    'type' => MENU_CALLBACK,
  );

  return $menu;
}

/**
 * Implementation of hook_preprocess_page()
 *
 * @param $vars
 */
function user_profile_preprocess_page(&$vars)
{
  # user profile pages
  if ('user' == arg(0) && 'profile' == arg(1)) {
    drupal_add_js(drupal_get_path('module', 'user_profile') . '/user_profile.js');
    switch (arg(2)) {
      case 'view' :
      case 'follow' :
        $vars['right'] = theme('user_profile_info', NULL);

        # categories
        $account = _user_profile_get_user(arg(3));
        global $user;
        if (($account->uid == $user->uid) && user_is_logged_in()) {
          $vars['right'] .= theme('categories_user_block');
        }

        # events
        if ('view' == arg(2)) {
          $account = _user_profile_get_user(arg(3));
          if ($account) {
            $request = events_build_query(array(
              array(
                'uid' => $account->uid,
                'operation' => array(
                  'create',
                  'debate',
                  'reply',
                  'vote',
                  'follow',
                  'yn_voteup',
                  'yn_votedn',
                  'taxonomy',
                ),
              ),
              events_build_query_subscriptions($account->uid),
            ));
            $vars['content_bottom'] = theme('events', events_get($request['query'], $request['vars']));
          }
          drupal_set_subtitle(t('View Profile'));
        }
        array_push($vars['template_files'], 'page_11_5');
      break;

      case 'edit' :
        array_push($vars['template_files'], 'page_empty');
      break;
    }
  }

  #  Popup
  if (user_is_logged_in()) {
    $vars['user_popups'] = theme('user_profile_popup');
  }
}

/**
 * Check permission to view the profile page
 *
 * @param $user_access
 * @param $string
 * @return bool
 */
function user_profile_access_user_profile($user_access, $string)
{
  if (empty($string) && !user_is_logged_in()) {
    return FALSE;
  } else {
    $user = _user_profile_get_user($string);
    if ($user === FALSE) {
      if (arg(0) == 'user' && arg(1) == 'profile') {
        drupal_not_found();
      }
      return FALSE;
    } else {
      return user_access($user_access);
    }
  }
}

/**
 * Get user by string
 *
 * @param $string
 * @return bool
 */
function _user_profile_get_user($string)
{
  static $account = NULL;

  if (is_null($account)) {
    if (empty($string)) {
      if (user_is_logged_in()) {
        global $user;
        $account = $user;
      } else {
        $account = FALSE;
      }
    } elseif (!is_numeric($string)) {
      $string = strtolower($string);
      $account = user_load(array('name' => $string));
    } else {
      $account = user_load(array('uid' => $string));
    }
  }

  return $account;
}

/**
 * Implementation of hook_theme()
 *
 * @return array
 */
function user_profile_theme()
{
  $theme = array();

  # view page
  $theme['user_profile_view'] = array(
    'arguments' => array(),
    'template' => 'templates/user-profile-view',
    'preprocess functions' => array('user_profile_view_preprocess'),
  );
  $theme['user_profile_info'] = array(
    'arguments' => array('user' => NULL,),
    'template' => 'templates/user-profile-info',
    'preprocess functions' => array('user_profile_info_preprocess'),
  );

  # edit page - form
  $theme['user_profile_edit_form'] = array(
    'arguments' => array('form' => NULL),
    'template' => 'templates/user-profile-edit-form',
  );
  # edit page - avatar selection
  $theme['user_profile_avatar_selection'] = array(
    'arguments' => array('user' => NULL,),
  );

  # follow page
  $theme['user_profile_follow'] = array(
    'arguments' => array(
      'uid' => NULL,
      'code' => NULL,
    ),
    'template' => 'templates/user-profile-follow',
    'preprocess functions' => array('user_profile_follow_preprocess'),
  );

  # popups/blocks
  foreach (array('popup', 'right', 'bottom') as $place) {
    $theme['user_profile_' . $place] = array(
      'arguments' => array('user' => NULL,),
      'template' => 'templates/user-profile-' . $place,
      'preprocess functions' => array('user_profile_block_preprocess'),
    );
  }

  return $theme;
}

/**
 * Theme "user_profile_view" preprocess function
 *
 * @param $vars
 */
function user_profile_view_preprocess(&$vars)
{
  $vars['account'] = _user_profile_get_user(arg(3));
  $vars['rank'] = $vars['account']->rank['name'];
}

/**
 * Theme "user_profile_info" preprocess function
 *
 * @param $vars
 */
function user_profile_info_preprocess(&$vars)
{
  if (!isset($vars['account'])) {
    $vars['account'] = _user_profile_get_user(arg(3));
    if ($vars['account'] === FALSE) {
      $vars['denied'] = TRUE;
      return;
    }
  }
  $uid = $vars['account']->uid;

  # badges
  $vars['badges'] = $vars['account']->badges;
  # comments
  $vars['comments'] = @db_result(db_query("SELECT COUNT(DISTINCT(nid)) FROM {comments} WHERE uid = '%d'", $uid));
  # votes
  $vars['votes'] = cpoll_uservotes($uid);
  # references
  $vars['references'] = (int)db_result(db_query("SELECT COUNT(*) FROM {node} n WHERE n.uid = '%d' AND n.type IN ('argument', 'resource') AND n.status = '%d'", $uid, 1));
  # following
  $vars['followers_count'] = follower_get_followers($uid, TRUE);
  $vars['followers'] = follower_get_followers($uid, FALSE, 8);
  $vars['following_count'] = follower_get_following($uid, TRUE);
  $vars['following'] = follower_get_following($uid, FALSE, 8);
}

/**
 * @param $code
 * @return null|string
 */
function user_profile_follow_title($code, $set_as_title = FALSE)
{
  $title = $code == 'following' ? t('Following Users') : t('Followers');
  return $set_as_title ? drupal_set_subtitle($title) : $title;
}

/**
 * Theme "user_profile_follow" preprocess function
 *
 * @param $vars
 */
function user_profile_follow_preprocess(&$vars)
{
  switch ($vars['code']) {
    case 'following' :
      $vars['users'] = follower_get_following($vars['uid']);
      break;
    case 'followers' :
      $vars['users'] = follower_get_followers($vars['uid']);
      break;
  }
  $vars['followers_count'] = follower_get_followers($vars['uid'], TRUE);
  $vars['following_count'] = follower_get_following($vars['uid'], TRUE);
}

/**
 * Theme preprocess function
 *
 * @param $vars
 */
function user_profile_block_preprocess(&$vars)
{
  if (!user_is_logged_in()) {
    $vars['denied'] = TRUE;
    return;
  }

  static $preprocessed = array();

  if (empty($preprocessed)) {
    drupal_add_js(drupal_get_path('module', 'user_profile') . '/user_profile.js');
    global $user;
    $preprocessed['user'] = $user;
    $preprocessed['complete'] = pcp_alter_get_complete_percentage_data($user);
    $preprocessed['badges'] = $user->badges;
//    if (module_exists('up')) {
//      $preprocessed['points'] = up_userpoints_get($user->uid);
//    }
  }

  foreach ($preprocessed as $key => $value) {
    $vars[$key] = $preprocessed[$key];
  }
}





