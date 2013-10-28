<div class="dark-grey-box top clearfix">
  <div class="profile-meta profile_page_wrapper">
	<i class="icon cat text icon-groups-friends"></i>
    <label for="profile" class="white_text with_icon"><?php print t('You\'re following'); ?></label>
  </div>
  <div class="following clearfix" id="events_users">
    <?php print theme('events_follower_block_content', $users); ?>
    <?php if ((count($users) < $users_count) && false) : ?>
    <span id="events_users_more"
          style="display: block; background: #CCC; width: 100%; padding: 5px; text-align: center; border-radius: 5px; clear: both; cursor: pointer;"><?php print t('more'); ?></span>
    <?php endif; ?>
  </div>
  <?php if (!empty($users)) : ?>
  <div class="following clearfix">
    <?php global $user; ?>
    <?php print l(
      t('See all') . ' (' .$users_count. ')',
      'user/profile/follow/'.$user->uid.'/following',
      array('attributes' => array('class' => 'more'))
    ); ?>
  </div>
  <?php endif; ?>
</div>