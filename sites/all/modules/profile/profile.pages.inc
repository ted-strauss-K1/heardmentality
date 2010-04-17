<?php
// tree menu listing
function profile_view() {
    global $gSitePath,$user,$gDocPath,$base_root;
	  $profile_name = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
	  
	  $getuser=user_load(array('name' => $profile_name));
	 $uid=$getuser->uid;
	if($uid==''){
	 $uid=$user->uid;
	}
	$image='noimage.jpg';
	$bio='';
	$real_name='';
	$gender='';
	$optionlist='';
	$image='noimage.jpg';
	$zip='';
	$country='';
	$slant='';
	$religion='';
	$ethnic='';
	$facebook='';
	$twitter='';
	$inc_list='';
	$ins_ans='';
	$inc_qns='';
	$qns_list='';
	$qns_list='';
	$upcount = null;$downcount =null;
    $get_cn = db_query("select * from {user_profile} where uid='$uid'");
    $result = db_fetch_array($get_cn);

	$vot_counts= checkUpAndDownVotes( $uid);
    $userPoints = checkUserPoints($user->uid);
	$upcount = $vot_counts['upcount'];
	$downcount = $vot_counts['downcount'];
	if(is_array($result))
    extract($result);
	$userSettings = checkPrivacySettings($uid);
	$is_follow_follower = checkFollowStatus($user->uid, $uid);
    drupal_add_css(drupal_get_path('module', 'profile').'/styles/profile.css');
    $get_cn = db_query("select * from {user_profile} where uid='$uid'");
    $result = db_fetch_array($get_cn);
	$real_name1 = NULL ; $PROFILE_IMAGE= NULL;    $bio1 =  NULL; $zip1= null;
	$country1 = NULL; $religion1 = NULL; $img_path1 =NULL; $gender_name1 = NULL; $facebook1 = NULL; $twitter1 =NULL;
	$medal = NULL;$questions   = NULL;$ansers = NULL;$updownvote_display = NULL;$dob1 = NULL;
	$answer1= NULL;	$question1= NULL;
	if(is_array($result))
    extract($result);

	 $gender_name = isset($gender) && ($gender == 1)? 'Male': 'Female';
     //Checking settings and displaying the field
 	if( ($userSettings['real_name'] == 1) || ($userSettings['real_name'] == 3  && $user->uid !=0 ) || ($user->uid == $uid) || ($user->uid == 1)
	   || ($userSettings['real_name'] == 2  && $is_follow_follower == TRUE  ) ){
      $real_name1 = $real_name;
	}
	if( ($userSettings['bio'] == 1) || ($userSettings['bio'] == 3  && $user->uid !=0 )  || ($user->uid == $uid) || ($user->uid == 1) 
	   || ($userSettings['bio'] == 2  && $is_follow_follower == TRUE  ) 	){
       $bio1 = $bio;
	}
	if( ($userSettings['country'] == 1) || ($userSettings['country'] == 3  && $user->uid !=0 ) || ($user->uid == $uid)  || ($user->uid == 1) 
	   || ($userSettings['country'] == 2  && $is_follow_follower == TRUE  ) ) {
       $country1 = $country;
	}
	if( ($userSettings['religion'] == 1) || ($userSettings['religion'] == 3  && $user->uid !=0 ) || ($user->uid == $uid) || ($user->uid == 1) 
	   || ($userSettings['religion'] == 2  && $is_follow_follower == TRUE  ) ) {
       $religion1 = $religion;
	}
	if( ($userSettings['image'] == 1) || ($userSettings['image'] == 3  && $user->uid !=0 ) || ($user->uid == $uid) || ($user->uid == 1) 
	   || ($userSettings['image'] == 2  && $is_follow_follower == TRUE  ) ){
	 $img_path1=  $gSitePath.drupal_get_path('module', 'profile').'/snap/'.$image;
	 $PROFILE_IMAGE= '<img src="'.$img_path1.'" align="absmiddle" alt="Profile image" >';
	}
	if( ($userSettings['zip'] == 1) || ($userSettings['zip'] == 3  && $user->uid !=0 )|| ($user->uid == $uid) || ($user->uid == 1) 
	|| ($userSettings['zip'] == 2  && $is_follow_follower == TRUE  )	
	){
       $zip1 = $zip;
	}
if( ($userSettings['dob'] == 1) || ($userSettings['dob'] == 3  && $user->uid !=0 )|| ($user->uid == $uid) || ($user->uid == 1) 
	|| ($userSettings['dob'] == 2  && $is_follow_follower == TRUE  )	
	){
       $dob1 = $dob;
	}


   if( ($userSettings['gender'] == 1) || ($userSettings['gender'] == 3  && $user->uid !=0 )|| ($user->uid == $uid) || ($user->uid == 1) 
	|| ($userSettings['gender'] == 2  && $is_follow_follower == TRUE  )   ){
       $gender_name1  = $gender_name ;
	}
	if( ($userSettings['facebook'] == 1) || ($userSettings['facebook'] == 3  && $user->uid !=0 ) || ($user->uid == $uid) || ($user->uid == 1)
	|| ($userSettings['facebook'] == 2  && $is_follow_follower == TRUE  )	){
       $facebook1  =		'<img src="'.$gSitePath.drupal_get_path('module', 'profile').'/images/facebook.png" align="absmiddle" alt="Facebook" >&nbsp; @'.$facebook;
	}
	if( ($userSettings['twitter'] == 1) || ($userSettings['twitter'] == 3  && $user->uid !=0 ) || ($user->uid == $uid) || ($user->uid == 1)
	|| ($userSettings['twitter'] == 2  && $is_follow_follower == TRUE  )	){
       $twitter1  =   '<img src="'.$gSitePath.drupal_get_path('module', 'profile').'/images/twitter.png" align="absmiddle" alt="Twitter" >&nbsp; @'.$twitter;
	}
	//answers posted
	$get_ans= db_query("select q.* from {possible_answer_vote} as a join {question} as q on a.qid=q.qid where a.uid='".$uid."'");
  $ins_ans='<ul>';
    while($setans = db_fetch_object($get_ans)){
    	
	$inc_list.="<li><a href='".$gSitePath.$setans->url."'>$setans->question?</a></li>";
		
    }

     $ins_ans.=$inc_list."</ul>";
	
	$ins_ans=(empty($inc_list))?'No Result':$ins_ans;
	//answers ends
	
	//question sposted
	$get_ans= db_query("select q.* from {question} as q where q.uid='".$uid."' ORDER BY q.qid DESC  LIMIT 0,5");
  $ins_qns='<ul>';
    while($setans = db_fetch_object($get_ans)){
    	
	$qns_list.="<li><a href='".$gSitePath.$setans->url."'>$setans->question?</a></li>";
		
    }
   $inc_qns.=$qns_list."</ul>";
   
	$inc_qns=(empty($qns_list))?'No Result':$inc_qns;
	//question ends
	
	//profile badge
	$arr = updateProfileBadge($uid);
	$pat = $gSitePath.drupal_get_path('module', 'profile');
	$post_count = isset($arr['post_count'])?$arr['post_count']:'';
		if( $arr['badge_type_id'] == 1){
					$li="Brown";
					$li_img_source = $pat."/images/brown.jpg";
	    }elseif($arr['badge_type_id']== 2){
							$li="Silver";
				    $li_img_source = $pat."/images/silver.jpg";
		}elseif($arr['badge_type_id'] == 3){
			$li="Gold";
			$li_img_source = $pat."/images/gold.jpg";
	   }

	if( ($userSettings['medal'] == 1) || ($userSettings['medal'] == 3  && $user->uid !=0 ) || ($user->uid == $uid) || ($user->uid == 1) 
		|| ($userSettings['medal'] == 2  && $is_follow_follower == TRUE  )	) {
		  $medal = 	'<p>
			<span><img title="'.$li .'"  src="'.$li_img_source .'" >
			</span>'.$post_count.'
			</p>';
		}

	if( ($userSettings['answers'] == 1) || ($userSettings['answers'] == 3  && $user->uid !=0 ) || ($user->uid == $uid) || ($user->uid == 1)
		|| ($userSettings['answers'] == 2  && $is_follow_follower == TRUE  )	){
		  $answer1 =  	'<div  class="lft">
				<p><b>Answers</b></p>
				'.$ins_ans.'
				</div>';
	}
	if( ($userSettings['questions'] == 1) || ($userSettings['questions'] == 3  && $user->uid !=0 ) || ($user->uid == $uid) || ($user->uid == 1) 
			|| ($userSettings['questions'] == 2  && $is_follow_follower == TRUE  )) {
		  $question1 =  	'<div class="rht">
				<p><b>Questions Posted</b></p>
				'.$inc_qns.'
				</div>';
	}

	if((isset($userPoints) &&   $userPoints > 999)|| ($user->uid == $uid) || ($user->uid == 1) || ($userSettings['vote_graph'] == 1) || ($userSettings['vote_graph'] == 3  && $user->uid !=0 ))  			
	{
	  $updownvote_display ='<p><b>Votes</b></p>
				<table>
					<tbody>
					<tr>
					<td style="width: 80px;">
					<div class="vote">
					<img width="40" height="25" alt="up" style="cursor: default;" src="'.$gSitePath.drupal_get_path('module', 'profile').'/images/vote-arrow-up-on.png"   http://sstatic.net/so/img/vote-arrow-up-on.png"/>
					<span class="vote-count-post" title="total number of up votes this user has given">'.$downcount.'</span>
					<img width="40" height="25" alt="down" style="cursor: default;" src="http://sstatic.net/so/img/vote-arrow-down.png"/>
					</div>
					</td>
					<td style="width: 80px;">
					<div class="vote">
					<img width="40" height="25" alt="up" style="cursor: default;" src="http://sstatic.net/so/img/vote-arrow-up.png"/>
					<span class="vote-count-post" title="total number of down votes this user has given">'.$upcount.'</span>
					<img width="40" height="25" alt="down" style="cursor: default;" src="http://sstatic.net/so/img/vote-arrow-down-on.png"/>
					</div>
					</td>
					</tr>
					</tbody>
					</table>';
	}


    $strReturn = '<div class="main">
			
			<div class="lft">
			
			<div class="clear">
			<div class="img">'.$PROFILE_IMAGE.$medal.'
			</div>
			<div class="info">
					'.$getuser->name.'<br/>
					'.$real_name1.'<br/>
					'.$dob1.'<br/>	
					'.$gender_name1.'<br/>	
					'.$religion1.'<br/>
					'.$country1.'<br/>
					'.$zip1.'<br/>	
			</div>
			</div>	
			<div class="clear">&nbsp; </div>	<div class="clear">&nbsp; </div>
<hr align="center" size="1"  style="width:96%"  noshade="noshade" />
				<div class="lft bio">
					
					'.$bio1.'
				</div>
				<div class="rht">
					<a href="'.$facebook.'" target="blank">'.$facebook1.'</a><br/>
					<a href="'.$twitter.'" target="blank">'.$twitter1.'</a>
				</div>
				
				
				
			</div>
			
		<div class="rht">
		
				<div class="follow">';
						
					
		if( ($userSettings['following'] == 1) || ($userSettings['following'] == 3  && $user->uid !=0 ) || ($user->uid == $uid)|| ($user->uid == 1) 
				|| ($userSettings['following'] == 2  && $is_follow_follower == TRUE  ) ) {
		 $strReturn.='<p><b>Following</b></p><div id="showid"> </div>';
				$newlist=followinglist($uid);
				for($i=0; $i<count($newlist); $i++)
				{
				$strReturn.=''.$newlist[$i].'';
				
				}
		}	
				$strReturn.='</div>
				<div class="follower">
				';
				
		if( ($userSettings['followers'] == 1) || ($userSettings['followers'] == 3  && $user->uid !=0 ) || ($user->uid == $uid) || ($user->uid == 1) 
				|| ($userSettings['followers'] == 2  && $is_follow_follower == TRUE  )){
			
			 $strReturn.='<p><b>Followers</b></p>';
				$newlist2=followerlist($uid);
				for($k=0; $k<count($newlist2); $k++)
				{
				$strReturn.=''.$newlist2[$k].'';
				
				}
		}	
				$strReturn.='</div>
				
				
				
			</div>
			
			<div class="clear">'. $answer1.	$question1.'
			</div>'. $updownvote_display.'
			
			
		</div>
	
	';

    
    return $strReturn;


}


// Edit Profile
function profile_edit() {
    global $gSitePath,$user,$gDocPath,$base_root;
	
    //print_r($_REQUEST);
	 $uid=$user->uid;
	$bio='';
	$real_name='';
	$gender='';
	$optionlist='';
	$image='noimage.jpg';
	$zip='';
	$country='';
	$slant='';
	$religion='';
	$ethnic='';
	$facebook='';
	$twitter='';
	$check1='';
	$check2='';
    $question_privacy='4';
	$dob='';
	
    if ($_REQUEST['update'] == 'Update') {
        extract($_REQUEST);
        if ($rname == '') {
            drupal_set_message($message = 'Real Name should not be empty!', $type = 'error');
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
            
            $result = db_query("UPDATE {user_profile} set uid='$user->uid',real_name='$rname',gender='$gender',image='$insimage',bio=' $bio',zip='$zip',country='$country',religion='$religion',ethnic='$ethnic',dob='$dob',slant='$slant',facebook='$facebook',twitter='$twitter',question_privacy='$qrset' where uid='$user->uid' ");
        
        } else {
            $result = db_query("INSERT INTO {user_profile} set uid='$user->uid',real_name='$rname',gender='$gender',image='$insimage',bio=' $bio',zip='$zip',country='$country',religion='$religion',ethnic='$ethnic',dob='$dob',slant='$slant',facebook='$facebook',twitter='$twitter',question_privacy='$qrset'");
        }
        if($result){
        	$sucflag='';
        	$sucflag=1;
        drupal_set_message($message = 'Profile Updated Successfully!', $type = 'success');
		
		}
	if(!empty($pass1)){
    	
	if($pass1==$pass2){
		
  $result = db_query("UPDATE {users} set pass='".md5($pass1)."' where uid='$user->uid' ");		
		  drupal_set_message($message = 'Password Updated Successfully!', $type = 'success');
		
	}else{
		
		 drupal_set_message($message = 'Password should be same to chnage!', $type = 'error');
	}
	}	else{
		if($sucflag){
		drupal_goto('profile/');}
	}
	
	
    }

    $get_cn = db_query("select * from {user_profile} where uid='$user->uid'");
    $result = db_fetch_array($get_cn);
    extract($result);
    
    drupal_add_js(drupal_get_path('module', 'profile').'/js/en.js');
    drupal_add_js(drupal_get_path('module', 'profile').'/js/formcheck.js');
    drupal_add_css(drupal_get_path('module', 'profile').'/theme/classic/formcheck.css');
    $result = geonames_query('countryinfo');
    foreach ($result->results as $countries) {
    	$select='';
    	if($country== $countries['countrycode'])
		{
			$select="SELECTED='SELECTED'";
		}
		
        $optionlist .= sprintf('<option %s value="%s">%s</option>',$select, $countries['countrycode'], $countries['countryname']);
    }
	
	if($gender==1){
		$check1="checked='checked'";
	}elseif($gender==2){
			$check2="checked='checked'";
		
	}
    
    $strReturn = '	
		<script src="'.$gSitePath.'sites/all/modules/profile/js/profile.js" type="text/javascript"></script>
		<form name="profile" id="profile"  onsubmit="return validate_profile();"  method="post" enctype="multipart/form-data">
		<fieldset>
        	<legend><b><i>Account information</i></b></legend>
				<div class="form-item" id="edit-name-wrapper"> 
					<label for="edit-name">Username: <span class="form-required" title="This field is required.">*</span></label> <input maxlength="60" name="name" id="edit-name" disabled="disabled" size="60" value="'.$user->name.'" class="form-text required" type="text">
                     
					<div class="description">Spaces are allowed; punctuation is not allowed except for periods, hyphens, and underscores.</div>
               </div>
			<div class="form-item" id="edit-mail-wrapper"> 
            	<label for="edit-mail">E-mail address: <span class="form-required" title="This field is required.">*</span></label> <input maxlength="64" name="mail" id="edit-mail" size="60"  disabled="disabled"  value="'.$user->mail.'"  class="form-text required" type="text"> 
                <div class="description">A valid e-mail address. All e-mails from the system will be sent to this address. The e-mail address is not made public and will only be used if you wish to receive a new password or wish to receive certain news or notifications by e-mail.</div>
           </div>
		<div class="form-item" id="edit-pass-wrapper"> 
        	<div class="form-item" id="edit-pass-pass1-wrapper"> 
            	<label for="edit-pass-pass1">Password: </label> <input name="pass1" id="edit-pass-pass1" maxlength="128" size="25" class="form-text password-field validate[\'required\']" type="password">
            </div>
			<div class="form-item" id="edit-pass-pass2-wrapper"> <label for="edit-pass-pass2">Confirm password: </label> <input name="pass2" id="edit-pass-pass2" maxlength="128" size="25" class="form-text password-confirm validate[\'required\',\'confirm[password]\']" type="password"></div> 
            <div class="description">To change the current user password, enter the new password in both fields.</div>
       </div>
	<!--   <div class="form-item"> <label>Status: </label> 
             <div class="form-radios">
                 <div class="form-item" id="edit-status-0-wrapper"> <label class="option" for="edit-status-0"><input id="edit-status-0" name="status" value="0"  class="form-radio validate[\'required\']" type="radio"> Blocked</label></div>
		         <div class="form-item" id="edit-status-1-wrapper"> <label class="option" for="edit-status-1"><input id="edit-status-1" name="status" value="1"  class="form-radio" type="radio"> Active</label></div>
             </div> 
		</div> -->
     </fieldset>
   
		<fieldset>
			<legend> <b><i>Profile Bio</i></b> </legend>
				<div class="form-item" id="edit-name-wrapper"> 
					<label for="edit-rname">Real Name: <span class="form-required" title="This field is required.">*</span></label> <input maxlength="60" name="rname" id="edit-rname" size="40"  value="'.$real_name.'"  class="form-text required"  type="text"> 
					<div class="description">Spaces are allowed; punctuation is not allowed except for periods, hyphens, and underscores.</div>
                </div>
				<div class="form-item" id="edit-image-wrapper"> <label for="edit-image">Image : </label> <input type="file" name="image" id="image" /> <img src="'.$gSitePath.drupal_get_path('module', 'profile').'/snap/'.$image.'" align="absmiddle" alt="Profile Image" >
				<input type="hidden" name="oldimg" value="'.$image.'"/>
					<div class="description">accept only jpeg,jpg,gif format max. 1 mb size</div>
                </div>
				<div class="form-item">
				<label for="edit-dob">DOB : </label> <input name="dob"  value="'.$dob.'"  id="edit-dob" maxlength="128" size="25" class="form-text" type="text">
				<div class="description">DD/MM/YYYY</div>
				</div>

				<div class="form-item" id="edit-bio-wrapper"> <label for="edit-bio">Bio : </label> 
                	<textarea name="bio" id="edit-bio" class="form-text" rows="7" cols="70">'.$bio.'</textarea>
        			<div class="description">Describe about yourself to others.</div>
        		</div>
				<div class="form-item"> <label>Gender : </label> 
                	<div class="form-radios">
                    	<div class="form-item" id="edit-gender"> <label class="option" for="edit-gender-0"><input id="edit-gender-0" name="gender" value="1" class="form-radio" '.$check1.' type="radio"> Male</label></div>
						<div class="form-item" id="edit-gender-1-wrapper"><label class="option" for="edit-gender-1"><input id="edit-gender-1" name="gender" value="2" class="form-radio" '.$check2.' type="radio"> Female</label> </div>
                   </div>
				</div> 
			        		<div class="form-item" id="edit-country-wrapper"> <label for="edit-country">Country : </label><select name="country" style="width: 125px;" tabindex="16" id="edit-country">'.$optionlist.'</select> <div class="description"></div></div>	
        		<div class="form-item" id="edit-zip-wrapper"> <label for="edit-zip">Zip/Postal code : </label> <input name="zip"  value="'.$zip.'"  id="edit-zip" maxlength="128" size="25" class="form-text" type="text"> </div>
        		<div class="form-item" id="edit-religion-wrapper"> <label for="edit-religion">Religion : </label> <input name="religion"  value="'.$religion.'"  id="edit-religion" maxlength="128" size="25" class="form-text" type="text"> <div class="description"></div></div>
        		<div class="form-item" id="edit-ethnic-wrapper"> <label for="edit-ethnic">Ethnicity : </label> <input name="ethnic"  value="'.$ethnic.'"  id="edit-ethnic" maxlength="128" size="25" class="form-text" type="text"> <div class="description"></div></div>
          		<div class="form-item" id="edit-slant-wrapper"> <label for="edit-slant">Slant : </label> <input name="slant" id="edit-slant"  value="'.$slant.'"  maxlength="128" size="25" class="form-text" type="text"> <div class="description"></div></div>
         
        </fieldset>
	  <fieldset>
		<legend><b><i>Links</i></b> </legend>
		<div class="form-item" id="edit-name-wrapper"> 
			<label for="edit-facebook">Facebook: </label> <input maxlength="60" name="facebook" id="edit-facebook"  value="'.$facebook.'"  size="60"  class="form-text required" type="text"> 
			<div class="description"></div>
        </div>
		<div class="form-item" id="edit-twitter-wrapper"> <label for="edit-twitter">Twitter :</label> <input maxlength="64" value="'.$twitter.'"  name="twitter" id="edit-twitter" size="60" class="form-text required" type="text"> <div class="description"></div></div>
	
         
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
        </fieldset>		
	<div class="clear"  style="height:100px;"><input type="submit" name="update" value="Update"></div>
        
		</form>
		
		<script>
		
		
setTimeout(markit,2000);

function markit(){
	
	var chk='.$question_privacy.';
	
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
    global $objSmarty,$config;
    $return = array();
    $filename = $_FILES['image']['name'];// file up starts
    $tmp_image = $_FILES['image']['tmp_name'];
    if ($filename != '') {
        include drupal_get_path('module', 'profile')."/img_resize.php";
        $ext = strtolower(substr($filename, strpos($filename, '.'), strlen($filename) - 1));
        
        if ($ext == '.jpg' || $ext == '.gif' || $ext == '.jpeg') {
            $imagefun = new SimpleImage();
            
            $image = time().$filename;
            
            $path = drupal_get_path('module', 'profile')."/snap/";
            copy($tmp_image, $path.$image);
            //img resize
            $sz = getimagesize($path.$image);
            
            $x = $sz[0]; // org image width
            $y = $sz[1]; // org image height
            if ($x > 100) {
                $imagefun->load($path.$image);
                
                $imagefun->resizeToWidth(100);
                
                $imagefun->save($path.$image);
            
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


function followinglist($uids)
{

 global $gSitePath,$user,$gDocPath,$base_root;
 
 	print'<script type="text/javascript">
		function deletefollowing(fid){
		var abc="show-"+fid;
									var url = "'.$gSitePath.'profile/deletefollow";
									var req = new Request({    
											method: \'get\'
											,url: url
											,data: { \'action\':fid,\'ids\':abc},
											onRequest: function() { },
											onComplete: function(response) {
													 $(abc).set(\'html\', response);
											}
									}).send();
						
							
                           
							}	
	
	</script>';
 $sel_list="select * from follower  where uid='".$uids."'  and follower_status='1' limit 0,5";
	$rs_foll_list=db_query($sel_list);
	$numfolls= db_result(db_query("SELECT COUNT(*)  from follower  where uid='".$uids."'  and follower_status='1'  "));
	$following=array();
	 
	while($following_list=db_fetch_object($rs_foll_list))
	{
	
	if($uids==$user->uid)
	  {
	  $flinks='<a onclick="deletefollowing('.$following_list->id.')" style="color:#F37321;" >Unfollow</a>';
	
	  
	  }
//	 $sel_userm="select * from users  where uid='".$following_list->follower_id."' ";
	  $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='".$following_list->follower_id."'";
		$rs_userm=db_query($sel_userm);
	$user_namelist=db_fetch_object($rs_userm);
	 if(isset($user_namelist->image) && !empty($user_namelist->image)){
	  $imgsrc = $user_namelist->image;
	 }else{
	  $imgsrc = 'noimage.jpg';
	 } 
	 $img_path=  $gSitePath.drupal_get_path('module', 'profile').'/snap/'.$imgsrc;
	 $PROFILE_IMAGE= '<img src="'.$img_path.'" align="absmiddle" height="27" width="27" alt="Profile image" >';

	$following[]='<div  id="show-'.$following_list->id.'"><a href="'.$gSitePath.'profile/'.$user_namelist->name.'">'.$PROFILE_IMAGE.$user_namelist->name.'  </a>'.$flinks.'</div>' ;
	
	}
	if($numfolls>5)
	{
	$following[].='<a style="color:#F37321;
text-decoration:none;" onclick="loadfollowing(\''.$gSitePath.'following/'.$uids.'\',\'Following\');">More</a>';
	
	}
	if($numfolls==0)
	{
	$following[].='No Records';
	}	
return $following;

}

function save_follow_profile()
{

if(isset($_GET['action']))
{
 $query = 'DELETE FROM follower WHERE id = '.(int)$_GET['action'];
$result = db_query($query);
echo '<div id="'.$_REQUEST['ids'].'" ></div>';
}

}


//////////follower //////////////////////////


function followerlist($umid)
{

	global $gSitePath,$user, $gDocPath,$base_root,$base_path;
	
	print'<script type="text/javascript">
		function blockandunblock(fid,divid,blk){
			var abcm="list-"+fid;
			
			
									var url = "'.$gSitePath.'profile/savefollowerlink";
									var req = new Request({    
											method: \'get\'
											,url: url
											,data: { \'action\':fid,\'ids\':abcm,\'blk\':blk,\'usid\':divid},
											onRequest: function() { },
											onComplete: function(response) {
													 $(abcm).set(\'html\', response);
											}
									}).send();
						
							
                           
							}	
	
	</script>
	';
	

	
	  $sel_listf="select * from follower  where follower_id='".$umid."'   limit 0,5  ";
	$rs_followerf=db_query($sel_listf);
	
	 $numfoll= db_result(db_query("SELECT COUNT(*)  from follower  where follower_id='".$umid."'   "));
	
	 $followeru=array();
	while($follower_resultfuser=db_fetch_object($rs_followerf))
	{
	
	  // $sel_ulist="select * from users  where uid='".$follower_resultfuser->uid."' ";
	   $sel_ulist = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='".$follower_resultfuser->uid."'";
	$rs_umlog=db_query($sel_ulist);
	$user_namelistf=db_fetch_object($rs_umlog);
	if(isset($user_namelistf->image) && !empty($user_namelistf->image)){
	  $imgsrc = $user_namelist->image;
	 }else{
	  $imgsrc = 'noimage.jpg';
	 } 
	 $img_path=  $gSitePath.drupal_get_path('module', 'profile').'/snap/'.$imgsrc;
	 $PROFILE_IMAGE= '<img src="'.$img_path.'" align="absmiddle" height="27" width="27" alt="Profile image" >';

	  $user_namelistf->name;
	  if($umid==$user->uid)
	  {
	  $flink1='<a style="color:#F37321;" onclick="blockandunblock('.$follower_resultfuser->id.','.$follower_resultfuser->uid.',1)" >UnBlock</a>';
	  $flink2='<a style="color:#F37321;" onclick="blockandunblock('.$follower_resultfuser->id.','.$follower_resultfuser->uid.',0)" >Block</a>';
	  
	  }
	if($follower_resultfuser->follower_status==0)
	{
		$followeru[]='<input type="hidden" value="1" name="blk" id="blk"/><div  id="list-'.$follower_resultfuser->id.'"><a href="'.$gSitePath.'profile/'.$user_namelistf->name.'">'. $PROFILE_IMAGE.$user_namelistf->name.' </a> '.$flink1.'</div>';
	} 
	else 
	{
		$followeru[]='<input type="hidden" value="0" name="blk" id="blk"/><div  id="list-'.$follower_resultfuser->id.'"><a href="'.$gSitePath.'profile/'.$user_namelistf->name.'">'. $PROFILE_IMAGE.$user_namelistf->name.' </a> '.$flink1.'</div>';
	
	} 
	
	
	//$followeru[]='<a href="'.$gSitePath.'profile/'.$user_namelistf->name.'">'.$user_namelistf->name.' </a><br>';
	}
	
	if($numfoll>5)
	{
	$followeru[].='<a style="color:#F37321;
text-decoration:none;" onclick="loadfollower(\''.$gSitePath.'follower/'.$umid.'\',\'Follower\');">More</a>';
	}	
	if($numfoll==0)
	{
	$followeru[].='No Records';
	}	
	
			   
				   return $followeru;

}




function save_follower_profile()
{

if(isset($_GET['action']))
{
$del_blog="update  follower  set follower_status='".$_REQUEST['blk']."' where  id='".$_GET['action']."' ";
	$rs_blog_del=db_query($del_blog);
	
	 
	 $sel_userms="select * from users  where uid='".$_GET['usid']."' ";
	$rs_userms=db_query($sel_userms);
	$resulrnames=db_fetch_object($rs_userms);
	if($_REQUEST['blk']==0)
	{
	$blkid='1';
	$valss='UnBlock';
	}
	else
	{
	$valss='Block';
    $blkid='0';
	}
	echo '<div id="'.$_REQUEST['ids'].'" ><a href="'.$gSitePath.'profile/'.$resulrnames->name.'">'.$resulrnames->name.'</a> <a onclick="blockandunblock('.$_GET['action'].','.$_GET['usid'].','.$blkid.')" style="color:#F37321;" >'.$valss.'</a></div>';
	
}

}



function privacy_settings()
{
  global $gSitePath,$user,$gDocPath,$base_root;
  $uid=$user->uid;
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
        if($result){
        drupal_set_message($message = 'Privacy Settings Updated Successfully!', $type = 'success');
		  echo '<script>window.parent.location.href="'.$gSitePath.'profile/";</script>';
		}
    }
		$query = "select * from {privacy_settings} where uid='$user->uid'";
	   $fetch  = ExecuteQuery($query, "select");
	   if(is_array($fetch)){
		$get=extract($fetch);
		}else{
		$get=NULL;
		}
			
 //privacy settings form
$usertypes = userTypes();
$option1 = '<option value=1>'.$usertypes[0].'</option>';
$option2 = '<option value=2>'.$usertypes[1].'</option>';
$option3 = '<option value=3>'.$usertypes[2].'</option>';



  $strReturn = '
  <script type="text/javascript" src="'.$gSitePath.'sites/all/themes/heardmentality/scripts/mootools-1.2-core.js"></script>
	<script type="text/javascript" src="'.$gSitePath.'sites/all/themes/heardmentality/scripts/mootools-1.2-more.js"></script>	
  <link rel="stylesheet" href="'.$gSitePath.'modules/system/system.css" type="text/css" />
	<link rel="stylesheet" href="'.$gSitePath.'sites/all/themes/heardmentality/css/content.css" type="text/css" />
	
		<form name="profile" id="profile" method="post" enctype="multipart/form-data">
		<fieldset>
        	<legend>Privacy Settings</legend>
			<table>
		       <tr><td>Email  </td>
   			        <td></td>
   			        <td><select class="email" name="email">'.$option1.$option2.$option3.'</select>  </td>
			   </tr>
			   <tr><td></td><td></td><td></td></tr>
		       <tr><td>Real Name  </td>
   			       <td></td>
   			       <td><select class="real_name" name="real_name">'.$option1.$option2.$option3.'</select> </td>
				</tr>
			   <tr><td></td><td></td><td></td></tr>
		       <tr><td>Image</td>
   			       <td>	</td>
   			       <td>	<select class="image"  name="image">'.$option1.$option2.$option3.'</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			   <tr><td>Bio</td>
   			       <td>	</td>
   			       <td>	<select class="bio"  name="bio">'.$option1.$option2.$option3.'</select> </td>
		       </tr>
			   <tr><td></td><td></td><td></td></tr>	
			    <tr><td>Gender</td>
   			       <td>	</td>
   			       <td>	<select class="gender"  name="gender">'.$option1.$option2.$option3.'</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			     <tr><td>Zip</td>
   			       <td>	</td>
   			       <td>	<select class="zip"  name="zip">'.$option1.$option2.$option3.'</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			     <tr><td>Country</td>
   			       <td>	</td>
   			       <td>	<select class="country"  name="country">'.$option1.$option2.$option3.'</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			    <tr><td>Religion</td>
   			       <td>	</td>
   			       <td>	<select class="religion"  name="religion">'.$option1.$option2.$option3.'</select> </td>
		       </tr>
			   <tr><td></td><td></td><td></td></tr>
			   <tr><td>Ethnic</td>
   			       <td>	</td>
   			       <td>	<select class="ethnic"  name="ethnic">'.$option1.$option2.$option3.'</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			   <tr><td>Slant</td>
   			       <td>	</td>
   			       <td>	<select class="slant"  name="slant">'.$option1.$option2.$option3.'</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
              <tr><td>Facebook</td>
   			       <td>	</td>
   			       <td>	<select class="facebook"  name="facebook">'.$option1.$option2.$option3.'</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			   <tr><td>Twitter</td>
   			       <td>	</td>
   			       <td>	<select class="twitter"  name="twitter">'.$option1.$option2.$option3.'</select> </td>
		       </tr>
	           <tr><td></td><td></td><td></td></tr>
			   <tr><td>Followers</td>
   			       <td>	</td>
   			       <td>	<select class="followers"  name="followers">'.$option1.$option2.$option3.'</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			  <tr><td>Following</td>
   			       <td>	</td>
   			       <td>	<select class="following"  name="following">'.$option1.$option2.$option3.'</select> </td>
		       </tr>
			  <tr><td></td><td></td><td></td></tr>
		     <tr><td>Medal</td>
   			       <td>	</td>
   			       <td>	<select class="medal"  name="medal">'.$option1.$option2.$option3.'</select> </td>
		       </tr>
		      <tr><td></td><td></td><td></td></tr>
			  <tr><td>Posted Answers </td>
   			       <td>	</td>
   			       <td>	<select class="answers"  name="answers">'.$option1.$option2.$option3.'</select> </td>
		      </tr>
		     <tr><td></td><td></td><td></td></tr>
			  <tr><td>Posted Questions</td>
   			       <td>	</td>
   			       <td>	<select class="questions"  name="questions">'.$option1.$option2.$option3.'</select> </td>
		       </tr>
			</table>
			</fieldset>
			<div class="clear" style="height:100px;" ><input type="submit" name="update" value="Update"></div>
			</form>
			
			<script>
			
			setTimeout(markit,1000);

function markit(){
	
var chk=\''.$fetch[0]['email'].'\';
var elt=$$(\'.email\');
elt.each(function(el){ el.set(\'value\',chk); });

var chk=\''.$fetch[0]['real_name'].'\';
var elt=$$(\'.real_name\');
elt.each(function(el){ el.set(\'value\',chk); });

	
	var chk=\''.$fetch[0]['image'].'\';
var elt=$$(\'.image\');
elt.each(function(el){ el.set(\'value\',chk); });

var chk=\''.$fetch[0]['bio'].'\';
var elt=$$(\'.bio\');
elt.each(function(el){ el.set(\'value\',chk); });

var chk=\''.$fetch[0]['gender'].'\';
var elt=$$(\'.gender\');
elt.each(function(el){ el.set(\'value\',chk); });

var chk=\''.$fetch[0]['zip'].'\';
var elt=$$(\'.zip\');
elt.each(function(el){ el.set(\'value\',chk); });

var chk=\''.$fetch[0]['country'].'\';
var elt=$$(\'.country\');
elt.each(function(el){ el.set(\'value\',chk); });


var chk=\''.$fetch[0]['religion'].'\';
var elt=$$(\'.religion\');
elt.each(function(el){ el.set(\'value\',chk); });

var chk=\''.$fetch[0]['ethnic'].'\';
var elt=$$(\'.ethnic\');
elt.each(function(el){ el.set(\'value\',chk); });

var chk=\''.$fetch[0]['slant'].'\';
var elt=$$(\'.slant\');
elt.each(function(el){ el.set(\'value\',chk); });

var chk=\''.$fetch[0]['facebook'].'\';
var elt=$$(\'.facebook\');
elt.each(function(el){ el.set(\'value\',chk); });


var chk=\''.$fetch[0]['twitter'].'\';
var elt=$$(\'.twitter\');
elt.each(function(el){ el.set(\'value\',chk); });

var chk=\''.$fetch[0]['followers'].'\';
var elt=$$(\'.followers\');
elt.each(function(el){ el.set(\'value\',chk); });

var chk=\''.$fetch[0]['following'].'\';
var elt=$$(\'.following\');
elt.each(function(el){ el.set(\'value\',chk); });

var chk=\''.$fetch[0]['medal'].'\';
var elt=$$(\'.medal\');
elt.each(function(el){ el.set(\'value\',chk); });

var chk=\''.$fetch[0]['answers'].'\';
var elt=$$(\'.answers\');
elt.each(function(el){ el.set(\'value\',chk); });

var chk=\''.$fetch[0]['questions'].'\';
var elt=$$(\'.questions\');
elt.each(function(el){ el.set(\'value\',chk); });

}
			</script>
		';

    
    echo $strReturn;
 
 }











