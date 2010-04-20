<?php
ob_start();
session_start();

require 'functions.php';


if(isset($_SESSION['loggedin']) && $_SESSION['loggedin']){
	//header("Location:http://192.9.200.10/heardmentality/ids/index.php");
	//exit;
}
if(isset($_POST['process'])){

	require 'class.dopeopenid.php';
	
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
		$openid->setReturnURL("http://192.9.200.10/heardmentality/ids/login.php?action=verify");
	
		/*
		* YOU MUST EDIT THIS LINE
		* Set the trust root. This is the URL or set of URLs the user will be asked
		* to trust when signing in with their OpenID Provider. It could be your base
		* URL or a subdirectory thereof. Up to you.
		*/
		$openid->SetTrustRoot('http://192.9.200.10/heardmentality/ids/');
	
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
			//$_SESSION['openid_endpoint_url'] = $endpoint_url;
			// Redirect the user to their OpenID Provider
			//$openid->redirect();
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
