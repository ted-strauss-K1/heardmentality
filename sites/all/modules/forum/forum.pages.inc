<?php
// tree menu listing
function forum_list($qid = '') {
    global $gSitePath,$user,$gDocPath,$base_root;
    $output = '';
    
    extract($_REQUEST);
    //drupal_add_css(drupal_get_path('module', 'quest').'/styles/screen.css');

    
    $query = "SELECT *,u.uid as uid  FROM {forum_wave} as f left join {user_profile} as u on u.uid=f.uid   where f.qid_rid='$qid' AND f.fid='$wid'";
    $list = ExecuteQuery($query, "select");
    
    $output .= '<link rel="stylesheet" href="'.$gSitePath.drupal_get_path('module', 'quest_lite').'/css/wave.css" type="text/css" />';
    
    $output .= '<div class="">';
    foreach ($list as $forum) {
        
        //$date = cdatetime($forum['date_added']).$forum['date_added'];
		  $date = format_date_class($forum['date_added'],date());
        $account = user_load($forum['uid']);

        
        $output .= '
		
	<div class="comment com-1">
	<div class="waveTime">'.$date.'</div>
	<div class="commentAvatar">
				<img width="30" height="30" alt="" src="'.$gSitePath.drupal_get_path('module', 'profile').'/snap/'.$forum['image'].'"/>
				</div>
				<div class="commentText">
				<span class="name">'.$account->name.':</span>  '.$forum['title'].'
				</div>
				<div class="replyLink">
				<a onclick="addComment('.$wid.',0);return false;" href="#">add a reply »</a>
				</div>
				<div class="clear"></div>
			</div></div>
			<div id="wavelet-list">
			';
        
       
    }
    $output.=get_wavelets($wid,0);
    $output .= '	</div><div id="wavefooter">

	<input type="button" class="waveButtonMain"  value="Add Comment" id="newwaveletbut"/>
		</div>';
    
    $output .= '<div id="commentArea" class="waveletmain-add" style="visibility:hidden;">            
        <div class="waveComment addComment">
		<div class="comment">			
		<div class="commentAvatar">	
		<img width="30" height="30" src="img/demo.png"/>	
		</div>	
		<div class="commentText">			
		<textarea name="waveletcmt" id="waveletcmt" cols="70" rows="2"  class="textArea"></textarea>
		<input type="hidden" name="waveid" id="waveid" value=""/>
		<input type="hidden" name="wletid" id="wletid" value=""/>
		<div><input type="button" onclick="addSubmit();return false;" value="Add comment" class="waveButton"/> or <a onclick="cancelAdd(this);return false" href="">cancel</a></div>	
		</div>	
		</div>	
		</div></div>';

    
    echo $output;


}

function cmt_submit(){
	$output='';
	//print_r($_REQUEST);
	extract($_REQUEST);
	 global $gSitePath,$user,$gDocPath,$base_root;
	
	    $query = "insert into {forum_wavelets} set wid='$wid',uid='$user->uid',parentid='$wlet',wavelet='$cmt'";
	   
    $set = ExecuteQuery($query, "insert");
	
	
	
	echo $output=get_wavelets($wid,0);
	exit;
}

function get_wavelets($wid='',$pid=''){
	
	$output='';
	if(!empty($wid)){
		
		
		 $query = "select * from {forum_wavelets} as f left join {user_profile} as u on u.uid=f.uid  where f.wid='$wid' and parentid='$pid'";
	   
    $list = ExecuteQuery($query, "select");
		
		print_r($set);
		
		foreach ($list as $forum) {
       
       // $date = cdatetime($forum['date_added']).$forum['date_added'];
	   $date = format_date_class($forum['date_added'],date());
        $account = user_load($forum['uid']);

        
        $output .= '
		<div class="waveComment com-'.$forum['wlid'].'">
	<div class="comment">
	<div class="waveTime">'.$date.'</div>
	<div class="commentAvatar">
				<img width="30" height="30" alt="" src="'.$gSitePath.drupal_get_path('module', 'profile').'/snap/'.$forum['image'].'"/>
				</div>
				<div class="commentText">
				<span class="name">'.$account->name.':</span>  '.$forum['wavelet'].'
				</div>
				<div class="replyLink">
				<a onclick="addComment('.$wid.','.$forum['wlid'].');return false;" href="#">add a reply »</a>
				</div>
				<div class="clear">
			</div>
			</div>
	
			';
       $output.= get_wavelets($wid,$forum['wlid']);
	   
	   $output.='		</div>';
    }
		return $output;
		
	}else {
		
		
		return '';
	}
	
	
	
	
	
	
}
