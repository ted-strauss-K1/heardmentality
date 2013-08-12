<?php if ($denied) : ?>

<div class="foot-empty">
  <div class="profile-meta footerfloat">
    <p><?php print t('Please Login to view your profile details'); ?></p>
    <?php print drupal_get_form('user_login'); ?>
  </div>
</div>

<?php else : ?>

<i class="icon cat text icon-businesscardalt"></i>
<label for="profile" class="profile-dark dinbold"><?php print $user->name; ?>, <?php print t($user->rank['name']); ?></label>
<p class="profile-links">
  <?php print l(t('View Profile'), 'user/profile/view');?> |
  <?php print l(t('Edit Profile'), 'user/profile/edit');?>
</p>
<?php if ($complete['percent'] < 100) : ?>
  <div class="profile-meta">
    <div class="profile-meta footerfloat">
      <p><?php print t('Your profile is !complete% Complete', array('!complete' => $complete['percent']))?></p>

      <div class="profile-complete">
        <div class="progress" style="width: <?php print $complete['percent']; ?>%;"></div>
      </div>
    </div>
  </div>
  <?php endif; ?>
<div class="floatleft">
  <?php print l(
    '<img class="user-profile" src="'.user_profile_image($user).'">',
    'user/profile/view', array(
    'attributes' => array(
      'title' => t('View Profile'),
    ),
    'html' => true,
  )); ?>
  <?php if ($badges) foreach ($badges['#stat'] as $type => $badge) : ?>
  <div class="medal">
    <span class="<?php print $type ?>" id="medal1" title="<?php print t(ucfirst($type) . ' Medals'); ?>">&nbsp;</span>
    <?php print $badge; ?>
  </div>
  <?php endforeach; ?>
</div>
  <?php print l(t('Logout'), 'logout', array(
    'attributes' => array(
      'title' => t('Logout'),
      'class' => 'button darker floatright',
    )
  )); ?>
<?php endif; ?>