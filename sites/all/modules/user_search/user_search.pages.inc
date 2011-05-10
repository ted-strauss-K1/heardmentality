<?php

function search_results() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

    $flink = '';
    $fetresult = '';
    extract($_REQUEST);
    $page_name = "searchuser"; //  If you use this code with a different page ( or file ) name then change this

    if (strlen($start) > 0 && !is_numeric($start)) {
        echo "Data Error";
        exit;
    }
    $eu = ($start - 0);
    $limit = 14; // No of records to be shown per page.
    $this1 = $eu + $limit;
    $back = $eu - $limit;
    $next = $eu + $limit;
    $fetresult = '';
    if (!isAjax ()) {
        drupal_add_js(drupal_get_path('module', 'user_search') . '/js/search_user.js');
        drupal_add_js(drupal_get_path('module', 'profiles') . '/js/profile.js');
    }

    $name = $_REQUEST['txt_search'];
    $q_country = $_REQUEST['q_country'];
    $q_state = $_REQUEST['q_state'];

    $cid = $_REQUEST['cid'];
    $scid = $_REQUEST['scid'];


    if ($_REQUEST['code'] != '') {
        $code = $_REQUEST['code'];
    }

    $qry = 'where reg.uid=img.uid ';
    if (!empty($name))
        $qry .= "AND (img.real_name LIKE '%" . $name . "%' OR reg.name LIKE '%" . $name . "%' ) ";

    if (!empty($q_country))
        $qry .= "AND (img.country ='" . $q_country . "') ";

    if (!empty($q_state) && $q_state > 0) {
        $query = array('geonameid' => $q_state, 'style' => '', 'lang' => 'en');
        $result = geonames_query('get', $query);

        $state_name = ((!empty($result->results[0]['name'])) ? $result->results[0]['name'] : '');

        $qry .= "AND (img.state ='%" . $state_name . "%') ";
    }
    if (!empty($q_city) && $q_city > 0) {
        $query = array('geonameid' => $q_city, 'style' => '', 'lang' => 'en');
        $result = geonames_query('get', $query);
        $city_name = ((!empty($result->results[0]['name'])) ? $result->results[0]['name'] : '');
        $qry .= "AND (img.city ='%" . $city_name . "%') ";
    }


//SELECT * FROM users reg, user_profile img, follower fol WHERE (fol.cat_id ='1') AND reg.status='1' and reg.uid=fol.uid group by fol.uid
    if ($_REQUEST['cid'] != '') {
        if ($scid != '')
            $c_qry .= "AND (fol.cat_id=$scid)";

        $qry_form = " ,follower fol  $qry AND (fol.cat_id=$cid) AND reg.status=1 and reg.uid=fol.uid $c_qry group by fol.uid";
    }
    else {
        $qry_form = $qry;
    }
    $sel = "SELECT * FROM {users} reg,{user_profile} img  $qry_form";

    //  echo $sel;

    $user_qry = db_query($sel);


    $sel_count = ExecuteQuery($sel, 'norows');


    $sel .= " limit $eu, $limit";


    $sel_search = db_query($sel);

    $incr = 0;

    $fetresult = ' <div class="rleft">
       <!--<span class="padding10">SEARCH RESULTS</span><br />-->
       <div class="clr"></div>
     
       <div class="result-item">
       <div class="rleft">';

    while ($user_result = db_fetch_object($sel_search)) {
        $incr = $incr + 1;
        if ($user->uid != '') {
            //$flink='<a class="linkfol" href="user/'.$user_result->uid.'?act=flag">Follow </a>';
            //$flink='<a class="linkfol" href="'.$gSitePath.'profile/'.$user_result->uid.'">View </a>';
        }
        $gquery = "select ifnull(sum(points),0) as qpt from {tbl_user_points} where uid='" . $user_result->uid . "'";
        $gpoints = db_result(db_query($gquery));
        if ($user_result->gender == 1) {
            $usetype = 'Male';
        } elseif ($user_result->gender == 2) {

            $usetype = 'Female';
        } else {
            $usetype = '<b>--</b>';
        }
        if ($incr == 2) {
            $divider = '<div class="clr"></div>';
        } else {
            $divider = '';
        }

        $fetresult .= load_user_badge($user_result->uid, 1);
    }
    if ($sel_count == 0) {
        $fetresult .= '<div align="center"><b>No Search Results  </b></div>';
    }
    $fetresult .= '</div>
       </div>
     
       <div class="clr"></div>
       </div>  ';
/////////////new sigma
    if ($sel_count > $limit) {


        $fetresult .= "   <div class='page-n' align='center'>
            <ul><li>";
        if ($back >= 0) {
            //href='$page_name?start=$back&$lkr'
            $fetresult .= "<a class='' href='JavaScript:void(0);' id='$back'>Previous</a>";
            //href='$page_name?start=$back&$lkr'
            $fetresult .= "&nbsp;&nbsp;<a class='' href='JavaScript:void(0);' id='$back'><img alt='Previous' src='" . $gSitePath . drupal_get_path('theme', 'newtheme') . "/images/p-l.jpg'></a>";
        }
        $fetresult .= "</li><li>";
        $i = 0;
        $l = 1;
        for ($i = 0; $i < $sel_count; $i = $i + $limit) {
            if ($i <> $eu) {
                //$fetresult .= " <a href='$page_name?start=$i&code=$code&txt_search=$name'>$l</a> ";
                $fetresult .= " <a class='sidelinks' href='JavaScript:void(0)' id='$i'>$l</a> ";
            } else {
                //$fetresult .= "<font color=red>$l</font>";
                $fetresult .= "<font color='black'>$l</font>";
            }
            $l = $l + 1;
        }


        $fetresult .= "</li<li>";
        if ($this1 < $sel_count) {

            //$fetresult .= "<li><a href='$page_name?start=$next&code=$code&txt_search=$name'><img alt='Next' src='".$gSitePath."sites/all/themes/newtheme/images/p-r.jpg'></a></li>";
            //$fetresult .= "&nbsp;&nbsp;<li><a href='$page_name?start=$next&code=$code&txt_search=$name'>Next</a></li>";
            //href='$page_name?start=$next&$lkr'
            $fetresult .= "<a class='sidelinks' href='JavaScript:void(0);' id='$next'><img alt='Next' src='" . $gSitePath . drupal_get_path('theme', 'newtheme') . "/images/p-r.jpg'></a>";
            //href='$page_name?start=$next&$lkr'
            $fetresult .= "&nbsp;&nbsp;<a class='sidelinks' href='JavaScript:void(0)' id='$next'>Next</a>";
        }
        $fetresult .= "</li></ul>
        </div><input type='hidden' name='hid_page' id='hid_page' value=''/>";
    }

    $fetresult .= ' ';

    if (isset($_REQUEST['act']) == 'flag') {
        $mem_id = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);


        $res_num = db_result(db_query("SELECT COUNT(*) from follower  where  follower_id='" . $mem_id . "'  and  uid ='" . $user->uid . "'"));
        if ($res_num == 0) {
            $ins_commg = "insert into   follower (uid,follower_id,follower_status,joindate) values('" . $user->uid . "','" . $mem_id . "','1','" . date('Y-m-d') . "') ";
            $rs_commg = db_query($ins_commg);

            drupal_set_message(t('Successfully Added as Follower'), $type = 'success');
        } else {
            $sel_usermdet = "select * from users  where uid='" . $mem_id . "' ";
            $rs_usernam = db_query($sel_usermdet);
            $namelist = db_fetch_object($rs_usernam);

            drupal_set_message(t('You are already following ' . $namelist->name . '.'), $type = 'error');
        }
    }

    return $fetresult;
}

function category_ajax() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    echo _sidebar_category();
    exit;
}

function categoryuser_ajax() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    echo _sidebaruser_category();
    exit;
}

/*
  function search_user_ajax() {

  // print_r($_REQUEST);
  global $gSitePath, $user, $gDocPath, $base_root, $base_path;

  $flink = '';
  $fetresult = '';
  extract($_REQUEST);
  $page_name = "searchuser"; //  If you use this code with a different page ( or file ) name then change this
  if (isset($_GET['start'])) {
  $start = $_GET['start'];
  } else {
  $start = 0;
  }
  if (strlen($start) > 0 and !is_numeric($start)) {
  echo "Data Error";
  exit;
  }
  $eu = ($start - 0);
  $limit = 14; // No of records to be shown per page.
  $this1 = $eu + $limit;
  $back = $eu - $limit;
  $next = $eu + $limit;
  $fetresult = '';
  //drupal_add_js(drupal_get_path('module', 'user_search') . '/js/search.js');
  drupal_add_js(drupal_get_path('module', 'user_search') . '/js/search_user.js');

  $txt_search = $_REQUEST['txt_search'];
  $name = $_REQUEST['txt_search'];
  $q_country = $_REQUEST['q_country'];
  $q_state = $_REQUEST['q_state'];

  $cid = $_REQUEST['cid'];
  $scid = $_REQUEST['scid'];



  if ($_REQUEST['code'] != '') {
  $code = $_REQUEST['code'];
  }

  $qry = '';
  if ($name != '')
  $qry .= " AND (img.real_name LIKE '" . $name . "%')";

  if ($_REQUEST['code'] != '')
  $qry .= " AND (img.country ='" . $code . "')";

  if ($_REQUEST['q_country'] != '')
  $qry .= " AND (img.country ='" . $q_country . "')";


  if ($_REQUEST['q_state'] != '' && $_REQUEST['q_state'] != 0)
  $qry .= " AND (img.state ='" . $q_state . "')";

  if ($_REQUEST['q_city'] != '')
  $qry .= " AND (img.city ='" . $q_city . "')";



  //SELECT * FROM users reg, user_profile img, follower fol WHERE (fol.cat_id ='1') AND reg.status='1' and reg.uid=fol.uid group by fol.uid
  if ($user->uid != '') {
  if ($_REQUEST['cid'] != '') {

  if ($scid != '')
  $c_qry .= "OR (fol.cat_id=$scid)";

  $qry_form = "img, follower fol where 1 $qry AND (fol.cat_id=$cid) AND reg.status=1 and reg.uid=fol.uid $c_qry group by fol.uid";
  }
  else {
  $qry_form = "img WHERE 1 $qry and img.uid=reg.uid AND reg.status='1'";
  }
  } else {

  if ($_REQUEST['cid'] != '') {
  if ($scid != '')
  $c_qry .= "OR (fol.cat_id=$scid)";

  $qry_form = "img, follower fol where 1 $qry AND (fol.cat_id=$cid) AND reg.status=1 and reg.uid=fol.uid $c_qry group by fol.uid";
  }
  else {
  $qry_form = "img WHERE 1 $qry AND reg.status='1' AND img.uid=reg.uid";
  }
  }
  $sel = "SELECT * FROM {users} reg,{user_profile} $qry_form";


  //echo $sel;

  $user_qry = db_query($sel);


  $sel_count = ExecuteQuery($sel, 'norows');


  if ($user->uid != '') {
  if ($_REQUEST['cid'] != '') {

  if ($scid != '')
  $c_qry .= "OR (fol.cat_id=$scid)";

  $qry_form = "img, follower fol where 1 $qry and (fol.cat_id=$cid) AND reg.status=1 and reg.uid=fol.uid $c_qry group by fol.uid";
  $sel_count = mysql_num_rows(db_query("SELECT count(*) FROM {users} reg,{user_profile} $qry_form"));
  }
  else {

  $qry_form = "img WHERE 1 $qry and img.uid=reg.uid AND reg.status='1'";
  $sel_count = db_result(db_query("SELECT count(*) FROM {users} reg,{user_profile} $qry_form"));
  }


  //$sel_count = db_result(db_query("SELECT COUNT(*) FROM {users} reg,{user_profile} img WHERE $qry reg.uid<>$user->uid and img.uid=reg.uid AND reg.status='1'"));
  } else {
  //  $sel_count = db_result(db_query("SELECT COUNT(*) FROM {users} reg,{user_profile} img WHERE $qry status='1' and img.uid=reg.uid "));

  if ($_REQUEST['cid'] != '') {

  if ($scid != '')
  $c_qry .= "OR (fol.cat_id=$scid)";

  $qry_form = "img, follower fol where $qry (fol.cat_id=$cid) AND reg.status=1 and reg.uid<>$user->uid and reg.uid=fol.uid $c_qry group by fol.uid";
  $sel_count = mysql_num_rows(db_query("SELECT count(*) FROM {users} reg,{user_profile} $qry_form"));
  }
  else {

  $qry_form = "img WHERE $qry reg.uid<>$user->uid and img.uid=reg.uid AND reg.status='1'";
  $sel_count = db_result(db_query("SELECT count(*) FROM {users} reg,{user_profile} $qry_form"));
  }
  }
  $sel .= " limit $eu, $limit";

  //echo $sel;
  $sel_search = db_query($sel);

  $incr = 0;

  $fetresult = ' <div class="rleft">
  <!--<span class="padding10">SEARCH RESULTS</span><br />-->
  <div class="clr"></div>
  <div class="result-item"></div>
  <div class="clr"></div>
  <div class="clr"></div>
  <div class="result-item">
  <div class="rleft">';

  while ($user_result = db_fetch_object($sel_search)) {
  $incr = $incr + 1;
  if ($user->uid != '') {
  //$flink='<a class="linkfol" href="user/'.$user_result->uid.'?act=flag">Follow </a>';
  //$flink='<a class="linkfol" href="'.$gSitePath.'profile/'.$user_result->uid.'">View </a>';
  }
  $gquery = "select ifnull(sum(points),0) as qpt from {tbl_user_points} where uid='" . $user_result->uid . "'";
  $gpoints = db_result(db_query($gquery));
  if ($user_result->gender == 1) {
  $usetype = 'Male';
  } elseif ($user_result->gender == 2) {

  $usetype = 'Female';
  } else {
  $usetype = '<b>--</b>';
  }
  if ($incr == 2) {
  $divider = '<div class="clr"></div>';
  } else {
  $divider = '';
  }

  $fetresult .= ' <div class="prof-it-1">
  <div class="lefimg-it-c"><a href="#" onclick="get_profile_details(' . $user_result->uid . ');" >' . UserPicture($user_result->uid) . '</a></div>
  <div class="ritecont-it-c">
  <div>
  <ul>
  <li><a  onclick="get_profile_details(' . $user_result->uid . ');" style="cursor:pointer" > ' . $user_result->real_name . '</a></li><br />
  <!--<li>' . $gpoints . '</li><br />-->
  ' . updateProfileBadge($user_result->uid) . '
  </ul>
  </div>
  </div>
  <div class="clr"></div>
  </div>';
  }
  if ($sel_count == 0) {
  $fetresult .= '<div align="center"><b>No Search Results  </b></div>';
  }
  $fetresult .= '</div>
  </div>
  <div class="clr"></div>
  <div class="clr"></div>
  <div class="result-item">


  </div>
  <div class="clr"></div>
  </div>  ';

  if ($sel_count > $limit) {


  $fetresult .= "   <div class='page-n' align='center'>
  <ul><li>";
  if ($back >= 0) {
  $fetresult .= "<a href='$page_name?start=$back&code=$code&txt_search=$name'>Previous</a>";
  $fetresult .= "&nbsp;&nbsp;<li><a href='$page_name?start=$back&code=$code&txt_search=$name'><img alt='Previous' src='" . $gSitePath . "sites/all/themes/newtheme/images/p-l.jpg'></a></li>";
  }
  $fetresult .= "</li><li>";
  $i = 0;
  $l = 1;
  for ($i = 0; $i < $sel_count; $i = $i + $limit) {
  if ($i <> $eu) {
  $fetresult .= " <a href='$page_name?start=$i&code=$code&txt_search=$name'>$l</a> ";
  } else {
  $fetresult .= "<font color=red>$l</font>";
  }
  $l = $l + 1;
  }


  $fetresult .= "</li>";
  if ($this1 < $sel_count) {

  $fetresult .= "<li><a href='$page_name?start=$next&code=$code&txt_search=$name'><img alt='Next' src='" . $gSitePath . "sites/all/themes/newtheme/images/p-r.jpg'></a></li>";
  $fetresult .= "&nbsp;&nbsp;<li><a href='$page_name?start=$next&code=$code&txt_search=$name'>Next</a></li>";
  }
  $fetresult .= "</ul>
  </div>";
  }

  $fetresult .= ' ';

  if (isset($_REQUEST['act']) == 'flag') {
  $mem_id = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);


  $res_num = db_result(db_query("SELECT COUNT(*) from follower  where  follower_id='" . $mem_id . "'  and  uid ='" . $user->uid . "'"));
  if ($res_num == 0) {
  $ins_commg = "insert into   follower (uid,follower_id,follower_status,joindate) values('" . $user->uid . "','" . $mem_id . "','1','" . date('Y-m-d') . "') ";
  $rs_commg = db_query($ins_commg);

  drupal_set_message(t('Successfully Added as Follower'), $type = 'success');
  } else {
  $sel_usermdet = "select * from users  where uid='" . $mem_id . "' ";
  $rs_usernam = db_query($sel_usermdet);
  $namelist = db_fetch_object($rs_usernam);

  drupal_set_message(t('You are already following ' . $namelist->name . '.'), $type = 'error');
  }
  }

  echo $fetresult;
  }
 */

function search_user_ajax() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

    $content = '';

    echo $content = search_results();


    die;
}

function question_follow() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $ques = explode("/", $_REQUEST['q']);
    $quesid = explode("=", $ques[2]);


    $res_num = db_result(db_query("SELECT COUNT(*) from follower  where  question_id='" . $quesid[1] . "'  and  uid ='" . $user->uid . "'"));


    if (!$res_num) {
        db_query("insert into follower(uid,question_id)values('" . $user->uid . "','" . $quesid[1] . "')");
        $output = drupal_set_message(t('Questions follows added successfully !'), $type = 'success');
        echo '<script>window.parent.location.href="' . $gSitePath . 'category/";</script>';
    } else {
        $output = drupal_set_message(t('Questions follows already added !'), $type = 'success');
        echo '<script>window.parent.location.href="' . $gSitePath . 'category/";</script>';
    }
}

function question_unfollow() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $ques = explode("/", $_REQUEST['q']);
    $quesid = explode("=", $ques[2]);


    $res_num = db_result(db_query("SELECT COUNT(*) from follower  where  question_id='" . $quesid[1] . "'  and  uid ='" . $user->uid . "'"));


    if ($res_num == 1) {
        db_query("delete from follower where uid='" . $user->uid . "' and question_id='" . $quesid[1] . "'");
        $output = drupal_set_message(t('Questions follows deleted successfully !'), $type = 'success');
        echo '<script>window.parent.location.href="' . $gSitePath . 'category/";</script>';
    }
}

function check_select($gid, $quid) {
    if ($gid == $quid) {

        //$check = "checked='" . checked . "'";
        $check = "checked";
    } else {
        $check = " ";
    }
    return $check;
}

function search_results_ajax() {

    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/wave.js');
    // drupal_add_js(drupal_get_path('module', 'question') . '/scripts/question.js');

    global $gSitePath, $user, $gDocPath, $base_root, $base_path, $apikey;
    $start = '';
    $txt_search = '';
    $cid = '';
    $scid = '';
    $sscid = '';
    $suid = '';
    $lkr = '';
    $tag = '';
    $name = '';
    $fetresult = '';
    $totalvotes = 0;
    $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    //echo $idb;
    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/subtab.js');


    $page_name = "searchquestion";
    if (isset($_GET['start'])) {
        $start = $_GET['start'];
    }

    if (strlen($start) > 0 and !is_numeric($start)) {
        echo "Data Error";
        exit;
    }
    if ($_GET['cid'] != '') {
        $cid = $_GET['cid'];
    }
    if ($_GET['scid'] != '') {
        $scid = $_GET['scid'];
    }
    if ($_GET['sscid'] != '') {
        $scid = $_GET['sscid'];
    }



    $eu = ($start - 0);
    $limit = 10; // No of records to be shown per page.
    $this1 = $eu + $limit;
    $back = $eu - $limit;
    $next = $eu + $limit;

    $sel = facetad_refine();
    $sel_count = $sel['qcnt'];
    $sel['query'] .= " limit  $eu, $limit";

    drupal_add_js(drupal_get_path('module', 'user_search') . '/js/search.js');
    //drupal_add_js(drupal_get_path('module', 'user_search') . '/js/sub.js');
    // echo $sel;
    // $sel_search = ExecuteQuery($sel, "select");
    // print_r($sel_search);

    $fetresult.='<SCRIPT type="text/javascript" lang="javascript" src="http://cdn.gigya.com/JS/socialize.js"></SCRIPT>
	<script>
        var conf =
        {
           // APIKey: \'2_Zfr6Di925xeUYK-BRe1kNOYYclMYDUbGsgb_kF4NqlZaJ4owUytfdi2cnRePUJ_j\'
		   APIKey: \'' . $apikey . '\'
        };

        function onLoad()
        {
            gigya.services.socialize.getUserInfo(conf,{callback:renderUI});


            gigya.services.socialize.addEventHandlers(conf, { onConnect:renderUI, onDisconnect:renderUI}   );

        }
    </script>';
    //echo $sel['query'];
    $sel_search = db_query($sel['query']);
    $i = 0;
    while ($user_result = db_fetch_object($sel_search)) {

        if ($user->uid != '') {
            //$flink='<a class="linkfol" href="'.$gSitePath.''.$user_result->url.'">View More </a>';
        }
        $vans = "select * from {poll_choices} where  nid ='$user_result->qid' order by chvotes desc";

        $vlist = db_query($vans);

        $query = "SELECT nid,SUM(chvotes) as possiblevote FROM poll_choices where nid='$user_result->qid' GROUP BY nid";
        $query_list = db_query($query);
        $fetvot = db_fetch_object($query_list);
        if (!empty($fetvot)) {

            $vot1 = $fetvot->possiblevote;
        }
        $query_sugest = "SELECT qid, SUM(vote) as suggestv FROM suggest_answer where qid='$user_result->qid' GROUP BY qid";
        $query_sugestlist = db_query($query_sugest);
        $fetvotsugest = db_fetch_object($query_sugestlist);
        if (!empty($fetvotsugest)) {
            $vot2 = $fetvotsugest->suggestv;
            $totalvotes = $vot1 + $vot2;
        }
        // alter for $totalvotes
        $ques_count = db_fetch_object(db_query("SELECT count(nid) as qcount FROM `poll_votes` where nid='" . $user_result->qid . "'"));

        // alter for numresum
        $for_count = db_result(db_query("SELECT count(nid) as fcount FROM `content_type_forum` where field_ref_qid_nid='" . $user_result->qid . "' AND field_type_value = '1'"));

        $numresum = db_result(db_query("SELECT COUNT(nid) FROM content_type_forum where  field_ref_qid_nid='$user_result->qid' AND field_type_value = '2'"));
        $posts = $for_count + $numresum;
        $fetresult .= ' <div class="result-item">
	<div class="rleft">
       <div class="titl">
        <form id="answer_frm" name="answer_frm" method="post" action="' . $gSitePath . 'qlite/save">
        <input type="hidden" name="mid" id="mid" value="' . $user_result->qid . '"/>
<a href="' . $gSitePath . $user_result->url . '?ajax=1" style="' . drupal_link_color($user->uid, $user_result->qid) . '">' . htmlentities(rtrim($user_result->question, "?")) . '?</a>
</div>';
//<a href="javascript:void(0);" onclick="get_quest_details(' . $user_result->qid . ',this);" title="'. htmlentities(wordwrap($user_result->question, 40,'<br/>')).'" style="'.drupal_link_color($user->uid,$user_result->qid).'">' . htmlentities(substr(rtrim($user_result->question, "?"),0,70)). '?</a>

        while ($vlistquest = db_fetch_object($vlist)) {

            $sel_qry = db_query("select * from {poll_votes} where nid='" . $user_result->qid . "' and uid='" . $user->uid . "'");
            $get_value = db_fetch_object($sel_qry);
            $check = '';

            if (!empty($get_value)) {
                $sel_ans = db_query("select * from {poll_choices} where chorder='" . $get_value->chorder . "'");
                $get_ans = db_fetch_object($sel_ans);
                $check = check_select($get_ans->chorder, $vlistquest->chorder);
            }

            //  name="answer_al['.$i.']"
            $fetresult .= ' <div class="item1">
                <input name="answer_al[' . $i . ']" id="answer" type="radio"  value="' . $vlistquest->chorder . '" ' . $check . '  />&nbsp;&nbsp;' . $vlistquest->chtext . '</div>';
        }
        $fetresult .= '  <div class="rright">
      <div class="vote-post-outer">
      <div class="vote-post-outer-top">
      </div>   <div class="vote-post-outer-bottom">
      <div align="center" class="vot-t" style="border-right:1px solid black">
      <img src="' . $gSitePath . path_to_theme() . '/images/tick.jpg" alt="img" /> Votes | ' . $ques_count->qcount . '</div>
       <div align="center" class="vot-t">
       <img src="' . $gSitePath . path_to_theme() . '/images/post.jpg" alt="img" /> Posts | ' . $posts . '</div>

      </div>

      </div>

      </div> ';

        $numran = db_result(db_query("SELECT COUNT(*) from {poll_votes} where nid='" . $user_result->qid . "' and uid='" . $user->uid . "'"));
        if ($numran != 0) {
            $query = "select chorder from {poll_votes} where nid='$user_result->qid' AND uid='" . $user->uid . "'";
            $voteid = db_result(db_query($query));
            $fetresult .= ' <div class="item1"><input type="submit" name="change" id="change" value="Change" /><input type="hidden" name="vote_id" value="' . $voteid . '"/> </div></form>';
            //     $optio = '<div align="center" class="share2"><a title="Withdraw Your Answer" class="share-link" onclick="formsubmittype(1,' . $qid . ');" href="javascript:void(0);">Withdraw</a></div>';
        }
        if ($numran == 0) {

            $fetresult .= ' <div class="item1"><input type="submit" name="save" id="save" value="Vote" /> </div></form>';
        }
        // $fetresult .= ' <p><input type="submit" name="save" id="save" value="Vote" /></p></form>';
//        $fol_qry = db_query("SELECT count(*) as count FROM {follower} where uid='" . $user->uid . "'and question_id='" . $user_result->qid . "'");
//        $fol_list = db_fetch_object($fol_qry);
//
//        if ($fol_list->count == 1) {
//            $follow = "UnFollow";
//        }
//        if ($fol_list->count == 0) {
//            $follow = "Follow";
//        }

        $fetresult .= '  </div></div>
       <div class="clr"></div>
';
        $i++;
    }


    if (isset($_REQUEST['cid']) || isset($_REQUEST['scid'])) {


        $lkr = 'cid=' . $cid . '&scid=' . $scid . '&sscid=' . $sscid . '';
    }

    if ($tag != '') {
        $lkr = 'cid=' . $cid . '&scid=' . $scid . '&sscid=' . $sscid . '&tag=' . $tag . '';
    }


    ///////////////////////////////
    if ($sel_count > $limit) { // Let us display bottom links if sufficient records are there for paging
        /////////////// Start the bottom links with Prev and next link with page numbers /////////////////
        $fetresult .= "</div> <div class='result-item factmore'><div class='page-n' align='center'><ul><li>";
        //// if our variable $back is equal to 0 or more then only we will display the link to move back ////////
        if ($back >= 0) {
            //href='$page_name?start=$back&$lkr'
            $fetresult .= "<a class='' href='JavaScript:void(0);' id='$back'>Previous</a>";
            //href='$page_name?start=$back&$lkr'
            $fetresult .= "&nbsp;&nbsp;<a class='' href='JavaScript:void(0);' id='$back'><img alt='Previous' src='" . $gSitePath . drupal_get_path('theme', 'newtheme') . "/images/p-l.jpg'></a>";
        }
        //////////////// Let us display the page links at  center. We will not display the current page as a link ///////////
        $fetresult .= "</li><li>";
        $i = 0;
        $l = 1;
        for ($i = 0; $i < $sel_count; $i = $i + $limit) {
            if ($i <> $eu) {
                //href='$page_name?start=$i&$lkr'
                $fetresult .= " <a class='sidelinks' href='JavaScript:void(0);' id='$i'>$l</a> ";
            } else {
                $fetresult .= "<font color='black'>$l</font>";
            } /// Current page is not displayed as link and given font color red
            $l = $l + 1;
        }


        $fetresult .= "</li<li>";
        ///////////// If we are not in the last page then Next link will be displayed. Here we check that /////
        if ($this1 < $sel_count) {
            //href='$page_name?start=$next&$lkr'
            $fetresult .= "<a class='sidelinks' href='JavaScript:void(0);' id='$next'><img alt='Next' src='" . $gSitePath . drupal_get_path('theme', 'newtheme') . "/images/p-r.jpg'></a>";
            //href='$page_name?start=$next&$lkr'
            $fetresult .= "&nbsp;&nbsp;<a class='sidelinks' href='JavaScript:void(0);' id='$next'>Next</a>";
        }
        $fetresult .= "</li></ul></div><input type='hidden' name='hid_page' id='hid_page' value=''/>";
    }

    if ($sel_count == 0) {
        $fetresult .= ' <div  align="center" class="result-item"><b>No Search Results </b></div>';
    }

    echo $fetresult;
}

function search_results_question() {
    // print_r($_REQUEST);
    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/wave.js');
    //drupal_add_js(drupal_get_path('module', 'question') . '/scripts/question.js');

    global $gSitePath, $user, $gDocPath, $base_root, $base_path, $apikey;
    $start = '';
    $txt_search = '';
    $cid = '';
    $scid = '';
    $sscid = '';
    $suid = '';
    $lkr = '';
    $tag = '';
    $name = '';
    $fetresult = '';
    $totalvotes = 0;
    $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    //echo $idb;
    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/subtab.js');


    //  $page_name = "searchquestion";
    if (isset($_GET['start'])) {
        $start = $_GET['start'];
    }

    if (strlen($start) > 0 and !is_numeric($start)) {
        echo "Data Error";
        exit;
    }
    if ($_GET['cid'] != '') {
        $cid = $_GET['cid'];
    }
    if ($_GET['scid'] != '') {
        $scid = $_GET['scid'];
    }
    if ($_GET['sscid'] != '') {
        $scid = $_GET['sscid'];
    }


    $eu = ($start - 0);
    $limit = 10; // No of records to be shown per page.
    $this1 = $eu + $limit;
    $back = $eu - $limit;
    $next = $eu + $limit;

    $sel = facetad_refine();
    $sel_count = $sel['qcnt'];
    $sel['query'] .= " limit  $eu, $limit";

    drupal_add_js(drupal_get_path('module', 'user_search') . '/js/search.js');
    //drupal_add_js(drupal_get_path('module', 'user_search') . '/js/sub.js');
    // echo $sel;
    // $sel_search = ExecuteQuery($sel, "select");
    // print_r($sel_search);
    //echo $sel['query'];
    $sel_search = db_query($sel['query']);
    $i = 0;
    while ($user_result = db_fetch_object($sel_search)) {

        if ($user->uid != '') {
            //$flink='<a class="linkfol" href="'.$gSitePath.''.$user_result->url.'">View More </a>';
        }
        $vans = "select * from {poll_choices} where  nid ='$user_result->qid' order by chvotes desc";

        $vlist = db_query($vans);

        $query = "SELECT nid,SUM(chvotes) as possiblevote FROM poll_choices where nid='$user_result->qid' GROUP BY nid";
        $query_list = db_query($query);
        $fetvot = db_fetch_object($query_list);
        if (!empty($fetvot)) {

            $vot1 = $fetvot->possiblevote;
        }
        $query_sugest = "SELECT qid, SUM(vote) as suggestv FROM suggest_answer where qid='$user_result->qid' GROUP BY qid";
        $query_sugestlist = db_query($query_sugest);
        $fetvotsugest = db_fetch_object($query_sugestlist);
        if (!empty($fetvotsugest)) {
            $vot2 = $fetvotsugest->suggestv;
            $totalvotes = $vot1 + $vot2;
        }
        // alter for $totalvotes
        $ques_count = db_fetch_object(db_query("SELECT count(nid) as qcount FROM `poll_votes` where nid='" . $user_result->qid . "'"));

        // alter for numresum
        $for_count = db_result(db_query("SELECT count(nid) as fcount FROM `content_type_forum` where field_ref_qid_nid='" . $user_result->qid . "' AND field_type_value = '1'"));

        $numresum = db_result(db_query("SELECT COUNT(nid) FROM content_type_forum where  field_ref_qid_nid='$user_result->qid' AND field_type_value = '2'"));
        $posts = $for_count + $numresum;
        $fetresult .= ' <div class="result-item">
	<div class="rleft">
       <div class="titl">
        <form id="answer_frm" name="answer_frm" method="post" action="' . $gSitePath . 'qlite/save">
        <input type="hidden" name="mid" id="mid" value="' . $user_result->qid . '"/>
<a href="' . $gSitePath . $user_result->url . '?ajax=1" style="' . drupal_link_color($user->uid, $user_result->qid) . '">' . htmlentities(rtrim($user_result->question, "?")) . '?</a>
</div>';
//<a href="javascript:void(0);" onclick="get_quest_details(' . $user_result->qid . ',this);" title="'. htmlentities(wordwrap($user_result->question, 40,'<br/>')).'" style="'.drupal_link_color($user->uid,$user_result->qid).'">' . htmlentities(substr(rtrim($user_result->question, "?"),0,70)). '?</a>

        while ($vlistquest = db_fetch_object($vlist)) {

            $sel_qry = db_query("select * from {poll_votes} where nid='" . $user_result->qid . "' and uid='" . $user->uid . "'");
            $get_value = db_fetch_object($sel_qry);
            $check = '';
            
            if (!empty($get_value)) {
                $sel_ans = db_query("select * from {poll_choices} where chorder='" . $get_value->chorder . "'");
                $get_ans = db_fetch_object($sel_ans);
                $check = check_select($get_ans->chorder, $vlistquest->chorder);
            }
            
            //  name="answer_al['.$i.']"
            $fetresult .= ' <div class="item1">
                <input name="answer_al[' . $i . ']" id="answer" type="radio"  value="' . $vlistquest->chorder . '" ' . $check . '  />&nbsp;&nbsp;' . $vlistquest->chtext . '</div>';
        }
        $fetresult .= '  <div class="rright">
      <div class="vote-post-outer">
      <div class="vote-post-outer-top">
      </div>   <div class="vote-post-outer-bottom">
      <div align="center" class="vot-t" style="border-right:1px solid black">
      <img src="' . $gSitePath . path_to_theme() . '/images/tick.jpg" alt="img" /> Votes | ' . $ques_count->qcount . '</div>
       <div align="center" class="vot-t">
       <img src="' . $gSitePath . path_to_theme() . '/images/post.jpg" alt="img" /> Posts | ' . $posts . '</div>

      </div>

      </div>

      </div> ';

        $numran = db_result(db_query("SELECT COUNT(*) from {poll_votes} where nid='" . $user_result->qid . "' and uid='" . $user->uid . "'"));
        if ($numran != 0) {
            $query = "select chorder from {poll_votes} where nid='$user_result->qid' AND uid='" . $user->uid . "'";
            $voteid = db_result(db_query($query));
            $fetresult .= ' <div class="item1"><input type="submit" name="change" id="change" value="Change" /><input type="hidden" name="vote_id" value="' . $voteid . '"/> </div></form>';
            //     $optio = '<div align="center" class="share2"><a title="Withdraw Your Answer" class="share-link" onclick="formsubmittype(1,' . $qid . ');" href="javascript:void(0);">Withdraw</a></div>';
        }
        if ($numran == 0) {

            $fetresult .= ' <div class="item1"><input type="submit" name="save" id="save" value="Vote" /> </div></form>';
        }
        // $fetresult .= ' <p><input type="submit" name="save" id="save" value="Vote" /></p></form>';
//        $fol_qry = db_query("SELECT count(*) as count FROM {follower} where uid='" . $user->uid . "'and question_id='" . $user_result->qid . "'");
//        $fol_list = db_fetch_object($fol_qry);
//
//        if ($fol_list->count == 1) {
//            $follow = "UnFollow";
//        }
//        if ($fol_list->count == 0) {
//            $follow = "Follow";
//        }

        $fetresult .= '  </div></div>
       <div class="clr"></div>
';
        $i++;
    }


    if (isset($_REQUEST['cid']) || isset($_REQUEST['scid'])) {


        $lkr = 'cid=' . $cid . '&scid=' . $scid . '&sscid=' . $sscid . '';
    }

    if ($tag != '') {
        $lkr = 'cid=' . $cid . '&scid=' . $scid . '&sscid=' . $sscid . '&tag=' . $tag . '';
    }


    /////////////////////////////// sigma pagination
    if ($sel_count > $limit) { // Let us display bottom links if sufficient records are there for paging
        /////////////// Start the bottom links with Prev and next link with page numbers /////////////////
        $fetresult .= " <div class='result-item factmore'><div class='page-n' align='center'><ul><li>";
        //// if our variable $back is equal to 0 or more then only we will display the link to move back ////////
        if ($back >= 0) {
            //href='$page_name?start=$back&$lkr'
            $fetresult .= "<a class='' href='JavaScript:void(0);' id='$back'>Previous</a>";
            //href='$page_name?start=$back&$lkr'
            $fetresult .= "&nbsp;&nbsp;<a class='' href='JavaScript:void(0);' id='$back'><img alt='Previous' src='" . $gSitePath . "sites/all/themes/newtheme/images/p-l.jpg'></a>";
        }
        //////////////// Let us display the page links at  center. We will not display the current page as a link ///////////
        $fetresult .= "</li><li>";
        $i = 0;
        $l = 1;
        for ($i = 0; $i < $sel_count; $i = $i + $limit) {
            if ($i <> $eu) {
                //href='$page_name?start=$i&$lkr'
                $fetresult .= " <a class='sidelinks' href='JavaScript:void(0)' id='$i'>$l</a> ";
            } else {
                $fetresult .= "<font color='black'>$l</font>";
            } /// Current page is not displayed as link and given font color red
            $l = $l + 1;
        }


        $fetresult .= "</li<li>";
        ///////////// If we are not in the last page then Next link will be displayed. Here we check that /////
        if ($this1 < $sel_count) {
            //href='$page_name?start=$next&$lkr'
            $fetresult .= "<a class='sidelinks' href='JavaScript:void(0);' id='$next'><img alt='Next' src='" . $gSitePath . "sites/all/themes/newtheme/images/p-r.jpg'></a>";
            //href='$page_name?start=$next&$lkr'
            $fetresult .= "&nbsp;&nbsp;<a class='sidelinks' href='JavaScript:void(0)' id='$next'>Next</a>";
        }
        $fetresult .= "</li></ul></div></div><input type='hidden' name='hid_page' id='hid_page' value=''/>";
    }

    if ($sel_count == 0) {
        $fetresult .= ' <div  align="center" class="result-item"><b>No Search Results </b></div>';
    }
    if (isAjax ())
        echo $fetresult;
    else
        return $fetresult;
}

function user_follower() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

    $follid = (int) substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    $follower .= '
        <script>
        var gSitePath="' . $gSitePath . '";
</script>
        	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('theme', 'newtheme') .'/scripts/jquery1.4.js"></script>
      	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'profiles') . '/js/profile.js"></script>
  <link rel="stylesheet" href="' . $gSitePath . 'modules/system/system.css" type="text/css" />
		<link rel="stylesheet" href="' . $gSitePath . path_to_theme() . '/css/css.css" type="text/css" />
                    <link rel="stylesheet" href="' . $gSitePath . path_to_theme() . '/lib/jquery.tab.css" type="text/css" />
      
        <div class="facttop">FOLLOWERS</div>
	';


    if ($_REQUEST['act'] == "del") {
        $del_blog = "update  follower  set follower_status='" . $_REQUEST['block'] . "' where  id='" . $follid . "' ";
        $rs_blog_del = db_query($del_blog);
        drupal_set_message(t('Updated Successfully '), $type = 'success');
        drupal_goto("follower/");
    }
    // get followers for this user
//        $followers = _activity_heartbeat_related_uid_info($user->uid);
//        $countrowsm = count($followers);


    if (!empty($follid)) {
    $followers = user_relationships_load($param = array("approved" => 1, "requestee_id" => $follid, 'rtid' => 1), $options = array('include_user_info' => 1, 'order' => 1, 'limit' => '10'), $reset = FALSE);
    $countrowsm = count($followers);
        //echo '<pre>';
        //print_r($followers);
        $follower.= '<div class="following">';
        $i = 0;
        foreach ($followers as $rtid => $relationship) {
            //echo '<pre>';
            //print_r($relationship);
            $user_namelistf = load_user($relationship->requester_id);


            $user_namelistf->name;

            if ($follid == $user->uid) {
                $flink1 = '<a style="color:#F37321;" onclick="blockandunblock(' . $relationship->rid . ',' . $relationship->requester_id . ',1,1)" >UnBlock</a>';
                $flink2 = '<a style="color:#F37321;" onclick="blockandunblock(' . $relationship->rid . ',' . $relationship->requester_id . ',0,1)" >Block</a>';
                if ($relationship->flags == 0) {
                    $input = '<span style="padding-left:17px;">&nbsp;</span>';
                } else {
                    $input = '<input type="checkbox" name="muid[]"  value="' . $relationship->requester_id . '"/> &nbsp;';
                }
            }
            if ($relationship->flags == 0) {
                $followeru = '<div class="contact-user-list"  id="list-' . $relationship->rid . '">' . $input . '<a href="' . $gSitePath . 'profile/' . $user_namelistf->name . '">' . UserPicture_small($relationship->requester_id) . $user_namelistf->name . ' </a> ' . $flink1 . '</div>';
            } else {
                $followeru = '<div class="contact-user-list"  id="list-' . $relationship->rid . '">' . $input . '<a href="' . $gSitePath . 'profile/' . $user_namelistf->name . '">' . UserPicture_small($relationship->requester_id) . $user_namelistf->name . ' </a> ' . $flink2 . '</div>';
            }

            $follow .= '' . $followeru . '';
        }


        if ($countrowsm == 0) {

            $follower .= '<span style="padding-left:17px;">No Followers Found</span> ';
        } elseif ($user->uid == $follid) {
            $follower.='  <div class="clear"><ul class="subtabs"><li>Select</li> <li><a href="#" onclick="chk_all(1);";>All</a> </li><li><a href="#" onclick="chk_all(0);";>None</a></li><li><a href="#" onclick="enable_form(1,this);";>Send Message</a><li><li></li></ul></div>
<form name="frmsgform" id="frmsgform" action="' . $gSitePath . 'postmessage" method="POST">' . $follow . '
     <div align="left" style="display:none;" id="frmsgbox"><div class="facttop2">SEND MESSAGE</div><br><textarea id="msgs" row="17" cols="55" name="frmsgs"></textarea><input type="hidden" value="37" name="actions" id="actions"><br><br><input type="button" value="sendmessage" id="usmsg">&nbsp; <input type="button" onclick="rel_msg(0);"  value="cancel"/></div>

</form>
';
        }
    } else {
        $follower = ' No Records';
    }

//    if (!empty($follid)) {
//        $follower .= '<div class="following">';
//        $sel_pro = "select * from follower  where follower_id='" . $follid . "'  ";
//        $rs_follower = db_query($sel_pro);
//        $countrowsm = db_result(db_query("SELECT COUNT(*) from follower  where follower_id='" . $follid . "' "));
//        $followeru = '';
//
//        while ($follower_resultfuser = db_fetch_object($rs_follower)) {
//
//            // $sel_ulist="select * from users  where uid='".$follower_resultfuser->uid."' ";
//            $sel_ulist = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $follower_resultfuser->uid . "'";
//            $rs_umlog = db_query($sel_ulist);
//            $user_namelistf = db_fetch_object($rs_umlog);
//
//
//            $user_namelistf->name;
//
//            if ($follid == $user->uid) {
//                $flink1 = '<a style="color:#F37321;" onclick="blockandunblock(' . $follower_resultfuser->id . ',' . $follower_resultfuser->uid . ',1,1)" >UnBlock</a>';
//                $flink2 = '<a style="color:#F37321;" onclick="blockandunblock(' . $follower_resultfuser->id . ',' . $follower_resultfuser->uid . ',0,1)" >Block</a>';
//                if ($follower_resultfuser->follower_status == 0) {
//                    $input = '<span style="padding-left:17px;">&nbsp;</span>';
//                } else {
//                    $input = '<input type="checkbox" name="muid"  value="' . $follower_resultfuser->id . '"/> &nbsp;';
//                }
//            }
//            if ($follower_resultfuser->follower_status == 0) {
//                $followeru = '<div class="contact-user-list"  id="list-' . $follower_resultfuser->id . '">' . $input . '<a href="' . $gSitePath . 'profile/' . $user_namelistf->name . '">' . UserPicture_small($follower_resultfuser->uid) . $user_namelistf->name . ' </a> ' . $flink1 . '</div>';
//            } else {
//                $followeru = '<div  class="contact-user-list"   id="list-' . $follower_resultfuser->id . '">' . $input . '<a href="' . $gSitePath . 'profile/' . $user_namelistf->name . '">' . UserPicture_small($follower_resultfuser->uid) . $user_namelistf->name . ' </a> ' . $flink2 . '</div>';
//            }
//
//            $follow .= '' . $followeru . '';
//            //$followeru[]='<a href="'.$gSitePath.'profile/'.$user_namelistf->name.'">'.$user_namelistf->name.' </a><br>';
//        }
//
//        if ($countrowsm == 0) {
//
//            $follower .= '<span style="padding-left:17px;">No Followers Found</span> ';
//        } elseif ($user->uid == $follid) {
//            $follower.='  <div class="clear"><ul class="subtabs"><li>Select</li> <li><a href="#" onclick="chk_all(1);";>All</a> </li><li><a href="#" onclick="chk_all(0);";>None</a></li><li><a href="#" onclick="enable_form(1,this);";>Send Message</a><li><li></li></ul></div>
//<form name="frmsgform" id="frmsgform" action="' . $gSitePath . 'postmessage" method="POST">' . $follow . '
//     <div align="left" style="display:none;" id="frmsgbox"><div class="facttop2">SEND MESSAGE</div><br><textarea id="msgs" row="17" cols="55" name="frmsgs"></textarea><input type="hidden" value="37" name="actions" id="actions"><br><br><input type="button" value="sendmessage" id="usmsg">&nbsp; <input type="button" onclick="rel_msg(0);"  value="cancel"/></div>
//
//</form>
//';
//        }
//    } else {
//
//        $follower = ' No Records';
//    }



    echo $follower;
}

function user_following() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $follid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $following = '<script type="text/javascript">
	window.addEvent(\'domready\',function() {
	$$(\'a.delete\').each(function(el) {
		el.addEvent(\'click\',function(e) {
			e.stop();
			var parent = el.getParent(\'div\');
			var request = new Request({
				url: \'' . $gSitePath . 'savefollowing\',
				link: \'chain\',
				method: \'get\',
				data: {
					\'delete\': parent.get(\'id\').replace(\'record-\',\'\'),
					ajax: 1
				},
				onRequest: function() {
					new Fx.Tween(parent,{
						duration:300
					}).start(\'background-color\', \'#fb6c6c\');
				},
				onSuccess: function() {
					new Fx.Slide(parent,{
						duration:300,
						onComplete: function() {
							parent.dispose();
						}
					}).slideOut();
				}
			}).send();
		});
	});
});
	
	</script>
	';

    $following .= '<div class="following">';
    $sel_pro = "select * from follower  where uid='" . $follid . "'  and follower_status='1' ";
    $rs_following = db_query($sel_pro);
    $countrows = db_result(db_query("SELECT COUNT(*) from follower  where uid='" . $follid . "'  and follower_status='1'"));
    while ($following_result = db_fetch_object($rs_following)) {
        // $sel_userm="select * from users  where uid='".$following_result->follower_id."' ";
        $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $following_result->follower_id . "'";
        $rs_userm = db_query($sel_userm);
        $user_namelist = db_fetch_object($rs_userm);
        if ($follid == $user->uid) {
            $linkj = '<a href="?delete=' . $following_result->id . '" class="delete">Unfollow</a>';
        }
        $following .= '<div class="record" id="record-' . $following_result->id . '"><strong>' . $user_namelist->real_name . '</strong> ' . $linkj . ' </div>';
    }
    if ($countrows == 0) {

        $following .= ' No Records';
    }
    echo $following;
}

function suggest_follow() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $sel_flow = "select * from follower  where uid='" . $user->uid . "'  and follower_status='1' ";
    $rs_folwin = db_query($sel_flow);
    $array2 = array();
    $array1 = array();
    while ($flwing_result = db_fetch_object($rs_folwin)) {

        array_push($array2, $flwing_result->follower_id);

        $sel_suge = "select * from follower  where uid='" . $flwing_result->follower_id . "' and follower_id!='" . $user->uid . "' limit 0,5";
        $rs_suges = db_query($sel_suge);

        while ($suggest_list = db_fetch_object($rs_suges)) {

            //echo $suggest_list->follower_id;
            array_push($array1, $suggest_list->follower_id);
        }
    }


    $reult = array_diff($array1, $array2);


    $result_array = array_values($reult);
    if (count($result_array) != 0) {
        $suggest_follow = '
		<div id="container">
		<div class="feature">
		<div class="l col">
		<ul>';


        for ($m = 0; $m < count($result_array); $m++) {
            $user_listsm = "select * from {users} where status='1' and uid='$result_array[$m]'";
            $user_qrylist = db_query($user_listsm);
            $user_resultry = db_fetch_object($user_qrylist);

            $suggest_follow .= '<li>
	<h3><a href="' . $gSitePath . 'profile/' . $user_resultry->name . '">' . $user_resultry->name . '</a>      </h3>';
        }


        $suggest_follow .= '</ul></div>
	</div>
	</div>
	';
    } else {
        //////////////////// Maximum User Posted Questions//////////////////////


        $qusetion_user = "SELECT uid, count( uid )FROM question GROUP BY uid limit 0, 10";

        $rs_user_quest = db_query($qusetion_user);
        $quid = array();
        while ($question_list_user = db_fetch_object($rs_user_quest)) {


            array_push($quid, $question_list_user->uid);
        }

        //print_r($quid);
        //	print_r($array1);
        $reultss = array_diff($quid, $array1);
        //print_r($reultss);


        $result_array_quest = array_values($reultss);
        //print_r($result_array_quest);

        $suggest_follow .= '<ul>';

        for ($t = 0; $t < count($result_array_quest); $t++) {
            if ($result_array_quest[$t] != $user - uid) {
                $user_quest = "select * from {users} where status='1' and uid='$result_array_quest[$t]' ";
                $user_qryqlist = db_query($user_quest);
                $user_resultrym = db_fetch_object($user_qryqlist);

                $suggest_follow .= '<li>
	<h3><a href="' . $gSitePath . 'user/' . $user_resultrym->uid . '">' . $user_resultrym->name . '</a>      </h3>
	<h4>' . $user_resultrym->mail . '</h4>
	
	</li><a class="linkfol" href="follow/' . $user_resultrym->uid . '?act=flag">Follow </a>';
            }
        }


        $suggest_follow .= '</ul>
	</div>
	</div>
	</div>';
    }
    //echo $suggest_follow;


    if ($_REQUEST['act'] == 'flag') {
        $mem_id = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);


        $res_num = db_result(db_query("SELECT COUNT(*) from follower  where  follower_id='" . $mem_id . "'  and  uid ='" . $user->uid . "'"));

        if ($res_num == 0) {
            $ins_commg = "insert into   follower (uid,follower_id,follower_status,joindate) values('" . $user->uid . "','" . $mem_id . "','1','" . date('Y-m-d') . "') ";
            $rs_commg = db_query($ins_commg);

            drupal_set_message(t('Successfully Added as Follower'), $type = 'success');
        } else {
            $sel_usermdet = "select * from users  where uid='" . $mem_id . "' ";
            $rs_usernam = db_query($sel_usermdet);
            $namelist = db_fetch_object($rs_usernam);

            drupal_set_message(t('You are already following ' . $namelist->name . '.'), $type = 'error');
        }
        drupal_goto("suggest/follow");
    }

    $numt = count($result_array_quest);
    $numi = count($result_array);
    if (($numt == 0) && ($numi == 0)) {
        $suggest_follow .= 'No suggested Users';
    }
    return $suggest_follow;
}

function save_follow() {

    $follid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    if (isset($_GET['delete'])) {
        $query = 'DELETE FROM follower WHERE id = ' . (int) $_GET['delete'];
        $result = db_query($query);
    }
}

function save_follower() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $follid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    if (isset($_GET['action'])) {
        //$del_blog = "update  follower  set follower_status='" . $_REQUEST['blk'] . "' where  id='" . $_GET['action'] . "' ";
        $del_blog = "update  user_relationships  set flags='" . $_REQUEST['blk'] . "' where  rid='" . $_GET['action'] . "' ";
        $rs_blog_del = db_query($del_blog);


        $sel_userms = "select * from users  where uid='" . $_GET['usid'] . "' ";
        $rs_userms = db_query($sel_userms);
        $resulrnames = db_fetch_object($rs_userms);
        if ($_REQUEST['blk'] == 0) {
            $blkid = '1';
            $valss = 'UnBlock';

            $input = ($_REQUEST['show']) ? '<span style="padding-left:17px;">&nbsp;</span>' : '';
            if ($resulrnames->notify_itype == 1) {
                $insert_notify = db_query("insert into notification (uid,is_block,is_user,node_id) values('" . $_GET['usid'] . "','1','1','" . $user->uid . "' ");
            }
            if ($resulrnames->notify_etype == 1) {
                $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='2'";
                $rs_mgmt = db_query($sel_user_cmt);
                $list_content = db_fetch_object($rs_mgmt);
                $contentm = str_replace("#uname#", $resulrnames->name, $list_content->content);
                $contentm = str_replace("#anothername#", $user->name, $contentm);
                //echo  $contentm;
                $subjects = $list_content->subject;
                $mail_success = htmlmail_function($resulrnames->mail, $subjects, $contentm, '');
            }
        } else {
            $valss = 'Block';
            $blkid = '0';
            $input = ($_REQUEST['show']) ? '<input type="checkbox" name="muid"  value="' . $_REQUEST['usid'] . '"/> &nbsp;' : '';
        }
        echo '<div id="' . $_REQUEST['ids'] . '" > ' . $input . '<a href="' . $gSitePath . 'profile/' . $resulrnames->name . '">' . UserPicture_small($resulrnames->uid) . $resulrnames->name . '</a>&nbsp; <a onclick="blockandunblock(' . $_GET['action'] . ',' . $_GET['usid'] . ',' . $blkid . ',' . $_REQUEST['show'] . ')" >' . $valss . '</a>

</div>';
    }
}

function followerlist($umid) {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

    $sel_listf = "select * from follower  where follower_id='" . $umid . "' AND uid>0  limit 0,5  ";
    $rs_followerf = db_query($sel_listf);

    $numfoll = db_result(db_query("SELECT COUNT(*)  from follower  where follower_id='" . $umid . "' AND uid>0  "));

    $followeru = array();
    while ($follower_resultfuser = db_fetch_object($rs_followerf)) {

        // $sel_ulist="select * from users  where uid='".$follower_resultfuser->uid."' ";
        $sel_ulist = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $follower_resultfuser->uid . "'";
        $rs_umlog = db_query($sel_ulist);
        $user_namelistf = db_fetch_object($rs_umlog);


        $user_namelistf->name;

        if ($umid == $user->uid) {
            $flink1 = '<a style="color:#F37321;" onclick="blockandunblock(' . $follower_resultfuser->id . ',' . $follower_resultfuser->uid . ',1,0)" >UnBlock</a>';
            $flink2 = '<a style="color:#F37321;" onclick="blockandunblock(' . $follower_resultfuser->id . ',' . $follower_resultfuser->uid . ',0,0)" >Block</a>';
        }

        $bubble = load_bubble($user_namelistf->uid);
        if ($follower_resultfuser->follower_status == 0) {
            $followeru[] = '<li  id="list-' . $follower_resultfuser->id . '"><a href="' . $gSitePath . 'profile/' . $user_namelistf->name . '" rel=\'' . $bubble . '\'>' . UserPicture_small($follower_resultfuser->uid) . '</a></li>';
        } else {

            $followeru[] = '<li  id="list-' . $follower_resultfuser->id . '"><a href="' . $gSitePath . 'profile/' . $user_namelistf->name . '" rel=\'' . $bubble . '\'>' . UserPicture_small($follower_resultfuser->uid) . '</a></li>';
        }
    }

    if ($numfoll > 5) {
        $followeru[] .= '<a style="color:#F37321;" href="javascript:void(0);" onclick="loadfollower(\'' . $gSitePath . 'follower/' . $umid . '\',\'Follower\');">More</a>';
    }
    if ($numfoll == 0) {
        $followeru[] .= '<span style="padding-left:17px;">No Followers Yet</span>';
    }


    return $followeru;
}

function followinglist($uids) {

    global $gSitePath, $user, $gDocPath, $base_root;


    $sel_list = "select * from follower  where uid='" . $uids . "'  and follower_status='1' limit 0,5";
    $rs_foll_list = db_query($sel_list);
    $numfolls = db_result(db_query("SELECT COUNT(*)  from follower  where uid='" . $uids . "'  and follower_status='1'  "));
    $following = array();

    while ($following_list = db_fetch_object($rs_foll_list)) {

        if ($uids == $user->uid) {
            $flinks = '<a onclick="deletefollowing(' . $following_list->id . ')" style="color:#F37321;" >Unfollow</a>';
        }
        //	 $sel_userm="select * from users  where uid='".$following_list->follower_id."' ";
        $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $following_list->follower_id . "'";
        $rs_userm = db_query($sel_userm);
        $user_namelist = db_fetch_object($rs_userm);

        $bubble = load_bubble($following_list->follower_id);

        $following[] = '<li  id="show-' . $following_list->id . '"><a rel=\'' . $bubble . '\' href="' . $gSitePath . 'profile/' . $user_namelist->name . '">' . UserPicture_small($following_list->follower_id) . '</a></li>';
    }
    if ($numfolls > 5) {
        $following[] .= '<a style="color:#F37321;" onclick="loadfollowing(\'' . $gSitePath . 'following/' . $uids . '\',\'Following\');">More</a>';
    }
    if ($numfolls == 0) {
        $following[] .= '<span style="padding-left:17px;">Please Follow People</span>';
    }
    return $following;
}

function activities($uid = '') {
    drupal_set_title('Recent Activities');
    global $gSitePath, $user, $gDocPath, $base_root;
    //$uid = $user->uid;


    $strReturn = '<div class="history-tab">';
    //Questions
    $selQ = "(select 1 as tbl,qid,date_added as dat,0 as vars  from {question} where uid='$uid' ORDER BY qid DESC) union
	(select 2 as tbl,qid,vote_pdate as dat,0 as vars  from {possible_answer_vote} where uid='$uid') union
	(select 3 as tbl,qid_rid as qid,date_added as dat,title as vars  from {forum_wave} where uid='$uid' ) union
	(select 4 as tbl,f.qid_rid as qid,w.date_added as dat,wavelet as vars  from {forum_wavelets} w join {forum_wave} as f on f.fid=w.wid where w.uid='$uid' ) union
	(select 5 as tbl,f.qid_rid as qid,l.date_added as dat,f.title as vars  from {forumwave_like} as l join {forum_wave} as f on f.fid=l.wid where l.uid='$uid' ) union
	(select 6 as tbl,u.image_url as qid,f.joindate as dat,u.real_name as vars from {follower} as f join {user_profile} as u on u.uid=f.uid where f.follower_id='$uid' )union
	(select 7 as tbl,qid,posted_date as dat,0 as vars  from {resource} where uid='$uid') union
	(select 8 as tbl,qid,vote_date as dat,0 as vars from {suggest_answer_vote} where uid='$uid') union
	(select 9 as tbl,badge as qid,date_added as dat,badge as vars from {user_badges} where uid='$uid')
	ORDER BY dat DESC LIMIT 0,50 ";
    $fetch = ExecuteQuery($selQ, "select");


    $strReturn.='';

    if (!empty($fetch)) {



        foreach ($fetch as $list) {


            $type = $list['tbl'];

            switch ($type) {


                case '1':
                    //questions
                    $quest = get_question($list['qid']);
                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>Asked</b></span> <span><a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '2':
                    //answered

                    $quest = get_question($list['qid']);
                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>Answered</b></span> <span><a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }

                    break;
                case '3':
                    //New Wave Post
                    $quest = get_question($list['qid']);

                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>New Wave</b></span> <span>' . $list['vars'] . '<span> <b>for</b>  <a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '4':
                    $quest = get_question($list['qid']);
                    //new wavelet
                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>New Wavelets</b></span> <span>' . $list['vars'] . '<span> <b>for</b> Wave <b>in</b><a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '5':

                    //Like this wave
                    $quest = get_question($list['qid']);

                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>I like This Wave</b></span> <span>' . $list['vars'] . '<span> <b>for</b>  <a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '6':
                    //followers
                    $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                    $strReturn .= '<div ><span>' . $date . '</span><span> <b>New Follower</b></span> <span><a href="' . $gSitePath . '/profile/' . $list['vars'] . '">' . $list['vars'] . '  <img src="' . $list['qid'] . '" border="0" width="20" height="20"></a></a></span></div>';
                    break;
                case '7':
                    //New Resources
                    //New Wave Post
                    $quest = get_question($list['qid']);

                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>New Resource posted for </b> <a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '8':
                    //suggest answer answered

                    $quest = get_question($list['qid']);
                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>Suggested Answer</b></span> <span><a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '9':

                    $bad = db_fetch_object(db_query("select * from {user_badges} as ub join {badges} as b on ub.bid=b.bid where ub.badge='" . $list['vars'] . "'"));

                    //echo "<pre>"; print_r($bad);

                    if (!empty($bad)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>Awarded Badge </b></span> <span><a title=' . $bad->info . ' href="' . $gSitePath . 'badges/user/' . $bad->bid . '">' . $bad->name . ' </a></span></div>';
                    }



                    break;
                default:
                    drupal_set_message($message = 'Oops, No Recent Activities !', $type = 'error');
                    break;
            }//switch ends
        }//foreach ends
    } else {

        drupal_set_message($message = 'Oops, No Recent Activities !', $type = 'error');
    }
    $strReturn.='</div>';
    // return $uid;
    echo $strReturn;
    exit;
}

function get_user_details() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    extract($_REQUEST);
    $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $getuid . "'";
    $rs_userms = db_query($sel_userm);
    $resulrnames = db_fetch_object($rs_userms);
    $gquery = "select ifnull(sum(points),0) as qpt from {tbl_user_points} where uid='" . $getuid . "' group by uid";
    $gpoints = db_result(db_query($gquery));
    if (is_numeric($getuid))
        $get_details = profile($getuid);
    else
        $get_details='Sorry Error Occurs';

    echo $content.=' <div class="commu-profile">
          <div class="commutop-profile">
  CONTRIBUTOR
          </div>
             <div class="inner2">
      ' . $get_details . '
             </div>
        </div>
            ';

    exit;
}

function search_results_user() {

    ///vijay2

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;


    extract($_REQUEST);
    //echo $_REQUEST['code'];
    $page_name = "searchuser"; //  If you use this code with a different page ( or file ) name then change this
    if (isset($_GET['start'])) {
        $start = $_GET['start'];
    } else {
        $start = 0;
    }
    if (strlen($start) > 0 and !is_numeric($start)) {
        echo "Data Error";
        exit;
    }


    $eu = ($start - 0);
    $limit = 10; // No of records to be shown per page.
    $this1 = $eu + $limit;
    $back = $eu - $limit;
    $next = $eu + $limit;

    $fetresult .= '';
    $name = $_REQUEST['txt_search'];

    if ($name != '')
        $qry .= "(img.real_name LIKE '%" . $name . "%' OR reg.name LIKE '%" . $name . "%' ) AND ";
    if ($code != '')
        $qry .= "(img.country LIKE '" . $code . "%') AND ";
    if ($ccode != '')
        $qry .= "(img.state LIKE '" . $ccode . "%') AND ";

    if ($user->uid != '')
        $sel = "SELECT * FROM {users} reg,{user_profile} img WHERE $qry reg.uid<>$user->uid and img.uid=reg.uid AND reg.status='1' ";
    else
        $sel = "SELECT * FROM {users} reg,{user_profile} img WHERE $qry reg.status='1' and img.uid=reg.uid  ";
    //echo $sel;
    $user_qry = db_query($sel);
    if ($user->uid != '')
        $sel_count = db_result(db_query("SELECT COUNT(*) FROM {users} reg,{user_profile} img WHERE $qry reg.uid<>$user->uid and img.uid=reg.uid AND reg.status='1'"));
    else
        $sel_count = db_result(db_query("SELECT COUNT(*) FROM {users} reg,{user_profile} img WHERE $qry reg.status='1' and img.uid=reg.uid "));
    $sel .= " limit $eu, $limit";
    $sel_search = db_query($sel);



    $fetresult = ' <div class="rleft">
      <h1>SEARCH RESULTS</h1>
       <div class="clr"></div>
      
       <div class="clr"></div>
       <div class="clr"></div>
      
       <div class="rleft">';

    while ($user_result = db_fetch_object($sel_search)) {
        if ($user->uid != '') {
            //$flink='<a class="linkfol" href="search/'.$user_result->uid.'?act=flag">Follow </a>';
            //$flink='<a class="linkfol" href="'.$gSitePath.'profile/'.$user_result->uid.'">View </a>';
        }
        $gquery = "select ifnull(sum(points),0) as qpt from {tbl_user_points} where uid='" . $user_result->uid . "'";
        $gpoints = db_result(db_query($gquery));

        $fetresult .= ' <div class="prof-it-1">
                    <div class="lefimg-it-c"><a href="#" onclick="get_profile_details(' . $user_result->uid . ');">' . UserPicture($user_result->uid) . '</a></div>
                    <div class="ritecont-it-c">
            <div>
            <ul>
            <li><a  onclick="get_profile_details(' . $user_result->uid . ');" > ' . $user_result->real_name . '</a></li><br />
           <!--<li>' . $gpoints . '</li><br />-->
            ' . updateProfileBadge($user_result->uid) . '
            </ul>
            </div>
            </div>
            <div class="clr"></div>
               </div>';

        $fetresult .= $flink;
    }

    $fetresult .= '</div>
       </div>
      
       
       
       <div class="clr"></div>';

    if ($sel_count == 0) {
        $fetresult .= '<div style="padding-top:10px" align="center"><b>No Search Results </b></div>';
    }

    $fetresult .= '</div>';

    $fetresult .= '<input type="hidden" name="stype" value="' . $_REQUEST['stype'] . '"/></ul>';


    if ($sel_count > $limit) {

        $fetresult .= "<table align = 'center' width='100%'><tr><td  align='left' width='30%'>";
        if ($back >= 0) {
            $fetresult .= "<a href='$page_name?start=$back&code=$code&txt_search=$name'><font face='Verdana' size='2'>PREV</font></a>";
        }
        $fetresult .= "</td><td align=center width='30%'>";
        $i = 0;
        $l = 1;

        for ($i = 0; $i < $sel_count; $i = $i + $limit) {
            if ($i <> $eu) {
                $fetresult .= " <a href='$page_name?start=$i&code=$code&txt_search=$name'><font face='Verdana' size='2'>$l</font></a> ";
            } else {
                $fetresult .= "$l";
            }
            $l = $l + 1;
        }


        $fetresult .= "</td><td  align='right' width='30%'>";
        if ($this1 < $sel_count) {
            $fetresult .= "<a href='$page_name?start=$next&code=$code&txt_search=$name'><font face='Verdana' size='2'>NEXT</font></a>";
        }
        $fetresult .= "</td></tr></table>";
    }

    $fetresult .= ' ';


    echo $fetresult;
}

function get_question_details() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path, $apikey;

    extract($_REQUEST);

    $vSql = "select *,q.uid as uid from {question} as q left join {user_profile} as u on q.uid=u.uid where q.status='1' and q.qid='$qsaid'  ";
    $rlist = db_query($vSql);
    $oListquest = db_fetch_object($rlist);
    $qid = $oListquest->qid;
    $vresultm .= '<div><small>' . $oListquest->question . '</small><br/>';
    $vans = "select * from {possible_answer} where  qid=$qsaid order by vote desc";
    //voted answer
    $list_lengthan = db_query("select * from {possible_answer_vote} where qid='" . $qid . "' and uid='" . $user->uid . "'  ");
    $numran = db_result(db_query("SELECT COUNT(*) from {possible_answer_vote} where qid='" . $qid . "' and uid='" . $user->uid . "'"));
    $answer_id = db_fetch_object($list_lengthan);
    $vlist = db_query($vans);
    $chk = '';
    while ($vlistquest = db_fetch_object($vlist)) {
        if ($numran == 0) {
            $answprc = $vlistquest->vote / 100 * $totalvotes;
            $valu = $answprc * 100;
            $vresultm .= '
		 <input name="answer" type="radio" value="' . $vlistquest->paid . '" /> <span class="black11">
		' . $vlistquest->answer . '</span> <br/>  ';
        } else {
            $answprc = $vlistquest->vote / 100 * $totalvotes;
            $valu = $answprc * 100;
            $chk = '';
            if ($answer_id->panswer_id == $vlistquest->paid) {

                $chk = "checked";
            }
            $vresultm .= ' <input name="answer_al" type="radio" ' . $chk . '  value="' . $vlistquest->paid . '" />&nbsp;&nbsp;<span class="black11">
		' . $vlistquest->answer . ' </span> <br/>   ';
        }
        $chk = '';
    }

    $vresultm.='<script>	function formsubmittype(mtype,ids){
		jQuery("#txt_act").val(mtype);
		if(mtype==1)
		{
		
		
		document.getElementById(\'answer_frm\').submit();
		}
		if(mtype==2)
		{
		
		load_invite(\'' . $gSitePath . 'invite/invite_friends?qid=' . $qid . '\',\'Profile \');
		//onclick="load_invite(\'' . $gSitePath . 'c?qid=' . $qid . '\',\'Profile\');
		}
		if(mtype==3)
		{
		loadflagquestion(\'' . $gSitePath . 'qlite/flag/\'+ids,\'Report \');
		
		}
		if(mtype==4)
		{
		loadsuggest(\'' . $gSitePath . 'qlite/suggest/\'+ids,\'Answers \');
		
		}
		if(mtype==5)
		{
		window.location.href="' . $gSitePath . 'mashup/' . $qid . '";
		
		}
		}</script>';
    $vresultm.='
		
       <script type="text/javascript">

        
        function showShareUI() {

		   
		    var act = new gigya.services.socialize.UserAction();

		    act.setUserMessage("Your comment here...");

		   
		    act.setTitle("' . $oListquest->question . '");

		    act.setDescription("' . $oListquest->context . '");

           
		    act.setLinkBack("' . $gSitePath . '' . $oListquest->url . '");

		  
		    act.addActionLink("' . $oListquest->question . '",
		        "' . $gSitePath . '' . $lji[1] . '");

		   
	       

			
			var params = 
			{
			    userAction: act,  	                                  
			    onError: onError,  
			    onSendDone: onSendDone, 
               showEmailButton:true,
               showMoreButton:true
			};

			
			gigya.services.socialize.showShareUI(conf, params);

		}
		
		
		function onError(event) {
		    alert(\'An error has occured\' + \': \' + event.status + \'; \' + event.statusMessage);
		}

		
		function onSendDone(event)
		{
		    document.getElementById(\'status\').style.color = "green";
		    document.getElementById(\'status\').innerHTML = 
                            \'The newsfeed has been posted to: \' 
		            + event.providers;
		}    
	</script>';



    $vresultm .= '   <div class="sharing-section sharing-width paddi40">
        
               <div class="share1">
            <a title="Bookmark" class="share-link" onclick="showShareUI();" href="javascript:void(0);">Bookmark</a> / <a title="Invite" onclick="formsubmittype(2,' . $qid . ');" href="javascript:void(0);" class="share-link">Invite</a>
             </div>
             
						      
             <div align="center" class="share1">
              <a title="Suggest a new answer" class="share-link"  onclick="formsubmittype(4,' . $qid . ');" href="javascript:void(0);">Suggest a new answer</a>
             </div>
             <div class="share3">
        <a title="Create Mashup" class="share-link" onclick="formsubmittype(5,' . $qid . ');" href="javascript:void(0);">&lt;Embed&gt;</a>
             </div>
             <div class="share3">
             <img src="' . $gSitePath . path_to_theme() . '/images/flag.png" alt="flag" align="middle" /><a title="Flag" class="share-link"  onclick="formsubmittype(3,' . $qid . ');" href="javascript:void(0);">Flag</a>    </div>
             
            </div>
			  <div class="clr"></div>
            </div>
              <h3>PERCENTAGE</h3>
              <div class="innerbox"><iframe width="300" height="200" frameborder="0" border="0" src="' . $gSitePath . '/qlite/percent/' . $qid . '" id="frmGooglevotes"/></div>
            </div>
            <div class="clr"/>
            <div>
              <h3>OVERTIME</h3>
              <div class="innerbox"><iframe width="300" height="200" frameborder="0" border="0" src="' . $gSitePath . '/qlite/graph/' . $qid . '" id="frmGooglepercent"/></div>
            </div>
            <div class="clr"/>
            <div>
              <h3>BY AREA</h3>
<div class="innerbox"><iframe width="300" height="200" frameborder="0" border="0" src="' . $gSitePath . '/qlite/map/' . $qid . '" id="frmGooglemap"/></div>
        
            </div>
            <div class="clr"></div>
          ';

    echo $vresultm;
}

function search_report($idb = '') {
    global $gSitePath, $user, $gDocPath, $base_root;
    $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    //echo veni  .$idb;
    echo $output = '<div class="toolbarTabs">
	<ul id="qTabs" class="tab-menu">
	<li id="qTabs1Link" class="selected"><a>Percentage</a></li>
	<li id="qTabs2Link"><a>Over Time</a></li>
	<li id="qTabs3Link" ><a>By Area</a></li>
	</ul>
	<div class="clear"></div>
	</div>

	<script type="text/javascript">
	
	MochaUI.initializeTabs("qTabs");
	
	$("qTabs1Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("search-panel"),
	"url":       "' . $gSitePath . 'searchcontent/' . $idb . '?t=per"
	});
	});
	
	$("qTabs2Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("notify-panel"),
	"url":       "' . $gSitePath . 'searchcontent/' . $idb . '?t=time"
	});
	});
	
	$("qTabs3Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("notify-panel"),
	"url":       "' . $gSitePath . 'searchcontent/' . $idb . '?t=area"
	});
	});

	
	</script>';
}

function search_content() {
    global $gSitePath, $user, $gDocPath, $base_root;
    $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    //echo "kkkkkkkk".$qid;
    $type = $_REQUEST[t];

    switch ($type) {

        case "time":
            $output = '<div id="contents"><iframe id="frmGoogle" src="' . $gSitePath . '/qlite/graph/' . $qid . '" border="0" height="450" frameborder="0" width="100%"></iframe></div>';
            break;
        case "area":
            $output = '<div id="contents"><iframe id="frmGoogle" src="' . $gSitePath . '/qlite/map/' . $qid . '" border="0" height="450" frameborder="0" width="100%"></iframe></div>';
            break;
        case "per":
        default:
            $output = '<div id="contents"><iframe id="frmGoogle" src="' . $gSitePath . '/qlite/percent/' . $qid . '" border="0" height="450" frameborder="0" width="100%"></iframe></div>';
            break;
    }


    $output .= '<div>108 comments &nbsp;&nbsp;&nbsp;' . $numres . ' Resources </div>';

    echo $output;
}

function search_quest_cat() {
    $link1 = '';
    $link2 = '';
    $link3 = '';
    $cid = '';
    $scid = '';
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    if (($_REQUEST['scid'] != '') || ($_REQUEST['cid'] != '')) {
        $suid = $_REQUEST['scid'];
        if ($_REQUEST['cid'] == '') {
            $sel_catm = db_query("select * from category  where cat_id='" . $suid . "'   ");
            $saveresult = db_fetch_object($sel_catm);
            $cid = $saveresult->parent_id;
        } else {
            $cid = $_REQUEST['cid'];
        }

        //$catlist='Category';
        $sel_cat = db_query("select * from category  where cat_id=" . $cid . "   ");
        $saveresult = db_fetch_object($sel_cat);


        $sel_suge = "select * from category  where parent_id=" . $cid . "   ";

        $rs_folwin = db_query($sel_suge);
        $numrancnt = db_result(db_query("SELECT COUNT(*) from  question   where cid=" . $cid . "  "));

        $catlist = '
		<div id="container">
		<div class="feature">
		<div class="l col">
		<ul><li><b><a href="' . $gSitePath . 'searchquestion?cid=' . $cid . '">' . $saveresult->cat_name . '(' . $numrancnt . ')</a></b></li>';

        while ($flwing_result = db_fetch_object($rs_folwin)) {
            //echo "SELECT COUNT(*) from  question   where cid=".$cid." and scid=".$flwing_result->cat_id."";

            $numrancnts = db_result(db_query("SELECT COUNT(*) from  question   where cid=" . $cid . " and scid=" . $flwing_result->cat_id . ""));


            $catlist .= '<li>&nbsp;<a href="' . $gSitePath . 'searchquestion?cid=' . $cid . '&scid=' . $flwing_result->cat_id . '">' . $flwing_result->cat_name . '(' . $numrancnts . ')</li>';
            //echo $flwing_result->cat_id;

            $sel_sugess = "select * from category  where parent_id=" . $flwing_result->cat_id . "   ";
            $rs_folwinss = db_query($sel_sugess);
            while ($sm_result = db_fetch_object($rs_folwinss)) {
                $numrancntss = db_result(db_query("SELECT COUNT(*) from  question   where cid=" . $cid . " and scid=" . $flwing_result->cat_id . " and  sscid=" . $sm_result->cat_id . ""));
                $catlist .= '<li>&nbsp;&nbsp; <a href="' . $gSitePath . 'searchquestion?cid=' . $cid . '&scid=' . $flwing_result->cat_id . '&sscid=' . $sm_result->cat_id . '">' . $sm_result->cat_name . '(' . $numrancntss . ') </a> </li>';
            }
        }
        $catlist .= '</ul></div>
	</div>
	</div>
	';
    } else {

        //$catlist='Category';


        $sel_sugef = "select * from category where parent_id='0'    ";

        $rs_cat = db_query($sel_sugef);


        $catlist = '
		<div id="container">
		<div class="feature">
		<div class="l col">
		<ul>';

        while ($cat_result = db_fetch_object($rs_cat)) {


            $numrancnts = db_result(db_query("SELECT COUNT(*) from  question where  cid=" . $cat_result->cat_id . ""));


            $catlist .= '<li>&nbsp;<a href="' . $gSitePath . 'searchquestion?cid=' . $cat_result->cat_id . '">' . $cat_result->cat_name . '(' . $numrancnts . ')</li>';
        }
        $catlist .= '</ul></div>
	</div>
	</div>
	';
    }
    echo $catlist;
}

?>
