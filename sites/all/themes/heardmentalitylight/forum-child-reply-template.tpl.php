<?php	
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)).'/'; 
$items['reply_content'] = str_replace("\r\n", "<br>", $items['reply_content']);  
$items['reply_content'] = str_replace("\n", "<br>", $items['reply_content']);
?>

<li id="reply-block-<?php print $items['cid'];?>">
    <a href="javascript:void(0);" class="icon flag2" onclick="open_flag_box(<?php print $items['cid'];?>, 'comment')" title="flag this Reply"></a>
	

	<p class="reply_body">
		<?php print t($items['reply_content']); ?>
		<a href="#" class="translate"><?php print t('Translate'); ?></a><span class="userinfo-reply">&nbsp;-&nbsp;<span class="name"><a href="<?php print $sitelink . 'profile/' . $items['uname']; ?>"><?php print $items['uname']; ?></a></span>&nbsp;<span class="date"><?php echo $items['ago']; ?></span></span>
	</p>
	<!--<p class="comment-meta"><a><?php //print t('No Replies'); ?></a></p>-->
  
	<div class="position-question">
		<?php print $ratings; ?>
    </div>

    <?php if($delete):
        print $delete;
        endif;
    ?>

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