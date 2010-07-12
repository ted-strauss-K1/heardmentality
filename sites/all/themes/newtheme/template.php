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
	 if ((arg(1) == 'block')) {
        $vars['template_files'][0] = 'page-test';
      }
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

function phptemplate_variables($hook, $variables = array()) {

  switch ($hook) {
    case 'page':
      if ((arg(0) == 'blog')) {
        $variables['template_file'] = 'page-blog';
      }
      break;
  }

  return $variables;
}

function sub_menu_cat($id='',$level='')
{
	global $gSitePath;
	$strReturn = null;
	if($level<1){
			 $client_select =db_query("SELECT cat_id,cat_name FROM {category} where parent_id='".$id."'");
			
			$client_array=array();
			$client_key=array();
		
			while($list=db_fetch_object($client_select))
			{
		
		   $client_array[] = $list->cat_name;
			$client_key[]=$list->cat_id;
		
			}
								
			if(count($client_array)>0){
		
			
				 $strReturn.='<ul >';
			 
				 for($i=0;$i<count($client_array);$i++){
				 
				  $check_sub =db_query("SELECT cat_id,cat_name FROM {category} where parent_id='".$client_key[$i]."'");
				  	$cnt=array();
				  while($sublevel=db_fetch_object($check_sub)){
				  $cnt[]=$sublevel->cat_name;
				  }
				
					if(count($cnt)>0){
					$class="arrow-right";
					$link='onclick="loadSubCat(\''.$gSitePath.'category/list/'.$client_key[$i].'\',\''.$client_array[$i].'\')"';
					$class_li='';
					}else{
						$link='href='.$gSitePath.'category/';
					$class="";
					$class_li='';
					}
				$strReturn .= '<li class="divider"><a  id="mootoolsLink" class="returnFalse '.$class.'"  '.$link.'>'.$client_array[$i].'</a>';
				 $strReturn.=sub_menu_cat($client_key[$i],$level+1);
				 
				$strReturn.='</li>';
			}
		
		
			
		 $strReturn.='</ul>';
		 
		 }
	}
	return $strReturn;

}
?>
