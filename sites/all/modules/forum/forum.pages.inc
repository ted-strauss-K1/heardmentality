<?php

		
			
// tree menu listing
	function forum_list($qid='')
	{
		global $gSitePath,$user, $gDocPath,$base_root;
			$output='';
		//drupal_add_css(drupal_get_path('module', 'quest_lite').'/styles/jquery.treeview.css');
			//drupal_add_css(drupal_get_path('module', 'category').'/styles/screen.css');
			$action=$_REQUEST['action'];
			$qid = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
	
			switch($action){
				
				case 'new':
					
						$output.='<form action="'.url($_GET['q'], array('absolute'=>true)).'" method="post" accept-charset="utf-8">
	<div >Post New Wave</div>
	<p><input type="text" name="wtitle" id="wtitle" value="" size="55" maxlength="255" /></p>	
	<div >Private Reply : [Only followers can do reply]</div>
	<p><select name="wprivate" id="wprivate">
	<option value="0"> <small>Disabled</small></option>
	<option value="1"> <small>Enabled  </small></option>
	</select></p>					
	<p><input type="submit" value="Post" /></p>
</form>';
							break;
				
				
				default:
					echo "No Action!!";
					break;
				
				
				
			}
		
		
		
		echo $output;
	
		
	}

	
	
	