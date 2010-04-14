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
    <td width="46%" height="37"></td>
    <td width="54%">
      Points
   </td>
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
  </tr>';
   $querys= "SELECT * FROM tbl_vote_gurupoints  "; 
	 $vlistm = ExecuteQuery($querys, "select");
	 for($k=0;$k<count($vlistm);$k++)
	 { 
	 
   $addoutput.='<tr>
      <td height="43">Created question Vote Range Points '.$vlistm[$k][id].'  </td>
    
	 <td><input type="text" name="from'.$vlistm[$k][id].'" id="from'.$vlistm[$k][id].'" size="3" value='.$vlistm[$k][vstart].' onkeypress="return isNumberKey(event)" /> -
        <input type="text" name="to'.$vlistm[$k][id].'" id="to'.$vlistm[$k][id].'" size="3" value='.$vlistm[$k][vend].' onkeypress="return isNumberKey(event)" />
        <input type="text" name="votepts'.$vlistm[$k][id].'" id="votepts'.$vlistm[$k][id].'" size="5" value='.$vlistm[$k][points].' onkeypress="return isNumberKey(event)" /> 
		
		
		
		
		
		
		
		
		</td>
		
    </tr>';
	}
	$addoutput.='<tr>
      <td height="43"><a class="cursor_txt"   onClick="showhidem(\'showid\');"> Add Vote Points </a> </td>
    
	 <td> <div  id="showid" style="display:none;"><input type="text" name="fromr" id="fromr" size="3"  onkeypress="return isNumberKey(event)" /> -
        <input type="text" name="tor" id="tor" size="3" onkeypress="return isNumberKey(event)" />
        <input type="text" name="voteptsr" id="voteptsr" size="5" onkeypress="return isNumberKey(event)" /> 
		
		<input type="submit" name="Add" Value="Add"  /> 
		
		</div>
		
		
		
		
		</td>
		
    </tr>';
	
	 $addoutput.='<tr>
    <td></td>
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
		$valm="qusetion_points".$m;
		$qpt=$_REQUEST[$valm];
		$updatevoteposs="update  tbl_points set points='$qpt' where id=$m ";
		db_query($updatevoteposs);
		
		
		}
		$quetb= "SELECT * FROM tbl_vote_gurupoints  "; 
		 $gpoint= ExecuteQuery($quetb, "select");
		 echo count($gpoint);
		for($i=1;$i<=count($gpoint);$i++)
		{
		$fromt="from".$i;
		$fromp=$_REQUEST[$fromt];
		$tot="to".$i;
		$topin=$_REQUEST[$tot];
		$vtpts="votepts".$i;
		$vtptsy=$_REQUEST[$vtpts];
		
		 $updateguru="update  tbl_vote_gurupoints set vstart=$fromp ,vend=$topin, points='$vtptsy' where id=$i ";
		db_query($updateguru);
		
		
		}
	
	
	
	
	  $queryd = "SELECT id from {tbl_vote_gurupoints} order by id DESC limit 0,1 ";
		  $pointstb = db_query($queryd);
	 $idm = db_result($pointstb);
	 
	// echo $idm;
	
		if($_REQUEST['Add'])
		{
		
		  $insertsql="insert into  tbl_vote_gurupoints (vstart,vend,points) values('".$_REQUEST['fromr']."','".$_REQUEST['tor']."','".$_REQUEST['voteptsr']."')";
			 db_query($insertsql);
		
		}
		
		
		
		
			drupal_goto("admin/addpoints");
		drupal_set_message(t('Settings Have Been Saved successfully!'), $type = 'success'); 
		$msg="Updated Successfully";
		
		return $msg;
		
		
		
		
		}


?>