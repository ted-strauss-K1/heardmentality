<?php

function debate_list($qid = '', $did='') {

    global $gSitePath, $user, $gDocPath, $base_root, $language;
    $curLanguage = $language->language;

    // site url with default language
    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';
    //$gSitePath = $sitelink;

    // translated node title, body for a debate
    $tnid = get_tnid($did);
    $did = $tnid;

    // main node for a question
    $issuId = $qid;
    $tqid = get_tnid($qid);
    $qid = $tqid;
    
    
    if (empty($qid) || !is_numeric($qid) || empty($did) || !is_numeric($did)) {
        return FALSE;
    }
    $output = '';
    $like = '';
    $flag = '';
// get nid for respective did
    //$nodeid = db_result(db_query("SELECT nid FROM {debate} WHERE did = '%d'", $did));
    //$query = "SELECT *,u.uid as uid,IFNULL((select did  FROM {debate} where did > f.did AND qid='$qid'  limit 0,1 ),0) as pdid,IFNULL((select did FROM {debate} where did < f.did AND qid='$qid' order by did DESC limit 0,1 ),0) as ndid  FROM {debate} as f  join {user_profile} as u on u.uid=f.uid   where f.qid='$qid' AND f.did='$did' AND f.status='1'";
    //$list = ExecuteQuery($query, "select");
    $forum = node_load($did);

    /*******************/
    // translated content for title and body
    $translated = get_translated_content_forum($issuId, $forum->nid, $curLanguage);
    $forum->title = $translated->title;
    $forum->body = $translated->body;
    ///*******************/

    $dlink = $gSitePath . 'issues/debate/';

//    foreach ($list as $forum) {

    if ($forum->pdid > 0) {
        $prev = $dlink . $qid . '/' . $forum->pdid;
        $set_p_link = '<li><a  href="' . $prev . '" class="previous"  onclick="switchdebate(this.href);return false;" >Previous Debate</a></li>';
    }
    if ($forum->ndid > 0) {
        $next = $dlink . $qid . '/' . $forum->ndid;
        $set_n_link = '   <li><a   href="' . $next . '" class="next"  onclick="switchdebate(this.href);return false;" >Next Debate</a></li>';
    }
    $output .= '<div class="popup-debate">
       <div class="hm-debate2-wrapper">
    	<div class="titlebg">
        	<div class="menudebate">
            	<ul>' . $set_p_link . $set_n_link . '
    </ul>
            </div>

            	<div class="backbtn"><a href="javascript:void(0);" onclick="fb.end();"></a></div>
                	<h2>' . $forum->title . '</h2>
        <div class="clr"></div>
        </div>


        <div class="clr"></div>
            <div class="hm-debate-cont-outer backping">

           <h3> Debate Title Coming here...</h3>

                        <div>

                        <hr class="hr-silver"/>

<div align="center" id="waveerr"></div>
';

//$date = cdatetime($forum['date_added']).$forum['date_added'];
    $posted = date("Y-m-d H:i:s", $forum->created);
    $date = format_date_class($posted, date());
    $account = user_load($forum->uid);
    //$image = empty($forum['image']) ? 'noimage.jpg' : $forum['image'];
    //$name = empty($forum['real_name']) ? $forum['first_name'] : $forum['real_name'];
//likes or not       
    $querylike = "SELECT * FROM {votingapi_vote} WHERE content_type = 'node' AND uid = '$user->uid' AND content_id = '$forum->nid'";
    $fetch = ExecuteQuery($querylike, "select");
    //$querylike = "select * from {user_likes} where is_debate='1' AND uid='$user->uid' AND node_id='" . $forum['did'] . "'";
    //$fetch = ExecuteQuery($querylike, "select");

    $criteriaUpNode = array('content_type' => 'node',
        'content_id' => $forum->nid,
        'tag' => 'vote',
        'vote_type' => 'up');
    $criteriaDownNode = array('content_type' => 'node',
        'content_id' => $forum->nid,
        'tag' => 'vote',
        'vote_type' => 'down');
    $agreecnt = vote_up_down_count($criteriaUpNode);
    $disagreecnt = vote_up_down_count($criteriaDownNode);

    //$agreecnt = db_result(db_query("SELECT COUNT(*) FROM {votingapi_vote} WHERE content_type = '%s' AND content_id = '%d' AND value = '%d'", 'node', $forum->nid,  '1'));
    //$disagreecnt = db_result(db_query("SELECT COUNT(*) FROM {votingapi_vote} WHERE content_type = '%s' AND content_id = '%d' AND value = '%d'", 'node', $forum->nid, '-1'));
    //$agreecnt = db_result(db_query("select count(*) from {user_likes} where is_debate='1' AND is_agree='1' AND node_id='" . $forum['did'] . "'"));
    //$disagreecnt = db_result(db_query("select count(*) from {user_likes} where is_debate='1' AND is_agree='0' AND node_id='" . $forum['did'] . "'"));
    if ($user->uid != $forum->uid) {

        if (count($fetch) < 1) {
            $imgpath = $gSitePath.drupal_get_path('theme', 'newtheme').'/images/';
            $likeImg = '<img src="'.$imgpath.'likebig.png" title="like" />';
            $dislikeImg = '<img src="'.$imgpath.'dislike.png" title="dislike" />';
            $like = '<li id="lik-btns-node-'.$forum->nid.'"><span type="is_debate" name="' . $did . '" id="dagree" ><a href="javascript:void(0);" name="a-' . $did . '" class="dagree">'.$likeImg.'</a>&nbsp;<a name="da-' . $did . '" href="javascript:void(0);" class="ddisagree">'.$dislikeImg.'</a></span></li>';
        } elseif ($fetch[0]['is_debate'] == '1' && $fetch[0]['is_agree']) {

            $like = '<li><em>You <strong>agree</strong> with this comment</em></li>';
        } else {
            $like = '<li><em>You <strong>Disagree</strong> with this comment</em></li>';
        }
    } else {
        $like = '<li></li>';
    }

    // like bar percent calculation
                
                $like.= '<li id="bar-area-node-'.$forum->nid.'">'.like_dislike_bar($agreecnt, $disagreecnt).'</li>';

//flag
    if (user_is_logged_in ()) {
        $replybutton = '<a class="floatbox reply-menu" onclick="addComment(this);" name="rep" title="Reply Post"  id="' . $did . '-0" href="#postreply"></a>';
        //$flag.='<a name="' . $did . '-0" href="#freport"  class="floatbox flag-menu" title="Report Post" onclick="report_forum(\'debate\',this);"></a>';
        $flag.='<a name="' . $did . '-0" href="javascript:void(0);"  class="flag-menu" title="Report Post" onclick="loadflagresdeb(\''.$gSitePath.'qlite/flag/'.$did.'\', \'Report\');"></a>';
    } else {
        $replybutton = '<a class=" reply-menu" onclick="check_popup_login();" name="rep" title="Reply Post"  id="' . $did . '-0" href="#postreply"></a>';
        $flag.='<a name="' . $did . '-0" href="#freport"  class=" flag-menu" title="Report Post" onclick="check_popup_login();"></a>';
    }

    $bubble = load_bubble($account->uid);

    $output .= '

<div class="debate-inn-item">
<div class=" itemto">
<div class="itemto-right">
<h5>' . $forum->title . '</h5>
' . make_clickable($forum->body) . '
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
<li>' . $replybutton . '</li>
<li>' . $flag . '</li>
</ul>
</div>
<div class="itemthird">
' . load_user_badge($account->uid) . '
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
//    }
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
    <input type="hidden" name="qid" id="qid" value="' . $qid . '" />
		<input type="hidden" name="frid" id="frid" value="" />
		<input type="hidden" name="action" value="reply" />
                <input type="hidden" name="nodeid" value="' . $did . '" />
                <input type="hidden" name="comid" id="comid" value=""/>
        </div>

        <div class="clr"></div>
        	<div class="m-out">
            	<div class="m1"><input type="radio" value="1" CHECKED name="str_wk"/> Strengthen</div>
                <div class="m2"><input type="radio" value="0" name="str_wk"/> Weaken</div>
                 <div align="right" class="m3"><input type="submit" id="waveButton" value="" class="submit-debate-btn" ' . $chkuser . '  name="dreply"></div>

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

	<input type="hidden" value="" id="rwave" name="did"/>
	<input type="hidden" value="" id="rwavelet" name="rdid"/>
	

<div class="adcomment-outer">
	' . report_theme() . '<p>
	  or <a href="javascript:void(0);" onclick="parent.fb.end();" id="wavecancel1" href="">cancel</a>
        </p>
       
	</div>
         <div class="clr"></div>
</form> </div>
        <div class="clr"></div>
</div></div>
</div> </div>';
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
    global $gSitePath, $user, $gDocPath, $base_root, $language;
    $output = '';
    $bg = '';
    $curLanguage = $language->language;
    if (!empty($did)) {

        //$query = "select * from {debate_reply} as f  join {user_profile} as u on u.uid=f.uid  where f.did='$did' and f.status='1' and parentid='$pid'";
        $query = "SELECT * FROM {comments} as c where c.nid='$did' and c.status='0' and c.pid='$pid' AND (c.cid = c.tcid OR c.tcid = 0)";
        $list = ExecuteQuery($query, "select");

//print_r($set);

        foreach ($list as $forum) {
            $cid = $forum['cid'];

            // get language translated comment
            $translated = get_translated_comment($cid, $curLanguage);
            $forum['comment'] = $translated;

// $date = cdatetime($forum['date_added']).$forum['date_added'];
            //$date = format_date_class($forum['date_added'], date());
            $posted = date("Y-m-d H:i:s", $forum['timestamp']);
            $date = format_date_class($posted, date());
            $account = user_load($forum['uid']);


            if (wave_access($forum['cid'], $forum['private'])) {

                //$image = empty($forum['image']) ? 'noimage.jpg' : $forum['image'];
                //$name = empty($forum['real_name']) ? $forum['first_name'] : $forum['real_name'];

                $querylike = "SELECT * FROM {votingapi_vote} WHERE content_type = 'comment' AND uid = '$user->uid' AND content_id = '" . $forum['cid'] . "'";
                $fetch = ExecuteQuery($querylike, "select");

                $criteriaUp = array('content_type' => 'comment',
                    'content_id' => $forum['cid'],
                    'tag' => 'vote',
                    'vote_type' => 'up');
                $criteriaDown = array('content_type' => 'comment',
                    'content_id' => $forum['cid'],
                    'tag' => 'vote',
                    'vote_type' => 'down');
                $cntagree = vote_up_down_count($criteriaUp);
                $cntdisagree = vote_up_down_count($criteriaDown);

                //$cntagree = db_result(db_query("SELECT COUNT(*) FROM {votingapi_vote} WHERE content_type = '%s' AND content_id = '%d' AND value = '%d'", 'comment', $forum['cid'], '1'));
                //$cntdisagree = db_result(db_query("SELECT COUNT(*) FROM {votingapi_vote} WHERE content_type = '%s' AND content_id = '%d' AND value = '%d'", 'comment', $forum['cid'], '-1'));
                //$cntagree = db_result(db_query("select count(*) from {user_likes} where is_debate_reply='1' AND is_agree='1' AND node_id='" . $forum['rid'] . "'"));
                //$cntdisagree = db_result(db_query("select count(*) from {user_likes} where is_debate_reply='1' AND is_agree='0' AND node_id='" . $forum['rid'] . "'"));
                if ($user->uid != $forum['uid']) {
                    if (count($fetch) < 1) {
                        $imgpath = $gSitePath.drupal_get_path('theme', 'newtheme').'/images/';
                        $likeImg = '<img src="'.$imgpath.'likebig.png" title="like" />';
                        $dislikeImg = '<img src="'.$imgpath.'dislike.png" title="dislike" />';
                        $like = '<li id="lik-btns-comment-'.$forum['cid'].'"><span name="' . $forum['cid'] . '" type="is_debate_reply" id="dragree" ><a href="javascript:void(0);" name="a-' . $forum['cid'] . '" class="ragree"">'.$likeImg.'</a>&nbsp;<a name="da-' . $forum['cid'] . '" href="javascript:void(0);" class="rdisagree">'.$dislikeImg.'</a></span></li>';
                    } elseif ($fetch[0]['value'] == '1') {

                        $like = '<li><em>You <strong>agree</strong> with this comment</em></li>';
                    } else {
                        $like = '<li><em>You <strong>Disagree</strong> with this comment</em></li>';
                    }
                        
                } else {
                    $like = '<li></li>';
                }
                // like bar percent calculation
                
                $like.= '<li id="bar-area-comment-'.$forum['cid'].'">'.like_dislike_bar($cntagree, $cntdisagree).'</li>';
//flag
                $flag = '';

                // $flag.='<a name="' . $did . '-' . $forum['cid'] . '" href="#freport" class="floatbox flag-menu" onclick="report_forum(\'debate_reply\',this);"></a>';

                if (user_is_logged_in ()) {
                    $replybutton = '<a class="floatbox reply-menu" onclick="addComment(this);" id="' . $did . '-' . $forum['cid'] . '"  href="#postreply"></a>';
                    //$flag.='<a name="' . $did . '-' . $forum['cid'] . '" href="#freport" class="floatbox flag-menu" onclick="report_forum(\'debate_reply\',this);"></a>';
                    $flag.='<a name="' . $did . '-' . $forum['cid'] . '" href="#freport" class="flag-menu" onclick="loadflagresdeb(\''.$gSitePath.'qlite/flag/comment/'.$forum['cid'].'\', \'Report\');"></a>';
                    
                } else {
                    $replybutton = '<a class=" reply-menu" onclick="check_popup_login();" name="rep" title="Reply Post"  id="' . $did . '-0" href="#postreply"></a>';
                    $flag.='<a  href="#freport"  class=" flag-menu" title="Report Post" onclick="check_popup_login();"></a>';
                }

                $medal = updateProfileBadge($account->uid);
                $bubble = load_bubble($account->uid);
                if ($forum['str_wk'])
                    $plus = '<a href="#"><img width="23" height="23" alt="Strengthen" src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/plus-img.jpg"></a>';
                else
                    $plus='<a href="#"><img width="23" height="23" alt="Weaken" src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/minus-img.jpg"></a>';

                $output .= '<div class="clr"></div>
<div class="hm-debate-cont-outer backash com-' . $forum['cid'] . '"">
' . $plus . '
<div>



<hr class="hr-silver-2"></hr>

<div class="debate-inn-item">
<div class=" itemto">
<div class="itemto-right">
<div class="form-outer-debate">
<div class="fm-1">&nbsp;</div>
<div class="fm-4">
' . make_clickable($forum['comment']) . '
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

<li><a class="floatbox reply-menu" onclick="addComment(this);" id="' . $did . '-' . $forum['cid'] . '"  href="#postreply"></a></li>

<li>' . $flag . '</li><li>' . $date . '</li>
</ul>
</div>

<div class="itemthird">

' . load_user_badge($account->uid) . '


</div>
<div class="clr"></div>
';
                $output .= get_debate($did, $forum['cid']);

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

    global $gSitePath, $user, $gDocPath, $base_root, $language;
    $curLanguage = $language->language;
    $output = '';
    $bg = '';
    if (!empty($rid)) {


        //$query = "select * from {resource_reply} as f  join {user_profile} as u on u.uid=f.uid  where f.rid='$rid' and f.status='1' and parentid='$pid'";
        $query = "SELECT * FROM {comments} as c where c.nid='$rid' and c.status='0' and c.pid='$pid' AND (c.cid = c.tcid OR c.tcid = 0) ";
        $list = ExecuteQuery($query, "select");

//print_r($set);

        foreach ($list as $forum) {

            $cid = $forum['cid'];

            // get language translated comment
            $translated = get_translated_comment($cid, $curLanguage);
            $forum['comment'] = $translated;

// $date = cdatetime($forum['date_added']).$forum['date_added'];
            $posted = date("Y-m-d H:i:s", $forum['timestamp']);
            $date = format_date_class($posted, date());
            $account = user_load($forum['uid']);


            if (wave_access($forum['cid'], $forum['private'])) {

                //$image = empty($forum['image']) ? 'noimage.jpg' : $forum['image'];
                //$name = empty($forum['real_name']) ? $forum['first_name'] : $forum['real_name'];
//                $querylike = "select * from {user_likes} where is_resource_reply='1' AND uid='$user->uid' AND node_id='" . $forum['reid'] . "'";
//                $fetch = ExecuteQuery($querylike, "select");
//                $cntagree = db_result(db_query("select count(*) from {user_likes} where is_resource_reply='1' AND is_agree='1' AND node_id='" . $forum['reid'] . "'"));
//                $cntdisagree = db_result(db_query("select count(*) from {user_likes} where is_resource_reply='1' AND is_agree='0' AND node_id='" . $forum['reid'] . "'"));

                $querylike = "SELECT * FROM {votingapi_vote} WHERE content_type = 'comment' AND uid = '$user->uid' AND content_id = '" . $forum['cid'] . "'";
                $fetch = ExecuteQuery($querylike, "select");

                $criteriaUp = array('content_type' => 'comment',
                    'content_id' => $forum['cid'],
                    'tag' => 'vote',
                    'vote_type' => 'up');
                $criteriaDown = array('content_type' => 'comment',
                    'content_id' => $forum['cid'],
                    'tag' => 'vote',
                    'vote_type' => 'down');
                $cntagree = vote_up_down_count($criteriaUp);
                $cntdisagree = vote_up_down_count($criteriaDown);

                if ($user->uid != $forum['uid']) {
                    if (count($fetch) < 1) {
                        $imgpath = $gSitePath.drupal_get_path('theme', 'newtheme').'/images/';
                        $likeImg = '<img src="'.$imgpath.'likebig.png" title="like" />';
                        $dislikeImg = '<img src="'.$imgpath.'dislike.png" title="dislike" />';
                        $like = '<li id="lik-btns-comment-'.$forum['cid'].'"><span type="is_resource_reply" name="' . $forum['cid'] . '" id="dragree" ><a href="javascript:void(0);" name="a-' . $forum['cid'] . '" class="ragree"">'.$likeImg.'</a>&nbsp;<a name="da-' . $forum['cid'] . '" href="javascript:void(0);" class="rdisagree">'.$dislikeImg.'</a></span></li>';
                    } elseif ($fetch[0]['value'] == '1') {

                        $like = '<li><em>You <strong>agree</strong> with this comment</em></li>';
                    } else {
                        $like = '<li><em>You <strong>Disagree</strong> with this comment</em></li>';
                    }
                } else {
                    $like = '<li></li>';
                }
                // like bar percent calculation
                
                $like.= '<li id="bar-area-comment-'.$forum['cid'].'">'.like_dislike_bar($cntagree, $cntdisagree).'</li>';
//flag
                $flag = '';

                //$flag.='<a  href="#freport" class="floatbox flag-menu" onclick="report_forum(\'rresource\',' . $forum['cid'] . ');"></a>';

                if (user_is_logged_in ()) {
                    $replybutton = '<a class="floatbox reply-menu" onclick="addComment(this);" id="' . $rid . '-' . $forum['cid'] . '"  href="#postreply"></a>';
                    //$flag.='<a name="' . $rid . '-' . $forum['reid'] . '" href="#freport" class="floatbox flag-menu" onclick="report_forum(\'rresource\',this);"></a>';
                    $flag.='<a name="' . $rid . '-' . $forum['cid'] . '" href="javascript:void(0);" class="flag-menu" onclick="loadflagresdeb(\''.$gSitePath.'qlite/flag/comment/'.$forum['cid'].'\', \'Report\');"></a>';
                } else {
                    $replybutton = '<a class=" reply-menu" onclick="check_popup_login();" name="rep" title="Reply Post"  id="' . $rid . '-' . $forum['reid'] . '" href="#postreply"></a>';
                    $flag.='<a  href="#freport"  class=" flag-menu" title="Report Post" onclick="check_popup_login();"></a>';
                }



                $medal = updateProfileBadge($account->uid);
                $bubble = load_user_badge($account->uid);
                if ($forum['str_wk'])
                    $plus = '<a href="#"><img width="23" height="23" alt="Strengthen" src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/plus-img.jpg"></a>';
                else
                    $plus='<a href="#"><img width="23" height="23" alt="Weaken" src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/minus-img.jpg"></a>';

                $output .= '<div class="clr"></div>
<div class="hm-debate-cont-outer backash com-' . $forum['cid'] . '"">
' . $plus . '
<div>



<hr class="hr-silver-2"></hr>

<div class="debate-inn-item">
<div class=" itemto">
<div class="itemto-right">
<div class="form-outer-debate">
<div class="fm-1">&nbsp;</div>
<div class="fm-4">
' . make_clickable($forum['comment']) . '
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

<li><a class="floatbox reply-menu" onclick="addComment(this);" id="' . $rid . '-' . $forum['cid'] . '"  href="#postreply"></a></li>

<li>' . $flag . '</li><li>' . $date . '</li>
</ul>
</div>

<div class="itemthird">


' . $bubble . '


</div>
<div class="clr"></div>
';
                $output .= get_res_debate($rid, $forum['cid']);

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

    // site url with default language
    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';
    $gSitePath = $sitelink;


    $ans = load_options($qid);
    drupal_add_js('var spath="' . $gSitePath . '";', 'inline');
    drupal_add_css(drupal_get_path('module', 'debate') . '/css/fileuploader.css');
    drupal_add_js(drupal_get_path('module', 'debate') . '/scripts/fileuploader.js');
    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/jquery.blockUI.js');
    drupal_add_js(drupal_get_path('module', 'debate') . '/scripts/add_resource.js');


    //answers
    foreach ($ans as $list) {
        $short_answer = get_short_answer($qid, $list['chorder']);
        $answer = $short_answer!=''?$short_answer:$list['chtext'];

        $inc_pans.='
	<div class="debate-r-row">
        <div class="fm-2">
        <div class="fm-2-left">' . $answer . ' </div>
<div class="fm-2-right">

            <input type="hidden" name="ans_id[]" value="' . $list['chorder'] . '"/><select  name="sup_opp[]"><option value="0">Neutral</option><option  value="1">Supports</option><option value="2">Oppose</option></select>
              </div>
        </div>




    <div class="clr"></div>
    </div>
    		';
    }

    $resources .= '

              <div class="popup-resource-new">         <div class="" id="err">' . $list_err . '</div>
    <div class="">
        <form id="myForm" name="myForm"  method="post" action="' . $gSitePath . 'debate/ajax" enctype="multipart/form-data" >
            <input type="hidden" name="qaid" value="' . $qid . '"/>
             <input type="hidden" name="action" value="resource_new"/>

<div class="debate-l">
    <div class="fm-1">Please Follow the <a href="#">Principles and Guidelines.</a></div>
    <div class="fm-1">All debates should be:<br />
            <ul>
            <li>Concise</li>
            <li>Etc</li>
            </ul>
    </div>
</div>
<div class="debate-r">
    <div class="debate-r-row">
        <div class="fm-2">   <select name="rtype" class="listbox1" id="rtype" >
	<option value="0">Resource Type </option>
	<option value="1">News </option>
	<option value="2">Multimedia </option>
	<option value="3">Facts </option>
	</select></div>
    </div>

    <div id="div1" style="display:none;"  class="debate-r-row"><input type="text" class="" style="float:left; padding:3px;"  name="nlink" value="http://" id="nlink"/> <div><input id="lattach" name="name" type="button" value="Attach"  style="float:left; width:50px; padding:1px;"/></div></div>
    <div id="div2" style="display:none;"  class="debate-r-row"><select name="mtype" class="listbox1" id="mtype"   >
    <option value="0">Choose Format </option>
    <option value="1">Web Video </option>
    <option value="2">Podcast,PDF, DOC, PPT. </option>
    </select>
    </div>
    
    <div id="media" style="display:none;"  class="debate-r-row"> <input type="text"  name="membed" id="membed" value="http://"  class="" ></div>
    <div id="media_div" style="display:none;"  class="debate-r-row">
    <input type="hidden" name="docpath" id="docpath"/> <div id="file-uploader-demo1"> </div>
    </div>
    <div class="debate-r-row" id="linkbox"></div>



 ' . $inc_pans . '
     	<div class="debate-r-row">
          <div class="fm-2">
        <div class="fm-2-right" align="right"><input name="submit" value="" type="submit" id="submitter" class="submit-debate-btn"/></div>
        </div>
    <div class="clr"></div>
    </div>
</div>

</form>
      <div class="clr"></div>
  </div>
</div>

</body>


      
';

    if (!user_is_logged_in()) {
        $resources = '<div class="warning">Please log in to post a reference!</div><script>jQuery(document).ready(function() {jQuery(\'#twitMsg\',top.document).html("Please log in to post a reference!");
        jQuery(\'#twitMsg\',top.document).delay(400).slideDown(400).delay(3000).slideUp(400); }); </script>';
    }

    return $resources;
}

function resource_list($type, $qid) {
    global $gSitePath, $user, $gDocPath, $base_root;
    $output = '';
    $ans = load_options($qid);
    //answers
    $filter_list.='<select name="rfilt-ans" id="rfilt-ans" class="select-1"><option value="">Possible Answers</option>';
    foreach ($ans as $list) {

        $short_answer = get_short_answer($qid, $list['chorder']);
        $answer = $short_answer!=''?$short_answer:$list['chtext'];

        $filter_list.='<option value="' . $list['chorder'] . '">' . $answer . '</option>';
        $inc_pans.='<div class="form-outer-debate">
    	<div class="fm-1">&nbsp;</div>
        <div class="fm-2">
        <div class="fm-2-left">' . $answer . '</div>
        <div class="fm-2-right"><input type="hidden" name="ans_id[]" value="' . $list['chorder'] . '"/><select  name="sup_opp[]"><option value="0">Neutral</option><option  value="1">Supports</option><option value="2">Oppose</option></select></div>
        </div>
        <div class="clr"></div>
    </div>';
    }
    $filter_list.='</select>';
    //print_r($cnt);
    if (user_is_logged_in ())
        $rbutton = '<a href="javascript:void(0);" onclick="javascript:loadresource(\'' . $gSitePath . 'debate/resource/new/' . $qid . '\',\'Add\');" title="New Debate"><input name="" type="button"   class="submit-debate-btn"/></a>';
    else
        $rbutton='<a href="javascript:void(0);" onclick="javascript:check_popup_login();" title="New Debate"><input name="" type="button"   class="submit-debate-btn"/></a>';

    $output .= '

     <div class=" debate-round-tab-outer">
              	<div class="form-part-top">
                    <div class="form-m1">Filter By :
<select name="rfilt-sup" id="rfilt-sup" class="select-2"><option value="0">+/-</option><option value="1">+</option><option value="2">-</option></select></div>
                    <div class="form-m2"><br/>
                    ' . $filter_list . '
                    </div>
                    <div class="form-m3"><br/><input type="hidden" name="rtype" id="rtype" value="' . $type . '" />
                    <select name="rfilt-sort" id="rfilt-sort" class="select-2"><option value="0">Sort By :</option>
                    <option value="1">Most Recent</option>
                     <option value="2">Most Support</option>
                    </select>

                    </div>
                    <div class="form-m4" align="right">&nbsp;<br />' . $rbutton . '</div>

                </div>

                	<div class="clr"></div><br />
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
    global $gSitePath, $user, $gDocPath, $base_root, $language;
    $wave = '';
    $click = '';
    $sortin = 'ORDER BY rid DESC';
    $cond = '';

    // site url with default language
    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';
    
    extract($_REQUEST);
//    if (isset($sort) && $sort == 1)
//        $sortin = ' ORDER BY r.posted_date DESC';
//    elseif (isset($sort) && $sort == 2)
//        $sortin = ' ORDER BY r.strength DESC';
//    if (isset($ans) && !empty($ans))
//        $cond.=" AND ro.paid='$ans'";
//    if (isset($sup) && $sup > 0)
//        $cond.=" AND ro.ans_val='$sup'";
//
//    if (empty($cond))
//        $query = "select r.*,DATE_FORMAT(r.posted_date, '%a %M %Y %h:%i %p') as date_added,IFNULL((select DATE_FORMAT(date_added, '%a %M %Y %h:%i %p') from {resource_reply} as wl where wl.rid=r.rid ORDER BY wl.rid ASC LIMIT 0,1),0) as rdate from {resource} as r join {user_profile} as u on u.uid=r.uid where r.qid='$qid' AND r.rtype='$rtype' AND status='1' $sortin ";
//    else
//        $query = "select r.*,DATE_FORMAT(r.posted_date, '%a %M %Y %h:%i %p') as date_added,IFNULL((select DATE_FORMAT(date_added, '%a %M %Y %h:%i %p') from {resource_reply} as wl where wl.rid=r.rid ORDER BY wl.rid ASC LIMIT 0,1),0) as rdate from {resource_options} as ro join {resource} as r on ro.rid=r.rid join {user_profile} as u on u.uid=r.uid where r.qid='$qid' AND r.rtype='$rtype' AND status='1' $cond  group by r.rid $sortin ";
//
//    $cnt = ExecuteQuery($query, "select");
    // load Resource

    $sorting = 'ORDER BY f.nid DESC';
    $cond = '';
    extract($_REQUEST);
    if (isset($sort) && $sort == 1) {
        $sorting = 'ORDER BY n.created DESC';
    } elseif (isset($sort) && $sort == 2) {
        $sorting = ' ORDER BY c.field_strength_value DESC';
    }
    if (isset($ans) && !empty($ans)) {
        $cond.=" AND do.chorder='$ans'";
    }
    if (isset($sup) && $sup > 0) {
        $cond.=" AND do.ans_val='$sup'";
    }

    $resType = $rtype == 1 ? 'news' : 'facts';
    $tid = get_taxonomy_id('forum', 'Resource');

    if (empty($cond))
        $sql = "SELECT DISTINCT(f.nid) FROM {forum} as f JOIN {node} as n ON f.nid = n.nid RIGHT JOIN {content_type_forum} as c ON f.nid = c.nid WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' AND c.field_rtype_value = '%s' $sorting";
    else
        $sql = "SELECT DISTINCT(f.nid) FROM  {resource_options} as do  JOIN  {forum} as f ON f.nid = do.nid LEFT JOIN {content_type_forum} as c ON f.nid = c.nid JOIN {node} as n ON f.nid = n.nid  WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' AND c.field_rtype_value = '%s' $cond $sorting";

    // forum for translated languages
   $issueId = $qid;
   $tnid = get_tnid($qid);
   $qid = $tnid;

    $nodes = db_query($sql, $tid, $qid, $resType);
    $count = db_result(db_query($sql, $tid, $qid, $resType));

    if ($count > 0) {
        $i = 0;

        while ($node = db_fetch_object($nodes)) {
            $forum = node_load(array('nid' => $node->nid, 'status' => '1'));


            ///*******************/
            // translated content for title and body
            // get forum default language id
            $translated = get_translated_content_forum($issueId, $forum->nid, $curLanguage);
            $forum->title = $translated->title;
            $forum->body = $translated->body;
            ///*******************/



            $bg = $i % 2;
            if ($bg)
                $setbg = 'back-col';
            else
                $setbg='';
            $i++;
            $account = user_load($forum->uid);
            // resource round up
            $tForumId = get_tnid($forum->nid);
            resource_roundup($tForumId);


            // vote agree, disagree calculation
            $voteUp = 0;
            $voteDown = 0;
            $criteriaUpNode = array('content_type' => 'node',
                'content_id' => $forum->nid,
                'tag' => 'vote',
                'vote_type' => 'up');
            $criteriaDownNode = array('content_type' => 'node',
                'content_id' => $forum->nid,
                'tag' => 'vote',
                'vote_type' => 'down');
            $voteUp = vote_up_down_count($criteriaUpNode);
            $voteDown = vote_up_down_count($criteriaDownNode);
            $sql = db_query("SELECT cid FROM {comments} WHERE nid = '%d'", $forum->nid);
            while ($row = db_fetch_object($sql)) {
                $criteriaUp = array('content_type' => 'comment',
                    'content_id' => $row->cid,
                    'tag' => 'vote',
                    'vote_type' => 'up');
                $criteriaDown = array('content_type' => 'comment',
                    'content_id' => $row->cid,
                    'tag' => 'vote',
                    'vote_type' => 'down');
                $voteUp += vote_up_down_count($criteriaUp);
                $voteDown += vote_up_down_count($criteriaDown);
            }
            // date posted, last activity
            $last_timestamp = db_result(db_query("SELECT timestamp FROM {comments} WHERE nid = '%d' ORDER BY cid DESC LIMIT 0,1", $forum->nid));

            $posted = date("F d Y H:i:s", $forum->created);
            $last_activity = $last_timestamp != '' ? date("F d Y H:i:s", $last_timestamp) : $posted;

            $strength = '';
            $image = !empty($forum->field_filepath[0]['value']) ? $forum->field_filepath[0]['value'] : file_directory_path() . '/noimage.jpg';

            //$query = "select * from {resource_options} a,{possible_answer} b where a.paid=b.paid AND a.rid='" . $forum->nid . "'";
            $query = "select * from {resource_options} a join {poll_choices} b on a.chorder=b.chorder where a.nid='" . $forum->nid . "' AND b.nid='$qid'";
            $strnth = ExecuteQuery($query, "select");
            foreach ($strnth as $list) {
                $ans = $list['chtext'];

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
<div class="toppart"><p>' . $voteUp . '</p>

<p align="center"><img src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/aggree-hand.jpg" width="18" height="15" alt="Agree" /></p></div>
<div class="toppart2"><p>' . $voteDown . '</p>
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
<a class="debate-links" href="' . $sitelink . 'resource/debate/' . $qid . '/' . $forum->nid . '" >' . myTruncate($forum->body, '50', '', '..') . '</a><br>
<a target="_blank" href="' . $forum->title . '">' . myTruncate($forum->title, '25', '', '..') . '</a><br>
<br>


' . myTruncate($forum->body, '125', '', '..') . '
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


<li>Posted : ' . $posted . ' </li>
<div class="clr"></div>
<li>Last Activity: ' . $last_activity . '</li>


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


//    if (count($cnt)) {
//
//
//        foreach ($cnt as $forum) {
//            $bg = $i % 2;
//            if ($bg)
//                $setbg = 'back-col';
//            else
//                $setbg='';
//            $i++;
//            $account = user_load($forum['uid']);
//            // resource round up
//            resource_roundup($forum['rid']);
//
//            $query = "select * from {resource_options} a,{possible_answer} b where a.paid=b.paid AND a.rid='" . $forum['rid'] . "'";
//            $strnth = ExecuteQuery($query, "select");
//            $strength = '';
//            $image = !empty($forum['uimg']) ? $forum['uimg'] : file_directory_path() . '/noimage.jpg';
//            foreach ($strnth as $list) {
//                $ans = $list['answer'];
//
//                switch ($list['ans_val']) {
//                    case 0:
//                        $strength.='<div class="bottpart">
//                                <div class="green"><em>&nbsp;&nbsp;+</em></div>
//                                <div class="green-box">' . $ans . '</div>
//                                     <div class="clr"></div>
//                                     </div>';
//                        break;
//                    case 1:
//                        $strength.='<div class="bottpart">
//                                <div class="green"><em>&nbsp;&nbsp;+</em></div>
//                                <div class="green-box">' . $ans . '</div>
//                                     <div class="clr"></div>
//                                     </div>';
//                        break;
//                    case 2:
//                        $strength.='<div class="bottpart">
//                                <div class="pink"><em>&nbsp;&nbsp;-</em></div>
//                                <div class="pink-box">' . $ans . '</div>
//                                     <div class="clr"></div>
//                                     </div>';
//                        break;
//                }
//            }
//
//            $wave.='         <div class="debate-summary-wrapper" >
//<div class="deb-center">
//<div class="leftpartside">
//<div class="toppart"><p>' . $forum['agree'] . '</p>
//
//<p align="center"><img src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/aggree-hand.jpg" width="18" height="15" alt="Agree" /></p></div>
//<div class="toppart2"><p>' . $forum['disagree'] . '</p>
//<p align="center"><img src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/disaggree-hand.jpg" width="18" height="15" alt="Agree" /></p>
//
//</div>
//
//</div>
//
//
//<div class="centerpartside-out">
//<div class="centerpartside-top">
//<div class="centerpartside">
//<div class="form-outer-debate">
//<div class="fm-1">&nbsp;</div>
//<div class="fm-5">
//<div class="leftfm">' . theme('image', $image, t('Resources'), 'Resources', array('width' => '118px', 'height' => '73px'), FALSE) . '</div>
//<div class="rightfm">
//<a class="debate-links" href="' . $gSitePath . 'resource/debate/' . $qid . '/' . $forum['rid'] . '" >' . myTruncate($forum['udesc'], '50', '', '..') . '</a><br>
//<a target="_blank" href="' . $forum['nlink'] . '">' . myTruncate($forum['nlink'], '25', '', '..') . '</a><br>
//<br>
//
//
//' . myTruncate($forum['udesc'], '125', '', '..') . '
//</div>
//
//
//
//</div>
//
//
//<div class="clr"></div>
//</div>
//</div>
//<div class="rightpartside">
//<a  rel=\'' . $bubble . '\' href="' . $gSitePath . 'profile/' . $account->name . '">' . UserPicture_small($account->uid) . '</a></div>
//
//</div>
//<div class="clr"></div>
//
//<div class="centerpartside-bottom">
//' . $strength . '
//
//<ul>
//
//
//<li>Posted : ' . $forum['date_added'] . ' </li>
//<div class="clr"></div>
//<li>Last Activity: ' . $forum['rdate'] . '</li>
//
//
//</ul>
//
//
//</div>
//
//
//<div class="clr"></div>
//
//</div>
//
//</div>
//<div class="deb-bott">
//</div>
//<div class="clr"></div>
//
//</div>
//
//<div class="clr"></div>
//';
//        }
//    }

    return $wave;
}

function resource_media($qid='') {
    global $gSitePath, $user, $gDocPath, $base_root;
    $wave = '';
    $click = '';
        $sorting = 'ORDER BY f.nid DESC';
    $cond = '';
    extract($_REQUEST);
    if (isset($sort) && $sort == 1) {
        $sorting = 'ORDER BY n.created DESC';
    } elseif (isset($sort) && $sort == 2) {
        $sorting = ' ORDER BY c.field_strength_value DESC';
    }
    if (isset($ans) && !empty($ans)) {
        $cond.=" AND do.chorder='$ans'";
    }
    if (isset($sup) && $sup > 0) {
        $cond.=" AND do.ans_val='$sup'";
    }

    $tid = get_taxonomy_id('forum', 'Resource');
    //$query = "select *,DATE_FORMAT(r.posted_date, '%a %M %Y %h:%i %p') as date_added,IFNULL((select DATE_FORMAT(date_added, '%a %M %Y %h:%i %p') from {resource_reply} as wl where wl.rid=r.rid ORDER BY wl.rid ASC LIMIT 0,1),0) as rdate from {resource} as r join {user_profile} as u on u.uid=r.uid where r.qid='$qid' AND r.rtype='2' AND status='1' ORDER BY rid DESC ";
    //$cnt = ExecuteQuery($query, "select");
   if (empty($cond))
     $sql = "SELECT f.nid FROM {forum} as f RIGHT JOIN {content_type_forum} as c ON f.nid = c.nid JOIN {node} as n ON f.nid = n.nid WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' AND c.field_rtype_value = '%s' $sorting";
    else
        $sql = "SELECT DISTINCT(f.nid) FROM  {resource_options} as do  JOIN  {forum} as f ON f.nid = do.nid LEFT JOIN {content_type_forum} as c ON f.nid = c.nid JOIN {node} as n ON f.nid = n.nid  WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' AND c.field_rtype_value = '%s' AND c.field_rtype_value = '%s' $cond $sorting";

   
    $nodes = db_query($sql, $tid, $qid, 'multimedia');
    $count = db_result(db_query($sql, $tid, $qid, 'multimedia'));
    if ($count > 0) {



        while ($node = db_fetch_object($nodes)) {
            $forum = node_load(array('nid' => $node->nid, 'status' => '1'));
//           echo '<pre>';
//           print_r($forum);
            $bg = $i % 2;
            if ($bg)
                $setbg = 'back-col';
            else
                $setbg='';
            $i++;
            $account = user_load($forum->uid);


            $strength = '';
            $content = '';
            if ($forum->field_videoid[0]['value'] != '') {
                $content.='<div class="form-outer-debate">
<div class="fm-1">&nbsp;</div>
<div class="fm-5">
<div class="leftfm"><a  target="_blank" title="Youtube Video" href="http://www.youtube.com/v/' . $forum->field_videoid[0]['value'] . '"  class="floatbox" data-fb-options="width:480 height:384"><img width="125" height="100" src="http://img.youtube.com/vi/' . $forum->field_videoid[0]['value'] . '/default.jpg" alt="Video " ></a></div>
<div class="rightfm">
<a class="debate-links" href="' . $gSitePath . 'resource/debate/' . $qid . '/' . $forum->nid . '" >' . myTruncate($forum->field_nlink[0]['value'], '50', '', '..') . '</a><br>
<br>
</div>


</div>


<div class="clr"></div>
</div>';
            } elseif ($forum->field_filepath[0]['value'] != '') {
                $url = explode('/', $forum->field_filepath[0]['value']);
                $content.='<a class="debate-links" href="' . $gSitePath . 'resource/debate/' . $qid . '/' . $forum->nid . '" > ' . $url[2] . ' </a> ';
            }
            //$query = "select * from {resource_options} a,{possible_answer} b where a.paid=b.paid AND a.rid='" . $forum->nid . "'";
         $query = "select * from {resource_options} a,{poll_choices} b where a.chorder=b.chorder AND a.nid='" . $forum->nid . "' AND b.nid='$qid'";
            $strnth = ExecuteQuery($query, "select");
            foreach ($strnth as $list) {
                $ans = $list['chtext'];

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
            // vote agree, disagree calculation
            $voteUp = 0;
            $voteDown = 0;
            $criteriaUpNode = array('content_type' => 'node',
                'content_id' => $forum->nid,
                'tag' => 'vote',
                'vote_type' => 'up');
            $criteriaDownNode = array('content_type' => 'node',
                'content_id' => $forum->nid,
                'tag' => 'vote',
                'vote_type' => 'down');
            $voteUp = vote_up_down_count($criteriaUpNode);
            $voteDown = vote_up_down_count($criteriaDownNode);
            $sql = db_query("SELECT cid FROM {comments} WHERE nid = '%d'", $forum->nid);
            while ($row = db_fetch_object($sql)) {
                $criteriaUp = array('content_type' => 'comment',
                    'content_id' => $row->cid,
                    'tag' => 'vote',
                    'vote_type' => 'up');
                $criteriaDown = array('content_type' => 'comment',
                    'content_id' => $row->cid,
                    'tag' => 'vote',
                    'vote_type' => 'down');
                $voteUp += vote_up_down_count($criteriaUp);
                $voteDown += vote_up_down_count($criteriaDown);
            }
            // date posted, last activity
            $last_timestamp = db_result(db_query("SELECT timestamp FROM {comments} WHERE nid = '%d' ORDER BY cid DESC LIMIT 0,1", $forum->nid));

            $posted = date("F d Y H:i:s", $forum->created);
            $last_activity = $last_timestamp != '' ? date("F d Y H:i:s", $last_timestamp) : $posted;

            $wave.='         <div class="debate-summary-wrapper" >
<div class="deb-center">
<div class="leftpartside">
<div class="toppart"><p>' . $voteUp . '</p>

<p align="center"><img src="' . $gSitePath . drupal_get_path('theme', 'newtheme') . '/images/aggree-hand.jpg" width="18" height="15" alt="Agree" /></p></div>
<div class="toppart2"><p>' . $voteDown . '</p>
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


<li>Posted : ' . $posted . ' </li>
<div class="clr"></div>
<li>Last Activity: ' . $last_activity . '</li>


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
            // resource round up
            $tForumId = get_tnid($forum->nid);
            resource_roundup($tForumId);
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

    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';

    $output = '';
    $like = '';
    $flag = '';
    // get nid for respective did
    //$nodeid = db_result(db_query("SELECT nid FROM {resource} WHERE rid = '%d'", $rid));
    //$query = "SELECT *,u.uid as uid,IFNULL((select rid  FROM {resource} where rid > r.rid AND qid='$qid' limit 0,1 ),0) as prid,IFNULL((select rid FROM {resource} where rid < r.rid AND qid='$qid' limit 0,1 ),0) as nrid   FROM {resource} as r  join {user_profile} as u on u.uid=r.uid   where r.qid='$qid' AND r.rid='$rid' AND r.status='1'";
    //$list = ExecuteQuery($query, "select");
    $forum = node_load($rid);
    $dlink = $gSitePath . 'resource/debate/';


//    foreach ($list as $forum) {
    //Agree Disagree
    if ($forum->prid > 0) {
        $prev = $dlink . $qid . '/' . $forum['prid'];
        $set_p_link = '<li><a  href="' . $prev . '" class="previous"  onclick="switchdebate(this.href);return false;" >Previous Debate</a></li>';
    }
    if ($forum->nrid > 0) {
        $next = $dlink . $qid . '/' . $forum['nrid'];
        $set_n_link = '   <li><a   href="' . $next . '" class="next" onclick="switchdebate(this.href);return false;" >Next Debate</a></li>';
    }
    //Agree Disagree ends
    $output .= '
       <div class="hm-debate2-wrapper">
    	<div class="titlebg">
        	<div class="menudebate">
            	<ul>
                ' . $set_p_link . $set_n_link . '
                	</ul>
            </div>

            	<div class="backbtn"><a href="javascript:void(0);" onclick="fb.end();"></a></div>
                	<h2>Resource Summary</h2>
        <div class="clr"></div>
        </div>


        <div class="clr"></div>
            <div class="hm-debate-cont-outer backping">

           <h3> Debate Title Coming here...</h3>

                        <div>

                        <hr class="hr-silver"/>

<div align="center" id="waveerr"></div>
';
//$date = cdatetime($forum['date_added']).$forum['date_added'];
    $posted = date("Y-m-d H:i:s", $forum->created);
    $date = format_date_class($posted, date());
    $account = user_load($forum->uid);

    $image = empty($forum->field_filepath[0]['value']) ? file_directory_path() . '/noimage.jpg' : $forum->field_filepath[0]['value'];
    //$name = empty($forum['real_name']) ? $forum['first_name'] : $forum['real_name'];
//likes or not
    //$querylike = "select * from {user_likes} where is_resource='1' AND uid='$user->uid' AND node_id='" . $forum['rid'] . "'";
    //$fetch = ExecuteQuery($querylike, "select");
    //$agreecnt = db_result(db_query("select count(*) from {user_likes} where is_resource='1' AND is_agree='1' AND node_id='" . $forum['rid'] . "'"));
    //$disagreecnt = db_result(db_query("select count(*) from {user_likes} where is_resource='1' AND is_agree='0' AND node_id='" . $forum['rid'] . "'"));
    $agreecnt = 0;
    $disagreecnt = 0;
    $querylike = "SELECT * FROM {votingapi_vote} WHERE content_type = 'node' AND uid = '$user->uid' AND content_id = '$forum->nid'";
    $fetch = ExecuteQuery($querylike, "select");
    $criteriaUpNode = array('content_type' => 'node',
        'content_id' => $forum->nid,
        'tag' => 'vote',
        'vote_type' => 'up');
    $criteriaDownNode = array('content_type' => 'node',
        'content_id' => $forum->nid,
        'tag' => 'vote',
        'vote_type' => 'down');
    $agreecnt = vote_up_down_count($criteriaUpNode);
    $disagreecnt = vote_up_down_count($criteriaDownNode);
    if ($user->uid != $forum->uid) {
        if (count($fetch) < 1) {
            $imgpath = $gSitePath.drupal_get_path('theme', 'newtheme').'/images/';
            $likeImg = '<img src="'.$imgpath.'likebig.png" title="like" />';
            $dislikeImg = '<img src="'.$imgpath.'dislike.png" title="dislike" />';
            $like = '<li id="lik-btns-node-'.$forum->nid.'"><span name="' . $rid . '" id="dagree" type="is_resource" ><a href="javascript:void(0);" name="a-' . $rid . '" class="dagree">'.$likeImg.'</a>&nbsp;<a name="da-' . $rid . '" href="javascript:void(0);" class="ddisagree">'.$dislikeImg.'</a></span></li>';
        } elseif ($fetch[0]['value'] == '1') {

            $like = '<li><em>You <strong>agree</strong> with this comment</em></li>';
        } else {
            $like = '<li><em>You <strong>Disagree</strong> with this comment</em></li>';
        }
    }

    // like bar percent calculation
                
                $like.= '<li id="bar-area-node-'.$forum->nid.'">'.like_dislike_bar($agreecnt, $disagreecnt).'</li>';
//flag


    if (user_is_logged_in ()) {
        $replybutton = '<a class="floatbox reply-menu" onclick="addComment(this);" name="rep" title="Reply Post"  id="' . $rid . '-0" href="#postreply"></a>';
        //$flag.='<a name="' . $rid . '-0" href="#freport"  class="floatbox flag-menu" title="Report Post" onclick="report_forum(\'resource\',this);"></a>';
        $flag.='<a name="' . $rid . '-0" href="javascript:void(0);"  class="flag-menu" title="Report Post" onclick="loadflagresdeb(\''.$gSitePath.'qlite/flag/'.$rid.'\', \'Report\');"></a>';
    } else {
        $replybutton = '<a class=" reply-menu" onclick="check_popup_login();" name="rep" title="Reply Post"  id="' . $rid . '-' . $forum->reid . '" href="#postreply"></a>';
        $flag.='<a  href="#freport"  class=" flag-menu" title="Report Post" onclick="check_popup_login();"></a>';
    }

    $bubble = load_user_badge($account->uid);
    $medal = updateProfileBadge($account->uid);

    if ($forum->field_rtype[0]['value'] == 'multimedia') {
        if ($forum->field_mtype[0]['value'] == 'video') {
            $content.='<div class="form-outer-debate">
<div class="fm-1">&nbsp;</div>
<div class="fm-5">
<div class="leftfm"><a  target="_blank" title="Youtube Video" href="http://www.youtube.com/v/' . $forum->field_videoid[0]['value'] . '"  class="floatbox" data-fb-options="width:480 height:384"><img width="125" height="100" src="http://img.youtube.com/vi/' . $forum->field_videoid[0]['value'] . '/default.jpg" alt="Video " ></a></div>
<div class="rightfm">
<a href="' . $forum->field_nlink[0]['value'] . '" target="_blank" >' . myTruncate($forum->field_nlink[0]['value'], '50', '', '..') . '</a><br>
<br>
</div>
</div>
<div class="clr"></div>
</div>';
        } else {
            $url = explode('/', $forum->field_filepath[0]['value']);
            $content.='<a href="' . $gSitePath . '' . $forum->field_filepath[0]['value'] . '" target="_blank"> ' . $url[2] . ' </a> ';
        }
    } else {

        $content.='<div class="form-outer-debate">
                <div class="fm-1">&nbsp;</div>
        <div class="fm-4">
        	<div class="leftfm">' . theme('image', $image, t('Resources'), 'Resources', array('width' => '118px', 'height' => '73px'), FALSE) . '</div>
            <div class="rightfm">
 <a href="' . $forum->title . '" target="_blank"><h5>' . $forum->title . '</h5></a>
' . make_clickable($forum->body) . '
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
<li>' . $replybutton . '</li>
<li>' . $flag . '</li>
</ul>
</div>
<div class="itemthird">

' . $bubble . '

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
    // }
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
<form id="postreplyform" name="freply" action="' . $sitelink . 'issues/debate/save">
  	<h2>REPLY</h2>

    	<div>
        <textarea rows="10" cols="" name="waveletcmt" id="waveletcmt">Enter text here</textarea>
<!--<input type="checkbox" name="privt" value="1" id="privt"/> Private Reply-->
<input type="hidden" name="fdid" id="fdid" value="' . $rid . '"/>
		<input type="hidden" name="frid" id="frid" value=""/>
                 <input type="hidden" name="qid" id="qid" value="' . $qid . '"/>
			<input type="hidden" name="action" value="resreply" />
                        <input type="hidden" name="nodeid" value="' . $rid . '" />
                        <input type="hidden" name="comid" id="comid" value=""/>
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
    <input type="hidden" value="" id="rtype" name="rtype"/>
	<input type="hidden" value="" id="rwave" name="did"/>
	<input type="hidden" value="" id="rwavelet" name="rdid"/>


<div class="adcomment-outer">
	' . report_theme() . '<p>
	 or <a onclick=" jQuery.unblockUI();return false;" id="wavecancel1" href="">cancel</a>
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
    // site url with default language
    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';
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
                $web_images = collect_valid_images($imgs);
                
                $count = count($web_images);
                $totalImage = $count>10?'10':$count;
                //$totalImage = $count;
                $imgCount = $count>0?1:0;
                $endImage = $totalImage!=0?($totalImage-1):0;
                $imgPath = $gSitePath.drupal_get_path('theme', 'newtheme').'/images/';
                $imgSelector = '<div class="img-selector">';
                for($i=0;$i<$totalImage;$i++){
                    $imgSelector .= '<div class="cur-img">
                                    <img id="cur_img_'.$i.'" src="' . $web_images[$i] . '" width="118" height="73"  />
                                    </div>';
                }
                $imgSelector .= ' <input type="hidden" id="cur_id_val" value="0" />
                                    <input type="hidden" id="end_image" value="'.$endImage.'" />
                                        <input type="hidden" id="pre_id_val" value="" />
                                        
                                 </div>
                                 <table><tr><td width="16"><a href="javascript:void(0)" title="previous"  id="re-sel-pre"><img src="'.$imgPath.'arrow_left.png"></a></td>
                                <td>&nbsp;&nbsp;<a href="javascript:void(0)" title="next"  id="re-sel-next"><img src="'.$imgPath.'arrow_right.png"></a></td></tr></table><br>
                                    <span id="img_count">'.$imgCount.'</span> of '.$totalImage.'';
                echo $imgSelector;
                echo '<div class="rightfm">' . $inc . '</div><br>
                    <input type="checkbox" name="no_thumbnail" id="no_thumbnail" />&nbsp; No Thumbnail
                    <input type="hidden" name="udesc" value="' . myTruncate($inc, 255) . '"/><input type="hidden" id="final_uimage" name="uimg" value="' . $web_images[0] . '"/>
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

                // save values as node

                $res = new stdClass();
                //  identify resource type and insert datas
                switch ($rtype) {
                    case '1':
                        $res->field_rtype[0]['value'] = 'news';
                        $res->title = $nlink;
                        $res->body = $udesc;
                        $res->field_filepath[0]['value'] = $files;
                        $res->field_nlink[0]['value'] = $nlink;
                        $rtitle = $nlink;
                        break;
                    case '2':
                        $res->field_rtype[0]['value'] = 'multimedia';
                        if ($mtype == 1) {
                            $res->title = $membed;
                            $res->field_mtype[0]['value'] = 'video';
                            $res->field_videoid[0]['value'] = $ytvID;
                            $res->field_nlink[0]['value'] = $membed;
                            $rtitle = $membed;
                        } else if ($mtype == 2) {
                            $res->title = $docpath;
                            $res->field_mtype[0]['value'] = 'doc';
                            $res->field_filepath[0]['value'] = $docpath;
                            $rtitle = $docpath;
                        }
                        break;
                    case '3':
                        $res->field_rtype[0]['value'] = 'facts';
                        $res->title = $nlink;
                        $res->body = $udesc;
                        $res->field_filepath[0]['value'] = $files;
                        $rtitle = $nlink;
                        break;
                }
                $res->type = 'forum';
                $res->uid = $user->uid;
                $res->status = 1;
                // get tid (debate or resource)
                // get_taxonomy_id('module name','term data name')
                $tid = get_taxonomy_id('forum', 'Resource');
                $res->taxonomy = array($tid);
                // content type values

                // set main node as ref node for all resources
                $qaid = get_tnid($qaid);
                
                $res->field_ref_qid[0]['nid'] = $qaid;
                $res->field_type[0]['value'] = '2';
                
                $res->language = 'en';

                $save = node_save($res);

                $nodeid = $res->nid;
                $vid = $res->vid;

                // insert debate as forum in database programmatically
                //db_query("INSERT INTO {forum} SET nid = '%d', vid = '%d', tid = '%d'", $nodeid, $vid, $tid);
                //db_query("INSERT INTO {term_node} SET nid = '%d', vid = '%d', tid = '%d'", $nodeid, $vid, $tid);
                //  $resourceadd = "insert into resource(rtype,nlink,ntitle,ncontent,mtype,membed,facts,uid,qid,nimage,document,video_id,udesc,uimg) values ('$rtype','" . addslashes($nlink) . "','" . addslashes($ntitle) . "','" . addslashes($ncontent) . "','" . $mtype . "','" . addslashes($membed) . "','" . addslashes($flink) . "', '" . $user->uid . "','" . $qaid . "','" . $path . "','" . $docpath . "','" . $ytvID . "','" . $udesc . "','" . $files . "')";
                //$resourceadd = "insert into resource(rtype,nid,nlink,ntitle,ncontent,mtype,membed,facts,uid,qid,nimage,document,video_id,udesc,uimg) values ('%d','%d','%s','%s','%s','%d','%s','%s', '%d','%d','%s','%s','%s','%s','%s')";
                //db_query($resourceadd, $rtype,$nodeid, $nlink, $ntitle, $ncontent, $mtype, $membed, $flink, $user->uid, $qaid, $path, $docpath, $ytvID, $udesc, $files);
                //$nid = db_last_insert_id('resource', 'rid');
                $i = 0;
                foreach ($ans_id as $list) {
                    $forum = "INSERT INTO {resource_options} set nid='%d',chorder='%d',ans_val='%d' ";
                    //$forum = "INSERT INTO {resource_options} set rid='%d',paid='%d',ans_val='%d' ";
                    $result = db_query($forum, $nodeid, $list, $sup_opp[$i]);
                    $i++;
                }
                /* New SET NOTIFY LOG */
                $description = $udesc;
                $file = $files;
                $qtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $qaid));
                $variable = array('rid' => $nodeid, 'r_title' => $rtitle, 'uid' => $user->uid, 'qid' => $qaid, 'q_title' => $qtitle, 'description' => $description, 'file' => $file, 'rtype' => $rtype, 'videoid' => $ytvID);
                set_notify_log($user->uid, $nodeid, 'add_resource', $variable);
                /* New SET NOTIFY LOG */
                echo '<div class="messages success"> Your reference has been added </div>';
            }
            break;
        case 'analysis':
            $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
            $tnid = get_tnid($qid);
            //$vans = "select * from {possible_answer} where  qid=$qid ";
            $vans = "select * from {poll_choices} where  nid=$qid ";
            $vlist = ExecuteQuery($vans, "select");
            $cnt_ans = count($vlist);
            $output.="<link rel='stylesheet' href='" . $gSitePath . drupal_get_path('module', 'quest_lite') . "/plugins/jquery.jqplot.css' type='text/css' />
        <script type='text/javascript' src='http://code.jquery.com/jquery-1.4.2.min.js'></script>
       			<script type='text/javascript' src='" . $gSitePath . drupal_get_path('module', 'quest_lite') . "/scripts/highcharts.js'></script>
<link rel='stylesheet' href='" . $gSitePath . drupal_get_path('theme', 'heardmentality') . "/css/content.css' type='text/css' />
<script type='text/javascript' language='javascript'>

";
            $insdata.="[";
            $data.="[";

            for ($ab = 0; $ab < $cnt_ans; $ab++) {
                // short answers
                $short_answer = get_short_answer($qid, $vlist[$ab]['chorder']);
                $answer = $short_answer!=''?$short_answer:$vlist[$ab]['chtext'];

                $insdata.="'" . $answer . "',";

                //$sel = "select * from {debate_options} as o join {debate} as d on d.did=o.did  where o.paid='" . $vlist[$ab]['paid'] . "' AND o.ans_val IN ('1','2') group by o.did";
                $sel = "select * from {debate_options} as o join {content_type_forum} as d on d.nid=o.nid  where o.chorder='" . $vlist[$ab]['chorder'] . "' AND d.field_ref_qid_nid = '$tnid' AND o.ans_val IN ('1','2') group by o.nid";
                $tmplist = ExecuteQuery($sel, "select");

                $final = '';
                foreach ($tmplist as $list) {

                    //$cnt_opt = db_result(db_query("select count(paid) from {debate_options} where did=" . $list['did'] . " AND ans_val IN ('1','2')"));
                    $cnt_opt = db_result(db_query("select count(chorder) from {debate_options} where nid=" . $list['nid'] . " AND ans_val IN ('1','2')"));

                    $tmp = ($list['ans_val'] == 1) ? '1' : '-1';

                    $final = $final + (($tmp * $list['field_strength_value']) / $cnt_opt);
                   // echo $final.'<br>';
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
            //$vans = "select * from {possible_answer} where  qid=$qid ";
            $vans = "select * from {poll_choices} where  nid=$qid ";
            $vlist = ExecuteQuery($vans, "select");
            $cnt_ans = count($vlist);
            $output.="<link rel='stylesheet' href='" . $gSitePath . drupal_get_path('module', 'quest_lite') . "/plugins/jquery.jqplot.css' type='text/css' />
        <script type='text/javascript' src='http://code.jquery.com/jquery-1.4.2.min.js'></script>
       			<script type='text/javascript' src='" . $gSitePath . drupal_get_path('module', 'quest_lite') . "/scripts/highcharts.js'></script>
<link rel='stylesheet' href='" . $gSitePath . drupal_get_path('theme', 'heardmentality') . "/css/content.css' type='text/css' />
<script type='text/javascript' language='javascript'>

";
            $insdata.="[";
            $data.="[";

            for ($ab = 0; $ab < $cnt_ans; $ab++) {

                // short answers
                $short_answer = get_short_answer($qid, $vlist[$ab]['chorder']);
                $answer = $short_answer!=''?$short_answer:$vlist[$ab]['chtext'];
                
                $insdata.="'" . $answer . "',";

                //$sel = "select * from {resource_options} as o join {resource} as d on d.rid=o.rid  where o.paid='" . $vlist[$ab]['paid'] . "' AND o.ans_val IN (1,2) group by o.rid";
                $sel = "select * from {resource_options} as o join {content_type_forum} as d on d.nid=o.nid  where o.chorder='" . $vlist[$ab]['chorder'] . "' AND o.ans_val IN (1,2) group by o.nid";
                $tmplist = ExecuteQuery($sel, "select");
                foreach ($tmplist as $list) {
                    //$cnt_opt = db_result(db_query("select count(paid) from {resource_options} where rid=" . $list['rid'] . " AND ans_val IN (1,2) group by paid"));
                    $cnt_opt = db_result(db_query("select count(chorder) from {resource_options} where nid=" . $list['nid'] . " AND ans_val IN (1,2) group by chorder"));
                    $tmp = ($list['ans_val'] == 1) ? '1' : '-1';
                    $final = $final + (($tmp * $list['field_strength_value']) / $cnt_opt);
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
            echo '<iframe scrolling="no" style="height: 250px;" id="frmGoogle" src="' . $sitelink . 'debate/ajax/' . $qid . '?action=analysis" border="0" frameborder="0" width="100%"></iframe>';
            break;
        case 'resreport':
            $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
            echo '<iframe scrolling="no" style="height: 250px;" id="frmGoogle" src="' . $sitelink . 'debate/ajax/' . $qid . '?action=resanalysis" border="0" frameborder="0" width="100%"></iframe>';
            break;
        case 'filter':
            $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
            echo list_debate($qid, 1);
            break;
        case 'resfilter':
            $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
            extract($_REQUEST);
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
            echo $output;
            break;
        default:
            echo "<div class='messages error'>No Action found</div>";
            break;
    }

    exit;
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

    global $gSitePath, $user, $gDocPath, $base_root, $base_url, $language;
    extract($_REQUEST);

    if (!user_is_logged_in()) {

        echo "<small>Sorry, Please log in first before you can join this debate!</small>";
        exit;
    }
    $user_coins = db_result(db_query("SELECT total_coins FROM {users} WHERE uid = '$user->uid'"));
    switch ($action) {

        case 'new':
            if (!empty($wtitle) && !empty($user->uid)) {
                $lose_coins = get_coins('c_debate');
                if ($user_coins >= $lose_coins) {

                    // save values as node
                    $deb = new stdClass();
                    $deb->field_private[0]['value'] = $wprivate;
                    $qid = get_tnid($qid);
                    $deb->field_ref_qid[0]['nid'] = $qid;
                    $deb->field_type[0]['value'] = '1';

                    $deb->type = 'forum';
                    $deb->title = $wtitle;
                    $deb->uid = $user->uid;
                    $deb->body = $wcon;
                    $deb->status = 1;
                    // get tid for debate
                    // get_taxonomy_id('module name','term data name')
                    $tid = get_taxonomy_id('forum', 'Debate');
                    $deb->taxonomy = array($tid);

                    // LANGUAGE DETECTION
                    // detect language from inputs using googleapis
                    $inputLanguage = get_input_language($wtitle);
                    $deb->language = $inputLanguage;
                    // language status, initially language status is 0
                    $deb->field_lang_status[0]['value'] = 0;
                    
                    //node_validate($deb);
                    //$node = node_submit($deb);
                    $save = node_save($deb);

                    $nodeid = $deb->nid;
                    $vid = $deb->vid;




                    // insert debate as forum in database programmatically
                    //db_query("INSERT INTO {forum} SET nid = '%d', vid = '%d', tid = '%d'", $nodeid, $vid, $tid);
                    //db_query("INSERT INTO {term_node} SET nid = '%d', vid = '%d', tid = '%d'", $nodeid, $vid, $tid);
                    //$forum = "INSERT INTO {debate} set qid='%d',type='1',uid='%d',title='%s',content='%s',private='%d', nid='%d' ";
                    //$result = db_query($forum, $qid, $user->uid, $wtitle, $wcon, $wprivate, $nodeid);
                    //$nid = db_last_insert_id('debate', 'did');


                    ;
                    $i = 0;
// add coin for Create new debates
                    $coin_type = 'c_debate';
                    users_coins_update($user->uid, '', $coin_type);

                    foreach ($ans_id as $list) {
                        //$forum = "INSERT INTO {debate_options} set did='%d', paid='%d',ans_val='%d' ";
                        $forum = "INSERT INTO {debate_options} set nid = '%d',chorder='%d',ans_val='%d' ";
                        $result = db_query($forum, $nodeid, $list, $sup_opp[$i]);
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
                    //heartbeat_api_log($message_id, $user->uid, $question_urlff, $qid, $question_urlff, $variables);
                    /* RAM HEARTBEAT MODULE INSERT DEBATE */
                    send_forumnotify($nid, $qid);

                    /* New SET NOTIFY LOG */
                    $qtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $qid));
                    $variable = array('did' => $nodeid, 'd_title' => $wtitle, 'uid' => $user->uid, 'qid' => $qid, 'q_title' => $qtitle);
                    set_notify_log($user->uid, $nodeid, 'add_debate', $variable);
                    /* New SET NOTIFY LOG */
                } else {
                    echo '<div align="center"><b>Sorry you do not have enough coins to post New Debate</b></div>';
                }
            } elseif (isset($wtitle)) {
                echo '<div align="center"><b>Sorry Only Logged in user can post New Debate</b></div>';
                echo list_debate($qid, 1);
            }
            break;
        case 'reply':
            $lose_coins = get_coins('p_debate');
            if ($user_coins >= $lose_coins) {
                //$query = "insert into {debate_reply} set did='%d',uid='%d',parentid='%d',str_wk='%d',reply='%s',private='%s'";
                ///$result = db_query($query, $fdid, $user->uid, $frid, $str_wk, check_plain($waveletcmt), $pvt);
                //$rid = db_last_insert_id('debate_reply', 'rid');
                //insert debate reply to comments table
                $values = array();
                $values['did'] = $fdid;
                $values['pid'] = $comid;
                $values['nid'] = $nodeid;
                $values['uid'] = $user->uid;
                $values['name'] = $user->name;
                
                $values['subject'] = check_plain($waveletcmt);
                $values['comment'] = check_plain($waveletcmt);
                $values['status'] = 0;
                $values['format'] = '';
                $values['mail'] = '';
                $values['homepage'] = '';
                $values['str_wk'] = $str_wk;


                // LANGUAGE DETECTION
                // detect language from inputs using googleapis
                $inputLanguage = get_input_language(check_plain($waveletcmt));
                $values['language'] = $inputLanguage;

                //drupal_execute('postreplyform', $values, NULL);
                //custom comment submission (debate reply as comments)
                
                $commentId = comment_save($values);
                custom_comment_update($commentId,$values);

//                $getcomments = array();
//
//                $getcomments['values']['subject'] = 'Debate';
//                $getcomments['values']['comment'] = check_plain($waveletcmt);
//
//                $getcomments['values']['nid'] = $nodeid;
//                $getcomments['values']['uid'] = $user->uid;
//                $getcomments['values']['name'] = $user->name;
//                $getcomments['values']['pid'] = $comid;
//
//                $getcomments['values']['timestamp'] = time();
//                $getcomments['values']['status'] = COMMENT_PUBLISHED;
//
//                comment_form_submit("comment_form", $getcomments);

                $cid = db_last_insert_id('comments', 'cid');
                post_notification($nodeid, $cid);
                echo $output = get_debate($nodeid, 0);
// add coin for participate in debate debates
                $coin_type = 'p_debate';
                users_coins_update($user->uid, '', $coin_type);

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
                //heartbeat_api_log($message_id, $user->uid, $question_urlff, $qid, $question_urlff, $variables);
                /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */

                /* New SET NOTIFY LOG */
                $qtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $qid));
                $dtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $nodeid));
                $variable = array('did' => $nodeid, 'd_title' => $dtitle, 'uid' => $user->uid, 'qid' => $qid, 'q_title' => $qtitle);
                set_notify_log($user->uid, $nodeid, 'debate_reply', $variable);
                /* New SET NOTIFY LOG */
            } else {
                echo '<div align="center"><b>Sorry you do not have enough coins to reply for this post</b></div>';
            }
            break;
        case 'resreply':
            //$query = "insert into {resource_reply} set rid='%d',uid='%d',parentid='%d',str_wk='%d',reply='%s',private='%s'";
            //$result = db_query($query, $fdid, $user->uid, $frid, $str_wk, check_plain($waveletcmt), $pvt);
            //$rid = db_last_insert_id('resource_reply', 'rid');
            //echo $output = get_res_debate($fdid, 0);
            // post_notification($fdid, $rid);

            $values = array();
            $values['did'] = $frid;
            $values['pid'] = $comid;
            $values['nid'] = $nodeid;
            $values['uid'] = $user->uid;
            $values['name'] = $user->name;
            $values['subject'] = check_plain($waveletcmt);
            $values['comment'] = check_plain($waveletcmt);
            $values['status'] = 0;
            $values['format'] = '';
            $values['mail'] = '';
            $values['homepage'] = '';
            $values['str_wk'] = $str_wk;


            // LANGUAGE DETECTION
            // detect language from inputs using googleapis
            $inputLanguage = get_input_language(check_plain($waveletcmt));
            $values['language'] = $inputLanguage;

            //drupal_execute('postreplyform', $values, NULL);
            //custom comment submission (debate reply as comments)
            
            $commentId = comment_save($values);
            custom_comment_update($commentId,$values);

            $cid = db_last_insert_id('comments', 'cid');
            post_notification($nodeid, $cid);
            echo $output = get_res_debate($nodeid, 0);
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
            //heartbeat_api_log($message_id, $user->uid, $question_urlff, $qid, $question_urlff, $variables);
            /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */

            /* New SET NOTIFY LOG */
            $qtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $qid));
            $rtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $nodeid));
            $variable = array('rid' => $nodeid, 'r_title' => $rtitle, 'uid' => $user->uid, 'qid' => $qid, 'q_title' => $qtitle);
            set_notify_log($user->uid, $nodeid, 'resource_reply', $variable);
            /* New SET NOTIFY LOG */

            break;
        case 'is_debate':
        case 'is_debate_reply':
        case 'is_resource':
        case 'is_resource_reply':

            if ($action == 'is_debate' || $action == 'is_resource') {
                $type = 'node';
            } else if ($action == 'is_debate_reply' || $action == 'is_resource_reply') {
                $type = 'comment';
            }


            $cond = " AND type = '" . $type . "'";
            //$cond = " AND " . $action . "='1'";
            //$set = " " . $action . "='1'";
            //$query = "select * from {user_likes} where node_id='$content_id' $cond AND uid='$user->uid'";
            $query = "select * from {votingapi_vote} where content_id ='$content_id' $cond AND uid='$user->uid'";

            $chk = db_result(db_query($query));

            if (!$chk && $user->uid > 0) {
                $lose_coins = $agree == 1 ? get_coins('agree') : get_coins('disagree');
                if ($user_coins >= $lose_coins) {
                    //$query = "insert into {user_likes} set $set ,node_id='$content_id',uid='$user->uid',is_agree='$agree'";
                    //$chk = db_query($query);
                    // add values into votingapi_vote
                    $voteValue = $agree == 1 ? '1' : '-1';
                    if ($action == 'is_debate' || $action == 'is_resource') {
                        $content_type = 'node';
                    } else if ($action == 'is_debate_reply' || $action == 'is_resource_reply') {
                        $content_type = 'comment';
                    }

                    db_query("INSERT INTO {votingapi_vote} SET content_type = '%s', content_id = '%d', value = '%s', value_type = '%s', tag = '%s', uid = '%d', timestamp = '%d'",
                            $content_type, $content_id, $voteValue, 'points', 'vote', $user->uid, time());

                    // get like dislike counts

                    $criteriaUpNode = array('content_type' => $type,
                    'content_id' => $content_id,
                    'tag' => 'vote',
                    'vote_type' => 'up');
                    $criteriaDownNode = array('content_type' => $type,
                    'content_id' => $content_id,
                    'tag' => 'vote',
                    'vote_type' => 'down');
                    $agreecnt = vote_up_down_count($criteriaUpNode);
                    $disagreecnt = vote_up_down_count($criteriaDownNode);

// add coin for agree and disagree
                    $coin_type = $agree == '1' ? 'agree' : 'disagree';
                    $coins = users_coins_update($user->uid, '', $coin_type);

//guru points
                    insertpoints($action, $content_id);
//notification
                    like_notification($content_id, $set);

                    /* New SET NOTIFY LOG */
                    $nodeid = 0;
                    if ($agree == 1) {
                        if ($action == 'is_debate') {

                            $message_id = 'deb_agree';
                            $dtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $content_id));

                            $qid = db_result(db_query("SELECT field_ref_qid_nid FROM {content_type_forum} WHERE nid = '%d'", $content_id));
                            $qtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $qid));

                            $variable = array('did' => $content_id, 'd_title' => $dtitle, 'qid' => $qid, 'q_title' => $qtitle);
                            $nodeid = $content_id;
                        } else if ($action == 'is_debate_reply') {

                            $message_id = 'deb_reply_agree';
                            $did = db_result(db_query("SELECT nid FROM {comments} WHERE cid = '%d'", $content_id));
                            $ctitle = db_result(db_query("SELECT comment FROM {comments} WHERE cid = '%d'", $content_id));

                            $qid = db_result(db_query("SELECT field_ref_qid_nid FROM {content_type_forum} WHERE nid = '%d'", $did));
                            $qtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $qid));

                            $variable = array('did' => $did, 'cid' => $content_id, 'c_title' => $ctitle, 'qid' => $qid, 'q_title' => $qtitle);
                        } else if ($action == 'is_resource') {

                            $message_id = 'res_agree';
                            $rtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $content_id));
                            $qid = db_result(db_query("SELECT field_ref_qid_nid FROM {content_type_forum} WHERE nid = '%d'", $content_id));
                            $qtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $qid));

                            $variable = array('rid' => $content_id, 'r_title' => $rtitle, 'qid' => $qid, 'q_title' => $qtitle);
                            $nodeid = $content_id;
                        } else if ($action == 'is_resource_reply') {

                            $message_id = 'res_reply_agree';
                            $rid = db_result(db_query("SELECT nid FROM {comments} WHERE cid = '%d'", $content_id));
                            $qid = db_result(db_query("SELECT field_ref_qid_nid FROM {content_type_forum} WHERE nid = '%d'", $rid));
                            $qtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $qid));

                            $ctitle = db_result(db_query("SELECT comment FROM {comments} WHERE cid = '%d'", $content_id));
                            $variable = array('rid' => $rid, 'cid' => $content_id, 'c_title' => $ctitle, 'qid' => $qid, 'q_title' => $qtitle);
                        }
                    } else if ($agree == 0) {
                        if ($action == 'is_debate') {

                            $message_id = 'deb_disagree';
                            $dtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $content_id));
                            $qid = db_result(db_query("SELECT field_ref_qid_nid FROM {content_type_forum} WHERE nid = '%d'", $content_id));
                            $qtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $qid));

                            $variable = array('did' => $content_id, 'd_title' => $dtitle, 'qid' => $qid, 'q_title' => $qtitle);
                            $nodeid = $content_id;
                        } else if ($action == 'is_debate_reply') {

                            $message_id = 'deb_reply_disagree';
                            $did = db_result(db_query("SELECT nid FROM {comments} WHERE cid = '%d'", $content_id));
                            $ctitle = db_result(db_query("SELECT comment FROM {comments} WHERE cid = '%d'", $content_id));
                            $qid = db_result(db_query("SELECT field_ref_qid_nid FROM {content_type_forum} WHERE nid = '%d'", $did));
                            $qtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $qid));

                            $variable = array('did' => $did, 'cid' => $content_id, 'c_title' => $ctitle, 'qid' => $qid, 'q_title' => $qtitle);
                        } else if ($action == 'is_resource') {
                            $qid = db_result(db_query("SELECT field_ref_qid_nid FROM {content_type_forum} WHERE nid = '%d'", $content_id));
                            $qtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $qid));
                            $message_id = 'res_disagree';
                            $rtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $content_id));
                            $variable = array('rid' => $content_id, 'r_title' => $rtitle, 'qid' => $qid, 'q_title' => $qtitle);
                            $nodeid = $content_id;
                        } else if ($action == 'is_resource_reply') {

                            $message_id = 'res_reply_disagree';
                            $rid = db_result(db_query("SELECT nid FROM {comments} WHERE cid = '%d'", $content_id));
                            $ctitle = db_result(db_query("SELECT comment FROM {comments} WHERE cid = '%d'", $content_id));
                            $qid = db_result(db_query("SELECT field_ref_qid_nid FROM {content_type_forum} WHERE nid = '%d'", $rid));
                            $qtitle = db_result(db_query("SELECT title FROM {node} WHERE nid = '%d'", $qid));

                            $variable = array('rid' => $rid, 'cid' => $content_id, 'c_title' => $ctitle, 'qid' => $qid, 'q_title' => $qtitle);
                        }
                    }
                    // print_r($variable); exit;
                    set_notify_log($user->uid, $nodeid, $message_id, $variable);
                    /* New SET NOTIFY LOG */


                    $msg['cnt'] = db_result(db_query("select count(*) from {user_likes} where $set AND is_debate='1' AND node_id='" . $nodeid . "'"));
                    if ($agree) {
                        $msg['msg'] = "<em><strong>Agreed!</strong>You have $coins coins left</em> ";
                        /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */
                        $qid_url = db_query("select * from {question} where qid='$content_id'");
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
                        //heartbeat_api_log($message_id, $user->uid, $question_urlff, $qid, $question_urlff, $variables);
                        /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */
                    } else {
                        $msg['msg'] = "<em><strong>Disagreed!</strong>You have $coins coins left</em> ";
                        /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */
                        $qid_url = db_query("select * from {question} where qid='$content_id'");
                        $question_values = db_fetch_array($qid_url);
                        if (isset($question_values)) {
                            $question_urlff = $question_values['url'] . '/' . $content_id;
                            $qtion = $question_values['question'];
                            $ctxt = $question_values['context'];
                        }
                        $message_id = 'debate_disagree';
                        $variables = array(
                            '@username' => l(user_load($user->uid)->name, 'profile/' . $user->name),
                            '@debate_title' => "<a href='$base_url/$question_urlff' >" . $qtion . "</a>",
                        );
                        //heartbeat_api_log($message_id, $user->uid, $question_urlff, $qid, $question_urlff, $variables);
                        /* RAM HEARTBEAT MODULE DEBATE REPLY UPDATE */
                    }
                    $msg['error'] = '0';
                    $msg['type'] = $type;
                    $msg['likebar'] = like_dislike_bar($agreecnt, $disagreecnt);
                } else {
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

function users_coins_update($uid = '', $bid = '', $keyname = '') {
    if ($bid != '') {
        $keyname = db_result(db_query("SELECT btype FROM {badges} WHERE bid = '$bid'"));
    }
    $sql = "SELECT * FROM {tbl_coins} WHERE key_name = '$keyname'";
    $coins = ExecuteQuery($sql, 'select');
    foreach ($coins as $coin) {
        $coin_count = $coin['coin_count'];
        $coin_type = $coin['type'];
    }
    $insert = "INSERT INTO {user_coins} SET coin_key = '%s', coin_type = '%s', coin_count = '%d', uid = '%d'";
    db_query($insert, $keyname, $coin_type, $coin_count, $uid);

    // update total coins
    $user_coins = db_result(db_query("SELECT total_coins FROM {users} WHERE uid = '$uid'"));
    if ($coin_type == 'earn') {
        $total_coins = $user_coins + $coin_count;
        $message_id = 'add_coins';
    }
    if ($coin_type == 'lose') {
        $total_coins = $user_coins - $coin_count;
        $message_id = 'lose_coins';
    }

    /* New SET NOTIFY LOG */
    $variable = array('coin_count' => $coin_count, 'coint_type' => $coin_type);
    set_notify_log($uid, '', $message_id, $variable);
    /* New SET NOTIFY LOG */

    db_query("UPDATE {users} SET total_coins = '%d' WHERE uid = '$uid'", $total_coins);
    $details = user_load(array('uid' => $uid));
    return $details->total_coins;
}

function get_coins($key) {
    $coins = db_result(db_query("SELECT coin_count FROM {tbl_coins} WHERE key_name = '$key'"));
    return $coins;
}

// reply as comments
function custom_comment_update($cid, $comm = '') {
    //db_query("INSERT INTO {comments} SET pid = '%d', nid = '%d', uid = '%d', subject = '%s', comment = '%s', name = '%s', timestamp = '%d', status = '%d', str_wk = '%d', language = '%s'", $comm['pid'], $comm['nid'], $comm['uid'], $comm['subject'], $comm['comment'], $comm['name'], time(), '1', $comm['str_wk'], $comm['language']);
    db_query("UPDATE {comments} SET str_wk = '%d', language = '%s' WHERE cid = '%d'", $comm['str_wk'], $comm['language'], $cid);
}


function like_dislike_bar($cntagree = '', $cntdisagree = ''){
    $totalCount = $cntagree + $cntdisagree;
    $up_percent = ($cntagree*100)/$totalCount;
    $down_percent = ($cntdisagree*100)/$totalCount;
    $bar = '<div><b>Rating </b>('.$totalCount.' total)</div><div id="likebar"><span id="like-percent-area" class="like-per" style="width:'.$up_percent.'%;"></span><span id="dislike-percent-area" class="dislike-per" style="width:'.$down_percent.'%;"></span></div>
            '.$cntagree.'&nbsp;likes&nbsp;'.$cntdisagree.'&nbsp;dislikes';
    return $bar;
}

function collect_valid_images($images){
    $ext_arr = array('jpg', 'jpeg', 'gif', 'png', 'JPEG', 'bmp');
    foreach($images as $image){
    $im = explode("/",$image);
    $webimage = end($im);
    $ext = explode(".",$webimage);
    $extension = end($ext);
    if(in_array($extension, $ext_arr)){
        $fImages[] = $image;
    }
    }
    return $fImages;
}