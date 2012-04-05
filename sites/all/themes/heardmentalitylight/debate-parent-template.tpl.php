<?php
global $user;
$loginBoxClass = $user->uid == 0 ? 'openlogin_box' : '';
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)) . '/';
$items['title'] = str_replace("\r\n", "<br>", $items['title']);
$items['title'] = str_replace("\n", "<br>", $items['title']);
?>
<div id="forum-block-<?php print $items['debate_tnid']; ?>" class="one-forum">
  <!--<?php if ($comments) { ?>
        <h6 class="active">/ <?php print t('Argument'); ?></h6>
  <?php }
  else { ?>
        <h6 class="active"><a href="#">/ <?php print t('Argument'); ?></a></h6>
  <?php } ?>-->


  <ul class="argument_box">
    <li>

      <div class="arg">
        <span class="sum"><?php $diff = $items['vote_up'] - $items['vote_down'];
			if ($diff > 0) { ?>
            <span class="positive"> <?php print $diff; ?></span>
          <?php }
          elseif ($diff < 0) { ?>
            <span class="negative"> <?php print $diff; ?></span>
          <?php }
          else { ?>
            <span class="null"> <?php print $diff; ?></span>
          <?php }
          ?> 
        </span>
        <div class="goog-trans-section argument_body">
		
			<p><?php print t($items['title']); ?></p>&nbsp;<div class="sq">[<div class="goog-trans-control translate"></div>]</div>
          
		</div>

        <div class="position">
          <?php print $strength; ?>
        </div>

        <div class="userinfo-debate">
          <span class="date"><?php print t('posted '); ?><span><?php echo $items['ago']; ?></span></span>
          <a class="user-thumb" href="<?php print $sitelink . 'profile/' . $items['uname']; ?>"><img src="<?php print UserPicture_small_src($items['uid']); ?>" alt="<?php print $items['uname']; ?>" class="user-thumb" ></a>
          <span class="name"><a href="<?php print $sitelink . 'profile/' . $items['uname']; ?>"><?php print $items['uname']; ?></a></span>
        </div>

      </div>

	  <ul class="control_links">
			<li><a href="#" class="icon flag2" title="flag this argument">flag</a></li>
			<li>&nbsp;|&nbsp;<a href="#" class="flag2" title="permalink">link</a></li>
			<?php if ($delete):?><li>&nbsp;|&nbsp;<?php print $delete; ?></li><?php endif; ?>
	  </ul>
	  
      <div class="replies">

        <?php if ($comments): ?>
		
        <fieldset class="collapsible collapsed reply_wrapper">
		
		<legend class="comment-meta"><?php print t('&#9658; '); ?><span><?php print $reply_count; ?><?php print t(' replies'); ?></span></legend>
            <div class="fieldset-wrapper">
				<ul>
				  <div id="all_replybox_<?php print $items['debate_tnid']; ?>">
					<?php print $comments; ?>
				  </div>
				</ul>
			</div>
        </fieldset> 
		
		<?php endif; ?>
		
	  </div>
	  
      <div class="position-question">
      <?php print $ratings; ?>
      
	  <?php if ($reply_box): ?>
		<!--<h6 value="Reply" id="reply" class="add-comment button light <?php print $loginBoxClass; ?>"><?php print t('Reply'); ?></h6>-->
		<ul class="argument_replybox">
			<div id="reply-msg-<?php print $items['debate_tnid']; ?>" class="suc-msg"></div>
			<div id="reply-comment"> 
				<?php print $reply_box; ?>
			</div>
		</ul>
	  <?php endif; ?>
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

