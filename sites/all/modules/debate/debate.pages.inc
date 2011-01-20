<?php

function debate_list($qid = '', $did='') {

    global $gSitePath, $user, $gDocPath, $base_root;
    if (empty($qid) || !is_numeric($qid) || empty($did) || !is_numeric($did)) {
        return FALSE;
    }
    $output = '';
    $like = '';
    $flag = '';
    // update points
    debate_roundup($did);
    $query = "SELECT *,u.uid as uid  FROM {debate} as f  join {user_profile} as u on u.uid=f.uid   where f.qid='$qid' AND f.did='$did' AND f.status='1'";
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

            $like = '<li><span type="is_debate" name="' . $did . '" id="dagree" ><a href="javascript:void(0);" name="a-' . $did . '" class="dagree">Agree</a>&nbsp;<a name="da-' . $did . '" href="javascript:void(0);" class="ddisagree">Disagree</a></span></li>';
        } elseif ($fetch[0]['is_debate'] == '1' && $fetch[0]['is_agree']) {

            $like = '<li><em>You <strong>agree</strong> with this comment</em></li>';
        } else {
            $like = '<li><em>You <strong>Disagree</strong> with this comment</em></li>';
        }
//flag
        $flag.='<a href="#freport"  class="floatbox flag-menu" title="Report Post" onclick="report_forum(\'debate\',' . $did . ');"></a>';
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
<form id="postreplyform" name="freply" action="' . $gSitePath . 'issues/debate/save">
  	<h2>REPLY</h2>

    	<div>
        <textarea rows="10" cols="" name="waveletcmt" id="waveletcmt">Enter text here</textarea>
<!--<input type="checkbox" name="privt" value="1" id="privt"/> Private Reply-->
<input type="hidden" name="fdid" id="fdid" value="' . $did . '"/>
    <input type="hidden" name="qid" id="qid" value="' . $qid . '"/>
		<input type="hidden" name="frid" id="frid" value=""/>
			<input type="hidden" name="action" value="reply" />
        </div>

        <div class="clr"></div>
        	<div class="m-out">
            	<div class="m1"><input type="radio" value="1" CHECKED name="str_wk"/> Strengthen</div>
                <div class="m2"><input type="radio" value="0" name="str_wk"/> Weaken</div>
                 <div align="right" class="m3"><input type="submit" id="waveButton" value="" class="submit-debate-btn"  name="dreply"></div>

            	<div class="clr"></div>
            </div>

</form>


  <div class="clr"></div>
  </div>
<!-- end popup-->
<div class="clr"></div>
<div class="" id="freport" style="display:none;">
<div class="d-header">
 <h3 class="">Report the post</h3>
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
    $qid_rid = $forum_row->qid;
    hm_mails($qid, $nid, 'add_like');
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

                    $like = '<li><span name="' . $forum['rid'] . '" type="is_debate_reply" id="dragree" ><a href="javascript:void(0);" name="a-' . $forum['rid'] . '" class="ragree"">Agree</a>&nbsp;<a name="da-' . $forum['rid'] . '" href="javascript:void(0);" class="rdisagree">Disagree</a></span></li>';
                } elseif ($fetch[0]['is_agree']) {

                    $like = '<li><em>You <strong>agree</strong> with this comment</em></li>';
                } else {
                    $like = '<li><em>You <strong>Disagree</strong> with this comment</em></li>';
                }
//flag
                $flag = '';
                $flag.='<a  href="#freport" class="floatbox flag-menu" onclick="report_forum(\'rdebate\',' . $forum['rid'] . ');"></a>';

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



<hr class="hr-silver-2"></hr>

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

function get_res_debate($rid = '', $pid = '') {

    global $gSitePath, $user, $gDocPath, $base_root;
    $output = '';
    $bg = '';
    if (!empty($rid)) {


        $query = "select * from {resource_reply} as f  join {user_profile} as u on u.uid=f.uid  where f.rid='$rid' and f.status='1' and parentid='$pid'";

        $list = ExecuteQuery($query, "select");

//print_r($set);

        foreach ($list as $forum) {

// $date = cdatetime($forum['date_added']).$forum['date_added'];
            $date = format_date_class($forum['date_added'], date());
            $account = user_load($forum['uid']);


            if (wave_access($forum['reid'], $forum['private'])) {

                $image = empty($forum['image']) ? 'noimage.jpg' : $forum['image'];
                $name = empty($forum['real_name']) ? $forum['first_name'] : $forum['real_name'];
                $querylike = "select * from {user_likes} where is_resource_reply='1' AND uid='$user->uid' AND node_id='" . $forum['reid'] . "'";
                $fetch = ExecuteQuery($querylike, "select");
                $cntagree = db_result(db_query("select count(*) from {user_likes} where is_resource_reply='1' AND is_agree='1' AND node_id='" . $forum['reid'] . "'"));
                $cntdisagree = db_result(db_query("select count(*) from {user_likes} where is_resource_reply='1' AND is_agree='0' AND node_id='" . $forum['reid'] . "'"));

                if (count($fetch) < 1) {

                    $like = '<li><span type="is_resource_reply" name="' . $forum['reid'] . '" id="dragree" ><a href="javascript:void(0);" name="a-' . $forum['reid'] . '" class="ragree"">Agree</a>&nbsp;<a name="da-' . $forum['reid'] . '" href="javascript:void(0);" class="rdisagree">Disagree</a></span></li>';
                } elseif ($fetch[0]['is_agree']) {

                    $like = '<li><em>You <strong>agree</strong> with this comment</em></li>';
                } else {
                    $like = '<li><em>You <strong>Disagree</strong> with this comment</em></li>';
                }
//flag
                $flag = '';
                $flag.='<a  href="#freport" class="floatbox flag-menu" onclick="report_forum(\'rresource\',' . $forum['reid'] . ');"></a>';

                $medal = updateProfileBadge($account->uid);
                $bubble = load_bubble($account->uid);
                if ($forum['str_wk'])
                    $plus = '<a href="#"><img width="23" height="23" alt="Strengthen" src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/plus-img.jpg"></a>';
                else
                    $plus='<a href="#"><img width="23" height="23" alt="Weaken" src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/minus-img.jpg"></a>';

                $output .= '<div class="clr"></div>
<div class="hm-debate-cont-outer backash com-' . $forum['reid'] . '"">
' . $plus . '
<div>



<hr class="hr-silver-2"></hr>

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
<li><a class="floatbox reply-menu" onclick="addComment(this);" id="' . $rid . '-' . $forum['reid'] . '"  href="#postreply"></a></li>
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
                $output .= get_res_debate($rid, $forum['reid']);

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

    $resources = '<link rel="stylesheet" href="' . $gSitePath . drupal_get_path('module', 'debate') . '/css/answer.css" type="text/css" />
         <script src="' . $gSitePath . '/misc/jquery.js"></script>
<link rel="stylesheet" href="' . $gSitePath . drupal_get_path('module', 'debate') . '/css/fileuploader.css" type="text/css" />
            <script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'debate') . '/scripts/fileuploader.js"></script>
            <script> var spath="' . $gSitePath . '";</script>
                   	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'quest_lite') . '/scripts/jquery.blockUI.js"></script>
	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'debate') . '/scripts/add_resource.js"></script>
	<link rel="stylesheet" href="' . $gSitePath . path_to_theme() . '/css/css.css" type="text/css" />
	';
    if ($user->uid < 1) {
        echo $resources.='<div class="messages error">Sorry you have to login to post New Resource!</div>';
        die;
    }

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

    $resources .= '<body style="background:none;background:#FFF;">
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
        $ans=load_options($qid);
    //answers
    $filter_list.='<select name="rfilt-ans" id="rfilt-ans" class="select-1"><option value="">Possible Answers</option>';
    foreach($ans as $list){
        $filter_list.='<option value="'.$list['paid'].'">'.$list['answer'].'</option>';
        $inc_pans.='<div class="form-outer-debate">
    	<div class="fm-1">&nbsp;</div>
        <div class="fm-2">
        <div class="fm-2-left">'.$list['answer'].'</div>
        <div class="fm-2-right"><input type="hidden" name="ans_id[]" value="'.$list['paid'].'"/><select  name="sup_opp[]"><option value="0">Neutral</option><option  value="1">Supports</option><option value="2">Oppose</option></select></div>
        </div>
        <div class="clr"></div>
    </div>';
    }
$filter_list.='</select>';
    //print_r($cnt);
    $output .= '

     <div class=" debate-round-tab-outer">
              	<div class="form-part-top">
                    <div class="form-m1">Filter By :
<select name="rfilt-sup" id="rfilt-sup" class="select-2"><option value="0">+/-</option><option value="1">+</option><option value="2">-</option></select></div>
                    <div class="form-m2"><br/>
                    '.$filter_list.'
                    </div>
                    <div class="form-m3"><br/><input type="hidden" name="rtype" id="rtype" value="'.$type.'" />
                    <select name="rfilt-sort" id="rfilt-sort" class="select-2"><option value="0">Sort By :</option>
                    <option value="1">Most Recent</option>
                     <option value="2">Most Support</option>
                    </select>

                    </div>
                    <div class="form-m4" align="right">&nbsp;<br />
<a href="javascript:void(0);" onclick="javascript:loadresource(\'' . $gSitePath . 'debate/resource/new/' . $qid . '\',\'Add\');" title="New Debate"><input name="" type="button"   class="submit-debate-btn"/></a></div>

                </div>

                	<div class="clr"></div><br />

                    <hr />

                    <br />


                    <div class="clr"></div> <div id="resfilter">';

    switch ($type) {
        case 'innews':
            $output.= resource_innews($qid, 1);
            break;
        case 'media':

            $output.= resource_media($qid);
            break;
        case 'facts':


            $output.= resource_innews($qid, 3);
            break;
        default:
            $output = '<div class="messages warning">No Action Found!</div>';
            break;
    }

    $output.='</div></div>';

    if (isAjax ())
        echo $output;
    else
        return $output;
}

function resource_innews($qid='', $rtype='') {
    global $gSitePath, $user, $gDocPath, $base_root;
    $wave = '';
    $click = '';
    $sortin='ORDER BY rid DESC';
    $cond='';
    extract($_REQUEST);
        if(isset($sort)&&$sort==1)
            $sortin=' ORDER BY r.posted_date DESC';
        elseif(isset($sort)&&$sort==2)
             $sortin=' ORDER BY r.strength DESC';
        if(isset($ans)&&!empty($ans))
            $cond.=" AND ro.paid='$ans'";
        if(isset($sup)&&$sup>0)
             $cond.=" AND ro.ans_val='$sup'";

             if(empty($cond))
   $query = "select r.*,DATE_FORMAT(r.posted_date, '%a %M %Y %h:%i %p') as date_added,IFNULL((select DATE_FORMAT(date_added, '%a %M %Y %h:%i %p') from {resource_reply} as wl where wl.rid=r.rid ORDER BY wl.rid ASC LIMIT 0,1),0) as rdate,IFNULL(r.agree,0) as cntagree,IFNULL(r.disagree,0) as cntdisagree from {resource} as r join {user_profile} as u on u.uid=r.uid where r.qid='$qid' AND r.rtype='$rtype' AND status='1' $sortin ";
   else
   $query = "select r.*,DATE_FORMAT(r.posted_date, '%a %M %Y %h:%i %p') as date_added,IFNULL((select DATE_FORMAT(date_added, '%a %M %Y %h:%i %p') from {resource_reply} as wl where wl.rid=r.rid ORDER BY wl.rid ASC LIMIT 0,1),0) as rdate,IFNULL(r.agree,0) as cntagree,IFNULL(r.disagree,0) as cntdisagree from {resource_options} as ro join {resource} as r on ro.rid=r.rid join {user_profile} as u on u.uid=r.uid where r.qid='$qid' AND r.rtype='$rtype' AND status='1' $cond  group by r.rid $sortin ";

   $cnt = ExecuteQuery($query, "select");
    
    if (count($cnt)) {


        foreach ($cnt as $forum) {
            $bg = $i % 2;
            if ($bg)
                $setbg = 'back-col';
            else
                $setbg='';
            $i++;
            $account = user_load($forum['uid']);

            $query = "select * from {debate_options} a,{possible_answer} b where a.paid=b.paid AND a.did='" . $forum['did'] . "'";
            $strnth = ExecuteQuery($query, "select");
            $strength = '';
            $image = !empty($forum['uimg']) ? $forum['uimg'] : file_directory_path() . '/noimage.jpg';
            foreach ($strnth as $list) {
                $ans = $list['answer'];

                switch ($list['ans_val']) {
                    case 0:
                        $strength.='<div class="bottpart">
                                <div class="green"><em>&nbsp;&nbsp;+</em></div>
                                <div class="green-box">' . $ans . '</div>
                                     <div class="clr"></div>
                                     </div>';
                        break;
                    case 1:
                        $strength.='<div class="bottpart">
                                <div class="green"><em>&nbsp;&nbsp;+</em></div>
                                <div class="green-box">' . $ans . '</div>
                                     <div class="clr"></div>
                                     </div>';
                        break;
                    case 2:
                        $strength.='<div class="bottpart">
                                <div class="pink"><em>&nbsp;&nbsp;-</em></div>
                                <div class="pink-box">' . $ans . '</div>
                                     <div class="clr"></div>
                                     </div>';
                        break;
                }
            }

            $wave.='         <div class="debate-summary-wrapper" >
<div class="deb-center">
<div class="leftpartside">
<div class="toppart"><p>' . $forum['cntagree'] . '</p>

<p align="center"><img src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/aggree-hand.jpg" width="18" height="15" alt="Agree" /></p></div>
<div class="toppart2"><p>' . $forum['cntdisagree'] . '</p>
<p align="center"><img src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/disaggree-hand.jpg" width="18" height="15" alt="Agree" /></p>

</div>

</div>


<div class="centerpartside-out">
<div class="centerpartside-top">
<div class="centerpartside">
<div class="form-outer-debate">
<div class="fm-1">&nbsp;</div>
<div class="fm-5">
<div class="leftfm">' . theme('image', $image, t('Resources'), 'Resources', array('width' => '118px', 'height' => '73px'), FALSE) . '</div>
<div class="rightfm">
<a class="debate-links" href="' . $gSitePath . 'resource/debate/' . $qid . '/' . $forum['rid'] . '" >' . myTruncate($forum['udesc'], '50', '', '..') . '</a><br>
<a target="_blank" href="' . $forum['nlink'] . '">' . myTruncate($forum['nlink'], '25', '', '..') . '</a><br>
<br>


' . myTruncate($forum['udesc'], '125', '', '..') . '
</div>



</div>


<div class="clr"></div>
</div>
</div>
<div class="rightpartside">
<a  rel=\'' . $bubble . '\' href="' . $gSitePath . 'profile/' . $account->name . '">' . UserPicture_small($account->uid) . '</a></div>

</div>
<div class="clr"></div>

<div class="centerpartside-bottom">
' . $strength . '

<ul>


<li>Posted : ' . $forum['date_added'] . ' </li>
<div class="clr"></div>
<li>Last Activity: ' . $forum['rdate'] . '</li>


</ul>


</div>


<div class="clr"></div>

</div>

</div>
<div class="deb-bott">
</div>
<div class="clr"></div>

</div>

<div class="clr"></div>
';
        }
    } else {
        $wave.='<div class="messages warning">No Resources Found!</div>';
    }
    return $wave;
}

function resource_media($qid='') {
    global $gSitePath, $user, $gDocPath, $base_root;
    $wave = '';
    $click = '';
    $query = "select *,DATE_FORMAT(r.posted_date, '%a %M %Y %h:%i %p') as date_added,IFNULL((select DATE_FORMAT(date_added, '%a %M %Y %h:%i %p') from {resource_reply} as wl where wl.rid=r.rid ORDER BY wl.rid ASC LIMIT 0,1),0) as rdate,IFNULL((select count(*) from {user_likes} as l where l.node_id=r.rid AND is_resource='1' AND is_agree='1' group by l.node_id),0) as cntagree,IFNULL((select count(*) from {user_likes} as l where l.node_id=r.rid AND is_resource='1' AND is_agree='0' group by l.node_id),0) as cntdisagree from {resource} as r join {user_profile} as u on u.uid=r.uid where r.qid='$qid' AND r.rtype='2' AND status='1' ORDER BY rid DESC ";
    $cnt = ExecuteQuery($query, "select");
    if (count($cnt)) {


        foreach ($cnt as $forum) {
            $bg = $i % 2;
            if ($bg)
                $setbg = 'back-col';
            else
                $setbg='';
            $i++;
            $account = user_load($forum['uid']);

            $query = "select * from {debate_options} a,{possible_answer} b where a.paid=b.paid AND a.did='" . $forum['did'] . "'";
            $strnth = ExecuteQuery($query, "select");
            $strength = '';
            $content = '';
            if ($forum['video_id'] != '') {
                $content.='<div class="form-outer-debate">
<div class="fm-1">&nbsp;</div>
<div class="fm-5">
<div class="leftfm"><a  target="_blank" title="Youtube Video" href="http://www.youtube.com/v/' . $forum['video_id'] . '"  class="floatbox" data-fb-options="width:480 height:384"><img width="125" height="100" src="http://img.youtube.com/vi/' . $forum['video_id'] . '/default.jpg" alt="Video " ></a></div>
<div class="rightfm">
<a class="debate-links" href="' . $gSitePath . 'resource/debate/' . $qid . '/' . $forum['rid'] . '" >' . myTruncate($forum['membed'], '50', '', '..') . '</a><br>
<br>
</div>


</div>


<div class="clr"></div>
</div>';
            } elseif ($forum['document'] != '') {
                $url = explode('/', $forum['document']);
                $content.='<a class="debate-links" href="' . $gSitePath . 'resource/debate/' . $qid . '/' . $forum['rid'] . '" > ' . $url[2] . ' </a> ';
            }
            foreach ($strnth as $list) {
                $ans = $list['answer'];

                switch ($list['ans_val']) {
                    case 0:
                        $strength.='<div class="bottpart">
                                <div class="green"><em>&nbsp;&nbsp;+</em></div>
                                <div class="green-box">' . $ans . '</div>
                                     <div class="clr"></div>
                                     </div>';
                        break;
                    case 1:
                        $strength.='<div class="bottpart">
                                <div class="green"><em>&nbsp;&nbsp;+</em></div>
                                <div class="green-box">' . $ans . '</div>
                                     <div class="clr"></div>
                                     </div>';
                        break;
                    case 2:
                        $strength.='<div class="bottpart">
                                <div class="pink"><em>&nbsp;&nbsp;-</em></div>
                                <div class="pink-box">' . $ans . '</div>
                                     <div class="clr"></div>
                                     </div>';
                        break;
                }
            }

            $wave.='         <div class="debate-summary-wrapper" >
<div class="deb-center">
<div class="leftpartside">
<div class="toppart"><p>' . $forum['cntagree'] . '</p>

<p align="center"><img src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/aggree-hand.jpg" width="18" height="15" alt="Agree" /></p></div>
<div class="toppart2"><p>' . $forum['cntdisagree'] . '</p>
<p align="center"><img src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/disaggree-hand.jpg" width="18" height="15" alt="Agree" /></p>

</div>

</div>


<div class="centerpartside-out">
<div class="centerpartside-top">
<div class="centerpartside">
' . $content . '
</div>
<div class="rightpartside">
<a  rel=\'' . $bubble . '\' href="' . $gSitePath . 'profile/' . $account->name . '">' . UserPicture_small($account->uid) . '</a></div>

</div>
<div class="clr"></div>

<div class="centerpartside-bottom">
' . $strength . '

<ul>


<li>Posted : ' . $forum['date_added'] . ' </li>
<div class="clr"></div>
<li>Last Activity: ' . $forum['rdate'] . '</li>


</ul>


</div>


<div class="clr"></div>

</div>

</div>
<div class="deb-bott">
</div>
<div class="clr"></div>

</div>

<div class="clr"></div>
';
        }
    } else {
       $wave.='<div class="messages warning">No Resources Found!</div>';
    }
    return $wave;
}

function resdebate_list($qid='', $rid='') {
    global $gSitePath, $user, $gDocPath, $base_root;
    if (empty($qid) || !is_numeric($qid) || empty($rid) || !is_numeric($rid)) {
        return FALSE;
    }

    $output = '';
    $like = '';
    $flag = '';
    // resource round up
    resource_roundup($rid);
    $query = "SELECT *,u.uid as uid  FROM {resource} as r  join {user_profile} as u on u.uid=r.uid   where r.qid='$qid' AND r.rid='$rid' AND r.status='1'";
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

        $image = empty($forum['uimg']) ? file_directory_path() . '/noimage.jpg' : $forum['uimg'];
        $name = empty($forum['real_name']) ? $forum['first_name'] : $forum['real_name'];
//likes or not
        $querylike = "select * from {user_likes} where is_resource='1' AND uid='$user->uid' AND node_id='" . $forum['rid'] . "'";
        $fetch = ExecuteQuery($querylike, "select");
        $agreecnt = db_result(db_query("select count(*) from {user_likes} where is_resource='1' AND is_agree='1' AND node_id='" . $forum['rid'] . "'"));
        $disagreecnt = db_result(db_query("select count(*) from {user_likes} where is_resource='1' AND is_agree='0' AND node_id='" . $forum['rid'] . "'"));
        if (count($fetch) < 1) {

            $like = '<li><span name="' . $rid . '" id="dagree" type="is_resource" ><a href="javascript:void(0);" name="a-' . $rid . '" class="dagree">Agree</a>&nbsp;<a name="da-' . $rid . '" href="javascript:void(0);" class="ddisagree">Disagree</a></span></li>';
        } elseif ($fetch[0]['is_agree']) {

            $like = '<li><em>You <strong>agree</strong> with this comment</em></li>';
        } else {
            $like = '<li><em>You <strong>Disagree</strong> with this comment</em></li>';
        }
//flag
        $flag.='<a href="#freport"  class="floatbox flag-menu" title="Report Post" onclick="report_forum(\'resource\',' . $rid . ');"></a>';
        $bubble = load_bubble($account->uid);
        $medal = updateProfileBadge($account->uid);

        if ($forum['rtype'] == '2') {
            if ($forum['mtype'] == '1') {
                $content.='<div class="form-outer-debate">
<div class="fm-1">&nbsp;</div>
<div class="fm-5">
<div class="leftfm"><a  target="_blank" title="Youtube Video" href="http://www.youtube.com/v/' . $forum['video_id'] . '"  class="floatbox" data-fb-options="width:480 height:384"><img width="125" height="100" src="http://img.youtube.com/vi/' . $forum['video_id'] . '/default.jpg" alt="Video " ></a></div>
<div class="rightfm">
<a href="' . $forum['membed'] . '" target="_blank" >' . myTruncate($forum['membed'], '50', '', '..') . '</a><br>
<br>
</div>
</div>
<div class="clr"></div>
</div>';
            } else {
                $url = explode('/', $forum['document']);
                $content.='<a href="' . $gSitePath . '' . $forum['document'] . '" target="_blank"> ' . $url[2] . ' </a> ';
            }
        } else {

            $content.='<div class="form-outer-debate">
                <div class="fm-1">&nbsp;</div>
        <div class="fm-4">
        	<div class="leftfm">' . theme('image', $image, t('Resources'), 'Resources', array('width' => '118px', 'height' => '73px'), FALSE) . '</div>
            <div class="rightfm">
<h5>' . $forum['title'] . '</h5>
' . make_clickable($forum['udesc']) . '
            </div>
      </div>
    <div class="clr"></div>
    </div>
';
        }


        $output .= '

<div class="debate-inn-item">
<div class=" itemto">
<div class="itemto-right">
 ' . $content . '
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
<li><a class="floatbox reply-menu" onclick="addComment(this);" name="rep" title="Reply Post"  id="' . $rid . '-0" href="#postreply"></a></li>
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
    $output .= get_res_debate($rid, 0);


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
<form id="postreplyform" name="freply" action="' . $gSitePath . 'issues/debate/save">
  	<h2>REPLY</h2>

    	<div>
        <textarea rows="10" cols="" name="waveletcmt" id="waveletcmt">Enter text here</textarea>
<!--<input type="checkbox" name="privt" value="1" id="privt"/> Private Reply-->
<input type="hidden" name="fdid" id="fdid" value="' . $rid . '"/>
		<input type="hidden" name="frid" id="frid" value=""/>
                 <input type="hidden" name="qid" id="qid" value="' . $qid . '"/>
			<input type="hidden" name="action" value="resreply" />
        </div>

        <div class="clr"></div>
        	<div class="m-out">
            	<div class="m1"><input type="radio" value="1" CHECKED name="str_wk"/> Strengthen</div>
                <div class="m2"><input type="radio" value="0" name="str_wk"/> Weaken</div>
                   <div align="right" class="m3"><input type="submit" id="waveButton" value="" class="submit-debate-btn"  name="dreply"></div>

            	<div class="clr"></div>
            </div>

</form>


  <div class="clr"></div>
  </div>
<!-- end popup-->
<div class="clr"></div>
<div class="" id="freport" style="display:none;">
<div class="d-header">
 <h3 class="">Report the post</h3>
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
 </div></form>
        <div class="clr"></div>
</div></div>
</div>';
    if (isAjax ()) {
        echo $output;
    } else {

        return $output;
    }
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
                if (!empty($nlink) && empty($udesc)) {

                    require_once('simple_html_dom.php');
                    require_once('thumbnail.php');
                    require_once('url_to_absolute.php');
                    $html = file_get_html($nlink);

                    $udesc = $html->find('title', 0)->innertext;
                }
                //  $resourceadd = "insert into resource(rtype,nlink,ntitle,ncontent,mtype,membed,facts,uid,qid,nimage,document,video_id,udesc,uimg) values ('$rtype','" . addslashes($nlink) . "','" . addslashes($ntitle) . "','" . addslashes($ncontent) . "','" . $mtype . "','" . addslashes($membed) . "','" . addslashes($flink) . "', '" . $user->uid . "','" . $qaid . "','" . $path . "','" . $docpath . "','" . $ytvID . "','" . $udesc . "','" . $files . "')";
                $resourceadd = "insert into resource(rtype,nlink,ntitle,ncontent,mtype,membed,facts,uid,qid,nimage,document,video_id,udesc,uimg) values ('%d','%s','%s','%s','%d','%s','%s', '%d','%d','%s','%s','%s','%s','%s')";
                db_query($resourceadd, $rtype, $nlink, $ntitle, $ncontent, $mtype, $membed, $flink, $user->uid, $qaid, $path, $docpath, $ytvID, $udesc, $files);
                $nid = db_last_insert_id('resource', 'rid');
                   $i = 0;
                foreach ($ans_id as $list) {

                    $forum = "INSERT INTO {resource_options} set rid='%d',paid='%d',ans_val='%d' ";
                    $result = db_query($forum, $nid, $list, $sup_opp[$i]);
                    $i++;
                }
                echo '<div class="messages success"> Resources Added Successfully! </div>';
            }
            break;
        case 'analysis':
            $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
            $vans = "select * from {possible_answer} where  qid=$qid ";
            $vlist = ExecuteQuery($vans, "select");
            $cnt_ans = count($vlist);
            $output.="<link rel='stylesheet' href='" . $gSitePath . drupal_get_path('module', 'quest_lite') . "/plugins/jquery.jqplot.css' type='text/css' />
        <script type='text/javascript' src='" . $gSitePath . "misc/jquery.js'></script>
       			<script type='text/javascript' src='" . $gSitePath . drupal_get_path('module', 'quest_lite') . "/scripts/highcharts.js'></script>
<link rel='stylesheet' href='" . $gSitePath . drupal_get_path('theme', 'heardmentality') . "/css/content.css' type='text/css' />
<script type='text/javascript' language='javascript'>

";
            $insdata.="[";
            $data.="[";

            for ($ab = 0; $ab < $cnt_ans; $ab++) {

                $insdata.="'" . $vlist[$ab]['answer'] . "',";

                $sel = "select * from {debate_options} as o join {debate} as d on d.did=o.did  where o.paid='" . $vlist[$ab]['paid'] . "' AND o.ans_val IN ('1','2') group by o.did";
                $tmplist = ExecuteQuery($sel, "select");
                foreach ($tmplist as $list) {
                 
                    $cnt_opt = db_result(db_query("select count(paid) from {debate_options} where did=" . $list['did'] . " AND ans_val IN ('1','2')"));
             
                     $tmp = ($list['ans_val'] == 1) ? '1' : '-1';
                    $final = $final + (($tmp * $list['strength']) / $cnt_opt);
                }

                $final = (!empty($final)) ? $final : '0';
                $data.=$final . ',';
            }
            $insdata = rtrim($insdata, ',');
            $insdata = $insdata . ']';
            $data = rtrim($data, ',');
            $data = $data . ']';

            $output.= "
var chart;
var gSitePath='" . $gSitePath . "';
$(document).ready(function() {
   chart = new Highcharts.Chart({
      chart: {
         renderTo: 'container',
         defaultSeriesType: 'column'
      },
      title: {
         text: 'Debate Report Analysis'
      },
      xAxis: {
         categories:" . $insdata . "
      },
      yAxis:{ tickInterval  :1
    },
      tooltip: {
         formatter: function() {
            return ''+
                this.series.name +': '+ this.y +'';
         }
      },
      credits: {
         enabled: false
      },
      series: [{
         name: 'Strength',
         data: " . $data . "
      }]
   });


});

 </script>";
            echo $output.='<div id="container" class="highcharts-container" style="height:auto; width: 400px; margin: 0 auto; clear:both"></div>
        <div id="resource" style="height:auto; width: 400px; margin: 0 auto; clear:both"></div>

';
            break;
        case 'resanalysis':
            $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
            $vans = "select * from {possible_answer} where  qid=$qid ";
            $vlist = ExecuteQuery($vans, "select");
            $cnt_ans = count($vlist);
            $output.="<link rel='stylesheet' href='" . $gSitePath . drupal_get_path('module', 'quest_lite') . "/plugins/jquery.jqplot.css' type='text/css' />
        <script type='text/javascript' src='" . $gSitePath . "misc/jquery.js'></script>
       			<script type='text/javascript' src='" . $gSitePath . drupal_get_path('module', 'quest_lite') . "/scripts/highcharts.js'></script>
<link rel='stylesheet' href='" . $gSitePath . drupal_get_path('theme', 'heardmentality') . "/css/content.css' type='text/css' />
<script type='text/javascript' language='javascript'>

";
            $insdata.="[";
            $data.="[";

            for ($ab = 0; $ab < $cnt_ans; $ab++) {

                $insdata.="'" . $vlist[$ab]['answer'] . "',";

                $sel = "select * from {resource_options} as o join {resource} as d on d.rid=o.rid  where o.paid='" . $vlist[$ab]['paid'] . "' AND o.ans_val IN (1,2) group by o.rid";
                $tmplist = ExecuteQuery($sel, "select");
                foreach ($tmplist as $list) {
                    $cnt_opt = db_result(db_query("select count(paid) from {resource_options} where rid=" . $list['rid'] . " AND ans_val IN (1,2) group by paid"));
                    $tmp = ($list['ans_val'] == 1) ? '1' : '-1';
                    $final = $final + (($tmp * $list['strength']) / $cnt_opt);
                }

                $final = (!empty($final)) ? $final : '0';
                $data.=$final . ',';
            }
            $insdata = rtrim($insdata, ',');
            $insdata = $insdata . ']';
            $data = rtrim($data, ',');
            $data = $data . ']';

            $output.= "
var chart;
var gSitePath='" . $gSitePath . "';
$(document).ready(function() {
   chart = new Highcharts.Chart({
      chart: {
         renderTo: 'container',
         defaultSeriesType: 'column'
      },
      title: {
         text: 'Resource Report Analysis'
      },
      xAxis: {
         categories:" . $insdata . "
      },
      yAxis:{ tickInterval  :1
    },
      tooltip: {
         formatter: function() {
            return ''+
                this.series.name +': '+ this.y +'';
         }
      },
      credits: {
         enabled: false
      },
      series: [{
         name: 'Strength',
         data: " . $data . "
      }]
   });


});

 </script>";
            echo $output.='<div id="container" class="highcharts-container" style="height:auto; width: 400px; margin: 0 auto; clear:both"></div>
        <div id="resource" style="height:auto; width: 400px; margin: 0 auto; clear:both"></div>

';

            break;
      case 'debatelist':
          $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
          echo $output = debate_wave($qid);
          break;
      case 'dreport':
         $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
            echo '<iframe style="min-height:320px;" id="frmGoogle" src="' . $gSitePath . '/debate/ajax/'.$qid.'?action=analysis" border="0" frameborder="0" width="100%"></iframe>';
          break;
      case 'resreport':
         $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
            echo '<iframe style="min-height:320px;" id="frmGoogle" src="' . $gSitePath . '/debate/ajax/'.$qid.'?action=resanalysis" border="0" frameborder="0" width="100%"></iframe>';
          break;
      case 'filter':
              $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
           echo list_debate($qid, 1);
          break;
      case 'resfilter':
           $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
          extract($_REQUEST);
          switch($type){
            case 'innews':
            $output.= resource_innews($qid, 1);
            break;
        case 'media':

            $output.= resource_media($qid);
            break;
        case 'facts':


            $output.= resource_innews($qid, 3);
            break;
        default:
            $output = '<div class="messages warning">No Action Found!</div>';
            break;

          }
          echo $output;
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
    $user_coins  = db_result(db_query("SELECT total_coins FROM {users} WHERE uid = '$user->uid'"));
    switch ($action) {

        case 'new':
            if (!empty($wtitle) && !empty($user->uid)) {
                $lose_coins = get_coins('c_debate');
                if($user_coins >= $lose_coins)
                {
                $forum = "INSERT INTO {debate} set qid='%d',type='1',uid='%d',title='%s',content='%s',private='%d' ";
                $result = db_query($forum, $qid, $user->uid, $wtitle, $wcon, $wprivate);

                $nid = db_last_insert_id('debate', 'did');
                ;
                $i = 0;
// add coin for Create new debates
                $coin_type = 'c_debate';
                users_coins_update($user->uid,'',$coin_type);
                
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
                    '@username' => l(user_load($user->uid)->name, 'profile/' . $user->name),
                    //'@node_type' => 'page',
                    '@debate_title' => "<a href='$base_url/$question_urlff' >" . $qtion . "</a>",
                );
                heartbeat_api_log($message_id, $user->uid, $question_urlff, $qid, $question_urlff, $variables);
                /* RAM HEARTBEAT MODULE INSERT DEBATE */
                send_forumnotify($nid, $qid);
                }else{
                    echo '<div align="center"><b>Sorry you do not have enough coins to post New Debate</b></div>';
                }
            } elseif (isset($wtitle)) {
                echo '<div align="center"><b>Sorry Only Logged in user can post New Debate</b></div>';
                echo list_debate($qid, 1);
            }
            break;
        case 'reply':
            $lose_coins = get_coins('p_debate');
            if($user_coins >= $lose_coins)
            {
            $query = "insert into {debate_reply} set did='%d',uid='%d',parentid='%d',str_wk='%d',reply='%s',private='%s'";
            $result = db_query($query, $fdid, $user->uid, $frid, $str_wk, check_plain($waveletcmt), $pvt);
            $rid = db_last_insert_id('debate_reply', 'rid');
            echo $output = get_debate($fdid, 0);
            post_notification($fdid, $rid);

// add coin for participate in debate debates
                $coin_type = 'p_debate';
                users_coins_update($user->uid,'',$coin_type);

            /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */
            $qid_url = db_query("select * from {question} where qid='$qid'");
            $question_values = db_fetch_array($qid_url);
            if (isset($question_values)) {
                $question_urlff = $question_values['url'] . '/' . $fdid;
                $qtion = $question_values['question'];
                $ctxt = $question_values['context'];
            }
            $message_id = 'debate_reply';
            $variables = array(
                '@username' => l(user_load($user->uid)->name, 'profile/' . $user->name),
                '@debate_title' => "<a href='$base_url/$question_urlff' >" . $qtion . "</a>",
            );
            heartbeat_api_log($message_id, $user->uid, $question_urlff, $qid, $question_urlff, $variables);
            /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */
            }else{
              echo '<div align="center"><b>Sorry you do not have enough coins to reply for this post</b></div>';
            }
            break;
        case 'resreply':
            $query = "insert into {resource_reply} set rid='%d',uid='%d',parentid='%d',str_wk='%d',reply='%s',private='%s'";
            $result = db_query($query, $fdid, $user->uid, $frid, $str_wk, check_plain($waveletcmt), $pvt);
            $rid = db_last_insert_id('resource_reply', 'rid');
            echo $output = get_res_debate($fdid, 0);
            post_notification($fdid, $rid);
            /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */
            $qid_url = db_query("select * from {question} where qid='$qid'");
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
        case 'is_resource':
        case 'is_resource_reply':
            $cond = " AND " . $action . "='1'";
            $set = " " . $action . "='1'";

            $query = "select * from {user_likes} where node_id='$nodeid' $cond AND uid='$user->uid'";

            $chk = db_result(db_query($query));

            if (!$chk && $user->uid > 0) {
                $lose_coins = $agree==1?get_coins('agree'):get_coins('disagree');
                if($user_coins >= $lose_coins)
                {
                $query = "insert into {user_likes} set $set ,node_id='$nodeid',uid='$user->uid',is_agree='$agree'";

                $chk = db_query($query);
// add coin for agree and disagree
                $coin_type = $agree=='1'?'agree':'disagree';
                users_coins_update($user->uid,'',$coin_type);
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
                        '@username' => l(user_load($user->uid)->name, 'profile/' . $user->name),
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
                        '@username' => l(user_load($user->uid)->name, 'profile/' . $user->name),
                        '@debate_title' => "<a href='$base_url/$question_urlff' >" . $qtion . "</a>",
                    );
                    heartbeat_api_log($message_id, $user->uid, $question_urlff, $qid, $question_urlff, $variables);
                    /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */
                }
                $msg['error'] = '0';
                }else {
                    $msg['msg'] = '<em>Sorry <strong>Error, You do not have enough coins.</strong></em>';
                }
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
function users_coins_update($uid = '',$bid,$keyname){
    if($bid!=''){
    $keyname = db_result(db_query("SELECT btype FROM {badges} WHERE bid = '$bid'"));
    }
    $sql = "SELECT * FROM {tbl_coins} WHERE key_name = '$keyname'";
    $coins = ExecuteQuery($sql,'select');
    foreach($coins as $coin){
        $coin_count = $coin['coin_count'];
        $coin_type = $coin['type'];
    }
    $insert = "INSERT INTO {user_coins} SET coin_key = '%s', coin_type = '%s', coin_count = '%d', uid = '%d'";
    db_query($insert,$keyname,$coin_type,$coin_count,$uid);

    // update total coins
    $user_coins  = db_result(db_query("SELECT total_coins FROM {users} WHERE uid = '$uid'"));
    if($coin_type == 'earn'){
        $total_coins = $user_coins + $coin_count;
    }
    if($coin_type == 'lose'){
         $total_coins = $user_coins - $coin_count;
    }
    db_query("UPDATE {users} SET total_coins = '%d' WHERE uid = '$uid'",$total_coins);
}
function get_coins($key)
{
    $coins = db_result(db_query("SELECT coin_count FROM {tbl_coins} WHERE key_name = '$key'"));
    return $coins;
}