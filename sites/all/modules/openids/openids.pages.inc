<?php

function openid_login() {
    global $gSitePath, $user, $gDocPath, $base_root;


    $shwrpx = $_REQUEST['msg'];


    /* echo '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
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
      </html>'; */


    //echo $showop='<iframe src="'.$gSitePath.'dope-openid-1.0.1/login.php" width="800" height="900"  scrolling="no"></iframe>';


    return $shwrpx;
}

function openid_login2() {
    global $gSitePath, $user, $gDocPath, $base_root;
    $showops = print_r($_GET);
    $showops .= print_r($_POST);

    $showops = '<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<title>Dope OpenID Demo: Log In</title>
	<meta http-equiv="content-type" content="text/html;charset=ANSI" />
	<meta http-equiv="Content-Style-Type" content="text/css" />
    <link rel="stylesheet" href="' . $gSitePath . 'sites/all/themes/heardmentality/css/content.css" type="text/css" />
       <link type="text/css" rel="stylesheet" href="' . $gSitePath . 'sites/all/modules/openids/css/openid.css" />
	    <script type="text/javascript" src="' . $gSitePath . 'sites/all/modules/openids/js/core.js"></script>
	    <script type="text/javascript" src="' . $gSitePath . 'sites/all/modules/openids/js/more.js"></script>
   
  
	
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

    img_path: \'' . $gSitePath . 'sites/all/modules/openids/images/\',

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

	<!--<form name="openid_form" id="openid_form" action="' . $gSitePath . 'openids/save" method="get" autocomplete="off">-->
<!--		<form name="openid_form" id="openid_form" action="' . $gSitePath . 'dope-openid-1.0.1/login.php" method="post" autocomplete="off">-->
		
		<form name="openid_form" id="openid_form" action="' . $gSitePath . 'login.php" method="post" autocomplete="off">
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
    //  echo $showops;


    return $showops;
}

function openid_login_save() {
    global $gSitePath, $user, $gDocPath, $base_root;
    //print_r($_COOKIE);
    //echo $_COOKIE["faceidc"];
    $pass = $_GET['UID'];
    //print_r($_REQUEST);

    if ($_GET['gender'] == 'm')
        $gender = '1';
    else if ($_GET['gender'] == 'f') {
        $gender = '2';
    }
    $pass = $_GET['UID'];
    $dob = $_GET['birthYear'];
    if ($_GET['provider'] == 'facebook') {
        $prolink = $_GET['profileURL'];
        $prolink2 = '';
    } elseif ($_GET['provider'] == 'twitter') {
        $prolink = '';
        $prolink2 = $_GET['profileURL'];
    } else {

        $prolink = '';
        $prolink2 = '';
    }


    /////////////////////NEW USER//////////////////////////////
    $select_user_count = db_result(db_query("SELECT COUNT(*) from users where Identity='" . $pass . "' and provider='" . $_GET['provider'] . "'"));
     $formret .='<div><b>Login processing please wait..</b></div>';
    if ($select_user_count == 0) {
        $ini_coins = initial_coins();
        $insert = "insert into {users} (pass,mail,provider,created,access,login,status,Identity,total_coins)values('" . md5($pass) . "','" . $_GET['email'] . "','" . $_GET['provider'] . "','" . time() . "','" . time() . "','" . time() . "','1','" . $pass . "', '" . $ini_coins . "') ";
        $insersult = db_query($insert);
        $lid = mysql_insert_id();
        // add visit points
        add_visit_points($lid);
///////////////welcome mail start here ///////////////
        $sel_ulists = "SELECT * FROM users where uid='$lid'";
        $user_namelistfs = ExecuteQuery($sel_ulists, "select");

        $sel_user_cmt = "SELECT * FROM {notification_mail_format} Where id='6'";
        $rs_mgmt = db_query($sel_user_cmt);
        $list_content = db_fetch_object($rs_mgmt);
        $subject_proj = $list_content->subject;
        $contentm = str_replace("#uname#", $user_namelistfs[0]['name'], $list_content->content);
        //echo $contentm;die;
        $ins_qry = "insert into hm_mails(from_mail_id,user_from_id,user_to_id,subject,content,mail_status,notify,posted_date)values('mgopi.php@gmail.com','mgopi.php@gmail.com','" . $user_namelistfs[0]['mail'] . "','" . $subject_proj . "','" . $contentm . "',0,0,now())";
        db_query($ins_qry);

        //$mail_success = htmlmail_function($user_namelistfs[0]['mail'], $subject, $contentm, '');
///////////////welcome mail end here ///////////////


        if ($_GET['nickname'] != '') {

            $unames = str_replace(" ", "", $_GET['nickname']);
            $uname = $unames . $lid;
            //echo $onlyconsonants;
        } else {
            $uname = "user" . $lid;
        }


        /////////////////update user name/////////////////////////

        $updates = "update {users} set name='$uname',prompt='1' where uid=$lid";
        $up = db_query($updates);

        $age = '';
        // $age=age($dob);
        /////////////insert into new profile user///////////////

        $social = $prolink . '||' . $prolink2;

        $insert_profile = "insert into {user_profile} (uid,real_name,first_name,last_name,gender,zip,country,social,dob,age,image_url,provider,date_update)values('" . $lid . "','" . $_GET['nickname'] . "','" . $_GET['firstName'] . "' ,'" . $_GET['lastName'] . "' ,'" . $gender . "','" . $_GET['zip'] . "','" . $_GET['country'] . "','" . $social . "','" . $dob . "','" . $age . "','" . $_GET['photoURL'] . "','" . $_GET['provider'] . "',now()  ) ";

        $insersult = db_query($insert_profile);
  $select_user = db_fetch_object(db_query("SELECT * from {users} where Identity='$pass' and provider='" . $_GET['provider'] . "' AND uid='$lid'"));

      
    } else {

        $select_user = db_fetch_object(db_query("SELECT * from {users} where Identity='" . $pass . "' and provider='" . $_GET['provider'] . "'"));
    }
$user=make_login($select_user,$_GET['UID']);
if ($user){
       add_visit_points($select_user->uid);
    drupal_goto();
}

  return $formret;
}
function make_login($result='',$pwd){


    if($result && function_exists("user_load"))
    {
           if ($account = user_load(array('uid'=>$result->uid, 'status' => 1)))
               {
                 $user = $account;
                 watchdog('user', 'Session opened for %name.', array('%name' => $user->name));
                 $user->login = time();
                 db_query("UPDATE {users} SET login = %d WHERE uid = %d", $user->login, $user->uid);
                sess_regenerate();
                $params = array(
  'mail'   => $user->email,
  'name'   => $user->name,
  'pass'   => $pwd, // No need to hash the password
  'status' => 1, // Otherwise the user is blocked on creation
);
                  $users=user_authenticate($params);
       // print_r($users);
               // print_r($user);
              // drupal_set_message(t("<h1>You have been logged in success...</h1>"),$type="success");
                }
    }
    else
    {
        drupal_set_message(t("Could not log you in. Please try again later..."),$type="error");
    }

return $users;
}
function openid_login3() {
    global $gSitePath, $user, $gDocPath, $base_root;
    $select_fet = db_query("SELECT * from users order by uid desc limit 0,1");
    $prouser = db_fetch_object($select_fet);

    $ouptii = '<form action="' . $gSitePath . 'user/login" method="post" id="user-login">
			<input type="hidden" maxlength="60" name="name" id="edit-name" size="60" value=' . $prouser->name . ' class="form-text required"/>
			<input type="password" name="pass" id="edit-pass" value="' . $prouser->hidden_pass . '"  maxlength="128"  size="60" style="display:none";  class="form-text required"/>
			<input type="hidden" name="form_id" id="edit-user-login" value="user_login"/>
			
			</form>
			<script language="JavaScript" type="text/javascript">
			
			document.getElementById(\'user-login\').submit();
			
			
			</script>
			';
    return $ouptii;
}

function friends_answers() {
    global $gSitePath, $user, $gDocPath, $base_root;

    $listans = '<div>';
    $sel_count = db_result(db_query("SELECT COUNT(*) from facebook_friends as a,possible_answer_vote as b,question as c   where a.uid=$user->uid and a.face_uid=b.uid and b.qid=c.qid "));
    //echo "select * from facebook_friends as a,possible_answer_vote as b,question as c   where a.uid=$user->uid and a.face_uid=b.uid and b.qid=c.qid ";
    $selmrq = db_query("select * from facebook_friends as a,possible_answer_vote as b,question as c   where a.uid=$user->uid and a.face_uid=b.uid and b.qid=c.qid ");
    while ($in_list = db_fetch_object($selmrq)) {
        $numran = db_result(db_query("SELECT COUNT(*) from {possible_answer_vote} where qid='" . $in_list->qid . "' and uid='" . $in_list->face_uid . "'"));

        $listans .= '<li> <a href="' . $gSitePath . '' . $in_list->url . '">' . $in_list->question . ' </a> </li>';
        $vans = "select * from {possible_answer} where  qid='" . $in_list->qid . "'order by vote desc";

        $vlist = db_query($vans);
        while ($vlistquest = db_fetch_object($vlist)) {
            // echo $in_list->panswer_id;
            $chk = '';
            if ($in_list->panswer_id == $vlistquest->paid) {

                $chk = "checked";
            }
            $listans .= '<div><input name="answer_al.' . $in_list->qid . '" type="radio" ' . $chk . '  value="' . $vlistquest->paid . '" />
	' . $vlistquest->answer . '</div>';
        }
    }
    if ($sel_count == 0) {
        $listans .= 'No Question answered by Your Facebook Friends';
    }
    $listans .= '</div>';
    return $listans;
}

function age($date) {

    $year_diff = '';
    if (!empty($date)) {
        //list($day,$month,$year)=explode("/",$date);

        $year_diff = date("Y") - $date;
        //$month_diff = date("m")-$month;
        //$day_diff = date("d")- $day;
        //if ($day_diff < 0 || $month_diff < 0) $year_diff–;

        return $year_diff;
    } else {

        return '';
    }
}

function welcome_page() {
//ob_start();
    global $gSitePath, $user, $gDocPath, $base_root, $apikey;
    //print_r($_COOKIE);
    //echo $_COOKIE["faceidc"];
    //echo "<pre>";
  //  print_r($_REQUEST);die;
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
    $selr1 = '';
    $selr2 = '';
    $selr3 = '';
    $selr4 = '';
    $selr5 = '';
    $selr6 = '';
    $sele1 = '';
    $sele2 = '';
    $sele3 = '';
    $sele4 = '';
    $sele5 = '';
    $sele6 = '';
    $sele7 = '';
    $seleant1 = '';
    $seleant2 = '';
    $seleant3 = '';
    $checkm = '';
    $checkf = '';
    $selm2 = '';
    $selm3 = '';
    $selm4 = '';
    $statecity = '';
    $ntype = '';
    $nitype = '';
    $questions = '';
    $emsg = '';
    $message = '';
    $suc = '';
    $medal = '';
    $answers = '';
    $email = '';
    $followers = '';
    $following = '';
    echo '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" dir="ltr">';
    if (!$user->uid > 0){
        drupal_not_found();        return;
    }
    //   print_r(avatar_selection_form_user_profile_form_alter());
    if ($_COOKIE["faceidc"] != '') {
        //////////////////////faceboook friends////////////////////////////////
        $insertface = "insert into facebook_friends (uid,face_uid)values('" . $_COOKIE["faceidc"] . "','" . $user->uid . "') ";
        $insersult = db_query($insertface);


        ///////////////////////// follower list///////////

        $ins_commg = "insert into   follower (uid,follower_id,follower_status,joindate) values('" . $user->uid . "' ,'" . $_COOKIE["faceidc"] . "','1','" . date('Y-m-d') . "') ";
        $rs_commg = db_query($ins_commg);

        $query_pt = "SELECT * FROM tbl_points where id='6' ";
        $query_ptinfo = db_query($query_pt);
        $fetuserpts = db_fetch_object($query_ptinfo);
        $ins_commg = "insert into   tbl_user_points (uid,point_id,points,vote_point_id) values('" . $_COOKIE["faceidc"] . "' ,'6',$fetuserpts->points,'0') ";
        $rs_commg = db_query($ins_commg);
        setcookie("friend_id", '0');
        $sel_ulist = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $user->uid . "'";
        $rs_umlog = db_query($sel_ulist);
        $user_namelistf = db_fetch_object($rs_umlog);

        $sel_ulists = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $_COOKIE["faceidc"] . "'";
        $rs_umlogs = db_query($sel_ulists);
        $user_namelistfs = db_fetch_object($rs_umlogs);

        ///////////////////Noftication  for invite friend //////////////////////////////////
        if ($user_namelistfs->notify_itype == 1) {
            $insert_notify = db_query("insert into notification (uid,new_followe,is_user,node_id) values('" . $_COOKIE["faceidc"] . "','1','1','" . $user->uid . "') ");
        }
        if ($user_namelistfs->notify_etype == 1) {


            $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='1'";
            $rs_mgmt = db_query($sel_user_cmt);
            $list_content = db_fetch_object($rs_mgmt);
            $subject = $list_content->subject;
            $contentm = str_replace("#uname#", $user_namelistf->name, $list_content->content);
            $contentm = str_replace("#anothername#", $user_namelistfs->name, $contentm);
            // $contentm;

            $mail_success = htmlmail_function($user_namelistfs->mail, $subject, $contentm, '');
        }


        ///////////////////badges for invite friend //////////////////////////////////

        $insert_badges = "insert into user_badges (uid,bid) values('" . $_COOKIE["faceidc"] . "','1') ";
        $result_badges = db_query($insert_badges);
    }

    //print_r($_REQUEST);
    // exit;
    if (isset($_REQUEST['update']) == 'Update') {
    $error_flag = 0;
         // follow links starts here
        $links=$_REQUEST['follow_links'];
    foreach($links as $name => $link) {
    $link = (object) $link;
    $link->url = trim($link->url);

    // Check to see if there's actually a link
    if (!preg_match("/^[a-zA-Z]+[:\/\/]+[A-Za-z0-9\-_]+\\.+[A-Za-z0-9\.\/%&=\?\-_]+$/i", $link->url)) {
      // If there's an lid, delete the link.
      if (isset($link->lid)) {
        follow_link_delete($link->lid);
        
      }
      if(!empty($link->url))
      $error_flag = 1;
      // Continue to the next link.
      continue;
    }
    // Otherwise save the link.
    else {
      $link->uid = $user->uid;
      $link->name = $name;
      follow_link_save($link);
    }
  }  // follow links ends here

    extract($_REQUEST);
        $chk = db_query("select * from {privacy_settings} where uid='$user->uid'");
        $chk1 = db_result($chk);
        if ($chk1) {
           
             $set_qry = "UPDATE {privacy_settings} set real_name='$real_name_privacy',name='$name_privacy',gender='$gender_privacy',image='$image_privacy',bio=' $bio_privacy',zip='$zip_privacy',country='$country_privacy',religion='$religion_privacy',ethnic='$ethnic_privacy',slant='$slant_privacy',sorient='$sorient_privacy',edu='$edu_privacy',facebook='$facebook_privacy',twitter='$twitter_privacy',email='$email_privacy',
		followers='$followers_privacy',following='$following_privacy',medal='$medal_privacy',questions='$questions_privacy',answers='$answers_privacy',dob='$dob_privacy'  where uid='$user->uid' ";
            
           
            $result = db_query($set_qry);
        } else {
            $result = db_query("INSERT INTO {privacy_settings} set uid='$user->uid',name='$name_privacy',gender='$gender_privacy',image='$image_privacy',bio=' $bio_privacy',zip='$zip_privacy',country='$country_privacy',religion='$religion_privacy',ethnic='$ethnic',slant='$slant_privacy',sorient='$sorient_privacy',edu='$edu_privacy',facebook='$facebook_privacy',twitter='$twitter_privacy',email='$email_privacy',
			followers='$followers_privacy',following='$following_privacy',questions='$questions_privacy',answers='$answers_privacy' ,medal='$medal_privacy',dob='$dob_privacy'");
        }

        if (isset($_FILES)) {


            $return = event_photo_profile();
            //print_r($return);
            $insimage = $return['image'];
            $flag = $return['flag'];
            $suc = $return['suc'];
        }

        $chk = db_query("select * from {user_profile}  where uid='$user->uid'");
        $chk1 = db_result($chk);
        $result_profile = db_fetch_object($chk);

        $socials = implode('||', $social);
        $urls = implode(';', $ptitle) . '@' . implode('||', $purl);
            if(!preg_match('/^[A-Za-z0-9_]{5,20}$/i',$rname)){
                  $message.="<div class='error red'>Username should be Alphabets, numbers and no special characters min 5 and max 20 allowed</div>";
                }  elseif (db_result(db_query("SELECT COUNT(*) FROM {users} WHERE name = '%s' AND uid!='%d'",$rname,$user->uid))) {
         $message.="<div class='error red'>Sorry Username already exists try any other combination</div>";
            }else{
              db_query("update {users} set name='$rname' where uid='$user->uid'");
            }
        $update_user = db_query("update {users} set mail='$mail' ,notify_etype='$ntype',notify_itype='$nitype' where uid='$user->uid' ");
        $age = '';
        $age = age($dob);
        $country = (!empty($country1)) ? $country1 : $country;
    
        $result = db_query("UPDATE {user_profile} set uid='$user->uid',gender='$gender',image_avatar='$pic_avt',image='$insimage',avatar='$select_avatar',bio=' $bio',zip='$zip',country='$country',state='$state',city='$city',religion='$religion',ethnic='$ethnic',dob='$dob',age='$age',slant='$slant',sorient='$sorient',edu='$edu',social='$socials',question_privacy='$qrset',first_name='$fname',last_name='$lname',urls='$urls' where uid='$user->uid' ");
        


        $sel_ulists = "select * from {user_profile} where uid='$user->uid'";
        $rs_umlogs = db_query($sel_ulists);
        $user_namelistfs = db_fetch_object($rs_umlogs);

        if (($user_namelistfs->religion != '') && ($user_namelistfs->ethnic != '') && ($user_namelistfs->slant != '') && ($user_namelistfs->dob != '') && ($user_namelistfs->gender != '') && ($user_namelistfs->zip != '')) {
            $result_profile_edit = db_query("UPDATE {users} set profile_edit='1' where uid='$user->uid' ");
        }


        if ($result) {
            $sucflag = '';
            $sucflag = 1;
            if (isset($_SESSION['filepath'])) {
                echo '<script>window.top.location.href="' . $gSitePath . 'user/cropimage";</script>';
            }
            $message.= '<div class="success">Profile Updated Successfully!</div>';
            if($error_flag > 0){
             $message.= '<div class="error">Invalid web reference URL(s)</div>';
            }
        }
    }

    $get_cn = db_query("select * from {user_profile} as a, {users} as b where a.uid='$user->uid' and b.uid='$user->uid'");
    $result = db_fetch_array($get_cn);

    extract($result);
    drupal_set_title('Edit Profile');
    $psplit = explode('@', $urls);
    $ptitle = explode(';', $psplit[0]);
    $purl = explode('||', $psplit[1]);
    $social = explode('||', $social);
    drupal_add_js(drupal_get_path('module', 'profile') . '/js/en.js');
    drupal_add_js(drupal_get_path('module', 'profile') . '/js/formcheck.js');
    drupal_add_css(drupal_get_path('module', 'profile') . '/theme/classic/formcheck.css');
    //geoname
    $options = array('sortby' => 'countryname', 'sortorder' => 'ASC');
    $result = geonames_query('countryinfo', NULL, $options);
    $optionlist .='<option value="">Select Location</option>';
    foreach ($result->results as $countries) {
        $select = '';
        if (strtoupper($country) == strtoupper($countries['countryname'])) {
            //   if(preg_match('/$country/',$countries['countryname'])){
            $select = "SELECTED='SELECTED'";
        }

        $optionlist .= sprintf('<option %s value="%s">%s</option>', $select, $countries['countryname'], $countries['countryname']);
    }
    //echo $user->notify_type;
    if ($user->notify_etype == 1) {
        $checkm = "checked='checked'";
    }

    if ($user->notify_itype == 1) {
        $checkf = "checked='checked'";
    }
    if ($gender == 1) {
        $check1 = "checked='checked'";
    } elseif ($gender == 2) {
        $check2 = "checked='checked'";
    }
    //////////////////question privacy/////////////////////////

    if ($question_privacy == 1) {
        $selm = "checked='checked'";
    } elseif ($question_privacy == 2) {
        $selm2 = "checked='checked'";
    } elseif ($question_privacy == 3) {
        $selm3 = "checked='checked'";
    } elseif ($question_privacy == 4) {
        $selm4 = "checked='checked'";
    }
    //////////////////religion/////////////////////////
    if ($religion == 'Christian') {
        $selr1 = "selected='selected'";
    } elseif ($religion == 'Muslim') {
        $selr2 = "selected='selected'";
    } elseif ($religion == 'Jewish') {
        $selr3 = "selected='selected'";
    } elseif ($religion == 'Hindu') {
        $selr4 = "selected='selected'";
    } elseif ($religion == 'Buddhist') {
        $selr5 = "selected='selected'";
    } elseif ($religion == 'Other') {
        $selr6 = "selected='selected'";
    }
    //////////////////ethinicity/////////////////////////

    if ($ethnic == 'Caucasian') {
        $sele1 = "selected='selected'";
    } elseif ($ethnic == 'Black') {
        $sele2 = "selected='selected'";
    } elseif ($ethnic == 'Asian') {
        $sele3 = "selected='selected'";
    } elseif ($ethnic == 'Indian') {
        $sele4 = "selected='selected'";
    } elseif ($ethnic == 'Semetic') {
        $sele5 = "selected='selected'";
    } elseif ($ethnic == 'Latin') {
        $sele6 = "selected='selected'";
    } elseif ($ethnic == 'Aborigines') {
        $sele7 = "selected='selected'";
    }
    if ($slant == 'Left') {
        $seleant1 = "selected='selected'";
    } elseif ($slant == 'Right') {
        $seleant2 = "selected='selected'";
    } elseif ($slant == 'Center') {
        $seleant3 = "selected='selected'";
    }

    if (!empty($state)) {

        $statecity = ' <input type="hidden" name="country" value="' . $country . '">
				<input type="hidden" name="state" value="' . $state . '">
				<input type="hidden" name="city" value="' . $city . '">
				';
    }

    $query = "select * from {privacy_settings} where uid='$user->uid'";
    $fetch = ExecuteQuery($query, "select");
    $result = db_query($query);
    $i = 0;
    while ($i < mysql_num_fields($result)) {

        $meta =  mysql_fetch_field($result, $i);
        $col = $meta->name;
        if ($fetch[0][$col] > 1)
            $inc_script.='jQuery("input[name=\'' . $meta->name . '_privacy\']").filter(\'[value="' . $fetch[0][$col] . '"]\').attr(\'checked\', true);';
        else
            $inc_script.='jQuery("input[name=\'' . $meta->name . '_privacy\']").filter(\'[value="1"]\').attr(\'checked\', true);';

        $i++;
    }
    //avatar
    if ($image_avatar == 2)
        $avtchk2 = "checked='checked'";
    else
        $avtchk1= "checked='checked'";
        $follow=drupal_get_form('follow_links_form',$uid);
            $follow = str_replace("</form>", "", $follow);
    $follow = str_replace(' <form action="/heardmentality/edit"  accept-charset="UTF-8" method="post" id="follow-links-form">', "", $follow);
    $avatarform = drupal_get_form('avatar_form');
    $avatarform = str_replace("</form>", "", $avatarform);
    $avatarform = str_replace('<form action="/heardmentality/edit"  accept-charset="UTF-8" method="post" id="avatar-form">', "", $avatarform);
    $ava_js = drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection.js';
    $ava_page_js = drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection_pager.js';
    $ava_css = drupal_get_path('module', 'avatar_selection') . '/avatar_selection.css';


    //privacy settings form
    $usertypes = userTypes();
    $option1 = '<option value=1>' . $usertypes[0] . '</option>';
    $option2 = '<option value=2>' . $usertypes[1] . '</option>';
    $option3 = '<option value=3>' . $usertypes[2] . '</option>';
    $op = '
<head>
<script type="text/javascript">
var spath=\'' . $gSitePath . '\';
    </script><script src="' . $gSitePath . '/misc/jquery.js" type="text/javascript"></script>
<script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'quest_lite') . '/scripts/jquery.blockUI.js"></script>
<script src="' . $gSitePath . path_to_theme() . '/floatbox/floatbox.js" type="text/javascript"></script>
    	<SCRIPT type="text/javascript" lang="javascript"
	   src="http://cdn.gigya.com/JS/socialize.js?apikey=' . $apikey . '">
	</SCRIPT>
	<script>
	    var conf =
        {
            APIKey: \'' . $apikey . '\'
        };
</script><script src="' . $gSitePath . 'sites/all/modules/profile/js/profile.js" type="text/javascript">
</script><script src="' . $gSitePath . 'sites/all/modules/openids/js/validate.js" type="text/javascript"></script>
<link rel="stylesheet" href="' . $gSitePath . path_to_theme() . '/css/css.css" type="text/css" />

<script>
jQuery.noConflict();
</script>
</script><script src="' . $gSitePath . '/misc/drupal.js" type="text/javascript"></script>

</script><script src="' . $gSitePath . $ava_js . '" type="text/javascript"></script>
    <script src="' . $gSitePath . $ava_page_js . '" type="text/javascript"></script>
<link rel="stylesheet" href="' . $gSitePath . $ava_css . '" type="text/css" />
<!--<link type="text/css" rel="stylesheet" href="' . $gSitePath . drupal_get_path('module', 'openids') . '/css/log.css" />-->
</head>
<body style="background:none;">
<form name="reg" id="reg"  onsubmit="return validate_reg();"  method="post" enctype="multipart/form-data">

<div class="crete-profile-wrapper">
<div class="inside-wrapper">
<div class="crete-profile-toppart">
    <div class="top-abturself">
    TELL US ABOUT YOURSELF
    </div>
<div class="info">
	 <input type="input" class="" style="display:none;"  readonly="true" border="0" width="1" size="1" name="errbox" id="errbox">
         <div id="err_div" style="display:none;" class="">' . $emsg . ' ' . $message . '</div>
    </div>
    <div class="clr"></div>
    <div class="creat-inner-title-outer">
       <div class="creat-inner-title-left">INFO</div>
       <div class="creat-inner-title-right">PRIVACY SETTINGS</div>
       <div class="clr"></div>
    </div>
    <div class="clr"></div>
          <div class="creat-inner-gridpart">
          <div class="col-1">

          <div class=" w-outer">
                 <div class="ti-1">`</div>
                 <div class="w3">Anyone</div>
                 <div class="w4">Logged in Users</div>
                 <div class="w5">Followers &amp; Followees</div>
                 <div class="w5">No one</div>
             </div>

          <div class="clr"></div>
          <div class="bord-alin-rite"></div>
                       <div class=" w-outer">
                 <div class="w1">User Name:</div>
                 <div class="w2"> <input id="rname" maxlength="20" name="rname" onblur="chk_uname(this.value);" class="txtbx-1" value="' . $name . '" tabindex="1" type="text">
   </div>
                 <div class="w3"><input name="real_name_privacy" type="radio" value="1" /></div>
                 <div class="w4"><input name="real_name_privacy" type="radio" value="2" /></div>
                 <div class="w5"><input name="real_name_privacy" type="radio" value="3" /></div>
                 <div class="w6"><input name="real_name_privacy" type="radio" value="4" /></div>
                  
             </div>
             <div class="clr"></div>
<div class="bord-alin-rite"></div>
             <div class=" w-outer">
                 <div class="w1">First Name:</div>
                 <div class="w2">
                 <input id="fname" name="fname" class="txtbx" value="' . $first_name . '" size="8" tabindex="2" type="text"> <input id="lname" name="lname" class="txtbx" value="' . $last_name . '" size="12" tabindex="3" type="text">
  </div>
                 <div class="w3"><input name="name_privacy" type="radio" value="1" /></div>
                 <div class="w4"><input name="name_privacy" type="radio" value="2" /></div>
                 <div class="w5"><input name="name_privacy" type="radio" value="3" /></div>
                 <div class="w6"><input name="name_privacy" type="radio" value="4" /></div>
             </div>
             <div class="clr"></div>
             <div class="bord-alin-rite"></div>
             <div class=" w-outer">
                 <div class="w1">Email:</div>
                 <div class="w2"><input id="edit-mail" name="mail" class="txtbx-1" value="' . $mail . '" maxlength="255" tabindex="4" type="text">
	</div>
                 <div class="w3"><input name="email_privacy" type="radio" value="1" /></div>
                 <div class="w4"><input name="email_privacy" type="radio" value="2" /></div>
                 <div class="w5"><input name="email_privacy" type="radio" value="3" /></div>
                 <div class="w6"><input name="email_privacy" type="radio" value="4" /></div>
             </div>
             <div class="clr"></div>
             <div class="bord-alin-rite"></div>
             <div class=" w-outer">
                 <div class="w1">Year Of Birth:</div>
                 <div class="w2"> <input name="dob"  value="' . $dob . '"  id="dob" class="txtbx" maxlength="4"  tabindex="5" type="text"><small>[yyyy]</small></div>
                 <div class="w3"><input name="dob_privacy" type="radio" value="1" /></div>
                 <div class="w4"><input name="dob_privacy" type="radio" value="2" /></div>
                 <div class="w5"><input name="dob_privacy" type="radio" value="3" /></div>
                 <div class="w6"><input name="dob_privacy" type="radio" value="4" /></div>
             </div>
             <div class="clr"></div>
             <div class="bord-alin-rite"></div>
             <div class=" w-outer">
                 <div class="w1">Gender:</div>
                 <div class="w2"><span><input id="edit-gender-0" tabindex="6" name="gender" value="1" ' . $check1 . ' type="radio"> Male</span>&nbsp;&nbsp;<span><input id="edit-gender-1" name="gender" value="2" class="form-radio" ' . $check2 . ' type="radio"> Female</span></div>
                 <div class="w3"><input name="gender_privacy" type="radio" value="1" /></div>
                 <div class="w4"><input name="gender_privacy" type="radio" value="2" /></div>
                 <div class="w5"><input name="gender_privacy" type="radio" value="3" /></div>
                 <div class="w6"><input name="gender_privacy" type="radio" value="4" /></div>
             </div>
             <div class="clr"></div>
             <div class="bord-alin-rite"></div>
             <div class=" w-outer">
                 <div class="w1">Country:</div>
                 <div class="w2"><select name="country1" class="txtbx-1" tabindex="7" id="edit-country">' . $optionlist . '</select></div>
                 <div class="w3"><input name="country_privacy" type="radio" value="1" /></div>
                 <div class="w4"><input name="country_privacy" type="radio" value="2" /></div>
                 <div class="w5"><input name="country_privacy" type="radio" value="3" /></div>
                 <div class="w6"><input name="country_privacy" type="radio" value="4" /></div>
             </div>
             <div class="clr"></div>
             <div class="bord-alin-rite"></div>
             <div class=" w-outer">
                 <div class="w1">Postal / Zip Code:</div>
                 <div class="w2"> <input name="zip"  value="' . $zip . '" class="txtbx-1" tabindex="8" onblur="get_zip_city(this.value);" id="edit-zip"  type="text"><span style="display:none;" id="edit-city-wrapper">' . $statecity . ' </span></div>
                 <div class="w3"><input name="zip_privacy" type="radio" value="1" /></div>
                 <div class="w4"><input name="zip_privacy" type="radio" value="2" /></div>
                 <div class="w5"><input name="zip_privacy" type="radio" value="3" /></div>
                 <div class="w6"><input name="zip_privacy" type="radio" value="4" /></div>
             </div>
                 <div class="clr"></div>
               <div class="bord-alin-rite"></div>
             <div class=" w-outer">
                 <div class="w1">Religion:</div>
                 <div class="w2"> <select  name="religion" id="edit-religion"  tabindex="9" class="txtbx-1" ><option value="" >Select</option><option value="Christian" ' . $selr1 . ' >Christian (Cath or Prod)</option><option value="Muslim" ' . $selr2 . ' >Muslim (Suni Shiite)</option><option value="Jewish" ' . $selr3 . ' >Jewish</option><option value="Hindu" ' . $selr4 . ' > Hindu</option><option value="Buddhist" ' . $selr5 . ' >Buddhist</option><option value="Other" ' . $selr6 . '>Other</option></select> </div>
                 <div class="w3"><input name="religion_privacy" type="radio" value="1" /></div>
                 <div class="w4"><input name="religion_privacy" type="radio" value="2" /></div>
                 <div class="w5"><input name="religion_privacy" type="radio" value="3" /></div>
                 <div class="w6"><input name="religion_privacy" type="radio" value="4" /></div>
                 
             </div>
             <div class="clr"></div>
             <div class="bord-alin-rite"></div>
             <div class=" w-outer">
                 <div class="w1">Ethnicity:</div>
                 <div class="w2"><select name="ethnic" id="edit-ethnic" tabindex="10" class="txtbx-1" ><option value="">Select </option><option value="Caucasian" ' . $sele1 . '>Caucasian</option><option value="Black" ' . $sele2 . '>Black</option><option value="Asian" ' . $sele3 . '>Asian</option> <option value="Indian" ' . $sele4 . '>Indian</option> <option value="Semetic" ' . $sele5 . '>Semetic</option><option value="Latin" ' . $sele6 . '>Latin</option> <option value="Aborigines" ' . $sele7 . '>Aborigines</option>  </select></div>
                 <div class="w3"><input name="ethnic_privacy" type="radio" value="1" /></div>
                 <div class="w4"><input name="ethnic_privacy" type="radio" value="2" /></div>
                 <div class="w5"><input name="ethnic_privacy" type="radio" value="3" /></div>
                 <div class="w6"><input name="ethnic_privacy" type="radio" value="4" /></div>
             </div>
             <div class="clr"></div>
             <div class="bord-alin-rite"></div>
             <div class=" w-outer">
                 <div class="w1">Slant:</div>
                 <div class="w2"><select name="slant" id="edit-slant"  class="txtbx-1" ><option value="">Select</option><option value="Left" ' . $seleant1 . '>Left</option><option value="Right" ' . $seleant2 . '>Right </option> <option value="Center" ' . $seleant3 . '>Center </option>  </select>
	       </div>
                 <div class="w3"><input name="slant_privacy" type="radio" value="1" /></div>
                 <div class="w4"><input name="slant_privacy" type="radio" value="2" /></div>
                 <div class="w5"><input name="slant_privacy" type="radio" value="3" /></div>
                 <div class="w6"><input name="slant_privacy" type="radio" value="4" /></div>
             </div>
             <div class="clr"></div>
             <div class="bord-alin-rite"></div>
             <div class=" w-outer">
                 <div class="w1">Sex. Orientation:</div>
                 <div class="w2"><select name="sorient" id="edit-sorient"  tabindex="11" class="txtbx-1" ><option value="">Select</option><option value="Straight" ' . $seleant1 . '>Straight</option><option value="Gay" ' . $seleant2 . '>Gay </option> <option value="Bisexual" ' . $seleant3 . '>Bisexual </option><option value="Transgender" ' . $seleant3 . '>Transgender </option>  </select>
	       </div>
                 <div class="w3"><input name="sorient_privacy" type="radio" value="1" /></div>
                 <div class="w4"><input name="sorient_privacy" type="radio" value="2" /></div>
                 <div class="w5"><input name="sorient_privacy" type="radio" value="3" /></div>
                 <div class="w6"><input name="sorient_privacy" type="radio" value="4" /></div>
             </div>
                  <div class="clr"></div>
             <div class="bord-alin-rite"></div>
             <div class=" w-outer">
                 <div class="w1">Education Level:</div>
                 <div class="w2"><select name="edu" id="edit-edu" tabindex="12"  class="txtbx-1" ><option value="">Select</option><option value="No High School" ' . $seleant1 . '>No High School</option><option value="High School" ' . $seleant2 . '>High School </option> <option value="Technical College" ' . $seleant3 . '>Technical College </option><option value="University" ' . $seleant3 . '>University </option><option value="Masters Degree" ' . $seleant3 . '>Masters Degree </option><option value="PhD" ' . $seleant3 . '>PhD </option>  </select>
	       </div>
                 <div class="w3"><input name="edu_privacy" type="radio" value="1" /></div>
                 <div class="w4"><input name="edu_privacy" type="radio" value="2" /></div>
                 <div class="w5"><input name="edu_privacy" type="radio" value="3" /></div>
                 <div class="w6"><input name="edu_privacy" type="radio" value="4" /></div>
             </div>
             <div class="bord-alin-rite"></div>
              <div class="clr"></div>
          </div>

 <div class="col-2-outer">
          <div class="col-2">
          When i vote on issues or posting content to Heard Mentality I want the following privacy settings applied when other users view my profile<br /><br />

<span><input type="radio" name="qrset"  class="qrset" value="1" ' . $selm . '/>&nbsp;No one can see what i do</span><br />

<span> <input type="radio" name="qrset" class="qrset" value="2" ' . $selm2 . '/>&nbsp;Only my followers and followees can see</span><br />

<span> <input type="radio" name="qrset" class="qrset"  value="3" ' . $selm3 . '/>&nbsp;Anyone can see what i do</span><br />

<span> <input type="radio" name="qrset" class="qrset"  value="4" ' . $selm4 . '/>&nbsp;I want to be asked each time</span><br />
<br />
<h4>NOTIFY TYPE</h4><br />


<span> <input name="ntype" type="checkbox" ' . $checkm . '  value="1"  />&nbsp;Email</span>
<span><input name="nitype" type="checkbox" ' . $checkf . '  value="1"  />&nbsp;Internal Message Only</span>
          <div class="clr"></div>


          </div>

          <div class="clr"></div>

          <div class="merge-social">
          <div class="merge-social-tit">merge your social networks</div>
          <div class="clr"></div>
          <div class="merge-script-outer"> <div id="divConnect"></div>
    <script type="text/javascript">
        // show Add Connections Plugin in "divConnect"
        gigya.services.socialize.showAddConnectionsUI(conf, {
			height:65
			,width:175
			,showTermsLink:false //remove trems link
			,hideGigyaLink:true // remove Gigya link
			,useHTML:true  // Use the HTML implementation of the Plugin (rather then Flash implementation)
			,containerID: "divConnect" // The component will embed itself inside the divConnect Div
		});
    </script>    </div>

          </div>

          </div>
 </div>
      </div>
      <div class="clr"></div>
      <div class="create-inner-bot">
                 <div class="bio">
                 <div class="bio-title">BIO <div class="clr"></div></div>
                 <div class="clr"></div>
                 <div>

                 <div class="bio-left"> <textarea name="bio" id="edit-bio" class="form-text" rows="3" cols="9">' . $bio . '</textarea><br />
<span>Write a short blurb that describes you. This provides context
to your account, will appear in your profile, and will help you
get found through search engines such as Google and Yahoo.</span></div>
     <div class="bio-right">
     ' . $avatarform . '
   </div>
   </div>
    <div class="clr"></div>
<div class="clr"></div>
                 </div>

                     <div class="web-reference">
                     <div class="web-reference-tit">WEB REFERENCES</div>
                     <div class="clr"></div>
                     '.$follow.'
                        <!-- <div class="social-outer">
                          <div class="social-left"><img src="' . $gSitePath . path_to_theme() . '/images/soc-face.jpg" width="26" height="27" alt="Facebook" /></div>
                          <div class="social-rite"><input maxlength="60" name="social[]"   value="' . $social[0] . '"  size="60"  type="text"> </div>
                         </div>

                         <div class="clr"></div>
                         <div class="social-outer">
                          <div class="social-left"><img src="' . $gSitePath . path_to_theme() . '/images/soc-twit.jpg" width="27" height="27" alt="Twitter" /></div>
                          <div class="social-rite"><input name="social[]" value="' . $social[1] . '" type="text" /></div>
                         </div>

                         <div class="clr"></div>


                         <div class="social-outer">
                          <div class="social-left"><img src="' . $gSitePath . path_to_theme() . '/images/soc-myspace.jpg" width="26" height="27" alt="My Space" /></div>
                          <div class="social-rite"><input name="social[]" value="' . $social[2] . '"  type="text" /></div>
                         </div>

                         <div class="clr"></div>
                         <div class="border4web"></div>
                         <div class="clr"></div>
                         <div class="social-outer">

                          <div class="social-rite">Link Title :<input name="ptitle[]" type="text" value="' . $ptitle[0] . '" maxlength="255" /></div>
                         </div>
                         <div class="clr"></div>

                         <div class="social-outer">

                          <div class="social-rite">URL :&nbsp; &nbsp; &nbsp; &nbsp;<input name="purl[]" value="' . $purl[0] . '" maxlength="255"  type="text" /></div>
                         </div>
                         <div class="clr"></div>
                         <div class="border4web"></div>
                         <div class="clr"></div>
                         <div class="social-outer">

                          <div class="social-rite">Link Title :<input name="ptitle[]" value="' . $ptitle[1] . '" type="text" maxlength="255" /></div>
                         </div>
                         <div class="clr"></div>
                         <div class="social-outer">

                          <div class="social-rite">URL :&nbsp; &nbsp; &nbsp; &nbsp;<input name="purl[]" value="' . $purl[1] . '" type="text" maxlength="255"  /></div>
                         </div> -->


                     </div>

      </div>
    <div class="clr"></div>

      </div>
      <div class="clr"></div>
      <div class="save-changes-outer"><input type="submit" name="update" value="Update" src="' . $gSitePath . path_to_theme() . '/images/save-changes-bt.png" style="width:100px;height:21px;" alt="Save Changes" /></div>
          </form>    </div>



                 
  
		<script>
			
			
			
jQuery(document).ready(function(){
chk_avatar();
			var avatchk="' . $image_avatar . '";

			jQuery("div.bio-right input:radio[value="+avatchk+"]").attr("checked","checked");

' . $inc_script . '

var sorient="'.$sorient.'";
 var edu="'.$edu.'";

jQuery("#edit-sorient option[value="+sorient+"]").attr("selected","selected") ;
jQuery("#edit-edu option[value="+edu+"]").attr("selected","selected") ;
});

function chk_avatar(){

var avat="' . $avatar . '";
			if(avat.length>2){
			jQuery("div.form-item img[src*=\'' . $avatar . '\']").addClass("avatar-select").prev("input radio").attr("checked",true);
}else{
	jQuery("div.form-item img:first").addClass("avatar-select");
	jQuery("input[name=select_avatar]:first").attr("checked",true);
}
}
	</script>

    </div> </body>
	</html>
';





    setcookie("faceidc");
    echo $op;
}

function avatar_form($form, &$form_state) {
    global $gSitePath, $user, $gDocPath, $base_root, $_GET;
    //avatar
    $form = array();
    // We find out the current page number.
    $page = 0;

    //$form['#attributes']['enctype'] = 'multipart/form-data';

    $form['pic_exp'] = array(
        '#type' => 'markup',
        '#value' => t(' <h4><input type="radio" value="1" name="pic_avt"> IMAGE UPLOAD</h4>'),
    );

    $form['avatar_crop_title'] = array(
        '#type' => 'markup',
        '#prefix' => ' <div>
                                     <span class="imgupload-img">',
        '#suffix' => '</span>

                                     <span class="imgupload-txt">Select an image file on your computer.(2MB max)</span>
                                     </div>',
        '#value' => UserPicture($user->uid, 1),
    );
    $form['file_upload'] = array(
        '#prefix' => '  <div class="clr"></div><br />',
        '#suffix' => '     <div class="clr"></div>',
        '#title' => t('Upload file'),
        '#type' => 'file',
        '#size' => 20,
    );
    $form['submit_upload'] = array(
        '#type' => 'markup',
        '#value' => ' <div><h4 class="border4web">[OR]<input type="radio" value="2" name="pic_avt"> SELECT AN AVATAR </h4></div>
<br  class="clr"/><div>',
    );


    if (isset($_GET['page']) && is_numeric($_GET['page'])) {
        $page = $_GET['page'];
    }
    $anon_user = drupal_anonymous_user();
    $force_choose = variable_get('avatar_selection_force_user_avatar_reg', 0);
    $avatars_per_page = variable_get('avatar_selection_avatar_per_page', 30);
    $selects = _avatar_selection_image_list($anon_user, "", 0, $page * $avatars_per_page, $avatars_per_page);

    $udetails = load_user($user->uid);

    $avatar = (!empty($udetails->avatar)) ? $udetails->avatar : '';

    if (count($selects['avatars'])) {

        drupal_add_js(drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection_pager.js', 'module', 'header');
        $form['picture']['select_avatar'] = array(
            '#type' => 'radios',
            '#title' => ($upload == 0 ? t('Select an avatar') : t('Or simply select an icon')),
            '#description' => $upload ? '' : t('Your virtual face or picture.'),
            '#options' => $selects['avatars'],
            '#required' => $force_choose ? TRUE : FALSE,
            '#default_value' => $avatar,
            '#attributes' => array('class' => 'user-avatar-select'),
            '#prefix' => '<div id="avatar-selection-loading"></div>',
            '#suffix' => theme('avatar_selection_pager', 'form#user-register', 'div.user-avatar-select', $selects['total'], $avatars_per_page, '/' . $js_file),
        );
    }
    $form['submit_close'] = array(
        '#type' => 'markup',
        '#value' => ' <div class="clr"></div></div>',
    );

    //avatar
    return $form;
}

function event_photo_profile() {
    global $gSitePath, $user, $gDocPath, $base_root;
    $suc = '';
    $return = array();

    $validators = array(
        'file_validate_is_image' => array(),
        'file_validate_image_resolution' => array('500x500'),
        'file_validate_size' => array(500 * 1024),
    );
    $upload_dir = variable_get('user_picture_path', 'pictures');
    $filepath = file_directory_path();
    $dest = $filepath . '/' . $upload_dir;
    $file = file_save_upload('file_upload', $validators, $dest);
    global $user;
    $owner = $user->uid;
    $filetype;
    $filetype = $file->filemime;
    $extension = '';
    switch ($filetype) {
        case 'image/jpeg':
            $extension = 'jpg';
            break;
        case 'image/png':
            $extension = 'png';
            break;
        case 'image/gif':
            $extension = 'gif';
            break;
    }
    $dest = variable_get('user_picture_path', 'pictures') . '/picture-' . $owner . '.' . $extension;

    if ($file != 0) {
        //$dest_path = 'files/upload_directory';
        $result = file_move($file, $dest, FILE_EXISTS_RENAME);
        $flag = 0;
    }

    if ($result == 1) {
        $insimage = $file->filepath;
        $_SESSION['filepath'] = $file->filepath;
        $_SESSION['fid'] = $file->fid;
        $_SESSION['filetype'] = $file->filemime;
        $flag = 0;
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
    /*
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

     */
}

?>
