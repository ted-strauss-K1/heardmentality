<?php

// tree menu listing
function profile_view() {

    global $user;
    // get user profile id for a particular user
    $uid = get_user_profile_id();
    $strReturn = user_profile_bio($uid);

     // profile badges
    enthusiast($uid);
    fanatic($uid);
    
    return $strReturn;
}







function save_follow_profile() {

    if (isset($_REQUEST['action'])) {
        $query = 'DELETE FROM follower WHERE id = ' . (int) $_REQUEST['action'];
        $result = db_query($query);
        echo '<div id="' . $_REQUEST['ids'] . '" >Removed</div>';
    }
}

//////////following //////////////////////////




function save_follower_profile() {
    global $base_url, $user, $base_root;
    print_r($_REQEST);
    if (isset($_REQEST['action'])) {
        print_r($_REQEST);
        $del_blog = "update  follower  set follower_status='" . $_REQUEST['blk'] . "' where  id='" . $_REQEST['action'] . "' ";
        $rs_blog_del = db_query($del_blog);

        $sel_userms = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $_REQEST['usid'] . "'";
        // $sel_userms="select * from users  where uid='".$_GET['usid']."' ";
        $rs_userms = db_query($sel_userms);
        $resulrnames = db_fetch_object($rs_userms);
        if ($_REQUEST['blk'] == 0) {
            $blkid = '1';
            $valss = 'UnBlock';
            $insert_notify = db_query("insert into notification (uid,is_block,is_user,node_id) values('" . $_REQEST['usid'] . "','1','1','" . $user->uid . "' ");
            $sel_ulists = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $_REQEST['usid'] . "'";
            $rs_umlogs = db_query($sel_ulists);
            $user_namelistfs = db_fetch_object($rs_umlogs);




            $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='2'";
            $rs_mgmt = db_query($sel_user_cmt);
            $list_content = db_fetch_object($rs_mgmt);
            $contentm = str_replace("#uname#", $user_namelistfs->name, $list_content->content);
            $contentm = str_replace("#anothername#", $user->name, $contentm);
            // $contentm;

            $mail_success = htmlmail_function($user_namelistfs->mail, $subject, $contentm, '');
        } else {
            $valss = 'Block';
            $blkid = '0';
        }
        echo '<div id="' . $_REQUEST['ids'] . '" >' . UserPicture_small($_GET['usid']) . '<a href="' . $base_url . '/profile/' . $resulrnames->name . '">' . $resulrnames->name . '</a> <a onclick="blockandunblock(' . $_GET['action'] . ',' . $_GET['usid'] . ',' . $blkid . ')" style="color:#F37321;" >' . $valss . '</a></div>';
    }
}






function google_map() {
    $page = $_REQUEST[q];
    switch ($page) {

        case 'google/map/users':
            $variable = "Users";
            //$geomap_qry = "SELECT count(country)as count,country from `user_profile` where country REGEXP '[^0-9]' group by country ";
            $geomap_qry = "select count(u.uid) as count,up.country from users as u join user_profile as up on u.uid=up.uid where u.status=1 and up.country REGEXP '[^0-9]' group by up.country";
            $geomap_exec = ExecuteQuery($geomap_qry, "select");
            $cnt = db_result(db_query(" select count(u.uid) from users as u join user_profile as up on u.uid=up.uid where u.status=1 and up.country REGEXP '[^0-9]'"));

            $first = 0;
            foreach ($geomap_exec as $geomapeach) {

                $asscountry .= " data.setValue(" . $first . ", 0,'" . $geomapeach['country'] . "');" . ' data.setValue(' . $first . ', 1,' . $geomapeach['count'] . ');';
                // $assuser .=  'data.setValue(5, 1,'.$geomapeach['count'].');';
                $first = $first + 1;
            }
            break;
        case 'google/map/online':
            $variable = "Online";
            $time_period = variable_get('user_block_seconds_online', 900);
            $cnt = db_query('SELECT count(*) access FROM {users} WHERE access >= %d AND uid != 0 ORDER BY access DESC', time() - $time_period);

            //$userslist = db_query('SELECT * FROM users as u join user_profile as up on u.uid=up.uid  WHERE u.access >= %d AND u.uid != 0 group BY up.country', time() - $time_period);
            //echo $total_users = db_result($userslist);

            $get_ans = db_query('SELECT count(*) as count,up.* FROM users as u join user_profile as up on u.uid=up.uid  WHERE u.access >= %d AND u.uid != 0 AND up.country REGEXP \'[^0-9]\'  group BY up.country', time() - $time_period);
            $first = 0;
            while ($geoans = db_fetch_object($get_ans)) {
                $first = $first + 1;
                $asscountry .= " data.setValue(" . $first . ", 0,'" . $geoans->country . "');" . ' data.setValue(' . $first . ', 1,' . $geoans->count . ');';
            }

            //$geomap_qry = "'SELECT * FROM users as u join user_profile as up on u.uid=up.uid  WHERE u.access >= %d AND u.uid != 0 group BY up.country', time() - $time_period";
            //$geomap_exec= ExecuteQuery($geomap_qry, "select");
//            foreach($geomap_exec as $geomapeach){
//               echo $geomapeach['country'];
//            // $asscountry .=  "data.setValue(5, 0,'".$geomapeach['country']."');";
//            //$assuser .=  'data.setValue(5, 1,'.$geomapeach['uid'].');';
//             }
            break;
        case 'google/map/questions':
            $variable = "Issues";
            // $geomap_qry = "select count(*)as count,q.country from question as q join users as u on q.uid=u.uid where q.status='1' group by q.country";
             $cnt = db_result(db_query("select count(*) from {content_field_issue_country}  where field_issue_country_value REGEXP '[^0-9]'"));

            // $geomap_qry = "select count(*) as count, country from question where country REGEXP '[^0-9]' group by country";
            $geomap_qry = "select count(*) as count,field_issue_country_value as country from {content_field_issue_country} where field_issue_country_value REGEXP '[^0-9]' group by field_issue_country_value";
            $geomap_exec = ExecuteQuery($geomap_qry, "select");

            $first = 0;
            foreach ($geomap_exec as $geomapeach) {

                $asscountry .= " data.setValue(" . $first . ", 0,'" . $geomapeach['country'] . "');" . ' data.setValue(' . $first . ', 1,' . $geomapeach['count'] . ');';
                $first = $first + 1;
            }
            break;
        case 'google/map/answer':
            $variable = "Votes";
            $geomap_qry = "select count(*)as count,q.field_issue_country_value as country from {poll_votes} as a join {content_field_issue_country} as q on q.nid=a.nid where q.field_issue_country_value REGEXP '[^0-9]' group by q.field_issue_country_value";
            $geomap_exec = ExecuteQuery($geomap_qry, "select");
            $cnt = db_result(db_query("select count(*) from {poll_votes} as a join {content_field_issue_country} as q on q.nid=a.nid where q.field_issue_country_value REGEXP '[^0-9]'"));

            $first = 0;
            foreach ($geomap_exec as $geomapeach) {

                $asscountry .= " data.setValue(" . $first . ", 0,'" . $geomapeach['country'] . "');" . ' data.setValue(' . $first . ', 1,' . $geomapeach['count'] . ');';


                $first = $first + 1;
            }
            break;
    }
    if ($_REQUEST['width'] == '155')
        $vars = ' geomap.draw(data,{width:155,height:100,showLegend:false});';
    else
        $vars=' geomap.draw(data,{width:'.$_REQUEST['width'].',height:'.$_REQUEST['height'].',showLegend:true});';

    echo $script .= "<script type='text/javascript' src='http://www.google.com/jsapi'></script>";
    echo $script.="<script type='text/javascript'>
    google.load('visualization', '1', {packages: ['geomap']});

    function drawVisualization() {
      var data = new google.visualization.DataTable();
      data.addRows(50);
      data.addColumn('string', 'Country');
      data.addColumn('number', '" . $variable . "');" . $asscountry . "
      var geomap = new google.visualization.GeoMap(
          document.getElementById('visualization'));
     " . $vars . "
    }
    google.setOnLoadCallback(drawVisualization);
  function loadtab(href,title){
    	  var options = 'sameBox:true width:650px height:370px caption:'+title;

 parent.fb.start(href, options);
}
  </script>";

    echo "<div id=visualization style='cursor:pointer;' onclick=\"return loadtab('" . url($_GET['q'], array('absolute' => true)) . "','`Facts And Figures : " . $variable . " : " . $cnt . "  `')\"></div>";
}



// update profile
function update_profile() {

    global $user, $base_url;
    $data = '

var spath=\'' . $base_url.'/' . '\';
';
    drupal_add_js($data, 'inline');
    drupal_add_js(drupal_get_path('module', 'profiles') . '/js/validate.js');
    drupal_add_js(drupal_get_path('module', 'profiles') . '/js/profile.js');
    
    $update = '';
    $update .= drupal_get_form('user_details');
    
    return $update;
}

function user_details() {
    global $base_url, $user, $apikey, $theme;
    $details = load_user($user->uid);
    $options = array('1' => t(''), '2' => t(''), '0' => t(''));
    $form['#attributes']['enctype'] = "multipart/form-data";
    $form['#attributes']['onsubmit'] = "return validate_reg();";

    $form['username'] = array(
        '#type' => 'textfield',
        '#title' => t(''),
        '#maxlength' => 20,
        '#description' => t(''),
        '#default_value' => variable_get('username', ''),
        '#id' => 'username',
        '#required' => 1,
        '#attributes' => array('class' => 'info','onblur'=>'chk_uname(this.value);'),
    );
    $form['fname'] = array(
        '#type' => 'textfield',
        '#title' => t(''),
        '#maxlength' => 20,
        '#description' => t(' '),
        '#default_value' => variable_get('fname', ''),
        '#id' => 'name',
        '#attributes' => array('class' => 'info'),
    );
    $form['email'] = array(
        '#type' => 'textfield',
        '#title' => t(''),
        '#maxlength' => 50,
        '#description' => t(' '),
        '#default_value' => variable_get('email', ''),
        '#id' => 'email',
        '#required' => 1,
        '#attributes' => array('class' => 'info'),
    );
    $form['gender'] = array(
        '#type' => 'select',
        '#title' => t(''),
        '#options' => array('0' => 'Gender', 1 => 'Male', 2 => 'Female'),
        '#description' => t(' '),
        '#default_value' => variable_get('gender', ''),
        '#id' => 'gender',
        '#attributes' => array('class' => 'info'),
    );
    $form['dob'] = array(
        '#type' => 'textfield',
        '#title' => t(''),
        '#maxlength' => 4,
        '#description' => t(' '),
        '#default_value' => variable_get('dob', ''),
        '#id' => 'year',
        '#attributes' => array('class' => 'info'),
    );

    $form['country'] = array(
        '#type' => 'hidden',
        '#default_value' => variable_get('country', $details->country),
        '#id' => 'country',
        '#attributes' => array('class' => 'info'),
    );
    
    $form['zip'] = array(
        '#type' => 'textfield',
        '#title' => t(''),
        '#maxlength' => 10,
        '#description' => t(''),
        '#default_value' => variable_get('zip', ''),
        '#id' => 'location',
        '#attributes' => array('class' => 'info', 'onblur' => 'get_zip_city(this.value);'),
    );

    $locDetails = $details->city.','.$details->state.','.$details->country;
    
    $form['city-state-country'] = array('#type' => 'markup', '#value' => '<span id="cit-stat">'.$locDetails.'</span>');
    $form['state'] = array(
        '#type' => 'hidden',
        '#default_value' => variable_get('state', $details->state),
        '#id' => 'state',
    );
    $form['city'] = array(
        '#type' => 'hidden',
        '#default_value' => variable_get('city', $details->city),
        '#id' => 'city',
    );
    $form['religion'] = array(
        '#type' => 'select',
        '#title' => t(''),
                        '#options' => array('0' => 'Religion','Christian'=>'Christian (Cath or Prod)','Muslim' => 'Muslim (Suni Shiite)','Hindu' => 'Hindu','Jewish'=>'Jewish','Buddhist'=>'Buddhist','Other'=>'Other'),
        '#description' => t(' '),
        '#default_value' => variable_get('religion', ''),
        '#id' => 'religion',
        '#attributes' => array('class' => 'info'),
    );
    $form['ethnic'] = array(
        '#type' => 'select',
        '#title' => t(''),
        '#options' => array('0' => 'Ethnicity','Caucasian'=>'Caucasian','Black'=>'Black','Asian' => 'Asian','Indian' => 'Indian','Semetic'=>'Semetic','Latin'=>'Latin','Aborigines'=>'Aborigines' ),
        '#description' => t(' '),
        '#default_value' => variable_get('ethinicity', ''),
        '#id' => 'ethnicity',
        '#attributes' => array('class' => 'info'),
    );

    $form['sorient'] = array(
        '#type' => 'select',
        '#title' => t(''),
         '#options' => array('0' => 'Sexual Orientation', 'Straight' => 'Straight', 'Gay' => 'Gay','Bisexual'=>'Bisexual','Transgender'=>'Transgender'),
        '#default_value' => variable_get('sorient', ''),
        '#description' => t(' '),
        '#id' => 'sex',
        '#attributes' => array('class' => 'info'),
    );
        $form['education'] = array(
        '#type' => 'select',
        '#title' => t(''),
        '#options' => array('0' => 'Education Level', 'No High School' => 'No High School', 'High School' => 'High School', 'Technical College' => 'Technical College', 'University' => 'University', 'Masters Degree' => 'Masters Degree'),
        '#description' => t(' '),
        '#default_value' => variable_get('education', ''),
        '#id' => 'education',
        '#attributes' => array('class' => 'info'),
    );
    $form['income'] = array(
        '#type' => 'select',
        '#title' => t(''),
        '#options' => array('0' => 'Select', '$0-$9,999' => '$0-$9,999', '$10,000 - $19,999' => '$10,000 - $19,999','$20,000 - $39,999'=>'$20,000 - $39,999','$40,000 - $69,999'=>'$40,000 - $69,999','$70,000 - $99,999'=>'$70,000 - $99,999','$100,000 - $149,999'=>'$100,000 - $149,999','$150,000 - $299,999'=>'$150,000 - $299,999','>$300,000'=>'>$300,000'),
        '#description' => t(' '),
        '#default_value' => variable_get('income', ''),
        '#id' => 'income',
        '#attributes' => array('class' => 'info'),
    );
    $form['marital'] = array(
        '#type' => 'select',
        '#title' => t(''),
        '#options' => array('0' => 'Select', 'Single' => 'Single', 'Married' => 'Married','Divorced'=>'Divorced','Widow'=>'Widow'),
        '#description' => t(' '),
        '#default_value' => variable_get('marital', ''),
        '#id' => 'marital',
        '#attributes' => array('class' => 'info'),
    );
    $form['bio'] = array(
        '#type' => 'textarea',
        '#title' => t(''),
        '#default_value' => variable_get('description', ''),
        '#cols' => '',
        '#rows' => 1,
        '#description' => t(''),
        '#default_value' => variable_get('bio', ''),
        '#id' => 'bio',
        '#attributes' => array('class' => 'info'),
        '#resizable' => FALSE,
    );
    // set default values
    $form['bio']['#default_value'] = empty($details->bio) ? 'Bio' : $details->bio;

    $form['sorient']['#default_value'] = empty($details->sorient) ? '0' : $details->sorient;
    $form['income']['#default_value'] = empty($details->income) ? '0' : $details->income;
     $form['marital']['#default_value'] = empty($details->marital) ? '0' : $details->marital;
    $form['education']['#default_value'] = empty($details->edu) ? '0' : $details->edu;
    $form['ethnic']['#default_value'] = empty($details->ethnic) ? '0' : $details->ethnic;
    $form['religion']['#default_value'] = empty($details->religion) ? '0' : $details->religion;
    $form['zip']['#default_value'] = empty($details->zip) ? 'Zip code' : $details->zip;
    $form['gender']['#default_value'] = empty($details->gender) ? '0' : $details->gender;
    $form['dob']['#default_value'] = empty($details->dob) ? 'Year OF Birth' : $details->dob;
    $form['email']['#default_value'] = empty($details->mail) ? 'Email' : $details->mail;
    $form['fname']['#default_value'] = empty($details->real_name) ? 'Name' : $details->real_name;
    $form['username']['#default_value'] = empty($details->name) ? 'Username' : $details->name;
    
   
    $form = $form + get_privacy_form();
    

    

    $social = explode('||', $details->social);
    $form['facebook'] = array(
        '#type' => 'textfield',
        '#description' => t(''),
        '#default_value' => variable_get('facebook', $social[0]),
        '#id' => 'face',
        '#attributes' => array('class' => 'info'),
    );
    $form['twitter'] = array(
        '#type' => 'textfield',
        '#description' => t(' '),
        '#default_value' => variable_get('twitter', $social[1]),
        '#id' => 'twitter',
        '#attributes' => array('class' => 'info'),
    );
     $form['myweb'] = array(
        '#type' => 'textfield',
        '#title' => t(''),
        '#description' => t(''),
        '#default_value' => variable_get('myweb', $details->urls),
        '#id' => 'myweb',
        '#attributes' => array('class' => 'info'),
     );   
    
    $form = $form + follow_links_form($form_state, $user->uid);

    $form['merge'] = array('#type' => 'markup', '#value' => '
                
          <div id="divConnect"></div>
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
    </script>
         ');

    //$form['personal_links'] = array('#type' => 'markup', '#value' => '<div class="web-reference-new">');
    $form['notify'] = array(
        '#type' => 'radios',
        '#default_value' => variable_get('notify', $details->notify_etype),
        '#options' => $options,
        );
    // avatar hidden values
    
    $form['img_avt'] = array('#type' => 'hidden', '#default_value' => variable_get('img_avt', $details->image_avatar));
    //$form['image'] = array('#type' => 'textfield', '#default_value' => variable_get('image', $details->image));
    $form['image'] = array('#type' => 'hidden', '#default_value' => $user->picture);
    $form['current_image'] = array('#type' => 'hidden', '#id' => 'curr_avatar', '#default_value' => '');

   

    $form['hiddentop'] = array('#type' => 'markup', '#value' => '<div id="avatar-profile-ele" class="d-header" style="display:none;background-color:white;width:350px;position:absolute;top:200px;left:350px;"><a href="javascript:void(0)" onclick="jQuery(\'#avatar-profile-ele\').slideToggle();update_avatar();" style="float:right">close[X]</a>');
    $form = $form + inc_avatar_form($form, $form_state);
    $form['hiddenbot'] = array('#type' => 'markup', '#value' => '</div>');
    $languages = i18n_language_list();
    $form['default_language'] = array('#type' => 'select', 
                                        '#options' => $languages, 
                                        '#default_value' => $details->language);
    // subscription hidden value
    $form['subscription_email'] = array(
        '#type' => 'textfield',
        '#title' => t(''),
        '#maxlength' => 50,
        '#default_value' => variable_get('email', $user->mail),
        '#id' => 'sub_email',
        '#required' => 1,
        '#attributes' => array('class' => 'upload button'),
    );
    $form['submit'] = array('#type' => 'submit', '#value' => t('Save Changes'), '#id' => 'update_submit', '#attributes' => array('class' => 'submit-issue'));
    
   
    $form = $form + get_avatar_form();
    
    
    return $form;

    
}

function get_privacy_form() {

    global $user;
    $query = "select * from {user_profile} where uid='$user->uid'";
    $fetch = ExecuteQuery($query, "select");
    $options = array('1' => t(''), '2' => t(''), '3' => t(''), '4' => t(''));
    $noOne = array('4' => t(''));
    $query = "select * from {profile_fields} ORDER BY `profile_fields`.`fid` ASC";
    $result = db_query($query);
   
    $form['username_privacy'] = array(
        '#type' => 'markup',
        '#value' => '<div class="form-wra">&nbsp;
                     <div class="clr"></div>
                     </div>',
    );
    while ($meta = db_fetch_object($result)) {
        $col = $fields[] = $meta->name;
        $list = trim($fetch[0][$col]);

        $sel = db_result(db_query("SELECT $col FROM {privacy_settings} WHERE uid = '%d'", $user->uid));
        $sel=empty($sel) ? '1' : $sel;

        if($col!='income'){
        $form[$col . '_privacy'] = array(
            '#type' => 'radios',
            '#default_value' => variable_get($col . '_privacy', $sel),
            '#options' => $options,   
        );
        }else{
        $form[$col . '_privacy'] = array(
            '#type' => 'radios',
            '#default_value' => 4,
            '#options' => $noOne,
            '#checked' => TRUE,
        );
        }
   
       
        $form['div_down'] = array('#type' => 'markup', '#value' => '
          <div class="clr"></div>
       ');
    }

    $form['activity_privacy'] = array(
        '#type' => 'radios',
        '#default_value' => variable_get('activity_privacy', $fetch[0]['question_privacy']),
        '#options' => $options,
        '#prefix' => '<br/><br/><br/><div class="form-wra">',
        '#suffix' => '<div class="clr"></div></div>',
        
    );
    $form['mid_div'] = array('#type' => 'markup', '#value' => '
          <div class="clr"></div>
       ');
    return $form;
}

function get_avatar_form() {
    global $user, $apikey, $theme;
    $form = array();
    drupal_add_js(drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection.js');
    drupal_add_js(drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection_pager.js');
    drupal_add_css(drupal_get_path('module', 'avatar_selection') . '/avatar_selection.css');
    drupal_add_js(drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection_pager.js');
    drupal_set_html_head('<script src="http://cdn.gigya.com/JS/socialize.js?apikey=' . $apikey . '" type="text/javascript"></script>');
    drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection.js';
    $account = load_user($user->uid);
    $data = '
	    var conf =
        {
            APIKey: \'' . $apikey . '\'
        };
var avtar=\'' . $account->avatar . '\';
';
    drupal_add_js($data, 'inline');

    // set the form encoding type
    
    $form['#attributes']['enctype'] = "multipart/form-data";
    $options = array('1' => t('weekly'), '2' => t('monthly'), '0' => t('never'));
    // add a file upload file
    $form['file_upload'] = array(
        '#type' => 'file',
        '#size' => '10',        
        '#prefix' => '<div class="avatar-left"><img src="' . UserPicture_small_src($user->uid, 0).'" /><p>'.t('Select an image file on your computer. (2MB max)').'</p>',
        '#suffix' => '</div>',
    );
    
       $form['oldimg'] = array(
                '#type' => 'hidden',
                '#default_value' => variable_get('oldimg', $user->picture),
                '#id' => 'oldimg',
            );
    $form['avatar_div_close'] = array('#type' => 'markup', '#value' => '<div class="clr"></div>
    </div><div class="clr"></div>');    
    return $form;
}

function user_details_validate($form, &$form_state) {
    global $user;
    $step = $form_state['values']['step'];
    $dob = $form_state['values']['dob'];
    $zip = $form_state['values']['zip'];
    $state = $form_state['values']['state'];
    $uname = $form_state['values']['username'];

    if (!preg_match('/^[A-Za-z0-9_]{5,20}$/i', $uname)) {
        form_set_error('username', t('Username should be Alphabets, numbers and no special characters min 5 and max 20 allowed'));
        $form_state['rebuild'] = TRUE;
    } elseif (db_result(db_query("SELECT COUNT(*) FROM {users} WHERE name = '%s' AND uid!='%d'", $uname, $user->uid))) {
        form_set_error('username', t('Sorry Username already exists try any other combination'));
        $form_state['rebuild'] = TRUE;
    }
    
    if (!empty($dob)) {

        if (!is_numeric($dob) || strlen($dob) != '4') {
            form_set_error('dob', t('Year Of Birth should be Numeric & Proper Format Ex : 1986'));
            $form_state['rebuild'] = TRUE;
        }
    }
    if (!empty($zip)) {
        if (!preg_match('/^[0-9A-Za-z ]+?$/i', $zip)) {
            form_set_error('zip', t('Zip Code should be Proper One & Proper Format Ex : 11010'));
            $form_state['rebuild'] = TRUE;
        } elseif (empty($state)) {
            form_set_error('zip', t('Kindly Recheck your Zip Code, We find its invalid one! '));
            $form_state['rebuild'] = TRUE;
        }
    }
}

function user_details_submit($form, &$form_state) {
    global $user;

    //profile fields update
    _basic_submit($form, $form_state);
    //privacy update
    _privacy_submit($form, $form_state);
    //avatar update
    _avatar_submit($form, $form_state);

    
    /*New SET NOTIFY LOG*/
    $variable = array();
    set_notify_log($user->uid, '', 'update_profile', $variable);
    /*New SET NOTIFY LOG*/


    drupal_set_message(t('Your profile info has been updated'), 'success');
}
