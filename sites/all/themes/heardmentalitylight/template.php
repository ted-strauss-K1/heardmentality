<?php

/**
 * Preprocess Drupal Status Messages
 *
 * @author odyachenko
 *
 * @param null $display
 * @return bool
 */
function heardmentalitylight_status_messages($display = NULL) {
  $noty = array();
//  $noty_pattern = "$.hrd.noty({'text':'%s','type':'%s'});";
  $noty_pattern = "$.hrd.noty(%s);";
  foreach (drupal_get_messages($display) as $type => $messages) {
    $noty_type = FALSE;
    switch ($type) {
      case 'status' :
        $noty_type = 'success';
      break;
      case 'warning' :
        $noty_type = 'warning';
      break;
      case 'error' :
        $noty_type = 'error';
      break;
    }
    if ($noty_type !== FALSE) {
      foreach ($messages as $message) {
//        $noty[] = sprintf($noty_pattern, addslashes($message), $noty_type);
        $noty[] = sprintf($noty_pattern, json_encode(array(
          'text' => $message,
          'type' => $noty_type,
        ) + ($noty_type == 'error' && preg_match('/password/', $message) ?
          array('timeout' => FALSE) : array()
        )));
      }
    }
  }
  drupal_add_js('$(document).ready(function(){'.implode('',$noty).'});', 'inline');
  return FALSE;
}


/**
 * Preprocess Pages
 *
 * @param $vars
 */
function heardmentalitylight_preprocess_page(&$vars) {
  // TODO - I dunno what this is for
  if($vars['node']->type == 'static_pages' || $vars['node']->type == 'page'|| $vars['node']->type == 'webform'){
    $suggestions = array('page-static-pages');
    $vars['template_files'] = array_merge($vars['template_files'], $suggestions);
  }

  if ($_GET['q'] == variable_get('site_403', '') || $_GET['q'] == variable_get('site_404', '')) {
    array_push($vars['template_files'], 'page-error');
  }

  if ((arg(0)=='node') && is_numeric(arg(1))) {
    if ($node = $vars['node']) {
      switch ($node->type) {
        case 'poll' :
          # set specific page templates
          drupal_set_subtitle(t('Issue'));
          array_push($vars['template_files'], 'page_12_4');
          $vars['content_class'] = 'poll-box';
        break;
        case 'static' :
          drupal_set_subtitle(drupal_get_title());
          array_push($vars['template_files'], 'page_12_4');
        break;
      }
    }
  }

  if (arg(0) == 'issue' && arg(1) == 'create') {
    drupal_set_subtitle(t('Add an Issue'));
	array_push($vars['template_files'], 'page_11_5');
    $vars['content_class'] = 'grey-box';
    $vars['content_nowrap'] = TRUE;
  }

  # js setting for all modules to use
  global $language;
  drupal_add_js(array('language' => $language->language), 'setting');

}

/**
 * Preprocess Node Pages
 *
 * @param $vars
 */
function heardmentalitylight_preprocess_node(&$vars) {
  $node = &$vars['node'];

  # js setting for all modules to use
  drupal_add_js(array('node' => array('nid' => $node->nid)), 'setting');
}























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
  $vars['styles'] = drupal_get_css();

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

//    $query = db_query("SELECT * FROM {moderator_messages} WHERE to_uid = '$user->uid' AND status = '0' ORDER BY id DESC");
//    while($res = db_fetch_object($query)){
//        $notify[] = $res;
//    }
//    $vars['notify'] = $notify;
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
    $picture = theme('image', $picture, $alt, $alt,$attr, FALSE);
    if (!empty($account->uid) && user_access('access user profiles')) {
      $picture = l($picture, "user/profile/view/$account->name", array('html' => TRUE));
    }

    return $picture;
  }
}
function phptemplate_preprocess_node(&$vars) {
  if (arg(0) == 'issues' or arg(0) == 'issues_solr2') {
    $suggestions = array(
      'node-issues'
    );
    $vars['template_files'] = array_merge($vars['template_files'], $suggestions);
  }
}


/**
 * @return array
 */
function heardmentalitylight_theme(){
  $theme = array();

  $theme['moderation_pager'] = array(
    'arguments' => array(
      'page' => 1,
      'pages' => 1,
      'pattern' => NULL,
    ),
  );

  $theme['gpager'] = array(
    'arguments' => array(
      'page' => 1,
      'pages' => 1,
      'count' => 0,
      'perpage' => 5,
    ),
  );
  $theme['gpager_link'] = array(
    'arguments' => array(
      'page' => 1,
      'page_active' => 1,
      'anchor' => FALSE,
    ),
  );

  return $theme;
}

/**
 * @param $page
 * @param $pages
 * @param $count
 * @param $perpage
 * @param string $theme_callback
 * @return string
 */
function heardmentalitylight_gpager($page, $pages, $count, $perpage, $theme_callback = 'gpager_link') {
  if (is_null($pages)) {
    $pages = ceil($count/$perpage);
  }
  if ($pages <= 0) {
    $pages = 1;
  }
  if (($page <= 0) || ($page > $pages)) {
    $page = 1;
  }
  if (1 == $pages) return '';

  $show_l = min(5,$page-1);
  $show_r = min(9-$show_l, $pages-$page);
  $output = '<div class="mod-pager"><span class="mod-text">PAGE</span> &nbsp;';
  if ($page - $show_l > 1) {
    $output .= theme($theme_callback, $page-1, $page, '<');
    $output .= '<span class="mod-spacer">&nbsp;</span>';
  }
  for ($i = $page-$show_l; $i <= $page-1; $i++) {
    $output .= theme($theme_callback, $i, $page);
  }
  $output .= theme($theme_callback, $page, $page);
  for ($i = $page+1; $i <= $page+$show_r; $i++) {
    $output .= theme($theme_callback, $i, $page);
  }
  if ($page + $show_r < $pages) {
    $output .= '<span class="mod-spacer">&nbsp;</span>';
    $output .= theme($theme_callback, $page+1, $page, '>');
  }
  $output .= '</div>';
  return $output;
}

/**
 * @param $page
 * @param $page_active
 * @param bool $anchor
 * @return string
 */
function heardmentalitylight_gpager_link($page, $page_active, $anchor = FALSE) {
  return sprintf('<a href="?page=%d" class="%s">%s</a>',
    $page,
    $page == $page_active ? 'mod-active' : '',
    FALSE == $anchor ? $page : $anchor
  );
}

/**
 * Theme for pager
 *
 * @param $page
 * @param $pages
 * @param $pattern
 * @return string
 */
function heardmentalitylight_moderation_pager($page, $pages, $pattern)
{
  if ($pages == 1) return '';
  if ($page > $pages) $page = $pages;
  $output = '<div class="mod-pager"><span class="mod-text">PAGE</span> &nbsp;';
  $a = '<a href="/%s" class="%s">%d</a>';
  $showpages = array_unique(array(1, 2, $page - 1, $page, $page + 1, $pages - 1, $pages));
  $flag = TRUE;
  for ($i = 1; $i <= $pages; $i++) {
    if (in_array($i, $showpages)) {
      $output .= sprintf($a, sprintf($pattern, $i), $page == $i ? 'mod-active' : '', $i);
      $flag = TRUE;
    } elseif ($i == 3 || $i == $pages - 2) {
      if ($flag) $output .= '<span class="mod-spacer">&nbsp;</span>';
      $flag = FALSE;
    }
  }
  $output .= '</div>';
  return $output;
}