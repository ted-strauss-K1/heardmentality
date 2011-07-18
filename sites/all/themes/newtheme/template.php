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
// print_r($vars);exit;
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

/**
 * Add a "Comments" heading above comments except on forum pages.
 */
function garland_preprocess_comment_wrapper(&$vars) {
    if ($vars['content'] && $vars['node']->type != 'forum') {
        $vars['content'] = '<h2 class="comments">' . t('Comments') . '</h2>' . $vars['content'];
    }
}

function newtheme_preprocess_page(&$vars) {
    global $theme;
    $path = drupal_get_path('theme', $theme);

// there's also a $theme_path global
   
    global $theme_path;
//overide default jquery
   // if($vars['template_files'][1]!='page-issue-create'){
        drupal_add_js($path . "/scripts/jquery1.4.js", 'core'); //where you store your jque
   // }

    //drupal_add_js("js/more_javascripts.js", 'theme'); //any other js files you may have

    $js = drupal_add_js(NULL, NULL, 'header'); //get header js files in an array
   
    unset($js['core']['misc/jquery.js']); //unset default drupal jquery js
    $js['core'] = array_reverse($js['core'], 1); //make our own jquery file first (see note)


    if($vars['template_files'][1]=='page-account-edit'){
    unset($js['theme']['sites/all/themes/newtheme/scripts/preload.js']); //unset default drupal jquery js
    //print_r($js);
    }
    /*
      if ($vars['content'] && $vars['node']->type != 'forum') {
      $vars['content'] = '<h2 class="comments">'. t('Comments') .'</h2>'.  $vars['content'];
      }

     */
 $vars['scripts'] = drupal_get_js('header', $js); //create script tags and set them to $scripts
   
}

/**
 * Returns the rendered local tasks. The default implementation renders
 * them as tabs. Overridden to split the secondary tasks.
 *
 * @ingroup themeable
 */
function phptemplate_menu_local_tasks() {
    return menu_primary_local_tasks();
}

function phptemplate_comment_submitted($comment) {
    return t('!datetime — !username',
            array(
                '!username' => theme('username', $comment),
                '!datetime' => format_date($comment->timestamp)
    ));
}

function phptemplate_node_submitted($node) {
    return t('!datetime — !username',
            array(
                '!username' => theme('username', $node),
                '!datetime' => format_date($node->created),
    ));
}

/**
 * Generates IE CSS links for LTR and RTL languages.
 */
function phptemplate_get_ie_styles() {
    global $language;

    $iecss = '<link type="text/css" rel="stylesheet" media="all" href="' . base_path() . path_to_theme() . '/fix-ie.css" />';
    if ($language->direction == LANGUAGE_RTL) {
        $iecss .= '<style type="text/css" media="all">@import "' . base_path() . path_to_theme() . '/fix-ie-rtl.css";</style>';
    }

    return $iecss;
}

function phptemplate_preprocess_block(&$variables) {
    $path = base_path() . path_to_theme() . '/';
    $variables['path'] = $path;

}

function phptemplate_preprocess_node(&$vars) {
  if (arg(0) == 'issues') {
    $suggestions = array(
      'node-issues'
    );
    $vars['template_files'] = array_merge($vars['template_files'], $suggestions);
  }
}


function sub_menu_cat($id='', $level='') {
    global $gSitePath;
    $strReturn = null;
    if ($level < 1) {
        $client_select = db_query("SELECT cat_id,cat_name FROM {category} where parent_id='" . $id . "'");

        $client_array = array();
        $client_key = array();

        while ($list = db_fetch_object($client_select)) {

            $client_array[] = $list->cat_name;
            $client_key[] = $list->cat_id;
        }

        if (count($client_array) > 0) {


            $strReturn.='<ul >';

            for ($i = 0; $i < count($client_array); $i++) {

                $check_sub = db_query("SELECT cat_id,cat_name FROM {category} where parent_id='" . $client_key[$i] . "'");
                $cnt = array();
                while ($sublevel = db_fetch_object($check_sub)) {
                    $cnt[] = $sublevel->cat_name;
                }

                if (count($cnt) > 0) {
                    $class = "arrow-right";
                    $link = 'onclick="loadSubCat(\'' . $gSitePath . 'category/list/' . $client_key[$i] . '\',\'' . $client_array[$i] . '\')"';
                    $class_li = '';
                } else {
                    $link = 'href=' . $gSitePath . 'category/';
                    $class = "";
                    $class_li = '';
                }
                $strReturn .= '<li class="divider"><a  id="mootoolsLink" class="returnFalse ' . $class . '"  ' . $link . '>' . $client_array[$i] . '</a>';
                $strReturn.=sub_menu_cat($client_key[$i], $level + 1);

                $strReturn.='</li>';
            }



            $strReturn.='</ul>';
        }
    }
    return $strReturn;
}

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

/**
 * Theme function for a list of heartbeat activity messages.
 */
function newtheme_heartbeat_list($messages, HeartbeatAccess $heartbeatAccess, $link = '') {

    global $user, $language;
    //echo '<pre>';
    //print_r($heartbeatAccess);
    $content = '';

    drupal_add_css(drupal_get_path('module', 'heartbeat') . '/heartbeat.css');

    $access_type = drupal_strtolower($heartbeatAccess->getAccess());
    $stream = $heartbeatAccess->stream;

    if ($stream->display_filters) {
        $content .= theme('heartbeat_filters', $stream);
    }

    $class = $heartbeatAccess->isPage() ? 'page' : 'block';

    //$content .= '<div id="heartbeat-stream-' . $access_type . '" class="heartbeat-' . $class  . ' heartbeat-stream heartbeat-stream-' . $access_type . '">';
    //$content .= '<div class="heartbeat-messages-wrapper">';

    $content .= '<div style="float: left;" class="commu3"><div class="inner">';
    //$content .= '<div class="clr"></div>';

    if (empty($messages)) {
        if ($heartbeatAccess->hasErrors()) {
            $content .= '<p>' . implode('<br />', $heartbeatAccess->getErrors()) . '</p>';
        } else {
            $content .= '<p>' . t('No activity yet.') . '</p>';
        }
    } else {
        $content .= theme('heartbeat_messages', $messages, $heartbeatAccess, $link);
    }

    $content .= '</div>';
    $content .= '</div>';



    return $content;
}

function newtheme_user_profile($account) {
    $output = '<div class="profile">';
    $output.='Hi ' . $account->name . '<br />';
    $output .= '</div>';
    $output .= '<p>Your 10 most recent posts</p>';

    $uid = $account->uid;
    $result = db_query_range(db_rewrite_sql("SELECT n.nid, n.title FROM {node} n WHERE n.uid = %d and n.status=1 ORDER BY n.changed DESC"), $uid, 0, 10);

    $output .= '<ul>';
    while ($data = db_fetch_object($result)) {
        $edit = "/node/" . $data->nid . "/edit";

        $output .= '<li>' . l(check_plain($data->title), "node/$data->nid") . ' <a href="' . $edit . '">edit</a></li>';
    }
    $output .= '</ul>';

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
