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



    case 'filter':
      $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
      echo list_debate($qid, 1);
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










