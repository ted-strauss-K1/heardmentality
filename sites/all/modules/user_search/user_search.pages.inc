<?php

function search_results() {
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
    $limit = 5; // No of records to be shown per page.
    $this1 = $eu + $limit;
    $back = $eu - $limit;
    $next = $eu + $limit;
    $fetresult = '';
    drupal_add_js(drupal_get_path('module', 'user_search') . '/js/search.js');


    $name = $_REQUEST['txt_search'];
    if (isset($_REQUEST['code'])) {
        $code = $_REQUEST['code'];
    } else {
        $code = '';
    }
    $qry = '';
    if ($name)
        $qry .= "(img.real_name LIKE '" . $name . "%') AND ";
    if (isset($_REQUEST['code']))
        $qry .= "(img.country ='" . $code . "') AND ";

    if ($user->uid != '')
        $sel = "SELECT * FROM {users} reg,{user_profile} img WHERE $qry reg.uid<>$user->uid and img.uid=reg.uid AND reg.status='1' ";
    else
        $sel = "SELECT * FROM {users} reg,{user_profile} img WHERE $qry reg.status='1' and img.uid=reg.uid  ";
    // echo $sel;
    $user_qry = db_query($sel);
    if ($user->uid != '')
        $sel_count = db_result(db_query("SELECT COUNT(*) FROM {users} reg,{user_profile} img WHERE $qry reg.uid<>$user->uid and img.uid=reg.uid AND reg.status='1'"));
    else
        $sel_count = db_result(db_query("SELECT COUNT(*) FROM {users} reg,{user_profile} img WHERE $qry status='1' and img.uid=reg.uid "));
    $sel .= " limit $eu, $limit";
    $sel_search = db_query($sel);

    while ($user_result = db_fetch_object($sel_search)) {
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


        $fetresult .= '<div class="result-item">
		 <div class="first-col"> 
		 <div class="photo"><a href="#" onclick="get_profile_details(' . $user_result->uid . ');">' . UserPicture($user_result->uid) . '</a></div>
		 </div>
		    <div class="second-col">
    <div class="textouter"> <div class="grayt">Username:</div>
    <div class="blakt"><a  onclick="get_profile_details(' . $user_result->uid . ');" > ' . $user_result->real_name . '</a></div>
    </div>
	<div class="clr"></div>
	<div class="textouter"> <div class="grayt">Name:</div>
    <div class="blakt"> ' . $user_result->first_name . '</div>
    </div>
        <div class="clr"></div>
	 <div class="textouter"> <div class="grayt">Sex:</div>
    <div class="blakt">' . $usetype . '</div>
    </div>
    
       <!-- <div class="clr"></div>
		
		<div class="textouter"> <div class="grayt">Points:</div>
    <div class="blakt">' . $gpoints . '</div>
    </div>
     -->
        <div class="clr"></div>
		<div class="textouter"> <div class="grayt">Badges:</div>
     <div class="blakt">'.updateProfileBadge($user_result->uid).'</div>
    </div>
    
    </div>
      
       </div> <div class="clr"></div>
		';
    }

    if ($sel_count > $limit) {

        $fetresult .= "   <div class='result-item factmore'><table align = 'center' width='100%'><tr><td  align='left' width='30%'>";
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
                $fetresult .= "<font face='Verdana' size='4' color=red>$l</font>";
            }
            $l = $l + 1;
        }


        $fetresult .= "</td><td  align='right' width='30%'>";
        if ($this1 < $sel_count) {
            $fetresult .= "<a href='$page_name?start=$next&code=$code&txt_search=$name'><font face='Verdana' size='2'>NEXT</font></a>";
        }
        $fetresult .= "</td></tr></table></div>";
    }
    if ($sel_count == 0) {
        $fetresult .= '<b>No Search Results </b>';
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
   $cat =  explode("/",$_REQUEST['q']);
        $catid = explode("=",$cat[2]);

          $res_num = db_result(db_query("SELECT COUNT(*) from follower  where  cat_id='" .$catid[1]."'  and  uid ='" . $user->uid . "'"));
        
        if(!$res_num){
             db_query("insert into follower(uid,cat_id)values('".$user->uid."','".$catid[1]."')");
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
   $cat =  explode("/",$_REQUEST['q']);
        $catid = explode("=",$cat[2]);

          $res_num = db_result(db_query("SELECT COUNT(*) from follower  where  cat_id='" .$catid[1]."'  and  uid ='" . $user->uid . "'"));


        if($res_num){
             db_query("delete from follower where uid='".$user->uid."' and cat_id='".$catid[1]."'");
            // db_query("delete from follower(uid,cat_id)values('".$user->uid."','".$catid[1]."')");
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
             //db_query("insert into follower(uid,question_id)values('".$user->uid."','".$quesid[1]."')");
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
    if (isset($_GET['cid'])) {
        $cid = $_GET['cid'];
    }
    if (isset($_GET['scid'])) {
        $scid = $_GET['scid'];
    }
    if (isset($_GET['sscid'])) {
        $scid = $_GET['sscid'];
    }
    $eu = ($start - 0);
    $limit = 15; // No of records to be shown per page.
    $this1 = $eu + $limit;
    $back = $eu - $limit;
    $next = $eu + $limit;

    $sel = facetad_refine();
    $sel_count = $sel['qcnt'];
    $sel['query'] .= " limit  $eu, $limit";
    drupal_add_js(drupal_get_path('module', 'user_search') . '/js/search.js');
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

    $sel_search = db_query($sel['query']);
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
        $numresum = db_result(db_query("SELECT COUNT(*) FROM resource where  qid='$user_result->qid'"));
        $fetresult .= ' <div class="result-item">
		
       <div class="titl">
        
	<a href="javascript:void(0);" onclick="get_quest_details(' . $user_result->qid . ',this);" title="'. htmlentities(wordwrap($user_result->question, 40,'<br/>')).'" style="'.drupal_link_color($user->uid,$user_result->qid).'">' . htmlentities(substr(rtrim($user_result->question, "?"),0,70)). '?</a>    </div><div class="rleft">';
        $i = 0;
        while ($vlistquest = db_fetch_object($vlist)) {

           
        $sel_qry = db_query("select * from {possible_answer_vote} where qid='".$user_result->qid."' and uid='".$user->uid."'  ");
        $get_value = db_fetch_object($sel_qry);
       
  
       $sel_ans = db_query("select * from {possible_answer} where paid='".$get_value->panswer_id."'");
       $get_ans = db_fetch_object($sel_ans);

       
        
            $fetresult .= ' <div class="item1"><input name="answer_al['.$i.']" type="radio"  value="' . $vlistquest->paid . '" '.check_select($get_ans->paid,$vlistquest->paid).'  />' . $vlistquest->answer. '</div>';
            $i++;
        }


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
        <a href="'.$gSitePath.'categoryquestion/'.$follow.'/'.'quesid='.$user_result->qid .'">'.$follow.'</a>
      <div class="vote-post-outer">
      <div class="vote-post-outer-top">
	 
	   <div align="center"><a href="#" class="vote-post">' . $totalvotes . '</a></div>
      <div align="center"><a href="#" class="vote-post">' . $numresum . '</a></div>
      </div>';
        $fetresult .= '     <div class="vote-post-outer-bottom">
      <div align="center" class="vot-t">Votes</div>
       <div align="center" class="vot-t">Posts</div>
      
      </div>
      
      </div>
      
      </div>  </div>    
       <div class="clr"></div>
';
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
        $fetresult .= " <div class='result-item factmore'><table align = 'center' width='98%'><tr><td  align='left' width='30%'>";
        //// if our variable $back is equal to 0 or more then only we will display the link to move back ////////
        if ($back >= 0) {
            $fetresult .= "<a class='' href='$page_name?start=$back&$lkr'><font  size='2'>PREV</font></a>";
        }
        //////////////// Let us display the page links at  center. We will not display the current page as a link ///////////
        $fetresult .= "</td><td align=center width='30%'>";
        $i = 0;
        $l = 1;
        for ($i = 0; $i < $sel_count; $i = $i + $limit) {
            if ($i <> $eu) {
                $fetresult .= " <a class='sidelinks' href='$page_name?start=$i&$lkr'><font  size='2'>$l</font></a> ";
            } else {
                $fetresult .= "<font color='black' size='4' >$l</font>";
            } /// Current page is not displayed as link and given font color red
            $l = $l + 1;
        }


        $fetresult .= "</td><td  align='right' width='30%'>";
        ///////////// If we are not in the last page then Next link will be displayed. Here we check that /////
        if ($this1 < $sel_count) {
            $fetresult .= "<a class='sidelinks' href='$page_name?start=$next&$lkr'><font size='2'>NEXT</font></a>";
        }
        $fetresult .= "</td></tr></table></div>";
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

function get_user_details() {
    global $gSitePath, $user, $gDocPath, $base_root, $base_path;
    extract($_REQUEST);
    $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='" . $getuid . "'";
    $rs_userms = db_query($sel_userm);
    $resulrnames = db_fetch_object($rs_userms);
    $gquery = "select ifnull(sum(points),0) as qpt from {tbl_user_points} where uid='" . $getuid . "' group by uid";
    $gpoints = db_result(db_query($gquery));
    //echo $resulrnames->real_name;
    //$ret = $resulrnames->real_name;
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


    $ret = '<div class="inner-commutop">
            <p>PROFILE INFORMATION</p>
		  <div class="inner">
          <div class="result-item width200">
     <div class="first-col"> 
     <div class="photo"><a href="' . $gSitePath . 'profile/' . $resulrnames->name . '">' . UserPicture($resulrnames->uid) . '</a></div>
		 </div>	
	<div class="second-col width200">
    <div class="textouter"> <div class="grayt">Username:</div>
    <div class="blakt"> ' . $resulrnames->name . '</div>
    </div>
    <div class="clr"></div>
    
    <div class="textouter"> <div class="grayt">Name:</div>
    <div class="blakt">' . $resulrnames->real_name . '</div>
    </div>
        <div class="clr"></div>		
		 <div class="textouter"> <div class="grayt">Sex:</div>
    <div class="blakt">' . $usetype . '</div>
    </div>
    
        <div class="clr"></div>
    
    <div class="textouter"> <div class="grayt">Points:</div>
    <div class="blakt">' . $gpoints . '</div>
    </div>
            <div class="clr"></div>
 <div class="textouter"> <div class="grayt">Badges:</div>
    <div class="blakt">'.updateProfileBadge($resulrnames->uid).'</div>
    </div>
          
          </div>
        </div>
      </div>
          </div>
      <div class="clr"></div>
    <div class="outer-foll">
      <div class="navig">
  <ul>
  <li><a href="#" title="History">History</a></li>
  <li>|</li>
  <li><a href="#" title="Edit my profile">Edit My Profile</a></li>
   <li>|</li>
  <li><a href="#" title="Notifications">Notifications</a></li>
   <li>|</li>
  <li><a href="#" title="Follow">Follow</a></li>
  
</ul>
      
  </div>
  <div class="clr"></div>
  
    <div class="left-contd">
  <div class="bio-box">
  <strong>Bio</strong><br />
' . $resulrnames->bio . '
  
  </div>
  
  <div class="followers">
  <div>Followers</div>
  ' . $followers . '
  </div>
  
  </div>    
  
  <div class="right-contd">
  <div class="links-box">
  <strong>Links</strong><br/>
  <a target="_blank" href="' . (!empty($resulrnames->facebook) ? 'http://' . $resulrnames->facebook : '#') . '" class="links">Facebook</a><br/>
  <a target="_blank" href="' . (!empty($resulrnames->twitter) ? 'http://' . $resulrnames->twitter : '#') . '" class="links">Twitter</a><br/>
  
  </div>
  
  <div class="following">
  <div>Following</div>
	' . $following . '
  </div>
  
  </div>
  
  
';

    echo $ret;
}

/*
  function get_user_details() {
  global $gSitePath,$user,$gDocPath,$base_root,$base_path;
  extract($_REQUEST);
  $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='".$getuid."'";
  $rs_userms = db_query($sel_userm);
  $resulrnames = db_fetch_object($rs_userms);
  //echo $resulrnames->real_name;
  //$ret = $resulrnames->real_name;
  if ($resulrnames->gender == 1) {
  $usetype = 'Male';
  } else {

  $usetype = 'Female';

  }
  $ret = '<table width="100%" border="0">
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

  $sel_list = "select * from follower  where uid='".$getuid."'  and follower_status='1' ";
  $rs_foll_list = db_query($sel_list);
  $numfolls = db_result(db_query("SELECT COUNT(*)  from follower  where uid='".$getuid."'  and follower_status='1'  "));

  if ($numfolls != 0) {
  while ($following_list = db_fetch_object($rs_foll_list)) {


  $sel_userm = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='".$following_list->follower_id."'";
  $rs_userm = db_query($sel_userm);
  $user_namelist = db_fetch_object($rs_userm);


  $ret .= '<tr>
  <td>&nbsp;</td>
  <td colspan="2"> <a href="'.$gSitePath.'../profile/'.$user_namelistf->name.'">'.$user_namelist->name.'</a>   </td>
  </tr>';


  }
  } else {
  $ret .= 'No Records';
  }


  $sel_listf = "select * from follower  where follower_id='".$getuid."'   limit 0,5  ";
  $rs_followerf = db_query($sel_listf);

  $numfoll = db_result(db_query("SELECT COUNT(*)  from follower  where follower_id='".$getuid."'   "));

  if ($numfoll != 0) {
  while ($follower_resultfuser = db_fetch_object($rs_followerf)) {


  $sel_ulist = "SELECT * FROM users LEFT JOIN user_profile ON users.uid=user_profile.uid Where users.uid='".$follower_resultfuser->uid."'";
  $rs_umlog = db_query($sel_ulist);
  $user_namelistf = db_fetch_object($rs_umlog);


  $ret .= '<a href="'.$gSitePath.'../profile/'.$user_namelistf->name.'">'.$user_namelistf->real_name.' </a>';


  }
  } else {
  $ret .= 'No Records';
  }

  if ($_REQUEST == '') {
  $ret .= ' <tr>
  <td colspan="3">Select User</td>
  </tr>';

  }
  $ret .= ' <tr>
  <td colspan="3">&nbsp;</td>
  </tr>
  </table>';

  echo $ret;


  }

 */

function search_results_user() {
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
    $limit = 2; // No of records to be shown per page.
    $this1 = $eu + $limit;
    $back = $eu - $limit;
    $next = $eu + $limit;

    $fetresult .= '';
    $name = $_REQUEST['txt_search'];

    if ($name)
        $qry .= "(img.real_name LIKE '" . $name . "%') AND ";
    if ($code)
        $qry .= "(img.country LIKE '" . $code . "%') AND ";

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

    while ($user_result = db_fetch_object($sel_search)) {
        if ($user->uid != '') {
            //$flink='<a class="linkfol" href="search/'.$user_result->uid.'?act=flag">Follow </a>';
            //$flink='<a class="linkfol" href="'.$gSitePath.'profile/'.$user_result->uid.'">View </a>';
        }
        $fetresult .= '<div class="result-item">
		 <div class="first-col"> 
		 <div class="photo"><a href="#" onclick="get_profile_details(' . $user_result->uid . ');">' . UserPicture($user_result->uid) . '</a></div>
		 </div>
		    <div class="second-col">
    <div class="textouter"> <div class="grayt">Username:</div>
    <div class="blakt"><a  onclick="get_profile_details(' . $user_result->uid . ');" > ' . $user_result->real_name . '</a></div>
    </div>
	<div class="clr"></div>
	<div class="textouter"> <div class="grayt">Name:</div>
    <div class="blakt">Loremi</div>
    </div>
        <div class="clr"></div>
	 <div class="textouter"> <div class="grayt">Sex:</div>
    <div class="blakt">Male</div>
    </div>
    
        <div class="clr"></div>
		
		<div class="textouter"> <div class="grayt">Points:</div>
    <div class="blakt">12, 13, 405</div>
    </div>
    
        <div class="clr"></div>
		<div class="textouter"> <div class="grayt">Badges:</div>
    <div class="blakt"><img src="images/yellow-dot.png" alt="yellow badge" />2 <img src="images/violet-dot.png" alt="violet-badges" />4 <img src="images/brown-dot.png" alt="brown badges" />40</div>
    </div>
    
    </div>
      
       </div> <div class="clr"></div>
		';

        $fetresult .= $flink;
    }

    $fetresult .= '<input type="hidden" name="stype" value="' . $_REQUEST['stype'] . '"/></ul>';


    if ($sel_count > $limit) {

        $fetresult .= "<table align = 'center' width='100%'><tr><td  align='left' width='30%'>";
        if ($back >= 0) {
            $fetresult .= "<a href='$page_name?start=$back&code=$code'><font face='Verdana' size='2'>PREV</font></a>";
        }
        $fetresult .= "</td><td align=center width='30%'>";
        $i = 0;
        $l = 1;
        for ($i = 0; $i < $sel_count; $i = $i + $limit) {
            if ($i <> $eu) {
                $fetresult .= " <a href='$page_name?start=$i&code=$code'><font face='Verdana' size='2'>$l</font></a> ";
            } else {
                $fetresult .= "<font face='Verdana' size='4' color=red>$l</font>";
            }
            $l = $l + 1;
        }


        $fetresult .= "</td><td  align='right' width='30%'>";
        if ($this1 < $sel_count) {
            $fetresult .= "<a href='$page_name?start=$next&code=$code'><font face='Verdana' size='2'>NEXT</font></a>";
        }
        $fetresult .= "</td></tr></table>";
    }
    if ($sel_count == 0) {
        $fetresult .= '<b>No Search Results </b>';
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
