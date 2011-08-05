<?php

// tree menu listing
function profile_view() {

    global $gSitePath, $user, $gDocPath, $base_root;
    $profile_name = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $uid = '';

    if(!is_numeric($profile_name)){
    $profile_name = strtolower($profile_name);
    $getuser = user_load(array('name' => $profile_name));
    }else{
    $getuser = user_load(array('uid' => $profile_name));
    }
    if (isset($getuser) && !empty($getuser)) {

        $uid = $getuser->uid;
    }

    if ($uid == '') {
        $uid = $user->uid;
    }
    $strReturn = '';

    if ($uid == '') {
        drupal_not_found();
        return;
    }
    
    //activities
    $tag = '';
    if (isset($_REQUEST['tag'])) {
        $tag = $_REQUEST['tag'];
    }

    switch ($tag) {

        case 'activity':

            $strReturn = profile_activities($uid);
            break;
        case 'history':
            $strReturn = profile_tab($tag, $uid);
            break;
        case 'badge':
            $strReturn = profile_tab($tag, $uid);
            break;
        case 'info':
            $strReturn = profile_tab($tag, $uid);
            break;
        case 'msg':
            $strReturn = profile_tab($tag, $uid);
        default:
            // $strReturn ="something wrong";
//badges
            enthusiast($uid);
            fanatic($uid);
            $strReturn = profile($uid);
            break;
    }

    if (isAjax ())
        echo $strReturn;
    else
        return $strReturn;
}

function inbox_flex() {
    global $gSitePath, $user, $gDocPath, $base_root;
    $case = $_REQUEST['action'];
    switch ($case) {

        case 'delete':
            $ids = $_REQUEST['id'];

            $query = "delete from {messages} where mid='$ids' AND to_id='$user->uid'";
            db_query($query);
            $result = db_affected_rows();

            if ($result

                )echo '<div class="messages success">Message deleted successfully, please wait to reload...!</div>';
            break;
        default :
            echo '<div class="messages error">Sorry no event occurs!</div>';
            break;
    }
}

function inbox_msg() {

    global $gSitePath, $user, $gDocPath, $base_root;
    $inbox = '';
    $query = "select * from {messages} as m join {users} as u on u.uid=m.from_id where m.to_id='$user->uid' order by mid DESC";
    $msgs = ExecuteQuery($query, "select");
    $i = 1;
    if (!empty($msgs)) {

        foreach ($msgs as $list) {
            $bubble = load_bubble($list['from_id']);
            $inbox.='  <tr><td height="40px" style="font-style:justify;" >' . $i . '</td><td>' . wordwrap($list['message'], 100, "<br/>") . '</td><td><a href="' . $gSitePath . 'profile/' . $list['name'] . '" rel=\'' . $bubble . '\'>' . $list['name'] . '</a></td><td>' . format_date_class($list['posted_date'], date('Y-m-d')) . '</td><td><a href="#" onclick="del_msg(' . $list['mid'] . ',this);">Delete</a> &nbsp;/&nbsp; <a href="#" onclick="rel_msg(' . $list['from_id'] . ');">Reply</a></td></tr>';
            $i++;
        }
    } else {

        $inbox = '  <tr><td height="40px" align="center" colspan="5" style="font-style:justify;" > <b>No Messages</b></td></tr>';
    }

    $content = '';
    //drupal_add_js(drupal_get_path('module','profile').'/js/flexigrid.js');
    drupal_add_js(drupal_get_path('module', 'profiles') . '/js/profile.js');
    //drupal_add_css(drupal_get_path('module','profile').'/css/flexigrid/flexigrid.css');
    $content = '
       <script>
       $(document).ready(function() {

            $(\'#inbox > tbody > tr:odd\').css("background-color", "#EDEDED");

        });

    </script>

       <div class="facttop2">INBOX MESSAGE(S)</div>
       <div>

<table id="inbox" width="100%" style="height:100%;padding:10px;"><thead><tr><th align="left">S.No</th><th align="left">Msg</th><th align="left">From</th><th align="left">Date</th><th align="left">Action</th></tr></thead><tbody>
            ' . $inbox . '

          </tbody></table>
    </div>';

    return $content;
}

function event_photo() {
    global $objSmarty, $config;
    $return = array();
    $filename = $_FILES['image']['name']; // file up starts
    $tmp_image = $_FILES['image']['tmp_name'];
    if ($filename != '') {
        include drupal_get_path('module', 'profiles') . "/img_resize.php";
        $ext = strtolower(substr($filename, strpos($filename, '.'), strlen($filename) - 1));

        if ($ext == '.jpg' || $ext == '.gif' || $ext == '.jpeg') {
            $imagefun = new SimpleImage();

            $image = time() . $filename;

            $path = drupal_get_path('module', 'profiles') . "/snap/";
            copy($tmp_image, $path . $image);
            //img resize
            $sz = getimagesize($path . $image);

            $x = $sz[0]; // org image width
            $y = $sz[1]; // org image height
            if ($x > 100) {
                $imagefun->load($path . $image);

                $imagefun->resizeToWidth(100);

                $imagefun->save($path . $image);
            }


            if ($image != "") {
                $insimage = $image;
                //include('round_corner.php');
            }
        } else {
            $flag = 1;
            $suc = ' Sorry Image Cant Uploaded It Should be gif or Jpeg format!';
        }
    } elseif (isset($_REQUEST['oldimg'])) {
        $insimage = $_REQUEST['oldimg'];
        $flag = 0;
    } else {
        $flag = 0;
        $insimage = "noimage.jpg";
    }//file up ends

    $return['image'] = $insimage;
    $return['flag'] = $flag;
    $return['suc'] = $suc;
    return $return;
}

////followers/////////////////////////


function profile_followerlist($uids) {
global $user,$gSitePath;
  //using user relation module api
$relationships = user_relationships_load($param = array("approved" => 1, "requestee_id" => $uids,'rtid'=>1), $options = array('include_user_info'=>1,'order'=>1,'limit'=>'10'), $reset = FALSE);
//echo "<pre>";
//print_r($relationships);die;
$requestcount = count($relationships);

if ($relationships) {
  $the_other_uid =$uids;
  $showing_all_types = $settings->rtid == 1;
  $rows = array();
  foreach ($relationships as $rtid => $relationship) {
    //echo '<pre>';
      //print_r($relationship);
      
    $tt_rel_name = ur_tt("user_relationships:rtid:$rtid:name", $relationship->name);
    $tt_rel_plural_name = ur_tt("user_relationships:rtid:$rtid:plural_name", $relationship->plural_name);
    if ($the_other_uid == $relationship->requester_id) {
         $bubble = load_bubble($relationship->requestee_id);
  $output[]='<a rel=\''.$bubble.'\' href="'.$gSitePath.'profile/'.$relationship->requestee->name.'">'.userPicture_small($relationship->requestee_id).'</a>';
      $rtype_heading = $relationship->is_oneway ?
        t("@rel_name of", array('@rel_name' => $tt_rel_name, '@rel_plural_name' => $tt_rel_plural_name)) :
        t("@rel_plural_name", array('@rel_name' => $tt_rel_name, '@rel_plural_name' => $tt_rel_plural_name));
      $relatee = $relationship->requestee;
    }
    else {
      $rtype_heading = t("@rel_plural_name", array('@rel_name' => $tt_rel_name, '@rel_plural_name' => $tt_rel_plural_name));
      $relatee = $relationship->requester;
     
        $bubble = load_bubble($relationship->requester_id);
  $output[]='<a title="'.$relationship->requester->real_name.'" rel=\''.$bubble.'\' href="'.$gSitePath.'profile/'.$relationship->requester->name.'">'.userPicture_small($relationship->requester_id).'</a>';
    }

    $title = $rtype_heading;

    $username = theme('username', $relatee);
    $rows[$title][] = $username;
  }

}


    if ($requestcount > 5) {
        $output[] .= '<a style="color:#F37321;" href="javascript:void(0);" onclick="loadfollower(\'' . $gSitePath . 'follower/' . $uids . '\',\'Follower\');">More</a>';
    }
    if ($requestcount == 0) {
        $output[] .= '<span style="padding-left:17px;">Please follow people!</span>';
    }

//$output is new one using user relationship
    return $output;
}

function save_follow_profile() {

    if (isset($_REQUEST['action'])) {
        $query = 'DELETE FROM follower WHERE id = ' . (int) $_REQUEST['action'];
        $result = db_query($query);
        echo '<div id="' . $_REQUEST['ids'] . '" >Removed</div>';
    }
}

//////////following //////////////////////////


function profile_followinglist($umid) {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

  //using user relation module api
$relationships = user_relationships_load($param = array("approved" => 1, "requester_id" => $umid,'rtid'=>1), $options = array('include_user_info'=>1,'order'=>1,'limit'=>'10'), $reset = FALSE);
//echo "<pre>";
$requestcount = count($relationships);

if ($relationships) {
  $the_other_uid =$umid;
  $showing_all_types = $settings->rtid == 1;
  $rows = array();
  foreach ($relationships as $rtid => $relationship) {
    //echo '<pre>';
      //print_r($relationship);
       $bubble = load_bubble($relationship->requestee_id);
  $output[]='<a rel=\''.$bubble.'\' href="'.$gSitePath.'profile/'.$relationship->requestee->name.'">'.userPicture_small($relationship->requestee_id).'</a>';
    $tt_rel_name = ur_tt("user_relationships:rtid:$rtid:name", $relationship->name);
    $tt_rel_plural_name = ur_tt("user_relationships:rtid:$rtid:plural_name", $relationship->plural_name);
    if ($the_other_uid == $relationship->requester_id) {
      $rtype_heading = $relationship->is_oneway ?
        t("@rel_name of", array('@rel_name' => $tt_rel_name, '@rel_plural_name' => $tt_rel_plural_name)) :
        t("@rel_plural_name", array('@rel_name' => $tt_rel_name, '@rel_plural_name' => $tt_rel_plural_name));
      $relatee = $relationship->requestee;
    }
    else {
      $rtype_heading = t("@rel_plural_name", array('@rel_name' => $tt_rel_name, '@rel_plural_name' => $tt_rel_plural_name));
      $relatee = $relationship->requester;
    }

    $title = $rtype_heading;

    $username = theme('username', $relatee);
    $rows[$title][] = $username;
  }

}



    if ($requestcount > 5) {
        $output[] .= '<a style="color:#F37321;" href="javascript:void(0);" onclick="loadfollower(\'' . $gSitePath . 'following/' . $umid . '\',\'Follower\');">More</a>';
    }
    if ($requestcount == 0) {
        $output[] .= '<span style="padding-left:17px;">No Followers Yet</span>';
    }

//$output is new one using user relationship
    return $output;
}

function save_follower_profile() {
    global $gSitePath, $user, $gDocPath, $base_root;
    print_r($_REQEST);
    if (isset($_REQEST['action'])) {
        print_r($_REQEST);
        $del_blog = "update  follower  set follower_status='" . $_REQUEST['blk'] . "' where  id='" . $_REQEST['action'] . "' ";
        $rs_blog_del = db_query($del_blog);

        $sel_userms = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $_REQEST['usid'] . "'";
        // $sel_userms="select * from users  where uid='".$_GET['usid']."' ";
        $rs_userms = db_query($sel_userms);
        $resulrnames = db_fetch_object($rs_userms);
        if ($_REQUEST['blk'] == 0) {
            $blkid = '1';
            $valss = 'UnBlock';
            $insert_notify = db_query("insert into notification (uid,is_block,is_user,node_id) values('" . $_REQEST['usid'] . "','1','1','" . $user->uid . "' ");
            $sel_ulists = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $_REQEST['usid'] . "'";
            $rs_umlogs = db_query($sel_ulists);
            $user_namelistfs = db_fetch_object($rs_umlogs);




            $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='2'";
            $rs_mgmt = db_query($sel_user_cmt);
            $list_content = db_fetch_object($rs_mgmt);
            $contentm = str_replace("#uname#", $user_namelistfs->name, $list_content->content);
            $contentm = str_replace("#anothername#", $user->name, $contentm);
            // $contentm;

            $mail_success = htmlmail_function($user_namelistfs->mail, $subject, $contentm, '');
        } else {
            $valss = 'Block';
            $blkid = '0';
        }
        echo '<div id="' . $_REQUEST['ids'] . '" >' . UserPicture_small($_GET['usid']) . '<a href="' . $gSitePath . 'profile/' . $resulrnames->name . '">' . $resulrnames->name . '</a> <a onclick="blockandunblock(' . $_GET['action'] . ',' . $_GET['usid'] . ',' . $blkid . ')" style="color:#F37321;" >' . $valss . '</a></div>';
    }
}

function privacy_settings() {
    global $gSitePath, $user, $gDocPath, $base_root;
    $uid = $user->uid;
    //updating privacy settings
    if (isset($_REQUEST['update'])) {
        extract($_REQUEST);
        $chk = db_query("select * from {privacy_settings} where uid='$user->uid'");
        $chk1 = db_result($chk);
        if ($chk1) {
            $result = db_query("UPDATE {privacy_settings} set real_name='$real_name',gender='$gender',image='$image',bio=' $bio',zip='$zip',country='$country',religion='$religion',ethnic='$ethnic',income='$income',marital='$marital',facebook='$facebook',twitter='$twitter',email='$email',
			followers='$followers',following='$following',medal='$medal',questions='$questions',answers='$answers'  where uid=$user->uid ");
        } else {
            $result = db_query("INSERT INTO {privacy_settings} set uid='$user->uid',real_name='$real_name',gender='$gender',image='$image',bio=' $bio',zip='$zip',country='$country',religion='$religion',ethnic='$ethnic',income='$income',marital='$marital',facebook='$facebook',twitter='$twitter',email='$email',
			followers='$followers',following='$following',questions='$questions',answers='$answers' ,medal='$medal'");
        }
        if ($result) {
            drupal_set_message($message = 'Privacy Settings Updated Successfully!', $type = 'success');
            echo '<script>window.parent.location.href="' . $gSitePath . 'profile/";</script>';
        }
    }
    $query = "select * from {privacy_settings} where uid='$user->uid'";
    $fetch = ExecuteQuery($query, "select");
    if (is_array($fetch)) {
        $get = extract($fetch);
    } else {
        $get = NULL;
    }

    //privacy settings form
    $usertypes = userTypes();
    $option1 = '<option value=1>' . $usertypes[0] . '</option>';
    $option2 = '<option value=2>' . $usertypes[1] . '</option>';
    $option3 = '<option value=3>' . $usertypes[2] . '</option>';


    $strReturn = '
  <script type="text/javascript" src="' . $gSitePath . 'sites/all/themes/heardmentality/scripts/mootools-1.2-core.js"></script>
	<script type="text/javascript" src="' . $gSitePath . 'sites/all/themes/heardmentality/scripts/mootools-1.2-more.js"></script>
  <link rel="stylesheet" href="' . $gSitePath . 'modules/system/system.css" type="text/css" />
		<link rel="stylesheet" href="' . $gSitePath . path_to_theme() . '/css/css.css" type="text/css" />
	
		<form name="profile" id="profile" method="post" enctype="multipart/form-data">
		<fieldset>
        	<legend>Privacy Settings</legend>
			<table border="0" cellpadding="4" cellspacing="4"  >
		       <tr><td>Email  </td>
   			        <td></td>
   			        <td><select class="email" name="email">' . $option1 . $option2 . $option3 . '</select>  </td>
			   </tr>
			   <tr><td></td><td></td><td></td></tr>
		       <tr><td>User Name  </td>
   			       <td></td>
   			       <td><select class="real_name" name="real_name">' . $option1 . $option2 . $option3 . '</select> </td>
				</tr>
			   <tr><td></td><td></td><td></td></tr>
		       <tr><td>Image</td>
   			       <td>	</td>
   			       <td>	<select class="image"  name="image">' . $option1 . $option2 . $option3 . '</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			   <tr><td>Bio</td>
   			       <td>	</td>
   			       <td>	<select class="bio"  name="bio">' . $option1 . $option2 . $option3 . '</select> </td>
		       </tr>
			   <tr><td></td><td></td><td></td></tr>	
			    <tr><td>Gender</td>
   			       <td>	</td>
   			       <td>	<select class="gender"  name="gender">' . $option1 . $option2 . $option3 . '</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			     <tr><td>Zip</td>
   			       <td>	</td>
   			       <td>	<select class="zip"  name="zip">' . $option1 . $option2 . $option3 . '</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			     <tr><td>Country</td>
   			       <td>	</td>
   			       <td>	<select class="country"  name="country">' . $option1 . $option2 . $option3 . '</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			    <tr><td>Religion</td>
   			       <td>	</td>
   			       <td>	<select class="religion"  name="religion">' . $option1 . $option2 . $option3 . '</select> </td>
		       </tr>
			   <tr><td></td><td></td><td></td></tr>
			   <tr><td>Ethnic</td>
   			       <td>	</td>
   			       <td>	<select class="ethnic"  name="ethnic">' . $option1 . $option2 . $option3 . '</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			   <tr><td>Slant</td>
   			       <td>	</td>
   			       <td>	<select class="slant"  name="slant">' . $option1 . $option2 . $option3 . '</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
              <tr><td>Facebook</td>
   			       <td>	</td>
   			       <td>	<select class="facebook"  name="facebook">' . $option1 . $option2 . $option3 . '</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			   <tr><td>Twitter</td>
   			       <td>	</td>
   			       <td>	<select class="twitter"  name="twitter">' . $option1 . $option2 . $option3 . '</select> </td>
		       </tr>
	           <tr><td></td><td></td><td></td></tr>
			   <tr><td>Followers</td>
   			       <td>	</td>
   			       <td>	<select class="followers"  name="followers">' . $option1 . $option2 . $option3 . '</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			  <tr><td>Following</td>
   			       <td>	</td>
   			       <td>	<select class="following"  name="following">' . $option1 . $option2 . $option3 . '</select> </td>
		       </tr>
			  <tr><td></td><td></td><td></td></tr>
		     <tr><td>Medal</td>
   			       <td>	</td>
   			       <td>	<select class="medal"  name="medal">' . $option1 . $option2 . $option3 . '</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			  <tr><td>Posted Answers </td>
   			       <td>	</td>
   			       <td>	<select class="answers"  name="answers">' . $option1 . $option2 . $option3 . '</select> </td>
		      </tr>
		     <tr><td></td><td></td><td></td></tr>
			  <tr><td>Posted Questions</td>
   			       <td>	</td>
   			       <td>	<select class="questions"  name="questions">' . $option1 . $option2 . $option3 . '</select> </td>
		       </tr>
			</table>
			</fieldset>
			<div class="clear" style="height:100px;" ><input type="submit" name="update" value="Update"></div>
			</form>
			
			<script>
			
			setTimeout(markit,1000);

function markit(){
	
var chk=\'' . $fetch[0]['email'] . '\';
var elt=$$(\'.email\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}
var chk=\'' . $fetch[0]['real_name'] . '\';
var elt=$$(\'.real_name\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}
	
	var chk=\'' . $fetch[0]['image'] . '\';
var elt=$$(\'.image\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}
var chk=\'' . $fetch[0]['bio'] . '\';
var elt=$$(\'.bio\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}
var chk=\'' . $fetch[0]['gender'] . '\';
var elt=$$(\'.gender\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}
var chk=\'' . $fetch[0]['zip'] . '\';
var elt=$$(\'.zip\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}
var chk=\'' . $fetch[0]['country'] . '\';
var elt=$$(\'.country\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}

var chk=\'' . $fetch[0]['religion'] . '\';
var elt=$$(\'.religion\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}
var chk=\'' . $fetch[0]['ethnic'] . '\';
var elt=$$(\'.ethnic\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}
var chk=\'' . $fetch[0]['slant'] . '\';
var elt=$$(\'.slant\');
elt.each(function(el){ el.set(\'value\',chk); });

var chk=\'' . $fetch[0]['facebook'] . '\';
var elt=$$(\'.facebook\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}

var chk=\'' . $fetch[0]['twitter'] . '\';
var elt=$$(\'.twitter\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}
var chk=\'' . $fetch[0]['followers'] . '\';
var elt=$$(\'.followers\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}
var chk=\'' . $fetch[0]['following'] . '\';
var elt=$$(\'.following\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}
var chk=\'' . $fetch[0]['medal'] . '\';
var elt=$$(\'.medal\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}
var chk=\'' . $fetch[0]['answers'] . '\';
var elt=$$(\'.answers\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}
var chk=\'' . $fetch[0]['questions'] . '\';
var elt=$$(\'.questions\');
if(chk!=\'\'){
elt.each(function(el){ el.set(\'value\',chk); });
}
}
			</script>
		';


    echo $strReturn;
}

// after node conversion
function profile_activities($uid = ''){
     drupal_set_title('Recent Activities');
    global $gSitePath, $user, $gDocPath, $base_root;
    //$uid = $user->uid;
  $is_follow_follower = checkFollowStatus($user->uid, $uid);
  $userSettings = (array)load_user($uid);
    $strReturn = '<div class="history-tab">';
    //privacy settings
      if (($userSettings['question_privacy'] == 1) || ($userSettings['question_privacy'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['question_privacy'] == 3 && $is_follow_follower == TRUE) && ($userSettings['question_privacy'] != 4)) {

          $sql = "SELECT * FROM {notify_activity} WHERE uid = '$uid' ORDER BY naid DESC LIMIT 0,50";
          $fetch = ExecuteQuery($sql, "select");
          if(!empty($fetch)){
             foreach($fetch as $list){
                 $type = $list['message_id'];
                 switch($type){
                   case 'add_question':
                         //questions
                    $quest = db_result(db_query("SELECT title FROM {node} WHERE nid='".$list['nid']."'"));
                    if (!empty($quest)) {
                        $date = format_date_class(date('Y-m-d h:i:s', $list['timestamp']), date('Y-m-d h:i:s'));
                        $alias = drupal_get_path_alias('node/'.$list['nid']);
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>Asked</b></span> <span><a href="' . $gSitePath . $alias . '">' . myTruncate($quest, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                    case 'add_vote':
                        //vote
                        $quest = db_result(db_query("SELECT title FROM {node} WHERE nid='".$list['nid']."'"));
                        if (!empty($quest)) {
                            $date = format_date_class(date('Y-m-d h:i:s', $list['timestamp']), date('Y-m-d h:i:s'));
                            $alias = drupal_get_path_alias('node/'.$list['nid']);
                            $strReturn .= '<div ><span>' . $date . '</span><span> <b>Answered</b></span> <span><a href="' . $gSitePath . $alias . '">' . myTruncate($quest, '60', '..', '..') . ' </a></span></div>';
                        }
                    break;
                    case 'add_resource':
                        //resource
                        $resource = db_result(db_query("SELECT title FROM {node} WHERE nid='".$list['nid']."'"));
                        $vars = unserialize($list['variables']);
                        $qid = $vars['qid'];
                        $quest = db_result(db_query("SELECT title FROM {node} WHERE nid='".$qid."'"));
                        if (!empty($quest)) {
                            $date = format_date_class(date('Y-m-d h:i:s', $list['timestamp']), date('Y-m-d h:i:s'));
                            $alias = drupal_get_path_alias('node/'.$qid);
                            $strReturn .= '<div ><span>' . $date . '</span><span> <b>Added new resource</b></span> <span></span>'.$resource.'<span> <b>for</b> <a href="' . $gSitePath . $alias . '">' . myTruncate($quest, '60', '..', '..') . ' </a></span></div>';
                        }
                    break;
                    case 'add_debate':
                        //debate
                        $resource = db_result(db_query("SELECT title FROM {node} WHERE nid='".$list['nid']."'"));
                        $vars = unserialize($list['variables']);
                        $qid = $vars['qid'];
                        $quest = db_result(db_query("SELECT title FROM {node} WHERE nid='".$qid."'"));
                        if (!empty($quest)) {
                            $date = format_date_class(date('Y-m-d h:i:s', $list['timestamp']), date('Y-m-d h:i:s'));
                            $alias = drupal_get_path_alias('node/'.$qid);
                            $strReturn .= '<div ><span>' . $date . '</span><span> <b>Posted new debate</b></span> <span></span>'.$resource.'<span> <b>for</b> <a href="' . $gSitePath . $alias . '">' . myTruncate($quest, '60', '..', '..') . ' </a></span></div>';
                        }
                    break;
                    case 'deb_agree':
                        //agree
                         $vars = unserialize($list['variables']);
                         $pid = $vars['did'];
                         $debate = db_result(db_query("SELECT title FROM {node} WHERE nid='".$pid."'"));
                         
                         $qid = db_result(db_query("SELECT field_ref_qid_nid FROM {content_type_forum} WHERE nid = '$pid'"));
                         $quest = db_result(db_query("SELECT title FROM {node} WHERE nid='".$qid."' AND type='poll'"));
                          if (!empty($quest)) {
                         $date = format_date_class(date('Y-m-d h:i:s', $list['timestamp']), date('Y-m-d h:i:s'));
                         $alias = drupal_get_path_alias('node/'.$qid);
                         $strReturn .= '<div ><span>' . $date . '</span><span> <b>I like This Wave</b></span> <span>' . $debate . '<span> <b>for</b>  <a href="' . $gSitePath . $alias . '">' . myTruncate($quest, '60', '..', '..') . ' </a></span></div>';
                          }
                    break;
                    case 'res_agree':
                        //agree
                         $vars = unserialize($list['variables']);
                         $pid = $vars['rid'];
                         $resource = db_result(db_query("SELECT title FROM {node} WHERE nid='".$pid."'"));
                         $qid = db_result(db_query("SELECT field_ref_qid_nid FROM {content_type_forum} WHERE nid = '$pid'"));
                         $quest = db_result(db_query("SELECT title FROM {node} WHERE nid='".$qid."' AND type='poll'"));
                         if (!empty($quest)) {
                         $date = format_date_class(date('Y-m-d h:i:s', $list['timestamp']), date('Y-m-d h:i:s'));
                         $alias = drupal_get_path_alias('node/'.$qid);
                         $strReturn .= '<div ><span>' . $date . '</span><span> <b>I like This Wave</b></span> <span>' . $resource . '<span> <b>for</b>  <a href="' . $gSitePath . $alias . '">' . myTruncate($quest, '60', '..', '..') . ' </a></span></div>';
                         }
                    break;
                    case 'user_follow':
                        //follower
                        $vars = unserialize($list['variables']);
                        $fuid = $vars['target_id'];
                        $foll = load_user($fuid);
                        $date = format_date_class(date('Y-m-d h:i:s', $list['timestamp']), date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>New Follower</b></span> <span><a href="' . $gSitePath . 'profile/' .$fuid . '">' . $foll->name . '</a></span></div>';
                    break;
                    case 'suggest_answer':
                        //suggest answer
                        $quest = db_result(db_query("SELECT title FROM {node} WHERE nid='".$list['nid']."'"));
                        if (!empty($quest)) {
                            $date = format_date_class(date('Y-m-d h:i:s', $list['timestamp']), date('Y-m-d h:i:s'));
                            $alias = drupal_get_path_alias('node/'.$list['nid']);
                            $strReturn .= '<div ><span>' . $date . '</span><span> <b>Suggested Answer</b></span> for <span><a href="' . $gSitePath . $alias . '">' . myTruncate($quest, '60', '..', '..') . ' </a></span></div>';
                        }
                    break;
                    case 'add_badge':
                        // badges
                        $vars = unserialize($list['variables']);
                        $badge = $vars['bid'];
                        $bad = db_fetch_object(db_query("select * from {user_badges} as ub join {badges} as b on ub.bid=b.bid where ub.badge='" . $badge . "'"));

                        //echo "<pre>"; print_r($bad);

                        if (!empty($bad)) {
                            $date = format_date_class(date('Y-m-d h:i:s', $list['timestamp']), date('Y-m-d h:i:s'));
                            $strReturn .= '<div ><span>' . $date . '</span><span> <b>Awarded Badge </b></span> <span><a title=' . $bad->info . ' href="' . $gSitePath . 'badges/user/' . $bad->bid . '">' . $bad->name . ' </a></span></div>';
                        }
                    break;
                    
                 }
             }
          } else {
          $strReturn .='<div class="warning">No Activity Found!</div>';
    }

    }
      $strReturn.='</div>';
    echo $strReturn;
}

function activities_old($uid = '') {
    drupal_set_title('Recent Activities');
    global $gSitePath, $user, $gDocPath, $base_root;
    //$uid = $user->uid;
  $is_follow_follower = checkFollowStatus($user->uid, $uid);
  $userSettings = (array)load_user($uid);
    $strReturn = '<div class="history-tab">';
    //privacy settings
      if (($userSettings['question_privacy'] == 1) || ($userSettings['question_privacy'] == 2 && $user->uid != 0) || ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['question_privacy'] == 3 && $is_follow_follower == TRUE) && ($userSettings['question_privacy'] != 4)) {

    //Questions
    $selQ = "(select 1 as tbl,qid,date_added as dat,0 as vars  from {question} where uid='$uid' ORDER BY qid DESC) union
	(select 2 as tbl,qid,vote_pdate as dat,0 as vars  from {possible_answer_vote} where uid='$uid') union 
	(select 3 as tbl,qid_rid as qid,date_added as dat,title as vars  from {forum_wave} where uid='$uid' ) union
	(select 4 as tbl,f.qid_rid as qid,w.date_added as dat,wavelet as vars  from {forum_wavelets} w join {forum_wave} as f on f.fid=w.wid where w.uid='$uid' ) union
	(select 5 as tbl,f.qid_rid as qid,l.date_added as dat,f.title as vars  from {forumwave_like} as l join {forum_wave} as f on f.fid=l.wid where l.uid='$uid' ) union
	(select 6 as tbl,u.image_url as qid,f.joindate as dat,u.real_name as vars from {follower} as f join {user_profile} as u on u.uid=f.uid where f.follower_id='$uid' )union
	(select 7 as tbl,qid,posted_date as dat,0 as vars  from {resource} where uid='$uid') union
	(select 8 as tbl,qid,vote_date as dat,0 as vars from {suggest_answer_vote} where uid='$uid') union
	(select 9 as tbl,badge as qid,date_added as dat,badge as vars from {user_badges} where uid='$uid') 
	ORDER BY dat DESC LIMIT 0,50 ";
    $fetch = ExecuteQuery($selQ, "select");
      }

    $strReturn.='';

    if (!empty($fetch)) {



        foreach ($fetch as $list) {


            $type = $list['tbl'];

            switch ($type) {


                case '1':
                    //questions
                    $quest = get_question($list['qid']);
                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>Asked</b></span> <span><a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '2':
                    //answered

                    $quest = get_question($list['qid']);
                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>Answered</b></span> <span><a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }

                    break;
                case '3':
                    //New Wave Post
                    $quest = get_question($list['qid']);

                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>New Wave</b></span> <span>' . $list['vars'] . '<span> <b>for</b>  <a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '4':
                    $quest = get_question($list['qid']);
                    //new wavelet
                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>New Wavelets</b></span> <span>' . $list['vars'] . '<span> <b>for</b> Wave <b>in</b><a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '5':

                    //Like this wave
                    $quest = get_question($list['qid']);

                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>I like This Wave</b></span> <span>' . $list['vars'] . '<span> <b>for</b>  <a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '6':
                    //followers
                    $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                    $strReturn .= '<div ><span>' . $date . '</span><span> <b>New Follower</b></span> <span><a href="' . $gSitePath . '/profile/' . $list['vars'] . '">' . $list['vars'] . '  <img src="' . $list['qid'] . '" border="0" width="20" height="20"></a></a></span></div>';
                    break;
                case '7':
                    //New Resources
                    //New Wave Post
                    $quest = get_question($list['qid']);

                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>New Resource posted for </b> <a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '8':
                    //suggest answer answered

                    $quest = get_question($list['qid']);
                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>Suggested Answer</b></span> <span><a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '9':

                    $bad = db_fetch_object(db_query("select * from {user_badges} as ub join {badges} as b on ub.bid=b.bid where ub.badge='" . $list['vars'] . "'"));

                    //echo "<pre>"; print_r($bad);

                    if (!empty($bad)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>Awarded Badge </b></span> <span><a title=' . $bad->info . ' href="' . $gSitePath . 'badges/user/' . $bad->bid . '">' . $bad->name . ' </a></span></div>';
                    }



                    break;
                default:
                    //drupal_set_message($message = 'Oops, No Recent Activities !', $type = 'error');
                      $strReturn .='<div class="warning">No Activity Found!</div>';
                    break;
            }//switch ends
        }//foreach ends
    } else {
          $strReturn .='<div class="warning">No Activity Found!</div>';
       // drupal_set_message($message = 'Oops, No Recent Activities !', $type = 'error');
    }
    $strReturn.='</div>';
    // return $uid;
    echo $strReturn;
}

function google_map() {
    $page = $_REQUEST[q];
    switch ($page) {

        case 'google/map/users':
            $variable = "Users";
            //$geomap_qry = "SELECT count(country)as count,country from `user_profile` where country REGEXP '[^0-9]' group by country ";
            $geomap_qry = "select count(u.uid) as count,up.country from users as u join user_profile as up on u.uid=up.uid where u.status=1 and up.country REGEXP '[^0-9]' group by up.country";
            $geomap_exec = ExecuteQuery($geomap_qry, "select");
            $cnt = db_result(db_query(" select count(u.uid) from users as u join user_profile as up on u.uid=up.uid where u.status=1 and up.country REGEXP '[^0-9]'"));

            $first = 0;
            foreach ($geomap_exec as $geomapeach) {

                $asscountry .= " data.setValue(" . $first . ", 0,'" . $geomapeach['country'] . "');" . ' data.setValue(' . $first . ', 1,' . $geomapeach['count'] . ');';
                // $assuser .=  'data.setValue(5, 1,'.$geomapeach['count'].');';
                $first = $first + 1;
            }
            break;
        case 'google/map/online':
            $variable = "Online";
            $time_period = variable_get('user_block_seconds_online', 900);
            $cnt = db_query('SELECT count(*) access FROM {users} WHERE access >= %d AND uid != 0 ORDER BY access DESC', time() - $time_period);

            //$userslist = db_query('SELECT * FROM users as u join user_profile as up on u.uid=up.uid  WHERE u.access >= %d AND u.uid != 0 group BY up.country', time() - $time_period);
            //echo $total_users = db_result($userslist);

            $get_ans = db_query('SELECT count(*) as count,up.* FROM users as u join user_profile as up on u.uid=up.uid  WHERE u.access >= %d AND u.uid != 0 AND up.country REGEXP \'[^0-9]\'  group BY up.country', time() - $time_period);
            $first = 0;
            while ($geoans = db_fetch_object($get_ans)) {
                $first = $first + 1;
                $asscountry .= " data.setValue(" . $first . ", 0,'" . $geoans->country . "');" . ' data.setValue(' . $first . ', 1,' . $geoans->count . ');';
            }

            //$geomap_qry = "'SELECT * FROM users as u join user_profile as up on u.uid=up.uid  WHERE u.access >= %d AND u.uid != 0 group BY up.country', time() - $time_period";
            //$geomap_exec= ExecuteQuery($geomap_qry, "select");
//            foreach($geomap_exec as $geomapeach){
//               echo $geomapeach['country'];
//            // $asscountry .=  "data.setValue(5, 0,'".$geomapeach['country']."');";
//            //$assuser .=  'data.setValue(5, 1,'.$geomapeach['uid'].');';
//             }
            break;
        case 'google/map/questions':
            $variable = "Issues";
            // $geomap_qry = "select count(*)as count,q.country from question as q join users as u on q.uid=u.uid where q.status='1' group by q.country";
             $cnt = db_result(db_query("select count(*) from {content_field_issue_country}  where field_issue_country_value REGEXP '[^0-9]'"));

            // $geomap_qry = "select count(*) as count, country from question where country REGEXP '[^0-9]' group by country";
            $geomap_qry = "select count(*) as count,field_issue_country_value as country from {content_field_issue_country} where field_issue_country_value REGEXP '[^0-9]' group by field_issue_country_value";
            $geomap_exec = ExecuteQuery($geomap_qry, "select");

            $first = 0;
            foreach ($geomap_exec as $geomapeach) {

                $asscountry .= " data.setValue(" . $first . ", 0,'" . $geomapeach['country'] . "');" . ' data.setValue(' . $first . ', 1,' . $geomapeach['count'] . ');';
                $first = $first + 1;
            }
            break;
        case 'google/map/answer':
            $variable = "Votes";
            $geomap_qry = "select count(*)as count,q.field_issue_country_value as country from {poll_votes} as a join {content_field_issue_country} as q on q.nid=a.nid where q.field_issue_country_value REGEXP '[^0-9]' group by q.field_issue_country_value";
            $geomap_exec = ExecuteQuery($geomap_qry, "select");
            $cnt = db_result(db_query("select count(*) from {poll_votes} as a join {content_field_issue_country} as q on q.nid=a.nid where q.field_issue_country_value REGEXP '[^0-9]'"));

            $first = 0;
            foreach ($geomap_exec as $geomapeach) {

                $asscountry .= " data.setValue(" . $first . ", 0,'" . $geomapeach['country'] . "');" . ' data.setValue(' . $first . ', 1,' . $geomapeach['count'] . ');';


                $first = $first + 1;
            }
            break;
    }
    if ($_REQUEST['width'] == '155')
        $vars = ' geomap.draw(data,{width:155,height:100,showLegend:false});';
    else
        $vars=' geomap.draw(data,{width:600,height:400,showLegend:true});';

    echo $script .= "<script type='text/javascript' src='http://www.google.com/jsapi'></script>";
    echo $script.="<script type='text/javascript'>
    google.load('visualization', '1', {packages: ['geomap']});

    function drawVisualization() {
      var data = new google.visualization.DataTable();
      data.addRows(50);
      data.addColumn('string', 'Country');
      data.addColumn('number', '" . $variable . "');" . $asscountry . "
      var geomap = new google.visualization.GeoMap(
          document.getElementById('visualization'));
     " . $vars . "
    }
    google.setOnLoadCallback(drawVisualization);
  function loadtab(href,title){
    	  var options = 'sameBox:true width:650px height:370px caption:'+title;

 parent.fb.start(href, options);
}
  </script>";

    echo "<div id=visualization style='cursor:pointer;' onclick=\"return loadtab('" . url($_GET['q'], array('absolute' => true)) . "','`Facts And Figures : " . $variable . " : " . $cnt . "  `')\"></div>";
}

function amber_tour() {

    global $gSitePath, $user, $gDocPath, $base_root;

    $page = substr($_REQUEST['q'], strrpos($_REQUEST['q'], '/'));
    $page = ltrim($page, '/');

    switch ($page) {
        case home:
            $output = '<img width="650" height="600" src="' . $gSitePath . path_to_theme() . '/images/tour/home.jpg"/>';
            break;

        case question:
            $output = '<img width="650" height="600" src="' . $gSitePath . path_to_theme() . '/images/tour/addquestion.jpg"/>';
            break;

        case donate:
            $output = '<img width="650" height="600" src="' . $gSitePath . path_to_theme() . '/images/tour/donate.jpg"/>';
            break;
    }

    return $output;
}

// update profile
function update_profile() {

    global $gSitePath, $user, $gDocPath, $base_root, $apikey;
    $data = '

var spath=\'' . $gSitePath . '\';
';
    drupal_add_js($data, 'inline');
    drupal_add_js(drupal_get_path('module', 'profiles') . '/js/validate.js');
    drupal_add_js(drupal_get_path('module', 'profiles') . '/js/profile.js');
    
    $update = '';
    $update .= drupal_get_form('user_details');
    return $update;
}

function user_details() {
    global $gSitePath, $user, $gDocPath, $base_root, $apikey;
    $details = load_user($user->uid);
       $form['#attributes']['enctype'] = "multipart/form-data";
    $form['#attributes']['onsubmit'] = "return validate_reg();";
    $form['main_div'] = array('#type' => 'markup', '#value' => '<div class="newcretae-profile-wrapper">');
    $form['right_div'] = array('#type' => 'markup', '#value' => '<div class="newcretae-profile-rightside"><h3>SOCIAL  NETWORK SETTINGS</h3>');
    $form = $form + get_avatar_form();
    $form['right_div_close'] = array('#type' => 'markup', '#value' => '</div>');

    $form['left_div_top'] = array('#type' => 'markup', '#value' => '<div class="newcretae-profile-leftside">');
    $form['left_div'] = array('#type' => 'markup', '#value' => '<div class="newcretae-profile-leftside-forms">
                          <h3>'.t('PERSONAL INFO AND DEMOGRAPHICS').'</h3>
                          <div class="form-wra">
                          &nbsp;
                          <div class="clr"></div> </div>');
    $form['username'] = array(
        '#type' => 'textfield',
        '#title' => t(''),
        '#maxlength' => 20,
        '#description' => t(''),
        '#default_value' => variable_get('username', ''),
        '#id' => 'username',
        '#required' => 1,
        '#prefix' => ' <div class="form-wra"><div class="form-wra-1">'.t('User Name').'</div>
                <div class="form-wra-2">',
        '#suffix' => '</div>
           <div class="clr"></div>
           </div>',
        '#attributes' => array('class' => 'input-nor','onblur'=>'chk_uname(this.value);'),
    );
    $form['fname'] = array(
        '#type' => 'textfield',
        '#title' => t(''),
        '#maxlength' => 20,
        '#description' => t(' '),
        '#default_value' => variable_get('fname', ''),
        '#id' => 'name',
        '#prefix' => ' <div class="form-wra"><div class="form-wra-1">'.t('Name').'</div>
                <div class="form-wra-2">',
        '#suffix' => '</div>
           <div class="clr"></div>
           </div>',
        '#attributes' => array('class' => 'input-nor'),
    );
    $form['email'] = array(
        '#type' => 'textfield',
        '#title' => t(''),
        '#maxlength' => 50,
        '#description' => t(' '),
        '#default_value' => variable_get('email', ''),
        '#id' => 'email',
        '#required' => 1,
        '#prefix' => ' <div class="form-wra"><div class="form-wra-1">'.t('Email').'</div>
                <div class="form-wra-2">',
        '#suffix' => '</div>
           <div class="clr"></div>
           </div>',
        '#attributes' => array('class' => 'input-nor'),
    );
    $form['gender'] = array(
        '#type' => 'select',
        '#title' => t(''),
        '#options' => array('0' => 'Gender', 1 => 'Male', 2 => 'Female'),
        '#description' => t(' '),
        '#default_value' => variable_get('gender', ''),
        '#id' => 'gender',
        '#prefix' => ' <div class="form-wra"><div class="form-wra-1">'.t('Gender').'</div>
                <div class="form-wra-2">',
        '#suffix' => '</div>
           <div class="clr"></div>
           </div>',
        '#attributes' => array('class' => 'input-sma'),
    );
    $form['dob'] = array(
        '#type' => 'textfield',
        '#title' => t(''),
        '#maxlength' => 4,
        '#description' => t(' '),
        '#default_value' => variable_get('dob', ''),
        '#id' => 'year',
        '#prefix' => ' <div class="form-wra"><div class="form-wra-1">'.t('Year of Birth').'</div>
                <div class="form-wra-2">',
        '#suffix' => '</div>
           <div class="clr"></div>
           </div>',
        '#attributes' => array('class' => 'input-sma'),
    );

    $form['zip'] = array(
        '#type' => 'textfield',
        '#title' => t(''),
        '#maxlength' => 10,
        '#description' => t(''),
        '#default_value' => variable_get('zip', ''),
        '#id' => 'location',
        '#prefix' => ' <div class="form-wra"><div class="form-wra-1">'.t('Zip').'</div>
                <div class="form-wra-2">',
        '#suffix' => '</div>
           <div class="clr"></div>
           </div>',
        '#attributes' => array('class' => 'input-nor', 'onblur' => 'get_zip_city(this.value);', 'onkeypress' => 'dis_submit()')
    );
    $form['country'] = array(
        '#type' => 'hidden',
        '#default_value' => variable_get('country', $details->country),
        '#id' => 'country',
    );
    $form['state'] = array(
        '#type' => 'hidden',
        '#default_value' => variable_get('state', $details->state),
        '#id' => 'state',
    );
    $form['city'] = array(
        '#type' => 'hidden',
        '#default_value' => variable_get('city', $details->state),
        '#id' => 'city',
    );
    $form['religion'] = array(
        '#type' => 'select',
        '#title' => t(''),
                        '#options' => array('0' => 'Religion','Christian'=>'Christian (Cath or Prod)','Muslim' => 'Muslim (Suni Shiite)','Hindu' => 'Hindu','Jewish'=>'Jewish','Buddhist'=>'Buddhist','Other'=>'Other'),
        '#description' => t(' '),
        '#default_value' => variable_get('religion', ''),
        '#id' => 'religion',
        '#prefix' => ' <div class="form-wra"><div class="form-wra-1">'.t('Religion').'</div>
                <div class="form-wra-2">',
        '#suffix' => '</div>
           <div class="clr"></div>
           </div>',
        '#attributes' => array('class' => 'input-sma'),
    );
    $form['ethnic'] = array(
        '#type' => 'select',
        '#title' => t(''),
        '#options' => array('0' => 'Ethnicity','Caucasian'=>'Caucasian','Black'=>'Black','Asian' => 'Asian','Indian' => 'Indian','Semetic'=>'Semetic','Latin'=>'Latin','Aborigines'=>'Aborigines' ),
        '#description' => t(' '),
        '#default_value' => variable_get('ethinicity', ''),
        '#id' => 'ethnicity',
        '#prefix' => ' <div class="form-wra"><div class="form-wra-1">'.t('Ethnic').'</div>
                <div class="form-wra-2">',
        '#suffix' => '</div>
           <div class="clr"></div>
           </div>',
        '#attributes' => array('class' => 'input-sma'),
    );

    $form['sorient'] = array(
        '#type' => 'select',
        '#title' => t(''),
         '#options' => array('0' => 'Sexual Orientation', 'Straight' => 'Straight', 'Gay' => 'Gay','Bisexual'=>'Bisexual','Transgender'=>'Transgender'),
        '#default_value' => variable_get('sorient', ''),
        '#description' => t(' '),
        '#id' => 'sex',
        '#prefix' => ' <div class="form-wra"><div class="form-wra-1">'.t('Sexual Orientation').'</div>
                <div class="form-wra-2">',
        '#suffix' => '</div>
           <div class="clr"></div>
           </div>',
        '#attributes' => array('class' => 'input-sma'),
    );
        $form['education'] = array(
        '#type' => 'select',
        '#title' => t(''),
        '#options' => array('0' => 'Education Level', 'No High School' => 'No High School', 'High School' => 'High School', 'Technical College' => 'Technical College', 'University' => 'University', 'Masters Degree' => 'Masters Degree'),
        '#description' => t(' '),
        '#default_value' => variable_get('education', ''),
        '#id' => 'education',
        '#prefix' => ' <div class="form-wra"><div class="form-wra-1">'.t('Education').'</div>
                <div class="form-wra-2">',
        '#suffix' => '</div>
           <div class="clr"></div>
           </div>',
        '#attributes' => array('class' => 'input-sma'),
    );
    $form['income'] = array(
        '#type' => 'select',
        '#title' => t(''),
        '#options' => array('0' => 'Select', '$0-$9,999' => '$0-$9,999', '$10,000 - $19,999' => '$10,000 - $19,999','$20,000 - $39,999'=>'$20,000 - $39,999','$40,000 - $69,999'=>'$40,000 - $69,999','$70,000 - $99,999'=>'$70,000 - $99,999','$100,000 - $149,999'=>'$100,000 - $149,999','$150,000 - $299,999'=>'$150,000 - $299,999','>$300,000'=>'>$300,000'),
        '#description' => t(' '),
        '#default_value' => variable_get('income', ''),
        '#id' => 'income',
        '#prefix' => ' <div class="form-wra"><div class="form-wra-1">'.t('Income Range').'[USD]</div>
                <div class="form-wra-2">',
        '#suffix' => '  </div>
           <div class="clr"></div>
           </div>',
        '#attributes' => array('class' => 'input-sma'),
    );
    $form['marital'] = array(
        '#type' => 'select',
        '#title' => t(''),
        '#options' => array('0' => 'Select', 'Single' => 'Single', 'Married' => 'Married','Divorced'=>'Divorced','Widow'=>'Widow'),
        '#description' => t(' '),
        '#default_value' => variable_get('marital', ''),
        '#id' => 'marital',
        '#prefix' => ' <div class="form-wra"><div class="form-wra-1">'.t('Marital Status').'</div>
                <div class="form-wra-2">',
        '#suffix' => ' </div>
           <div class="clr"></div>
           </div>',
        '#attributes' => array('class' => 'input-sma'),
    );
    $form['bio'] = array(
        '#type' => 'textarea',
        '#title' => t(''),
        '#default_value' => variable_get('description', ''),
        '#cols' => '',
        '#rows' => 1,
        '#description' => t(''),
        '#default_value' => variable_get('bio', ''),
        '#id' => 'bio',
        '#prefix' => ' <div class="form-wra"><div class="form-wra-1">'.t('Bio').'</div>
                <div class="form-wra-2">',
        '#suffix' => '</div>
           <div class="clr"></div>
           </div>',
        '#attributes' => array('class' => 'input-nor'),
    );
    $form['text'] = array('#type' => 'markup', '#value' => '<div class="form-wra">
           	           '.t('When I vote on issues or post content to Heard
Mentality I want the following privacy settings applied
when other users view my profile').'
           <div class="clr"></div>
           </div>');
    $form['left_div_close'] = array('#type' => 'markup', '#value' => '</div>');
    $form['left_privacy'] = array('#type' => 'markup', '#value' => '<div class="newcretae-profile-leftside-privacy">');
    $form = $form + get_privacy_form();
    $form['left_privacy_close'] = array('#type' => 'markup', '#value' => '<div class="clr"></div></div>');
    $form['left_div_bottom'] = array('#type' => 'markup', '#value' => '<div class="clr"></div></div>');

    $form['main_div_close'] = array('#type' => 'markup', '#value' => '<div class="clr"></div></div>');

    // set default values
    $form['bio']['#default_value'] = empty($details->bio) ? 'Bio' : $details->bio;
    
    $form['sorient']['#default_value'] = empty($details->sorient) ? '0' : $details->sorient;
    $form['income']['#default_value'] = empty($details->income) ? '0' : $details->income;
     $form['marital']['#default_value'] = empty($details->marital) ? '0' : $details->marital;
    $form['education']['#default_value'] = empty($details->edu) ? '0' : $details->edu;
    $form['ethnic']['#default_value'] = empty($details->ethnic) ? '0' : $details->ethnic;
    $form['religion']['#default_value'] = empty($details->religion) ? '0' : $details->religion;
    $form['zip']['#default_value'] = empty($details->zip) ? 'Zip code' : $details->zip;
    $form['gender']['#default_value'] = empty($details->gender) ? '0' : $details->gender;
    $form['dob']['#default_value'] = empty($details->dob) ? 'Year OF Birth' : $details->dob;
    $form['email']['#default_value'] = empty($details->mail) ? 'Email' : $details->mail;
    $form['fname']['#default_value'] = empty($details->real_name) ? 'Name' : $details->real_name;
    $form['username']['#default_value'] = empty($details->name) ? 'Username' : $details->name;
    return $form;
}

function get_privacy_form() {

    global $gSitePath, $user, $gDocPath, $base_root, $apikey;
    $query = "select * from {user_profile} where uid='$user->uid'";
    $fetch = ExecuteQuery($query, "select");
    $options = array('1' => t(''), '2' => t(''), '3' => t(''), '4' => t(''));
    $query = "select * from {profile_fields} ORDER BY `profile_fields`.`fid` ASC";
    $result = db_query($query);
    $form['privacy_setting'] = array('#type' => 'markup', '#value' => '<h3>'.t('PRIVACY SETTINGS').'</h3>
              <div class="form-wra">
           	    <div class="form-wra-4">'.t('Anyone').'</div>
                <div class="form-wra-4">'.t('Logged in Users').'</div>
                <div class="form-wra-4">'.t('Followers & Followees').'</div>
                <div class="form-wra-4">'.t('No one').'</div>
           <div class="clr"></div>
           </div>');
    $form['username_privacy'] = array(
        '#type' => 'markup',
        '#value' => '<div class="form-wra">&nbsp;
                     <div class="clr"></div>
                     </div>',
    );
    while ($meta = db_fetch_object($result)) {
        $col = $fields[] = $meta->name;
        $list = trim($fetch[0][$col]);

        $sel = db_result(db_query("SELECT $col FROM {privacy_settings} WHERE uid = '%d'", $user->uid));
        $sel=empty($sel) ? '1' : $sel;
        $form[$col . '_privacy'] = array(
            '#type' => 'radios',
            '#default_value' => variable_get($col . '_privacy', $sel),
            '#options' => $options,
            // '#attributes'=>array('class'=>'form-wra'),
            '#prefix' => '<div class="form-wra">',
            '#suffix' => '<div class="clr"></div></div>'
        );
   
       
        $form['div_down'] = array('#type' => 'markup', '#value' => '
          <div class="clr"></div>
       ');
    }

    $form['activity_privacy'] = array(
        '#type' => 'radios',
        '#default_value' => variable_get('activity_privacy', $fetch[0]['question_privacy']),
        '#options' => $options,
        '#prefix' => '<br/><br/><br/><div class="form-wra">',
        '#suffix' => '<div class="clr"></div></div>',
        '#suffix' => '<div class="clr"></div>'
    );
    $form['mid_div'] = array('#type' => 'markup', '#value' => '
          <div class="clr"></div>
       ');
    return $form;
}

function get_avatar_form() {
    global $gSitePath, $user, $gDocPath, $base_root, $apikey, $theme;
    $form = array();
    drupal_add_js(drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection.js');
    drupal_add_js(drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection_pager.js');
    drupal_add_css(drupal_get_path('module', 'avatar_selection') . '/avatar_selection.css');
    drupal_add_js(drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection_pager.js');
    drupal_set_html_head('<script src="http://cdn.gigya.com/JS/socialize.js?apikey=' . $apikey . '" type="text/javascript"></script>');
    drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection.js';
    $account = load_user($user->uid);
    $data = '
	    var conf =
        {
            APIKey: \'' . $apikey . '\'
        };
var avtar=\'' . $account->avatar . '\';
';
    drupal_add_js($data, 'inline');

    // set the form encoding type
    $form['avatar_div'] = array('#type' => 'markup', '#value' => '<div class="newimage-upload">');
    $form['#attributes']['enctype'] = "multipart/form-data";
    $options = array('1' => t('weekly'), '2' => t('monthly'), '0' => t('never'));
    // add a file upload file
    $form['file_upload'] = array(
        '#type' => 'file',
        '#size' => '10',
        '#description' => t('Select an image file on your computer. (2MB max) '),
        '#prefix' => '<div class="avatar">
            <div class="avatar-right">
            <div class="pick-avatar" onClick="jQuery(\'#avatar-profile-ele\').slideToggle();"></div>
- Or -
            <div class="clr"></div>
            <div></div>
            <div class="clr"></div>',
        '#suffix' => '</div>
        	<div class="avatar-left">' . UserPicture($user->uid, 0) . '</div>

        <div class="clr"></div>
        </div>'
    );
       $form['oldimg'] = array(
                '#type' => 'hidden',
                '#default_value' => variable_get('oldimg', $details->image),
                '#id' => 'oldimg',
            );
    $form['avatar_div_close'] = array('#type' => 'markup', '#value' => '<div class="clr"></div>
    </div><div class="clr"></div>');


    $form['notify'] = array(
        '#type' => 'radios',
        '#prefix' => '<div class="summarymail"><p>'.t('Send me a summary of my subscriptions to my email').'</p>
                    <div class="form-wra bortopnone">',
        '#default_value' => variable_get('notify', $account->notify_etype),
        '#options' => $options,
        '#suffix' => '<div class="clr"></div>
                            </div>
                            </div>');
    $form['merge'] = array('#type' => 'markup', '#value' => '
                <div class="clr"></div>
        <div class="merge-social-new">
          <div align="center">'.t('Select the Social networks you want to share you Heard Mentality opinions add posts with.').'</div>
          <div class="clr"></div>
          <div align="center" class="merge-script-outer-new">
          <div id="divConnect"></div>
    <script type="text/javascript">
        // show Add Connections Plugin in "divConnect"
        gigya.services.socialize.showAddConnectionsUI(conf, {
			height:65
			,width:175
			,showTermsLink:false //remove trems link
			,hideGigyaLink:true // remove Gigya link
			,useHTML:true  // Use the HTML implementation of the Plugin (rather then Flash implementation)
			,containerID: "divConnect" // The component will embed itself inside the divConnect Div
		});
    </script>
         </div>
    </div>
          <div class="clr"></div>');

    //$form['personal_links'] = array('#type' => 'markup', '#value' => '<div class="web-reference-new">');


    $form['fb_outer'] = array('#type' => 'markup',
        '#value' => '<div class="web-reference-new">
                     <div class="web-reference-tit-new">'.t('PERSONAL LINKS').'</div>
                     <div class="clr"></div>');

    $social = explode('||', $account->social);
    $form['facebook'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="social-outer-new">
                          <div class="social-left-new">
                          <img width="26" height="27" alt="facebook" src="' . $gSitePath . drupal_get_path('theme', $theme) . '/images/soc-face.jpg"></div>
                          <div class="social-rite-new">',
        '#description' => t(''),
        '#default_value' => variable_get('facebook', $social[0]),
        '#id' => 'face',
        '#suffix' => '</div>
                         </div><div class="clr"></div>',
    );
    $form['twitter'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div class="social-outer-new">
                          <div class="social-left-new"><img width="26" height="27" alt="Twitter" src="' . $gSitePath . drupal_get_path('theme', $theme) . '/images/soc-twit.jpg"></div>
                          <div class="social-rite-new">',
        '#description' => t(' '),
        '#default_value' => variable_get('twitter', $social[1]),
        '#id' => 'twitter',
        '#suffix' => '</div>
                         </div>
                         <div class="clr"></div>',
    );
     $form['myweb'] = array(
                '#type' => 'textfield',
                '#title' => t(''),
                '#description' => t(''),
                '#default_value' => variable_get('myweb', $account->urls),
                '#id' => 'myweb',
                 '#prefix' => '<div class="social-outer-new">
                         
                          <div class="social-left-new">My Website :</div><div class="social-rite-new">',
                '#suffix' => '</div>
                         </div>
                         <div class="clr"></div>',
            );
    $form = $form + follow_links_form($form_state, $user->uid);
    // avatar hidden values
    $form['img_avt'] = array('#type' => 'hidden', '#default_value' => variable_get('img_avt', $account->image_avatar));
    $form['image'] = array('#type' => 'hidden', '#default_value' => variable_get('image', $account->image));

    $form['bot_div'] = array('#type' => 'markup', '#value' => '<div class=" clr"></div>
      </div>');

    $form['hiddentop'] = array('#type' => 'markup', '#value' => '<div id="avatar-profile-ele" class="d-header" style="display:none;background-color:white;width:350px;position:absolute;top:200px;left:350px;"><a href="javascript:void(0)" onclick="jQuery(\'#avatar-profile-ele\').slideToggle();update_avatar();" style="float:right">close[X]</a>');
    $form = $form + inc_avatar_form($form, $form_state);
    $form['hiddenbot'] = array('#type' => 'markup', '#value' => '</div>');
    $languages = i18n_language_list();
    $form['default_language'] = array('#type' => 'select', '#prefix' => t('Default Language'), 
                                        '#options' => $languages, '#suffix' => '<br />',
                                        '#default_value' => $account->language);
    $form['submit'] = array('#type' => 'submit', '#value' => 'Submit', '#id' => 'update_submit');
    return $form;
}

function user_details_validate($form, &$form_state) {
    global $gSitePath, $user, $gDocPath, $base_root, $apikey;
    $step = $form_state['values']['step'];
    $dob = $form_state['values']['dob'];
    $zip = $form_state['values']['zip'];
    $state = $form_state['values']['state'];
    $uname = $form_state['values']['username'];

    if (!preg_match('/^[A-Za-z0-9_]{5,20}$/i', $uname)) {
        form_set_error('username', t('Username should be Alphabets, numbers and no special characters min 5 and max 20 allowed'));
        $form_state['rebuild'] = TRUE;
    } elseif (db_result(db_query("SELECT COUNT(*) FROM {users} WHERE name = '%s' AND uid!='%d'", $uname, $user->uid))) {
        form_set_error('username', t('Sorry Username already exists try any other combination'));
        $form_state['rebuild'] = TRUE;
    }
    
    if (!empty($dob)) {

        if (!is_numeric($dob) || strlen($dob) != '4') {
            form_set_error('dob', t('Year Of Birth should be Numeric & Proper Format Ex : 1986'));
            $form_state['rebuild'] = TRUE;
        }
    }
    if (!empty($zip)) {
        if (!preg_match('/^[0-9A-Za-z ]+?$/i', $zip)) {
            form_set_error('zip', t('Zip Code should be Proper One & Proper Format Ex : 11010'));
            $form_state['rebuild'] = TRUE;
        } elseif (empty($state)) {
            form_set_error('zip', t('Kindly Recheck your Zip Code, We find its invalid one! '));
            $form_state['rebuild'] = TRUE;
        }
    }
}

function user_details_submit($form, &$form_state) {
    global $gSitePath, $user, $gDocPath, $base_root, $apikey;

    //profile fields update
    _basic_submit($form, $form_state);
    //privacy update
    _privacy_submit($form, $form_state);
    //avatar update
    _avatar_submit($form, $form_state);

    
    /*New SET NOTIFY LOG*/
    $variable = array();
    set_notify_log($user->uid, '', 'update_profile', $variable);
    /*New SET NOTIFY LOG*/


    drupal_set_message(t('Your profile has been updated'), 'success');
}
