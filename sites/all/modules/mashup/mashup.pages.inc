<?php

function createMashup($pmID) {
    
    global $gSitePath;
	drupal_add_css(drupal_get_path('module', 'mashup').'/mashup.css');
	drupal_add_js(drupal_get_path('module', 'mashup').'/jscolor/jscolor.js');
	drupal_add_js(drupal_get_path('module', 'mashup').'/mashupvalid.js');
    /*$vOutput ='
			<!--script type="text/javascript" src="'.$gSitePath.'sites/all/themes/heardmentality/scripts/mootools-1.2-core.js"></script>
			<script type="text/javascript" src="'.$gSitePath.'sites/all/themes/heardmentality/scripts/mootools-1.2-more.js"></script-->
			<script type="text/javascript" src="'.$gSitePath.'misc/jquery.js"></script>
			<script src="'.$gSitePath.'sites/all/modules/mashup/mashup.js"></script>
				<script>
				//loadWidgetMootools("asdtt34asasdasd3214","testMash")
				loadWidgetJquery("asdtt34asasdasd3214","testMash")
				</script>
				<div id="testMash"></div>
				';*/
	$vOutput ='<form class="formstyle" action="'.$gSitePath.'mashup/save" method="POST" name="frmMail" id="frmMail" onsubmit="return validMashup(this);">
					<input type="hidden" name="hidId" id="hidId" value="'.$pmID.'">
						<table width="100%" border="0" cellspacing="7" cellpadding="7">
						  <tr>
						    <td width="23%"><label for="First Name">Question Font Size<span class="red_txt">*</span></label></td>
						    <td width="77%">
								<select name="selQFSize" id="selQFSize">
									<option value="">Select Question Font Size</option>
						            <option value="8">8px</option>
									<option value="10">10px</option>
									<option value="12">12px</option>
									<option value="14">14px</option>
									<option value="16">16px</option>
									<option value="18">18px</option>
									<option value="20">20px</option>
							    </select>
								<div class="err" id="errQFSize"></div>
							</td>
						  </tr>
						  <tr>
						    <td><label for="Last Name">Question Font Color<span class="red_txt">*</span></label></td>
						    <td><input type="text" id="txtQFColor" name="txtQFColor" class="color" /><div class="err" id="errQFColor"></div></td>
						  </tr>
						  <tr>
						    <td><label for="Company">Answer Font Size</label> <span class="red_txt">*</span></td>
						    <td>
								<select name="selAFSize" id="selAFSize">
									<option value="">Select Question Font Size</option>
						            <option value="8">8px</option>
									<option value="10">10px</option>
									<option value="12">12px</option>
									<option value="14">14px</option>
									<option value="16">16px</option>
									<option value="18">18px</option>
									<option value="20">20px</option>
							    </select>
								<div class="err" id="errAFSize"></div>
							</td>
						  </tr>
						  <tr>
						    <td><label for="Title">Answer Font Color</label> <span class="red_txt">*</span></td>
						    <td><input type="text" id="txtAFColor" name="txtAFColor" class="color" /><div class="err" id="errAFColor"></div></td>
						  </tr>
						  <tr>
						    <td><label for="Email address">Frame Width</label> <span class="red_txt">*</span></td>
						    <td><input type="text" id="txtWidth" name="txtWidth" /><div class="err" id="errWidth"></div></td>
						  </tr>
						  <tr>
						    <td>Frame Height <span class="red_txt">*</span></td>
						    <td><input type="text" id="txtHeight" name="txtHeight" /><div id="errHeight" class="err"></div></td>
						  </tr>
						  <tr>
						    <td>Frame Border Color <span class="red_txt">*</span></td>
						    <td><input type="text" id="txtFBColor" name="txtFBColor" class="color" /><div id="errFBColor" class="err"></div></td>
						  </tr>
						  <tr>
							<td>&nbsp;</td>
							<td><input type="image" src="'.$gSitePath.'sites/all/themes/heardmentality/images/submit.png" class="submit" title="submit" /></td>
						  </tr>
						</table>
						</form>';
	
    return $vOutput;
}
function mashupSave()
{
	global $gSitePath,$gDocPath;
	$vQuestId	= trim($_REQUEST['hidId']);
	$vQFSize	= trim($_REQUEST['selQFSize']);
	$vQFColor	= trim($_REQUEST['txtQFColor']);
	$vAFSize	= trim($_REQUEST['selAFSize']);
	$vAFColor	= trim($_REQUEST['txtAFColor']);
	$vWidth		= trim($_REQUEST['txtWidth']);
	$vHeight	= trim($_REQUEST['txtHeight']);
	$vFBColor	= trim($_REQUEST['txtFBColor']);
	$vApiKey	= md5(rand());
	if($vQFSize != '' && $vQFColor != '' && $vQuestId != '')
	{
		$vInsertSql	= "insert into mashup (apikey, question, quest_font_size, quest_font_color, ans_font_size, ans_font_color, weight, height, border) values ('".$vApiKey."', '".$vQuestId."', '".$vQFSize."', '".$vQFColor."', '".$vAFSize."', '".$vAFColor."', '".$vWidth."', '".$vHeight."', '$vFBColor')";
		db_query($vInsertSql);
		drupal_set_message(t('you have success full create a mashup. Please copy your mashup sample code'));
		drupal_goto($gSitePath."mashup/confrim/".$vApiKey);
	}
}
function mashupConfrim($pmApiKey)
{
	global $gSitePath,$gDocPath;
	 $vJquery ='
			<script type="text/javascript" src="'.$gSitePath.'misc/jquery.js"></script>
			<script src="'.$gSitePath.'sites/all/modules/mashup/mashup.js"></script>
				<script type="text/javascript">
				loadWidgetJquery("'.$pmApiKey.'","testMash")
				</script>
				<div id="testMash"></div>';
	$vMootols ='
			<script type="text/javascript" src="'.$gSitePath.'sites/all/themes/heardmentality/scripts/mootools-1.2-core.js"></script>
			<script type="text/javascript" src="'.$gSitePath.'sites/all/themes/heardmentality/scripts/mootools-1.2-more.js"></script>
			<script src="'.$gSitePath.'sites/all/modules/mashup/mashup.js"></script>
				<script type="text/javascript">
				loadWidgetMootools("'.$pmApiKey.'","testMash")
				</script>
				<div id="testMash"></div>';
				
	$vOutput='<table width="100%" border="0" cellspacing="7" cellpadding="7">
				  <tr>
					<td><b>Api:</b>&nbsp;'.$pmApiKey.'</td>
				  </tr>
				  <tr>
					<td><b>For Jquery Code:</b></td>
				  </tr>
				  <tr>
				  	<td>'.nl2br(htmlentities($vJquery)).'</td>
				  </tr>
				  <tr>
					<td><b>For Mootools Code:</b></td>
				  </tr>
				  <tr>
				  	<td>'.nl2br(htmlentities($vMootols)).'</td>
				  </tr>
				</table>';
	return $vOutput;
}
function mashupXML($id) {
    
    global $gSitePath,$user,$gDocPath,$base_root,$base_path;
	$vApiSql="select * from mashup where status=1 and apikey = '".$id."'";
	$oApi=db_fetch_object(db_query($vApiSql));
	
	$vQuestSql="select * from question where qid = ".$oApi->question;
	$vAnsSql="select * from possible_answer where qid = ".$oApi->question;
	$oQuest=db_fetch_object(db_query($vQuestSql));
	$rRes=db_query($vAnsSql);
	$vAns='';
	$vTotal=db_result(db_query("SELECT count(*) FROM possible_answer where qid=".$oApi->question))-1;
	$vCout=0;
	while($oAns=db_fetch_object($rRes))
	{
		if($vCout==0)
			$vAns=$oAns->answer;
		elseif($vCout <= $vTotal)
			$vAns = $vAns."||".$oAns->answer;
		$vCout++;	
	}
	$vOutput .='<result>';
	$vOutput .='<question>';
	$vOutput .='<value>'.$oQuest->question.'</value>';
	$vOutput .='<color>'.$oApi->quest_font_color.'</color>';
	$vOutput .='<size>'.$oApi->quest_font_size.'</size>';
	$vOutput .='</question>';
	$vOutput .='<answer>';
	$vOutput .='<value>'.$vAns.'</value>';
	$vOutput .='<color>'.$oApi->ans_font_color.'</color>';
	$vOutput .='<size>'.$oApi->ans_font_size.'</size>';
	$vOutput .='</answer>';
	$vOutput .='<width>';
	$vOutput .='<value>'.$oApi->weight.'</value>';
	$vOutput .='</width>';
	$vOutput .='<height>';
	$vOutput .='<value>'.$oApi->height.'</value>';
	$vOutput .='</height>';
	$vOutput .='<border>';
	$vOutput .='<value>'.$oApi->border.'</value>';
	$vOutput .='</border>';
	$vOutput .='</result>';
    header('Content-type: text/xml');
	echo $vOutput;
}
