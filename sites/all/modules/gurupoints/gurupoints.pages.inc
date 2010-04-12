<?php

function add_points()
{
global $gSitePath,$user, $gDocPath,$base_root,$base_path;
	$query = "SELECT * FROM tbl_points  "; 
	 $vlist = ExecuteQuery($query, "select");
     $cnt_ans = count($vlist);
    $array_get=array();
	for($k=0;$k<6;$k++)
	{
	array_push($array_get, $vlist[$k]['points']);
	}
//print_r($array_get);

	$addoutput='<SCRIPT language=Javascript>
   
      function isNumberKey(evt)
      {
         var charCode = (evt.which) ? evt.which : event.keyCode
         if (charCode > 31 && (charCode < 48 || charCode > 57))
            return false;

         return true;
      }
   
   </SCRIPT><script src="'.$gSitePath.'sites/all/modules/gurupoints/scripts/add.js" type="text/javascript"></script>
<form id="point" name="point" method="post" action="'.$gSitePath.'admin/point/save"  ><div id="err" class="clear"></div> <table width="100%" border="0" cellspacing="0" cellpadding="0">
 <tr>
    <td width="46%" height="37"> <b style="color:red">*Only Numbers are allowed in  boxes </b> </td>
    <td width="54%"></td>
  </tr>
  <tr>
    <td width="46%" height="37">Creating a question</td>
    <td width="54%">
      <input type="text" onkeypress="return isNumberKey(event)" name="qusetion_points1" id="qusetion_points1" size="7" value='.$array_get[0].' />
   </td>
  </tr>
  
  <tr>
    <td height="35">Answering a question</td>
    <td><input type="text" onkeypress="return isNumberKey(event)" name="qusetion_points2" id="qusetion_points2" size="7" value='.$array_get[1].'  /></td>
  </tr>
  <tr>
    <td height="33">Have a post liked</td>
    <td><input type="text" onkeypress="return isNumberKey(event)" name="qusetion_points3" id="qusetion_points3" size="7" value='.$array_get[2].' /></td>
  </tr>
  <tr>
    <td height="35">Flagging a question or user that is ultimately removed</td>
    <td><input type="text" onkeypress="return isNumberKey(event)" name="qusetion_points4" id="qusetion_points4" size="7" value='.$array_get[3].' /></td>
  </tr>
  <tr>
    <td height="30">Subscribing a friend</td>
    <td><input type="text" onkeypress="return isNumberKey(event)" name="qusetion_points5" id="qusetion_points5" size="7" value='.$array_get[4].' /></td>
  </tr>
  <tr>
    <td height="34">Followers Points</td>
    <td><input type="text" onkeypress="return isNumberKey(event)" name="qusetion_points6" id="qusetion_points6" size="7" value='.$array_get[5].' /></td>
  </tr>
    <tr>
      <td height="43">Created question Vote Values </td>
      <td><input type="text" name="from" id="from" size="3" onkeypress="return isNumberKey(event)" /> -
        <input type="text" name="to" id="to" size="3" onkeypress="return isNumberKey(event)" />
        <input type="text" name="votepts" id="votepts" size="5" onkeypress="return isNumberKey(event)" /></td>
    </tr>
	
	  <tr>
    <td><input type="button" tabindex="13" name="Add" onclick="add_ans();" id="Add" value="Add More" /> <input type="hidden" name="ans_cnt" id="ans_cnt" value="0"></td>
    <td>
	
    <tr>
    <td><div id="add_more"></div></td>
    <td>
      <input type="submit" name="button" id="button" value="Update" />
   </td>
  </tr>
</table>
</form>';
return $addoutput;
}
function save_points()
		{
		
		global $gSitePath,$user, $gDocPath,$base_root;
		
		
	
		for($m=1;$m<7;$m++)
		{
		echo $valm="qusetion_points".$m;
		$qpt=$_REQUEST[$valm];
		echo  $updatevoteposs="update  tbl_points set points='$qpt' where id=$m ";
			 db_query($updatevoteposs);
		
			
		}
		drupal_goto("admin/addpoints");
		drupal_set_message(t('Settings Have Been Saved successfully!'), $type = 'success'); 
		$msg="Updated Successfully";
		
		return $msg;
		}


?>