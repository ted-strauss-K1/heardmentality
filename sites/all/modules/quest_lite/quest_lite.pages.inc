
<?php

function qlite_view()
{
	global $gSitePath,$user, $gDocPath,$base_root;
	


		drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/main.css');
		drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/page.css');
			drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/tabs.css');	
	drupal_add_js(drupal_get_path('module', 'quest_lite').'/scripts/jtabsn.js');	
	drupal_add_js(drupal_get_path('module', 'quest_lite').'/scripts/jtabsn2.js');	
 $qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
	$vSql="select * from {question} where status='1' and qid=$qid ";
		$rlist=db_query($vSql);
		$oListquest=db_fetch_object($rlist);
		
		$vuser="select * from {users} where  uid=$oListquest->uid ";
		$username=db_query($vuser);
		$ufet=db_fetch_object($username);
		
			$output.='<form id="answer" name="answer" method="post" action="'.$gSitePath.'qlite/save" >
  <table width="100%" border="0" align="center"><input type="hidden" name="mid" value="'.$qid.'">
  <tr>
		<td width="16%" align="right" valign="top"><strong>Question:</strong></td>
		<td valign="top">'.$oListquest->question.'</td>
	</tr>
	<tr>
		<td align="right" valign="top"><strong>Context:</strong></td>
		<td valign="top"> '.$oListquest->context.'</td>
	</tr>

	<tr>
		<td align="right"><strong>Answer:</strong></td>
		
		<td>		</td>
	</tr>';
		
			$vans="select * from {possible_answer} where  qid=$qid ";
		
		
		$vlist=db_query($vans);
		while($vlistquest=db_fetch_object($vlist))
		{
			$output.= '
			<tr>
			  <td align="right">&nbsp;</td>
			  <td><input name="answer" type="radio" value="'.$vlistquest->paid.'" />
'.$vlistquest->answer.'</td>
  </tr>';
	
		
		}
	$output.='
  <tr>
    <td align="right">ACTIONS </td>
    <td>
      <select name="txt_act" id="txt_act">
	  <option value="0"> Select</option >
      <option value="1"> Withdraw answer</option >
       <option value="2"> Invite</option >
      <option value="3"> Flag</option >
       <option value="4">Suggest New Answer</option> 
      <option value="5">Create Mashup:</option> 
      </select>
    </td>
  </tr>
  <tr>
			  <td align="right">&nbsp;</td>
			  <td>
			    <input type="submit" name="save" id="save" value="Save" />
			 </td></tr>
 </table>
';
		
			
	$output.='
     
      

          
	   <div id="usual2" class="usual">
	  
	  <ul id="navigation">

		<li><a href="#c1">Reporting</a></li>
		<li><a href="#c2">Forum</a></li>
		<li><a href="#c3">Resources</a></li>
		<li><a href="#c4">Gurus</a></li>
		<li><a href="#c5">Info</a></li>
		<li><a href="#c6">Politician</a></li>
		<li><a href="#c7">Raw Data</a></li>
	</ul>
	
	<div id="container">
	
		<div class="content">
			<a name="c1" id="c1"></a>

			<h1>Reporting</h1>
			<p>Here is some content, I hope that you like it!</p>
		</div>
		
		<div class="content">
			<a name="c2" id="c2"></a>
			<h2>Forum</h2>
			<p>Now that you have read content block 1, you can learn more in this block</p>

		</div>
		
		<div class="content">
			<a name="c3" id="c3"></a>
			<h3>Resources </h3>
			<p>In conclusion, content blocks are fun</p>
		</div>
		<div class="content">
			<a name="c4" id="c4"></a>
			<h3>Gurus</h3>
			<p>In conclusion, content blocks are fun</p>
		</div>
	 <div class="content">
	
			<a name="c5" id="c5"></a>
			<h2>Info</h2>
			<p>Question Author: '.$ufet->name.' </p>
			<p>Date Created:'.$oListquest->date_added.' </p>
			<p>Number of Votes: 0</p>
			<p>Number of Forum Posts: 0 </p>
			<p>Number of Resources: 0</p>
		</div>
		
		<div class="content">
			<a name="c6" id="c6"></a>
			<h3>Politiciain</h3>
			<p>In conclusion, content blocks are fun</p>
		</div>
		
		<div class="content">
			<a name="c7" id="c7"></a>
			<h3>Raw Data</h3>
			<p>In conclusion, content blocks are fun</p>
		</div>
	</div> 
	  
	  </div></form>
	  

';
    return $output;
}


function qlite_save()
{

		global $gSitePath,$user, $gDocPath,$base_root;
$mid=$_REQUEST['mid'];

	$voutput='';
		$vquest="select * from {possible_answer} where paid='".$_REQUEST['answer']."'  ";
		$rquest=db_query($vquest);
		$olistquest=db_fetch_object($rquest);
		 
		 if(($_REQUEST['answer']!=''))
		 {
		$list_length = db_query("select * from {user_answers} where qid='".$mid."' and uid='".$user->uid."' ");
		$numr=mysql_num_rows($list_length);
		echo $numr;
		if($numr==0)
		{
		$vInsQuery="insert into user_answers(qid, ans_id,uid,answered_date) values ('".$mid."', '".$_REQUEST['answer']."','".$user->uid."','".date('Y-m-d h:i:s')."')";
		db_query($vInsQuery);
		
		drupal_set_message(t('Thank you,Your Answer has been saved successfully!'), $type = 'success');
		drupal_goto("qlite/view/$mid");
		}
		else
		{
		drupal_set_message($message = 'You Have already answered This Question!', $type = 'error');
		drupal_goto("qlite/view/$mid");
		
		}
		
		}
		
		
		 
		 if($_REQUEST['txt_act']==1)
		 {
		  $list_length = db_query("select * from {user_answers} where qid='".$mid."' and uid='".$user->uid."' ");
		 $numr=mysql_num_rows($list_length);
		 echo $numr;
		 if($numr==0)
		 {
		 
		 drupal_set_message($message = 'You Have Not Posted Answer !', $type = 'error');
		 drupal_goto("qlite/view/$mid");
		 }
		  else
		  {
		  $delQuery="delete from  user_answers where qid='".$mid."' and uid='".$user->uid."' ";
		db_query($delQuery);
		
		 drupal_set_message(t('Your Answer has beed  Removed successfully!'), $type = 'success');
	    drupal_goto("qlite/view/$mid");
		  
		  }
		  
		  }
		  
		
	   return $voutput;

}