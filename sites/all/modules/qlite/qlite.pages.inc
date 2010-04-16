<?php
function qlitemini() {
    global $gSitePath,$user,$gDocPath,$base_root,$base_path;
    //SELECT answer, vote * 2.75/100 AS PercentOfTotal FROM suggested_answer order by PercentOfTotal desc limit 0,3
    
    drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/main.css');
    drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/page.css');
    drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/tabs.css');

  $qid=get_qid();
	 

   
    $vSql = "select * from {question} where status='1' and qid=$qid ";
    $rlist = db_query($vSql);
    $oListquest = db_fetch_object($rlist);
  
    $list_lengthan = db_query("select * from {possible_answer_vote} where qid='".$qid."' and uid='".$user->uid."'  ");
    $numran = mysql_num_rows($list_lengthan);
    $answer_id = db_fetch_object($list_lengthan);
    drupal_set_title($oListquest->question);
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
    
    
		$voutput.='</div></div>';

   // $voutput.=qlite_report($qid);
    return $voutput;
}

function get_qid(){
	
	 global $gSitePath,$user,$gDocPath,$base_root;
	 $qid='';
	 if($user->uid>0){
	
	   $query = "SELECT qid from {question} where uid='".$user->uid."' order by qid DESC limit 0,1 ";
	    $quest = db_query($query);
	  $qid = db_result($quest); 
	 
	 }
	 
	 if($qid==''){
		   $query = "SELECT qid from {question} order by qid DESC limit 0,1 ";
		  $quest = db_query($query);
	 $qid = db_result($quest);
	 }
   
	 
	 return $qid;
	
}

 function qlite_report($qid='') {
    global $gSitePath,$user,$gDocPath,$base_root;


  echo  $output= '<div class="toolbarTabs">
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
    
    $qid=get_qid();
	  $numres= db_result(db_query("SELECT COUNT(*) FROM resource where  qid='$qid'"));
    $type=$_REQUEST[t];
   
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
	
	
	$output.='<div>108 comments &nbsp;&nbsp;&nbsp;'.$numres.' Resources </div>';
	
    echo $output;
}




?>
