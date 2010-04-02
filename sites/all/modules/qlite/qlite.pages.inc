<?php
function qlitemini() {
    global $gSitePath,$user,$gDocPath,$base_root,$base_path;
    //SELECT answer, vote * 2.75/100 AS PercentOfTotal FROM suggested_answer order by PercentOfTotal desc limit 0,3
    
    drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/main.css');
    drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/page.css');
    drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/tabs.css');

  $qid=get_qid();
	 

   // $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $query = "SELECT qid, SUM(vote) as possiblevote FROM possible_answer where qid='$qid' GROUP BY qid";
    $query_list = db_query($query);
    $fetvot = db_fetch_object($query_list);
    //echo $fetvot->possiblevote;
    
    $query_sugest = "SELECT qid, SUM(vote) as suggestv FROM suggest_answer where qid='$qid' GROUP BY qid";
    $query_sugestlist = db_query($query_sugest);
    $fetvotsugest = db_fetch_object($query_sugestlist);
    
    $totalvotes = $fetvot->possiblevote + $fetvotsugest->suggestv;

    
    $percent = 2.5 / 100 * $totalvotes;
    //echo $percent;
    $tot = $percent * 100;
    // echo "<br/>";
    $vSql = "select * from {question} where status='1' and qid=$qid ";
    $rlist = db_query($vSql);
    $oListquest = db_fetch_object($rlist);
    
    $vuser = "select * from {users} where  uid=$oListquest->uid ";
    $username = db_query($vuser);
    $ufet = db_fetch_object($username);
    $list_lengthan = db_query("select * from {possible_answer_vote} where qid='".$qid."' and uid='".$user->uid."'  ");
    $numran = mysql_num_rows($list_lengthan);
    $answer_id = db_fetch_object($list_lengthan);
    drupal_set_title($oListquest->question);
    $voutput = '<form id="answer" name="answer" method="post" action="'.$gSitePath.'qlite/save"  > <input type="hidden" name="mid" value="'.$qid.'"><div class="cmt_list">
		<div class="lft_view"> <!--<h4 class="cmt_name"><a>'.$oListquest->question.' </a></h4>-->
		<p>'.$oListquest->context.'</p>';
    $vans = "select * from {possible_answer} where  qid=$qid order by paid ASC";

    
    $vlist = db_query($vans);
    $chk = '';
    while ($vlistquest = db_fetch_object($vlist)) {
        if ($numran == 0) {
            $answprc = $vlistquest->vote / 100 * $totalvotes;
            $valu = $answprc * 100;
            $voutput .= '
		 <p><input name="answer" type="radio" value="'.$vlistquest->paid.'" />
		'.$vlistquest->answer.'   </p>';
        } else {
            $answprc = $vlistquest->vote / 100 * $totalvotes;
            $valu = $answprc * 100;
            $chk = '';
            if ($answer_id->panswer_id == $vlistquest->paid) {
                
                $chk = "checked";
            }
            $voutput .= ' <p><input name="answer_al" type="radio" '.$chk.'  value="'.$vlistquest->paid.'" />
		'.$vlistquest->answer.'   </p>';
        
        }
        $chk = '';
    }
    $vsans = "select * from {suggest_answer} where  qid=$qid ";

    
    $vslist = db_query($vsans);
    
    while ($vlsistquest = db_fetch_object($vslist)) {

        
        $answprcs = $vlsistquest->vote / 100 * $totalvotes;
        
        $valuss = $answprcs * 100;
        if ($valuss > $tot) {
            
            $insert_change = "insert into suggest_ans_changeids (qid,ans_id)Values('".$qid."','".$vlsistquest->said."') ";
            $listchnge = db_query($insert_change);

            
            $select_allv = "select * from suggest_answer_vote where answer_id=$vlsistquest->said  ";
            $listam = db_query($select_allv);
            
            while ($listamqry = db_fetch_object($listam)) {

                
                $insert_white = "insert into suggest_ans_tmp (qid,uid,answer_id,vote,vote_date)Values('".$qid."','".$listamqry->uid."','".$vlsistquest->said."','".$vlsistquest->vote."','".$listamqry->vote_date."') ";
                $qrylist = db_query($insert_white);

            
            }
            //echo $valuss;
            //echo $vlsistquest->said;
        
        }

    
    }

    
    $mysql_sug_rows = mysql_num_rows(mysql_query("select distinct(answer_id) from suggest_ans_tmp  "));

    
    //echo $mysql_sug_rows;
    $vpans = "select * from {possible_answer} where  qid='".$qid."' order by paid desc limit 0,$mysql_sug_rows ";

    
    $vplist = db_query($vpans);
    
    while ($vplistquest = db_fetch_object($vplist)) {
        
        $insert_list_ids = "insert into possible_answer_changeids (qid,ans_id)Values('".$qid."','".$vplistquest->paid."') ";
        $qrylist_change = db_query($insert_list_ids);

        
        $select_allvp = "select * from possible_answer_vote where panswer_id=$vplistquest->paid  ";
        $listamp = db_query($select_allvp);
        
        while ($listamqryamp = db_fetch_object($listamp)) {

            
            $insert_whited = "insert into possible_answer_tmp (qid,uid,panswer_id,vote,vote_pdate)Values('".$qid."','".$listamqryamp->uid."','".$vplistquest->paid."','".$vplistquest->vote."','".$listamqryamp->vote_pdate."') ";
            $qrylist = db_query($insert_whited);

        
        }

    
    }

    
    $qry1 = mysql_query("select * from suggest_ans_changeids where qid ='$qid'");
    
    while ($row1 = mysql_fetch_array($qry1)) {
        $array1[] = $row1['ans_id'];
    }
    
    $qry2 = mysql_query("select * from possible_answer_changeids where qid ='$qid' ");
    while ($row2 = mysql_fetch_array($qry2)) {
        $array2[] = $row2['ans_id'];
    }
    
    for ($x = 0; $x < sizeof($array1); $x++) {
        $array[] = $array1[$x]." - ".$array2[$x];
        
        $array1[$x]." - ".$array2[$x];

        
        $update_idss = db_query("update possible_answer_tmp set  panswer_id='$array1[$x]'  where panswer_id='$array2[$x]' ");

        
        $updateval = db_query("update suggest_ans_tmp set  answer_id='$array2[$x]' where answer_id='$array1[$x]'");
        
        $deletsug = db_query("delete from suggest_answer_vote where answer_id='$array1[$x]'");
        
        $deletpos = db_query("delete from possible_answer_vote where panswer_id='$array2[$x]'");

        
        $rechange_list = db_query("select * from {possible_answer} where  paid='".$array2[$x]."'  ");
        
        $rechg = db_fetch_object($rechange_list);
        $rechg->vote;
        
        $rechange_list_new = db_query("select * from {suggest_answer} where  said='".$array1[$x]."'  ");
        
        $rechg_new = db_fetch_object($rechange_list_new);
        $rechg_new->vote;

        
        $update_ids = "update possible_answer set  answer='$rechg_new->answer', vote='$rechg_new->vote'  where paid='$array2[$x]' ";
        $updateqry = db_query($update_ids);
        
        $update_sug = "update suggest_answer set  answer='$rechg->answer', vote='$rechg->vote' where said='$array1[$x]' ";
        
        $updateqrys = db_query($update_sug);

        
        $delossld = "delete  from possible_answer_changeids where ans_id='".$array2[$x]."'";
        
        $delssqry = db_query($delossld);

        
        $deloldwds = "delete  from suggest_ans_changeids where ans_id='".$array1[$x]."'";
        
        $delqrysss = db_query($deloldwds);

    
    }
    
    $seltmp = db_query("select * from suggest_ans_tmp");
    
    while ($tmp_rec = db_fetch_object($seltmp)) {
        
        $insert_dumm = "insert into possible_answer_vote (qid,uid,panswer_id,vote_pdate) values ('".$tmp_rec->qid."','".$tmp_rec->uid."','".$tmp_rec->answer_id."','".$tmp_rec->vote_date."')";
        $dumy_rec = mysql_query($insert_dumm);
        
        $deltmp = db_query("delete  from suggest_ans_tmp");
    
    }
    
    $seltmps = db_query("select * from possible_answer_tmp");
    
    while ($tmp_recs = db_fetch_object($seltmps)) {
        
        $insert_dumms = "insert into suggest_answer_vote (qid,uid,answer_id,vote_date) values ('".$tmp_recs->qid."','".$tmp_recs->uid."','".$tmp_recs->panswer_id."','".$tmp_recs->vote_pdate."')";
        $dumy_recs = mysql_query($insert_dumms);
        
        $deltmps = db_query("delete  from possible_answer_tmp");
    
    }

    
    $voutput .= '<script type="text/javascript">
		function formsubmittype(mtype,ids){
		
		if(mtype==1)
		{
		document.forms["answer"].submit();
		
		}
		if(mtype==3)
		{
		loadflagquestion(\''.$gSitePath.'qlite/flag/\'+ids,\'Report \');
		
		}
		if(mtype==4)
		{
		loadsuggest(\''.$gSitePath.'qlite/suggest/\'+ids,\'Answers \');
		
		}
		}
		</script>
		';
    if ($numran != 0) {
        
        $optio = '<option value="1"> Withdraw answer</option>';
    }
    if ($numran == 0) {
        
        $submitbutt = ' <p><input type="submit" name="save" id="save" value="Vote" /></p>';
    }
    $voutput .= $submitbutt.' 
		
		</div></div></form>';

   // $voutput.=qlite_report($qid);
    return $voutput;
}

function get_qid(){
	
	 global $gSitePath,$user,$gDocPath,$base_root;
	 if($user->uid>0){
	
	   $query = "SELECT qid from {question} where uid='".$user->uid."' order by qid DESC limit 0,1 ";
	   
	 }else{
	 	
		   $query = "SELECT qid from {question} order by qid DESC limit 0,1 ";
		
	 }
    $quest = db_query($query);
	 $qid = db_result($quest);
	 
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
    echo $output;
}




?>
