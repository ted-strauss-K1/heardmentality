<?php if (!$denied && ($complete['percent'] < 100) && is_null($_COOKIE['profile_status'])) : ?>
  <div class="message right-message profile-status-toggle">
    <a href="#" id="button" class="hide-message2 ui-dialog-titlebar-close profile-close-icon"> <i
        class="close_icon icon-remove"></i> </a>

    <p class="profile-status">
      <strong>
        <?php print __('Your profile is !complete% Complete', array('@code' => 'user_profile-57', '!complete' => $complete['percent'])) ?>
      </strong>
    </p>

    <div class="profile-complete">
      <div class="progress" style="width: <?php print $complete['percent']; ?>%;"></div>
    </div>
    <p>
      <?php print __('Filling in your <em>!empty-field</em> will bring you to !complete% Complete', array(
        '!empty-field' => __($complete['nextfield'], array('@code' => 'user_profile-field-' . $complete['nextname'])),
        '!complete'    => $complete['nextpercent'],
        '@code'        => 'user_profile-58',
      )); ?>
      <a class="bolded"
         href="<?php print url('user/profile/edit', array('fragment' => $complete['nextname'] . "-wrapper")) ?>">
        <?php print __('Add it here.', array('@code' => 'user_profile-59')); ?>
      </a>
    </p>
  </div>
<?php endif; ?>
