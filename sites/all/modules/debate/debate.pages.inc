<?php

/**
 * The function to handle "/debate/ajax" callbacks
 *
 *
 */
function debate_ajax() {
  global $base_url, $user, $gDocPath, $base_root, $theme;
  # Extract the params: $_REQUEST['action'] to $action
  $action = '';
  $url = '';
  extract($_REQUEST);
  # Get site url with default language
  $sitelink = url('<front>', array('absolute' => TRUE)) . '/';

  # Switch $action
  switch( $action ) {
    case 'url' :
      if( empty($url) ) {
        exit("<div class='messages error'>".t('No URL provided.')."</div>");
      }
      _debate_ajax_url($url);
      break;
  }

  switch ($action) {
    case 'url' : break;
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
            }
            else if ($mtype == 2) {
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
        $tid = ugc_taxonomy_term_id('Resource', 'forum');
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

        $i = 0;
        foreach ($ans_id as $list) {
          $forum = "INSERT INTO {resource_options} set nid='%d',chorder='%d',ans_val='%d' ";
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
        $items = load_resource($nodeid, $qaid, $tnid, $res->field_rtype[0]['value']);


        // strength
        // anwers strength
        $strnth = $items['strength'];
        //echo '<pre>';print_r($strnth);exit;
        $strength = '';
        foreach ($strnth as $list) {
          $short_answer = get_short_answer($items['issue_id'], $list['chorder']);
          $tranAns = db_result(db_query("SELECT chtext FROM {poll_choices} WHERE nid = '" . $items['issue_id'] . "' AND chorder = '" . $list['chorder'] . "'"));
          $ans = $short_answer != '' ? $short_answer : $tranAns;

          switch ($list['ans_val']) {
            case 0:
              $strength.='<div><span class="yellow-box">+/-</span>' . $ans . '</div>';
              break;
            case 1:
              $strength.='<div><span class="green-box">+</span>' . $ans . '</div>';
              break;
            case 2:
              $strength.='<div><span class="red-box">-</span>' . $ans . '</div>';
              break;
          }
        }

        // delete
        if (is_moderator() || $items['uid'] == $user->uid) {
          $delete = theme('delete_button', $items['content_id'], $items['type'], 'Are you sure you want to delete this thread?');
        }

        // reply box
        $reply_box = '';
        $comments = '';
        $reply_count = db_result(db_query("SELECT COUNT(cid) FROM {comments} WHERE nid = '" . $items['resource_id'] . "'"));

        // ratings
        // allow rating check
        $ratings = theme('rating_button', $items);

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
      $colors = array('#55BA59',
        '#C2499B');
      for ($ab = 0; $ab < $cnt_ans; $ab++) {
        // short answers
        $short_answer = get_short_answer($qid, $vlist[$ab]['chorder']);
        $answer = $short_answer != '' ? $short_answer : $vlist[$ab]['chtext'];

        $insdata[] = $answer;

        //$sel = "select * from {debate_options} as o join {debate} as d on d.did=o.did  where o.paid='" . $vlist[$ab]['paid'] . "' AND o.ans_val IN ('1','2') group by o.did";
        $sel = "select * from {debate_options} as o join {content_type_forum} as d on d.nid=o.nid  where o.chorder='" . $vlist[$ab]['chorder'] . "' AND d.field_ref_qid_nid = '$tnid' AND o.ans_val IN ('1','2') group by o.nid";
        $tmplist = ExecuteQuery($sel, "select");

        $final = '';

        foreach ($tmplist as $key => $list) {

          //$cnt_opt = db_result(db_query("select count(paid) from {debate_options} where did=" . $list['did'] . " AND ans_val IN ('1','2')"));
          $cnt_opt = db_result(db_query("select count(chorder) from {debate_options} where nid=" . $list['nid'] . " AND ans_val IN ('1','2')"));

          $tmp = ($list['ans_val'] == 1) ? '1' : '-1';

          $final = $final + (($tmp * $list['field_strength_value']) / $cnt_opt);
          // echo $final.'<br>';
        }

        $final = (!empty($final)) ? $final : '0';
        $data[$ab]['y'] = $final;
        if ($final >= 0) {
          $data[$ab]['color'] = $colors[0];
        }
        else {
          $data[$ab]['color'] = $colors[1];
        }
        $data[$ab]['name'] = t('Strength');
      }

      print drupal_json(array('data' => $data, 'categories' => $insdata));
      /* jQuery(window).resize(function() {
        chart.destroy();
       */
      /*   echo $output.='<div id="container" class="highcharts-container" style="height:360px; width: 100%; margin: 0 auto; clear:both"></div>
        <div id="resource" style="height:auto; width: 400px; margin: 0 auto; clear:both"></div>
        '; */
      break;
    case 'resanalysis':
      $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
      //$vans = "select * from {possible_answer} where  qid=$qid ";
      $vans = "select * from {poll_choices} where  nid=$qid ";
      $vlist = ExecuteQuery($vans, "select");
      $cnt_ans = count($vlist);
      $output.="<link rel='stylesheet' href='" . $base_url . '/' . drupal_get_path('module', 'quest_lite') . "/plugins/jquery.jqplot.css' type='text/css' />
        <script type='text/javascript' src='http://code.jquery.com/jquery-1.4.2.min.js'></script>
       			<script type='text/javascript' src='" . $base_url . '/' . drupal_get_path('module', 'quest_lite') . "/scripts/highcharts.js'></script>
<script type='text/javascript' language='javascript'>

";
      $insdata.="[";
      $data.="[";

      for ($ab = 0; $ab < $cnt_ans; $ab++) {

        // short answers
        $short_answer = get_short_answer($qid, $vlist[$ab]['chorder']);
        $answer = $short_answer != '' ? $short_answer : $vlist[$ab]['chtext'];

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
      echo $output.='<div id="container" class="highcharts-container" style="height:360px; width: 100%; margin: 0 auto; clear:both; border: 1px solid red;"></div>
        <div id="resource" style="height:auto; width: 100%; margin: 0 auto; clear:both"></div>';

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
 
 
/**
 * Function to handle URL calls fro debate_ajax()
 *
 * @param url - the URL to handle
 */
function _debate_ajax_url($url) {
  global $base_url;

  # include required libraries
  require_once('simple_html_dom.php');
  require_once('thumbnail.php');
  require_once('url_to_absolute.php');

  # get html
  $html = file_get_html($url);
  if( !$html ) {
    exit('');
    # exit("<div class='messages error'>".t('Error loading URL')."</div>");
  }

  # get domain
  $domain = parse_url($url, PHP_URL_HOST);
  # get images
  $images = array();
  $images_source = $html->find('img');
  foreach( $images_source as $element ) {
    # $images[$element->src] = true;
    $images[] = url_to_absolute($url, $element->src);
  }
  $images = arguments_resource_validate_images($images);
  # get title
  $title = $html->find('title', 0);
  if( $title ) {
    $title = $title->innertext;
  }
  # get description
  $tags = get_meta_tags($url);
  $description = $tags['description'];
  # get image count
  $count = count($images);
  $image_count = $count > 10 ? '10' : $count;
  $image_first = $count > 0 ? 1 : 0;
  $image_last = $image_count != 0 ? ($image_count - 1) : 0;
  $image_path = $base_url . '/' . drupal_get_path('theme', 'hmware') . '/images/';
  # output
  echo theme('debate_ajax_url',
    $images, $image_count, $image_first, $image_last, $image_path,
    '<em>'.$title.'</em>source:&nbsp;<strong>'.$domain.'</strong><span>'.$description.'</span>'
  );
}

/**
 * The function to handle "/issue/debate/save" callbacks
 *
 *
 */
function debate_submit() {
  global $user;
  if( !user_is_logged_in() ) {
    exit("<small>Sorry, Please log in first before you can join this debate!</small>");
  }
  # $action - debate/resource/reply
  $action = '';
  $content_id = '';
  $parent_node = '';
  $agree = 1;
  extract($_REQUEST);
  #exit($action.'&'.$content_id.'&'.$parent_node.'&'.$agree);

  switch( $action ) {
    case  'debate'    :
    case  'resource'  :
    case  'reply'     :
      $json = array();
      $type = $action == 'reply' ? 'comment' : 'node';
      $not_voted = !yn_user_voted($content_id, $type);
      # add vote only for logged in user
      if( $not_voted && user_is_logged_in() ) {
        $coins_threshold = 0;
        # $coins_threshold = $agree == 1 ? get_coins('agree') : get_coins('disagree');
        if( $user->total_coins < $coins_threshold ) {
          $json['msg'] = '<em>Sorry! <strong>Error, You do not have enough coins.</strong></em>';
        } else {
          # add votes
          $vote_value = $agree == 1 ? VOTE_AGREE : VOTE_DISAGREE;
          yn_vote( $content_id, $vote_value, $type );
          # add like/dislike counts
          if( $action == 'reply' ) {
            $result = db_result(db_query("SELECT str_wk FROM {comments} WHERE cid = '%d'", $content_id));
            if( !$result ) {
              yn_invert_vote_value($vote_value);
            }
            yn_vote( $parent_node, $vote_value, 'node', VOTE_AUTOADD );
          }
          # recalculate votes
          list($json['vote_up'],$json['vote_dn'], $json['sum']) = yn_votes($content_id, $type);
          if( $type == 'node' ) {
            $node = node_load($content_id);
            $node->field_strength[0]['value'] = $json['sum'];
            node_save($node);
          }
          # add coin for agree and disagree
          $coin_type = $agree == '1' ? 'agree' : 'disagree';
          $coins = user_coins_update($user->uid, '', $coin_type);

          # insert guru points TODO -- this function's doing something somehow
          ### insertpoints($action, $content_id);
          # like notification TODO -- not supported when reply id is sent
          ### user_notify('like', array('nid' => $content_id));

          # RAM HEARTBEAT MODULE DEBATE REPLY UPDATE TODO -- there's no even such table in db!
          /*
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
          */
          # message
          if( $agree ) {
            $json['msg'] = "<em><strong>Agreed! </strong>You have $coins coins left.</em> ";
          } else {
            $json['msg'] = "<em><strong>Disagreed! &nbsp;</strong>You have $coins coins left.</em> ";
          }
          $json['error'] = '0';
          $json['type'] = $type;
          $json['likebar'] = theme('like_dislike_bar', $json['vote_up'], $json['vote_dn']);
        }
      } else {
        $json['error'] = '1';
        $json['msg'] = '<em>Sorry! <strong>Error</strong> occurs while updating.</em>';
      }
      list($json['pvote_up'],$json['pvote_dn'], $json['sum_count']) = yn_votes($parent_node, 'node');
      echo json_encode($json);
    break;
  }
  return;
}

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

