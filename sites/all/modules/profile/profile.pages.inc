<?php
// tree menu listing
function profile_view() {
    global $gSitePath,$user,$gDocPath,$base_root;
	
	$uid=$user->uid;
	$image='noimage.jpg';
	$zip='';
	$country='';
	$slant='';
	$ethnic='';
	
	
    $get_cn = db_query("select * from {user_profile} where uid='$uid'");
    $result = db_fetch_array($get_cn);
    extract($result);
    drupal_add_css(drupal_get_path('module', 'profile').'/styles/profile.css');
    
    $get_cn = db_query("select * from {user_profile} where uid='$uid'");
    $result = db_fetch_array($get_cn);
    extract($result);
    
	
	//answers posted
	$get_ans= db_query("select q.* from {possible_answer_vote} as a join {question} as q on a.qid=q.qid where a.uid='".$uid."'");
  $inc_ans='<ul>';
    while($setans = db_fetch_object($get_ans)){
    	
	$inc_ans.="<li><a href='".$gSitePath.$setans->url."'>$setans->question?</a></li>";
		
    }
   $ins_ans.="</ul>";
	
	//question sposted
	$get_ans= db_query("select q.* from {question} as q where q.uid='".$uid."' ORDER BY q.qid DESC  LIMIT 0,5");
  $inc_qns='<ul>';
    while($setans = db_fetch_object($get_ans)){
    	
	$inc_qns.="<li><a href='".$gSitePath.$setans->url."'>$setans->question?</a></li>";
		
    }
   $ins_qns.="</ul>";
	
	$arr = updateProfileBadge($uid);
	$pat = $gSitePath.drupal_get_path('module', 'profile');
	$post_count = isset($arr['post_count'])?$arr['post_count']:'';
		if( $arr['badge_type_id'] == 1){
					$li="2";
					$li_img_source = $pat."/images/brown.jpg";
	    }elseif($arr['badge_type_id']== 2){
					$li="14";
				    $li_img_source = $pat."/images/silver.jpg";
		}elseif($arr['badge_type_id'] == 3){
			$li="40";
			$li_img_source = $pat."/images/gold.jpg";
	   }
    $strReturn = '<div class="main">
			
			<div class="lft">
			
			<div class="clear">
			<div class="img"><img src="'.$gSitePath.drupal_get_path('module', 'profile').'/snap/'.$image.'" align="absmiddle" alt="Profile Image" >
			'.$post_count.'
			<p>
			<span><img src="'.$li_img_source .'" >'.$badge_type_id.'
			</span>
			</p>
			</div>
			<div class="info">
					'.$user->name.'<br/>
					'.$real_name.'<br/>
					'.$country.'<br/>
					'.$zip.'<br/>	
			</div>
			</div>	
			<div class="clear">&nbsp; </div>
<hr align="center" size="1"  style="width:96%"  noshade="noshade" />
				<div class="lft">
					
					'.$bio.'
				</div>
				<div class="rht">
					
					<img src="'.$gSitePath.drupal_get_path('module', 'profile').'/images/facebook.png" align="absmiddle" alt="Facebook" >&nbsp; @'.$facebook.'<br/>
										<img src="'.$gSitePath.drupal_get_path('module', 'profile').'/images/twitter.png" align="absmiddle" alt="Twitter" >&nbsp; @'.$twitter.'
				</div>
				
				
				
			</div>
			
			<div class="rht">
				right
				<div class="follow">
					follow
					
				</div>
				<div class="follower">
					follower
					
				</div>
				
				
				
			</div>
			
			<div class="clear">
				
				<div  class="lft">
				<p><b>Answers</b></p>
				'.$inc_ans.'
				</div>
				<div class="rht">
				<p><b>Questions Posted</b></p>
				'.$inc_qns.'
				</div>
			</div>
			
			
		</div>';

    
    return $strReturn;


}


// Edit Profile
function profile_edit() {
    global $gSitePath,$user,$gDocPath,$base_root;
    //print_r($_REQUEST);
    
    if ($_REQUEST['update'] == 'Update') {
        extract($_REQUEST);
        if ($rname == '') {
            drupal_set_message($message = 'Real Name should not be empty!', $type = 'error');
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
            
            $result = db_query("UPDATE {user_profile} set uid='$user->uid',real_name='$rname',gender='$gender',image='$insimage',bio=' $bio',zip='$zip',country='$country',religion='$religion',ethnic='$ethnic',slant='$slant',facebook='$facebook',twitter='$twitter' where uid='$user->uid' ");
        
        } else {
            $result = db_query("INSERT INTO {user_profile} set uid='$user->uid',real_name='$rname',gender='$gender',image='$insimage',bio=' $bio',zip='$zip',country='$country',religion='$religion',ethnic='$ethnic',slant='$slant',facebook='$facebook',twitter='$twitter' ");
        }
        if($result){
        drupal_set_message($message = 'Profile Updated Successfully!', $type = 'success');
		}
	if(!empty($pass1)){
    	
	if($pass1==$pass2){
		
  $result = db_query("UPDATE {users} set pass='".md5($pass1)."' where uid='$user->uid' ");		
		  drupal_set_message($message = 'Password Updated Successfully!', $type = 'success');
	}else{
		
		 drupal_set_message($message = 'Password should be same to chnage!', $type = 'error');
	}
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
		<form name="profile" id="profile" method="post" enctype="multipart/form-data">
		<fieldset>
        	<legend>Account information</legend>
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
			<legend> Profile Bio </legend>
				<div class="form-item" id="edit-name-wrapper"> 
					<label for="edit-rname">Real Name: <span class="form-required" title="This field is required.">*</span></label> <input maxlength="60" name="rname" id="edit-rname" size="40"  value="'.$real_name.'"  class="form-text required"  type="text"> 
					<div class="description">Spaces are allowed; punctuation is not allowed except for periods, hyphens, and underscores.</div>
                </div>
				<div class="form-item" id="edit-image-wrapper"> <label for="edit-image">Image : </label> <input type="file" name="image" id="image" /> <img src="'.$gSitePath.drupal_get_path('module', 'profile').'/snap/'.$image.'" align="absmiddle" alt="Profile Image" >
				<input type="hidden" name="oldimg" value="'.$image.'"/>
					<div class="description">accept only jpeg,jpg,gif format max. 1 mb size</div>
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
        		<div class="form-item" id="edit-zip-wrapper"> <label for="edit-zip">Zipcode : </label> <input name="zip"  value="'.$zip.'"  id="edit-zip" maxlength="128" size="25" class="form-text" type="text"> <div class="description"></div></div>
        		<div class="form-item" id="edit-religion-wrapper"> <label for="edit-religion">Religion : </label> <input name="religion"  value="'.$religion.'"  id="edit-religion" maxlength="128" size="25" class="form-text" type="text"> <div class="description"></div></div>
        		<div class="form-item" id="edit-ethnic-wrapper"> <label for="edit-ethnic">Ethnicity : </label> <input name="ethnic"  value="'.$ethnic.'"  id="edit-ethnic" maxlength="128" size="25" class="form-text" type="text"> <div class="description"></div></div>
          		<div class="form-item" id="edit-slant-wrapper"> <label for="edit-slant">Slant : </label> <input name="slant" id="edit-slant"  value="'.$slant.'"  maxlength="128" size="25" class="form-text" type="text"> <div class="description"></div></div>
         
        </fieldset>
	  <fieldset>
		<legend>Links </legend>
		<div class="form-item" id="edit-name-wrapper"> 
			<label for="edit-facebook">Facebook: </label> <input maxlength="60" name="facebook" id="edit-facebook"  value="'.$facebook.'"  size="60" value="" class="form-text required" type="text"> 
			<div class="description"></div>
        </div>
		<div class="form-item" id="edit-twitter-wrapper"> <label for="edit-twitter">Twitter :</label> <input maxlength="64" value="'.$twitter.'"  name="twitter" id="edit-twitter" size="60" value="" class="form-text required" type="text"> <div class="description"></div></div>
	
         
        </fieldset>	
	<div class="clear" ><input type="submit" name="update" value="Update"></div>
        
		</form>
		
		<script>
		
		window.addEvent(\'domready\', function() {
			var chk="'.$gender.'";
	if(chk==1){
	
$(\'edit-gender-0\').set(\'checked\',true);
document.profile.gender[0].checked = true;

	}

else if(chk==2){
 $(\'edit-gender-1\').set(\'checked\',true);
 document.profile.gender[1].checked = true;
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


function followinglist()
{

 global $gSitePath,$user,$gDocPath,$base_root;
 $sel_list="select * from follower  where uid='".$user->uid."'  and follower_status='1' limit 0,5";
	$rs_foll_list=db_query($sel_list);
	while($following_list=db_fetch_object($rs_foll_list))
	{
	 $sel_userm="select * from users  where uid='".$following_list->follower_id."' ";
	$rs_userm=db_query($sel_userm);
	$user_namelist=db_fetch_object($rs_userm);
	$following='<h4>'.$user_namelist->name.'  </h4>';
	
	}
	$following.='<a onclick="loadfollowing(\''.$gSitePath.'following\',\'Following\');">More</a>';
return $following;

}




//////////follower //////////////////////////


function followerlist()
{

	global $gSitePath,$user, $gDocPath,$base_root,$base_path;
	
	

	
	$sel_listf="select * from follower  where follower_id='".$user->uid."'  and follower_status='1'  ";
	$rs_followerf=db_query($sel_listf);
	while($follower_resultfuser=db_fetch_object($rs_followerf))
	{
	
	$sel_usermf="select * from users  where uid='".$follower_resultfuser->uid."' ";
	$rs_usermf=db_query($sel_usermf);
	$user_namelistf=db_fetch_object($rs_usermf);
	$followeru='<h4>'.$user_namelistf->name.' </h4>';
	}
	$followeru.='<a onclick="loadfollower(\''.$gSitePath.'follower\',\'Follower\');">More</a>';
				   
				   return $followeru;

}














