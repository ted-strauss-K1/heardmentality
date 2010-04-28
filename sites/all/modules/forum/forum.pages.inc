<?php

		
			
// tree menu listing
	function forum_list($qid='')
	{
		global $gSitePath,$user, $gDocPath,$base_root;
			$output='';
		
	
			//drupal_add_css(drupal_get_path('module', 'category').'/styles/screen.css');
			$action=$_REQUEST['action'];
			$qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
	
			switch($action){
				
				case 'new':
					
						$output.='
					
					<link rel="stylesheet" href="'.$gSitePath.drupal_get_path('module','forum').'/styles/wave.css" type="text/css" />
<form  id="newwave" action="'.url($_GET['q'], array('absolute'=>true)).'" method="post" accept-charset="utf-8">
	<div ><b>Post New Wave</b></div>
	<p><textarea row="7" class="textArea" cols="55"  name="wtitle" id="wtitle" ></textarea></p>	
	<div ><b>Private Reply :</b> [Only followers can do reply]</div>
	<p><select name="wprivate" id="wprivate">
	<option value="0"> Disabled</option>
	<option value="1"> Enabled  </option>
	</select></p>					
	<p><input type="submit" class="waveButtonMain" value="Post" /></p>
</form>';
							break;
				
				case 'list':
					
						
						 $query = "SELECT *  FROM {forum_wave} ";
   						 $list = ExecuteQuery($query, "select");	
							
						break;		
				default:
					echo "No Action!!";
					break;
				
				
				
			}
		
		
		
		echo $output;
	
		
	}

	
	
	