<?php

// $Id: issue.pages.inc,v 1.1.2.2 2010/06/22 11:33:06 mirodietiker Exp $

/**
 * @file
 * Page callbacks for the issue module.
 */

/**
 * List all issue as a page.
 */
function report_percent($nid='') {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $output = '';
    $filter = '';
    $incflt = '';
    $opt = '';
    if (!is_numeric($nid))
        return 'No Data Found';

    //$vans = "select * from {possible_answer} where  qid='" . $nid . "'";

    $vans = "select * from {poll_choices} where  nid='" . $nid . "' ORDER BY chorder";

    $vlist = ExecuteQuery($vans, "select");
    $cnt_ans = count($vlist);
    drupal_add_js(drupal_get_path('module', 'issue') . "/js/highcharts.js");
    drupal_add_js(drupal_get_path('module', 'issue') . "/js/skies.js");
    $inline = "var example = 'bar-stacked',
            theme = 'skies'";
    drupal_add_js($inline, 'inline');
    


    $ans_array = array();
    for ($ab = 0; $ab < $cnt_ans; $ab++) {

        $short_answer = get_short_answer($nid, $vlist[$ab]['chorder']);
        $answer = $short_answer != '' ? $short_answer : $vlist[$ab]['chtext'];

        array_push($ans_array, $answer);
        //array_push($ans_array, $vlist[$ab]['answer']);
    }
    $result = report_percent_broken($nid, '', $_REQUEST);
    //echo "<pre>";
    //print_r($result);
    $ans = $result['divide'];
    $cnt = $result['cnt'];

    foreach ($ans as $key => $value) {
        $ins_script .= "{name: '" .t(addslashes($ans[$key])) . "',data: " . $cnt[$key] . "},";
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
						defaultSeriesType:'bar',
                                                spacingRight: 300,
                                               
					},
					title: {
						text: ''
					},
					xAxis: {
						categories: " . json_encode($ans_array) . ",
                                                  labels :{ style: {
                  font: '10px Arial,Helvetica,sans-serif '
               }}
	},
					yAxis: {tickInterval  :1,
						min: 0,
						title: {
							text: ''
						},
                                                labels :{ style: {
                   font: '10px Arial,Helvetica,sans-serif '
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

        $incflt = '<script>jQuery(document).ready(function() {jQuery("#dochg").val(\'' . $filter . '\');});</script>';
    }


    $output .= '
<div id="contentr1" class="clear">
	' . $incflt . '
     <div style="padding-right:20px;" > <form id="form1" name="form1" method="post" action="">
Filter by :

  <select name="dochg" onchange="MM_jumpMenuGo(this.value);"  id="dochg">

  <option value="">Select</option>
  <option value="gender">Gender</option>
   <option value="age">Age</option>
    <option value="religion">Religion</option>
    <option value="ethnicity">Ethnicity</option>
    <option value="income">Income</option>
    <option value="marital">Marital</option>
     <option value="sorient">Sexual Orientation</option>
     <option value="edu">Education Level</option>
  </select></label>
  <span id="fopt" ></span>

    <br />
 </form></div>
    <div id="chart_div" style=" width:300px; height: 200px;">
    </div>
</div>';
    return $output;
}

function report_percent_broken($nid = '', $aid = '', $array = '') {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;


    $filter = '';
    $filter = (!empty($array['dochg'])) ? $array['dochg'] : '';
    $vans = "select * from {poll_choices} where  nid='" . $nid . "'  order by chorder";
    // $vans = "select * from {poll_choices} where  nid='" . $nid . "'";
    $vlist = ExecuteQuery($vans, "select");

    // IMPORTANT get translate nid (tnid) for current node
    $nid = get_tnid($nid);

    switch ($filter) {
        case 'gender':
            $answer['divide'] = array('male', 'female', 'undefined');




            foreach ($answer['divide'] as $list) {
                if ($list == 'male')
                    $gen = 1;
                elseif ($list == 'female')
                    $gen = 2;
                else
                    $gen='0';

                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND u.gender='" . $gen . "' ";
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
                    $query_ins = "AND u.age BETWEEN '31' AND '50'";
                elseif ($key == 2)
                    $query_ins = "AND u.age>='51' ";
                else
                    $query_ins = "AND u.age='0' ";


                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' " . $query_ins;
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
                    $reg = '0';
                else
                    $reg=$list;

                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND religion='" . $reg . "'";
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
                    $reg = '0';
                else
                    $reg=$list;

                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND ethnic='" . $reg . "'";
                    $tcnt = ExecuteQuery($query, "norows");
                    $inc_cnt .= $tcnt . ',';
                }
                $inc_cnt = rtrim($inc_cnt, ",");
                $inc_cnt .= ']';
                $answer_cnt[] = $inc_cnt;
            }


            break;
        case 'income':
            $answer['divide'] = array('$0-$9,999', '$10,000 - $19,999', '$20,000 - $39,999', '$40,000 - $69,999', '$70,000 - $99,999', '$100,000 - $149,999', '$150,000 - $299,999', '>$300,000', 'undefined');

            foreach ($answer['divide'] as $list) {
                if ($list == 'undefined')
                    $reg = '0';
                else
                    $reg=$list;


                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND income='" . $reg . "'";
                    $tcnt = ExecuteQuery($query, "norows");
                    $inc_cnt .= $tcnt . ',';
                }
                $inc_cnt = rtrim($inc_cnt, ",");
                $inc_cnt .= ']';
                $answer_cnt[] = $inc_cnt;
            }
            $answer['divide'] = array( '0' => '$0-$9,999', '1' => '$10,000 - $19,999', '2' => '$20,000 - $39,999', '3' => '$40,000 - $69,999', '4' => '$70,000 - $99,999', '5' => '$100,000 - $149,999', '6' => '$150,000 - $299,999', '7' => '>$300,000','8' => 'undefined');
            break;
        case 'marital':
            $answer['divide'] = array('Single', 'Married', 'Divorced', 'Widow', 'undefined');

            foreach ($answer['divide'] as $list) {
                if ($list == 'undefined')
                    $reg = '0';
                else
                    $reg=$list;


                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND marital='" . $reg . "'";
                    $tcnt = ExecuteQuery($query, "norows");
                    $inc_cnt .= $tcnt . ',';
                }
                $inc_cnt = rtrim($inc_cnt, ",");
                $inc_cnt .= ']';
                $answer_cnt[] = $inc_cnt;
            }

            break;
        case 'sorient':
            $answer['divide'] = array('Straight', 'Gay', 'Bisexual', 'Transgender', 'undefined');

            foreach ($answer['divide'] as $list) {
                if ($list == 'undefined')
                    $reg = '0';
                else
                    $reg=$list;


                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND sorient='" . $reg . "'";
                    $tcnt = ExecuteQuery($query, "norows");
                    $inc_cnt .= $tcnt . ',';
                }
                $inc_cnt = rtrim($inc_cnt, ",");
                $inc_cnt .= ']';
                $answer_cnt[] = $inc_cnt;
            }


            break;
        case 'edu':
            $answer['divide'] = array('No High School', 'High School', 'Technical College', 'Masters Degree', 'PhD', 'undefined');

            foreach ($answer['divide'] as $list) {
                if ($list == 'undefined')
                    $reg = '0';
                else
                    $reg=$list;


                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' AND edu='" . $reg . "'";
                    $tcnt = ExecuteQuery($query, "norows");
                    $inc_cnt .= $tcnt . ',';
                }
                $inc_cnt = rtrim($inc_cnt, ",");
                $inc_cnt .= ']';
                $answer_cnt[] = $inc_cnt;
            }


            break;

        default:
            $answer['divide'] = array('Total Votes');
            $inc_cnt = '[';
            for ($ab = 0; $ab < count($vlist); $ab++) {
                $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $vlist[$ab]['chorder'] . "' ";
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

function report_get_ans_range($nid='', $range='') {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    switch ($range) {
        case 'start':
            $query = "select date(date_voted) as dat from {poll_votes} where nid='" . $nid . "' ORDER BY date_voted ASC LIMIT 0,1 ";
            $answer = ExecuteQuery($query, "select");
            break;
        case 'end':
            $query = "select date(date_voted) as dat from poll_votes where nid='" . $nid . "' ORDER BY date_voted DESC LIMIT 0,1 ";
            $answer = ExecuteQuery($query, "select");
            break;
        default:
            $query = "select count(*) as cnt from poll_votes where nid='" . $nid . "' ";
            $answer = ExecuteQuery($query, "select");
            break;
    }
    return $answer[0];
}

function report_answer_details($nid = '', $aid = '', $action = '', $date = '') {
    switch ($action) {
        case 'percent':
            if ($_REQUEST['fopt']) {
                $opt = filter_opt($_REQUEST);

                $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $aid . "' $opt ";
                $answer = ExecuteQuery($query, "norows");
            } else {

                $query = "select * from {poll_votes} as p join {user_profile} as u on u.uid=p.uid where  p.nid='" . $nid . "' and p.chorder='" . $aid . "' ";
                $answer = ExecuteQuery($query, "norows");
            }


            return $answer;
            break;
        case 'timeline':
            $query = "select count(*) as cnt from {poll_votes} where nid='" . $nid . "' and chorder='" . $aid . "'AND date(date_voted)<='" . $date . "' ";
            $answer = ExecuteQuery($query, "select");

            return $answer ? $answer[0]['cnt'] : 'null';

            break;
    }
}

function report_graph($nid='') {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

    $output = '';

    $vans = "select * from {poll_choices} where  nid=$nid order by chorder";
    $vlist = ExecuteQuery($vans, "select");
    $cnt_ans = count($vlist);

    drupal_add_js(drupal_get_path('module', 'issue') . "/js/highcharts.js");
    drupal_add_js(drupal_get_path('module', 'issue') . "/js/skies.js");
    drupal_add_css(drupal_get_path('theme', 'hmware') . "/css/css.css");


    $output.= "
<script type='text/javascript' language='javascript'>

";

    $query = "select date(date_voted) as dat from {poll_votes} where nid='" . $nid . "' ORDER BY date_voted DESC";
    $list = ExecuteQuery($query, "select");
    $s1 = array();
    $grid = array();

    $srange = report_get_ans_range($nid, 'start');
    $erange = report_get_ans_range($nid, 'end');
    $count = report_get_ans_range($nid);
    //   echo $srange['dat'];
    //   echo $erange['dat'];
    //  echo $count['cnt'];exit;
    $query = "select DATEDIFF(date(now()),'" . $srange['dat'] . "') as diff,date(now()) as today";
    $overall_range = ExecuteQuery($query, "select");
    $frange = $overall_range[0]['diff'];
    $drange = dates_range($srange['dat'], $overall_range[0]['today']);
//print_r($drange);
    $drange = array_reverse($drange);
    for ($ab = 0; $ab < $cnt_ans; $ab++) {

        // short answers
        $short_answer = get_short_answer($nid, $vlist[$ab]['chorder']);
        $answer = $short_answer != '' ? $short_answer : $vlist[$ab]['chtext'];
        $answer=t(addslashes($answer));
        $i = $ab + 1;
        $ans = array();

        if (count($drange) > 6) {
            for ($mn = $frange; $mn >= 0; $mn--) {
                $date = $drange[$mn];

                $inc_this = report_answer_details($nid, $vlist[$ab]['chorder'], 'timeline', $date);
                array_push($ans, $inc_this);
            }
            $ins_sc = '[' . implode(',', $ans) . ']';
            array_push($grid, "'" . $answer . "'");
            $insdata.="{name :'" . $answer . "', data: " . $ins_sc . "},";

            $dexp = explode('-', $srange['dat']);

            $year = $dexp[0];
            $month = $dexp[1] - 1;
            $dat = $dexp[2];
            $sdate = "Date.UTC(" . $year . "," . $month . "," . $dat . ", 0, 0, 0)";
            $tickint = "";
        } else {
            for ($mn = 6; $mn >= 0; $mn--) {

                $year = date("Y");
                $month = date("m");
                $dat = date("d") - $mn;
                $date = date('Y-m-d', mktime(0, 0, 0, $month, $dat, $year));

                $inc_this = report_answer_details($nid, $vlist[$ab]['chorder'], 'timeline', $date);
                array_push($ans, $inc_this);
            }
            $ins_sc = '[' . implode(',', $ans) . ']';
            array_push($grid, "'" . $answer . "'");
            $insdata.="{name :'" . $answer . "', data: " . $ins_sc . "},";

            $sdate = "Date.UTC(" . $year . "," . ($month - 1) . "," . (date("d") - 6) . ")";
            $tickint = ",tickInterval: 24 * 3600 * 1000 // one day";
        }
    }

    $year = date("Y");
    $month = date("m") - 1;
    $dat = date("d");
    $edate = "Date.UTC(" . $year . "," . $month . "," . $dat . ")";
    // $script.=$ins_sc;



    $output.= "
var chart;
var gSitePath='" . $gSitePath . "';
var example = 'area-basic',
	theme = 'skies';
        Highcharts.theme = { colors: ['#4572A7'] };// prevent errors in default theme
	var highchartsOptions = Highcharts.getOptions();


jQuery(document).ready(function() {
   chart = new Highcharts.Chart({
      chart: {
         renderTo: 'container_graph',
         defaultSeriesType: 'spline',
         zoomType: 'x',
        
      },
      title: {
         text: ''
      },
      subtitle: {
         text: ''
      },
      xAxis: {
        labels: {
                style: {
                        color: '#666',
                        fontWeight: 'normal',
                        font: '10px Arial,Helvetica,sans-serif '

                },
                        rotation:270
		},
         type: 'datetime',
       plotBands: [{ // mark the weekend
            from: " . $sdate . ",
            to: " . $edate . "
        }] " . $tickint . "
      },
      yAxis: {
         title: {
            text: 'No Of Votes (Per Day)'
         },
         labels: {
                style: {
                        color: '#666',
                        fontWeight: 'normal',
                        font: '10px Arial,Helvetica,sans-serif '

                }
		},
         min: 0,
         minorGridLineWidth: 0,

         gridLineWidth: 0,
         alternateGridColor: null,
         tickInterval  :1
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
            pointInterval: 24 * 3600 * 1000, // one day
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
            qid:'" . $nid . "'
        },
   success: function(msg){
jQuery('#resource').html(msg);
   }
 });

}


</script>
";


    $output.='<div id="container_graph" class="highcharts-container" style="height:200px; width: 300px; "></div>
        <div id="resource" style="height:auto; width: 450px; margin: 0 auto; clear:both"></div>

';
    return $output;
}

function report_map($nid='') {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path, $googlekey;

    $inc_script = '';
    $resulte = '';
    $script = '';
    $desc = '';


    $marker = array('blue', 'green', 'red', 'black', 'brown', ' purple', 'yellow', 'gray', 'orange', 'white');

    $vans = "select * from {poll_choices} where  nid=$nid  order by chorder";
    $vlist = ExecuteQuery($vans, "select");
    $cnt_ans = count($vlist);

    $mlatall = '';
    $mlongall = '';
    $ziparyall = '';
    for ($i = 0; $i < $cnt_ans; $i++) {

        $pans = db_query("select * from {poll_votes} as pav left join {user_profile} as u on u.uid=pav.uid where pav.chorder='" . $vlist[$i]['chorder'] . "' AND pav.nid='$nid'");
        //$pans = db_query("select * from {users}  LIMIT 0,3");
        $ans_cnt = $i + 1;
        $getresult = array();
        while ($fieldsset = db_fetch_object($pans)) {

            $getresult[] = $fieldsset;
        }
        $pcnt_ans = count($getresult);

        // $desc .= '<img src="http://gmaps-samples.googlecode.com/svn/trunk/markers/'.$marker[$i].'/blank.png" border="0" alt=""/> &nbsp; '.$vlist[$i]['answer'].'<br/>';
        $desc .= '<img src="http://labs.google.com/ridefinder/images/mm_20_' . $marker[$i] . '.png" border="0" alt=""/> &nbsp; ' . $vlist[$i]['chtext'] . '&nbsp;&nbsp;';

        if (is_array($getresult)) {
            $zcnt = 0;

            foreach ($getresult as $for_zip_user) {
                $uzip = '';
                $uzip = $for_zip_user->zip;
                // $code = rand(600001, 600028);
                $cntcode = '';
                if (!empty($uzip)) {
                    $list = array();
                    $list = report_get_zip($uzip, $cntcode);
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




     $script.="<script type='text/javascript' >
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
    $zoom = "<span>Zoom to :</span> -
<span style='cursor: pointer;' onclick='map.setCenter(new GLatLng(21.943046, -51.328125), 2);'><u>Reset</u></span>";


    $filter = '<select onchange="zoomto(this.value);"><option value="-180,-90,0,90">Left hemisphere</option><option value="0,-90,180,90">Right hemisphere</option><optgroup label="Countries"><option value="22.3569164276123,41.2420806884766,28.6092796325684,44.2154502868652">Bulgaria</option><option value="-5.51891613006592,9.40110778808594,2.40539503097534,15.0825939178467">Burkina Faso</option><option value="28.9948463439941,-4.46461534500122,30.8477306365967,-2.31012296676636">Burundi</option><option value="102.343940734863,9.90625,107.626121520996,14.6860008239746">Cambodia</option><option value="43.2163543701172,-12.4138212203979,44.5382232666016,-11.3628215789795">Comoros</option><option value="11.2050085067749,-5.02722311019897,18.6498394012451,3.70308208465576">Congo</option><option value="13.493221282959,42.1301956176758,19.4491195678711,46.5336112976074">Croatia</option><option value="-176.64323425293,0.797774970531464,-176.635711669922,0.812214016914368">Howland Island</option><option value="-174.545059204102,-11.4370384216309,176.845108032227,4.71521615982056">Kiribati</option><option value="-61.0741500854492,13.7047777175903,-60.8742027282715,14.1032457351685">Saint Lucia</option><option value="-56.4206581115723,46.7532615661621,-56.1582107543945,47.1462860107422">Saint Pierre and Miquelon</option><option value="60.4784393310547,29.3774719238281,74.8785552978516,38.4834213256836">Afghanistan</option><option value="19.2767753601074,39.6444816589355,21.0572834014893,42.6610832214355">Albania</option><option value="-8.67386817932129,18.9600276947021,11.9795484542847,37.0915260314941">Algeria</option><option value="-171.088394165039,-14.3824787139893,-169.416076660156,-11.0518245697021">American Samoa</option><option value="1.42388892173767,42.4401626586914,1.78038907051086,42.6586952209473">Andorra</option><option value="11.680835723877,-18.0417594909668,24.0821208953857,-4.37682580947876">Angola</option><option value="-179.139190673828,18.9136848449707,179.776428222656,71.3906631469727">United States</option><option value="-58.4427223205566,-35.0479431152344,-53.0755386352539,-30.0822238922119">Uruguay</option><option value="-63.4325141906738,18.1668148040771,-62.9320373535156,18.6127872467041">Anguilla</option><option value="-180,-90,180,-60.5157585144043">Antarctica</option><option value="-62.3516807556152,16.9272193908691,-61.6613693237305,17.728967666626">Antigua and Barbuda</option><option value="-73.5829772949219,-55.0613174438477,-53.5918312072754,-21.7812767028809">Argentina</option><option value="43.449779510498,38.8312454223633,46.6300315856934,41.3014183044434">Armenia</option><option value="-70.0607833862305,12.4060926437378,-69.8761215209961,12.6306180953979">Aruba</option><option value="122.928695678711,-12.5325832366943,123.559524536133,-12.2509994506836">Ashmore and Cartier Islands</option><option value="112.911056518555,-54.7782554626465,159.111282348633,-9.18258380889893">Australia</option><option value="9.53591537475586,46.3780288696289,17.1627235412598,49.0170593261719">Austria</option><option value="44.771915435791,38.3983573913574,50.6067771911621,41.9056434631348">Azerbaijan</option><option value="50.3862228393555,25.5422496795654,50.8286437988281,26.2825832366943">Bahrain</option><option value="-176.484802246094,0.194290995597839,-176.47380065918,0.206694006919861">Baker Island</option><option value="88.0283279418945,20.5852508544922,92.6736755371094,26.6319465637207">Bangladesh</option><option value="-59.64892578125,13.0398435592651,-59.4235229492188,13.3269510269165">Barbados</option><option value="23.176887512207,51.2564125061035,32.769474029541,56.1658096313477">Belarus</option><option value="2.54694390296936,49.4936065673828,6.4038610458374,51.5054473876953">Belgium</option><option value="-89.2234725952148,15.8894281387329,-87.4725036621094,18.4965286254883">Belize</option><option value="0.774574995040894,6.22574758529663,3.85097622871399,12.4174184799194">Benin</option><option value="-64.8960494995117,32.2466354370117,-64.6553649902344,32.3901176452637">Bermuda</option><option value="88.7597198486328,26.7076396942139,92.1245651245117,28.3237781524658">Bhutan</option><option value="-69.6407623291016,-22.8961334228516,-57.4580955505371,-9.68056678771973">Bolivia</option><option value="15.720027923584,42.5602226257324,19.6219367980957,45.2391967773438">Bosnia and Herzegovina</option><option value="20,-26.907247543335,29.360782623291,-17.781774520874">Botswana</option><option value="3.34104180335999,-54.4623832702637,3.48797607421875,-54.4023056030273">Bouvet Island</option><option value="-73.9821701049805,-33.7505340576172,-28.8408145904541,5.26487731933594">Brazil</option><option value="71.2599716186523,-7.43802833557129,72.4926452636719,-5.22719383239746">British Indian Ocean Territory</option><option value="-64.8315200805664,18.3127365112305,-64.2770538330078,18.7566604614258">British Virgin Islands</option><option value="114.071441650391,4.00636053085327,115.359451293945,5.04716730117798">Brunei</option><option value="8.49497222900391,1.652547955513,16.1919918060303,13.0780563354492">Cameroon</option><option value="-141,41.7082939147949,-52.6362915039062,83.1066513061523">Canada</option><option value="-25.3564014434814,14.8022136688232,-22.6758079528809,17.195369720459">Cape Verde</option><option value="-81.4327774047852,19.2630271911621,-79.7272644042969,19.7614250183105">Cayman Islands</option><option value="14.4200963973999,2.22051382064819,27.4634227752686,11.0072717666626">Central African Republic</option><option value="13.4788265228271,7.44106769561768,24.0015850067139,23.4503707885742">Chad</option><option value="-109.455894470215,-55.9794960021973,-66.4180908203125,-17.5075511932373">Chile</option><option value="73.5587387084961,18.1612777709961,134.771575927734,53.560863494873">China</option><option value="105.539878845215,-10.5758619308472,105.719581604004,-10.4159154891968">Christmas Island</option><option value="-109.233299255371,10.2820692062378,-109.199317932129,10.3134508132935">Clipperton Island</option><option value="96.8245544433594,-12.1854162216187,96.9247512817383,-11.8039169311523">Cocos (Keeling) Islands</option><option value="-81.7241363525391,-4.22554445266724,-66.8698348999023,13.3902921676636">Colombia</option><option value="12.2041435241699,-13.4556751251221,31.305362701416,5.38609838485718">Congo, The Democratic Republic</option><option value="-165.858093261719,-21.944164276123,-157.312133789062,-8.94402980804443">Cook Islands</option><option value="149.12907409668,-17.7276382446289,155.860565185547,-16.0195007324219">Coral Sea Islands</option><option value="-87.0909652709961,5.49907398223877,-82.5565185546875,11.2168197631836">Costa Rica</option><option value="-8.59930229187012,4.35707759857178,-2.49489593505859,10.7366428375244">Cote D\'Ivoire</option><option value="-84.9574356079102,19.8280811309814,-74.1317749023438,23.5949268341064">Cuba</option><option value="32.2749404907227,34.6314964294434,34.5969734191895,35.701530456543">Cyprus</option><option value="12.0961933135986,48.542911529541,18.8601112365723,51.058780670166">Czech Republic</option><option value="8.07561016082764,54.562385559082,15.1582221984863,57.7480545043945">Denmark</option><option value="41.7734413146973,10.9099168777466,43.4160575866699,12.7068338394165">Djibouti</option><option value="-61.4841117858887,15.2016897201538,-61.2480926513672,15.6312808990479">Dominica</option><option value="-72.0034942626953,17.4700908660889,-68.3242645263672,19.929859161377">Dominican Republic</option><option value="124.979042053223,-9.36294555664062,127.304916381836,-8.3279447555542">Eastern Timor (Timor-Leste)</option><option value="-92.0107803344727,-4.99882316589355,-75.1845855712891,1.66477310657501">Ecuador</option><option value="24.6981105804443,21.7253875732422,36.2417793273926,31.6665840148926">Egypt</option><option value="-90.128662109375,13.1495923995972,-87.6965866088867,14.4450521469116">El Salvador</option><option value="5.60236692428589,-1.45994603633881,11.3347826004028,3.78598022460938">Equatorial Guinea</option><option value="36.438777923584,12.3596668243408,43.1480865478516,18.0030841827393">Eritrea</option><option value="21.7737216949463,57.5200538635254,28.2055015563965,59.687198638916">Estonia</option><option value="33.0001945495605,3.40242195129395,47.9861793518066,14.8937501907349">Ethiopia</option><option value="-61.3451957702637,-52.9005813598633,-57.7124824523926,-51.0149383544922">Falkland Islands (Islas Malvinas)</option><option value="-7.68125009536743,61.3949394226074,-6.25861072540283,62.400749206543">Faroe Islands</option><option value="138.052825927734,5.25983285903931,163.034896850586,11.6744441986084">Federated States of Micronesia</option><option value="-180,-20.6759700775146,180,-12.480110168457">Fiji</option><option value="19.3196926116943,59.7675819396973,31.5809440612793,70.0960540771484">Finland</option><option value="-5.14222240447998,41.3387756347656,9.56155681610107,51.0928077697754">France</option><option value="-54.539306640625,2.12709379196167,-51.6150588989258,5.77625942230225">French Guiana</option><option value="-154.688171386719,-27.6535720825195,-134.880523681641,-7.82849979400635">French Polynesia</option><option value="50.1766357421875,-50.0202674865723,77.598274230957,-37.7907218933105">French Southern and Antarctic Lands</option><option value="8.69573020935059,-3.97880601882935,14.5016717910767,2.32261204719543">Gabon</option><option value="40.0101356506348,41.0531959533691,46.7259712219238,43.5857772827148">Georgia</option><option value="5.86563873291016,47.275806427002,15.0398893356323,55.0550575256348">Germany</option><option value="-3.25542116165161,4.73672294616699,1.19178104400635,11.1733016967773">Ghana</option><option value="-5.35322237014771,36.1125259399414,-5.34002780914307,36.1598052978516">Gibraltar</option><option value="47.2800827026367,-11.5733966827393,47.2940711975098,-11.5492248535156">Glorioso Islands</option><option value="19.3744449615479,34.8096389770508,29.6455841064453,41.7574195861816">Greece</option><option value="-73.2634735107422,59.7772636413574,-11.3123188018799,83.6274261474609">Greenland</option><option value="-61.799976348877,11.9923734664917,-61.3776893615723,12.5292158126831">Grenada</option><option value="-63.1440391540527,15.8309726715088,-61,18.1306972503662">Guadeloupe</option><option value="144.619506835938,13.2406101226807,144.953308105469,13.6508884429932">Guam</option><option value="-92.2414932250977,13.7381963729858,-88.2231979370117,17.8174018859863">Guatemala</option><option value="-15.0862560272217,7.19355297088623,-7.64107084274292,12.6762208938599">Guinea</option><option value="-16.7175350189209,10.8599691390991,-13.6365213394165,12.6807899475098">Guinea-Bissau</option><option value="-61.384765625,1.17507994174957,-56.4802474975586,8.55756759643555">Guyana</option><option value="-74.4777145385742,18.0210304260254,-71.6133499145508,20.0878200531006">Haiti</option><option value="72.5965347290039,-53.1920013427734,73.856689453125,-52.9094123840332">Heard Island and McDonald Islands</option><option value="12.4434814453125,41.8991355895996,12.459584236145,41.9092025756836">Holy See (Vatican City State)</option><option value="-89.3499450683594,12.9824104309082,-83.1560516357422,17.4236297607422">Honduras</option><option value="113.837745666504,22.1532497406006,114.432861328125,22.5619487762451">Hong Kong</option><option value="16.111888885498,45.7436065673828,22.9060001373291,48.5851135253906">Hungary</option><option value="-24.5423412322998,63.2867546081543,-13.4958143234253,66.5625381469727">Iceland</option><option value="68.1629409790039,6.74713897705078,97.4033050537109,35.5042266845703">India</option><option value="95.0093307495117,-11.004861831665,141.021820068359,5.90441703796387">Indonesia</option><option value="44.0472755432129,25.0640811920166,63.3174743652344,39.7762222290039">Iran</option><option value="38.7896156311035,29.0612087249756,48.5759162902832,37.3809356689453">Iraq</option><option value="-10.6181116104126,51.4245567321777,-6.00255489349365,55.4365043640137">Ireland</option><option value="34.2203826904297,29.4915351867676,35.8947334289551,33.3337440490723">Israel</option><option value="6.61569356918335,35.4921913146973,18.5134468078613,47.0951995849609">Italy</option><option value="-78.3666381835938,17.7035522460938,-76.1803207397461,18.5269775390625">Jamaica</option><option value="122.938659667969,24.036470413208,153.984741210938,45.5231437683105">Japan</option><option value="-160.033142089844,-0.389006018638611,-160.004577636719,-0.368994981050491">Jarvis Island</option><option value="-169.542739868164,16.7265472412109,-169.51708984375,16.7411346435547">Johnston Atoll</option><option value="34.9579772949219,29.1850357055664,39.3012046813965,33.3712501525879">Jordan</option><option value="42.720832824707,-17.0631427764893,42.7592620849609,-17.0481777191162">Juan De Nova Island</option><option value="46.4918556213379,40.9363327026367,87.3125915527344,55.4511985778809">Kazakhstan</option><option value="33.9088554382324,-4.67804718017578,41.8990783691406,4.62933301925659">Kenya</option><option value="-162.896896362305,6.19838857650757,-162.294158935547,6.60813903808594">Kingman Reef</option><option value="46.5570602416992,28.5246105194092,48.4314765930176,30.1037006378174">Kuwait</option><option value="69.2766036987305,39.1728286743164,80.2826080322266,43.238224029541">Kyrgyzstan</option><option value="100.093055725098,13.910083770752,107.696754455566,22.5001964569092">Laos</option><option value="20.9742774963379,55.6688575744629,28.2411670684814,58.0818061828613">Latvia</option><option value="35.114875793457,33.0545616149902,36.6252174377441,34.6848564147949">Lebanon</option><option value="27.0290679931641,-30.6689643859863,29.4657611846924,-28.572057723999">Lesotho</option><option value="-11.4920835494995,4.35707759857178,-7.36511278152466,8.55179119110107">Liberia</option><option value="9.38785362243652,19.5080432891846,25.1480560302734,33.169002532959">Libya</option><option value="9.47780418395996,47.0615539550781,9.6321964263916,47.2735290527344">Liechtenstein</option><option value="20.9415264129639,53.9013023376465,26.8719444274902,56.4469184875488">Lithuania</option><option value="5.73455572128296,49.4465827941895,6.52700042724609,50.184944152832">Luxembourg</option><option value="20.4537353515625,40.8552207946777,23.0340957641602,42.3744812011719">Macedonia, The Former Yugoslav Republic of</option><option value="43.1913757324219,-25.6089534759521,50.4837837219238,-11.9454326629639">Madagascar</option><option value="32.6739463806152,-17.125,35.9168243408203,-9.36896133422852">Malawi</option><option value="98.9354934692383,0.85522198677063,119.267082214355,7.36341714859009">Malaysia</option><option value="72.684211730957,-0.692694008350372,73.706169128418,7.09836101531982">Maldives</option><option value="-12.2419233322144,10.1614255905151,4.24288845062256,25">Mali</option><option value="14.1915836334229,35.8102722167969,14.5776395797729,36.0810317993164">Malta</option><option value="165.260009765625,4.57486057281494,172.162017822266,14.6551675796509">Marshall Islands</option><option value="-61.2301216125488,14.392261505127,-60.8155097961426,14.8788194656372">Martinique</option><option value="-17.0663738250732,14.7155466079712,-4.82767486572266,27.29807472229">Mauritania</option><option value="56.5160026550293,-20.5257186889648,63.5001792907715,-10.3192548751831">Mauritius</option><option value="45.0224723815918,-13.00013256073,45.2929534912109,-12.6338367462158">Mayotte</option><option value="-118.453956604004,14.5380716323853,-86.7059326171875,32.7167625427246">Mexico</option><option value="-178.312774658203,28.1996631622314,-177.319320678711,28.4439697265625">Midway Islands</option><option value="26.6189422607422,45.4668807983398,30.1354446411133,48.4901695251465">Moldova</option><option value="7.39574956893921,43.7319717407227,7.45227813720703,43.7625045776367">Monaco</option><option value="87.7496566772461,41.5676345825195,119.92431640625,52.1542510986328">Mongolia</option><option value="-62.2425842285156,16.6710052490234,-62.1464157104492,16.8173294067383">Montserrat</option><option value="-13.168586730957,27.6621131896973,-0.991777956485748,35.9199180603027">Morocco</option><option value="30.2173194885254,-26.8686866760254,40.8444747924805,-10.4718828201294">Mozambique</option><option value="92.1892776489258,9.60036087036133,101.176254272461,28.5349731445312">Myanmar</option><option value="11.7165384292603,-28.9714317321777,25.2567005157471,-16.9598922729492">Namibia</option><option value="166.899932861328,-0.552333056926727,166.943206787109,-0.504971981048584">Nauru</option><option value="-75.027214050293,18.3967037200928,-75.0013275146484,18.4206371307373">Navassa Island</option><option value="80.056266784668,26.3567218780518,88.199333190918,30.4333915710449">Nepal</option><option value="3.36255598068237,50.7539176940918,7.22794437408447,53.5551414489746">Netherlands</option><option value="-69.1554641723633,11.9731969833374,-62.944751739502,18.0702495574951">Netherlands Antilles</option><option value="158.197631835938,-22.7146415710449,172.061386108398,-19.1038055419922">New Caledonia</option><option value="-178.627655029297,-52.6075820922852,179.102386474609,-29.2435512542725">New Zealand</option><option value="-87.6870422363281,10.7075424194336,-82.5920715332031,15.0259094238281">Nicaragua</option><option value="0.167994990944862,11.6969747543335,15.9956436157227,23.5250263214111">Niger</option><option value="2.66843199729919,4.27714395523071,14.678204536438,13.8920078277588">Nigeria</option><option value="-169.95100402832,-19.152193069458,-169.775161743164,-18.9537715911865">Niue</option><option value="167.919036865234,-29.11936378479,167.993743896484,-28.9953594207764">Norfolk Island</option><option value="124.189109802246,37.5973014831543,130.674880981445,43.0112953186035">North Korea</option><option value="144.886077880859,14.1073608398438,146.080307006836,20.5406951904297">Northern Mariana Islands</option><option value="-9.07860374450684,57.9665794372559,31.1381950378418,79.6883392333984">Norway</option><option value="52,16.6544017791748,59.8365821838379,26.3879737854004">Oman</option><option value="60.8786125183105,23.694694519043,77.8409194946289,37.0950317382812">Pakistan</option><option value="131.169219970703,3.00113892555237,134.723724365234,8.09291648864746">Palau</option><option value="-162.460922241211,5.86023092269897,-162.052642822266,5.89236116409302">Palmyra Atoll</option><option value="-83.0514450073242,7.19790697097778,-77.1768646240234,9.64443111419678">Panama</option><option value="140.842864990234,-11.6578617095947,159.47819519043,-0.877888977527618">Papua New Guinea</option><option value="111.196418762207,15.7754154205322,112.735176086426,16.9332237243652">Paracel Islands</option><option value="-62.6470794677734,-27.6087398529053,-54.2599678039551,-19.2940406799316">Paraguay</option><option value="-81.3258514404297,-18.3497295379639,-68.6792907714844,-0.0129769993945956">Peru</option><option value="116.93155670166,4.61344385147095,126.601524353027,21.1206111907959">Philippines</option><option value="-130.745101928711,-25.077522277832,-124.775924682617,-23.9178161621094">Pitcairn Islands</option><option value="14.1229991912842,49.0092506408691,24.1506671905518,54.8383636474609">Poland</option><option value="-31.2657527923584,30.1388874053955,-6.18269395828247,42.145637512207">Portugal</option><option value="-67.9395751953125,17.8830432891846,-65.2199859619141,18.5201663970947">Puerto Rico</option><option value="50.7572174072266,24.4733295440674,52.4275856018066,26.1775856018066">Qatar</option><option value="55.2190856933594,-21.3722114562988,55.8450393676758,-20.8568534851074">Reunion</option><option value="20.2643947601318,43.6273002624512,29.6910552978516,48.2652587890625">Romania</option><option value="-180,41.1888618469238,180,81.8567810058594">Russia</option><option value="28.8567924499512,-2.84067916870117,30.895959854126,-1.06239593029022">Rwanda</option><option value="-14.4212303161621,-40.3671417236328,-5.64036083221436,-7.89402198791504">Saint Helena</option><option value="-62.8675117492676,17.0953426361084,-62.5432624816895,17.4188270568848">Saint Kitts and Nevis</option><option value="-61.4592552185059,12.5301694869995,-61.1160049438477,13.3778343200684">Saint Vincent and the Grenadines</option><option value="-172.798538208008,-14.0635347366333,-171.41162109375,-13.4323930740356">Samoa</option><option value="12.4023523330688,43.8939590454102,12.5156879425049,44.0000419616699">San Marino</option><option value="6.47121953964233,-0.0140040004625916,7.46552801132202,1.70132303237915">Sao Tome and Principe</option><option value="34.4956893920898,15.6142492294312,55.6666984558105,32.1543273925781">Saudi Arabia</option><option value="-17.5352363586426,12.3072748184204,-11.3568553924561,16.6915531158447">Senegal</option><option value="46.2001495361328,-10.1937065124512,56.2753791809082,-3.71151876449585">Seychelles</option><option value="-13.3076305389404,6.92868852615356,-10.2843294143677,9.99999904632568">Sierra Leone</option><option value="103.639724731445,1.16402792930603,104.088249206543,1.4712780714035">Singapore</option><option value="16.847749710083,47.7281074523926,22.5704441070557,49.6031723022461">Slovakia</option><option value="13.3830833435059,45.4131355285645,16.5660018920898,46.8779182434082">Slovenia</option><option value="155.508605957031,-12.2918891906738,168.843521118164,-5.07830572128296">Solomon Islands</option><option value="40.9886283874512,-1.66205310821533,51.4130325317383,11.9851942062378">Somalia</option><option value="16.4597396850586,-46.978931427002,37.9976196289062,-22.1266117095947">South Africa</option><option value="-41.8118782043457,-59.4842987060547,-26.2301902770996,-53.6485786437988">South Georgia and the South Sandwich Islands</option><option value="124.611190795898,33.1061096191406,130.923233032227,38.6124496459961">South Korea</option><option value="-18.1665706634521,27.6388187408447,4.31538915634155,43.7917213439941">Spain</option><option value="114.029525756836,9.67947196960449,115.846031188965,11.1179723739624">Spratly Islands</option><option value="79.654655456543,5.91683292388916,81.8812866210938,9.83136177062988">Sri Lanka</option><option value="21.8396377563477,3.48638987541199,38.579475402832,23.1468906402588">Sudan</option><option value="-58.0863990783691,1.83114492893219,-53.9774894714355,6.00454616546631">Suriname</option><option value="10.49072265625,74.3457489013672,36.8152770996094,80.8323974609375">Svalbard</option><option value="30.7941055297852,-27.3169918060303,32.1367034912109,-25.7196464538574">Swaziland</option><option value="10.9911108016968,55.3371086120605,24.1632785797119,69.0625">Sweden</option><option value="5.95747184753418,45.8256912231445,10.4914722442627,47.8051681518555">Switzerland</option><option value="35.727222442627,32.3161888122559,42.3704643249512,37.3191413879395">Syria</option><option value="116.706657409668,20.6974983215332,122.000442504883,26.3920555114746">Taiwan</option><option value="67.3922729492188,36.6741333007812,75.1372222900391,41.0412254333496">Tajikistan</option><option value="29.3271656036377,-11.7456960678101,40.4432220458984,-0.990735948085785">Tanzania</option><option value="97.3484115600586,5.60999965667725,105.63786315918,20.4631958007812">Thailand</option><option value="-80.4992370605469,20.9160652160645,-72.7115936279297,27.232027053833">The Bahamas</option><option value="-16.825080871582,13.0642518997192,-13.8052921295166,13.8265705108643">The Gambia</option><option value="-0.145849004387856,6.104416847229,1.8066930770874,11.1389770507812">Togo</option><option value="-172.499420166016,-9.38111114501953,-171.21142578125,-8.55388736724854">Tokelau</option><option value="-176.211334228516,-22.3457183837891,-173.70246887207,-15.5629873275757">Tonga</option><option value="-61.9237747192383,10.0361042022705,-60.4895515441895,11.3343181610107">Trinidad and Tobago</option><option value="54.5148315429688,-15.8935108184814,54.5249710083008,-15.8797283172607">Tromelin Island</option><option value="7.5248327255249,30.2404174804688,11.5982780456543,37.5439186096191">Tunisia</option><option value="25.6709728240967,35.8154144287109,44.8338356018066,42.1075820922852">Turkey</option><option value="52.4414405822754,35.1410827636719,66.6843032836914,42.7955551147461">Turkmenistan</option><option value="-72.480842590332,21.1700344085693,-71.0803375244141,21.9712448120117">Turks and Caicas Islands</option><option value="176.065032958984,-9.43619441986084,179.861907958984,-5.64336061477661">Tuvalu</option><option value="29.5732517242432,-1.48405003547668,35.0360527038574,4.21442604064941">Uganda</option><option value="22.1303615570068,44.3904113769531,40.2073936462402,52.3686370849609">Ukraine</option><option value="51.5076332092285,22.634069442749,56.3750877380371,26.076416015625">United Arab Emirates</option><option value="-8.64963912963867,34.5650253295898,33.9176940917969,60.8458061218262">United Kingdom</option><option value="55.9981117248535,37.1843338012695,73.1322784423828,45.5996780395508">Uzbekistan</option><option value="166.524978637695,-20.2489452362061,170.234085083008,-13.0734434127808">Vanuatu</option><option value="-73.3540802001953,0.627002954483032,-59.8062973022461,12.2019033432007">Venezuela</option><option value="102.14958190918,8.4082498550415,109.464645385742,23.3888359069824">Vietnam</option><option value="-65.0862884521484,17.6817245483398,-64.5651779174805,18.4118766784668">Virgin Islands</option><option value="166.611892700195,19.2695255279541,166.650817871094,19.3167247772217">Wake Island</option><option value="-178.203842163086,-14.387791633606,-176.128768920898,-13.2142505645752">Wallis and Futuna</option><option value="-17.1031837463379,20.7741565704346,-8.67027568817139,27.6670207977295">Western Sahara</option><option value="41.8160514831543,12.1110820770264,54.5294761657715,19">Yemen</option><option value="18.4339809417725,41.8524208068848,23.0052738189697,46.1894454956055">Yugoslav Republic (Serbia and Montenegro)</option><option value="21.999662399292,-18.079475402832,33.7057075500488,-8.2243595123291">Zambia</option><option value="25.2371768951416,-22.4177398681641,33.0550193786621,-15.6093597412109">Zimbabwe</option></optgroup></select>';
    $out .= $script;
    //$out .= '<script type="text/javascript">window.onload=start(); window.onunload=GUnload;</script>';
    $out .= '<script type="text/javascript">window.onunload=GUnload;</script>';
    
    $out .= '
    <div  class="">
        ' . $zoom . '<span style="padding-right:10px ">' . $filter . '</span></div>
            </br>
        <div id="map_div" style="width: 300px; height: 150px"></div><br/>
        <div style="position: relative;" id="desc">' . $desc . '</div>
';
    return $out;
}


// report vote percent(redesign)
function report_vote_percent(){
    $perc .= '<p>90% of the voters are between the ages of 20 and 30.</p>';
    $perc .= '<p>65% of Christians voted Yes.</p>';
    $perc .= '<p>Users with Masters Degrees are 2 times as likely to vote No.</p>';
    $perc .= '<p>65% of Christians voted Yes.</p>';
    $perc .= '<p>74% Income Range between $40,000 - $69,000 are voted No.</p>';
    $perc .= '<p>15% Asian people voted Yes.</p>';
    return $perc;
}


function report_get_zip($code = '', $ccode = '') {

    $query = array('postalcode' => $code, 'maxrows' => 1);
    $result = geonames_query('postalcodesearch', $query);

    return $result;
}

// add new issue

function issue_create() {
    $issueForm = drupal_get_form('issue_create_form');
    return $issueForm;
}

function issue_create_form(&$form_state) {


    //drupal_add_js( drupal_get_path('module', 'question') . '/scripts/post_list.js');
    if (isset($form_state['action'])) {
        $form['#action'] = $form_state['action'];
    }
    //$form['#attributes'] = array('onsubmit' => 'return validate_question()');
    $form['issue_cont'] = array('#type' => 'markup', '#value' => '<div ><ul id="add_more">');
    $form['title_div'] = array('#type' => 'markup', '#value' => '<li><label><span>');
    $form['q_quest'] = array('#type' => 'textfield', '#maxlength' => 140, '#suffix' => '
                                </span></label><small id="numberofword">140</small><small> ' . t('Chars Left.') . '</small>
                                <span class="span1">&nbsp;</span>
                                </li>', '#required' => TRUE, '#id' => 'q_quest', '#title' => t('Enter Question'),
        '#ahah' => array('path' => 'issue/get_related_issues', 'wrapper' => 'related-issues', 'effect' => 'fade'),
        '#attributes' => array('onkeyup' => 'CountlimitChars()'));
    $form['desc_div'] = array('#type' => 'markup', '#value' => '<li><label><span>');
    $form['q_context'] = array('#type' => 'textarea', '#rows' => 4, '#suffix' => '</span></label></li>', '#title' => t('Enter Context'));
//    $form['choices'][] = array('#type' => 'textfield', '#prefix' => ' <li><label><span>', '#suffix' => '</span></label></li>', '#required' => TRUE, '#id' => 'q_ans1', '#title' => 'Option1');
//    $form['choices'][] = array('#type' => 'textfield', '#prefix' => '<li><label><span>', '#suffix' => '</span></label></li>', '#required' => TRUE, '#id' => 'q_ans2', '#title' => 'Option2');

    if (isset($form_state['choice_count'])) {
        $choice_count = $form_state['choice_count'];
    } else {
        $choice_count = 2;
    }

    $form['choice_wrapper'] = array(
        '#tree' => FALSE,
        '#prefix' => '<div class="clear-block" id="poll-choice-wrapper">',
        '#suffix' => '</div>',
    );


// Container for just the poll choices.
    $form['choice_wrapper']['answer'] = array(
        '#prefix' => '<div id="poll-choices">',
        '#suffix' => '</div>',
        '#theme' => 'issue_answer',
    );


// Add the current choices to the form.
    for ($delta = 0; $delta < $choice_count; $delta++) {
        $form['choice_wrapper']['answer'][$delta] = _issue_answer_form($delta);
    }


// We name our button 'poll_more' to avoid conflicts with other modules using
    // AHAH-enabled buttons with the id 'more'.
    $form['choice_wrapper']['poll_more'] = array(
        '#type' => 'submit',
        '#value' => t('Add Another Answer'),
        '#description' => t("If the amount of boxes above isn't enough, click here to add more choices."),
        '#weight' => 1,
        '#ahah' => array(
            'path' => 'issue/autotextfields/callback',
            'wrapper' => 'poll-choices',
            'method' => 'replace',
            'effect' => 'fade',
        ),
    );



    $form['exist_check'] = array('#type' => 'hidden', '#value' => '', '#id' => 'exist_check');
    $form['issue_cont_close'] = array('#type' => 'markup', '#value' => '</ul><div class="clr"></div>');

    $form['related_issues'] = array(
        '#title' => t("Related Issues"),
        '#prefix' => '<div id="related-issues">',
        '#suffix' => '</div>',
        '#type' => 'fieldset',
    );

    if ($form_state['values']['q_quest']) {

        $question = $form_state['values']['q_quest'];

        // define a string variable to contain callback output
        $output = "";

        // loop through the taxonomy tree and fetch child taxonomies
        $options = array();

        $res = get_releated_issues($question);
        
        if (!empty($res)) {
            $nids = $res['nid'];
            $contents = $res['content'];
            $i = 0;
            if (!empty($contents)) {
                foreach ($contents as $key => $result) {
                    $array[$nids[$key]] = $result;

                    $i++;
                }

                $form['related_issues']['rel_iss_check'] = array('#type' => 'checkboxes',
                    '#options' => $array);
            } else {
                $form['related_issues']['no_rel'] = array('#type'=>'markup', '#value' =>'No Related Issues');
            }
        }else{
            $form['related_issues']['no_rel'] = array('#type'=>'markup', '#value' =>'No Related Issues');
        }
    }

    $form['dupe_count'] = array('#type' => 'hidden', '#id' => 'dupe_count', '#default_value' => 0);
    //$form['#validate'][] = 'issue_create_form_validate';

    $form['submit'] = array('#type' => 'submit', '#attributes' => array('class' => 'question-save'), '#value' => t('SUBMIT NEW ISSUE'), '#id' => 'save_issue');
    //$form['#redirect'] = '';

    $form['#cache'] = TRUE;
    return $form;
}

function issue_form_validate($form, &$form_state) {
    if ($form['form_id']['#post']['answer'][0] == '' || $form['form_id']['#post']['answer'][1] == '') {
        $error = 'You must fill in at least two choices.';
    }
    return $error;
}

function issue_autotextfields_callback() {
    $delta = count($_POST['answer']);

    // Build our new form element.
    $form_element = _issue_answer_form($delta);
    // drupal_alter('form', $form_element, array(), 'issue/autotextfields/callback');
    // Build the new form.
    $form_state = array('storage' => NULL, 'submitted' => FALSE);
    $form_build_id = $_POST['form_build_id'];

    // Add the new element to the stored form. Without adding the element to the
    // form, Drupal is not aware of this new elements existence and will not
    // process it. We retreive the cached form, add the element, and resave.
    $form = form_get_cache($form_build_id, $form_state);
    $args = $form['#parameters'];
    $form_id = array_shift($args);
    $form['choice_wrapper']['answer'][$delta] = $form_element;
    form_set_cache($form_build_id, $form, $form_state);
    $form += array(
        '#post' => $_POST,
        '#programmed' => FALSE,
    );
    $form_state['post'] = $_POST;
    // Build, validate and if possible, submit the form.
    $form_state['action'] = $form['#action'];
    $form_state['rebuild'] = TRUE;
    drupal_process_form($form_id, $form, $form_state);
    // Rebuild the form.
    $form = form_builder($form_id, $form, $args, $form_state);
   
//  $validate = issue_form_validate($form, $form_state);
//  if($validate){$delta = 1;}
    // Render the new output.

    $choice_form = $form['choice_wrapper']['answer'];
    unset($choice_form['#prefix'], $choice_form['#suffix']); // Prevent duplicate wrappers.
    $choice_form[$delta]['#attributes']['class'] = empty($choice_form[$delta]['#attributes']['class']) ? 'ahah-new-content' : $choice_form[$delta]['#attributes']['class'] . ' ahah-new-content';
    //$choice_form[$delta]['chvotes']['#value'] = 0;
    $output = drupal_render($choice_form);

    drupal_json(array('status' => TRUE, 'data' => $output));
}

function _issue_answer_form($delta, $value = '', $votes = 0) {
    $form = array(
        '#tree' => TRUE,
    );

    // We'll manually set the #parents property of these fields so that
    // their values appear in the $form_state['values']['choice'] array.
    // limited fields 10 (0 to 9)
    if ($delta == 0 || $delta == 1) {
        $req = TRUE;
    } else {
        $req = FALSE;
    }
    if ($delta < 10) {
        $form['chtext'] = array(
            '#type' => 'textfield',
            '#title' => t('Choice @n', array('@n' => ($delta + 1))),
            '#default_value' => $value,
            '#parents' => array('answer', $delta),
            '#prefix' => '<li><label><span>', '#suffix' => '</span></label></li>',
            '#required' => $req,
        );
    } else {
        $form['error_msg'] = array(
            '#type' => 'markup',
            '#value' => 'Maximum Fields Exceeded',
            '#prefix' => '<li><label><span class="error">', '#suffix' => '</span></label></li>',
        );
    }
    return $form;
}

function issue_related_callback() {

    $form_state = array('storage' => NULL, 'submitted' => FALSE);
    $form_build_id = $_POST['form_build_id'];
    $form = form_get_cache($form_build_id, $form_state);
    $delta = count($_POST['answer']);

    $args = $form['#parameters'];
    $form_id = array_shift($args);
    $form_state['post'] = $form['#post'] = $_POST;
    $form['#programmed'] = $form['#redirect'] = FALSE;
// Stash original form action to avoid overwriting with drupal_rebuild_form().
    $form_state['action'] = $form['#action'];
    $form_state['rebuild'] = TRUE;
    $form_state['choice_count'] = $delta;
    drupal_process_form($form_id, $form, $form_state);
    $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);

    //$form = form_builder($form_id, $form, $form_state);

    $textfields = $form['related_issues'];
    $output = drupal_render($textfields);


// Final rendering callback.
    print drupal_json(array('status' => TRUE, 'data' => $output));
    exit();
}

function issue_create_form_submit($form, &$form_state) {
    //echo '<pre>'; print_r($form_state); exit;
    global $user, $gSitePath;


    $account = user_load(array('uid' => $user->uid));
    $node = new StdClass();
    $node->type = 'poll';
    $node->create = time();
    $node->title = $form_state['values']['q_quest'];
    $node->body = $form_state['values']['q_context'];
    $node->uid = $account->uid;
    $node->status = 1;
    $node->active = 1;
    //$node->path=
    // LANGUAGE DETECTION
    // detect language from inputs using googleapis
    $inputLanguage = get_input_language($form_state['values']['q_quest']);

    $node->language = $inputLanguage; // set user input language
    $node->field_mod_status[0]['value'] = 0;
    if (!user_access('administer nodes')) {
        $node->active = 1;
    }
    $count = count($form_state['values']['answer']);
    for ($i = 0; $i < $count; $i++) {
        $node->choice[$i]['chtext'] = $form_state['values']['answer'][$i];
        $node->choice[$i]['chorder'] = $i;
        // Make sure all votes are 0 initially
        $node->choice[$i]['chvotes'] = 0;
    }
    //echo '<pre>'; print_r($node); exit;
    node_save($node);

    /* New SET NOTIFY LOG */
    //set_notify_log($uid , $message_id, $nid, $variable)
    $qid = $node->nid;
    $qtitle = $node->title;
    $variable = array('qid' => $qid, 'q_title' => $qtitle, 'uid' => $user->uid);
    set_notify_log($user->uid, $qid, 'add_question', $variable);
    /* New SET NOTIFY LOG */
    //url alias
    $dst = clean_url(myTruncate($node->title, 100, ''), '', '-', $node->nid);
    $url = 'node/' . $node->nid;
   // db_query("INSERT INTO {url_alias} (src, dst, language) VALUES ('%s', '%s', '%s')", $url, $dst, $inputLanguage);

    path_set_alias($url, $dst,'',$inputLanguage);

    // return $node;
    // insert default debate for each issue
    $deb = new stdClass();
    $deb->field_private[0]['value'] = '';
    $deb->field_ref_qid[0]['nid'] = $node->nid;
    $deb->field_type[0]['value'] = '1';

    $deb->type = 'forum';
    $deb->title = 'What you think about this issue!';
    $deb->uid = $user->uid;
    $deb->body = "Let's have a debate";
    $deb->status = 1;
    // get tid for debate
    // get_taxonomy_id('module name','term data name')
    $tid = get_taxonomy_id('forum', 'Debate');
    $deb->taxonomy = array($tid);
    $deb->language = 'en'; // set current language
    // language status, initially language status is 0
    $deb->field_lang_status[0]['value'] = 0;

    //node_validate($deb);
    //$node = node_submit($deb);
    //$save = node_save($deb);

    // add default debate options
    $choices = db_query("SELECT * FROM {poll_choices} WHERE nid = '$node->nid'");
    while ($list = db_fetch_object($choices)) {
        //$forum = "INSERT INTO {debate_options} set did='%d', paid='%d',ans_val='%d' ";
        $forum = "INSERT INTO {debate_options} set nid = '%d',chorder='%d',ans_val='%d' ";
        db_query($forum, $deb->nid, $list->chorder, 1);
    }

    //Related Issues
    if (!empty($form_state['values']['rel_iss_check'])) {
        $cont_type = array('content_types' => array('poll' => 'poll'));
        $relatedissues = array_combine($form_state['values']['rel_iss_check'], $form_state['values']['rel_iss_check']);
        $arrayid = array('nids' => $relatedissues);
        $manual = array('enable' => 1, 'nodes' => array('poll' => $arrayid));
        $related = array('nid' => $node->nid, 'content_types' => $cont_type, 'taxonomy' => array(''), 'manual' => $manual, 'sort' => array('criteria' => 'none'));
        db_query("INSERT INTO {noderecommendation_node} (nid, data) VALUES (%d, '%s')", $node->nid, serialize($related));
    }

    cache_clear_all();
    $output = drupal_set_message(t('Your issue has been added.  It will be reviewed by 3 moderators but is available immediately.
'), $type = 'success');
    unset($_SESSION['post']);
    $_SESSION['post'] = '';
    $path = db_result(db_query("SELECT dst FROM {url_alias} WHERE src = 'node/%d' LIMIT 1",$node->nid));
    if(empty ($path))
     $path = drupal_get_path_alias(getPathAlias($node->nid));

    increasepoints('1', $node->nid, '0');
    //_send_qnotify($node->nid);
    //drupal_goto($path);
    //echo '<script>window.parent.location.href="' . $gSitePath . $path . '";</script>';
    drupal_goto($gSitePath.$inputLanguage.'/'.$path);
}
function getPathAlias($nid){
	$alias = 'node/'.$nid;

	//check for an alias using drupal_lookup_path()
	if((drupal_lookup_path('alias', 'node/'.$nid)!==false))
		$alias = drupal_lookup_path('alias', 'node/'.$nid);

	return $alias;
}
function get_releated_issues($question = '', $cat_id = '', $context = '') {
    //$form = array('#tree'=>TRUE);

    $currLanguage = i18n_get_lang();
    $where_condition = '';
    $words = explode(" ", $question);
    $words = array_filter($words, 'word_array_filter');
    $words = array_filter($words);
    for ($i = 0; $i < count($words); $i++) {
        $wheres2 = array();
        if ($words[$i] != '') {
            $wheres2[] = "  q.title  LIKE CONVERT(_utf8 '%$words[$i]%' USING latin1 ) COLLATE latin1_swedish_ci";
            $wheres[] = implode(' OR ', $wheres2);
        }
    }
    $where_condition = '((' . implode(($match == 'all' ? ') AND (' : ') OR ('), $wheres) . '))';

    if ($context != '') {
        $words = explode(" ", $context);
        for ($i = 0; $i < count($words); $i++) {
            $wheres2 = array();
            if ($words[$i] != '') {
                $wheres2[] = "  q.context  LIKE CONVERT(_utf8 '%$words[$i]%' USING latin1 ) COLLATE latin1_swedish_ci";
                $wheres1[] = implode(' OR ', $wheres2);
            }
        }
        $where_condition .= ' and ((' . implode(($match == 'all' ? ') AND (' : ') OR ('), $wheres1) . '))';
    }
    if ($cat_id != 0) {
        $where_condition .= " and qc.cat in ($cat_id)";
    }
    $text = "$question $context";
    $text = trim($text);
    //printf("SELECT r.nid,r.title FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' AND MATCH(r.body, r.title) AGAINST ('%s') AND n.language = '%s' GROUP BY n.nid  ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10",$text, $currLanguage);
//printf("SELECT count(MATCH(r.body, r.title) AGAINST ('%s')) FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' GROUP BY n.nid ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10",$text,0);
    $count = db_result(db_query("SELECT COUNT(n.nid) FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' GROUP BY n.nid AND MATCH(r.body, r.title) AGAINST ('%s') AND n.language = '%s' ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10", $text, $currLanguage));
    $rel_output.= '<div class="innerbox" style="width:auto;height:auto; overflow:auto; min-height:150px;"><ul>';
    if (($count != 0) && ($question != '')) {
        $rel_count = 1;
        $rel_query = db_query("SELECT r.nid,r.title FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' AND MATCH(r.body, r.title) AGAINST ('%s') AND n.language = '%s' GROUP BY n.nid  ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10", $text, $currLanguage);
        //$sql = "SELECT r.nid,r.title FROM {node_revisions} r INNER JOIN {node} n ON r.nid = n.nid AND r.vid = n.vid WHERE n.status <> 0 AND n.type='poll' AND n.title LIKE '%$question%' GROUP BY n.nid  ORDER BY n.nid DESC, r.vid DESC LIMIT 0,10";
        //$rel_query = db_query($sql);
        while ($rel_options = db_fetch_object($rel_query)) {

            $form['mycheck_' . $rel_count] = array('#type' => 'checkbox', '#default_value' => $rel_count, '#title' => substr($rel_options->title, 0, 50));


            $rel_output .= substr($rel_options->title, 0, 50) . '...</li>';
            $content[] = substr($rel_options->title, 0, 50);
            $ids[] = $rel_options->nid;
            $rel_count++;
        }
    } else {
        $rel_output.= t('No Releated issues available');
    }

    $rel_output.= '</ul></div>';
    $quest = array($rel_count, $content);
    $conResult = array('content' => $content, 'nid' => $ids);
    return $conResult;
    //return $form;
//echo "SELECT q.qid, q.question FROM {question} q  left join question_cat qc on qc.qid=q.qid  WHERE $where_condition  group by q.qid ";
}


// issue list here
function issues_list(){
    $output = '';
    //drupal_add_js(drupal_get_path('module','issue').'/js/filter.js');
    $output .= '<div class="search-left">';
    $output .= drupal_get_form('issue_search_form');
    $output .= '</div>
                <div class="search-right">';
    $output .= '<b>'.t('ISSUES').'</b>&nbsp;<b>[&nbsp;</b>'.t('INDICATE SEARCH STATE LIKE KEYWORD, SUBJECT, ETC').'<b>&nbsp;]</b><br /><br />';
    $output .= search_issue_results();
    $output .= '</div><div class="clr"></div>';
    return $output;
}
function issue_search_form(&$form_state){
    //$form['#method'] = 'get';
    $key = arg(1)=='0'?'':check_plain(arg(1));
    $subject = check_plain(arg(2));
    $area = check_plain(arg(3));
    $detail = check_plain(arg(4));
    $getcountry = check_plain(arg(5));
    $getState = check_plain(arg(6));
    $getCity = check_plain(arg(7));
    
    $form['issue_key'] = array('#type' => 'textfield',
                                '#title' => t('SEARCH ISSUES'),
                                '#size' => 40,
                                '#default_value' => $key);
    $form['category_mark'] = array('#type' => 'markup', '#value' => t('FILTER BY CATEGORY').'<br /><div class="clr"></div>');
    /*categories*/
    $vid = db_result(db_query("SELECT vid FROM {vocabulary} WHERE name = '%s' AND module = '%s'", 'Sections', 'taxonomy'));
    $client_select = db_query("SELECT t.tid AS cat_id, t.name AS cat_name FROM term_data t RIGHT JOIN term_hierarchy h ON t.tid = h.tid where h.parent='0' AND t.vid = '$vid'");
    $options[''] = 'SUBJECT';
    while ($list = db_fetch_object($client_select)) {
        $cnt = taxonomy_term_count_nodes($list->cat_id);
        if($cnt!=0){
        $options[$list->cat_id] = t(stripslashes($list->cat_name));
        }
    }
    $form['subject'] = array('#type' => 'select',
                            '#options' => $options,
                            '#prefix' => '<div style="float:left;">',
                            '#suffix' => '</div>',
                            '#ahah' => array('wrapper' => 'sub-cat-wrapper',
                                                'event' => 'change',
                                                'path' => 'issue/ahah/category/scat',
                                                'effect' => 'fade',
                                                'method' => 'replace'),
                            '#attributes' => array('class'=>'selectbox-sm'),
                            '#default_value' => $subject,
                            '#id' => 'subject');
    // get first level category
    $form['defarea'] = array('#type' => 'hidden', '#default_value' => $area);
    $form['defdetail'] = array('#type' => 'hidden', '#default_value' => $detail);
    $form['sub_categories'] = array('#type' => 'markup',
                                    '#value' => '<div id="sub-cat-wrapper" style="float:left"></div>',
                                    );

    $form['sub_sub_categories'] = array('#type' => 'markup',
                                    '#value' => '<div id="sub-sub-cat-wrapper" style="float:left">
                                                </div>',
                                    '#suffix' => '<br /><div class="clr"></div>');
    $form['location_mark'] = array('#type' => 'markup', '#value' => t('FILTER BY LOCATION').'<br /><div class="clr"></div>');
    // location
    $countries[''] = 'COUNTRY';
   // $countryList = geonames_query('countryinfo',NULL);
      //foreach($countryList->results as $country){
     //   $countries[$country['countryname']] = $country['countryname'];
    //}
    //list only the country the issue is
    $cck_country=db_query("select field_issue_country_value from {content_field_issue_country} group by field_issue_country_value");
    while ($ccklist = db_fetch_object($cck_country)) {
        if(!empty($ccklist->field_issue_country_value))
          $countries[$ccklist->field_issue_country_value] =$ccklist->field_issue_country_value;
    }
  //  array_filter($countries, 'strlen');
    $form['country'] = array('#type' => 'select',
                            '#options' => $countries,
                            '#prefix' => '<div style="float:left;">',
                            '#suffix' => '</div>',
                            '#ahah' => array('wrapper' => 'state-wrapper',
                                                'path' => 'issue/ahah/location/state',
                                                'effect' => 'fade',
                                                'event' => 'change',),
                            '#attributes' => array('class'=>'selectbox-sm'),
                            '#default_value' => $getcountry,
                            '#id' => 's_country');

    // default state, city
    $form['defstate'] = array('#type' => 'hidden', '#default_value' => $getState);
    $form['defcity'] = array('#type' => 'hidden', '#default_value' => $getCity);

    $form['state_div'] = array('#type' => 'markup',
                                '#value' => '<div id="state-wrapper" style="float:left"></div>');
    $form['city_div'] = array('#type' => 'markup',
                                '#value' => '<div id="city-wrapper" style="float:left"></div>',
                                '#suffix' => '<br /><div class="clr"></div>');
    
    $form['search'] = array('#type'=>'submit', '#value' => t('SUBMIT'));
    return $form;
}
function issue_search_form_submit($form, &$form_state){
    $key = $form_state['values']['issue_key'];
    $key = $key!=""?$key:0;
    
    $subject = $form_state['values']['subject'];
    $subject = $subject!=""?$subject:0;
    $area = $form_state['clicked_button']['#post']['area'];
    $area = $area!=""?$area:0;
    $detail = $form_state['clicked_button']['#post']['detail'];
    $detail = $detail!=""?$detail:0;

    $country = $form_state['values']['country'];
    $country = $country!=""?$country:0;
    $state = $form_state['clicked_button']['#post']['state'];
    $state = $state!=""?$state:0;
    $city = $form_state['clicked_button']['#post']['city'];
    $city = $city!=""?$city:0;

   // $path = 'issues/?key='.$key.'&subject='.$subject.'&area='.$area.'&detail='.$detail.'&country='.$country.'&state='.$state.'&city='.$city;
     $path = 'issues/'.$key.'/'.$subject.'/'.$area.'/'.$detail.'/'.$country.'/'.$state.'/'.$city;
    drupal_goto($path);
}

// search issue results
function search_issue_results(){
    global $language;
    $issue = '';
    $curLanguage = $language->language;
    
    $key = arg(1)!='0'?arg(1):'';
    $subject = arg(2)!='0'?arg(2):'';
    $area = arg(3)!='0'?arg(3):'';
    $detail = arg(4)!='0'?arg(4):'';
    $country = arg(5)!='0'?arg(5):'';
    $state = arg(6)!='0'?arg(6):'';
    $city = arg(7)!='0'?arg(7):'';

    $sortValue = arg(8)!=''?arg(8):'all';
    $where = '';
    $groupBy = '';
    
   

    $rec_per_page = 5;

    
    $val = array();
    // conditions key
    if(!empty($key)){
        $where .= " AND MATCH(nr.title, nr.body) AGAINST('%s')";
        $val[] = $key;
        
    }
    // categories
    if(!empty($detail)){
        $where .= " AND tn.tid = '%d'";
        $val[] = $detail;
        
    }elseif(!empty($area)){
        $where .= " AND tn.tid = '%d'";
        $val[] = $area;
        
    }elseif(!empty($subject)){
        $where .= " AND tn.tid = '%d'";
        $val[] = $subject;
        
    }
    // locations
    if(!empty($country)){
        $where .= "AND cc.field_issue_country_value = '%s'";
        $val[] = $country;
        
    }
    if(!empty($state)){
        $where .= "AND cs.field_issue_state_value = '%d'";
        $val[] = $state;
        
    }
    if(!empty($city)){
        $where .= "AND ct.field_issue_city_value = '%d'";
        $val[] = $city;
        
    }

    // filter with default language if issue key is empty
    $langFilter = $key==''?"AND n.language = '$curLanguage'":'';


     switch($sortValue){
        case 'alltime':
            $sortBy = 'ORDER BY COUNT(pv.nid) DESC';
            $groupBy = 'GROUP BY pv.nid';

            $sql = "SELECT pv.nid FROM {poll_votes} AS pv JOIN
                (SELECT DISTINCT(n.nid) FROM {node} AS n
                JOIN {content_field_issue_country} AS cc ON n.nid = cc.nid
                JOIN {content_field_issue_state} AS cs ON n.nid = cs.nid
                JOIN {content_field_issue_city} AS ct ON n.nid = ct.nid
                LEFT JOIN {term_node} AS tn ON n.nid = tn.nid 
                WHERE n.type = 'poll' $langFilter $where) AS temp ON pv.nid = temp.nid $groupBy $sortBy";
            break;
        case '7days':
            $where .= 'AND pv.date_voted >= DATE_SUB(CURDATE(), INTERVAL 7 DAY)';
            $sortBy = 'ORDER BY SUM(pc.chvotes) DESC';
            $groupBy = 'GROUP BY pc.nid';

            $sql = "SELECT DISTINCT(n.nid) FROM {node} AS n JOIN {node_revisions} AS nr ON n.nid = nr.nid
            JOIN {content_field_issue_country} AS cc ON n.nid = cc.nid
            JOIN {content_field_issue_state} AS cs ON n.nid = cs.nid
            JOIN {content_field_issue_city} AS ct ON n.nid = ct.nid
            JOIN {poll_choices} AS pc ON n.nid = pc.nid
            LEFT JOIN {poll_votes} AS pv ON n.nid = pv.nid
            LEFT JOIN {term_node} AS tn ON n.nid = tn.nid
            WHERE n.type = 'poll' $langFilter $where $groupBy $sortBy";

            break;
        case 'views':
            $sortBy = 'ORDER BY COUNT(qv.qid) DESC';
            $groupBy = 'GROUP BY qv.qid';

            $sql = "SELECT qv.qid as nid FROM {qviews} AS qv 
                    JOIN (SELECT DISTINCT(n.nid) FROM {node} AS n
                    JOIN {content_field_issue_country} AS cc ON n.nid = cc.nid
                    JOIN {content_field_issue_state} AS cs ON n.nid = cs.nid
                    JOIN {content_field_issue_city} AS ct ON n.nid = ct.nid
                    LEFT JOIN {term_node} AS tn ON n.nid = tn.nid
                   WHERE n.type = 'poll' $langFilter $where) AS iss ON qv.qid = iss.nid $groupBy $sortBy";

            break;
        default:
            $sortBy = 'ORDER BY n.nid DESC';
            $groupBy = '';

            $sql = "SELECT DISTINCT(n.nid) FROM {node} AS n JOIN {node_revisions} AS nr ON n.nid = nr.nid
            JOIN {content_field_issue_country} AS cc ON n.nid = cc.nid
            JOIN {content_field_issue_state} AS cs ON n.nid = cs.nid
            JOIN {content_field_issue_city} AS ct ON n.nid = ct.nid
            LEFT JOIN {term_node} AS tn ON n.nid = tn.nid
            WHERE n.type = 'poll' $langFilter $where $groupBy $sortBy";

            break;
    }


//echo $sql; exit;
   
   $sqlcount = ExecuteQuery($sql, 'norows');

   $final = call_user_func_array('sprintf', array_merge((array) $sql, $val));
   $sqlcount = ExecuteQuery($final, 'norows');

    $query = pager_query_new($final, $rec_per_page, 0, $sqlcount);
//    $query = do_search($keywords, $type, $join1 = '', $where1 = '1',
//            $arguments1 = array(), $select2 = 'i.relevance AS score',
//            $join2 = '', $arguments2 = array(),
//            $sort_parameters = 'ORDER BY score DESC');

    $count = db_affected_rows($query);
    if($sqlcount){

    $key = arg(1)!=''?arg(1):'0';
    $subject = arg(2)!=''?arg(2):'0';
    $area = arg(3)!=''?arg(3):'0';
    $detail = arg(4)!=''?arg(4):'0';
    $country = arg(5)!=''?arg(5):'0';
    $state = arg(6)!=''?arg(6):'0';
    $city = arg(7)!=''?arg(7):'0';

    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';


    $key_path = $sitelink.'issues/'.$key.'/'.$subject.'/'.$area.'/'.$detail.'/'.$country.'/'.$state.'/'.$city;
    $issue .= 'SORT BY:&nbsp;<a href="'.$key_path.'/alltime">'.t('# of Votes all-time').'</a>&nbsp;|&nbsp;'
              .'<a href="'.$key_path.'/7days">'.t('# of Votes last 7 days').'</a>&nbsp;|&nbsp;'
                .'<a href="'.$key_path.'/views">'.t('# Views all-time').'</a>';
    while($result = db_fetch_object($query)){
        $nid = $result->nid;
        $node = node_load($nid);
        $issue .= node_view(node_load($node->nid), 1);
    }
    $issue .= '<div class="clr"></div><br />';
    $issue .= theme('pager', array(), $rec_per_page);
    }else{
        $issue .= t('No Issues Found');
    }
    return $issue;
}


function issue_debates($qid='', $type='') {
    global $gSitePath, $user, $gDocPath, $base_root, $language, $theme;
    $curLanguage = $language->language;
    $wave = '';
    $click = '';
    $debate_theme = '';

    //drupal_add_js( drupal_get_path('module', 'debate') . '/scripts/debate.js');

    // load debate
    $sup = isset($_GET['sup'])?$_GET['sup']:'';
    $ans = isset($_GET['ans'])?$_GET['ans']:'';
    $sort = isset($_GET['sort'])?$_GET['sort']:'';


    $sorting = 'ORDER BY f.nid DESC';
    $cond = '';
    extract($_REQUEST);
    if (isset($sort) && $sort == 1){
        $sorting = 'ORDER BY n.created DESC';
    }elseif (isset($sort) && $sort == 2){
        $sorting = ' ORDER BY c.field_strength_value DESC';
    }
    if (isset($ans) && !empty($ans)){
        $cond.=" AND do.chorder='$ans'";
    }
    if (isset($sup) && $sup > 0){
        $cond.=" AND do.ans_val='$sup'";
    }
    $tid = get_taxonomy_id('forum', 'Debate');
    //$sql = "SELECT f.nid FROM {forum} as f LEFT JOIN {content_type_forum} as c ON f.nid = c.nid JOIN {node} as n ON f.nid = n.nid WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' $cond $sorting";

   if (empty($cond))
  $sql = "SELECT DISTINCT(f.nid) FROM {forum} as f LEFT JOIN {content_type_forum} as c ON f.nid = c.nid JOIN {node} as n ON f.nid = n.nid JOIN {debate_options} as do ON n.nid = do.nid WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' $sorting";
   else
   $sql = "SELECT DISTINCT(f.nid) FROM  {debate_options} as do  JOIN  {forum} as f ON f.nid = do.nid LEFT JOIN {content_type_forum} as c ON f.nid = c.nid JOIN {node} as n ON f.nid = n.nid  WHERE f.tid = '%d' AND c.field_ref_qid_nid = '%d' $cond $sorting";

   // forum for translated languages
   $issueId = $qid;
   $tnid = get_tnid($qid);
   $qid = $tnid;

   $nodes = db_query($sql, $tid, $qid);
   $count = db_result(db_query($sql, $tid, $qid));

    if ($count>0) {
        $i=0;
        while ($node = db_fetch_object($nodes)) {
            
            $items = load_debate_datas($node->nid, $issueId, $tnid);


            $debate_theme .= theme('single_debate_template', $items);
            // update points
            $tForumId = get_tnid($node->nid);
            debate_roundup($tForumId);
        }
    } else {
        $debate_theme .= '<div class="messages warning">'.t('No Debate Posted Yet!!').'</div>';
    }


    
    return $debate_theme;
    //return $wave;
}

// forum replies
function forum_replies($debate_tnid, $pid = ''){
    global $gSitePath, $user, $language, $theme;
    $curLanguage = $language->language;
    $comments = '';

    $query = "SELECT * FROM {comments} as c where c.nid='$debate_tnid' and c.status='0' and c.pid='$pid' AND (c.cid = c.tcid OR c.tcid = 0) ORDER BY c.cid DESC";
    $list = ExecuteQuery($query, "select");

    if(count($list)>0){
    foreach ($list as $forum) {
            $cid = $forum['cid'];
            if (!empty($forum['comment'])) {
                $items = forum_reply_datas($cid);
                $comments .= theme('forum_reply_template', $items);
            }
    }
    }else{
        $comments .= '<div id="no_rply_'.$debate_tnid.'">'.t('No Replies').'</div>';
    }
    return $comments;
}

// delete forum, comments
function issue_thread_delete($type = '', $tnid = '', $source = ''){
    if($type == 'forum'){
        if($source=='debate'){
        $tlists = translation_node_get_translations($tnid);
        //echo '<pre>';print_r($tlists);exit;
        foreach($tlists as $list){ 
            node_delete($list->nid);
        }
        db_query("DELETE FROM {debate_options} WHERE nid = '$tnid'");
        print t('Your argument removed from list'); exit;
        }elseif($source=='resource'){
            node_delete($tnid);
            db_query("DELETE FROM {resource_options} WHERE nid = '$tnid'");
            print t('Your reference removed from list'); exit;
        }
    }
    if($type == 'reply'){
        $tcid = $tnid;
        $comment = db_fetch_object(db_query('SELECT c.*, u.name AS registered_name, u.uid FROM {comments} c INNER JOIN {users} u ON u.uid = c.uid WHERE c.cid = %d', $tcid));
       
        if($comment->translate==1){
            $trans = db_query('SELECT c.*, u.name AS registered_name, u.uid FROM {comments} c INNER JOIN {users} u ON u.uid = c.uid WHERE c.tcid = %d', $comment->cid);
            while($translations = db_fetch_object($trans)){
                delete_replies($translations);
            }
        }else{
            delete_replies($comment);
        }
        print t('Your reply removed from list'); exit;
    }
}

function delete_replies($comment){
      // Delete the comment:
      db_query('DELETE FROM {comments} WHERE cid = %d', $comment->cid);
      watchdog('content', 'Comment: deleted %subject.', array('%subject' => $comment->subject));

      comment_invoke_comment($comment, 'delete');
      // update comment statistics
      _comment_update_node_statistics($comment->nid);
}


function issue_ajax($task = '', $nid = ''){
    switch($task){
        case 'insightview':
            $result = insight_view($nid);
    }
    echo $result;
}


function insight_view($nid=''){


//    1.  Demographics by possible answer to total votes
//   Sum of votes for a possible answer by each demographic / total votes.
//ex: sum votes for possible answer A where demographic = male / total number of votes (not including changed votes)
//
//2.  Demographics by possible answer by total demographic votes
//   Sum of votes for a possible answer by each demographic / total votes for the same demographic
//ex: sum votes for possible answer A where demographic = age group X / total votes for age group X
//
//3. Demographics total votes by total votes
//   Sum of all votes by a demographic / total votes
//ex: Sum all votes by hindus (regardless of possible answer) / total votes

    if(is_numeric($nid)){
        $nid = get_tnid($nid);
        // calculation
        // total votes a issue
        //echo '<pre>';
        $insight = '';
        $totalVotes = db_result(db_query("SELECT COUNT(chorder) FROM {poll_votes} WHERE nid = '%d'", $nid));
        if($totalVotes >= 10){
        $insight .= by_possible_answers_votes($nid).'<br />';
        $insight .= by_demographic_votes($nid).'<br />';
        $insight .= by_total_votes($nid);
        }else{
            $insight .= t('Insight view cannot be calculated until 10 votes have been received.');
        }
        return $insight;
        

//        $income=report_percent_broken($nid,'',array('dochg'=>'age'));
//        $val = 0;
//        $cnt = $income['cnt'];
//        print_r($income);
//        foreach($cnt as $key=>$count){
//            $arr = json_decode($count);
//            $val = $val+array_sum($arr);
//        }
//        echo $val;
    }


//exit;

}

function by_possible_answers_votes($nid = ''){
    $byPossible = array();
    $totalVotes = db_result(db_query("SELECT COUNT(chorder) FROM {poll_votes} WHERE nid = '%d'", $nid));
        $node = node_load($nid);

        //demo['divide'],demo['cnt']
        // DEMOGRAPHICS
        $demographics = array('gender', 'age', 'religion', 'ethnicity', 'income', 'marital', 'sorient', 'edu');
        foreach($demographics as $demographic){
            $demo=report_percent_broken($nid,'',array('dochg'=>$demographic));

            $divides = $demo['divide'];
            $cnts = $demo['cnt'];
            foreach($divides as $key=>$divide){
               $divide = $divide=='undefined'?'undefined_'.$demographic:$divide;
               $count = $cnts[$key];
               $choices = json_decode($count);
               
               foreach($choices as $choice=>$cCount){
                    $percent = ($cCount/$totalVotes)*100;
                    $byPossible[$divide][$node->choice[$choice]['chtext']] = $percent;

               }
               unset($choices);
            }
        }


   
            $temp = $byPossible;

            $first_key=max_key($byPossible);
            unset($byPossible[$first_key]);
            $second_key=max_key($byPossible);

            $first = $temp[$first_key];
            $second = $temp[$second_key];

            $fmax = max($first);
            $smax = max($second);
            foreach($first as $ch => $val){
                if($val==$fmax){
                    $fChoice = $ch;
                }
            }
            foreach($second as $ch => $val){
                if($val==$smax){
                    $sChoice = $ch;
                }
            }

            //special wordings for each demographic
            $age=report_percent_broken($nid,'',array('dochg'=>'age'));
            $income=report_percent_broken($nid,'',array('dochg'=>'income'));
                if(in_array($first_key,$age['divide'])){
                    $extraStr1 = " aged people";
                }else if(in_array($first_key,$income['divide'])){
                    $extraStr1 = " salaried people";
                }
                if(in_array($second_key,$age['divide'])){
                    $extraStr2 = " aged people";
                }else if(in_array($second_key,$income['divide'])){
                    $extraStr2 = " salaried people";
                }
            $str .= ceil($fmax).'% '.t('of '.$first_key.$extraStr1.' voted for '.$fChoice).'<br />';
            $str .= ceil($smax).'% '.t('of '.$second_key.$extraStr2.' voted for '.$sChoice);
            return $str;
}

function by_demographic_votes($nid = ''){
        $byDemographic = array();
        $node = node_load($nid);

        //demo['divide'],demo['cnt']
        // DEMOGRAPHICS
        $demographics = array('gender', 'age', 'religion', 'ethnicity', 'income', 'marital', 'sorient', 'edu');
        foreach($demographics as $demographic){
            $demo=report_percent_broken($nid,'',array('dochg'=>$demographic));

            $divides = $demo['divide'];
            $cnts = $demo['cnt'];
            
           // total votes per demographic
           $val = 0;
//           foreach($cnts as $arrkey=>$votes){
//                $arr = json_decode($votes);
//                $val = $val+array_sum($arr);
//            }
//           $demoVotes = $val;
           
            foreach($divides as $key=>$divide){
               $divide = $divide=='undefined'?'undefined_'.$demographic:$divide;
               $count = $cnts[$key];
               $choices = json_decode($count);
               // total counts for group x in each demographic
               $demoVotes = array_sum($choices);

               foreach($choices as $choice=>$cCount){
                    $percent = ($cCount/$demoVotes)*100;
                    $byDemographic[$divide][$node->choice[$choice]['chtext']] = $percent;
               }
               unset($choices);
            }
        }


        //print_r($byDemographic);exit;
            $temp = $byDemographic;

            $first_key=max_key($byDemographic);
            unset($byDemographic[$first_key]);
            $second_key=max_key($byDemographic);

            $first = $temp[$first_key];
            $second = $temp[$second_key];

            $fmax = max($first);
            $smax = max($second);
            foreach($first as $ch => $val){
                if($val==$fmax){
                    $fChoice = $ch;
                }
            }
            foreach($second as $ch => $val){
                if($val==$smax){
                    $sChoice = $ch;
                }
            }

            //special wordings for each demographic
            $age=report_percent_broken($nid,'',array('dochg'=>'age'));
            $income=report_percent_broken($nid,'',array('dochg'=>'income'));
                if(in_array($first_key,$age['divide'])){
                    $extraStr1 = "between the ages of ";
                }else if(in_array($first_key,$income['divide'])){
                    $extraStr1 = "salaried between ";
                }
                if(in_array($second_key,$age['divide'])){
                    $extraStr2 = "between the ages of ";
                }else if(in_array($second_key,$income['divide'])){
                    $extraStr2 = "salaried between ";
                }
            $str .= ceil($fmax).'% '.t('of the voters are '.$extraStr1.$first_key).' voted for '.$fChoice.'<br />';
            $str .= ceil($smax).'% '.t('of the voters are '.$extraStr2.$second_key).' voted for '.$sChoice;
            return $str;
}

function by_total_votes($nid = ''){
    $bytotalVotes = array();
    $totalVotes = db_result(db_query("SELECT COUNT(chorder) FROM {poll_votes} WHERE nid = '%d'", $nid));
    $node = node_load($nid);
    //demo['divide'],demo['cnt']
    // DEMOGRAPHICS
    $demographics = array('gender', 'age', 'religion', 'ethnicity', 'income', 'marital', 'sorient', 'edu');
    foreach($demographics as $demographic){
        $demo=report_percent_broken($nid,'',array('dochg'=>$demographic));
        $divides = $demo['divide'];
        $cnts = $demo['cnt'];

       // total votes per demographic
       $val = 0;
       
       $demoVotes = $val;
        foreach($divides as $key=>$divide){
            $count = $cnts[$key];
            $choices = json_decode($count);
            // total counts for group x in each demographic
            $demoVotes = array_sum($choices);
            $percent = ($demoVotes/$totalVotes)*100;
            $bytotalVotes[$divide] = $percent;
        }
       
    }
    $temp = $bytotalVotes;
    $fmax = max($bytotalVotes);
    foreach($bytotalVotes as $vkey => $byVotes){
        if($fmax == $byVotes){
            $first_key = $vkey;
            break;
        }
    }
    unset($bytotalVotes[$first_key]);
    $smax = max($bytotalVotes);
    foreach($bytotalVotes as $vkey => $byVotes){
        if($smax == $byVotes){
            $second_key = $vkey;
            break;
        }
    }

    //special wordings for each demographic
            $age=report_percent_broken($nid,'',array('dochg'=>'age'));
            $income=report_percent_broken($nid,'',array('dochg'=>'income'));
                if(in_array($first_key,$age['divide'])){
                    $extraStr1 = "between the ages of ";
                }else if(in_array($first_key,$income['divide'])){
                    $extraStr1 = "salaried between ";
                }
                if(in_array($second_key,$age['divide'])){
                    $extraStr2 = "between the ages of ";
                }else if(in_array($second_key,$income['divide'])){
                    $extraStr2 = "salaried between ";
                }
            $str .= ceil($fmax).'% '.t('of the voters are '.$extraStr1.$first_key).'<br />';
            $str .= ceil($smax).'% '.t('of the voters are '.$extraStr2.$second_key);
            return $str;

}


function max_key($array) {
    foreach ($array as $key => $val) {
        if ($val == max($array))
        return $key;
    }
}


// debate filter options
function filter_options($form, $nid){
    $form = '';
    $ans = load_options($nid);
    $filterBy[''] = t('Answer');
    foreach ($ans as $list) {
         $short_answer = get_short_answer($nid, $list['chorder']);
         $answer = $short_answer!=''?$short_answer:$list['chtext'];
         $filterBy[$list['chorder']] = $answer;
    }
    $sortBy = array('0' => t('Sort By'), '1' => t('Most Recent'), '2' => t('Most Support'));

    $panOptions = array('0'=>'+/-', '1'=>'+', '2'=>'-');

    $dSup = $_GET['sup'];
    $dans = $_GET['ans'];
    $dSort = $_GET['sort'];
    
    $form['nid'] = array('#type' => 'hidden', '#value' => $nid);
    $form['title'] = array('#type' => 'markup', '#value' => t('FILTER ARGUMENTS BY'), '#suffix' => '<div class="clr"></div>');
    $form['dfilt_sup'] = array('#type' => 'select',
                '#options' => $panOptions,
                '#default_value' => $dSup,
                '#prefix' => '<span class="fl-left">',
                '#suffix' => '</span>');
    $form['dfilt_ans'] = array('#type' => 'select',
                '#options' => $filterBy,
                '#default_value' => $dans,
                '#prefix' => '<span class="fl-left">',
                '#suffix' => '</span>');
    $form['dfilt_sort'] = array('#type' => 'select',
                '#options' => $sortBy,
                '#default_value' => $dSort,
                '#prefix' => '<span class="fl-left">',
                '#suffix' => '</span>');
    $form['debate_filter'] = array('#type' => 'submit',
                                '#value' => t('Filter'));

    return $form;
}

function filter_options_submit($form, &$form_state){
    global $gSitePath, $language;
    $nid = $form_state['values']['nid'];
    $sup = $form_state['values']['dfilt_sup'];
    $ans = $form_state['values']['dfilt_ans'];
    $sort = $form_state['values']['dfilt_sort'];
    $ids = '?sup='.$sup.'&ans='.$ans.'&sort='.$sort;
    $path = $gSitePath.$language->language.'/'.drupal_get_path_alias('node/'.$nid).$ids;
    drupal_goto($path);
}

// add new resource
function add_new_resources($qid='') {
    global $gSitePath, $user, $gDocPath, $base_root;

    // site url with default language
    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';
    //$gSitePath = $sitelink;


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

<div class="debate-r">
    <div class="debate-r-row">
        <div class="fm-2">   <select name="rtype" class="listbox1" id="rtype" >
	<option value="0">Resource Type </option>
	<option value="1">News </option>
	<option value="2">Multimedia </option>
	<option value="3">Facts </option>
	</select></div>
    </div>

    <div id="div1" style="display:none;"  class="debate-r-row"><input type="text" class="listbox1" style="float:left; padding:3px;"  name="nlink" value="http://" id="nlink"/> <div><input id="lattach" name="name" type="button" value="Attach"  style="float:left; width:50px; padding:1px;"/></div></div>
    <div id="div2" style="display:none;"  class="debate-r-row"><select name="mtype" class="listbox1" id="mtype"   >
    <option value="0">Choose Format </option>
    <option value="1">Web Video </option>
    <option value="2">Podcast,PDF, DOC, PPT. </option>
    </select>
    </div>
    
    <div id="media" style="display:none;"  class="debate-r-row"> <input type="text"  name="membed" id="membed" value="http://"  class="listbox1" ></div>
    <div id="media_div" style="display:none;"  class="debate-r-row">
    <input type="hidden" name="docpath" id="docpath"/> <div id="file-uploader-demo1"> </div>
    </div>
    <div class="debate-r-row" id="linkbox"></div>



 ' . $inc_pans . '
     	<div class="debate-r-row">
          <div class="fm-2">
        <div class="fm-2-right" align="right"><input name="submit" value="Submit" title="submit" type="submit" id="submitter" class="orange-btn"/></div>
        <br />
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


// ISSUE RESOURCES
function issue_resources_list($qid = ''){
    $inline = 'jQuery(document).ready(function(){res_type_tab(1,\'resource\','.$qid.')})';
    drupal_add_js($inline, 'inline');
    $resources = '';
    $resources .= '<div id="load-resource">';
    //$resources .= '<div id="res-type-1">'.issue_resources($qid,1).'</div>';
    //$resources .= '<div id="res-type-2" style="display: none">'.issue_resources($qid,2).'</div>';
    //$resources .= '<div id="res-type-3" style="display: none">'.issue_resources($qid,3).'</div>';
    $resources .= '</div>';
   
    return $resources;
}

// resources in news
function issue_resources($qid, $rtype = '', $sup='', $ans='', $sort=''){
    global $gSitePath, $user, $gDocPath, $base_root, $language, $theme;
    $wave = '';
    $click = '';
    $sortin = 'ORDER BY rid DESC';
    $cond = '';

    // load resources
    $sup = $sup!='n'?$sup:'';
    $ans = $ans!='n'?$ans:'';
    $sort = $sort!='n'?$sort:'';

    // site url with default language
    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';

    extract($_REQUEST);

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

    // resource type
    switch($rtype){
    case '1':
        $resType  = 'news';
        break;

    case '2':
        $resType  = 'multimedia';
        break;

    case '3':
        $resType  = 'facts';
        break;
    
    default:
        $resType  = 'news';
        break;
    }

    
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
            $items = load_resource_datas($node->nid, $issueId, $tnid, $resType);
            $resouce_theme .= theme('single_resource_template', $items);
        }
   }else{
       $resouce_theme = '<div class="messages warning">'.t('No Resource Posted Yet!!').'</div>';
   }
   //return $resouce_theme;
   print $resouce_theme;
}