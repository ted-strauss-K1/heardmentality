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
        $date = format_date_class($forum['date_added'], date());
        $account = user_load($forum['uid']);

        
        $output .= '
		
	<div class="comment com-1" style="background:#ECECEF">
	<div class="waveTime">'.$date.'</div>
	<div class="commentAvatar">
				<img  alt="'.$forum['name'].'" title="'.$forum['name'].'" src="'.$gSitePath.drupal_get_path('module', 'profile').'/snap/'.$forum['image'].'"/>
				</div>
				<div class="commentText" >
				<span class="name" >'.$account->name.':</span>  '.$forum['title'].'
				</div>
				<div class="replyLink">
				<a id="'.$wid.'-0" href="#commentArea">add a reply »</a>
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
    
    $output .= '<div id="commentArea" class="waveletmain-add" style="visibility:hidden;"> <div class="waveComment addComment">  ';
    
    if (! empty($user->uid)) {
        $output .= '
		<div class="comment">			
		
		<div class="commentText">			
		<textarea name="waveletcmt" id="waveletcmt" cols="70" rows="2"  class="textArea"></textarea>
		<input type="hidden" name="waveid" id="waveid" value=""/>
		<input type="hidden" name="wletid" id="wletid" value=""/>
		<div><input type="checkbox" name="privt" value="1" id="privt" > <small>Private Reply</small> &nbsp;<input type="button" onclick="addSubmit();return false;" value="Add comment" class="waveButton"/> or <a onclick="cancelAdd(this);return false" href="">cancel</a></div>	
		</div>	
		</div>	';
    } else {
        
        $output .= '<div id="waveletcmt"  align="center"><b>Sorry Only Logged in user can post wave</b><input type="hidden" name="waveid" id="waveid" value=""/>
		<input type="hidden" name="wletid" id="wletid" value=""/></div>';
    }
    $output .= '</div></div>';

    
    echo $output;


}

function cmt_submit() {
    $output = '';
    //print_r($_REQUEST);
    extract($_REQUEST);
    global $gSitePath,$user,$gDocPath,$base_root;
    
    $query = "insert into {forum_wavelets} set wid='$wid',uid='$user->uid',parentid='$wlet',wavelet='$cmt',private='$pvt'";
    
    $set = ExecuteQuery($query, "insert");

    
    echo $output = get_wavelets($wid, 0);
    exit;
}

function get_wavelets($wid = '', $pid = '') {
     global $gSitePath,$user,$gDocPath,$base_root;
    $output = '';
    $bg = '';
    if (! empty($wid)) {

        
        $query = "select * from {forum_wavelets} as f left join {user_profile} as u on u.uid=f.uid  where f.wid='$wid' and parentid='$pid'";
        
        $list = ExecuteQuery($query, "select");
        
        print_r($set);
        
        foreach ($list as $forum) {
            
            // $date = cdatetime($forum['date_added']).$forum['date_added'];
            $date = format_date_class($forum['date_added'], date());
            $account = user_load($forum['uid']);

            
            if (wave_access($forum['wlid'],$forum['private'])) {
                $output .= '
							<div class="waveComment com-'.$forum['wlid'].'" '.$bg.'>
							<div class="comment">
							<div class="waveTime">'.$date.'</div>
							<div class="commentAvatar">
								<img  alt="'.$forum['name'].'" title="'.$forum['name'].'" src="'.$gSitePath.drupal_get_path('module', 'profile').'/snap/'.$forum['image'].'"/>
							</div>
							<div class="commentText" >
							<span class="name">'.$account->name.':</span>  '.$forum['wavelet'].'
							</div>
							<div class="replyLink">
							<a id="'.$wid.'-'.$forum['wlid'].'" href="#commentArea">add a reply »</a>
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

function wave_access($id='',$pvt=''){
	 global $gSitePath,$user,$gDocPath,$base_root;
	 
	 
	if($pvt==1){
		 $query = "select * from {forum_wavelets} as f left join {user_profile} as u on u.uid=f.uid  where f.wlid='$id' ";
        
        $list = ExecuteQuery($query, "select");
		//print_r($list);
		
	if($list[0]['uid']==$user->uid){
		
		return true;
	}	
	
		
	}else{
		
		return true;
	}

	
}


