<?php
global $user;
$loginBoxClass = $user->uid == 0 ? 'openlogin_box' : '';
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)) . '/';
$items['title'] = str_replace("\r\n", "<br>", $items['title']);
$items['title'] = str_replace("\n", "<br>", $items['title']);
/*  krumo($items);
  krumo($strength);
  krumo($comments);
  krumo($reply_box);
  krumo($reply_count);
  krumo($ratings);
  krumo($delete);
  exit;
 */
?>
<div id="forum-block-<?php print $items['debate_tnid']; ?>">
  <!--<?php if ($comments) { ?>
    <h6 class="active">/ <?php print t('Argument'); ?></h6>
  <?php }
  else { ?>
    <h6 class="active"><a href="#">/ <?php print t('Argument'); ?></a></h6>
  <?php } ?>-->
  
  
  <ul>
    <li>
	
	<div class="arg">
		<a href="#" class="icon flag2" title="flag this argument"></a>
		<span class="sum"><?php print t('Sum would be here'); ?></span>
		<p class="argument_body"><?php print t($items['title']); ?><a href="#" class="translate"><?php print t('Translate'); ?></a></p>
	  
		<div class="position">
			<?php print $strength; ?>
		</div>
	  
		<div class="userinfo-debate">
			<span class="date"><?php print t('posted '); ?><span><?php echo $items['ago']; ?></span></span>
			<a class="user-thumb" href="<?php print $sitelink . 'profile/' . $items['uname']; ?>"><img src="<?php print UserPicture_small_src($items['uid']); ?>" alt="<?php print $items['uname']; ?>" class="user-thumb" ></a>
			<span class="name"><a href="<?php print $sitelink . 'profile/' . $items['uname']; ?>"><?php print $items['uname']; ?></a></span>
		</div>
		
		<div class="position-question">
			<?php print $ratings; ?>
		</div>
		
		<?php if ($reply_box): ?>
        <h6 value="Reply" id="reply" class="add-comment button light <?php print $loginBoxClass; ?>"><?php print t('Reply'); ?></h6>
        <ul>
          <div id="reply-msg-<?php print $items['debate_tnid']; ?>" class="suc-msg"></div>
          <div id="reply-comment">
            <?php print $reply_box; ?>
          </div>
        </ul>
		<?php endif; ?>
	</div>
	
	<div class="replies">
	
    <?php if ($comments): ?>

        <!--<h6 class="active">/ <?php print $reply_count; ?> <?php print t('REPLIES'); ?></h6>-->
		
        <ul><!--<div class="top-arrow"></div>-->
          <div id="all_replybox_<?php print $items['debate_tnid']; ?>">
			<?php print $comments; ?>
          </div>
        </ul>
		<?php endif; ?>
      
		<p class="comment-meta"><?php print t('Show '); ?><?php print $reply_count; ?><?php print t(' more replies'); ?></p>

		<?php
			if ($delete):
					print $delete;
					print t('del debateparenttpl');
			endif;
		?>

	</div>
    </li>
  </ul>
</div>

<div id="flag-arg-<?php print $items['debate_tnid']; ?>" title="<?php print t('FLAG THIS ITEM'); ?>" class="form-flag" style="display: none">
	<input type="hidden" value="forum" id="flagtype" />
	<?php print t('Please Wait...'); ?>
</div>

<script type="text/javascript">
  $('#flag-arg-<?php print $items['debate_tnid']; ?>').dialog({
    autoOpen: false,
    modal: false,
    minWidth: 320,
    resizable:false
  });
</script>