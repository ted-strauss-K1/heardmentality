
<?php

function qlite_view()
{
	global $gSitePath,$user, $gDocPath,$base_root,$base_path;
	

drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/main.css');
drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/page.css');
			drupal_add_css(drupal_get_path('module', 'quest_lite').'/css/tabs.css');
 $qid = substr($_GET['q'],strrpos($_GET['q'],"/")+1);
	$vSql="select * from {question} where status='1' and qid=$qid ";
		$rlist=db_query($vSql);
		$oListquest=db_fetch_object($rlist);
		
		$vuser="select * from {users} where  uid=$oListquest->uid ";
		$username=db_query($vuser);
		$ufet=db_fetch_object($username);
		$vSql="SELECT *
FROM node_revisions as a JOIN node as b
ON a.nid = b.nid and 
b.type='news_page' and b.status='1'  ";
$rlist=mysql_query($vSql);

		
			$output.='<form id="answer" name="answer" method="post" action="'.$gSitePath.'qlite/save" >
  <table width="100%" border="0" align="center"><input type="hidden" name="mid" value="".$qid."">
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
			$output.='
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

		 <li id="one"><a href="javascript:void(0);">Reporting</a></li>
                               <li id="two"><a href="javascript:void(0);">Forum</a></li>
                               <li id="three"><a href="javascript:void(0);">Resources</a></li>
                               <li id="four"><a href="javascript:void(0);">Gurus</a></li>
                               <li id="five"><a href="javascript:void(0);">Info</a></li>
							    <li id="six"><a href="javascript:void(0);">Politician</a></li>
					</ul>
               <div id="container">
                               <div id="contentone" class="hidden">
                                     <p class="con"> This is a demo for the donationware Sliding Tabs script by Jenna Fox. You can click the links at the top or use the arrows to move to different panes. If you dig the effect, go check out the docs, and if you use it, make sure to donate something! Oh and if you need any help getting the script set up, feel free to drop me a message.</p>
                               </div>

                               <div id="contenttwo" class="hidden">
                                     <p class="con">  This is the second. Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Check out the docs
                              </p> </div>
                               <div id="contentthree" class="hidden">
                                       <ul id="navigation">
									    <li id="seven"><a style="font:10px Verdana;
  color:#FFF;" href="javascript:void(0);">In the News</a></li>
                               <li id="eight"><a style="font:10px Verdana;
  color:#FFF;" href="javascript:void(0);">Multimedia </a></li>
                               <li id="nine"><a style="font:10px Verdana;
  color:#FFF;"  href="javascript:void(0);">Facts</a></li>
                              
					</ul>
					<div >
                               <div id="contentseven" class="hiddens">';
							   $output.='<table width="100%" border="0">';
			$i=1;
while($oListUser=mysql_fetch_object($rlist))
					{
 $output.='<tr>
    <td width="100%"><p class="con">'.$i++.'<strong>'.$oListUser->title.'</strong> </p></td>
    <td width="37%">&nbsp;</td>
  </tr>
  <tr>
    <td width="100%"><div id="newsd"><p class="con">'.$oListUser->body.'</p></div></td>
    <td width="100%">&nbsp;</td>
  </tr>
  <tr>
    <td></td>
    <td>&nbsp;</td>
  </tr>';
  }
  $output.='</table>
							</div>
							<div id="contenteight" class="hiddens">
							<p class="con"> Multimedia Content comes here </p> 
							</div>
							
							
								<div id="contentnine" class="hiddens">
							<p class="con"> Facts comes here  </p> 
							</div>   
					</div>		   
                               </div>
							   
							    <div id="contentfour" class="hidden">
                                <p class="con">  Gurus Content comes here  
                               </div>
							  
	


							    <div id="contentfive" class="hidden">
                                         <h1> Question Information </h1><p class="con"> <b>Question Author: </b> '.$ufet->name.' <br>
			<b>Date Created:</b> '.format_date($oListquest->date_added, "custom", "D j M Y"). ' <br>
			<b>Number of Votes:</b> 0<br>
			<b>Number of Forum Posts:</b> 0 <br>
			<b>Number of Resources:</b> 0</p>
		
                               </div>
							<div id="contentsix" class="hidden">
							<p class="con"> Gurus Content comes here </p> 
							</div>
							
							
							<div id="contentseven" class="hidden">";
							
							
		  
		
		$output.="
								
							
							
							
							
                            </div>   
</div>
      
	  </form>
	  

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
		  if($_REQUEST['txt_act']==3)
		 {
		  $list_length = db_query("select * from {question_flags} where nodeid='".$mid."' and uid='".$user->uid."' and  type='question' ");
		 $numr=mysql_num_rows($list_length);
		 echo $numr;
		 if($numr==0)
		 {
		 $flagquery="insert into question_flags(nodeid,uid,flag_date,type) values ('".$mid."','".$user->uid."','".date('Y-m-d')."','question')";
		 	db_query($flagquery);
		 drupal_set_message($message = 'You Have Flagged successfully !', $type = 'success');
		 drupal_goto("qlite/view/$mid");
		 }
		  else
		  {
		  	
	
		
		 drupal_set_message(t('You Have Already Flagged !'), $type = 'error');
	    drupal_goto("qlite/view/$mid");
		  
		  }
		  
		  }
		
	   return $voutput;

}