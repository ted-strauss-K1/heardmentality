<?php
function search_results() {
    ////vijay1
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    
    $flink = '';
    $fetresult = '';
    extract($_REQUEST);
    $page_name = "searchuser"; //  If you use this code with a different page ( or file ) name then change this
    if (isset($_GET['start'])) {
         $start = $_GET['start'];
        
    } else {
        $start = 0;
    }
    if (strlen($start) > 0 and !is_numeric($start)) {
        echo "Data Error";
        exit;
    }


    $eu = ($start - 0);
    $limit = 14; // No of records to be shown per page.
    $this1 = $eu + $limit;
    $back = $eu - $limit;
    $next = $eu + $limit;
    $fetresult = '';
    drupal_add_js(drupal_get_path('module', 'user_search') . '/js/search.js');

   $txt_search =  $_REQUEST['txt_search'];
    $name = $_REQUEST['txt_search'];
    $q_country = $_REQUEST['q_country'];
    $q_state = $_REQUEST['q_state'];
    
    $cid = $_REQUEST['cid'];
    $scid = $_REQUEST['scid'];

    
    if ($_REQUEST['code']!='') {
        $code = $_REQUEST['code'];
    }
     
    $qry = '';
    if($name!='')
        $qry .= "AND (img.real_name LIKE '" . $name . "%')";
    
    if($_REQUEST['code']!='')
        $qry .= "AND (img.country ='" . $code . "')";

    if($_REQUEST['q_country']!='')
        $qry .= "AND (img.country ='" . $q_country . "')";

    if($_REQUEST['q_state']!='')
        $qry .= "AND (img.state ='" . $q_state . "')";
    
    if($_REQUEST['q_city']!='')
        $qry .= "AND (img.city ='" . $q_city . "')";
     

   
//SELECT * FROM users reg, user_profile img, follower fol WHERE (fol.cat_id ='1') AND reg.status='1' and reg.uid=fol.uid group by fol.uid
    if ($user->uid != '')
    {
            if($_REQUEST['cid']!=''){

                if($scid!='')
                    $c_qry .= "AND (fol.cat_id=$scid)";
                
                $qry_form = "img, follower fol where 1 $qry AND (fol.cat_id=$cid) AND reg.status=1 and reg.uid=fol.uid $c_qry group by fol.uid";
            }
            else{
                $qry_form = "img WHERE 1 $qry and img.uid=reg.uid AND reg.status='1'";
            }


    }
    else
    {
            
        if($_REQUEST['cid']!=''){
                if($scid!='')
                    $c_qry .= "AND (fol.cat_id=$scid)";
                
                $qry_form = "img, follower fol where 1 $qry AND (fol.cat_id=$cid) AND reg.status=1 and reg.uid=fol.uid $c_qry group by fol.uid";
            }
            else{
                $qry_form = "img WHERE 1 $qry AND reg.status='1' and img.uid=reg.uid";
            }

    
    }
     $sel = "SELECT * FROM {users} reg,{user_profile} $qry_form";
   
   //  echo $sel;
   
    $user_qry = db_query($sel);


    $sel_count=ExecuteQuery($sel, 'norows');
    

    if ($user->uid != '')
    {
             if($_REQUEST['cid']!=''){

                if($scid!='')
                    $c_qry .= "AND (fol.cat_id=$scid)";
                  
                $qry_form = "img, follower fol where 1 $qry and (fol.cat_id=$cid) AND reg.status=1 and reg.uid=fol.uid $c_qry group by fol.uid";
                $sel_count =  mysql_num_rows(db_query("SELECT count(*) FROM {users} reg,{user_profile} $qry_form"));
            }
            else{
                  
                $qry_form = "img WHERE 1 $qry and img.uid=reg.uid AND reg.status='1'";
                  $sel_count =  db_result(db_query("SELECT count(*) FROM {users} reg,{user_profile} $qry_form"));
            }

        
      //$sel_count = db_result(db_query("SELECT COUNT(*) FROM {users} reg,{user_profile} img WHERE $qry reg.uid<>$user->uid and img.uid=reg.uid AND reg.status='1'"));
    }
    else
    {
      //  $sel_count = db_result(db_query("SELECT COUNT(*) FROM {users} reg,{user_profile} img WHERE $qry status='1' and img.uid=reg.uid "));

        if($_REQUEST['cid']!=''){

                if($scid!='')
                    $c_qry .= "AND (fol.cat_id=$scid)";

                $qry_form = "img, follower fol where $qry (fol.cat_id=$cid) AND reg.status=1 and reg.uid<>$user->uid and reg.uid=fol.uid $c_qry group by fol.uid";
                $sel_count =  mysql_num_rows(db_query("SELECT count(*) FROM {users} reg,{user_profile} $qry_form"));
            }
            else{
                
                 $qry_form = "img WHERE $qry reg.uid<>$user->uid and img.uid=reg.uid AND reg.status='1'";
                 $sel_count =  db_result(db_query("SELECT count(*) FROM {users} reg,{user_profile} $qry_form"));
            }

    }
    $sel .= " limit $eu, $limit";
   
   
    $sel_search = db_query($sel);

    $incr = 0;

     $fetresult = ' <div class="rleft">
       <!--<span class="padding10">SEARCH RESULTS</span><br />-->
       <div class="clr"></div>
       <div class="result-item"></div>
       <div class="clr"></div>
       <div class="clr"></div>
       <div class="result-item">
       <div class="rleft">';

    while ($user_result = db_fetch_object($sel_search)) {
        $incr = $incr + 1;
        if ($user->uid != '') {
            //$flink='<a class="linkfol" href="user/'.$user_result->uid.'?act=flag">Follow </a>';
            //$flink='<a class="linkfol" href="'.$gSitePath.'profile/'.$user_result->uid.'">View </a>';
        }
        $gquery = "select ifnull(sum(points),0) as qpt from {tbl_user_points} where uid='" . $user_result->uid . "'";
        $gpoints = db_result(db_query($gquery));
        if ($user_result->gender == 1) {
            $usetype = 'Male';
        } elseif ($user_result->gender == 2) {

            $usetype = 'Female';
        } else {
            $usetype = '<b>--</b>';
        }
        if($incr==2)
        {
            $divider = '<div class="clr"></div>';
        }
        else
        {
            $divider = '';
        }
        
      $fetresult .=  ' <div class="prof-it-1">
        <div class="lefimg-it-c"><a href="#" onclick="get_profile_details(' . $user_result->uid . ');" >' . UserPicture($user_result->uid) . '</a></div>
        <div class="ritecont-it-c">
<div>
<ul>
<li><a  onclick="get_profile_details(' . $user_result->uid . ');" style="cursor:pointer" > ' . $user_result->real_name . '</a></li><br />
<!--<li>' . $gpoints . '</li><br />-->
'.updateProfileBadge($user_result->uid).'
</ul>
</div>
</div>
<div class="clr"></div>
   </div>';
    }
    if ($sel_count == 0) {
        $fetresult .= '<div align="center"><b>No Search Results  </b></div>';
    }
   $fetresult .=  '</div>
       </div>
       <div class="clr"></div>
       <div class="clr"></div>
       <div class="result-item">


       </div>
       <div class="clr"></div>
       </div>  ';

    if ($sel_count > $limit) {
       

        $fetresult .= "   <div class='page-n' align='center'>
            <ul><li>";
        if ($back >= 0) {
            $fetresult .= "<a href='$page_name?start=$back&code=$code&txt_search=$name'>Previous</a>";
            $fetresult .= "&nbsp;&nbsp;<li><a href='$page_name?start=$back&code=$code&txt_search=$name'><img alt='Previous' src='".$gSitePath."sites/all/themes/newtheme/images/p-l.jpg'></a></li>";

        }
        $fetresult .= "</li><li>";
        $i = 0;
        $l = 1;
        for ($i = 0; $i < $sel_count; $i = $i + $limit) {
            if ($i <> $eu) {
                $fetresult .= " <a href='$page_name?start=$i&code=$code&txt_search=$name'>$l</a> ";
            } else {
                $fetresult .= "<font color=red>$l</font>";
            }
            $l = $l + 1;
        }


        $fetresult .= "</li>";
        if ($this1 < $sel_count) {
          
             $fetresult .= "<li><a href='$page_name?start=$next&code=$code&txt_search=$name'><img alt='Next' src='".$gSitePath."sites/all/themes/newtheme/images/p-r.jpg'></a></li>";
             $fetresult .= "&nbsp;&nbsp;<li><a href='$page_name?start=$next&code=$code&txt_search=$name'>Next</a></li>";
        }
        $fetresult .= "</ul>
        </div>";
    }
    
    $fetresult .= ' ';

    if (isset($_REQUEST['act']) == 'flag') {
        $mem_id = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);


        $res_num = db_result(db_query("SELECT COUNT(*) from follower  where  follower_id='" . $mem_id . "'  and  uid ='" . $user->uid . "'"));
        if ($res_num == 0) {
            $ins_commg = "insert into   follower (uid,follower_id,follower_status,joindate) values('" . $user->uid . "','" . $mem_id . "','1','" . date('Y-m-d') . "') ";
            $rs_commg = db_query($ins_commg);

            drupal_set_message(t('Successfully Added as Follower'), $type = 'success');
        } else {
            $sel_usermdet = "select * from users  where uid='" . $mem_id . "' ";
            $rs_usernam = db_query($sel_usermdet);
            $namelist = db_fetch_object($rs_usernam);

            drupal_set_message(t('You are already following ' . $namelist->name . '.'), $type = 'error');
        }
    }

    return $fetresult;
}
function search_follow()
{
     global $gSitePath, $user, $gDocPath, $base_root, $base_path;
      $qry_value = substr($_REQUEST[q],strrpos($_REQUEST[q],"/"));
     $cat_id = ltrim($qry_value,"/");
  // $cat =  explode("/",$_REQUEST['q']);
    //    $catid = explode("=",$cat[2]);

          $res_num = db_result(db_query("SELECT COUNT(*) from follower  where  cat_id='" .$cat_id."'  and  uid ='" . $user->uid . "'"));
        
        if(!$res_num){

            //insert into notification
            
             db_query("insert into notification(uid,is_cat,node_id)values('".$user->uid."',1,'".$cat_id."')");
             db_query("insert into follower(uid,cat_id)values('".$user->uid."','".$cat_id."')");
             $output = drupal_set_message(t('Category follows added successfully !'), $type = 'success');
              echo '<script>window.parent.location.href="'.$gSitePath.'category/";</script>';
        }
        else
        {
             $output = drupal_set_message(t('Category follows already added !'), $type = 'success');
             echo '<script>window.parent.location.href="'.$gSitePath.'category/";</script>';
        }
}
function search_unfollow()
{
        
     global $gSitePath, $user, $gDocPath, $base_root, $base_path;

      $qry_value = substr($_REQUEST[q],strrpos($_REQUEST[q],"/"));
     $cat_id = ltrim($qry_value,"/");
     
   //$cat =  explode("/",$_REQUEST['q']);
     //   $catid = explode("=",$cat[2]);

          $res_num = db_result(db_query("SELECT COUNT(*) from follower  where  cat_id='" .$cat_id."'  and  uid ='" . $user->uid . "'"));


        if($res_num){
             db_query("delete from follower where uid='".$user->uid."' and cat_id='".$cat_id."'");
             $output = drupal_set_message(t('Category Unfollows successfully !'), $type = 'success');
              echo '<script>window.parent.location.href="'.$gSitePath.'category/";</script>';
        }
        
}


function question_follow()
{

     global $gSitePath, $user, $gDocPath, $base_root, $base_path;
   $ques =  explode("/",$_REQUEST['q']);
        $quesid = explode("=",$ques[2]);
       

          $res_num = db_result(db_query("SELECT COUNT(*) from follower  where  question_id='" .$quesid[1]."'  and  uid ='" . $user->uid . "'"));
         

        if(!$res_num){
             db_query("insert into follower(uid,question_id)values('".$user->uid."','".$quesid[1]."')");
             $output = drupal_set_message(t('Questions follows added successfully !'), $type = 'success');
              echo '<script>window.parent.location.href="'.$gSitePath.'category/";</script>';
        }
        else
        {
             $output = drupal_set_message(t('Questions follows already added !'), $type = 'success');
             echo '<script>window.parent.location.href="'.$gSitePath.'category/";</script>';
        }
   
}

function question_unfollow()
{

     global $gSitePath, $user, $gDocPath, $base_root, $base_path;
   $ques =  explode("/",$_REQUEST['q']);
        $quesid = explode("=",$ques[2]);


          $res_num = db_result(db_query("SELECT COUNT(*) from follower  where  question_id='" .$quesid[1]."'  and  uid ='" . $user->uid . "'"));


        if($res_num==1){
            db_query("delete from follower where uid='".$user->uid."' and question_id='".$quesid[1]."'");
             $output = drupal_set_message(t('Questions follows deleted successfully !'), $type = 'success');
              echo '<script>window.parent.location.href="'.$gSitePath.'category/";</script>';
        }
}

function check_select($gid,$quid){
       if($gid==$quid)
       {

            $check = "checked='".checked."'";
       }
       else
       {
           $check = " ";
       }
       return $check;
       }

function search_results_question() {
///vijay search
   // print_r($_REQUEST);
   // exit;
    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/wave.js');
    global $gSitePath, $user, $gDocPath, $base_root, $base_path, $apikey;
    $start = '';
    $txt_search = '';
    $cid = '';
    $scid = '';
    $sscid = '';
    $suid = '';
    $lkr = '';
    $tag = '';
    $name = '';
    $fetresult = '';
    $totalvotes = 0;
    $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    //echo $idb;
    drupal_add_js(drupal_get_path('module', 'quest_lite') . '/scripts/subtab.js');
    

    $page_name = "searchquestion";
    if (isset($_GET['start'])) {
        $start = $_GET['start'];
    }

    if (strlen($start) > 0 and !is_numeric($start)) {
        echo "Data Error";
        exit;
    }
    if ($_GET['cid']!='') {
        $cid = $_GET['cid'];
    }
    if ($_GET['scid']!='') {
        $scid = $_GET['scid'];
    }
    if ($_GET['sscid']!='') {
        $scid = $_GET['sscid'];
    }
     

    $eu = ($start - 0);
    $limit = 10; // No of records to be shown per page.
    $this1 = $eu + $limit;
    $back = $eu - $limit;
    $next = $eu + $limit;

    $sel = facetad_refine();
    $sel_count = $sel['qcnt'];
    $sel['query'] .= " limit  $eu, $limit";
   
    drupal_add_js(drupal_get_path('module', 'user_search') . '/js/search.js');
     drupal_add_js(drupal_get_path('module', 'user_search') . '/js/sub.js');
    // echo $sel;
    // $sel_search = ExecuteQuery($sel, "select");
    // print_r($sel_search);
    $fetresult.='<SCRIPT type="text/javascript" lang="javascript" src="http://cdn.gigya.com/JS/socialize.js"></SCRIPT>
	<script>
        var conf = 
        {
           // APIKey: \'2_Zfr6Di925xeUYK-BRe1kNOYYclMYDUbGsgb_kF4NqlZaJ4owUytfdi2cnRePUJ_j\'
		   APIKey: \'' . $apikey . '\'
        };
        
        function onLoad()
        {
            gigya.services.socialize.getUserInfo(conf,{callback:renderUI});	    
            
           
            gigya.services.socialize.addEventHandlers(conf, { onConnect:renderUI, onDisconnect:renderUI}   ); 
            
        }
    </script>   ';
    //echo $sel['query'];
    $sel_search = db_query($sel['query']);
    $i = 0;
    while ($user_result = db_fetch_object($sel_search)) {

        if ($user->uid != '') {
            //$flink='<a class="linkfol" href="'.$gSitePath.''.$user_result->url.'">View More </a>';
        }
         $vans = "select * from {possible_answer} where  qid='$user_result->qid' order by vote desc";

        $vlist = db_query($vans);

        $query = "SELECT qid,SUM(vote) as possiblevote FROM possible_answer where qid='$user_result->qid' GROUP BY qid";
        $query_list = db_query($query);
        $fetvot = db_fetch_object($query_list);
        if (!empty($fetvot)) {

            $vot1 = $fetvot->possiblevote;
        }
        $query_sugest = "SELECT qid, SUM(vote) as suggestv FROM suggest_answer where qid='$user_result->qid' GROUP BY qid";
        $query_sugestlist = db_query($query_sugest);
        $fetvotsugest = db_fetch_object($query_sugestlist);
        if (!empty($fetvotsugest)) {
            $vot2 = $fetvotsugest->suggestv;
            $totalvotes = $vot1 + $vot2;
        }
        // alter for $totalvotes
        $ques_count = db_fetch_object(db_query("SELECT count(qid) as qcount FROM `possible_answer_vote` where qid='".$user_result->qid."'"));
        
        // alter for numresum
        $for_count = db_fetch_object(db_query("SELECT count(qid_rid) as fcount FROM `forum_wave` where qid_rid='".$user_result->qid."'"));
        
        $numresum = db_result(db_query("SELECT COUNT(*) FROM resource where  qid='$user_result->qid'"));
        $fetresult .= ' <div class="result-item">
	<div class="rleft">
       <div class="titl">
        <form id="answer_frm" name="answer_frm" method="post" action="' . $gSitePath . 'qlite/save"  >
             <input type="hidden" name="mid" id="mid" value="' . $user_result->qid . '"/>
<a href="'.$gSitePath.$user_result->url.'?ajax=1" style="'.drupal_link_color($user->uid,$user_result->qid).'">' . htmlentities(rtrim($user_result->question, "?")). '?</a>
</div>';
//<a href="javascript:void(0);" onclick="get_quest_details(' . $user_result->qid . ',this);" title="'. htmlentities(wordwrap($user_result->question, 40,'<br/>')).'" style="'.drupal_link_color($user->uid,$user_result->qid).'">' . htmlentities(substr(rtrim($user_result->question, "?"),0,70)). '?</a>
        
        while ($vlistquest = db_fetch_object($vlist)) {

           ///vijay implement
        $sel_qry = db_query("select * from {possible_answer_vote} where qid='".$user_result->qid."' and uid='".$user->uid."'  ");
        $get_value = db_fetch_object($sel_qry);
       
  
       $sel_ans = db_query("select * from {possible_answer} where paid='".$get_value->panswer_id."'");
       $get_ans = db_fetch_object($sel_ans);

       
      //  name="answer_al['.$i.']"
            $fetresult .= ' <div class="item1"><input name="answer_al['.$i.']" id="answer" type="radio"  value="' . $vlistquest->paid . '" '.check_select($get_ans->paid,$vlistquest->paid).'  />' . $vlistquest->answer. '</div>';
            
        }


        $numran = db_result(db_query("SELECT COUNT(*) from {possible_answer_vote} where qid='" .$user_result->qid. "' and uid='" . $user->uid . "'"));
        if ($numran != 0) {
        $query="select vote_pid from {possible_answer_vote} where qid='$user_result->qid' AND uid='".$user->uid."'";
        $voteid=db_result(db_query($query));
     $fetresult .= ' <p style="padding-left:8px"><input type="submit" name="change" id="change" value="Change" /><input type="hidden" name="vote_id" value="'.$voteid.'"/></p></form>';
   //     $optio = '<div align="center" class="share2"><a title="Withdraw Your Answer" class="share-link" onclick="formsubmittype(1,' . $qid . ');" href="javascript:void(0);">Withdraw</a></div>';
    }
    if ($numran == 0) {

        $fetresult .= ' <p style="padding-left:8px"><input type="submit" name="save" id="save" value="Vote" /></p></form>';
    }




       


       // $fetresult .= ' <p><input type="submit" name="save" id="save" value="Vote" /></p></form>';


        $fol_qry = db_query("SELECT count(*) as count FROM {follower} where uid='".$user->uid."'and question_id='".$user_result->qid."'");
          $fol_list = db_fetch_object($fol_qry);

          if($fol_list->count==1)
          {
                $follow = "UnFollow";
          }
          if($fol_list->count==0)
          {
              $follow = "Follow";
          }
          
        $fetresult .= '</div><div class="rright">
      <div class="vote-post-outer">
      <div class="vote-post-outer-top"> 
      </div>';  
        $fetresult .= '     <div class="vote-post-outer-bottom">
      <div align="center" class="vot-t" style="border-right:1px solid black"><img src="'.$gSitePath.'sites/all/themes/newtheme/images/tick.jpg" alt="img" /> Votes | '.$ques_count->qcount.'</div>
       <div align="center" class="vot-t"><img src="'.$gSitePath.'sites/all/themes/newtheme/images/post.jpg" alt="img" /> Posts | '.$for_count->fcount.'</div>
      
      </div>
      
      </div>
      
      </div>  </div>    
       <div class="clr"></div>
';
        $i++;
    }


    if (isset($_REQUEST['cid']) || isset($_REQUEST['scid'])) {


        $lkr = 'cid=' . $cid . '&scid=' . $scid . '&sscid=' . $sscid . '';
    }

    if ($tag != '') {
        $lkr = 'cid=' . $cid . '&scid=' . $scid . '&sscid=' . $sscid . '&tag=' . $tag . '';
    }


    ///////////////////////////////
    if ($sel_count > $limit) { // Let us display bottom links if sufficient records are there for paging
        /////////////// Start the bottom links with Prev and next link with page numbers /////////////////
        $fetresult .= " <div class='result-item factmore'><div class='page-n' align='center'><ul><li>";
        //// if our variable $back is equal to 0 or more then only we will display the link to move back ////////
        if ($back >= 0) {
            $fetresult .= "<a class='' href='$page_name?start=$back&$lkr'>Previous</a>";
            $fetresult .= "&nbsp;&nbsp;<a class='' href='$page_name?start=$back&$lkr'><img alt='Previous' src='".$gSitePath."sites/all/themes/newtheme/images/p-l.jpg'></a>";
            
        }
        //////////////// Let us display the page links at  center. We will not display the current page as a link ///////////
        $fetresult .= "</li><li>";
        $i = 0;
        $l = 1;
        for ($i = 0; $i < $sel_count; $i = $i + $limit) {
            if ($i <> $eu) {
                $fetresult .= " <a class='sidelinks' href='$page_name?start=$i&$lkr'>$l</a> ";
            } else {
                $fetresult .= "<font color='black'>$l</font>";
            } /// Current page is not displayed as link and given font color red
            $l = $l + 1;
        }


        $fetresult .= "</li<li>";
        ///////////// If we are not in the last page then Next link will be displayed. Here we check that /////
        if ($this1 < $sel_count) {
            
            $fetresult .= "<a class='sidelinks' href='$page_name?start=$next&$lkr'><img alt='Next' src='".$gSitePath."sites/all/themes/newtheme/images/p-r.jpg'></a>";
            $fetresult .= "&nbsp;&nbsp;<a class='sidelinks' href='$page_name?start=$next&$lkr'>Next</a>";
        }
        $fetresult .= "</li></ul></div></div>";
    }

    if ($sel_count == 0) {
        $fetresult .= ' <div  align="center" class="result-item"><b>No Search Results </b></div>';
    }

    return $fetresult;
}

function user_follower() {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

    $follid = (int) substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    $follower = '
        <script>
        var gSitePath="'.$gSitePath.'";
</script>
        	<script type="text/javascript" src="' . $gSitePath . '/misc/jquery.js"></script>
      	<script type="text/javascript" src="' . $gSitePath . drupal_get_path('module', 'profile') . '/js/profile.js"></script>
  <link rel="stylesheet" href="' . $gSitePath . 'modules/system/system.css" type="text/css" />
		<link rel="stylesheet" href="' . $gSitePath . path_to_theme() . '/css/css.css" type="text/css" />
                    <link rel="stylesheet" href="' . $gSitePath . path_to_theme() . '/lib/jquery.tab.css" type="text/css" />
      
        <div class="facttop">FOLLOWERS</div>
	';


    if ($_REQUEST['act'] == "del") {
        $del_blog = "update  follower  set follower_status='" . $_REQUEST['block'] . "' where  id='" . $follid . "' ";
        $rs_blog_del = db_query($del_blog);
        drupal_set_message(t('Updated Successfully '), $type = 'success');
        drupal_goto("follower/");
    }
    if (!empty($follid)) {
        $follower .= '<div class="following">';
        $sel_pro = "select * from follower  where follower_id='" . $follid . "'  ";
        $rs_follower = db_query($sel_pro);
        $countrowsm = db_result(db_query("SELECT COUNT(*) from follower  where follower_id='" . $follid . "' "));
        $followeru = '';
        while ($follower_resultfuser = db_fetch_object($rs_follower)) {

            // $sel_ulist="select * from users  where uid='".$follower_resultfuser->uid."' ";
            $sel_ulist = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $follower_resultfuser->uid . "'";
            $rs_umlog = db_query($sel_ulist);
            $user_namelistf = db_fetch_object($rs_umlog);


            $user_namelistf->name;
          
            if ($follid == $user->uid) {
                $flink1 = '<a style="color:#F37321;" onclick="blockandunblock(' . $follower_resultfuser->id . ',' . $follower_resultfuser->uid . ',1,1)" >UnBlock</a>';
                $flink2 = '<a style="color:#F37321;" onclick="blockandunblock(' . $follower_resultfuser->id . ',' . $follower_resultfuser->uid . ',0,1)" >Block</a>';
                if ($follower_resultfuser->follower_status == 0) {
                     $input = '<span style="padding-left:17px;">&nbsp;</span>';
                }else{
                $input = '<input type="checkbox" name="muid"  value="' . $follower_resultfuser->id . '"/> &nbsp;';
                }
            }
            if ($follower_resultfuser->follower_status == 0) { 
                $followeru = '<div  id="list-' . $follower_resultfuser->id . '">' . $input . '<a href="' . $gSitePath . 'profile/' . $user_namelistf->name . '">' . UserPicture_small($follower_resultfuser->uid) . $user_namelistf->name . ' </a> ' . $flink1 . '</div>';
            } else {
                $followeru = '<div  id="list-' . $follower_resultfuser->id . '">' . $input . '<a href="' . $gSitePath . 'profile/' . $user_namelistf->name . '">' . UserPicture_small($follower_resultfuser->uid) . $user_namelistf->name . ' </a> ' . $flink2 . '</div>';
            }

            $follow .= '' . $followeru . '';
            //$followeru[]='<a href="'.$gSitePath.'profile/'.$user_namelistf->name.'">'.$user_namelistf->name.' </a><br>';
        }

        if ($countrowsm == 0) {

            $follower .= '<span style="padding-left:17px;">No Followers Found</span> ';
        }elseif ($user->uid == $follid) {
            $follower.='  <div class="clear"><ul class="subtabs"><li>Select</li> <li><a href="#" onclick="chk_all(1);";>All</a> </li><li><a href="#" onclick="chk_all(0);";>None</a></li><li><a href="#" onclick="enable_form(1,this);";>Send Message</a><li><li></li></ul></div>
<form name="frmsgform" id="frmsgform" action="' . $gSitePath . 'postmessage" method="POST">' . $follow . '
     <div align="left" style="display:none;" id="frmsgbox"><div class="facttop2">SEND MESSAGE</div><br><textarea id="msgs" row="17" cols="55" name="frmsgs"></textarea><input type="hidden" value="37" name="actions" id="actions"><br><br><input type="button" value="sendmessage" id="usmsg"></div>

</form>
'; 
           
        }
    } else {

        $follower = ' No Records';
    }



    echo $follower;
}

function user_following() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $follid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    $following = '<script type="text/javascript">
	window.addEvent(\'domready\',function() {
	$$(\'a.delete\').each(function(el) {
		el.addEvent(\'click\',function(e) {
			e.stop();
			var parent = el.getParent(\'div\');
			var request = new Request({
				url: \'' . $gSitePath . 'savefollowing\',
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

    $following .= '<div class="following">';
    $sel_pro = "select * from follower  where uid='" . $follid . "'  and follower_status='1' ";
    $rs_following = db_query($sel_pro);
    $countrows = db_result(db_query("SELECT COUNT(*) from follower  where uid='" . $follid . "'  and follower_status='1'"));
    while ($following_result = db_fetch_object($rs_following)) {
        // $sel_userm="select * from users  where uid='".$following_result->follower_id."' ";
        $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $following_result->follower_id . "'";
        $rs_userm = db_query($sel_userm);
        $user_namelist = db_fetch_object($rs_userm);
        if ($follid == $user->uid) {
            $linkj = '<a href="?delete=' . $following_result->id . '" class="delete">Unfollow</a>';
        }
        $following .= '<div class="record" id="record-' . $following_result->id . '"><strong>' . $user_namelist->real_name . '</strong> ' . $linkj . ' </div>';
    }
    if ($countrows == 0) {

        $following .= ' No Records';
    }
    echo $following;
}

function suggest_follow() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $sel_flow = "select * from follower  where uid='" . $user->uid . "'  and follower_status='1' ";
    $rs_folwin = db_query($sel_flow);
    $array2 = array();
    $array1 = array();
    while ($flwing_result = db_fetch_object($rs_folwin)) {

        array_push($array2, $flwing_result->follower_id);

        $sel_suge = "select * from follower  where uid='" . $flwing_result->follower_id . "' and follower_id!='" . $user->uid . "' limit 0,5";
        $rs_suges = db_query($sel_suge);

        while ($suggest_list = db_fetch_object($rs_suges)) {

            //echo $suggest_list->follower_id;
            array_push($array1, $suggest_list->follower_id);
        }
    }


    $reult = array_diff($array1, $array2);


    $result_array = array_values($reult);
    if (count($result_array) != 0) {
        $suggest_follow = '
		<div id="container">
		<div class="feature">
		<div class="l col">
		<ul>';


        for ($m = 0; $m < count($result_array); $m++) {
            $user_listsm = "select * from {users} where status='1' and uid='$result_array[$m]'";
            $user_qrylist = db_query($user_listsm);
            $user_resultry = db_fetch_object($user_qrylist);

            $suggest_follow .= '<li>
	<h3><a href="' . $gSitePath . 'profile/' . $user_resultry->name . '">' . $user_resultry->name . '</a>      </h3>';
        }


        $suggest_follow .= '</ul></div>
	</div>
	</div>
	';
    } else {
        //////////////////// Maximum User Posted Questions//////////////////////


        $qusetion_user = "SELECT uid, count( uid )FROM question GROUP BY uid limit 0, 10";

        $rs_user_quest = db_query($qusetion_user);
        $quid = array();
        while ($question_list_user = db_fetch_object($rs_user_quest)) {


            array_push($quid, $question_list_user->uid);
        }

        //print_r($quid);
        //	print_r($array1);
        $reultss = array_diff($quid, $array1);
        //print_r($reultss);


        $result_array_quest = array_values($reultss);
        //print_r($result_array_quest);

        $suggest_follow .= '<ul>';

        for ($t = 0; $t < count($result_array_quest); $t++) {
            if ($result_array_quest[$t] != $user - uid) {
                $user_quest = "select * from {users} where status='1' and uid='$result_array_quest[$t]' ";
                $user_qryqlist = db_query($user_quest);
                $user_resultrym = db_fetch_object($user_qryqlist);

                $suggest_follow .= '<li>
	<h3><a href="' . $gSitePath . 'user/' . $user_resultrym->uid . '">' . $user_resultrym->name . '</a>      </h3>
	<h4>' . $user_resultrym->mail . '</h4>
	
	</li><a class="linkfol" href="follow/' . $user_resultrym->uid . '?act=flag">Follow </a>';
            }
        }


        $suggest_follow .= '</ul>
	</div>
	</div>
	</div>';
    }
    //echo $suggest_follow;


    if ($_REQUEST['act'] == 'flag') {
        $mem_id = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);


        $res_num = db_result(db_query("SELECT COUNT(*) from follower  where  follower_id='" . $mem_id . "'  and  uid ='" . $user->uid . "'"));

        if ($res_num == 0) {
            $ins_commg = "insert into   follower (uid,follower_id,follower_status,joindate) values('" . $user->uid . "','" . $mem_id . "','1','" . date('Y-m-d') . "') ";
            $rs_commg = db_query($ins_commg);

            drupal_set_message(t('Successfully Added as Follower'), $type = 'success');
        } else {
            $sel_usermdet = "select * from users  where uid='" . $mem_id . "' ";
            $rs_usernam = db_query($sel_usermdet);
            $namelist = db_fetch_object($rs_usernam);

            drupal_set_message(t('You are already following ' . $namelist->name . '.'), $type = 'error');
        }
        drupal_goto("suggest/follow");
    }

    $numt = count($result_array_quest);
    $numi = count($result_array);
    if (($numt == 0) && ($numi == 0)) {
        $suggest_follow .= 'No suggested Users';
    }
    return $suggest_follow;
}

function save_follow() {

    $follid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    if (isset($_GET['delete'])) {
        $query = 'DELETE FROM follower WHERE id = ' . (int) $_GET['delete'];
        $result = db_query($query);
    }
}

function save_follower() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    $follid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    if (isset($_GET['action'])) {
        $del_blog = "update  follower  set follower_status='" . $_REQUEST['blk'] . "' where  id='" . $_GET['action'] . "' ";
        $rs_blog_del = db_query($del_blog);


        $sel_userms = "select * from users  where uid='" . $_GET['usid'] . "' ";
        $rs_userms = db_query($sel_userms);
        $resulrnames = db_fetch_object($rs_userms);
        if ($_REQUEST['blk'] == 0) {
            $blkid = '1';
            $valss = 'UnBlock';

              $input =($_REQUEST['show'])?'<span style="padding-left:17px;">&nbsp;</span>':'';
            if ($resulrnames->notify_itype == 1) {
                $insert_notify = db_query("insert into notification (uid,is_block,is_user,node_id) values('" . $_GET['usid'] . "','1','1','" . $user->uid . "' ");
            }
            if ($resulrnames->notify_etype == 1) {
                $sel_user_cmt = "SELECT * FROM notification_mail_format Where id='2'";
                $rs_mgmt = db_query($sel_user_cmt);
                $list_content = db_fetch_object($rs_mgmt);
                $contentm = str_replace("#uname#", $resulrnames->name, $list_content->content);
                $contentm = str_replace("#anothername#", $user->name, $contentm);
               //echo  $contentm;
                $subjects = $list_content->subject;
                $mail_success = htmlmail_function($resulrnames->mail, $subjects, $contentm, '');
            }
        } else {
            $valss = 'Block';
            $blkid = '0';
           $input =($_REQUEST['show'])?'<input type="checkbox" name="muid"  value="' . $follower_resultfuser->id . '"/> &nbsp;':'';
        }
        echo '<div id="' . $_REQUEST['ids'] . '" > '.$input.'<a href="' . $gSitePath . 'profile/' . $resulrnames->name . '">' .UserPicture_small($resulrnames->uid).$resulrnames->name . '</a>&nbsp; <a onclick="blockandunblock(' . $_GET['action'] . ',' . $_GET['usid'] . ',' . $blkid . ','.$_REQUEST['show'].')" >' . $valss . '</a>

</div>';
    }
}
function followerlist($umid) {

    global $gSitePath, $user, $gDocPath, $base_root, $base_path;

    $sel_listf = "select * from follower  where follower_id='" . $umid . "' AND uid>0  limit 0,5  ";
    $rs_followerf = db_query($sel_listf);

    $numfoll = db_result(db_query("SELECT COUNT(*)  from follower  where follower_id='" . $umid . "' AND uid>0  "));

    $followeru = array();
    while ($follower_resultfuser = db_fetch_object($rs_followerf)) {

        // $sel_ulist="select * from users  where uid='".$follower_resultfuser->uid."' ";
        $sel_ulist = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $follower_resultfuser->uid . "'";
        $rs_umlog = db_query($sel_ulist);
        $user_namelistf = db_fetch_object($rs_umlog);


        $user_namelistf->name;

        if ($umid == $user->uid) {
            $flink1 = '<a style="color:#F37321;" onclick="blockandunblock(' . $follower_resultfuser->id . ',' . $follower_resultfuser->uid . ',1,0)" >UnBlock</a>';
            $flink2 = '<a style="color:#F37321;" onclick="blockandunblock(' . $follower_resultfuser->id . ',' . $follower_resultfuser->uid . ',0,0)" >Block</a>';
        }

        $bubble = load_bubble($user_namelistf->uid);
        if ($follower_resultfuser->follower_status == 0) {
            $followeru[] = '<li  id="list-' . $follower_resultfuser->id . '"><a href="' . $gSitePath . 'profile/' . $user_namelistf->name . '" rel=\'' . $bubble . '\'>'. UserPicture_small($follower_resultfuser->uid).'</a></li>';

        } else {

             $followeru[] = '<li  id="list-' . $follower_resultfuser->id . '"><a href="' . $gSitePath . 'profile/' . $user_namelistf->name . '" rel=\'' . $bubble . '\'>'.UserPicture_small($follower_resultfuser->uid).'</a></li>';
        }

        
    }

    if ($numfoll > 5) {
        $followeru[] .= '<a style="color:#F37321;" href="javascript:void(0);" onclick="loadfollower(\'' . $gSitePath . 'follower/' . $umid . '\',\'Follower\');">More</a>';
    }
    if ($numfoll == 0) {
        $followeru[] .= '<span style="padding-left:17px;">No Followers Yet</span>';
    }


    return $followeru;
}
function followinglist($uids) {

    global $gSitePath, $user, $gDocPath, $base_root;


    $sel_list = "select * from follower  where uid='" . $uids . "'  and follower_status='1' limit 0,5";
    $rs_foll_list = db_query($sel_list);
    $numfolls = db_result(db_query("SELECT COUNT(*)  from follower  where uid='" . $uids . "'  and follower_status='1'  "));
    $following = array();

    while ($following_list = db_fetch_object($rs_foll_list)) {

        if ($uids == $user->uid) {
            $flinks = '<a onclick="deletefollowing(' . $following_list->id . ')" style="color:#F37321;" >Unfollow</a>';
        }
        //	 $sel_userm="select * from users  where uid='".$following_list->follower_id."' ";
        $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $following_list->follower_id . "'";
        $rs_userm = db_query($sel_userm);
        $user_namelist = db_fetch_object($rs_userm);

        $bubble = load_bubble($following_list->follower_id);

        $following[] = '<li  id="show-' . $following_list->id . '"><a rel=\'' . $bubble . '\' href="' . $gSitePath . 'profile/' . $user_namelist->name . '">'.UserPicture_small($following_list->follower_id).'</a></li>';

        }
    if ($numfolls > 5) {
        $following[] .= '<a style="color:#F37321;" onclick="loadfollowing(\'' . $gSitePath . 'following/' . $uids . '\',\'Following\');">More</a>';
    }
    if ($numfolls == 0) {
        $following[] .= '<span style="padding-left:17px;">Please Follow People</span>';
    }
    return $following;
}

function activities($uid = '') {
    drupal_set_title('Recent Activities');
    global $gSitePath, $user, $gDocPath, $base_root;
    //$uid = $user->uid;


    $strReturn = '<div class="history-tab">';
    //Questions
    $selQ = "(select 1 as tbl,qid,date_added as dat,0 as vars  from {question} where uid='$uid' ORDER BY qid DESC) union
	(select 2 as tbl,qid,vote_pdate as dat,0 as vars  from {possible_answer_vote} where uid='$uid') union
	(select 3 as tbl,qid_rid as qid,date_added as dat,title as vars  from {forum_wave} where uid='$uid' ) union
	(select 4 as tbl,f.qid_rid as qid,w.date_added as dat,wavelet as vars  from {forum_wavelets} w join {forum_wave} as f on f.fid=w.wid where w.uid='$uid' ) union
	(select 5 as tbl,f.qid_rid as qid,l.date_added as dat,f.title as vars  from {forumwave_like} as l join {forum_wave} as f on f.fid=l.wid where l.uid='$uid' ) union
	(select 6 as tbl,u.image_url as qid,f.joindate as dat,u.real_name as vars from {follower} as f join {user_profile} as u on u.uid=f.uid where f.follower_id='$uid' )union
	(select 7 as tbl,qid,posted_date as dat,0 as vars  from {resource} where uid='$uid') union
	(select 8 as tbl,qid,vote_date as dat,0 as vars from {suggest_answer_vote} where uid='$uid') union
	(select 9 as tbl,badge as qid,date_added as dat,badge as vars from {user_badges} where uid='$uid')
	ORDER BY dat DESC LIMIT 0,50 ";
    $fetch = ExecuteQuery($selQ, "select");


    $strReturn.='';

    if (!empty($fetch)) {



        foreach ($fetch as $list) {


            $type = $list['tbl'];

            switch ($type) {


                case '1':
                    //questions
                    $quest = get_question($list['qid']);
                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>Asked</b></span> <span><a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '2':
                    //answered

                    $quest = get_question($list['qid']);
                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>Answered</b></span> <span><a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }

                    break;
                case '3':
                    //New Wave Post
                    $quest = get_question($list['qid']);

                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>New Wave</b></span> <span>' . $list['vars'] . '<span> <b>for</b>  <a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '4':
                    $quest = get_question($list['qid']);
                    //new wavelet
                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>New Wavelets</b></span> <span>' . $list['vars'] . '<span> <b>for</b> Wave <b>in</b><a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '5':

                    //Like this wave
                    $quest = get_question($list['qid']);

                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>I like This Wave</b></span> <span>' . $list['vars'] . '<span> <b>for</b>  <a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '6':
                    //followers
                    $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                    $strReturn .= '<div ><span>' . $date . '</span><span> <b>New Follower</b></span> <span><a href="' . $gSitePath . '/profile/' . $list['vars'] . '">' . $list['vars'] . '  <img src="' . $list['qid'] . '" border="0" width="20" height="20"></a></a></span></div>';
                    break;
                case '7':
                    //New Resources
                    //New Wave Post
                    $quest = get_question($list['qid']);

                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>New Resource posted for </b> <a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '8':
                    //suggest answer answered

                    $quest = get_question($list['qid']);
                    if (!empty($quest)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>Suggested Answer</b></span> <span><a href="' . $gSitePath . $quest->url . '">' . myTruncate($quest->question, '60', '..', '..') . ' </a></span></div>';
                    }
                    break;
                case '9':

                    $bad = db_fetch_object(db_query("select * from {user_badges} as ub join {badges} as b on ub.bid=b.bid where ub.badge='" . $list['vars'] . "'"));

                    //echo "<pre>"; print_r($bad);

                    if (!empty($bad)) {
                        $date = format_date_class($list['dat'], date('Y-m-d h:i:s'));
                        $strReturn .= '<div ><span>' . $date . '</span><span> <b>Awarded Badge </b></span> <span><a title=' . $bad->info . ' href="' . $gSitePath . 'badges/user/' . $bad->bid . '">' . $bad->name . ' </a></span></div>';
                    }



                    break;
                default:
                    drupal_set_message($message = 'Oops, No Recent Activities !', $type = 'error');
                    break;
            }//switch ends
        }//foreach ends
    } else {

        drupal_set_message($message = 'Oops, No Recent Activities !', $type = 'error');
    }
$strReturn.='</div>';
    // return $uid;
    echo $strReturn;
    exit;
}


function get_user_details() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    extract($_REQUEST);
    $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $getuid . "'";
    $rs_userms = db_query($sel_userm);
    $resulrnames = db_fetch_object($rs_userms);
    $gquery = "select ifnull(sum(points),0) as qpt from {tbl_user_points} where uid='" . $getuid . "' group by uid";
    $gpoints = db_result(db_query($gquery));

    if ($resulrnames->gender == 1) {
        $usetype = 'Male';
    } elseif ($resulrnames->gender == 2) {

        $usetype = 'Female';
    } else {
        $usetype = '<b>--</b>';
    }

    //followers
    $sel_list = "select * from follower  where uid='" . $getuid . "'  and follower_status='1' ";
    $rs_foll_list = db_query($sel_list);
    $numfolls = db_result(db_query("SELECT COUNT(*)  from follower  where uid='" . $getuid . "'  and follower_status='1'  "));

    if ($numfolls != 0) {
        while ($following_list = db_fetch_object($rs_foll_list)) {


            $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $following_list->follower_id . "'";
            $rs_userm = db_query($sel_userm);
            $user_namelist = db_fetch_object($rs_userm);


            $following .= '<div class="thumb2"><a href="' . $gSitePath . 'profile/' . $user_namelist->name . '">' . UserPicture_small($user_namelist->uid) . '</a></div>  ';
        }
    } else {
        $following .= 'No Records';
    }

    $sel_listf = "select * from follower  where follower_id='" . $getuid . "'   limit 0,5  ";
    $rs_followerf = db_query($sel_listf);

    $numfoll = db_result(db_query("SELECT COUNT(*)  from follower  where follower_id='" . $getuid . "'   "));

    if ($numfoll != 0) {
        while ($follower_resultfuser = db_fetch_object($rs_followerf)) {


            $sel_ulist = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $follower_resultfuser->uid . "'";
            $rs_umlog = db_query($sel_ulist);
            $user_namelistf = db_fetch_object($rs_umlog);


            $followers .= '  <div class="thumb"><a  title="' . $user_namelistf->name . '" href="' . $gSitePath . 'profile/' . $user_namelistf->name . '">' . UserPicture_small($user_namelistf->uid) . '</a></div>';
        }
    } else {
        $followers .= 'No Records';
    }
    
    function profile_tab($tab='',$uid=''){
    global $gSitePath, $user, $gDocPath, $base_root;
    $output='<div class="history-tab">';
switch($tab){
    case 'info':
           $getuser = user_load($uid);
          $output.='<div id="l1">

            <span  class="tab-historyspan4"><a href="javascript:void(0);" onclick="bio_tog(this);">Bio</a> </span>
            <span  class="tab-historyspan5"><a href="javascript:void(0);" onClick="bio_tog(this);" > Links</a></span>
            </div><br>
';

          $psplit = explode('@', $getuser->urls);
    $ptitle = explode(';', $psplit[0]);
    $purl = explode('||', $psplit[1]);
     $social = explode('||', $getuser->social);
     $bio=trim($getuser->bio);

        $output.='<div id="bio">'.(!empty($bio)?$getuser->bio:"No Bio updated yet").'</div><div style="display:none;" id="link">
            <div class="face_book">
            <h4>Follow me on</h4>
                    <a title="FaceBook" target="_blank" href="' .((!empty($social[0]))?$social[0]:'#'). '"><img align="left" alt="" src="' . path_to_theme() . '/images/face_icon.png"/>Face Book</a> <span>|</span>
                    <a title="Twitter" target="_blank" href="' .((!empty($social[1]))?$social[1]:'#'). '"><img align="left" alt="" src="' .  path_to_theme() . '/images/twitter.png"/>Twitter</a>
            </div>
              <div class="face_book">
              <span class="tab-historyspan4">'.$ptitle[0].'</span>
               <span class="tab-historyspan4"><a href="'.$purl[0].'" target="_blank">'.$purl[0].'</a></span>
                   <br/>
                    <span class="tab-historyspan4">'.$ptitle[1].'</span>
               <span class="tab-historyspan4"><a href="'.$purl[1].'" target="_blank">'.$purl[1].'</a></span>
              </div>
</div>';
        break;
    case 'badge':
        $badges.='';

    //$imageresult=UserPicture($uid);
    $getbadges = "SELECT *,(select count(*) from {user_badges} where uid='$uid' AND bid=ub.bid) as bcnt from {user_badges} as ub join {badges} as b on ub.bid=b.bid where ub.uid='$uid' and ub.status='1' group by ub.bid";
    $badgelist = ExecuteQuery($getbadges, "select");

    foreach ($badgelist as $badgeach) {

        $badges.='<li>' . $badgeach['name'] . '</b>[' . $badgeach['bcnt'] . ']</li>';
    }
    if (empty($badgelist)) {

        $badges.='<li><h3>No Badges Yet !</h3></li>';
    }
    $output.=$badges;
        break;
    case 'history':
             //answers posted

    $get_ans = db_query("select q.*,a.vote_pdate as vdate from {possible_answer_vote} as a join {question} as q on a.qid=q.qid where  q.status='1' and a.uid='" . $uid . "'");

    while ($setans = db_fetch_object($get_ans)) {

        $inc_list .= "<div class='tab-history'><span class='tab-historyspan1'>$setans->vdate</span>  <span class='tab-historyspan2'>answered</span>  <a href='" . $gSitePath . $setans->url . "' class='tab-historyspan3' title='".htmlentities(wordwrap($setans->question, 40,'<br/>'))."' style='".drupal_link_color($user->uid,$setans->qid)."'>".htmlentities(substr($setans->question,0,40))."</a></div>
"; }



    $ins_ans .= $inc_list;

    $inc_ans = ( empty($inc_list)) ? 'No Result' : $ins_ans;
    //answers ends
    //question sposted
    $get_ans = db_query("select q.* from {question} as q where q.uid='" . $uid . "' AND q.status='1' ORDER BY q.qid DESC  LIMIT 0,5");

    while ($setans = db_fetch_object($get_ans)) {

       // $qns_list .= "<li><a href='" . $gSitePath . $setans->url . "'>$setans->question?</a></li>";
 $qns_list .= "<div class='tab-history'><span class='tab-historyspan1'>$setans->date_added</span>  <span class='tab-historyspan2'>Issue Created</span>  <a href='" . $gSitePath . $setans->url . "' class='tab-historyspan3' title='".htmlentities(wordwrap($setans->question, 40,'<br/>'))."' style='".drupal_link_color($user->uid,$setans->qid)."'>".htmlentities(substr($setans->question,0,40))."</a></div>
";
    }
    $inc_qns .= $qns_list;

    $inc_qns = ( empty($qns_list)) ? 'No Result' : $inc_qns;
    //question ends
    $output.='<div id="l1">

            <span  class="tab-historyspan4"><a href="javascript:void(0);" onclick="bio_tog(this);">Issue Added</a> </span>
            <span  class="tab-historyspan5"><a href="javascript:void(0);" onClick="bio_tog(this);" > Issue Voted</a></span>
            </div><br>';
$output.='<div id="bio">'.$inc_qns.'</div><div id="link" style="display:none">'.$inc_ans.'</div>';


        break;
    default:
        $output='No Results';
        break;
}
$output.='</div>';
echo $output;
exit;
}





    $tag = '';
    if (isset($_REQUEST['tag'])) {
        $tag = $_REQUEST['tag'];
    }

    switch ($tag) {

        case 'activity':
            $strReturn = activities($resulrnames->uid);
            break;
        case 'history':
            $strReturn = profile_tab($tag,$resulrnames->uid);
            break;
        case 'badge':
              $strReturn = profile_tab($tag,$resulrnames->uid);
            break;
        case 'info':
              $strReturn = profile_tab($tag,$resulrnames->uid);
            break;
        default:
//badges
           // enthusiast($uid);
            //fanatic($uid);
            //$strReturn = profile($uid);
    }

    
    

      $following = '';
        $newlist = followinglist($resulrnames->uid);
        for ($i = 0; $i < count($newlist); $i++) {
            $following .= '' . $newlist[$i] . '';
        }

        $follower = '';
        $newlist2 = followerlist($resulrnames->uid);
        for ($k = 0; $k < count($newlist2); $k++) {
            $follower .= '' . $newlist2[$k] . '';
        }
        if($user->uid>0&&$user->uid!=$resulrnames->uid)
      $inc = '<li><img src="'.$gSitePath.path_to_theme().'/images/mail.jpg" alt="mail" width="19" height="11" />&nbsp;<a href="javascript:void(0);" onclick="rel_msg(' . $resulrnames->uid . ');" > Contact Contributor</a><span class="separate"></span> <br/><form id="proform" method="post" action="' . $gSitePath . 'postmessage" ><div id="showboxcmt" align="left" style="display:none"><div class="facttop2" >SEND MESSAGE</div><br/><textarea name="msgs" cols="55" row="17" id="msgs"></textarea><input type="hidden" id="actions" name="actions" value="' .$resulrnames->uid. '"/><br/><br/><input type="button" id="usmsg"  value="sendmessage"/></div></form></li>';
        else
            $inc='';
  // echo  request_uri();
    $ret = '<div class="contributer">
          <div class="facttop">
  CONTRIBUTOR
          </div>
          <div class="hm-cen">

            <div>
            <div class="profile-left-c">







<div class="profile-img">

<div class="profile-imgs">
<a href="' . $gSitePath . 'profile/' . $resulrnames->name . '">' . UserPicture($resulrnames->uid) . '</a>
</div>
<div class="profile-con">'.updateProfileBadge($resulrnames->uid).'
</div>
</div>



<div class="clr"></div>
<div style="padding-top:20px">
<span class="profile-gray">Name </span>: ' . $resulrnames->real_name . '<br />
<span class="profile-gray">Location </span>: ' . $resulrnames->state . ',' . $resulrnames->country.'<br />
<span class="profile-gray">Age</span> : ' .$resulrnames->age. '<br />
<span class="profile-gray">Sex</span> : ' . $usetype . '<br />
<span class="profile-gray">Religion</span> : ' .$resulrnames->religion. '<br />
<span class="profile-gray">Ethinicity</span> : ' .$resulrnames->ethnic. '<br />
<span class="profile-gray">Slant </span>: Left<br />
</div>
</div>

<div class="profile-right-c">
<div style="margin-left:8px;">
<ul>
<li><img src="'.$gSitePath.'sites/all/themes/newtheme/images/follow.jpg" alt="img" width="19" height="13" />&nbsp;<a class="linkfol" href="' . $gSitePath . 'profile/' .$resulrnames->name. '?delm=' .$resulrnames->uid. '">Follow</a></li>
'.$inc.'
</ul>
</div>
<div class="clr"></div>
<div class="p-foll-c">Following<br />
<ul>
	' . $following . '
</ul>
</div>
<div class="p-foll-c">Followed by<br />
<ul>
	' . $follower. '
</ul>
</div>
</div>
<div class="clr"></div>

            </div>
            </div><br />


            <div class="clr"></div>


            <div class="clr"></div>
            <div id="page">
       <ul class="mytabs" id="tabs">
            <li class="current"><a href="'.  check_plain(request_uri()).'?tag=info&getuid='.$resulrnames->uid.'">Info</a></li>
            <li><a href="'.  check_plain(request_uri()).'?tag=badge&getuid='.$resulrnames->uid.'">Badges</a></li>
            <li><a href="'.  check_plain(request_uri()).'?tag=activity&getuid='.$resulrnames->uid.'">Activity</a></li>
             <li><a href="'.  check_plain(request_uri()).'?tag=history&getuid='.$resulrnames->uid.'">History</a></li>
        </ul>
        <div style="width:480px;" class="mytabs-container" id="tabs-container">
            Loading. Please Wait...
        </div>
    </div>

          </div>';



    echo $ret;
}

function search_results_user() {
    
    ///vijay2
    
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;


    extract($_REQUEST);
    //echo $_REQUEST['code'];
    $page_name = "searchuser"; //  If you use this code with a different page ( or file ) name then change this
    if (isset($_GET['start'])) {
        $start = $_GET['start'];
    } else {
        $start = 0;
    }
    if (strlen($start) > 0 and !is_numeric($start)) {
        echo "Data Error";
        exit;
    }


    $eu = ($start - 0);
    $limit = 10; // No of records to be shown per page.
    $this1 = $eu + $limit;
    $back = $eu - $limit;
    $next = $eu + $limit;

    $fetresult .= '';
    $name = $_REQUEST['txt_search'];

    if ($name!='')
        $qry .= "(img.real_name LIKE '%" . $name . "%') AND ";
    if ($code!='')
        $qry .= "(img.country LIKE '" . $code . "%') AND ";
    if ($ccode!='')
        $qry .= "(img.state LIKE '" . $ccode . "%') AND ";

    if ($user->uid != '')
        $sel = "SELECT * FROM {users} reg,{user_profile} img WHERE $qry reg.uid<>$user->uid and img.uid=reg.uid AND reg.status='1' ";
    else
        $sel = "SELECT * FROM {users} reg,{user_profile} img WHERE $qry reg.status='1' and img.uid=reg.uid  ";
    //echo $sel;
    $user_qry = db_query($sel);
    if ($user->uid != '')
        $sel_count = db_result(db_query("SELECT COUNT(*) FROM {users} reg,{user_profile} img WHERE $qry reg.uid<>$user->uid and img.uid=reg.uid AND reg.status='1'"));
    else
        $sel_count = db_result(db_query("SELECT COUNT(*) FROM {users} reg,{user_profile} img WHERE $qry reg.status='1' and img.uid=reg.uid "));
    $sel .= " limit $eu, $limit";
    $sel_search = db_query($sel);



    $fetresult = ' <div class="rleft">
      <span>SEARCH RESULTS</span><br />
       <div class="clr"></div>
       <div class="result-item"></div>
       <div class="clr"></div>
       <div class="clr"></div>
       <div class="result-item">
       <div class="rleft">';
    
    while ($user_result = db_fetch_object($sel_search)) {
        if ($user->uid != '') {
            //$flink='<a class="linkfol" href="search/'.$user_result->uid.'?act=flag">Follow </a>';
            //$flink='<a class="linkfol" href="'.$gSitePath.'profile/'.$user_result->uid.'">View </a>';
        }
        $gquery = "select ifnull(sum(points),0) as qpt from {tbl_user_points} where uid='" . $user_result->uid . "'";
        $gpoints = db_result(db_query($gquery));
        
            $fetresult .=  ' <div class="prof-it-1">
                    <div class="lefimg-it-c"><a href="#" onclick="get_profile_details(' . $user_result->uid . ');">' . UserPicture($user_result->uid) . '</a></div>
                    <div class="ritecont-it-c">
            <div>
            <ul>
            <li><a  onclick="get_profile_details(' . $user_result->uid . ');" > ' . $user_result->real_name . '</a></li><br />
           <!--<li>' . $gpoints . '</li><br />-->
            '.updateProfileBadge($user_result->uid).'
            </ul>
            </div>
            </div>
            <div class="clr"></div>
               </div>';

        $fetresult .= $flink;
    }

$fetresult .=  '</div>
       </div>
       <div class="clr"></div>
       <div class="clr"></div>
       <div class="result-item">
       </div>
       
       <div class="clr"></div>';

if ($sel_count == 0) {
        $fetresult .= '<div style="padding-top:10px" align="center"><b>No Search Results </b></div>';
    }

      $fetresult .=  '</div>';

    $fetresult .= '<input type="hidden" name="stype" value="' . $_REQUEST['stype'] . '"/></ul>';


    if ($sel_count > $limit) {

        $fetresult .= "<table align = 'center' width='100%'><tr><td  align='left' width='30%'>";
        if ($back >= 0) {
            $fetresult .= "<a href='$page_name?start=$back&code=$code&txt_search=$name'><font face='Verdana' size='2'>PREV</font></a>";
        }
        $fetresult .= "</td><td align=center width='30%'>";
        $i = 0;
        $l = 1;
       
        for ($i = 0; $i < $sel_count; $i = $i + $limit) {
            if ($i <> $eu) {
                $fetresult .= " <a href='$page_name?start=$i&code=$code&txt_search=$name'><font face='Verdana' size='2'>$l</font></a> ";
            } else {
                $fetresult .= "$l";
            }
            $l = $l + 1;
        }


        $fetresult .= "</td><td  align='right' width='30%'>";
        if ($this1 < $sel_count) {
            $fetresult .= "<a href='$page_name?start=$next&code=$code&txt_search=$name'><font face='Verdana' size='2'>NEXT</font></a>";
        }
        $fetresult .= "</td></tr></table>";
    }
    
    $fetresult .= ' ';


    echo $fetresult;
}

function get_question_details() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path, $apikey;

    extract($_REQUEST);

    $vSql = "select *,q.uid as uid from {question} as q left join {user_profile} as u on q.uid=u.uid where q.status='1' and q.qid='$qsaid'  ";
    $rlist = db_query($vSql);
    $oListquest = db_fetch_object($rlist);
    $qid = $oListquest->qid;
    $vresultm .= '<div><small>' . $oListquest->question . '</small><br/>';
    $vans = "select * from {possible_answer} where  qid=$qsaid order by vote desc";
    //voted answer
    $list_lengthan = db_query("select * from {possible_answer_vote} where qid='" . $qid . "' and uid='" . $user->uid . "'  ");
    $numran = db_result(db_query("SELECT COUNT(*) from {possible_answer_vote} where qid='" . $qid . "' and uid='" . $user->uid . "'"));
    $answer_id = db_fetch_object($list_lengthan);
    $vlist = db_query($vans);
    $chk = '';
    while ($vlistquest = db_fetch_object($vlist)) {
        if ($numran == 0) {
            $answprc = $vlistquest->vote / 100 * $totalvotes;
            $valu = $answprc * 100;
            $vresultm .= '
		 <input name="answer" type="radio" value="' . $vlistquest->paid . '" /> <span class="black11">
		' . $vlistquest->answer . '</span> <br/>  ';
        } else {
            $answprc = $vlistquest->vote / 100 * $totalvotes;
            $valu = $answprc * 100;
            $chk = '';
            if ($answer_id->panswer_id == $vlistquest->paid) {

                $chk = "checked";
            }
            $vresultm .= ' <input name="answer_al" type="radio" ' . $chk . '  value="' . $vlistquest->paid . '" /><span class="black11">
		' . $vlistquest->answer . ' </span> <br/>   ';
        }
        $chk = '';
    }

    $vresultm.='<script>	function formsubmittype(mtype,ids){
		jQuery("#txt_act").val(mtype);
		if(mtype==1)
		{
		
		
		document.getElementById(\'answer_frm\').submit();
		}
		if(mtype==2)
		{
		
		load_invite(\'' . $gSitePath . 'invite/invite_friends?qid=' . $qid . '\',\'Profile \');
		//onclick="load_invite(\'' . $gSitePath . 'c?qid=' . $qid . '\',\'Profile\');
		}
		if(mtype==3)
		{
		loadflagquestion(\'' . $gSitePath . 'qlite/flag/\'+ids,\'Report \');
		
		}
		if(mtype==4)
		{
		loadsuggest(\'' . $gSitePath . 'qlite/suggest/\'+ids,\'Answers \');
		
		}
		if(mtype==5)
		{
		window.location.href="' . $gSitePath . 'mashup/' . $qid . '";
		
		}
		}</script>';
    $vresultm.='
		
       <script type="text/javascript">

        
        function showShareUI() {

		   
		    var act = new gigya.services.socialize.UserAction();

		    act.setUserMessage("Your comment here...");

		   
		    act.setTitle("' . $oListquest->question . '");
		    act.setDescription("' . $oListquest->context . '");

           
		    act.setLinkBack("' . $gSitePath . '' . $oListquest->url . '");

		  
		    act.addActionLink("' . $oListquest->question . '",
		        "' . $gSitePath . '' . $lji[1] . '");

		   
	       

			
			var params = 
			{
			    userAction: act,  	                                  
			    onError: onError,  
			    onSendDone: onSendDone, 
               showEmailButton:true,
               showMoreButton:true
			};

			
			gigya.services.socialize.showShareUI(conf, params);

		}
		
		
		function onError(event) {
		    alert(\'An error has occured\' + \': \' + event.status + \'; \' + event.statusMessage);
		}

		
		function onSendDone(event)
		{
		    document.getElementById(\'status\').style.color = "green";
		    document.getElementById(\'status\').innerHTML = 
                            \'The newsfeed has been posted to: \' 
		            + event.providers;
		}    
	</script>';



    $vresultm .= '   <div class="sharing-section sharing-width paddi40">
        
               <div class="share1">
            <a title="Bookmark" class="share-link" onclick="showShareUI();" href="javascript:void(0);">Bookmark</a> / <a title="Invite" onclick="formsubmittype(2,' . $qid . ');" href="javascript:void(0);" class="share-link">Invite</a>
             </div>
             
						      
             <div align="center" class="share1">
              <a title="Suggest a new answer" class="share-link"  onclick="formsubmittype(4,' . $qid . ');" href="javascript:void(0);">Suggest a new answer</a>
             </div>
             <div class="share3">
        <a title="Create Mashup" class="share-link" onclick="formsubmittype(5,' . $qid . ');" href="javascript:void(0);">&lt;Embed&gt;</a>
             </div>
             <div class="share3">
             <img src="' . $gSitePath . path_to_theme() . '/images/flag.png" alt="flag" align="middle" /><a title="Flag" class="share-link"  onclick="formsubmittype(3,' . $qid . ');" href="javascript:void(0);">Flag</a>    </div>
             
            </div>
			  <div class="clr"></div>
            </div>
              <h3>PERCENTAGE</h3>
              <div class="innerbox"><iframe width="300" height="200" frameborder="0" border="0" src="' . $gSitePath . '/qlite/percent/' . $qid . '" id="frmGooglevotes"/></div>
            </div>
            <div class="clr"/>
            <div>
              <h3>OVERTIME</h3>
              <div class="innerbox"><iframe width="300" height="200" frameborder="0" border="0" src="' . $gSitePath . '/qlite/graph/' . $qid . '" id="frmGooglepercent"/></div>
            </div>
            <div class="clr"/>
            <div>
              <h3>BY AREA</h3>
<div class="innerbox"><iframe width="300" height="200" frameborder="0" border="0" src="' . $gSitePath . '/qlite/map/' . $qid . '" id="frmGooglemap"/></div>
        
            </div>
            <div class="clr"></div>
          ';

    echo $vresultm;
}

function search_report($idb = '') {
    global $gSitePath, $user, $gDocPath, $base_root;
    $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    //echo veni  .$idb;
    echo $output = '<div class="toolbarTabs">
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
	"url":       "' . $gSitePath . 'searchcontent/' . $idb . '?t=per"
	});
	});
	
	$("qTabs2Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("notify-panel"),
	"url":       "' . $gSitePath . 'searchcontent/' . $idb . '?t=time"
	});
	});
	
	$("qTabs3Link").addEvent("click", function(e){
	MochaUI.updateContent({
	"element":  $("notify-panel"),
	"url":       "' . $gSitePath . 'searchcontent/' . $idb . '?t=area"
	});
	});

	
	</script>';
}

function search_content() {
    global $gSitePath, $user, $gDocPath, $base_root;
    $idb = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);

    //echo "kkkkkkkk".$qid;
    $type = $_REQUEST[t];

    switch ($type) {

        case "time":
            $output = '<div id="contents"><iframe id="frmGoogle" src="' . $gSitePath . '/qlite/graph/' . $qid . '" border="0" height="450" frameborder="0" width="100%"></iframe></div>';
            break;
        case "area":
            $output = '<div id="contents"><iframe id="frmGoogle" src="' . $gSitePath . '/qlite/map/' . $qid . '" border="0" height="450" frameborder="0" width="100%"></iframe></div>';
            break;
        case "per":
        default:
            $output = '<div id="contents"><iframe id="frmGoogle" src="' . $gSitePath . '/qlite/percent/' . $qid . '" border="0" height="450" frameborder="0" width="100%"></iframe></div>';
            break;
    }


    $output .= '<div>108 comments &nbsp;&nbsp;&nbsp;' . $numres . ' Resources </div>';

    echo $output;
}

function search_quest_cat() {
    $link1 = '';
    $link2 = '';
    $link3 = '';
    $cid = '';
    $scid = '';
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    if (($_REQUEST['scid'] != '') || ($_REQUEST['cid'] != '')) {
        $suid = $_REQUEST['scid'];
        if ($_REQUEST['cid'] == '') {
            $sel_catm = db_query("select * from category  where cat_id='" . $suid . "'   ");
            $saveresult = db_fetch_object($sel_catm);
            $cid = $saveresult->parent_id;
        } else {
            $cid = $_REQUEST['cid'];
        }

        //$catlist='Category';
        $sel_cat = db_query("select * from category  where cat_id=" . $cid . "   ");
        $saveresult = db_fetch_object($sel_cat);


        $sel_suge = "select * from category  where parent_id=" . $cid . "   ";

        $rs_folwin = db_query($sel_suge);
        $numrancnt = db_result(db_query("SELECT COUNT(*) from  question   where cid=" . $cid . "  "));

        $catlist = '
		<div id="container">
		<div class="feature">
		<div class="l col">
		<ul><li><b><a href="' . $gSitePath . 'searchquestion?cid=' . $cid . '">' . $saveresult->cat_name . '(' . $numrancnt . ')</a></b></li>';

        while ($flwing_result = db_fetch_object($rs_folwin)) {
            //echo "SELECT COUNT(*) from  question   where cid=".$cid." and scid=".$flwing_result->cat_id."";

            $numrancnts = db_result(db_query("SELECT COUNT(*) from  question   where cid=" . $cid . " and scid=" . $flwing_result->cat_id . ""));


            $catlist .= '<li>&nbsp;<a href="' . $gSitePath . 'searchquestion?cid=' . $cid . '&scid=' . $flwing_result->cat_id . '">' . $flwing_result->cat_name . '(' . $numrancnts . ')</li>';
            //echo $flwing_result->cat_id;

            $sel_sugess = "select * from category  where parent_id=" . $flwing_result->cat_id . "   ";
            $rs_folwinss = db_query($sel_sugess);
            while ($sm_result = db_fetch_object($rs_folwinss)) {
                $numrancntss = db_result(db_query("SELECT COUNT(*) from  question   where cid=" . $cid . " and scid=" . $flwing_result->cat_id . " and  sscid=" . $sm_result->cat_id . ""));
                $catlist .= '<li>&nbsp;&nbsp; <a href="' . $gSitePath . 'searchquestion?cid=' . $cid . '&scid=' . $flwing_result->cat_id . '&sscid=' . $sm_result->cat_id . '">' . $sm_result->cat_name . '(' . $numrancntss . ') </a> </li>';
            }
        }
        $catlist .= '</ul></div>
	</div>
	</div>
	';
    } else {

        //$catlist='Category';


        $sel_sugef = "select * from category where parent_id='0'    ";

        $rs_cat = db_query($sel_sugef);


        $catlist = '
		<div id="container">
		<div class="feature">
		<div class="l col">
		<ul>';

        while ($cat_result = db_fetch_object($rs_cat)) {


            $numrancnts = db_result(db_query("SELECT COUNT(*) from  question where  cid=" . $cat_result->cat_id . ""));


            $catlist .= '<li>&nbsp;<a href="' . $gSitePath . 'searchquestion?cid=' . $cat_result->cat_id . '">' . $cat_result->cat_name . '(' . $numrancnts . ')</li>';
        }
        $catlist .= '</ul></div>
	</div>
	</div>
	';
    }
    echo $catlist;
}

?>
