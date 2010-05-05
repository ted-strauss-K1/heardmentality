<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Untitled Document</title>
</head>

<body>
<?php 
global $gSitePath,$user, $gDocPath,$base_root,$base_path;
	
	$sel_flow="select * from follower as a, question as b  where a.uid='1'  and a.follower_status='1' and a.follower_id=b.uid ";
	$rs_folwin=db_query($sel_flow);
	$questlist='
		<div id="container">
		<div class="feature">
		<div class="l col">
		<ul>';
	while($flwing_result=db_fetch_object($rs_folwin))
	{
	
	
	
	$sel_suge="select * from possible_answer  where qid=".$flwing_result->qid."  ";
	$mm=mysql_query($sel_suge);
	/*$rs_ans=db_query($sel_suge);
	$ans_result=db_fetch_object($rs_ans)*/
		$questlist.='<li>
	<h3><a href="'.$gSitePath.$flwing_result->url.'">'.$flwing_result->question.'</a>      </h3><div>'.$flwing_result->context.'</div>
	'.$ans_result->answer.'';
	
	
	}
	
$questlist.='</ul></div>
	</div>
	</div>
	';
	
	echo $questlist
		
	
	?>
    <input name="" type="radio" value="" />
</body>
</html>
