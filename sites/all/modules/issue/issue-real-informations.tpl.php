<?php
//theme_issue_information($nid = '', $created = '', $postedby = '', $ctitle = array(), $sctitle = array(), $ssctitle = array(), $original_nid = '', $original_language = '', $orgLangKey = '')
?>
<?php
  global $base_url;
  $path = '<front>';
  $sitelink = url($path, array('absolute' => TRUE)).'/';    
  
    //category details
  //print_r($ctitle); exit;
        if(!empty($subject)){
        foreach($subject as $tid=>$subjects){
            $info .= '<li>'.l($subjects,'issues/0/'.$tid.'/0/0/0/0/0').'</li>';
        }}
        
        if(!empty($area)){
        foreach($area as $tid=>$areas){
            $parent = taxonomy_get_parents($tid);
            $cid = array_keys($parent);
            $info .= '<li>'.l($areas,'issues/0/'.$cid[0].'/'.$tid.'/0/0/0/0').'</li>';
        }}
        
   
        if(!empty($detail)){
        foreach($detail as $tid=>$details){
             $sparent = taxonomy_get_parents($tid);
             $ssid = array_keys($sparent);
             $ssparent = taxonomy_get_parents($ssid[0]);
             $cid = array_keys($ssparent);
             $info .= '<li>'.l($details,'issues/0/'.$cid[0].'/'.$ssid[0].'/'.$tid.'/0/0/0').'</li>';
        }}
        $info = $info!=''?$info:'<li>'.t('No categories associated with this issue').'</li>';
    
    $path = drupal_get_path_alias('node/'.$original_nid);
    


?>
<div class="icon cat text"></div>
				<ul class="tags">
				    <label for="" class="tags-on"><?php print t('ACTIVE CATEGORIES'); ?></label>
					<?php print $info; ?>
				</ul>
				<br class="clear">
				<hr class="short">
				<br> 
				<p class="issue-meta"><?php print t('Posted on'); ?> <?php print $created; ?> <br><?php print t('by');?> <a class="username" href="<?php print $sitelink.'profile/'.$postedby; ?>" ><?php print $postedby; ?></a>.
                                <?php print t('Read original post in');?> <a href="<?php print $base_url.'/'.$orgLangKey.'/'.$path;?>"><?php print $original_language; ?></a> </p>

				<div class="clear"></div>
