<?php	
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)).'/'; 
?>
<li id="reply-block-<?php print $items['cid'];?>">
      <a href="javascript:void(0);" class="icon flag2" onclick="open_flag_box(<?php print $items['cid'];?>, 'comment')" title="flag this Reply"></a>
  <a href="<?php print $sitelink.'profile/'.$items['uname']; ?>"><img src="<?php print $userPicture; ?>" class="user-thumb" /></a>
  <span class="name"><a href="<?php print $sitelink.'profile/'.$items['uname']; ?>"><?php print $items['uname']; ?></a></span>
  <p><?php print t($items['reply_content']); ?></p>
  <p class="comment-meta"><a><?php //print t('No Replies'); ?></a></p>
  <br class="clear">
  
  <div class="position-question">
    <?php print $ratings; ?>
            </div>
<br class="clear">
        <?php if($delete):
              print $delete;
              endif;
          ?>
<br class="clear">
</li>
<div id="flag-comm-<?php print $items['cid'];?>" title="<?php print t('FLAG THIS ITEM'); ?>" class="form-flag" style="display: none">
    <input type="hidden" value="comment" id="flagtype" />
    <?php print t('Please Wait...'); ?>
</div>
<script type="text/javascript">
    $('#flag-comm-<?php print $items['cid'];?>').dialog({
		autoOpen: false,
		modal: false,
		minWidth: 320,
		resizable:false
	});
</script>