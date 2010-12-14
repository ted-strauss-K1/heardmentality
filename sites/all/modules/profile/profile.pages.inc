<?php

// tree menu listing
function profile_view() {
  
    global $gSitePath, $user, $gDocPath, $base_root;
    $profile_name = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $uid = '';

    $profile_name = strtolower($profile_name);
    $getuser = user_load(array('name' => $profile_name));

    if (isset($getuser) && !empty($getuser)) {

        $uid = $getuser->uid;
    }

    if ($uid == '') {
        $uid = $user->uid;
    }
    $strReturn = '';

if($uid=='')
{
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

            $strReturn = activities($uid);
            break;
        case 'history':
            $strReturn = profile_tab($tag,$uid);
            break;
        case 'badge':
              $strReturn = profile_tab($tag,$uid);
            break;
        case 'info':
              $strReturn = profile_tab($tag,$uid);
            break;
        case 'msg':
             $strReturn = profile_tab($tag,$uid);
        default:
		// $strReturn ="something wrong";
//badges
           enthusiast($uid);
            fanatic($uid);
            $strReturn = profile($uid);
            break;
    }
     
if(isAjax ())
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
    drupal_add_js(drupal_get_path('module', 'profile') . '/js/profile.js');
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



// Edit Profile
function profile_edit() {
    global $gSitePath, $user, $gDocPath, $base_root;
    $result_profile_edit = db_query("UPDATE {users} set profile_edit='1' where uid='$user->uid' ");
    //print_r($_REQUEST);
    $uid = $user->uid;
    $bio = '';
    $real_name = '';
    $gender = '';
    $optionlist = '';
    $image = 'noimage.jpg';
    $zip = '';
    $country = '';
    $slant = '';
    $religion = '';
    $ethnic = '';
    $facebook = '';
    $twitter = '';
    $check1 = '';
    $check2 = '';
    $question_privacy = '4';
    $dob = '';
    //exit;
    if ($_REQUEST['update'] == 'Update') {

        extract($_REQUEST);
        if ($rname == '') {
            drupal_set_message($message = 'User Name should not be empty!', $type = 'error');
            drupal_goto('profile/edit');
        }


        if (isset($_FILES)) {


            $return = event_photo();
            //print_r($return);
            $insimage = $return['image'];
            $flag = $return['flag'];
            $suc = $return['suc'];
        }

        $chk = db_query("select * from {user_profile} where uid='$user->uid'");
        $chk1 = db_result($chk);


        if ($chk1) {

            $update_user = db_query("update {users} set mail='$mail' ,notify_etype='$ntype',notify_itype='$nitype' where uid='$user->uid' ");

            $result = db_query("UPDATE {user_profile} set uid='$user->uid',real_name='$rname',gender='$gender',image='$insimage',bio=' $bio',zip='$zip',country='$country',state='$state',city='$city',religion='$religion',ethnic='$ethnic',dob='$dob',slant='$slant',facebook='$facebook',twitter='$twitter',question_privacy='$qrset',first_name='$fname',last_name='$lname' where uid='$user->uid' ");

        } else {
            $result = db_query("INSERT INTO {user_profile} set uid='$user->uid',real_name='$rname',gender='$gender',image='$insimage',bio=' $bio',zip='$zip',country='$country',state='$edit-state',city='$edit-city',religion='$religion',ethnic='$ethnic',dob='$dob',slant='$slant',facebook='$facebook',twitter='$twitter',question_privacy='$qrset'");
        }
        if ($result) {
            $sucflag = '';
            $sucflag = 1;
            drupal_set_message($message = 'Profile Updated Successfully!', $type = 'success');
        }
        if (!empty($pass1)) {

            if ($pass1 == $pass2) {

                $result = db_query("UPDATE {users} set pass='" . md5($pass1) . "' where uid='$user->uid' ");
                drupal_set_message($message = 'Password Updated Successfully!', $type = 'success');
            } else {

                drupal_set_message($message = 'Password should be same to chnage!', $type = 'error');
            }
        } else {
            if ($sucflag) {
                // echo "<script>window.location.href='".$gSitePath."'profile/';</script>";
                drupal_goto('profile/');
            }
        }
    }

    $get_cn = db_query("select * from {user_profile} where uid='$user->uid'");
    $result = db_fetch_array($get_cn);

    extract($result);

    drupal_add_js(drupal_get_path('module', 'profile') . '/js/en.js');
    drupal_add_js(drupal_get_path('module', 'profile') . '/js/profile.js');
    drupal_add_js(drupal_get_path('module', 'profile') . '/js/formcheck.js');
    drupal_add_css(drupal_get_path('module', 'profile') . '/theme/classic/formcheck.css');
    //geoname
    $options = array('sortby' => 'countryname', 'sortorder' => 'ASC');
    $result = geonames_query('countryinfo', NULL, $options);
    foreach ($result->results as $countries) {
        $select = '';
        if ($country == $countries['countrycode']) {
            $select = "SELECTED='SELECTED'";
        }

        $optionlist .= sprintf('<option %s value="%s">%s</option>', $select, $countries['countryname'], $countries['countryname']);
    }
    //echo $user->notify_type;
    if ($user->notify_etype == 1) {
        $checkm = "checked='checked'";
    }

    if ($user->notify_itype == 1) {
        $checkf = "checked='checked'";
    }
    if ($gender == 1) {
        $check1 = "checked='checked'";
    } elseif ($gender == 2) {
        $check2 = "checked='checked'";
    }
    if (!empty($state)) {

        $statecity = '<b>Province/State :</b>' . $state . '<br/><b>City :</b>' . $city . '
				<input type="hidden" name="state" value="' . $state . '">
				<input type="hidden" name="city" value="' . $city . '">
				';
    }



    $strReturn = '	<script>
		var spath=\'' . $gSitePath . '\';
		</script>
		<script src="' . $gSitePath . 'sites/all/modules/profile/js/profile.js" type="text/javascript"></script>
		
		<form name="profile" id="profile"  onsubmit="return validate_profile();"  method="post" enctype="multipart/form-data">
		<fieldset>
        	<legend><b><i>Account information</i></b></legend>
				<!--<div class="form-item" id="edit-name-wrapper"> 
					<label for="edit-name">Username: <span class="form-required" title="This field is required.">*</span></label> <input maxlength="60" name="name" id="edit-name" disabled="disabled" size="60" value="' . $user->name . '" class="form-text required" type="text">
                     
					<div class="description">Spaces are allowed; punctuation is not allowed except for periods, hyphens, and underscores.</div>
               </div>-->
			<div class="form-item" id="edit-mail-wrapper"> 
            	<label for="edit-mail">E-mail address: <span class="form-required" title="This field is required.">*</span></label> <input maxlength="64" name="mail" id="edit-mail" size="60"  value="' . $user->mail . '"  class="form-text required" type="text">
                <div class="description">A valid e-mail address. All e-mails from the system will be sent to this address. The e-mail address is not made public and will only be used if you wish to receive a new password or wish to receive certain news or notifications by e-mail.</div>
           </div>

		<!-- <div class="form-item" id="edit-pass-wrapper">

        	<div class="form-item" id="edit-pass-pass1-wrapper"> 
            	<label for="edit-pass-pass1">Password: </label> <input name="pass1" id="edit-pass-pass1" maxlength="128" size="25" class="form-text password-field validate[\'required\']" type="password">
            </div>
			<div class="form-item" id="edit-pass-pass2-wrapper"> <label for="edit-pass-pass2">Confirm password: </label> <input name="pass2" id="edit-pass-pass2" maxlength="128" size="25" class="form-text password-confirm validate[\'required\',\'confirm[password]\']" type="password"></div> 
            <div class="description">To change the current user password, enter the new password in both fields.</div>
       </div>
	  <div class="form-item"> <label>Status: </label>
             <div class="form-radios">
                 <div class="form-item" id="edit-status-0-wrapper"> <label class="option" for="edit-status-0"><input id="edit-status-0" name="status" value="0"  class="form-radio validate[\'required\']" type="radio"> Blocked</label></div>
		         <div class="form-item" id="edit-status-1-wrapper"> <label class="option" for="edit-status-1"><input id="edit-status-1" name="status" value="1"  class="form-radio" type="radio"> Active</label></div>
             </div> 
		</div> -->
     </fieldset>
   
		<fieldset>
			<legend> <b><i>Profile Bio</i></b> </legend>
				<div class="form-item" id="edit-name-wrapper"> 
					<label for="edit-rname">User Name: <span class="form-required" title="This field is required.">*</span></label> <input maxlength="60" name="rname" id="edit-rname" size="40"  value="' . $real_name . '"  class="form-text required"  type="text">
					
                </div>
				<div class="form-item" id="edit-fname-wrapper"> 
					<label for="edit-rname">First Name: </label> <input maxlength="60" name="fname" id="edit-fname" size="40"  value="' . $first_name . '"  class="form-text required"  type="text">
					
                </div>
				
				<div class="form-item" id="edit-lname-wrapper"> 
					<label for="edit-lname">Last Name: </label> <input maxlength="60" name="lname" id="edit-lname" size="40"  value="' . $last_name . '"  class="form-text required"  type="text">
					<div class="description">Spaces are allowed; punctuation is not allowed except for periods, hyphens, and underscores.</div>
                </div>
				<div class="form-item" id="edit-image-wrapper"> <label for="edit-image">Image : </label> <input type="file" name="image" id="image" /> <img src="' . $gSitePath . drupal_get_path('module', 'profile') . '/snap/' . $image . '" align="absmiddle" alt="Profile Image" >
				<input type="hidden" name="oldimg" value="' . $image . '"/>
					<div class="description">accept only jpeg,jpg,gif format max. 1 mb size</div>
                </div>
				<div class="form-item">
				<label for="edit-dob">DOB : </label> <input name="dob"  value="' . $dob . '"  id="edit-dob" maxlength="128" size="25" class="form-text" type="text">
				<div class="description">DD/MM/YYYY</div>
				</div>

				<div class="form-item" id="edit-bio-wrapper"> <label for="edit-bio">Bio : </label> 
                	<textarea name="bio" id="edit-bio" class="form-text" rows="7" cols="70">' . $bio . '</textarea>
        			<div class="description">Describe about yourself to others.</div>
        		</div>
				<div class="form-item"> <label>Gender : </label> 
                	<div class="form-radios">
                    	<div class="form-item" id="edit-gender"> <label class="option" for="edit-gender-0"><input id="edit-gender-0" name="gender" value="1" class="form-radio" ' . $check1 . ' type="radio"> Male</label></div>
						<div class="form-item" id="edit-gender-1-wrapper"><label class="option" for="edit-gender-1"><input id="edit-gender-1" name="gender" value="2" class="form-radio" ' . $check2 . ' type="radio"> Female</label> </div>
                   </div>
				</div> 
			        		<div class="form-item" id="edit-country-wrapper"> <label for="edit-country">Country : </label><select name="country" style="width: 125px;" tabindex="16" id="edit-country">' . $optionlist . '</select> <div class="description"></div></div>
        		<div class="form-item" id="edit-zip-wrapper"> <label for="edit-zip">Zip/Postal code : </label> <input name="zip"  value="' . $zip . '" maxlength="9" onblur="get_zip_city(this.value);" id="edit-zip" maxlength="128" size="25" class="form-text" type="text"> </div>
        		        		<div class="form-item" id="edit-city-wrapper">' . $statecity . ' </div>
				<div class="form-item" id="edit-religion-wrapper"> <label for="edit-religion">Religion : ' . $religion . '</label> <select  name="religion" id="edit-religion" class="form-text" ><option value="" >Select</option><option value="Christian" >Christian (Cath or Prod)</option><option value="Muslim">Muslim (Suni Shiite)</option><option value="Jewish">Jewish</option><option value="Hindu"> Hindu</option><option value="Buddhist">Buddhist</option><option value="Other">Other</option></select> <div class="description"></div></div>
        		<div class="form-item" id="edit-ethnic-wrapper"> <label for="edit-ethnic">Ethnicity : ' . $ethnic . '</label> <select name="ethnic" id="edit-ethnic" class="form-text" ><option value="">Select </option><option value="Caucasian">Caucasian</option><option value="Black">Black</option><option value="Asian">Asian</option> <option value="Indian">Indian</option> <option value="Semetic">Semetic</option><option value="Latin">Latin</option> <option value="Aborigines">Aborigines</option>  </select> <div class="description"></div></div>
          		<div class="form-item" id="edit-slant-wrapper"> <label for="edit-slant">Slant : ' . $slant . '</label> <select name="slant" id="edit-slant"  class="form-text" ><option value="">Select</option><option value="Left">Left</option><option value="Right">Right </option> <option value="Center">Center </option>  </select><div class="description"></div></div>
         
        </fieldset>
	  <fieldset>
		<legend><b><i>Links</i></b> </legend>
		<div class="form-item" id="edit-name-wrapper"> 
			<label for="edit-facebook">Facebook: </label> <input maxlength="60" name="facebook" id="edit-facebook"  value="' . $facebook . '"  size="60"  class="form-text required" type="text">
			<div class="description"></div>
        </div>
		<div class="form-item" id="edit-twitter-wrapper"> <label for="edit-twitter">Twitter :</label> <input maxlength="64" value="' . $twitter . '"  name="twitter" id="edit-twitter" size="60" class="form-text required" type="text"> <div class="description"></div></div>
	
         
        </fieldset>	
		 <fieldset>
		<legend><b><i>Question & Resource Privacy Settings</i></b> </legend>
		<div class="form-item" id="edit-name-wrapper">
            <label for="edit-"></label>
             <input type="radio" name="qrset"  class="qrset" value="1">&nbsp;Always Post Non-Anonymous
            <div class="description"></div>
        </div>
        <div class="form-item" id="edit-name-wrapper">
            <label for="edit-"></label>
             <input type="radio" name="qrset" class="qrset" value="2">&nbsp;Only allow Followers & Followees to see
            <div class="description"></div>
        </div>
         <div class="form-item" id="edit-name-wrapper">
            <label for="edit-"></label>
             <input type="radio" name="qrset" class="qrset"  value="3">&nbsp;Only Post Anonymous
            <div class="description"></div>
        </div>
        <div class="form-item" id="edit-name-wrapper">
            <label for="edit-"></label>
             <input type="radio" name="qrset" class="qrset"  value="4">&nbsp;Prompt on all (if prompt all, pop up to ask if he wants to share with
everyone or just followers or not at all while adding a question)
            <div class="description"></div>
        </div>
		
		  <div class="form-item" id="edit-name-wrapper">
            <label for="edit-">Notify Type </label>
             <input name="ntype" type="checkbox" ' . $checkm . '  value="1"  /> E-mail    <input name="nitype" type="checkbox" ' . $checkf . '  value="1"  /> Internal  Message Only
           
			<div class="description"></div>
        </div>
        </fieldset>		
	<div class="clear"  style="height:100px;"><input type="submit" name="update" value="Update"></div>
        
		</form>
		
		<script>
		
		
setTimeout(markit,2000);

function markit(){
	
	var chk=' . $question_privacy . ';
	
var elt=$$(\'.qrset\');

elt.each(function(el){var alt=el.get(\'value\'); if(chk==alt){

el.set(\'checked\',true);
}
});
}
		</script>
		
		
		
		';


    return $strReturn;
}

function event_photo() {
    global $objSmarty, $config;
    $return = array();
    $filename = $_FILES['image']['name']; // file up starts
    $tmp_image = $_FILES['image']['tmp_name'];
    if ($filename != '') {
        include drupal_get_path('module', 'profile') . "/img_resize.php";
        $ext = strtolower(substr($filename, strpos($filename, '.'), strlen($filename) - 1));

        if ($ext == '.jpg' || $ext == '.gif' || $ext == '.jpeg') {
            $imagefun = new SimpleImage();

            $image = time() . $filename;

            $path = drupal_get_path('module', 'profile') . "/snap/";
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

////following users/////////////////////////


function followinglist($uids) {

    global $gSitePath, $user, $gDocPath, $base_root;


    $sel_list = "select * from follower  where uid='" . $uids . "'  and follower_status='1' limit 0,5";
    $rs_foll_list = db_query($sel_list);
    $numfolls = db_result(db_query("SELECT COUNT(*)  from follower  where uid='" . $uids . "'  and follower_status='1'  "));
    $following = array();

    while ($following_list = db_fetch_object($rs_foll_list)) {

        if ($uids == $user->uid) {
            $flinks = '<a onclick="deletefollowing(' . $following_list->id . ')" style="color:#F37321;" >Unfollow</a>';
        }
        //	 $sel_userm="select * from users  where uid='".$following_list->follower_id."' ";
        $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $following_list->follower_id . "'";
        $rs_userm = db_query($sel_userm);
        $user_namelist = db_fetch_object($rs_userm);

        $bubble = load_bubble($following_list->follower_id);

        //$following[] = '<div  id="show-' . $following_list->id . '"><a rel=\'' . $bubble . '\' href="' . $gSitePath . 'profile/' . $user_namelist->name . '">' . UserPicture_small($following_list->follower_id) . $user_namelist->real_name . '  </a>' . $flinks . '</div>';
        $following[] = '<li  id="show-' . $following_list->id . '"><a rel=\'' . $bubble . '\' href="' . $gSitePath . 'profile/' . $user_namelist->name . '">'.UserPicture_small($following_list->follower_id).'</a></li>';

        }
    if ($numfolls > 5) {
        $following[] .= '<a style="color:#F37321;" onclick="loadfollowing(\'' . $gSitePath . 'following/' . $uids . '\',\'Following\');">More</a>';
    }
    if ($numfolls == 0) {
        $following[] .= '<span style="padding-left:17px;">Please Follow People</span>';
    }
    return $following;
}

function save_follow_profile() {

    if (isset($_REQUEST['action'])) {
        $query = 'DELETE FROM follower WHERE id = ' . (int) $_REQUEST['action'];
        $result = db_query($query);
        echo '<div id="' . $_REQUEST['ids'] . '" >Removed</div>';
    }
}

//////////follower //////////////////////////


function followerlist($umid) {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

    $sel_listf = "select * from follower  where follower_id='" . $umid . "' AND uid>0  limit 0,5  ";
    $rs_followerf = db_query($sel_listf);

    $numfoll = db_result(db_query("SELECT COUNT(*)  from follower  where follower_id='" . $umid . "' AND uid>0  "));

    $followeru = array();
    while ($follower_resultfuser = db_fetch_object($rs_followerf)) {

        // $sel_ulist="select * from users  where uid='".$follower_resultfuser->uid."' ";
        $sel_ulist = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $follower_resultfuser->uid . "'";
        $rs_umlog = db_query($sel_ulist);
        $user_namelistf = db_fetch_object($rs_umlog);


        $user_namelistf->name;

        if ($umid == $user->uid) {
            $flink1 = '<a style="color:#F37321;" onclick="blockandunblock(' . $follower_resultfuser->id . ',' . $follower_resultfuser->uid . ',1,0)" >UnBlock</a>';
            $flink2 = '<a style="color:#F37321;" onclick="blockandunblock(' . $follower_resultfuser->id . ',' . $follower_resultfuser->uid . ',0,0)" >Block</a>';
        }

        $bubble = load_bubble($user_namelistf->uid);
        if ($follower_resultfuser->follower_status == 0) {
           // $followeru[] = '<div  id="list-' . $follower_resultfuser->id . '"><a href="' . $gSitePath . 'profile/' . $user_namelistf->name . '" rel=\'' . $bubble . '\'>' . UserPicture_small($follower_resultfuser->uid) . $user_namelistf->name . ' </a> ' . $flink1 . '</div>';
            $followeru[] = '<li  id="list-' . $follower_resultfuser->id . '"><a href="' . $gSitePath . 'profile/' . $user_namelistf->name . '" rel=\'' . $bubble . '\'>'. UserPicture_small($follower_resultfuser->uid).'</a></li>';

        } else {
          //  $followeru[] = '<div  id="list-' . $follower_resultfuser->id . '"><a href="' . $gSitePath . 'profile/' . $user_namelistf->name . '" rel=\'' . $bubble . '\'>' . UserPicture_small($follower_resultfuser->uid) . $user_namelistf->name . ' </a> ' . $flink2 . '</div>';
        
             $followeru[] = '<li  id="list-' . $follower_resultfuser->id . '"><a href="' . $gSitePath . 'profile/' . $user_namelistf->name . '" rel=\'' . $bubble . '\'>'.UserPicture_small($follower_resultfuser->uid).'</a></li>';
        }

        //$followeru[]='<a href="'.$gSitePath.'profile/'.$user_namelistf->name.'">'.$user_namelistf->name.' </a><br>';
    }

    if ($numfoll > 5) {
        $followeru[] .= '<a style="color:#F37321;" href="javascript:void(0);" onclick="loadfollower(\'' . $gSitePath . 'follower/' . $umid . '\',\'Follower\');">More</a>';
    }
    if ($numfoll == 0) {
        $followeru[] .= '<span style="padding-left:17px;">No Followers Yet</span>';
    }


    return $followeru;
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
            $result = db_query("UPDATE {privacy_settings} set real_name='$real_name',gender='$gender',image='$image',bio=' $bio',zip='$zip',country='$country',religion='$religion',ethnic='$ethnic',slant='$slant',facebook='$facebook',twitter='$twitter',email='$email',
			followers='$followers',following='$following',medal='$medal',questions='$questions',answers='$answers'  where uid=$user->uid ");
        } else {
            $result = db_query("INSERT INTO {privacy_settings} set uid='$user->uid',real_name='$real_name',gender='$gender',image='$image',bio=' $bio',zip='$zip',country='$country',religion='$religion',ethnic='$ethnic',slant='$slant',facebook='$facebook',twitter='$twitter',email='$email',
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

function activities($uid = '') {
    drupal_set_title('Recent Activities');
    global $gSitePath, $user, $gDocPath, $base_root;
    //$uid = $user->uid;


    $strReturn = '<div class="history-tab">';
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
                    drupal_set_message($message = 'Oops, No Recent Activities !', $type = 'error');
                    break;
            }//switch ends
        }//foreach ends
    } else {

        drupal_set_message($message = 'Oops, No Recent Activities !', $type = 'error');
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
            $cnt = db_result(db_query("select count(*) from {question} as q join {users} as u on q.uid=u.uid where q.status='1' and q.country REGEXP '[^0-9]'"));

           // $geomap_qry = "select count(*) as count, country from question where country REGEXP '[^0-9]' group by country";
            $geomap_qry = "select count(*) as count, q.country from {question} as q join {users} as u on q.uid=u.uid where q.status='1' and q.country REGEXP '[^0-9]' group by country";
            $geomap_exec = ExecuteQuery($geomap_qry, "select");

            $first = 0;
            foreach ($geomap_exec as $geomapeach) {
               
                $asscountry .= " data.setValue(" . $first . ", 0,'" . $geomapeach['country'] . "');" . ' data.setValue(' . $first . ', 1,' . $geomapeach['count'] . ');';
                 $first = $first + 1;
            }
            break;
        case 'google/map/answer':
            $variable = "Votes";
            $geomap_qry = "select count(*)as count,q.country from possible_answer_vote as a join question as q on q.qid=a.qid where q.status='1' and q.country REGEXP '[^0-9]' group by q.country";
            $geomap_exec = ExecuteQuery($geomap_qry, "select");
 $cnt = db_result(db_query("select count(*) from {possible_answer_vote} as a join {question} as q on q.qid=a.qid where q.status='1' and q.country REGEXP '[^0-9]'"));

            $first = 0;
            foreach ($geomap_exec as $geomapeach) {
                
                $asscountry .= " data.setValue(" . $first . ", 0,'" . $geomapeach['country'] . "');" . ' data.setValue(' . $first . ', 1,' . $geomapeach['count'] . ');';

             
                $first = $first + 1;
            }
            break;
    }
if($_REQUEST['width']=='155')
    $vars=' geomap.draw(data,{width:155,height:100,showLegend:false});';
   else
      $vars=' geomap.draw(data,{width:640,height:350,showLegend:true});';

    echo $script .= "<script type='text/javascript' src='http://www.google.com/jsapi'></script>";
    echo $script.="<script type='text/javascript'>
    google.load('visualization', '1', {packages: ['geomap']});

    function drawVisualization() {
      var data = new google.visualization.DataTable();
      data.addRows(50);
      data.addColumn('string', 'Country');
      data.addColumn('number', '".$variable."');" . $asscountry . "
      var geomap = new google.visualization.GeoMap(
          document.getElementById('visualization'));
     ".$vars."
    }
    google.setOnLoadCallback(drawVisualization);
  function loadtab(href,title){
    	  var options = 'sameBox:true width:650px height:370px caption:'+title;

 parent.fb.start(href, options);
}
  </script>";

    echo "<div id=visualization style='cursor:pointer;' onclick=\"return loadtab('".url($_GET['q'], array('absolute' => true))."','`Facts And Figures : ".$variable." : ".$cnt."  `')\"></div>";
}


function amber_tour()
{
    
    global $gSitePath, $user, $gDocPath, $base_root;

     $page = substr($_REQUEST['q'],strrpos($_REQUEST['q'],'/'));
    $page =  ltrim($page,'/');

    switch($page)
    {
        case home:
           $output='<img width="650" height="600" src="' . $gSitePath . path_to_theme() . '/images/tour/home.jpg"/>';
         break;

     case question:
           $output='<img width="650" height="600" src="' . $gSitePath . path_to_theme() . '/images/tour/addquestion.jpg"/>';
         break;

      case donate:
           $output='<img width="650" height="600" src="' . $gSitePath . path_to_theme() . '/images/tour/donate.jpg"/>';
         break;



    }

return $output;
}
