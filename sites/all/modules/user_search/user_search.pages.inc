<?php

function search_results()
{
global $gSitePath,$user, $gDocPath,$base_root,$base_path;

$flink='';
$fetresult='';
extract($_REQUEST);
$page_name="searchuser"; //  If you use this code with a different page ( or file ) name then change this 
if(isset($_GET['start']))
{
$start=$_GET['start'];
}
else
{
$start='';
}
if(strlen($start) > 0 and !is_numeric($start)){
echo "Data Error";
exit;
}


$eu = ($start - 0); 
$limit = 5;                                 // No of records to be shown per page.
$this1 = $eu + $limit; 
$back = $eu - $limit; 
$next = $eu + $limit; 
$fetresult = '<script type="text/javascript">
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
	
				
				 function get_profile_details(urid){
						//alert(urid);
						var url = "'.$gSitePath.'userinfo";
									var req = new Request({    
											method: \'get\'
											,url: url
											,data: {\'getuid\':urid },
											onRequest: function() { },
											onComplete: function(response) {
													 $(\'user_info\').set(\'html\', response);
											}
									}).send();
						
						
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
						
							var url = "'.$gSitePath.'userresults";
									var req = new Request({    
											method: \'get\'
											,url: url
											,data: { \'action\':1,\'code\':code},
											onRequest: function() { },
											onComplete: function(response) {
													 $(\'container-user\').set(\'html\', response);
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
$fetresult.='<style type="text/css">
ul{ list-style-type: none; }
#container{ width: 960px; margin: 0 auto; position: relative; }
#feature,
.feature { padding: 10px 20px 0 20px;}
#feature li a,
.feature li a { color: #F37321; text-decoration: none;}
.feature h4 {
font-style:italic;
overflow:hidden;
}
.feature p{
color:#464A3F;
font-size:11px;
margin:3px 0;
font-family:inherit;
font-size:100%;
font-style:inherit;
font-weight:inherit;
}
.linkfol
{
background:#098ED1 none repeat scroll 0 0;
color:#fff;
padding:3px 6px;
text-decoration:none;
}

	</style>
	<div id="container-user">
	<div class="feature">
	<div class="l col">
	<ul>';
	
	  $name=$_REQUEST['txt_search'];
	  if(isset($_REQUEST['code']))
	  {
	  $code=$_REQUEST['code'];
	  }
	  else
	  {
	  $code='';
	  }
	 $qry='';
		if($name)
			$qry.="(img.real_name LIKE '".$name."%') AND ";
		if(isset($_REQUEST['code']))
			$qry.="(img.country ='".$code."') AND ";
	 
	 if($user->uid!='')
		   $sel="SELECT * FROM {users} reg,{user_profile} img WHERE $qry reg.uid<>$user->uid and img.uid=reg.uid AND reg.status='1' ";
		else
			$sel="SELECT * FROM {users} reg,{user_profile} img WHERE $qry reg.status='1' and img.uid=reg.uid  ";
	// echo $sel;
	$user_qry=db_query($sel);
	if($user->uid!='')
	$sel_count = db_result(db_query("SELECT COUNT(*) FROM {users} reg,{user_profile} img WHERE $qry reg.uid<>$user->uid and img.uid=reg.uid AND reg.status='1'"));
	else
	$sel_count = db_result(db_query("SELECT COUNT(*) FROM {users} reg,{user_profile} img WHERE $qry status='1' and img.uid=reg.uid "));
		$sel.=" limit $eu, $limit";
		$sel_search=db_query($sel);
	
	while($user_result=db_fetch_object($sel_search))
	{
	if($user->uid!='')
	{
	//$flink='<a class="linkfol" href="user/'.$user_result->uid.'?act=flag">Follow </a>';
	//$flink='<a class="linkfol" href="'.$gSitePath.'profile/'.$user_result->uid.'">View </a>';
	}
	$fetresult.='<li>
	<h3>'.UserPicture_small($user_result->uid).'<a  onclick="get_profile_details('.$user_result->uid.');" > '.$user_result->real_name.'</a>      </h3>
	<h4>'.$user_result->mail.'</h4>		 	
	<p>';
	
	$fetresult.='</p> 
	
	</li> '.$flink.'';
	}
	
	$fetresult.='</ul>';
	
	
	
if($sel_count > $limit ){ 

$fetresult.="<table align = 'center' width='100%'><tr><td  align='left' width='30%'>";
if($back >=0) { 
$fetresult.= "<a href='$page_name?start=$back&code=$code&txt_search=$name'><font face='Verdana' size='2'>PREV</font></a>"; 
} 
$fetresult.= "</td><td align=center width='30%'>";
$i=0;
$l=1;
for($i=0;$i < $sel_count;$i=$i+$limit){
if($i <> $eu){
$fetresult.= " <a href='$page_name?start=$i&code=$code&txt_search=$name'><font face='Verdana' size='2'>$l</font></a> ";
}
else { $fetresult.= "<font face='Verdana' size='4' color=red>$l</font>";}      
$l=$l+1;
}


$fetresult.="</td><td  align='right' width='30%'>";
if($this1 < $sel_count) { 
$fetresult.= "<a href='$page_name?start=$next&code=$code&txt_search=$name'><font face='Verdana' size='2'>NEXT</font></a>";} 
$fetresult.= "</td></tr></table>";

}
	if($sel_count==0)
{
$fetresult.='<b>No Search Results </b>';

}
	$fetresult.=' </div>
	</div>
	</div>';
	
	if(isset($_REQUEST['act'])=='flag')
	{
	$mem_id = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
	 
	 
	 $res_num= db_result(db_query("SELECT COUNT(*) from follower  where  follower_id='".$mem_id."'  and  uid ='".$user->uid."'"));
	if($res_num==0)
	{
	 $ins_commg="insert into   follower (uid,follower_id,follower_status,joindate) values('".$user->uid."','".$mem_id."','1','".date('Y-m-d')."') ";
	$rs_commg=db_query($ins_commg);
	
	drupal_set_message(t('Successfully Added as Follower'), $type = 'success');
	}
	else
	{
	$sel_usermdet="select * from users  where uid='".$mem_id."' ";
	$rs_usernam=db_query($sel_usermdet);
	$namelist=db_fetch_object($rs_usernam);
	
	drupal_set_message(t('You are already following '.$namelist->name.'.'), $type = 'error');
	}
	}

return $fetresult;















}
function search_results_question()
{
 global $gSitePath,$user,$gDocPath,$base_root,$base_path;
	$start='';
	$txt_search='';
	$scid='';
	$sscid=''; 
	$suid=''; 
	$lkr='';
	$tag='';
	$name='';
	$fetresult='';
 $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
//echo $idb;
$page_name="searchquestion"; 
if(isset($_GET['start'])){
	$start=$_GET['start'];
	
}

if(strlen($start) > 0 and !is_numeric($start)){
echo "Data Error";
exit;
}


$eu = ($start - 0); 
$limit = 5;                                 // No of records to be shown per page.
$this1 = $eu + $limit; 
$back = $eu - $limit; 
$next = $eu + $limit; 
$fetresult = '<script type="text/javascript">
				

window.addEvent(\'domready\', function(){
//setDefaultCountry();
});
	
				
				 function get_quest_details(quid){
						//alert(quid);
						var url = "'.$gSitePath.'questinfo";
						//alert(url);
									var req = new Request({    
											method: \'get\'
											,url: url
											,data: {\'qsaid\':quid },
											onRequest: function() { },
											onComplete: function(response) {
													 $(\'quest_info\').set(\'html\', response);
											}
									}).send();
						
						
						}
					
						
				
			
			
							
						</script>
			
			';
$fetresult.='<style type="text/css">
ul{ list-style-type: none; }
#container{ width: 960px; margin: 0 auto; position: relative; }
#feature,
.feature { padding: 10px 20px 0 20px;}
#feature li a,
.feature li a { color: #F37321; text-decoration: none;}
.feature h4 {
font-style:italic;
overflow:hidden;
}
.feature p{
color:#464A3F;
font-size:11px;
margin:3px 0;
font-family:inherit;
font-size:100%;
font-style:inherit;
font-weight:inherit;
}
.linkfol
{
background:#098ED1 none repeat scroll 0 0;
color:#fff;
padding:3px 6px;
text-decoration:none;
}

	</style>
	<div id="container">
	<div class="feature">
	<div class="l col">
	<ul>';
	extract($_REQUEST);
	if(isset($_REQUEST['txt_search'])){
	$name=$_REQUEST['txt_search'];
	}
	
	if(isset($_GET['scid'])){
	$suid=$_GET['scid'];
	
	}
	//$suid=$_REQUEST['scid'];
	//echo "select * from category  where cat_id='".$suid."' " ;
	$sel_catm=db_query("select * from category  where cat_id='".$suid."'   ");
	$saveresult=db_fetch_object($sel_catm);
	 $qry='';
	if(isset($_GET['cid'])){
	$cid=$_GET['cid'];
	
	}
	if(isset($_GET['scid'])){
	$scid=$_GET['scid'];
	
	}
	if($name)
			$qry.="(question LIKE '".$name."%') AND ";
	 if(isset($cid))
	 $qry.="(cid  LIKE '%".$cid."%') AND ";
	  if($scid)
	 $qry.="(scid LIKE '%".$scid."%') AND";
	 if($sscid)
	// $qry.="(sscid LIKE '%".$sscid."%') AND (cid  LIKE '%".$saveresult->parent_id."%') AND ";
	$qry.="(sscid LIKE '%".$sscid."%')  AND ";
	
	 if($tag!='')
		   $sel="SELECT * FROM {question} as q, qtag as tg    WHERE tg.tag_id=$tag and tg.qid=q.qid   and q.status='1'  ";
		else
			$sel="SELECT * FROM {question}   WHERE $qry status='1'   ";
	
	$user_qry=db_query($sel);
	if($tag!='')
	$sel_count = db_result(db_query("SELECT COUNT(*) FROM {question} as q, qtag as tg    WHERE tg.tag_id=$tag and tg.qid=q.qid  and q.status='1'   "));
	else
	$sel_count = db_result(db_query("SELECT COUNT(*) FROM {question}   WHERE $qry status='1'  "));
	$sel.=" limit  $eu, $limit";
	//echo $sel;
		$sel_search=db_query($sel);
	while($user_result=db_fetch_object($sel_search))
	{
	if($user->uid!='')
	{
	//$flink='<a class="linkfol" href="'.$gSitePath.''.$user_result->url.'">View More </a>';
	}
	$vans = "select * from {possible_answer} where  qid=$user_result->qid order by vote desc";
    
    $vlist = db_query($vans);
  
  $query = "SELECT qid, SUM(vote) as possiblevote FROM possible_answer where qid='$user_result->qid' GROUP BY qid";
    $query_list = db_query($query);
    $fetvot = db_fetch_object($query_list);
	if(!empty($fetvot)){
		
		  $vot1= $fetvot->possiblevote;
	}
 
    
    $query_sugest = "SELECT qid, SUM(vote) as suggestv FROM suggest_answer where qid='$user_result->qid' GROUP BY qid";
    $query_sugestlist = db_query($query_sugest);
    $fetvotsugest = db_fetch_object($query_sugestlist);
	if(!empty($fetvotsugest)){
    $vot2=$fetvotsugest->suggestv;
    $totalvotes = $vot1 + $vot2;
	}
	 $numresum = db_result(db_query("SELECT COUNT(*) FROM resource where  qid='$user_result->qid'"));
	$fetresult.='<li>
	<h3><a onclick="get_quest_details('.$user_result->qid.');">'.$user_result->question.'</a>      </h3>';
	 while($vlistquest = db_fetch_object($vlist))
	 {
	$fetresult.='<h4><input name="answer_al" type="radio"  value="'.$vlistquest->paid.'" />'.$vlistquest->answer.'</h4>';		 	
	
	}
	$fetresult.='</li> '.$totalvotes.' Votes  '.$numresum.' Posts';
	}
	
	
	
	if(isset($_REQUEST['cid'])|| isset($_REQUEST['scid']))
	{
	
	
	
	$lkr='cid='.$cid.'&scid='.$scid.'&sscid='.$sscid.'';
	}
	
	if($tag!='')
	{
	$lkr='cid='.$cid.'&scid='.$scid.'&sscid='.$sscid.'&tag='.$tag.'';
	
	}
	
	
	/////////////////////////////// 
if($sel_count > $limit ){ // Let us display bottom links if sufficient records are there for paging

/////////////// Start the bottom links with Prev and next link with page numbers /////////////////
$fetresult.="<table align = 'center' width='100%'><tr><td  align='left' width='30%'>";
//// if our variable $back is equal to 0 or more then only we will display the link to move back ////////
if($back >=0) { 
$fetresult.= "<a href='$page_name?start=$back&$lkr'><font face='Verdana' size='2'>PREV</font></a>"; 
} 
//////////////// Let us display the page links at  center. We will not display the current page as a link ///////////
$fetresult.= "</td><td align=center width='30%'>";
$i=0;
$l=1;
for($i=0;$i < $sel_count;$i=$i+$limit){
if($i <> $eu){
$fetresult.= " <a href='$page_name?start=$i&$lkr'><font face='Verdana' size='2'>$l</font></a> ";
}
else { $fetresult.= "<font face='Verdana' size='4' color=red>$l</font>";}        /// Current page is not displayed as link and given font color red
$l=$l+1;
}


$fetresult.="</td><td  align='right' width='30%'>";
///////////// If we are not in the last page then Next link will be displayed. Here we check that /////
if($this1 < $sel_count) { 
$fetresult.= "<a href='$page_name?start=$next&$lkr'><font face='Verdana' size='2'>NEXT</font></a>";} 
$fetresult.= "</td></tr></table>";

}

if($sel_count==0)
{
$fetresult.='<b>No Search Results </b>';

}
	$fetresult.=' </div>
	</div>
	</div>';
	


return $fetresult;



}
function user_follower()
{

	global $gSitePath,$user, $gDocPath,$base_root,$base_path;
	$follid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
	//echo $follid;
	//echo $user->uid;
	$follower='<script type="text/javascript">
		function changeblk(fid,divid,blk){
			var abc="welcum-"+fid;
			
			
									var url = "'.$gSitePath.'savefollower";
									var req = new Request({    
											method: \'get\'
											,url: url
											,data: { \'action\':fid,\'ids\':abc,\'blk\':blk,\'usid\':divid},
											onRequest: function() { },
											onComplete: function(response) {
													 $(abc).set(\'html\', response);
											}
									}).send();
						
							
                           
							}	
	
	</script>
	';
	
	
	if($_REQUEST['act']=="del")
	{
	$del_blog="update  follower  set follower_status='".$_REQUEST['block']."' where  id='".$follid."' ";
	$rs_blog_del=db_query($del_blog);
	drupal_set_message(t('Updated Successfully '), $type = 'success');
	drupal_goto("follower/");
	}
	$follower.='<div class="following">';
	 $sel_pro="select * from follower  where follower_id='".$follid."'  ";
	$rs_follower=db_query($sel_pro);
	$countrowsm= db_result(db_query("SELECT COUNT(*) from follower  where follower_id='".$follid."' "));
	while($follower_result=db_fetch_object($rs_follower))
	{
	
	
	
	 $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='".$follower_result->uid."'";
	$rs_userm=db_query($sel_userm);
	$user_namelist=db_fetch_object($rs_userm);
	if($follower_result->follower_status==0){
	  if($follid==$user->uid)
	  {
	  $linkr='<a onclick="changeblk('.$follower_result->id.','.$follower_result->uid.',1)" >UnBlock</a>';
	  }
	$blocklink='<input type="hidden" value="1" name="blk" id="blk"/>';
	$blocklink.='<div  id="welcum-'.$follower_result->id.'"><strong>'.$user_namelist->name.'</strong> '.$linkr.'</div>';
	
	} 
	else 
	{
	 if($follid==$user->uid)
	  {
	  $blocklinkdd='<a onclick="changeblk('.$follower_result->id.','.$follower_result->uid.',0)" >Block</a>';
	  }
	$blocklink='<input type="hidden" value="0" name="blk" id="blk"/>';
	$blocklink.='<div  id="welcum-'.$follower_result->id.'"><strong>'.$user_namelist->name.'</strong>'.$blocklinkdd.'</div>';
	
	
	} 
	
	//$follower.='<h4>'.$user_namelist->name.'</a>'.$blocklink.'</h4>';
	$follower.=''.$blocklink.'';
	}
	if($countrowsm==0)
	{
	
	$follower.=' No Records';
	}
	
				   
	echo $follower;

}
function user_following()
{
	global $gSitePath,$user, $gDocPath,$base_root,$base_path;
	$follid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
	$following='<script type="text/javascript">
	window.addEvent(\'domready\',function() {
	$$(\'a.delete\').each(function(el) {
		el.addEvent(\'click\',function(e) {
			e.stop();
			var parent = el.getParent(\'div\');
			var request = new Request({
				url: \''.$gSitePath.'savefollowing\',
				link: \'chain\',
				method: \'get\',
				data: {
					\'delete\': parent.get(\'id\').replace(\'record-\',\'\'),
					ajax: 1
				},
				onRequest: function() {
					new Fx.Tween(parent,{
						duration:300
					}).start(\'background-color\', \'#fb6c6c\');
				},
				onSuccess: function() {
					new Fx.Slide(parent,{
						duration:300,
						onComplete: function() {
							parent.dispose();
						}
					}).slideOut();
				}
			}).send();
		});
	});
});
	
	</script>
	';
	
	$following.='<div class="following">';
	 $sel_pro="select * from follower  where uid='".$follid."'  and follower_status='1' ";
	$rs_following=db_query($sel_pro);
	$countrows = db_result(db_query("SELECT COUNT(*) from follower  where uid='".$follid."'  and follower_status='1'"));
		while($following_result=db_fetch_object($rs_following))
	{
	// $sel_userm="select * from users  where uid='".$following_result->follower_id."' ";
	 $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='".$following_result->follower_id."'";
	$rs_userm=db_query($sel_userm);
	$user_namelist=db_fetch_object($rs_userm);
	 if($follid==$user->uid)
	  {
	  $linkj='<a href="?delete='.$following_result->id.'" class="delete">Unfollow</a>';
	  
	  }
	$following.= '<div class="record" id="record-'.$following_result->id.'"><strong>'.$user_namelist->real_name.'</strong> '.$linkj.' </div>';
	}
	if($countrows==0)
	{
	
	$following.=' No Records';
	}
	echo $following;
	

}
function suggest_follow()
{
	global $gSitePath,$user, $gDocPath,$base_root,$base_path;
	$sel_flow="select * from follower  where uid='".$user->uid."'  and follower_status='1' ";
	$rs_folwin=db_query($sel_flow);
	$array2=array();
	$array1=array();
	while($flwing_result=db_fetch_object($rs_folwin))
	{
	
	array_push($array2,$flwing_result->follower_id);
	
	 $sel_suge="select * from follower  where uid='".$flwing_result->follower_id."' and follower_id!='".$user->uid."' limit 0,5";
	$rs_suges=db_query($sel_suge);
	
	while($suggest_list=db_fetch_object($rs_suges))
	{
	
	//echo $suggest_list->follower_id;
	array_push($array1,$suggest_list->follower_id);
	
	}
	}
	

	$reult = array_diff($array1, $array2);
		
		
		$result_array=array_values($reult);
		if(count($result_array)!=0)
		{
		$suggest_follow='
		<div id="container">
		<div class="feature">
		<div class="l col">
		<ul>';
		
		
		
		for($m=0;$m<count($result_array);$m++)
		{
		 $user_listsm="select * from {users} where status='1' and uid='$result_array[$m]'";
		$user_qrylist=db_query($user_listsm);
		$user_resultry=db_fetch_object($user_qrylist);
	
		$suggest_follow.='<li>
	<h3><a href="'.$gSitePath.'profile/'.$user_resultry->name.'">'.$user_resultry->name.'</a>      </h3>';
	
	
	
	
	}
	
	
	
	$suggest_follow.='</ul></div>
	</div>
	</div>
	';
}
else
{
//////////////////// Maximum User Posted Questions//////////////////////
	
	
	
	 $qusetion_user="SELECT uid, count( uid )FROM question GROUP BY uid limit 0, 10";
	
	$rs_user_quest=db_query($qusetion_user);
	$quid=array();
	while($question_list_user=db_fetch_object($rs_user_quest))
	{
	
	
	array_push($quid,$question_list_user->uid);
	
	}
	
	//print_r($quid);
	//	print_r($array1);
	$reultss= array_diff($quid, $array1);
	//print_r($reultss);
	
	
	$result_array_quest=array_values($reultss);
	//print_r($result_array_quest);
	
	$suggest_follow.='<ul>';
		
		for($t=0;$t<count($result_array_quest);$t++)
		{
		if($result_array_quest[$t]!=$user-uid)
		{
		  $user_quest="select * from {users} where status='1' and uid='$result_array_quest[$t]' ";
		$user_qryqlist=db_query($user_quest);
		$user_resultrym=db_fetch_object($user_qryqlist);
	
		$suggest_follow.='<li>
	<h3><a href="'.$gSitePath.'user/'.$user_resultrym->uid.'">'.$user_resultrym->name.'</a>      </h3>
	<h4>'.$user_resultrym->mail.'</h4>		 	
	
	</li><a class="linkfol" href="follow/'.$user_resultrym->uid.'?act=flag">Follow </a>';
	}
	}

	
	$suggest_follow.='</ul>
	</div>
	</div>
	</div>';



}
	//echo $suggest_follow;
	
	
	
	if($_REQUEST['act']=='flag')
	{
	$mem_id = substr($_GET['q'],strrpos($_GET['q'],"/")+1);

	 
	  $res_num= db_result(db_query("SELECT COUNT(*) from follower  where  follower_id='".$mem_id."'  and  uid ='".$user->uid."'"));
	 
	if($res_num==0)
	{
	 $ins_commg="insert into   follower (uid,follower_id,follower_status,joindate) values('".$user->uid."','".$mem_id."','1','".date('Y-m-d')."') ";
	$rs_commg=db_query($ins_commg);
	
	drupal_set_message(t('Successfully Added as Follower'), $type = 'success');
	}
	else
	{
	$sel_usermdet="select * from users  where uid='".$mem_id."' ";
	$rs_usernam=db_query($sel_usermdet);
	$namelist=db_fetch_object($rs_usernam);
	
	drupal_set_message(t('You are already following '.$namelist->name.'.'), $type = 'error');
	}
drupal_goto("suggest/follow");
	}

$numt= count($result_array_quest);
$numi= count($result_array);
if(($numt==0)&&($numi==0))
{
$suggest_follow.='No suggested Users';

}
	return $suggest_follow;
	














}


function save_follow()
{

$follid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
if(isset($_GET['delete']))
{
 $query = 'DELETE FROM follower WHERE id = '.(int)$_GET['delete'];
$result = db_query($query);
}

}


function save_follower()
{
global $gSitePath,$user, $gDocPath,$base_root,$base_path;
$follid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
if(isset($_GET['action']))
{
$del_blog="update  follower  set follower_status='".$_REQUEST['blk']."' where  id='".$_GET['action']."' ";
	$rs_blog_del=db_query($del_blog);
	
	 
	 $sel_userms="select * from users  where uid='".$_GET['usid']."' ";
	$rs_userms=db_query($sel_userms);
	$resulrnames=db_fetch_object($rs_userms);
	if($_REQUEST['blk']==0)
	{
	$blkid='1';
	$valss='UnBlock';

		if($resulrnames->notify_itype==1)
		{	
			 $insert_notify=db_query("insert into notification (uid,is_block,is_user,node_id) values('".$_GET['usid']."','1','1','".$user->uid."' ");
		}	
		if($resulrnames->notify_etype==1)
		{	
		$sel_user_cmt="SELECT * FROM notification_mail_format Where id='2'";
		$rs_mgmt=db_query($sel_user_cmt);
		$list_content=db_fetch_object($rs_mgmt);
		$contentm=str_replace("#uname#",$resulrnames->name,$list_content->content);
		$contentm= str_replace("#anothername#",$user->name,$contentm);
	//echo  $contentm;
			$subjects=$list_content->subject;
			$mail_success = htmlmail_function($resulrnames->mail,$subjects,$contentm,'');
	   }
	}
	else
	{
	$valss='Block';
    $blkid='0';
	}
	echo '<div id="'.$_REQUEST['ids'].'" ><strong>'.$resulrnames->name.'</strong> <a onclick="changeblk('.$_GET['action'].','.$_GET['usid'].','.$blkid.')" >'.$valss.'</a></div>';
	
}

}

function get_user_details()
{
global $gSitePath,$user, $gDocPath,$base_root,$base_path;
 extract($_REQUEST);
  $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='".$getuid."'";
 $rs_userms=db_query($sel_userm);
	$resulrnames=db_fetch_object($rs_userms);
	//echo $resulrnames->real_name;
 //$ret = $resulrnames->real_name;
   if($resulrnames->gender==1)
   {
   $usetype='Male';
   }
   else
   {
   
   $usetype='Female';
   
   }
	$ret='<table width="100%" border="0">
  <tr>
    <td width="26%">'.UserPicture($resulrnames->uid).'</td>
    <td colspan="2">
      <table width="300" border="1">
        <tr>
          <td width="96">First Name</td>
          <td width="188"> '.$resulrnames->first_name.'</td>
        </tr>
        <tr>
          <td>Last Name</td>
          <td>'.$resulrnames->last_name.'</td>
        </tr>
        <tr>
          <td>Display name</td>
          <td>'.$resulrnames->real_name.'</td>
        </tr>
        <tr>
          <td>DOB</td>
          <td>'.$resulrnames->dob.'</td>
        </tr>
        <tr>
          <td>Country</td>
          <td>'.$resulrnames->country.'</td>
        </tr>
        <tr>
          <td>Gender </td>
          <td>&nbsp;</td>
        </tr>
      </table></td>
  </tr>
  <tr>
    <td>Bio</td>
    <td width="17%">Links</td>
    <td width="57%">'.$resulrnames->bio.'</td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td>Facebook</td>
    <td>'.$resulrnames->facebook.'</td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td>Twitter</td>
    <td>'.$resulrnames->twitter.'</td>
  </tr>
  <tr>
    <td>Following</td>
    <td colspan="2">Followers</td>
  </tr>';

$sel_list="select * from follower  where uid='".$getuid."'  and follower_status='1' ";
	$rs_foll_list=db_query($sel_list);
	$numfolls= db_result(db_query("SELECT COUNT(*)  from follower  where uid='".$getuid."'  and follower_status='1'  "));

if($numfolls!=0)
	{
while($following_list=db_fetch_object($rs_foll_list))
	{
	
	
	  $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='".$following_list->follower_id."'";
		$rs_userm=db_query($sel_userm);
	$user_namelist=db_fetch_object($rs_userm);
	
	

	
	
	






 $ret.='<tr>
    <td>&nbsp;</td>
    <td colspan="2"> <a href="'.$gSitePath.'../profile/'.$user_namelistf->name.'">'.$user_namelist->name.'</a>   </td>
  </tr>';
  
 
				
				}
	}			
	else
	{			
	$ret.='No Records';
	}
	
	
	
	$sel_listf="select * from follower  where follower_id='".$getuid."'   limit 0,5  ";
	$rs_followerf=db_query($sel_listf);
	
	 $numfoll= db_result(db_query("SELECT COUNT(*)  from follower  where follower_id='".$getuid."'   "));
	
	if($numfoll!=0)
	{
	while($follower_resultfuser=db_fetch_object($rs_followerf))
	{
	
	 
	   $sel_ulist = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='".$follower_resultfuser->uid."'";
	$rs_umlog=db_query($sel_ulist);
	$user_namelistf=db_fetch_object($rs_umlog);
	
	
	
		$ret.='<a href="'.$gSitePath.'../profile/'.$user_namelistf->name.'">'.$user_namelistf->real_name.' </a>';
	
	
	
	
	}
	}			
	else
	{			
	$ret.='No Records';
	}
	
	if($_REQUEST=='')
	{	
 $ret.=' <tr>
    <td colspan="3">Select User</td>
  </tr>';
  
    }
 $ret.=' <tr>
    <td colspan="3">&nbsp;</td>
  </tr> 
</table>';

	echo $ret;


}

function search_results_user()
{
global $gSitePath,$user, $gDocPath,$base_root,$base_path;



extract($_REQUEST);
//echo $_REQUEST['code'];
$page_name="searchuser"; //  If you use this code with a different page ( or file ) name then change this 
$start=$_GET['start'];
if(strlen($start) > 0 and !is_numeric($start)){
echo "Data Error";
exit;
}


$eu = ($start - 0); 
$limit = 5;                                 // No of records to be shown per page.
$this1 = $eu + $limit; 
$back = $eu - $limit; 
$next = $eu + $limit; 
$fetresult .= '<script type="text/javascript">
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
	
				
				 function get_profile_details(urid){
						alert(urid);
						var url = "'.$gSitePath.'userinfo";
									var req = new Request({    
											method: \'get\'
											,url: url
											,data: {\'getuid\':urid },
											onRequest: function() { },
											onComplete: function(response) {
													 $(\'user_info\').set(\'html\', response);
											}
									}).send();
						
						
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
						
							var url = "'.$gSitePath.'userresults";
									var req = new Request({    
											method: \'get\'
											,url: url
											,data: { \'action\':1,\'code\':code},
											onRequest: function() { },
											onComplete: function(response) {
													 $(\'container-user\').set(\'html\', response);
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
$fetresult.='<style type="text/css">
ul{ list-style-type: none; }
#container{ width: 960px; margin: 0 auto; position: relative; }
#feature,
.feature { padding: 10px 20px 0 20px;}
#feature li a,
.feature li a { color: #F37321; text-decoration: none;}
.feature h4 {
font-style:italic;
overflow:hidden;
}
.feature p{
color:#464A3F;
font-size:11px;
margin:3px 0;
font-family:inherit;
font-size:100%;
font-style:inherit;
font-weight:inherit;
}
.linkfol
{
background:#098ED1 none repeat scroll 0 0;
color:#fff;
padding:3px 6px;
text-decoration:none;
}

	</style>
	<div id="container-user_list">
	<div class="feature">
	<div class="l col">
	<ul>';
	
	  $name=$_REQUEST['txt_search'];
	 
		if($name)
			$qry.="(img.real_name LIKE '".$name."%') AND ";
		if($code)
			$qry.="(img.country LIKE '".$code."%') AND ";
	 
	 if($user->uid!='')
		   $sel="SELECT * FROM {users} reg,{user_profile} img WHERE $qry reg.uid<>$user->uid and img.uid=reg.uid AND reg.status='1' ";
		else
			$sel="SELECT * FROM {users} reg,{user_profile} img WHERE $qry reg.status='1' and img.uid=reg.uid  ";
//echo $sel;
	$user_qry=db_query($sel);
	if($user->uid!='')
	$sel_count = db_result(db_query("SELECT COUNT(*) FROM {users} reg,{user_profile} img WHERE $qry reg.uid<>$user->uid and img.uid=reg.uid AND reg.status='1'"));
	else
	$sel_count = db_result(db_query("SELECT COUNT(*) FROM {users} reg,{user_profile} img WHERE $qry reg.status='1' and img.uid=reg.uid "));
		$sel.=" limit $eu, $limit";
		$sel_search=db_query($sel);
	
	while($user_result=db_fetch_object($sel_search))
	{
	if($user->uid!='')
	{
	//$flink='<a class="linkfol" href="search/'.$user_result->uid.'?act=flag">Follow </a>';
	//$flink='<a class="linkfol" href="'.$gSitePath.'profile/'.$user_result->uid.'">View </a>';
	}
	$fetresult.='<li>
	<h3>'.UserPicture_small($user_result->uid).'<a  onclick="get_profile_details('.$user_result->uid.');" > '.$user_result->real_name.'</a>      </h3>
	<h4>'.$user_result->mail.'</h4>		 	
	<p>';
	
	$fetresult.='</p> 
	
	</li> '.$flink.'';
	}
	
	$fetresult.='<input type="hidden" name="stype" value="'.$_REQUEST['stype'].'"/></ul>';
	
	
	
if($sel_count > $limit ){ 

$fetresult.="<table align = 'center' width='100%'><tr><td  align='left' width='30%'>";
if($back >=0) { 
$fetresult.= "<a href='$page_name?start=$back&code=$code'><font face='Verdana' size='2'>PREV</font></a>"; 
} 
$fetresult.= "</td><td align=center width='30%'>";
$i=0;
$l=1;
for($i=0;$i < $sel_count;$i=$i+$limit){
if($i <> $eu){
$fetresult.= " <a href='$page_name?start=$i&code=$code'><font face='Verdana' size='2'>$l</font></a> ";
}
else { $fetresult.= "<font face='Verdana' size='4' color=red>$l</font>";}      
$l=$l+1;
}


$fetresult.="</td><td  align='right' width='30%'>";
if($this1 < $sel_count) { 
$fetresult.= "<a href='$page_name?start=$next&code=$code'><font face='Verdana' size='2'>NEXT</font></a>";} 
$fetresult.= "</td></tr></table>";

}
if($sel_count==0)
{
$fetresult.='<b>No Search Results </b>';

}
	$fetresult.=' </div>
	</div>
	</div>';
	
	


echo  $fetresult;









}

function get_question_details()
{
global $gSitePath,$user, $gDocPath,$base_root,$base_path;



extract($_REQUEST);

 $vSql = "select *,q.uid as uid from {question} as q left join {user_profile} as u on q.uid=u.uid where q.status='1' and q.qid='$qsaid'  ";
    $rlist = db_query($vSql);
    $oListquest = db_fetch_object($rlist);
  $vresultm=$oListquest->question;
 $vans = "select * from {possible_answer} where  qid=$qsaid order by vote desc";
    
    $vlist = db_query($vans);
    $chk = '';
    while ($vlistquest = db_fetch_object($vlist)) {
        if ($numran == 0) {
            $answprc = $vlistquest->vote / 100 * $totalvotes;
            $valu = $answprc * 100;
            $vresultm .= '
		 <br/><input name="answer" type="radio" value="'.$vlistquest->paid.'" />
		'.$vlistquest->answer.'  ';
        } else {
            $answprc = $vlistquest->vote / 100 * $totalvotes;
            $valu = $answprc * 100;
            $chk = '';
            if ($answer_id->panswer_id == $vlistquest->paid) {
                
                $chk = "checked";
            }
            $vresultm .= ' <br/><input name="answer_al" type="radio" '.$chk.'  value="'.$vlistquest->paid.'" />
		'.$vlistquest->answer.'   ';
        
        }
        $chk = '';
    }




echo $vresultm;
}


function search_report($idb='') {
    global $gSitePath,$user,$gDocPath,$base_root;
  $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
//echo veni  .$idb;
  echo  $output= '<div class="toolbarTabs">
	<ul id="qTabs" class="tab-menu">
	<li id="qTabs1Link" class="selected"><a>Percentage</a></li>
	<li id="qTabs2Link"><a>Over Time</a></li>
	<li id="qTabs3Link" ><a>By Area</a></li>
	</ul>
	<div class="clear"></div>
	</div>

	<script type="text/javascript">
	
	MochaUI.initializeTabs("qTabs");
	
	$("qTabs1Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("search-panel"),
	"url":       "'.$gSitePath.'searchcontent/'.$idb.'?t=per"
	});
	});
	
	$("qTabs2Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("notify-panel"),
	"url":       "'.$gSitePath.'searchcontent/'.$idb.'?t=time"
	});
	});
	
	$("qTabs3Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("notify-panel"),
	"url":       "'.$gSitePath.'searchcontent/'.$idb.'?t=area"
	});
	});

	
	</script>';

}
function search_content() {
    global $gSitePath,$user,$gDocPath,$base_root;
      $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
	
	 //echo "kkkkkkkk".$qid;
    $type=$_REQUEST[t];
   
    switch ($type) {
    	
        case "time":
            $output = '<div id="contents"><iframe id="frmGoogle" src="'.$gSitePath.'/qlite/graph/'.$qid.'" border="0" height="450" frameborder="0" width="100%"></iframe></div>';
            break;
        case "area":
            $output = '<div id="contents"><iframe id="frmGoogle" src="'.$gSitePath.'/qlite/map/'.$qid.'" border="0" height="450" frameborder="0" width="100%"></iframe></div>';
            break;
		 case "per":	
        default:
            $output = '<div id="contents"><iframe id="frmGoogle" src="'.$gSitePath.'/qlite/percent/'.$qid.'" border="0" height="450" frameborder="0" width="100%"></iframe></div>';
            break;
    }
	
	
	$output.='<div>108 comments &nbsp;&nbsp;&nbsp;'.$numres.' Resources </div>';
	
    echo $output;
}

function search_quest_cat()
{
$link1 ='';
$link2 ='';
$link3='';
$cid='';
$scid='';
 global $gSitePath,$user,$gDocPath,$base_root,$base_path;
if(($_REQUEST['scid']!='')||($_REQUEST['cid']!=''))
{
$suid=$_REQUEST['scid'];
if($_REQUEST['cid']=='')
{
$sel_catm=db_query("select * from category  where cat_id='".$suid."'   ");
$saveresult=db_fetch_object($sel_catm);
$cid=$saveresult->parent_id;
}
else
{
$cid=$_REQUEST['cid'];
}

//$catlist='Category';
   $sel_cat=db_query("select * from category  where cat_id=".$cid."   ");
   $saveresult=db_fetch_object($sel_cat);


    $sel_suge="select * from category  where parent_id=".$cid."   ";
	
	$rs_folwin=db_query($sel_suge);
	$numrancnt = db_result(db_query("SELECT COUNT(*) from  question   where cid=".$cid."  "));
	
	$catlist='
		<div id="container">
		<div class="feature">
		<div class="l col">
		<ul><li><b><a href="'.$gSitePath.'searchquestion?cid='.$cid.'">'.$saveresult->cat_name.'('.$numrancnt.')</a></b></li>';
      
	while($flwing_result=db_fetch_object($rs_folwin))
	{
	//echo "SELECT COUNT(*) from  question   where cid=".$cid." and scid=".$flwing_result->cat_id."";
	
	$numrancnts= db_result(db_query("SELECT COUNT(*) from  question   where cid=".$cid." and scid=".$flwing_result->cat_id.""));
	
	
	$catlist.='<li>&nbsp;<a href="'.$gSitePath.'searchquestion?cid='.$cid.'&scid='.$flwing_result->cat_id.'">'.$flwing_result->cat_name.'('.$numrancnts.')</li>';
	//echo $flwing_result->cat_id;
	
	 $sel_sugess="select * from category  where parent_id=".$flwing_result->cat_id."   ";
	 $rs_folwinss=db_query($sel_sugess);
	while($sm_result=db_fetch_object($rs_folwinss))
	{
	$numrancntss= db_result(db_query("SELECT COUNT(*) from  question   where cid=".$cid." and scid=".$flwing_result->cat_id." and  sscid=".$sm_result->cat_id.""));
	$catlist.='<li>&nbsp;&nbsp; <a href="'.$gSitePath.'searchquestion?cid='.$cid.'&scid='.$flwing_result->cat_id.'&sscid='.$sm_result->cat_id.'">'.$sm_result->cat_name.'('.$numrancntss.') </a> </li>';
	
	}
	}
$catlist.='</ul></div>
	</div>
	</div>
	';
	}
	else
	{
	
	//$catlist='Category';
   

    $sel_sugef="select * from category where parent_id='0'    ";
	
	$rs_cat=db_query($sel_sugef);
	
	
	$catlist='
		<div id="container">
		<div class="feature">
		<div class="l col">
		<ul>';
      
	while($cat_result=db_fetch_object($rs_cat))
	{
	
	
	$numrancnts= db_result(db_query("SELECT COUNT(*) from  question where  cid=".$cat_result->cat_id.""));
	
	
	$catlist.='<li>&nbsp;<a href="'.$gSitePath.'searchquestion?cid='.$cat_result->cat_id.'">'.$cat_result->cat_name.'('.$numrancnts.')</li>';
	
	
	
	}
$catlist.='</ul></div>
	</div>
	</div>
	';
	
	
	}
	echo  $catlist;
}


?>