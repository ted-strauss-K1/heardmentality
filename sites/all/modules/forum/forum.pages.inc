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
    
    $output .= '<div class="waveComment ">';
    foreach ($list as $forum) {
        
        $date = cdatetime($forum['date_added']);
        $account = user_load($forum['uid']);

        
        $output .= '
		
	<div class="comment">
	<div class="waveTime">'.$date.'</div>
	<div class="commentAvatar">
				<img width="30" height="30" alt="" src="'.$gSitePath.drupal_get_path('module', 'profile').'/snap/'.$forum['image'].'"/>
				</div>
				<div class="commentText">
				<span class="name">'.$account->name.':</span>  '.$forum['title'].'
				</div>
				<div class="replyLink">
				<a onclick="addComment(this,1);return false;" href="">add a reply »</a>
				</div>
				<div class="clear"/>
		<div class="div4">
	
		</div>
		<div class="div5">
			';

        
        $output .= '	
		</div>
		
		</div>	
	
	
	';
    
    }
    
    $output .= '</div><div "wavefooter">

	<input type="button" class="waveButtonMain" onclick="addComment('.$wid.');"  value="Add Comment" id="newwaveletbut"/>
		</div>';
    
    $output .= '<div id="commentArea">            
        <div class="waveComment addComment">
		<div class="comment">			
		<div class="commentAvatar">	
		<img width="30" height="30" src="img/demo.png"/>	
		</div>	
		<div class="commentText">			
		<textarea name="" cols="70" rows="2" class="textArea">	</textarea>
		<div><input type="button" onclick="addSubmit(this,0)" value="Add comment" class="waveButton"/> or <a onclick="cancelAdd(this);return false" href="">cancel</a></div>	
		</div>	
		</div>	
		</div></div>';

    
    echo $output;


}



