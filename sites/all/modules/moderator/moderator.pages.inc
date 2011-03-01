<?php


function moderater_user_mail($array='',$type='',$action='') {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
 $days_from_now = 10; //10 days from now
    $us_id = implode(',', $array['qids']);
      $msg=$_REQUEST['reporttext'];
switch($type){
    case 'warning':

    if ($action) {


        foreach ($array as $idd) {
            quest_mail_warning($idd,$msg);
        }
        return '<div class="success">Warning Message Send!</div>';
    } else {

      flag_user_mail($array,$days_from_now);
        foreach ($array as $idd) {
          
            $conv_secs = $days_from_now * 60 * 60 * 24; //convert days to secs

            $current_timestamp = date("U");

            $target_timestamp = $current_timestamp + $conv_secs;
            
         db_query("update {users} set status='%d',blocktime='%d' where uid='%d'",'0',$target_timestamp,$idd);
        }



        return  '<div class="success">Suspended  successfully for '.$days_from_now.' days!</div>';

       
    }
    break;
    case 'ignore':
         if ($action) {
         $qids = implode(',', $array);
        $query = db_query("delete  from {question_flags} where type='user' AND fid in ($qids)");
                      return '<div class="success">User(s) has been unflagged successfully!</div>';

         }else{
          flag_user_mail($array,$days_from_now);
        foreach ($idr as $idd) {



            $days_from_now = 10; //10 days from now

            $conv_secs = $days_from_now * 60 * 60 * 24; //convert days to secs

            $current_timestamp = date("U");

            $target_timestamp = $current_timestamp + $conv_secs;

           db_query("update {users} set status='%d',blocktime='%d' where uid='%d'",'0',$target_timestamp,$idd);
        }
        return  '<div class="success">Users has been suspended  successfully for '.$days_from_now.' days!</div>';


         }
        
        
        break;
    default:
        return "No Action Found!";

 break;
}
}

function quest_mail($qids = '') {

    global $gSitePath, $user, $gDocPath, $base_root;

    $from = variable_get('site_mail');
    $subject = 'Heardmentality suspended Your account  ';
    $warn = $_REQUEST['warn_msg'];
    foreach ($qids as $id) {


        $query = db_query("select u.mail,q.question  from {question} as q left join {users} as u on u.uid=q.uid where qid='$id' ");
        $det = db_fetch_object($query);

        $to = $det->mail;
        $msg = '<br/>Question : ' . $det->question . ' ' . $warn . '<br/>';
        if (!empty($to)) {

            $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
    }
    return true;
}

function quest_mail_warning($uid = '',$msg='') {

    global $gSitePath, $user, $gDocPath, $base_root;

    $from = variable_get('site_mail');
    $subject = 'Heardmentality Warning Mail   ';
    $warn = ' This is warning message from Heardmentality .If this continues we will block Your account';
   
        $query = db_query("select mail from {users} where uid='$uid' ");
        $det = db_fetch_object($query);

        $to = $det->mail;
        $msg = '<br/> '. $warn . '<br/>'.$msg;
        if (!empty($to)) {

            $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }

    return true;
}



function question_deleted_mail($qaid) {

    global $gSitePath, $user, $gDocPath, $base_root;

    $from = variable_get('site_mail');
    $subject = 'Heardmentality Question Has Been Deleted ';
    $delmsg = 'Has been Deleted By Headmentality admin';

    $query = db_query("select u.mail,q.question  from {question} as q left join {users} as u on u.uid=q.uid where q.qid='$qaid' ");
    $det = db_fetch_object($query);

    $to = $det->mail;
    $msg = '<br/>Question : ' . $det->question . ' ' . $delmsg . '<br/>';
    if (!empty($to)) {

        $mail_suc = htmlmail($to, $subject, $msg, $from, '');
    }


    return true;
}

function question_deleted_mail_voters($qaid) {

    global $gSitePath, $user, $gDocPath, $base_root;

    $from = variable_get('site_mail');
    $subject = 'Heardmentality question  Has Been Deleted which You have  answered  ';
    $delmsg = 'Has been Deleted By Headmentality admin';

    $query = db_query("select u.question,q.uid  from possible_answer_vote as q left join question as u on u.qid=q.qid where q.qid='$qaid' ");

    while ($det = db_fetch_object($query)) {

        $sellist = "select * from users where uid='" . $det->uid . "'";
        $res_users = db_query($sellist);
        $usert = db_fetch_object($res_users);
        $to = $usert->mail;
        $msg = '<br/>Question : ' . $det->question . ' ' . $delmsg . '<br/>';



        if (!empty($to)) {

            $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
    }
    return true;
}

function question_deleted_mail_suggest($qaid) {

    global $gSitePath, $user, $gDocPath, $base_root;

    $from = variable_get('site_mail');
    $subject = 'Heardmentality question  Has Been Deleted which You have  answered  ';
    $delmsg = 'Has been Deleted By Headmentality admin';

    $query = db_query("select u.question,q.uid  from suggest_answer as q left join question as u on u.qid=q.qid where q.qid='$qaid' ");

    while ($det = db_fetch_object($query)) {

        $sellist = "select * from users where uid='" . $det->uid . "'";
        $res_users = db_query($sellist);
        $usert = db_fetch_object($res_users);
        $to = $usert->mail;
        $msg = '<br/>Question : ' . $det->question . ' ' . $delmsg . '<br/>';



        if (!empty($to)) {

            $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
    }
    return true;
}




function question_edited_mail($qaid) {

    global $gSitePath, $user, $gDocPath, $base_root;

    $from = variable_get('site_mail');
    $subject = 'Heardmentality Issue Has Been Edited By Moderator ';
    $delmsg = 'Has been edited by our Moderator';

    $query = db_query("select u.mail,q.question  from {question} as q left join {users} as u on u.uid=q.uid where q.qid='$qaid' ");
    $det = db_fetch_object($query);

    $to = $det->mail;
    $msg = '<br/>Question : ' . $det->question . ' ' . $delmsg . '<br/>';
    if (!empty($to)) {

        $mail_suc = htmlmail($to, $subject, $msg, '');
    }


    return true;
}

function question_edited_mail_voters($qaid) {

    global $gSitePath, $user, $gDocPath, $base_root;

    $from = variable_get('site_mail');
    $subject = 'Heardmentality Question Has Been Edited By admin ';
    $delmsg = 'Has been Edited By Headmentality admin';
    $query = db_query("select u.question,q.uid  from possible_answer_vote as q left join question as u on u.qid=q.qid where q.qid='$qaid' ");

    while ($det = db_fetch_object($query)) {

        $sellist = "select * from users where uid='" . $det->uid . "'";
        $res_users = db_query($sellist);
        $usert = db_fetch_object($res_users);
        $to = $usert->mail;
        $msg = '<br/>Question : ' . $det->question . ' ' . $delmsg . '<br/>';



        if (!empty($to)) {

            $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
    }
    return true;
}

function question_edited_mail_suggest($qaid) {

    global $gSitePath, $user, $gDocPath, $base_root;

    $from = variable_get('site_mail');
    $subject = 'Heardmentality Question Has Been Edited By admin ';
    $delmsg = 'Has been Edited By Moderator';

    $query = db_query("select u.question,q.uid  from suggest_answer as q left join question as u on u.qid=q.qid where q.qid='$qaid' ");

    while ($det = db_fetch_object($query)) {

        $sellist = "select * from users where uid='" . $det->uid . "'";
        $res_users = db_query($sellist);
        $usert = db_fetch_object($res_users);
        $to = $usert->mail;
        $msg = '<br/>Question : ' . $det->question . ' ' . $delmsg . '<br/>';



        if (!empty($to)) {

            $mail_suc = htmlmail($to, $subject, $msg, $from, '');
        }
    }
    return true;
}

function question_merge_mail($qid='', $dupe='') {

    global $gSitePath, $user, $gDocPath, $base_root;

    $from = variable_get('site_mail');
    $subject = 'Heardmentality Issue has be Merged ';
    // for voters who voted the dupe issues
    $query = db_query("select u.question,q.uid  from possible_answer_vote as q left join question as u on u.qid=q.qid where q.qid='$qid' ");

    $dq = load_question($dupe);
    $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='9'";
    $rs_mgmt = db_query($sel_user_cmt);
    $list_content = db_fetch_object($rs_mgmt);
    $msg = '<br/>Issue [' . $dq['question'] . '] <br/> has been merged to below Issue due to Duped <br/> [ ' . $det->question . '] <br/>';


    $contentm = str_replace("#content#", $msg, $list_content->content);


    while ($det = db_fetch_object($query)) {

        $usert = user_load(array('uid' => $det->uid));
        $to = $usert->mail;
        $contentm = str_replace("#uname#", $usert->name, $contentm);

        if (!empty($to)) {
            $ins_qry = "insert into hm_mails(from_mail_id,user_from_id,user_to_id,subject,content,mail_status,notify,posted_date)values('$from','$from','$to','" . $subject . "','" . $contentm . "',0,0,now())";

            db_query($ins_qry);
        }
    }


    // for the user who posted the mail
    $usert = user_load(array('uid' => $dq['uid']));
    $contentm = str_replace("#uname#", $usert->name, $list_content->content);
    $contentm = str_replace("#content#", $msg, $contentm);
    $to = $usert->mail;

    if (!empty($to)) {
        $ins_qry = "insert into hm_mails(from_mail_id,user_from_id,user_to_id,subject,content,mail_status,notify,posted_date)values('$from','$from','$to','" . $subject . "','" . $contentm . "',0,0,now())";

        db_query($ins_qry);
    }
    return true;
}

?>