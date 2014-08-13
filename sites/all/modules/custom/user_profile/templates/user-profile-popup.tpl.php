<?php if ($denied) : ?>

  <!-- login using ui tabs -->

<?php else : ?>

  <div style="display:none">

    <a href="#popup-login" class="inline-dialog"></a>

    <div id="popup-login" class="logged_in">
      <div class="popup-login-inner <?php print is_mobile() ? 'mobile' : '' ?>">

        <label for="profile" class="profile"></label>
        <?php print l('<img class="user-profile" src="' . user_profile_image($user) . '"/>', 'user/profile/view', array(
          'attributes' => array(
            'title' => __('View Profile', array('@code' => 'user_profile-view')),
          ),
          'html'       => TRUE,
        )); ?>
        <?php if ($complete['percent'] < 100) : ?>
          <div class="floatleft small-prog">
            <div class="profile-meta quick-profile">

              <div class="profile-meta quick-profile">
                <p><?php print __('Your profile is !complete% Complete', array('@code' => 'user_profile-57', '!complete' => $complete['percent'])) ?></p>

                <div class="profile-complete">
                  <div class="progress" style="width: <?php print $complete['percent']; ?>%;"></div>
                </div>
                <p>
                  <?php print __('Filling in your <em>!empty-field</em> will bring you to !complete% Complete', array(
                    '!empty-field' => __($complete['nextfield'], array('@code' => 'user_profile-field-' . $complete['nextname'])),
                    '!complete'    => $complete['nextpercent'],
                    '@code'        => 'user_profile-58',
                  )); ?>
                  <a class="blue"
                     href="<?php print url('user/profile/edit', array('fragment' => $complete['nextname'] . "-wrapper")) ?>"><?php print __('Add it here.', array('@code' => 'user_profile-59')); ?></a>
                </p>
              </div>

            </div>
          </div>

        <?php else : ?>

          <div class="floatleft" style="padding-left: 26px">
            <?php foreach ($badges['#stat'] as $type => $badge) : ?>
              <div class="medal">
                <span class="<?php print $type ?>" id="medal1"
                      title="<?php print __(badges_types($type) . ' Medals', array(
                        '@code' => 'medals-' . $type,
                      )); ?>">&nbsp;</span>
                <?php print $badge; ?>
              </div>
            <?php endforeach; ?>
          </div>

        <?php endif; ?>

        <p class="profile-links quick-profile">
          <a href="<?php print url('user/profile/view'); ?>"><?php print __('View Profile', array('@code' => 'user_profile-view')); ?></a> | <a
            href="<?php print url('user/profile/edit'); ?>"><?php print __('Edit Profile', array('@code' => 'user_profile-edit')); ?></a> | <a
            href="<?php print url('logout'); ?>"><?php print __('Logout', array('@code' => 'user_profile-logout')); ?></a>
        </p>

      </div>
    </div>
  </div>

  <div id="dialog" title="<?php print $name; ?>" class="dialog vcard">


  </div>

<?php endif; ?>
