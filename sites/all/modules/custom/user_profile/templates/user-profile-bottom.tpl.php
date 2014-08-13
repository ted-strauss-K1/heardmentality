<?php if ($denied) : ?>

  <div class="foot-empty">
    <div class="profile-meta footerfloat">
      <p><?php print __('Please Login to view your profile details', array('@code' => 'user_profile-26')); ?></p>
      <?php print drupal_get_form('user_login'); ?>
    </div>
  </div>

<?php else : ?>

  <i class="icon cat text icon-businesscardalt"></i>
  <label for="profile" class="profile-dark dinbold"><?php print $user->name; ?>
    , <?php $rank = $user->rank; print __($rank['name'], array('@code' => 'rank-' . $rank['index'], '@textgroup' => 'rank')); ?></label>
  <p class="profile-links">
    <?php print l(__('View Profile', array('@code' => 'user_profile-view')), 'user/profile/view'); ?> |
    <?php print l(__('Edit Profile', array('@code' => 'user_profile-edit')), 'user/profile/edit'); ?>
  </p>
  <?php if ($complete['percent'] < 100) : ?>
    <div class="profile-meta">
      <div class="profile-meta footerfloat">
        <p><?php print __('Your profile is !complete% Complete', array('@code' => 'user_profile-27', '!complete' => $complete['percent'])) ?></p>

        <div class="profile-complete">
          <div class="progress" style="width: <?php print $complete['percent']; ?>%;"></div>
        </div>
      </div>
    </div>
  <?php endif; ?>
  <div class="floatleft">
    <?php print l('<img class="user-profile" src="' . user_profile_image($user) . '">', 'user/profile/view', array(
      'attributes' => array(
        'title' => __('View Profile', array('@code' => 'user_profile-view')),
      ),
      'html'       => TRUE,
    )); ?>
    <?php if ($badges) : ?>
      <div class="medal clearfix"><?php foreach ($badges['#stat'] as $type => $badge) : ?>
        <span class="medal_box">
    <span class="medal1 <?php print $type ?>" title="<?php
      print __(badges_types($type) . ' Medals', array(
        '@code' => 'medals-' . $type,
      )); ?>">&nbsp;</span>
          <?php print $badge; ?>
    </span>
      <?php endforeach; ?>
      </div><?php endif; ?>
  </div>
  <?php print l(__('Logout', array('@code' => 'user_profile-logout')), 'logout', array(
    'attributes' => array(
      'title' => __('Logout', array('@code' => 'user_profile-logout')),
      'class' => 'button darker floatright',
    )
  )); ?>
<?php endif; ?>
