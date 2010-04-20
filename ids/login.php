<?php
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
	header("Location:http://192.9.200.10/heardmentality/ids/index.php");
	exit;
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
				
			
			
				
				
					$userinfo = $openid->filterUserInfo($_GET);
			
			//echo "<p>Your OpenID Identity (".$_GET['openid_identity'].") wasn't found in our records.</p>";
			//echo "<p>Good news though: We just need your email and a friendly name and you'll have full access to all the site's features.</p>";
		
				
			
				
				
				
				// Redirect the user to another page, i.e. index.php
				header("Location:http://192.9.200.10/heardmentality/ids/index.php");
				exit;
			}
			
		}
		else {
			// Else the user doesn't have an existing OpenID record in your database.
			// In this case, you need the user to register an account in order
			// to log in to your site. Store useful information from their
			// OpenID Provider so you can populate the necessary fields on
			// your registration page. Redirect the user there.
			$userinfo = $openid->filterUserInfo($_GET);
			
			print_r($_SESSION);
			//echo "<p>Your OpenID Identity (".$_GET['openid_identity'].") wasn't found in our records.</p>";
			//echo "<p>Good news though: We just need your email and a friendly name and you'll have full access to all the site's features.</p>";
			//echo "<p>DEBUG: The following information came back from your OpenID provider:</p>";
			if($userinfo['email']!='')
			{
			
			echo $insert="insert into users (name,mail,language,openid)values(" . $userinfo['nickname'] . "," . $userinfo['email'] . "," . $userinfo['language'] . "," . $_SESSION['openid_url'] . ") ";
			}
			echo "<ul>";
			echo "\t<li><b>nickname yahoo</b>: " .  $_REQUEST['openid_ax_value_nickname'] . "</li>";
				echo "\t<li><b>link</b>: " . print_r($_REQUEST) . "</li>";
			
				echo "\t<li><b>yahoo email</b>: " .  $_REQUEST['openid_ax_value_email'] . "</li>";
				echo "\t<li><b>yahoo language -country</b>: " .  $_REQUEST['openid_ax_value_language'] . "</li>";
				
			//echo "\t<li><b>link</b>: " . print_r($_REQUEST) . "</li>";
			echo "\t<li><b>link</b>: " . $_SESSION['openid_url'] . "</li>";
			echo "\t<li><b>Nickname</b>: " . $userinfo['openid_ax_value_nickname'] . "</li>";
			echo "\t<li><b>Language</b>: " . $userinfo['language'] . "</li>";
			echo "\t<li><b>Email</b>: " . $userinfo['email'] . "</li>";
			echo "\t<li><b>Country</b>: " . $userinfo['country'] . "</li>";
			echo "</ul>";
			
			exit;
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

<body>

	<p style="color:#f00;"><?php echo $error; ?></p>
	
	<form name="openid_form" id="openid_form" action="login.php" method="post" autocomplete="off">
		
		<!-- Your OpenID input should be named "openid_identifier" to follow best practices
	     and in order to work with the ID Selector JavaScript, should you choose to use it. -->
         
           <div id="openid_choice">
            
                <div id="openid_btns"></div>
            </div>
		<label>
			OpenID URL: <input type="text" name="openid_identifier" id="openid_identifier" maxlength="320" />
		</label>
		
		<input type="hidden" name="process" value="1" />
		
<!--		<button type="submit">Sign In With OpenID</button>
-->		
        
        
        
        
        
        
        
        
        
        
        
         
            <input type="hidden" name="action" value="verify" />

            <div id="openid_choice">
                <p>Please click your account provider:</p>
                <div id="openid_btns"></div>
            </div>
            <div id="openid_input_area">
                <input id="openid_identifier" name="openid_identifier" type="text" value="http://" />
                <input id="openid_submit" type="submit" value="Sign-In"/>
            </div>
            <noscript>
                <p>
                    OpenID is service that allows you to log-on to many different websites using a single indentity.
                    Find out <a href="http://openid.net/what/">more about OpenID</a> 
                    and <a href="http://openid.net/get/">how to get an OpenID enabled account</a>.
                </p>
            </noscript>
       
        
        
        
        
        
	</form>
	
<!-- BEGIN ID SELECTOR -->
<!--<script type="text/javascript" id="__openidselector" src="script.js" charset="utf-8"></script>-->
<!-- END ID SELECTOR -->

</body>
</html>
