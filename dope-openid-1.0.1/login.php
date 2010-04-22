<?php
$path='http://192.9.200.10/heardmentality/';

  $con = mysql_connect("localhost","root","");
  mysql_select_db("heards10", $con);
   //echo llllllllllllll;
  
            
/**
*	This file is part of Dope OpenID.
*   Author: Steve Love (http://www.stevelove.org)
*   
*   Some code has been modified from Simple OpenID:
*   http://www.phpclasses.org/browse/package/3290.html
*
*   Yadis Library provided by JanRain:
*   http://www.openidenabled.com/php-openid/
*
*	Dope OpenID is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	Dope OpenID is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with Dope OpenID. If not, see <http://www.gnu.org/licenses/>.
**/

/*
* Example uses default PHP sessions.
* Feel free to use whatever session management you prefer.
*/
session_start();
/*
* Include our example functions. Your actual functions may differ.
*/
require 'functions.php';

/*
* Is $_SESSION['loggedin'] set and does it evaluate to TRUE?
* If yes, user is already logged in. Redirect them somewhere else.
*/
if(isset($_SESSION['loggedin']) && $_SESSION['loggedin']){
	//header("Location:index.php");
	//exit;
}



/*
* If $_POST['process'] is set, begin OpenID login form processing.
*/
if(isset($_POST['process'])){
	/*
	* Include the Dope OpenID class file.
	*/
	require 'class.dopeopenid.php';
	
	/*
	* URL input is expected here.
	*/
	$openid_url = trim($_POST['openid_identifier']);
	
	/*
	* If running PHP 5, use the built-in URL validator.
	* Else use something like the following regex to validate input.
	*/
	if(function_exists('filter_input')) {
		if( ! filter_input(INPUT_POST, "openid_identifier", FILTER_VALIDATE_URL)) {
			$error = "Error: OpenID Identifier is not in proper format.";
		}
	}
	else 
	{
		// Found this on Google. Seems to match most valid URLs. Feel free to modify or replace.
		if( ! eregi("^((https?)://)?(((www\.)?[^ ]+\.[com|org|net|edu|gov|us]))([^ ]+)?$",$openid_url)) {
			$error = "Error: OpenID Identifier is not in proper format.";
		}
	}
	
	// Proceed if we made it through without setting $error
	if ( ! isset($error)) {
		/*
		* Store the user's submitted OpenID Identity for later use.
		*/
		$_SESSION['openid_url'] = $openid_url;

		/*
		* Create a new Dope_OpenID object
		*/
		$openid = new Dope_OpenID($openid_url);
		/*
		* YOU MUST EDIT THIS LINE.
		* The user's OpenID provider will return them to the URL that you provide here.
		* It could be a separate verify.php script, or just pass a parameter to tell a
		* single processing script what to do (like I've done with this file you're reading).
		*/
	$openid->setReturnURL("".$path."dope-openid-1.0.1/login.php?action=verify");
	//$openid->setReturnURL("http://localhost/heardmentality/dope-openid-1.0.1/login.php?action=verify");
		/*
		* YOU MUST EDIT THIS LINE
		* Set the trust root. This is the URL or set of URLs the user will be asked
		* to trust when signing in with their OpenID Provider. It could be your base
		* URL or a subdirectory thereof. Up to you.
		*/
		//$openid->SetTrustRoot('http://192.9.200.10/heardmentality/');
		$openid->SetTrustRoot(''.$path.'');
	
		/*
		* EDIT THIS LINE (OPTIONAL)
		* When the user signs in with their OpenID Provider, these are
		* the details you would like sent back for your own use.
		* Dope OpenID attempts to get this information using both Simple Registration
		* and Attribute Exchange protocols. The type that is returned depends on the
		* user's Provider. Each provider chooses what they wish to provide and all 
		* defined attributes may not be available. To see where these two types of
		*  attributes intersect, see the following: http://www.axschema.org/types/
		*/
		$openid->setOptionalInfo(array('dob','nickname','country','language','email'));
		
		/*
		* EDIT THIS LINE (OPTIONAL)
		* This is the same as above, except much stricter. By using this method, you
		* are telling the OpenID Provider you *must* have this information. If the Provider
		* will not give you the information the transaction should logically fail, either 
		* at the Provider's end or yours. No info, no sign in. Uncomment to use it.
		*/
		//$openid->setRequiredInfo(array('dob','nickname','country','language','email'));
		
		/*
		* EDIT THIS LINE (OPTIONAL)
		* PAPE Policies help protect users and you against phishing and other authentication
		* forgeries. It's an optional extension, so not all OpenID Providers will be using it.
		* Uncomment to use it.
		* More info and possible policy values here: http://openid.net/specs/openid-provider-authentication-policy-extension-1_0-01.html
		*/
		//$openid->setPapePolicies('http://schemas.openid.net/pape/policies/2007/06/phishing-resistant ');
		
		/*
		* EDIT THIS LINE (OPTIONAL)
		* Also part of the PAPE extension, you can set a time limit for users to
		* authenticate themselves with their OpenID Provider. If it takes too long,
		* authentication will fail and the user will not be allowed access to your site.
		* Uncomment and set a value in seconds to use.
		*/
		//$openid->setPapeMaxAuthAge(120);
		
		/*
		* Attempt to discover the user's OpenID provider endpoint
		*/
		$endpoint_url = $openid->getOpenIDEndpoint();
		if($endpoint_url){
			// If we find the endpoint, you might want to store it for later use.
			$_SESSION['openid_endpoint_url'] = $endpoint_url;
			// Redirect the user to their OpenID Provider
			$openid->redirect();
			// Call exit so the script stops executing while we wait to redirect.
			//exit;
		}
		else{
			/*
			* Else we couldn't find an OpenID Provider endpoint for the user.
			* You can report this error any way you like, but just for demonstration
			* purposes we'll get the error as reported by Dope OpenID. It will be
			* displayed farther down in this file with the HTML.
			*/
			$the_error = $openid->getError();
			$error = "Error Code: {$the_error['code']}<br />";
			$error .= "Error Description: {$the_error['description']}<br />";
		}
	}	
}


/*
* Begin the verification process.
* Note: This is the script that should execute at your return URL, 
* in case you choose to put it in a separate file.
*/
if(isset($_GET['action']) && $_GET['action']=="verify" && $_GET['openid_mode'] != "cancel"){
	/*
	* Include the Dope OpenID class file
	*/
	
	
	require_once 'class.dopeopenid.php';
	
	// Get the user's OpenID Identity as returned to us from the OpenID Provider
	 $openid_url = $_GET['openid_identity'];
	
	/*
	* Create a new Dope_OpenID object.
	*/
	$openid = new Dope_OpenID($openid_url);
	
	/*
	* All the data we received from the OpenID Provider must now be sent back
	* to validate it and verify that nothing has been tampered with in the process.
	*/
	$validate_result = $openid->validateWithServer();

	
	if ($validate_result === TRUE) {
		/*
		* If validation is successful, your next step is to
		* see if the user already exists in your database. Specifically, you
		* need your own function to check for a user_id where openid_url = $openid_url
		*/
		$user_id = your_get_user_function($openid_url);
		
		
		/*
		* If you get a user ID back from your function, this user is a member of
		* your website and is all set up to log in with OpenID. You should now
		* call your own function that logs in the user on your site.
		*/
		if ($user_id > 0) {
			// Assumes your login function returns user details
			// as a string delimited with the pipe ("|") character.
			$str_user = your_openid_login_function($openid_url);
			
			if($str_user) {
				// Assumes you want to split the pipe-delimited string
				list($user_id,$username,$nickname,$email,$dob,$country) = split("[|]",$str_user);
				
				// Assuming you want to store the user details in the session
				$_SESSION['loggedin'] = TRUE;
				$_SESSION['user_id']  = $user_id;
				$_SESSION['username'] = $username;
				
				// Redirect the user to another page, i.e. index.php
				//header("Location:index.php");
				//exit;
			}
			
		}
		else {
		
		echo $_GET['openid_identity'];
			// Else the user doesn't have an existing OpenID record in your database.
			// In this case, you need the user to register an account in order
			// to log in to your site. Store useful information from their
			// OpenID Provider so you can populate the necessary fields on
			// your registration page. Redirect the user there.
			$userinfo = $openid->filterUserInfo($_GET);
			if(($userinfo['email']!='')||($_REQUEST['openid_ax_value_email']!=''))
			{
			if($_REQUEST['openid_ax_value_email']!='')
			$temail=$_REQUEST['openid_ax_value_email'];
			else
			$temail=$userinfo['email'];
			if($_REQUEST['openid_ax_value_language']!='')
			$lang=$_REQUEST['openid_ax_value_language'];
			else
			$lang=$userinfo['language'];
			if($userinfo['nickname']=='')
			{
			if($_REQUEST['openid_ax_value_email']!='')
			$mailg=$_REQUEST['openid_ax_value_email'];
			else
			$mailg=$userinfo['email'];
			$uinfo=explode("@",$mailg);
			$uname=$uinfo[0];
			
			}
			elseif($_REQUEST['openid_ax_value_nickname']!='')
			{
			
			$uname=$_REQUEST['openid_ax_value_nickname'];
			
			}
			else
			{
			$uname=$userinfo['nickname'];
			}
			
			$select_user_count=mysql_num_rows(mysql_query("select * from users where mail='".$userinfo['email']."' and openid='".$_GET['openid_identity']."' "));
			if($select_user_count==0)
			{
			$insert="insert into users (name,pass,mail,language,openid,status)values('".$uname."','".md5($uname)."','".$temail."','".$lang."','".$_GET['openid_identity']."','1') ";
			$insersult=mysql_query($insert);
			}
			}
				/*echo " (".$_GET['openid_identity'].")</p>";
			echo "\t<li><b>nickname yahoo</b>: " .  $_REQUEST['openid_ax_value_nickname'] . "</li>";
			
			echo "\t<li><b>yahoo email</b>: " .  $_REQUEST['openid_ax_value_email'] . "</li>";
			echo "\t<li><b>yahoo language -country</b>: " .  $_REQUEST['openid_ax_value_language'] . "</li>";
			echo "<ul>";
			echo "\t<li><b>Nickname</b>: " . $userinfo['nickname'] . "</li>";
			echo "\t<li><b>Language</b>: " . $userinfo['language'] . "</li>";
			echo "\t<li><b>Email</b>: " . $userinfo['email'] . "</li>";
			echo "</ul>";*/
			$formret= '<form action="'.$path.'user" method="post" id="user-login">
			<input type="hidden" maxlength="60" name="name" id="edit-name" size="60" value="'.$uname.'" class="form-text required"/>
			<input type="password" name="pass" id="edit-pass" value="'.$uname.'"  maxlength="128"  size="60" style="display:none";  class="form-text required"/>
			<input type="hidden" name="form_build_id" id="form-0bb73f903dafa2bf7464d10802fda45b" value="form-0bb73f903dafa2bf7464d10802fda45b"/>
			<input type="hidden" name="form_id" id="edit-user-login" value="user_login"/>
			
			</form>
			<script language="JavaScript" type="text/javascript">
			
			document.getElementById(\'user-login\').submit();
			
			
			</script>
			';
			
			?>
            
		
        
            <?php
			
			echo $formret;
		}
	}
	else if ($openid->isError() === TRUE){
		/*
		* Else if you're here, there was some sort of error during processing.
		*/		
		$the_error = $openid->getError();
		$error = "Error Code: {$the_error['code']}<br />";
		$error .= "Error Description: {$the_error['description']}<br />";
	}
	else{
		/*
		* Else validation with the server failed for some reason.
		*/
		$error = "Error: Could not validate the OpenID at {$_SESSION['openid_url']}";
	}	
}
/*
* The user canceled the process at some point. Nothing to do here except let them know.
*/
else if (isset($_GET['openid_mode']) && $_GET['openid_mode'] == "cancel") {
	$error = "OpenID authorization canceled by user.";
}

/*
* Begin HTML display of login form and any errors that might have occurred.
*/
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<title>Dope OpenID Demo: Log In</title>
	<meta http-equiv="content-type" content="text/html;charset=utf-8" />
	<meta http-equiv="Content-Style-Type" content="text/css" />
   
      <link type="text/css" rel="stylesheet" href="css/openid.css" />
     <script type="text/javascript" src="js/core.js"></script>
    <script type="text/javascript" src="js/more.js"></script>
    <script type="text/javascript" src="js/openid.js"></script>
	<meta http-equiv="content-type" content="text/html;charset=utf-8" />
	<meta http-equiv="Content-Style-Type" content="text/css" />
     <script type="text/javascript">
        window.addEvent('domready', function(){
            new OpenIdSelector('openid_identifier');
        });
		
		
    </script>
</head>

<body  >

	
	
	<form name="openid_form" id="openid_form" action="login.php" method="post" autocomplete="off">
		
	
         
           <div id="openid_choice">
            
                <div id="openid_btns"></div>
            </div>
		<label>
			OpenID URL: <input type="text" name="openid_identifier" id="openid_identifier" maxlength="320" />
		</label>
		
		<input type="hidden" name="process" value="1" />
		
		<!--<button type="submit">Sign In With OpenID</button>-->
	
       
        
        
        
        
        
        
        
        
        
        
         
            <input type="hidden" name="action" value="verify" />

            <div id="openid_choice">
                <p>Please click your account provider:</p>
                <div id="openid_btns"></div>
            </div>
            <div id="openid_input_area">
                <!--<input id="openid_identifier" name="openid_identifier" type="text" value="http://" />
                <input id="openid_submit" type="submit" value="Sign-In"/>-->
            </div>
          <!--  <noscript>
                <p>
                    OpenID is service that allows you to log-on to many different websites using a single indentity.
                    Find out <a href="http://openid.net/what/">more about OpenID</a> 
                    and <a href="http://openid.net/get/">how to get an OpenID enabled account</a>.
                </p>
            </noscript>-->
       
        
        
        
        
        
	</form>
	

</body>
</html>
