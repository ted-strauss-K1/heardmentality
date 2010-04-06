<?php

function search_results()
{
global $gSitePath,$user, $gDocPath,$base_root,$base_path;

/*$fetresult='<style type="text/css" src="'.$gSitePath.'/sites/all/modules/user_search/style/style.css">
</style>';*/
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
	 $user_list="select * from {users} where status='1' and uid!=$user->uid";
	$user_qry=db_query($user_list);
	while($user_result=db_fetch_object($user_qry))
	{
	if($user->uid!='')
	{
	$flink='<a class="linkfol" href="search/'.$user_result->uid.'?act=flag">Follow </a>';
	}
	$fetresult.='<li>
	<h3><a href="'.$gSitePath.'user/'.$user_result->uid.'">'.$user_result->name.'</a>      </h3>
	<h4>'.$user_result->mail.'</h4>		 	
	<p>Follow
	FlyLady as she weaves her way through housecleaning &amp; organizing
	tips, with homespun humor, daily musings about life &amp; love, and
	anything else. </p> 
	
	</li> '.$flink.'';
	}
	
	$fetresult.='</ul>
	</div>
	</div>
	</div>';
	
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
drupal_goto("search/");
	}

return $fetresult;
}

function user_follower()
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
				url: \'http://localhost/heard/savefollowing\',
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
	
	
	if($_REQUEST['act']=="del")
	{
	$del_blog="update  follower  set follower_status='".$_REQUEST['block']."' where  id='".$follid."' ";
	$rs_blog_del=db_query($del_blog);
	drupal_set_message(t('Updated Successfully '), $type = 'success');
	drupal_goto("follower/");
	}
	$follower.='<div class="following">';
	$sel_pro="select * from follower  where follower_id='".$user->uid."'  and follower_status='1' or follower_status='0' ";
	$rs_follower=db_query($sel_pro);
	$countrowsm= db_result(db_query("SELECT COUNT(*) from follower  where uid='".$user->uid."'  and follower_status='1' or follower_status='0'"));
	while($follower_result=db_fetch_object($rs_follower))
	{
	if($follower_result->follower_status==0){
	//$blocklink='<a style="text-decoration:none;" href="follower/'.$follower_result->id.'?act=del&block=1"><span>UnBlock </span></a>';
	$blocklink='<input type="submit" name="button" id="submitter"  value="UnBlock"/>';
	} 
	else 
	{
	//$blocklink='<a style="text-decoration:none;" href="follower/'.$follower_result->id.'?act=del&block=0"><span>Block </span></a>';
	
	
	} 
	$sel_userm="select * from users  where uid='".$follower_result->uid."' ";
	$rs_userm=db_query($sel_userm);
	$user_namelist=db_fetch_object($rs_userm);
	$follower.='<h4>'.$user_namelist->name.'</a></h4>';
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
	
	$following='<script type="text/javascript">
	window.addEvent(\'domready\',function() {
	$$(\'a.delete\').each(function(el) {
		el.addEvent(\'click\',function(e) {
			e.stop();
			var parent = el.getParent(\'div\');
			var request = new Request({
				url: \'http://192.9.200.10/heardmentality/savefollowing\',
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
	 $sel_pro="select * from follower  where uid='".$user->uid."'  and follower_status='1' ";
	$rs_following=db_query($sel_pro);
	$countrows = db_result(db_query("SELECT COUNT(*) from follower  where uid='".$user->uid."'  and follower_status='1'"));
		while($following_result=db_fetch_object($rs_following))
	{
	 $sel_userm="select * from users  where uid='".$following_result->follower_id."' ";
	$rs_userm=db_query($sel_userm);
	$user_namelist=db_fetch_object($rs_userm);
	$following.= '<div class="record" id="record-'.$following_result->id.'"><strong>'.$user_namelist->name.'</strong> <a href="?delete='.$following_result->id.'" class="delete">Unfollow</a</div>';
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
	
	
	array_push($array1,$suggest_list->follower_id);
	
	}
	}
	
	
	//print_r($array1);
	//print_r($array2);
	//echo count($array1);
	//echo	count($array2);
	$reult = array_diff($array1, $array2);
		
		//print_r($reult);
		$result_array=array_values($reult);
		//print_r($result_array);
		//echo $result_array[$m];
		$suggest_follow='<style type="text/css">
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
		
		for($m=0;$m<count($result_array);$m++)
		{
		 $user_listsm="select * from {users} where status='1' and uid='$result_array[$m]'";
		$user_qrylist=db_query($user_listsm);
		$user_resultry=db_fetch_object($user_qrylist);
	
		$suggest_follow.='<li>
	<h3><a href="'.$gSitePath.'user/'.$user_resultry->uid.'">'.$user_resultry->name.'</a>      </h3>
	<h4>'.$user_resultry->mail.'</h4>		 	
	
	</li><a class="linkfol" href="follow/'.$user_resultry->uid.'?act=flag">Follow </a>';
	
	}
	
	$suggest_follow.='</ul>
	';
	
	
	//////////////////// Maximum User Posted Questions//////////////////////
	
	
	
	$qusetion_user="SELECT uid, count( uid )FROM question GROUP BY uid limit 0, 10";
	
	$rs_user_quest=db_query($qusetion_user);
	$quid=array();
	while($question_list_user=db_fetch_object($rs_user_quest))
	{
	
	
	array_push($quid,$question_list_user->uid);
	
	}
	
	//print_r($quid);
	$reultss= array_diff($array1, $quid);
	//print_r($reultss);
	$valueresult= array_diff($reultss, $result_array);
	//print_r($valueresult);
	
	$result_array_quest=array_values($valueresult);
	
	
	$suggest_follow.='<ul>';
		
		for($t=0;$t<count($result_array_quest);$t++)
		{
		  $user_quest="select * from {users} where status='1' and uid='$result_array_quest[$t]'";
		$user_qryqlist=db_query($user_quest);
		$user_resultrym=db_fetch_object($user_qryqlist);
	
		$suggest_follow.='<li>
	<h3><a href="'.$gSitePath.'user/'.$user_resultrym->uid.'">'.$user_resultrym->name.'</a>      </h3>
	<h4>'.$user_resultrym->mail.'</h4>		 	
	
	</li><a class="linkfol" href="follow/'.$user_resultrym->uid.'?act=flag">Follow </a>';
	
	}

	
	$suggest_follow.='</ul>
	</div>
	</div>
	</div>';
	
	
	
	
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



	return $suggest_follow;
	

}


function save_follow()
{

$follid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
	
	

		
		
		if(isset($_GET['delete']))
{
	echo $query = 'DELETE FROM follower WHERE id = '.(int)$_GET['delete'];
	$result = db_query($query);
}

}


function save_follower()
{
$follid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
$del_blog="update  follower  set follower_status='".$_REQUEST['block']."' where  id='".$follid."' ";
	$rs_blog_del=db_query($del_blog);
	echo 'Updated Successfully ';


}
?>