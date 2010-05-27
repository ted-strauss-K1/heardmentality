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
        $find_url = db_query("select * from {question} where qid='$question_id'");
        $question_url = db_fetch_array($find_url);
        if (isset($question_url)) {
            $question_urlff = $question_url['url'];
			 $qtion = $question_url['question'];
			  $ctxt = $question_url['context'];
			
				$input='<input type="hidden" name="qid" value="'.$question_id.'" />';
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
       $body .= $message;
        if (isset($_REQUEST['qid'])) {
		
           $subject = "Heardmentality Question Invite";
            
           //$body .= "Check this question url <br/>";

        
        } else if (isset($_REQUEST['uid'])) {
           $subject = "Heardmentality Profile Invite";
            
           $body .= "Check this profile url <br/>";
        }
        
     // $body .= $question_urlink;
		
			$from = $user->mail;
			
			//$headers = array();
			
		$sel_ulist = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='".$user->uid."'";
		$rs_umlog=db_query($sel_ulist);
		$user_namelistf=db_fetch_object($rs_umlog);
        foreach ($mail_cont as $mail) {

         
          //   $to = email_format(trim($mail));
           // $mail_success = drupal_mail('invite', $to, $subject, $body, $from);

            
          	$to = email_format(trim($mail));

			
			if($to!='')
			{
			
		$query_pt= "SELECT * FROM tbl_points where id='5' "; 
		$query_ptinfo=db_query($query_pt);
		$fetuserpts=db_fetch_object($query_ptinfo);
		$ins_commg="insert into   tbl_user_points (uid,point_id,points,vote_point_id) values('".$user->uid."' ,'5',$fetuserpts->points,'0') ";
		$rs_commg=db_query($ins_commg);
			
			 	$vInsQuery = "insert into invite_friend(uid,friend_email) values ( '".$user->uid."','".$to."')";
				db_query($vInsQuery);
				$lastid=mysql_insert_id();
				
				$idlink = '<a href="'.$question_urlink.'?lid='.$lastid.' "> Click here to View question  </a> ';
				
				$contentlink='<font face="Verdana, Arial, Helvetica, sans-serif"> 
                  <p class="text_black"><font face="Verdana, Arial, Helvetica, sans-serif" 
                  size=2><i>['.$user_namelistf->real_name.'] Someone you know has invited you to join Heardmentality, 
                    a free sharing  site!</i></font></p>
                 </font> 
                  <br>
  
                  <br>
                  <table cellspacing=0 cellpadding=10 width=525  bgcolor="#EBE9D8"
                  border=0>
                    <tbody> 
                    <tr> 
                      <td valign=top align=left><font 
                        face="Verdana, Arial, Helvetica, sans-serif" 
                        size=2>'.$user_namelistf->real_name.' invites you to join us at <a href="'.$gSitePath.'">'.$gSitePath.'</a>.<br>
<div align="justify">The Heardmentality Team is trying to build the largest  site for users to post free question and answers . 

HeardMentality: Its all about Sharing </div>
<br>
<br>
<b>This is a message from '.$user_namelistf->real_name.':</b> <br>
                        <br>
                        '.nl2br($message).'</font></td>
                    </tr>
                    </tbody> 
                  </table>
                  <br>
				
                '. $idlink.' </td>
				  
              </tr>
              </tbody> 
            </table>
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <tr> 
    <td> 
      <p align=left><font face="Verdana, Arial, Helvetica, sans-serif" 
            size=1><br>
        You received this email because someone who knows you sent you an invitation 
        to join them on Heardmentality<br>
        <br>
        </font></p>';
				
				
				
				
				
				
				
				
				$msginvite=$contentlink ;
				
				
				
				$mail_success = htmlmail( $to, $subject, $msginvite, $from,'');
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
    
    
    $strReturn = '
		<div id="log_res"><!-- spanner --></div>
	<div id="err"></div>
	<span class="clr"><!-- spanner --></span>
		<form name="inviteform" id="inviteform" action="'.url($_GET['q'], array('absolute'=>true)).'" method="post" enctype="multipart/form-data">
		<fieldset>
		 <legend>
                        Invite Facebook Friends 
                    </legend>
        	 <table width="100%" border="0" cellpadding="2" cellspacing="2">
           
            <tr>
                <td>
                </td>
                <td align="left">
                    
<script type="text/javascript" 
	src="http://cdn.gigya.com/JS/socialize.js?apikey=2_Zfr6Di925xeUYK-BRe1kNOYYclMYDUbGsgb_kF4NqlZaJ4owUytfdi2cnRePUJ_j">
</script>
<script type="text/javascript">
var conf =
{
   // APIKey: \'2_Zfr6Di925xeUYK-BRe1kNOYYclMYDUbGsgb_kF4NqlZaJ4owUytfdi2cnRePUJ_j\'
   APIKey: \'2_OdDWGhe73p04B0m5k4zqlKdtnBCu9jbyud93Jgy-b8jEtbAXlAkbfpk9qBp781g8\'
    ,enabledProviders: \'facebook\' 
	
}


var invite =
{
    title: "Invite your friends to Answer Question on Heardmentality",
    text: "You are invited to Answer the "
		+ "<a href=\''.$question_urlink.'\'>Question .</a>" 
		+ " '.$ctxt.'.",
    name: "'.$qtion.'",
    actionText: "Answer This question on Heardmentality",
    actionURL: " '.$question_urlink.'"
}



var params =
{
showTermsLink:false, 
    containerID: "loginDiv", // The Plugin will embed itself inside 
		invite:invite
	   
};
function printResponse(response) {  
    if ( response.errorCode == 0 ) {             
        var user = response.user;
 
    }
    else {
   
    }  
}

</script>

<div id="loginDiv"></div>
<script type="text/javascript">
  
	gigya.services.socialize.disconnect(conf,{callback:printResponse, provider:\'facebook\'});
    gigya.services.socialize.showLoginUI(conf, params);
	
</script>


                </td>
            </tr>
            
			
			
        </table>
			</fieldset>
	
			
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
          return  $email = trim($e[0]);

            $contact_names[trim($e[0])] = trim($t[0]);
        }
    } else {
        if (ereg("^[a-zA-Z0-9_\.\-]+[a-zA-Z0-9_\+\.\-]*@[a-zA-Z0-9\-]+\.[a-zA-Z0-9\-\.]+[a-zA-Z0-9\-\.]*$", $valueFrmsubmit)) {
          return  $email = $valueFrmsubmit;
        }

        //return $email;

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


