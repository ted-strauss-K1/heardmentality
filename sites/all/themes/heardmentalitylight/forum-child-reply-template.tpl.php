<?php
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)) . '/';
$items['reply_content'] = str_replace("\r\n", "<br>", $items['reply_content']);
$items['reply_content'] = str_replace("\n", "<br>", $items['reply_content']);
?>

<li id="reply-block-<?php print $items['cid']; ?>" class="one_reply">
  <span class=<?php print $items['class'];?>><?php print $items['sign'] ?></span>
  
    <div class="goog-trans-section reply_body">
		
		<p><?php print t($items['reply_content']); ?></p>&nbsp;<div class="sq">[<div class="goog-trans-control translate"></div>]</div>
          
	</div>
    <span class="userinfo-reply">&nbsp;-&nbsp;
      <span class="name">
        <a href="<?php print $sitelink . 'profile/' . $items['uname']; ?>">
          <?php print $items['uname']; ?></a></span>&nbsp;
      <span class="date"><?php echo $items['ago']; ?>
      </span>
    </span>

  <div class="position-question">
    <?php print $ratings; ?>
  
   <ul class="control_links">
		<li>
      <!-- <a href="javascript:void(0);" class="icon flag2 flag_reply" onclick="open_flag_box(<?php print $items['cid']; ?>, 'comment')" title="flag this reply">flag</a>
      -->
      <?php print theme('flagger_button', $item['content_id'], 'comment'); ?>
    </li>
		<?php if ($delete):?><li>&nbsp;|&nbsp;<?php print $delete; ?></li><?php endif; ?>
   </ul>
   
  </div>
  
</li>
<div id="flag-comm-<?php print $items['cid']; ?>" title="<?php print t('FLAG THIS ITEM'); ?>" class="form-flag" style="display: none">
  <input type="hidden" value="comment" id="flagtype" />
<?php print t('Please Wait...'); ?>
</div>
<script type="text/javascript">
  $('#flag-comm-<?php print $items['cid']; ?>').dialog({
    autoOpen: false,
    modal: false,
    minWidth: 320,
    resizable:false
  });
</script>