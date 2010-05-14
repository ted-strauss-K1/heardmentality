<?php

function moderate_user()
{
global $gSitePath,$user, $gDocPath,$base_root,$base_path;
 drupal_add_js(drupal_get_path('module', 'moderator').'/scripts/moderate.js');

$seldonar="select count(nodeid) as cnt ,f.nodeid from question_flags as f   where f.type='question'   group by nodeid";

$res_donar=db_query($seldonar);
$moduser='	<div id="nlist">
	<form id="notify" method="post" action="'.$gSitePath.'admin/notifymail" ><table width="100%" border="1">
  <tr>
    <td>Question </td>
    <td>Flagged </td>
    <td>Question Author </td>
    <td></td>
  </tr>';
while($don=db_fetch_object($res_donar))
{
 $sequest="select * from question where qid='".$don->nodeid."'";
$res_quest=db_query($sequest);
$qlist=db_fetch_object($res_quest);
 // $ss=$qlist->question;
 $sellist="select * from users where uid='".$qlist->uid."'";
$res_users=db_query($sellist);
$usert=db_fetch_object($res_users);
 $uname=$usert->name;
if($user->uid!=$qlist->uid)
{
$moduser.='<tr>
    <td>'.$qlist->question.'</td>
    <td>'.$don->cnt.'</td>
    <td>'.$uname.' </td>
    <td><input type="checkbox" class="check-user" name="us_id[]" value="'.$qlist->uid.'" /> </td>
  </tr>';
}

}
$moduser.=' <tr>
    <td colspan="5"><input type="hidden" id="action" name="action" value="1"/> <input type="button" onclick="send_notify(0);"  value="Send Notification"/>&nbsp; <input onclick="send_suspend(0);" type="button" value="Suspend User"/></td>
    
  
  </tr></table></div>';

return $moduser;















}

?>