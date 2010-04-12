<?php

function invite_friends()
{
  global $gSitePath,$user,$gDocPath,$base_root;
  $uid=$user->uid;

include("gmail.api.include.php");
  if (isset($_REQUEST['invite'])) {
      $GMAIL_USERNAME =$_REQUEST['gmail_username'];
	  $GMAIL_PASSWORD =$_REQUEST['gmail_pass'];
	   $emails = getContacts("$GMAIL_USERNAME","$GMAIL_PASSWORD");

    }


 $strReturn = '
  <script type="text/javascript" src="'.$gSitePath.'sites/all/themes/heardmentality/scripts/mootools-1.2-core.js"></script>
	<script type="text/javascript" src="'.$gSitePath.'sites/all/themes/heardmentality/scripts/mootools-1.2-more.js"></script>	
  <link rel="stylesheet" href="'.$gSitePath.'modules/system/system.css" type="text/css" />
	<link rel="stylesheet" href="'.$gSitePath.'sites/all/themes/heardmentality/css/content.css" type="text/css" />
	
		<form name="profile" id="profile" method="post" enctype="multipart/form-data">
		<fieldset>
        	<legend>From</legend>	<p><input type="text" name="gmail_username" >
			   <input type="password" name="gmail_pass" ></p>
			<p> To: (use commas to separate emails)<textarea id="recipient_list" rows="3" cols="80" name="recipient_list"></textarea></p>
			<p>Message: (optional)	<textarea id="message" rows="3" cols="80"></textarea></p>
			<p>Please use "Contact Name" &lt;XXX@YYY.com&gt; format. Multiple email separated with comma.</p>
			</fieldset>
			<div class="clear" style="height:100px;" ><input type="submit" name="invite" value="Invite">
			<input type="submit" name="cancel" value="Cancel"></div>
			</form>		';
    echo $strReturn;
 
 }


function getContacts($username = null, $password = null){

  $login = $username;
  $password =  $password;
  
  $resultarray = get_contacts($login, $password);
  print_r( $resultarray);
  	foreach($resultarray as $res){
		$emailArray['email'] = $res;
	}
  return $emailArray;
	
} 


