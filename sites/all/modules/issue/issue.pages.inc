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
    if(!is_numeric($nid))
        return 'No Data Found';

   //$vans = "select * from {possible_answer} where  qid='" . $qid . "'";
     $vans = "select * from {poll_choices} where  nid='" . $nid . "'";
    $vlist = ExecuteQuery($vans, "select");
    $cnt_ans = count($vlist);
    $output .= "
            <script type='text/javascript' src='http://code.jquery.com/jquery-1.4.2.min.js'></script>
            <script type='text/javascript' src='" . $gSitePath . drupal_get_path('module', 'issue') . "/js/highcharts.js'></script>
            <script>var example = 'bar-stacked',
            theme = 'skies';
            </script>
            <link rel='stylesheet' href='" . $gSitePath . drupal_get_path('theme', 'issue') . "/css/css.css' type='text/css' />
            <script type='text/javascript' src='" . $gSitePath . drupal_get_path('module', 'issue') . "/js/filter.js'></script>
            <script type='text/javascript' src='" . $gSitePath . drupal_get_path('module', 'issue') . "/js/skies.js'></script>
			";

    $ans_array = array();
    for ($ab = 0; $ab < $cnt_ans; $ab++) {
        array_push($ans_array, $vlist[$ab]['chtext']);
        //array_push($ans_array, $vlist[$ab]['answer']);
    }
    $result = report_percent_broken($nid, '', $_REQUEST);
    //echo "<pre>";
    //print_r($result);
    $ans = $result['divide'];
    $cnt = $result['cnt'];

    foreach ($ans as $key => $value) {
        $ins_script .= "{name: '" . $ans[$key] . "',data: " . $cnt[$key] . "},";
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
						defaultSeriesType:'bar'
					},
					title: {
						text: ''
					},
					xAxis: {
						categories: " . json_encode($ans_array) . ",
                                                  labels :{ style: {
                  font: 'bold 12px Arial,Helvetica,sans-serif '
               }}
	},
					yAxis: {tickInterval  :1,
						min: 0,
						title: {
							text: 'No Of Votes'
						},
                                                labels :{ style: {
                   font: 'bold 12px Arial,Helvetica,sans-serif '
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
     <div align="right" style="padding-right:20px;" > <form id="form1" name="form1" method="post" action="">
Filter by :

  <select name="dochg" onchange="MM_jumpMenuGo(this.value);"  id="dochg">

  <option value="">Select</option>
  <option value="gender">Gender</option>
   <option value="age">Age</option>
    <option value="religion">Religion</option>
    <option value="ethnicity">Ethnicity</option>
    <option value="slant">Slant</option>
     <option value="sorient">Sexual Orientation</option>
     <option value="edu">Education Level</option>
  </select></label>
  <span id="fopt" ></span>

    <br />
 </form></div>
    <div id="chart_div" style="width: 400px; height: 240px;">
    </div>
</div>';
     return $output;
}


function report_percent_broken($qid = '', $aid = '', $array = '') {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;


    $filter = '';
    $filter = (!empty($array['dochg'])) ? $array['dochg'] : '';
   $vans = "select * from {possible_answer} where  qid='" . $qid . "'";
    // $vans = "select * from {poll_choices} where  nid='" . $qid . "'";
    $vlist = ExecuteQuery($vans, "select");
    switch ($filter) {
        case 'gender':
            $answer['divide'] = array('male', 'female', 'undefined');




            foreach ($answer['divide'] as $list) {
                if ($list == 'male')
                    $gen = 1;
                elseif ($list == 'female')
                    $gen = 2;
                else
                    $gen='';

                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' AND u.gender='" . $gen . "' ";
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
                    $query_ins = "AND u.age='' ";


                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' " . $query_ins;
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
                    $reg = '';
                else
                    $reg=$list;

                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' AND religion='" . $reg . "'";
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
                    $reg = '';
                else
                    $reg=$list;

                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' AND ethnic='" . $reg . "'";
                    $tcnt = ExecuteQuery($query, "norows");
                    $inc_cnt .= $tcnt . ',';
                }
                $inc_cnt = rtrim($inc_cnt, ",");
                $inc_cnt .= ']';
                $answer_cnt[] = $inc_cnt;
            }


            break;
        case 'slant':
            $answer['divide'] = array('Left', 'Right', 'Center', 'undefined');

            foreach ($answer['divide'] as $list) {
                if ($list == 'undefined')
                    $reg = '';
                else
                    $reg=$list;


                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' AND slant='" . $reg . "'";
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
                    $reg = '';
                else
                    $reg=$list;


                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' AND sorient='" . $reg . "'";
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
                    $reg = '';
                else
                    $reg=$list;


                $inc_cnt = '[';
                for ($ab = 0; $ab < count($vlist); $ab++) {
                    $query = "select * from {possible_answer_vote} as p join {user_profile} as u on u.uid=p.uid where  p.qid='" . $qid . "' and p.panswer_id='" . $vlist[$ab]['paid'] . "' AND edu='" . $reg . "'";
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
                $query = "select * from {possible_answer_vote} where qid='" . $qid . "' and panswer_id='" . $vlist[$ab]['paid'] . "' ";
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