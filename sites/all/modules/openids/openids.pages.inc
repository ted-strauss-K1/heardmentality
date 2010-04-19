<?php
function openid_login()
{
 global $gSitePath,$user,$gDocPath,$base_root;
session_start();

require 'functions.php';

if(isset($_SESSION['loggedin']) && $_SESSION['loggedin']){
	header("Location:".$gSitePath."member/index");
	exit;
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
		
		$openid->setReturnURL("".$gSitePath."member/login?action=verify");
	
		
		$openid->SetTrustRoot('".$gSitePath."member/login');
	

		$openid->setOptionalInfo(array('dob','nickname','country','language','email'));

		$endpoint_url = $openid->getOpenIDEndpoint();
		if($endpoint_url){
		
			$_SESSION['openid_endpoint_url'] = $endpoint_url;
		
			$openid->redirect();
		
			exit;
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
			
			
				header("Location:'.$gSitePath.'member/index");
				exit;
			}
			
		}
		else {
			
			$userinfo = $openid->filterUserInfo($_GET);
			
			
		
			if($userinfo['email']!='')
			{
			
			echo $insert="insert into users (name,mail,language,openid)values('".$userinfo['nickname']."','".$userinfo['email']."','".$userinfo['language']."','".$_SESSION['openid_url']."') ";
			$inforesult=db_query($insert);
			}
			/*echo "<ul>";
			
			echo "\t<li><b>link</b>: " . $_SESSION['openid_url'] . "</li>";
			echo "\t<li><b>Nickname</b>: " . $userinfo['nickname'] . "</li>";
			echo "\t<li><b>Language</b>: " . $userinfo['language'] . "</li>";
			echo "\t<li><b>Email</b>: " . $userinfo['email'] . "</li>";
			echo "\t<li><b>Country</b>: " . $userinfo['country'] . "</li>";
			echo "</ul>";
			
			exit;*/
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

	
	$showop='<link type="text/css" rel="stylesheet" href="'.$gSitePath.'sites/all/modules/openids/css/openid.css" />
	<script type="text/javascript" src="'.$gSitePath.'sites/all/modules/openids/js/openid.js"></script>
	<script type="text/javascript">
        window.addEvent(\'domready\', function(){
            new OpenIdSelector(\'openid_identifier\');
        });
    </script>
	<form name="openid_form" id="openid_form" action="'.$gSitePath.'member/login" method="post" autocomplete="off"><div id="openid_choice">
         
                <div id="openid_btns"></div>
            </div>
		<label>
			OpenID URL: <input type="text" name="openid_identifier" id="openid_identifier" maxlength="320" />
		</label><input type="hidden" name="process" value="1" />
		
		 <fieldset>
            <legend>Sign-in or Create New Account</legend>
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
        </fieldset>
		<embed height="55" width="120" align="middle" pluginspage="http://www.macromedia.com/go/getflashplayer" type="application/x-shockwave-flash" swliveconnect="true" flashvars="ContainerAndSWF=componentDiv|Gigya.Socialize.Login_en&amp;SWFModuleID=componentDiv|Gigya.Socialize.Login_en&amp;now=1271686009477" salign="" allowscriptaccess="always" allowfullscreen="false" menu="true" devicefont="false" scale="showall" loop="true" play="true" quality="high" src="http://cdn.gigya.com/Wildfire/swf/Gigya.Socialize.Login_en.swf" name="componentDiv_Gigya.Socialize.Login_en" wmode="transparent" id="componentDiv_Gigya.Socialize.Login_en"/>
	</form>';



	


return $showop;


}
function openid_index()
{
 global $gSitePath,$user,$gDocPath,$base_root;
header('X-XRDS-Location:".$gSitePath."sites/all/modules/openids/yadis.xrdf');


session_start();

if (isset($_GET['openid_mode'])) {

    if(!isset($_SESSION['loggedin'],$_SESSION['username']) || $_SESSION['username'] == ''){
        header("Location: login.php");
        exit;
    }    
}


print_r($_SESSION);

echo $_SESSION['openid_url'];

$message  = "Welcome, ";
$message .= ($_SESSION['loggedin'])?$_SESSION['username']:"guest";
$message .= "!<br /><br />";
$message .= ($_SESSION['loggedin'])?'<a href="logout.php">Log Out</a>':'<a href="login.php">Log In</a>';

return $message;
}
?>