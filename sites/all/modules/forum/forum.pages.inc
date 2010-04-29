<?php

		
			
// tree menu listing
	function forum_list($qid='')
	{
		global $gSitePath,$user, $gDocPath,$base_root;
			$output='';
		
	extract($_REQUEST);
			//drupal_add_css(drupal_get_path('module', 'quest').'/styles/screen.css');
		
					
						
						 $query = "SELECT *  FROM {forum_wave} where qid_rid='$qid' AND fid='$wid' ";
   						 $list = ExecuteQuery($query, "select");	
							
							
							 foreach ($list as $forum) {
       $output.='<link rel="stylesheet" href="'.$gSitePath.drupal_get_path('module', 'quest_lite').'/css/wave.css" type="text/css" />';
        $output .= '
	<div class="comment">
		<div class="div1">
			
		</div>	
		<div class="div2">
			likes
		</div>
		<div class="div3">
			10 post
		</div>
		<div class="div4">
			<a href="javascript:void(0);" onclick="loadwave('.$qid.','.$forum['fid'].')"> '.myTruncate($forum['title'],'25','','..').'</a>
		</div>
		<div class="div5">
			'.$forum['date_added'].'
		</div>
		
		</div>	
	
	
	';
   
    }
		
							
							
					
				
		
		
		echo $output;
	
		
	}

	
	
	