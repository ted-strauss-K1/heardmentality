<li class="clearfix">
  <?php
  $account = $item['account'];
  $target = user_load($item['content_id']);

  $text = 'now following';
  $link = '<span class="name"><a href="' . $target->viewlink . '" title="' . $target->name . '">' . ucwords($target->name) . '</a></span>';
  $text2 = l(
    sprintf('<img class="following-user listed" src="%s" />', user_profile_image($target)),
    $target->viewlink,
    array('html' => true)
  );
  ?>
  <?php print l(
  sprintf('<img class="following-user listed" src="%s" />', user_profile_image($account)),
  $account->viewlink,
  array('html' => true)
); ?>
<p class="action-item">
  <span class="name">
    <a href="<?php print $account->viewlink ?>" title="<?php print $account->name ?>">
      <?php print ucwords($account->name) ?>
    </a>
  </span>

  <?php print t($text); ?>
  <?php print $link; ?>
  <?php if ($text2) : ?>
    </p><p class="action-comment-ref"><?php print t($text2) ?>
  <br clear="both">
  <?php endif; ?>

</p>
  <span class="submitted" name="<?php print $item['timestamp']; ?>"><?php print $item['date_added']; ?></span>
</li>