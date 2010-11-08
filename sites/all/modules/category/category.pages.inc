<?php
// tree menu listing
function treemenu_list() {
    global $gSitePath,$user,$gDocPath,$base_root;
    
    drupal_add_css(drupal_get_path('module', 'category').'/styles/jquery.treeview.css');
    drupal_add_css(drupal_get_path('module', 'category').'/styles/screen.css');
    drupal_add_js(drupal_get_path('module', 'category').'/scripts/jquery.cookie.js');
    drupal_add_js(drupal_get_path('module', 'category').'/scripts/jquery.treeview.js');
    drupal_add_js(drupal_get_path('module', 'category').'/scripts/demo.js');
    drupal_add_js(drupal_get_path('module', 'category').'/scripts/demo.js');
    $strReturn = '';
    
    $client_select = db_query("SELECT cat_id,cat_name FROM {category} where parent_id='0'");
    
    $client_array = array();
    $client_key = array();
    
    while ($list = db_fetch_object($client_select)) {
        
        $client_array[] = $list->cat_name;
        $client_key[] = $list->cat_id;
    
    }
    
    $strReturn .= '<div id="catlist"><b>Category Tree View</b>';
    if (user_access("administer nodes")) {
        // Do something.
        $strReturn .= '&nbsp;[<a href="'.$gSitePath.'category/add/0" >Add New</a>]';
    }
    $strReturn .= '</div>';
    
    $strReturn .= '<ul id="navigation">';
    
    for ($i = 0; $i < count($client_array); $i++) {

         $fol_qry = db_query("SELECT count(*) as count FROM {follower} where uid='".$user->uid."'and cat_id='".$client_key[$i]."'");
          $fol_list = db_fetch_object($fol_qry);

          if($fol_list->count==1)
          {
                $follow = "UnFollow";
          }
          if($fol_list->count==0)
          {
              $follow = "Follow";
          }


        $strReturn .= '<li> <div><a href="'.$gSitePath.'searchquestion?cid='.$client_key[$i].'" >'.stripslashes($client_array[$i]).'</a>&nbsp|&nbsp<a id="ajaxpageLinkCheck" href="'.$gSitePath.'searchquestion/'.$follow.'/'.'catid='.$client_key[$i].'">'.$follow.'</a></div>';
        if (user_access("administer nodes")) {
            // Do something.
            
            $strReturn .= '&nbsp;<a href="'.$gSitePath.'category/add/'.$client_key[$i].'">Add</a>&nbsp;|&nbsp;<a id="ajaxpageLinkCheck" href="'.$gSitePath.'category/edit/'.$client_key[$i].'">Edit </a>';
            $strReturn .= '&nbsp;|&nbsp;<a id="ajaxpageLinkCheck" href="'.$gSitePath.'category/delete/'.$client_key[$i].'">Delete </a>';
            //$strReturn .= '&nbsp;|&nbsp;<a id="ajaxpageLinkCheck" href="'.$gSitePath.'searchquestion/follow/'.'catid='.$client_key[$i].'">Follow</a>';
        }
        $strReturn .= sub_menu($client_key[$i], 0);
        $strReturn .= '</li>';
    }
 //<a href="'.$gSitePath.'searchquestion/follow/'.'catid='.$user_result->cat.'">Follow</a>
    
    $strReturn .= '</ul>';
    
    if (count($client_array) < 1) {
        drupal_set_message($message = 'No category Found!', $type = 'error');
    }
    
    return $strReturn;


}

//list categories
function category_list() {
    
    $nid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    
    echo sub_menu($nid, 0);

    
    return;

}


// category add

function treemenu_add() {

    
    global $gSitePath,$user,$gDocPath;
    return drupal_get_form('cat_add');

}

//category Edit

function treemenu_edit() {

    
    global $gSitePath,$user,$gDocPath;
    return drupal_get_form('cat_edit');

}


//category add core form build

function cat_add() {

    
    $form['cname'] = array('#type'=>'textfield', '#title'=>t('Category Name'), '#size'=>60, '#maxlength'=>50, '#required'=>TRUE, );
    $form['submit'] = array('#type'=>'submit', '#value'=>t('Add'));
    $form['#validate'][] = 'cat_add_validate';
    $form['cancel'] = array('#type'=>'button', '#attributes'=>array('onClick'=>'location.replace("'.referer_uri().'"); return false;'), '#value'=>t('Cancel'), );
    
    return $form;
}
// category edit form
function cat_edit() {
    $nid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $iscat = treemenu_get($nid);
    $form['cname'] = array('#type'=>'textfield', '#title'=>t('Category Name'), '#size'=>60, '#default_value'=>stripslashes($iscat->cat_name), '#maxlength'=>50, '#required'=>TRUE, );
    $form['submit'] = array('#type'=>'submit', '#value'=>t('Update'));
    $form['#validate'][] = 'cat_edit_validate';
    $form['cancel'] = array('#type'=>'button', '#attributes'=>array('onClick'=>'location.replace("'.referer_uri().'"); return false;'), '#value'=>t('Back'), );
    
    return $form;
}

//delete confirm

function menu_delete_confirm(&$form_state, $category) {
    
    $form['_menu'] = array('#type'=>'value', '#value'=>$menu, );
    $form['cat'] = array('#type'=>'hidden', '#value'=>$category, );
    
    return confirm_form($form, t('Are you sure you want to delete this category?'), isset($_GET['destination']) ? $_GET['destination'] : "admin/category/", t('This action cannot be undone.'), t('Delete'), t('Cancel'));
}
// delete category
function menu_delete_confirm_submit($form, &$form_state) {
    $form_values = $form_state['values'];
    
    if ($form_state['values']['confirm']) {
        $menu = $form_state['values']['cat'];
        
        db_query("delete from {category} where cat_id='".$menu."'");
        
        drupal_set_message(t('Cateogry has been deleted successfully.'), 'success');
    }
    
    drupal_goto("admin/category/");
}

// category menu add validation
function cat_add_validate($form, &$form_state) {
   // print_r($_REQUEST[q]);
 $pos = substr($_REQUEST[q],strrpos($_REQUEST[q], "/"));
$get_value =  ltrim($pos,"/");


    $cname = trim($form_state['values']['cname']);
    if($get_value=='add')
    {
    $iscat = treemenu_load(array('category'=>$cname, 'status'=>1, 'case'=>'add'));
    }
    else
    {
       
         $iscat = treemenu_load(array('category'=>$cname,'id'=>$get_value, 'status'=>1, 'case'=>'exist'));
    }
    
    if (!$iscat) {
        //	form_set_value(array('#parents' => array('account')), $account, $form_state);
    } else {
        
        form_set_error('cname', t('Sorry, %cname is already exist in our category!', array('%cname'=>$cname)));
    }
}

// category menu Edit validation
function cat_edit_validate($form, &$form_state) {
    $cname = trim($form_state['values']['cname']);

    
    $iscat = treemenu_load(array('category'=>$cname, 'status'=>1, 'case'=>'edit'));
    
    if (!$iscat) {
        //	form_set_value(array('#parents' => array('account')), $account, $form_state);
    } else {
        
        form_set_error('cname', t('Sorry, another category %cname is already exist!', array('%cname'=>$cname)));
    }
}


// cat add submit
function cat_add_submit($form, &$form_state) {
    global $language,$gSitePath;
    $nid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    //$result = db_query("INSERT INTO {category} set cat_name='".$form_state['values']['cname']."'");
     $html_special =   addslashes($form_state['values']['cname']);
    $result = db_query("INSERT INTO {category} (cat_name,parent_id) VALUES ('%s', %d)", $html_special, $nid);
    drupal_set_message(t('Category added successfully!'), 'success');
    
    $form_state['redirect'] = $gSitePath.'admin/category/';
    return;
}
//cat update save
function cat_edit_submit($form, &$form_state) {
    global $language,$gSitePath;
    $nid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
 
 $html_special =   addslashes($form_state['values']['cname']);
    $result = db_query("UPDATE  {category} set cat_name='".$html_special."' where cat_id='".$nid."'");
    //  $result =   db_query("INSERT INTO {category} (cat_name,parent_id) VALUES ('%s', %d)", $form_state['values']['cname'],$nid);
    drupal_set_message(t('Category Updated successfully!'), 'success');
    
    $form_state['redirect'] = $gSitePath.'admin/category/';
    return;
}


// load category
function cat_list_load($cat_id) {
    
    $query = "SELECT * FROM {category} WHERE cat_id = %d";
    $rs = db_query($query, $doctorid);
    
    if ($rs) {
        while ($data = db_fetch_object($rs)) {
            return $data;
        }
    }
    
    return FALSE;


}

//load menu validation
function treemenu_load($array = array()) {
    $case = $array['case'];
    
    switch ($case) {
        case add:
            $result = db_query("SELECT * FROM {category} where cat_name='".$array['category']."'");
            if ($menu = db_fetch_object($result)) {
                if ($menu != '') {
                    $menu = $menu;
                
                } else
                    $menu = '';
            } else {
                $menu = '';
            }
            return $menu;
            break;
        case edit:
            $nid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
            
            $result = db_query("SELECT * FROM {category} where cat_name='".$array['category']."' AND cat_id!='".$nid."'");
            if ($menu = db_fetch_object($result)) {
                if ($menu != '') {
                    $menu = $menu;
                
                } else
                    $menu = '';
            } else {
                $menu = '';
            }
            return $menu;
            
            break;

            case exist:
            $result = db_query("SELECT * FROM {category} where cat_name='".$array['category']."' and parent_id='".$array['id']."'");
                
            if ($menu = db_fetch_object($result)) {
                if ($menu != '') {
                    $menu = $menu;

                } else
                    $menu = '';
            } else {
                $menu = '';
            }
            return $menu;
            break;
    
    }
}
//get menu by id
function treemenu_get($nid = '') {
    
    $result = db_query("SELECT * FROM {category} where cat_id='".$nid."'");
    if ($menu = db_fetch_object($result)) {
        if ($menu != '') {
            $menu = $menu;
        
        } else
            $menu = '';
    } else {
        $menu = '';
    }
    return $menu;

}

// recursive sub menu

function sub_menu($id = '', $level = '') {
    $strReturn = null;
     global $gSitePath,$user,$gDocPath,$base_root;
    if ($level < 2) {
        
        $client_select = db_query("SELECT cat_id,cat_name,(select cat_name from {category} where cat_id='$id') as mcat FROM {category} where parent_id='".$id."'  ");
        
        $client_array = array();
        $client_key = array();
        
        while ($list = db_fetch_object($client_select)) {
            
            $client_array[] = $list->cat_name;
            $client_key[] = $list->cat_id;
            $mcat = $list->mcat;
        }
       // $strReturn .= '<div><a href="'.$gSitePath.'searchquestion?cid='.$id.'" >'.$mcat.'</a></div>';
        if (count($client_array) > 0) {
            $strReturn .= '<ul >';
            
            for ($i = 0; $i < count($client_array); $i++) {

                
                //echo $level;
                if ($level == 0) {
                    $lnrk = 'cid='.$id.'&scid='.$client_key[$i].'';
                
                }
                if ($level == 1) {
                    $lnr = 'scid='.$id.'&sscid='.$client_key[$i].'';
                }

                
                // $strReturn .= '<li><a href="'.$gSitePath.'searchquestion?cid='.$id.'&scid='.$client_key[$i].'">'.$client_array[$i].' </a>';
                $strReturn .= '<li><a href="'.$gSitePath.'searchquestion?'.$lnrk.''.$lnr.'">'.stripslashes($client_array[$i]).' </a>';
                if (user_access("administer nodes")) {
                    // is admin
                    if ($level == 0) {
                        $strReturn .= '&nbsp; <a id="ajaxpageLinkCheck" href="add/'.$client_key[$i].'">Add </a>';
                    }
                    
                    $strReturn .= '&nbsp;|&nbsp;<a id="ajaxpageLinkCheck" href="edit/'.$client_key[$i].'">Edit </a>';
                    $strReturn .= '&nbsp;|&nbsp;<a id="ajaxpageLinkCheck" href="delete/'.$client_key[$i].'">Delete </a>';
                }
                $strReturn .= '|&nbsp<a id="ajaxpageLinkCheck" href="'.$gSitePath.'searchquestion/follow/'.'catid='.stripslashes($client_key[$i]).'">Follow</a>';
                $strReturn .= sub_menu($client_key[$i], $level + 1);
                
                $strReturn .= '</li>';
            }

            
            $strReturn .= '</ul>';
        
        }
    }
    return $strReturn;

}

function category_admin() {
	 $strReturn = null;
    global $gSitePath,$user,$gDocPath,$base_root;
    drupal_add_js(drupal_get_path('module', 'category').'/scripts/admincat.js');
    $query = "SELECT cat_id,cat_name,IFNULL((select count(*) from {question} where cid=cat_id),0) as qcnt FROM {category} where parent_id='0'";
    $list = ExecuteQuery($query, "select");
    
    $strReturn .= '<div class="">
	
	<div align="right"><a href="'.$gSitePath.'admin/category/add">Add New</a></div>
	<form id="qadmin" method="post" action="'.$gSitePath.'admin/panelc/flagsave" >
	<table width="98%" border="1" cellspacing="5" cellpadding="5">';
    foreach ($list as $quest) {
      
        $strReturn .= '<tr><td>';
        $strReturn .= '<a href="javascript:void(0);" onclick="toggle_sub('.$quest['cat_id'].');">'.stripslashes($quest['cat_name']).'</a>';
        $strReturn .= '</td>';
        $strReturn .= '<td>#Questions : '.$quest['qcnt'].'</td><td>';
        
        $strReturn .= '<!--<input type="checkbox" class="check-me" name="qids[]" value="'.$quest['cat_id'].'" />--><a id="" href="'.$gSitePath.'admin/category/add/'.$quest['cat_id'].'">Add </a> <b>|</b> <a href="'.$gSitePath.'admin/category/delete/'.$quest['cat_id'].'">Delete</a> <b>|</b><a href="'.$gSitePath.'admin/category/edit/'.$quest['cat_id'].'">Edit</a>  ';
        
        $strReturn .= '</td></tr>';
       
        $strReturn .= '<tr  id="q'.$quest['cat_id'].'" style="display: none;"><td colspan="2" >'.admin_sub_menu($quest['cat_id'], 0).'</td></tr>';
       
    }

    
    if (count($list) < 1) {
        //  drupal_set_message($message = 'No Questions Found!', $type = 'error');
        $strReturn .= ' <div class="error" align="left" >No Questions Found!</div> ';
    } else {
        
        $strReturn .= '</table></form></div>';
    }
    
    return $strReturn;

}

function admin_sub_menu($id = '', $level = '') {

    $strReturn = null;
    $mcat = '';
    $flag_date = '';
    global $gSitePath,$user,$gDocPath,$base_root;
    if ($level < 2) {
        
        $client_select = db_query("SELECT cat_id,cat_name FROM {category} where parent_id='".$id."'  ");
        
        $client_array = array();
        $client_key = array();
        
        while ($list = db_fetch_object($client_select)) {
            if (! empty($list)) {
                
                $client_array[] = $list->cat_name;
                $client_key[] = $list->cat_id;
                
            
            }
        
        }
        
        if (count($client_array) > 0) {
            $strReturn .= '<ul >';
            
            for ($i = 0; $i < count($client_array); $i++) {

                
                // $strReturn .= '<li><a href="'.$gSitePath.'searchquestion?cid='.$id.'&scid='.$client_key[$i].'">'.$client_array[$i].' </a>';
                $strReturn .= '<li>'.stripslashes($client_array[$i]).'';
                if (user_access("administer nodes")) {
                    // is admin
                    if ($level == 0) {
                        $strReturn .= '&nbsp; <a id="" href="'.$gSitePath.'admin/category/add/'.$client_key[$i].'">Add </a>';
                    }
                    
                    $strReturn .= '&nbsp;|&nbsp;<a id="" href="'.$gSitePath.'admin/category/edit/'.$client_key[$i].'">Edit </a>';
                    $strReturn .= '&nbsp;|&nbsp;<a id="" href="'.$gSitePath.'admin/category/delete/'.$client_key[$i].'">Delete </a>';
                }
                $strReturn .= admin_sub_menu($client_key[$i], $level + 1);
                
                $strReturn .= '</li>';
            }

            
            $strReturn .= '</ul>';
        
        }
    }
    $get = trim($strReturn);
    if ( empty($get)) {
        
        //$strReturn.='<b>No Sub Category!</b>';
    }
    return $strReturn;

}



