<?php global $user; ?>

<li id="reply-block-<?php print $comment->cid; ?>" class="one_reply">
  <span class=<?php print empty($comment->support) ? 'negative' : 'positive'; ?>>
    <?php print empty($comment->support) ? '-' : '+'; ?>
  </span>

  <div class="goog-trans-section reply_body">
    <p><?php print $comment->comment; ?></p>&nbsp;
    <div class="sq">
      [
      <div class="goog-trans-control translate"></div>
      ]
    </div>
  </div>
  <span class="userinfo-reply">&nbsp;-&nbsp;
    <span class="name">
      <a href="<?php print '/user/profile/view/' . $comment->name; ?>">
        <?php print $comment->name; ?>
      </a>
    </span>&nbsp;
    <span class="date"><?php print $comment->creation_time; ?></span>
  </span>

  <div class="position-question">
    <?php print theme('yn', 'comment', $comment->cid, $user->uid == $comment->uid); ?>
    <ul class="control_links">
      <li><?php print theme('flagger_button', $comment->cid, 'comment'); ?></li>
      <li>&nbsp;|&nbsp;<?php
        $counts = flagger_get_flags('comment', $comment->cid);
        print theme(
          'flagger_button_flags', $comment->cid, 'comment',
          !empty($counts)); ?></li>
      <?php if ($delete = theme('argument_delete', 'comment', $comment->content_id)) : ?>
      <li>&nbsp;|&nbsp;<?php print $delete; ?></li>
      <?php endif; ?>
    </ul>
  </div>
</li>