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
	$list_err='';
    if (!empty($error)) {
        $list_err = implode("<br/>", $error['error']);
    }

    
    //print_r($_SESSION['post']);
    $q_quest = '';
    $optionlist = '';
    $q_context = '';
    $q_ans1 = '';
    $q_ans2 = '';
    if (isset($_SESSION['post'])&&!empty($_SESSION['post'])) {
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

	
	
	
	
				<script type="text/javascript">
				var spath=\''.$gSitePath.'\';
				window.setTimeout("setDefaultCountry()", 1000);
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
setDefaultCountry();
});
	
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
						
						
						}
							function get_city(code){
							
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
    $options = array('sortby' => 'countryname', 'sortorder' => 'ASC');
    $result = geonames_query('countryinfo',NULL,$options);
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
        <input type="text" name="q_quest" tabindex="1" value="'.$q_quest.'" id="q_quest"  size="100"/>    </td>
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
            <input tabindex="3" name="q_ans1" type="text" id="q_ans1" value="'.$q_ans1.'" size="40" />
          </td>
        </tr>
        <tr><td>&nbsp;</td></tr>
        <tr>
          <td>
            <input name="q_ans2" tabindex="4" type="text" id="q_ans2"  value="'.$q_ans2.'" size="40" />
			<p></p>
          </td>
        </tr>
        
        ';

    
    $output .= '</table><div id="add_more"></div><div id="del_ans" style="visibility:hidden;"><small><a href="javascript:void(0);" tabindex="88" onclick="del_ans();">[Remove]</a></div><small><br/>
	
	<input type="button" tabindex="13" name="Add" onclick="add_ans();" id="Add" value="Add Answer" /> <input type="hidden" name="ans_cnt" id="ans_cnt" value="2"><input type="hidden" id="cat1" name="cat1" value="">&nbsp;<input type="hidden" id="cat2" name="cat2" value="">&nbsp; <input type="hidden"  id="cat3" name="cat3" value=""> 
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
	
    <td width="13%"><!--<input type="text" name="q_state" id="q_state" value="State"  onblur="javascript: if(this.value == \'\') this.value=\'State\';" onfocus="javascript: if(this.value == \'State\') this.value=\'\';"   size="30"/>--> <div id="chg_state"></div></td>
	
    <td width="43%"><!--<input type="text" name="q_city" id="q_city" value="City" onblur="javascript: if(this.value == \'\') this.value=\'City\';" onfocus="javascript: if(this.value == \'City\') this.value=\'\';"    size="30"/>--><div id="chg_city"></div></td>  </tr>
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
    <td><input type="submit" name="save" tabindex="21" id="save" value="Save" /></td>
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
    $randomtag='';
    $content = '';
    $tagged = '';
	
	 $randomtag=popular_tag();
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
         increasepoints('1',$ins_id,'0');
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
            
				$q_tag=explode(',',$q_tag);
				
				//its in quset_lite.module
				process_tags($q_tag,$ins_id,0);
			
			
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

function myTruncate($string, $limit, $break = " ", $pad = "") {
    
    // return with no change if string is shorter than $limit
    if (strlen($string) <= $limit)
        return $string;
    $string = substr($string, 0, $limit);
    if (false !== ($breakpoint = strrpos($string, $break))) {
        $string = substr($string, 0, $breakpoint);
    }
    $string = str_replace("\"", "", $string);
    return $string.$pad;
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
						
						
						}
							function get_city(code){
							
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
                $ret = '<select tabindex="18"  style="width: 125px;"  onchange="get_city(this.value);" id="q_state" name="q_state"> ';
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
                $ret = '<select  tabindex="19"  style="width: 125px;"  id="q_city" name="q_city"> ';
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
				
				
				
				
				
                $qids=array_unique($qids);
              $qids= implode(',', $qids);
			  
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
                $tag .= '	<a class="taga" title="Add tag" href="#">
            	                    <div id="tagging-1" class="tagging-suggest-tag processed">
            	                        '.$ins.'</div></a>';

            
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
        
        $result = db_query("delete from {question} where qid='".$qid."' AND uid='".$user->uid."'");
        db_query("delete from {possible_answer} where qid='".$qid."'");
        if ($result)
            drupal_set_message(t('Question has been deleted successfully.'), $type = 'success');
        else
            drupal_set_message(t('sorry error Occurs, Try Again! .'), $type = 'error');
    }
    
    drupal_goto("question/");
}

