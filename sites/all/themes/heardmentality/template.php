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
  }
  else {
    if ($left != '') {
      $class = 'sidebar-left';
    }
    if ($right != '') {
      $class = 'sidebar-right';
    }
  }

  if (isset($class)) {
    print ' class="'. $class .'"';
  }
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
    return '<div class="breadcrumb">'. implode(' › ', $breadcrumb) .'</div>';
  }
}

/**
 * Override or insert PHPTemplate variables into the templates.
 */
function phptemplate_preprocess_page(&$vars) {
  $vars['tabs2'] = menu_secondary_local_tasks();

  // Hook into color.module
  if (module_exists('color')) {
    _color_page_alter($vars);
  }
}

/**
 * Add a "Comments" heading above comments except on forum pages.
 */
function garland_preprocess_comment_wrapper(&$vars) {
  if ($vars['content'] && $vars['node']->type != 'forum') {
    $vars['content'] = '<h2 class="comments">'. t('Comments') .'</h2>'.  $vars['content'];
  }
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

  $iecss = '<link type="text/css" rel="stylesheet" media="all" href="'. base_path() . path_to_theme() .'/fix-ie.css" />';
  if ($language->direction == LANGUAGE_RTL) {
    $iecss .= '<style type="text/css" media="all">@import "'. base_path() . path_to_theme() .'/fix-ie-rtl.css";</style>';
  }

  return $iecss;
}
function user_login_block_new() {
  $form = array(
    '#action' => url($_GET['q'], array('query' => drupal_get_destination())),
    '#id' => 'user-login-form',
    '#validate' => user_login_default_validators(),
    '#submit' => array('user_login_submit'),
  );
  $form['name'] = array('#type' => 'textfield',
    '#title' => t('Username'),
    '#maxlength' => USERNAME_MAX_LENGTH,
    '#size' => 15,
    '#required' => TRUE,
  );
  $form['pass'] = array('#type' => 'password',
    '#title' => t('Password'),
    '#maxlength' => 60,
    '#size' => 15,
    '#required' => TRUE,
  );
  $form['submit'] = array('#type' => 'submit',
    '#value' => t('Log in'),
  );
  $items = array();
 
    $items[] = l(t('Sign In'), 'user/login', array('attributes' => array('title' => t('Sign In'))));

 // $items[] = l(t('Request new password'), 'user/password', array('attributes' => array('title' => t('Request new password via e-mail.'))));
  $form['links'] = array('#value' => theme('item_list', $items));
  return $form;
}

function garland_user_bar() {
  global $user;                                                               
  $output = '';

  if (!$user->uid) {                                                          
    $output .= drupal_get_form('user_login_block_new');   
	// $output .= '&nbsp;'.l(t('Sign In'), 'user/login', array('attributes' => array('title' => t('Sign In'))));                       
  }                                                                           
  else {                                                                      
    $output .= t('<p class="user-info">welcome !user.</p>', array('!user' => theme('username', $user)));
 
    $output .= theme('item_list', array(
      l(t('Your account'), 'user/'.$user->uid, array('title' => t('Edit your account'))),
      l(t('Sign out'), 'logout')));
  }
   
  $output = '<div id="user-bar">'.$output.'</div>';
     
  return $output;
}






?>