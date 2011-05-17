<?php

// tree menu listing
function treemenu_list() {
    global $gSitePath, $user, $gDocPath, $base_root;

    drupal_add_css(drupal_get_path('module', 'category') . '/styles/jquery.treeview.css');
    drupal_add_css(drupal_get_path('module', 'category') . '/styles/screen.css');
    drupal_add_js(drupal_get_path('module', 'category') . '/scripts/jquery.cookie.js');
    drupal_add_js(drupal_get_path('module', 'category') . '/scripts/jquery.treeview.js');

    $ijs='$(document).ready(function(){

	// first example
        jQuery("div.item-list").removeAttr("class");
	jQuery("#navigation").treeview({
		animated: "slow",
		collapsed: true,
		unique: true,
		persist: "cookie",
		toggle: function() {
			window.console && console.log("%o was toggled", this);
		}
	});



});';
    drupal_add_js($ijs,$type = 'inline');
     $path = drupal_get_path('module', 'vocabindex');
  //drupal_add_css($path . '/vocabindex.css', 'module', 'screen', FALSE);
  // Only add the JavaScript file if this is a tree view.
   // drupal_add_js($path . '/vocabindex.js');

    $strReturn = '';
   $vocabs=section_get_vocabulary_by_name("Sections");



 // module_load_include('inc', 'vocabindex', 'vocabindex.view');
  // $vi = vocabindex_vi_load(VOCABINDEX_VI_BLOCK, $vocabs->vid);
    $pid = $type == VOCABINDEX_TERM ? $vocabs->tid : 0;
    $tree = taxonomy_get_tree($vocabs->vid, $pid, -1, $vi->depth);

    // Display an error message if there are no terms.
    if (count($tree) == 0) {
      return  t('There are currently no terms in this vocabulary.');
    }
    // We do have terms, so render them.
    else {
      // Calculate node counts.
    //  foreach ($tree as $term) {
   //     $term->node_count = $vi->node_count ? taxonomy_term_count_nodes($term->tid) : 0;
    //  }

    //  $children = vocabindex_get_children($tree);

      // Render the list-items.
    //  $view = vocabindex_convert_view($vi->view);
    //  $output = call_user_func('section_list_render_tree', $tree, $children, $vi);
      // Render the list.
    // $strReturn = theme('item_list', $output['list_items'], NULL, 'ul', array('class' => 'treeview ','id'=>'navigation'));
   $vid =$vocabs->vid;  // Set the vid to the vocabulary id of the vocabulary you wish to list the terms from
    return _get_taxonomy_tree2($vid);
    }
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
        $strReturn .= '&nbsp;[<a href="' . $gSitePath . 'category/add/0" >Add New</a>]';
    }
    $strReturn .= '</div>';

    $strReturn .= '<ul id="navigation">';

    for ($i = 0; $i < count($client_array); $i++) {

        $fol_qry = db_query("SELECT count(*) as count FROM {follower} where uid='" . $user->uid . "'and cat_id='" . $client_key[$i] . "'");
        $fol_list = db_fetch_object($fol_qry);

        if ($fol_list->count == 1) {
            $follow = "UnFollow";
        }
        if ($fol_list->count == 0) {
            $follow = "Follow";
        }


        $strReturn .= '<li> <div><a href="' . $gSitePath . 'searchquestion?cid=' . $client_key[$i] . '" >' . stripslashes($client_array[$i]) . '</a>&nbsp|&nbsp<a id="ajaxpageLinkCheck" href="' . $gSitePath . 'category/' . $follow . '/' . 'catid/' . $client_key[$i] . '">' . $follow . '</a></div>';
        if (user_access("administer nodes")) {
            // Do something.

            $strReturn .= '&nbsp;<a href="' . $gSitePath . 'category/add/' . $client_key[$i] . '">Add</a>&nbsp;|&nbsp;<a id="ajaxpageLinkCheck" href="' . $gSitePath . 'category/edit/' . $client_key[$i] . '">Edit </a>';
            $strReturn .= '&nbsp;|&nbsp;<a id="ajaxpageLinkCheck" href="' . $gSitePath . 'category/delete/' . $client_key[$i] . '">Delete </a>';
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

function _get_taxonomy_tree2($vid) {
  global $gSitePath, $user;
  $pole = array();
  $items = array();
  $terms = taxonomy_get_tree($vid);
  //$output = '<li>' . taxonomy_vocabulary_load($vid)->name;
  foreach ($terms as $term) {
    $count = db_result(db_query("SELECT COUNT(nid) FROM {term_node} WHERE tid = %d", $term->tid));
    $foll = db_result(db_query("SELECT COUNT(sid) FROM {subscriptions} WHERE field = '%s' AND value = '%d' AND recipient_uid = '%d'", 'tid', $term->tid, $user->uid));
    $pole[] = Array(
      l($term->name, "taxonomy/term/$term->tid") . " ($count)", $term->depth, $count, $term->tid, $foll
    );
  }
  $depth = -1;
  foreach ($pole as $list) {
    if ($list[1] > $depth) $output .= "<ul id='navigation'>";
    if ($list[1] < $depth) {
      for ($i=$list[1]; $i<$depth; $i++)
        $output .= "</li></ul></li>";
    }
    if ($list[1] == $depth) $output .= "</li>";
    $dest = '?destination=category';
    $subscription = $list[4]==1?"<a href='".$gSitePath."subscriptions/del/taxa/".$list[3].$dest."' title='unfollow'>unfollow</a>":"<a href='".$gSitePath."subscriptions/add/taxa/".$list[3].$dest."' title='follow'>follow</a>";
    $output .= "<li>$list[0]&nbsp;&nbsp;<span>$subscription</span>";

    $depth = $list[1];
  }
  for ($i=0; $i<=$depth; $i++)
    $output .= "</li></ul>";;
  return $output;
} 
function section_list_render_tree($tree, $children, $vi) {
  //Prepare the tree; use the TIDs as keys for easy access to the terms.
  $tree_buffer = array();
  for ($i = 0, $len_i = count($tree); $i < $len_i; $i++) {
    $term = $tree[$i];
    $tree_buffer[$term->tid] = $term;
  }
  $tree = $tree_buffer;

  return array('list_items' => _section_list_render_tree($tree, $children, $vi));
}
function _section_list_render_tree($tree, $children, $vi, $pid = 0, &$zebra_i = 0) {
  $items = array();

  for ($i = 0, $len_i = count($children[$pid]); $i < $len_i; $i++) {
    $zebra_i++;
    $zebra = ($zebra_i % 2 == 0 ? 'even' : 'odd');
    $term = $tree[$children[$pid][$i]];

    $term_children = NULL;
    $parent = NULL;
    if (array_key_exists($term->tid, $children)) {
      $term_children = _section_list_render_tree($tree, $children, $vi, $term->tid, $zebra_i);
    }

    // Render the current term.
    $items[] = array(
      'data' => vocabindex_term_link($term, $vi),
      'children' => $term_children,
   //   'class' => $zebra . (!is_null($term_children) ? ' parent expanded' : NULL),
        'class'=>'expandable',
    );
  }

  return $items;
}

function section_get_vocabulary_by_name($vocabulary_name) {
  $vocabs = taxonomy_get_vocabularies(NULL);

  foreach ($vocabs as $vocab_object) {
    if ($vocab_object->name == $vocabulary_name) {
 
      return $vocab_object;
    }
  }
  return NULL;
}

//list categories
function category_list() {

    $nid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    echo sub_menu($nid, 0);


    return;
}

// category add

function treemenu_add() {

    drupal_add_js(drupal_get_path('module', 'category') . '/scripts/redirect.js');
    global $gSitePath, $user, $gDocPath;
    return drupal_get_form('cat_add');
}

//category Edit

function treemenu_edit() {


    global $gSitePath, $user, $gDocPath;
    return drupal_get_form('cat_edit');
}

//category add core form build


function cat_add() {
    //print_r()
    $form['cname'] = array('#type' => 'textfield', '#title' => t('Category Name'), '#size' => 60, '#maxlength' => 50, '#required' => TRUE,);
    $form['submit'] = array('#type' => 'submit', '#value' => t('Add'));
    $form['#validate'][] = 'cat_add_validate';
    //$form['cancel'] = array('#type'=>'button','#button_type'=>'reset','#submit' => FALSE,'#attributes'=>array('onClick'=>'location.replace("'.referer_uri().'"); return false;'), '#value'=>t('Cancel'), );
    $form['cancel'] = array(
        '#value' => '<input type="button" value="Cancel" id="cancel">',
    );

    //$form['cancel'] = array('#type'=>'button', '#value'=>t('Add'),'#submit' => FALSE);
    return $form;
}

// category edit form
function cat_edit() {
    $nid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $iscat = treemenu_get($nid);
    $form['cname'] = array('#type' => 'textfield', '#title' => t('Category Name'), '#size' => 60, '#default_value' => stripslashes($iscat->cat_name), '#maxlength' => 50, '#required' => TRUE,);
    $form['submit'] = array('#type' => 'submit', '#value' => t('Update'));
    $form['#validate'][] = 'cat_edit_validate';
    $form['cancel'] = array('#type' => 'button', '#attributes' => array('onClick' => 'location.replace("' . referer_uri() . '"); return false;'), '#value' => t('Back'),);

    return $form;
}

//delete confirm

function menu_delete_confirm(&$form_state, $category) {

    $form['_menu'] = array('#type' => 'value', '#value' => $menu,);
    $form['cat'] = array('#type' => 'hidden', '#value' => $category,);

    return confirm_form($form, t('Are you sure you want to delete this category?'), isset($_GET['destination']) ? $_GET['destination'] : "admin/category/", t('This action cannot be undone.'), t('Delete'), t('Cancel'));
}

// delete category
function menu_delete_confirm_submit($form, &$form_state) {
    $form_values = $form_state['values'];

    if ($form_state['values']['confirm']) {
        $menu = $form_state['values']['cat'];

        db_query("delete from {category} where cat_id='" . $menu . "'");

        drupal_set_message(t('Cateogry has been deleted successfully.'), 'success');
    }

    drupal_goto("admin/category/");
}

// category menu add validation
function cat_add_validate($form, &$form_state) {
    // print_r($_REQUEST[q]);
    $pos = substr($_REQUEST[q], strrpos($_REQUEST[q], "/"));
    $get_value = ltrim($pos, "/");


    $cname = trim($form_state['values']['cname']);
    if ($get_value == 'add') {
        $iscat = treemenu_load(array('category' => $cname, 'status' => 1, 'case' => 'add'));
    } else {

        $iscat = treemenu_load(array('category' => $cname, 'id' => $get_value, 'status' => 1, 'case' => 'exist'));
    }

    if (!$iscat) {
        //	form_set_value(array('#parents' => array('account')), $account, $form_state);
    } else {

        form_set_error('cname', t('Sorry, %cname is already exist in our category!', array('%cname' => $cname)));
    }
}

// category menu Edit validation
function cat_edit_validate($form, &$form_state) {
    $cname = trim($form_state['values']['cname']);


    $iscat = treemenu_load(array('category' => $cname, 'status' => 1, 'case' => 'edit'));

    if (!$iscat) {
        //	form_set_value(array('#parents' => array('account')), $account, $form_state);
    } else {

        form_set_error('cname', t('Sorry, another category %cname is already exist!', array('%cname' => $cname)));
    }
}

// cat add submit
function cat_add_submit($form, &$form_state) {
    global $language, $gSitePath;
    $nid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    //$result = db_query("INSERT INTO {category} set cat_name='".$form_state['values']['cname']."'");
    $html_special = addslashes($form_state['values']['cname']);
    $result = db_query("INSERT INTO {category} (cat_name,parent_id) VALUES ('%s', %d)", $html_special, $nid);
    drupal_set_message(t('Category added successfully!'), 'success');

    $form_state['redirect'] = $gSitePath . 'admin/category/';
    return;
}

//cat update save
function cat_edit_submit($form, &$form_state) {
    global $language, $gSitePath;
    $nid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    $html_special = addslashes($form_state['values']['cname']);
    $result = db_query("UPDATE  {category} set cat_name='" . $html_special . "' where cat_id='" . $nid . "'");
    //  $result =   db_query("INSERT INTO {category} (cat_name,parent_id) VALUES ('%s', %d)", $form_state['values']['cname'],$nid);
    drupal_set_message(t('Category Updated successfully!'), 'success');

    $form_state['redirect'] = $gSitePath . 'admin/category/';
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
            $result = db_query("SELECT * FROM {category} where cat_name='" . $array['category'] . "'");
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

            $result = db_query("SELECT * FROM {category} where cat_name='" . $array['category'] . "' AND cat_id!='" . $nid . "'");
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
            $result = db_query("SELECT * FROM {category} where cat_name='" . $array['category'] . "' and parent_id='" . $array['id'] . "'");

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

    $result = db_query("SELECT * FROM {category} where cat_id='" . $nid . "'");
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
    global $gSitePath, $user, $gDocPath, $base_root;
    if ($level < 2) {

        $client_select = db_query("SELECT cat_id,cat_name,(select cat_name from {category} where cat_id='$id') as mcat FROM {category} where parent_id='" . $id . "'  ");

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



                $fol_qry = db_query("SELECT count(*) as count FROM {follower} where uid='" . $user->uid . "'and cat_id='" . $client_key[$i] . "'");
                $fol_list = db_fetch_object($fol_qry);

                if ($fol_list->count == 1) {
                    $follow = "UnFollow";
                }
                if ($fol_list->count == 0) {
                    $follow = "Follow";
                }


                //echo $level;
                if ($level == 0) {
                    $lnrk = 'cid=' . $id . '&scid=' . $client_key[$i] . '';
                }
                if ($level == 1) {
                    $lnr = 'scid=' . $id . '&sscid=' . $client_key[$i] . '';
                }


                // $strReturn .= '<li><a href="'.$gSitePath.'searchquestion?cid='.$id.'&scid='.$client_key[$i].'">'.$client_array[$i].' </a>';
                $strReturn .= '<li><a href="' . $gSitePath . 'searchquestion?' . $lnrk . '' . $lnr . '">' . stripslashes($client_array[$i]) . ' </a>';
                if (user_access("administer nodes")) {
                    // is admin
                    if ($level == 0) {
                        $strReturn .= '&nbsp; <a id="ajaxpageLinkCheck" href="add/' . $client_key[$i] . '">Add </a>';
                    }

                    $strReturn .= '&nbsp;|&nbsp;<a id="ajaxpageLinkCheck" href="edit/' . $client_key[$i] . '">Edit </a>';
                    $strReturn .= '&nbsp;|&nbsp;<a id="ajaxpageLinkCheck" href="delete/' . $client_key[$i] . '">Delete </a>';
                }
                //$strReturn .= '<li> <div><a href="'.$gSitePath.'searchquestion?cid='.$client_key[$i].'" >'.stripslashes($client_array[$i]).'</a>&nbsp|&nbsp<a id="ajaxpageLinkCheck" href="'.$gSitePath.'searchquestion/'.$follow.'/'.'catid='.$client_key[$i].'">'.$follow.'</a></div>';
                $strReturn .= '|&nbsp<a id="ajaxpageLinkCheck" href="' . $gSitePath . 'category/' . $follow . '/' . 'catid/' . stripslashes($client_key[$i]) . '">' . $follow . '</a>';
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
    global $gSitePath, $user, $gDocPath, $base_root;
    drupal_add_js(drupal_get_path('module', 'category') . '/scripts/admincat.js');
    $query = "SELECT cat_id,cat_name,IFNULL((select count(*) from {question} where cid=cat_id),0) as qcnt FROM {category} where parent_id='0'";
    $list = ExecuteQuery($query, "select");

    $strReturn .= '<div class="">
	
	<div align="right"><a href="' . $gSitePath . 'admin/category/add">Add New</a></div>
	<form id="qadmin" method="post" action="' . $gSitePath . 'admin/panelc/flagsave" >
	<table width="98%" border="1" cellspacing="5" cellpadding="5">';
    foreach ($list as $quest) {

        $strReturn .= '<tr><td>';
        $strReturn .= '<a href="javascript:void(0);" onclick="toggle_sub(' . $quest['cat_id'] . ');">' . stripslashes($quest['cat_name']) . '</a>';
        $strReturn .= '</td>';
        $strReturn .= '<td>#Questions : ' . $quest['qcnt'] . '</td><td>';

        $strReturn .= '<!--<input type="checkbox" class="check-me" name="qids[]" value="' . $quest['cat_id'] . '" />--><a id="" href="' . $gSitePath . 'admin/category/add/' . $quest['cat_id'] . '">Add </a> <b>|</b> <a href="' . $gSitePath . 'admin/category/delete/' . $quest['cat_id'] . '">Delete</a> <b>|</b><a href="' . $gSitePath . 'admin/category/edit/' . $quest['cat_id'] . '">Edit</a>  ';

        $strReturn .= '</td></tr>';

        $strReturn .= '<tr  id="q' . $quest['cat_id'] . '" style="display: none;"><td colspan="2" >' . admin_sub_menu($quest['cat_id'], 0) . '</td></tr>';
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
    global $gSitePath, $user, $gDocPath, $base_root;
    if ($level < 2) {

        $client_select = db_query("SELECT cat_id,cat_name FROM {category} where parent_id='" . $id . "'  ");

        $client_array = array();
        $client_key = array();

        while ($list = db_fetch_object($client_select)) {
            if (!empty($list)) {

                $client_array[] = $list->cat_name;
                $client_key[] = $list->cat_id;
            }
        }

        if (count($client_array) > 0) {
            $strReturn .= '<ul >';

            for ($i = 0; $i < count($client_array); $i++) {


                // $strReturn .= '<li><a href="'.$gSitePath.'searchquestion?cid='.$id.'&scid='.$client_key[$i].'">'.$client_array[$i].' </a>';
                $strReturn .= '<li>' . stripslashes($client_array[$i]) . '';
                if (user_access("administer nodes")) {
                    // is admin
                    if ($level == 0) {
                        $strReturn .= '&nbsp; <a id="" href="' . $gSitePath . 'admin/category/add/' . $client_key[$i] . '">Add </a>';
                    }

                    $strReturn .= '&nbsp;|&nbsp;<a id="" href="' . $gSitePath . 'admin/category/edit/' . $client_key[$i] . '">Edit </a>';
                    $strReturn .= '&nbsp;|&nbsp;<a id="" href="' . $gSitePath . 'admin/category/delete/' . $client_key[$i] . '">Delete </a>';
                }
                $strReturn .= admin_sub_menu($client_key[$i], $level + 1);

                $strReturn .= '</li>';
            }


            $strReturn .= '</ul>';
        }
    }
    $get = trim($strReturn);
    if (empty($get)) {

        //$strReturn.='<b>No Sub Category!</b>';
    }
    return $strReturn;
}

function search_follow() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $qry_value = substr($_REQUEST[q], strrpos($_REQUEST[q], "/"));
    $cat_id = ltrim($qry_value, "/");
    // $cat =  explode("/",$_REQUEST['q']);
    //    $catid = explode("=",$cat[2]);

    $res_num = db_result(db_query("SELECT COUNT(*) from follower  where  cat_id='" . $cat_id . "'  and  uid ='" . $user->uid . "'"));

    if (!$res_num) {

        //insert into notification

        db_query("insert into notification(uid,is_cat,node_id)values('" . $user->uid . "',1,'" . $cat_id . "')");
        db_query("insert into follower(uid,cat_id)values('" . $user->uid . "','" . $cat_id . "')");
        $output = drupal_set_message(t('You are now following this section'), $type = 'success');
        echo '<script>window.parent.location.href="' . $gSitePath . 'category/";</script>';
    } else {
        $output = drupal_set_message(t('Section follows already added !'), $type = 'success');
        echo '<script>window.parent.location.href="' . $gSitePath . 'category/";</script>';
    }
}

function search_unfollow() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

    $qry_value = substr($_REQUEST[q], strrpos($_REQUEST[q], "/"));
    $cat_id = ltrim($qry_value, "/");

    //$cat =  explode("/",$_REQUEST['q']);
    //   $catid = explode("=",$cat[2]);

    $res_num = db_result(db_query("SELECT COUNT(*) from follower  where  cat_id='" . $cat_id . "'  and  uid ='" . $user->uid . "'"));


    if ($res_num) {
        db_query("delete from follower where uid='" . $user->uid . "' and cat_id='" . $cat_id . "'");
        $output = drupal_set_message(t('You are now un-following this section'), $type = 'success');
        echo '<script>window.parent.location.href="' . $gSitePath . 'category/";</script>';
    }
}

