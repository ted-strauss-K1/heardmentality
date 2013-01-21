<li class="clearfix">
  <?php
  $account = $item['account'];
  $node = node_load($item['vars']['nid']);
  $text = 'got the badge';
  if (module_exists("badges")) {
    $badges = badges_get();
    $badges_types = badges_types();
    foreach ($badges as $badge) {
      if (($badge['status'] == 1) && ($vars['badge_id'] == $badge['id'])) {
        $text2 = sprintf('<span class="medal"><span class="%s" id="medal1" title="%s Medal">&nbsp;</span>&nbsp;%s</span>',
          $badges_types[$badge['type']], ucfirst($badges_types[$badge['type']]), $badge['name']);
        break;
      }
    }
  }
  ?>

  <?php print l(
  sprintf('<img class="following-user listed" src="%s" />', user_profile_image($account)),
  $account->viewlink,
  array('html' => true)
); ?>
<p class="action-item">
  <span class="name">
    <a href="/<?php print $account->viewlink ?>" title="<?php print $account->name ?>">
      <?php print ucwords($account->name) ?>
    </a>
  </span>
  <?php print t($text); ?>
  <?php if ($text2) : ?>
    </p><p class="action-comment-ref"><?php print t($text2) ?>
  <br clear="both">
  <?php endif; ?>

</p>
  <span class="submitted"><?php print $date; ?></span>
</li>