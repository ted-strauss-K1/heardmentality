<div class="following_page">
  <?php if ($users) : ?>
  <?php $param = $code == 'following' ? 'requestee' : 'requester'; ?>

  <?php foreach ($users as $item) : ?>
    <?php $user = $item->{$param}; ?>

    <div class="one_person clearfix">
      <?php print theme('follower_button', $user); ?>

      <div class="name_wrapper">
        <a href="/<?php print $user->viewlink; ?>">
          <img class="following-user-2" src="<?php print user_profile_image($user); ?>" alt="">
        </a>
			<span class="name din">
			  <a href="/<?php print $user->viewlink; ?>"><?php print $user->name; ?></a>
			</span>
      </div>
    </div>

    <?php endforeach; ?>

  <?php else : ?>

  <?php
  global $user;
  if ($user->uid == $uid) {
    print $code == 'following' ?
      t('You\'re not following anyone from the Heard yet. You can follow users by clicking the \'Follow\' button on their profile pages.') :
      t('No users from the Heard follow you yet');
  } else {
    print t('No users found');
  }
  ?>

  <?php endif; ?>

</div>