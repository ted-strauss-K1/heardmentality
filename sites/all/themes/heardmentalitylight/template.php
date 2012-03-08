<?php

// $Id: template.php,v 1.16.2.2 2009/08/10 11:32:54 goba Exp $

/**
 * Sets the body-tag class attribute.
 *
 * Adds 'sidebar-left', 'sidebar-right' or 'sidebars' classes as needed.
 */
function phptemplate_body_class($left, $right) {
    if ($left != '' && $right != '') {
        $class = 'sidebars';
    } else {
        if ($left != '') {
            $class = 'sidebar-left';
        }
        if ($right != '') {
            $class = 'sidebar-right';
        }
    }

    if (isset($class)) {
        print ' class="' . $class . '"';
    }
}

function zonechange($current, $target) {

    $timezone = new DateTimeZone("America/New_York");
    $date = new DateTime();
    $date->setTimezone($timezone);
    return $date->format("F j,Y | g:i a T");
    /* $utc_str = gmdate("M d Y H:i:s", time());
      echo $utc = strtotime($utc_str);
      $current = -1 * $current;
      $zonedate = mktime(date('G'), date('i'), date('s'), date('n'),
      date('j'), date('Y'), 1) + (($current + $target) * 3600);
      return date("F j,Y | g:i a T", $zonedate);


     */
}

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return a string containing the breadcrumb output.
 */
function phptemplate_breadcrumb($breadcrumb) {
    if (!empty($breadcrumb)) {
        return '<div class="breadcrumb">' . implode(' › ', $breadcrumb) . '</div>';
    }
}

/**
 * Override or insert PHPTemplate variables into the templates.
 */
function phptemplate_preprocess_page(&$vars) {
    global $user;
	//echo '<pre>';
//print_r($vars);exit;
    if ((arg(1) == 'block')) {
        $vars['template_files'][0] = 'page-test';
    }
    if (arg(0) == 'searchuser') {

        $variables['template_file'][0] = 'page-searchquestion';
    }

    $vars['tabs2'] = menu_secondary_local_tasks();

    // Hook into color.module
    if (module_exists('color')) {
        _color_page_alter($vars);
    }

    $query = db_query("SELECT * FROM {moderator_messages} WHERE to_uid = '$user->uid' AND status = '0' ORDER BY id DESC");
    while($res = db_fetch_object($query)){
        $notify[] = $res;
    }
    $vars['notify'] = $notify;
}


function heardmentalitylight_preprocess_page(&$vars) {
    // there's also a $theme_path global
    global $theme, $theme_path;
    $path = drupal_get_path('theme', $theme);

if($vars['node']->type == 'static_pages' || $vars['node']->type == 'page'|| $vars['node']->type == 'webform'){
    $suggestions = array(
      'page-static-pages'
    );
    $vars['template_files'] = array_merge($vars['template_files'], $suggestions);
}

//overide default jquery
   // if($vars['template_files'][1]!='page-issue-create'){
      //psh  drupal_add_js($path . "/javascripts/jquery1.4.js", 'core'); //where you store your jque
   // }
    
    

 //psh   $js = drupal_add_js(NULL, NULL, 'header'); //get header js files in an array
   
 //psh   unset($js['core']['misc/jquery.js']); //unset default drupal jquery js
 //psh  $js['core'] = array_reverse($js['core'], 1); //make our own jquery file first (see note)

 //psh  if($vars['template_files'][1]=='page-issue-create'){
 //psh   unset($js['theme']['sites/all/themes/heardmentalitylight/javascripts/jquery-1.5.1.min.js']); //unset default drupal jquery js
 //psh   //echo '<pre>';    print_r($js);exit;
 //psh   }
    
    /*
      if ($vars['content'] && $vars['node']->type != 'forum') {
      $vars['content'] = '<h2 class="comments">'. t('Comments') .'</h2>'.  $vars['content'];
      }

     */
 //psh $vars['scripts'] = drupal_get_js('header', $js); //create script tags and set them to $scripts
   
}

/**
 * Returns the rendered local tasks. The default implementation renders
 * them as tabs. Overridden to split the secondary tasks.
 *
 * @ingroup themeable
 */

function onlineuser_count() {
    global $gSitePath;
    $number = db_result(db_query('SELECT COUNT(uid) AS number FROM {users} WHERE status=1'));
    if (user_access('access content')) {
        // Count users with activity in the past defined period.
        $time_period = variable_get('user_block_seconds_online', 900);

        // Perform database queries to gather online user lists.
        $guests = db_fetch_object(db_query('SELECT COUNT(sid) AS count FROM {sessions} WHERE timestamp >= %d AND uid = 0', time() - $time_period));
        $userslist = db_query('SELECT uid, name, access FROM {users} WHERE access >= %d AND uid != 0 ORDER BY access DESC', time() - $time_period);
        $total_users = db_result($userslist);

        // Format the output with proper grammar.
        echo "Out of $number registered users ";
        if ($total_users == 1 && $guests->count == 1) {
            $output = t('%members and %visitors online.', array('%members' => format_plural($total_users, 'there is currently 1 user', 'there are currently @count users'), '%visitors' => format_plural($guests->count, '1 guest', '@count guests')));
        } else {
            $output = t('there are currently %members and %visitors online.', array('%members' => format_plural($total_users, '1 user', '@count users'), '%visitors' => format_plural($guests->count, '1 guest', '@count guests')));
        }
        // Display a list of currently online users.
        $max_users = variable_get('user_block_max_list_count', 10);
        if ($total_users && $max_users) {
            $items = array();
            while ($max_users-- && $account = db_fetch_object($users)) {
                $items[] = $account;
            }
            $output .= theme('user_list', $items, t('Online users'));
        }
    }
    return $output;
}



function phptemplate_user_picture($account, $size = '65x56') {
    //print_r(func_get_args());
  if (!variable_get('user_pictures', 0))  {
    return '';
  }

  // Default to a certain size
  if (arg(0) == 'user' && is_numeric(arg(1))) {
    $size = '65x56';
  }
 
  if ($account->picture && file_exists($account->picture)) {
    switch($size) {
      case '65x56':
        $maxsize_icon = array('w'=> 65, 'h'=> 56);
        $info = image_get_info($account->picture);
        if ($info['height'] < $maxsize_icon['h']) {
          $maxsize_icon['h'] = $info['height'];
        }
        if ($info['width'] < $maxsize_icon['w']) {
          $maxsize_icon['w'] = $info['width'];
        }
        
        $newpicture = dirname($account->picture) . '/picture-'
         . $account->uid . '.' . $info['extension'];
        if (!file_exists($newpicture) ||
          (filectime($newpicture) < filectime($account->picture))) {
          image_scale($account->picture, $newpicture, $maxsize_icon['w'],
            $maxsize_icon['h']);
        }
        $picture = file_create_url($newpicture);
        break;

      case '30x30':
        $maxsize_tile = array('w'=> 30, 'h'=> 30);
        $info = image_get_info($account->picture);
        $newpicture = dirname($account->picture) . '/picture-'
          . $account->uid . '-small' . '.' . $info['extension'];
        if (!file_exists($newpicture) ||
          (filectime($newpicture) < filectime($account->picture))) {
          image_scale($account->picture, $newpicture, $newpicture,
            $maxsize_tile['w'], $maxsize_tile['h']);
        }
        $picture = file_create_url($newpicture);
        break;

      default:
        $picture = file_create_url($account->picture);
        break;
    }
  }
  else {
    $picture = variable_get('user_picture_default', '');
  }

  if (isset($picture)) {
    $alt = t('@user\'s picture',
      array('@user' => $account->name ? $account->name :
        variable_get('anonymous', 'Anonymous')));
    $attr=array('width'=>$maxsize_icon['w'],'height'=>$maxsize_icon['h']);
    $picture = theme('image', $picture, $alt, $alt,$attr, false);
    if (!empty($account->uid) && user_access('access user profiles')) {
      $picture = l($picture, "profile/$account->name", array('html' => TRUE));
    }

    return $picture;
  }
}
function phptemplate_preprocess_node(&$vars) {
  if (arg(0) == 'issues') {
    $suggestions = array(
      'node-issues'
    );
    $vars['template_files'] = array_merge($vars['template_files'], $suggestions);
  }
}

function heardmentalitylight_theme($existing, $type, $theme, $path){
  $themePath = drupal_get_path('theme', $theme);
  $formPath = $themePath.'/forms/';

return array(
        'issue_search_form' => array(
        'arguments' => array('form' => NULL),
        'template' => 'issue-search-form',
        ),
        'issue_suggest_form' => array(
        'arguments' => array('form' => NULL),
        'template' => 'issue-suggest-form',
        ),
        'user_details' => array(
        'arguments' => array('form' => NULL),
        'template' => 'profile-edit-form',
        ),
        'abuse_report_form' => array(
        'arguments' => array('form' => NULL),
        'template' => 'issue-flag-form',
        ),
    );
}



