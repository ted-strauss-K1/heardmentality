<?php
// tree menu listing
function forum_list($qid = '') {
    global $gSitePath,$user,$gDocPath,$base_root;
	$output = '';
    $like = '';
	$flag='';
    extract($_REQUEST);

		
    
    $query = "SELECT *,u.uid as uid  FROM {forum_wave} as f  join {user_profile} as u on u.uid=f.uid   where f.qid_rid='$qid' AND f.fid='$wid' AND f.status='1'";
    $list = ExecuteQuery($query, "select");
    
    $output .= '	<script>
	var spath="'.$gSitePath.'";
	</script>
	<script type="text/javascript" src="'.$gSitePath.drupal_get_path('theme', 'heardmentality').'/scripts/mootools-1.2-core.js"></script>
	<script type="text/javascript" src="'.$gSitePath.drupal_get_path('theme', 'heardmentality').'/scripts/mootools-1.2-more.js"></script>
	<script type="text/javascript" src="'.$gSitePath.drupal_get_path('module', 'forum').'/scripts/forum.js"></script>
         
                   
          <script type="text/javascript" src="'.$gSitePath.drupal_get_path('module', 'forum').'/scripts/Overlay.js"></script>
	  <script src="'.$gSitePath.'/misc/jquery.js"></script>
              <script>jQuery.noConflict();
 </script>
     <script src="'.$gSitePath.drupal_get_path('theme', 'newtheme').'/scripts/jbubble.js"></script>
<link rel="stylesheet" href="'.base_path().path_to_theme().'/css/css.css" type="text/css" />
	<link rel="stylesheet" href="'.$gSitePath.drupal_get_path('module', 'quest_lite').'/css/wave.css" type="text/css" />';
    $output.="
        <script>
             jQuery(document).ready(function(){
                        jQuery('body a').each(function()
                        {
                            if( jQuery(this).attr('rel').length>0){

                                jQuery(this).SetBubblePopup({
                                    innerHtml: jQuery(this).attr('rel'),
                                    color:'grey',
                                    imageFolder: '".$gSitePath.drupal_get_path('theme', 'newtheme')."/images/bp_images',

                                });
                            }


                        });
                        });

                        </script>
        ";
    $output .= '	<div class="facttop2">FORUM POSTS</div><div class="">';
    foreach ($list as $forum) {

        
        //$date = cdatetime($forum['date_added']).$forum['date_added'];
        
        $date = format_date_class($forum['date_added'], date());
        $account = user_load($forum['uid']);
        $image = empty($forum['image']) ? 'noimage.jpg' : $forum['image'];
        $name = empty($forum['real_name']) ? $forum['first_name'] : $forum['real_name'];
		//likes or not
        $querylike = "select * from {user_likes} where is_wave='1' AND uid='$user->uid' AND node_id='".$forum['fid']."'";
        $fetch = ExecuteQuery($querylike, "select");
        
        if (count($fetch) < 1||$fetch[0]['is_like']=='0') {
            
            $like .= '<span  id="likelink" ><a href="javascript:void(0);" class="href" onclick="likethis(\'is_wave\','.$wid.',1,this);">Like</a></span>';
        } elseif($fetch[0]['is_like']=='1') {
            
            $like .= '<span id="likelink" > <a href="javascript:void(0);" class="href" onclick="likethis(\'is_wave\','.$wid.',0,this);">Unlike</a></span>';
        }//likes end
		
		//flag
		$flag.='<a href="#wavefooter" onclick="report_forum(\'rwave\','.$wid.');">Report</a>';
        $bubble=load_bubble($account->uid);
        $output .= '
		<div id="waveerr" align="center"></div>
	<div class="comment com-1" style="background:#ECECEF">
	<div class="waveTime">'.$date.'</div>
	<div class="commentAvatar">
				'.UserPicture_small($account->uid).'
				</div>
				<div class="commentText" >
				<span class="name" ><a  rel=\''.$bubble.'\' href="'.$gSitePath.'profile/'.$account->name.'">'.$name.'</a>:</span>  '.$forum['title'].'
				</div>
				<div class="replyLink">
				'.$like.'<b> | </b><span>'.$flag.'</span><span><b> | </b></span><a class="rep" id="'.$wid.'-0" href="#wavefooter">add a reply »</a>
				</div>
				<div class="clear"></div>
			</div></div>
			<div id="wavelet-list">
			';

    
    }
    $output .= get_wavelets($wid, 0);
    $output .= '	</div><div class="wavefooter">

<!--	<input type="button" class="waveButtonMain"  value="Add Comment" id="newwaveletbut"/>-->
		</div>';
    
    $output .= '<div id="commentArea" class="waveletmain-add" style="display:none;"> <div class="waveComment addComment">  ';
    
    if (! empty($user->uid)) {
        $output .= '
		<div class="comment">			
		
		<div class="commentText">			
		<textarea name="waveletcmt" id="waveletcmt" cols="70" rows="2"  class="textArea"></textarea>
		<input type="hidden" name="waveid" id="waveid" value=""/>
		<input type="hidden" name="wletid" id="wletid" value=""/>
			<input type="hidden" name="burl" value="'.$gSitePath.'" id="burl"/>
		<div><span><input type="checkbox" name="privt" value="1" id="privt"/></span> <span><small>Private Reply</small> </span><span> <input type="button" value="Add comment" id="waveButton" class="waveButton"/> </span><span>  or <a onclick="cancelAdd(this);return false" id="wavecancel" href="javascript:void(0);">cancel</a></span> </div>	
		</div>	
		</div>	';
    } else {
        
        $output .= '<div id="waveletcmt"  align="center"><b>Sorry Only Logged in user can post wave</b><input type="hidden" name="waveid" id="waveid" value=""/>
		<input type="hidden" name="wletid" id="wletid" value=""/></div>';
    }
	
	
    $output .= '</div></div>';
$output.='<div class="comment" id="freport" style="background:#ECECEF;display:none;">';
	$output.='<form  action="'.$gSitePath.'qlite/flagreport" method="post" id="flagform">
	<input type="hidden" value="" id="rwave" name="rwave"/>
	<input type="hidden" value="" id="rwavelet" name="rwavelet"/>
	<div class="cmt_list">  <p id="log_res"><span>Report the Post</span> </p></div>
	<div class="txt_area">
	<input type="radio" checked="checked" value="Pornography or obscenity" id="abuse_type" name="abuse_type"/>
	Pornography or obscenity <br/><input type="radio" value="radically or ethnically hateful content" id="abuse_type" name="abuse_type"/>
	radically or ethnically hateful content  <br/> <input type="radio" value="Graphic Violence" id="abuse_type" name="abuse_type"/>
	Graphic Violence <br/><input type="radio" value="other content inappropirate for young Viewers" id="abuse_type" name="abuse_type"/>
	other content inappropirate for young Viewers <br/>
	<input type="submit" value="Report Problem" class="waveButton" id="submitter" name="button"/>  or <a onclick="cancelAdd(this);return false" id="wavecancel1" href="">cancel</a>   </div>
	</form><div>';
	
    
    echo $output;


}

function cmt_submit() {
    extract($_REQUEST);
    global $gSitePath,$user,$gDocPath,$base_root;
    $output = '';
    
     if(empty($user->uid)){
        
        echo "<small>Sorry, Please login to do this action!</small>";
        exit;
    }
    
    if (isset($_REQUEST['like'])) {
        
        $cond = " AND ".$action."='1'";
        $set = " ".$action."='1'";
        
        $query = "select * from {user_likes} where node_id='$nodeid' $cond AND uid='$user->uid'";
        
        $chk = db_result(db_query($query));
      
        if (!$chk) {
            
            $query = "insert into {user_likes} set $set ,node_id='$nodeid',uid='$user->uid',is_like='$like'";
            
            $chk = db_query($query);
			//guru points
		  insertpoints($action, $nodeid);
		  //notification
			if($action=='is_wave'||$action=='is_wavelets')
				like_notification($nodeid,$set);
			
            
            //	echo "<b>Thank you for liking, Have a great day!";
        echo '<span id="likelink" > <a href="javascript:void(0);" class="href" onclick="likethis(\''.$action.'\','.$nodeid.',0,this);">Unlike</a></span>';
        } else {
            $query = "update {user_likes} set is_like='$like' where $set AND node_id='$nodeid' AND uid='$user->uid'";
          $chk = db_query($query);
			if($like){
				
			echo '<a href="javascript:void(0);" class="href" onclick="likethis(\''.$action.'\','.$nodeid.',0,this);">Unlike</a>';
			}else{
				
			echo '<a href="javascript:void(0);" class="href" onclick="likethis(\''.$action.'\','.$nodeid.',1,this);">Like</a>';
			}
			
			
            //echo "<b>Sorry, Already u liked this wave!</b>";
        }

        
        exit;
    } else {
        //print_r($_REQUEST);

        
        $query = "insert into {forum_wavelets} set wid='$wid',uid='$user->uid',parentid='$wlet',wavelet='".mysql_escape_string($cmt)."',private='$pvt'";
        
        $wlid = ExecuteQuery($query, "insert");
     
        
        echo $output = get_wavelets($wid, 0); 
		
		  post_notification($wid,$wlid);
        exit;
    }

}
function post_notification($wid='',$wlid=''){
    
 global $gSitePath,$user,$gDocPath,$base_root;
	////////////mail notication for user follwers to me//////////////////////////////////////
		 $sel_listf = "select * from follower  where follower_id='".$user->uid."'   ";
		$rs_followerf = db_query($sel_listf);
		 $sel_wave = db_fetch_object(db_query("select * from {forum_wave} where fid='$wid'"));
		 
		   $qdetails = load_question($sel_wave->qid_rid);
		 $sel_wavelet = db_fetch_object(db_query("select * from {forum_wavelets} where wlid='$wlid' AND uid='$user->uid'"));
		while ($follower_resultfuser = db_fetch_object($rs_followerf))
		{

			$sellist="select * from users where uid='".$follower_resultfuser->uid."'";
			$res_users=db_query($sellist);
			$usert=db_fetch_object($res_users);
			 $to = $usert->mail;
		if($usert->notify_itype==1)
		{


		db_query("insert into {notification} set follower_action='1',is_wavelets='1',uid='$follower_resultfuser->uid',node_id='$nid' ");
		}
		if($usert->notify_etype==1)
		{

		///////////email for following ///////////////

		$sel_user_cmt="SELECT * FROM notification_mail_format Where id='5'";
		$rs_mgmt=db_query($sel_user_cmt);
		$list_content=db_fetch_object($rs_mgmt);
		$subject_proj=$list_content->subject;
		$contentm=str_replace("#uname#",$usert->name,$list_content->content);
		$contentm= str_replace("#anothername#",$user->name,$contentm);
		
		 $contentm = str_replace("#question#", rtrim($qdetails['question'], '?') . '?', $contentm);
            $contentm = str_replace("#link#", $gSitePath . $qdetails['url'], $contentm);
		 $contentm = str_replace("#content#", "posted a reply['.$sel_wavelet->wavelet.'] under Forum Topic [" . $sel_wave->title . "] for the below question. Kindly have a review", $contentm);

		//echo $contentm;
		$mail_success = htmlmail_function($to,$subject_proj,$contentm,'');
		}

		}

}
function like_notification($nid='',$set=''){
	 global $gSitePath,$user,$gDocPath,$base_root;
	////////////mail notication for user follwers to me//////////////////////////////////////
		 $sel_listf = "select * from follower  where follower_id='".$user->uid."'   ";
		$rs_followerf = db_query($sel_listf);
		while ($follower_resultfuser = db_fetch_object($rs_followerf)) 
		{
		
			$sellist="select * from users where uid='".$follower_resultfuser->uid."'";
			$res_users=db_query($sellist);
			$usert=db_fetch_object($res_users);
			 $to = $usert->mail;
		if($usert->notify_itype==1)
		{
		
		
		db_query("insert into {notification} set is_like='1',$set,uid='$follower_resultfuser->uid',node_id='$nid' ");	
		}
		if($usert->notify_etype==1)
		{
		
		///////////email for following ///////////////
		
		
		
		
		
		$sel_user_cmt="SELECT * FROM notification_mail_format Where id='5'";
		$rs_mgmt=db_query($sel_user_cmt);
		$list_content=db_fetch_object($rs_mgmt);
		$subject_proj=$list_content->subject;
		$contentm=str_replace("#uname#",$usert->name,$list_content->content);
		$contentm= str_replace("#anothername#",$user->name,$contentm);
		//echo $contentm;
		$mail_success = htmlmail_function($to,$subject_proj,$contentm,'');
		}
		
		}
       
}



function get_wavelets($wid = '', $pid = '') {
    global $gSitePath,$user,$gDocPath,$base_root;
    $output = '';
    $bg = '';
    if (! empty($wid)) {

        
        $query = "select * from {forum_wavelets} as f  join {user_profile} as u on u.uid=f.uid  where f.wid='$wid' and f.status='1' and parentid='$pid'";
        
        $list = ExecuteQuery($query, "select");
        
        //print_r($set);
        
        foreach ($list as $forum) {
            
            // $date = cdatetime($forum['date_added']).$forum['date_added'];
            $date = format_date_class($forum['date_added'], date());
            $account = user_load($forum['uid']);

            
            if (wave_access($forum['wlid'], $forum['private'])) {
                
                $image = empty($forum['image']) ? 'noimage.jpg' : $forum['image'];
                $name = empty($forum['real_name']) ? $forum['first_name'] : $forum['real_name'];
                $querylike = "select * from {user_likes} where is_wavelets='1' AND uid='$user->uid' AND node_id='".$forum['wlid']."'";
        $fetch = ExecuteQuery($querylike, "select");
        $like='';
        if (count($fetch) < 1||$fetch[0]['is_like']=='0') {
            
            $like .= '<span  id="likelink" ><a href="javascript:void(0);" class="href" onclick="likethis(\'is_wavelets\','.$forum['wlid'].',1,this);">Like</a></span>';
        } elseif($fetch[0]['is_like']=='1') {
            
            $like .= '<span id="likelink" > <a href="javascript:void(0);" class="href" onclick="likethis(\'is_wavelets\','.$forum['wlid'].',0,this);">Unlike</a></span>';
        }
		
		//flag
		$flag='';
		$flag.='<a href="#wavefooter" onclick="report_forum(\'rwavelet\','.$forum['wlid'].');">Report</a>';
		
			/////////vijay
                        $bubble=load_bubble($account->uid);
                $output .= '
							<div class="waveComment com-'.$forum['wlid'].'" '.$bg.'>
							<div class="comment">
							<div class="waveTime">'.$date.'</div>
							<div class="commentAvatar">
                                                            '.  UserPicture_small($account->uid).'
									</div>
	                            
							<div class="commentText" >
							<span class="name hyp_up"><a rel=\''.$bubble.'\' href="'.$gSitePath.'profile/'.$name.'">'.$name.'</a>:</span>  '.make_clickable($forum['wavelet']).'
							</div>
							<div class="replyLink hyp_up">'.$like.' <b> | </b><span>'.$flag.'</span>  <span> <b>|</b> </span> 
							<a class="rep" id="'.$wid.'-'.$forum['wlid'].'" href="#wavefooter">add a reply »</a>
							</div>
							<div class="clear">
						</div>
						</div>
	
					';
                $output .= get_wavelets($wid, $forum['wlid']);
                
                $output .= '		</div>';
            
            }
        }
        return $output;
    
    } else {

        
        return '';
    }


}

function wave_access($id = '', $pvt = '') {
    global $gSitePath,$user,$gDocPath,$base_root;

    
    if ($pvt == 1) {
        $query = "select *,f.uid as uid from {forum_wavelets} as f left join {user_profile} as u on u.uid=f.uid  where f.wlid='$id' ";
        
        $list = ExecuteQuery($query, "select");
        //print_r($list);
        
        if ($list[0]['uid'] == $user->uid) {
            
            return true;
        } else {
            
            //followers or following
            
            $query = "(select count(*) as a from {follower} where uid='".$list[0]['uid']."' AND follower_id='$user->uid') union (select count(*) as b from {follower} where uid='$user->uid' AND follower_id='".$list[0]['uid']."') ";
            
            $fet = ExecuteQuery($query, "select");
            
            if ($fet[0]['a'] || $fet[0]['b']) {
                return true;
            }

        
        }

    
    } else {
        
        return true;
    }
    
    return false;
}

function admin_forum() {
    global $gSitePath,$user,$gDocPath,$base_root;
    $strReturn = '';

    drupal_add_js(drupal_get_path('module', 'forum').'/scripts/admin_forum.js');
    // print_r($_REQUEST);
    if (isset($_REQUEST['fdelete']) && $_REQUEST['delete'] == 1) {
        //echo $_REQUEST['fid'];
        //$ids=(!empty($_REQUEST['fid']))?$_REQUEST['fid']:$_REQUEST['fids'];
        $qid = $_REQUEST['fid'];
        
        db_query("delete from {forum_wave} where fid in ($qid)");
        
        db_query("delete from {forum_wavelets} where wid in ($qid)");
        drupal_set_message($message = 'Forum wave & wavelets deleted successfully!', $type = 'success');
        drupal_goto('admin/forum');
    } elseif (isset($_REQUEST['Inactive'])) {
        
        $ids = implode(',', $_REQUEST['qids']);
        if (! empty($ids)) {
            db_query("update {forum_wave} set status='0' where fid in ($ids)");
            db_query("update {forum_wavelets} set status='0' where wid in ($ids)");
            drupal_set_message($message = 'Forum wave & wavelets InActive  successfully!', $type = 'success');
        
        } else {
            
            drupal_set_message($message = 'Sorry no Waves Selected', $type = 'error');
        }
    
    } elseif (isset($_REQUEST['Active'])) {
        
        $ids = implode(',', $_REQUEST['qids']);
        if (! empty($ids)) {
            db_query("update {forum_wave} set status='1' where fid in ($ids)");
            db_query("update {forum_wavelets} set status='1' where wid in ($ids)");
            drupal_set_message($message = 'Forum wave & wavelets Activated  successfully!', $type = 'success');
        
        } else {
            
            drupal_set_message($message = 'Sorry no Waves Selected', $type = 'error');
        }
    
    }

    
    $query = "select f.*,u.*,DATE_FORMAT(f.date_added, '%a %M %Y %h:%i %p') as date_added,IFNULL((select count(*) from {forum_wavelets} as wl where wl.wid=f.fid group by wl.wid ),0) as cntpost,IFNULL((select count(*) from {forumwave_like} as l where l.wid=f.fid group by l.wid),0) as cntlike,IFNULL((select count(*) from {user_likes} where is_wave='1' AND node_id=f.fid group by node_id),0) as cntlikes,IFNULL((select count(*) from {question_flags} where type='wave' and nodeid=f.fid group by nodeid),0) as cntflag from {forum_wave} as f  join {user_profile} as u on u.uid=f.uid ORDER BY f.fid DESC ";
    $list = ExecuteQuery($query, "select");
    //pagination
    
    $nodes_per_page = 2;
    
    /* $rs = pager_query($query,$nodes_per_page,0,count($list));
     $array=array();
     while($rw = db_fetch_array($rs))
     {
     array_push($array,$rw);
     }
     //pagination */

    
    $strReturn .= '<div class="clear-block">
	
	<div align="right"></div>
	<form id="fadmin" method="post" action="'.url($_GET['q'], array('absolute'=>true)).'" >
	<input type="hidden" name="fdelete" id="fdelete" value=""/>
	<input type="hidden" name="fid" id="fid" value=""/>
	<table width="98%" border="1" cellspacing="5" cellpadding="5">
	<tr><td><b><i>Forum Topics</i></b></td><td><i><b># Wavelets</b></i></td><td><i><b># Likes</b></i></td><td><i><b>Posted By</b></i></td><td><i><b>#Flags</b></i></td><td><i><b>Status</b></i></td><td><i><b>Date</b></i></td><td><i><b>Action</b></i></td></tr>
	';
    foreach ($list as $quest) {
        
        if ($quest['type'] == 1) {
            
            $vSql = "select * from {question} where qid='".$quest['qid_rid']."' ";
            $rlist = db_query($vSql);
            $oListquest = db_fetch_object($rlist);
        }
		
		//flag report
			$flag_report='';
		if($quest['cntflag']>0){
			   $fquery = "select u.real_name,l.* from {question_flags} as l join {user_profile} as u on u.uid=l.uid  where l.type='wave' AND l.nodeid='".$quest['fid']."' ORDER BY flag_date DESC";
  			  $flaglist = ExecuteQuery($fquery, "select");
			  foreach($flaglist as $flist){
			  	$flag_report.='<span>Flagged by '.$flist['real_name'].'</span>';
			$flag_report.='<span> as '.$flist['abuse_type'].'</span>';
			$flag_report.='<span> on '.$flist['flag_date'].'</span><hr/>';
				
			  }
			
		}
		
		
		
        $rand = rand(10, 100);
        $stat = ($quest['status'] == 1) ? 'Active' : 'InActive';
        $date = format_date_class($quest['date_added'], date('Y-m-d H:m:s'));
        //$date= date_format('Y-m-d H:m:s',$quest['date_added']);
        
        $strReturn .= '<tr><td>';
        $strReturn .= '<a href="javascript:void(0);" onclick="toggle_sub('.$quest['qid_rid'].$rand.');">'.wordwrap($quest['title'], 40, '<br/>').'</a>';
        $strReturn .= '</td>';
        $strReturn .= '<td><a href="'.$gSitePath.'admin/wavelets/'.$quest['fid'].'">'.$quest['cntpost'].'</a></td><td>'.$quest['cntlike'].'</td>
		<td>'.$quest['real_name'].'</td><td>'.$quest['cntflag'].'</td><td>'.$stat.'</td><td>'.$date.'</td><td>';
        
        $strReturn .= '<input type="checkbox" class="check-me" name="qids[]" value="'.$quest['fid'].'" /> <b>|</b> <a href="javascript:void(0);" onclick="forum_del('.$quest['fid'].');">Delete</a> <b>|</b><a href="'.$gSitePath.'admin/forum/edit/'.$quest['fid'].'">Edit</a>  ';
        
        $strReturn .= '</td></tr>';
        $strReturn .= '<TR > <TD height="0" COLSPAN=8><div style="display:none;" id="q'.$quest['qid_rid'].$rand.'"><b>Posted For Question :</b><a  href="'.$gSitePath.$oListquest->url.'">'.wordwrap($oListquest->question, 80, '<br/>').'</a>&nbsp;'.$flag_report.'</div></TD> </TR>
';
    }

    
    if (count($list) < 1) {
        //  drupal_set_message($message = 'No Questions Found!', $type = 'error');
        $strReturn .= ' <div class="error" align="left" >No Result Found!</div> ';
    } else {
        
        $strReturn .= '</table>
		<div><input type="submit" name="Inactive" value="Inactive" />   <input type="submit" name="Active" value="Active" /><span onclick="checkall(1);">Check All</span>&nbsp;<span onclick="checkall(0);">Uncheck All</span></form>
		</div>';
    }
    $strReturn .= theme('pager', NULL, 10);
    
    return $strReturn;
}


function admin_forum_edit() {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    $strReturn = '';
    $fid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    
    if (isset($_REQUEST['fsubmit'])) {
        extract($_REQUEST);
        if (! empty($ftopic)) {
            
            $query = "update {forum_wave} set title='".mysql_escape_string($ftopic)."' where fid='$fid'";
            
            $up = db_query($query);
            drupal_set_message($message = 'Thank you Topic updated', $type = 'success');
            drupal_goto('admin/forum');
        } else {
            
            drupal_set_message($message = 'Topic should not be empty!', $type = 'error');
        
        }
    
    }

    
    drupal_add_js(drupal_get_path('module', 'forum').'/scripts/admin_forum.js');
    $query = "select f.*,DATE_FORMAT(f.date_added, '%a %M %Y %h:%i %p') as date_added,IFNULL((select count(*) from {forum_wavelets} as wl where wl.wid=f.fid group by wl.wid ),0) as cntpost,IFNULL((select count(*) from {forumwave_like} as l where l.wid=f.fid group by l.wid),0) as cntlike from {forum_wave} as f where f.fid='$fid' ";
    $list = ExecuteQuery($query, "select");
    
    $strReturn .= '<div class="clear-block">
	<div align="right"></div>
	<form id="qadmin" method="post" action="'.url($_GET['q'], array('absolute'=>true)).'" >
	<table width="98%" border="0" cellspacing="5" cellpadding="5">
	<tr><td align="left"><b>Edit Forum Topic</b> </td></tr>
	<tr><td align="left"><textarea cols="40" rows="17" name="ftopic" id="ftopic" >'.$list[0]['title'].'</textarea> </td></tr>
	<tr><td align="left"><input type="submit" name="fsubmit" value="Update"/> <span> </span><input type="button" name="fback" value="Back" onclick="window.location.href=\''.$gSitePath.'admin/forum\';"/></td></tr>
	</form>
	';
    
    return $strReturn;
}


function admin_forum_wlets() {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    $strReturn = '';
    drupal_add_js(drupal_get_path('module', 'forum').'/scripts/admin_forum.js');
    $wid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    
    if (isset($_REQUEST['fdelete']) && $_REQUEST['fdelete'] == 1) {
        //echo $_REQUEST['fid'];
        //$ids=(!empty($_REQUEST['fid']))?$_REQUEST['fid']:$_REQUEST['fids'];
        $qid = $_REQUEST['fid'];

        
        db_query("delete from {forum_wavelets} where wlid in ($qid)");
        drupal_set_message($message = 'wavelets deleted successfully!', $type = 'success');
        drupal_goto('admin/wavelets/'.$wid);
    } elseif (isset($_REQUEST['Inactive'])) {
        
        $ids = implode(',', $_REQUEST['qids']);
        if (! empty($ids)) {
            
            db_query("update {forum_wavelets} set status='0' where wlid in ($ids)");
            drupal_set_message($message = 'Forum wavelets InActive  successfully!', $type = 'success');
        
        } else {
            
            drupal_set_message($message = 'Sorry no Wavelets Selected', $type = 'error');
        }
    
    } elseif (isset($_REQUEST['Active'])) {
        
        $ids = implode(',', $_REQUEST['qids']);
        if (! empty($ids)) {
            
            db_query("update {forum_wavelets} set status='1' where wlid in ($ids)");
            drupal_set_message($message = 'Forum  wavelets Activated  successfully!', $type = 'success');
        
        } else {
            
            drupal_set_message($message = 'Sorry no Wavelets Selected', $type = 'error');
        }
    
    }

    
    $query = "select *, IFNULL((select count(*) from {forum_wavelets} as wl where wl.parentid=f.wlid group by wl.wid ),0) as cntpost,IFNULL((select count(*) from {user_likes} where is_wavelets='1' and node_id=f.wlid group by node_id ),0) as cntlike,IFNULL((select count(*) from {question_flags} where type='wavelet' and nodeid=f.wlid group by nodeid),0) as cntflag from {forum_wavelets} as f  join {user_profile} as u on u.uid=f.uid where f.wid='$wid'";
   
    $list = ExecuteQuery($query, "select");
    
    $strReturn .= '<div class="clear-block">
	
	<div align="right"><a href="'.$gSitePath.'admin/forum">Back To Forum </a></div>
	<form id="fadmin" method="post" action="'.url($_GET['q'], array('absolute'=>true)).'" >
	<input type="hidden" name="fdelete" id="fdelete" value=""/>
	<input type="hidden" name="fid" id="fid" value=""/>
	<table width="98%" border="1" cellspacing="5" cellpadding="5">
	<tr><td><b><i>Wavelets</i></b></td><td><b><i># Reply</i></b></td><td><b><i># Likes</i></b></td><td><b><i># flag</i></b></td> <td><b><i>Posted By</i></b></td><td><i><b>Status</b></i></td><td><i><b>Date</b></i></td><td><i><b>Action</b></i></td></tr>
	';
    foreach ($list as $quest) {

        
        $stat = ($quest['status'] == 1) ? 'Active' : 'InActive';
        $date = format_date_class($quest['date_added'], date('Y-m-d H:m:s'));
        //$date= date_format('Y-m-d H:m:s',$quest['date_added']);
        	$flag_report='';
		if($quest['cntflag']>0){
			   $fquery = "select u.real_name,l.* from {question_flags} as l join {user_profile} as u on u.uid=l.uid  where l.type='wavelet' AND l.nodeid='".$quest['wlid']."' ORDER BY flag_date DESC";
  			  $flaglist = ExecuteQuery($fquery, "select");
			  foreach($flaglist as $flist){
			  	$flag_report.='<span>Flagged by '.$flist['real_name'].'</span>';
			$flag_report.='<span> as '.$flist['abuse_type'].'</span>';
			$flag_report.='<span> on '.$flist['flag_date'].'</span><hr/>';
				
			  }
			
		}
        $strReturn .= '<tr><td>';
        $strReturn .= wordwrap($quest['wavelet'], 40, '<br/>');
        $strReturn .= '</td>';
        $strReturn .= '<td>'.$quest['cntpost'].'</td><td>'.$quest['cntlike'].'</td><td>'.$quest['cntflag'].'</td><td>'.$quest['real_name'].'</td><td>'.$stat.'</td><td>'.$date.'</td><td>';
        
        $strReturn .= '<input type="checkbox" class="check-me" name="qids[]" value="'.$quest['wlid'].'" /> <b>|</b><a href="javascript:void(0);" onclick="wavelet_del('.$quest['wlid'].');">Delete</a> <b>|</b><a href="'.$gSitePath.'admin/wavelets/edit/'.$quest['wlid'].'">Edit</a>  ';
        
        $strReturn .= '</td></tr>';
    
    }

    
    if (count($list) < 1) {
        //  drupal_set_message($message = 'No Questions Found!', $type = 'error');
        $strReturn .= ' <div class="error" align="left" >No Result Found!</div> ';
    } else {
        
        $strReturn .= '</table>
		<div><input type="submit" name="Inactive" value="Inactive" />   <input type="submit" name="Active" value="Active" /><span onclick="checkall(1);">Check All</span>&nbsp;<span onclick="checkall(0);">Uncheck All</span></form>
		</div>';
    }
    
    return $strReturn;

}


function admin_wlets_edit() {
    
    global $gSitePath,$user,$gDocPath,$base_root;
    $fid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
    
    if (isset($_REQUEST['fsubmit'])) {
        extract($_REQUEST);
        if (! empty($ftopic)) {
            
            $query = "update {forum_wavelets} set wavelet='".mysql_escape_string($ftopic)."' where wlid='$fid'";
            
            $up = db_query($query);
            drupal_set_message($message = 'Thank you Topic updated', $type = 'success');
            drupal_goto('admin/wavelets/'.$fid);
        } else {
            
            drupal_set_message($message = 'Wavelet should not be empty!', $type = 'error');
        
        }
    
    }

    
    drupal_add_js(drupal_get_path('module', 'forum').'/scripts/admin_forum.js');
    $query = "select * from {forum_wavelets} where wlid='$fid' ";
    $list = ExecuteQuery($query, "select");
    
    $strReturn .= '<div class="clear-block">
	<div align="right"></div>
	<form id="qadmin" method="post" action="'.url($_GET['q'], array('absolute'=>true)).'" >
	<input type="hidden" name="fid" value="'.$list[0]['wid'].'"/>
	<table width="98%" border="0" cellspacing="5" cellpadding="5">
	<tr><td align="left"><b>Edit Forum Wavelet</b> </td></tr>
	<tr><td align="left"><textarea cols="40" rows="17" name="ftopic" id="ftopic" >'.$list[0]['wavelet'].'</textarea> </td></tr>
	<tr><td align="left"><input type="submit" name="fsubmit" value="Update"/> <span> </span><input type="button" name="fback" value="Back" onclick="window.location.href=\''.$gSitePath.'admin/wavelets/'.$list[0]['wid'].'\';"/></td></tr>
	</form>
	';
    
    return $strReturn;
}




function resforum_list() {
    global $gSitePath,$user,$gDocPath,$base_root;
	 $rid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
	 
	 if(isset($_POST['wtitle'])&&!empty($user->uid)){
						
						  $rid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
						  extract($_POST);
							 $forum = db_query("INSERT INTO {forum_wave} set qid_rid='$rid',type='2',uid='$user->uid',title='".mysql_escape_string($wtitle)."',private='$wprivate' ");	
							echo list_wave($rid,2);						
						exit;
					}elseif(isset($_POST['wtitle'])){
						echo '<div align="center"><b>Sorry Only Logged in user can post wave</b></div>';
						echo list_wave($rid,2);	
						exit;
					}
	 
   // $rid=$_REQUEST['rid'];
    $wave = '';
  $wave .= '	<script>
	var spath="'.$gSitePath.'";
	</script>
	<script type="text/javascript" src="'.$gSitePath.drupal_get_path('theme', 'heardmentality').'/scripts/mootools-1.2-core.js"></script>
	<script type="text/javascript" src="'.$gSitePath.drupal_get_path('theme', 'heardmentality').'/scripts/mootools-1.2-more.js"></script>
	<script type="text/javascript" src="'.$gSitePath.drupal_get_path('module', 'forum').'/scripts/forum.js"></script>
	<link rel="stylesheet" href="'.$gSitePath.path_to_theme().'/css/css.css" type="text/css" />
	
	<link rel="stylesheet" href="'.$gSitePath.drupal_get_path('module', 'quest_lite').'/css/wave.css" type="text/css" />';
 
    //print_r($cnt);
    $wave .= '
	
	<div id="ajaxpage_content">
	<div class="facttop2">FORUM POSTS</div>
		<div class="qwavebut">
	<!--	<input type="button" onclick="newwave(\''.$gSitePath.'question/forum/'.$rid.'?action=new\',\'New Wave\')" value="New Wave" class="waveButtonMain"/> -->
	<input type="button" id="newwavebut" value="New Wave" onclick="toggle();" class="waveButtonMain"/>
		</div>
		<div id="qwave" class="">
		
		';
 $wave.=list_wave($rid,2);
 
 
    $wave .= '</div>
	<div class="comment" id="newwavediv" style="visibility:hidden;">';
	if(!empty($user->uid)){
	$wave.='
	<div align="right"><a href="javascript:void(0);" onclick="$(\'newwavediv\').fade(\'out\');">Close</a></div>
	<form  id="newwaveform" class="newwave" action="'.url($_GET['q'], array('absolute'=>true)).'" method="post" accept-charset="utf-8">
	<div ><b>Post New Wave</b></div>
	<p><textarea row="7" class="textArea" cols="55" name="wtitle" id="wtitle" ></textarea></p>	
	<!--<div ><b>Private Reply :</b> [Only followers can do reply]</div>
	<p><select name="wprivate" id="wprivate">
	<option value="0"> Disabled</option>
	<option value="1"> Enabled  </option>
	</select></p>		-->			
	<input type="hidden" name="type" value="2"/>
	<input type="hidden" name="burl" value="'.$gSitePath.'" id="burl"/>
	<p><input type="button" class="waveButtonMain" onclick="wave_form();" value="Post" /></p>
</form>';
	}
else{
		$wave.='<div align="center"><b>Sorry Only Logged in user can post wave</b></div>';
}
	$wave.='</div>
	<div>
	</div>
	<div class="clr"></div>
	';
  
    echo $wave;


}

////url to hyperlink converting 
function _make_url_clickable_cb($matches) {
	$ret = '';
	$url = $matches[2];
	if ( empty($url) )
		return $matches[0];
	// removed trailing [.,;:] from URL
	if ( in_array(substr($url, -1), array('.', ',', ';', ':')) === true ) {
		$ret = substr($url, -1);
		$url = substr($url, 0, strlen($url)-1);
	}
	return $matches[1] . "<a href=\"$url\" rel=\"nofollow\">$url</a>" . $ret;
}
function _make_web_ftp_clickable_cb($matches) {
	$ret = '';
	$dest = $matches[2];
	$dest = 'http://' . $dest;
	if ( empty($dest) )
		return $matches[0];
	// removed trailing [,;:] from URL
	if ( in_array(substr($dest, -1), array('.', ',', ';', ':')) === true ) {
		$ret = substr($dest, -1);
		$dest = substr($dest, 0, strlen($dest)-1);
	}
	return $matches[1] . "<a href=\"$dest\" rel=\"nofollow\" target=\"_blank\">$dest</a>" . $ret;
}
function _make_email_clickable_cb($matches) {
	$email = $matches[2] . '@' . $matches[3];
	return $matches[1] . "<a href=\"mailto:$email\" target=\"_blank\">$email</a>";
}
function make_clickable($ret) {
	$ret = ' ' . $ret;
	// in testing, using arrays here was found to be faster
	$ret = preg_replace_callback('#([\s>])([\w]+?://[\w\\x80-\\xff\#$%&~/.\-;:=,?@\[\]+]*)#is', '_make_url_clickable_cb', $ret);
	$ret = preg_replace_callback('#([\s>])((www|ftp)\.[\w\\x80-\\xff\#$%&~/.\-;:=,?@\[\]+]*)#is', '_make_web_ftp_clickable_cb', $ret);
	$ret = preg_replace_callback('#([\s>])([.0-9a-z_+-]+)@(([0-9a-z-]+\.)+[0-9a-z]{2,})#i', '_make_email_clickable_cb', $ret);
	// this one is not in an array because we need it to run last, for cleanup of accidental links within links
	$ret = preg_replace("#(<a( [^>]+?>|>))<a [^>]+?>([^>]+?)</a></a>#i", "$1$3</a>", $ret);
	$ret = trim($ret);
	return $ret;
}

