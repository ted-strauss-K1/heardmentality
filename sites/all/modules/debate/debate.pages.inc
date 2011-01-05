<?php

function debate_list($qid = '', $did='') {

    global $gSitePath, $user, $gDocPath, $base_root;
    if (empty($qid) || !is_numeric($qid) || empty($did) || !is_numeric($did)) {
        return FALSE;
    }

    global $gSitePath, $user, $gDocPath, $base_root;
    $output = '';
    $like = '';
    $flag = '';

    $query = "SELECT *,u.uid as uid  FROM {debate} as f  join {user_profile} as u on u.uid=f.uid   where f.qid_rid='$qid' AND f.did='$did' AND f.status='1'";
    $list = ExecuteQuery($query, "select");


    $output .= '
       <div class="hm-debate2-wrapper">
    	<div class="titlebg">
        	<div class="menudebate">
            	<ul>

                	<li><a href="#">Previous Debate</a></li>
                    <li><a href="#">Next Debate</a></li>
                </ul>
            </div>

            	<div class="backbtn"><a href="#"></a></div>
                	<h2>TITLE OF THE DEBATE</h2>
        <div class="clr"></div>
        </div>


        <div class="clr"></div>
            <div class="hm-debate-cont-outer backping">

           <h3> Debate Title Coming here...</h3>

                        <div>

                        <hr class="hr-silver"/>

<div align="center" id="waveerr"></div>
';
    foreach ($list as $forum) {


//$date = cdatetime($forum['date_added']).$forum['date_added'];

        $date = format_date_class($forum['date_added'], date());
        $account = user_load($forum['uid']);
        $image = empty($forum['image']) ? 'noimage.jpg' : $forum['image'];
        $name = empty($forum['real_name']) ? $forum['first_name'] : $forum['real_name'];
//likes or not
        $querylike = "select * from {user_likes} where is_debate='1' AND uid='$user->uid' AND node_id='" . $forum['did'] . "'";
        $fetch = ExecuteQuery($querylike, "select");
        $agreecnt = db_result(db_query("select count(*) from {user_likes} where is_debate='1' AND is_agree='1' AND node_id='" . $forum['did'] . "'"));
        $disagreecnt = db_result(db_query("select count(*) from {user_likes} where is_debate='1' AND is_agree='0' AND node_id='" . $forum['did'] . "'"));
        if (count($fetch) < 1) {

            $like = '<li><span name="' . $did . '" id="dagree" ><a href="javascript:void(0);" name="a-' . $did . '" class="dagree">Agree</a>&nbsp;<a name="da-' . $did . '" href="javascript:void(0);" class="ddisagree">Disagree</a></span></li>';
        } elseif ($fetch[0]['is_debate'] == '1' && $fetch[0]['is_agree']) {

            $like = '<li><em>You <strong>agree</strong> with this comment</em></li>';
        } else {
            $like = '<li><em>You <strong>Disagree</strong> with this comment</em></li>';
        }
//flag
        $flag.='<a href="#freport"  class="floatbox flag-menu" title="Report Post" onclick="report_forum(\'rwave\',' . $did . ');"></a>';
        $bubble = load_bubble($account->uid);
        $medal = updateProfileBadge($account->uid);
        $output .= '

<div class="debate-inn-item">
<div class=" itemto">
<div class="itemto-right">
<h5>' . $forum['title'] . '</h5>
' . make_clickable($forum['content']) . '
</div>

<div class="itemto-left">

<div class="toppart"><p>' . $agreecnt . '</p>

<p align="center"><img height="15" width="18" alt="Agree" src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/aggree-hand.jpg"></p></div>

<div class="toppart2"><p>' . $disagreecnt . '</p>
<p align="center"><img height="15" width="18" alt="Dis Agree" src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/disaggree-hand.jpg"></p>
<div class="clr"></div>
</div>
<div class="clr"></div>
</div>
<div class="clr"></div>
<div class="itembott">
<div class="itemfirst">
<ul>
' . $like . '
</ul>
<div class="clr"></div>
</div>

<div class="itemsecond">
<ul>
<li><a class="floatbox reply-menu" onclick="addComment(this);" name="rep" title="Reply Post"  id="' . $did . '-0" href="#postreply"></a></li>
<li>' . $flag . '</li>
</ul>
</div>
<div class="itemthird">
<div class="profile-img">
<div class="profile-imgs">
<a title="' . $account->name . '" href="' . $gSitePath . 'profile/' . $account->name . '">' . UserPicture($account->uid) . '</a>
</div>
<div class="profile-con">' . $medal . '
<div>
</div>
</div>

</div>
<div class="clr"></div>
</div>
</div>
<div class="clr"></div>
</div>
<div class="clr"></div>
</div>
<div id="wavelet-list">
	';
    }
    $output .= get_debate($did, 0);


    $output.='
       </div>
      
       </div>

<div class="clr"></div>
</div>
 <div class="clr"></div>
</div>
<div class="clr"></div>
</div>
<div class="clr"></div>
<div class="reply-wrapper" id="postreply" style="display:none;">
<form id="postreply" name="freply" action="' . $gSitePath . 'issues/debate/save">
  	<h2>REPLY</h2>

    	<div>
        <textarea rows="10" cols="" name="waveletcmt" id="waveletcmt">Enter text here</textarea>
<!--<input type="checkbox" name="privt" value="1" id="privt"/> Private Reply-->
<input type="hidden" name="fdid" id="fdid" value="' . $did . '"/>
		<input type="hidden" name="frid" id="frid" value=""/>
			<input type="hidden" name="action" value="reply" />
        </div>

        <div class="clr"></div>
        	<div class="m-out">
            	<div class="m1"><input type="radio" value="1" CHECKED name="str_wk"/> Strengthen</div>
                <div class="m2"><input type="radio" value="0" name="str_wk"/> Weaken</div>
                 <div align="right" class="m3"><input type="button" id="waveButton" class="submit-debate-btn"  name="dreply"></div>

            	<div class="clr"></div>
            </div>

</form>


  <div class="clr"></div>
  </div>
<!-- end popup-->
<div class="clr"></div>
<div class="" id="freport" style="display:none;">
<div class="d-header">
 <h3 class="">Report the post<a class="close" href="#"> [X] Close</a></h3>
<div class="clr"></div><form  action="' . $gSitePath . 'qlite/flagreport" method="post" id="flagform">
<div class="comment-area">

	<input type="hidden" value="" id="rwave" name="rwave"/>
	<input type="hidden" value="" id="rwavelet" name="rwavelet"/>
	

<div class="adcomment-outer">
	<p><input type="radio" checked="checked" value="Pornography or obscenity" id="abuse_type" name="abuse_type"/>
	Pornography or obscenity </p><p><input type="radio" value="radically or ethnically hateful content" id="abuse_type" name="abuse_type"/>
	radically or ethnically hateful content  </p><p><input type="radio" value="Graphic Violence" id="abuse_type" name="abuse_type"/>
	Graphic Violence </p><p><input type="radio" value="other content inappropirate for young Viewers" id="abuse_type" name="abuse_type"/>
	other content inappropirate for young Viewers </p><p>
	<input type="submit" value="Report Problem" class="waveButton" id="submitter" name="button"/>  or <a onclick=" jQuery.unblockUI();return false;" id="wavecancel1" href="">cancel</a>
        </p>
       
	</div>
         <div class="clr"></div>
</form> </div>
        <div class="clr"></div>
</div></div>
</div>';
    if (isAjax ()) {
        echo $output;
    } else {

        return $output;
    }
}

function post_notification($did='', $rid='') { ///vijay important comented
    global $gSitePath, $user, $gDocPath, $base_root;
    db_query("insert into {notification} set follower_action='1',is_wavelets='1',uid='$user->uid',node_id='$nid' ");


    hm_mails('', $did, 'reply_forum');
////////////mail notication for user follwers to me//////////////////////////////////////
}

function like_notification($nid='', $set='') { //vijay important comented
    global $gSitePath, $user, $gDocPath, $base_root;



///////vijay///
    db_query("insert into {notification} set is_like='1',$set,uid='$user->uid',node_id='$nid' ");
    $sel_forum = "select * from debate_reply as f join debate as w on f.rid=w.fid where f.rid='" . $nid . "'";
    $forum_fet = db_query($sel_forum);
    $forum_row = db_fetch_object($forum_fet);
    $qid_rid = $forum_row->qid_rid;
    hm_mails($qid_rid, $nid, 'add_like');
//////vijay///
// db_query("insert into {notification} set is_like='1',$set,uid='$user->uid',node_id='$nid' ");
//hm_mails($nid);
////////////mail notication for user follwers to me//////////////////////////////////////
    /* $sel_listf = "select * from follower  where follower_id='".$user->uid."'";
      $rs_followerf = db_query($sel_listf);
      while ($follower_resultfuser = db_fetch_object($rs_followerf))
      {

      $sellist="select * from users where uid='".$follower_resultfuser->uid."'";
      $res_users=db_query($sellist);
      $usert=db_fetch_object($res_users);
      $to = $usert->mail;
      if($usert->notify_itype==1)
      {

      ///$follower_resultfuser->uid vijay changed here
      db_query("insert into {notification} set is_like='1',$set,uid='$user->uid',node_id='$nid' ");
      }
      if($usert->notify_etype==1)
      {

      ///////////email for following ///////////////
      $sel_user_cmt="SELECT * FROM notification_mail_format Where id='5'";
      $rs_mgmt=db_query($sel_user_cmt);
      $list_content=db_fetch_object($rs_mgmt);
      $subject_proj=$list_content->subject;
      $contentm=str_replace("#uname#",$usert->name,$list_content->content);
      $contentm= str_replace("#anothername#",$user->name,$contentm);
      $mail_success = htmlmail_function($to,$subject_proj,$contentm,'');
      }
      } */
}

function get_debate($did = '', $pid = '') {

    global $gSitePath, $user, $gDocPath, $base_root;
    $output = '';
    $bg = '';
    if (!empty($did)) {


        $query = "select * from {debate_reply} as f  join {user_profile} as u on u.uid=f.uid  where f.did='$did' and f.status='1' and parentid='$pid'";

        $list = ExecuteQuery($query, "select");

//print_r($set);

        foreach ($list as $forum) {

// $date = cdatetime($forum['date_added']).$forum['date_added'];
            $date = format_date_class($forum['date_added'], date());
            $account = user_load($forum['uid']);


            if (wave_access($forum['rid'], $forum['private'])) {

                $image = empty($forum['image']) ? 'noimage.jpg' : $forum['image'];
                $name = empty($forum['real_name']) ? $forum['first_name'] : $forum['real_name'];
                $querylike = "select * from {user_likes} where is_debate_reply='1' AND uid='$user->uid' AND node_id='" . $forum['rid'] . "'";
                $fetch = ExecuteQuery($querylike, "select");
                $cntagree = db_result(db_query("select count(*) from {user_likes} where is_debate_reply='1' AND is_agree='1' AND node_id='" . $forum['rid'] . "'"));
                $cntdisagree = db_result(db_query("select count(*) from {user_likes} where is_debate_reply='1' AND is_agree='0' AND node_id='" . $forum['rid'] . "'"));

                if (count($fetch) < 1) {

                    $like = '<li><span name="' . $forum['rid'] . '" id="dragree" ><a href="javascript:void(0);" name="a-' . $forum['rid'] . '" class="ragree"">Agree</a>&nbsp;<a name="da-' . $forum['rid'] . '" href="javascript:void(0);" class="rdisagree">Disagree</a></span></li>';
                } elseif ($fetch[0]['is_agree']) {

                    $like = '<li><em>You <strong>agree</strong> with this comment</em></li>';
                } else {
                    $like = '<li><em>You <strong>Disagree</strong> with this comment</em></li>';
                }
//flag
                $flag = '';
                $flag.='<a  href="#freport" class="floatbox flag-menu" onclick="report_forum(\'rwavelet\',' . $forum['rid'] . ');"></a>';

                $medal = updateProfileBadge($account->uid);
                $bubble = load_bubble($account->uid);
                if ($forum['str_wk'])
                    $plus = '<a href="#"><img width="23" height="23" alt="Strengthen" src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/plus-img.jpg"></a>';
                else
                    $plus='<a href="#"><img width="23" height="23" alt="Weaken" src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/minus-img.jpg"></a>';

                $output .= '<div class="clr"></div>
<div class="hm-debate-cont-outer backash com-' . $forum['rid'] . '"">
' . $plus . '
<div>


<!-- <h3> Debate Title Coming here...</h3>--!>
<hr class="hr-silver-2">

<div class="debate-inn-item">
<div class=" itemto">
<div class="itemto-right">
<div class="form-outer-debate">
<div class="fm-1">&nbsp;</div>
<div class="fm-4">
' . make_clickable($forum['reply']) . '
</div>



</div>


<div class="clr"></div>
</div>

<div class="itemto-left">

<div class="toppart">
<p>' . $cntagree . '</p>

<p align="center">
<img height="15" width="18" alt="Agree" src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/aggree-hand.jpg">
</p></div>

<div class="toppart2">
<p>' . $cntdisagree . '</p>
<p align="center">
<img height="15" width="18" alt="Dis Agree" src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/disaggree-hand.jpg">
</p>
<div class="clr"></div>
</div>
</div>

<div class="clr"></div>
</div>

<div class="clr"></div>
<div class="itembott">
<div class="itemfirst">
<ul>
' . $like . '
</ul>
<div class="clr"></div>
</div>

<div class="itemsecond">
<ul>
<li><a class="floatbox reply-menu" onclick="addComment(this);" id="' . $did . '-' . $forum['rid'] . '"  href="#postreply"></a></li>
<li>' . $flag . '</li><li>' . $date . '</li>
</ul>
</div>

<div class="itemthird">
<div class="profile-img">
<div class="profile-imgs">
<a title="' . $account->name . '" href="' . $gSitePath . 'profile/' . $account->name . '">' . UserPicture($account->uid) . '</a>
</div>
<div class="profile-con">' . $medal . '
<div>

</div>
</div></div>
</div>
<div class="clr"></div>
';
                $output .= get_debate($did, $forum['rid']);

                $output .= '    </div>
<div class="clr"></div>
</div>
</div>
<div class="clr"></div>
</div>	';
            }
        }

        return $output;
    } else {


        return 'Error Occurs ';
    }
}

function wave_access($id = '', $pvt = '') {
    global $gSitePath, $user, $gDocPath, $base_root;


    if ($pvt == 1) {
        $query = "select *,f.uid as uid from {debate_reply} as f left join {user_profile} as u on u.uid=f.uid  where f.rid='$id' ";

        $list = ExecuteQuery($query, "select");
//print_r($list);

        if ($list[0]['uid'] == $user->uid) {

            return true;
        } else {

//followers or following

            $query = "(select count(*) as a from {follower} where uid='" . $list[0]['uid'] . "' AND follower_id='$user->uid') union (select count(*) as b from {follower} where uid='$user->uid' AND follower_id='" . $list[0]['uid'] . "')";

            $fet = ExecuteQuery($query, "select");

            if ($fet[0]['a'] || $fet[0]['b']) {
                return true;
            }
        }
    } else {

        return true;
    }

    return false;
}

function admin_debate() {
    global $gSitePath, $user, $gDocPath, $base_root;
    $strReturn = '';

    drupal_add_js(drupal_get_path('module', 'forum') . '/scripts/admin_forum.js');
// print_r($_REQUEST);
    if (isset($_REQUEST['fdelete']) && $_REQUEST['delete'] == 1) {
//echo $_REQUEST['fid'];
//$ids=(!empty($_REQUEST['fid']))?$_REQUEST['fid']:$_REQUEST['fids'];
        $qid = $_REQUEST['fid'];

        db_query("delete from {debate} where fid in ($qid)");

        db_query("delete from {debate_reply} where wid in ($qid)");
        drupal_set_message($message = 'Forum wave & wavelets deleted successfully!', $type = 'success');
        drupal_goto('admin/forum');
    } elseif (isset($_REQUEST['Inactive'])) {

        $ids = implode(',', $_REQUEST['qids']);
        if (!empty($ids)) {
            db_query("update {debate} set status='0' where fid in ($ids)");
            db_query("update {debate_reply} set status='0' where wid in ($ids)");
            drupal_set_message($message = 'Forum wave & wavelets InActive  successfully!', $type = 'success');
        } else {

            drupal_set_message($message = 'Sorry no Waves Selected', $type = 'error');
        }
    } elseif (isset($_REQUEST['Active'])) {

        $ids = implode(',', $_REQUEST['qids']);
        if (!empty($ids)) {
            db_query("update {debate} set status='1' where fid in ($ids)");
            db_query("update {debate_reply} set status='1' where wid in ($ids)");
            drupal_set_message($message = 'Forum wave & wavelets Activated  successfully!', $type = 'success');
        } else {

            drupal_set_message($message = 'Sorry no Waves Selected', $type = 'error');
        }
    }


    $query = "select f.*,u.*,DATE_FORMAT(f.date_added, '%a %M %Y %h:%i %p') as date_added,IFNULL((select count(*) from {debate_reply} as wl where wl.wid=f.fid group by wl.wid ),0) as cntpost,IFNULL((select count(*) from {forumwave_like} as l where l.wid=f.fid group by l.wid),0) as cntlike,IFNULL((select count(*) from {user_likes} where is_wave='1' AND node_id=f.fid group by node_id),0) as cntlikes,IFNULL((select count(*) from {question_flags} where type='wave' and nodeid=f.fid group by nodeid),0) as cntflag from {debate} as f  join {user_profile} as u on u.uid=f.uid ORDER BY f.fid DESC ";
    $list = ExecuteQuery($query, "select");
//pagination

    $nodes_per_page = 2;

    /* $rs = pager_query($query,$nodes_per_page,0,count($list));
      $array=array();
      while($rw = db_fetch_array($rs))
      {
      array_push($array,$rw);
      }
      //pagination */


    $strReturn .= '<div class="clear-block">
	
	<div align="right"></div>
	<form id="fadmin" method="post" action="' . url($_GET['q'], array('absolute' => true)) . '" >
	<input type="hidden" name="fdelete" id="fdelete" value=""/>
	<input type="hidden" name="fid" id="fid" value=""/>
	<table width="98%" border="1" cellspacing="5" cellpadding="5">
	<tr><td><b><i>Forum Topics</i></b></td><td><i><b># Wavelets</b></i></td><td><i><b># Likes</b></i></td><td><i><b>Posted By</b></i></td><td><i><b>#Flags</b></i></td><td><i><b>Status</b></i></td><td><i><b>Date</b></i></td><td><i><b>Action</b></i></td></tr>
	';
    foreach ($list as $quest) {

        if ($quest['type'] == 1) {

            $vSql = "select * from {question} where qid='" . $quest['qid_rid'] . "' ";
            $rlist = db_query($vSql);
            $oListquest = db_fetch_object($rlist);
        }

//flag report
        $flag_report = '';
        if ($quest['cntflag'] > 0) {
            $fquery = "select u.real_name,l.* from {question_flags} as l join {user_profile} as u on u.uid=l.uid  where l.type='wave' AND l.nodeid='" . $quest['fid'] . "' ORDER BY flag_date DESC";
            $flaglist = ExecuteQuery($fquery, "select");
            foreach ($flaglist as $flist) {
                $flag_report.='<span>Flagged by ' . $flist['real_name'] . '</span>';
                $flag_report.='<span> as ' . $flist['abuse_type'] . '</span>';
                $flag_report.='<span> on ' . $flist['flag_date'] . '</span><hr/>';
            }
        }



        $rand = rand(10, 100);
        $stat = ($quest['status'] == 1) ? 'Active' : 'InActive';
        $date = format_date_class($quest['date_added'], date('Y-m-d H:m:s'));
//$date= date_format('Y-m-d H:m:s',$quest['date_added']);

        $strReturn .= '<tr><td>';
        $strReturn .= '<a href="javascript:void(0);" onclick="toggle_sub(' . $quest['qid_rid'] . $rand . ');">' . wordwrap($quest['title'], 40, '<br/>') . '</a>';
        $strReturn .= '</td>';
        $strReturn .= '<td><a href="' . $gSitePath . 'admin/wavelets/' . $quest['fid'] . '">' . $quest['cntpost'] . '</a></td><td>' . $quest['cntlike'] . '</td>
		<td>' . $quest['real_name'] . '</td><td>' . $quest['cntflag'] . '</td><td>' . $stat . '</td><td>' . $date . '</td><td>';

        $strReturn .= '<input type="checkbox" class="check-me" name="qids[]" value="' . $quest['fid'] . '" /> <b>|</b> <a href="javascript:void(0);" onclick="forum_del(' . $quest['fid'] . ');">Delete</a> <b>|</b><a href="' . $gSitePath . 'admin/forum/edit/' . $quest['fid'] . '">Edit</a>  ';

        $strReturn .= '</td></tr>';
        $strReturn .= '<TR > <TD height="0" COLSPAN=8><div style="display:none;" id="q' . $quest['qid_rid'] . $rand . '"><b>Posted For Question :</b><a  href="' . $gSitePath . $oListquest->url . '">' . wordwrap($oListquest->question, 80, '<br/>') . '</a>&nbsp;' . $flag_report . '</div></TD> </TR>
';
    }


    if (count($list) < 1) {
//  drupal_set_message($message = 'No Questions Found!', $type = 'error');
        $strReturn .= ' <div class="error" align="left" >No Result Found!</div> ';
    } else {

        $strReturn .= '</table>
		<div><input type="submit" name="Inactive" value="Inactive" />   <input type="submit" name="Active" value="Active" /><span onclick="checkall(1);">Check All</span>&nbsp;<span onclick="checkall(0);">Uncheck All</span></form>
		</div>';
    }
    $strReturn .= theme('pager', NULL, 10);

    return $strReturn;
}

function admin_debate_edit() {

    global $gSitePath, $user, $gDocPath, $base_root;
    $strReturn = '';
    $fid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    if (isset($_REQUEST['fsubmit'])) {
        extract($_REQUEST);
        if (!empty($ftopic)) {

            $query = "update {debate} set title='" . mysql_escape_string($ftopic) . "' where fid='$fid'";

            $up = db_query($query);
            drupal_set_message($message = 'Thank you Topic updated', $type = 'success');
            drupal_goto('admin/forum');
        } else {

            drupal_set_message($message = 'Topic should not be empty!', $type = 'error');
        }
    }


    drupal_add_js(drupal_get_path('module', 'forum') . '/scripts/admin_forum.js');
    $query = "select f.*,DATE_FORMAT(f.date_added, '%a %M %Y %h:%i %p') as date_added,IFNULL((select count(*) from {debate_reply} as wl where wl.wid=f.fid group by wl.wid ),0) as cntpost,IFNULL((select count(*) from {forumwave_like} as l where l.wid=f.fid group by l.wid),0) as cntlike from {debate} as f where f.fid='$fid' ";
    $list = ExecuteQuery($query, "select");

    $strReturn .= '<div class="clear-block">
	<div align="right"></div>
	<form id="qadmin" method="post" action="' . url($_GET['q'], array('absolute' => true)) . '" >
	<table width="98%" border="0" cellspacing="5" cellpadding="5">
	<tr><td align="left"><b>Edit Forum Topic</b> </td></tr>
	<tr><td align="left"><textarea cols="40" rows="17" name="ftopic" id="ftopic" >' . $list[0]['title'] . '</textarea> </td></tr>
	<tr><td align="left"><input type="submit" name="fsubmit" value="Update"/> <span> </span><input type="button" name="fback" value="Back" onclick="window.location.href=\'' . $gSitePath . 'admin/forum\';"/></td></tr>
	</form>
	';

    return $strReturn;
}

function admin_debate_wlets() {

    global $gSitePath, $user, $gDocPath, $base_root;
    $strReturn = '';
    drupal_add_js(drupal_get_path('module', 'forum') . '/scripts/admin_forum.js');
    $did = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    if (isset($_REQUEST['fdelete']) && $_REQUEST['fdelete'] == 1) {
//echo $_REQUEST['fid'];
//$ids=(!empty($_REQUEST['fid']))?$_REQUEST['fid']:$_REQUEST['fids'];
        $qid = $_REQUEST['fid'];


        db_query("delete from {debate_reply} where rid in ($qid)");
        drupal_set_message($message = 'wavelets deleted successfully!', $type = 'success');
        drupal_goto('admin/wavelets/' . $did);
    } elseif (isset($_REQUEST['Inactive'])) {

        $ids = implode(',', $_REQUEST['qids']);
        if (!empty($ids)) {

            db_query("update {debate_reply} set status='0' where rid in ($ids)");
            drupal_set_message($message = 'Forum wavelets InActive  successfully!', $type = 'success');
        } else {

            drupal_set_message($message = 'Sorry no Wavelets Selected', $type = 'error');
        }
    } elseif (isset($_REQUEST['Active'])) {

        $ids = implode(',', $_REQUEST['qids']);
        if (!empty($ids)) {

            db_query("update {debate_reply} set status='1' where rid in ($ids)");
            drupal_set_message($message = 'Forum  wavelets Activated  successfully!', $type = 'success');
        } else {

            drupal_set_message($message = 'Sorry no Wavelets Selected', $type = 'error');
        }
    }


    $query = "select *, IFNULL((select count(*) from {debate_reply} as wl where wl.parentid=f.rid group by wl.wid ),0) as cntpost,IFNULL((select count(*) from {user_likes} where is_wavelets='1' and node_id=f.rid group by node_id ),0) as cntlike,IFNULL((select count(*) from {question_flags} where type='wavelet' and nodeid=f.rid group by nodeid),0) as cntflag from {debate_reply} as f  join {user_profile} as u on u.uid=f.uid where f.wid='$did'";

    $list = ExecuteQuery($query, "select");

    $strReturn .= '<div class="clear-block">
	
	<div align="right"><a href="' . $gSitePath . 'admin/forum">Back To Forum </a></div>
	<form id="fadmin" method="post" action="' . url($_GET['q'], array('absolute' => true)) . '" >
	<input type="hidden" name="fdelete" id="fdelete" value=""/>
	<input type="hidden" name="fid" id="fid" value=""/>
	<table width="98%" border="1" cellspacing="5" cellpadding="5">
	<tr><td><b><i>Wavelets</i></b></td><td><b><i># Reply</i></b></td><td><b><i># Likes</i></b></td><td><b><i># flag</i></b></td> <td><b><i>Posted By</i></b></td><td><i><b>Status</b></i></td><td><i><b>Date</b></i></td><td><i><b>Action</b></i></td></tr>
	';
    foreach ($list as $quest) {


        $stat = ($quest['status'] == 1) ? 'Active' : 'InActive';
        $date = format_date_class($quest['date_added'], date('Y-m-d H:m:s'));
//$date= date_format('Y-m-d H:m:s',$quest['date_added']);
        $flag_report = '';
        if ($quest['cntflag'] > 0) {
            $fquery = "select u.real_name,l.* from {question_flags} as l join {user_profile} as u on u.uid=l.uid  where l.type='wavelet' AND l.nodeid='" . $quest['rid'] . "' ORDER BY flag_date DESC";
            $flaglist = ExecuteQuery($fquery, "select");
            foreach ($flaglist as $flist) {
                $flag_report.='<span>Flagged by ' . $flist['real_name'] . '</span>';
                $flag_report.='<span> as ' . $flist['abuse_type'] . '</span>';
                $flag_report.='<span> on ' . $flist['flag_date'] . '</span><hr/>';
            }
        }
        $strReturn .= '<tr><td>';
        $strReturn .= wordwrap($quest['wavelet'], 40, '<br/>');
        $strReturn .= '</td>';
        $strReturn .= '<td>' . $quest['cntpost'] . '</td><td>' . $quest['cntlike'] . '</td><td>' . $quest['cntflag'] . '</td><td>' . $quest['real_name'] . '</td><td>' . $stat . '</td><td>' . $date . '</td><td>';

        $strReturn .= '<input type="checkbox" class="check-me" name="qids[]" value="' . $quest['rid'] . '" /> <b>|</b><a href="javascript:void(0);" onclick="wavelet_del(' . $quest['rid'] . ');">Delete</a> <b>|</b><a href="' . $gSitePath . 'admin/wavelets/edit/' . $quest['rid'] . '">Edit</a>  ';

        $strReturn .= '</td></tr>';
    }


    if (count($list) < 1) {
//  drupal_set_message($message = 'No Questions Found!', $type = 'error');
        $strReturn .= ' <div class="error" align="left" >No Result Found!</div> ';
    } else {

        $strReturn .= '</table>
		<div><input type="submit" name="Inactive" value="Inactive" />   <input type="submit" name="Active" value="Active" /><span onclick="checkall(1);">Check All</span>&nbsp;<span onclick="checkall(0);">Uncheck All</span></form>
		</div>';
    }

    return $strReturn;
}

function admin_wlets_edit() {

    global $gSitePath, $user, $gDocPath, $base_root;
    $fid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    if (isset($_REQUEST['fsubmit'])) {
        extract($_REQUEST);
        if (!empty($ftopic)) {

            $query = "update {debate_reply} set wavelet='" . mysql_escape_string($ftopic) . "' where rid='$fid'";

            $up = db_query($query);
            drupal_set_message($message = 'Thank you Topic updated', $type = 'success');
            drupal_goto('admin/wavelets/' . $fid);
        } else {

            drupal_set_message($message = 'Wavelet should not be empty!', $type = 'error');
        }
    }


    drupal_add_js(drupal_get_path('module', 'forum') . '/scripts/admin_forum.js');
    $query = "select * from {debate_reply} where rid='$fid' ";
    $list = ExecuteQuery($query, "select");

    $strReturn .= '<div class="clear-block">
	<div align="right"></div>
	<form id="qadmin" method="post" action="' . url($_GET['q'], array('absolute' => true)) . '" >
	<input type="hidden" name="fid" value="' . $list[0]['wid'] . '"/>
	<table width="98%" border="0" cellspacing="5" cellpadding="5">
	<tr><td align="left"><b>Edit Forum Wavelet</b> </td></tr>
	<tr><td align="left"><textarea cols="40" rows="17" name="ftopic" id="ftopic" >' . $list[0]['wavelet'] . '</textarea> </td></tr>
	<tr><td align="left"><input type="submit" name="fsubmit" value="Update"/> <span> </span><input type="button" name="fback" value="Back" onclick="window.location.href=\'' . $gSitePath . 'admin/wavelets/' . $list[0]['wid'] . '\';"/></td></tr>
	</form>
	';

    return $strReturn;
}

function add_resources($qid='') {
    global $gSitePath, $user, $gDocPath, $base_root;
    $ans = load_options($qid);

    //answers
    foreach ($ans as $list) {

        $inc_pans.='
	<div class="form-outer-debate">
    	<div class="fm-1">&nbsp;</div>
        <div class="fm-2">
        <div class="fm-2-left">' . $list['answer'] . ' </div>
<div class="fm-2-right">

            <input type="hidden" name="ans_id[]" value="' . $list['paid'] . '"/><select  name="sup_opp[]"><option value="0">Neutral</option><option  value="1">Supports</option><option value="2">Oppose</option></select>
              </div>




        </div>




    <div class="clr"></div>
    </div>
    		';
    }

    $resources = '<link rel="stylesheet" href="' . $gSitePath . drupal_get_path('module', 'debate') . '/css/answer.css" type="text/css" />
         <script src="' . $gSitePath . '/misc/jquery.js"></script>
<link rel="stylesheet" href="' . $gSitePath . drupal_get_path('module', 'debate') . '/css/fileuploader.css" type="text/css" />
            <script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'debate') . '/scripts/fileuploader.js"></script>
            <script> var spath="' . $gSitePath . '";</script>
                   	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'quest_lite') . '/scripts/jquery.blockUI.js"></script>
	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'debate') . '/scripts/add_resource.js"></script>
	<link rel="stylesheet" href="' . $gSitePath . path_to_theme() . '/css/css.css" type="text/css" />
	';

    $resources .= '<body style="background:none;background:#666;">
          <div class="" id="err">' . $list_err . '</div>
    <div class="new-debate-wrapper">
        <form id="myForm" name="myForm"  method="post" action="' . $gSitePath . 'debate/ajax" enctype="multipart/form-data" >
            <input type="hidden" name="qaid" value="' . $qid . '"/>
             <input type="hidden" name="action" value="resource_new"/>
  <div class="form-outer-debate">
    	<div class="fm-1">Please Follow the <a href="#">Principles and Guidelines.</a></div>
        <div class="fm-2">   <select name="rtype" class="listbox1" id="rtype" >
	<option value="0">Resource Type </option>
	<option value="1">News </option>
	<option value="2">Multimedia </option>
	<option value="3">Facts </option>
	</select></div>


    <div class="clr"></div>
    </div>
    <div class="form-outer-debate">
    	<div class="fm-1">All debates should be:<br />
            <ul>
            <li>Concise</li>
            <li>Etc</li>
            </ul></div>
        <div id="div1" style="display:none;"  class="fm-2"><input type="text" class="" style="float:left; padding:3px;"  name="nlink" value="http://" id="nlink"/> <div><input id="lattach" name="name" type="button" value="Attach"  style="float:left; width:50px; padding:1px;"/></div></div>
<div id="div2" style="display:none;"  class="fm-2"><select name="mtype" class="listbox1" id="mtype"   >
	<option value="0">Choose Format </option>
	<option value="1">Web Video </option>
	<option value="2">Podcast,PDF, DOC, PPT. </option>
	</select> 
            </div>

    <div class="clr"></div>
    </div>
 <div class="form-outer-debate">
 <div class="fm-1"> &nbsp;</div>
<div id="media" style="display:none;"  class="fm-2"> <input type="text"  name="membed" id="membed" value="http://"  class="" ></div>
<div id="media_div" style="display:none;"  class="fm-2">
<input type="hidden" name="docpath" id="docpath"/> <div id="file-uploader-demo1"> </div>
</div>

    <div class="clr"></div>
    </div>

        <div class="form-outer-debate">
    	<div class="fm-1"> &nbsp;
</div>
        <div class="fm-2" id="linkbox">
        	



      </div>


    <div class="clr"></div>
    </div>

 ' . $inc_pans . '
     	<div class="form-outer-debate">
    	<div class="fm-1">&nbsp;</div>
        <div class="fm-2">
        <div class="fm-2-left">&nbsp</div>
        <div class="fm-2-right" align="right"><input name="submit" value="" type="submit" id="submitter" class="submit-debate-btn"/></div>

        </div>

    <div class="clr"></div>
    </div>


</form>
      <div class="clr"></div>
  </div>


</body>


      
';
    echo $resources;
}

function resource_list($type, $qid) {
    global $gSitePath, $user, $gDocPath, $base_root;
    $output = '';
    switch ($type) {
        case 'innews':

            $output = 'innews';
            break;
        case 'media':

            $output = 'media';
            break;
        case 'facts':


            $output = 'ffacts';
            break;
        default:
            $output = 'No Action Found!';
            break;
    }


    if (isAjax ())
        echo $output;
    else
        return $output;
}

function resdebate_list() {
    global $gSitePath, $user, $gDocPath, $base_root;
    $rid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    if (isset($_POST['wtitle']) && !empty($user->uid)) {

        $rid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
        extract($_POST);
        $forum = "INSERT INTO {debate} set qid_rid='$rid',type='2',uid='$user->uid',title='" . mysql_escape_string($wtitle) . "',content='" . mysql_escape_string($wcon) . "',private='$wprivate' ";
        $nid = ExecuteQuery($forum, 'insert');
        echo list_wave($rid, 2);
        send_forumnotify($nid, $rid);
        exit;
    } elseif (isset($_POST['wtitle'])) {
        echo '<div align="center"><b>Sorry Only Logged in user can post wave</b></div>';
        echo list_wave($rid, 2);
        exit;
    }

// $rid=$_REQUEST['rid'];
    $wave = '';
    $wave .= '	<script>
	var spath="' . $gSitePath . '";
            var uid="' . $user->uid . '";
	</script>

  <script src="' . $gSitePath . '/misc/jquery.js"></script>

 	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'forum') . '/scripts/forum.js"></script>

<script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'quest_lite') . '/scripts/jquery.blockUI.js"></script>
     <script src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/scripts/jbubble.js"></script>
<link rel="stylesheet" href="' . base_path() . path_to_theme() . '/css/css.css" type="text/css" />';

//print_r($cnt);
    $wave .= '
	<body style="background:none;">
<div class="pop-up-wrapper">
<div class="pop-up" align="center">
<div class="pop-tp"></div>
<div class="pop-md" align="center">
<div class="tp-sandalbar">
<span class="pimg"><img src="' . base_path() . path_to_theme() . '/images/pimg1.jpg" width="30" height="25" alt="image1" /></span>
<span class="pimg"><img src="' . base_path() . path_to_theme() . '/images/pimg2.jpg" width="30" height="25" alt="image2" /></span>
<span class="pimg"><img src="' . base_path() . path_to_theme() . '/images/pimg3.jpg" width="30" height="25" alt="image3" /></span>
<span class="pimg"><img src="' . base_path() . path_to_theme() . '/images/pimg4.jpg" width="30" height="25" alt="image4" /></span>
<span class="pimg"><img src="' . base_path() . path_to_theme() . '/images/pimg5.jpg" width="30" height="25" alt="image5" /></span>
<div class="ad-bt"><a href="#" title="Add"><img src="' . base_path() . path_to_theme() . '/images/add-bt.jpg" width="37" height="22" alt="Add button" /></a></div>
<div class="clr"></div>

</div>

<div class="clr"></div>


<div class="popmenu">
<ul>
<ul>
<li><a href="#"><span><img src="' . base_path() . path_to_theme() . '/images/menu-b1.png" width="14" height="7" alt="Menu1" /></span>Next</a></li>
<li><a href="#"><span><img src="' . base_path() . path_to_theme() . '/images/menu-b2.png" width="11" height="11" alt="menu2" /></span>Reply</a></li>
<li><a href="#"><span><img src="' . base_path() . path_to_theme() . '/images/menu-b3.png" width="9" height="11" alt="menu3"/></span>Edit</a></li>
<li><a href="#" class="selectpop"><span><img src="' . base_path() . path_to_theme() . '/images/menu-b4.png" width="8" height="7" alt="menu4" /></span>Playback</a></li>
<li><a href="#"><span><img src="' . base_path() . path_to_theme() . '/images/menu-b5.png" width="10" height="10" alt="menu5" /></span>Unfollow</a></li>
<li><a href="#"><span><img src="' . base_path() . path_to_theme() . '/images/menu-b6.png" width="10" height="11" alt="menu6" /></span>Archive</a></li>
<li><a href="#"><span><img src="' . base_path() . path_to_theme() . '/images/menu-b7.png" width="8" height="9" alt="menu7" /></span>Spam</a></li>


</ul>


</ul>
<div class="clr"></div>
</div>

<div class="clr"></div>
<div class="content-popup">
	<div id="ajaxpage_content">
	<div align="right"><a href="#" id="newwavebut" onclick="toggle();" >Post New Topic</a></div>
	<div id="qwave" class="">
		
		';
    $wave.=list_wave($rid, 2);


    $wave .= '</div></div><!--ajax content end-->
        </div>

<div class="clr"></div>
</div>
<div class="pop-bt"></div>
</div>
<div class="clr"></div>
</div>

	<div class="" id="newwavediv" style="display:none">';
    if (!empty($user->uid)) {
        $wave.='
	 <div class="d-header">
    <h3 class="">POST A TOPIC<a href="#" class="close"> [X] Close</a></h3>
<div class="clr"></div>
<div class="comment-area">
	<form  id="newwaveform" class="newwave" action="' . url($_GET['q'], array('absolute' => true)) . '" method="post" accept-charset="utf-8">
            <p><b>Title</b></p>
        	<p><input type="text" name="wtitle" id="wtitle" value=""/></p>
                <p><b>Content</b></p>
	<textarea row="7" class="textArea" cols="40" name="wcon" id="wcon" ></textarea>
        <div class="clr"></div>

<div class="adcomment-outer">
	<!--<div ><b>Private Reply :</b> [Only followers can do reply]</div>
	<p><select name="wprivate" id="wprivate">
	<option value="0"> Disabled</option>
	<option value="1"> Enabled  </option>
	</select></p>		-->			
	<input type="hidden" name="type" value="2"/>
	<input type="hidden" name="burl" value="' . $gSitePath . '" id="burl"/>
	<div class="ad-bt"><input type="button" class="waveButton" onclick="wave_form();" value="Post" /></div>
        </div>
        <div class="clr"></div>

</form> </div>';
    } else {
        $wave.='<div align="center"><b>Sorry Only Logged in user can post wave</b></div>';
    }
    $wave.='</body>
		';

    echo $wave;
}

function debate_ajax() {
    global $gSitePath, $user, $gDocPath, $base_root;

    extract($_REQUEST);

    switch ($action) {

        case 'url':
            if ($_GET['url']) {

                require_once('simple_html_dom.php');
                require_once('thumbnail.php');
                require_once('url_to_absolute.php');
                $url = $_GET['url'];
                $html = file_get_html($url);
                $tags = get_meta_tags($url);
                $domain = parse_url($url, PHP_URL_HOST);
                $images = array();
                foreach ($html->find('img') as $element) {
                    $images[$element->src] = true;
                }
                $inc.='<em>' . $html->find('title', 0)->innertext . '</em><br/>';
                $inc.='<strong>' . $domain . '</strong><br/>';
                $inc.='<span>' . $tags['description'] . '</span>';

                foreach ($html->find('img') as $element) {
                    $imgs[] = url_to_absolute($url, $element->src);
                }
                echo '<div class="leftfm"><img src="' . $imgs[0] . '" width="118" height="73"  /></div><div class="rightfm">' . $inc . '</div>
                    <input type="hidden" name="udesc" value="' . myTruncate($inc, 255) . '"/><input type="hidden" name="uimg" value="' . $imgs[0] . '"/>
                        ';

                /*
                  $tg = new thumbnailGenerator;
                  foreach($images as $url => $void) {
                  $tg->generate($url, 100, 100, 'thumbnails/' . md5($url) . '.jpg');
                  } */
            }
            break;
        case 'resource_new':

            global $gSitePath, $user, $gDocPath, $base_root;
            if ($rtype != 0) {
                if (!empty($membed) && $rtype == 2 && $mtype == 1) {
                    $ytURL = $membed;
                    $ytvIDlen = 11; // This is the length of YouTube's video IDs

                    $idStarts = strpos($ytURL, "?v=");


                    if ($idStarts === FALSE)
                        $idStarts = strpos($ytURL, "&v=");

                    if ($idStarts === FALSE)
                        die("<div class='messages error'>YouTube video ID not found. Please double-check your URL.</div>");

                    $idStarts += 3;

                    $ytvID = substr($ytURL, $idStarts, $ytvIDlen);

                    $ytvID;
                }
                $files = resource_save_ext_imgs($uimg);

                $resourceadd = "insert into resource(rtype,nlink,ntitle,ncontent,mtype,membed,facts,uid,qid,nimage,document,video_id,udesc,uimg) values ('$rtype','" . addslashes($nlink) . "','" . addslashes($ntitle) . "','" . addslashes($ncontent) . "','" . $mtype . "','" . addslashes($membed) . "','" . addslashes($flink) . "', '" . $user->uid . "','" . $qaid . "','" . $path . "','" . $docpath . "','" . $ytvID . "','" . $udesc . "','" . $files . "')";
                db_query($resourceadd);
                $nid = db_last_insert_id('resource', 'rid');
                foreach ($ans_id as $list) {

                    $forum = "INSERT INTO {resource_options} set rid='%d',paid='%d',ans_val='%d' ";
                    $result = db_query($forum, $nid, $list, $sup_opp[$i]);
                    $i++;
                }
                echo '<div class="messages success"> Resources Added Successfully! </div>';
            }
            break;
        default:
            echo "<div class='messages error'>No Action found</div>";
            break;
    }

    exit;
}

function resource_save_ext_imgs($url='') {


    $result = drupal_http_request($url);

    $dir = file_create_path() . '/resources';

    if (!file_check_directory($dir)) {

        mkdir($dir, 0775, true);
    }
    $code = floor($result->code / 100) * 100;
    $ext = '.' . 'jpg';
    $types = array('image/jpeg', 'image/png', 'image/gif');
    $src = file_create_path() . '/resources/' . md5($url) . $ext;
    if ($result->data && $code != 400 && $code != 500 && in_array($result->Content - Type, $types)) {

        $return = file_save_data($result->data, $src);

        return $return;
    } else {

        //if we are unsuccessful then log a message in the watchdog

        watchdog('resource', 'The image ' . $url . ' could not be retrieved');
        return false;
    }
}

////url to hyperlink converting 
function _make_url_clickable_cb($matches) {
    $ret = '';
    $url = $matches[2];
    if (empty($url))
        return $matches[0];
// removed trailing [.,;:] from URL
    if (in_array(substr($url, -1), array('.', ',', ';', ':')) === true) {
        $ret = substr($url, -1);
        $url = substr($url, 0, strlen($url) - 1);
    }
    return $matches[1] . "<a href=\"$url\" rel=\"nofollow\">" . myTruncate($url, '30', '', '...') . "</a>" . $ret;
}

function _make_web_ftp_clickable_cb($matches) {
    $ret = '';
    $dest = $matches[2];
    $dest = 'http://' . $dest;
    if (empty($dest))
        return $matches[0];
// removed trailing [,;:] from URL
    if (in_array(substr($dest, -1), array('.', ',', ';', ':')) === true) {
        $ret = substr($dest, -1);
        $dest = substr($dest, 0, strlen($dest) - 1);
    }
    return $matches[1] . "<a href=\"$dest\" rel=\"nofollow\" target=\"_blank\">$dest</a>" . $ret;
}

function _make_email_clickable_cb($matches) {
    $email = $matches[2] . '@' . $matches[3];
    return $matches[1] . "<a href=\"mailto:$email\" target=\"_blank\">$email</a>";
}

function make_clickable($ret) {
    //  $ret = ltrim($ret, 'http://');
    //  $ret = ' ' . $ret;
// in testing, using arrays here was found to be faster
    $ret = preg_replace_callback('#([\s>])([\w]+?://[\w\\x80-\\xff\#$%&~/.\-;:=,?@\[\]+]*)#is', '_make_url_clickable_cb', $ret);
    $ret = preg_replace_callback('#([\s>])((www|ftp)\.[\w\\x80-\\xff\#$%&~/.\-;:=,?@\[\]+]*)#is', '_make_web_ftp_clickable_cb', $ret);
    $ret = preg_replace_callback('#([\s>])([.0-9a-z_+-]+)@(([0-9a-z-]+\.)+[0-9a-z]{2,})#i', '_make_email_clickable_cb', $ret);
// this one is not in an array because we need it to run last, for cleanup of accidental links within links
    $ret = preg_replace("#(<a( [^>]+?>|>))<a [^>]+?>([^>]+?)</a></a>#i", "$1$3</a>", $ret);
    $ret = trim($ret);
    return $ret;
}

function debate_submit() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_url;
    extract($_REQUEST);

    if (empty($user->uid)) {

        echo "<small>Sorry, Please login to do this action!</small>";
        exit;
    }
    switch ($action) {

        case 'new':
            if (!empty($wtitle) && !empty($user->uid)) {

                $forum = "INSERT INTO {debate} set qid_rid='%d',type='1',uid='%d',title='%s',content='%s',private='%d' ";
                $result = db_query($forum, $qid, $user->uid, $wtitle, $wcon, $wprivate);

                $nid = db_last_insert_id('debate', 'did');
                ;
                $i = 0;

                foreach ($ans_id as $list) {

                    $forum = "INSERT INTO {debate_options} set did='%d',paid='%d',ans_val='%d' ";
                    $result = db_query($forum, $nid, $list, $sup_opp[$i]);
                    $i++;
                }
                echo list_debate($qid, 1);
                /* RAM HEARTBEAT MODULE INSERT DEBATE */
                $qid_url = db_query("select * from {question} where qid='$qid'");
                $question_values = db_fetch_array($qid_url);
                if (isset($question_values)) {
                    $question_urlff = $question_values['url'] . '/' . $nid;
                    $qtion = $question_values['question'];
                    $ctxt = $question_values['context'];
                }
                $message_id = 'debate_add';
                $variables = array(
                    '@username' => l(user_load($user->uid)->name, 'user/' . $user->name),
                    //'@node_type' => 'page',
                    '@debate_title' => "<a href='$base_url/$question_urlff' >" . $qtion . "</a>",
                );
                heartbeat_api_log($message_id, $user->uid, $question_urlff, $qid, $question_urlff, $variables);
                /* RAM HEARTBEAT MODULE INSERT DEBATE */
                send_forumnotify($nid, $qid);
            } elseif (isset($wtitle)) {
                echo '<div align="center"><b>Sorry Only Logged in user can post New Debate</b></div>';
                echo list_debate($qid, 1);
            }
            break;
        case 'reply':
            $query = "insert into {debate_reply} set did='%d',uid='%d',parentid='%d',str_wk='%d',reply='%s',private='%s'";
            $result = db_query($query, $fdid, $user->uid, $frid, $str_wk, check_plain($waveletcmt), $pvt);
            $rid = db_last_insert_id('debate_reply', 'rid');
            echo $output = get_debate($fdid, 0);
            post_notification($fdid, $rid);
            /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */
            $qid_url = db_query("select * from {question} where qid='$frid'");
            $question_values = db_fetch_array($qid_url);
            if (isset($question_values)) {
                $question_urlff = $question_values['url'] . '/' . $fdid;
                $qtion = $question_values['question'];
                $ctxt = $question_values['context'];
            }
            $message_id = 'debate_reply';
            $variables = array(
                '@username' => l(user_load($user->uid)->name, 'user/' . $user->name),
                '@debate_title' => "<a href='$base_url/$question_urlff' >" . $qtion . "</a>",
            );
            heartbeat_api_log($message_id, $user->uid, $question_urlff, $qid, $question_urlff, $variables);
            /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */
            break;
        case 'is_debate':
        case 'is_debate_reply':
            $cond = " AND " . $action . "='1'";
            $set = " " . $action . "='1'";

            $query = "select * from {user_likes} where node_id='$nodeid' $cond AND uid='$user->uid'";

            $chk = db_result(db_query($query));

            if (!$chk && $user->uid > 0) {

                $query = "insert into {user_likes} set $set ,node_id='$nodeid',uid='$user->uid',is_agree='$agree'";

                $chk = db_query($query);
//guru points
                insertpoints($action, $nodeid);
//notification
                like_notification($nodeid, $set);

                $msg['cnt'] = db_result(db_query("select count(*) from {user_likes} where $set AND is_debate='1' AND node_id='" . $nodeid . "'"));
                if ($agree) {
                    $msg['msg'] = '<em>You <strong>agree</strong> with this comment</em>';
                    /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */
                    $qid_url = db_query("select * from {question} where qid='$nodeid'");
                    $question_values = db_fetch_array($qid_url);
                    if (isset($question_values)) {
                        $question_urlff = $question_values['url'] . '/' . $frid;
                        $qtion = $question_values['question'];
                        $ctxt = $question_values['context'];
                    }
                    $message_id = 'debate_agree';
                    $variables = array(
                        '@username' => l(user_load($user->uid)->name, 'user/' . $user->name),
                        '@debate_title' => "<a href='$base_url/$question_urlff' >" . $qtion . "</a>",
                    );
                    heartbeat_api_log($message_id, $user->uid, $question_urlff, $qid, $question_urlff, $variables);
                    /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */
                } else {
                    $msg['msg'] = '<em>You <strong>Disagree</strong> with this comment</em>';
                    /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */
                    $qid_url = db_query("select * from {question} where qid='$nodeid'");
                    $question_values = db_fetch_array($qid_url);
                    if (isset($question_values)) {
                        $question_urlff = $question_values['url'] . '/' . $nodeid;
                        $qtion = $question_values['question'];
                        $ctxt = $question_values['context'];
                    }
                    $message_id = 'debate_disagree';
                    $variables = array(
                        '@username' => l(user_load($user->uid)->name, 'user/' . $user->name),
                        '@debate_title' => "<a href='$base_url/$question_urlff' >" . $qtion . "</a>",
                    );
                    heartbeat_api_log($message_id, $user->uid, $question_urlff, $qid, $question_urlff, $variables);
                    /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */
                }
                $msg['error'] = '0';
            } else {
                $msg['error'] = '1';
                $msg['msg'] = '<em>Sorry <strong>Error</strong> occurs while updating</em>';
            }
            echo json_encode($msg);
            break;
        default:

            break;
    }
    return;
}
