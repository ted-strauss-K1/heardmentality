<?php

function moderate_user()
{
global $gSitePath,$user, $gDocPath,$base_root,$base_path;
 drupal_add_js(drupal_get_path('module', 'moderator').'/scripts/moderate.js');

$seldonar="select count(nodeid) as cnt ,f.nodeid from question_flags as f   where f.type='question'   group by nodeid";

$res_donar=db_query($seldonar);
$moduser='<div id="nlist"></div>
	<form id="notify" method="post" action="'.$gSitePath.'admin/notifymail" ><table width="100%" border="1">
  <tr>
    <td>Question </td>
    <td>Flagged </td>
    <td>Question Author </td>
	 <td>Status</td>
    <td></td>
  </tr>';
while($don=db_fetch_object($res_donar))
{
 $sequest="select * from question where qid='".$don->nodeid."'";
$res_quest=db_query($sequest);
$qlist=db_fetch_object($res_quest);
 // $ss=$qlist->question;
 $sellist="select * from users where uid='".$qlist->uid."'";
$res_users=db_query($sellist);
$usert=db_fetch_object($res_users);
 $uname=$usert->name;
if($user->uid!=$qlist->uid)
{
if($usert->status=='0')
{
$blockedst="Blocked";
}
$moduser.='<tr>
    <td>'.$qlist->question.'</td>
    <td>'.$don->cnt.'</td>
    <td>'.$uname.' </td>
	 <td>'.$blockedst.' </td>
    <td><input type="checkbox" class="check-user" name="us_id[]" value="'.$don->nodeid.'" /> </td>
  </tr>';
}

}
$moduser.=' </table><div id="showbox_user" align="left" style="width:100%;display:none"><label for="warn_msg"><b>Send Warning Message :</b></label><br/><textarea name="warn_msg" cols="55" row="17" id="warn_msg"></textarea></div><div><input type="hidden" id="action_value" name="action_value" value=""/> <input type="button" onclick="send_notify(1);"  value="Send warning message"/>&nbsp; <input onclick="send_suspend(0);" type="button" value="Suspend User"/></div>';
 
return $moduser;




}
function moderate_user_mail()
{
global $gSitePath,$user, $gDocPath,$base_root,$base_path;

$us_id = implode(',', $_REQUEST['us_id']);
$idr=$_REQUEST['us_id'];
		if ($_REQUEST['action_value']) {
		
		
		foreach ($idr as $idd) {
		
		$query = db_query("select u.mail,u.uid,q.question  from {question} as q left join {users} as u on u.uid=q.uid where qid='$idd' ");
		$det = db_fetch_object($query);
		
		quest_mail_warning($det->uid); 
		}
		echo '<div class="success">Warning Message Send!</div>';
		} else {
		
		
		
		foreach ($idr as $idd) {
		
		
		
		$query = db_query("select u.mail,u.uid,q.question  from {question} as q left join {users} as u on u.uid=q.uid where qid='$us_id' ");
		$det = db_fetch_object($query);
		$query_block = db_query("update {users} set status='0' where uid='$det->uid'");
		}
		
		
		
		echo '<div class="success">Suspended  successfully!</div>';
		quest_mail($_REQUEST['us_id']);
		}

}





function quest_mail($qids = '') {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    
     $from = variable_get('site_mail');
     $subject = 'Heardmentality suspended Your account  ';
  $warn = $_REQUEST['warn_msg'];
    foreach ($qids as $id) {

      
        $query = db_query("select u.mail,q.question  from {question} as q left join {users} as u on u.uid=q.uid where qid='$id' ");
        $det = db_fetch_object($query);
        
         $to = $det->mail;
         $msg = '<br/>Question : '.$det->question.' '.$warn.'<br/>';
        if(!empty($to)){
        	
			 $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
       
    }
return true;
}



function quest_mail_warning($qids = '') {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    
     $from = variable_get('site_mail');
     $subject = 'Heardmentality Warning Mail for Flagged question of yours  ';
   $warn='Has been Flagged Many times, This is warning message from Heardmentality .If this continues we will block Your account';
    foreach ($qids as $id) {

      
        $query = db_query("select u.mail,q.question  from {question} as q left join {users} as u on u.uid=q.uid where qid='$id' ");
        $det = db_fetch_object($query);
        
         $to = $det->mail;
         $msg = '<br/>Question : '.$det->question.' '.$warn.'<br/>';
        if(!empty($to)){
        	
			 $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
       
    }
return true;
}
function moderate_quest()
{

global $gSitePath,$user,$gDocPath,$base_root,$base_path;
	

$page_name="moderatequestion"; 
if(isset($_GET['start'])){
	$start=$_GET['start'];
	
}

if(strlen($start) > 0 and !is_numeric($start)){
echo "Data Error";
exit;
}


$eu = ($start - 0); 
$limit = 10;                                 
$this1 = $eu + $limit; 
$back = $eu - $limit; 
$next = $eu + $limit; 

$modquest.='
	<form id="notify" method="post" action="'.$gSitePath.'admin/notifymail" ><table width="100%" border="1">
  <tr>
    <td>Question </td>
 
    <td>Question Author </td>
	 <td>Status</td>
    <td></td>
  </tr>';
	

	
	
	$sel="SELECT * FROM {question}     ";
	
	$user_qry=db_query($sel);
	
	$sel_count = db_result(db_query("SELECT COUNT(*) FROM {question}    "));
	$sel.=" limit  $eu, $limit";
	
	$sel_search=db_query($sel);
	while($qid_result=db_fetch_object($sel_search))
	{
	if($qid_result->status=='1')
	{
	$blockedst='Active';
	
	}
	else
	{
	
	$blockedst='Inactive';
	
	}
	$sellist="select * from users where uid='".$qid_result->uid."'";
	$res_users=db_query($sellist);
	$usert=db_fetch_object($res_users);
	$uname=$usert->name;
	$modquest.='<tr>
	<td><a href="../'.$qid_result->url.'">'.wordwrap($qid_result->question,"50","<br/>\n").'</a></td>
	
	<td>'.$uname.' </td>
	<td>'.$blockedst.' </td>
	<td><a href="'.$gSitePath.'admin/editquestions/'.$qid_result->qid.'">Edit </a> / <a href="'.$gSitePath.'admin/moderatequestion?del='.$qid_result->qid.'"> Delete </a>/<a href="'.$gSitePath.'admin/viewquestion/'.$qid_result->qid.'"> View </a>  </td>
	</tr>';
	
	
	}
	
	
	$modquest.='</table>';
	/////////////////////////////// 
if($sel_count > $limit ){ // Let us display bottom links if sufficient records are there for paging

/////////////// Start the bottom links with Prev and next link with page numbers /////////////////
$fetresult.="<table align = 'center' width='100%'><tr><td  align='left' width='30%'>";
//// if our variable $back is equal to 0 or more then only we will display the link to move back ////////
if($back >=0) { 
$modquest.= "<a href='$page_name?start=$back&$lkr'><font face='Verdana' size='2'>PREV</font></a>"; 
} 
//////////////// Let us display the page links at  center. We will not display the current page as a link ///////////
$modquest.= "</td><td align=center width='30%'>";
$i=0;
$l=1;
for($i=0;$i < $sel_count;$i=$i+$limit){
if($i <> $eu){
$modquest.= " <a href='$page_name?start=$i&$lkr'><font face='Verdana' size='2'>$l</font></a> ";
}
else { $fetresult.= "<font face='Verdana' size='4' color=red>$l</font>";}        /// Current page is not displayed as link and given font color red
$l=$l+1;
}


$modquest.="</td><td  align='right' width='30%'>";
///////////// If we are not in the last page then Next link will be displayed. Here we check that /////
if($this1 < $sel_count) { 
$modquest.= "<a href='$page_name?start=$next&$lkr'><font face='Verdana' size='2'>NEXT</font></a>";} 
$modquest.= "</td></tr></table>";

}

if($sel_count==0)
{
$modquest.='<b>No Search Results </b>';

}
	
	
if(isset($_REQUEST['del']))
{

//echo "lllll";
$del_ques=db_query("Delete  FROM {question} where qid='".$_REQUEST['del']."'    ");
$del_answ=db_query("Delete  FROM {possible_answer} where qid='".$_REQUEST['del']."'    ");
$del_sansw=db_query("Delete  FROM {suggest_answer} where qid='".$_REQUEST['del']."'    ");
question_deleted_mail($_REQUEST['del']);
question_deleted_mail_voters($_REQUEST['del']);
question_deleted_mail_suggest($_REQUEST['del']);
	echo '<div class="success">Deleted   successfully!</div>';
drupal_goto('admin/moderatequestion');
}

return $modquest;



}

function question_deleted_mail($qaid) {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    
     $from = variable_get('site_mail');
     $subject = 'Heardmentality Question Has Been Deleted ';
   $delmsg='Has been Deleted By Headmentality admin';
 
        $query = db_query("select u.mail,q.question  from {question} as q left join {users} as u on u.uid=q.uid where q.qid='$qaid' ");
        $det = db_fetch_object($query);
        
        $to = $det->mail;
         $msg = '<br/>Question : '.$det->question.' '.$delmsg.'<br/>';
        if(!empty($to)){
        	
			 $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
       
   
return true;
}

function question_deleted_mail_voters($qaid) {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    
     $from = variable_get('site_mail');
     $subject = 'Heardmentality question  Has Been Deleted which You have  answered  ';
   $delmsg='Has been Deleted By Headmentality admin';

       $query = db_query("select u.question,q.uid  from possible_answer_vote as q left join question as u on u.qid=q.qid where q.qid='$qaid' ");
      
        while($det = db_fetch_object($query))
		{
        	
	$sellist="select * from users where uid='".$det->uid."'";
	$res_users=db_query($sellist);
	$usert=db_fetch_object($res_users);
	 $to = $usert->mail;
         $msg = '<br/>Question : '.$det->question.' '.$delmsg.'<br/>';
		 
		 
		 
        if(!empty($to)){
        	
			 $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
       
   }
return true;
}

function question_deleted_mail_suggest($qaid) {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    
     $from = variable_get('site_mail');
     $subject = 'Heardmentality question  Has Been Deleted which You have  answered  ';
   $delmsg='Has been Deleted By Headmentality admin';

       $query = db_query("select u.question,q.uid  from suggest_answer as q left join question as u on u.qid=q.qid where q.qid='$qaid' ");
      
        while($det = db_fetch_object($query))
		{
        	
	$sellist="select * from users where uid='".$det->uid."'";
	$res_users=db_query($sellist);
	$usert=db_fetch_object($res_users);
	 $to = $usert->mail;
         $msg = '<br/>Question : '.$det->question.' '.$delmsg.'<br/>';
		 
		 
		 
        if(!empty($to)){
        	
			 $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
       
   }
return true;
}
function get_tagging($tag = '') {
    global $gSitePath,$user,$gDocPath,$base_root,$base_path;
    $randomtag = '';
    $content = '';
    $tagged = '';
    
    $randomtag = popular_tag();
    if ($tag != '') {
        
        $exp = explode(",", $tag);

        
        foreach ($exp as $list) {
            
            $tagged .= '<div id="tagset" class="tagging-tag" onclick="tag_delq(this);return false;">'.$list.'</div>';
        }
    
    }
    $content .= '<div id="tagging-widget-container">
        <fieldset>
            <legend>
            <b><i>    Tag Question for Searching </i></b>
            </legend>
            <div id="tagdiv" class="tagging-curtags-wrapper tagging-curtags-wrapper-1">
                <label>
                    Assigned Tags:
                </label>
				'.$tagged.'
            </div>
            <div class="form-item" id="tagging-widget-input-1-wrapper">
			
                <span class="field-prefix">
                    <div class="taggin-widget-input-wrapper">
                        <input maxlength="20" tabindex="20" name="taxonomy[tags][1]" id="tagging-widget-input-1" value="" class="form-text form-autocomplete tagging-widget-input tagging-widget-input-1" type="text"><span class="field-suffix"><a class="tagging-button-container" href="#" title="Add"><span class="tagging-button tagging-button-1"></span></a>
						
						<input name="taxonomy[tags][1]" id="edit-taxonomy-tags-1" value="" class="tagging-widget-target-1" type="hidden"></span>
						
						<input name="q_tag" type="hidden" id="q_tag" value="'.$tag.'"  >
                    </div>
                </span>
                <div class="description">
                   Add New Tag
                </div>
            </div>
            <input class="autocomplete" id="tagging-widget-input-1-autocomplete" value="http://localhost/heardmentalitylocal/taxonomy/autocomplete/1" disabled="disabled" type="hidden">
          
		    <div id="sug_div" class="tagging-suggestions-wrapper tagging-suggestions-wrapper-1">
               <label>Suggestions:</label>
               '.$randomtag.'
            </div>
        </fieldset></div>';

    
    return $content;
}
function edit_questions()
{
    global $gSitePath,$user,$gDocPath,$base_root;

  
    $output = '';

    
    drupal_set_html_head('<script src="http://ws.geonames.org/export/geonamesData.js"
        type="text/javascript"></script>');

    
    if (isset($_POST['update'])) {
        
        question_edit_save_admin($_POST);
    }
    
    $result = geonames_query('countryinfo');
    foreach ($result->results as $country) {
        $optionlist .= sprintf('<option value="%s">%s</option>', $country['countrycode'], $country['countryname']);
    }

    
    $nid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    
   // $result = db_query("SELECT * FROM {question} as q left join {qtag} as t on q.qid=t.qid where q.qid='".$nid."' ");
    echo $qry = "SELECT * FROM {question} as q join {question_cat} as t on q.qid=t.qid where q.qid='".$nid."' group by t.qid ";
     $result = db_query($qry);
    $quest = db_fetch_object($result);
  //  drupal_add_js(drupal_get_path('module', 'question').'/scripts/question.js');
    $output .= '
		<script type="text/javascript">
		
					
			function get_subcat(sid,divid,level){
			
										var foo = [];
										$(sid).getSelected().each(function(number,i){
										if(number.value!=\'\'){
										  foo[i] =number.value;
												}
											});
										var foo = foo.filter(function(item, index){
    return item > 0;
});
			  						 var ids = foo.toString();
			   					
			  							if(level==1){
									$(\'cat1\').set(\'value\',ids);
									$(\'chg_sscat\').fade(\'out\');
										}
									
									if(level==2){
									
									$(\'cat2\').set(\'value\',ids);
									$(\'chg_sscat\').fade(\'in\');
										}
									
									if(level==3)
									$(\'cat3\').set(\'value\',ids);
									
									if(ids.length>0){
									
									if(level<3){
									var url = "'.$gSitePath.'question/ajax";
									var req = new Request({    
											method: \'get\'
											,url: url
											,data: { \'action\':level,\'ids\':ids},
											onRequest: function() { },
											onComplete: function(response) {
													 $(divid).set(\'html\', response);
											}
									}).send();
							}
							}else{
							 $(divid).set(\'html\',\'No Subcategory\');
							}
							}	
						
						
									function setDefaultCountry() {
  var countrySelect = document.getElementById("q_country");

  for (i=0;i< countrySelect.length;i++) {
			// the javascript geonamesData.js contains the countrycode
			// of the userIp in the variable \'geonamesUserIpCountryCode\'
			if (countrySelect[i].value == \''.$quest->country.'\') {
			  // set the country selectionfield
				  countrySelect.selectedIndex = i;
				 
				get_state(\''.$quest->country.'\');
				
			}else if(countrySelect[i].value == geonamesUserIpCountryCode) {
			 countrySelect.selectedIndex = i;
			 get_state(geonamesUserIpCountryCode);
			}
	}

}
		function setState(){
		
							var stid=\''.$quest->state.'\';
					if(stid!=""){
								 var stateSelect = document.getElementById("q_state");
								
							  for (i=0;i< stateSelect.length;i++) {
								// the javascript geonamesData.js contains the countrycode
								// of the userIp in the variable \'geonamesUserIpCountryCode\'
								if (stateSelect[i].value == \''.$quest->state.'\') {
								  // set the country selectionfield
									  stateSelect.selectedIndex = i;
									 
									get_city(stid);
								}
								
					}
				  }
		}
		
		function setCity(){
		
							var cid=\''.$quest->city.'\';
					if(cid!=""){
								 var citySelect = document.getElementById("q_city");
							
							  for (i=0;i< citySelect.length;i++) {
								// the javascript geonamesData.js contains the countrycode
								// of the userIp in the variable \'geonamesUserIpCountryCode\'
								if (citySelect[i].value == cid) {
								  // set the country selectionfield
									  citySelect.selectedIndex = i;
									 
								}
								
					}
				  }
		}
		
		
window.setTimeout("setDefaultCountry()", 1000);
window.setTimeout("setState()", 2000);
window.setTimeout("setCity()", 3000);
window.addEvent(\'domready\', function(){
setDefaultCountry();
});
							function get_state(code){
						
						var url = "'.$gSitePath.'question/ajax";
									var req = new Request({    
											method: \'get\'
											,url: url
											,data: { \'action\':1,\'code\':code},
											onRequest: function() { },
											onComplete: function(response) {
													 $(\'chg_state\').set(\'html\', response);
											}
									}).send();
						
						 $(\'chg_city\').fade(\'out\');
						}
							function get_city(code){
							 $(\'chg_city\').fade(\'in\');
							var url = "'.$gSitePath.'question/ajax";
									var req = new Request({    
											method: \'get\'
											,url: url
											,data: { \'action\':2,\'code\':code},
											onRequest: function() { },
											onComplete: function(response) {
													 $(\'chg_city\').set(\'html\', response);
											}
									}).send();
							
							}
							
						</script>
		
			
			';
    
    $output .= '<link rel="stylesheet" href="'.$gSitePath.'sites/all/themes/heardmentality/css/content.css" type="text/css" />
<link rel="stylesheet" href="'.$gSitePath.'sites/all/themes/heardmentality/css/ui.css" type="text/css" />
<link rel="stylesheet" href="'.$gSitePath.'sites/all/modules/tagging/tagging.css" type="text/css" />';
    $output .= '<div id="err" class="clear"></div>
<div align="right"><span title="This field is required." class="form-required">*</span> Required Fields</div>
				<form id="question" name="question" method="post"   onsubmit="return validate_question();" ><table width="100%" border="0" align="center" style="border:0px;">
  <tr>
    <td width="0%" height="94">&nbsp;</td>
    <td width="14%">Question<span title="This field is required." class="form-required">*</span></td>
    <td colspan="4">
        <input type="text" name="q_quest"  tabindex="1" id="q_quest" value="'.$quest->question.'"  size="150"/>    </td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td valign="top">Context</td>
    <td colspan="4">
      <textarea   tabindex="2" name="q_context" id="q_context" cols="150" rows="2" style="border:1px solid #BBBBBB;

width:775px; scroll;">'.$quest->context.'</textarea>  </td>
  </tr>
  <tr><td>&nbsp;</td></tr>
    <tr>
    <td>&nbsp;</td>
    <td valign="top">Answer<span title="This field is required." class="form-required">*</span></td>
    <td width="26%" valign="top"><table width="100%" border="0">';

    
    $query = "SELECT * FROM {possible_answer} where qid='".$nid."' ";
    $ans = ExecuteQuery($query, "select");
    $i = 1;
    $tab = 3;
    foreach ($ans as $array) {
        
        $output .= ' <tr>
          <td>
            <input  tabindex="'.$tab++.'" name="q_ans'.$i.'" type="text" id="q_ans'.$i.'" size="40" value="'.$array['answer'].'" />&nbsp;<input type="hidden" name="aid'.$i.'" value="'.$array['paid'].'">
          </td>
        </tr>
        <tr><td>&nbsp;</td></tr>
          ';
        $i++;
    }

    
    $output .= '</table><div id="add_more"></div><div id="del_ans" style="visibility:hidden;"><small><a href="javascript:void(0);"  tabindex="88" onclick="del_ans();">[Remove]</a></div><small><br/>
	
	<input type="button" name="Add"  tabindex="13" id="Add" onclick="add_ans();" value="Add Answer" /> <input type="hidden" name="ans_cnt" id="ans_cnt" value="'.count($ans).'"><input type="hidden" id="cat1" name="cat1" value="'.$quest->cid.'">&nbsp;<input type="hidden" id="cat2" name="cat2" value="'.$quest->scid.'">&nbsp; <input type="hidden"  id="cat3" name="cat3" value="'.$quest->sscid.'"> 
	
	</td>
    <td colspan="3" valign="top" align="left"><table width="65%" border="0">
		<tr><td colspan="3" height="40"  valign="middle" ><b>Categories</b></td></tr>
      <tr>
        <td width="25%" align="left">



        <select  tabindex="14" name="q_cat[]" id="q_cat" multiple="multiple"  onchange="get_subcat(\'q_cat\',\'chg_scat\',1);"  size="5"><option value="">Select Category</option>';
    $client_select = db_query("SELECT cat_id,cat_name FROM {category} where parent_id='0'");
   // $ecat1 = explode(",", $quest->cid);
    while ($list = db_fetch_object($client_select)) {

        if($quest->cat==$list->cat_id)
        {
            $sel = 'SELECTED';
        }
        else
        {
            $sel = '';
        }
        /*if (in_array($list->cat_id, $ecat1)) {
            $sel = 'SELECTED="SELECTED"';
        } else {
            $sel = '';
        }*/
        $output .= '<option value="'.$list->cat_id.'" '.$sel.'>'.$list->cat_name.'</option>';

    }

    $output .= '</select>
    


        </td>
        <td width="25%" align="left"><div id="chg_scat"><select  tabindex="15" name="q_scat[]" onchange="get_subcat(q_scat,\'chg_sscat\',2);" id="q_scat" multiple="multiple"  size="5"><option value="">Select Sub Category</option>';
    $client_select1 = db_query("SELECT cat_id,cat_name FROM {category} where parent_id IN ('".$quest->cid."')");
    $ecat2 = explode(",", $quest->scid);
    while ($list = db_fetch_object($client_select1)) {
        if (in_array($list->cat_id, $ecat2)) {
            $sel = 'SELECTED="SELECTED"';
        } else {
            $sel = '';
        }

        
        $output .= '<option value="'.$list->cat_id.'" '.$sel.'>'.$list->cat_name.'</option>';
    
    }
    $output .= '</select></div></td>
        <td width="25%" align="left"><div id="chg_sscat"><select  tabindex="16" name="q_sscat[]" onchange="get_subcat(q_sscat,\'chg_sscat\',3);" id="q_sscat" multiple="multiple"  size="5"><option value="">Select Sub Sub Category</option>';
    if ($quest->scid != '') {
        $client_select2 = db_query("SELECT cat_id,cat_name FROM {category} where parent_id IN ('".$quest->scid."')");
        $ecat3 = explode(",", $quest->sscid);
        while ($list = db_fetch_object($client_select2)) {
            if (in_array($list->cat_id, $ecat3)) {
                $sel = 'SELECTED="SELECTED"';
            } else {
                $sel = '';
            }

            
            $output .= '<option value="'.$list->cat_id.'" '.$sel.'>'.$list->cat_name.'</option>';
        
        }
    }
    $output .= '</select></div></td>
      </tr>
	  <tr><td colspan="3" height="40"  valign="middle">&nbsp;<strong>Location</strong></td></tr>
	  <tr> <td width="13%">&nbsp;<!--<input type="text" name="q_country" id="q_country" value="Country" onblur="javascript: if(this.value == \'\') this.value=\'Country\';" onfocus="javascript: if(this.value == \'Country\') this.value=\'\';" size="30" />--><select name="q_country" style="width: 125px;" tabindex="17" onchange="get_state(this.value);" id="q_country">'.$optionlist.'</select></td>
	
    <td width="13%">&nbsp;<!--<input type="text" name="q_state" id="q_state" value="State"  onblur="javascript: if(this.value == \'\') this.value=\'State\';" onfocus="javascript: if(this.value == \'State\') this.value=\'\';"   size="30"/>--> <div id="chg_state"></div></td>
	
    <td width="43%">&nbsp;<!--<input type="text" name="q_city" id="q_city" value="City" onblur="javascript: if(this.value == \'\') this.value=\'City\';" onfocus="javascript: if(this.value == \'City\') this.value=\'\';"    size="30"/>--><div id="chg_city"></div></td></tr>
	
    </table></td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
 <td width="13%" align="left" colspan="4">
       </td>
 
  </tr>
  
  <!--<tr>
    <td>&nbsp;</td>
    <td nowrap="nowrap">End Date<span title="This field is required." class="form-required">*</span></td>
    <td><input type="text" name="q_edate" autocomplete="off" id="q_edate" value="'.$quest->enddate.'"  /> <small>Eg: yyyy-mm-dd</small></td>
    <td><input name="invite_count" type="hidden" id="invite_count" value="1" /></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>-->
  <tr><td colspan="6">';
    
    $output .= '<tr><td colspan="6"></td></tr>';

    
    $output .= ' </td></tr>
  
  <tr>
    <td height="42">&nbsp;</td>
    <td>&nbsp;</td>
    <td><input type="submit" name="update" tabindex="21" id="save" value="Update" /></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td align="right"></td>
  </tr>
</table>
</form>

';
    
    return $output;


}


function question_edit_save_admin($array) {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    $nid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    
    //  print_r($array);
    extract($array);
    $output = '';
    
    if (! empty($q_quest) && ! empty($q_ans1) && ! empty($q_ans2) && ! empty($cat1)) {
        $edate = $q_edate;
        $result = db_query("update {question} set question='$q_quest',context='$q_context',cid='$cat1',scid='$cat2',sscid='$cat3',	 global='$q_global',country='$q_country',state='$q_state',city='$q_city',enddate='$edate' where qid='".$nid."' ");
        
        $ins_id = db_last_insert_id('question', 'qid');
        for ($i = 1; $i <= $ans_cnt; $i++) {
            $name = "q_ans".$i;
            $aid = "aid".$i;
            if (! empty($$name)) {
                
                if (! empty($$aid)) {
                    $result = db_query("UPDATE {possible_answer} set answer='".$$name."' where paid='".$$aid."' AND qid='".$nid."'");
                } else {
                   // echo kkkkkkkkkk;
				//	echo "INSERT INTO {possible_answer} (qid,answer) VALUES (%d,'%s')", $nid, $$name;
                    $result = db_query("INSERT INTO {possible_answer} (qid,answer) VALUES (%d,'%s')", $nid, $$name);
                }
            }
        }
        
        if (db_query("select * from {qtag} where qid='".$nid."'")) {
            
           // db_query("update {qtag} set tag='".$q_tag."' where qid='".$nid."'");
        
        }
        
        if ($result)
            drupal_set_message(t('Thank you, Question updated successfully!'), $type = 'success');
		//	print_r($result);
		question_edited_mail($nid);
		question_edited_mail_voters($nid);
		question_edited_mail_suggest($nid);
    //  drupal_goto("admin/moderatequestion");
    } else {
        
        $_SESSION['post'] = $_POST;
        drupal_set_message($message = 'Sorry, Following required fields are Empty!', $type = 'error');
        
        if ( empty($q_quest))
            drupal_set_message($message = 'Question should not be Empty!', $type = 'error');
        
        if ( empty($q_ans1) || empty($q_ans2))
            drupal_set_message($message = 'Minimum 2 answers should be needed!', $type = 'error');
        
        if ( empty($cat1))
            drupal_set_message($message = 'Main Category should not be Empty!', $type = 'error');

    
    }
    
    return $output;
}
function view_questions()
{
          global $gSitePath,$user,$gDocPath,$base_root;

  
    $output = '';

    
    drupal_set_html_head('<script src="http://ws.geonames.org/export/geonamesData.js"
        type="text/javascript"></script>');

    
    if (isset($_POST['update'])) {
        
        question_edit_save_admin($_POST);
    }
    
    $result = geonames_query('countryinfo');
    foreach ($result->results as $country) {
        $optionlist .= sprintf('<option value="%s">%s</option>', $country['countrycode'], $country['countryname']);
    }

    
    $nid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    
    $result = db_query("SELECT * FROM {question} as q left join {qtag} as t on q.qid=t.qid where q.qid='".$nid."' ");
    $quest = db_fetch_object($result);
  //  drupal_add_js(drupal_get_path('module', 'question').'/scripts/question.js');
    $output .= '
		<script type="text/javascript">
		
					
			function get_subcat(sid,divid,level){
			
										var foo = [];
										$(sid).getSelected().each(function(number,i){
										if(number.value!=\'\'){
										  foo[i] =number.value;
												}
											});
										var foo = foo.filter(function(item, index){
    return item > 0;
});
			  						 var ids = foo.toString();
			   					
			  							if(level==1){
									$(\'cat1\').set(\'value\',ids);
									$(\'chg_sscat\').fade(\'out\');
										}
									
									if(level==2){
									
									$(\'cat2\').set(\'value\',ids);
									$(\'chg_sscat\').fade(\'in\');
										}
									
									if(level==3)
									$(\'cat3\').set(\'value\',ids);
									
									if(ids.length>0){
									
									if(level<3){
									var url = "'.$gSitePath.'question/ajax";
									var req = new Request({    
											method: \'get\'
											,url: url
											,data: { \'action\':level,\'ids\':ids},
											onRequest: function() { },
											onComplete: function(response) {
													 $(divid).set(\'html\', response);
											}
									}).send();
							}
							}else{
							 $(divid).set(\'html\',\'No Subcategory\');
							}
							}	
						
						
									function setDefaultCountry() {
  var countrySelect = document.getElementById("q_country");

  for (i=0;i< countrySelect.length;i++) {
			// the javascript geonamesData.js contains the countrycode
			// of the userIp in the variable \'geonamesUserIpCountryCode\'
			if (countrySelect[i].value == \''.$quest->country.'\') {
			  // set the country selectionfield
				  countrySelect.selectedIndex = i;
				 
				get_state(\''.$quest->country.'\');
				
			}else if(countrySelect[i].value == geonamesUserIpCountryCode) {
			 countrySelect.selectedIndex = i;
			 get_state(geonamesUserIpCountryCode);
			}
	}

}
		function setState(){
		
							var stid=\''.$quest->state.'\';
					if(stid!=""){
								 var stateSelect = document.getElementById("q_state");
								
							  for (i=0;i< stateSelect.length;i++) {
								// the javascript geonamesData.js contains the countrycode
								// of the userIp in the variable \'geonamesUserIpCountryCode\'
								if (stateSelect[i].value == \''.$quest->state.'\') {
								  // set the country selectionfield
									  stateSelect.selectedIndex = i;
									 
									get_city(stid);
								}
								
					}
				  }
		}
		
		function setCity(){
		
							var cid=\''.$quest->city.'\';
					if(cid!=""){
								 var citySelect = document.getElementById("q_city");
							
							  for (i=0;i< citySelect.length;i++) {
								// the javascript geonamesData.js contains the countrycode
								// of the userIp in the variable \'geonamesUserIpCountryCode\'
								if (citySelect[i].value == cid) {
								  // set the country selectionfield
									  citySelect.selectedIndex = i;
									 
								}
								
					}
				  }
		}
		
		
window.setTimeout("setDefaultCountry()", 1000);
window.setTimeout("setState()", 2000);
window.setTimeout("setCity()", 3000);
window.addEvent(\'domready\', function(){
setDefaultCountry();
});
							function get_state(code){
						
						var url = "'.$gSitePath.'question/ajax";
									var req = new Request({    
											method: \'get\'
											,url: url
											,data: { \'action\':1,\'code\':code},
											onRequest: function() { },
											onComplete: function(response) {
													 $(\'chg_state\').set(\'html\', response);
											}
									}).send();
						
						 $(\'chg_city\').fade(\'out\');
						}
							function get_city(code){
							 $(\'chg_city\').fade(\'in\');
							var url = "'.$gSitePath.'question/ajax";
									var req = new Request({    
											method: \'get\'
											,url: url
											,data: { \'action\':2,\'code\':code},
											onRequest: function() { },
											onComplete: function(response) {
													 $(\'chg_city\').set(\'html\', response);
											}
									}).send();
							
							}
							
						</script>
		
			
			';
    
    $output .= '<link rel="stylesheet" href="'.$gSitePath.'sites/all/themes/heardmentality/css/content.css" type="text/css" />
<link rel="stylesheet" href="'.$gSitePath.'sites/all/themes/heardmentality/css/ui.css" type="text/css" />
<link rel="stylesheet" href="'.$gSitePath.'sites/all/modules/tagging/tagging.css" type="text/css" />';
    $output .= '<div id="err" class="clear"></div>

				<form id="question_view" name="question_view" method="post" action="'.$gSitePath.'admin/moderatequestion"><table width="100%" border="0" align="center" style="border:0px;">
  <tr>
    <td width="0%" height="94">&nbsp;</td>
    <td width="14%">Question</td>
    <td colspan="4">
       '.$quest->question.'    </td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td valign="top">Context</td>
    <td colspan="4">
    '.$quest->context.' </td>
  </tr>
  <tr><td>&nbsp;</td></tr>
    <tr>
    <td>&nbsp;</td>
    <td valign="top">Answer</td>
    <td width="26%" valign="top"><table width="100%" border="0">';

    
    $query = "SELECT * FROM {possible_answer} where qid='".$nid."' ";
    $ans = ExecuteQuery($query, "select");
    $i = 1;
    $tab = 3;
    foreach ($ans as $array) {
        
        $output .= ' <tr>
          <td>
           '.$array['answer'].'
          </td>
        </tr>
        <tr><td>&nbsp;</td></tr>
          ';
        $i++;
    }

    
    $output .= '</table><div id="add_more"></div><div id="del_ans" style="visibility:hidden;"><small><a href="javascript:void(0);"  tabindex="88" onclick="del_ans();">[Remove]</a></div><small><br/>
	

	
	</td>
    <td colspan="3" valign="top" align="left"><table width="65%" border="0">
		<tr><td colspan="3" height="40"  valign="middle" ><b>Categories</b></td></tr>
      <tr>
        <td width="25%" align="left"><select  tabindex="14" name="q_cat[]" id="q_cat" multiple="multiple"  onchange="get_subcat(\'q_cat\',\'chg_scat\',1);"  size="5"><option value="">Select Category</option>';
    $client_select = db_query("SELECT cat_id,cat_name FROM {category} where parent_id='0'");
    $ecat1 = explode(",", $quest->cid);
    
    while ($list = db_fetch_object($client_select)) {
        if (in_array($list->cat_id, $ecat1)) {
            $sel = 'SELECTED="SELECTED"';
        } else {
            $sel = '';
        }
        $output .= '<option value="'.$list->cat_id.'" '.$sel.'>'.$list->cat_name.'</option>';
    
    }
    
    $output .= '</select></td>
        <td width="25%" align="left"><div id="chg_scat"><select  tabindex="15" name="q_scat[]" onchange="get_subcat(q_scat,\'chg_sscat\',2);" id="q_scat" multiple="multiple"  size="5"><option value="">Select Sub Category</option>';
    $client_select1 = db_query("SELECT cat_id,cat_name FROM {category} where parent_id IN ('".$quest->cid."')");
    $ecat2 = explode(",", $quest->scid);
    while ($list = db_fetch_object($client_select1)) {
        if (in_array($list->cat_id, $ecat2)) {
            $sel = 'SELECTED="SELECTED"';
        } else {
            $sel = '';
        }

        
        $output .= '<option value="'.$list->cat_id.'" '.$sel.'>'.$list->cat_name.'</option>';
    
    }
    $output .= '</select></div></td>
        <td width="25%" align="left"><div id="chg_sscat"><select  tabindex="16" name="q_sscat[]" onchange="get_subcat(q_sscat,\'chg_sscat\',3);" id="q_sscat" multiple="multiple"  size="5"><option value="">Select Sub Sub Category</option>';
    if ($quest->scid != '') {
        $client_select2 = db_query("SELECT cat_id,cat_name FROM {category} where parent_id IN ('".$quest->scid."')");
        $ecat3 = explode(",", $quest->sscid);
        while ($list = db_fetch_object($client_select2)) {
            if (in_array($list->cat_id, $ecat3)) {
                $sel = 'SELECTED="SELECTED"';
            } else {
                $sel = '';
            }

            
            $output .= '<option value="'.$list->cat_id.'" '.$sel.'>'.$list->cat_name.'</option>';
        
        }
    }
    $output .= '</select></div></td>
      </tr>
	  <tr><td colspan="3" height="40"  valign="middle">&nbsp;<strong>Location</strong></td></tr>
	  <tr> <td width="13%">&nbsp;<!--<input type="text" name="q_country" id="q_country" value="Country" onblur="javascript: if(this.value == \'\') this.value=\'Country\';" onfocus="javascript: if(this.value == \'Country\') this.value=\'\';" size="30" />--><select name="q_country" style="width: 125px;" tabindex="17" onchange="get_state(this.value);" id="q_country">'.$optionlist.'</select></td>
	
    <td width="13%">&nbsp;<!--<input type="text" name="q_state" id="q_state" value="State"  onblur="javascript: if(this.value == \'\') this.value=\'State\';" onfocus="javascript: if(this.value == \'State\') this.value=\'\';"   size="30"/>--> <div id="chg_state"></div></td>
	
    <td width="43%">&nbsp;<!--<input type="text" name="q_city" id="q_city" value="City" onblur="javascript: if(this.value == \'\') this.value=\'City\';" onfocus="javascript: if(this.value == \'City\') this.value=\'\';"    size="30"/>--><div id="chg_city"></div></td></tr>
	
    </table></td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
 <td width="13%" align="left" colspan="4">
       </td>
 
  </tr>
  
 
  <tr><td colspan="6">';
    
    $output .= '<tr><td colspan="6"></td></tr>';

    
    $output .= ' </td></tr>
  
  <tr>
    <td height="42">&nbsp;</td>
    <td>&nbsp;</td>
    <td><input type="submit" name="update" tabindex="21" id="save" value="Cancel" /></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td align="right"></td>
  </tr>
</table>
</form>

';
    
    return $output;

}
function question_edited_mail($qaid) {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    
     $from = variable_get('site_mail');
     $subject = 'Heardmentality Question Has Been Edited By admin ';
   $delmsg='Has been Edited By Headmentality admin';
 
        $query = db_query("select u.mail,q.question  from {question} as q left join {users} as u on u.uid=q.uid where q.qid='$qaid' ");
        $det = db_fetch_object($query);
        
      echo  $to = $det->mail;
         $msg = '<br/>Question : '.$det->question.' '.$delmsg.'<br/>';
        if(!empty($to)){
        	
			 $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
       
   
return true;
}

function question_edited_mail_voters($qaid) {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    
     $from = variable_get('site_mail');
   $subject = 'Heardmentality Question Has Been Edited By admin ';
   $delmsg='Has been Edited By Headmentality admin';
       $query = db_query("select u.question,q.uid  from possible_answer_vote as q left join question as u on u.qid=q.qid where q.qid='$qaid' ");
      
        while($det = db_fetch_object($query))
		{
        	
	$sellist="select * from users where uid='".$det->uid."'";
	$res_users=db_query($sellist);
	$usert=db_fetch_object($res_users);
	echo  $to = $usert->mail;
         $msg = '<br/>Question : '.$det->question.' '.$delmsg.'<br/>';
		 
		 
		 
        if(!empty($to)){
        	
			 $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
       
   }
return true;
}

function question_edited_mail_suggest($qaid) {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    
     $from = variable_get('site_mail');
    $subject = 'Heardmentality Question Has Been Edited By admin ';
   $delmsg='Has been Edited By Headmentality admin';

       $query = db_query("select u.question,q.uid  from suggest_answer as q left join question as u on u.qid=q.qid where q.qid='$qaid' ");
      
        while($det = db_fetch_object($query))
		{
        	
	$sellist="select * from users where uid='".$det->uid."'";
	$res_users=db_query($sellist);
	$usert=db_fetch_object($res_users);
	echo $to = $usert->mail;
         $msg = '<br/>Question : '.$det->question.' '.$delmsg.'<br/>';
		 
		 
		 
        if(!empty($to)){
        	
			 $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
       
   }
return true;
}


?>