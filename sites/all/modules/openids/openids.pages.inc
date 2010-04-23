<?php
function openid_login()
{
 global $gSitePath,$user,$gDocPath,$base_root;



/*echo '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<title>Dope OpenID Demo: Log In</title>
	<meta http-equiv="content-type" content="text/html;charset=utf-8" />
	<meta http-equiv="Content-Style-Type" content="text/css" />
      <link type="text/css" rel="stylesheet" href="'.$gSitePath.'sites/all/modules/openids/css/openid.css" />
     <script type="text/javascript" src="'.$gSitePath.'sites/all/modules/openids/js/core.js"></script>
    <script type="text/javascript" src="'.$gSitePath.'sites/all/modules/openids/js/more.js"></script>
    <script type="text/javascript" src="'.$gSitePath.'sites/all/modules/openids/js/openid.js"></script>
	<meta http-equiv="content-type" content="text/html;charset=utf-8" />
	<meta http-equiv="Content-Style-Type" content="text/css" />
     <script type="text/javascript">
        window.addEvent(\'domready\', function(){
            new OpenIdSelector(\'openid_identifier\');
        });
    </script>
</head>

<body>

	<form name="openid_form" id="openid_form" action="'.$gSitePath.'dope-openid-1.0.1/login.php" method="post" autocomplete="off">
		
		<label>
			OpenID URL: <input type="text" name="openid_identifier" id="openid_identifier" maxlength="320" />
		</label>
		
		<input type="hidden" name="process" value="1" />

        
         
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
</html>';*/


echo $showop='<iframe src="'.$gSitePath.'dope-openid-1.0.1/login.php" width="800" height="900"  scrolling="no"></iframe>';





}




function openid_login2()
{
 global $gSitePath,$user,$gDocPath,$base_root;



$showops= '<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<title>Dope OpenID Demo: Log In</title>
	<meta http-equiv="content-type" content="text/html;charset=ANSI" />
	<meta http-equiv="Content-Style-Type" content="text/css" />
    <link rel="stylesheet" href="'.$gSitePath.'sites/all/themes/heardmentality/css/content.css" type="text/css" />
       <link type="text/css" rel="stylesheet" href="'.$gSitePath.'sites/all/modules/openids/css/openid.css" />
	    <script type="text/javascript" src="'.$gSitePath.'sites/all/modules/openids/js/core.js"></script>
	    <script type="text/javascript" src="'.$gSitePath.'sites/all/modules/openids/js/more.js"></script>
   
  
	
    <script type="text/javascript">
	
	
	
var OpenIdProviders = new Class({

        all: {},

        large: {
            google: {
                name: \'Google\',
                url: \'https://www.google.com/accounts/o8/id\'
            },
            yahoo: {
                name: \'Yahoo\',      
                url: \'http://me.yahoo.com/\'
            },    
            aol: {
                name: \'AOL\',    
                label: \'Enter your AOL screenname.\',
                url: \'http://openid.aol.com/{username}/\'
            },
            openid: {
                name: \'OpenID\',    
                label: \'Enter your OpenID.\',
                url: null
            }
        },

        small: {
                myopenid: {
                name: \'MyOpenID\',
                label: \'Enter your MyOpenID username.\',
                url: \'http://{username}.myopenid.com/\'
            },
            livejournal: {
                name: \'LiveJournal\',
                label: \'Enter your Livejournal username.\',
                url: \'http://{username}.livejournal.com/\'
            },
         
            wordpress: {
                name: \'Wordpress\',
                label: \'Enter your Wordpress.com username.\',
                url: \'http://{username}.wordpress.com/\'
            },
            blogger: {
                name: \'Blogger\',
                label: \'Your Blogger account\',
                url: \'http://{username}.blogspot.com/\'
            },
            verisign: {
                name: \'Verisign\',
                label: \'Your Verisign username\',
                url: \'http://{username}.pip.verisignlabs.com/\'
            },
            vidoop: {
                name: \'Vidoop\',
                label: \'Your Vidoop username\',
                url: \'http://{username}.myvidoop.com/\'
            },
            verisign: {
                name: \'Verisign\',
                label: \'Your Verisign username\',
                url: \'http://{username}.pip.verisignlabs.com/\'
            },
            claimid: {
                name: \'ClaimID\',
                label: \'Your ClaimID username\',
                url: \'http://claimid.com/{username}\'
            }
        },

        initialize: function(){
                this.all = $merge(this.large, this.small);
        }
});

var OpenIdSelector = new Class({
							   

        cookie_expires: 6*30, // 6 months.
    cookie_name: \'openid_provider\',
    cookie_path: \'/\',

    img_path: \''.$gSitePath.'sites/all/modules/openids/images/\',

    input_id: null,
    provider_url: null,

    providers: null,

   
    initialize: function(input_id) {

        var openid_btns = $(\'openid_btns\');

        this.input_id  = input_id;
        this.providers = new OpenIdProviders();

        $(\'openid_choice\').setStyle(\'display\', \'block\');
        $(\'openid_input_area\').empty();
      
        for (id in this.providers.large) {
                box = this.getBoxHTML(this.providers.large[id], \'large\', \'.gif\');
                box.inject(openid_btns);
        }

        if (this.providers.small) {
            openid_btns.grab(new Element(\'br\'));
            for (id in this.providers.small) {
                box = this.getBoxHTML(this.providers.small[id], \'small\', \'.jpeg\');
                box.inject(openid_btns);
            }
        }

        $(\'openid_form\').addEvent(\'submit\', this.submit.bind(this));

        var box_id = Cookie.read(this.cookie_name);
        if (box_id !== null) this.signin(box_id, true);
    },

       getBoxHTML: function(provider, box_size, image_ext){
        var box_id = provider.name.toLowerCase();
        var openid = this;
        return  new Element(\'a\', {
                \'href\':  "javascript:void(0);",
                \'title\': provider.name,
            \'class\': box_id + \' openid_\' + box_size + \'_btn\',
            \'styles\': {
                        \'display\': \'block\',
                \'background\': \'#fff url(\' + this.img_path + box_id + image_ext + \') no-repeat center center\'
            },
            \'events\': {
                \'click\': openid.signin.pass(box_id, openid)
				
			   
            }
        });
    },
    signin: function(box_id, onload){

        var provider = this.providers.all[box_id];
        if (!provider) return;

        this.highlight(box_id);

        Cookie.write(this.cookie_name, box_id, {
            duration: this.cookie_expires,
            path: this.cookie_path
        });
       
               if (provider.label) {
            this.useInputBox(provider);
            this.provider_url = provider.url;
        }

        else {
            this.setOpenIdUrl(provider.url);
            if (!onload) $(\'openid_form\').submit();
        }
    },
       submit: function(){
        var url = this.provider_url;
        if (url) {
            url = url.substitute({ \'username\': $(\'openid_username\').get(\'value\') });
            this.setOpenIdUrl(url);
        }
        return true;
    },

    setOpenIdUrl: function(url){

        var hidden = $(this.input_id);

        if (hidden) {
            hidden.set(\'value\', url);
        }
        else {
                $(\'openid_form\').grab(new Element(\'input\', {
                \'type\':  \'hidden\',
                \'id\':    this.input_id,
                \'name\':  this.input_id,
                \'value\': url
                }));
        }
    },
        highlight: function(box_id){
        
        var highlight = $(\'openid_highlight\');
        if (highlight)
            $(\'openid_highlight\').getFirst(\'a\').replaces(highlight);
      
        new Element(\'div\', { \'id\': \'openid_highlight\' }).wraps($$(\'.\' + box_id)[0]);
    },

    useInputBox: function(provider){

        var input_area = $(\'openid_input_area\');

        var html  = \'\';
        var id    = \'openid_username\';
        var value = \'\';
        var label = provider[\'label\'];
        var style = \'\';

        if (label)
                html  = \'<p>\' + label + \'</p>\';

        if (provider[\'name\'] == \'OpenID\') {
            id    = this.input_id;
            value = \'http://\';
            style = \'background: #fff url(\' + this.img_path + \'openid-inputicon.gif) no-repeat scroll 0 50%; padding-left:18px;\';
        }

        html += \'<input id="\'+id+\'" type="text" style="\'+style+\'" name="\'+id+\'" value="\'+value+\'" />\' +
                \'<input id="openid_submit" type="submit" value="Sign-In"/>\';

        input_area.set(\'html\', html);

        $(id).focus();
    }
});

	
	</script>
	
	 <script type="text/javascript">
        window.addEvent(\'domready\', function(){
            new OpenIdSelector(\'openid_identifier\');
        });
	
		
		
		
    </script>
	
	
	
	
</head>

<body>

	<!--<form name="openid_form" id="openid_form" action="'.$gSitePath.'openids/save" method="get" autocomplete="off">-->
		<form name="openid_form" id="openid_form" action="'.$gSitePath.'dope-openid-1.0.1/login.php" method="post" autocomplete="off">
		<label>
			OpenID URL: <input type="text" name="openid_identifier" id="openid_identifier" maxlength="320" />
		</label>
		
		<input type="hidden" name="process" value="1" />

      
         
            <input type="hidden" name="action" value="verify" />

            <div id="openid_choice">
                <p>Please click your account provider:</p>
                <div id="openid_btns">
            </div>
            </div>
            <div id="openid_input_area">
                <input id="openid_identifier" name="openid_identifier" type="text" value="http://" />
                <input id="openid_submit" type="submit" value="Sign-In"/>
            </div>
           
        
        
          
        
	</form>
	

</body>
</html>';
echo $showops;











}
function openid_login_save()
{
//echo $_REQUEST['action'];
session_start();

require 'functions.php';
ini_set('display_errors',1);
if(isset($_SESSION['loggedin']) && $_SESSION['loggedin']){


	
header('X-XRDS-Location:http://localhost/heardmentality/dope-openid-1.0.1/yadis.xrdf');

if (isset($_GET['openid_mode'])) {
	
    if(!isset($_SESSION['loggedin'],$_SESSION['username']) || $_SESSION['username'] == ''){
        header("Location:http://localhost/heardmentality/openids/save");
      
    }    
}
}




if(isset($_POST['process'])){
	
	require 'class.dopeopenid.php';
	
	
	$openid_url = trim($_POST['openid_identifier']);
	
	
	if(function_exists('filter_input')) {
		if( ! filter_input(INPUT_POST, "openid_identifier", FILTER_VALIDATE_URL)) {
			$formret = "Error: OpenID Identifier is not in proper format.";
		}
	}
	else 
	{
		
		if( ! eregi("^((https?)://)?(((www\.)?[^ ]+\.[com|org|net|edu|gov|us]))([^ ]+)?$",$openid_url)) {
			$formret = "Error: OpenID Identifier is not in proper format.";
		}
	}
	
	// Proceed if we made it through without setting $error
	if ( ! isset($error)) {
	
		$_SESSION['openid_url'] = $openid_url;

		$openid = new Dope_OpenID($openid_url);
		
		//$openid->setReturnURL("http://192.9.200.10/heardmentality/dope-openid-1.0.1/login.php?action=verify");
	$openid->setReturnURL("http://localhost/heardmentality/openids/save?action=verify");
		
		//$openid->SetTrustRoot('http://192.9.200.10/heardmentality/');
		$openid->SetTrustRoot('http://localhost/heardmentality/openids/save');
	
		
		$openid->setOptionalInfo(array('dob','nickname','country','language','email'));
		
		
		
		
		$endpoint_url = $openid->getOpenIDEndpoint();
		if($endpoint_url){
			
			$_SESSION['openid_endpoint_url'] = $endpoint_url;
		
			$openid->redirect();
			
			
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
				
				
				if(isset($_SESSION['loggedin']) && $_SESSION['loggedin']){
				
				header('X-XRDS-Location:http://localhost/heardmentality/dope-openid-1.0.1/yadis.xrdf');
				
				if (isset($_GET['openid_mode'])) {
				
				if(!isset($_SESSION['loggedin'],$_SESSION['username']) || $_SESSION['username'] == ''){
				header("Location:http://localhost/heardmentality/openids/save");
				
				}    
				}
				}
			}
			
		}
		else {
		
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
			
				echo " (".$_GET['openid_identity'].")</p>";
			echo "\t<li><b>nickname yahoo</b>: " .  $_REQUEST['openid_ax_value_nickname'] . "</li>";
			
			echo "\t<li><b>yahoo email</b>: " .  $_REQUEST['openid_ax_value_email'] . "</li>";
			echo "\t<li><b>yahoo language -country</b>: " .  $_REQUEST['openid_ax_value_language'] . "</li>";
			echo "<ul>";
			echo "\t<li><b>Nickname</b>: " . $userinfo['nickname'] . "</li>";
			echo "\t<li><b>Language</b>: " . $userinfo['language'] . "</li>";
			echo "\t<li><b>Email</b>: " . $userinfo['email'] . "</li>";
			echo "</ul>";
			$formret= '<form action="http://localhost/heardmentality/user" method="post" id="user-login">
			<input type="hidden" maxlength="60" name="name" id="edit-name" size="60" value="'.$uname.'" class="form-text required"/>
			<input type="password" name="pass" id="edit-pass" value="'.$uname.'"  maxlength="128"  size="60" style="display:none";  class="form-text required"/>
			<input type="hidden" name="form_build_id" id="form-0bb73f903dafa2bf7464d10802fda45b" value="form-0bb73f903dafa2bf7464d10802fda45b"/>
			<input type="hidden" name="form_id" id="edit-user-login" value="user_login"/>
			
			</form>
			<script language="JavaScript" type="text/javascript">
			
			document.getElementById(\'user-login\').submit();
			
			
			</script>
			';
			}
			
            
		
        
          
			
			
		}
	}
	else if ($openid->isError() === TRUE){
		
		$the_error = $openid->getError();
		$formret = "Error Code: {$the_error['code']}<br />";
		$formret .= "Error Description: {$the_error['description']}<br />";
	}
	else{
		
		$formret = "Error: Could not validate the OpenID at {$_SESSION['openid_url']}";
	}	
}
else if (isset($_GET['openid_mode']) && $_GET['openid_mode'] == "cancel") {
	$formret = "OpenID authorization canceled by user.";
}


echo $formret;


}
function openid_login3()
{
 global $gSitePath,$user,$gDocPath,$base_root;
$ouptii='  <link rel="stylesheet" href="'.$gSitePath.'sites/all/themes/heardmentality/css/content.css" type="text/css" /><link type="text/css" rel="stylesheet" href="'.$gSitePath.'sites/all/modules/openids/css/openid.css" />
<script type="text/javascript" src="'.$gSitePath.'sites/all/modules/openids/js/openid-jquery.js"></script>
	<script type="text/javascript">
	jQuery(document).ready(function() {
	    openid.init(\'openid_identifier\');
	});
	</script><form name="openid_form" id="openid_form" action="'.$gSitePath.'openids/save" method="get" autocomplete="off">
		<label>
			OpenID URL: <input type="text" name="openid_identifier" id="openid_identifier" maxlength="320" />
		</label>
		
		<input type="hidden" name="process" value="1" />

      
         
            <input type="hidden" name="action" value="verify" />

            <div id="openid_choice">
                <p>Please click your account provider:</p>
                <div id="openid_btns">
            </div>
            </div>
            <div id="openid_input_area">
                <input id="openid_identifier" name="openid_identifier" type="text" value="http://" />
                <input id="openid_submit" type="submit" value="Sign-In"/>
            </div>
           
        
        
          
        
	</form>';
return $ouptii;

}


?>