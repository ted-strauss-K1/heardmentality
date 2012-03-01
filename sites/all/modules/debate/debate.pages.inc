<?php
function post_notification($did='', $rid='') { ///vijay important comented
    global $user;
    db_query("insert into {notification} set follower_action='1',is_wavelets='1',uid='$user->uid',node_id='$nid' ");


    hm_mails('', $did, 'reply_forum');
////////////mail notication for user follwers to me//////////////////////////////////////
}

function like_notification($nid='', $set='') { //vijay important comented
    global $user;
///////Notifications///
    db_query("insert into {notification} set is_like='1',$set,uid='$user->uid',node_id='$nid' ");
    $sel_forum = "select * from debate_reply as f join debate as w on f.rid=w.fid where f.rid='" . $nid . "'";
    $forum_fet = db_query($sel_forum);
    $forum_row = db_fetch_object($forum_fet);
    $qid_rid = $forum_row->qid;
    hm_mails($qid, $nid, 'add_like');
//////Notifications///

}
function debate_ajax() {

    global $base_url, $user, $gDocPath, $base_root, $theme;

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
                $imgPath = $base_url.'/'.drupal_get_path('theme', 'hmware').'/images/';
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

                // return inserted data
                $tnid = get_tnid($qaid);
                module_load_include('inc', 'issue', 'issue.pages');
                $items = load_resource_datas($nodeid, $qaid, $tnid, $res->field_rtype[0]['value']);


                // strength
                // anwers strength
                $strnth = $items['strength'];
                //echo '<pre>';print_r($strnth);exit;
                $strength = '';
                foreach ($strnth as $list) {
                $short_answer = get_short_answer($items['issue_id'], $list['chorder']);
                $tranAns = db_result(db_query("SELECT chtext FROM {poll_choices} WHERE nid = '".$items['issue_id']."' AND chorder = '".$list['chorder']."'"));
                $ans = $short_answer!=''?$short_answer:$tranAns;

                switch ($list['ans_val']) {
                    case 0:
                        $strength.='<div><span class="yellow-box">+/-</span>'.$ans.'</div>';
                        break;
                    case 1:
                        $strength.='<div><span class="green-box">+</span>'.$ans.'</div>';
                        break;
                    case 2:
                        $strength.='<div><span class="red-box">-</span>'.$ans.'</div>';
                        break;
                }
                }

                // delete
                if(is_moderator() || $items['uid']==$user->uid){
                   $delete = '<h6 value="Delete" id="reply" class="add-comment button light" onclick="delete_thread(\'own_forum_'.$items['resource_id'].'\', \'resource\')">'.t('Delete').'</h6>';
                }else{
                    $delete = '';
                }

                // reply box
                $reply_box = '';
                $comments = '';
                $reply_count =  db_result(db_query("SELECT COUNT(cid) FROM {comments} WHERE nid = '".$items['resource_id']."'"));

                // ratings
                // allow rating check
                $ratings = get_rating_buttons($items, 'is_resource');


                $resouce_theme .= theme('reference_parent_template', $items, $strength, $comments, $reply_box, $reply_count, $ratings, $delete);





                //$co = theme('single_resource_template', $items);
                print $co;
                //echo '<div class="messages success"> Your reference has been added </div>';
                exit;
            }
            break;
        case 'analysis':
            $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
            $tnid = get_tnid($qid);
            //$vans = "select * from {possible_answer} where  qid=$qid ";
            $vans = "select * from {poll_choices} where  nid=$qid ORDER BY chorder";
            $vlist = ExecuteQuery($vans, "select");
            $cnt_ans = count($vlist);
            $output.="<link rel='stylesheet' href='" . $base_url.'/' . drupal_get_path('module', 'quest_lite') . "/plugins/jquery.jqplot.css' type='text/css' />
        <script type='text/javascript' src='http://code.jquery.com/jquery-1.4.2.min.js'></script>
       			<script type='text/javascript' src='" . $base_url.'/' . drupal_get_path('module', 'quest_lite') . "/scripts/highcharts.js'></script>
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
var gSitePath='" . $base_url . "/';
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
            echo $output.='<div id="container" class="highcharts-container" style="height:auto; width: 100%; margin: 0 auto; clear:both"></div>
        <div id="resource" style="height:auto; width: 400px; margin: 0 auto; clear:both"></div>

';
            break;
        case 'resanalysis':
            $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
            //$vans = "select * from {possible_answer} where  qid=$qid ";
            $vans = "select * from {poll_choices} where  nid=$qid ";
            $vlist = ExecuteQuery($vans, "select");
            $cnt_ans = count($vlist);
            $output.="<link rel='stylesheet' href='" . $base_url.'/' . drupal_get_path('module', 'quest_lite') . "/plugins/jquery.jqplot.css' type='text/css' />
        <script type='text/javascript' src='http://code.jquery.com/jquery-1.4.2.min.js'></script>
       			<script type='text/javascript' src='" . $base_url.'/' . drupal_get_path('module', 'quest_lite') . "/scripts/highcharts.js'></script>
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
var gSitePath='" . $base_url . "/';
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
            echo $output.='<div id="container" class="highcharts-container" style="height:auto; width: 100%; margin: 0 auto; clear:both"></div>
        <div id="resource" style="height:auto; width: 100%; margin: 0 auto; clear:both"></div>

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

    global $user, $base_root, $base_url, $language, $theme;
    extract($_REQUEST);

    if (!user_is_logged_in()) {

        echo "<small>Sorry, Please log in first before you can join this debate!</small>";
        exit;
    }
    $user_coins = db_result(db_query("SELECT total_coins FROM {users} WHERE uid = '$user->uid'"));
    switch ($action) {
       
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
                            $item = load_debate_datas($content_id);
                            $msg['cnt'] = $item['vote_up'];
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
                            $item = load_debate_datas($content_id);
                            $msg['cnt'] = $item['vote_down'];
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


                    //$msg['cnt'] = db_result(db_query("select count(*) from {user_likes} where $set AND is_debate='1' AND node_id='" . $nodeid . "'"));
                    if ($agree) {
                        $msg['msg'] = "<em><strong>Agreed!</strong>You have $coins coins left</em> ";
                        $msg['ratecount'] = $agreecnt;
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
                        $msg['ratecount'] = $disagreecnt;
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