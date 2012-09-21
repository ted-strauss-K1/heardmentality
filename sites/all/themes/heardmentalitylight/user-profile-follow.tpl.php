<div class="following">
  <?php if ($users) : ?>
    <?php $param = $code == 'following' ? 'requestee' : 'requester'; ?>

    <?php foreach ($users as $item) : ?>
      <?php $user = $item->{$param}; ?>
      
      <div>
        <div>
          <?php print theme('follower_button', $user); ?>
        </div>
        <a href="/user/profile/view/<?php print $user->name; ?>">
          <img class="following-user-2" src="<?php print user_profile_image($user); ?>" alt="">
        </a>
        <h2 class="din">
          <span class=""><a href="/user/profile/view/<?php print $user->name; ?>"><?php print $user->name; ?></a></span>
        </h2>
      </div>
      <hr class="short">

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
<br class="clear">