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
      $voutput='<form id="answer" name="answer" method="post" action="'.$gSitePath.'qlite/save"  > <input type="hidden" name="mid" value="'.$qid.'"><div class="cmt_list">
    <div class="lft_view"> <!--<h4 class="cmt_name"><a>'.$oListquest->question.' </a></h4>-->
    <p>'.$oListquest->context.'</p>';
 $vans="select * from {possible_answer} where  qid=$qid ";
		
		
		$vlist=db_query($vans);
  
		while($vlistquest=db_fetch_object($vlist))
		{
		if($numran==0)
		{
		$voutput.='
		 <p><input name="answer" type="radio" value="'.$vlistquest->paid.'" />
		'.$vlistquest->answer.'</p>';
		}
		else
		{
		if($answer_id->qid==$vlistquest->qid) { $chk= "checked";}
		$voutput.=' <p><input name="answer_al" type="radio" '.$chk.'  value="'.$vlistquest->paid.'" />
		'.$vlistquest->answer.'</p>';
		
		}
		
		}
		
    	$voutput.='<script type="text/javascript">
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
		$voutput.='
		  <p><select name="txt_act" id="txt_act"  onchange="formsubmittype(this.value,'.$qid.');">
		<option value=""> Select</option >
		'.$optio.'
		<option value="2"> Invite</option >
		<option value="3"> Flag</option >
		<option value="4">Suggest New Answer</option> 
		<option value="5">Create Mashup:</option> 
		</select></p>
		'.$submitbutt.' 
		
		</div></div></form>';
		
		
		return $voutput;
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
	
	
	$qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
	$resources='<link rel="stylesheet" href="'.$gSitePath.'sites/all/modules/quest_lite/css/answer.css" type="text/css" />';
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

	$resources.='<div id="log">
	
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
	<div id="div1" >
	<p> Link <input type="text" class="textfieldm"  name="nlink" id="nlink"/> </p>
	
	<p> Title <input type="text" class="textfieldm" name="ntitle" id="ntitle"/></p>
	<p> Content <textarea name="ncontent" class="textfield02" id="ncontent" ></textarea> </p>
	<p>Image  <input type="hidden" name="path" id="path"/><iframe src="'.$gSitePath.'uploader.php" width="62" height="26"  scrolling="no"></iframe></p>
	</div>
	
	<div  id="div2" >
	<p> Type <select name="mtype" class="textfieldm" id="mtype"  onchange="showhidemulti(this.value);" >
	<option value="0">Select </option>
	<option value="1">Web Video </option>
	<option value="2">Podcast,PDF, DOC, PPT. </option>
	</select> </p>
	<div  id="media" > 
	<p> Embed Url <textarea name="membed" id="membed"  class="textfield02" ></textarea> </p> 
	</div>
	<div  id="media_div" >
	<p> File <input type="hidden" name="docpath" id="docpath"/><iframe src="'.$gSitePath.'upload_document.php" width="62" height="26"  scrolling="no"></iframe></p> 
	</div>
	
	</div>
	
	<div  id="div3" >
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
	echo '<div class="messages success"> Resources Added Successfull </div>';
	
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
	$falgq.='<div id="log">
	
	<div id="log_res"><!-- spanner --></div>
	</div>
	<span class="clr"><!-- spanner --></span>';
$falgq.='<form id="flagform"  method="post" action="'.$gSitePath.'qlite/flagreport" enctype="multipart/form-data"><input type="hidden" name="qaid" value="'.$qid.'"/>
	<div class="cmt_list"><div class="lft_view">  <p>'.$oListquest->question.' </p>
 <p class="cmt_date">  '.$oListquest->context.' </p></div></div>
<div class="txt_area">
	<input type="radio" name="abuse_type" id="abuse_type" value="Pornography or obscenity" />
	Pornography or obscenity <br/><input type="radio" name="abuse_type" id="abuse_type" value="radically or ethnically hateful content" />
	radically or ethnically hateful content  <br/> <input type="radio" name="abuse_type" id="abuse_type" value="Graphic Violence" />
	Graphic Violence <br/><input type="radio" name="abuse_type" id="abuse_type" value="other content inappropirate for young Viewers" />
	other content inappropirate for young Viewers <br/><input type="submit" name="button" id="submitter"  value="Report Problem" onclick="return formreport(this.form);"/></div></form>';
	
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
	"url":       "'.$gSitePath.'qlite/panel/'.$qid.'"
	});
	});
	
	$("panelTabs2Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("help-panel"),
	"url":       "'.$gSitePath.'qlite/panel/'.$qid.'?type=Forum"
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
	"url":       "'.$gSitePath.'qlite/panel/'.$qid.'?type=Gurus"
	});
	});
	
	$("panelTabs5Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("help-panel"),
	"url":       "'.$gSitePath.'qlite/panel/'.$qid.'?type=Info"
	});
	});
	
	$("panelTabs6Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("help-panel"),
	"url":       "'.$gSitePath.'qlite/panel/'.$qid.'?type=Politician"
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
	
	$output='<link rel="stylesheet" href="'.$gSitePath.'sites/all/modules/quest_lite/css/subtab.css" type="text/css" />
                       <ul id="tabmenu" >
                                       <li><a class="" href="javascript:tabactive(1,\''.$gSitePath.'\',\''.$qid.'\')" id="tab1">In the News</a></li>
                                       <li><a class="" href="javascript:tabactive(2,\''.$gSitePath.'\',\''.$qid.'\')" id="tab2">Multimedia</a></li>
                                       <li><a class="" href="javascript:tabactive(3,\''.$gSitePath.'\',\''.$qid.'\')" id="tab3">Facts</a></li>
                                       <li><a class="" href="javascript:loadresource(\''.$gSitePath.'qlite/resource/'.$qid.'\',\'Add\')" id="tab4">Add Resource</a></li>
                               </ul>
                               <div id="contents"></div>
                               <script type="text/javascript">tabactive(1,\''.$gSitePath.'\',\''.$qid.'\')</script>';
				
	break;
	case "Gurus":
	$output='sample content Gurus';
	break;
	case "Info":
	$output=' <h1> Question Information </h1><p class="con"> <b>Question Author: </b> '.$ufet->name.' <br/>
			<b>Date Created:</b> '.format_date($oListquest->date_added, "custom", "D j M Y"). ' <br/>
			<b>Number of Votes:</b> 0<br/>
			<b>Number of Forum Posts:</b> 0 <br/>
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
            $output = '<link rel="stylesheet" href="'.$gSitePath.'sites/all/modules/quest_lite/css/subtab.css" type="text/css" />
			<ul id="tabmenu" >
				<li ><a href="javascript:loadReport(1,\''.$gSitePath.'\','.$qid.');" class="" id="tab1">Percentage</a></li>
				<li ><a href="javascript:loadReport(2,\''.$gSitePath.'\','.$qid.');" class="" id="tab2">Overtime</a></li>
				<li ><a href="javascript:loadReport(3,\''.$gSitePath.'\','.$qid.');" class="" id="tab3">By Area</a></li>
			</ul>
			<div id="contents"><iframe id="frmGoogle" src="" border="0" height="450" frameborder="0" width="100%"></iframe></div>
			<script type="text/javascript">loadReport(1,\''.$gSitePath.'\','.$qid.')</script>';
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
		echo '<div class="messages error">You Have Already Flagged !</div>';
		  }
	
	}	
	
	function suggest_answer()
	{
	
	global $gSitePath,$user, $gDocPath,$base_root;

	$qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
		$ansoutput='<link rel="stylesheet" href="'.$gSitePath.'sites/all/modules/quest_lite/css/answer.css" type="text/css" />';

	$answers="SELECT *	FROM suggest_answer where qid='$qid'  ";
	$anslist=mysql_query($answers);
	$list_length = db_query("select * from {suggest_answer} where qid='$qid' and uid='".$user->uid."'  ");
    $numr=mysql_num_rows($list_length);
	$ansoutput.='<div id="log">
	<div id="log_res"><!-- spanner --></div>
	</div>
	<span class="clr"><!-- spanner --></span>';
	
	$ansoutput.='<div id="log_res_ans"><!-- spanner --></div>
	<span class="clr"><!-- spanner --></span>';
	
	$ansoutput.='<script type="text/javascript">
	window.addEvent(\'domready\', function() {
	
	if (!window.demo_path) window.demo_path = \'\';
	var demo_path = window.demo_path;
	
	$(\'voteform\').addEvent(\'submit\', function(e) {
	
	e.stop();
	
	var log = $(\'log_res_ans\').empty().addClass(\'ajax-loadings\');
	
	this.set(\'send\', {onComplete: function(response) { 
	log.removeClass(\'ajax-loadings\');
	log.set(\'html\', response);
	}});
	
	this.send();
	});
	});
	
	
	</script>
	<form id="voteform"  method="post" action="'.$gSitePath.'qlite/answervote"  enctype="multipart/form-data">
	<input type="hidden" name="qaid" value="'.$qid.'"/>
	Select Answer <select name="suggest" class="textfieldm" id="suggest">';
	while($answerfet=mysql_fetch_object($anslist))
	{
	$ansoutput.='<option  value="'.$answerfet->said.'">'.$answerfet->answer.' </option>';

	}
	$ansoutput.='</select> <input type="submit" name="buttonvote" id="voteid"  value="Vote "/></form> ';	
	
		
	if($numr==0)
	{
	$ansoutput.='<script type="text/javascript">
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
	</script>	<form id="answerform"  method="post" action="'.$gSitePath.'qlite/answersubmit"  enctype="multipart/form-data"><input type="hidden" name="qaid" value="'.$qid.'"/>
	
	<div class="txt_area">	Suggest Answer <input type="text" class="textfieldm"  name="txt_answer" id="txt_answer"/><br />
	<div class="comment_but"><input type="submit" name="button" id="submitter"  value="Suggest Answer"/></div>
	</div></form>';
	}
	
	echo $ansoutput;
	}	
    function suggest_answer_save()
	{
	global $gSitePath,$user, $gDocPath,$base_root;
	$list_length = db_query("select * from {suggest_answer} where qid='".$_REQUEST['qaid']."' and uid='".$user->uid."'  ");
		 $numr=mysql_num_rows($list_length);
		
		 if($numr==0)
		 {
	 $answerquery="insert into suggest_answer(qid,uid,answer,date_added) values ('".$_REQUEST['qaid']."','".$user->uid."','".$_REQUEST['txt_answer']."','".date('Y-m-d')."')";
		 	db_query($answerquery);
		echo '<div class="messages success">Your Answer Posted Successfully ! </div>';
		}
		/*else
		{
		echo '<div class="messages error">Already ! </div>';
		
		}*/
	
	}
	function question_news()
	{
	global $gSitePath,$user, $gDocPath,$base_root;
	$qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
	$vSql="SELECT *	FROM resource where rtype='1' and qid='$qid' ";
	$rlistnews=mysql_query($vSql);
	$numnews=mysql_num_rows($rlistnews);
	$newsresult='<link rel="stylesheet" href="'.$gSitePath.'sites/all/modules/quest_lite/css/answer.css" type="text/css" />';
	while($usernews=mysql_fetch_object($rlistnews))
	{
	$newsresult.='<div class="cmt_list">
	<a class="cmt_pic"> <img src="'.$gSitePath.''.$usernews->nimage.'" width="60" height="80"/></a>
	<div class="lft_view"> <h4 class="cmt_name"><a style="font: normal 14px Arial, Helvetica, sans-serif; color:#02a33c; text-decoration:none;"; href="'.$usernews->nlink.'" target="new"> '.$usernews->nlink.' </a> </h4>
	<p>'.$usernews->ntitle.' </p>  
	<p>'.$usernews->ncontent.' </p>  
	<p class="cmt_date"> '.format_date($usernews->posted_date, "custom", "D j M Y"). '</p> </div>
	</div>';
	}
	
	if($numnews==0)
	{
	
	$newsresult.='No News  Under This Question.';
	
	}
	echo $newsresult;
	
	
	}
	
	function question_media()
	{
	
	global $gSitePath,$user, $gDocPath,$base_root;
	$qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
	$vSqlmedia="SELECT *	FROM resource where rtype='2' and qid='$qid' ";
	$rlistmedia=mysql_query($vSqlmedia);
	$nummedia=mysql_num_rows($vSqlmedia);
	$mediaresult='<link rel="stylesheet" href="'.$gSitePath.'sites/all/modules/quest_lite/css/answer.css" type="text/css" />';
	while($usermedia=mysql_fetch_object($rlistmedia))
	{
	$mediaresult.='<div class="cmt_list">
	<div class="lft_view"> <h4 class="cmt_name"><a style="font: normal 14px Arial, Helvetica, sans-serif; color:#02a33c; text-decoration:none;"; href="'.$gSitePath.''.$usermedia->document.'" target="new"> '.$usermedia->document.' </a> </h4>
	<p>'.$usermedia->membed.' </p>  
	<p class="cmt_date"> '.format_date($usermedia->posted_date, "custom", "D j M Y"). '</p> </div>
	</div>';
	}
	if($nummedia==0)
	{
	
	$mediaresult.='No Media Under This Question.';
	
	}
	echo $mediaresult;
	
	}
	
	function question_facts()
	{
	
global $gSitePath,$user, $gDocPath,$base_root;
	$qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
	$vSqlfact="SELECT *	FROM resource where rtype='3' and qid='$qid' ";
	$rlistfacts=mysql_query($vSqlfact);
	$numfacts=mysql_num_rows($rlistfacts);
	$newsresult='<link rel="stylesheet" href="'.$gSitePath.'sites/all/modules/quest_lite/css/answer.css" type="text/css" />';
	while($userfacts=mysql_fetch_object($rlistfacts))
	{
	$newsresult.='<div class="cmt_list">
	<div class="lft_view"> <h4 class="cmt_name"><a style="font: normal 14px Arial, Helvetica, sans-serif; color:#02a33c; text-decoration:none;";href="'.$userfacts->facts.'" target="new"> '.$userfacts->facts.' </a> </h4>
	<p class="cmt_date"> '.format_date($userfacts->posted_date, "custom", "D j M Y"). '</p> </div>
	</div>';
	}
	if($numfacts==0)
	{
	
	$newsresult.='No Facts Under This Question.';
	
	}
	echo $newsresult;
	
	}
	
	

function qlite_percent()
{
		global $gSitePath,$user, $gDocPath,$base_root,$base_path;
			$output='';
			  $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
			  
			$vans="select * from {possible_answer} where  qid=$qid ";
			$vlist=ExecuteQuery($vans,"select");
			$cnt_ans=count($vlist);
			 $script=" 
			<script src='".$gSitePath.drupal_get_path('module', 'quest_lite')."/scripts/jsapi.js' type='text/javascript' ></script>
			
			 <script type='text/javascript'> google.load(\"visualization\", \"1\", {packages:[\"barchart\"]});
			google.setOnLoadCallback(drawChart);
			function drawChart() {
			var data = new google.visualization.DataTable();
			data.addColumn('string', 'Answers');
			data.addColumn('number', 'Percent(%)');
			data.addRows(".$cnt_ans.");";
			for($ab=0;$ab<$cnt_ans;$ab++){
			$per=answer_details($vlist[$ab]['paid'],'percent');
			$inc=$ab+1;
			$script.=" data.setValue(".$ab.", 0, 'Answer".$inc."');
			data.setValue(".$ab.", 1, ".$per.");";
			}
			
		echo	$script.="	var chart = new google.visualization.BarChart(document.getElementById('chart_div'));
			chart.draw(data, {width: 400, height: 240,max:100, is3D: true, title: 'Answer Percentage'});
			}
			</script>";
			
//drupal_add_js($script,'inline');
	echo $output.='
<div id="contentr1" class="clear">
    percentage 
    <div id="chart_div" style="width: 700px; height: 240px;">
    </div>
</div>';

}
function qlite_graph()
{
	
		global $gSitePath,$user, $gDocPath,$base_root,$base_path;
		 $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
		 
		 
		 $vans="select * from {possible_answer} where  qid=$qid ";
		$vlist=ExecuteQuery($vans,"select");
		$cnt_ans=count($vlist);
		 
$script.=" 
<script src='".$gSitePath.drupal_get_path('module', 'quest_lite')."/scripts/jsapi.js' type='text/javascript' ></script>
			
			 <script type='text/javascript'>
google.load(\"visualization\", \"1\", {packages:[\"annotatedtimeline\"]});
      google.setOnLoadCallback(drawAnnot);
      function drawAnnot() {
        var data = new google.visualization.DataTable();
        data.addColumn('date', 'Date');";

	 $ins_tot_ans='';
	 $ins_tot_val='';
         for($ab=0;$ab<$cnt_ans;$ab++){
		 	 $inc=$ab+1;
		 $ins_tot_ans.=" data.addColumn('number', 'Answer". $inc."');";
	  
		} 
        
		for($mn=5;$mn>0;$mn--){
	
		 $year=date("Y");
		 $month=date("m")-1;
		 $dat=date("d")-$mn;
		 
	 $ins_tot_val.=" [new Date(".$year.", ".$month." ,".$dat."),";
	 
	 $inc_this='';
	 
	  for($ab=0;$ab<$cnt_ans;$ab++){
	 $inc_this.= rand(100,1000).",";
	 	} 
	 $ins_tot_val.=rtrim($inc_this,',');
	 $ins_tot_val.="],";
		
		}
		
		
		 $script.=$ins_tot_ans;
		  $script.="   data.addRows([".rtrim($ins_tot_val, ',')."]); ";


   echo  $script.="   var chart = new google.visualization.AnnotatedTimeLine(document.getElementById('annot_div'));
        chart.draw(data, {displayAnnotations: false});
      }
	  </script>
";


echo '<div  >By Time Line <div id="annot_div" style="width: 700px; height: 240px;"></div></div>';

}
function qlite_map()
{

	
		global $gSitePath,$user, $gDocPath,$base_root,$base_path;
		 $qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
		 
		 
		 $vans="select * from {possible_answer} where  qid=$qid ";
		$vlist=ExecuteQuery($vans,"select");
		$cnt_ans=count($vlist);
		 
 echo $script.=" 
<script src='".$gSitePath.drupal_get_path('module', 'quest_lite')."/scripts/jsapi.js' type='text/javascript' ></script>
			
			 <script type='text/javascript'>

    google.load(\"visualization\", \"1\", {packages:[\"map\"]});
      google.setOnLoadCallback(drawMap);
      function drawMap() {
        var data = new google.visualization.DataTable();
        data.addColumn('number', 'Lat');
        data.addColumn('number', 'Lon');
        data.addColumn('string', 'Name');
        data.addRows(4);
        data.setCell(0, 0, 37.4232);
        data.setCell(0, 1, -122.0853);
        data.setCell(0, 2, 'Work');
        data.setCell(1, 0, 37.4289);
        data.setCell(1, 1, -122.1697);
        data.setCell(1, 2, 'University');
        data.setCell(2, 0, 37.6153);
        data.setCell(2, 1, -122.3900);
        data.setCell(2, 2, 'Airport');
        data.setCell(3, 0, 77.2);
        data.setCell(3, 1, 28.6);
        data.setCell(3, 2, 'Shopping');

        var map = new google.visualization.Map(document.getElementById('map_div'));
        map.draw(data, {showTip: true,mapType:'normal',zoomLevel:'0'});
}
	  </script>
";


echo '<div  class="">by area <div id="map_div" style="width: 100%; height: 400px"></div>';
}

	function answer_details($aid='',$action=''){
	switch($action)
	{
	case 'percent':
	return rand(10, 100);
	break;
	}
}	
	function answer_vote()
{

	global $gSitePath,$user, $gDocPath,$base_root;
	$list_length = db_query("select * from {suggest_answer_vote} where answer_id='".$_REQUEST['suggest']."' and uid='".$user->uid."'  ");
	$numr=mysql_num_rows($list_length);
	$fetvote=mysql_fetch_object($list_length);
	$list_own_answer = db_query("select * from {suggest_answer} where said='".$_REQUEST['suggest']."'   ");
	$userownid=mysql_fetch_object($list_own_answer);
	if($userownid->uid!=$user->uid)
	{
		if($numr==0)
		{
		$numvote = db_query("select * from {suggest_answer_vote} where answer_id='".$_REQUEST['suggest']."'   ");
		$calvote=mysql_num_rows($numvote);
		if($calvote==0)
		{
		$votepoint='1';
		}
		else
		{
		$votepoint=$userownid->vote+1;
		}
			$answerquery="insert into suggest_answer_vote(qid,uid,answer_id,vote_date) values ('".$_REQUEST['qaid']."','".$user->uid."','".$_REQUEST['suggest']."','".date('Y-m-d')."')";
			db_query($answerquery);
			
			
			$updatevotesug="update  suggest_answer set vote='$votepoint' where said='".$_REQUEST['suggest']."'";
			db_query($updatevotesug);
			echo '<div class="messages success">Thanks For Voting ! </div>';
		}
		else
		{
			echo '<div class="messages error"> You Have Already Voted This Answer ! </div>';
		
		}
		
	}
	else
	{
		
		echo '<div class="messages error"> You Cannot  Vote For Your  Answer ! </div>';
		
    }

}
?>
