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
//print_r($_GET);
  extract($_REQUEST);

	
if($_GET['gender']=='m')
$genderl='1';
else
$genderl='2';
if ($gender == 'm') {
$check1 = "checked='checked'";
} elseif ($gender == 'f') {
$check2 = "checked='checked'";

}
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
	
	
	
	
	//echo $gender;
	
	$select_user_count = db_result(db_query("SELECT COUNT(*) from users where Identity='".$UID."' and provider='".$provider."'"));
	$select_user_name = db_result(db_query("SELECT COUNT(*) from users where name='".$uname."' "));
	if($select_user_count==0)
{
	if($saveForm!='')
	{
	
	
	if($select_user_name==0)
	{
	$insert="insert into users (name,pass,mail,provider,created,access,login,status,Identity,hidden_pass)values('".$uname."','".md5($pass1)."','".$email."','".$provider."','".time()."','".time()."','".time()."','1','".$UID."','".$pass1."') ";
	$insersult=db_query($insert);
	$lid=mysql_insert_id();
	if($_COOKIE["faceid"]!='')
	{
	//////////////////////faceboook friends////////////////////////////////
	$insertface="insert into facebook_friends (uid,face_uid)values('".$_COOKIE['faceid']."','".$lid."') ";
	$insersult=db_query($insertface);
	
	
	///////////////////////// follower list///////////
	
	$ins_commg="insert into   follower (uid,follower_id,follower_status,joindate) values('".$lid."' ,'".$_COOKIE['faceid']."','1','".date('Y-m-d')."') ";
	$rs_commg=db_query($ins_commg);
	
	$query_pt= "SELECT * FROM tbl_points where id='6' "; 
	$query_ptinfo=db_query($query_pt);
	$fetuserpts=db_fetch_object($query_ptinfo);
	$ins_commg="insert into   tbl_user_points (uid,point_id,points,vote_point_id) values('".$_COOKIE['faceid']."' ,'6',$fetuserpts->points,'0') ";
	$rs_commg=db_query($ins_commg);
	setcookie("friend_id", '0');
	$sel_ulist = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='".$lid."'";
	$rs_umlog=db_query($sel_ulist);
	$user_namelistf=db_fetch_object($rs_umlog);
	
	$sel_ulists = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='".$_COOKIE['faceid']."'";
	$rs_umlogs=db_query($sel_ulists);
	$user_namelistfs=db_fetch_object($rs_umlogs);
	if($user_namelistfs->notify_itype==1)
	{
	$insert_notify=db_query("insert into notification (uid,new_followe,is_user,node_id) values('".$_COOKIE['faceid']."','1','1','".$lid."') ");
	}
	if($user_namelistfs->notify_etype==1)
	{
	$subject='You Got new Follower in Heardmenatlity ';
		
	
	$sel_user_cmt="SELECT * FROM notification_mail_format Where id='2'";
	$rs_mgmt=db_query($sel_user_cmt);
	$list_content=db_fetch_object($rs_mgmt);
	$contentm=str_replace("#uname#",$user_namelistf->name,$list_content->content);
	$contentm.= str_replace("#anothername#",$user_namelistfs->name,$contentm);
	// $contentm;
	
	$mail_success = htmlmail_function($user_namelistfs->email,$subject,$contentm,$from,'');
	
	
	}
	
	
	
	
	
	
	
	
	
	setcookie("faceid");
	
	}
	
	
	$insert_profile="insert into user_profile (uid,real_name,first_name,last_name,gender,zip,country,facebook,twitter,dob,image_url,provider)values('".$lid."','".$_GET['nickname']."','".$firstName."' ,'".$lastName."' ,'".$genderl."','".$zip."','".$country."','".$prolink."','".$prolink2."','".$dob."','".$_GET['photoURL']."','".$_GET['provider']."'  ) ";
	
	$insersult=db_query($insert_profile);
	$select_fet = db_query("SELECT * from users where Identity='".$UID."' and provider='".$provider."'");
	$prouser=db_fetch_object($select_fet);
	//echo $prouser->name;
	$formret='<form action="'.$gSitePath.'user/login" method="post" id="user-login">
			<input type="hidden" maxlength="60" name="name" id="edit-name" size="60" value="'.$prouser->name.'" class="form-text required"/>
			<input type="password" name="pass" id="edit-pass" value="'.$prouser->hidden_pass.'"  maxlength="128"  size="60" style="display:none";  class="form-text required"/>
			<input type="hidden" name="form_id" id="edit-user-login" value="user_login"/>
			
			</form>
			<script language="JavaScript" type="text/javascript">
			
			document.getElementById(\'user-login\').submit();
			
			
			</script>
			';
	}
	else
	{
	$emsg='User Name Already Exist';
	}
	
	
	}
	
$formret.='<script src="'.$gSitePath.'sites/all/modules/openids/js/validate.js" type="text/javascript"></script>
		<link type="text/css" rel="stylesheet" href="'.$gSitePath.'sites/all/modules/openids/css/log.css" /><div id="container">
   <form name="reg" id="reg"    method="post" enctype="multipart/form-data">
    <div class="info">
    <h2> Registration</h2>
	 <input type="text" class="hidden_box1" readonly="true" border="0" width="1" size="1" name="errbox" id="errbox"><div id="err_div" class="warningMessage">'.$emsg.'</div>
    </div>
    <ul>
    <li id="foli0" class="name">
    <label class="desc" id="title0" for="Field0">
    Name
    <span id="req_0" class="req">*</span>
    </label>
    <span>
    <input id="uname" name="uname" class="field text" value="" size="10" tabindex="1" type="text">
    <label for="Field0">User Name</label>
    </span>
   
    
    </li>
	
	 <li id="foli0" class="firstName">
    <label class="desc" id="title0" for="Field0">
   First Name
  
    </label>
   
    <span>
    <input id="firstName" name="firstName" class="field text" value="'.$firstName.'" size="8" tabindex="2" type="text">
   
    </span>
    
    </li>
	 <li id="foli0" class="lastName">
    <label class="desc" id="title0" for="Field0">
   Last Name
  
    </label>
   
    <span>
    <input id="lastName" name="lastName" class="field text" value="'.$lastName.'" size="12" tabindex="3" type="text">
   
    </span>
    
    </li>
	
    <li id="foli11" class="">
    <label class="desc" id="title11" for="Field11">
    Password
    <span id="req_11" class="req">*</span>
    </label>
    <div>
    <input id="pass1" name="pass1" class="field text medium" value="" maxlength="255" tabindex="11" type="password"> 
    </div>
	<label class="desc" id="title11" for="Field11">
   Confirm Password
    <span id="req_11" class="req">*</span>
    </label>
    <div>
    <input id="pass2" name="pass2" class="field text medium" value="" maxlength="255" tabindex="11" type="password"> 
    </div>
    <label class="desc" id="title11" for="Field11">
    Email
    <span id="req_11" class="req">*</span>
    </label>
    <div>
    <input id="email" name="email" class="field text medium" value="'.$email.'" maxlength="255" tabindex="11" type="text"> 
    </div>
	</li>
    <li id="foli14" class="">
    <label class="desc" id="title14" for="Field14">
   Real Name
    </label>
    <div>
    <input id="nickname" name="nickname" class="field text medium" value="'.$nickname.'" maxlength="255" tabindex="11" type="text"> 
    </div>
    </li>
   
	 <li id="foli14" class="">
    <label class="desc" id="title14" for="Field14">
  Gender
    </label>
    <div>
    <label class="option" for="edit-gender-0"><input id="edit-gender-0" name="gender" value="m" class="form-radio" '.$check1.' type="radio"> Male</label>
	<label class="option" for="edit-gender-1"><input id="edit-gender-1" name="gender" value="f" class="form-radio" '.$check2.' type="radio"> Female</label>
    </div>
    </li>
    <li class="buttons">
    <input id="saveForm" name="saveForm" class="btTxt submit" value="Submit" type="submit" onclick="return validate_reg();">
	
    </li>
    </ul>
    </form>
    </div>
';	

	}
	else
	{
	$select_fet = db_query("SELECT * from users where Identity='".$UID."' and provider='".$provider."'");
	$prouser=db_fetch_object($select_fet);
	//echo $prouser->name;
	//echo md5('veni');
	$formret.='<form action="'.$gSitePath.'user/login" method="post" id="user-login">
			<input type="hidden" maxlength="60" name="name" id="edit-name" size="60" value='.$prouser->name.' class="form-text required"/>
			<input type="password" name="pass" id="edit-pass" value="'.$prouser->hidden_pass.'"  maxlength="128"  size="60" style="display:none";  class="form-text required"/>
			<input type="hidden" name="form_id" id="edit-user-login" value="user_login"/>
			
			</form>
			<script language="JavaScript" type="text/javascript">
			
			document.getElementById(\'user-login\').submit();
			
			
			</script>
			';
	
	}
	
	
	
return $formret;


}
function openid_login3()
{
 global $gSitePath,$user,$gDocPath,$base_root;
$select_fet = db_query("SELECT * from users order by uid desc limit 0,1");
	$prouser=db_fetch_object($select_fet);
	
	$ouptii='<form action="'.$gSitePath.'user/login" method="post" id="user-login">
			<input type="hidden" maxlength="60" name="name" id="edit-name" size="60" value='.$prouser->name.' class="form-text required"/>
			<input type="password" name="pass" id="edit-pass" value="'.$prouser->hidden_pass.'"  maxlength="128"  size="60" style="display:none";  class="form-text required"/>
			<input type="hidden" name="form_id" id="edit-user-login" value="user_login"/>
			
			</form>
			<script language="JavaScript" type="text/javascript">
			
			document.getElementById(\'user-login\').submit();
			
			
			</script>
			';
return $ouptii;

}
function friends_answers()
{
global $gSitePath,$user,$gDocPath,$base_root;

$listans = '<div>';
$sel_count = db_result(db_query("SELECT COUNT(*) from facebook_friends as a,possible_answer_vote as b,question as c   where a.uid=$user->uid and a.face_uid=b.uid and b.qid=c.qid "));
//echo "select * from facebook_friends as a,possible_answer_vote as b,question as c   where a.uid=$user->uid and a.face_uid=b.uid and b.qid=c.qid ";
 $selmrq=db_query("select * from facebook_friends as a,possible_answer_vote as b,question as c   where a.uid=$user->uid and a.face_uid=b.uid and b.qid=c.qid ");
while($in_list=db_fetch_object($selmrq))
{
    $numran = db_result(db_query("SELECT COUNT(*) from {possible_answer_vote} where qid='".$in_list->qid."' and uid='".$in_list->face_uid."'"));

	$listans.='<li> <a href="'.$gSitePath.''.$in_list->url.'">'.$in_list->question.' </a> </li>';
	$vans = "select * from {possible_answer} where  qid='".$in_list->qid."'order by vote desc";
	
	$vlist = db_query($vans);
	 while ($vlistquest = db_fetch_object($vlist)) {
	// echo $in_list->panswer_id;
	  $chk = '';
	  if ($in_list->panswer_id == $vlistquest->paid) {
                
                $chk = "checked";
            }
	$listans.='<div><input name="answer_al.'.$in_list->qid.'" type="radio" '.$chk.'  value="'.$vlistquest->paid.'" />
	'.$vlistquest->answer.'</div>';
  }
}
if($sel_count==0)
{
$listans.='No Question answered by Your Facebook Friends';

}
$listans.= '</div>';
return $listans;







}

?>