<?php if ($denied) : ?>

<div class="foot-empty">
  <div class="profile-meta footerfloat">
    <p><?php print t('Please Login to view your profile details'); ?></p>
    <?php print drupal_get_form('user_login'); ?>
  </div>
</div>

<?php else : ?>

<i class="icon cat text icon-businesscardalt"></i>
<label for="profile" class="profile-dark dinbold"><?php print $user->name; ?>, <?php print t($rank); ?></label>
<p class="profile-links">
  <a href="/user/profile/view"><?php print t('View Profile');?></a> |
  <a href="/user/profile/edit"><?php print t('Edit Profile');?></a>
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
  <a href="/user/profile/view" title="<?php print t('View Profile');?>">
    <img class="user-profile" src="<?php print user_profile_image($user);?>">
  </a>
  <?php if ($badges) foreach ($badges['#stat'] as $type => $badge) : ?>
  <div class="medal">
    <span class="<?php print $type ?>" id="medal1" title="<?php print ucfirst($type) ?> Medals">&nbsp;</span>
    <?php print $badge; ?>
  </div>
  <?php endforeach; ?>
</div>
<a type="submit" title="<?php print t('Log out');?>" href="/logout"
   class="button darker floatright"><?php print t('Logout'); ?></a>
<?php endif; ?>