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
	
	if(function_exists('filter_input')) {
		if( ! filter_input(INPUT_POST, "openid_identifier", FILTER_VALIDATE_URL)) {
			$error = "Error: OpenID Identifier is not in proper format.";
		}
	}
	else 
	{
		
		if( ! eregi("^((https?)://)?(((www\.)?[^ ]+\.[com|org|net|edu|gov|us]))([^ ]+)?$",$openid_url)) {
			$error = "Error: OpenID Identifier is not in proper format.";
		}
	}
	
	
	if ( ! isset($error)) {
		
		$_SESSION['openid_url'] = $openid_url;

		
		$openid = new Dope_OpenID($openid_url);
		
		$openid->setReturnURL("http://192.9.200.10/heardmentality/ids/login.php?action=verify");
	
		
		$openid->SetTrustRoot('http://192.9.200.10/heardmentality/ids/');
	
		
		$openid->setOptionalInfo(array('dob','nickname','country','language','email'));
		
		
		$endpoint_url = $openid->getOpenIDEndpoint();
		if($endpoint_url){
			
			//$openid->redirect();
			
			//exit;
		}
		else{
			
			$the_error = $openid->getError();
			$error = "Error Code: {$the_error['code']}<br />";
			$error .= "Error Description: {$the_error['description']}<br />";
		}
	}	
}



if(isset($_GET['action']) && $_GET['action']=="verify" && $_GET['openid_mode'] != "cancel"){
	require_once 'class.dopeopenid.php';
	$openid_url = $_GET['openid_identity'];
	$openid = new Dope_OpenID($openid_url);
	
	$validate_result = $openid->validateWithServer();
	
	
	if ($validate_result === TRUE) {
	
		$user_id = your_get_user_function($openid_url);
		
		if ($user_id > 0) {
			
			$str_user = your_openid_login_function($openid_url);
			
			if($str_user) {
			
				list($user_id,$username,$nickname,$email,$dob,$country) = split("[|]",$str_user);
				
				
				$_SESSION['loggedin'] = TRUE;
				$_SESSION['user_id']  = $user_id;
				$_SESSION['username'] = $username;
				
			
			
				
				
					$userinfo = $openid->filterUserInfo($_GET);
			
		
				
				
				
				header("Location:http://192.9.200.10/heardmentality/ids/index.php");
				exit;
			}
			
		}
		else {
		
			$userinfo = $openid->filterUserInfo($_GET);
			
			
		
		}
	}
	else if ($openid->isError() === TRUE){
			
		$the_error = $openid->getError();
		$error = "Error Code: {$the_error['code']}<br />";
		$error .= "Error Description: {$the_error['description']}<br />";
	}
	else{
		
		$error = "Error: Could not validate the OpenID at {$_SESSION['openid_url']}";
	}	
}
else if (isset($_GET['openid_mode']) && $_GET['openid_mode'] == "cancel") {
	$error = "OpenID authorization canceled by user.";
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
	


</body>
</html>
