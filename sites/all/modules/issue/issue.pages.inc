<?php
// $Id: issue.pages.inc,v 1.1.2.2 2010/06/22 11:33:06 mirodietiker Exp $

/**
 * @file
 * Page callbacks for the issue module.
 */

/**
 * List all issue as a page.
 */

function resource_innews($qid='', $rtype='') {
    global $gSitePath, $user, $gDocPath, $base_root;
    $wave = '';
    $click = '';
    $sortin = 'ORDER BY rid DESC';
    $cond = '';
    extract($_REQUEST);
    if (isset($sort) && $sort == 1)
        $sortin = ' ORDER BY r.posted_date DESC';
    elseif (isset($sort) && $sort == 2)
        $sortin = ' ORDER BY r.strength DESC';
    if (isset($ans) && !empty($ans))
        $cond.=" AND ro.paid='$ans'";
    if (isset($sup) && $sup > 0)
        $cond.=" AND ro.ans_val='$sup'";

    if (empty($cond))
        $query = "select r.*,DATE_FORMAT(r.posted_date, '%a %M %Y %h:%i %p') as date_added,IFNULL((select DATE_FORMAT(date_added, '%a %M %Y %h:%i %p') from {resource_reply} as wl where wl.rid=r.rid ORDER BY wl.rid ASC LIMIT 0,1),0) as rdate from {resource} as r join {user_profile} as u on u.uid=r.uid where r.qid='$qid' AND r.rtype='$rtype' AND status='1' $sortin ";
    else
        $query = "select r.*,DATE_FORMAT(r.posted_date, '%a %M %Y %h:%i %p') as date_added,IFNULL((select DATE_FORMAT(date_added, '%a %M %Y %h:%i %p') from {resource_reply} as wl where wl.rid=r.rid ORDER BY wl.rid ASC LIMIT 0,1),0) as rdate from {resource_options} as ro join {resource} as r on ro.rid=r.rid join {user_profile} as u on u.uid=r.uid where r.qid='$qid' AND r.rtype='$rtype' AND status='1' $cond  group by r.rid $sortin ";

    $cnt = ExecuteQuery($query, "select");
    // load Resource
    $resType = $rtype==1?'news':'facts';
    $tid = get_taxonomy_id('forum', 'Resource');
    $sql = "SELECT f.nid FROM {forum} as f RIGHT JOIN {content_type_forum} as c ON f.nid = c.nid WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' AND c.field_rtype_value = '%s' ORDER BY f.nid DESC";
    $nodes = db_query($sql, $tid, $qid, $resType);
    $count = db_result(db_query($sql, $tid, $qid, $resType));

    if ($count>0) {
    $i=0;

         while ($node = db_fetch_object($nodes)) {
            $forum = node_load( array('nid' => $node->nid, 'status' => '1'));

            $bg = $i % 2;
            if ($bg)
                $setbg = 'back-col';
            else
                $setbg='';
            $i++;
            $account = user_load($forum->uid);
            // resource round up
            resource_roundup($forum->nid);


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
            while($row = db_fetch_object($sql)){
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
            $last_activity = $last_timestamp!=''?date("F d Y H:i:s", $last_timestamp):$posted;

            $strength = '';
            $image = !empty($forum->field_filepath[0]['value']) ? $forum->field_filepath[0]['value'] : file_directory_path() . '/noimage.jpg';

            //$query = "select * from {resource_options} a,{possible_answer} b where a.paid=b.paid AND a.rid='" . $forum->nid . "'";
            $query = "select * from {resource_options} a,{poll_choices} b where a.chid=b.chid AND a.nid='" . $forum->nid . "'";
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
<a class="debate-links" href="' . $gSitePath . 'resource/debate/' . $qid . '/' . $forum->nid . '" >' . myTruncate($forum->body, '50', '', '..') . '</a><br>
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
    }
else {
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
    //$query = "select *,DATE_FORMAT(r.posted_date, '%a %M %Y %h:%i %p') as date_added,IFNULL((select DATE_FORMAT(date_added, '%a %M %Y %h:%i %p') from {resource_reply} as wl where wl.rid=r.rid ORDER BY wl.rid ASC LIMIT 0,1),0) as rdate from {resource} as r join {user_profile} as u on u.uid=r.uid where r.qid='$qid' AND r.rtype='2' AND status='1' ORDER BY rid DESC ";
    //$cnt = ExecuteQuery($query, "select");
    $tid = get_taxonomy_id('forum', 'Resource');
    $sql = "SELECT f.nid FROM {forum} as f RIGHT JOIN {content_type_forum} as c ON f.nid = c.nid WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' AND c.field_rtype_value = '%s' ORDER BY f.nid DESC";
    $nodes = db_query($sql, $tid, $qid, 'multimedia');
    $count = db_result(db_query($sql, $tid, $qid, 'multimedia'));
    if ($count>0) {



       while ($node = db_fetch_object($nodes)) {
           $forum = node_load( array('nid' => $node->nid, 'status' => '1'));
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
            $query = "select * from {resource_options} a,{poll_choices} b where a.chid=b.chid AND a.nid='" . $forum->nid . "'";
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
            while($row = db_fetch_object($sql)){
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
            $last_activity = $last_timestamp!=''?date("F d Y H:i:s", $last_timestamp):$posted;

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
            resource_roundup($forum->nid);
        }
    } else {
        $wave.='<div class="messages warning">No Resources Found!</div>';
    }
    return $wave;
}
