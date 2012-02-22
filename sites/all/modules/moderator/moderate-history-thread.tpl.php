<?php global $base_url;
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)).'/';
?>
<p class="issue-meta"><?php print t('Posted by'); ?> <a class="username" href="<?php print $sitelink.'profile/'.$modName; ?>"><?php print $modName; ?></a> <?php print t('on'); ?> <?php print $updatedOn;?>.</p>
<hr>