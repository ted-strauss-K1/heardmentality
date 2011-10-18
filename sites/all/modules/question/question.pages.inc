<?php
// question add
function question_add() {
    global $gSitePath, $user, $gDocPath, $base_root;
    //get error msgs
    $error = drupal_get_messages();
    $list_err = '';
    if (!empty($error)) {
        $list_err = implode("<br/>", $error['error']);
    }


    //print_r($_SESSION['post']);
    $q_quest = '';
    $optionlist = '';
    $q_context = '';
    $q_ans1 = '';
    $q_ans2 = '';
    if (isset($_SESSION['post']) && !empty($_SESSION['post'])) {
        extract($_SESSION['post']);
    }
    global $gSitePath, $user, $gDocPath, $base_root;
    $output = '';

    $cncode = '';
    $zicode = db_result(db_query("select zip from {user_profile} where uid='$user->uid'"));
    $ustate = db_result(db_query("select state from {user_profile} where uid='$user->uid'"));
    if (!empty($zicode)) {
        if (empty($ustate)) {
            $query = array('postalcode' => $zicode, 'maxrows' => 1);
            $result = geonames_query('postalcodesearch', $query);
            $state = $result->results;

            // print_r($state);
            $cncode = $state['0']['countrycode'];
            $options = array('columns' => array('geonameid', 'countrycode'));
            $query = array('query' => $state['0']['adminname1'], 'maxrows' => 1);
            $result = geonames_query('search', $query, $options);
            $fstate = $result->results;
            //print_r($fstate);
            $setstate = $fstate['0']['geonameid'];
        } else {
            $udet = load_user($user->uid);

            $cncode = $udet->country;
            $setstate = $udet->state;
            $fcity = $udet->city;
        }
    }
    $data=' var mpath=\'' . $gSitePath . '\';
                    var spath=\'' . $gSitePath . '\';
                    var cncode=\'' . $cncode . '\';
                    var ustate=\'' . $ustate . '\';
                    var setstate=\'' . $setstate . '\';
                        var setcity=\'' . $fcity . '\';
                            var admin=0;';
    drupal_add_js($data,'inline');
drupal_add_js(drupal_get_path('module', 'question') . '/scripts/question.js');
drupal_add_js( drupal_get_path('module', 'question') . '/scripts/post_list.js');



    //geoname api
    $options = array('sortby' => 'countryname', 'sortorder' => 'ASC');
    $result = geonames_query('countryinfo', NULL, $options);
//    $optionlist .= ' <option value="0" >--Country--</option>';
//    foreach ($result->results as $country) {
//        $optionlist .= sprintf('<option value="%s">%s</option>', $country['countryname'], $country['countryname']);
//    }



    $output .= '
       <form id="question" name="question" onsubmit="return validate_question();"  method="post" action="' . $gSitePath . 'question/save" >
       <ul id="add_more">
               <li><label><span class="span1">Issue <b>*</b></span><span>
          <input name="q_quest" autocomplete="off" type="text" tabindex="1" id="q_quest" maxlength="140"   size="100" ><br>
        
        </span></label>
        <span class="span1">&nbsp;</span><small> 140 Characters Max.</small>
        </li>

          <li><label><span class="span1">Details</span><span> <textarea name="q_context" rows="4" id="q_context" tabindex="2">' . $q_context . '</textarea> </span></label></li>
         <li><label><span class="span1">Option <b>*</b></span><span> <input tabindex="3" name="q_ans1" type="text" id="q_ans1"  value="' . $q_ans1 . '" size="40" /></span></label></li>
         <li><label><span class="span1">Option <b>*</b></span><span> <input name="q_ans2" tabindex="4" type="text" id="q_ans2"   value="' . $q_ans2 . '" size="40" />
         </span></label></li>
         <li>&nbsp;</li>
       </ul>
       <div class="clr"></div>
       <ul >
         <li>
         <div  style="width:100%;padding-left:20px;">
           <div id="del_ans" style="display:none;padding:2px;">
            <small><a href="javascript:void(0);" tabindex="88" onclick="del_ans();">[Remove]</a></small>
            </div>
       <!--<a href="javascript:void(0);" id="Add" title="Add Answer " tabindex="13"><img src="' . $gSitePath . path_to_theme() . '/images/addanswer.jpg" onclick="add_ans();"  alt="Add Answer" /></a>-->
            <div><div class="but-left"><img src="' . $gSitePath . path_to_theme() . '/images/but-left.jpg"></div>
           <input type="button"  tabindex="13" name="Add" title="Add More Answer" class="but"  onclick="add_ans();" id="Add" value="Add Answer" />
           <div class="but-right">
           <img width="7" height="24" src="' . $gSitePath . path_to_theme() . '/images/but-right.jpg"></div></div>
            <input type="hidden" name="ans_cnt" id="ans_cnt" value="2">
            <input type="hidden" id="cat1" name="cat1" value="">
            <input type="hidden" id="cat2" name="cat2" value="">
            <input type="hidden"  id="cat3" name="cat3" value="">
            <input type="hidden" id="exist_check" name="exist_check" value="">
         
            </div>
         </li>
       </ul>
	  
       <div class="clr"></div>	   
       <div class="do-in2cat">
       <!--<ul >
         <li><span>Categorize <b>*</b></span>:</li>
          <li>
          <div class="listmenu2" title="Select category">
           <select tabindex="14" title="Select sub category"  name="q_cat[]" id="q_cat" class="listbox2" multiple="multiple"  onchange="get_subcat(\'q_cat\',\'chg_scat\',1);" >
            <option value="">Select Category</option>-->';
  //  $client_select = db_query("SELECT cat_id,cat_name FROM {category} where parent_id='0'");
  //  while ($list = db_fetch_object($client_select)) {
   //     $output .= '<option value="' . $list->cat_id . '">' . stripslashes($list->cat_name) . '</option>';
   // }

    $output .= '<!--</select>
        </div>
        </li>
        <li>
              <div class="listmenu2" title="Select Sub Category"  id="chg_scat">

               <select class="listbox2" tabindex="15" title="Select Sub Category"  name="q_scat[]" id="q_scat"  >
               <option value="">Select Sub Category</option>
              </select>
              </div>
       </li>
       <li>
          <div class="listmenu2" title="Select Sub Sub Category" id="chg_sscat">
          <select tabindex="16" title="Select Sub Sub Category"  name="q_sscat[]" id="q_sscat" class="listbox2"  >
          <option value="">Select Sub Sub Category</option>
          </select>
          </div>
       </li>
      </ul>
       <ul >
       <li>Localize:</li>
        <li>
        <div class="listmenu2">
         <select name="q_country" class="listbox2" style="width: 125px;" tabindex="16"  onchange="get_state(this.value);" id="q_country">' . $optionlist . '</select>
	</div>
        </li>
        <li>
        <div class="listmenu2" id="chg_state">
        <select id="q_state" name="q_state" class="listbox2" onchange="get_city(this.value);" style="width: 125px;" tabindex="18"><option value="0" >--State--</option></select>
    </div>
    </li>
        <li>
        <div class="listmenu2" id="chg_city" >
        <select name="q_city" class="listbox2" id="q_city" style="width: 125px;" tabindex="19"> <option value="0" >--Cities--</option></select>
    </div>
    </li>
       </ul>-->
          </div>		  
        <div class="clr"></div>		 
		<div class="do-in2bor"><strong>Related Issue(s):</strong></div>
		<div><span  title="Releted Questions"  id="releated_questions"></span></div>
       </div> 
	   <div class="clr"></div>
		
       <div class="do-in2savetop">';



    $output.=' <div class="clr">&nbsp;</div>
    <span>Required <b>*</b></span><div class="do-in2save" >
      <div><div class="but-left"><img src="' . $gSitePath . path_to_theme() . '/images/but-left.jpg"></div>
         <input type="submit"  class="but" name="save" tabindex="21" title="Submit an Issue" id="save" value="Save" class="question-save"/>
           <div class="but-right">
           <img width="7" height="24" src="' . $gSitePath . path_to_theme() . '/images/but-right.jpg"></div></div>
       </div>
              </div>
         <div class="clr"></div>
        </div>
</form>
       
        ';


    return $output;
}

function get_tagging($tag = '') {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $randomtag = '';
    $content = '';
    $tagged = '';

    $randomtag = popular_tag();
    if ($tag != '') {

        $exp = explode(",", $tag);


        foreach ($exp as $list) {

            $tagged .= '<div id="tagset" class="tagging-tag" onclick="tag_delq(this);return false;">' . $list . '</div>';
        }
    }
    $content .= '<div id="tagging-widget-container">
        <fieldset>
            <legend>
            <b><i>    Tag Question for Searching </i></b>
            </legend>
            <div id="tagdiv" class="tagging-curtags-wrapper tagging-curtags-wrapper-1">
                <label>
                    Assigned Tags:
                </label>
				' . $tagged . '
            </div>
            <div class="form-item" id="tagging-widget-input-1-wrapper">
			
                <span class="field-prefix">
                    <div class="taggin-widget-input-wrapper">
                        <input maxlength="20" tabindex="20" name="taxonomy[tags][1]" id="tagging-widget-input-1" value="" class="form-text form-autocomplete tagging-widget-input tagging-widget-input-1" type="text"><span class="field-suffix"><a class="tagging-button-container" href="#" title="Add"><span class="tagging-button tagging-button-1"></span></a>
						
						<input name="taxonomy[tags][1]" id="edit-taxonomy-tags-1" value="" class="tagging-widget-target-1" type="hidden"></span>
						
						<input name="q_tag" type="hidden" id="q_tag" value="' . $tag . '"  >
                    </div>
                </span>
                <div class="description">
                   Add New Tag
                </div>
            </div>
            <input class="autocomplete" id="tagging-widget-input-1-autocomplete" value="http://localhost/heardmentalitylocal/taxonomy/autocomplete/1" disabled="disabled" type="hidden">
          
		    <div id="sug_div" class="tagging-suggestions-wrapper tagging-suggestions-wrapper-1">
               <label>Suggestions:</label>
               ' . $randomtag . '
            </div>
        </fieldset></div>';


    return $content;
}

function get_tagging_edit($midr) {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $randomtag = '';
    $content = '';
    $tagged = '';

    $randomtag = popular_tag();
    if ($midr != '') {

        // $exp = explode(",", $tag);


        $selmlist = "select * from qtag as a, tagging as b where a.qid='$midr' and a.tag_id=b.tid ";
        $mysqlfet = db_query($selmlist);
        while ($rewdisp = db_fetch_object($mysqlfet)) {
            $tagged .= '<div id="tagset" class="tagging-tag" >' . $rewdisp->tag . '</div>';
        }
    }
    $content .= '<div id="tagging-widget-container">
        <fieldset>
            <legend>
            <b><i>    Tag Question for Searching </i></b>
            </legend>
            <div id="tagdiv" class="tagging-curtags-wrapper tagging-curtags-wrapper-1">
                <label>
                    Assigned Tags:
                </label>
				' . $tagged . '
            </div>
            <div class="form-item" id="tagging-widget-input-1-wrapper">
			
                <span class="field-prefix">
                    <div class="taggin-widget-input-wrapper">
                        <input maxlength="20" tabindex="20" name="taxonomy[tags][1]" id="tagging-widget-input-1" value="" class="form-text form-autocomplete tagging-widget-input tagging-widget-input-1" type="text"><span class="field-suffix"><a class="tagging-button-container" href="#" title="Add"><span class="tagging-button tagging-button-1"></span></a>
						
						<input name="taxonomy[tags][1]" id="edit-taxonomy-tags-1" value="" class="tagging-widget-target-1" type="hidden"></span>
						
						<input name="q_tag" type="hidden" id="q_tag" value="' . $tag . '"  >
                    </div>
                </span>
                <div class="description">
                   Add New Tag
                </div>
            </div>
            <input class="autocomplete" id="tagging-widget-input-1-autocomplete" value="http://localhost/heardmentalitylocal/taxonomy/autocomplete/1" disabled="disabled" type="hidden">
          
		    <div id="sug_div" class="tagging-suggestions-wrapper tagging-suggestions-wrapper-1">
               <label>Suggestions:</label>
               ' . $randomtag . '
            </div>
        </fieldset></div>';


    return $content;
}

function question_save() {

    global $gSitePath, $user, $gDocPath, $base_root;

    $q_quest = '';		
    extract($_REQUEST);
    $output = '';
    $g_global = '';
   // if (!empty($q_quest) && !empty($q_ans1) && !empty($q_ans2) && !empty($q_cat)) {
        if (!empty($q_quest) && !empty($q_ans1) && !empty($q_ans2)) {

       $result=issue_save($_REQUEST);
        

        if ($result->nid){

//        //forum
//
//        $forum = db_query("INSERT INTO {forum_wave} set qid_rid='$ins_id',type='1',uid='$user->uid',title='Discuss about this question',private='0' ");
//
            //create a default debate

               // save values as node
                    $deb = new stdClass();
                    $deb->field_private[0]['value'] ='';
                    $deb->field_ref_qid[0]['nid'] = $result->nid;
                    $deb->field_type[0]['value'] = '1';

                    $deb->type = 'forum';
                    $deb->title = 'What you think about this issue!';
                    $deb->uid = $user->uid;
                  $deb->body = "Let's have a debate";
                    $deb->status = 1;
                    // get tid for debate
                    // get_taxonomy_id('module name','term data name')
                    $tid = get_taxonomy_id('forum','Debate');
                    $deb->taxonomy = array($tid);

                    //node_validate($deb);
                    //$node = node_submit($deb);
                    $save = node_save($deb);
                    
                    // add default debate options
                    $choices = db_query("SELECT * FROM {poll_choices} WHERE nid = '$result->nid'");
                    while($list = db_fetch_object($choices)){
                       //$forum = "INSERT INTO {debate_options} set did='%d', paid='%d',ans_val='%d' ";
                        $forum = "INSERT INTO {debate_options} set nid = '%d',chorder='%d',ans_val='%d' ";
                        db_query($forum, $deb->nid, $list->chorder, 1);
                    }
            //create a default ends


            $output = drupal_set_message(t('Your issue has been added.  It will be reviewed by 3 moderators but is available immediately.
'), $type = 'success');
        unset($_SESSION['post']);
        $_SESSION['post'] = '';
        $path=drupal_get_path_alias('node/'.$result->nid);
         increasepoints('1', $ins_id, '0');
        _send_qnotify($result->nid);
         //drupal_goto($path);
              echo '<script>window.parent.location.href="' . $gSitePath . $path . '";</script>';
        }
    } else {
        drupal_get_messages($type = 'error', $clear = 'TRUE');
        $_SESSION['post'] = $_POST;
        drupal_set_message($message = '<li>Sorry, Following required fields are Empty!</li>', $type = 'error');

        if (empty($q_quest))
            drupal_set_message($message = '<li>Issue should not be empty!</li>', $type = 'error');

        if (empty($q_ans1) || empty($q_ans2))
            drupal_set_message($message = '<li>Minimum 2 options are required!</li>', $type = 'error');

//        if (empty($cat1))
//            drupal_set_message($message = '<li>Main Category should not be Empty!</li>', $type = 'error');


        drupal_goto("question/add");
    }
    if (!empty($output['error'])) {
        echo implode(" ", $output['error']);
    }
}


function _send_qnotify($qid='') {
    global $gSitePath, $user, $gDocPath, $base_root, $base_url;

    //inline site notify
    $insert_notify = db_query("insert into notification (uid,follower_action,is_question,node_id) values('" . $user->uid . "','1','1','" . $qid . "' ) ");

	$node=node_load($qid);
	$question_urlff=drupal_get_path_alias('node/'.$qid);
    $message_id = 'Add_question';
    $variables = array(
      '@username' => l(user_load($user->uid)->name, 'profile/' . $user->name),
      //'@node_type' => 'page',
      '@question_title' => "<a href='$base_url/$question_urlff' >".$node->title."</a>",
    );
		//heartbeat_api_log($message_id, $user->uid, $question_urlff , $qid, $question_urlff, $variables);
		//echo 'test';
		//die;
	/*RAM HEARTBEAT MODULE*/


    ////////////mail notication for user follwers to me//////////////////////////////////////

    hm_mails($qid, '', 'add_question');

}

function send_qnotify($qid='') { ///vijay important comented
    global $gSitePath, $user, $gDocPath, $base_root, $base_url;

    //inline site notify
    $insert_notify = db_query("insert into notification (uid,follower_action,is_question,node_id) values('" . $user->uid . "','1','1','" . $qid . "' ) ");

	$node=node_load($qid);
	$question_urlff=drupal_get_path_alias('node/'.$qid);
    $message_id = 'Add_question';
    $variables = array(
      '@username' => l(user_load($user->uid)->name, 'profile/' . $user->name),
      //'@node_type' => 'page',
      '@question_title' => "<a href='$base_url/$question_urlff' >".$node->title."</a>",
    );
		//heartbeat_api_log($message_id, $user->uid, $question_urlff , $qid, $question_urlff, $variables);
		//echo 'test';
		//die;
	/*RAM HEARTBEAT MODULE*/
    

    ////////////mail notication for user follwers to me//////////////////////////////////////

    hm_mails($qid, '', 'add_question');
    
}







function question_ajax() {
    //print_r($_REQUEST['code']);
    // print_r($action);
	$ret = '';
	global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    extract($_REQUEST);
    if (isset($_REQUEST['ids'])) {
        //$client_select = db_query("SELECT cat_id,cat_name FROM {category} where parent_id IN ($ids)");
        /********Node Conversion********/
        $vid = db_result(db_query("SELECT vid FROM {vocabulary} WHERE name = '%s' AND module = '%s'", 'Sections', 'taxonomy'));
        $client_select = db_query("SELECT t.tid AS cat_id, t.name AS cat_name FROM term_data t RIGHT JOIN term_hierarchy h ON t.tid = h.tid WHERE parent IN ($ids) AND t.vid = '$vid'");
        /********Node Conversion********/
        $client_array = array();
        $client_key = array();
        while ($list = db_fetch_object($client_select)) {

            $client_array[] = $list->cat_name;
            $client_key[] = $list->cat_id;
        }
        if (!empty($client_array)) {

            if ($action == 1) {
                $qscat = "q_scat";
                $tab = 15;
            }
            if ($action == 2) {
                $qscat = "q_sscat";
                $tab = 16; //	get_subcat(\'q_cat\',\'chg_scat\',1);
            }
            $ret = '<select class="listbox2" tabindex="' . $tab . '"  size="5" multiple="multiple" onchange="get_subcat(' . $qscat . ',\'chg_sscat\',' . ++$action . ');" id="' . $qscat . '" name="q_scat[]"> ';

            for ($i = 0; $i < count($client_array); $i++) {

                $ret .= '<option value="' . $client_key[$i] . '">' . stripslashes($client_array[$i]) . '</option>';
            }
            $ret .= "</select>";
        } else {
            $ret .= 'No Subcategory';
        }
        echo $ret;
        exit;
    } elseif (isset($_REQUEST['code'])) {
        switch ($action) {

            case 1: //get state
                $query = array('query' => $_REQUEST['code'], 'maxRows' => '1', 'featureclass' => 'S');
                $result = geonames_query('search', $query);
                print_r($result->results[0]['url']);
                // $cc=$result->results[0]['countrycode'];
                // $result = geonames_query('countryinfo', $query);
                // $result->results[0][geonameid];
                $query = array('country' => $result->results[0]['countrycode']);
                $result = geonames_query('countryinfo', $query);
                $query = array('geonameid' => $result->results[0]['geonameid']);
                $result = geonames_query('children', $query);

                if ($select && $user->uid > 0) {
                    $udet = load_user($user->uid);

                    $setstate = $udet->state;
                    $fcity = $udet->city;
                }
                $ret = "<script>
                $(document).ready(function() {
	$('select').change(function(){
		alert('ID: ' + $(this).attr('id') + ' Value: ' + $(this).attr('value'));
	});
                    </script>";

                $ret = '<select tabindex="18" class="listbox2" style="width: 125px;"  onchange="get_city(this.value);" id="q_state" name="q_state"> <option value="">--States--</option>';
                foreach ($result->results as $state) {
                    $set = '';
                    if (strpos(strtolower($setstate), strtolower($state['name']))) {
                        $set = 'SELECTED=SELECTED';
                    }
                    $ret .= sprintf('<option value="%s" %s >%s</option>', $state['geonameid'], $set, $state['name']);
                }
                $ret .= "</select>";
                echo $ret;
                break;
                exit;
            case 2: //get city

                $query = array('geonameid' => $code);
                $result = geonames_query('children', $query);
                //print_r($result);

                $ret = "<script>
                $(document).ready(function() {
	$('select').change(function(){
		alert('ID: ' + $(this).attr('id') + ' Value: ' + $(this).attr('value'));
	});
                    </script>";

                $ret = '<select class="listbox2"  tabindex="19"  style="width: 125px;"  id="q_city" name="q_city" > <option value="">--Cities--</option> ';
                foreach ($result->results as $state) {

                    $ret .= sprintf('<option value="%s">%s</option>', $state['geonameid'], $state['name']);
                }
                $ret .= "<option value='-1'>Others</option>";
                $ret .= "</select>";
                echo $ret;
                break;
		/*RELEATED QUESTIONS AUTO POPULATE*/		
			case 3: 
				echo get_releated_questions($_POST['question'],$_POST['cat_id'],$_POST['context']);                
                break;				
		/*RELEATED QUESTIONS AUTO POPULATE*/				
        }
    } elseif (isset($_REQUEST['tag'])) {

        extract($_REQUEST);

        $tarr = explode(' ', $tag);
        $qns = explode(' ', $qns);
        $tarr = array_merge($tarr, $qns);
        $tarr = array_filter($tarr);
        $tarr = array_unique($tarr);

        $taglist = array();

        foreach ($tarr as $list) {

            $query = " SELECT * FROM {tagging} WHERE `tag` LIKE  '%$list%' LIMIT 0 , 15 ";
            $result = ExecuteQuery($query, "select");
            foreach ($result as $single) {
                array_push($taglist, $single['tag']);
            }
        }
        //for category taglist
        if (!empty($cat1)) {

            $exp = explode(',', $cat1);

            $qids = array();
            foreach ($exp as $scat) {

                 $query = " SELECT * FROM {question}  ";
               
                $result = ExecuteQuery($query, "select");

                foreach ($result as $man) {

                    $getcat = explode(',', $man['cid']);

                    if (in_array($scat, $getcat)) {

                        array_push($qids, $man['qid']);
                    }
                }




                $qids = array_unique($qids);
                $qids = implode(',', $qids);

                $query = " SELECT * FROM {tagging} WHERE `qid` IN ($qids) ";
                $result = ExecuteQuery($query, "select");
                foreach ($result as $single) {
                    array_push($taglist, $single['tag']);
                }
            }
        }


        $taglist = array_filter($taglist);

        $taglist = array_unique($taglist);
        $taglist = implode(',', $taglist);
        $taglist = explode(',', $taglist);
        $taglist = array_filter($taglist);
        $taglist = array_unique($taglist);

        $tag = ' <label>
            	                    Suggestions:
            	                </label>';
        if (!empty($taglist)) {
            foreach ($taglist as $ins) {
                $tag .= '	
            	                    <div id="tagging-1" class="tagging-suggest-tag processed">
            	                        ' . $ins . '</div>';
            }
        } else {

            $tag .= '<b>No Suggestions</b>';
        }

        echo $tag;
      
    } elseif (isset($_REQUEST['ssearch'])) {


        $input = trim(strtolower($_REQUEST['input']));
        $stype = $_REQUEST['stype'];
        $aResults = array();
        if ($stype == '2') {


            $query = "select u.uid as id,u.name as value,up.first_name as info from user_profile as up,users as u where u.uid=up.uid AND (u.name like '%%%s%%' OR up.real_name like '%%%s%%')  ORDER BY u.uid ASC ";
            //  $aResults = ExecuteQuery($query, "select");
          //  printf($query,$input,$input);die;
            $Result = db_query($query,$input,$input);
        } else {


           // $query = "select qid as id,question as value,context as info from question where question like '%$input%' OR context like '%$input%' AND status='1' ORDER BY qid ASC ";
          $query = "select qid as id,question as value,context as info from question where question like '%$input%' AND status='1' ORDER BY qid ASC ";
          
           
            //$aResults = ExecuteQuery($query, "select");
            $Result = mysql_query($query);
        }
        while ($ResultSet1 = mysql_fetch_array($Result)) {
            $aResults[] = $ResultSet1;
        }
        //print_r($aResults);
        // $aResults[]=array('id'=>'question_1','value'=>'Question vs','info'=>'currency','currency'=>'hello');
        // $aResults[]=array('id'=>'question_2','value'=>'Question info','info'=>'currency','currency'=>'hello');
        //print_r($aResults);
        header("Expires: Mon, 26 Jul 1997 05:00:00 GMT"); // Date in the past
        header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT"); // always modified
        header("Cache-Control: no-cache, must-revalidate"); // HTTP/1.1
        header("Pragma: no-cache"); // HTTP/1.0

        header("Content-Type: application/json");

        echo "{\"results\": [";
        $arr = array();
        for ($i = 0; $i < count($aResults); $i++) {
            $arr[] = "{\"id\": \"" . $aResults[$i]['id'] . "\", \"value\": \"" . mysql_real_escape_string($aResults[$i]['value']) . "\", \"info\": \"" . mysql_real_escape_string(myTruncate($aResults[$i]['info'], 20, '...')) . "\"}";
        }
        echo implode(", ", $arr);
        echo "]}";
    } elseif (isset($_REQUEST['sel_id'])) {


        $link1 = '';
        $link2 = '';
        $link3 = '';
        $cid = '';
        $scid = '';
        $cond = '';
                    //print_r($_REQUEST);

        $scid = $_REQUEST['scid'];
        //$cond =" AND cat.scat=$scid";

        if ($_REQUEST['sel_id'] != '') {
        $cid=$_REQUEST['sel_id'];

                        /*Node conversion*/
                              $parent = taxonomy_get_parents($cid);
                              $childrens = taxonomy_get_children($cid);
                              foreach($childrens as $children){
                                  $style = '';
                              if ($sscid == $children->tid) {
                                 $style = 'style="font-weight:bold"';
                              }
                              $sscat_qry = "SELECT count(distinct cat.tid) FROM term_node as cat join node as q on q.nid=cat.nid where q.status='1' AND cat.tid ='" . $children->tid. "' $cond group by q.nid";
                              $total = db_result(db_query($sscat_qry));
                              $total = $total!=''?$total:0;
                              $style = 'class="sublinks scat" style="padding-left:10px"';
                              $catlist.= '<br class="scat"/><span ' . $style . '><a  id="sc-' . $children->tid . '" href="JavaScript:void(0);" ' . $style . '>' . stripslashes($children->name) . '[' .$total. ']' .'</a></span>';
                                }
                            echo $catlist;
                       /*Node conversion*/

            
        }
    }else if(isset($_REQUEST['user_scat'])){

         $cid=$_REQUEST['user_scat'];

         $parent=load_parent_cat($cid,3);
         $catid=(!empty($parent['lev1']))?$parent['lev1']:$parent['lev2'];
         if(!empty($catid)){
                        foreach ($listsscat as $sscat) {
                            $style = '';
                            if ($sscid == $sscat['cat_id']) {
                                $style = 'style="font-weight:bold"';
                            }
                      
                            $sscat_qry = "select count(uid) from follower where cat_id='".$sscat['cat_id']."'";
                           $total_count3= db_result(db_query($sscat_qry));


                            $style = 'class="sublinks scat" style="padding-left:10px"';
                            $catlist.='<br class="scat"/><span ' . $style . '><a  id="sc-'.$sscat['cat_id'].'" ' . $style . ' href="javascript:void(0);">' . $sscat['cat_name'] . '[' . $total_count3 . ']</a></span>';
                        }
                        echo $catlist;
         }

    }else if(isset($_REQUEST['notupdate'])){
        // update user message status, sent from moderator
            $mid = $_REQUEST['mid'];
            $uid = $_REQUEST['uid'];
            $sql = db_query("UPDATE {moderator_messages} SET status= '1' WHERE id = '%d' AND to_uid = '%d'", $mid, $uid);
            if($sql){
                echo "success";
            }
    }

     exit;
}

//delete confirm
function get_releated_questions($question,$cat_id,$context)
{	
	$where_condition = '';	
	$words = explode(" ", $question);
           $words = array_filter($words, 'word_array_filter');
            $words = array_filter($words);
	 for ($i = 0; $i < count($words); $i++) {
		$wheres2 	= array();
			if($words[$i]!='')
			{
				$wheres2[]  = "  q.title  LIKE CONVERT(_utf8 '%$words[$i]%' USING latin1 ) COLLATE latin1_swedish_ci";
				$wheres[] 	= implode( ' OR ', $wheres2 );
			}	
		}
	$where_condition = '((' . implode( ($match == 'all' ? ') AND (' : ') OR ('), $wheres ) . '))';
	
	if($context!='')
	{
		$words = explode(" ", $context);
		 for ($i = 0; $i < count($words); $i++) {
			$wheres2 	= array();
				if($words[$i]!='')
				{
					$wheres2[]  = "  q.context  LIKE CONVERT(_utf8 '%$words[$i]%' USING latin1 ) COLLATE latin1_swedish_ci";
					$wheres1[] 	= implode( ' OR ', $wheres2 );
				}	
			}	
		$where_condition .= ' and ((' . implode( ($match == 'all' ? ') AND (' : ') OR ('), $wheres1 ) . '))';
	}
	if($cat_id!=0)
	{
		$where_condition .= " and qc.cat in ($cat_id)";
	}
         $text="$question $context";
//printf("SELECT count(MATCH(r.body, r.title) AGAINST ('%s')) FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' GROUP BY n.nid ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10",$text,0);
	$count = db_result(db_query("SELECT count(MATCH(r.body, r.title) AGAINST ('%s')) FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' GROUP BY n.nid ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10",$text,0));
	$rel_output.= '<div class="innerbox" style="width:auto;height:auto; overflow:auto; min-height:150px;"><ul>';
	if (($count!=0)&&($question!=''))
	{
		$rel_count = 1;
		$rel_query = db_query("SELECT r.nid,r.title, MATCH(r.body, r.title) AGAINST ('%s') AS score FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' GROUP BY n.nid  ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10",$text,0);
		while ($rel_options = db_fetch_object($rel_query)) {		
		  $rel_output.='<li><input style="width:15px;" type="checkbox" name="chk_rel_issue[]" id="chk_rel_issue[]" value="'.$rel_options->nid.'"> ';
		  $rel_output .= substr($rel_options->title,0,50).'...</li>';
		  $rel_count ++;
		}
	} else {
		$rel_output.= 'No Releated question available';
	}		
	$rel_output.= '</ul></div>';
	echo  $rel_output;	
//echo "SELECT q.qid, q.question FROM {question} q  left join question_cat qc on qc.qid=q.qid  WHERE $where_condition  group by q.qid ";	
	
}

function question_edited_mail_voters($qaid) {

    global $gSitePath, $user, $gDocPath, $base_root;

    $from = variable_get('site_mail');
    $subject_proj = 'Heardmentality Question Has Been Edited By admin ';
    //$delmsg = 'Has been Edited By Headmentality admin';
    $query = db_query("select u.question,q.uid  from possible_answer_vote as q left join question as u on u.qid=q.qid where q.qid='$qaid' ");

    while ($det = db_fetch_object($query)) {

        $sellist = "select * from users where uid='" . $det->uid . "'";
        $res_users = db_query($sellist);
        $usert = db_fetch_object($res_users);
        $to = $usert->mail;
        // $msg = '<br/>Question : '.$det->question.' '.$delmsg.'<br/>';



        $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='5'";
        $rs_mgmt = db_query($sel_user_cmt);
        $list_content = db_fetch_object($rs_mgmt);

        $contentm = str_replace("#uname#", $usert->name, $list_content->content);
        $contentm = str_replace("#anothername#", $user->name, $contentm);
        $contentm = str_replace("#question#", rtrim($det->question, '?') . '?', $contentm);
        $contentm = str_replace("#link#", $gSitePath . $det->url, $contentm);
        $contentm = str_replace("#content#", 'Question edited By Headmentality admin', $contentm);

        //$mail_success = htmlmail_function($u_rows->email, $subject_proj, $contentm, '');
     $ins_qry = "insert into {hm_mails} (from_mail_id,user_from_id,user_to_id,subject,content,posted_date) values ('%s','%s','%s','%s','%s',now())";
    db_query($ins_qry, $from, $from, $to, $subject_proj, $contentm);
        /* if (! empty($to)) {

          $mail_suc = htmlmail($to, $subject, $msg, $from, '');
          } */
    }
    return true;
}

function question_edited_mail_suggest($qaid) {

    global $gSitePath, $user, $gDocPath, $base_root;

    $from = variable_get('site_mail');
    $subject = 'Heardmentality Issues Has Been Updated By Moderator ';
    // $delmsg = 'Has been Edited By Headmentality admin';

    $query = db_query("select u.question,q.uid  from suggest_answer as q left join question as u on u.qid=q.qid where q.qid='$qaid' ");

    while ($det = db_fetch_object($query)) {

        $sellist = "select * from users where uid='" . $det->uid . "'";
        $res_users = db_query($sellist);
        $usert = db_fetch_object($res_users);
        $to = $usert->mail;
        $msg = '<br/>Question : ' . $det->question . ' ' . $delmsg . '<br/>';


        $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='5'";
        $rs_mgmt = db_query($sel_user_cmt);
        $list_content = db_fetch_object($rs_mgmt);

        $contentm = str_replace("#uname#", $usert->name, $list_content->content);
        $contentm = str_replace("#anothername#", $user->name, $contentm);
        $contentm = str_replace("#question#", rtrim($det->question, '?') . '?', $contentm);
        $contentm = str_replace("#link#", $gSitePath . $det->url, $contentm);
        $contentm = str_replace("#content#", 'Question edited By Headmentality admin', $contentm);

        //$mail_success = htmlmail_function($u_rows->email, $subject_proj, $contentm, '');
     $ins_qry = "insert into {hm_mails} (from_mail_id,user_from_id,user_to_id,subject,content,posted_date) values ('%s','%s','%s','%s','%s',now())";
    db_query($ins_qry, $from, $from, $to, $subject_proj, $contentm);

        /* if (! empty($to)) {

          $mail_suc = htmlmail($to, $subject, $msg, $from, '');
          } */
    }
    return true;
}


function exist_dupe() {

    global $gSitePath, $user, $gDocPath, $base_root;

    $currLanguage = i18n_get_lang();
    $qaid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $question = $_REQUEST['question'];
   
    $words=removeCommonWords($question);
      $words=trim($words);
     $words = explode(" ", $words);
   
    $query = "SELECT distinct(n.nid), n.title FROM {node} n JOIN {node_revisions} nr ON n.nid = nr.nid WHERE n.status = 1 AND n.type = 'poll' AND language = '$currLanguage'";
    for ($i = 0; $i < count($words); $i++) {
        $samples = " " . $words[$i] . "  ";
        //echo $samples;
        // $query = "SELECT * FROM question WHERE question LIKE ('$words[$i]%') or question LIKE ('%$words[$i]%') or  context LIKE ('%$words[$i]%') and status='0' ";
        //AND question LIKE '%hi%' and question LIKE '%issue%' and status='1'"
        $query .= " AND nr.title LIKE CONVERT(_utf8 '%%$words[$i]%%' USING utf8 ) COLLATE utf8_general_ci";
    }
$result = db_query($query);
$dupecount = db_affected_rows($result);

 $rel_ques .= '<div class="innerbox" style="width:155px; height:150px; overflow:auto; margin-top:7px; color:#986700; ">';
 $rel_ques .= "<ul>";
 if($dupecount>0&&count($words))
 {
 while ($mylist = db_fetch_array($result)) {
        $validpath =  $gSitePath.drupal_get_path_alias('node/'.$mylist['nid']);
        $rel_ques .= "<li>";
        $rel_ques .= "<a href='".$validpath."' target='_blank'>&gt;&gt;&nbsp;".$mylist['title']."</a>";
        $rel_ques .= "</li>";
    }
 }else{
     $rel_ques .= "<li>".t('No Dupe Questions')."</li>";
 }
    $rel_ques .= "</ul>";
    $rel_ques .= '</div>';
    $json = array('result' => $rel_ques, 'dupe_count' => $dupecount);
    print_r(json_encode($json));
    exit;
}
