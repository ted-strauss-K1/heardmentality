<?php

function add_points()
{
global $gSitePath,$user, $gDocPath,$base_root,$base_path;
	

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
  </tr>';
  $query = "SELECT * FROM tbl_points limit 0, 6 "; 
	 $vlist = ExecuteQuery($query, "select");
  for($k=0;$k<6;$k++)
	{
	$pid=$vlist[$k]['id'];
 $addoutput.=' <tr>
    <td width="46%" height="37">'.$vlist[$k]['point_type'].'</td>
    <td width="54%">
      <input type="text" onkeypress="return isNumberKey(event)" name="qusetion_points'.$pid.'" id="qusetion_points'.$pid.'" size="7" value='.$vlist[$k]['points'].' />
   </td>
  </tr>';
  
  
  
  }
  
 /* <tr>
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
  </tr>';*/
   $querys= "SELECT * FROM tbl_vote_gurupoints  "; 
	 $vlistm = ExecuteQuery($querys, "select");
	 for($k=0;$k<count($vlistm);$k++)
	 { 
	 $vid=$vlistm[$k]['id'];
	 $ptstart=$vlistm[$k]['vstart'];
	 $ptend=$vlistm[$k]['vend'];
	 $ptpoints=$vlistm[$k]['points'];
   $addoutput.='<tr>
      <td height="43">Created question Vote Range Points '.$vid.'  </td>
    
	 <td><input type="text" name="from'.$vid.'" id="from'.$vid.'" size="3" value='.$ptstart.' onkeypress="return isNumberKey(event)" /> -
        <input type="text" name="to'.$vid.'" id="to'.$vid.'" size="3" value='.$ptend.' onkeypress="return isNumberKey(event)" />
        <input type="text" name="votepts'.$vid.'" id="votepts'.$vid.'" size="5" value='.$ptpoints.' onkeypress="return isNumberKey(event)" /> 
		
		
		
		
		
		
		
		
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



   function user_points()
   {
  
	$user_pt = "SELECT a.uid, a.name, a.mail, SUM(b.points) AS point FROM users as a LEFT OUTER JOIN tbl_user_points as b ON a.uid = b.uid GROUP BY uid  "; 

	 $point_list = ExecuteQuery($user_pt, "select");
   
   $outputppt='<form name="lname" method="post" ><table width="100%" border="1" cellspacing="0" cellpadding="0">
   
   
  <tr>
    <td>User</td>
    <td>Post Qusetion Points</td>
	<td>Answering a question</td>
	<td>Have a post liked</td>
	<td>Flagging a question</td>
	<td>Subscribing a friend</td>
	<td>Number of followers</td>
	<td>Created question Vote Values</td>
    <td>Total Points</td>
  </tr>';
  for($p=0;$p<count($point_list);$p++)
	{
	
	$puid=$point_list[$p]['uid'];
	
	   $qptstd="select SUM(points) AS qpt   FROM tbl_user_points where  uid=".$puid." and point_id='1' group by uid";
	  // $qrylist = ExecuteQuery($qptstd, "select");
	 $voteqrylist = db_query($qptstd);
    $fetqrylist = db_fetch_array($voteqrylist);
	
	
	     $qptstd2="select SUM(points) AS qpt   FROM tbl_user_points where  uid=".$puid." and point_id='2' group by uid";
	  // $qrylist2 = ExecuteQuery($qptstd2, "select");
	  $voteqrylist2 = db_query($qptstd2);
    $fetqrylist2 = db_fetch_array($voteqrylist2);
	$pt1=$fetqrylist2['qpt'];
	
	 $qptstd3="select SUM(points) AS qpt   FROM tbl_user_points where  uid=".$puid." and point_id='3' group by uid";
	  // $qrylist3 = ExecuteQuery($qptstd3, "select");
	   
	    $voteqrylist3 = db_query($qptstd3);
    $fetqrylist3 = db_fetch_array($voteqrylist3);
	$pt2=$fetqrylist3['qpt'];
	  
	   
	   $qptstd4="select SUM(points) AS qpt   FROM tbl_user_points where  uid=".$puid." and point_id='4' group by uid";
	  // $qrylist4 = ExecuteQuery($qptstd4, "select");
	  //$pt3=$qrylist4[0]['qpt'];
	    $voteqrylist4 = db_query($qptstd4);
    $fetqrylist4 = db_fetch_array($voteqrylist4);
	$pt3=$fetqrylist4['qpt'];
	  
	$qptstd5="select SUM(points) AS qpt   FROM tbl_user_points where  uid=".$puid." and point_id='5' group by uid";
	   //$qrylist5 = ExecuteQuery($qptstd5, "select");
	   //$pt4=$qrylist5[0]['qpt'];
	    $voteqrylist5 = db_query($qptstd5);
    $fetqrylist5 = db_fetch_array($voteqrylist5);
	$pt4=$fetqrylist5['qpt'];
	   
	   $qptstd6="select SUM(points) AS qpt   FROM tbl_user_points where  uid=".$puid." and point_id='6' group by uid";
	  // $qrylist6 = ExecuteQuery($qptstd6, "select");
	   // $pt5=$qrylist6[0]['qpt'];
		
		$voteqrylist6 = db_query($qptstd6);
		$fetqrylist6 = db_fetch_array($voteqrylist6);
		$pt5=$fetqrylist6['qpt'];
	   if($point_list[$p]['point']=='')
	$pt='0';
	else
	$pt=$point_list[$p]['point'];
	$spt=$fetqrylist['qpt'];
	   $vtpt=$pt-($spt+$pt1+$pt2+$pt3+$pt4+$pt5);
	
  $outputppt.=' <tr>
	<td>'.$point_list[$p]['name'].'</td>
	<td>'.$spt.'</td>
	<td>'.$pt1.'</td>
	<td>'.$pt2.'</td>
	<td>'.$pt3.'</td>
	<td>'.$pt4.'</td>
	<td>'.$pt5.'</td>
	<td>'.$vtpt.'</td>
	<td>'.$pt.'</td>
  </tr>';
  
  }
$outputppt.='</table></form>';
   
   return $outputppt;
   
   
   
   }






?>