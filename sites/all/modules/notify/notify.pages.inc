<?php


function admin_notify() {
    global $base_url, $user;
    drupal_add_js(drupal_get_path('module', 'notify') . '/tinymce/jscripts/tiny_mce/tiny_mce.js');
    drupal_add_js(drupal_get_path('module', 'notify') . '/scripts/tiny.js');
    $linkval = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    $query="select * from {notification_mail_format}";
    $list = ExecuteQuery($query, "select");
     if ($linkval != 'notification') {
        $mid = $linkval;
    } else {
        $mid = '1';
    }

      $adminmgmt = '<form id="myForm" name="myForm"  method="post" action="' . $base_url . '/admin/save_notify"  ><table width="100%" border="0"><tr>';
     foreach ($list as $loop) {
     if($loop['id']==$mid)
         $bold='style="font-weight:bold;"';
     else
         $bold='';
$adminmgmt.= '
    <td> <a '.$bold.' href="' . $base_url . '/admin/notification/'.$loop['id'].'">'.$loop['subject'].'</a></td>
    
  ';
     }
  


    // echo $linkval;
   
    $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='" . $mid . "'";
    $rs_mgmt = db_query($sel_user_cmt);
    $contenmt = db_fetch_object($rs_mgmt);



    $adminmgmt.='</tr>
</table>
<table width="100%" border="0">
 <tr colspan="6">
    <td>Subject : <input type="text" name="msub" value="' . $contenmt->subject . '"/></td>
   
  </tr>
<tr colspan="6">
    <td><textarea id="elm1" name="content" rows="15" cols="80">' . $contenmt->content . '</textarea></td>
    <input type="hidden" name="mlink" value="' . $mid . '"/>
  </tr>
   <tr colspan="6">
    <td><input type="submit" name="Submit" value="Save" class="btn"></td>
    
  </tr>
</table>







</form>';

    return $adminmgmt;
}

function admin_notify_save() {

    global $base_url, $user;
    $mid = $_REQUEST['mlink'];
    $updatevoteposs = "update  notification_mail_format set subject='" . addslashes($_REQUEST['msub']) . "', content='" . addslashes($_REQUEST['content']) . "' where id='" . $_REQUEST['mlink'] . "'";
    db_query($updatevoteposs);

    drupal_goto("admin/notification/$mid");

    return $savelink;
}


