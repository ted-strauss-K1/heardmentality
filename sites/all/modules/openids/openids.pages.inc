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

	$pass=$_GET['UID'];
	//print_r($_REQUEST);
	
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
	
	
	/////////////////////NEW USER//////////////////////////////
	$select_user_count = db_result(db_query("SELECT COUNT(*) from users where Identity='".$pass."' and provider='".$_GET['provider']."'"));
	
	if($select_user_count==0)
	{
	 $insert="insert into users (pass,mail,provider,created,access,login,status,Identity)values('".md5($pass)."','".$_GET['email']."','".$_GET['provider']."','".time()."','".time()."','".time()."','1','".$pass."') ";
	$insersult=db_query($insert);
	$lid=mysql_insert_id();
	
	
	if($_GET['nickname']!='')
	{
	
	$uname = str_replace(" ", "", $_GET['nickname']);
	echo $onlyconsonants;
	}
	else
	{
	$uname="user".$lid;
	
	}
	
	
	
	/////////////////update user name/////////////////////////
	
	$updates="update users set name='$uname' where uid=$lid";
	$up=db_query($updates);
	
	
	
	
	
	
	/////////////insert into new profile user///////////////
	
	$insert_profile="insert into user_profile (uid,real_name,first_name,last_name,gender,zip,country,facebook,twitter,dob,image_url,provider)values('".$lid."','".$_GET['nickname']."','".$_GET['firstName']."' ,'".$_GET['lastName']."' ,'".$gender."','".$_GET['zip']."','".$_GET['country']."','".$prolink."','".$prolink2."','".$dob."','".$_GET['photoURL']."','".$_GET['provider']."'  ) ";
		$insersult=db_query($insert_profile);
		
		
		
		
		$formret.='<form action="'.$gSitePath.'user/login" method="post" id="user-login">
			<input type="hidden" maxlength="60" name="name" id="edit-name" size="60" value='.$uname.' class="form-text required"/>
			<input type="password" name="pass" id="edit-pass" value='.$pass.'  maxlength="128"  size="60" style="display:none";  class="form-text required"/>
			<input type="hidden" name="form_id" id="edit-user-login" value="user_login"/>
			
			</form>
			<script language="JavaScript" type="text/javascript">
			
			document.getElementById(\'user-login\').submit();
			
			
			</script>
			';
		
		
		
		
		
	}
	else
	{
	  $result_profile_edit_promt = db_query("UPDATE {users} set prompt='1'where Identity='".$pass."' and provider='".$_GET['provider']."' ");
	$select_user_list = db_fetch_object(db_query("SELECT * from users where Identity='".$pass."' and provider='".$_GET['provider']."'"));
	 $unamelog=$select_user_list->name;
	 $passlog=$_GET['UID'];
 
	
		$formret.='<form action="'.$gSitePath.'user/login" method="post" id="user-login">
			<input type="hidden" maxlength="60" name="name" id="edit-name" size="60" value='.$unamelog.' class="form-text required"/>
			<input type="password" name="pass" id="edit-pass" value='.$passlog.'  maxlength="128"  size="60" style="display:none";  class="form-text required"/>
			<input type="hidden" name="form_id" id="edit-user-login" value="user_login"/>
			
			</form>
			<script language="JavaScript" type="text/javascript">
			
			document.getElementById(\'user-login\').submit();
			
			
			</script>
			';

	
	
	
	
	
	}

	
	/*$formret='<script type="text/javascript">
	</script>
	
	<div id="desktopNavbar">
	<ul>        
	<li><a title="Add  Question" id="advanced1" class="advanced1" rel="width:850,height:570" href="http://192.9.200.10/heardmentality/question/add/">Add  Question</a>            
	</li>
	</ul>	
	</div>
	';*/
	
	
	

	
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
function welcome_page()
{
global $gSitePath,$user,$gDocPath,$base_root;

    //print_r($_REQUEST);
    $uid = $user->uid;
    $bio = '';
    $real_name = '';
    $gender = '';
    $optionlist = '';
    $image = 'noimage.jpg';
    $zip = '';
    $country = '';
    $slant = '';
    $religion = '';
    $ethnic = '';
    $facebook = '';
    $twitter = '';
    $check1 = '';
    $check2 = '';
    $question_privacy = '';
    $dob = '';
    
    if ($_REQUEST['update'] == 'Update') {
        extract($_REQUEST);
       

        
        if (isset($_FILES)) {

            
            $return = event_photo_profile();
            //print_r($return);
            $insimage = $return['image'];
            $flag = $return['flag'];
            $suc = $return['suc'];

        
        }
        
        $chk = db_query("select * from {user_profile} where uid='$user->uid'");
        $chk1 = db_result($chk);
        $result_profile = db_fetch_object($chk);
        
       

            $update_user=db_query("update {users} set mail='$mail' ,notify_etype='$ntype',notify_itype='$nitype' where uid='$user->uid' ");

            $result = db_query("UPDATE {user_profile} set uid='$user->uid',real_name='$rname',gender='$gender',image='$insimage',bio=' $bio',zip='$zip',country='$country',religion='$religion',ethnic='$ethnic',dob='$dob',slant='$slant',facebook='$facebook',twitter='$twitter',question_privacy='$qrset',first_name='$fname',last_name='$lname' where uid='$user->uid' ");
			
			$sel_ulists="select * from {user_profile} where uid='$user->uid'";
		$rs_umlogs=db_query($sel_ulists);
		$user_namelistfs=db_fetch_object($rs_umlogs);
		
			if(($user_namelistfs->religion!='')&&($user_namelistfs->ethnic!='')&&($user_namelistfs->slant!='')&&($user_namelistfs->dob!='')&&($user_namelistfs->gender!='')&&($user_namelistfs->zip!=''))
			{
			 $result_profile_edit = db_query("UPDATE {users} set profile_edit='1' where uid='$user->uid' ");

			
			}
			
			
			
			
			
			
        
       
        if ($result) {
            $sucflag = '';
            $sucflag = 1;
           $message = 'Profile Updated Successfully!';
        
        }
        

    
    }
    
    $get_cn = db_query("select * from {user_profile} as a, {users} as b where a.uid='$user->uid' and b.uid='$user->uid'");
    $result = db_fetch_array($get_cn);
	
    extract($result);
   
    drupal_add_js(drupal_get_path('module', 'profile').'/js/en.js');
    drupal_add_js(drupal_get_path('module', 'profile').'/js/formcheck.js');
    drupal_add_css(drupal_get_path('module', 'profile').'/theme/classic/formcheck.css');
    //geoname
    $options = array('sortby'=>'countryname', 'sortorder'=>'ASC');
    $result = geonames_query('countryinfo', NULL, $options);
    foreach ($result->results as $countries) {
        $select = '';
        if ($country == $countries['countrycode']) {
            $select = "SELECTED='SELECTED'";
        }
        
        $optionlist .= sprintf('<option %s value="%s">%s</option>', $select, $countries['countrycode'], $countries['countryname']);
    }
	//echo $user->notify_type;
    if($user->notify_etype==1){
		$checkm="checked='checked'";
	}
	
	if($user->notify_itype==1){
			$checkf="checked='checked'";
		
	}
    if ($gender == 1) {
        $check1 = "checked='checked'";
    } elseif ($gender == 2) {
        $check2 = "checked='checked'";
    
    }
 //////////////////question privacy/////////////////////////

     if($question_privacy==1)
	 {
	 $selm = "checked='checked'";
	 }
	 elseif($question_privacy==2)
	 {
	  $selm2= "checked='checked'";
	 
	 }
	 elseif($question_privacy==3)
	 {
	  $selm3 = "checked='checked'";
	 
	 }
	 elseif($question_privacy==4)
	 {
	  $selm4 = "checked='checked'";
	 }
	 //////////////////religion/////////////////////////
      if($religion=='Christian')
	 {
	 $selr1 = "selected='selected'";
	 }
	 elseif($religion=='Muslim')
	 {
	  $selr2= "selected='selected'";
	 
	 }
	 elseif($religion=='Jewish')
	 {
	  $selr3 = "selected='selected'";
	 
	 }
	 elseif($religion=='Hindu')
	 {
	  $selr4 = "selected='selected'";
	 }
      elseif($religion=='Buddhist')
	 {
	  $selr5 = "selected='selected'";
	 }
	  elseif($religion=='Other')
	 {
	  $selr6 = "selected='selected'";
	 }
 //////////////////ethinicity/////////////////////////
 
	if($ethnic=='Caucasian')
	{
	$sele1 = "selected='selected'";
	}
	elseif($ethnic=='Black')
	{
	$sele2= "selected='selected'";
	
	}
	elseif($ethnic=='Asian')
	{
	$sele3 = "selected='selected'";
	
	}
	elseif($ethnic=='Indian')
	{
	$sele4 = "selected='selected'";
	}
	elseif($ethnic=='Semetic')
	{
	$sele5 = "selected='selected'";
	}
	elseif($ethnic=='Latin')
	{
	$sele6 = "selected='selected'";
	}
	elseif($ethnic=='Aborigines')
	{
	$sele7 = "selected='selected'";
	}
	if($slant =='Left')
	{
	$seleant1 = "selected='selected'";
	}
	elseif($slant =='Right')
	{
	$seleant2= "selected='selected'";
	
	}
	elseif($slant =='Center')
	{
	$seleant3 = "selected='selected'";
	
	}

	$op='<script type="text/javascript">
var spath=\''.$gSitePath.'\';
</script><script src="'.$gSitePath.'sites/all/modules/profile/js/profile.js" type="text/javascript"></script><script src="'.$gSitePath.'sites/all/modules/openids/js/validate.js" type="text/javascript"></script>
		<link type="text/css" rel="stylesheet" href="'.$gSitePath.'sites/all/modules/openids/css/log.css" /><div id="container">
   <form name="reg" id="reg"    method="post" enctype="multipart/form-data">
    <div class="info">
	 <input type="text" class="hidden_box1" readonly="true" border="0" width="1" size="1" name="errbox" id="errbox"><div id="err_div" class="warningMessage">'.$emsg.' '.$message.'</div>
    </div>
    <ul>
    <fieldset>
	 <legend><b><i> Basic Info</i></b> </legend>
	
	 <li id="foli0" class="firstName">
	<label class="desc" id="title0" for="Field0">
	First Name
	&nbsp;&nbsp;&nbsp;Last Name
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Real Name
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Email
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;DOB
	</label>
   
    <span>
    <input id="fname" name="fname" class="field text" value="'.$first_name.'" size="8" tabindex="2" type="text">
   <input id="lname" name="lname" class="field text" value="'.$last_name.'" size="12" tabindex="3" type="text">
    <input id="rname" name="rname" class="field text" value="'.$real_name.'" tabindex="4" type="text"> 
       <input id="edit-mail" name="mail" class="field text " value="'.$mail.'" maxlength="255" tabindex="5" type="text"> 
	   <input name="dob"  value="'.$dob.'"  id="dob" class="field text "  tabindex="5" type="text">
    </span>
     
  
    

    </li>
	  </fieldset>		
	 <fieldset>
	 <legend><b><i> Personal Info</i></b> </legend>
  <li id="foli14" class="">
			<label class="desc" id="title14" for="Field14"> 
			Gender
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Country 
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Religion :'.$religion.'
			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Ethnicity: '.$ethnic.'
			&nbsp;&nbsp;Slant: '.$slant.'
			</label> 
	<label class="option" for="edit-gender-0"><input id="edit-gender-0" name="gender" value="1" class="form-radio" '.$check1.' type="radio"> Male</label>
	<label class="option" for="edit-gender-1"><input id="edit-gender-1" name="gender" value="2" class="form-radio" '.$check2.' type="radio"> Female</label> 
       <select name="country" style="width: 125px;" tabindex="16" id="edit-country">'.$optionlist.'</select> 
		 <select  name="religion" id="edit-religion" class="form-text" ><option value="" >Select</option><option value="Christian" '.$selr1.' >Christian (Cath or Prod)</option><option value="Muslim" '.$selr2.' >Muslim (Suni Shiite)</option><option value="Jewish" '.$selr3.' >Jewish</option><option value="Hindu" '.$selr4.' > Hindu</option><option value="Buddhist" '.$selr5.' >Buddhist</option><option value="Other" '.$selr6.'>Other</option></select> 
		<select name="ethnic" id="edit-ethnic" class="form-text" ><option value="">Select </option><option value="Caucasian" '.$sele1.'>Caucasian</option><option value="Black" '.$sele2.'>Black</option><option value="Asian" '.$sele3.'>Asian</option> <option value="Indian" '.$sele4.'>Indian</option> <option value="Semetic" '.$sele5.'>Semetic</option><option value="Latin" '.$sele6.'>Latin</option> <option value="Aborigines" '.$sele7.'>Aborigines</option>  </select>
		<select name="slant" id="edit-slant"  class="form-text" ><option value="">Select</option><option value="Left" '.$seleant1.'>Left</option><option value="Right" '.$seleant2.'>Right </option> <option value="Center" '.$seleant3.'>Center </option>  </select>
	       
			 </li>
  
    <li id="foli14" class="">
	<label class="desc" id="title14" for="Field14"> 
	Image
	</label> 
	
	 <input type="file" name="image" id="image" /> <img src="'.$gSitePath.drupal_get_path('module', 'profile').'/snap/'.$image.'" align="absmiddle" alt="Profile Image" >
				<input type="hidden" name="oldimg" value="'.$image.'"/>
	 </li>
	  <li id="foli14" class="">
	<label class="desc" id="title14" for="Field14"> 
	Zipcode
	</label> 
	 <input name="zip"  value="'.$zip.'"  onblur="get_zip_city(this.value);" id="edit-zip"  class="field text" type="text">
	 <div class="form-item" id="edit-city-wrapper">'.$statecity.' </div>
	 </li>
	</fieldset>	
	
	 <fieldset>
		<legend><b><i>Question & Resource Privacy Settings</i></b> </legend>
		<div class="form-item" id="edit-name-wrapper">
            <label for="edit-"></label>
             <input type="radio" name="qrset"  class="qrset" value="1" '.$selm.'>&nbsp;Always Post Non-Anonymous
            <div class="description"></div>
        </div>
        <div class="form-item" id="edit-name-wrapper">
            <label for="edit-"></label>
             <input type="radio" name="qrset" class="qrset" value="2" '.$selm2.'>&nbsp;Only allow Followers & Followees to see
            <div class="description"></div>
        </div>
         <div class="form-item" id="edit-name-wrapper">
            <label for="edit-"></label>
             <input type="radio" name="qrset" class="qrset"  value="3" '.$selm3.'>&nbsp;Only Post Anonymous
            <div class="description"></div>
        </div>
        <div class="form-item" id="edit-name-wrapper">
            <label for="edit-"></label>
             <input type="radio" name="qrset" class="qrset"  value="4" '.$selm4.'>&nbsp;Prompt on all (if prompt all, pop up to ask if he wants to share with
everyone or just followers or not at all while adding a question)
            <div class="description"></div>
        </div>
		
		  <div class="form-item" id="edit-name-wrapper">
            <label for="edit-"><b>Notify Type </b></label>
             <input name="ntype" type="checkbox" '.$checkm.'  value="1"  /> E-mail    <input name="nitype" type="checkbox" '.$checkf.'  value="1"  /> Internal  Message Only
           
			<div class="description"></div>
        </div>
        </fieldset>		
	
	
	
    <li class="buttons">
    <input type="submit" name="update" value="Update" onclick="return validate_reg();">
	
    </li>
    </ul>
    </form>
	
    </div>
';	

echo $op;


}

function event_photo_profile() {
    global $objSmarty,$config;
    $return = array();
    $filename = $_FILES['image']['name'];// file up starts
    $tmp_image = $_FILES['image']['tmp_name'];
    if ($filename != '') {
        include drupal_get_path('module', 'profile')."/img_resize.php";
        $ext = strtolower(substr($filename, strpos($filename, '.'), strlen($filename) - 1));
        
        if ($ext == '.jpg' || $ext == '.gif' || $ext == '.jpeg') {
            $imagefun = new SimpleImage();
            
            $image = time().$filename;
            
            $path = drupal_get_path('module', 'profile')."/snap/";
            copy($tmp_image, $path.$image);
            //img resize
            $sz = getimagesize($path.$image);
            
            $x = $sz[0]; // org image width
            $y = $sz[1]; // org image height
            if ($x > 100) {
                $imagefun->load($path.$image);
                
                $imagefun->resizeToWidth(100);
                
                $imagefun->save($path.$image);
            
            }

            
            if ($image != "") {
                $insimage = $image;
                //include('round_corner.php');
            }
        } else {
            $flag = 1;
            $suc = ' Sorry Image Cant Uploaded It Should be gif or Jpeg format!';
        }
    } elseif (isset($_REQUEST['oldimg'])) {
        $insimage = $_REQUEST['oldimg'];
        $flag = 0;
    } else {
        $flag = 0;
        $insimage = "noimage.jpg";
    }//file up ends
    
    $return['image'] = $insimage;
    $return['flag'] = $flag;
    $return['suc'] = $suc;
    return $return;
}











?>