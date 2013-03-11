<?php if ($denied) : ?>

<!-- login using ui tabs -->

<?php else : ?>

<div id="dialog" title="<?php print $name; ?>" class="dialog vcard">

  <label for="profile" class="profile"></label>
  <a href="/user/profile/view" title="<?php print t('View Profile');?>">
    <img class="user-profile" src="<?php print user_profile_image($user) ?>"/>
  </a>

  <?php if ($complete['percent'] < 100) : ?>
  <div class="floatleft small-prog">
    <div class="profile-meta quick-profile">

      <div class="profile-meta quick-profile">
        <p><?php print t('Your profile is !complete% Complete', array('!complete' => $complete['percent']))?></p>

        <div class="profile-complete">
          <div class="progress" style="width: <?php print $complete['percent']; ?>%;"></div>
        </div>
        <p>
          <?php print t('Filling in your <em>!empty-field</em> will bring you to !complete% Complete', array('!empty-field' => t($complete['nextfield']), '!complete' => $complete['nextpercent'])); ?>
          <a class="blue"
             href="<?php print url('user/profile/edit', array('fragment' => $complete['nextname']."-wrapper")) ?>"><?php print t('Add it here.'); ?></a>
        </p>
      </div>

    </div>
  </div>

  <?php else : ?>

  <div class="floatleft" style="padding-left: 26px">
    <?php foreach ($badges['#stat'] as $type => $badge) : ?>
    <div class="medal">
      <span class="<?php print $type ?>" id="medal1" title="<?php print ucfirst($type) ?> Medals">&nbsp;</span>
      <?php print $badge; ?>
    </div>
    <?php endforeach; ?>
  </div>

  <?php endif; ?>

  <p class="profile-links quick-profile">
    <a href="/user/profile/view"><?php print t('View Profile');?></a> |
    <a href="/user/profile/edit"><?php print t('Edit Profile');?></a>
  </p>

  <a href="/logout?<?php print drupal_get_destination(); ?>" title="<?php print t('Log out');?>"
     class="button lighter"><?php print t('Logout'); ?></a>
</div>

<?php endif; ?>