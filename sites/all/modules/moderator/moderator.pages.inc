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
$limit = 5;                                 
$this1 = $eu + $limit; 
$back = $eu - $limit; 
$next = $eu + $limit; 

$modquest.='
	<form id="notify" method="post" action="'.$gSitePath.'admin/notifymail" ><table width="100%" border="1">
  <tr>
    <td>Question </td>
    <td>Flagged </td>
    <td>Question Author </td>
	 <td>Status</td>
    <td></td>
  </tr>';
	

	
	
		
			$sel="SELECT * FROM {question}   WHERE $qry status='1'   ";
	
	$user_qry=db_query($sel);
	
	$sel_count = db_result(db_query("SELECT COUNT(*) FROM {question}   WHERE $qry status='1'  "));
	$sel.=" limit  $eu, $limit";
	
		$sel_search=db_query($sel);
	while($user_result=db_fetch_object($sel_search))
	{
	
$modquest.='<tr>
    <td>'.$user_result->question.'</td>
    <td>'.$don->cnt.'</td>
    <td>'.$uname.' </td>
	 <td>'.$blockedst.' </td>
    <td><input type="checkbox" class="check-user" name="us_id[]" value="'.$don->nodeid.'" /> </td>
  </tr>';
  
  
	}
	
	
	
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
	$modquest.='</table>';
	


return $modquest;



}




?>