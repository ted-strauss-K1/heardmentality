<?php

	//my question
	
	
	function my_question(){
	
	global $gSitePath,$user, $gDocPath,$base_root;
	
	/*$client_select =db_query("SELECT *  FROM {question} where uid='".$user->uid."'");
	$client_array=array();
		$client_key=array();
		
			while($list=db_fetch_object($client_select))
			{
	
					$client_array[] = $list->cat_name;
					$client_key[]=$list->cat_id;
	
			}	
			*/
			
			$query="SELECT *  FROM {question} where uid='".$user->uid."'";
		$list=ExecuteQuery($query,"select");
		
		
			
	  
	 $strReturn.='<table width="98%" border="1" cellspacing="5" cellpadding="5">';
		for($i=0;$i<count($list);$i++){
	
			 $strReturn.='<tr><td>';
			 $strReturn.=$list[$i]['question'];
			 $strReturn.='</td><td>'.$list[$i]['date_added'].'</td><td>';
			 
			  $strReturn.='<a href="'.$gSitePath.'qlite/view/'.$list[$i]['qid'].'">View</a>&nbsp;<b>/</b>&nbsp;<a href="'.$gSitePath.'question/edit/'.$list[$i]['qid'].'">Edit</a> ';
			 
			  $strReturn.='</td></tr>';
			  
		}

		  $strReturn.='</table>';
		if(count($list)<1){
	drupal_set_message($message = 'No Questions Found!', $type = 'error');
		}
		
		return $strReturn;
	
	
	}
// question add

	function question_add(){
	
	
			global $gSitePath,$user, $gDocPath,$base_root;
				drupal_add_js('misc/firebug-lite-compressed.js');
				
			drupal_add_js('misc/jquery.js');
			drupal_add_js('misc/ui.core.min.js');
			
			drupal_add_js('misc/ui.datepicker.min.js');
			drupal_add_css('misc/themes/base/ui.all.css');
			$output.='
			
			 <script type="text/javascript">
  firebug.env.height = 100;
  </script>

				<script type="text/javascript" >
jQuery(function() {
		jQuery("#q_edate").datepicker({
			changeMonth: true,
			changeYear: true,minDate: \'1d\', dateFormat: \'yy-mm-dd\' 
		});

		
	});



function add_ans_field(){
 
}
 jQuery(document).ready(function(){
 
jQuery(\'#q_cat\').bind("change", function(){

      var foo = [];

      jQuery(\'#q_cat :selected\').each(function(i, selected){
   		
          foo[i] = jQuery(selected).val();
 
      });
 var str1 = foo.toString();
 var divid="chg_scat";
 jQuery(\'#cat1\').val(str1);
get_subcat(str1,divid,1);
 });
 
 jQuery(\'#q_scat\').bind("change", function(){

      var foo = [];

      jQuery(\'#q_cat :selected\').each(function(i, selected){
   		
          foo[i] = jQuery(selected).val();
 
      });
 var str2 = foo.toString();
 var divid="chg_sscat";
get_subcat(str2,divid,2);
 });
 
 
			  jQuery(\'#Add\').bind("click", function(){
			  
			  var ans_cnt=jQuery(\'#ans_cnt\').val();
		ans_cnt=++ans_cnt;
		jQuery(\'#ans_cnt\').val(ans_cnt);
		jQuery(\'#add_more\').slideUp();
		jQuery(\'#add_more\').append(\'  <p>&nbsp;</p>\');
		jQuery(\'#add_more\').append(\'  <div><input name="q_ans\'+ans_cnt+\'" type="text" id="q_ans\'+ans_cnt+\'" size="40" /></div>\');
		
		//jQuery(\'#add_more\').css("border", "1px solid red");
		jQuery(\'#add_more\').css("padding-top", "2px");
		jQuery(\'#add_more\').css("padding-bottom", "2px");
		jQuery(\'#add_more\').slideDown();
			  });
		
		  });

function get_subcat(ids,divid,level){

 		if(ids.length>0){
				jQuery.ajax({
		   type: "POST",
		   url: "'.$gSitePath.'question/ajax",
		   data: "action="+level+"&ids="+ids,
		   success: function(msg){
				  jQuery(\'#\'+divid+\'\').html(msg);
			 
		   }
		 });

}else{
 jQuery(\'#\'+divid+\'\').html(\'No Subcategory\');
}
}

function get_sscat(level){


 
 
if(level==1){

	 var foo = [];

      jQuery(\'#q_scat :selected\').each(function(i, selected){
   		
          foo[i] = jQuery(selected).val();
 
      });
 var str2 = foo.toString();



jQuery(\'#cat2\').val(str2);
 var divid="chg_sscat";
get_subcat(str2,divid,2);
}else{

		
	 var foo = [];

      jQuery(\'#q_sscat :selected\').each(function(i, selected){
   		
          foo[i] = jQuery(selected).val();
 
      });
 var str2 = foo.toString();

jQuery(\'#cat3\').val(str2);
}
}
</script>
			
			';
			
		$output.= '
				<form id="question" name="question" method="post" action="'.$gSitePath.'question/save" ><table width="100%" border="0" align="center" style="border:0px;">
  <tr>
    <td width="0%" height="94">&nbsp;</td>
    <td width="14%">Question<span title="This field is required." class="form-required">*</span></td>
    <td colspan="4">
        <input type="text" name="q_quest" id="q_quest"  size="150"/>    </td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td>Context</td>
    <td colspan="4">
      <textarea name="q_context" id="q_context" cols="150" rows="2" style="border:1px solid #BBBBBB;

width:775px; scroll;"></textarea>  </td>
  </tr>
  
  <tr>
    <td>&nbsp;</td>
    <td>Answer<span title="This field is required." class="form-required">*</span></td>
    <td width="17%"><table width="100%" border="0"> <tr>
          <td>
            <input name="q_ans1" type="text" id="q_ans1" size="40" />
          </td>
        </tr>
        <tr><td>&nbsp;</td></tr>
        <tr>
          <td>
            <input name="q_ans2" type="text" id="q_ans2" size="40" />
          </td>
        </tr>
        
        ';
    
        
    $output.='</table><div id="add_more"></div></td>
    <td colspan="3"><table width="100%" border="0">
      <tr>
        <td><select name="q_cat[]" id="q_cat" multiple="multiple"  size="5"><option value="">Select Category</option>'; 
		$client_select =db_query("SELECT cat_id,cat_name FROM {category} where parent_id='0'");
      while($list=db_fetch_object($client_select))
					{
		$output.= '<option value="'.$list->cat_id.'">'.$list->cat_name.'</option>';
		
		}			
					
      $output.='</select></td>
        <td><div id="chg_scat"><select name="q_scat[]" id="q_scat" multiple="multiple"  size="5"><option value="">Select Sub Category</option>';
		$client_select1 =db_query("SELECT cat_id,cat_name FROM {category} where parent_id='0'");
    while($list=db_fetch_object($client_select1))
					{
		$output.= '<option value="'.$list->cat_id.'">'.$list->cat_name.'</option>';
		
		}	 $output.='</select></div></td>
        <td><div id="chg_sscat"><select name="q_sscat[]" id="q_sscat" multiple="multiple"  size="5"><option value="">Select Sub Sub Category</option>';
     $client_select2 =db_query("SELECT cat_id,cat_name FROM {category} where parent_id='0'");
    while($list=db_fetch_object($client_select2))
					{
		$output.= '<option value="'.$list->cat_id.'">'.$list->cat_name.'</option>';
		
		}	 $output.='</select></div></td>
      </tr>
    </table></td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>
       <input type="button" name="Add" id="Add" value="Add Answer" /> <input type="hidden" name="ans_cnt" id="ans_cnt" value="2"><input type="hidden" id="cat1" name="cat1" value="">&nbsp;<input type="hidden" id="cat2" name="cat2" value="">&nbsp; <input type="hidden"  id="cat3" name="cat3" value=""> </td>
    <td width="13%"><input type="text" name="q_country" id="q_country" value="country" size="30" /></td>
    <td width="13%"><input type="text" name="q_state" id="q_state" value="state"  size="30"/></td>
    <td width="43%"><input type="text" name="q_city" id="q_city" value="city"  size="30"/></td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
  
  <tr>
    <td>&nbsp;</td>
    <td nowrap="nowrap">End Date<span title="This field is required." class="form-required">*</span></td>
    <td><input type="text" name="q_edate" autocomplete="off" id="q_edate" /></td>
    <td><input name="invite_count" type="hidden" id="invite_count" value="1" /></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td height="42">&nbsp;</td>
    <td>&nbsp;</td>
    <td><input type="submit" name="save" id="save" value="Save" /></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td align="right"></td>
  </tr>
</table>
</form>

';

    return $output;


	
	}

function question_save()
{

global $user;

	$q_quest='';
//print_r($_REQUEST);
	extract($_REQUEST);
	$output='';
	
	  if (!empty($q_quest)&&!empty($q_ans1)&&!empty($q_ans2)&&!empty($q_edate)) {
	  $edate=$q_edate;
		 $result =   db_query("INSERT INTO {question} (uid,question,context,cid,scid,sscid,global,country,state,city,enddate) VALUES (%d,'%s','%s','%s','%s','%s','%s','%s','%s', '%s','%s')", $user->uid,$q_quest,$q_context,$cat1,$cat2,$cat3,$q_global,$q_country,$q_state,$q_city,$edate);
		
		 $ins_id=db_last_insert_id('question','qid');
		 for($i=1;$i<=$ans_cnt;$i++)
		 {
			 $name="q_ans".$i;
			 if(!empty($$name))
			 	{
				  $result =   db_query("INSERT INTO {possible_answer} (qid,answer) VALUES (%d,'%s')",$ins_id,$$name);
				}
		 }
		 
		 if($result)
		 drupal_set_message(t('Thank you, Question added successfully!'), $type = 'success');
		 
		  }
		   else {
		   
				drupal_set_message($message = 'Sorry, Some Of The required fields are Empty!', $type = 'error');
				drupal_goto("question/add");
		  }
	
	return $output;
}


	function question_edit_save($array){
	
		global $gSitePath,$user, $gDocPath,$base_root;
			  $nid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
			  
			//  print_r($array);
	extract($array);
	$output='';
	
	  if (!empty($q_quest)&&!empty($q_ans1)&&!empty($q_ans2)&&!empty($q_edate)&&!empty($cat1)) {
	  $edate=$q_edate;
		 $result =   db_query("update {question} set question='$q_quest',context='$q_context',cid='$cat1',scid='$cat2',sscid='$cat3',	 global='$q_global',country='$q_country',state='$q_state',city='$q_city',enddate='$edate' where qid='".$nid."' AND uid='".$user->uid."'");
		
		 $ins_id=db_last_insert_id('question','qid');
		 for($i=1;$i<=$ans_cnt;$i++)
		 {
			 $name="q_ans".$i;
			 $aid="aid".$i;
			 if(!empty($$name))
			 	{
				
						if(!empty($$aid)){
						  $result =   db_query("UPDATE {possible_answer} set answer='".$$name."' where paid='".$$aid."' AND qid='".$nid."'");
						}else{
						
						  $result =   db_query("INSERT INTO {possible_answer} (qid,answer) VALUES (%d,'%s')",$ins_id,$$name);
						  }
				}
		 }
		 
		 if($result)
		 drupal_set_message(t('Thank you, Question updated successfully!'), $type = 'success');
		 drupal_goto("question/");
		  }
		   else {
		   
				drupal_set_message($message = 'Sorry, Some Of The required fields are Empty!', $type = 'error');
				
		  }
	
	return $output;
	}



function edit_question(){



	
	
			global $gSitePath,$user, $gDocPath,$base_root;
			
				
			drupal_add_js('misc/jquery.js');
			drupal_add_js('misc/ui.core.min.js');
			
			drupal_add_js('misc/ui.datepicker.min.js');
			drupal_add_css('misc/themes/base/ui.all.css');
			
			if(isset($_POST['update'])){
			
			question_edit_save($_POST);
			}
			
			
			$output.='
		
		<script type="text/javascript" >
		
							jQuery(function() {
									jQuery("#q_edate").datepicker({
										changeMonth: true,
										changeYear: true,minDate: \'1d\', dateFormat: \'yy-mm-dd\' 
									});
							
									
								});
							


						function add_ans_field(){
						 
						}
						 jQuery(document).ready(function(){
						 
						jQuery(\'#q_cat\').bind("change", function(){
						
							  var foo = [];
						
							  jQuery(\'#q_cat :selected\').each(function(i, selected){
								
								  foo[i] = jQuery(selected).val();
						 
							  });
						 var str1 = foo.toString();
						 var divid="chg_scat";
						 jQuery(\'#cat1\').val(str1);
						get_subcat(str1,divid,1);
						 });
 
						 jQuery(\'#q_scat\').bind("change", function(){
						
							  var foo = [];
						
							  jQuery(\'#q_cat :selected\').each(function(i, selected){
								
								  foo[i] = jQuery(selected).val();
						 
							  });
						 var str2 = foo.toString();
						 var divid="chg_sscat";
						get_subcat(str2,divid,2);
						 });
						 
 
						  jQuery(\'#Add\').bind("click", function(){
						  
						  var ans_cnt=jQuery(\'#ans_cnt\').val();
					ans_cnt=++ans_cnt;
					jQuery(\'#ans_cnt\').val(ans_cnt);
					jQuery(\'#add_more\').slideUp();
					jQuery(\'#add_more\').append(\'  <p>&nbsp;</p>\');
					jQuery(\'#add_more\').append(\'  <div><input name="q_ans\'+ans_cnt+\'" type="text" id="q_ans\'+ans_cnt+\'" size="40" /></div>\');
					
					//jQuery(\'#add_more\').css("border", "1px solid red");
					jQuery(\'#add_more\').css("padding-top", "2px");
					jQuery(\'#add_more\').css("padding-bottom", "2px");
					jQuery(\'#add_more\').slideDown();
						  });
					
					  });

					function get_subcat(ids,divid,level){
					
							if(ids.length>0){
									jQuery.ajax({
							   type: "POST",
							   url: "'.$gSitePath.'question/ajax",
							   data: "action="+level+"&ids="+ids,
							   success: function(msg){
									  jQuery(\'#\'+divid+\'\').html(msg);
								 
							   }
							 });
					
					}else{
					 jQuery(\'#\'+divid+\'\').html(\'No Subcategory\');
					}
					}

						function get_sscat(level){
						
						if(level==1){
						
							 var foo = [];
						
							  jQuery(\'#q_scat :selected\').each(function(i, selected){
								
								  foo[i] = jQuery(selected).val();
						 
							  });
						 var str2 = foo.toString();
						
						
						
						jQuery(\'#cat2\').val(str2);
						 var divid="chg_sscat";
						get_subcat(str2,divid,2);
						}else{
						
								
							 var foo = [];
						
							  jQuery(\'#q_sscat :selected\').each(function(i, selected){
								
								  foo[i] = jQuery(selected).val();
						 
							  });
						 var str2 = foo.toString();
						
						jQuery(\'#cat3\').val(str2);
						}
						}
		</script>
			
			';
			
			
			  $nid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
		
		
		  $result = db_query("SELECT * FROM {question} where qid='".$nid."' AND uid='".$user->uid."'");
			 $quest=db_fetch_object($result);
			
		$output.= '
				<form id="question" name="question" method="post"  ><table width="100%" border="0" align="center" style="border:0px;">
  <tr>
    <td width="0%" height="94">&nbsp;</td>
    <td width="14%">Question<span title="This field is required." class="form-required">*</span></td>
    <td colspan="4">
        <input type="text" name="q_quest" id="q_quest" value="'.$quest->question.'"  size="150"/>    </td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td valign="top">Context</td>
    <td colspan="4">
      <textarea name="q_context" id="q_context" cols="150" rows="2" style="border:1px solid #BBBBBB;

width:775px; scroll;">'.$quest->context.'</textarea>  </td>
  </tr>
  <tr><td>&nbsp;</td></tr>
    <tr>
    <td>&nbsp;</td>
    <td valign="top">Answer<span title="This field is required." class="form-required">*</span></td>
    <td width="17%"><table width="100%" border="0">';
	
	
        $query = "SELECT * FROM {possible_answer} where qid='".$nid."' ";
			 $ans=ExecuteQuery($query,"select"); 
			 $i=1;
			foreach($ans as $array){ 
	
	$output.=' <tr>
          <td>
            <input name="q_ans'.$i.'" type="text" id="q_ans'.$i.'" size="40" value="'.$array['answer'].'" />&nbsp;<input type="hidden" name="aid'.$i.'" value="'.$array['paid'].'">
          </td>
        </tr>
        <tr><td>&nbsp;</td></tr>
          ';
		  $i++;
    }
			 
			 
    $output.='</table><div id="add_more"></div></td>
    <td colspan="3"><table width="100%" border="0">

      <tr>
        <td><select name="q_cat[]" id="q_cat" multiple="multiple"  size="5"><option value="">Select Category</option>'; 
		$client_select =db_query("SELECT cat_id,cat_name FROM {category} where parent_id='0'");
		 $ecat1=explode(",",$quest->cid);
		
      while($list=db_fetch_object($client_select))
					{
					if (in_array($list->cat_id, $ecat1)) {
					$sel='SELECTED="SELECTED"';
				}else{
				$sel='';
				}
		$output.= '<option value="'.$list->cat_id.'" '.$sel.'>'.$list->cat_name.'</option>';
		
		}			
					
      $output.='</select></td>
        <td><div id="chg_scat"><select name="q_scat[]" id="q_scat" multiple="multiple"  size="5"><option value="">Select Sub Category</option>';
		$client_select1 =db_query("SELECT cat_id,cat_name FROM {category} where parent_id IN ('".$quest->cid."')");
		 $ecat2=explode(",",$quest->scid);
    while($list=db_fetch_object($client_select1))
					{
					if (in_array($list->cat_id, $ecat2)) {
					$sel='SELECTED="SELECTED"';
				}else{
				$sel='';
				}
					
					
		$output.= '<option value="'.$list->cat_id.'" '.$sel.'>'.$list->cat_name.'</option>';
		
		}	 $output.='</select></div></td>
        <td><div id="chg_sscat"><select name="q_sscat[]" id="q_sscat" multiple="multiple"  size="5"><option value="">Select Sub Sub Category</option>';
     $client_select2 =db_query("SELECT cat_id,cat_name FROM {category} where parent_id IN ('".$quest->scid."')");
	  $ecat3=explode(",",$quest->sscid);
    while($list=db_fetch_object($client_select2))
					{
						if (in_array($list->cat_id, $ecat3)) {
					$sel='SELECTED="SELECTED"';
				}else{
				$sel='';
				}
					
					
		$output.= '<option value="'.$list->cat_id.'" '.$sel.'>'.$list->cat_name.'</option>';
		
		}	 $output.='</select></div></td>
      </tr>
    </table></td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>
       <input type="button" name="Add" id="Add" value="Add Answer" /> <input type="hidden" name="ans_cnt" id="ans_cnt" value="'.count($ans).'"><input type="hidden" id="cat1" name="cat1" value="'.$quest->cid.'">&nbsp;<input type="hidden" id="cat2" name="cat2" value="'.$quest->scid.'">&nbsp; <input type="hidden"  id="cat3" name="cat3" value="'.$quest->sscid.'"> </td>
 <td width="13%"><input type="text" name="q_country" id="q_country" value="'.$quest->country.'" size="30" /></td>
    <td width="13%"><input type="text" name="q_state" id="q_state" value="'.$quest->state.'"  size="30"/></td>
    <td width="43%"><input type="text" name="q_city" id="q_city" value="'.$quest->city.'"  size="30"/></td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
  
  <tr>
    <td>&nbsp;</td>
    <td nowrap="nowrap">End Date<span title="This field is required." class="form-required">*</span></td>
    <td><input type="text" name="q_edate" autocomplete="off" id="q_edate" value="'.$quest->enddate.'" /></td>
    <td><input name="invite_count" type="hidden" id="invite_count" value="1" /></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td height="42">&nbsp;</td>
    <td>&nbsp;</td>
    <td><input type="submit" name="update" id="save" value="Update" /></td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td align="right"></td>
  </tr>
</table>
</form>

';

    return $output;


	
	

}


		function question_ajax(){
		//print_r($_REQUEST);
			$ret='';
		extract($_REQUEST);
			$client_select =db_query("SELECT cat_id,cat_name FROM {category} where parent_id IN ($ids)");
		
		$client_array=array();
		$client_key=array();
		
			while($list=db_fetch_object($client_select))
			{
	
					$client_array[] = $list->cat_name;
					$client_key[]=$list->cat_id;
	
			}
			if(!empty($client_array)){
			
			if($action==1)
			$qscat="q_scat";
			if($action==2)
			$qscat="q_sscat";
			
			$ret='<select size="5" multiple="multiple" onchange="get_sscat('.$action.');" id="'.$qscat.'" name="q_scat[]"> ';
		for($i=0;$i<count($client_array);$i++){
		
		$ret.='<option value="'.$client_key[$i].'">'.$client_array[$i].'</option>';
	
	}
	$ret.="</select>";
	
	}else{
	$ret.='No Subcategory';
	}
		echo $ret;
			exit;
		
		}