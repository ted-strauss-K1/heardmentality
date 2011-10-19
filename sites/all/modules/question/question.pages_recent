<?php

	
	
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
get_subcat(str1);
 });
 
 
 
      jQuery(\'#Add\').bind("click", function(){
	  
	  var ans_cnt=jQuery(\'#ans_cnt\').val();
ans_cnt=++ans_cnt;
jQuery(\'#ans_cnt\').val(ans_cnt);
jQuery(\'#add_more\').slideUp();
jQuery(\'#add_more\').append(\'  <p>&nbsp;</p>\');
jQuery(\'#add_more\').append(\'  <div><input name="q_ans\'+ans_cnt+\'" type="text" id="q_ans\'+ans_cnt+\'" size="40" /></div>\');

jQuery(\'#add_more\').css("border", "1px solid red");
jQuery(\'#add_more\').css("padding-top", "2px");
jQuery(\'#add_more\').css("padding-bottom", "2px");
jQuery(\'#add_more\').slideDown();
	  });

  });

function get_subcat(ids){

 		alert(ids);
		jQuery.ajax({
   type: "POST",
   url: "'.$gSitePath.'question/ajax",
   data: "action=scat&ids="+ids,
   success: function(msg){
   	      jQuery(\'#chg_scat\').html(msg);
	 
   }
 });

		


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
        <td><select name="q_sscat[]" id="q_sscat" multiple="multiple"  size="5"><option value="">Select Sub Sub Category</option>';
     $client_select2 =db_query("SELECT cat_id,cat_name FROM {category} where parent_id='0'");
    while($list=db_fetch_object($client_select2))
					{
		$output.= '<option value="'.$list->cat_id.'">'.$list->cat_name.'</option>';
		
		}	 $output.='</select></td>
      </tr>
    </table></td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>
       <input type="button" name="Add" id="Add" value="Add Answer" /> <input type="hidden" name="ans_cnt" id="ans_cnt" value="2">  </td>
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
	 echo $edate=$q_edate;
		 $result =   db_query("INSERT INTO {question} (uid,question,context,cid,scid,sscid,global,country,state,city,enddate) VALUES (%d,'%s','%s','%s','%s','%s','%s','%s','%s', '%s','%s')", $user->uid,$q_quest,$q_context,$q_cid,$q_scid,$q_sscid,$q_global,$q_country,$q_state,$q_city,$time,$edate);
		
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


		function question_ajax(){
		print_r($_REQUEST);
		extract($_REQUEST);
			$client_select =db_query("SELECT cat_id,cat_name FROM {category} where parent_id IN ('$ids')");
		
		$client_array=array();
		$client_key=array();
		
			while($list=db_fetch_object($client_select))
			{
	
					$client_array[] = $list->cat_name;
					$client_key[]=$list->cat_id;
	
			}
			
			$ret='<select size="5" multiple="multiple" id="q_scat" name="q_scat[]"> ';
		for($i=0;$i<count($client_array);$i++){
		
		$ret.='<option value="'.$client_key[$i].'">'.$client_array[$i].'</option>';
	
	}
	$ret.="</select>";
		return $ret;
			exit;
		
		}