<?php

function my_notify() {
    
     global $gSitePath,$user,$gDocPath,$base_root,$base_path;
    //SELECT answer, vote * 2.75/100 AS PercentOfTotal FROM suggested_answer order by PercentOfTotal desc limit 0,3
    
    drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/main.css');
    drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/page.css');
    drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/tabs.css');
 $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
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
						
						
						
						 function get_Reply(){
						
						var url = "'.$gSitePath.'reply";
						var clearfi=\'\';
									var req = new Request({    
											method: \'get\'
											,url: url
											,data: {\'reply\':1 },
											onRequest: function() { },
											onComplete: function(response) {
													 $(\'show_box\').set(\'html\', response);
													 $(\'div_msg\').set(\'html\', clearfi);
											}
									}).send();
						
						
						}
					</script>
			
			';
	if(($idb=='otify')||($idb=='repcontent'))
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
function get_nqid($idm){
	
	/* global $gSitePath,$user,$gDocPath,$base_root;
	 $qid=$idm;
	// echo $qid;
	 if($qid!='otify'&&$qid!='map' && $qid!='graph'){
	//echo kkkk;
	   $query = "SELECT qid from {question} where url='".$idm."'";
	    $quest = db_query($query);
	  $qid = db_result($quest); 
	 
	 }
	 
	 if($qid=='otify'|| $qid=='map' || $qid=='graph'){
	// echo jkjjjj;
		   $query = "SELECT qid from {question} order by qid DESC limit 0,1 ";
		  $quest = db_query($query);
	 $qid = db_result($quest);
	 }
   
	 
	 return $qid;*/
	
}

function notify_report($idb='') {
    global $gSitePath,$user,$gDocPath,$base_root;
  $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
//echo veni  .$idb;
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
	"element":  $("notify-panel"),
	"url":       "'.$gSitePath.'notify/repcontent/'.$idb.'?t=per"
	});
	});
	
	$("qTabs2Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("notify-panel"),
	"url":       "'.$gSitePath.'notify/repcontent/'.$idb.'?t=time"
	});
	});
	
	$("qTabs3Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("notify-panel"),
	"url":       "'.$gSitePath.'notify/repcontent/'.$idb.'?t=area"
	});
	});

	
	</script>';

}
function notify_content() {
    global $gSitePath,$user,$gDocPath,$base_root;
      $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
	if(($idb=='otify')||($idb=='repcontent'))
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
   
	 //echo "kkkkkkkk".$qid;
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

function mail_sent_reply()
{
 global $gSitePath,$user,$gDocPath,$base_root,$base_path;

	$numrancnt = db_result(db_query("SELECT COUNT(*) from follower as a, question as b  where a.uid=".$user->uid."  and a.follower_status='1' and a.follower_id=b.uid "));
	if($numrancnt==0)
	$sel_flow="select * from follower as a, question as b  where a.follower_id=".$user->uid."   and a.uid=b.uid ";
	else
	$sel_flow="select * from follower as a, question as b  where a.uid=".$user->uid."  and a.follower_status='1' and a.follower_id=b.uid ";
	$rs_folwin=db_query($sel_flow);
	
	while($flwing_result=db_fetch_object($rs_folwin))
	{
	
    $update_quest="delete  from possible_answer_vote where qid=".$flwing_result->qid." and uid=".$user->uid." ";

$ress=db_query($update_quest);


    }
 echo "Cleared Successfully";

}

function reply_box()
{

 global $gSitePath,$user,$gDocPath,$base_root,$base_path;


      echo '<script type="text/javascript" src="'.$gSitePath.drupal_get_path('theme', 'heardmentality').'/scripts/mootools-1.2-core.js"></script>
	<script type="text/javascript" src="'.$gSitePath.drupal_get_path('theme', 'heardmentality').'/scripts/mootools-1.2-more.js"></script>	<div id="log_response_txt"><!-- spanner --></div>
	<span class="clr"><!-- spanner --></span>';

	echo '<script type="text/javascript">
	window.addEvent(\'domready\', function() {
	
	if (!window.demo_path) window.demo_path = \'\';
	var demo_path = window.demo_path;
	
	$(\'cmt\').addEvent(\'submit\', function(e) {
	
	e.stop();
	
	var log = $(\'log_response_txt\').empty().addClass(\'ajax-loadings\');
	
	this.set(\'send\', {onComplete: function(response) { 
	log.removeClass(\'ajax-loadings\');
	log.set(\'html\', response);
	}});
	
	this.send();
	});
	});
	
	
	</script><form id="cmt"  method="post" action="'.$gSitePath.'savemsg"  ><textarea name="comment_txt" id="comment_txt" ></textarea><br>
	<input type="submit" name="buttonvote" id="message"  value="Send "/></form>';

}

function savemessage()
{

echo "jjjjjjjjjjjj";

}