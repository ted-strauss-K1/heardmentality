<?php
 set_time_limit  ( 0  );
function invite_friends()
{
  global $gSitePath,$user,$gDocPath,$base_root;
  $uid=$user->uid;
  $requestedemails = NULL ;
  $title = NULL ;
  $question_url = NULL;
   $invite_for_question = NULL;
 // include("gmail.api.include.php");
  include('openinviter.php');
$inviter=new OpenInviter();
$oi_services=$inviter->getPlugins();
if (!empty($_POST['step'])) $step=$_POST['step'];
else $step='get_contacts';

if (isset($_POST['provider_box'])) 
{
	if (isset($oi_services['email'][$_POST['provider_box']])) $plugType='email';
	elseif (isset($oi_services['social'][$_POST['provider_box']])) $plugType='social';
	else $plugType='';
}

   if(isset($_REQUEST['step']) && $_REQUEST['step']=='get_contacts')
		{
		
		if (empty($_POST['email_box']))
			echo $ers['email']="Email missing !";
		if (empty($_POST['password_box']))
			echo $ers['password']="Password missing !";
		if (empty($_POST['provider_box']))
			echo $ers['provider']="Provider missing !";
		if (count($ers)==0)
			{
			$inviter->startPlugin($_POST['provider_box']);
			$internal=$inviter->getInternalError();
			if ($internal)
 				echo $ers['inviter']=$internal;
			elseif (!$inviter->login($_POST['email_box'],$_POST['password_box']))
				{
				$internal=$inviter->getInternalError();
 				echo $ers['login']=($internal?$internal:"Login failed. Please check the email and password you have provided and try again later !");
				}
			elseif (false===$contacts=$inviter->getMyContacts())
			echo	$ers['contacts']="Unable to get contacts !";
			else
				{
				$import_ok=true;
				$step='send_invites';
				$_POST['oi_session_id']=$inviter->plugin->getSessionID();
				$_POST['message_box']='';
				$inviter->showContacts();
			    if(count($contacts) >0){
				$ALLEmails =array_keys($contacts);
				$requestedemails = implode(",", $ALLEmails);
				}else{
				
				
				}
				
	
				}
			}
		}


   if(isset($_REQUEST['qid'])){
	   $question_id =	$_REQUEST['qid'];
	   $find_url = db_query("select url from {question} where qid='$question_id'");
       $question_url = db_fetch_array($find_url);
		if(isset( $question_url)){
		$question_url = $question_url['url'];
		}
       $question_url= $gSitePath.$question_url;
 }


/*  if (isset($_REQUEST['gos'])) {
	    if (isset($_REQUEST['domain']) && $_REQUEST['domain']=='gmail.com' ) {
			  $GMAIL_USERNAME =$_REQUEST['gmail_username'];
			  $GMAIL_PASSWORD =$_REQUEST['gmail_pass'];
			  $emails = getContacts("$GMAIL_USERNAME","$GMAIL_PASSWORD");
              $title = 'The following contacts are imported from your gmail account';
		}
    }*/
  if (isset($_REQUEST['invite'])) {
		$senderlist = $_REQUEST['recipient_list'];
		$message = isset($_REQUEST['message'])?$_REQUEST['message']:'';
		$question_list = isset($_REQUEST['question_list'])?$_REQUEST['question_list']:'';
	    $mail_cont = explode(',',  $senderlist);
        $guest_mail = array();
		$params = array( 'myVar' => 'data you would like in your message and/or subject');
		$params['message'].=$message;
		$params['question'].=$question_list;
	
        foreach($mail_cont as $mail) {
		// $guest_mail[] = trim($mail);
		   $EmailTo = trim($mail);
		   drupal_mail('invite', 'invitation', $EmailTo, language_default(), $params);
           }
	 }


	if(isset($question_url) && $question_url != NULL){
     $invite_for_question = '<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<textarea id="question_list" rows="3" cols="80" name="question_list" disabled="disabled">'.$question_url.'</textarea><input type="hidden"  name="question_list" value="'.$question_url.'"></p>';
  
	 }
	$mail_options='<option value="aol">AOL</option>
                  <option value="gmail">Gmail</option>
		          <option value="hotmail"> Hotmail</option>
				  <option value="linkedin">LinkedIn</option>
		          <option value="yahoo">Yahoo</option>';
		
 $strReturn = '
  <script type="text/javascript" src="'.$gSitePath.'sites/all/themes/heardmentality/scripts/mootools-1.2-core.js"></script>
	<script type="text/javascript" src="'.$gSitePath.'sites/all/themes/heardmentality/scripts/mootools-1.2-more.js"></script>	
  <link rel="stylesheet" href="'.$gSitePath.'modules/system/system.css" type="text/css" />
	<link rel="stylesheet" href="'.$gSitePath.'sites/all/themes/heardmentality/css/content.css" type="text/css" />
	
		<form name="profile" id="profile" method="post" enctype="multipart/form-data">
		<fieldset>
        	<legend>Invite Friends</legend>	
			<p>	<label for="edit-name">Email: <span class="form-required" title="This field is required.">*</span></label>
			<input type="text" name="email_box" >&nbsp;&nbsp;&nbsp;<select name="provider_box">'.$mail_options.'</select>
			<br/></p>
					<input type="hidden" name="step" value="get_contacts">
			 <p> <label for="edit-name">Password: <span class="form-required" title="This field is required.">*</span></label> <input type="password" name="password_box" ></p>
			 <input type="submit" name="go" value="go"></br></br>
			 <h2>'.$title.'</h2>
			<p>
			To: (use commas to separate emails)<textarea id="recipient_list" rows="3" cols="80" name="recipient_list">'.$requestedemails.'</textarea></p>
			'.
			$invite_for_question.'
			<p>Message: (optional)	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<textarea id="message" name="message" rows="3" cols="80"></textarea></p>
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

//  $variables = user_mail_tokens($params, $language);
  $variables = $params['message'].$params['question'];
  switch ($key) {
    case 'invitation':
      // note: data can be passed to this function in the $params array
      $message['subject'] = t('EMAIL SUBJECT');
	//  $message['body'][] = t('MESSAGE BODY');
	  $message['body'][] = t("", $variables, $language->language);
      break;   
  }
}


