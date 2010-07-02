<?php
function qlitemini() {
    global $gSitePath,$user,$gDocPath,$base_root,$base_path;
    //SELECT answer, vote * 2.75/100 AS PercentOfTotal FROM suggested_answer order by PercentOfTotal desc limit 0,3
    $voutput = '';
    drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/main.css');
    drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/page.css');
    drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/tabs.css');
	//drupal_add_js('http://cdn.gigya.com/wildfire/js/wfapiv2.js');
    
    $qid = get_qid();
    $voutput .= '<script src="http://cdn.gigya.com/wildfire/js/wfapiv2.js"></script> 
	<script type="text/javascript">
		 var pconf1={  
         CID: "Site 1 - Widget A",  
         defaultContent: window.location.href,  
         UIConfig: \'<config><display showPost="true" showBookmark="true" showEmail="true" /></config>\'  
     };  
   
       
		function formsubmittype(mtype,ids){
		
		if(mtype==1)
		{
		
		
		document.getElementById(\'answer_frm\').submit();
		}
		if(mtype==2)
		{
		
		load_invite(\''.$gSitePath.'invite/invite_friends?qid='.$qid.'\',\'Profile \');
		//onclick="load_invite(\''.$gSitePath.'invite/invite_friends?qid='.$qid.'\',\'Profile\');
		}
		if(mtype==3)
		{
		loadflagquestion(\''.$gSitePath.'qlite/flag/\'+ids,\'Report \');
		
		}
		if(mtype==4)
		{
		loadsuggest(\''.$gSitePath.'qlite/suggest/\'+ids,\'Answers \');
		
		}
		if(mtype==5)
		{
		window.location.href="'.$gSitePath.'mashup/'.$qid.'";
		
		}
		}
		function displayBook()
		{
			document.getElementById("divWildfirePost").style.display="block"
		}
		function hideBook()
		{
			document.getElementById("divWildfirePost").style.display="none"
		}
		</script>
		';
    
    $optio = '';
    //for calculating active points
    cal_active_rate();
    
    $vSql = "select * from {question} where qid='$qid' ";
    $rlist = db_query($vSql);
    $oListquest = db_fetch_object($rlist);
    
    $list_lengthan = db_query("select * from {possible_answer_vote} where qid='".$qid."' and uid='".$user->uid."'  ");
    $numran = mysql_num_rows($list_lengthan);
    $answer_id = db_fetch_object($list_lengthan);
    
    drupal_set_title(myTruncate($oListquest->question, 80, '', '..').'  <a href="'.$gSitePath.$oListquest->url.'">View More</a>');
    $voutput .= '
		
		<div class="lft_view"> <!--<h4 class="cmt_name"><a>'.$oListquest->question.' </a></h4>-->
		<p>'.$oListquest->context.'</p><div align="right">
		<a href="javascript:void(0)" onmouseover="displayBook()">Bookmarks</a>
		<!-- AddThis Button BEGIN -->
<!--a class="addthis_button" href="http://www.addthis.com/bookmark.php?v=250&amp;username=xa-4bebc2a1621b1868"><img src="http://s7.addthis.com/static/btn/v2/lg-share-en.gif" width="125" height="16" alt="Bookmark and Share" style="border:0"/></a><script type="text/javascript" src="http://s7.addthis.com/js/250/addthis_widget.js#username=xa-4bebc2a1621b1868"></script-->
<!-- AddThis Button END -->
		<textarea rows="1" cols="1" id="TEXTAREA_ID" style="display: none">  
    	  Hello from Gigya!!! (Post content)  
	    </textarea>
		
		
		<select name="txt_act" id="txt_act"  onchange="formsubmittype(this.value,'.$qid.');">
		<option value=""> Select</option >
		'.$optio.'
		<option value="2"> Invite</option >
		<option value="3"> Flag</option >
		<option value="4">Suggest New Answer</option> 
		<option value="5">Create Mashup:</option> 
		</select>
		</div>
		<div id="divWildfirePost" onmouseout="hideBook()"></div>
		<script> Wildfire.initPost("PARTNER-ID", "divWildfirePost", 400, 300, pconf1);  </script>
		';
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

function get_qid_old() {
    
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
	<li id="qTabs1Link" class="selected"><a>Votes</a></li>
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
    
     $query = " SELECT (SELECT count( * ) FROM forum_wavelets AS w WHERE w.wid = f.fid GROUP BY w.wid ) AS wcnt FROM forum_wave AS f WHERE f.qid_rid = '$qid' ";
    $list = ExecuteQuery($query, "select");
   	$x=0;
	foreach($list as $fcnt){
		
		$x=$x+$fcnt['wcnt'];
	}
	 
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

    
    $output .= '<div>'.$x.' comments &nbsp;&nbsp;&nbsp;'.$numres.' Resources </div>';
    
    echo $output;
}

function load_ajax() {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    $output = '';
    $action = $_REQUEST['action'];
    
    switch ($action) {
        
        case '1':
        case '2':
            
            $output = '';
            
            $output .= get_top_list();
            
            $output .= get_hot_list();
            
            $output .= get_local_list();
            
            echo $output;
            
            break;
        case '5':
            extract($_REQUEST);
            
            $query = "SELECT * from {category} where parent_id='$cid' ORDER BY cat_name ASC";
            $list = ExecuteQuery($query, "select");
            $output .= '<select id="tscat" onchange="get_toplist(this.value,2)"><option value="" >Select</option>';
            foreach ($list as $cat) {
                
                $output .= '<option value='.$cat['cat_id'].' > '.$cat['cat_name'].' </option>';
            }
            
            $output .= '</select>';
            
            echo $output;
            break;
        default:
            
            break;

    
    }
    
    exit;

}




?>
