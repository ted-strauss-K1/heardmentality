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
		     drupal_set_title($oListquest->question);
      $output='<form id="answer" name="answer" method="post" action="'.$gSitePath.'qlite/save"  > <input type="hidden" name="mid" value="'.$qid.'"><div class="cmt_list">
    <div class="lft_view"> <!--<h4 class="cmt_name"><a>'.$oListquest->question.' </a></h4>-->
    <p>'.$oListquest->context.'</p>';
 $vans="select * from {possible_answer} where  qid=$qid ";
		
		
		$vlist=db_query($vans);
  
		while($vlistquest=db_fetch_object($vlist))
		{
		if($numran==0)
		{
		$output.='
		 <p><input name="answer" type="radio" value="'.$vlistquest->paid.'" />
		'.$vlistquest->answer.'</p>';
		}
		else
		{
		if($answer_id->qid==$vlistquest->qid) { $chk= "checked";}
		$output.=' <p><input name="answer_al" type="radio" '.$chk.'  value="'.$vlistquest->paid.'" />
		'.$vlistquest->answer.'</p>';
		
		}
		
		}
		
    	$output.='<script type="text/javascript">
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
		if($numran!=0)
		{ 
		
		$optio='<option value="1"> Withdraw answer</option>'; 
		}
		if($numran==0)
		{ 
		
		$submitbutt=' <p><input type="submit" name="save" id="save" value="Vote" /></p>'; 
		}
		$output.='
		  <p><select name="txt_act" id="txt_act"  onchange="formsubmittype(this.value,'.$qid.');">
		<option value=""> Select</option >
		'.$optio.'
		<option value="2"> Invite</option >
		<option value="3"> Flag</option >
		<option value="4">Suggest New Answer</option> 
		<option value="5">Create Mashup:</option> 
		</select></p>
		'.$submitbutt.' 
		
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
		
		$delQuery="delete from  user_answers where qid='".$mid."' and uid='".$user->uid."' ";
		db_query($delQuery);
		
		drupal_set_message(t('Your Answer has been  Removed successfully!'), $type = 'success');
		drupal_goto("qlite/view/$mid");
		
		
		
		}
		drupal_goto("qlite/view/$mid");
		
		return $voutput;
		
		}

	function add_resources()
	{
	global $gSitePath,$user, $gDocPath,$base_root;
	
	drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/demo.css');
	$qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
	$resources='<style type="text/css">
.mid_panel{ float:left; width:681px; overflow:hidden; border-right:1px solid #666; padding:6px 15px 27px 0; min-height:588px; height:auto!important; height:588px; }
.textfieldm {font:bold 14px Arial, Helvetica, sans-serif;; color:#5e5e5e;width:255px;   margin:0 0 10px 17px;border: 1px solid #000; display:inline; height:20px;  }
.textfield02 {font-family:Arial, Helvetica, sans-serif; font-size:12px; color:#5e5e5e; margin:10px 10px 0 0;border: 1px solid #000; width:550px; height:100px;}
.mar_top10{ margin-top:10px;}
</style>';
	$resources.='<script type="text/javascript">
	window.addEvent(\'domready\', function() {
	
	if (!window.demo_path) window.demo_path = \'\';
	var demo_path = window.demo_path;
	
	$(\'myForm\').addEvent(\'submit\', function(e) {
	
	e.stop();
	
	var log = $(\'log_res\').empty().addClass(\'ajax-loading\');
	
	this.set(\'send\', {onComplete: function(response) { 
	log.removeClass(\'ajax-loading\');
	log.set(\'html\', response);
	}});
	
	this.send();
	});
	});
	
	function showhide(selectValue){
	
	
	if(selectValue==1)
	{
	document.getElementById("div1").style.display=\'block\'
	document.getElementById("div2").style.display=\'none\'
	document.getElementById("div3").style.display=\'none\'
	}
	if(selectValue==2)
	{
	document.getElementById("div2").style.display=\'block\'
	document.getElementById("div1").style.display=\'none\'
	document.getElementById("div3").style.display=\'none\'
	}   
	if(selectValue==3)
	{
	document.getElementById("div3").style.display=\'block\'
	document.getElementById("div1").style.display=\'none\'
	document.getElementById("div2").style.display=\'none\'
	}		
	
	}
	function showhidemulti(selvalm)
	{
	//alert(selvalm);
	if(selvalm==1)
	{
	document.getElementById("media").style.display=\'block\'
	document.getElementById("media_div").style.display=\'none\'
	
	}
	if(selvalm==2)
	{
	document.getElementById("media_div").style.display=\'block\'
	document.getElementById("media").style.display=\'none\'
	
	}   
	
	}
	function validform(frm)
	{
	if(frm.rtype.value=="0")
	{
	alert("select  Type ");
	frm.mtype.focus();
	return false;
	}
	if(frm.rtype.value==1)
	{
	if(frm.nlink.value=="")
	{
	alert("Please enter News Link");
	frm.nlink.focus();
	return false;
	}
	var theurl=frm.nlink.value;
	var tomatch=/http:\/\/[A-Za-z0-9\.-]{3,}\.[A-Za-z]{3}/;
	if(theurl!="")
	{
	if (!tomatch.test(theurl))
	{
	
	alert("Please enter valid News Link ,Example:http://www.example.com");		
	frm.nlink.focus();			
	
	return false;
	}
	}
	if(frm.ntitle.value=="")
	{
	alert("Please enter News Title");
	frm.ntitle.focus();
	return false;
	}
	if(frm.ncontent.value=="")
	{
	alert("Please enter News Content");
	frm.ncontent.focus();
	return false;
	}
	if(frm.path.value=="")
	{
	alert("Please Upload Image");
	return false;
	}
	}
	if(frm.rtype.value==2)
	{
	
	if(frm.mtype.value=="0")
	{
	alert("select Media Type ");
	frm.mtype.focus();
	return false;
	}
	if(frm.mtype.value=="1")
	{
	
	if(frm.membed.value=="")
	{
	alert("Please enter Embed  Code");
	frm.membed.focus();
	return false;
	}
	
	}
	
	if(frm.mtype.value=="2")
	{
	
	if(frm.docpath.value=="")
	{
	alert("Please Upload Files ");
	return false;
	}
	
	}
	
	}
	if(frm.rtype.value==3)
	{
	if(frm.flink.value=="")
	{
	alert("Please enter Fact Link");
	frm.flink.focus();
	return false;
	}
	var theurl=frm.flink.value;
	var tomatch=/http:\/\/[A-Za-z0-9\.-]{3,}\.[A-Za-z]{3}/;
	if(theurl!="")
	{
	if (!tomatch.test(theurl))
	{
	
	alert("Please enter valid Fact Link ,Example:http://www.example.com");		
	frm.flink.focus();			
	
	return false;
	}
	}
	
	
	}
	
	return true;
	
	}
	
	</script>
	';

	$resources.='	<div id="log">
	
	<div id="log_res"><!-- spanner --></div>
	</div>
	<span class="clr"><!-- spanner --></span>';
	$resources.='<form id="myForm" name="myform"  method="post" action="'.$gSitePath.'qlite/ajaxadd" enctype="multipart/form-data"><input type="hidden" name="qaid" value="'.$qid.'"/>
	
	<p> Type <select name="rtype" class="textfieldm" id="rtype" onchange="showhide(this.value);">
	<option value="0">Select </option>
	<option value="1">News </option>
	<option value="2">Multimedia </option>
	<option value="3">Facts </option>
	</select>  
	</p>
	<div id="div1" style="display:none;">
	<p> Link <input type="text" class="textfieldm"  name="nlink" id="nlink"/> </p>
	
	<p> Title <input type="text" class="textfieldm" name="ntitle" id="ntitle"/></p>
	<p> Content <textarea name="ncontent" class="textfield02" id="ncontent" ></textarea> </p>
	<p>Image  <input type="hidden" name="path" id="path"/><iframe src="'.$gSitePath.'uploader.php" width="62" height="26"  scrolling="no"></iframe></p>
	</div>
	
	<div  id="div2" style="display:none;">
	<p> Type <select name="mtype" class="textfieldm" id="mtype"  onchange="showhidemulti(this.value);" >
	<option value="0">Select </option>
	<option value="1">Web Video </option>
	<option value="2">Podcast,PDF, DOC, PPT. </option>
	</select> </p>
	<div  id="media" style="display:none;"> 
	<p> Embed Url <textarea name="membed" id="membed"  class="textfield02" ></textarea> </p> 
	</div>
	<div  id="media_div" style="display:none;">
	<p> File <input type="hidden" name="docpath" id="docpath"/><iframe src="'.$gSitePath.'upload_document.php" width="62" height="26"  scrolling="no"></iframe></p> 
	</div>
	
	</div>
	
	<div  id="div3" style="display:none;">
	<p> Link <input type="text" name="flink" id="flink" class="textfieldm"/> </p>
	</div>
	<input type="submit" name="button" id="submitter"  value="Add Resource" onclick="return validform(this.form);" />
	</form>';			
	echo $resources;
	}
	function save_resources(){
	
	global $gSitePath,$user, $gDocPath,$base_root;
	$resourceadd="insert into resource(rtype,nlink,ntitle,ncontent,mtype,membed,facts,posted_date,uid,qid,nimage,document) values ('".$_REQUEST['rtype']."','".addslashes($_REQUEST['nlink'])."','".addslashes($_REQUEST['ntitle'])."','".addslashes($_REQUEST['ncontent'])."','".$_REQUEST['mtype']."','".addslashes($_REQUEST['membed'])."','".addslashes($_REQUEST['flink'])."','".date('Y-m-d')."', '".$user->uid."','".$_REQUEST['qaid']."','".$_REQUEST['path']."','".$_REQUEST['docpath']."')";
	db_query($resourceadd);
	echo '<div class="messages success"> Resources Added Suceesfully </div>';
	
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
	
	function formreport(flagfrm)
	{
	if((flagfrm.abuse_type[0].checked==false)&&
	(flagfrm.abuse_type[1].checked==false)&&
	(flagfrm.abuse_type[2].checked==false)&&
	(flagfrm.abuse_type[3].checked==false))
	{
	alert(" Select Report Type ");
	return false;
	}
	return true;
	}
	</script>
	';
	$qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
	$vSql="select * from {question} where status='1' and qid=$qid ";
	$rlist=db_query($vSql);
	$oListquest=db_fetch_object($rlist);
	$falgq.='	<div id="log">
	
	<div id="log_res"><!-- spanner --></div>
	</div>
	<span class="clr"><!-- spanner --></span>';
	$falgq.='<form id="flagform"  method="post" action="'.$gSitePath.'qlite/flagreport" enctype="multipart/form-data"><input type="hidden" name="qaid" value="'.$qid.'">
	<div id="form_box"><table width="100%" border="0">
	<tr>
	<td height="53" colspan="2">'.$oListquest->question.'</td>

	</tr>
	<tr>
	<td height="39" colspan="2">'.$oListquest->context.'</td>
	</tr>
	<tr>
	<td width="44%" height="39"><label>
	<input type="radio" name="abuse_type" id="abuse_type" value="Pornography or obscenity" />
	Pornography or obscenity</label></td>
	<td width="56%"><input type="radio" name="abuse_type" id="abuse_type" value="radically or ethnically hateful content" />
	radically or ethnically hateful content</td>
	</tr>
	<tr>
	<td height="44"><input type="radio" name="abuse_type" id="abuse_type" value="Graphic Violence" />
	Graphic Violence</td>
	<td><input type="radio" name="abuse_type" id="abuse_type" value="other content inappropirate for young Viewers" />
	other content inappropirate for young Viewers</td>
	</tr>
	<tr>
	<td height="72">&nbsp;</td>
	<td><label>
	<input type="submit" name="button" id="submitter"  value="Report Problem" onclick="return formreport(this.form);"/>
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
	"url":       "'.$gSitePath.'qlite/panel/'.$qid.'?type=Resources"
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
	drupal_add_js(drupal_get_path('module', 'quest_lite').'/scripts/mootools.js');
	drupal_add_js(drupal_get_path('module', 'quest_lite').'/scripts/history.js');
	drupal_add_js(drupal_get_path('module', 'quest_lite').'/scripts/pageLoader.js');
	$qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);

	$type=$_REQUEST['type'];
	switch($type)
	{
	case "Forum":
	$output='sample content Forum';
	break;
	case "Resources":
	$vSql="SELECT *	FROM resource	where rtype='1'  ";
	$rlistnews=mysql_query($vSql);

	
	$output=' <div class="proj_menu">
						<ul>
							<li><a>In the News |</a></li>
							  <li ><a>Multimedia |</a></li>
							<li ><a >Facts |</a> </li>
							<li ><a onclick="loadresource(\''.$gSitePath.'qlite/resource/'.$qid.'\',\'Add\')" class="returnFalse arrow-right" id="addresource">Add Resource </a></li>
						</ul>
					</div>';
		
					while($usernews=mysql_fetch_object($rlistnews))
					{
	$output.='<div class="cmt_list">
	 <a class="cmt_pic"> <img src="'.$gSitePath.''.$usernews->nimage.'" width="60" height="80"/></a>
    <div class="lft_view"> <h4 class="cmt_name"><a href="'.$usernews->nlink.'" target="new"> '.$usernews->nlink.' </a> </h4>
    <p>'.$usernews->ntitle.' </p>  
	 <p>'.$usernews->ncontent.' </p>  
    <p class="cmt_date"> '.format_date($usernews->posted_date, "custom", "D j M Y"). '</p> </div>
    </div>';
	}
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
		
	
	
	function flag_report()
	{
	global $gSitePath,$user, $gDocPath,$base_root;


	$list_length = db_query("select * from {question_flags} where nodeid='".$_REQUEST['qaid']."' and uid='".$user->uid."' and  type='question' ");
		 $numr=mysql_num_rows($list_length);
		
		 if($numr==0)
		 {
		 $flagquery="insert into question_flags(nodeid,uid,flag_date,type,abuse_type) values ('".$_REQUEST['qaid']."','".$user->uid."','".date('Y-m-d')."','question','".$_REQUEST['abuse_type']."')";
		 	db_query($flagquery);
		echo '<div class="messages success">You Have Flagged successfully ! </div>';
		
		 }
		  else
		  {
		  	
	
		
		echo '<div class="messages success">You Have Already Flagged !</div>';
	  
		  
		  }
	
	}	
	
	function suggest_answer()
	{
	
	global $gSitePath,$user, $gDocPath,$base_root;
	$ansoutput='<style>
	.cmt_list{ border:0px solid red; overflow:hidden; margin-bottom:10px;}
	.cmt_list a.cmt_pic{ display:block; float:left; width:100px; height:100px; text-align:center;}
	.cmt_list a.cmt_pic img{ margin:0 auto; padding-top:0px; vertical-align:middle; display:block;width:50px;}
	h4.cmt_name{ margin-top:10px; font:bold 12px Arial, Helvetica, sans-serif; color:#000;}
	h4.cmt_name a{ font: normal 14px Arial, Helvetica, sans-serif; color:#02a33c; text-decoration:none;}
	p.cmt_date{ font:normal 12px Arial, Helvetica, sans-serif; color:#696E6B;}
	span.draft{ display:block; width:160px; background:#BD0000;font:bold 12px Arial, Helvetica, sans-serif; color:#fff; padding:2px 0 2px 2px;}
	.lft_view{ float:left; text-align:justify; width:550px;}
	.txt_area textarea{width:498px; height:66px; border:3px solid #000; margin:32px 0 0 72px; padding:10px;}
	
	.comment_but{ margin:0 auto; text-align:center; padding:15px 0;}
	</style>';
	
	$qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
	$resources='<script type="text/javascript">
	window.addEvent(\'domready\', function() {
	
	if (!window.demo_path) window.demo_path = \'\';
	var demo_path = window.demo_path;
	
	$(\'answerform\').addEvent(\'submit\', function(e) {
	
	e.stop();
	
	var log = $(\'log_res\').empty().addClass(\'ajax-loading\');
	
	this.set(\'send\', {onComplete: function(response) { 
	log.removeClass(\'ajax-loading\');
	log.set(\'html\', response);
	}});
	
	this.send();
	});
	});

	function validanswer(frmansw)
	{
	
	if(frm.ncontent.value=="")
	{
	alert("Please enter News Content");
	frm.ncontent.focus();
	return false;
	}

	
	return true;
	
	}
	
	</script>
	';
	$ansoutput.='<form id="answerform"  method="post"  enctype="multipart/form-data"><input type="hidden" name="qaid" value="'.$qid.'"><div class="cmt_list">
    <div class="lft_view"> <h4 class="cmt_name"><a href="">Demo </a>Says:</h4>
    <p>ssssssssssssss</p>  
    <p class="cmt_date">   2010/09/09</p> </div>
    </div>
	
	<div class="txt_area">    <p style="color:#FF0000" align="center"><b><?=$msg;?></b><span style="color:#FF0000"  id="sad"></span> </p>
	Suggest Answer <input type="text" class="textfieldm"  name="txt_answer" id="txt_answer" ><br />
	
    <div class="comment_but"><input type="submit" name="comment" value="Submit" /></div>
    </div></div>
    </div></form>';
	echo $ansoutput;
	}	
    function suggest_answer_save()
	{
	
	echo 'jjjjjj';
	
	}
	
?>
