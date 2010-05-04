<?php
function openid_login()
{
 global $gSitePath,$user,$gDocPath,$base_root;


$shwrpx=$_REQUEST['msg'];


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


//echo $showop='<iframe src="'.$gSitePath.'dope-openid-1.0.1/login.php" width="800" height="900"  scrolling="no"></iframe>';


return $shwrpx;


}




function openid_login2()
{
 global $gSitePath,$user,$gDocPath,$base_root;
 $showops=print_r($_GET);
$showops.=print_r($_POST);

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
          
            vidoop: {
                name: \'Vidoop\',
                label: \'Your Vidoop username\',
                url: \'http://{username}.myvidoop.com/\'
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
                box = this.getBoxHTML(this.providers.small[id], \'small\', \'.jpg\');
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
<!--		<form name="openid_form" id="openid_form" action="'.$gSitePath.'dope-openid-1.0.1/login.php" method="post" autocomplete="off">-->
		
		<form name="openid_form" id="openid_form" action="'.$gSitePath.'login.php" method="post" autocomplete="off">
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






//return $showops;




}
function openid_login_save()
{
global $gSitePath,$user,$gDocPath,$base_root;
//$formret=print_r($_GET);

if($_GET['gender']=='m')
$gender='1';
else
$gender='2';
$pass=$_GET['UID'];
$dob=$_GET['birthDay']."/".$_GET['birthMonth']."/".$_GET['birthYear'];
if($_GET['provider']=='facebook')
{
$prolink=$_GET['profileURL'];
$prolink2='';
}
elseif($_GET['provider']=='twitter')
{
$prolink='';
$prolink2=$_GET['profileURL'];

}
else
{

$prolink='';
$prolink2='';
}
//echo "SELECT COUNT(*) from users where name='".$_GET['UID']."' and provider='".$_GET['provider']."'";

$uname=substr($_GET['provider'].$_GET['UID'],0,25);
$select_user_count = db_result(db_query("SELECT COUNT(*) from users where name='".$uname."' and provider='".$_GET['provider']."'"));

if($select_user_count==0)
{
	 $insert="insert into users (name,pass,mail,provider,created,access,login,status)values('".$uname."','".md5($pass)."','".$_GET['email']."','".$_GET['provider']."','".time()."','".time()."','".time()."','1') ";
	$insersult=db_query($insert);
	echo $lid=mysql_insert_id();
	if($_GET['email']=='')
	{
	$lnk=$lid.'@heardmentality.com';
	 $updates="update users set mail='$lnk' where uid=$lid";
	$up=db_query($updates);
	}
	$insert_profile="insert into user_profile (uid,real_name,first_name,last_name,gender,zip,country,facebook,twitter,dob,image_url,provider)values('".$lid."','".$_GET['nickname']."','".$_GET['firstName']."' ,'".$_GET['lastName']."' ,'".$gender."','".$_GET['zip']."','".$_GET['country']."','".$prolink."','".$prolink2."','".$dob."','".$_GET['photoURL']."','".$_GET['provider']."'  ) ";
	
	$insersult=db_query($insert_profile);
	
	}
	//echo $pass;
	//echo md5($pass);
	
	//echo $uname;
	//echo $pass;
	$formret.='<form action="'.$gSitePath.'user/login" method="post" id="user-login">
			<input type="hidden" maxlength="60" name="name" id="edit-name" size="60" value='.$uname.' class="form-text required"/>
			<input type="password" name="pass" id="edit-pass" value='.$pass.'  maxlength="128"  size="60" style="display:none";  class="form-text required"/>
			<input type="hidden" name="form_id" id="edit-user-login" value="user_login"/>
			
			</form>
			<script language="JavaScript" type="text/javascript">
			
			document.getElementById(\'user-login\').submit();
			
			
			</script>
			';
	
	
	
	
	
	
	
return $formret;


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