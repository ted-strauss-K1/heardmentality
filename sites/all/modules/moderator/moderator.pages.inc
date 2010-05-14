<?php

function moderate_user()
{
global $gSitePath,$user, $gDocPath,$base_root,$base_path;


$seldonar="select count(nodeid) as cnt ,f.nodeid from question_flags as f   where f.type='question'   group by nodeid";

$res_donar=db_query($seldonar);
$moduser='<table width="100%" border="1">
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

$moduser.='<tr>
    <td>'.$qlist->question.'</td>
    <td>'.$don->cnt.'</td>
    <td>'.$uname.' </td>
    <td></td>
  </tr>';


}


return $moduser;















}

?>