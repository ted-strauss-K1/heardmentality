<li class="clearfix">
  <?php
  $account = $item['account'];
  $text = 'updated the profile';
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
  </p>
  <span class="submitted"><?php print $date; ?></span>
</li>