<?php
$account = $item['account'];
$node = node_load($item['content_id']);
$translation = module_exists('poll_translate') ? poll_translate_translation($node) : array();
$vars = $item['vars'];

if (
  ($account->status != 1) ||
  ($node->status != 1)
) {
  return;
}

?>
<li class="clearfix">
  <?php

  $text = 'added a new issue';

  $link = l(
    (!empty($translation['title'][0]) ? $translation['title'][0] : $node->title) . '?',
    $node->path,
    array()
  );
  $text2 = '';
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