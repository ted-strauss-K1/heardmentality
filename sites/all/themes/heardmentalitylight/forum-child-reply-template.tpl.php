<li id="reply-block-<?php print $items['cid'];?>">
      <a href="#" class="icon flag2" title="flag this Reply"></a>
  <img src="<?php print $userPicture; ?>" class="user-thumb" />
  <span class="name"><a><?php print $items['uname']; ?></a></span>
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
