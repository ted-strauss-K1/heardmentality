<?php
//////////////insert front end mail notification//////////////////////
function hm_flag($qid, $last_id, $user, $admin) {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path, $saaais, $apikey;
    $qdetails = load_question($qid);

    $u_qry = "select * from users where uid='" . $qdetails['uid'] . "'";
    $u_res = db_query($u_qry);
    $u_rows = db_fetch_object($u_res);

    $flag_qry = "select * from question_flags where fid='" . $last_id . "'";
    $flag_res = db_query($flag_qry);
    $flag_rows = db_fetch_object($flag_res);


    $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='5'";
    $rs_mgmt = db_query($sel_user_cmt);
    $list_content = db_fetch_object($rs_mgmt);
    // $subject_proj = $list_content->subject;
    $subject_proj = "Heardmentality : Flag Actions";
    if ($user) {
        $name = '';
        $contentm = str_replace("#uname#", $u_rows->name, $list_content->content);
        $contentm = str_replace("#anothername#", $name, $contentm);
        $contentm = str_replace("#question#", rtrim($qdetails['question'], '?') . '?', $contentm);
        $contentm = str_replace("#link#", $gSitePath . $qdetails['url'], $contentm);
        $contentm = str_replace("#content#", 'some one flagged your question due to ' . $flag_rows->abuse_type . '', $contentm);
        //$mail_success = htmlmail_function($u_rows->email, $subject_proj, $contentm, '');
        $ins_qry = "insert into hm_mails(from_mail_id,user_from_id,user_to_id,subject,content,mail_status,notify,posted_date)values('mgopi.php@gmail.com','mgopi.php@gmail.com','" . $u_rows->mail . "','" . $subject_proj . "','" . $contentm . "',0,0,now())";
        db_query($ins_qry);
    }
    if ($admin) {

        $contentm = str_replace("#uname#", Admin, $list_content->content);
        $contentm = str_replace("#anothername#", $user->name, $contentm);
        $contentm = str_replace("#question#", rtrim($qdetails['question'], '?') . '?', $contentm);
        $contentm = str_replace("#link#", $gSitePath . $qdetails['url'], $contentm);
        $contentm = str_replace("#content#", ' flagged this question due to ' . $flag_rows->abuse_type . '', $contentm);

        //$mail_success = htmlmail_function($u_rows->email, $subject_proj, $contentm, '');
        $admin_qry = "insert into hm_mails(from_mail_id,user_from_id,user_to_id,subject,content,mail_status,notify,posted_date)values('mgopi.php@gmail.com','mgopi.php@gmail.com','mgopi.php@gmail.com','" . $subject_proj . "','" . $contentm . "',0,0,now())";
        db_query($admin_qry);
    }
}

//////////////insert front end mail notification//////////////////////
function qlite_view() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path, $saaais, $apikey;
    //echo $_SERVER['QUERY_STRING'];
    $lji = explode("=", $_SERVER['QUERY_STRING']);

    if (isset($_REQUEST['lid'])) {
        $select_user_count = db_result(db_query("SELECT COUNT(*) from invite_friend where inv_id='" . $_REQUEST['lid'] . "' and  status='1' "));
        if ($select_user_count == 0) {
            //session_start();
            //$_SESSION['friend_id']=$_REQUEST['lid'];
            // echo $_SESSION['friend_id'];
        }
    }
    if (isset($_REQUEST['faceid'])) {

        setcookie("faceidc", $_REQUEST['faceid']);
    }


    // unset($user->new_id);
    //echo $lji[0];

    drupal_add_css(drupal_get_path('module', 'quest_lite') . '/css/main.css');
    //drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/page.css');
    // drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/tabs.css');
    // drupal_add_css(drupal_get_path('module', 'quest_lite') . '/css/wave.css');
    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/wave.js');
    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/like.js');
    // drupal_add_js(drupal_get_path('module', 'forum').'/scripts/forum.js');
    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/subtab.js');

    $qid = get_qid();


    //$qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    /////////////qviews /////////////////////////
    popquest();

    insertviews($qid);
    //popquest();
    //////////////////////////////
    $query = "SELECT qid, SUM(vote) as possiblevote FROM possible_answer where qid='" . $qid . "' GROUP BY qid";
    $query_list = db_query($query);
    $fetvot = db_fetch_object($query_list);
    $vot1 = $fetvot->possiblevote;

    $query_sugest = "SELECT qid, SUM(vote) as suggestv FROM suggest_answer where qid='" . $qid . "' GROUP BY qid";
    $query_sugestlist = db_query($query_sugest);
    $fetvotsugest = db_fetch_object($query_sugestlist);
    $vot2 = $fetvotsugest->suggestv;
    $totalvotes = $vot1 + $vot2;


    $vqry = "select * from tbl_vote_gurupoints where vstart=$totalvotes and vend>$totalvotes";
    $voteqrylist = db_query($vqry);
    $fetqrylist = db_fetch_object($voteqrylist);
    if ($fetqrylist->id != '') {
        $fetqrylist->id;

        increasepoints('0', $qid, $fetqrylist->id);
    }

    $vSqlsv = "select * from {vote_percent} where id='1' ";
    $rlistbv = db_query($vSqlsv);
    $oListquestbv = db_fetch_object($rlistbv);

    $percent = $oListquestbv->percent / 100 * $totalvotes;
    //echo $percent;
    $tot = $percent * 100;

    $vSql = "select *,q.uid as uid from {question} as q left join {user_profile} as u on q.uid=u.uid where 1 AND q.qid='".$qid."' AND q.status='1'";
    $rlist = db_query($vSql);
    $oListquest = db_fetch_object($rlist);

    //question privacy check
    if (!$oListquest->status) {

        if ($user->uid != $oListquest->uid || $oListquest->uid != 1) {

            drupal_set_message('Sorry Question is inactive for user access!', 'error');
            drupal_access_denied();
            die;
        }
    }

    if (isAjax ())
        privacy_chk_ajax($oListquest->uid, $oListquest->question_privacy, $oListquest->share);
    else
        privacy_chk($oListquest->uid, $oListquest->question_privacy, $oListquest->share);
    ////question privacy check ends

    $list_lengthan = db_query("select * from {possible_answer_vote} where qid='" . $qid . "' and uid='" . $user->uid . "'  ");
    $numran = db_result(db_query("SELECT COUNT(*) from {possible_answer_vote} where qid='" . $qid . "' and uid='" . $user->uid . "'"));
    $answer_id = db_fetch_object($list_lengthan);
    $stringfunct = strlen($oListquest->question);
    $voutput = '<div id="qajax">

<link rel="stylesheet" href="' . $gSitePath . path_to_theme() . '/css/css.css" type="text/css" />
        <script type="text/javascript">
		var qid="' . $qid . '";
		var spath="' . $gSitePath . '";
		function showdetails(ids)
		{	
	
		loaddetails(\'' . $gSitePath . 'qlite/Details/\'+ids,\'Question Information\');
		}
		
		</script>';
    //echo $stringfunct;
    if (drupal_is_front_page ()) {
        $qlink = 'CONTRIBUTOR';
    } else {
        $qlink = substr($oListquest->question, 0, 160) . '<a onclick="showdetails(' . $qid . ');">...</a>';
        $qlink = "Question";
    }

/// vijay link color
//    function link_color($userid,$quesid)
//    {
//
//   if($userid)
//    {
//        $linkcolor = db_query("select count(*) as count from {possible_answer_vote} where qid='" . $quesid . "' and uid='" . $userid . "'  ");
//         $get_linkcolor = db_fetch_object($linkcolor);
//         if($get_linkcolor->count==0)
//         {
//             return "color:red";
//         }
//          if($get_linkcolor->count==1)
//         {
//            return "color:green";
//         }
//    }
//            return "color:#4170A0";
//
//    }

    drupal_set_title($qlink);
    $len = strlen($oListquest->context);
    if ($oListquest->context != "") {
        $linkj = '<a onclick="loaddetails(\'' . $gSitePath . 'qlite/Details/' . $qid . '\',\'Question Information\');">...</a>';
    }
    $shortdesc = substr($oListquest->context, 0, 250);


    $voutput .= '	  <div>
              <h2 style="' . drupal_link_color($user->uid, $oListquest->qid) . '">' . rtrim($oListquest->question, "?") . '? </h2>
            </div>          <div class="quesin">
              <div class="quesinner">
                <div class="quesinnerr">
<form id="answer_frm" name="answer_frm" method="post" action="' . $gSitePath . 'qlite/save"  >
		 <input type="hidden" name="txt_act" id="txt_act" value=""/>
	 <input type="hidden" name="mid" value="' . $qid . '"/>
		<!--<div class=""><div class="lft_view"> <h4 class="cmt_name"><a></a></h4>-->
		
		<!--<div>' . $shortdesc . ' ' . $linkj . '--><div>';
    //likes

    $query = "select sum(like_yes) as res from {question_like} where qid='" . $qid . "' group by qid ";
    $set = ExecuteQuery($query, "select");

    $set_cnt = ( empty($set[0]['res']) ? '0' : $set[0]['res']);
    /*

      $voutput .= '<div id="vote" class="vote">
      <img onclick="qns_like(1,'.$qid.');" src="'.$gSitePath.drupal_get_path('module', 'quest_lite').'/images/up.jpg" id="vote-up" alt="Up" title="This Question is good"/>
      <span  class="vote-cnt"><h2  id="vote-cnt">&nbsp;'.$set_cnt.'</h2></span>
      <img onclick="qns_like(-1,'.$qid.');" src="'.$gSitePath.drupal_get_path('module', 'quest_lite').'/images/down.jpg" id="vote-down" alt="Down" title="This Question is not useful"/><br/>
      </div>';
     */
    $vans = "select * from {possible_answer} where  qid=$qid order by vote desc";

    $vlist = db_query($vans);
    $chk = '';
    while ($vlistquest = db_fetch_object($vlist)) {
        if ($numran == 0) {
            $answprc = $vlistquest->vote / 100 * $totalvotes;
            $valu = $answprc * 100;
            $voutput .= '
		 <br/><input name="answer" type="radio" value="' . $vlistquest->paid . '" />
		' . $vlistquest->answer . '  ';
        } else {
            $answprc = $vlistquest->vote / 100 * $totalvotes;
            $valu = $answprc * 100;
            $chk = '';
            if ($answer_id->panswer_id == $vlistquest->paid) {

                $chk = "checked";
            }
            $voutput .= ' <br/><input name="answer_a2" type="radio" ' . $chk . '  value="' . $vlistquest->paid . '" />
		<label>' . $vlistquest->answer . '  </label> ';
        }
        $chk = '';
    }
    $vsans = "select * from {suggest_answer} where  qid=$qid ";
    $vslist = db_query($vsans);

    while ($vlsistquest = db_fetch_object($vslist)) {
        $answprcs = $vlsistquest->vote / 100 * $totalvotes;

        $valuss = $answprcs * 100;

        if ($valuss > $tot) {
            $insert_change = "insert into suggest_ans_changeids (qid,ans_id)Values('" . $qid . "','" . $vlsistquest->said . "') ";
            $listchnge = db_query($insert_change);

            $select_allv = "select * from suggest_answer_vote where answer_id=$vlsistquest->said  ";
            $listam = db_query($select_allv);

            while ($listamqry = db_fetch_object($listam)) {

                $insert_white = "insert into suggest_ans_tmp (qid,uid,answer_id,vote,vote_date)Values('" . $qid . "','" . $listamqry->uid . "','" . $vlsistquest->said . "','" . $vlsistquest->vote . "','" . $listamqry->vote_date . "') ";
                $qrylist = db_query($insert_white);
            }
            //echo $valuss;
            //echo $vlsistquest->said;
        }
    }
    $mysql_sug_rows = mysql_num_rows(db_query("select distinct(answer_id) from suggest_ans_tmp  "));


    //echo $mysql_sug_rows;
    $vpans = "select * from {possible_answer} where  qid='" . $qid . "' order by vote desc limit 0,$mysql_sug_rows ";

    $vplist = db_query($vpans);

    while ($vplistquest = db_fetch_object($vplist)) {
        $insert_list_ids = "insert into possible_answer_changeids (qid,ans_id)Values('" . $qid . "','" . $vplistquest->paid . "') ";
        $qrylist_change = db_query($insert_list_ids);

        $select_allvp = "select * from possible_answer_vote where panswer_id=$vplistquest->paid  ";
        $listamp = db_query($select_allvp);

        while ($listamqryamp = db_fetch_object($listamp)) {

            $insert_whited = "insert into possible_answer_tmp (qid,uid,panswer_id,vote,vote_pdate)Values('" . $qid . "','" . $listamqryamp->uid . "','" . $vplistquest->paid . "','" . $vplistquest->vote . "','" . $listamqryamp->vote_pdate . "') ";
            $qrylist = db_query($insert_whited);
        }
    }

    $qry1 = db_query("select * from suggest_ans_changeids where qid ='" . $qid . "'");
    $array1 = array();
    while ($row1 = db_fetch_object($qry1)) {
        $array1[] = $row1->ans_id;
    }

    $qry2 = db_query("select * from possible_answer_changeids where qid ='" . $qid . "' ");
    while ($row2 = db_fetch_object($qry2)) {
        $array2[] = $row2->ans_id;
    }

    for ($x = 0; $x < sizeof($array1); $x++) {
        $array[] = $array1[$x] . " - " . $array2[$x];

        $array1[$x] . " - " . $array2[$x];

        $update_idss = db_query("update possible_answer_tmp set  panswer_id='$array1[$x]'  where panswer_id='$array2[$x]' ");


        $updateval = db_query("update suggest_ans_tmp set  answer_id='$array2[$x]' where answer_id='$array1[$x]'");

        $deletsug = db_query("delete from suggest_answer_vote where answer_id='$array1[$x]'");

        $deletpos = db_query("delete from possible_answer_vote where panswer_id='$array2[$x]'");

        $rechange_list = db_query("select * from {possible_answer} where  paid='" . $array2[$x] . "'  ");

        $rechg = db_fetch_object($rechange_list);
        $rechg->vote;

        $rechange_list_new = db_query("select * from {suggest_answer} where  said='" . $array1[$x] . "'  ");

        $rechg_new = db_fetch_object($rechange_list_new);
        $rechg_new->vote;
        $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='3'";
        $rs_mgmt = db_query($sel_user_cmt);
        $list_content = db_fetch_object($rs_mgmt);

        $vuser_ownersug = "select * from {users} where  uid='" . $rechg_new->uid . "'";
        $userown = db_query($vuser_ownersug);
        $ufet_qwn = db_fetch_object($userown);
        $ufet_qwn->mail;
        if ($usert->notify_etype == 1) {
            $subject_proj = $list_content->subject;


            //////////mail for suggest answer owner///////////////


            $contentm = str_replace("#uname#", $ufet_qwn->name, $list_content->content);
            $contentm = str_replace("#quest#", $oListquest->question, $contentm);
            //echo  $contentm;

            $mail_success = htmlmail_function($ufet_qwn->mail, $subject_proj, $contentm, '');
        }
        if ($usert->notify_itype == 1) {
            $insert_notify = db_query("insert into notification (uid,new_answer,is_question,node_id) values('" . $rechg_new->uid . "','1','1','" . $qid . "') ");
        }
        $update_ids = "update possible_answer set  answer='$rechg_new->answer', vote='$rechg_new->vote'  where paid='$array2[$x]' ";
        $updateqry = db_query($update_ids);

        $update_sug = "update suggest_answer set  answer='$rechg->answer', vote='$rechg->vote',uid='$oListquest->uid' where said='$array1[$x]' ";
        $updateqrys = db_query($update_sug);


        /////////////Mail For question Author///////////


        $vuser = "select * from {users} where  uid='" . $oListquest->uid . "'";
        $username = db_query($vuser);
        $ufet = db_fetch_object($username);
        $ufet->mail;
        if ($ufet->notify_etype == 1) {
            $subject_projm = 'Heard Menatlity-Answer Has Been Replaced For Your Question';


            $contentmown = str_replace("#uname#", $ufet->name, $list_content->content);
            $contentmown .= str_replace("#quest#", $oListquest->question, $contentmown);
            //	echo  $contentmown;

            $mail_success = htmlmail_function($ufet->mail, $subject_projm, $contentmown, $from, '');


            // $mail_success = htmlmail_function($ufet->mail,$subject_proj,$messpro_list,$from,'');
        }
        $delossld = "delete  from possible_answer_changeids where ans_id='" . $array2[$x] . "'";
        $delssqry = db_query($delossld);
        $deloldwds = "delete  from suggest_ans_changeids where ans_id='" . $array1[$x] . "'";
        $delqrysss = db_query($deloldwds);
        if ($ufet->notify_itype == 1) {
            $insert_notify = db_query("insert into notification (uid,new_answer,is_question,node_id) values('" . $ufet->uid . "','1','1','" . $qid . "') ");
        }
    }

    $seltmp = db_query("select * from suggest_ans_tmp");

    while ($tmp_rec = db_fetch_object($seltmp)) {

        $insert_dumm = "insert into possible_answer_vote (qid,uid,panswer_id,vote_pdate) values ('" . $tmp_rec->qid . "','" . $tmp_rec->uid . "','" . $tmp_rec->answer_id . "','" . $tmp_rec->vote_date . "')";
        $dumy_rec = db_query($insert_dumm);

        ///////////////////////mail notification for who voted answers ///////////////////////////////
        $vusers = "select * from {users} where  uid='" . $tmp_rec->uid . "' ";
        $usernames = db_query($vusers);
        $ufets = db_fetch_object($usernames);
        $ufets->mail;
        if ($ufets->notify_etype == 1) {
            $subject_projlist = 'Heard Menatlity-Answer Has Been Replaced ';


            $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='3'";
            $rs_mgmt = db_query($sel_user_cmt);
            $list_content = db_fetch_object($rs_mgmt);
            $contentmlist = str_replace("#uname#", $ufets->name, $list_content->content);
            $contentmlist = str_replace("#quest#", $oListquest->question, $contentmlist);
            // $contentm;

            $mail_success = htmlmail_function($ufets->mail, $subject_projlist, $contentmlist, '');
        }

        if ($ufets->notify_itype == 1) {


            $insert_notify = db_query("insert into notification (uid,new_answer,is_question,node_id) values('" . $tmp_rec->uid . "','1','1','" . $qid . "' ");
        }
        $deltmp = db_query("delete  from suggest_ans_tmp");
    }

    $seltmps = db_query("select * from possible_answer_tmp");

    while ($tmp_recs = db_fetch_object($seltmps)) {

        $insert_dumms = "insert into suggest_answer_vote (qid,uid,answer_id,vote_date) values ('" . $tmp_recs->qid . "','" . $tmp_recs->uid . "','" . $tmp_recs->panswer_id . "','" . $tmp_recs->vote_pdate . "')";
        $dumy_recs = db_query($insert_dumms);

        $deltmps = db_query("delete  from possible_answer_tmp");
    }

    if ($user->uid > 0) {
        $voutput .= '
	<SCRIPT type="text/javascript" lang="javascript" src="http://cdn.gigya.com/JS/socialize.js"></SCRIPT>
	<script>
        var conf = 
        {
            APIKey: \'' . $apikey . '\'
        };
        
        function onLoad()
        {
            gigya.services.socialize.getUserInfo(conf,{callback:renderUI});	    
            
           
            gigya.services.socialize.addEventHandlers(conf, { onConnect:renderUI, onDisconnect:renderUI}   ); 
            
        }
    </script> ';
    }


    $voutput .= '
	<script type="text/javascript">
	        
     

			function formsubmittype(mtype,ids){
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
		}
		</script>
		';

    $optio = '';
    if ($numran != 0) {
        $query = "select vote_pid from {possible_answer_vote} where qid='$qid' AND uid='" . $user->uid . "'";
        $voteid = db_result(db_query($query));
        $submitbutt = ' <p><input type="submit" name="change" id="change" value="Change" /><input type="hidden" name="vote_id" value="' . $voteid . '"/></p>';
        //     $optio = '<div align="center" class="share2"><a title="Withdraw Your Answer" class="share-link" onclick="formsubmittype(1,' . $qid . ');" href="javascript:void(0);">Withdraw</a></div>';
    }
    if ($numran == 0) {

        $submitbutt = ' <p><input type="submit" name="save" id="save" value="Vote" /></p>';
    }

    //tags
    /* $instags = '';
      $query = " SELECT t.tag FROM {qtag} as qt left join {tagging} as t on t.tid=qt.tag_id WHERE qt.qid='" . $qid . "' ";
      $gettag = ExecuteQuery($query, "select");
      $gettag = array_filter($gettag);
      // print_r($gettag);
      if (!empty($gettag)) {
      foreach ($gettag as $intag) {
      $etag = '';

      $instags .= $intag['tag'] . "&nbsp;";
      }
      } else {
      $instags .= "&nbsp;<b> - -</b>&nbsp;";
      } */
    //	$voutput .='<a href="'.$gSitePath.'invite/invite_friends">Share This Question </a>';


    $voutput .= '
       <script type="text/javascript">

        
        function showShareUI() {

		   
		    var act = new gigya.services.socialize.UserAction();

		    act.setUserMessage("Your comment here...");

		   
		    act.setTitle("' . $oListquest->question . '");
		    act.setDescription("' . $oListquest->context . '");

           
		    act.setLinkBack("' . $gSitePath . '' . $lji[1] . '");

		  
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

    $numres = db_result(db_query("SELECT COUNT(*) FROM resource where  qid='$qid'"));

    $query = " SELECT (SELECT count( * ) FROM forum_wavelets AS w WHERE w.wid = f.fid GROUP BY w.wid ) AS wcnt FROM forum_wave AS f WHERE f.qid_rid = '$qid' ";
    $list = ExecuteQuery($query, "select");
    $debatecnt = 0;
    foreach ($list as $fcnt) {

        $debatecnt = $debatecnt + $fcnt['wcnt'];
    }

//tab
    $voutput .= $submitbutt . '
                 <div >&nbsp;
               <!--  <ul>
                  <li ><a href="javascript:set_tab_active(\'#par1 a\');" title="Comments">' . $debatecnt. ' comments</a></li>
                  <li>|</li>
                  <li ><a href="javascript:set_tab_active(\'#par2 a\');" title="Resources">' . $numres . ' Resources</a></li>
                  </ul>-->
              </div>
                </div>
                	</form>
              </div>
              </div>
	</div>
		  <div class="clr"></div>
            <!--<div class="tag">
             <span>Tags [<a href="#" onclick="loadtag(\'' . $gSitePath . 'qlite/addtag/' . $qid . '\',\'Edit Tags \'); ">Retag</a>]:</span>' . $instags . '</div>-->
            <div class="sharing-section">
             <div class="share1">
              <a title="Bookmark" class="share-link" onclick="showShareUI();" href="javascript:void(0);">
             <img ALIGN=ABSMIDDLE title="take the site tour" alt="take the site tour" src="' . $gSitePath . path_to_theme() . '/images/sm3.jpg"/>&nbsp;
              <img ALIGN=ABSMIDDLE title="take the site tour" alt="take the site tour" src="' . $gSitePath . path_to_theme() . '/images/sm4.jpg"/>&nbsp;
                  <img ALIGN=ABSMIDDLE title="take the site tour" alt="take the site tour" src="' . $gSitePath . path_to_theme() . '/images/sm5.jpg"/>&nbsp;
                    Share</a>                 
             </div>
              <!-- <div class="share2">
            <a title="Invite" onclick="formsubmittype(2,' . $qid . ');" href="javascript:void(0);" class="share-link"> Invite</a>
             </div>-->
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
		
		';

//////////////vijay multilevel menu
    $voteqry = "SELECT * FROM possible_answer_vote where qid='" . $qid . "'";
    $votelist = db_query($voteqry);
    $fetvote = db_fetch_object($votelist);
    $pundit_cnt = count(getAnsweredUsers($qid));
    if ($numran != 0) {


        $voutput .= '<div class="clr"></div>
	<div id="rotate">
        <br/>
              <ul id="maintabs" class="mytabs" >
             <li class="current" id="in"><a href="' . $gSitePath . '/qlite/panel/' . $qid . '" title="Report"><span>Reporting</span></a></li>
                <li class="" id="par1"><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Forum" title="Forum"><span>Forum ('.$debatecnt.')</span></a></li>
                <li class="" id="par2"><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Resources" title="Resources"><span>Resources ('.$numres.')</span></a></li>
				  <li class=""><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Gurus" title="Gurus"><span>Pundits (' . $pundit_cnt . ')</span></a></li>
				  <li class="" id="in"><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Info" title="Info"><span>Info</span></a></li>
				  
              </ul>
              <div class="mytabs-container" id="tabcontent">
            Loading. Please Wait...
        </div><div class="clr"></div>
           </div> ';
    } else {
////here
        $voutput .= '<div class="clr"></div>
	<div id="rotate">
        <br/>
              <ul id="maintabs" class="mytabs" >
              <li class="current" id="in"><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Info" title="Info"><span>Info</span></a></li>
               <li><a id="AF" href=\'#\' onClick="alert(\'Please vote the above question\');jQuery(this).die(\'click\');jQuery(this).unbind(\'click\');return false;"><span >Reporting</span></a></li>
                <li id="par1"><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Forum" title="Forum"><span>Forum ('.$debatecnt.')</span></a></li>
                <li id="par2"><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Resources" title="Resources"><span>Resources ('.$numres.')</span></a></li>
		<li class=""><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Gurus" title="Gurus"><span>Pundits (' . $pundit_cnt . ')</span></a></li>
              </ul>
              <div class="mytabs-container" id="tabcontent">
            Loading. Please Wait...
        </div><div class="clr"></div>
           </div>  ';
    }
    $voutput.='</div>'; // ajax div ends
    // cron job in qlite module
    // cal_active_rate();
    if (isAjax ()) {
        echo $voutput;
    } else {
        return $voutput;
    }
}

function qns_like() {
    global $gSitePath, $user, $gDocPath, $base_root;
    extract($_REQUEST);
    $userPoints = checkUserPoints($user->uid);

    $query = "select count(*) as res from {question_like} where qid='$qns' AND uid='$user->uid' ";
    $get = ExecuteQuery($query, "select");
    // Vote down needs minum 100 points
    if ((isset($type) && $type == '1') && (isset($userPoints) && $userPoints < 99)) {
        $array['msg'] = 'Sorry You Not Have Sufficent User Points To Up This Question!';
    } else if ((isset($type) && $type == '-1') && (isset($userPoints) && $userPoints < 15)) {
        $array['msg'] = 'Sorry You Not Have Sufficent User Points To Down This Question!';
    } else if ($get[0]['res'] > 0) {

        switch ($type) {

            case 1:
                $query = "update {question_like} set like_yes='-1' where qid='$qns' AND uid='$user->uid'";
                $ok = ExecuteQuery($query, "update");
                break;
            case - 1:
                $query = "update {question_like} set like_yes='1' where qid='$qns' AND uid='$user->uid'";
                $ok = ExecuteQuery($query, "update");
                break;
        }
    } else {

        $query = "insert into {question_like} set qid='$qns',uid='$user->uid',like_yes='$type' ";
        $set = ExecuteQuery($query, "insert");
        $array['suc'] = '1';
        $array['msg'] = 'Thank you, Votes counted';
    }

    $query = "select  SUM(like_yes)  as res from {question_like} where qid='$qns' group by qid ";
    $set = ExecuteQuery($query, "select");
    $show = empty($set[0]['res']) ? 0 : $set[0]['res'];
    echo $show . ' ' . $array['msg'];
}

function privacy_chk($owner = '', $qp = '', $share = '') {

    global $gSitePath, $user, $gDocPath, $base_root;
    if (!empty($user->uid) && $owner == $user->uid) {

        return true;
    }

    switch ($qp) {
        case 1:

            if (!empty($user->uid) && $owner == $user->uid) {
                return true;
            } else {
                drupal_set_message($message = 'Sorry Access deined for Other users!', $type = 'error');
                drupal_access_denied();
                die;
            }

            break;

        case 2:
            //check followers
            $query = "(select count(*) as yea from {follower} where follower_id='$user->uid' and uid='$owner') union(select count(*) as yea from {follower} where uid='$user->uid' and follower_id='$owner')  ";
            $cnt = ExecuteQuery($query, "select");

            if ($cnt[0][yea] || $cnt[1][yea]) {

            } else {
                drupal_set_message($message = 'Sorry, Only Followers and Followees to post answers!', $type = 'error');
                drupal_access_denied();
                die;
            }
            //check followee


            break;
        case 4:
            prompt_privacy($owner, $share);

            break;
        case 3:
        default:
            break;
    }
}

function prompt_privacy($owner = '', $share = '') {

    global $gSitePath, $user, $gDocPath, $base_root;

    switch ($share) {

        case 2:
            $query = "(select count(*) as yea from {follower} where follower_id='$user->uid' and uid='$owner') union(select count(*) as yea from {follower} where uid='$user->uid' and follower_id='$owner')  ";
            $cnt = ExecuteQuery($query, "select");

            if ($cnt[0][yea] || $cnt[1][yea]) {

            } else {
                drupal_set_message($message = 'Sorry, Only Followers and Followees to post answers!', $type = 'error');
                drupal_access_denied();
                die;
            }
            break;
        case 3:
            drupal_set_message($message = 'Sorry, Question is blocked for public by owner!', $type = 'error');
            drupal_access_denied();
            die;
            break;
        case 1:
        default:
            break;
    }
}

//ajax privacy


function privacy_chk_ajax($owner = '', $qp = '', $share = '') {

    global $gSitePath, $user, $gDocPath, $base_root;
    if ($owner == $user->uid) {

        return true;
    }

    switch ($qp) {
        case 1:

            if ($owner == $user->uid) {
                return true;
            } else {
                echo '<div class="warning">Sorry, Access denied for Other users for this question!</div>';
                exit;
            }

            break;

        case 2:
            //check followers
            $query = "(select count(*) as yea from {follower} where follower_id='$user->uid' and uid='$owner') union(select count(*) as yea from {follower} where uid='$user->uid' and follower_id='$owner')  ";
            $cnt = ExecuteQuery($query, "select");

            if ($cnt[0][yea] || $cnt[1][yea]) {
                
            } else {

                echo '<div class="warning">Sorry, Only Followers and Followees to access this question!</div>';
                exit;
                // drupal_set_message($message = 'Sorry, Only Followers and Followees to post answers!', $type = 'error');
                //drupal_goto();
            }
            //check followee


            break;
        case 4:
            prompt_privacy_ajax($owner, $share);

            break;
        case 3:
        default:
            break;
    }
}

function prompt_privacy_ajax($owner = '', $share = '') {

    global $gSitePath, $user, $gDocPath, $base_root;

    switch ($share) {

        case 2:
            $query = "(select count(*) as yea from {follower} where follower_id='$user->uid' and uid='$owner') union(select count(*) as yea from {follower} where uid='$user->uid' and follower_id='$owner')  ";
            $cnt = ExecuteQuery($query, "select");

            if ($cnt[0][yea] || $cnt[1][yea]) {

            } else {
                //  drupal_set_message($message = 'Sorry, Only Followers and Followees to post answers!', $type = 'error');
                echo '<div class="warning">Sorry, Only Followers and Followees to access answer!</div>';
                exit;
                //drupal_goto();
            }
            break;
        case 3:
            //drupal_set_message($message = 'Sorry, Question is blocked for public by owner!', $type = 'error');
            echo '<div class="warning">Sorry, Question is blocked for public by owner!</div>';
            exit;
            //drupal_goto();
            break;
        case 1:
        default:
            break;
    }
}

/// ajax privacy






function qlite_save() {
    global $gSitePath, $user, $gDocPath, $base_root;
    $mid = $_REQUEST['mid'];
    // print_r($_REQUEST);
    // exit;
    $voutput = '';
    $vquest = "select * from {possible_answer} where paid='" . $_REQUEST['answer'] . "'  ";
    $rquest = db_query($vquest);
    $olistquest = db_fetch_object($rquest);

    if (($_REQUEST['answer'] != '') && (isset($_REQUEST['save']))) {





        $numr = db_result(db_query("SELECT COUNT(*) from {possible_answer_vote} where qid='" . $mid . "' and uid='" . $user->uid . "'"));


        if ($numr == 0) {

            $calvotep = db_result(db_query("SELECT COUNT(*) from {possible_answer_vote} where panswer_id='" . $_REQUEST['answer'] . "' "));
            if ($calvotep == 0) {
                $votepointp = '1';
            } else {
                $votepointp = $olistquest->vote + 1;
            }

            $vInsQuery = "insert into possible_answer_vote(qid,uid,panswer_id,vote_pdate) values ('" . $mid . "', '" . $user->uid . "','" . $_REQUEST['answer'] . "','" . date('Y-m-d h:i:s') . "')";
            db_query($vInsQuery);




            $last_id = mysql_insert_id();
            ///////////////possible answer vote  mail start here ///////////////
            $qdetails = load_question($mid);

            $sel_ulists = "SELECT * FROM users where uid='$qdetails[uid]'";
            $user_namelistfs = ExecuteQuery($sel_ulists, "select");


            $sel_poss = "SELECT * FROM possible_answer_vote where vote_pid='$last_id'";
            $ans_exec = ExecuteQuery($sel_poss, "select");

            $sel_ans = "SELECT * FROM possible_answer where paid='$ans_exec[panswer_id]'";
            $panswer_exec = ExecuteQuery($sel_ans, "select");

            $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='5'";
            $rs_mgmt = db_query($sel_user_cmt);
            $list_content = db_fetch_object($rs_mgmt);
            $subject_proj = "Vote Notifications";
            $contentm = str_replace("#uname#", $user_namelistfs[0][name], $list_content->content);
            $contentm = str_replace("#anothername#", $user->name, $contentm);

            $contentm = str_replace("#question#", $qdetails[question], $contentm);
            $contentm = str_replace("#link#", $gSitePath . $qdetails['url'], $contentm);
            $contentm = str_replace("#content#", "vote for your question Answer is : " . $panswer_exec[answer] . "", $contentm);
            //echo $contentm;die;
            $ins_qry = "insert into hm_mails(from_mail_id,user_from_id,user_to_id,subject,content,mail_status,notify,posted_date)values('mgopi.php@gmail.com','" . $user->mail . "','" . $user_namelistfs[0]['mail'] . "','" . $subject_proj . "','" . $contentm . "',0,0,now())";
            db_query($ins_qry);

            //$mail_success = htmlmail_function($user_namelistfs[0]['mail'], $subject_proj, $contentm, '');
///////////////possible answer vote mail end here ///////////////





            $notify_insqry = "insert into notification(uid,is_answer,node_id)values('" . $user->uid . "','1','" . $mid . "')";
            db_query($notify_insqry);


            drupal_set_message(t('Thank you,Your Answer has been saved successfully!'), $type = 'success');
            send_votenotify($mid);

            increasepoints('2', $mid, '0');
            //badges
            //teacher($user->uid,$mid);

            $queryd = "SELECT qid, SUM(vote) as possiblevote FROM possible_answer where qid='" . $mid . "' GROUP BY qid";
            $query_listd = db_query($queryd);
            $fetvotd = db_fetch_object($query_listd);

            $query_sugests = "SELECT qid, SUM(vote) as suggestv FROM suggest_answer where qid='" . $mid . "' GROUP BY qid";
            $query_sugestlistd = db_query($query_sugests);
            $fetvotsugestbg = db_fetch_object($query_sugestlistd);
            $totalvotesm = $fetvotd->possiblevote + $fetvotsugestbg->suggestv;
            $totalvotesm;
            $calc = $totalvotesm * $votepointp / 100;
            $updatevoteposs = "update  possible_answer set vote='$votepointp' where paid='" . $_REQUEST['answer'] . "'";
            db_query($updatevoteposs);


            /////////////////////////nice answer /////////Good Answer ////////////////Great Answer////////

            $popcntans = db_result(db_query("SELECT COUNT(*) FROM {possible_answer_vote} where qid='" . $mid . "' "));
            //  echo $popcntans;
            $vSql = "select *,q.uid as uid from {question} as q left join {user_profile} as u on q.uid=u.uid where  q.qid='" . $mid . "'  ";
            $rlist = db_query($vSql);
            $ansrem = db_fetch_object($rlist);
            if ($popcntans == 1) {
                $stucntr = db_result(db_query("SELECT COUNT(*) FROM {user_badges} where  uid='" . $ansrem->uid . "'  and bid='25'"));
                if ($stucntr == 0) {
                    db_query("INSERT INTO {user_badges} (bid,uid) VALUES ('25','" . $ansrem->uid . "') ");
                }
            }
            //////////////Good Answer///////////////////////
            if ($popcntans == 3) {
                $stucntr = db_result(db_query("SELECT COUNT(*) FROM {user_badges} where  uid='" . $ansrem->uid . "'  and bid='17'"));
                if ($stucntr == 0) {
                    db_query("INSERT INTO {user_badges} (bid,uid) VALUES ('17','" . $ansrem->uid . "') ");
                }
            }
            //////////////great answers///////////////////////
            if ($popcntans == 5) {
                $stucntr = db_result(db_query("SELECT COUNT(*) FROM {user_badges} where  uid='" . $ansrem->uid . "'  and bid='19'"));
                if ($stucntr == 0) {
                    db_query("INSERT INTO {user_badges} (bid,uid) VALUES ('19','" . $ansrem->uid . "') ");
                }
            }
            drupal_goto("qlite/view/$mid");
        } else {
            drupal_set_message($message = 'You Have already answered This Question!', $type = 'error');
            drupal_goto("qlite/view/$mid");
        }
    } elseif (($_REQUEST['answer_al'] != '') && (isset($_REQUEST['change']))) {
        $arr = array_keys($_REQUEST['answer_al']);
        $a = $arr['0'];
        $poss_ans = $_REQUEST['answer_al'][$a];
        $vInsQuery = "update {possible_answer_vote} set qid='" . $mid . "',panswer_id='" . $poss_ans . "',vote_pdate=now() where vote_pid='" . $_REQUEST['vote_id'] . "' AND uid='" . $user->uid . "'";

        db_query($vInsQuery);
        drupal_set_message(t('Thank you,Your Answer has been changed successfully!'), $type = 'success');
        send_votenotify($mid);
    }

    if (($_REQUEST['answer_a2'] != '') && (isset($_REQUEST['change']))) {
        //$arr = array_keys($_REQUEST['answer_al']);
        //$a = $arr['0'];
        //$poss_ans = $_REQUEST['answer_al'][$a];
        $vInsQuery = "update {possible_answer_vote} set qid='" . $mid . "',panswer_id='" . $_REQUEST['answer_a2'] . "',vote_pdate=now() where vote_pid='" . $_REQUEST['vote_id'] . "' AND uid='" . $user->uid . "'";

        db_query($vInsQuery);
        drupal_set_message(t('Thank you,Your Answer has been changed successfully!'), $type = 'success');
        send_votenotify($mid);
    }




    ////////////question search vote added start here ****************
    if (($_REQUEST['answer_al'] != '') && (isset($_REQUEST['save']))) {
        $arr = array_keys($_REQUEST['answer_al']);
        $a = $arr['0'];
        $poss_ans = $_REQUEST['answer_al'][$a];


        $numr = db_result(db_query("SELECT COUNT(*) from {possible_answer_vote} where qid='" . $mid . "' and uid='" . $user->uid . "'"));
        if ($numr == 0) {

            $calvotep = db_result(db_query("SELECT COUNT(*) from {possible_answer_vote} where panswer_id='" . $poss_ans . "' "));
            if ($calvotep == 0) {
                $votepointp = '1';
            } else {
                $votepointp = $olistquest->vote + 1;
            }

            $vInsQuery = "insert into possible_answer_vote(qid,uid,panswer_id,vote_pdate) values ('" . $mid . "', '" . $user->uid . "','" . $poss_ans . "','" . date('Y-m-d h:i:s') . "')";
            db_query($vInsQuery);



            $last_id = mysql_insert_id();
            ///////////////possible answer vote  mail start here ///////////////
            $qdetails = load_question($mid);

            $sel_ulists = "SELECT * FROM users where uid='$qdetails[uid]'";
            $user_namelistfs = ExecuteQuery($sel_ulists, "select");


            $sel_poss = "SELECT * FROM possible_answer_vote where vote_pid='$last_id'";
            $ans_exec = ExecuteQuery($sel_poss, "select");

            $sel_ans = "SELECT * FROM possible_answer where paid='$ans_exec[panswer_id]'";
            $panswer_exec = ExecuteQuery($sel_ans, "select");

            $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='5'";
            $rs_mgmt = db_query($sel_user_cmt);
            $list_content = db_fetch_object($rs_mgmt);
            $subject_proj = "Vote Notifications";
            $contentm = str_replace("#uname#", $user_namelistfs[0][name], $list_content->content);
            $contentm = str_replace("#anothername#", $user->name, $contentm);

            $contentm = str_replace("#question#", $qdetails[question], $contentm);
            $contentm = str_replace("#link#", $gSitePath . $qdetails['url'], $contentm);
            $contentm = str_replace("#content#", "vote for your question Answer is : " . $panswer_exec[answer] . "", $contentm);
            //echo $contentm;die;
            $ins_qry = "insert into hm_mails(from_mail_id,user_from_id,user_to_id,subject,content,mail_status,notify,posted_date)values('mgopi.php@gmail.com','" . $user->mail . "','" . $user_namelistfs[0]['mail'] . "','" . $subject_proj . "','" . $contentm . "',0,0,now())";
            db_query($ins_qry);

            // $mail_success = htmlmail_function($user_namelistfs[0]['mail'], $subject_proj, $contentm, '');
///////////////possible answer vote mail end here ///////////////






            $notify_insqry = "insert into notification(uid,is_answer,node_id)values('" . $user->uid . "','1','" . $mid . "')";
            db_query($notify_insqry);


            drupal_set_message(t('Thank you,Your Answer has been saved successfully!'), $type = 'success');
            send_votenotify($mid);

            increasepoints('2', $mid, '0');
            //badges
            //teacher($user->uid,$mid);

            $queryd = "SELECT qid, SUM(vote) as possiblevote FROM possible_answer where qid='" . $mid . "' GROUP BY qid";
            $query_listd = db_query($queryd);
            $fetvotd = db_fetch_object($query_listd);

            $query_sugests = "SELECT qid, SUM(vote) as suggestv FROM suggest_answer where qid='" . $mid . "' GROUP BY qid";
            $query_sugestlistd = db_query($query_sugests);
            $fetvotsugestbg = db_fetch_object($query_sugestlistd);
            $totalvotesm = $fetvotd->possiblevote + $fetvotsugestbg->suggestv;
            $totalvotesm;
            $calc = $totalvotesm * $votepointp / 100;
            $updatevoteposs = "update  possible_answer set vote='$votepointp' where paid='" . $poss_ans . "'";
            db_query($updatevoteposs);


            /////////////////////////nice answer /////////Good Answer ////////////////Great Answer////////

            $popcntans = db_result(db_query("SELECT COUNT(*) FROM {possible_answer_vote} where qid='" . $mid . "' "));
            //  echo $popcntans;
            $vSql = "select *,q.uid as uid from {question} as q left join {user_profile} as u on q.uid=u.uid where  q.qid='" . $mid . "'  ";
            $rlist = db_query($vSql);
            $ansrem = db_fetch_object($rlist);
            if ($popcntans == 1) {
                $stucntr = db_result(db_query("SELECT COUNT(*) FROM {user_badges} where  uid='" . $ansrem->uid . "'  and bid='25'"));
                if ($stucntr == 0) {
                    db_query("INSERT INTO {user_badges} (bid,uid) VALUES ('25','" . $ansrem->uid . "') ");
                }
            }
            //////////////Good Answer///////////////////////
            if ($popcntans == 3) {
                $stucntr = db_result(db_query("SELECT COUNT(*) FROM {user_badges} where  uid='" . $ansrem->uid . "'  and bid='17'"));
                if ($stucntr == 0) {
                    db_query("INSERT INTO {user_badges} (bid,uid) VALUES ('17','" . $ansrem->uid . "') ");
                }
            }
            //////////////great answers///////////////////////
            if ($popcntans == 5) {
                $stucntr = db_result(db_query("SELECT COUNT(*) FROM {user_badges} where  uid='" . $ansrem->uid . "'  and bid='19'"));
                if ($stucntr == 0) {
                    db_query("INSERT INTO {user_badges} (bid,uid) VALUES ('19','" . $ansrem->uid . "') ");
                }
            }
            drupal_goto("qlite/view/$mid");
        } else {
            drupal_set_message($message = 'You Have already answered This Question!', $type = 'error');
            drupal_goto("qlite/view/$mid");
        }
    }
    ////////////question search vote added end here


    if ($_REQUEST['txt_act'] == 1) {


        $rlist = db_query("select * from possible_answer_vote where qid='" . $mid . "' and uid='" . $user->uid . "'");
        $ins = db_fetch_object($rlist);

        $query = "insert into {answer_withdraw} set uid='$user->uid',ans_type='',pid_sid='" . $ins->vote_pid . "',qid='$mid',ans_id='" . $ins->panswer_id . "',voted_date='" . $ins->vote_pdate . "'";
        db_query($query);

        $delQuery = "delete from  possible_answer_vote where qid='" . $mid . "' and uid='" . $user->uid . "' ";
        db_query($delQuery);

        drupal_set_message(t('Your Answer has been  Removed successfully!'), $type = 'success');
        drupal_goto("qlite/view/$mid");
    }
    drupal_goto("qlite/view/$mid");

    return $voutput;
}

function add_resources() {
    global $gSitePath, $user, $gDocPath, $base_root;

    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $resources = '<link rel="stylesheet" href="' . $gSitePath . drupal_get_path('module', 'quest_lite') . '/css/answer.css" type="text/css" />
         <script src="' . $gSitePath . '/misc/jquery.js"></script>
<link rel="stylesheet" href="' . $gSitePath . drupal_get_path('module', 'quest_lite') . '/css/fileuploader.css" type="text/css" />
            <script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'quest_lite') . '/scripts/fileuploader.js"></script>
            <script> var spath="' . $gSitePath . '";</script>
                   	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'forum') . '/scripts/jquery.blockUI.js"></script>
		<script type="text/javascript" src="' . $gSitePath . drupal_get_path('theme', 'heardmentality') . '/scripts/mootools-1.2-core.js"></script>
	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('theme', 'heardmentality') . '/scripts/mootools-1.2-more.js"></script>
	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'quest_lite') . '/scripts/add_resource.js"></script>
	<link rel="stylesheet" href="' . $gSitePath . path_to_theme() . '/css/css.css" type="text/css" />
	';

    $resources .= '<div id="log">
	<div class="facttop2">ADD RESOURCES</div>
	<div id="log_res"><!-- spanner --></div>
	</div><div id="err">' . $list_err . '</div><br/>
	<span class="clr"><!-- spanner --></span>';
    $resources .= '<form id="myForm" name="myForm"  method="post" action="' . $gSitePath . 'qlite/ajaxadd" enctype="multipart/form-data" ><input type="hidden" name="qaid" value="' . $qid . '"/>
	
	<br/><p class="float_lft"> Type	</p><p class="float_lft">
        <select name="rtype" class="textfieldm" id="rtype" >
	<option value="0">Select </option>
	<option value="1">News </option>
	<option value="2">Multimedia </option>
	<option value="3">Facts </option>
	</select>  
	</p>
    <br class="clr"/>
	<div id="div1" style="display:none;">
	<p class="float_lft"> Link </p>
    <p class="float_lft"><input type="text" class="textfieldm"  name="nlink" id="nlink"/> </p>
	<br class="clr"/>
	</div>
	
	<div  id="div2" style="display:none;">
	<br/><p class="float_lft"> Type </p><p class="float_lft"><select name="mtype" class="textfieldm" id="mtype"   >
	<option value="0">Select </option>
	<option value="1">Web Video </option>
	<option value="2">Podcast,PDF, DOC, PPT. </option>
	</select> </p>	<br class="clr"/></div>
	<div id="media" style="display:none;">
	<p class="float_lft">YouTube Link </p><p class="float_lft"><input type="text"  name="membed" id="membed"  class="textfieldm" > </p> <br class="clr"/>
	</div>
	<div id="media_div" style="display:none;">
	<p class="float_lft_file"> File </p><p class="float_lft" > <input type="hidden" name="docpath" id="docpath"/> <div id="file-uploader-demo1"> </div></p><br class="clr"/>
	</div>
	

	
	<div  id="div3" style="display:none;">
	<p class="float_lft"> Link </p><p class="float_lft"><input type="text" name="flink" id="flink" class="textfieldm"/> </p><br class="clr"/>
	</div>
	<input type="submit" name="button" id="submitter"  value="Add Resource"  />
	</form>';
    echo $resources;
}

function save_resources() {

    global $gSitePath, $user, $gDocPath, $base_root;
    if ($_REQUEST['rtype'] != 0) {
        if ($_REQUEST['membed'] != '') {
            $ytURL = $_REQUEST['membed'];
            $ytvIDlen = 11; // This is the length of YouTube's video IDs

            $idStarts = strpos($ytURL, "?v=");


            if ($idStarts === FALSE)
                $idStarts = strpos($ytURL, "&v=");

            if ($idStarts === FALSE)
                die("YouTube video ID not found. Please double-check your URL.");

            $idStarts += 3;

            $ytvID = substr($ytURL, $idStarts, $ytvIDlen);

            $ytvID;
        }

        $resourceadd = "insert into resource(rtype,nlink,ntitle,ncontent,mtype,membed,facts,uid,qid,nimage,document,video_id) values ('" . $_REQUEST['rtype'] . "','" . addslashes($_REQUEST['nlink']) . "','" . addslashes($_REQUEST['ntitle']) . "','" . addslashes($_REQUEST['ncontent']) . "','" . $_REQUEST['mtype'] . "','" . addslashes($_REQUEST['membed']) . "','" . addslashes($_REQUEST['flink']) . "', '" . $user->uid . "','" . $_REQUEST['qaid'] . "','" . $_REQUEST['path'] . "','" . $_REQUEST['docpath'] . "','" . $ytvID . "')";
        db_query($resourceadd);
        echo '<div class="messages success"> Resources Added Successfully! </div>';
    }
}

function flag_question() {
    global $gSitePath, $user, $gDocPath, $base_root;

    $falgq = '';
    $falgq .= '	<script>
	var spath="' . $gSitePath . '";
	</script>
		<script type="text/javascript" src="' . $gSitePath . '/misc/jquery.js"></script>
<script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'forum') . '/scripts/jquery.blockUI.js"></script>
	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'forum') . '/scripts/forum.js"></script>
	<link rel="stylesheet" href="' . base_path() . path_to_theme() . '/css/css.css" type="text/css" />
	';

    $falgq .= '
	
	';

    if (isset($_REQUEST['uid'])) {

        $uid = $_REQUEST['uid'];
        $vSql = "select * from {user_profile} where  uid='$uid' ";
        $rlist = db_query($vSql);
        $oListquest = db_fetch_object($rlist);
        $img_path1 = $gSitePath . drupal_get_path('module', 'profile') . '/snap/' . $oListquest->image;
        $PROFILE_IMAGE = '<img src="' . $img_path1 . '" align="absmiddle" alt="Profile image" >';
        $falgq .= '<div id="log">
	<div class="facttop2">FLAG USERS</div>
	<div id=""><b>Report this user!</b></div>
	<div id="log_res"></div>
	<span class="clr"><!-- spanner --></span>';
        $falgq .= '<form id="flagform"  method="post" action="' . $gSitePath . 'qlite/flagreport" enctype="multipart/form-data">
	<input type="hidden" name="uid" value="' . $uid . '"/>
	<div class="cmt_list"><div class="lft_view">  <p><span>' . $PROFILE_IMAGE . '</span><span>  </span><span>' . $oListquest->real_name . '</span> </p>
	 <p class="cmt_date">  ' . $oListquest->context . ' </p></div></div>
	<div class="txt_area">
	<input type="radio" name="abuse_type" id="abuse_type" value="Pornography or obscenity" />
	Pornography or obscenity <br/><input type="radio" name="abuse_type" id="abuse_type" value="radically or ethnically hateful content" />
	radically or ethnically hateful content  <br/> <input type="radio" name="abuse_type" id="abuse_type" value="Graphic Violence" />
	Graphic Violence <br/><input type="radio" name="abuse_type" id="abuse_type" value="other content inappropirate for young Viewers" />
	other content inappropirate for young Viewers <br/><input type="submit" name="button" id="submitter"  value="Report Problem"/></div></form>';
    } elseif (isset($_REQUEST['rid'])) {

        $rid = $_REQUEST['rid'];
        $vSql = "select * from {resource} as r  join {user_profile} as u on u.uid=r.uid where  r.rid='$rid' ";
        $rlist = db_query($vSql);
        $oListquest = db_fetch_object($rlist);
        $content = '';
        $content = (!empty($oListquest->nlink)) ? $oListquest->nlink : (!empty($oListquest->membed)) ? $oListquest->membed : (!empty($oListquest->facts)) ? $oListquest->facts : 'No Resource';
        $date = '';
        $date = format_date_class($oListquest->posted_date, date('Y-m-d h:i:s'));
        $falgq .= '<div id="log">
	<div class="facttop2">FLAG RESOURCES</div>
	<div id=""><b>Report this Resource!</b></div>
	<div id="log_res"></div>
	<span class="clr"><!-- spanner --></span>';
        $falgq .= '<form id="flagform"  method="post" action="' . $gSitePath . 'qlite/flagreport" enctype="multipart/form-data">
	<input type="hidden" name="rid" value="' . $rid . '"/>
	<div class="cmt_list"><div class="lft_view">  <p><span>Posted by ' . $oListquest->real_name . ' on ' . $date . '</span> </p>
	 <p class="cmt_date">  ' . $content . ' </p></div></div>
	<div class="txt_area">
	<input type="radio" name="abuse_type" id="abuse_type" value="Pornography or obscenity" />
	Pornography or obscenity <br/><input type="radio" name="abuse_type" id="abuse_type" value="radically or ethnically hateful content" />
	radically or ethnically hateful content  <br/> <input type="radio" name="abuse_type" id="abuse_type" value="Graphic Violence" />
	Graphic Violence <br/><input type="radio" name="abuse_type" id="abuse_type" value="other content inappropirate for young Viewers" />
	other content inappropirate for young Viewers <br/><input type="submit" name="button" id="submitter"  value="Report Problem"/></div></form>';
    } else {

        $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
        $vSql = "select * from {question} where status='1' and qid=$qid ";
        $rlist = db_query($vSql);
        $oListquest = db_fetch_object($rlist);
        $falgq .= '
	<div id="log">
	<div class="facttop2">FLAG QUESTIONS</div>
	<div id="log_res"><!-- spanner --></div>
	</div>
	<span class="clr"><!-- spanner --></span>';
        $falgq .= '<form id="flagform"  method="post" action="' . $gSitePath . 'qlite/flagreport" enctype="multipart/form-data">
	<input type="hidden" name="qaid" value="' . $qid . '"/>
	<div class="cmt_list"><div class="lft_view">  <p><b>Question :</b>' . $oListquest->question . ' </p>
 <p class="cmt_date"> <b>Context :</b> ' . $oListquest->context . ' </p></div></div>
<div class="txt_area">
	<input type="radio" name="abuse_type" id="abuse_type" value="Pornography or obscenity" />
	Pornography or obscenity <br/><input type="radio" name="abuse_type" id="abuse_type" value="radically or ethnically hateful content" />
	radically or ethnically hateful content  <br/> <input type="radio" name="abuse_type" id="abuse_type" value="Graphic Violence" />
	Graphic Violence <br/><input type="radio" name="abuse_type" id="abuse_type" value="other content inappropirate for young Viewers" />
	other content inappropirate for young Viewers <br/><input type="submit" name="button" id="submitter"  value="Report Problem"/></div></form>';
    }


    echo $falgq;
}

function tab_list() {
    global $gSitePath, $user, $gDocPath, $base_root;


    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    echo '<div class="toolbarTabs">
	<ul id="panelTabs" class="tab-menu">
	<li id="panelTabs1Link" class="selected"><a>Reporting</a></li>
	<li id="panelTabs2Link"><a>Forum</a></li>
	<li id="panelTabs3Link" ><a>Resources</a></li>
	<li id="panelTabs4Link"><a>Pundits</a></li>
	<li id="panelTabs5Link"><a>Info</a></li>
	<li id="panelTabs6Link"><a>Politician</a></li>
	</ul>
	<div class="clear"></div>
	</div>

	<script type="text/javascript">
	
	MochaUI.initializeTabs("panelTabs");
	
	$("panelTabs1Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("help-panel"),
	"url":       "' . $gSitePath . 'qlite/panel/' . $qid . '"
	});
	});
	
	$("panelTabs2Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("help-panel"),
	"url":       "' . $gSitePath . 'qlite/panel/' . $qid . '?type=Forum"
	});
	});
	
	$("panelTabs3Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("help-panel"),
	"url":       "' . $gSitePath . 'qlite/panel/' . $qid . '?type=Resources"
	});
	});
	$("panelTabs4Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("help-panel"),
	"url":       "' . $gSitePath . 'qlite/panel/' . $qid . '?type=Gurus"
	});
	});
	
	$("panelTabs5Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("help-panel"),
	"url":       "' . $gSitePath . 'qlite/panel/' . $qid . '?type=Info"
	});
	});
	
	$("panelTabs6Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("help-panel"),
	"url":       "' . $gSitePath . 'qlite/panel/' . $qid . '?type=Politician"
	});
	});
	
	
	</script>';
}

function panel_content() {

    global $gSitePath, $user, $gDocPath, $base_root;

    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    $type = $_REQUEST['type'];
    $queryd = "SELECT qid, SUM(vote) as possiblevote FROM possible_answer where qid='" . $qid . "' GROUP BY qid";
    $query_listd = db_query($queryd);
    $fetvotd = db_fetch_object($query_listd);

    $query_sugests = "SELECT qid, SUM(vote) as suggestv FROM suggest_answer where qid='" . $qid . "' GROUP BY qid";
    $query_sugestlistd = db_query($query_sugests);
    $fetvotsugestbg = db_fetch_object($query_sugestlistd);
    $totalvotesm = $fetvotd->possiblevote + $fetvotsugestbg->suggestv;
    $vSql = "select * from {question} where status='1' and qid=$qid ";
    $rlist = db_query($vSql);
    $oListquest = db_fetch_object($rlist);
//////////vijay 2 load submenu
    $query = " SELECT (SELECT count( * ) FROM forum_wavelets AS w WHERE w.wid = f.fid GROUP BY w.wid ) AS wcnt FROM forum_wave AS f WHERE f.qid_rid = '$qid' ";
    $list = ExecuteQuery($query, "select");
    $debatecnt = 0;
    foreach ($list as $fcnt) {

       $debatecnt = $debatecnt + $fcnt['wcnt'];
    }


    $numresource = db_result(db_query("SELECT COUNT(*) from {resource} where qid=$qid"));
    $query_user = "SELECT * FROM users where uid='$oListquest->uid' ";
    $query_userinfo = db_query($query_user);
    $fetuserlist = db_fetch_object($query_userinfo);
    switch ($type) {
        case "Forum":

            if (isset($_POST['wtitle']) && !empty($user->uid)) {

                $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
                extract($_POST);
                $forum = "INSERT INTO {forum_wave} set qid_rid='" . $qid . "',type='1',uid='$user->uid',title='" . mysql_escape_string($wtitle) . "',content='" . mysql_escape_string($wcon) . "',private='$wprivate' ";

                $nid = ExecuteQuery($forum, 'insert');
                echo list_wave($qid, 1);
                send_forumnotify($nid, $qid);
                exit;
            } elseif (isset($_POST['wtitle'])) {
                echo '<div align="center"><b>Sorry Only Logged in user can post wave</b></div>';
                echo list_wave($qid, 1);
                exit;
            }

            $output = forum_wave($qid);
            break;
        case "Resources":

            $output = '
			<div id="waveerr"></div>
                       <ul id="tabmenu" class="subtabs" >
                                       <li><a class="" href="javascript:tabactive(\'In\',\'' . $gSitePath . '\',\'' . $qid . '\')" id="tabIn">In the News</a></li>
                                       <li><a class="" href="javascript:tabactive(\'M\',\'' . $gSitePath . '\',\'' . $qid . '\')" id="tabM">Multimedia</a></li>
                                       <li><a class="" href="javascript:tabactive(\'F\',\'' . $gSitePath . '\',\'' . $qid . '\')" id="tabF">Facts</a></li>
                                       <li><a class="" href="javascript:loadresource(\'' . $gSitePath . 'qlite/resource/' . $qid . '\',\'Add\')" id="tab4">Add Resource</a></li>
                               </ul>
                               <div id="rcontents" class="mytabs-container"></div>
                               <script type="text/javascript">tabactive(\'In\',\'' . $gSitePath . '\',\'' . $qid . '\')</script>';

            break;
        case "Gurus":
            //	$output='sample content Gurus';
            $profileBadges = getAnsweredUsers($qid);


            $output1 = '';
            if (count($profileBadges) > 0) {
                $pat = $gSitePath . drupal_get_path('module', 'profile');
                foreach ($profileBadges as $profile) {
                    $medal = updateProfileBadge($profile['uid']);
                    $output1 .= '

<div class="profile-img">
<div class="profile-imgs">
 <a title="' . $profile['name'] . '" href="' . $gSitePath . 'profile/' . $profile['name'] . '">' . UserPicture($profile['uid']) . '</a>
</div>
<div class="profile-con">' . $medal . '
<div>

</div>
</div>

</div>


<div class="clr"></div><br/>';
                }
            } else {
                $output1 = "No Users available";
            }
            $output = $output1;

            break;
        case "Info":
            $bubble = load_bubble($fetuserlist->uid);
            $medal = updateProfileBadge($fetuserlist->uid);
            $section=load_qcat($qid);
            $output.= ' 
                       <div class="hm">
<div class="hm-left"><strong>Issue Information</strong><br />
  <br />
 <span class="profile-gray">Context</span> :' . $oListquest->context . '
     </div>
<div>
<div class="profile-lefthm">
<span class="profile-gray">Byline: </span>
<br />
<div class="profile-img">
<div class="profile-imgs">
 <a title="' . $fetuserlist->name . '" href="' . $gSitePath . 'profile/' . $fetuserlist->name . '">' . UserPicture($fetuserlist->uid) . '</a>
</div>
<div class="profile-con">' . $medal . '
<div>

</div>
</div>

</div>
<div class="clr"></div>
<div>

<span class="profile-gray">Date Created </span>:' . date("D j M Y", strtotime($oListquest->date_added)) . '  <br />
<span class="profile-gray">Number of Votes </span>:  ' . $totalvotesm . '<br />
<span class="profile-gray">Number of Forum Posts</span> : ' . $debatecnt . '<br />
<span class="profile-gray">Number of Resources </span> :  ' . $numresource . '<br />

</div>
</div>

</div><div class="clr"></div><br />

<div><span class="profile-gray">Section</span>:'.$section.'</div>

</div>
		';
            break;
        case "Politician":
            $output = 'sample content Politician';
            break;

        case "news":
            $output = 'sample content news';
            break;
        case "multimedia":
            $output = 'sample content multimedia';
            break;
        case "facts":
            $output = 'sample content facts';
            break;
        default:
            $output = '
			  <ul class="subtabs" id="tabs">
				<li class="current"><a href="javascript:loadReport(1,\'' . $gSitePath . '\',' . $qid . ');"  id="tab1">Votes</a></li>
				<li ><a href="javascript:loadReport(2,\'' . $gSitePath . '\',' . $qid . ');" class="" id="tab2">Overtime</a></li>
				<li ><a href="javascript:loadReport(3,\'' . $gSitePath . '\',' . $qid . ');" class="" id="tab3">By Area</a></li>
			</ul>
			   <div class="mytabs-container" id="tabs-container"><iframe id="frmGoogle" src="' . $gSitePath . '/qlite/percent/' . $qid . '" border="0" height="400" frameborder="0" width="100%"></iframe></div>
			<script type="text/javascript">loadReport(1,\'' . $gSitePath . '\',' . $qid . ')</script>';
            break;
    }
    echo $output;
}

function forum_wave($qid = '') {
    global $gSitePath, $user, $gDocPath, $base_root;

    $wave = '';


    //print_r($cnt);
    $wave .= '<div class="">
		<div class="qwavebut">
	<!--	<input type="button" onclick="newwave(\'' . $gSitePath . 'question/forum/' . $qid . '?action=new\',\'New Wave\')" value="New Wave" class="waveButtonMain"/> -->
	<input type="button" id="newwavebut" value="New Wave" onclick="toggle();" class="waveButtonMain"/>
		</div>
		<div class="comment" id="newwavediv" style="display:none">';
    if (!empty($user->uid)) {
        $wave .= '
	<div align="right"><a href="javascript:void(0);" onclick="toggle();">Close</a></div>
	<form  id="newwaveform" class="newwave" action="' . url($_GET['q'], array('absolute' => true)) . '?type=Forum" method="post" accept-charset="utf-8">
	<div ><b>Post New Wave</b></div>
        <p><b>Title</b></p>
        	<p><input type="text" name="wtitle" id="wtitle" value=""/></p>
                <p><b>Content</b></p>
	<p><textarea row="7" class="txtare" cols="55" name="wcon" id="wcon" ></textarea></p>
	<!--<div ><b>Private Reply :</b> [Only followers can do reply]</div>
	<p><select name="wprivate" id="wprivate">
	<option value="0"> Disabled</option>
	<option value="1"> Enabled  </option>
	</select></p>		-->			
	<p><input type="button" class="waveButtonMain" onclick="wave_form();" value="Post" /></p>
</form>';
    } else {
        $wave .= '<div align="center"><b>Sorry Only Logged in user can post wave</b></div>';
    }
    $wave .= '</div>
	<div><div id="qwave" class="">';


    $wave .= list_wave($qid, 1);


    $wave .= '</div>
	';


    return $wave;
}

function flag_report() {

    global $gSitePath, $user, $gDocPath, $base_root;

    $userPoints = checkUserPoints($user->uid);
    //&& $userPoints > 14
    if (isset($userPoints)) {
        if (isset($_REQUEST['uid'])) {

            $numr = db_result(db_query("SELECT COUNT(*) from {question_flags} where nodeid='" . $_REQUEST['uid'] . "' and uid='" . $user->uid . "' and  type='user' "));

            if ($_REQUEST['abuse_type'] != '') {
                if ($numr == 0) {
                    $flagquery = "insert into question_flags(nodeid,uid,type,abuse_type) values ('" . $_REQUEST['uid'] . "','" . $user->uid . "','user','" . $_REQUEST['abuse_type'] . "')";
                    db_query($flagquery);

                    $last_id = mysql_insert_id();
                    hm_flag($_REQUEST['uid'], $last_id, 1, 1);

                    $flagnotify = "insert into notification(uid,node_id,is_flag) values ('" . $user->uid . "','" . $_REQUEST['uid'] . "',1)";
                    db_query($flagnotify);

                    increasepoints('4', $_REQUEST['uid'], '0');
                    echo 'You Have Flagged successfully ! ';
                } else {
                    echo '<div class="red">You Have Already Flagged !</div>';
                }
            } else {

                echo '<div class="red">Select Report Type !</div>';
            }
        } elseif (isset($_REQUEST['rid'])) {

            $numr = db_result(db_query("SELECT COUNT(*) from {question_flags} where nodeid='" . $_REQUEST['rid'] . "' and uid='" . $user->uid . "' and  type='resource' "));
            if ($_REQUEST['abuse_type'] != '') {
                if ($numr == 0) {
                    $flagquery = "insert into question_flags(nodeid,uid,type,abuse_type) values ('" . $_REQUEST['rid'] . "','" . $user->uid . "','resource','" . $_REQUEST['abuse_type'] . "')";
                    db_query($flagquery);
                    $last_id = mysql_insert_id();
                    hm_flag($_REQUEST['rid'], $last_id, 1, 1);

                    $flagnotify = "insert into notification(uid,node_id,is_flag) values ('" . $user->uid . "','" . $_REQUEST['rid'] . "',1)";
                    db_query($flagnotify);

                    increasepoints('4', $_REQUEST['uid'], '0');
                    echo '<div class="">You Have Flagged successfully ! </div>';
                } else {
                    echo '<div class="red">You Have Already Flagged !</div>';
                }
            } else {

                echo '<div class="red">Select Report Type !</div>';
            }
        } elseif ($_REQUEST['rwave'] && $_REQUEST['rwave'] > 0) {


            $numr = db_result(db_query("SELECT COUNT(*) from {question_flags} where nodeid='" . $_REQUEST['rwave'] . "' and uid='" . $user->uid . "' and  type='wave' "));
            if ($_REQUEST['abuse_type'] != '') {
                if ($numr == 0) {
                    $flagquery = "insert into question_flags(nodeid,uid,type,abuse_type) values ('" . $_REQUEST['rwave'] . "','" . $user->uid . "','wave','" . $_REQUEST['abuse_type'] . "')";
                    db_query($flagquery);
                    $last_id = mysql_insert_id();
                    hm_flag($_REQUEST['rwave'], $last_id, 1, 1);

                    $flagnotify = "insert into notification(uid,node_id,is_flag) values ('" . $user->uid . "','" . $_REQUEST['rwave'] . "',1)";
                    db_query($flagnotify);

                    increasepoints('4', $_REQUEST['uid'], '0');
                    echo '<div class="">You Have Flagged successfully ! </div>';
                } else {
                    echo '<div class="red">You Have Already Flagged !</div>';
                }
            } else {

                echo '<div class="red">Select Report Type !</div>';
            }
        } elseif ($_REQUEST['rwavelet'] && $_REQUEST['rwavelet'] > 0) {


            $numr = db_result(db_query("SELECT COUNT(*) from {question_flags} where nodeid='" . $_REQUEST['rwavelet'] . "' and uid='" . $user->uid . "' and  type='wavelet' "));
            if ($_REQUEST['abuse_type'] != '') {
                if ($numr == 0) {
                    $flagquery = "insert into question_flags(nodeid,uid,type,abuse_type) values ('" . $_REQUEST['rwavelet'] . "','" . $user->uid . "','wavelet','" . $_REQUEST['abuse_type'] . "')";
                    db_query($flagquery);
                    $last_id = mysql_insert_id();
                    hm_flag($_REQUEST['rwavelet'], $last_id, 1, 1);

                    $flagnotify = "insert into notification(uid,node_id,is_flag) values ('" . $user->uid . "','" . $_REQUEST['rwavelet'] . "',1)";
                    db_query($flagnotify);

                    increasepoints('4', $_REQUEST['uid'], '0');
                    echo '<div class="">You Have Flagged successfully ! </div>';
                } else {
                    echo '<div class="red">You Have Already Flagged !</div>';
                }
            } else {

                echo '<div class="red">Select Report Type !</div>';
            }
        } else {

            $numr = db_result(db_query("SELECT COUNT(*) from {question_flags} where nodeid='" . $_REQUEST['qaid'] . "' and uid='" . $user->uid . "' and  type='question' "));
            if ($_REQUEST['abuse_type'] != '') {
                if ($numr == 0) {
                    $flagquery = "insert into question_flags(nodeid,uid,type,abuse_type) values ('" . $_REQUEST['qaid'] . "','" . $user->uid . "','question','" . $_REQUEST['abuse_type'] . "')";
                    db_query($flagquery);
                    $last_id = mysql_insert_id();
                    hm_flag($_REQUEST['qaid'], $last_id, 1, 1);

                    $flagnotify = "insert into notification(uid,node_id,is_flag) values ('" . $user->uid . "','" . $_REQUEST['qaid'] . "',1)";
                    db_query($flagnotify);

                    increasepoints('4', $_REQUEST['qaid'], '0');
                    echo '<div class="">You Have Flagged successfully ! </div>';
                } else {
                    echo '<div class="red">You Have Already Flagged !</div>';
                }
            } else {

                echo '<div class="red">Select Report Type !</div>';
            }
        }
    } else {

        echo '<div class="red">Sorry You Not Have Sufficent User Points To Flag !</div>';
    }
}

function suggest_answer() {

    global $gSitePath, $user, $gDocPath, $base_root;

    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $ansoutput = '	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('theme', 'heardmentality') . '/scripts/mootools-1.2-core.js"></script>
	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('theme', 'heardmentality') . '/scripts/mootools-1.2-more.js"></script>
	<link rel="stylesheet" href="' . $gSitePath . path_to_theme() . '/css/css.css" type="text/css" />
	<link rel="stylesheet" href="' . $gSitePath . 'sites/all/modules/quest_lite/css/answer.css" type="text/css" />';

    $answers = "SELECT * FROM suggest_answer where qid='" . $qid . "'  ";
    $anslist = db_query($answers);
    $count_row = db_result(db_query($answers));
    $numr = db_result(db_query("SELECT COUNT(*)  from {suggest_answer} where qid='" . $qid . "' and uid='" . $user->uid . "'"));
    $ansoutput .= '<div id="log">
	<div class="facttop">SUGGEST A NEW ANSWER</div>
	<div id="log_res"><!-- spanner --></div>
	</div>
	<span class="clr"><!-- spanner --></span>';

    $ansoutput .= '<div id="log_res_ans"><!-- spanner --></div>
	<span class="clr"><!-- spanner --></span>';

    $ansoutput .= '<script type="text/javascript">
	window.addEvent(\'domready\', function() {
	
	if (!window.demo_path) window.demo_path = \'\';
	var demo_path = window.demo_path;
	
	$(\'voteform\').addEvent(\'submit\', function(e) {
	
	e.stop();
	
	var log = $(\'log_res_ans\').empty().addClass(\'ajax-loadings\');
	
	this.set(\'send\', {onComplete: function(response) { 
	log.removeClass(\'ajax-loadings\');
	log.set(\'html\', response);
	}});
	
	this.send();
	});
	});
	
	
	</script>
	<form id="voteform"  method="post" action="' . $gSitePath . 'qlite/answervote"  enctype="multipart/form-data">
	<input type="hidden" name="qaid" value="' . $qid . '"/>';
    if (isset($count_row) && $count_row > 0) {
        $ansoutput .= '<h3>The Following Answers have been suggested by other users for this question:</h3>
	 <br/>
	Select Answer <br/>
	<p>'; // <select name="suggest" class="textfieldm" id="suggest">
        while ($answerfet = db_fetch_object($anslist)) {
            $ansoutput .= '<label><input type="radio" name="suggest" value="' . $answerfet->said . '" />' . $answerfet->answer . '</label><br/>';
            //<option  value="'.$answerfet->said.'">'.$answerfet->answer.' </option>';
        }
        $ansoutput .= '</p> <input type="submit" name="buttonvote" id="voteid"  value="Vote "/>';
    }
    $ansoutput .= '</form> ';


    if ($numr == 0) {
        $ansoutput .= '<script type="text/javascript">
	window.addEvent(\'domready\', function() {
	
	if (!window.demo_path) window.demo_path = \'\';
	var demo_path = window.demo_path;
	
	$(\'answerform\').addEvent(\'submit\', function(e) {
	
	e.stop();
	
	var log = $(\'log_res\').empty().addClass(\'ajax-loading\');
	
	this.set(\'send\', {onComplete: function(response) { 
	log.removeClass(\'ajax-loading\');
	log.set(\'html\', response);
	}});
	
	this.send();
	});
	});
	</script>	<form id="answerform"  method="post" action="' . $gSitePath . 'qlite/answersubmit"  enctype="multipart/form-data"><input type="hidden" name="qaid" value="' . $qid . '"/>
	<br/>
	<div class="txt_area">	Suggest Answer <input type="text" class="textfieldm"  name="txt_answer" id="txt_answer"/><br />
	<div class="comment_but"><input type="submit" name="button" id="submitter"  value="Suggest Answer"/></div>
	</div></form>';
    }
    if ($user->uid < 1) {
        $ansoutput = '<div class="messages error"> Sorry Only Registered User Can Suggest Answer! </div>';
    }

    echo $ansoutput;
}

function suggest_answer_save() {
    global $gSitePath, $user, $gDocPath, $base_root;

    $numr = db_result(db_query("SELECT COUNT(*) from {suggest_answer} where qid='" . $_REQUEST['qaid'] . "' and uid='" . $user->uid . "'"));
    if ($_REQUEST['txt_answer'] != '' && $user->uid > 0) {
        if ($numr == 0) {
            $answerquery = "insert into suggest_answer(qid,uid,answer,date_added) values ('" . $_REQUEST['qaid'] . "','" . $user->uid . "','" . $_REQUEST['txt_answer'] . "','" . date('Y-m-d') . "')";
            db_query($answerquery);
            //Suggest Answer badges
            db_query("insert into {user_badges} set bid='38',uid='$uid',qid='" . $_REQUEST['qaid'] . "'");
            $last_id = msyql_insert_id();
            // hm_mails('',$last_id,'user_badges');
            //badges_user($uid,$last_id);


            echo '<div class="messages success">Your Answer Posted Successfully ! </div>';
        }
    } else {
        echo '<div class="messages error">Sorry Error Occurs while voting! </div>';
    }
}

function question_news() {
    global $gSitePath, $user, $gDocPath, $base_root;
    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    set_time_limit(0);
    require ('RSSParser.class.php');
    $xml = & new RSSParser;

    $vSql = "SELECT *,IFNULL((select count(*) from {forum_wave} as w where w.qid_rid=r.rid AND type='2' group by w.qid_rid ),0) as cntpost,DATE_FORMAT(r.posted_date, '%a %M %Y %h:%i %p') as date_added FROM resource as r where r.rtype='1' and r.qid='" . $qid . "' ";
    $rlistnews = db_query($vSql);
    $numnews = db_result(db_query("SELECT COUNT(*) FROM resource where rtype='1' and qid='" . $qid . "'"));

    while ($usernews = db_fetch_object($rlistnews)) {
        $output = array();
        $output = $xml->parse($usernews->nlink);

        $like_count = resource_Like_checkCount($usermedia->rid, 1);
        $valuesresult = array();
        foreach ($output as $valuesresult) {

            // print_r( $valuesresult);
        }
        $opkt = array();
        foreach ($valuesresult as $opkt) {
            // print_r($opkt);
            $like = '';
            $flag = '';
            $post = '';
            $newsresult.='<div class=" post-title-forum " >';
            $querylike = "select * from {user_likes} where is_resource='1' AND uid='$user->uid' AND node_id='" . $usernews->rid . "'";
            $fetch = ExecuteQuery($querylike, "select");

            if (count($fetch) < 1 || $fetch[0]['is_like'] == '0') {

                $like .= '<span  id="likelink" ><a href="javascript:void(0);" class="href" onclick="likethis(\'is_resource\',' . $usernews->rid . ',1,this);">Like (' . $like_count . ')</a></span>';
            } elseif ($fetch[0]['is_like'] == '1') {

                $like .= '<span id="likelink" > <a href="javascript:void(0);" class="href" onclick="likethis(\'is_resource\',' . $usernews->rid . ',0,this);">Unlike (' . $like_count . ')</a></span>';
            }

            //flag
            $flag .= '[<a href="javascript:void(0);" onclick="loadflagquestion(\'' . $gSitePath . 'qlite/flag/?rid=' . $usernews->rid . '\',\'Report \');
">Report</a>]';

            //posts
            $post .= '[<a href="javascript:void(0);" onclick="loadrforum(\'' . $gSitePath . 'resource/forum/' . $usernews->rid . '\',\'Resource forum \');
">' . $usernews->cntpost . ' Comments</a>]';
            $getuser = user_load(array('uid' => $usernews->uid));
            $newsresult .= '
	
 <h4 ><a href="' . $opkt["LINK"] . '" target="new"> ' . $opkt["TITLE"] . ' </a> </h4>
		<p>' . $opkt['DESCRIPTION'] . ' </p>
                    <div class="clr"></div>
	 <div class="likelink-outer-forum">
           <div class="likekink-forum">
               <ul>
               <li>' . $like . ' </li>     <li>|</li>
               <li>' . $flag . '</li>     <li>|</li>
               <li>' . $post . '</li>   
             <li>Posted by <a href="' . $gSitePath . 'profile/' . $getuser->name . '">' . $getuser->name . '</a></li>     <li>|</li>
               </ul>
          </div>
           <div class="date">' . $opkt["PUBDATE"] . '</div>

        <div class="clr"></div>
        </div></div>';


            $newsresult .='</div><div class="clr"></div>';
        }
    }

    if ($numnews == 0) {

        $newsresult .= 'No News  Under This Question.';
    }
    echo $newsresult;
}

function question_media() {

    global $gSitePath, $user, $gDocPath, $base_root;
    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $vSqlmedia = "SELECT *,IFNULL((select count(*) from {forum_wave} as w where w.qid_rid=r.rid AND type='2' group by w.qid_rid ),0) as cntpost,DATE_FORMAT(r.posted_date, '%a %M %Y %h:%i %p') as date_added FROM resource as r where r.rtype='2' and r.qid='" . $qid . "' ";
    $rlistmedia = db_query($vSqlmedia);
    $nummedia = db_result(db_query("SELECT COUNT(*) FROM resource where rtype='2' and qid='" . $qid . "'"));


    while ($usermedia = db_fetch_object($rlistmedia)) {
        $mediaresult.= '<div class=" post-title-forum " >';
        //flag
        $flag = '';
        $post = '';
        $flag .= '[<a href="javascript:void(0);" onclick="loadflagquestion(\'' . $gSitePath . 'qlite/flag/?rid=' . $usermedia->rid . '\',\'Report \');
">Report</a>]';
        $like = '';
        $querylike = "select * from {user_likes} where is_resource='1' AND uid='$user->uid' AND node_id='" . $usermedia->rid . "'";
        $fetch = ExecuteQuery($querylike, "select");
        $like_count = resource_Like_checkCount($usermedia->rid, 2);
        if (count($fetch) < 1 || $fetch[0]['is_like'] == '0') {

            $like .= '<span  id="likelink" ><a href="javascript:void(0);" class="href" onclick="likethis(\'is_resource\',' . $usermedia->rid . ',1,this);">Like (' . $like_count . ')</a></span>';
        } elseif ($fetch[0]['is_like'] == '1') {

            $like .= '<span id="likelink" > <a href="javascript:void(0);" class="href" onclick="likethis(\'is_resource\',' . $usermedia->rid . ',0,this);">Unlike (' . $like_count . ')</a></span>';
        }

        //posts
        $post .= '[<a href="javascript:void(0);" onclick="loadrforum(\'' . $gSitePath . 'resource/forum/' . $usermedia->rid . '\',\'Resource forum \');
">' . $usermedia->cntpost . ' Comments</a>]';
        $getuser = user_load(array('uid' => $usermedia->uid));

        $mediaresult .= '
	 <h4 ><a href="' . $gSitePath . '' . $usermedia->document . '" target="_blank"> ' . $usermedia->document . ' </a> </h4>
	<!--<p><img src="http://img.youtube.com/vi/' . $usermedia->video_id . '/default.jpg" ></p>
	<br/> --> ';
        if (!empty($usermedia->video_id)) {
            $mediaresult .= '<p>
            <a  target="_blank" title="Youtube Video" href="http://www.youtube.com/v/' . $usermedia->video_id . '"  class="floatbox" data-fb-options="width:480 height:384">
<img width="125" height="100" src="http://img.youtube.com/vi/' . $usermedia->video_id . '/default.jpg" alt="Video " ></a></p>';
        }
        $mediaresult .= '
 <div class="clr"></div>
	 <div class="likelink-outer-forum">
           <div class="likekink-forum">
               <ul>
               <li>' . $like . ' </li>     <li>|</li>
               <li>' . $flag . '</li>     <li>|</li>
               <li>' . $post . '</li>
             <li>Posted by <a href="' . $gSitePath . 'profile/' . $getuser->name . '">' . $getuser->name . '</a></li>     <li>|</li>
               </ul>
          </div>
           <div class="date">' . $usermedia->date_added . '</div>

        <div class="clr"></div>
        </div></div>
';

        $mediaresult.='</div>';
    }
    if ($nummedia == 0) {

        $mediaresult .= 'No Media Under This Question.';
    }
    echo $mediaresult;
}

function question_facts() {

    global $gSitePath, $user, $gDocPath, $base_root;
    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $vSqlfact = "SELECT *,IFNULL((select count(*) from {forum_wave} as w where w.qid_rid=r.rid AND type='2' group by w.qid_rid ),0) as cntpost,DATE_FORMAT(r.posted_date, '%a %M %Y %h:%i %p') as date_added FROM resource as r where r.rtype='3' and r.qid='" . $qid . "' ";
    $rlistfacts = db_query($vSqlfact);
    $numfacts = db_result(db_query("SELECT COUNT(*) FROM resource where rtype='3' and qid='" . $qid . "'"));

    while ($userfacts = db_fetch_object($rlistfacts)) {
        $factsesult.= '<div class=" post-title-forum " >';
        $like = '';
        $querylike = "select * from {user_likes} where is_resource='1' AND uid='$user->uid' AND node_id='" . $userfacts->rid . "'";
        $fetch = ExecuteQuery($querylike, "select");

        if (count($fetch) < 1 || $fetch[0]['is_like'] == '0') {

            $like .= '<span  id="likelink" >[<a href="javascript:void(0);" class="href" onclick="likethis(\'is_resource\',' . $userfacts->rid . ',1,this);">Like</a>]</span>';
        } elseif ($fetch[0]['is_like'] == '1') {

            $like .= '<span id="likelink" > [<a href="javascript:void(0);" class="href" onclick="likethis(\'is_resource\',' . $userfacts->rid . ',0,this);">Unlike</a>]</span>';
        }

        //flag
        $flag = '';
        $post = '';
        $flag .= '[<a href="javascript:void(0);" onclick="loadflagquestion(\'' . $gSitePath . 'qlite/flag/?rid=' . $userfacts->rid . '\',\'Report \');
">Report</a>]';
        //posts
        $post .= '[<a href="javascript:void(0);" onclick="loadrforum(\'' . $gSitePath . 'resource/forum/' . $userfacts->rid . '\',\'Resource forum \');
">' . $userfacts->cntpost . ' Post</a>]';

        $like_count = resource_Like_checkCount($userfacts->rid, 3);

        $getuser = user_load(array('uid' => $userfacts->uid));

        $factsesult .= '<div class="">
<h4 class=""><a href="' . $userfacts->facts . '" target="_blank" > ' . $userfacts->facts . ' </a> </h4>
	';

        $factsesult .= '
 <div class="clr"></div>
	 <div class="likelink-outer-forum">
           <div class="likekink-forum">
               <ul>
               <li>' . $like . ' </li>     <li>|</li>
               <li>' . $flag . '</li>     <li>|</li>
               <li>' . $post . '</li>
             <li>Posted by <a href="' . $gSitePath . 'profile/' . $getuser->name . '">' . $getuser->name . '</a></li>     <li>|</li>
               </ul>
          </div>
           <div class="date">' . $userfacts->date_added . '</div>

        <div class="clr"></div>
        </div></div>
';

        $factsesult.='</div>';
    }
    if ($numfacts == 0) {

        $factsesult .= 'No Facts Under This Question.';
    }
    echo $factsesult;
}

function resource_Like_checkCount($rid = null, $rtype = null) {
    $query = "SELECT count(rid) FROM resource_like WHERE rid=$rid AND rtype=$rtype";
    $result = ExecuteQuery($query, "select");
    $like_count = isset($result[0][0]) ? $result[0][0] : 0;
    return $like_count;
}

function flip($arr) {
    $out = array();

    foreach ($arr as $key => $subarr) {
        foreach ($subarr as $subkey => $subvalue) {
            $out[$subkey][$key] = $subvalue;
        }
    }

    return $out;
}

function percent_broken($qid = '', $aid = '', $array = '') {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;


    $filter = '';
    $filter = (!empty($array['dochg'])) ? $array['dochg'] : '';
    $vans = "select * from {possible_answer} where  qid='" . $qid . "'";
    $vlist = ExecuteQuery($vans, "select");
    switch ($filter) {
        case 'gender':
            $answer['divide'] = array('male', 'female', 'undefined');




            foreach ($answer['divide'] as $list) {
                if ($list == 'male')
                    $gen = 1;
                elseif ($list == 'female')
                    $gen = 2;
                else
                    $gen='';

                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' AND u.gender='" . $gen . "' ";
                    $tcnt = ExecuteQuery($query, "norows");
                    $inc_cnt .= $tcnt . ',';
                }
                $inc_cnt = rtrim($inc_cnt, ",");
                $inc_cnt .= ']';

                $answer_cnt[] = $inc_cnt;
            }//[1,0][1,1]
            // $answer_cnt=array_reverse($answer_cnt);//[1,1][1,0]

            break;
        case 'age':
            $answer['divide'] = array('18-30', '30-50', '50 above', 'undefined');

            foreach ($answer['divide'] as $key => $value) {
                if ($key == 0)
                    $query_ins = "AND u.age BETWEEN '18' AND '30' ";
                elseif ($key == 1)
                    $query_ins = "AND u.age BETWEEN '30' AND '50'";
                elseif ($key == 2)
                    $query_ins = "AND u.age>='50' ";
                else
                    $query_ins = "AND u.age='' ";


                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' " . $query_ins;
                    $tcnt = ExecuteQuery($query, "norows");
                    $inc_cnt .= $tcnt . ',';
                }
                $inc_cnt = rtrim($inc_cnt, ",");
                $inc_cnt .= ']';

                $answer_cnt[] = $inc_cnt;
            }


            //$answer_cnt;
            break;
        case 'religion':
            $answer['divide'] = array('Christian', 'Muslim', 'Jewish', 'Hindu', 'Buddhist', 'Other', 'undefined');

            foreach ($answer['divide'] as $list) {
                if ($list == 'undefined')
                    $reg = '';
                else
                    $reg=$list;

                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' AND religion='" . $reg . "'";
                    $tcnt = ExecuteQuery($query, "norows");
                    $inc_cnt .= $tcnt . ',';
                }
                $inc_cnt = rtrim($inc_cnt, ",");
                $inc_cnt .= ']';
                $answer_cnt[] = $inc_cnt;
            }


            break;
        case 'ethnicity':
            $answer['divide'] = array('Caucasian', 'Black', 'Asian', 'Indian', 'Semetic', 'Latin', 'Aborigines', 'undefined');

            foreach ($answer['divide'] as $list) {
                if ($list == 'undefined')
                    $reg = '';
                else
                    $reg=$list;

                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' AND ethnic='" . $reg . "'";
                    $tcnt = ExecuteQuery($query, "norows");
                    $inc_cnt .= $tcnt . ',';
                }
                $inc_cnt = rtrim($inc_cnt, ",");
                $inc_cnt .= ']';
                $answer_cnt[] = $inc_cnt;
            }


            break;
        case 'slant':
            $answer['divide'] = array('Left', 'Right', 'Center', 'undefined');

            foreach ($answer['divide'] as $list) {
                if ($list == 'undefined')
                    $reg = '';
                else
                    $reg=$list;


                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' AND slant='" . $reg . "'";
                    $tcnt = ExecuteQuery($query, "norows");
                    $inc_cnt .= $tcnt . ',';
                }
                $inc_cnt = rtrim($inc_cnt, ",");
                $inc_cnt .= ']';
                $answer_cnt[] = $inc_cnt;
            }

            break;
        default:
            $answer['divide'] = array('Total No Of Votes');
            $inc_cnt = '[';
            for ($ab = 0; $ab < count($vlist); $ab++) {
                $query = "select * from {possible_answer_vote} where qid='" . $qid . "' and panswer_id='" . $vlist[$ab]['paid'] . "' ";
                $tcnt = ExecuteQuery($query, "norows");
                $inc_cnt .= $tcnt . ',';
            }
            $inc_cnt = rtrim($inc_cnt, ",");
            $inc_cnt .= ']';
            $answer_cnt[] = $inc_cnt;

            break;
    }

    $answer['cnt'] = $answer_cnt;
    return $answer;
}

function qlite_percent() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $output = '';
    $filter = '';
    $incflt = '';
    $opt = '';
    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    $vans = "select * from {possible_answer} where  qid='" . $qid . "'";
    $vlist = ExecuteQuery($vans, "select");
    $cnt_ans = count($vlist);
    $output .= " 	
			<script type='text/javascript' src='http://code.jquery.com/jquery-1.4.2.min.js'></script>				
			<script type='text/javascript' src='" . $gSitePath . drupal_get_path('module', 'quest_lite') . "/scripts/highcharts.js'></script>
<script>var example = 'bar-stacked',
	theme = 'skies';
</script>
<link rel='stylesheet' href='" . $gSitePath . drupal_get_path('theme', 'heardmentality') . "/css/content.css' type='text/css' />
			<script type='text/javascript' src='" . $gSitePath . drupal_get_path('module', 'quest_lite') . "/scripts/filter.js'></script>
	<script type='text/javascript' src='" . $gSitePath . drupal_get_path('module', 'quest_lite') . "/scripts/skies.js'></script>

			";

    $ans_array = array();
    for ($ab = 0; $ab < $cnt_ans; $ab++) {
        array_push($ans_array, $vlist[$ab]['answer']);
    }
    $result = percent_broken($qid, '', $_REQUEST);
    //echo "<pre>";
    //print_r($result);
    $ans = $result['divide'];
    $cnt = $result['cnt'];

    foreach ($ans as $key => $value) {
        $ins_script .= "{name: '" . $ans[$key] . "',data: " . $cnt[$key] . "},";
    }

    $per = json_encode($result);
    $inc = rtrim($ins_script, ',');
    $output .= "
		<script >

		var spath='" . $gSitePath . "';
		var chart;
			$(document).ready(function() {
				chart = new Highcharts.Chart({
					chart: {
						renderTo: 'chart_div',
						defaultSeriesType:'bar'
					},
					title: {
						text: 'Percent Reporting'
					},
					xAxis: {
						categories: " . json_encode($ans_array) . ",
                                                  labels :{ style: {
                  font: 'bold 12px Arial,Helvetica,sans-serif '
               }}
	},
					yAxis: {tickInterval  :1,
						min: 0,
						title: {
							text: 'No Of Votes'
						},
                                                labels :{ style: {
                   font: 'bold 12px Arial,Helvetica,sans-serif '
               }}},
					legend: {
						backgroundColor: '#FFFFFF',
						reversed: true
					},
					tooltip: {
						formatter: function() {
							return ''+
								 this.series.name +': '+ this.y +'';
						}
					},
					plotOptions: {
						series: {
							stacking: 'normal'
						}
					},
				      series: [" . $inc . " ]
				});
				
				
			});</script>";


    $filter = (!empty($_REQUEST['dochg'])) ? $_REQUEST['dochg'] : '';

    if (!empty($filter)) {

        $incflt = '<div ><b>Filter by :</b><i>' . ucwords($filter) . '';
        $incflt .= '<input type="button" name="go_button" id= "go_button" value="Reset" onclick="MM_jumpMenuGo(this.value)" /></div>';
    }


    echo $output .= '
<div id="contentr1" class="clear">
	' . $incflt . '
     <div align="right" > <form id="form1" name="form1" method="post" action="">
Filter by :
      
  <select name="dochg"  id="dochg">

  <option value="">Select</option>
  <option value="gender">Gender</option>
   <option value="age">Age</option>
    <option value="religion">Religion</option>
    <option value="ethnicity">Ethnicity</option>
    <option value="slant">Slant</option>
   
  </select></label>
  <span id="fopt" ></span>
  <input type="button" name="go_button" id= "go_button" value="Go" onclick="MM_jumpMenuGo(this.value)" />
  
    <br />
 </form></div>
    <div id="chart_div" style="width: 400px; height: 240px;">
    </div>
</div>';
}

function qlite_graph() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $script = '';
    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);


    $vans = "select * from {possible_answer} where  qid=$qid ";
    $vlist = ExecuteQuery($vans, "select");
    $cnt_ans = count($vlist);

    $script .= "
        				<link rel='stylesheet' href='" . $gSitePath . drupal_get_path('module', 'quest_lite') . "/plugins/jquery.jqplot.css' type='text/css' />
        <script type='text/javascript' src='http://code.jquery.com/jquery-1.4.2.min.js'></script>	
       			<script type='text/javascript' src='" . $gSitePath . drupal_get_path('module', 'quest_lite') . "/scripts/highcharts.js'></script>
<link rel='stylesheet' href='" . $gSitePath . drupal_get_path('theme', 'heardmentality') . "/css/content.css' type='text/css' />
<script type='text/javascript' language='javascript'>

";

    $s1 = array();
    $grid = array();


    for ($ab = 0; $ab < $cnt_ans; $ab++) {
        $i = $ab + 1;
        $ans = array();
        for ($mn = 4; $mn >= 0; $mn--) {

            $year = date("Y");
            $month = date("m") - 1;
            $dat = date("d") - $mn;
            $date = date('Y-m-d', mktime(0, 0, 0, $month + 1, $dat, $year));

            $inc_this = answer_details($qid, $vlist[$ab]['paid'], 'timeline', $date);
            array_push($ans, $inc_this);
        }
        $ins_sc = '[' . implode(',', $ans) . ']';
        array_push($grid, "'" . $vlist[$ab]['answer'] . "'");
        $insdata.="{name :'" . $vlist[$ab]['answer'] . "', data: " . $ins_sc . "},";
    }
    $sdate = "Date.UTC(" . $year . "," . $month . "," . (date("d") - 6) . ", 0, 0, 0)";
    // $script.=$ins_sc;



    echo $script .= "
var chart;
var gSitePath='" . $gSitePath . "';

$(document).ready(function() {
   chart = new Highcharts.Chart({
      chart: {
         renderTo: 'container',
         defaultSeriesType: 'spline',
         ignoreHiddenSeries: false,
         zoomType: 'x',
	spacingRight: 20

      },
      title: {
         text: 'Overtime Graph'
      },
      subtitle: {
         text: ''
      },
      xAxis: {
         type: 'datetime'
      },
      yAxis: {
         title: {
            text: 'No Of Votes (Per Day)'
         },
         min: 0,
         minorGridLineWidth: 0,
         gridLineWidth: 0,
         alternateGridColor: null,
         plotBands: [{ // Light air
            from: 0.3,
            to: 1.5,
            color: 'rgba(68, 170, 213, 0.1)'
         }, { // Gentle breeze
            from: 3.3,
            to: 5.5,
            color: 'rgba(68, 170, 213, 0.1)'
         }, { // Fresh breeze
            from: 8,
            to: 11,
            color: 'rgba(68, 170, 213, 0.1)'
         }, { // High wind
            from: 14,
            to: 15,
            color: 'rgba(68, 170, 213, 0.1)'
         }]
      },
      tooltip: {
         formatter: function() {
                   return ''+
               Highcharts.dateFormat('%e. %b %Y', this.x) +': '+ this.y +' Votes';
         }
      },
      plotOptions: {
          series: {
            cursor: 'pointer',
            point: {
                events: {
                    click: function() {
                       display_resource(this.category);
                    }
                }
            }
        },
         spline: {
            lineWidth: 4,
            states: {
               hover: {
                  lineWidth: 5
               }
            },
            marker: {
               enabled: false,
               states: {
                  hover: {
                     enabled: true,
                     symbol: 'circle',
                     radius: 5,
                     lineWidth: 1
                  }
               }
            },
            pointInterval: 3600000*36, // one hour
            pointStart:" . $sdate . "
         }
      },
      series: [" . $insdata . "]
   });


});

function display_resource(dat){

var url=gSitePath+'qlite/ajax';
jQuery.ajax({
   type: 'POST',
   url: url,
   dataType:'xhr',
  data: {
            action: 'graph',
            date:dat,
            qid:'" . $qid . "'
        },
   success: function(msg){
jQuery('#resource').html(msg);
   }
 });

}


</script>
";


    echo '<div id="container" class="highcharts-container" style="height:410px; width: 400px; margin: 0 auto; clear:both"></div>
        <div id="resource" style="height:auto; width: 400px; margin: 0 auto; clear:both"></div>

';
}

function qlite_map() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path, $googlekey;

    $inc_script = '';
    $resulte = '';
    $script = '';
    $desc = '';
    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    $marker = array('blue', 'green', 'red', 'black', 'brown', ' purple', 'yellow', 'gray', 'orange', 'white');

    $vans = "select * from {possible_answer} where  qid=$qid ";
    $vlist = ExecuteQuery($vans, "select");
    $cnt_ans = count($vlist);

    $mlatall = '';
    $mlongall = '';
    $ziparyall = '';
    for ($i = 0; $i < $cnt_ans; $i++) {

        $pans = db_query("select * from {possible_answer_vote} as pav left join {user_profile} as u on u.uid=pav.uid where pav.panswer_id='" . $vlist[$i]['paid'] . "' ");
        //$pans = db_query("select * from {users}  LIMIT 0,3");
        $ans_cnt = $i + 1;
        $getresult = array();
        while ($fieldsset = db_fetch_object($pans)) {

            $getresult[] = $fieldsset;
        }
        $pcnt_ans = count($getresult);

        $filter='<select onchange="zoomto(this.value);"><option value="-180,-90,0,90">Left hemisphere</option><option value="0,-90,180,90">Right hemisphere</option><optgroup label="Countries"><option value="22.3569164276123,41.2420806884766,28.6092796325684,44.2154502868652">Bulgaria</option><option value="-5.51891613006592,9.40110778808594,2.40539503097534,15.0825939178467">Burkina Faso</option><option value="28.9948463439941,-4.46461534500122,30.8477306365967,-2.31012296676636">Burundi</option><option value="102.343940734863,9.90625,107.626121520996,14.6860008239746">Cambodia</option><option value="43.2163543701172,-12.4138212203979,44.5382232666016,-11.3628215789795">Comoros</option><option value="11.2050085067749,-5.02722311019897,18.6498394012451,3.70308208465576">Congo</option><option value="13.493221282959,42.1301956176758,19.4491195678711,46.5336112976074">Croatia</option><option value="-176.64323425293,0.797774970531464,-176.635711669922,0.812214016914368">Howland Island</option><option value="-174.545059204102,-11.4370384216309,176.845108032227,4.71521615982056">Kiribati</option><option value="-61.0741500854492,13.7047777175903,-60.8742027282715,14.1032457351685">Saint Lucia</option><option value="-56.4206581115723,46.7532615661621,-56.1582107543945,47.1462860107422">Saint Pierre and Miquelon</option><option value="60.4784393310547,29.3774719238281,74.8785552978516,38.4834213256836">Afghanistan</option><option value="19.2767753601074,39.6444816589355,21.0572834014893,42.6610832214355">Albania</option><option value="-8.67386817932129,18.9600276947021,11.9795484542847,37.0915260314941">Algeria</option><option value="-171.088394165039,-14.3824787139893,-169.416076660156,-11.0518245697021">American Samoa</option><option value="1.42388892173767,42.4401626586914,1.78038907051086,42.6586952209473">Andorra</option><option value="11.680835723877,-18.0417594909668,24.0821208953857,-4.37682580947876">Angola</option><option value="-179.139190673828,18.9136848449707,179.776428222656,71.3906631469727">United States</option><option value="-58.4427223205566,-35.0479431152344,-53.0755386352539,-30.0822238922119">Uruguay</option><option value="-63.4325141906738,18.1668148040771,-62.9320373535156,18.6127872467041">Anguilla</option><option value="-180,-90,180,-60.5157585144043">Antarctica</option><option value="-62.3516807556152,16.9272193908691,-61.6613693237305,17.728967666626">Antigua and Barbuda</option><option value="-73.5829772949219,-55.0613174438477,-53.5918312072754,-21.7812767028809">Argentina</option><option value="43.449779510498,38.8312454223633,46.6300315856934,41.3014183044434">Armenia</option><option value="-70.0607833862305,12.4060926437378,-69.8761215209961,12.6306180953979">Aruba</option><option value="122.928695678711,-12.5325832366943,123.559524536133,-12.2509994506836">Ashmore and Cartier Islands</option><option value="112.911056518555,-54.7782554626465,159.111282348633,-9.18258380889893">Australia</option><option value="9.53591537475586,46.3780288696289,17.1627235412598,49.0170593261719">Austria</option><option value="44.771915435791,38.3983573913574,50.6067771911621,41.9056434631348">Azerbaijan</option><option value="50.3862228393555,25.5422496795654,50.8286437988281,26.2825832366943">Bahrain</option><option value="-176.484802246094,0.194290995597839,-176.47380065918,0.206694006919861">Baker Island</option><option value="88.0283279418945,20.5852508544922,92.6736755371094,26.6319465637207">Bangladesh</option><option value="-59.64892578125,13.0398435592651,-59.4235229492188,13.3269510269165">Barbados</option><option value="23.176887512207,51.2564125061035,32.769474029541,56.1658096313477">Belarus</option><option value="2.54694390296936,49.4936065673828,6.4038610458374,51.5054473876953">Belgium</option><option value="-89.2234725952148,15.8894281387329,-87.4725036621094,18.4965286254883">Belize</option><option value="0.774574995040894,6.22574758529663,3.85097622871399,12.4174184799194">Benin</option><option value="-64.8960494995117,32.2466354370117,-64.6553649902344,32.3901176452637">Bermuda</option><option value="88.7597198486328,26.7076396942139,92.1245651245117,28.3237781524658">Bhutan</option><option value="-69.6407623291016,-22.8961334228516,-57.4580955505371,-9.68056678771973">Bolivia</option><option value="15.720027923584,42.5602226257324,19.6219367980957,45.2391967773438">Bosnia and Herzegovina</option><option value="20,-26.907247543335,29.360782623291,-17.781774520874">Botswana</option><option value="3.34104180335999,-54.4623832702637,3.48797607421875,-54.4023056030273">Bouvet Island</option><option value="-73.9821701049805,-33.7505340576172,-28.8408145904541,5.26487731933594">Brazil</option><option value="71.2599716186523,-7.43802833557129,72.4926452636719,-5.22719383239746">British Indian Ocean Territory</option><option value="-64.8315200805664,18.3127365112305,-64.2770538330078,18.7566604614258">British Virgin Islands</option><option value="114.071441650391,4.00636053085327,115.359451293945,5.04716730117798">Brunei</option><option value="8.49497222900391,1.652547955513,16.1919918060303,13.0780563354492">Cameroon</option><option value="-141,41.7082939147949,-52.6362915039062,83.1066513061523">Canada</option><option value="-25.3564014434814,14.8022136688232,-22.6758079528809,17.195369720459">Cape Verde</option><option value="-81.4327774047852,19.2630271911621,-79.7272644042969,19.7614250183105">Cayman Islands</option><option value="14.4200963973999,2.22051382064819,27.4634227752686,11.0072717666626">Central African Republic</option><option value="13.4788265228271,7.44106769561768,24.0015850067139,23.4503707885742">Chad</option><option value="-109.455894470215,-55.9794960021973,-66.4180908203125,-17.5075511932373">Chile</option><option value="73.5587387084961,18.1612777709961,134.771575927734,53.560863494873">China</option><option value="105.539878845215,-10.5758619308472,105.719581604004,-10.4159154891968">Christmas Island</option><option value="-109.233299255371,10.2820692062378,-109.199317932129,10.3134508132935">Clipperton Island</option><option value="96.8245544433594,-12.1854162216187,96.9247512817383,-11.8039169311523">Cocos (Keeling) Islands</option><option value="-81.7241363525391,-4.22554445266724,-66.8698348999023,13.3902921676636">Colombia</option><option value="12.2041435241699,-13.4556751251221,31.305362701416,5.38609838485718">Congo, The Democratic Republic</option><option value="-165.858093261719,-21.944164276123,-157.312133789062,-8.94402980804443">Cook Islands</option><option value="149.12907409668,-17.7276382446289,155.860565185547,-16.0195007324219">Coral Sea Islands</option><option value="-87.0909652709961,5.49907398223877,-82.5565185546875,11.2168197631836">Costa Rica</option><option value="-8.59930229187012,4.35707759857178,-2.49489593505859,10.7366428375244">Cote D\'Ivoire</option><option value="-84.9574356079102,19.8280811309814,-74.1317749023438,23.5949268341064">Cuba</option><option value="32.2749404907227,34.6314964294434,34.5969734191895,35.701530456543">Cyprus</option><option value="12.0961933135986,48.542911529541,18.8601112365723,51.058780670166">Czech Republic</option><option value="8.07561016082764,54.562385559082,15.1582221984863,57.7480545043945">Denmark</option><option value="41.7734413146973,10.9099168777466,43.4160575866699,12.7068338394165">Djibouti</option><option value="-61.4841117858887,15.2016897201538,-61.2480926513672,15.6312808990479">Dominica</option><option value="-72.0034942626953,17.4700908660889,-68.3242645263672,19.929859161377">Dominican Republic</option><option value="124.979042053223,-9.36294555664062,127.304916381836,-8.3279447555542">Eastern Timor (Timor-Leste)</option><option value="-92.0107803344727,-4.99882316589355,-75.1845855712891,1.66477310657501">Ecuador</option><option value="24.6981105804443,21.7253875732422,36.2417793273926,31.6665840148926">Egypt</option><option value="-90.128662109375,13.1495923995972,-87.6965866088867,14.4450521469116">El Salvador</option><option value="5.60236692428589,-1.45994603633881,11.3347826004028,3.78598022460938">Equatorial Guinea</option><option value="36.438777923584,12.3596668243408,43.1480865478516,18.0030841827393">Eritrea</option><option value="21.7737216949463,57.5200538635254,28.2055015563965,59.687198638916">Estonia</option><option value="33.0001945495605,3.40242195129395,47.9861793518066,14.8937501907349">Ethiopia</option><option value="-61.3451957702637,-52.9005813598633,-57.7124824523926,-51.0149383544922">Falkland Islands (Islas Malvinas)</option><option value="-7.68125009536743,61.3949394226074,-6.25861072540283,62.400749206543">Faroe Islands</option><option value="138.052825927734,5.25983285903931,163.034896850586,11.6744441986084">Federated States of Micronesia</option><option value="-180,-20.6759700775146,180,-12.480110168457">Fiji</option><option value="19.3196926116943,59.7675819396973,31.5809440612793,70.0960540771484">Finland</option><option value="-5.14222240447998,41.3387756347656,9.56155681610107,51.0928077697754">France</option><option value="-54.539306640625,2.12709379196167,-51.6150588989258,5.77625942230225">French Guiana</option><option value="-154.688171386719,-27.6535720825195,-134.880523681641,-7.82849979400635">French Polynesia</option><option value="50.1766357421875,-50.0202674865723,77.598274230957,-37.7907218933105">French Southern and Antarctic Lands</option><option value="8.69573020935059,-3.97880601882935,14.5016717910767,2.32261204719543">Gabon</option><option value="40.0101356506348,41.0531959533691,46.7259712219238,43.5857772827148">Georgia</option><option value="5.86563873291016,47.275806427002,15.0398893356323,55.0550575256348">Germany</option><option value="-3.25542116165161,4.73672294616699,1.19178104400635,11.1733016967773">Ghana</option><option value="-5.35322237014771,36.1125259399414,-5.34002780914307,36.1598052978516">Gibraltar</option><option value="47.2800827026367,-11.5733966827393,47.2940711975098,-11.5492248535156">Glorioso Islands</option><option value="19.3744449615479,34.8096389770508,29.6455841064453,41.7574195861816">Greece</option><option value="-73.2634735107422,59.7772636413574,-11.3123188018799,83.6274261474609">Greenland</option><option value="-61.799976348877,11.9923734664917,-61.3776893615723,12.5292158126831">Grenada</option><option value="-63.1440391540527,15.8309726715088,-61,18.1306972503662">Guadeloupe</option><option value="144.619506835938,13.2406101226807,144.953308105469,13.6508884429932">Guam</option><option value="-92.2414932250977,13.7381963729858,-88.2231979370117,17.8174018859863">Guatemala</option><option value="-15.0862560272217,7.19355297088623,-7.64107084274292,12.6762208938599">Guinea</option><option value="-16.7175350189209,10.8599691390991,-13.6365213394165,12.6807899475098">Guinea-Bissau</option><option value="-61.384765625,1.17507994174957,-56.4802474975586,8.55756759643555">Guyana</option><option value="-74.4777145385742,18.0210304260254,-71.6133499145508,20.0878200531006">Haiti</option><option value="72.5965347290039,-53.1920013427734,73.856689453125,-52.9094123840332">Heard Island and McDonald Islands</option><option value="12.4434814453125,41.8991355895996,12.459584236145,41.9092025756836">Holy See (Vatican City State)</option><option value="-89.3499450683594,12.9824104309082,-83.1560516357422,17.4236297607422">Honduras</option><option value="113.837745666504,22.1532497406006,114.432861328125,22.5619487762451">Hong Kong</option><option value="16.111888885498,45.7436065673828,22.9060001373291,48.5851135253906">Hungary</option><option value="-24.5423412322998,63.2867546081543,-13.4958143234253,66.5625381469727">Iceland</option><option value="68.1629409790039,6.74713897705078,97.4033050537109,35.5042266845703">India</option><option value="95.0093307495117,-11.004861831665,141.021820068359,5.90441703796387">Indonesia</option><option value="44.0472755432129,25.0640811920166,63.3174743652344,39.7762222290039">Iran</option><option value="38.7896156311035,29.0612087249756,48.5759162902832,37.3809356689453">Iraq</option><option value="-10.6181116104126,51.4245567321777,-6.00255489349365,55.4365043640137">Ireland</option><option value="34.2203826904297,29.4915351867676,35.8947334289551,33.3337440490723">Israel</option><option value="6.61569356918335,35.4921913146973,18.5134468078613,47.0951995849609">Italy</option><option value="-78.3666381835938,17.7035522460938,-76.1803207397461,18.5269775390625">Jamaica</option><option value="122.938659667969,24.036470413208,153.984741210938,45.5231437683105">Japan</option><option value="-160.033142089844,-0.389006018638611,-160.004577636719,-0.368994981050491">Jarvis Island</option><option value="-169.542739868164,16.7265472412109,-169.51708984375,16.7411346435547">Johnston Atoll</option><option value="34.9579772949219,29.1850357055664,39.3012046813965,33.3712501525879">Jordan</option><option value="42.720832824707,-17.0631427764893,42.7592620849609,-17.0481777191162">Juan De Nova Island</option><option value="46.4918556213379,40.9363327026367,87.3125915527344,55.4511985778809">Kazakhstan</option><option value="33.9088554382324,-4.67804718017578,41.8990783691406,4.62933301925659">Kenya</option><option value="-162.896896362305,6.19838857650757,-162.294158935547,6.60813903808594">Kingman Reef</option><option value="46.5570602416992,28.5246105194092,48.4314765930176,30.1037006378174">Kuwait</option><option value="69.2766036987305,39.1728286743164,80.2826080322266,43.238224029541">Kyrgyzstan</option><option value="100.093055725098,13.910083770752,107.696754455566,22.5001964569092">Laos</option><option value="20.9742774963379,55.6688575744629,28.2411670684814,58.0818061828613">Latvia</option><option value="35.114875793457,33.0545616149902,36.6252174377441,34.6848564147949">Lebanon</option><option value="27.0290679931641,-30.6689643859863,29.4657611846924,-28.572057723999">Lesotho</option><option value="-11.4920835494995,4.35707759857178,-7.36511278152466,8.55179119110107">Liberia</option><option value="9.38785362243652,19.5080432891846,25.1480560302734,33.169002532959">Libya</option><option value="9.47780418395996,47.0615539550781,9.6321964263916,47.2735290527344">Liechtenstein</option><option value="20.9415264129639,53.9013023376465,26.8719444274902,56.4469184875488">Lithuania</option><option value="5.73455572128296,49.4465827941895,6.52700042724609,50.184944152832">Luxembourg</option><option value="20.4537353515625,40.8552207946777,23.0340957641602,42.3744812011719">Macedonia, The Former Yugoslav Republic of</option><option value="43.1913757324219,-25.6089534759521,50.4837837219238,-11.9454326629639">Madagascar</option><option value="32.6739463806152,-17.125,35.9168243408203,-9.36896133422852">Malawi</option><option value="98.9354934692383,0.85522198677063,119.267082214355,7.36341714859009">Malaysia</option><option value="72.684211730957,-0.692694008350372,73.706169128418,7.09836101531982">Maldives</option><option value="-12.2419233322144,10.1614255905151,4.24288845062256,25">Mali</option><option value="14.1915836334229,35.8102722167969,14.5776395797729,36.0810317993164">Malta</option><option value="165.260009765625,4.57486057281494,172.162017822266,14.6551675796509">Marshall Islands</option><option value="-61.2301216125488,14.392261505127,-60.8155097961426,14.8788194656372">Martinique</option><option value="-17.0663738250732,14.7155466079712,-4.82767486572266,27.29807472229">Mauritania</option><option value="56.5160026550293,-20.5257186889648,63.5001792907715,-10.3192548751831">Mauritius</option><option value="45.0224723815918,-13.00013256073,45.2929534912109,-12.6338367462158">Mayotte</option><option value="-118.453956604004,14.5380716323853,-86.7059326171875,32.7167625427246">Mexico</option><option value="-178.312774658203,28.1996631622314,-177.319320678711,28.4439697265625">Midway Islands</option><option value="26.6189422607422,45.4668807983398,30.1354446411133,48.4901695251465">Moldova</option><option value="7.39574956893921,43.7319717407227,7.45227813720703,43.7625045776367">Monaco</option><option value="87.7496566772461,41.5676345825195,119.92431640625,52.1542510986328">Mongolia</option><option value="-62.2425842285156,16.6710052490234,-62.1464157104492,16.8173294067383">Montserrat</option><option value="-13.168586730957,27.6621131896973,-0.991777956485748,35.9199180603027">Morocco</option><option value="30.2173194885254,-26.8686866760254,40.8444747924805,-10.4718828201294">Mozambique</option><option value="92.1892776489258,9.60036087036133,101.176254272461,28.5349731445312">Myanmar</option><option value="11.7165384292603,-28.9714317321777,25.2567005157471,-16.9598922729492">Namibia</option><option value="166.899932861328,-0.552333056926727,166.943206787109,-0.504971981048584">Nauru</option><option value="-75.027214050293,18.3967037200928,-75.0013275146484,18.4206371307373">Navassa Island</option><option value="80.056266784668,26.3567218780518,88.199333190918,30.4333915710449">Nepal</option><option value="3.36255598068237,50.7539176940918,7.22794437408447,53.5551414489746">Netherlands</option><option value="-69.1554641723633,11.9731969833374,-62.944751739502,18.0702495574951">Netherlands Antilles</option><option value="158.197631835938,-22.7146415710449,172.061386108398,-19.1038055419922">New Caledonia</option><option value="-178.627655029297,-52.6075820922852,179.102386474609,-29.2435512542725">New Zealand</option><option value="-87.6870422363281,10.7075424194336,-82.5920715332031,15.0259094238281">Nicaragua</option><option value="0.167994990944862,11.6969747543335,15.9956436157227,23.5250263214111">Niger</option><option value="2.66843199729919,4.27714395523071,14.678204536438,13.8920078277588">Nigeria</option><option value="-169.95100402832,-19.152193069458,-169.775161743164,-18.9537715911865">Niue</option><option value="167.919036865234,-29.11936378479,167.993743896484,-28.9953594207764">Norfolk Island</option><option value="124.189109802246,37.5973014831543,130.674880981445,43.0112953186035">North Korea</option><option value="144.886077880859,14.1073608398438,146.080307006836,20.5406951904297">Northern Mariana Islands</option><option value="-9.07860374450684,57.9665794372559,31.1381950378418,79.6883392333984">Norway</option><option value="52,16.6544017791748,59.8365821838379,26.3879737854004">Oman</option><option value="60.8786125183105,23.694694519043,77.8409194946289,37.0950317382812">Pakistan</option><option value="131.169219970703,3.00113892555237,134.723724365234,8.09291648864746">Palau</option><option value="-162.460922241211,5.86023092269897,-162.052642822266,5.89236116409302">Palmyra Atoll</option><option value="-83.0514450073242,7.19790697097778,-77.1768646240234,9.64443111419678">Panama</option><option value="140.842864990234,-11.6578617095947,159.47819519043,-0.877888977527618">Papua New Guinea</option><option value="111.196418762207,15.7754154205322,112.735176086426,16.9332237243652">Paracel Islands</option><option value="-62.6470794677734,-27.6087398529053,-54.2599678039551,-19.2940406799316">Paraguay</option><option value="-81.3258514404297,-18.3497295379639,-68.6792907714844,-0.0129769993945956">Peru</option><option value="116.93155670166,4.61344385147095,126.601524353027,21.1206111907959">Philippines</option><option value="-130.745101928711,-25.077522277832,-124.775924682617,-23.9178161621094">Pitcairn Islands</option><option value="14.1229991912842,49.0092506408691,24.1506671905518,54.8383636474609">Poland</option><option value="-31.2657527923584,30.1388874053955,-6.18269395828247,42.145637512207">Portugal</option><option value="-67.9395751953125,17.8830432891846,-65.2199859619141,18.5201663970947">Puerto Rico</option><option value="50.7572174072266,24.4733295440674,52.4275856018066,26.1775856018066">Qatar</option><option value="55.2190856933594,-21.3722114562988,55.8450393676758,-20.8568534851074">Reunion</option><option value="20.2643947601318,43.6273002624512,29.6910552978516,48.2652587890625">Romania</option><option value="-180,41.1888618469238,180,81.8567810058594">Russia</option><option value="28.8567924499512,-2.84067916870117,30.895959854126,-1.06239593029022">Rwanda</option><option value="-14.4212303161621,-40.3671417236328,-5.64036083221436,-7.89402198791504">Saint Helena</option><option value="-62.8675117492676,17.0953426361084,-62.5432624816895,17.4188270568848">Saint Kitts and Nevis</option><option value="-61.4592552185059,12.5301694869995,-61.1160049438477,13.3778343200684">Saint Vincent and the Grenadines</option><option value="-172.798538208008,-14.0635347366333,-171.41162109375,-13.4323930740356">Samoa</option><option value="12.4023523330688,43.8939590454102,12.5156879425049,44.0000419616699">San Marino</option><option value="6.47121953964233,-0.0140040004625916,7.46552801132202,1.70132303237915">Sao Tome and Principe</option><option value="34.4956893920898,15.6142492294312,55.6666984558105,32.1543273925781">Saudi Arabia</option><option value="-17.5352363586426,12.3072748184204,-11.3568553924561,16.6915531158447">Senegal</option><option value="46.2001495361328,-10.1937065124512,56.2753791809082,-3.71151876449585">Seychelles</option><option value="-13.3076305389404,6.92868852615356,-10.2843294143677,9.99999904632568">Sierra Leone</option><option value="103.639724731445,1.16402792930603,104.088249206543,1.4712780714035">Singapore</option><option value="16.847749710083,47.7281074523926,22.5704441070557,49.6031723022461">Slovakia</option><option value="13.3830833435059,45.4131355285645,16.5660018920898,46.8779182434082">Slovenia</option><option value="155.508605957031,-12.2918891906738,168.843521118164,-5.07830572128296">Solomon Islands</option><option value="40.9886283874512,-1.66205310821533,51.4130325317383,11.9851942062378">Somalia</option><option value="16.4597396850586,-46.978931427002,37.9976196289062,-22.1266117095947">South Africa</option><option value="-41.8118782043457,-59.4842987060547,-26.2301902770996,-53.6485786437988">South Georgia and the South Sandwich Islands</option><option value="124.611190795898,33.1061096191406,130.923233032227,38.6124496459961">South Korea</option><option value="-18.1665706634521,27.6388187408447,4.31538915634155,43.7917213439941">Spain</option><option value="114.029525756836,9.67947196960449,115.846031188965,11.1179723739624">Spratly Islands</option><option value="79.654655456543,5.91683292388916,81.8812866210938,9.83136177062988">Sri Lanka</option><option value="21.8396377563477,3.48638987541199,38.579475402832,23.1468906402588">Sudan</option><option value="-58.0863990783691,1.83114492893219,-53.9774894714355,6.00454616546631">Suriname</option><option value="10.49072265625,74.3457489013672,36.8152770996094,80.8323974609375">Svalbard</option><option value="30.7941055297852,-27.3169918060303,32.1367034912109,-25.7196464538574">Swaziland</option><option value="10.9911108016968,55.3371086120605,24.1632785797119,69.0625">Sweden</option><option value="5.95747184753418,45.8256912231445,10.4914722442627,47.8051681518555">Switzerland</option><option value="35.727222442627,32.3161888122559,42.3704643249512,37.3191413879395">Syria</option><option value="116.706657409668,20.6974983215332,122.000442504883,26.3920555114746">Taiwan</option><option value="67.3922729492188,36.6741333007812,75.1372222900391,41.0412254333496">Tajikistan</option><option value="29.3271656036377,-11.7456960678101,40.4432220458984,-0.990735948085785">Tanzania</option><option value="97.3484115600586,5.60999965667725,105.63786315918,20.4631958007812">Thailand</option><option value="-80.4992370605469,20.9160652160645,-72.7115936279297,27.232027053833">The Bahamas</option><option value="-16.825080871582,13.0642518997192,-13.8052921295166,13.8265705108643">The Gambia</option><option value="-0.145849004387856,6.104416847229,1.8066930770874,11.1389770507812">Togo</option><option value="-172.499420166016,-9.38111114501953,-171.21142578125,-8.55388736724854">Tokelau</option><option value="-176.211334228516,-22.3457183837891,-173.70246887207,-15.5629873275757">Tonga</option><option value="-61.9237747192383,10.0361042022705,-60.4895515441895,11.3343181610107">Trinidad and Tobago</option><option value="54.5148315429688,-15.8935108184814,54.5249710083008,-15.8797283172607">Tromelin Island</option><option value="7.5248327255249,30.2404174804688,11.5982780456543,37.5439186096191">Tunisia</option><option value="25.6709728240967,35.8154144287109,44.8338356018066,42.1075820922852">Turkey</option><option value="52.4414405822754,35.1410827636719,66.6843032836914,42.7955551147461">Turkmenistan</option><option value="-72.480842590332,21.1700344085693,-71.0803375244141,21.9712448120117">Turks and Caicas Islands</option><option value="176.065032958984,-9.43619441986084,179.861907958984,-5.64336061477661">Tuvalu</option><option value="29.5732517242432,-1.48405003547668,35.0360527038574,4.21442604064941">Uganda</option><option value="22.1303615570068,44.3904113769531,40.2073936462402,52.3686370849609">Ukraine</option><option value="51.5076332092285,22.634069442749,56.3750877380371,26.076416015625">United Arab Emirates</option><option value="-8.64963912963867,34.5650253295898,33.9176940917969,60.8458061218262">United Kingdom</option><option value="55.9981117248535,37.1843338012695,73.1322784423828,45.5996780395508">Uzbekistan</option><option value="166.524978637695,-20.2489452362061,170.234085083008,-13.0734434127808">Vanuatu</option><option value="-73.3540802001953,0.627002954483032,-59.8062973022461,12.2019033432007">Venezuela</option><option value="102.14958190918,8.4082498550415,109.464645385742,23.3888359069824">Vietnam</option><option value="-65.0862884521484,17.6817245483398,-64.5651779174805,18.4118766784668">Virgin Islands</option><option value="166.611892700195,19.2695255279541,166.650817871094,19.3167247772217">Wake Island</option><option value="-178.203842163086,-14.387791633606,-176.128768920898,-13.2142505645752">Wallis and Futuna</option><option value="-17.1031837463379,20.7741565704346,-8.67027568817139,27.6670207977295">Western Sahara</option><option value="41.8160514831543,12.1110820770264,54.5294761657715,19">Yemen</option><option value="18.4339809417725,41.8524208068848,23.0052738189697,46.1894454956055">Yugoslav Republic (Serbia and Montenegro)</option><option value="21.999662399292,-18.079475402832,33.7057075500488,-8.2243595123291">Zambia</option><option value="25.2371768951416,-22.4177398681641,33.0550193786621,-15.6093597412109">Zimbabwe</option></optgroup></select>';
echo '  <body onload="initialize()" onunload="GUnload()">
    <div style="width:100%;"><div  class=""><div style="position: relative;" id="desc">' . $desc . '</div><br/><div id="map_div" style="width: 472px; height: 300px"></div><br/>

'.$filter.'';
echo $zoom="<span>Zoom to :</span> - <span style='cursor: pointer;' onclick='map.setCenter(new GLatLng(39.504153, -94.928521), 5);'><u>United States</u></span> -
<span style='cursor: pointer;' onclick='map.setCenter(new GLatLng(22.877440,-101.777344), 5);'><u>Mexico</u></span> -
<span style='cursor: pointer;' onclick='map.setCenter(new GLatLng(21.943046, -51.328125), 2);'><u>Reset</u></span><br></body>";

        // $desc .= '<img src="http://gmaps-samples.googlecode.com/svn/trunk/markers/'.$marker[$i].'/blank.png" border="0" alt=""/> &nbsp; '.$vlist[$i]['answer'].'<br/>';
        $desc .= '<img src="http://labs.google.com/ridefinder/images/mm_20_' . $marker[$i] . '.png" border="0" alt=""/> &nbsp; ' . $vlist[$i]['answer'] . '<br/>';
       
        if (is_array($getresult)) {
            $zcnt = 0;

            foreach ($getresult as $for_zip_user) {
                $uzip = '';
                $uzip = $for_zip_user->zip;
                // $code = rand(600001, 600028);
                $cntcode = '';
                if (!empty($uzip)) {
                    $list = array();
                    $list = qlite_get_zip($uzip, $cntcode);
                    $list = $list->results;

                    if ($list[0]['countrycode'] != '') {
                        $zcnt++;
                        $mlatall .= "'" . $list[0]['lat'] . "',";

                        $mlongall .= "'" . $list[0]['lng'] . "',";
                        $ziparyall.="'" . $uzip . "',";
                        $colormark.="'" . $marker[$i] . "',";
                        //   $mlat .= "'".rand('30.232','72.03')."',";
                        //  $mlong .= "'".rand('56.232','103.03')."',";
                        //print_r($array);
                    }
                }
            }
        }
    }
    $mlat = "[";
    $mlong = "[";
    $zipary = "[";
    $color = "[";
    $mlat.= rtrim($mlatall, ',');
    $mlong.= rtrim($mlongall, ',');
    $zipary.=rtrim($ziparyall, ',');
    $color.=rtrim($colormark, ',');
    $mlat .= "]";
    $mlong .= "]";
    $zipary.="]";
    $color.="]";
    $inc_script .= "
                                 var lat=" . $mlat . ";
				 var lng=" . $mlong . ";
                                 var zip=" . $zipary . ";
                                 var color=" . $color . ";
		        for (var i = 0; i <lat.length; i++) {

		       var  marker=newMarker(new GLatLng(lat[i],lng[i]),zip[i],get_color(color[i]) );
                        markers.push(marker);

		          }";

    $script .= "
		<link rel='stylesheet' href='" . $gSitePath . drupal_get_path('theme', 'heardmentality') . "/css/content.css' type='text/css' />
				<script src='http://maps.google.com/maps?file=api&amp;v=2&amp;sensor=false&amp;key=" . $googlekey . "' type='text/javascript'></script>
                                <script src='http://gmaps-utility-library.googlecode.com/svn/trunk/markerclusterer/1.0/src/markerclusterer.js' type='text/javascript'></script>
                                  <script src=' http://gmaps-utility-library.googlecode.com/svn/trunk/markermanager/release/src/markermanager.js' type='text/javascript'></script>
";




    echo $script.="<script type='text/javascript' >
			  	var map ;
				 function initialize() {
    	 map = new google.maps.Map2(document.getElementById('map_div'));
		 map.setCenter(new GLatLng(34, 0), 1);
                   mgr = new MarkerManager(map);

                    var markers = [];
                 geocoder = new GClientGeocoder();
                        function createMarker(latlng, number,iconRed) {
                                // Set up our GMarkerOptions object
                markerOptions = { icon:iconRed };
                      var marker = new GMarker(latlng,markerOptions);
                      marker.value = number;
                      GEvent.addListener(marker,\"click\", function() {
                        var myHtml =number;
                        map.openInfoWindowHtml(latlng, myHtml);
                      });
                      return marker;
                  }
		//map.setCenter(new GLatLng(13.06556,80.26722), 5);
		  map.addControl(new GLargeMapControl());
    //map.addControl(new GMapTypeControl());
      	" . $inc_script . "
                  
                  
	 var markerCluster = new MarkerClusterer(map, markers);
map. disableInfoWindow ();

}

	function zoomto(val){
        var list=new Array();
 list=val.split(',');
 var lat=(parseInt(list[1])+parseInt(list[3]))/2;
 var lng=(parseInt(list[0])+parseInt(list[2]))/2;
map.setCenter(new GLatLng(Math.round(lat),Math.round(lng) ), 5);
}
		function get_color(type){

      var iconRed = new GIcon();
          iconRed.shadow = 'http://labs.google.com/ridefinder/images/mm_20_shadow.png';
    iconRed.iconSize = new GSize(12, 20);
    iconRed.shadowSize = new GSize(22, 20);
    iconRed.iconAnchor = new GPoint(6, 20);
    iconRed.infoWindowAnchor = new GPoint(5, 1);
	
	 iconRed.image = 'http://labs.google.com/ridefinder/images/mm_20_'+type+'.png';
		return iconRed;
		}
		function newMarker(markerLocation, markerId,icon) {

	//var markering=new GMarker(markerLocation, {title:'Zip['+markerId+']',icon:icon});
        var markering=new GMarker(markerLocation, {icon:icon});
    GEvent.addListener(markering, 'click', function() {
		markering.openInfoWindowHtml('<p>Zip['+markerId+']</p>');
	});
	return markering;
}

				</script>
					";

    echo '</div>';
}

function qlite_get_zip($code = '', $ccode = '') {

    $query = array('postalcode' => $code, 'maxrows' => 1);
    $result = geonames_query('postalcodesearch', $query);

    return $result;
}

function answer_details($qid = '', $aid = '', $action = '', $date = '') {
    switch ($action) {
        case 'percent':
            if ($_REQUEST['fopt']) {
                $opt = filter_opt($_REQUEST);

                $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $aid . "' $opt ";
                $answer = ExecuteQuery($query, "norows");
            } else {

                $query = "select * from {possible_answer_vote} where qid='" . $qid . "' and panswer_id='" . $aid . "' ";
                $answer = ExecuteQuery($query, "norows");
            }


            return $answer;
            break;
        case 'timeline':
            $query = "select count(*) as cnt from possible_answer_vote where qid='" . $qid . "' and panswer_id='" . $aid . "'AND date(vote_pdate)<='" . $date . "' ";
            $answer = ExecuteQuery($query, "select");

            return $answer ? $answer[0]['cnt'] : 'null';

            break;
    }
}

function filter_opt($array = '') {
    $code = '';
    $filter = '';
    $filter = (!empty($array['dochg'])) ? $array['dochg'] : '';
    switch ($filter) {
        case 'gender':
            $code = " AND gender='" . $array['fopt'] . "'";
            break;
        case 'age':
            //$code = "age>=18 AND age<=50 ";
            break;
        case 'religion':
            $code = " AND religion='" . $array['fopt'] . "'";
            break;
        case 'slant':
            $code = " AND slant='" . $array['fopt'] . "'";
            break;
        default:
            break;
    }
    return $code;
}

function answer_vote() {

    global $gSitePath, $user, $gDocPath, $base_root;


    $list_length = db_query("select * from {suggest_answer_vote} where answer_id='" . $_REQUEST['suggest'] . "' and uid='" . $user->uid . "'  ");

    $fetvote = db_fetch_object($list_length);

    $numr = db_result(db_query("SELECT COUNT(*) from {suggest_answer_vote} where answer_id='" . $_REQUEST['suggest'] . "' and uid='" . $user->uid . "' "));

    $list_own_answer = db_query("select * from {suggest_answer} where said='" . $_REQUEST['suggest'] . "'   ");
    $userownid = db_fetch_object($list_own_answer);
    if ($_REQUEST['suggest'] != '') {
        if ($userownid->uid != $user->uid) {
            if ($numr == 0) {

                $calvote = db_result(db_query("SELECT COUNT(*) from {suggest_answer_vote} where answer_id='" . $_REQUEST['suggest'] . "' "));

                if ($calvote == 0) {
                    $votepoint = '1';
                } else {
                    $votepoint = $userownid->vote + 1;
                }
                $answerquery = "insert into suggest_answer_vote(qid,uid,answer_id,vote_date) values ('" . $_REQUEST['qaid'] . "','" . $user->uid . "','" . $_REQUEST['suggest'] . "','" . date('Y-m-d') . "')";
                db_query($answerquery);


                $updatevotesug = "update  suggest_answer set vote='$votepoint' where said='" . $_REQUEST['suggest'] . "'";
                db_query($updatevotesug);
                send_votenotify($_REQUEST['qaid']);
                echo '<div class="messages success">Thanks For Voting ! </div>';
            } else {
                echo '<div class="messages error"> You Have Already Voted This Answer ! </div>';
            }
        } else {

            echo '<div class="messages error"> You Cannot Vote Your Answer! </div>';
        }
    } else {
        echo '<div class="messages error"> Select Suggest Answer! </div>';
    }
}

function send_votenotify($qid='') {///vijay important comented
    global $gSitePath, $user, $gDocPath, $base_root;
    $qry = "insert into notification (uid,follower_action,is_question,new_answer,node_id) values('" . $user->uid . "','1','1','1'," . $qid . "' ) ";

    //  $insert_notify = db_query($qry);
    ////////////mail notication for user follwers to me//////////////////////////////////////
    ///vijay coment start here////////////
    /*  $qdetails = load_question($qid);


      $sel_listf = "select * from follower  where follower_id='" . $user->uid . "'   ";
      $rs_followerf = db_query($sel_listf);
      while ($follower_resultfuser = db_fetch_object($rs_followerf)) {

      $sellist = "select * from users where uid='" . $follower_resultfuser->uid . "'";
      $res_users = db_query($sellist);
      $usert = db_fetch_object($res_users);
      $to = $usert->mail;

      if ($usert->notify_itype == 1) {

      $insert_notify = db_query("insert into notification (uid,follower_action,is_question,new_answer,node_id) values('" . $follower_resultfuser->uid . "','1','1','1'," . $qid . "' ) ");
      }
      if ($usert->notify_etype == 1) {

      ///////////email for following ///////////////

      $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='5'";
      $rs_mgmt = db_query($sel_user_cmt);
      $list_content = db_fetch_object($rs_mgmt);
      $subject_proj = $list_content->subject;
      $contentm = str_replace("#uname#", $usert->name, $list_content->content);
      $contentm = str_replace("#anothername#", $user->name, $contentm);


      $contentm = str_replace("#question#", rtrim($qdetails['question'], '?') . '?', $contentm);
      $contentm = str_replace("#link#", $gSitePath . $qdetails['url'], $contentm);
      $contentm = str_replace("#content#", "voted for the below question. Kindly have a review", $contentm);



      $mail_success = htmlmail_function($to, $subject_proj, $contentm, '');
      }

      } */
    hm_mails($qid, '', 'vote_answer');
}

function send_forumnotify($nid='', $qid='') { //vijay important comented
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

    $insert_notify = db_query("insert into notification (uid,follower_action,is_wave,node_id) values('" . $user->uid . "','1','1','" . $nid . "' ) ");


    /* $qdetails = load_question($qid);
      $sel_listf = "select * from follower  where follower_id='" . $user->uid . "'   ";
      $rs_followerf = db_query($sel_listf);

      $sel_wave = db_fetch_object(db_query("select * from {forum_wave} where fid='$nid'"));

      while ($follower_resultfuser = db_fetch_object($rs_followerf)) {

      $sellist = "select * from users where uid='" . $follower_resultfuser->uid . "'";
      $res_users = db_query($sellist);
      $usert = db_fetch_object($res_users);
      $to = $usert->mail;
      if ($usert->notify_itype == 1) {

      $insert_notify = db_query("insert into notification (uid,follower_action,is_wave,node_id) values('" . $follower_resultfuser->uid . "','1','1','" . $nid . "' ) ");
      }
      if ($usert->notify_etype == 1) {

      ///////////email for following ///////////////

      $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='5'";
      $rs_mgmt = db_query($sel_user_cmt);
      $list_content = db_fetch_object($rs_mgmt);
      $subject_proj = $list_content->subject;
      $contentm = str_replace("#uname#", $usert->name, $list_content->content);
      $contentm = str_replace("#anothername#", $user->name, $contentm);

      // print_r($qdetails);
      $contentm = str_replace("#question#", rtrim($qdetails['question'], '?') . '?', $contentm);
      $contentm = str_replace("#link#", $gSitePath . $qdetails['url'], $contentm);
      $contentm = str_replace("#content#", "created a Forum Topic [" . $sel_wave->title . "] for the below question. Kindly have a review", $contentm);
      $mail_success = htmlmail_function($to, $subject_proj, $contentm, '');




      }
      } */
    hm_mails($qid, $nid, 'add_forum');
}

function qusetion_info() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $vSql = "select * from {question} where status='1' and qid=$qid ";
    $rlist = db_query($vSql);
    $oListquest = db_fetch_object($rlist);
    $infooutput = '<strong>' . $oListquest->question . '</strong>';
    $infooutput .= '<p>' . $oListquest->context . '</p>';


    echo $infooutput;
}

function percent_info() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

    $vSqls = "select * from {vote_percent} where id='1' ";
    $rlistb = db_query($vSqls);
    $oListquestb = db_fetch_object($rlistb);

    $infooutput = '<form id="answer" name="answer" method="post" action="' . $gSitePath . 'admin/qlite/percentsave"  > <div class="cmt_list">
		<div class="lft_view">
		<p> Percentage of vote </p>
		<p><input type="text" name="percentage" value="' . $oListquestb->percent . '"/>% of total votes</p>
		<p><input type="submit" name="submitpercent" value="Save"/></p>	</div></div>	';

    return $infooutput;
}

function percent_save() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

    $updateper = "update  vote_percent set percent='" . $_REQUEST['percentage'] . "' where id='1'";
    db_query($updateper);

    drupal_goto("admin/qlite/percentage");
}

function retag() {
    // print_r($_REQUEST);
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $uid = $user->uid;

    if (isset($_REQUEST['tagsubmit'])) {


        //reset tags
        db_query("DELETE FROM {qtag} where  qid='" . $qid . "'");

        extract($_REQUEST);

        $qtag = explode(',', $q_tag);

        //its in quset_lite.module
        $tru = process_tags($qtag, $qid, 1);

        if ($tru) {
            //badges
            $chkbadge = db_result(db_query("select (*) from {user_badges} where uid='$uid' and bid='28'"));
            if ($chkbadge < 1) {

                db_query("insert into {user_badges} set bid='28',uid='$uid',qid='" . $qid . "'");
            }

            drupal_set_message($message = 'Thank you Tags are updated', $type = 'success');
            echo '<div class="success">Thank you Tags are updated</div>';
        }


        exit;
    }

    $display .= '
					<link rel="stylesheet" href="' . $gSitePath . path_to_theme() . '/css/css.css" type="text/css" />
				<script type="text/javascript" src="' . $gSitePath . drupal_get_path('theme', 'heardmentality') . '/scripts/mootools-1.2-core.js"></script>
				<script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'quest_lite') . '/scripts/tagging.js"></script>
				<link rel="stylesheet" href="' . $gSitePath . drupal_get_path('module', 'tagging') . '/tagging.css" type="text/css" />
				<link rel="stylesheet" href="' . $gSitePath . drupal_get_path('module', 'quest_lite') . '/css/Autocompleter.css" type="text/css" media="screen" />
			<script>
			var mpath=\'' . $gSitePath . '\';
		
			</script>';

    $query = " SELECT t.tag FROM {qtag} as qt left join {tagging} as t on t.tid=qt.tag_id WHERE qt.qid='" . $qid . "' ";
    $result = ExecuteQuery($query, "select");
    echo $display .= edit_tagging($result);
}

function edit_tagging($tag = '') {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

    $content = '';
    $tagged = '';
    if (!empty($tag)) {


        foreach ($tag as $list) {
            if (!empty($list)) {
                $tagged .= '<div id="tagset" class="tagging-tag" onclick="tag_delq(this);return false;">' . $list['tag'] . '</div>';
            }
        }
    }

    $randomtag = popular_tag();


    $tag = implode(',', $tag);
    $content .= '
		<div class="facttop">RETAG THIS QUESTION</div>
		<div id="log_res"><!-- spanner --></div>
	<div id="err"></div>
	<span class="clr"><!-- spanner --></span> <div id="tagging-widget-container">
	<form id="retagform" action="' . url($_GET['q'], array('absolute' => true)) . '" class="" method="post" >
            <fieldset>
                <legend>
                    Re Tag
                </legend>
				
                <div id="tagdiv" class="tagging-curtags-wrapper tagging-curtags-wrapper-1">
                    <label>
                        Assigned Tags:
                    </label>
                    ' . $tagged . '
                </div>
                <div class="form-item" id="tagging-widget-input-1-wrapper">
                    <div class="field-prefix">
                        <div class="taggin-widget-input-wrapper">
                            <input maxlength="20" autocomplete="off" tabindex="20" name="taxonomy[tags][1]" id="tagging-widget-input-1" value="" onkeyup="suggest(this.value);" onblur="fill(this.value);" class="form-text form-autocomplete tagging-widget-input tagging-widget-input-1" type="text"/>
							<div class="field-suffix">
							<a class="tagging-button-container" href="#" title="Add">
							<span class="tagging-button tagging-button-1"></span></a>
                            <div class="suggestionsBox" id="suggestions" style="visibility:hidden;">
                                <img src="' . $gSitePath . drupal_get_path('module', 'quest_lite') . '/images/arrow.png" style="position: relative; top: -12px; left: 30px;" alt="upArrow" />
                                <div class="suggestionList" id= "suggestionsList">
                                </div>
								</div>
                           </div> 
						   </div>
                            <input  name="taxonomy[tags][1]" id="edit-taxonomy-tags-1" value="" class="tagging-widget-target-1" type="hidden"/>
							<input name="q_tag" type="hidden" id="q_tag" value="' . $tag . '"/>
                     </div>
                    <div class="description">
                        Add New Tag
                    </div>
                    </div>
                    <input class="autocomplete" id="tagging-widget-input-1-autocomplete" value="" disabled="disabled" type="hidden"/>
                    <br/>
                    <div id="sug_div" class="tagging-suggestions-wrapper tagging-suggestions-wrapper-1">
                        <label>
                            Suggestions:
                        </label>
                        ' . $randomtag . '
                       
                    </div>
					<div ><input type="submit" name="tagsubmit" value="Retag" /> &nbsp; <input type="button" value="Cancel" class="nyroModalClose" onclick="window.top.location.reload();" /></div>
               
            </fieldset>
			</form>
        </div>';


    return $content;
}

function qfull_ajax() {
    $action = $_REQUEST['action'];

    switch ($action) {
        case 'tag':
            $q = clean_url($_REQUEST["queryString"]);

            if (!$q)
                return;
            $taglist = array();
            $items = array();
            $query = "SELECT * FROM tagging WHERE tag LIKE ('$q%') LIMIT 0 , 15 ";
            $result = ExecuteQuery($query, "select");
            $vResult = db_query($query);
            //$oBj= db_fetch_object(db_query($query));
            //print_r($oBj);
            foreach ($result as $single) {
                array_push($taglist, $single['tag']);
            }

            $taglist = array_filter($taglist);

            $taglist = array_unique($taglist);
            $taglist = implode(',', $taglist);
            $taglist = explode(',', $taglist);
            $taglist = array_filter($taglist);
            $items = array_unique($taglist);

            //print_r($items);
            $list = "<ul>";
            if (!empty($items)) {
                //print_r($items);
                foreach ($items as $value) {
                    //     if (strpos(strtolower($value), $q) !== false) {
                    $list .= '<li onclick=fill("' . $value . '")>' . $value . '</li>';
                    //  }
                }
            } else {

                $list .= '<li>No Result</li>';
            }
            echo $list .= "</ul>";

            break;
        case 'resource':

            $uid = clean_url($_REQUEST["uid"]);
            $rid = clean_url($_REQUEST["rid"]);
            $rtype = clean_url($_REQUEST["rtype"]);
            $query = "SELECT count(rid) FROM resource_like WHERE rid=$rid AND uid=$uid AND rtype=$rtype";
            $result = ExecuteQuery($query, "select");
            if (isset($result[0]) && $result[0][0] == 1) {
                $query1 = "SELECT count(rid) FROM resource_like WHERE rid=$rid ";
                $result1 = ExecuteQuery($query1, "select");
                $list .= $result1[0][0] . '&nbsp;&nbsp;';
                $list .= '<span class="err-message">Already Liked</span>';
            } else {
                $query = "INSERT INTO {resource_like} set rid='$rid',uid='$uid',rtype='$rtype',like_yes='1' ";
                $result = ExecuteQuery($query, "insert");
                $query1 = "SELECT count(rid) FROM resource_like WHERE rid=$rid ";
                $result1 = ExecuteQuery($query1, "select");
                $list .= '&nbsp;' . $result1[0][0] . '&nbsp;&nbsp;';
                $list .= '<span class="succ-message">Thanks For Liked</span>';
            }

            echo $list;
            break;
        case 'zipcity':
            $code = $_REQUEST['code'];
            $query = array('postalcode' => $code, 'maxrows' => 1);
            $result = geonames_query('postalcodesearch', $query);
            $city = $result->results;

            $query = array('country' => $city[0]['countrycode'], 'maxrows' => 1);
            $result1 = geonames_query('countryinfo', $query);
            $cnt = $result1->results;
            //   print_r($cnt);
            //print_r($city);
            echo '<b>Country :</b>' . $cnt[0]['countryname'];
            echo '<br/><b>Province/State :</b>' . $city[0]['adminname1'];
            echo '<br/><b>City :</b>' . $city[0]['adminname2'];
            echo '<input type="hidden" name="country" value="' . $cnt[0]['countryname'] . '">
                    <input type="hidden" name="state" value="' . $city[0]['adminname1'] . '">
				<input type="hidden" name="city" value="' . $city[0]['adminname2'] . '">
				';
            break;
        case 'filter':
            $type = $_REQUEST['type'];
            $output = '';
            $output .= '&nbsp;';
            switch ($type) {
                case 'gender':
                    echo $output .= "<select name='fopt' id='fopt'> <option value='1'>Male</option><option value='2'>Female</option></select>";
                    break;
                case 'age':
                    echo $output .= "<select name='fopt' id='fopt'> <option value='18-30'>18-30</option><option value='30-50'>30-50</option><option value='above'>Above 50</option></select>";
                    break;
                case 'religion':
                    echo $output .= '<select class="form-text" id="fopt" name="fopt"><option value="Christian">Christian (Cath or Prod)</option><option value="Muslim">Muslim (Suni Shiite)</option><option value="Jewish">Jewish</option><option value="Hindu"> Hindu</option><option value="Buddhist">Buddhist</option><option value="Other">Other</option></select>';
                    break;
                case 'ethnicity':
                    echo $output .= '<select class="form-text" id="fopt" name="fopt"><option value="Caucasian">Caucasian</option><option value="Black">Black</option><option value="Asian">Asian</option> <option value="Indian">Indian</option> <option value="Semetic">Semetic</option><option value="Latin">Latin</option> <option value="Aborigines">Aborigines</option>  </select>';
                    break;
                case 'slant':
                    echo $output .= '<select class="form-text" id="fopt" name="fopt"><option  value="Left">Left</option><option value="Right">Right </option> <option value="Center">Center </option>  </select>';
                default:
                    break;
            }

            break;
        case 'graph':

            $str = substr($_REQUEST['date'], '0', '10');
            $date = date('d-m-Y', $str);
            $qid = $_REQUEST['qid'];
            $query = "select * from {resource} where date(posted_date)='$date' AND qid='$qid'";
            $set = ExecuteQuery($query, "select");

            $result.="<div> <b>Resources For Date :" . date('d M,Y', $str) . "</b></div><hr/><br/><ul>";
            if (!empty($set)) {
                foreach ($set as $list) {

                    switch ($list['rtype']) {

                        case '1':
                            $inc.="<li><a href=\"" . $list['ncontent'] . "\" target=\"_blank\">You Tube Video</a></li>";
                            break;
                        case '2':

                            if (!empty($list['membed']))
                                $inc.="<li><a href=\"" . $list['membed'] . "\" target=\"_blank\">You Tube Video</a></li>";
                            elseif (!empty($list['document']))
                                $inc.="<li><a href=\"" . $list['document'] . "\" target=\"_blank\">Document</a></li>";

                            break;
                        case '3':
                            $inc.="<li><a href=\"" . $list['facts'] . "\">" . $list['facts'] . "</a></li>";
                            break;
                    }
                }
            } else {

                $inc = "<b>No Resource for this Date</b>";
            }
            echo $result = $result . $inc . "</ul>";

            break;
        default:
            break;
    }
}

function insertviews($qid = '') {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    //$qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    if ($user->uid != '') {
        $ulid = $user->uid;
        $ipid = $_SERVER['REMOTE_ADDR'];
        //echo "SELECT COUNT(*) FROM {qviews} where  uid='$user->uid'   and qid='".$qid."' and view_date='".date("Y-m-d")."' ";
        $countret = db_result(db_query("SELECT COUNT(*) FROM {qviews} where  uid='$user->uid'   and qid='" . $qid . "' and view_date='" . date("Y-m-d") . "' "));
    } else {

        $ulid = 0;
        $ipid = $_SERVER['REMOTE_ADDR'];

        $countret = db_result(db_query("SELECT COUNT(*) FROM {qviews} where ip='$ipid'  and qid='" . $qid . "' and view_date='" . date("Y-m-d") . "'"));
    }
    //echo  $countret;
    if ($countret == 0) {

        db_query("INSERT INTO {qviews} (ip,uid,qid,view_date) VALUES ('$ipid',$ulid,$qid,'" . date("Y-m-d") . "')");
    }
}

/////////////popular qusetion ////////// notable question /////////// Famous Question  /////////////////////
function popquest() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    $vSql = "select *,q.uid as uid from {question} as q left join {user_profile} as u on q.uid=u.uid where  q.qid='" . $qid . "'  ";
    $rlist = db_query($vSql);
    $oListquest = db_fetch_object($rlist);
    //echo $oListquest->uid;
    //echo "SELECT COUNT(*) FROM {qviews} where qid='".$qid."' ";
    $popcnt = db_result(db_query("SELECT COUNT(*) FROM {qviews} where qid='" . $qid . "' "));
    //  echo  $popcnt;
    if ($popcnt == 1) {
        $stucntr = db_result(db_query("SELECT COUNT(*) FROM {user_badges} where  uid='" . $oListquest->uid . "' and qid='" . $qid . "'  and bid='30'"));
        if ($stucntr == 0) {
            db_query("INSERT INTO {user_badges} (bid, uid,qid) VALUES ('30','" . $oListquest->uid . "','" . $qid . "') ");
        }
    }
    ////////////////////notable question//////////////
    if ($popcnt == 3) {
        $stucntr = db_result(db_query("SELECT COUNT(*) FROM {user_badges} where  uid='" . $oListquest->uid . "' and qid='" . $qid . "'  and bid='27'"));
        if ($stucntr == 0) {
            db_query("INSERT INTO {user_badges} (bid, uid,qid) VALUES ('27','" . $oListquest->uid . "','" . $qid . "') ");
        }
    }

    /////////////////famous question ////////////////


    if ($popcnt == 5) {
        $stucntr = db_result(db_query("SELECT COUNT(*) FROM {user_badges} where  uid='" . $oListquest->uid . "' and qid='" . $qid . "'  and bid='13'"));
        if ($stucntr == 0) {
            db_query("INSERT INTO {user_badges} (bid, uid,qid) VALUES ('13','" . $oListquest->uid . "','" . $qid . "') ");
        }
    }
}

?>
