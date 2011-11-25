<div id="forum-block-<?php print $items['debate_tnid'];?>">
<?php if($comments){ ?>
<h6 class="active">/ <?php print t('Argument'); ?></h6>
<?php } else{?>
<h6 class="active"><a href="#">/ <?php print t('Argument'); ?></a></h6>
<?php }?>
<ul>
<li>
    <a href="#" class="icon flag2" title="flag this argument"></a>
    <img src="<?php print UserPicture_small_src($items['uid']); ?>" alt="<?php print $items['uname']; ?>" class="user-thumb" >
    <span class="name"><a><?php print $items['uname']; ?></a></span>
    <p><?php print t($items['title']); ?></p>
    <p class="comment-meta"><a><?php print $reply_count; ?> <?php print t('Replies'); ?></a></p>
    
          <br class="clear">
          <div class="position">
            <?php print $strength; ?>
          </div>
          <div class="position-question">
              <?php print $ratings; ?>
            </div>
          <br class="clear">
          
          <?php if($delete):
              print $delete; 
                endif;
          ?>
          <?php if($reply_box): ?>
          <h6 value="Reply" id="reply" class="add-comment button light"><?php print t('Reply'); ?></h6>
            <ul>
          <br />
          <div id="reply-msg-<?php print $items['debate_tnid'];?>" class="suc-msg"></div>
          <div id="reply-comment">
          	<?php print $reply_box; ?>
          </div>
            </ul>
          <?php endif; ?>
          <hr>
          <?php if($comments): ?>
          
          <h6 class="active">/ <?php print $reply_count; ?> <?php print t('REPLIES'); ?></h6>
          <ul><div class="top-arrow"></div>
              <div id="all_replybox_<?php print $items['debate_tnid'];?>">
              <?php print $comments; ?>
              </div>
          </ul>
          <?php endif; ?>
</li>
</ul>
</div>