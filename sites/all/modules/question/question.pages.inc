<?php
//my question


function my_question() {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    $strReturn = '';
    /*$client_select =db_query("SELECT *  FROM {question} where uid='".$user->uid."'");
     $client_array=array();
     $client_key=array();
     
     while($list=db_fetch_object($client_select))
     {
     
     $client_array[] = $list->cat_name;
     $client_key[]=$list->cat_id;
     
     }
     */

    $query = "SELECT *  FROM {question} where uid='".$user->uid."'";
    $list = ExecuteQuery($query, "select");
    
    $strReturn .= '<div class="clear-block">';
    $strReturn .= '<table width="98%" border="1" cellspacing="5" cellpadding="5">';
    for ($i = 0; $i < count($list); $i++) {
        
        $strReturn .= '<tr><td>';
        $strReturn .= $list[$i]['question'];
        $strReturn .= '</td><td>'.$list[$i]['date_added'].'</td><td>';
        
        $strReturn .= '<a href="'.$gSitePath.$list[$i]['url'].'">View</a>&nbsp;<!--<b>/</b>&nbsp;<a href="'.$gSitePath.'question/edit/'.$list[$i]['qid'].'">Edit</a>&nbsp;--><b>/</b>&nbsp;<a href="'.$gSitePath.'question/delete/'.$list[$i]['qid'].'">Delete</a> ';
        
        $strReturn .= '</td></tr>';
    
    }
    
    $strReturn .= '</table></div>';
    if (count($list) < 1) {
        drupal_set_message($message = 'No Questions Found!', $type = 'error');
    }
    
    return $strReturn;


}
// question add
function question_add() {
    global $gSitePath,$user,$gDocPath,$base_root;
    //get error msgs
    $error = drupal_get_messages();
    $list_err = '';
    if (! empty($error)) {
        $list_err = implode("<br/>", $error['error']);
    }

    
    //print_r($_SESSION['post']);
    $q_quest = '';
    $optionlist = '';
    $q_context = '';
    $q_ans1 = '';
    $q_ans2 = '';
    if (isset($_SESSION['post']) && ! empty($_SESSION['post'])) {
        extract($_SESSION['post']);
    }
    global $gSitePath,$user,$gDocPath,$base_root;
    $output = '';
    
    //drupal_add_js(drupal_get_path('module', 'question').'/scripts/calendar.js');
    //drupal_add_js('misc/jquery.js');
    //drupal_add_js('misc/ui.core.min.js');

    
    //drupal_add_js('misc/ui.datepicker.min.js');
    //drupal_add_css(drupal_get_path('module', 'question').'tagging/tagging.css');
    
    //drupal_static_reset('drupal_add_js');
    //drupal_add_js('','external');
    //		 drupal_set_html_head('<script src="http://ws.geonames.org/export/geonamesData.js" type="text/javascript"></script>');

    
    //drupal_add_js(drupal_get_path('module', 'question').'/scripts/question.js');
    
    $output .= '
	
	<script type="text/javascript" src="'.$gSitePath.drupal_get_path('theme', 'heardmentality').'/scripts/mootools-1.2-core.js"></script>
	<script type="text/javascript" src="'.$gSitePath.drupal_get_path('theme', 'heardmentality').'/scripts/mootools-1.2-more.js"></script>	
	<script src="http://ws.geonames.org/export/geonamesData.js" type="text/javascript"></script>
	<script src="'.$gSitePath.drupal_get_path('module', 'question').'/scripts/question.js" type="text/javascript"></script>
	<link rel="stylesheet" href="'.$gSitePath.'sites/all/modules/tagging/tagging.css" type="text/css" />
<!--<script src="'.$gSitePath.drupal_get_path('module', 'question').'/scripts/auto.js" type="text/javascript"></script>
-->	

<script>
			var mpath=\''.$gSitePath.'\';
		
			</script>


<script src="'.$gSitePath.'sites/all/modules/question/scripts/suggest_dynamic.js" type="text/javascript"></script>
<script src="'.$gSitePath.'sites/all/modules/question/scripts/post_list.js" type="text/javascript"></script>
	<link rel="stylesheet" href="'.$gSitePath.'sites/all/modules/question/styles/auto.css" type="text/css" />
	
	
				<script type="text/javascript">
				var spath=\''.$gSitePath.'\';
			
				function setDefaultCountry() {
  var countrySelect = document.getElementById("q_country");

  for (i=0;i< countrySelect.length;i++) {
    // the javascript geonamesData.js contains the countrycode
    // of the userIp in the variable \'geonamesUserIpCountryCode\'
    if (countrySelect[i].value == geonamesUserIpCountryCode) {
      // set the country selectionfield
	      countrySelect.selectedIndex = i;
		get_state(geonamesUserIpCountryCode);
    }
  }
}


window.addEvent(\'domready\', function(){
//setDefaultCountry();
});
	//	window.setTimeout("setDefaultCountry()", 1000);
			/*	jQuery(function() {
		jQuery("#q_edate").datepicker({
			changeMonth: true,
			changeYear: true,minDate: \'1d\', dateFormat: \'yy-mm-dd\' 
		});

		
	});*/
				
				 
					
						
				
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
										get_tag_cat(ids,level);
							}
							}else{
							 $(divid).set(\'html\',\'No Subcategory\');
							}
							}	
						
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
							 $(\'chg_city\').set(\'html\', \'\');
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
							
				/*
		(function($) {
  $(document).ready(function() {
    $(\'input.tagging-widget-input\').tagging();
  });
})(jQuery);	
*/
							
						</script>
			
			';
    
    //geoname api
    $options = array('sortby'=>'countryname', 'sortorder'=>'ASC');
    $result = geonames_query('countryinfo', NULL, $options);
    $optionlist .= ' <option value="0" >--Country--</option>';
    foreach ($result->results as $country) {
        $optionlist .= sprintf('<option value="%s">%s</option>', $country['countrycode'], $country['countryname']);
    }

    
    $output .= '<link rel="stylesheet" href="'.$gSitePath.'modules/system/system.css" type="text/css" />
	<link rel="stylesheet" href="'.$gSitePath.'sites/all/themes/heardmentality/css/content.css" type="text/css" />
<link rel="stylesheet" href="'.$gSitePath.'sites/all/themes/heardmentality/css/ui.css" type="text/css" />
<link rel="stylesheet" href="'.$gSitePath.'sites/all/modules/tagging/tagging.css" type="text/css" />';
    $output .= '<style>td,select{font-size:12px;}</style>
	
		<div id="err" style="border: 3px solid rgb(221, 151, 161); display: block; background-color: rgb(238, 238, 238); height: auto; color: red;">'.$list_err.'</div>
	
			<br/>
			<div align="right"><span title="This field is required." class="form-required">*</span> Required Fields</div>
<form id="question" name="question" onsubmit="return validate_question();"  method="post" action="'.$gSitePath.'question/save" ><table width="100%" border="0" align="center" style="border:0px;">
  <tr>
    <td width="0%" height="44">&nbsp;</td>
    <td width="14%">Question<span title="This field is required." class="form-required">*</span></td>
    <td colspan="4">
       <!-- <input type="text" name="q_quest" tabindex="1" value="'.$q_quest.'" id="q_quest"  size="100"/> -->
		
		
		
		<input name="q_quest" autocomplete="off" type="text" tabindex="1" id="q_quest" 
     onkeyup="ajax_showOptions(this,\'getCountriesByLetters\',event,\'C1\')" 
     onKeyDown="ajax_showOptions(this,\'getCountriesByLetters\',event,\'C1\')" size="100" >
		
		
		<!--  <input size="100" autocomplete="off"  name="q_quest" id="q_quest" value="" onkeyup="suggest(this.value);" class="form-text form-autocomplete tagging-widget-input tagging-widget-input-1" type="text"/>
		 <div class="suggestionsBox" id="suggestions" style="visibility:hidden;">
                                
                                <div class="suggestionList" id= "suggestionsList">
                                </div>
								</div>-->
		
		   </td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td valign="top">Context</td>
    <td colspan="4">
      <textarea name="q_context" id="q_context" tabindex="2" cols="100" rows="2" style="border:1px solid #BBBBBB;

width:580px; scroll;">'.$q_context.'</textarea>  </td>
  </tr>
  <tr>    <td colspan="4">&nbsp;</td></tr>
  <tr>
    <td>&nbsp;</td>
    <td valign="top">Answer<span title="This field is required." class="form-required">*</span><br/><small>[min 2]</small></td>
    <td width="26%" valign="top"><table width="100%" border="0"> <tr>
          <td>
            <input tabindex="3" name="q_ans1" type="text" id="q_ans1"  value="'.$q_ans1.'" size="40" />
          </td>
        </tr>
        <tr><td>&nbsp;</td></tr>
        <tr>
          <td>
            <input name="q_ans2" tabindex="4" type="text" id="q_ans2"  onkeyup="  $(\'Add\').disabled =0;" value="'.$q_ans2.'" size="40" />
			<p></p>
          </td>
        </tr>
        
        ';

    
    $output .= '</table><div id="add_more"></div><div id="del_ans" style="visibility:hidden;"><small><a href="javascript:void(0);" tabindex="88" onclick="del_ans();">[Remove]</a></div><small><br/>
	
	<input type="button" tabindex="13" name="Add" disabled="disabled" onclick="add_ans();" id="Add" value="Add Answer" /> <input type="hidden" name="ans_cnt" id="ans_cnt" value="2"><input type="hidden" id="cat1" name="cat1" value="">&nbsp;<input type="hidden" id="cat2" name="cat2" value="">&nbsp; <input type="hidden"  id="cat3" name="cat3" value=""> 
	</td>
    <td colspan="3" align="left" valign="top"><table width="65%" border="0">
	<tr><td colspan="3" height="40"  valign="middle" ><b>Categories</b><small>[Main Category<span title="This field is required." class="form-required">*</span>]</small></td></tr>
      <tr>
        <td width="25%" align="left"><select tabindex="14"  name="q_cat[]" id="q_cat" multiple="multiple" onchange="get_subcat(\'q_cat\',\'chg_scat\',1);" size="5"><option value="">Select Category</option>';
    $client_select = db_query("SELECT cat_id,cat_name FROM {category} where parent_id='0'");
    while ($list = db_fetch_object($client_select)) {
        $output .= '<option value="'.$list->cat_id.'">'.$list->cat_name.'</option>';
    
    }
    
    $output .= '</select></td>
        <td width="25%" align="left"><div id="chg_scat"><select tabindex="15"  name="q_scat[]" id="q_scat" multiple="multiple"  size="5"><option value="">Select Sub Category</option>';
    //$client_select1 =db_query("SELECT cat_id,cat_name FROM {category} where parent_id='0'");
    $client_select1 = '';
    while ($list = db_fetch_object($client_select1)) {
        $output .= '<option value="'.$list->cat_id.'">'.$list->cat_name.'</option>';
    
    }
    $output .= '</select></div></td>
        <td  width="25%" align="left"><div id="chg_sscat"><select tabindex="16"  name="q_sscat[]" id="q_sscat" multiple="multiple"  size="5"><option value="">Select Sub Sub Category</option>';
    //$client_select2 =db_query("SELECT cat_id,cat_name FROM {category} where parent_id='0'");
    $client_select2 = '';
    while ($list = db_fetch_object($client_select2)) {
        $output .= '<option value="'.$list->cat_id.'">'.$list->cat_name.'</option>';
    
    }
    $output .= '</select></div></td>
      </tr>
	  	<tr><td colspan="3" height="40"  valign="middle" ><b>Location</b></td></tr>
	  <tr><td width="13%"><!--<input type="text" name="q_country" id="q_country" value="Country" onblur="javascript: if(this.value == \'\') this.value=\'Country\';" onfocus="javascript: if(this.value == \'Country\') this.value=\'\';" size="30" />--><select name="q_country" style="width: 125px;" tabindex="16"  onchange="get_state(this.value);" id="q_country">'.$optionlist.'</select></td>
	
    <td width="13%"><!--<input type="text" name="q_state" id="q_state" value="State"  onblur="javascript: if(this.value == \'\') this.value=\'State\';" onfocus="javascript: if(this.value == \'State\') this.value=\'\';"   size="30"/>--> <div id="chg_state"><select id="q_state" name="q_state" onchange="get_city(this.value);" style="width: 125px;" tabindex="18"><option value="0" >--State--</option></select></div></td>
	
    <td width="43%"><!--<input type="text" name="q_city" id="q_city" value="City" onblur="javascript: if(this.value == \'\') this.value=\'City\';" onfocus="javascript: if(this.value == \'City\') this.value=\'\';"    size="30"/>--><div id="chg_city"><select name="q_city" id="q_city" style="width: 125px;" tabindex="19"> <option value="0" >--Cities--</option></select></div></td>  </tr>
    </table></td>
  </tr>
  
  <tr>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
  
  <!--<tr>
    <td>&nbsp;</td>
    <td nowrap="nowrap">End Date<span title="This field is required." class="form-required">*</span></td>
    <td><input type="text" name="q_edate" value="" autocomplete="off"   id="q_edate" /> <small>Eg: yyyy-mm-dd</small></td>
    <td><input name="invite_count" type="hidden" id="invite_count" value="1" /></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>--><tr><td colspan="6">';
    
    $output .= '<tr><td colspan="6">'.get_tagging().'</td></tr>';

    
    $get_cn = db_query("select * from {user_profile} where uid='$user->uid'");
    $result = db_fetch_array($get_cn);
    extract($result);
    
    if ($question_privacy == '4') {
        
        $output .= '<tr><td colspan="6"> <fieldset>
		<legend><b><i>Share With</i></b> </legend>
		
		<div class="form-item" id="edit-name-wrapper">
            <label for="edit-"></label>
             <input type="radio" name="qrset"  class="qrset" value="1">&nbsp;Everyone
            <div class="description"></div>
        </div>
        <div class="form-item" id="edit-name-wrapper">
            <label for="edit-"></label>
             <input type="radio" name="qrset" class="qrset" value="2">&nbsp;Only Followers & Followees 
            <div class="description"></div>
        </div>
         <div class="form-item" id="edit-name-wrapper">
            <label for="edit-"></label>
             <input type="radio" name="qrset" class="qrset"  value="3">&nbsp;Not at all
            <div class="description"></div>
        </div>
       
        </fieldset>		</td></tr>';
    
    }
    
    $output .= ' </td></tr><tr>
    <td height="42">&nbsp;</td>
    <td>&nbsp;</td>
	    <td>&nbsp;</td>    <td>&nbsp;</td>    
    <td><input type="submit" name="save" tabindex="21" id="save" value="Save" class="question-save"/></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td align="right"></td>
  </tr>
</table>
</form>

';
    
    echo $output;


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


function get_tagging_edit($midr) {
    global $gSitePath,$user,$gDocPath,$base_root,$base_path;
    $randomtag = '';
    $content = '';
    $tagged = '';
    
    $randomtag = popular_tag();
    if ($midr != '') {
        
       // $exp = explode(",", $tag);

        
           $selmlist="select * from qtag as a, tagging as b where a.qid='$midr' and a.tag_id=b.tid ";
	 $mysqlfet=db_query($selmlist);
	 while($rewdisp=db_fetch_object($mysqlfet))
         {   
            $tagged .= '<div id="tagset" class="tagging-tag" >'.$rewdisp->tag.'</div>';
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
function question_save() {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    
    $q_quest = '';
    // print_r($_REQUEST);
    extract($_REQUEST);
    $output = '';
    $g_global = '';
    if (! empty($q_quest) && ! empty($q_ans1) && ! empty($q_ans2) && ! empty($cat1)) {
        $edate = $q_edate;
        
        $dst = clean_url(myTruncate($q_quest, 100, ' '));
        
        $result = db_query("INSERT INTO {question} set uid='$user->uid',question='$q_quest',context=' $q_context',cid=' $cat1',scid='$cat2',sscid='$cat3',country='$q_country',state='$q_state',city='$q_city',url='$dst',share='$qrset'  ");
        
        $ins_id = db_last_insert_id('question', 'qid');
		
		////////////mail notication for user follwers to me//////////////////////////////////////
		 $sel_listf = "select * from follower  where follower_id='".$user->uid."'   ";
		$rs_followerf = db_query($sel_listf);
		while ($follower_resultfuser = db_fetch_object($rs_followerf)) 
		{
		
			$sellist="select * from users where uid='".$follower_resultfuser->uid."'";
			$res_users=db_query($sellist);
			$usert=db_fetch_object($res_users);
			 $to = $usert->mail;
		if($usert->notify_itype==1)
		{
		
		$insert_notify=db_query("insert into notification (uid,follower_action,is_question,node_id) values('".$follower_resultfuser->uid ."','1','1','".$ins_id."' ) ");
		
		}
		if($usert->notify_etype==1)
		{
		
		///////////email for following ///////////////
		
		
		$subject_proj=$list_content->subject;
		
		
		$sel_user_cmt="SELECT * FROM notification_mail_format Where id='4'";
		$rs_mgmt=db_query($sel_user_cmt);
		$list_content=db_fetch_object($rs_mgmt);
		$contentm=str_replace("#uname#",$usert->name,$list_content->content);
		$contentm= str_replace("#anothername#",$user->name,$contentm);
		//echo $contentm;
		$mail_success = htmlmail_function($to,$subject_proj,$contentm,'');
		}
		
		}
       
		
        //forum
        
        $forum = db_query("INSERT INTO {forum_wave} set qid_rid='$ins_id',type='1',uid='$user->uid',title='Discuss about this question',private='0' ");

        
        increasepoints('1', $ins_id, '0');
        //for url alias
        $url = 'qlite/view/'.$ins_id;
        
        $urlins = db_query("insert INTO {url_alias} set src='".$url."',dst='".$dst."'");
        
        for ($i = 1; $i <= $ans_cnt; $i++) {
            $name = "q_ans".$i;
            if (! empty($$name)) {
                $result = db_query("INSERT INTO {possible_answer} (qid,answer) VALUES (%d,'%s')", $ins_id, $$name);
            }
        }
        
        if ($q_tag != '') {
            
            $q_tag = explode(',', $q_tag);
            
            //its in quset_lite.module
            process_tags($q_tag, $ins_id, 0);

        
        }
        
        if ($result)
            $output = drupal_set_message(t('Thank you, Question added successfully!'), $type = 'success');
        unset($_SESSION['post']);
        $_SESSION['post'] = '';
        // drupal_goto("question");
       echo '<script>window.parent.location.href="'.$gSitePath.'question/";</script>';
    } else {
        drupal_get_messages($type = 'error', $clear = 'TRUE');
        $_SESSION['post'] = $_POST;
        drupal_set_message($message = 'Sorry, Following required fields are Empty!', $type = 'error');
        
        if ( empty($q_quest))
            drupal_set_message($message = 'Question should not be Empty!', $type = 'error');
        
        if ( empty($q_ans1) || empty($q_ans2))
            drupal_set_message($message = 'Minimum 2 answers should be needed!', $type = 'error');
        
        if ( empty($cat1))
            drupal_set_message($message = 'Main Category should not be Empty!', $type = 'error');

        
        drupal_goto("question/add");
    
    }
    
    echo implode("<br/>", $output['error']);
}


function question_edit_save($array) {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    $nid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    
    //  print_r($array);
    extract($array);
    $output = '';
    
    if (! empty($q_quest) && ! empty($q_ans1) && ! empty($q_ans2) && ! empty($cat1)) {
        $edate = $q_edate;
        $result = db_query("update {question} set question='$q_quest',context='$q_context',cid='$cat1',scid='$cat2',sscid='$cat3',	 global='$q_global',country='$q_country',state='$q_state',city='$q_city',enddate='$edate' where qid='".$nid."' AND uid='".$user->uid."'");
        
        $ins_id = db_last_insert_id('question', 'qid');
        for ($i = 1; $i <= $ans_cnt; $i++) {
            $name = "q_ans".$i;
            $aid = "aid".$i;
            if (! empty($$name)) {
                
                if (! empty($$aid)) {
                    $result = db_query("UPDATE {possible_answer} set answer='".$$name."' where paid='".$$aid."' AND qid='".$nid."'");
                } else {
                    
                    $result = db_query("INSERT INTO {possible_answer} (qid,answer) VALUES (%d,'%s')", $ins_id, $$name);
                }
            }
        }
        
        if (db_query("select * from {qtag} where qid='".$nid."'")) {
            
            db_query("update {qtag} set tag='".$q_tag."' where qid='".$nid."'");
        
        }
        
        if ($result)
            drupal_set_message(t('Thank you, Question updated successfully!'), $type = 'success');
        drupal_goto("question/");
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


function edit_question() {

    
    global $gSitePath,$user,$gDocPath,$base_root;
    $output = '';

    
    drupal_set_html_head('<script src="http://ws.geonames.org/export/geonamesData.js"
        type="text/javascript"></script>');

    
    if (isset($_POST['update'])) {
        
        question_edit_save($_POST);
    }
    
    $result = geonames_query('countryinfo');
    foreach ($result->results as $country) {
        $optionlist .= sprintf('<option value="%s">%s</option>', $country['countrycode'], $country['countryname']);
    }

    
    $nid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    
    $result = db_query("SELECT * FROM {question} as q left join {qtag} as t on q.qid=t.qid where q.qid='".$nid."' AND q.uid='".$user->uid."'");
    $quest = db_fetch_object($result);
    drupal_add_js(drupal_get_path('module', 'question').'/scripts/question.js');
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
  
  <!--<tr>
    <td>&nbsp;</td>
    <td nowrap="nowrap">End Date<span title="This field is required." class="form-required">*</span></td>
    <td><input type="text" name="q_edate" autocomplete="off" id="q_edate" value="'.$quest->enddate.'"  /> <small>Eg: yyyy-mm-dd</small></td>
    <td><input name="invite_count" type="hidden" id="invite_count" value="1" /></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>-->
  <tr><td colspan="6">';
    
    $output .= '<tr><td colspan="6">'.get_tagging($quest->tag).'</td></tr>';

    
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


function question_ajax() {
    //print_r($_REQUEST);
    $ret = '';
    extract($_REQUEST);
    if (isset($_REQUEST['ids'])) {
        $client_select = db_query("SELECT cat_id,cat_name FROM {category} where parent_id IN ($ids)");
        
        $client_array = array();
        $client_key = array();
        
        while ($list = db_fetch_object($client_select)) {
            
            $client_array[] = $list->cat_name;
            $client_key[] = $list->cat_id;
        
        }
        if (! empty($client_array)) {
            
            if ($action == 1) {
                $qscat = "q_scat";
                $tab = 15;
            }
            if ($action == 2) {
                $qscat = "q_sscat";
                $tab = 16; //	get_subcat(\'q_cat\',\'chg_scat\',1);
            }
            $ret = '<select tabindex="'.$tab.'"  size="5" multiple="multiple" onchange="get_subcat('.$qscat.',\'chg_sscat\','.++$action.');" id="'.$qscat.'" name="q_scat[]"> ';
            
            for ($i = 0; $i < count($client_array); $i++) {
                
                $ret .= '<option value="'.$client_key[$i].'">'.$client_array[$i].'</option>';
            
            }
            $ret .= "</select>";
        
        } else {
            $ret .= 'No Subcategory';
        }
        echo $ret;
        exit;
    } elseif (isset($_REQUEST['code'])) {
        
        switch ($action) {
            
            case 1: //get state
                $query = array('country'=>$code);
                $result = geonames_query('countryinfo', $query);
                
                $query = array('geonameid'=>$result->results[0][geonameid]);
                $result = geonames_query('children', $query);
                //print_r($result);
                $ret = '<select tabindex="18"  style="width: 125px;"  onchange="get_city(this.value);" id="q_state" name="q_state"> <option value="">--States--</option>';
                foreach ($result->results as $state) {
                    
                    $ret .= sprintf('<option value="%s">%s</option>', $state['geonameid'], $state['name']);
                }
                $ret .= "</select>";
                echo $ret;
                break;
                exit;
            case 2: //get city
                
                $query = array('geonameid'=>$code);
                $result = geonames_query('children', $query);
                //print_r($result);
                $ret = '<select  tabindex="19"  style="width: 125px;"  id="q_city" name="q_city"> <option value="">--Cities--</option> ';
                foreach ($result->results as $state) {
                    
                    $ret .= sprintf('<option value="%s">%s</option>', $state['geonameid'], $state['name']);
                }
                $ret .= "<option value='-1'>Others</option>";
                $ret .= "</select>";
                echo $ret;
                break;

        
        }

    
    } elseif (isset($_REQUEST['tag'])) {
        
        extract($_REQUEST);
        
        $tarr = explode(' ', $tag);
        $qns = explode(' ', $qns);
        $tarr = array_merge($tarr, $qns);
        $tarr = array_filter($tarr);
        $tarr = array_unique($tarr);
        
        $taglist = array();
        
        foreach ($tarr as $list) {
            
            $query = " SELECT * FROM {tagging} WHERE `tag` LIKE  '%$list%' LIMIT 0 , 15 ";
            $result = ExecuteQuery($query, "select");
            foreach ($result as $single) {
                array_push($taglist, $single['tag']);
            }
        }
        //for category taglist
        if (! empty($cat1)) {
            
            $exp = explode(',', $cat1);
            
            $qids = array();
            foreach ($exp as $scat) {
                
                $query = " SELECT * FROM {question}  ";
                $result = ExecuteQuery($query, "select");
                
                foreach ($result as $man) {
                    
                    $getcat = explode(',', $man['cid']);
                    
                    if (in_array($scat, $getcat)) {
                        
                        array_push($qids, $man['qid']);
                    
                    }
                }
                
                /*
                 if(!empty($cat2)){
                 $exp1 = explode(',', $cat2);
                 
                 foreach ($exp1 as $ocat) {
                 
                 $query = " SELECT * FROM {question}";
                 $result = ExecuteQuery($query, "select");
                 
                 foreach ($result as $man) {
                 
                 $getcat1 = explode(',', $man['scid']);
                 
                 if (in_array($ocat, $getcat1)) {
                 
                 array_push($qids, $man['qid']);
                 
                 }
                 }
                 
                 }
                 */


                $qids = array_unique($qids);
                $qids = implode(',', $qids);
                
                $query = " SELECT * FROM {tagging} WHERE `qid` IN ($qids) ";
                $result = ExecuteQuery($query, "select");
                foreach ($result as $single) {
                    array_push($taglist, $single['tag']);
                }
            
            }

        
        }

        
        $taglist = array_filter($taglist);
        
        $taglist = array_unique($taglist);
        $taglist = implode(',', $taglist);
        $taglist = explode(',', $taglist);
        $taglist = array_filter($taglist);
        $taglist = array_unique($taglist);
        
        $tag = ' <label>
            	                    Suggestions:
            	                </label>';
        if (! empty($taglist)) {
            foreach ($taglist as $ins) {
                $tag .= '	
            	                    <div id="tagging-1" class="tagging-suggest-tag processed">
            	                        '.$ins.'</div>';

            
            }
        } else {
            
            $tag .= '<b>No Suggestions</b>';
        }
        
        echo $tag;
        exit;
    
    }
}


//delete confirm

function question_delete_confirm(&$form_state, $question) {
    $nid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $form['nid'] = array('#type'=>'hidden', '#value'=>$nid, );
    
    $form['qid'] = array('#type'=>'hidden', '#value'=>$question, );
    
    return confirm_form($form, t('Are you sure you want to delete this question?'), isset($_GET['destination']) ? $_GET['destination'] : "question/", t('This action cannot be undone.'), t('Delete'), t('Cancel'));
}

// delete category
function question_delete_confirm_submit($form, &$form_state) {

    
    global $gSitePath,$user,$gDocPath,$base_root;
    $form_values = $form_state['values'];
    
    if ($form_state['values']['confirm']) {
        $qid = $form_state['values']['nid'];
        discipline($uid,$qid);
       $result = db_query("delete from {question} where qid='".$qid."' AND uid='".$user->uid."'");
     db_query("delete from {possible_answer} where qid='".$qid."'");
        if ($result)
            drupal_set_message(t('Question has been deleted successfully.'), $type = 'success');
        else
            drupal_set_message(t('sorry error Occurs, Try Again! .'), $type = 'error');
    }
    
    drupal_goto("question/");
}

function admin_question() {
    
    $strReturn = '';
    global $gSitePath,$user,$gDocPath,$base_root;

    
    $type = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    switch ($type) {
        
        case 'flagged':
            drupal_set_title("Admin Flagged Questions");
            $query = "SELECT *  FROM {question_flags} as f  join {question} as q  on f.nodeid=q.qid where f.type='question' ORDER BY q.date_added DESC LIMIT 0,15";
            $list = ExecuteQuery($query, "select");

            
            break;
        case 'new':
            
            $query = "SELECT *  FROM {question} ORDER BY date_added DESC LIMIT 0,15";
            $list = ExecuteQuery($query, "select");

            
            break;
    }
    
    $strReturn .= '<div class="clear-block">';
    $strReturn .= '<table width="98%" border="1" cellspacing="5" cellpadding="5">';
    for ($i = 0; $i < count($list); $i++) {
        $date = format_date_class($list[$i]['date_added'], date('Y-m-d H:i:s'));
        $strReturn .= '<tr><td>';
        $strReturn .= '<a href="'.$gSitePath.$list[$i]['url'].'">'.$list[$i]['question'].'</a>';
        $strReturn .= '</td><td>'.$date.'</td><td>';
        
        $strReturn .= '<!--<b>/</b>&nbsp;<a href="'.$gSitePath.'question/edit/'.$list[$i]['qid'].'">Edit</a>&nbsp;<b>/</b>-->&nbsp;<a href="'.$gSitePath.'question/delete/'.$list[$i]['qid'].'">Delete</a> ';
        
        $strReturn .= '</td></tr>';
    
    }
    
    $strReturn .= '</table></div>';
    if (count($list) < 1) {
        drupal_set_message($message = 'No Questions Found!', $type = 'error');
    }

    
    echo $strReturn;

}

function admin_content() {
    global $gSitePath,$user,$gDocPath,$base_root;
    $outputcontent = '';
    drupal_add_js(drupal_get_path('module', 'question').'/scripts/qadmin.js');
    return $outputcontent;


}


function admin_panel_tab() {
    global $gSitePath,$user,$gDocPath,$base_root;
    $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    
    echo $output = '<div class="toolbarTabs">
	<ul id="qTabs" class="tab-menu">
	<li id="qTabs1Link" class="selected"><a>New</a></li>
	<li id="qTabs2Link"><a>Flagged</a></li>
	<li id="qTabs3Link" ><a>User</a></li>
	</ul>
	<div class="clear"></div>
	</div>

	<script type="text/javascript">
	
	MochaUI.initializeTabs("qTabs");
	
	$("qTabs1Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("admin-id"),
	"url":       "'.$gSitePath.'admin/panelc/new"
	});
	});
	
	$("qTabs2Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("admin-id"),
	"url":       "'.$gSitePath.'admin/panelc/flagged"
	});
	});
	
	$("qTabs3Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("admin-id"),
	"url":       "'.$gSitePath.'admin/panelc/user"
	});
	});
	
	</script>';

}
function panel_content($type = '') {
    global $gSitePath,$user,$gDocPath,$base_root;
    
    $strReturn = '';
    $strReturn .= '<div class="clear-block">';
    
    if ( empty($type)) {
        
        $type = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    }
    
    switch ($type) {
        
        case 'flagged':
            drupal_set_title("Admin Flagged Questions");
            $query = "SELECT *,ifnull((select count(*) from {question_flags} where nodeid=q.qid AND type='question' group by nodeid),0) as fcnt  FROM {question_flags} as f  join {question} as q  on f.nodeid=q.qid where f.type='question' ORDER BY f.flag_date DESC LIMIT 0,15";
            $list = ExecuteQuery($query, "select");
            
            $strReturn .= '
	<div id="qlist">
	<form id="qadmin" method="post" action="'.$gSitePath.'admin/panelc/flagsave" >
	<table width="98%" border="1" cellspacing="5" cellpadding="5">';
            foreach ($list as $quest) {
                $date = format_date_class($quest['flag_date'], date('Y-m-d H:i:s'));
                $strReturn .= '<tr><td>';
                $strReturn .= '<a href="'.$gSitePath.$quest['url'].'">'.wordwrap($quest['question'], 80, '<br/>').'</a>';
                $strReturn .= '</td><td>'.$quest['abuse_type'].'</td><td># Flag :'.$quest['fcnt'].'</td>';
                $strReturn .= '</td><td>'.$date.'</td><td>';
                
                $strReturn .= '<!--<b>/</b>&nbsp;<a href="'.$gSitePath.'question/edit/'.$quest['qid'].'">Edit</a>&nbsp;<b>/</b><a href="'.$gSitePath.'question/delete/'.$list[$i]['qid'].'">Delete</a>-->&nbsp;<input type="checkbox" class="check-me" name="qids[]" value="'.$quest['fid'].'" /> ';
                
                $strReturn .= '</td></tr>';
            
            }

            
            if (count($list) < 1) {
                //  drupal_set_message($message = 'No Questions Found!', $type = 'error');
                $strReturn .= ' <div class="error" align="left" >No Questions Found!</div> ';
            } else {
                
                $strReturn .= '</table>
					<br/><div id="showbox" align="left" style="width:100%;display:none"><label for="reporttext"><b>Send Report Message :</b></label><br/><textarea name="reporttext" cols="55" row="17" id="reporttext"></textarea></div>
	<br/>
	<div align="left" style="width:100%" ><input type="hidden" id="actions" name="actions" value="1"/><input type="submit"  value="Ignore"/>&nbsp; <input onclick="admin_reject(0);" type="button" value="Reject"/>&nbsp; <span onclick="checkall(1);">Check All</span>&nbsp;<span onclick="checkall(0);">Uncheck All</span></div>
	</div></form><script>admin_approve();</script></div>';
            }
            break;
        case 'flagsave':
            
            $qids = implode(',', $_REQUEST['qids']);
            if ($_REQUEST['actions']) {
                
                $query = db_query("delete from {question_flags} where type='question' AND fid in ($qids)");
                echo '<div class="success">Question updated successfully!</div>';
            } else {
                $query = db_query("delete from {question} where qid in ($qids)");
                echo '<div class="success">Question updated successfully!</div>';
            
            }
            
            panel_content('flagged');
            exit;
            break;

        
        case 'new':
            
            $query = "SELECT *  FROM {question} where status='0' ORDER BY date_added DESC LIMIT 0,15";
            $list = ExecuteQuery($query, "select");
            
            $strReturn .= '
	<div id="qlist">
	<form id="qadmin" method="post" action="'.$gSitePath.'admin/panelc/save" >
	<table width="98%" border="1" cellspacing="5" cellpadding="5">';
            for ($i = 0; $i < count($list); $i++) {
                $date = format_date_class($list[$i]['date_added'], date('Y-m-d H:i:s'));
                $strReturn .= '<tr><td>';
                $strReturn .= '<a href="'.$gSitePath.$list[$i]['url'].'">'.wordwrap($list[$i]['question'], 80, '<br/>').'</a>';
                $strReturn .= '</td><td>'.$date.'</td><td>';
                
                $strReturn .= '<!--<b>/</b>&nbsp;<a href="'.$gSitePath.'question/edit/'.$list[$i]['qid'].'">Edit</a>&nbsp;<b>/</b><a href="'.$gSitePath.'question/delete/'.$list[$i]['qid'].'">Delete</a>-->&nbsp;<input type="checkbox" class="check-me" name="qids[]" value="'.$list[$i]['qid'].'" /> ';
                
                $strReturn .= '</td></tr>';
            
            }

            
            if (count($list) < 1) {
                //  drupal_set_message($message = 'No Questions Found!', $type = 'error');
                $strReturn .= ' <div class="error" align="left" >No Questions Found!</div> ';
            } else {
                
                $strReturn .= '</table>
				<br/><div id="showbox" align="left" style="width:100%;display:none"><label for="reporttext"><b>Send Report Message :</b></label><br/><textarea name="reporttext" cols="55" row="17" id="reporttext"></textarea></div>
	<br/><div align="left" style="width:100%" ><input type="hidden" id="actions" name="actions" value="1"/><input type="submit"  value="Approve"/>&nbsp; <input onclick="admin_reject(0);" type="button" value="Reject"/>&nbsp; <span onclick="checkall(1);">Check All</span>&nbsp;<span onclick="checkall(0);">Uncheck All</span></div>
	</div></form><script>admin_approve();</script></div>';
            }
            break;
        case 'save':

            
            $qids = implode(',', $_REQUEST['qids']);
            if ($_REQUEST['actions']) {
                
                $query = db_query("update {question} set status='".$_REQUEST['actions']."' where qid in ($qids)");
                echo '<div class="success">Question updated successfully!</div>';
            } else {
              $query = db_query("delete from {question} where qid in ($qids)");
                echo '<div class="success">Question updated successfully!</div>';
                flag_quest_mail($_REQUEST['qids']);
            }
            
            panel_content('new');
            exit;
            break;
        case 'user':
            $query = "SELECT *,ifnull((select count(*) from {question_flags} where nodeid=u.uid AND type='user' group by nodeid),0) as fcnt  FROM {question_flags} as f  join {user_profile} as u  on f.nodeid=u.uid where f.type='user' ORDER BY f.flag_date DESC LIMIT 0,15";
            $list = ExecuteQuery($query, "select");
            
            $strReturn .= '
	<div id="qlist">
	<form id="qadmin" method="post" action="'.$gSitePath.'admin/panelc/ufsave" >
	<table width="98%" border="1" cellspacing="5" cellpadding="5">';
            foreach ($list as $quest) {
                $date = format_date_class($quest['flag_date'], date('Y-m-d H:i:s'));
                $strReturn .= '<tr><td>';
                $strReturn .= '<a href="#">'.wordwrap($quest['real_name'], 80, '<br/>').'</a>';
                $strReturn .= '</td><td>'.$quest['abuse_type'].'</td><td># Flag :'.$quest['fcnt'].'</td>';
                $strReturn .= '<td>'.$date.'</td><td>';
                
                $strReturn .= '<!--<b>/</b>&nbsp;<a href="'.$gSitePath.'question/edit/'.$quest['qid'].'">Edit</a>&nbsp;<b>/</b><a href="'.$gSitePath.'question/delete/'.$list[$i]['qid'].'">Delete</a>-->&nbsp;<input type="checkbox" class="check-me" name="qids[]" value="'.$quest['fid'].'" /> ';
                
                $strReturn .= '</td></tr>';
            
            }

            
            if (count($list) < 1) {
                //  drupal_set_message($message = 'No Questions Found!', $type = 'error');
                $strReturn .= ' <div class="error" align="left" >No Flagged User(s) Found!</div> ';
            } else {
                
                $strReturn .= '</table>
					<br/><div id="showbox" align="left" style="width:100%;display:none"><label for="reporttext"><b>Send Report Message :</b></label><br/><textarea name="reporttext" cols="55" row="17" id="reporttext"></textarea></div>
	<br/>
	<div align="left" style="width:100%" ><input type="hidden" id="actions" name="actions" value="1"/><input type="submit"  value="Ignore"/>&nbsp; <input onclick="admin_reject(0);" type="button" value="Reject"/>&nbsp; <span onclick="checkall(1);">Check All</span>&nbsp;<span onclick="checkall(0);">Uncheck All</span></div>
	</div></form><script>admin_approve();</script></div>';
            }
            
            break;
        case 'ufsave':
            
            $qids = implode(',', $_REQUEST['qids']);
            if ($_REQUEST['actions']) {
                
                $query = db_query("delete  from {question_flags} where type='user' AND fid in ($qids)");
                echo '<div class="success">User(s) updated successfully!</div>';
            } else {
                $query = db_query("update  {user} set status='0' where uid in ($qids)");
                flag_user_mail($_REQUEST['qids']);
                echo '<div class="success">User(s) updated successfully!</div>';
            
            }
            
            panel_content('user');
            exit;

            
            break;
    
    }

    
    echo $strReturn;


}


function flag_quest_mail($qids = '') {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    
     $from = variable_get('site_mail');
     $subject = 'Heardmentality Question Removal';
    $msg = $_REQUEST['reporttext'];
    foreach ($qids as $id) {

      
        $query = db_query("select u.mail,q.question  from {question} as q left join {users} as u on u.uid=q.uid where qid='$id' ");
        $det = db_fetch_object($query);
        
         $to = $det->mail;
         $msg .= '<br/>Question : '.$det->question.'<br/>';
        if(!empty($to)){
        	
			 $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
       
    }
return true;
}


function flag_user_mail($uids = '') {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    
     $from = variable_get('site_mail');
     $subject = 'Heardmentality Account Blocked';
    $msg = $_REQUEST['reporttext'];
    foreach ($qids as $id) {

      
        $query = db_query("select u.mail  from {users} where uid='$id' ");
        $det = db_fetch_object($query);
        
         $to = $det->mail;
        
        if(!empty($to)){
        	
			 $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
       
    }
return true;
}
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

      
        $query = db_query("select u.mail,u.uid,q.question  from {question} as q left join {users} as u on u.uid=q.uid where qid='$id' ");
        $det = db_fetch_object($query);
        
         $to = $det->mail;
		 $insert_notify=db_query("insert into notification (uid,admin_warning,is_user,node_id) values('".$det->uid."','1','1','".$det->uid."' ");
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
	
if(isset($_REQUEST['Inactive'])){
		
		 $ids=implode(',',$_REQUEST['qidsl']);
		if(!empty($ids)){
		db_query("update {question} set status='0' where qid in ($ids)");
		
		  drupal_set_message($message = 'Question InActivated  successfully!', $type = 'success');	
			
		}else{
			
		 drupal_set_message($message = 'Sorry no Waves Selected', $type = 'error');		
		}
		
	}
	
	
	if(isset($_REQUEST['Active'])){
		
		 $ids=implode(',',$_REQUEST['qidsl']);
		if(!empty($ids)){
		db_query("update {question} set status='1' where qid in ($ids)");
		
		  drupal_set_message($message = 'Question Activated  successfully!', $type = 'success');	
			
		}else{
			
		 drupal_set_message($message = 'Sorry no Waves Selected', $type = 'error');		
		}
		
	}
	 

	
	
	
$page_name="list"; 
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

$modquest.='<script type="text/javascript">
function checkall(val){


    $$(\'.check-me\').each(function(el){
        el.checked = val;
    });
    
}
</script>
	<form id="notify" method="post" action="" ><table width="100%" border="1">
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
	<td><a href="'.$gSitePath.'admin/edit/questions/'.$qid_result->qid.'">'.wordwrap($qid_result->question,"50","<br/>\n").'</a></td>
	
	<td>'.$uname.' </td>
	<td>'.$blockedst.' </td>
	<td><input type="checkbox" class="check-me" name="qidsl[]" value="'.$qid_result->qid.'" /> <a      onclick="loaddupe(\''.$gSitePath.'admin/dupe/questions/'.$qid_result->qid.'\',\'Dupe  Questions \'); ">Dupe </a> <a href="'.$gSitePath.'admin/edit/questions/'.$qid_result->qid.'">Edit </a> / <a href="'.$gSitePath.'admin/question/list?del='.$qid_result->qid.'"> Delete </a>/<a href="'.$gSitePath.'admin/view/question/'.$qid_result->qid.'"> View </a>  </td>
	</tr>';
	
	
	}
	
	
	$modquest.='</table><div><input type="submit" name="Inactive" value="Inactive" />   <input type="submit" name="Active" value="Active" /><span onclick="checkall(1);">Check All</span>&nbsp;<span onclick="checkall(0);">Uncheck All</span>';
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
	
drupal_goto('admin/question/list');
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

    
    $result = db_query("SELECT * FROM {question} as q left join {qtag} as t on q.qid=t.qid where q.qid='".$nid."' ");
    $quest = db_fetch_object($result);
  
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
<link rel="stylesheet" href="'.$gSitePath.'sites/all/modules/tagging/tagging.css" type="text/css" />
<script src="'.$gSitePath.drupal_get_path('module', 'question').'/scripts/question.js" type="text/javascript"></script>';
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
  
  <!--<tr>
    <td>&nbsp;</td>
    <td nowrap="nowrap">End Date<span title="This field is required." class="form-required">*</span></td>
    <td><input type="text" name="q_edate" autocomplete="off" id="q_edate" value="'.$quest->enddate.'"  /> <small>Eg: yyyy-mm-dd</small></td>
    <td><input name="invite_count" type="hidden" id="invite_count" value="1" /></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>-->
  <tr><td colspan="6">';
      $selmlist="select * from qtag as a, tagging as b where a.qid='$nid' and a.tag_id=b.tid ";
	 $mysqlfet=db_query($selmlist);
	
	
    $output .= '<tr><td colspan="6">'.get_tagging_edit($nid).'</td></tr>';

    
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
        
        $to = $det->mail;
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
	  $to = $usert->mail;
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
	 $to = $usert->mail;
         $msg = '<br/>Question : '.$det->question.' '.$delmsg.'<br/>';
		 
		 
		 
        if(!empty($to)){
        	
			 $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
       
   }
return true;
}
 function auto_suggest_quest() {
     
   global $gSitePath,$user,$gDocPath,$base_root;
  
           
				
				
				if(isset($_GET['getCountriesByLetters']) && isset($_GET['letters']) && isset($_GET['GetVal'])){
		 $letters = $_GET['letters'];
				//$letters = preg_replace("/[^a-z0-9 ]/si","",$letters);
	$where_condition="WHERE question LIKE CONVERT( _utf8 '%$letters%' USING latin1 ) COLLATE latin1_swedish_ci OR context LIKE CONVERT( _utf8 '$letters' USING latin1 )
	COLLATE latin1_swedish_ci and status='1'";
		
		if($_GET['GetVal']=="C1"){
			  $sql = "SELECT * FROM question   $where_condition";
			$res=mysql_query($sql);
			 $dir=mysql_num_rows($res);
			if($dir>0)
			{
				while($inf=mysql_fetch_array($res))
					echo " <a href='".$gSitePath."".$inf["url"]."' target='_blank'>".$inf["question"]."</a>|";
					}
			
		}
				} 
				
				
				
				
				
				
				
                
              
              
    
    }
	
	function dupe_question() {
      global $gSitePath,$user,$gDocPath,$base_root;
   $qaid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
              
                $query = db_query("select * from question  where qid='$qaid'  ");
				$detquest = db_fetch_object($query);
				  $q = $detquest->question;
				  
				  echo 'Dupe Search For '.$q.'<br/>';
                if (!$q)
                    return;
                $taglist = array();
                $urlm = array();
				$questionlm = array();
			$words = explode(" ",$q);
			for($i=0;$i<count($words);$i++){
			$samples= " ".$words[$i]."  ";
			//echo $samples;
			// $query = "SELECT * FROM question WHERE question LIKE ('$words[$i]%') or question LIKE ('%$words[$i]%') or  context LIKE ('%$words[$i]%') and status='0' ";
			 
			 
			 $query = " SELECT * FROM question WHERE question LIKE CONVERT( _utf8 '%$words[$i]%' USING latin1 ) COLLATE latin1_swedish_ci OR context LIKE CONVERT( _utf8 '%$words[$i]%' USING latin1 )
COLLATE latin1_swedish_ci and status='0'";
			 $myql_qry=db_query($query);
			while($mylist=db_fetch_array($myql_qry))
			{
			if($qaid!=$mylist['qid'])
			{
			array_push($questionlm, $mylist['qid']);
			}
			array_push($urlm, $mylist['url']);
			}

			}
			
		 $urldsi = array_unique($questionlm);
		 
		// echo count($urldsi);
		if(count($urldsi)!=0)
		{
		foreach ($urldsi as $value) {
		
		
		$querysquest = db_query("select * from question  where qid='$value'  ");
		$detquestqes = db_fetch_object($querysquest);
		$mlist = $detquestqes->question;
		echo '<a href="'.$detquestqes->url.'">'.$mlist.'</a><br>';
		}
        }
		else
		{
		
		echo "<b>No Dupe Questions</b>";
		
		}   
              
    
    }
	
	
	
	
	
	
	
	
	
	
	
	
	