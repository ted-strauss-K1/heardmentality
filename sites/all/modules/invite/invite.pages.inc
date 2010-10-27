<?php
function invite_friends() {
    global $gSitePath,$user,$gDocPath,$base_root,$apikey;
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
				  //#EBE9D8
                  <table cellspacing=0 cellpadding=10 width=525  bgcolor=""
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
        $question_urlink = $question_urlink."?faceid=$user->uid";
    }
    
    
    $strReturn = '
			<link rel="stylesheet" href="'.$gSitePath.path_to_theme().'/css/css.css" type="text/css" />
			<div class="facttop2">INVITE YOUR FRIENDS</div>
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
	src="http://cdn.gigya.com/JS/socialize.js?apikey=2_OdDWGhe73p04B0m5k4zqlKdtnBCu9jbyud93Jgy-b8jEtbAXlAkbfpk9qBp781g8">
</script>
<script type="text/javascript">
var conf =
{
   // APIKey: \'2_Zfr6Di925xeUYK-BRe1kNOYYclMYDUbGsgb_kF4NqlZaJ4owUytfdi2cnRePUJ_j\'
 APIKey: \''.$apikey.'\'
  //  APIKey: \'2_nyUH8AtI3Nced_GmaSm9Z0pg_mpO1tRigdBl_YpgUAAyZtfk42_V4sAE41M8WZ0i\'
   
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


function twitter_login()
{
global $gSitePath,$user,$gDocPath,$base_root;

$qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

 $log = '<script type="text/javascript">
	window.addEvent(\'domready\', function() {
	
	if (!window.demo_path) window.demo_path = \'\';
	var demo_path = window.demo_path;
	
	$(\'twitform\').addEvent(\'submit\', function(e) {
	
	e.stop();
	
	var log = $(\'log_res\').empty().addClass(\'ajax-loading\');
	
	this.set(\'send\', {onComplete: function(response) { 
	log.removeClass(\'ajax-loading\');
	log.set(\'html\', response);
	}});
	
	this.send();
	});
	});
	
	
	</script>
	';
$log.='<div id="log_res"></div><div id="form" align="center"><!--Start Form-->
<form id="twitform"  method="post" action="'.$gSitePath.'twitterpost" enctype="multipart/form-data">
  <p><br />
  <label>
    Twitter Username:
    <input name="t_user" type="text" id="t_user">
  </label>
  </p>
  
  <p><br />
    <label>Twitter Password:
    <input name="t_pass" type="password" id="t_pass">
	 <input name="t_qid" type="hidden" id="t_qid" value="'.$qid.'">
    </label>
    </p>
  
    <label>
	  
	  <input type="submit" name="button" id="submitter"  value="Post To Your Twitter Account!/>
    </label>
  </p>
</form>
</div>';





echo $log;





}



function twitterpost_save()
{
global $gSitePath,$user,$gDocPath,$base_root;




    $vSql = "select * from {question} where status='1' and qid='".$_POST[t_qid]."' ";
    $rlist = db_query($vSql);
    $oListquest = db_fetch_object($rlist);





$username = ($_POST['t_user']);
$password = ($_POST['t_pass']);
$file= "http://api.bit.ly/v3/shorten?login=amsaveni&apiKey=R_c5d3d662c70676d01183c1e59e1f048a&longUrl=http%3A%2F%2Fbetaworks.com%2F&format=json";
$url= file_get_contents($file);
$message = $oListquest->question.'  copy and paste this link  '.$gSitePath.''.$oListquest->url;

$url = 'http://twitter.com/statuses/update.xml';
$curl_handle = curl_init();
curl_setopt($curl_handle, CURLOPT_URL, "$url");
curl_setopt($curl_handle, CURLOPT_CONNECTTIMEOUT, 2);
curl_setopt($curl_handle, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($curl_handle, CURLOPT_POST, 1);
curl_setopt($curl_handle, CURLOPT_POSTFIELDS, "status=$message");
curl_setopt($curl_handle, CURLOPT_USERPWD, "$username:$password");

$buffer = curl_exec($curl_handle);
curl_close($curl_handle);
//echo $buffer;
if ($buffer=="Could not authenticate you") {
    echo "<p align=\"center\" >".'Sorry, due to an error your Twitter status could not be updated! Please check your username/password!'."</p>";
}
else
{
echo "<p align=\"center\" >".' Twitter  updated successfully !'."</p>";
} 

}

function send_mail()
{
    global $gSitePath,$user,$gDocPath,$base_root;
         $send_qry = "select * from hm_mails where mail_status='0'";
            $send_exec = ExecuteQuery($send_qry, "select");
        
            foreach ($send_exec as $sendeach) {
               
             $mail_success = htmlmail_function($sendeach['user_to_id'], $sendeach['subject'], $sendeach['content'], '');
             if($mail_success)
             {
                 db_query("update hm_mails set mail_status=1 where mail_id='".$sendeach['user_to_id']."'");
             }
          }
          exit;
}

