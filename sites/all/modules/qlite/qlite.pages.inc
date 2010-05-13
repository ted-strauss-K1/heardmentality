<?php
function qlitemini() {
    global $gSitePath,$user,$gDocPath,$base_root,$base_path;
    //SELECT answer, vote * 2.75/100 AS PercentOfTotal FROM suggested_answer order by PercentOfTotal desc limit 0,3
    
    drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/main.css');
    drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/page.css');
    drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/tabs.css');
   
    $qid = get_qid();
    
    //for calculating active points
    cal_active_rate();
    
    $vSql = "select * from {question} where status='1' and qid=$qid ";
    $rlist = db_query($vSql);
    $oListquest = db_fetch_object($rlist);
    
    $list_lengthan = db_query("select * from {possible_answer_vote} where qid='".$qid."' and uid='".$user->uid."'  ");
    $numran = mysql_num_rows($list_lengthan);
    $answer_id = db_fetch_object($list_lengthan);
    drupal_set_title($oListquest->question.'  <a href="'.$gSitePath.$oListquest->url.'">View More</a>');
    $voutput = '
		<div class="lft_view"> <!--<h4 class="cmt_name"><a>'.$oListquest->question.' </a></h4>-->
		<p>'.$oListquest->context.'</p>';
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

    
    $voutput .= '</div></div>';
    
    // $voutput.=qlite_report($qid);
    return $voutput;
}

function get_qid() {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    $qid = '';
    if ($user->uid > 0) {
        
        $query = "SELECT qid from {question} where uid='".$user->uid."' order by qid DESC limit 0,1 ";
        $quest = db_query($query);
        $qid = db_result($quest);
    
    }
    
    if ($qid == '') {
        $query = "SELECT qid from {question} where status='1' order by qid DESC limit 0,1 ";
        $quest = db_query($query);
        $qid = db_result($quest);
    }

    
    return $qid;

}

function qlite_report($qid = '') {
    global $gSitePath,$user,$gDocPath,$base_root;

    
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
	"element":  $("report-panel"),
	"url":       "'.$gSitePath.'qmini/repcontent/?t=per"
	});
	});
	
	$("qTabs2Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("report-panel"),
	"url":       "'.$gSitePath.'qmini/repcontent/?t=time"
	});
	});
	
	$("qTabs3Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("report-panel"),
	"url":       "'.$gSitePath.'qmini/repcontent/?t=area"
	});
	});

	
	</script>';

}
function report_content() {
    global $gSitePath,$user,$gDocPath,$base_root;
    
    $qid = get_qid();
    $numres = db_result(db_query("SELECT COUNT(*) FROM resource where  qid='$qid'"));
    $type = $_REQUEST[t];
    
    switch ($type) {
        
        case "time":
            $output = '<div id="contents"><iframe id="frmGoogle" src="'.$gSitePath.'/qlite/graph/'.$qid.'" border="0" height="450" frameborder="0" width="100%"></iframe></div>';
            break;
        case "area":
            $output = '<div id="contents"><iframe id="frmGoogle" src="'.$gSitePath.'/qlite/map/'.$qid.'" border="0" height="450" frameborder="0" width="100%"></iframe></div>';
            break;
        case "per":
        default:
            $output = '<div id="contents"><iframe id="frmGoogle" src="'.$gSitePath.'/qlite/percent/'.$qid.'" border="0" height="450" frameborder="0" width="100%"></iframe></div>';
            break;
    }

    
    $output .= '<div>108 comments &nbsp;&nbsp;&nbsp;'.$numres.' Resources </div>';
    
    echo $output;
}

function load_ajax(){
	
	 global $gSitePath,$user,$gDocPath,$base_root;
	 $output='';
	 $action=$_REQUEST['action'];
	 
	 switch($action){
	 	
		case '1':
		case '2':
			
				$output='';
	
	$output.=get_top_list();
	
	$output.=get_hot_list();
	
	$output.=get_local_list();	
	
	echo $output; 
						
				break;
		case '5':
			extract($_REQUEST);
			
	$query = "SELECT * from {category} where parent_id='$cid' ORDER BY cat_name ASC";
    $list = ExecuteQuery($query, "select");
	$output.='<select id="tscat" onchange="get_toplist(this.value,2)"><option value="" >Select</option>';
	foreach($list as $cat){
		
		$output.='<option value='.$cat['cat_id'].' > '.$cat['cat_name'].' </option>';
	}
	
	$output.='</select>';
	
	echo $output;
				break;
		default:

		break;				
		
		
	 }
	 
	exit;
	
	}

function load_condition(){
	$cond='';
	//print_r($_REQUEST);
	if(isset($_REQUEST['cid'])&&isset($_REQUEST['action'])){
		extract($_REQUEST);
		if(!empty($cid)){
			
			$cond.=" AND cid='$cid'";
		}
		
		if(!empty($scid)){
			
			$cond.=" AND scid='$scid'";	
		}
		
	}
	
	return $cond;
	
}

function get_top_list() {
	
	 global $gSitePath,$user,$gDocPath,$base_root;
    $output = '';$cond='';
   

    $cond=load_condition();
	
	
    $query = "SELECT * from {question} where status='1' $cond order by active_rate  DESC LIMIT 0,10";
    $list = ExecuteQuery($query, "select");
    $output .= '<div id="pageWrapper" >';
	 if (! empty($list)) {
    foreach ($list as $quest) {
        
        $output .= '<li><a href="'.$quest['url'].'">'.myTruncate($quest['question'], '40', '', '..').'</a></li>';

    
    }
    } else {
        
        $output .= '<div><b>No Top List Found</b></div>';
    
    }
    $output .= '</div>';
    return $output;
}

function get_hot_list() {
    
     global $gSitePath,$user,$gDocPath,$base_root;
    $output = '';$cond='';
   

    $cond=load_condition();
	
    $m = date("m");
    $de = date("d");
    $y = date("Y");
    $date = date('Y-m-d', mktime(0, 0, 0, $m, ($de - 7), $y));

    
    $query = "SELECT * from {question} where status='1' AND date(date_added) >= '$date' $cond order by active_rate  DESC LIMIT 0,10 ";
    $list = ExecuteQuery($query, "select");
    $output .= '<div id="pageWrapper" >';
    if (! empty($list)) {
        foreach ($list as $quest) {
            
            $output .= '<li><a href="'.$quest['url'].'">'.myTruncate($quest['question'], '40', '', '..').'</a></li>';

        
        }
    } else {
        
        $output .= '<div><b>No Hot List Found</b></div>';
    
    }
    $output .= '</div>';
    return $output;


}

function get_local_list() {
    global $gSitePath,$user,$gDocPath,$base_root;
    $output = '';$cond='';
   

    $cond=load_condition();
	
    $homepage = file_get_contents('http://api.hostip.info/country.php');
    

    $query = "SELECT * from {question} where status='1' AND country='".trim($homepage)."' $cond order by active_rate  DESC LIMIT 0,10 ";
    $list = ExecuteQuery($query, "select");
    $output .= '<div id="pageWrapper" >';
	
	if (! empty($list)) {
    foreach ($list as $quest) {
        
        $output .= '<li><a href="'.$quest['url'].'">'.myTruncate($quest['question'], '40', '', '..').'</a></li>';
    
    }
	   } else {
        
        $output .= '<div><b>No Local List Found</b></div>';
    
    }
    return $output;


}

function cal_active_rate() {

    
    global $gSitePath,$user,$gDocPath,$base_root;
    $j = 5;
    $k = 5;
    $l = 5;
	$fcnt=array();
	$gvote=array();
    $query = "SELECT * from {question}";
    $list = ExecuteQuery($query, "select");
    
    foreach ($list as $quest) {

        
        $query1 = "select IFNULL((select count(*) from {possible_answer_vote} as pa where q.qid=pa.qid group by pa.qid ),0) as pvote,(select count(*) from {suggest_answer_vote} as sa where q.qid=sa.qid group by sa.qid ) as svote from {question} as q where q.qid='".$quest['qid']."'";
        $gvote = ExecuteQuery($query1, "select");
		$m1=$gvote[0]['pvote'];
		$m2=$gvote[0]['svote'];
        
        $tvote = $m1 + $m2;
        
        $query2 = "select IFNULL((select count(*) from {forum_wavelets} as w where w.wid=f.fid group by w.wid),0) as wcnt,IFNULL((select count(*) from {resource} where qid='".$quest['qid']."' group by qid),0) as rcnt from {forum_wave} as f where f.qid_rid='".$quest['qid']."' ";
        $fcnt = db_fetch_object(db_query($query2));
        
        //The value “active” will be calculated as follows (j,k,l are constant values that will be hard-coded):
        //Active =  (j * #_of_votes_for_question) + (k * #_of_forum_posts) + (l * #_of_posted_resources)
		if(!empty($fcnt)){
			$cntr=$fcnt->wcnt;
		$wcnt=$fcnt->rcnt;
			   $active = (($j * $tvote) + ($k * $cntr) + ($l * $wcnt));
			       db_query("update {question} set active_rate='".$active."' where qid='".$quest['qid']."'");
		}
		
        
     
        
    
    
    }

}

?>
