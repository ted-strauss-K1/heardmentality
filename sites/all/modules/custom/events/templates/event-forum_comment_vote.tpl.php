<li class="clearfix">
  <?php
  $account = $item['account'];
  $comment = _comment_load($item['content_id']);
  $argument = node_load($comment->nid);
  $node = node_load($argument->field_issue[0]['nid']);
  $vars = $item['vars'];

  $translation = module_exists('poll_translate') ? poll_translate_translation($node) : array();

  if (!$comment->support) yn_invert_vote_value($vars['vote']);
  $text = ($vars['vote'] == VOTE_AGREE ? 'strenghtened' : 'weakened') .
    ' an argument on the issue';
  $link = l(
    (!empty($translation['title'][0]) ? $translation['title'][0] : $node->title) . '?',
    $node->path,
    empty($argument) ? array() : array('fragment' => 'forum-block-' . $argument->nid)
  );
  $text2 = $comment->comment;
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
        </p><p class="action-comment-ref">

    <!-- google translate -->
    <span class="goog-trans-section events_google_translate">
      <?php print $text2; ?>&nbsp;<span>[<span class="goog-trans-control translate"></span>]</span>
    </span>

  <br clear="both">
  <?php endif; ?>

</p>
  <span class="submitted"><?php print $date; ?></span>
</li>