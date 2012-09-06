<?php global $base_url; ?>

<li id="reply-block-<?php print $comment->cid; ?>" class="one_reply">
  <span class=<?php print $node->str_wk == 1 ? 'positive' : 'negative'; ?>>
    <?php print $node->str_wk == 1 ? '+' : '-'; ?>
  </span>
  <div class="goog-trans-section reply_body">
    <p><?php print $comment->comment; ?></p>&nbsp;
    <div class="sq">[<div class="goog-trans-control translate"></div>]</div>
  </div>
  <span class="userinfo-reply">&nbsp;-&nbsp;
    <span class="name">
      <a href="<?php print $base_url . 'profile/' . $comment->name; ?>">
        <?php print $comment->name; ?>
      </a>
    </span>&nbsp;
    <span class="date"><?php echo $comment->ago; ?></span>
  </span>
  <div class="position-question">
    <?php #print theme('arguments_rating_button', $comment); ?>
    <?php print theme('yn', $comment); ?>
    <ul class="control_links">
      <li><?php print theme('flagger_button', $comment->cid, 'comment'); ?></li>
      <?php if ($delete = theme('arguments_delete', 'comment', $comment->content_id)) : ?>
        <li>&nbsp;|&nbsp;<?php print $delete; ?></li>
      <?php endif; ?>
    </ul>
  </div>
</li>