<?php

function my_notify_list() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

    drupal_add_css(drupal_get_path('module', 'quest_lite') . '/css/main.css');
    // drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/page.css');
    // drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/tabs.css');
    drupal_add_css(drupal_get_path('module', 'quest_lite') . '/css/main.css');
    //drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/page.css');
    // drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/tabs.css');
    drupal_add_css(drupal_get_path('module', 'quest_lite') . '/css/wave.css');
    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/wave.js');
    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/like.js');
    // drupal_add_js(drupal_get_path('module', 'forum').'/scripts/forum.js');
    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/subtab.js');
    drupal_add_css(drupal_get_path('theme', 'newtheme') . '/rotate_files/ui.css');
    drupal_add_js(drupal_get_path('module', 'notify') . '/scripts/script.js');
    $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
// echo $idb;
    $voutput = '<style>
              .black_overlay{
                  display: none;
                  position: absolute;
                  top: 0%;
                  left: 0%;
                  width: 100%;


                  z-index:1001;
                  -moz-opacity: 0.8;
                  opacity:.30;
				  filter: alpha(opacity=80);
              }
              .white_content {
                  display: none;
                  position: absolute;
                  top: 17%;
                  left:10%;
				  z-index:1002;
                  overflow: auto;
				  cursor: move;
              }
          </style>
<script type="text/javascript">

				var spath=\'' . $gSitePath . '\';

				 function get_message(){
						var clearfi=\'\';
						var url = "' . $gSitePath . 'message";
									var req = new Request({
											method: \'get\'
											,url: url
											,data: {\'sendmail\':1 },
											onRequest: function() { },
											onComplete: function(response) {
													 $(\'div_msg\').set(\'html\', response);
													  $(\'show_box\').set(\'html\', clearfi);
											}
									}).send();


						}




					</script>

			';
    if (($idb == 'ynotify') || ($idb == 'repcontent')) {
        $query = "SELECT qid from {question} order by qid DESC limit 0,1 ";
        $quest = db_query($query);
        $qid = db_result($quest);
    } else {
        $query = "SELECT qid from {question} where url='" . $idb . "'";
        $quest = db_query($query);
        $qid = db_result($quest);
    }



    $vSql = "select * from {question} where status='1' and qid=$qid ";
    $rlist = db_query($vSql);
    $oListquest = db_fetch_object($rlist);

    $list_lengthan = db_query("select * from {possible_answer_vote} where qid='" . $qid . "' and uid='" . $user->uid . "'  ");
    $numran = mysql_num_rows($list_lengthan);
    $answer_id = db_fetch_object($list_lengthan);
    drupal_set_title('Notification');
    $voutput.= '<div class="lft_view"> <!--<h4 class="cmt_name"><a>' . $oListquest->question . ' </a></h4>-->
		<p><a title="' . htmlentities(wordwrap($oListquest->context, 40, '<br/>')) . '" style="' . drupal_link_color($user->uid, $oListquest->qid) . '">' . htmlentities(substr($oListquest->context, 0, 40)) . '</a></p>';
    $vans = "select * from {possible_answer} where  qid=$qid order by paid ASC";


    $vlist = db_query($vans);
    $chk = '';
    while ($vlistquest = db_fetch_object($vlist)) {
        if ($numran == 0) {

            $voutput .= '
		 <p><input name="answer" type="radio" value="' . $vlistquest->paid . '" />
		' . $vlistquest->answer . '   </p>';
        } else {

            $chk = '';
            if ($answer_id->panswer_id == $vlistquest->paid) {

                $chk = "checked";
            }
            $voutput .= ' <p><input name="answer_al" type="radio" ' . $chk . '  value="' . $vlistquest->paid . '" />
		' . $vlistquest->answer . '   </p>';
        }
    }
    $chk = '';


    $voutput.='</div>';

    // $voutput.=qlite_report($qid);
    return $voutput;
}

/*

  function my_notify_list() {

  global $gSitePath,$user,$gDocPath,$base_root,$base_path;

  drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/main.css');
  // drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/page.css');
  // drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/tabs.css');
  drupal_add_js(drupal_get_path('module', 'notify').'/scripts/script.js');
  $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
  // echo $idb;
  $voutput ='<style>
  .black_overlay{
  display: none;
  position: absolute;
  top: 0%;
  left: 0%;
  width: 100%;


  z-index:1001;
  -moz-opacity: 0.8;
  opacity:.30;
  filter: alpha(opacity=80);
  }
  .white_content {
  display: none;
  position: absolute;
  top: 17%;
  left:10%;
  z-index:1002;
  overflow: auto;
  cursor: move;
  }
  </style>
  <script type="text/javascript">

  var spath=\''.$gSitePath.'\';

  function get_message(){
  var clearfi=\'\';
  var url = "'.$gSitePath.'message";
  var req = new Request({
  method: \'get\'
  ,url: url
  ,data: {\'sendmail\':1 },
  onRequest: function() { },
  onComplete: function(response) {
  $(\'div_msg\').set(\'html\', response);
  $(\'show_box\').set(\'html\', clearfi);
  }
  }).send();


  }




  </script>

  ';
  if(($idb=='ynotify')||($idb=='repcontent'))
  {
  $query = "SELECT qid from {question} order by qid DESC limit 0,1 ";
  $quest = db_query($query);
  $qid = db_result($quest);

  }
  else
  {
  $query = "SELECT qid from {question} where url='".$idb."'";
  $quest = db_query($query);
  $qid = db_result($quest);

  }



  $vSql = "select * from {question} where status='1' and qid=$qid ";
  $rlist = db_query($vSql);
  $oListquest = db_fetch_object($rlist);

  $list_lengthan = db_query("select * from {possible_answer_vote} where qid='".$qid."' and uid='".$user->uid."'  ");
  $numran = mysql_num_rows($list_lengthan);
  $answer_id = db_fetch_object($list_lengthan);
  drupal_set_title($oListquest->question);
  $voutput.= '<div class="lft_view"> <!--<h4 class="cmt_name"><a>'.$oListquest->question.' </a></h4>-->
  <p><a title="'.htmlentities(wordwrap($oListquest->context, 40,'<br/>')).'" style="'.drupal_link_color($user->uid,$oListquest->qid).'">'.htmlentities(substr($oListquest->context,0,40)).'</a></p>';
  $vans = "select * from {possible_answer} where  qid=$qid order by paid ASC";


  $vlist = db_query($vans);
  $chk = '';
  while ($vlistquest = db_fetch_object($vlist)) {
  if ($numran == 0) {

  $voutput .= '
  <p><input name="answer" type="radio" value="'.$vlistquest->paid.'" />
  '.$vlistquest->answer.'   </p>';
  } else {

  $chk = '';
  if ($answer_id->panswer_id == $vlistquest->paid) {

  $chk = "checked";
  }
  $voutput .= ' <p><input name="answer_al" type="radio" '.$chk.'  value="'.$vlistquest->paid.'" />
  '.$vlistquest->answer.'   </p>';
  }
  }
  $chk = '';


  $voutput.='</div>';

  // $voutput.=qlite_report($qid);
  return $voutput;

  }
 *
 */

function notify_follow_question() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;


    $array = load_following_notify('is_question');

    $output = '';

    $output.='<div class="innerbox"> <ul class="menu">';

    foreach ($array as $list) {

        $qdet = load_question($list['node_id']);
        $vote = load_votes($list['node_id']);
        // print_r($qdet);
        if ($qdet['question'] != '') {
            $output.='<li><div><a href="'.$gSitePath.$qdet['url'].'?ajax=1" style="'.drupal_link_color($user->uid,$qdet['qid']).'" title="'.htmlentities(wordwrap($qdet['question'], 40,'<br/>')).'">' . truncate_utf8($qdet['question'], '50') . '</a><div>
                <div>' . $vote['qns'] . ' Votes &nbsp; ' . $vote['post'] . ' Posts</div></li>';
          }
    }
    $output.=' </ul></div>';

    if (count($array) < 1) {
        $output = 'No Notifications';
    }


    return $output;
}

function get_nqid($idm) {

    /* global $gSitePath,$user,$gDocPath,$base_root;
      $qid=$idm;
      // echo $qid;
      if($qid!='ynotify'&&$qid!='map' && $qid!='graph'){
      //echo kkkk;
      $query = "SELECT qid from {question} where url='".$idm."'";
      $quest = db_query($query);
      $qid = db_result($quest);

      }

      if($qid=='ynotify'|| $qid=='map' || $qid=='graph'){
      // echo jkjjjj;
      $query = "SELECT qid from {question} order by qid DESC limit 0,1 ";
      $quest = db_query($query);
      $qid = db_result($quest);
      }


      return $qid; */
}

function notify_report($idb='') {
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
	"element":  $("notify-panel"),
	"url":       "' . $gSitePath . 'notify/repcontent/' . $idb . '?t=per"
	});
	});
	
	$("qTabs2Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("notify-panel"),
	"url":       "' . $gSitePath . 'notify/repcontent/' . $idb . '?t=time"
	});
	});
	
	$("qTabs3Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("notify-panel"),
	"url":       "' . $gSitePath . 'notify/repcontent/' . $idb . '?t=area"
	});
	});

	
	</script>';
}

function notify_content() {
    global $gSitePath, $user, $gDocPath, $base_root;
    $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    if (($idb == 'ynotify') || ($idb == 'repcontent')) {
        $query = "SELECT qid from {question} order by qid DESC limit 0,1 ";
        $quest = db_query($query);
        $qid = db_result($quest);
    } else {
        $query = "SELECT qid from {question} where url='" . $idb . "'";
        $quest = db_query($query);
        $qid = db_result($quest);
    }

    //echo "kkkkkkkk".$qid;
    $type = $_REQUEST[t];

    switch ($type) {

        case "time":
            $output = '<div id="contents"><iframe id="frmGoogle" src="' . $gSitePath . 'qlite/graph/' . $qid . '" border="0" height="450" frameborder="0" width="100%"></iframe></div>';
            break;
        case "area":
            $output = '<div id="contents"><iframe id="frmGoogle" src="' . $gSitePath . 'qlite/map/' . $qid . '" border="0" height="450" frameborder="0" width="100%"></iframe></div>';
            break;
        case "per":
        default:
            $output = '<div id="contents"><iframe id="frmGoogle" src="' . $gSitePath . 'qlite/percent/' . $qid . '" border="0" height="450" frameborder="0" width="100%"></iframe></div>';
            break;
    }


    $output.='<div>108 comments &nbsp;&nbsp;&nbsp;' . $numres . ' Resources </div>';

    echo $output;
}

function mail_sent_reply() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

    $numrancnt = db_result(db_query("SELECT COUNT(*) from follower as a, question as b  where a.uid=" . $user->uid . "  and a.follower_status='1' and a.follower_id=b.uid  and b.status='1'"));
    $numrancntss = db_result(db_query("SELECT COUNT(*)  from follower as a, question as b  where a.follower_id=" . $user->uid . "   and a.uid=b.uid  and b.status='1'"));


    if (($numrancnt == 0) && ($numrancntss == 0)) {


        $sel_flow = "select * from  question   where uid!=" . $user->uid . " and status='1'  order by qid desc  ";
    } elseif ($numrancntss == 0) {

        $sel_flow = "select * from follower as a, question as b  where a.uid=" . $user->uid . "  and a.follower_status='1' and a.follower_id=b.uid and b.status='1'  order by a.id desc";
    } else {

        $sel_flow = "select * from follower as a, question as b  where a.follower_id=" . $user->uid . "   and a.uid=b.uid  and b.status='1' order by a.id desc";
    }
    $rs_folwin = db_query($sel_flow);

    while ($flwing_result = db_fetch_object($rs_folwin)) {

        $update_quest = "delete  from possible_answer_vote where qid=" . $flwing_result->qid . " and uid=" . $user->uid . " ";

        $ress = db_query($update_quest);
    }
    echo "Cleared Successfully";
}

function reply_box() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

//print_r($_REQUEST);


    if ($_REQUEST['action'] == '1') {

        $sel_flow = "select * from notification as a, question as b  where a.uid=" . $user->uid . " and a.follower_action='1'  and a.is_question='1' and a.node_id=b.qid  and b.status='1'  order by a.nid desc ";
        $rs_folwin = db_query($sel_flow);

        while ($flwing_result = db_fetch_object($rs_folwin)) {
            //echo $uif=$flwing_result->qid;
            if ($_REQUEST[$uif] != '') {
                $update_quest = "delete  from possible_answer_vote where qid=" . $flwing_result->qid . " and uid=" . $user->uid . " ";
                $ress = db_query($update_quest);
                $insert_dumm = "insert into possible_answer_vote (qid,uid,panswer_id,vote_pdate) values ('" . $flwing_result->qid . "','" . $user->uid . "','" . $_REQUEST[$uif] . "','')";
                $ress = db_query($insert_dumm);
            } else {
                $update_quest = "delete  from possible_answer_vote where qid=" . $flwing_result->qid . " and uid=" . $user->uid . " ";
                $ress = db_query($update_quest);
            }
        }
    } else {

        $sids = $_REQUEST['usids'];
        $msg .= $_REQUEST['cmt_txt'];
        foreach ($sids as $idu) {


            $query = db_query("select * from users   where uid='" . $idu . "' ");
            $det = db_fetch_object($query);

            $to = $det->mail;

            if (!empty($to)) {

                $mail_suc = htmlmail($to, $subject, $msg, $from, '');


                $inmessage = db_query("insert into messages (from_id,to_id,message) values('" . $idu . "','" . $user->uid . "','" . $_REQUEST['cmt_txt'] . "')");
                if ($det->notify_itype == 1) {
                    $insert_notify = db_query("insert into notification (uid,is_message,is_user,node_id) values('" . $idu . "','1','1','" . $user->uid . "') ");
                }
            }
        }

        echo "Message sent ";
    }
}

function admin_notify() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    drupal_add_js(drupal_get_path('module', 'notify') . '/tinymce/jscripts/tiny_mce/tiny_mce.js');
    drupal_add_js(drupal_get_path('module', 'notify') . '/scripts/tiny.js');
    $linkval = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $adminmgmt = '<form id="myForm" name="myForm"  method="post" action="' . $gSitePath . 'admin/save_notify"  ><table width="100%" border="0">
  <tr>
    <td> <a href="' . $gSitePath . 'admin/notification/1">New followee Mail </a></td>
    <td> <a href="' . $gSitePath . 'admin/notification/2">Follower Blocking Mail </a></td>
    <td><a href="' . $gSitePath . 'admin/notification/3">New Answer approved  Mail </a></td>
    <td> <a href="' . $gSitePath . 'admin/notification/4">New Question Posted  Mail </a></td>
    <td><a href="' . $gSitePath . 'admin/notification/5">Post Like  Mail </a></td>
  </tr>';
    // echo $linkval;
    if ($linkval != 'notification') {
        $mid = $linkval;
    } else {
        $mid = '1';
    }
    $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='" . $mid . "'";
    $rs_mgmt = db_query($sel_user_cmt);
    $contenmt = db_fetch_object($rs_mgmt);



    $adminmgmt.='
</table>
<table width="100%" border="0">
 <tr colspan="6">
    <td>Subject : <input type="text" name="msub" value="' . $contenmt->subject . '"/></td>
   
  </tr>
<tr colspan="6">
    <td><textarea id="elm1" name="content" rows="15" cols="80">' . $contenmt->content . '</textarea></td>
    <input type="hidden" name="mlink" value="' . $mid . '"/>
  </tr>
   <tr colspan="6">
    <td><input type="submit" name="Submit" value="Save" class="btn"></td>
    
  </tr>
</table>







</form>';

    return $adminmgmt;
}

function admin_notify_save() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $mid = $_REQUEST['mlink'];
    $updatevoteposs = "update  notification_mail_format set subject='" . addslashes($_REQUEST['msub']) . "', content='" . addslashes($_REQUEST['content']) . "' where id='" . $_REQUEST['mlink'] . "'";
    db_query($updatevoteposs);

    drupal_goto("admin/notification/$mid");

    return $savelink;
}