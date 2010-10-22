<?php

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
    drupal_add_css(drupal_get_path('module', 'quest_lite') . '/css/wave.css');
    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/wave.js');
    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/like.js');
    // drupal_add_js(drupal_get_path('module', 'forum').'/scripts/forum.js');
    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/subtab.js');
    drupal_add_css(drupal_get_path('theme', 'newtheme') . '/rotate_files/ui.css');
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

    $vSql = "select *,q.uid as uid from {question} as q left join {user_profile} as u on q.uid=u.uid where  q.qid='" . $qid . "'  ";
    $rlist = db_query($vSql);
    $oListquest = db_fetch_object($rlist);

    //question privacy check
    if (!$oListquest->status) {

        if ($user->uid != $oListquest->uid || $oListquest->uid != 1) {

            drupal_set_message('Sorry Question is inactive for user access!', 'error');
            drupal_goto();
        }
    }


    privacy_chk($oListquest->uid, $oListquest->question_privacy, $oListquest->share);
    ////question privacy check ends

    $list_lengthan = db_query("select * from {possible_answer_vote} where qid='" . $qid . "' and uid='" . $user->uid . "'  ");
    $numran = db_result(db_query("SELECT COUNT(*) from {possible_answer_vote} where qid='" . $qid . "' and uid='" . $user->uid . "'"));
    $answer_id = db_fetch_object($list_lengthan);
    $stringfunct = strlen($oListquest->question);
    $voutput = '<script type="text/javascript">
		var qid="' . $qid . '";
		var spath="' . $gSitePath . '";
		function showdetails(ids)
		{	
	
		loaddetails(\'' . $gSitePath . 'qlite/Details/\'+ids,\'Question Information\');
		}
		
		</script>';
    //echo $stringfunct;
    if (drupal_is_front_page ()) {
        $qlink = 'QUESTION OF THE DAY';
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
              <h2 style="'.drupal_link_color($user->uid,$oListquest->qid).'">' . rtrim($oListquest->question, "?") . '? </h2>
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
        $query="select vote_pid from {possible_answer_vote} where qid='$qid' AND uid='".$user->uid."'";
        $voteid=db_result(db_query($query));
     $submitbutt = ' <p><input type="submit" name="change" id="change" value="Change" /><input type="hidden" name="vote_id" value="'.$voteid.'"/></p>';
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
    }*/
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
    $x = 0;
    foreach ($list as $fcnt) {

        $x = $x + $fcnt['wcnt'];
    }


    $voutput .= $submitbutt . '
                  <div >
                <ul>
                  <li><a href="#Forum" onclick=""  title="Bookmark">' . $x . ' comments</a></li>
                  <li>|</li>
                  <li><a href="#Resources" onclick=""  title="Invite">' . $numres . ' Resources</a></li>
                  </ul>
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
             <img ALIGN=ABSMIDDLE title="take the site tour" alt="take the site tour" src="'.$gSitePath.path_to_theme().'/images/sm3.jpg"/>&nbsp;
              <img ALIGN=ABSMIDDLE title="take the site tour" alt="take the site tour" src="'.$gSitePath.path_to_theme().'/images/sm4.jpg"/>&nbsp;
                  <img ALIGN=ABSMIDDLE title="take the site tour" alt="take the site tour" src="'.$gSitePath.path_to_theme().'/images/sm5.jpg"/>&nbsp;
                    Share</a>                 
             </div>
             
			  <div class="share2">
            <a title="Invite" onclick="formsubmittype(2,' . $qid . ');" href="javascript:void(0);" class="share-link"> Invite</a>
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
		
		';

//////////////vijay multilevel menu
     $voteqry = "SELECT * FROM possible_answer_vote where qid='" .$qid . "'";
    $votelist = db_query($voteqry);
    $fetvote = db_fetch_object($votelist);
   
    if ($numran!= 0) {
        
    
    $voutput .= '<div class="clr"></div>
	<div id="rotate">
        <br/>
              <ul id="maintabs" class="mytabs" >
             <li class="current"><a href="' . $gSitePath . '/qlite/panel/' . $qid . '" title="Report"><span>Reporting</span></a></li>
                <li class=""><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Forum" title="Forum"><span>Forum</span></a></li>
                <li class=""><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Resources" title="Resources"><span>Resources</span></a></li>
				  <li class=""><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Gurus" title="Gurus"><span>Pundits</span></a></li>
				  <li class=""><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Info" title="Info"><span>Info</span></a></li>
				  
              </ul>
              <div class="mytabs-container" id="tabcontent">
            Loading. Please Wait...
        </div>
           </div>';
    }
    else
    {
           
        $voutput .= '<div class="clr"></div>
	<div id="rotate">
        <br/>
              <ul id="maintabs" class="mytabs" >
              <li class="current"><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Info" title="Info"><span>Info</span></a></li>
               <li><a href="javascript:void(0);return false;" onClick="alert(\'Please vote the above question\');return false;"><span >Reporting</span></a></li>
                <li class=""><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Forum" title="Forum"><span>Forum</span></a></li>
                <li class=""><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Resources" title="Resources"><span>Resources</span></a></li>
		<li class=""><a href="' . $gSitePath . '/qlite/panel/' . $qid . '?type=Gurus" title="Gurus"><span>Pundits</span></a></li>
              </ul>
              <div class="mytabs-container" id="tabcontent">
            Loading. Please Wait...
        </div>
           </div>';

    }
    
    // cron job in qlite module
   // cal_active_rate();
   if($_REQUEST['ajax']==1){
         echo $voutput;
   }
   else{
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
    if ($owner == $user->uid) {

        return true;
    }

    switch ($qp) {
        case 1:

            if (empty($user)) {
                drupal_set_message($message = 'Sorry Please login to post your answers!', $type = 'error');
                drupal_goto();
            } else {

            }

            break;

        case 2:
            //check followers
            $query = "(select count(*) as yea from {follower} where follower_id='$user->uid' and uid='$owner') union(select count(*) as yea from {follower} where uid='$user->uid' and follower_id='$owner')  ";
            $cnt = ExecuteQuery($query, "select");

            if ($cnt[0][yea] || $cnt[1][yea]) {

            } else {
                drupal_set_message($message = 'Sorry, Only Followers and Followees to post answers!', $type = 'error');
                drupal_goto();
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
                drupal_goto();
            }
            break;
        case 3:
            drupal_set_message($message = 'Sorry, Question is blocked for public by owner!', $type = 'error');
            drupal_goto();
            break;
        case 1:
        default:
            break;
    }
}

function qlite_save() {

    global $gSitePath, $user, $gDocPath, $base_root;
    $mid = $_REQUEST['mid'];
   // print_r($_REQUEST);
   // exit;
    $voutput = '';
    $vquest = "select * from {possible_answer} where paid='" . $_REQUEST['answer'] . "'  ";
    $rquest = db_query($vquest);
    $olistquest = db_fetch_object($rquest);

    if (($_REQUEST['answer'] != '')&&(isset($_REQUEST['save']))) {





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


            $notify_insqry = "insert into notification(uid,is_answer,node_id)values('".$user->uid."','1','".$mid."')";
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




    }elseif (($_REQUEST['answer_al'] != '')&&(isset($_REQUEST['change']))) {
        $arr = array_keys($_REQUEST['answer_al']);
         $a = $arr['0'];
        $poss_ans = $_REQUEST['answer_al'][$a];
     $vInsQuery = "update {possible_answer_vote} set qid='".$mid."',panswer_id='".$poss_ans."',vote_pdate=now() where vote_pid='".$_REQUEST['vote_id']."' AND uid='" . $user->uid . "'";
     
            db_query($vInsQuery);
            drupal_set_message(t('Thank you,Your Answer has been changed successfully!'), $type = 'success');
            send_votenotify($mid);

    }

    if (($_REQUEST['answer_a2'] != '')&&(isset($_REQUEST['change']))) {
        //$arr = array_keys($_REQUEST['answer_al']);
         //$a = $arr['0'];
        //$poss_ans = $_REQUEST['answer_al'][$a];
     $vInsQuery = "update {possible_answer_vote} set qid='".$mid."',panswer_id='".$_REQUEST['answer_a2']."',vote_pdate=now() where vote_pid='".$_REQUEST['vote_id']."' AND uid='" . $user->uid . "'";

            db_query($vInsQuery);
            drupal_set_message(t('Thank you,Your Answer has been changed successfully!'), $type = 'success');
            send_votenotify($mid);

    }




    ////////////question search vote added start here
    if (($_REQUEST['answer_al'] != '')&&(isset($_REQUEST['save']))) {
        $arr = array_keys($_REQUEST['answer_al']);
         $a = $arr['0'];
        $poss_ans = $_REQUEST['answer_al'][$a];


     $numr = db_result(db_query("SELECT COUNT(*) from {possible_answer_vote} where qid='" . $mid . "' and uid='" . $user->uid . "'"));
        if ($numr == 0) {

            $calvotep = db_result(db_query("SELECT COUNT(*) from {possible_answer_vote} where panswer_id='" .$poss_ans. "' "));
            if ($calvotep == 0) {
                $votepointp = '1';
            } else {
                $votepointp = $olistquest->vote + 1;
            }

                 $vInsQuery = "insert into possible_answer_vote(qid,uid,panswer_id,vote_pdate) values ('" . $mid . "', '" . $user->uid . "','" .$poss_ans. "','" . date('Y-m-d h:i:s') . "')";
            db_query($vInsQuery);


            $notify_insqry = "insert into notification(uid,is_answer,node_id)values('".$user->uid."','1','".$mid."')";
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
            $updatevoteposs = "update  possible_answer set vote='$votepointp' where paid='" .$poss_ans. "'";
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
    $resources = '<link rel="stylesheet" href="' . $gSitePath . 'sites/all/modules/quest_lite/css/answer.css" type="text/css" />
		<script type="text/javascript" src="' . $gSitePath . drupal_get_path('theme', 'heardmentality') . '/scripts/mootools-1.2-core.js"></script>
	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('theme', 'heardmentality') . '/scripts/mootools-1.2-more.js"></script>
	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'quest_lite') . '/scripts/add_resource.js"></script>
	<link rel="stylesheet" href="' . $gSitePath . path_to_theme() . '/css/css.css" type="text/css" />
	';
    $resources .= '<script type="text/javascript">
	window.addEvent(\'domready\', function() {
	
	if (!window.demo_path) window.demo_path = \'\';
	var demo_path = window.demo_path;
	
	$(\'myForm\').addEvent(\'submit\', function(e) {
	
	
	e.stop();
	 var cat1 = $(\'rtype\').value;
		var nlink = $(\'nlink\').value;
		var mtype = $(\'mtype\').value;
		var membed = $(\'membed\').value;
		var docpath = $(\'docpath\').value;
		var flink = $(\'flink\').value;
		var err = \'\';
	    var tomatch=/http:\/\/[A-Za-z0-9\.-]{3,}\.[A-Za-z]{3}/;
		 if (cat1==0) 
        err += \'<li>Please Select Type !</li>\';
		 if (cat1==1) 
		 {
		
		if (!tomatch.test(nlink))
		 err += \'<li>Please Enter Link </li>\';		
	
		 }
		if (cat1==2) 
		 {
		  if (mtype==0) 
        err += \'<li>Please Select Media Type !</li>\';
		
		if (mtype==1)
		{
		 
		if (!tomatch.test(membed))
		 err += \'<li>Please Enter YouTube Link </li>\';		
		}
		else
		{
		 if (docpath.trim().length < 1) 
        err += \'<li>Please Select Document !</li>\';
		}
		}
		 if (cat1==3) 
		 {
	
		 if (!tomatch.test(flink))
		 err += \'<li>Please Enter  Fact Link</li>\';		
	
		 }
		 if (err.trim().length > 1) {
        var el = $(\'err\');
        el.setStyle(\'background-color\', \'#eeeeee\');
        el.setStyle(\'height\', \'auto\');
        el.setStyle(\'color\', \'red\');
        el.setStyle(\'border\', \'3px solid #dd97a1\');
        el.setStyle(\'list-style\', \'none\');
        
        el.setStyle(\'display\', \'block\');
        el.set(\'html\', err);
        el.highlight("#EBCC22");
          return false;   
    }		
	var log = $(\'log_res\').empty().addClass(\'ajax-loading\');
	
	this.set(\'send\', {onComplete: function(response) { 
	log.removeClass(\'ajax-loading\');
	log.set(\'html\', response);
	if(response!=\'\')
	{
	
	MochaUI.closeAll();
	}
	}});
	
	this.send();
	
	});
	});
	
	
	
	</script>
	';

    $resources .= '<div id="log">
	<div class="facttop2">ADD RESOURCES</div>
	<div id="log_res"><!-- spanner --></div>
	</div><div id="err">' . $list_err . '</div><br/>
	<span class="clr"><!-- spanner --></span>';
    $resources .= '<form id="myForm" name="myForm"  method="post" action="' . $gSitePath . 'qlite/ajaxadd" enctype="multipart/form-data" ><input type="hidden" name="qaid" value="' . $qid . '"/>
	
	<br/><p class="float_lft"> Type	</p><p class="float_lft"> <select name="rtype" class="textfieldm" id="rtype" >
	<option value="0">Select </option>
	<option value="1">News </option>
	<option value="2">Multimedia </option>
	<option value="3">Facts </option>
	</select>  
	</p>
    <br class="clr"/>
	<div id="div1">
	<p class="float_lft"> Link </p>
    <p class="float_lft"><input type="text" class="textfieldm"  name="nlink" id="nlink"/> </p>
	<br class="clr"/>
	</div>
	
	<div  id="div2">
	<br/><p class="float_lft"> Type </p><p class="float_lft"><select name="mtype" class="textfieldm" id="mtype"   >
	<option value="0">Select </option>
	<option value="1">Web Video </option>
	<option value="2">Podcast,PDF, DOC, PPT. </option>
	</select> </p>	<br class="clr"/></div>
	<div id="media"> 
	<p class="float_lft">YouTube Link </p><p class="float_lft"><input type="text"  name="membed" id="membed"  class="textfieldm" > </p> <br class="clr"/>
	</div>
	<div id="media_div">
	<p class="float_lft_file"> File </p><p class="float_lft"> <input type="hidden" name="docpath" id="docpath"/><iframe src="' . $gSitePath . 'upload_document.php" width="100%" height="40"  frameborder="0" scrolling="no"></iframe></p><br class="clr"/>
	</div>
	

	
	<div  id="div3">
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
        echo '<div class="messages success"> Resources Added Successfull </div>';
    }
}

function flag_question() {
    global $gSitePath, $user, $gDocPath, $base_root;

    $falgq = '';
    $falgq .= '	<script>
	var spath="' . $gSitePath . '";
	</script>
	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('theme', 'heardmentality') . '/scripts/mootools-1.2-core.js"></script>
	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('theme', 'heardmentality') . '/scripts/mootools-1.2-more.js"></script>
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
    $x = 0;
    foreach ($list as $fcnt) {

        $x = $x + $fcnt['wcnt'];
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
                $forum ="INSERT INTO {forum_wave} set qid_rid='" . $qid . "',type='1',uid='$user->uid',title='" . mysql_escape_string($wtitle) . "',private='$wprivate' ";
				
                $nid = ExecuteQuery($forum,'insert');
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

            $output = '<script type="text/javascript" src="' . $gSitePath . drupal_get_path('theme', 'heardmentality') . '/scripts/jquery.tab.js"></script>
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
                    $output1 .= '<div class="img">
					<p>' . UserPicture($profile['uid']) . $medal . '
				 <a href="' . $gSitePath . 'profile/' . $profile['name'] . '">' . $profile['name'] . '  </a>
			  
			     </p>
				</div>';
                }
            } else {
                $output1 = "No Users available";
            }
            $output = $output1;

            break;
        case "Info":
              $bubble =load_bubble($fetuserlist->uid);
        
            $output.= ' <h1> Question Information </h1><p class="con"> <b>Question Author: </b> <a  href="' . $gSitePath . 'profile/' . $fetuserlist->name . '" rel=\''.$bubble.'\'>' . $fetuserlist->name . '</a> <br/>
			<b>Date Created:</b> ' . date("D j M Y", strtotime($oListquest->date_added)) . ' <br/>
			<b>Number of Votes:</b> ' . $totalvotesm . '<br/>
			<b>Number of Forum Posts:</b>'.$x.' <br/>
			<b>Number of Resources:</b> ' . $numresource . '<br/>
                         <b>Context:</b> ' .$oListquest->context.'<br/>
                       </p>
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
    $wave .= '
	
	<link rel="stylesheet" href="' . $gSitePath . drupal_get_path('module', 'quest_lite') . '/css/wave.css" type="text/css" />';

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
	<p><textarea row="7" class="textArea" cols="55" name="wtitle" id="wtitle" ></textarea></p>	
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
					
					$flagnotify = "insert into notification(uid,node_id,is_flag) values ('".$user->uid."','" . $_REQUEST['uid'] . "',1)";
					db_query($flagnotify);
					
                    increasepoints('4', $_REQUEST['uid'], '0');
                    echo '<div class="messages success">You Have Flagged successfully ! </div>';
                } else {
                    echo '<div class="messages error">You Have Already Flagged !</div>';
                }
            } else {

                echo '<div class="messages error">Select Report Type !</div>';
            }
        } elseif (isset($_REQUEST['rid'])) {

            $numr = db_result(db_query("SELECT COUNT(*) from {question_flags} where nodeid='" . $_REQUEST['rid'] . "' and uid='" . $user->uid . "' and  type='resource' "));
            if ($_REQUEST['abuse_type'] != '') {
                if ($numr == 0) {
                    $flagquery = "insert into question_flags(nodeid,uid,type,abuse_type) values ('" . $_REQUEST['rid'] . "','" . $user->uid . "','resource','" . $_REQUEST['abuse_type'] . "')";
                    db_query($flagquery);
					
					$flagnotify = "insert into notification(uid,node_id,is_flag) values ('".$user->uid."','" . $_REQUEST['rid'] . "',1)";
					db_query($flagnotify);
					
                    increasepoints('4', $_REQUEST['uid'], '0');
                    echo '<div class="messages success">You Have Flagged successfully ! </div>';
                } else {
                    echo '<div class="messages error">You Have Already Flagged !</div>';
                }
            } else {

                echo '<div class="messages error">Select Report Type !</div>';
            }
        } elseif ($_REQUEST['rwave'] && $_REQUEST['rwave'] > 0) {


            $numr = db_result(db_query("SELECT COUNT(*) from {question_flags} where nodeid='" . $_REQUEST['rwave'] . "' and uid='" . $user->uid . "' and  type='wave' "));
            if ($_REQUEST['abuse_type'] != '') {
                if ($numr == 0) {
                    $flagquery = "insert into question_flags(nodeid,uid,type,abuse_type) values ('" . $_REQUEST['rwave'] . "','" . $user->uid . "','wave','" . $_REQUEST['abuse_type'] . "')";
                    db_query($flagquery);
					
					$flagnotify = "insert into notification(uid,node_id,is_flag) values ('".$user->uid."','" . $_REQUEST['rwave'] ."',1)";
					db_query($flagnotify);
					
                    increasepoints('4', $_REQUEST['uid'], '0');
                    echo '<div class="messages success">You Have Flagged successfully ! </div>';
                } else {
                    echo '<div class="messages error">You Have Already Flagged !</div>';
                }
            } else {

                echo '<div class="messages error">Select Report Type !</div>';
            }
        } elseif ($_REQUEST['rwavelet'] && $_REQUEST['rwavelet'] > 0) {


            $numr = db_result(db_query("SELECT COUNT(*) from {question_flags} where nodeid='" . $_REQUEST['rwavelet'] . "' and uid='" . $user->uid . "' and  type='wavelet' "));
            if ($_REQUEST['abuse_type'] != '') {
                if ($numr == 0) {
                    $flagquery = "insert into question_flags(nodeid,uid,type,abuse_type) values ('" . $_REQUEST['rwavelet'] . "','" . $user->uid . "','wavelet','" . $_REQUEST['abuse_type'] . "')";
                    db_query($flagquery);
					
					$flagnotify = "insert into notification(uid,node_id,is_flag) values ('".$user->uid."','" . $_REQUEST['rwavelet'] . "',1)";
					db_query($flagnotify);
					
                    increasepoints('4', $_REQUEST['uid'], '0');
                    echo '<div class="messages success">You Have Flagged successfully ! </div>';
                } else {
                    echo '<div class="messages error">You Have Already Flagged !</div>';
                }
            } else {

                echo '<div class="messages error">Select Report Type !</div>';
            }
        } else {

            $numr = db_result(db_query("SELECT COUNT(*) from {question_flags} where nodeid='" . $_REQUEST['qaid'] . "' and uid='" . $user->uid . "' and  type='question' "));
            if ($_REQUEST['abuse_type'] != '') {
                if ($numr == 0) {
                    $flagquery = "insert into question_flags(nodeid,uid,type,abuse_type) values ('" . $_REQUEST['qaid'] . "','" . $user->uid . "','question','" . $_REQUEST['abuse_type'] . "')";
                    db_query($flagquery);
					
					$flagnotify = "insert into notification(uid,node_id,is_flag) values ('".$user->uid."','". $_REQUEST['qaid'] ."',1)";
					db_query($flagnotify);
					
                    increasepoints('4', $_REQUEST['qaid'], '0');
                    echo '<div class="messages success">You Have Flagged successfully ! </div>';
                } else {
                    echo '<div class="messages error">You Have Already Flagged !</div>';
                }
            } else {

                echo '<div class="messages error">Select Report Type !</div>';
            }
        }
    } else {

        echo '<div class="messages error">Sorry You Not Have Sufficent User Points To Flag !</div>';
    }
}

function suggest_answer() {

    global $gSitePath, $user, $gDocPath, $base_root;

    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $ansoutput = '	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('theme', 'heardmentality') . '/scripts/mootools-1.2-core.js"></script>
	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('theme', 'heardmentality') . '/scripts/mootools-1.2-more.js"></script>
	<link rel="stylesheet" href="' . $gSitePath . path_to_theme() . '/css/css.css" type="text/css" />
	<link rel="stylesheet" href="' . $gSitePath . 'sites/all/modules/quest_lite/css/answer.css" type="text/css" />';

    $answers = "SELECT *	FROM suggest_answer where qid='" . $qid . "'  ";
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


            echo '<div class="messages success">Your Answer Posted Successfully ! </div>';
        }
    } else {
        echo '<div class="messages error">Sorry Error Occurs while voting! </div>';
    }
}

function question_news() {
    global $gSitePath, $user, $gDocPath, $base_root;
    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    require ('RSSParser.class.php');
    $xml = & new RSSParser;

    $vSql = "SELECT *,IFNULL((select count(*) from {forum_wave} as w where w.qid_rid=r.rid AND type='2' group by w.qid_rid ),0) as cntpost FROM resource as r where r.rtype='1' and r.qid='" . $qid . "' ";
    $rlistnews = db_query($vSql);
    $numnews = db_result(db_query("SELECT COUNT(*) FROM resource where rtype='1' and qid='" . $qid . "'"));
    $newsresult = '<link rel="stylesheet" href="' . $gSitePath . 'sites/all/modules/quest_lite/css/answer.css" type="text/css" />';
    while ($usernews = db_fetch_object($rlistnews)) {

        $output = $xml->parse($usernews->nlink);
        foreach ($output as $valuesresult) {

            //print_r( $valuesresult);
        }

        foreach ($valuesresult as $opkt) {
            $like = '';
            $flag = '';
            $post = '';
            $querylike = "select * from {user_likes} where is_resource='1' AND uid='$user->uid' AND node_id='" . $usernews->rid . "'";
            $fetch = ExecuteQuery($querylike, "select");

            if (count($fetch) < 1 || $fetch[0]['is_like'] == '0') {

               $like .= '<span  id="likelink" ><a href="javascript:void(0);" class="href" onclick="likethis(\'is_resource\',' . $usernews->rid . ',1,this);">Like</a></span>';
            } elseif ($fetch[0]['is_like'] == '1') {

                $like .= '<span id="likelink" > <a href="javascript:void(0);" class="href" onclick="likethis(\'is_resource\',' . $usernews->rid . ',0,this);">Unlike</a></span>';
            }

            //flag
            $flag .= '[<a href="javascript:void(0);" onclick="loadflagquestion(\'' . $gSitePath . 'qlite/flag/?rid=' . $usernews->rid . '\',\'Report \');
">Report</a>]';

            //posts
            $post .= '[<a href="javascript:void(0);" onclick="loadrforum(\'' . $gSitePath . 'resource/forum/' . $usernews->rid . '\',\'Resource forum \');
">' . $usernews->cntpost . ' Post</a>]';
            $getuser = user_load(array('uid' => $usernews->uid));
            $newsresult .= '<div class="cmt_list">
	
	<div class="lft_view"> <h4 class="cmt_name"><a style="font: normal 14px Arial, Helvetica, sans-serif; color:#02a33c; text-decoration:none;"; href="' . $opkt["LINK"] . '" target="new"> ' . $opkt["TITLE"] . ' </a> </h4>
		<p>' . $opkt['DESCRIPTION'] . ' </p>
	<p class="cmt_date"> ' . date("D j M Y", strtotime($opkt['PUBDATE'])) . '</p>
		<p class="cmt_date"> Posted by <a href="' . $gSitePath . 'profile/' . $getuser->name . '">' . $getuser->name . '</a></p></div>
	<!--<div class="rght_view" onclick="resource_like(' . $usernews->rid . ',' . $user->uid . ',1);" >
	<p id ="resource-fact">' . $like_count . '</p>Like
	</div>-->' . $like . ' <span>' . $flag . '</span><span>' . $post . '</span>
	</div>';
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
    $vSqlmedia = "SELECT *,IFNULL((select count(*) from {forum_wave} as w where w.qid_rid=r.rid AND type='2' group by w.qid_rid ),0) as cntpost FROM resource as r where r.rtype='2' and r.qid='" . $qid . "' ";
    $rlistmedia = db_query($vSqlmedia);
    $nummedia = db_result(db_query("SELECT COUNT(*) FROM resource where rtype='2' and qid='" . $qid . "'"));
    $mediaresult = '<link rel="stylesheet" href="' . $gSitePath . 'sites/all/modules/quest_lite/css/answer.css" type="text/css" />';
    while ($usermedia = db_fetch_object($rlistmedia)) {

        //flag
        $flag = '';
        $post = '';
        $flag .= '[<a href="javascript:void(0);" onclick="loadflagquestion(\'' . $gSitePath . 'qlite/flag/?rid=' . $usermedia->rid . '\',\'Report \');
">Report</a>]';
        $like = '';
        $querylike = "select * from {user_likes} where is_resource='1' AND uid='$user->uid' AND node_id='" . $usermedia->rid . "'";
        $fetch = ExecuteQuery($querylike, "select");

        if (count($fetch) < 1 || $fetch[0]['is_like'] == '0') {

            $like .= '<span  id="likelink" ><a href="javascript:void(0);" class="href" onclick="likethis(\'is_resource\',' . $usermedia->rid . ',1,this);">Like</a></span>';
        } elseif ($fetch[0]['is_like'] == '1') {

            $like .= '<span id="likelink" > <a href="javascript:void(0);" class="href" onclick="likethis(\'is_resource\',' . $usermedia->rid . ',0,this);">Unlike</a></span>';
        }

        //posts
        $post .= '[<a href="javascript:void(0);" onclick="loadrforum(\'' . $gSitePath . 'resource/forum/' . $usermedia->rid . '\',\'Resource forum \');
">' . $usermedia->cntpost . ' Post</a>]';
        $getuser = user_load(array('uid' => $usermedia->uid));
        $like_count = resource_Like_checkCount($usermedia->rid, 2);
        $mediaresult .= '<div class="cmt_list">
	<div class="lft_view"> <h4 class="cmt_name"><a style="font: normal 14px Arial, Helvetica, sans-serif; color:#02a33c; text-decoration:none;"; href="' . $gSitePath . '' . $usermedia->document . '" target="new"> ' . $usermedia->document . ' </a> </h4>
	<!--<p><img src="http://img.youtube.com/vi/' . $usermedia->video_id . '/default.jpg" ></p>
	<br/> --> 
	<p>  <object width="425" height="350">
       <param name="movie" value="http://www.youtube.com/v/' . $usermedia->video_id . '">
       </param>
       <embed src="http://www.youtube.com/v/' . $usermedia->video_id . '" type="application/x-shockwave-flash" width="320" height="220">
       </embed>
</object>

 </p>
	<p class="cmt_date"> ' . date("D j M Y", strtotime($usermedia->posted_date)) . '</p>
		<p class="cmt_date"> Posted by <a href="' . $gSitePath . 'profile/' . $getuser->name . '">' . $getuser->name . '</a></p></div>
<!--	<div class="rght_view" onclick="resource_like(' . $usermedia->rid . ',' . $user->uid . ',2);" >
	<p id ="resource-fact">' . $like_count . '</p>Like
	</div>--><div>' . $like . ' <span>' . $flag . '</span><span>' . $post . '</span></div>
	</div>';
    }
    if ($nummedia == 0) {

        $mediaresult .= 'No Media Under This Question.';
    }
    echo $mediaresult;
}

function question_facts() {

    global $gSitePath, $user, $gDocPath, $base_root;
    $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $vSqlfact = "SELECT *,IFNULL((select count(*) from {forum_wave} as w where w.qid_rid=r.rid AND type='2' group by w.qid_rid ),0) as cntpost FROM resource as r where r.rtype='3' and r.qid='" . $qid . "' ";
    $rlistfacts = db_query($vSqlfact);
    $numfacts = db_result(db_query("SELECT COUNT(*) FROM resource where rtype='3' and qid='" . $qid . "'"));
    $factsesult = '<link rel="stylesheet" href="' . $gSitePath . 'sites/all/modules/quest_lite/css/answer.css" type="text/css" />';
    while ($userfacts = db_fetch_object($rlistfacts)) {

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

        $factsesult .= '<div class="cmt_list">
	<div class="lft_view"> <h4 class="cmt_name"><a href="' . $userfacts->facts . '" target="_blank" style="color:#02a33c;text-decoration:none;"> ' . $userfacts->facts . ' </a> </h4>
	<p class="cmt_date"> ' . date("D j M Y", strtotime($userfacts->posted_date)) . '</p>
	<p class="cmt_date"> Posted by <a href="' . $gSitePath . 'profile/' . $getuser->name . '">' . $getuser->name . '</a></p></div>
	<!--<div class="rght_view" onclick="resource_like(' . $userfacts->rid . ',' . $user->uid . ',3);" >
	<p id ="resource-fact">' . $like_count . '</p>Like
	</div>-->
	<div>' . $like . ' <span>' . $flag . '</span><span>' . $post . '</span></div>
	</div>';
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
            $answer['divide'] = array('male', 'female');


            for ($ab = 0; $ab < count($vlist); $ab++) {


                $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' AND u.gender='2' ";
                $female = ExecuteQuery($query, "norows");
                $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' AND u.gender='1' ";
                $male = ExecuteQuery($query, "norows");
                $answer_cnt[] = '[' . $male . ',' . $female . ']';
            }//[1,0][1,1]
            // $answer_cnt=array_reverse($answer_cnt);//[1,1][1,0]


            break;
        case 'age':
            $answer['divide'] = array('18-30', '30-50', '50 above');

            foreach ($answer['divide'] as $key => $value) {
                if ($key == 0)
                    $query_ins = "AND u.age BETWEEN '18' AND '30' ";
                elseif ($key == 1)
                    $query_ins = "AND u.age BETWEEN '30' AND '50'";
                elseif ($key == 2)
                    $query_ins = "AND u.age>='50' ";
                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' " . $query_ins;
                    $tcnt = ExecuteQuery($query, "norows");
                    $inc_cnt .= $tcnt . ',';
                }
                $inc_cnt .= ']';
                $answer_cnt[] = $inc_cnt;
            }


            //$answer_cnt;
            break;
        case 'religion':
            $answer['divide'] = array('Christian', 'Muslim', 'Jewish', 'Hindu', 'Buddhist', 'Other');

            foreach ($answer['divide'] as $list) {
                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' AND religion='" . $list . "'";
                    $tcnt = ExecuteQuery($query, "norows");
                    $inc_cnt .= $tcnt . ',';
                }
                $inc_cnt .= ']';
                $answer_cnt[] = $inc_cnt;
            }


            break;
        case 'ethnicity':
            $answer['divide'] = array('Caucasian', 'Black', 'Asian', 'Indian', 'Semetic', 'Latin', 'Aborigines');

            foreach ($answer['divide'] as $list) {
                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' AND ethnic='" . $list . "'";
                    $tcnt = ExecuteQuery($query, "norows");
                    $inc_cnt .= $tcnt . ',';
                }
                $inc_cnt .= ']';
                $answer_cnt[] = $inc_cnt;
            }


            break;
        case 'slant':
            $answer['divide'] = array('Left', 'Right', 'Center');

            foreach ($answer['divide'] as $list) {
                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' AND slant='" . $list . "'";
                    $tcnt = ExecuteQuery($query, "norows");
                    $inc_cnt .= $tcnt . ',';
                }
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
            $inc_cnt=rtrim($inc_cnt,",");
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

			<link rel='stylesheet' href='" . $gSitePath . drupal_get_path('theme', 'heardmentality') . "/css/content.css' type='text/css' />
			<script type='text/javascript' src='" . $gSitePath . drupal_get_path('module', 'quest_lite') . "/scripts/filter.js'></script>
	
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
        $ins_script .= "{	
						name: '" . $ans[$key] . "',
  				       data: " . $cnt[$key] . "
					}";
    }

    $per = json_encode($result);
    $inc = rtrim($inc, ',');
    $output .= "
		<script>
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
						categories: " . json_encode($ans_array) . "
					},
					yAxis: {
						min: 0,
						title: {
							text: 'No Of Votes'
						}
					},
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
				      series: [" . $ins_script . " ]
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
            array_push($ans,$inc_this);
        }
        $ins_sc='[' . implode(',', $ans) . ']';
        array_push($grid, "'" . $vlist[$ab]['answer'] . "'");
        $insdata.="{name :'".$vlist[$ab]['answer']."', data: ".$ins_sc."},";
    }
   $sdate="Date.UTC(".$year.",".$month.",".(date("d")-6).", 0, 0, 0)";
   // $script.=$ins_sc;

   

    echo $script .= "
var chart;
var gSitePath='".$gSitePath."';

$(document).ready(function() {
   chart = new Highcharts.Chart({
      chart: {
         renderTo: 'container',
         defaultSeriesType: 'spline',
         ignoreHiddenSeries: false
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
            pointStart:".$sdate."
         }
      },
      series: [".$insdata."]
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
            qid:'".$qid."'
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

    global $gSitePath, $user, $gDocPath, $base_root, $base_path,$googlekey;

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
				<script src='http://maps.google.com/maps?file=api&amp;v=2&amp;sensor=false&amp;key=".$googlekey."' type='text/javascript'></script>
                                <script src='http://gmaps-utility-library.googlecode.com/svn/trunk/markerclusterer/1.0/src/markerclusterer.js' type='text/javascript'></script>
                                  <script src=' http://gmaps-utility-library.googlecode.com/svn/trunk/markermanager/release/src/markermanager.js' type='text/javascript'></script>
";




    echo $script.="<script type='text/javascript' >
			
				 function initialize() {
    	var map = new google.maps.Map2(document.getElementById('map_div'));
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
		//map.setCenter(new GLatLng(37.4419, -122.1419), 13);
		  map.addControl(new GLargeMapControl());
    map.addControl(new GMapTypeControl());
      	" . $inc_script . "
                  
                  
	 var markerCluster = new MarkerClusterer(map, markers);

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

	var markering=new GMarker(markerLocation, {title:'Zip['+markerId+']',icon:icon});
	GEvent.addListener(markering, 'click', function() {
		markering.openInfoWindowHtml('<p>Zip['+markerId+']</p>');
	});
	return markering;
}

				</script>
					";


    echo '  <body onload="initialize()" onunload="GUnload()"><div style="width:100%;"><div  class=""><div id="map_div" style="width: 472px; height: 300px"></div><br/><div style="position: relative;" id="desc">' . $desc . '</div></div>';
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
            
    }*/
     hm_mails($qid,'','vote_answer');
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
    }*/
    hm_mails($qid,$nid,'add_forum');
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
         
          $str=substr($_REQUEST['date'],'0','10');
             $date=date('d-m-Y',$str);
             $qid=$_REQUEST['qid'];
             $query="select * from {resource} where date(posted_date)<='$date' AND qid='$qid'";
             $set = ExecuteQuery($query, "select");
             
              $result.="<div> <b>Resources For Date :".date('d M,Y',$str)."</b></div><hr/><br/><ul>";
              if(!empty($set)){
             foreach($set as $list){

                switch($list['rtype']){

                 case '1':
                    $inc.="<li><a href=\"".$list['ncontent']."\" target=\"_blank\">You Tube Video</a></li>";
                     break;
                 case '2':
                    $inc.="<li><a href=\"".$list['membed']."\" target=\"_blank\">You Tube Video</a></li>";
                     break;
                 case '3':
                   $inc.="<li><a href=\"".$list['facts']."\">".$list['facts']."</a></li>";
                     break;

                }
                
             }
              }else{

                  $inc="<b>No Resource for this Date</b>";
              }
          echo   $result=$result.$inc."</ul>";

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
