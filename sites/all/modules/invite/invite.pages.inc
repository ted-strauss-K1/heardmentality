<?php

function invite_friends()
{
  global $gSitePath,$user,$gDocPath,$base_root;
  $uid=$user->uid;
  $emails = NULL ;
  $title = NULL ;
  $question_url = NULL;
   $invite_for_question = NULL;
  include("gmail.api.include.php");
   if(isset($_REQUEST['qid'])){
	   $question_id =	$_REQUEST['qid'];
	   $find_url = db_query("select url from {question} where qid='$question_id'");
       $question_url = db_fetch_array($find_url);
		if(isset( $question_url)){
		$question_url = $question_url['url'];
		}
       $question_url= $gSitePath.$question_url;
 }


  if (isset($_REQUEST['go'])) {
	    if (isset($_REQUEST['domain']) && $_REQUEST['domain']=='gmail.com' ) {
			  $GMAIL_USERNAME =$_REQUEST['gmail_username'];
			  $GMAIL_PASSWORD =$_REQUEST['gmail_pass'];
			  $emails = getContacts("$GMAIL_USERNAME","$GMAIL_PASSWORD");
              $title = 'The following contacts are imported from your gmail account';
		}
    }

  if (isset($_REQUEST['invite'])) {
		$senderlist = $_REQUEST['recipient_list'];
	    $mail_cont = explode(',',  $senderlist);
        $guest_mail = array();
		$params = array( 'myVar' => 'data you would like in your message and/or subject');
        foreach($mail_cont as $mail) {
		// $guest_mail[] = trim($mail);
		   $EmailTo = trim($mail);
		   drupal_mail('invite', 'invitation', $EmailTo, language_default(), $params);
           }
	 }


	if(isset($question_url) && $question_url != NULL){
     $invite_for_question = '<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<textarea id="question_list" rows="3" cols="80" name="question_list" disabled="disabled">'.$question_url.'</textarea></p>';
  
	 }
	$mail_options='<option value="gmail.com">gmail</option>
		<option value="hotmail.com"> hotmail</option>
		<option value="yahoo.com">yahoo</option>';
		
 $strReturn = '
  <script type="text/javascript" src="'.$gSitePath.'sites/all/themes/heardmentality/scripts/mootools-1.2-core.js"></script>
	<script type="text/javascript" src="'.$gSitePath.'sites/all/themes/heardmentality/scripts/mootools-1.2-more.js"></script>	
  <link rel="stylesheet" href="'.$gSitePath.'modules/system/system.css" type="text/css" />
	<link rel="stylesheet" href="'.$gSitePath.'sites/all/themes/heardmentality/css/content.css" type="text/css" />
	
		<form name="profile" id="profile" method="post" enctype="multipart/form-data">
		<fieldset>
        	<legend>Invite Friends</legend>	
			<p>	<label for="edit-name">Username: <span class="form-required" title="This field is required.">*</span></label>
			<input type="text" name="gmail_username" >&nbsp;&nbsp;&nbsp;<select name="domain">'.$mail_options.'</select>
			<br/></p>
			 <p> <label for="edit-name">Password: <span class="form-required" title="This field is required.">*</span></label> <input type="password" name="gmail_pass" ></p>
			 <input type="submit" name="go" value="go"></br></br>
			 <h2>'.$title.'</h2>
			<p>
			To: (use commas to separate emails)<textarea id="recipient_list" rows="3" cols="80" name="recipient_list">'.$emails.'</textarea></p>
			'.
			$invite_for_question.'
			<p>Message: (optional)	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<textarea id="message" rows="3" cols="80"></textarea></p>
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
  if(isset($resultarray[1]) && count($resultarray[1])> 0) {
		foreach($resultarray[1] as $email){
		   $allemail.= $email.',';
		
		}
	  return $allemail;
  } 
	return null;
}

function invite_mail($key, &$message, $params) {
  switch ($key) {
    case 'invitation':
      // note: data can be passed to this function in the $params array
      $message['subject'] = t('EMAIL SUBJECT');
      $message['body'] = t('MESSAGE BODY');
      break;   
  }
}


