<?php
function invite_friends() {
    global $gSitePath,$user,$gDocPath,$base_root;
    $uid = $user->uid;
    $requestedemails = NULL;
    $title = NULL;
    $question_urlink = NULL;
    $invite_for_question = NULL;
    $body = NULL;
    /* // include("gmail.api.include.php");
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
     */


    if (isset($_REQUEST['qid'])) {
        $question_id = $_REQUEST['qid'];
        $find_url = db_query("select url from {question} where qid='$question_id'");
        $question_url = db_fetch_array($find_url);
        if (isset($question_url)) {
            $question_urlff = $question_url['url'];
				$input='<input type="hidden" name="qid" value="'.$uid.'" />';
        }
       $question_urlink = $gSitePath.$question_urlff;
    } else if (isset($_REQUEST['uid'])) {
        $uid = $_REQUEST['uid'];
        $find_url = db_query("select name from {users} where uid='$uid'");
        $udata = db_fetch_array($find_url);
        if (! empty($udata)) {
            $uname = $udata['name'];
        }
        $question_urlink = $gSitePath.'profile/'.$uname;
    		$input='<input type="hidden" name="uid" value="'.$uid.'" />';
    } else {
        echo "Sorry Nothing to Share";
        exit;
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
        set_time_limit(0);
		$flag=0;
		$msg='Sorry invitation sending failed!';
        //	print_r($_REQUEST);
        $senderlist = $_REQUEST['recipient_list'];
        $message = isset($_REQUEST['message']) ? $_REQUEST['message'] : '';
        $question_list = isset($_REQUEST['question_list']) ? $_REQUEST['question_list'] : '';
        $mail_cont = explode(',', $senderlist);
        $guest_mail = array();
        //mail
       // $body .= $message."<br/>";
        if (isset($_REQUEST['qid'])) {
		
          //  $subject = "Heardmentality Question Invite";
            
          //  $body .= "Check this question url <br/>";

        
        } else if (isset($_REQUEST['uid'])) {
           // $subject = "Heardmentality Profile Invite";
            
           // $body .= "Check this profile url <br/>";
        }
        
      //  $body .= $question_urlink;
		
			$from = $user->mail;
			//$headers = array();
			
       
        foreach ($mail_cont as $mail) {
            
          	$to = email_format(trim($mail));
			
			if($to!='')
			{
			 	$vInsQuery = "insert into invite_friend(uid,friend_email) values ( '".$user->uid."','".$to."')";
				db_query($vInsQuery);
				$lastid=mysql_insert_id();
				//$body .= '?lid='.$lastid.' ';
				
			$find_urls = db_query("select url from {question} where qid='$qid'");
			$question_urls = db_fetch_object($find_urls);
			
				$subject = "Heardmentality Question Invite";
				
				$body = " $message Check this question url $question_urls->url <br/>";
				
				
				$mail_success = htmlmail( $to, $subject, $body, $from,'');
			  }
			  
			
		
			
			
			
		
			
			//$mail_success = drupal_mail('invite', $to, $subject, $body, $from);
            if (! empty($to)) {
			
                // $mail_success=drupal_mail('invite', 'invitation', $EmailTo, language_default(), $params);
                if (!$mail_success) {
                $flag=0;
				$msg='Invitation not sent server error!';
				    drupal_set_message(t('There has been an error.\\nTo: '.$to.'\/nSubject: '.$subject.'\rBody: '.$body.'\nFrom: '.$from.'\nHeaders: '.$headers));
                } else {
				
			
                    $flag=1;
					$msg='Invitation sent successfully!';
                    drupal_set_message(t('Mail Sent Successfully!'), 'success');
					
                }
            }
        }
		echo $flag;
		exit;
    }

    
    if (isset($question_urlink) && $question_urlink != NULL) {
        $question_urlink = $question_urlink;
    }
    $mail_options = '<option value="aol">AOL</option>
                  <option value="gmail">Gmail</option>
		          <option value="hotmail"> Hotmail</option>
				  <option value="linkedin">LinkedIn</option>
		          <option value="yahoo">Yahoo</option>';
    
    $strReturn = '
		<div id="log_res"><!-- spanner --></div>
	<div id="err"></div>
	<span class="clr"><!-- spanner --></span>
		<form name="inviteform" id="inviteform" action="'.url($_GET['q'], array('absolute'=>true)).'" method="post" enctype="multipart/form-data">
		<fieldset>
		 <legend>
                        Invite Friends
                    </legend>
        	 <table width="100%" border="0" cellpadding="2" cellspacing="2">
            <tr>
                <td width="30%">
                </td>
                <td width="40%">
                </td>
				<td width="40%"  rowspan="5"> <!--<img src="'.$gSitePath.drupal_get_path('module', 'invite').'/images/invite_mail.jpg" border="0" />--></td>
            </tr>
            <tr>
                <td align="left">
                   
                    <!--		<p>	<label for="edit-name">Email: <span class="form-required" title="This field is required.">*</span></label>
                    <input type="text" name="email_box" >&nbsp;&nbsp;&nbsp;<select name="provider_box">'.$mail_options.'</select>
                    <br/></p>
                    <input type="hidden" name="step" value="get_contacts">
                    <p> <label for="edit-name">Password: <span class="form-required" title="This field is required.">*</span></label> <input type="password" name="password_box" ></p>
                    <input type="submit" name="go" value="go"></br></br>
                    <h2>'.$title.'</h2> --> 
					To: 
                    <br/>
                    (use commas to separate emails)
                </td>
                <td align="left">
                    <textarea id="recipient_list" rows="3" cols="80" name="recipient_list"></textarea>
                </td>
					<td></td>
            </tr>
            <tr>
                <td>
                </td>
                <td align="left">
                    <a href="#" onclick="showPlaxoABChooser(\'recipient_list\', \'heardmentality/'.drupal_get_path('module', 'quest_lite').'/plaxo.html\'); return false"><img src="http://www.plaxo.com/images/abc/buttons/add_button.gif" alt="Add from my address book" /></a>
                </td>
            </tr>
            <tr>
                <td align="left">
                    Message:
                    <br/>
                    (optional) 
                </td>
                <td align="left">
             <textarea id="message" name="message" rows="3" cols="80"></textarea>
                </td>
					<td></td>
            </tr>
			<tr>
			<td>
			Refer URL :
			</td>
			<td align="left">
			  '.$question_urlink.'
			
			</td>
				<td></td>
			</tr>
			
        </table>
			</fieldset>
	
			<div class="clear" style="height:100px;" >'.$input.'<input type="submit" name="invite" value="Invite">
			
			<input type="submit" name="cancel" onclick="MochaUI.closeAll();" value="Cancel"></div>
			</form>		';
    echo $strReturn;

}


function getContacts($username = null, $password = null) {
    
    $login = $username;
    $password = $password;
    
    $resultarray = get_contacts($login, $password);
    if (isset($resultarray[1]) && count($resultarray[1]) > 0) {
        foreach ($resultarray[1] as $email) {
            $allemail .= $email.',';
        
        }
        return $allemail;
    }
    return null;
}


function email_format($valueFrmsubmit = '') {
    
    $t = explode("<", $valueFrmsubmit);
    if (sizeof($t) > 1) {
        $e = explode(">", $t[1]);
        if (ereg("^[a-zA-Z0-9_\.\-]+[a-zA-Z0-9_\+\.\-]*@[a-zA-Z0-9\-]+\.[a-zA-Z0-9\-\.]+[a-zA-Z0-9\-\.]*$", trim($e[0]))) {
           return $email = trim($e[0]);
            $contact_names[trim($e[0])] = trim($t[0]);
        }
    } else {
        if (ereg("^[a-zA-Z0-9_\.\-]+[a-zA-Z0-9_\+\.\-]*@[a-zA-Z0-9\-]+\.[a-zA-Z0-9\-\.]+[a-zA-Z0-9\-\.]*$", $valueFrmsubmit)) {
          return  $email = $valueFrmsubmit;
        }
       // return $email;
    }


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


