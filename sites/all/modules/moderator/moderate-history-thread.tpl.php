<?php global $base_url;
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)).'/';
/**Rallydev:510**/
$modName = str_replace(':Owner',' ',$modName,$replace_count); 
$operation = 'Moderated by';
if($replace_count) {
  $operation = 'Posted by';
}
/**/
?>
<p class="issue-meta"><?php print t($operation); ?> <a class="username" href="<?php print $sitelink.'profile/'.$modName; ?>"><?php print $modName; ?></a> <?php print t('on'); ?> <?php print $updatedOn;?>.</p>
<hr>