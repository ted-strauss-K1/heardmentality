<?php

function qlite_view()
{
	global $gSitePath,$user, $gDocPath,$base_root,$base_path;
	

drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/main.css');
drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/page.css');
			drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/tabs.css');
 

 $qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
	$vSql="select * from {question} where status='1' and qid=$qid ";
		$rlist=db_query($vSql);
		$oListquest=db_fetch_object($rlist);
		
		$vuser="select * from {users} where  uid=$oListquest->uid ";
		$username=db_query($vuser);
		$ufet=db_fetch_object($username);
		
$list_lengthan = db_query("select * from {user_answers} where qid='".$qid."' and uid='".$user->uid."' ");
		 $numran=mysql_num_rows($list_lengthan);
		$answer_id=db_fetch_object($list_lengthan);
			$output='<form id="answer" name="answer" method="post" action="'.$gSitePath.'qlite/save"  >
 <div> <table width="100%" border="0" align="center" ><input type="hidden" name="mid" value="'.$qid.'">
  <tr  width="100%">
		<td width="30%" align="left" valign="top">'.$oListquest->question.'</td>
		<td > &nbsp;</td>
	</tr>
	<tr>
		<td align="left" valign="top">&nbsp; '.$oListquest->context.'</td>
		<td > </td>
	</tr>

	<tr>
		<td align="right"></td>
		
		<td>		</td>
	</tr>';
		
			$vans="select * from {possible_answer} where  qid=$qid ";
		
		
		$vlist=db_query($vans);
		while($vlistquest=db_fetch_object($vlist))
		{
		if($numran==0)
		{
			$output.='
			<tr>
			  <td align="left"><input name="answer" type="radio" value="'.$vlistquest->paid.'" />
'.$vlistquest->answer.'</td>
			  <td></td>
  </tr>';
	}
	else
	{
	if($answer_id->qid==$vlistquest->qid) { $chk= "checked";}
$output.='
			<tr>
			  <td align="left"><input name="answer_al" type="radio" '.$chk.'  value="'.$vlistquest->paid.'" />
'.$vlistquest->answer.'</td>
			  <td></td>
  </tr>';
	
	}
		
		}
		
		$output.='
  <tr>
    <td align="right">&nbsp; </td>
    <td>
      
    </td>
  </tr>';
  $output.='<script type="text/javascript">
function formsubmittype(mtype,ids){

if(mtype==1)
{
 document.forms["answer"].submit();
 
 }
if(mtype==3)
{
 loadflagquestion(\''.$gSitePath.'qlite/flag/\'+ids,\'Add \');
 
 }
  	
  }
</script>
';
	if($numran!=0)
	{ 
	
	$optio='<option value="1"> Withdraw answer</option>'; 
	}
  if($numran==0)
	{ 
	
		$submitbutt='<input type="submit" name="save" id="save" value="Vote" />'; 
	}
	$output.='
  <tr>
    <td align="left" valign="top"> <select name="txt_act" id="txt_act"  onchange="formsubmittype(this.value,'.$qid.');">
	  <option value=""> Select</option >
    '.$optio.'
       <option value="2"> Invite</option >
      <option value="3"> Flag</option >
       <option value="4">Suggest New Answer</option> 
      <option value="5">Create Mashup:</option> 
      </select></td>
    <td>
     
    </td>
  </tr>
  <tr>
			  <td align="left"> '.$submitbutt.'</td>
			  <td>
			  
			 </td></tr>
 </table></div>
</form>';
		

    return $output;
}

function qlite_save()
{

		global $gSitePath,$user, $gDocPath,$base_root;
$mid=$_REQUEST['mid'];

	$voutput='';
		$vquest="select * from {possible_answer} where paid='".$_REQUEST['answer']."'  ";
		$rquest=db_query($vquest);
		$olistquest=db_fetch_object($rquest);
		
		 if(($_REQUEST['answer']!=''))
		 {
		$list_length = db_query("select * from {user_answers} where qid='".$mid."' and uid='".$user->uid."' ");
		$numr=mysql_num_rows($list_length);
		echo $numr;
		if($numr==0)
		{
		$vInsQuery="insert into user_answers(qid, ans_id,uid,answered_date) values ('".$mid."', '".$_REQUEST['answer']."','".$user->uid."','".date('Y-m-d h:i:s')."')";
		db_query($vInsQuery);
		
		drupal_set_message(t('Thank you,Your Answer has been saved successfully!'), $type = 'success');
		drupal_goto("qlite/view/$mid");
		}
		else
		{
		drupal_set_message($message = 'You Have already answered This Question!', $type = 'error');
		drupal_goto("qlite/view/$mid");
		
		}
		
		}
		
		
		 
		 if($_REQUEST['txt_act']==1)
		 {
		  $list_length = db_query("select * from {user_answers} where qid='".$mid."' and uid='".$user->uid."' ");
		 $numr=mysql_num_rows($list_length);
		 echo $numr;
		 if($numr==0)
		 {
		 
		 drupal_set_message($message = 'You Have Not Posted Answer !', $type = 'error');
		 drupal_goto("qlite/view/$mid");
		 }
		  else
		  {
		  $delQuery="delete from  user_answers where qid='".$mid."' and uid='".$user->uid."' ";
		db_query($delQuery);
		
		 drupal_set_message(t('Your Answer has beed  Removed successfully!'), $type = 'success');
	    drupal_goto("qlite/view/$mid");
		  
		  }
		  
		  }
		/*  if($_REQUEST['txt_act']==3)
		 {
		  $list_length = db_query("select * from {question_flags} where nodeid='".$mid."' and uid='".$user->uid."' and  type='question' ");
		 $numr=mysql_num_rows($list_length);
		 echo $numr;
		 if($numr==0)
		 {
		 $flagquery="insert into question_flags(nodeid,uid,flag_date,type) values ('".$mid."','".$user->uid."','".date('Y-m-d')."','question')";
		 	db_query($flagquery);
		 drupal_set_message($message = 'You Have Flagged successfully !', $type = 'success');
		 drupal_goto("qlite/view/$mid");
		 }
		  else
		  {
		  	
	
		
		 drupal_set_message(t('You Have Already Flagged !'), $type = 'error');
	    drupal_goto("qlite/view/$mid");
		  
		  }
		  
		  }*/
		
	   return $voutput;

}





	function add_resources()
		{
			global $gSitePath,$user, $gDocPath,$base_root;
	drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/demo.css');
	
$qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);



	
			echo "kkkkk";
	
		}


function save_resources(){
		//print_r($_REQUEST);
		global $gSitePath,$user, $gDocPath,$base_root;
		
		
		
	
		 $resourceadd="insert into resource(rtype,nlink,ntitle,ncontent,mtype,membed,facts,posted_date,uid,qid,nimage,document) values ('".$_REQUEST['rtype']."','".$_REQUEST['nlink']."','".$_REQUEST['ntitle']."','".$_REQUEST['ncontent']."','".$_REQUEST['mtype']."','".$_REQUEST['membed']."','".$_REQUEST['flink']."','".date('Y-m-d')."', '".$user->uid."','".$_REQUEST['qaid']."','".$_REQUEST['path']."','".$_REQUEST['docpath']."')";
		db_query($resourceadd);
		echo "Resources Added Suceesfully ";
	
		}
		
		
		
	function flag_question()
	{
	global $gSitePath,$user, $gDocPath,$base_root;
	 $falgq='<script type="text/javascript">
window.addEvent(\'domready\', function() {

	if (!window.demo_path) window.demo_path = \'\';
	var demo_path = window.demo_path;
	
	$(\'flagform\').addEvent(\'submit\', function(e) {
		
		e.stop();
		
		var log = $(\'log_res\').empty().addClass(\'ajax-loading\');
		
		this.set(\'send\', {onComplete: function(response) { 
			log.removeClass(\'ajax-loading\');
			log.set(\'html\', response);
		}});
		
		this.send();
	});
});



</script>
';
	$qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
	$vSql="select * from {question} where status='1' and qid=$qid ";
		$rlist=db_query($vSql);
		$oListquest=db_fetch_object($rlist);
	echo $qid;
	 $falgq.='	<div id="log">
		
		<div id="log_res"><!-- spanner --></div>
	</div>
	<span class="clr"><!-- spanner --></span>';
	$falgq.='<form id="flagform"  method="post" action="'.$gSitePath.'qlite/flagreport" enctype="multipart/form-data"><input type="hidden" name="qaid" value="'.$qid.'">
		<div id="form_box"><table width="100%" border="1">
  <tr>
    <td height="53" colspan="2">'.$oListquest->question.'</td>
  </tr>
  <tr>
    <td height="39" colspan="2">'.$oListquest->context.'</td>
  </tr>
  <tr>
    <td width="44%" height="39"><label>
      <input type="radio" name="radio" id="radio" value="radio" />
    Pornography or obscenity</label></td>
    <td width="56%"><input type="radio" name="radio" id="radio2" value="radio" />
      radically or ethnically hateful content</td>
  </tr>
  <tr>
    <td height="44"><input type="radio" name="radio" id="radio3" value="radio" />
Graphic Violence</td>
    <td><input type="radio" name="radio" id="radio4" value="radio" />
other content inappropirate for young Viewers</td>
  </tr>
  <tr>
    <td height="72">&nbsp;</td>
    <td><label>
     <input type="submit" name="button" id="submitter"  value="Report Problem"/>
    </label></td>
  </tr>
</table></form>';

echo $falgq;
	
	}	
		
		
	function tab_list()
	{
		global $gSitePath,$user, $gDocPath,$base_root;
	
	
$qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);

	echo '<div class="toolbarTabs">
	<ul id="panelTabs" class="tab-menu">
		<li id="panelTabs1Link" class="selected"><a>Reporting</a></li>
		<li id="panelTabs2Link"><a>Forum</a></li>
		<li id="panelTabs3Link" ><a>Resources</a></li>
		<li id="panelTabs4Link"><a>Gurus</a></li>
		<li id="panelTabs5Link"><a>Info</a></li>
		<li id="panelTabs6Link"><a>Politician</a></li>
	</ul>
	<div class="clear"></div>
</div>

<script type="text/javascript">

	MochaUI.initializeTabs("panelTabs");

	$("panelTabs1Link").addEvent("click", function(e){
		MochaUI.updateContent({
			"element":  $("help-panel"),
			"url":       "'.$gSitePath.'qlite/panel"
		});
	});

	$("panelTabs2Link").addEvent("click", function(e){
		MochaUI.updateContent({
			"element":  $("help-panel"),
			"url":       "'.$gSitePath.'qlite/panel?type=Forum"
		});
	});
	
	$("panelTabs3Link").addEvent("click", function(e){
		MochaUI.updateContent({
			"element":  $("help-panel"),
			"url":       "'.$gSitePath.'qlite/panel?type=Resources&qid='.$qid.'"
		});
	});
$("panelTabs4Link").addEvent("click", function(e){
		MochaUI.updateContent({
			"element":  $("help-panel"),
			"url":       "'.$gSitePath.'qlite/panel?type=Gurus"
		});
	});
	
	$("panelTabs5Link").addEvent("click", function(e){
		MochaUI.updateContent({
			"element":  $("help-panel"),
			"url":       "'.$gSitePath.'qlite/panel?type=Info"
		});
	});
	
	$("panelTabs6Link").addEvent("click", function(e){
		MochaUI.updateContent({
			"element":  $("help-panel"),
			"url":       "'.$gSitePath.'qlite/panel?type=Politician"
		});
	});
	

</script>';
	
	}	
		
		
	function panel_content()
	{
	global $gSitePath,$user, $gDocPath,$base_root;

$qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);

	$type=$_REQUEST['type'];
	switch($type)
	{
	case "Forum":
	$output='sample content Forum';
	break;
	case "Resources":
	$vSql="SELECT *
FROM node_revisions as a JOIN node as b
ON a.nid = b.nid and 
b.type='news_page' and b.status='1'  ";
$rlistnews=mysql_query($vSql);
$output='<script type="text/javascript">
		
		window.addEvent("domready", function() {
			
			
			Element.implement({
			
				fancyShow: function() {
					this.fade("in");
				},
			
				fancyHide: function() {
					this.fade("out");
				}
			});
			
		});
	</script>';
	$output.=' <p> <input type="button" name="resource" value="Add Resources" onclick="loadresource(\''.$gSitePath.'qlite/resource/'.$qid.'\',\'Add \')" class="returnFalse arrow-right" id="mootoolsLink"></p>';
	
	break;
	case "Gurus":
	$output='sample content Gurus';
	break;
	case "Info":
	$output=' <h1> Question Information </h1><p class="con"> <b>Question Author: </b> '.$ufet->name.' <br>
			<b>Date Created:</b> '.format_date($oListquest->date_added, "custom", "D j M Y"). ' <br>
			<b>Number of Votes:</b> 0<br>
			<b>Number of Forum Posts:</b> 0 <br>
			<b>Number of Resources:</b> 0</p>
		';
	break;
	case "Politician":
	$output='sample content Politician';
	break;

	case "news":
	$output='sample content news';
	break;
	case "multimedia":
	$output='sample content multimedia';
	break;
	case "facts":
	$output='sample content facts';
	break;
	default:
	$output='sample content first';
	break;
	}
	echo $output;
	}
		
	function flag_save()
	{
	  $list_length = db_query("select * from {question_flags} where nodeid='".$mid."' and uid='".$user->uid."' and  type='question' ");
		 $numr=mysql_num_rows($list_length);
		 echo $numr;
		 if($numr==0)
		 {
		 $flagquery="insert into question_flags(nodeid,uid,flag_date,type) values ('".$_REQUEST['qaid']."','".$user->uid."','".date('Y-m-d')."','question')";
		 	db_query($flagquery);
		 drupal_set_message($message = 'You Have Flagged successfully !', $type = 'success');
		 drupal_goto("qlite/view/$mid");
		 }
		  else
		  {
		  	
	
		
		 drupal_set_message(t('You Have Already Flagged !'), $type = 'error');
	    drupal_goto("qlite/view/$mid");
		  
		  }
	
	
	}	
		

?>
