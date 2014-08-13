<div class="line-top">
  <div class="container">
    <div class="navigation">
      <div class="top-left">
        <a class="logo" href="<?php print url(); ?>"><img
            src="<?php print url(path_to_theme() . '/images/tiny_logo.png', array('language' => '')); ?>"
            class="logo-img"/> <?php print __('Heard Mentality', array('@code' => 'header-01')); ?><span
            class="beta"><?php print __('Beta', array('@code' => 'header-02')); ?></span></a>
      </div>

      <div class="top-right login">
        <?php print $user_login_modal; ?>
      </div>
    </div>
  </div>
</div>

<div class="line-bottom">
  <div class="container">
    <div class="navigation">
      <div
        class="top-left clearfix user-menu<?php if (module_exists('moderation') && moderation_check_perm()) : ?> full<?php endif; ?>">
        <ul class="menu">
          <li><?php print l(__('Issues', array('@code' => 'header-03')), 'issues', array('attributes' => array('class' => 'issues'))); ?></li>

          <li class="following"><?php print l(__('Analysis', array('@code' => 'header-04')), 'analysis', array('attributes' => array('class' => 'analysis'))); ?></li>

          <?php if (user_is_logged_in()) : ?>
            <li
              class="following"><?php print l(__('Following', array('@code' => 'header-05')), 'following', array('attributes' => array('class' => 'following'))); ?></li>
          <?php endif; ?>

          <?php if (module_exists('moderation') && moderation_check_perm()) : ?>
            <li
              class="moderator"><?php print l(__('Moderator', array('@code' => 'header-06')), 'moderation', array('attributes' => array('class' => 'moderator'))); ?></li>
          <?php endif; ?>

        </ul>
        <ul
          class="menu second<?php if (module_exists('moderation') && moderation_check_perm()) : ?> full<?php endif; ?>">
          <li class="add_issue"><?php print l(__('Add an Issue', array('@code' => 'header-07')), 'create', array(
              'attributes' => array(
                'class' => 'add ' . theme('user_login_modal_class')
              )
            )); ?></li>
        </ul>
      </div>
      <?php if (module_exists('moderation') && moderation_check_perm()) : ?>
        <div class="top-right blue">
          <div class="expanding">
            <h6 class="inactive"><?php print __('Language', array('@code' => 'header-08')); ?></h6>
            <ul class="lang" style="display:none;" aria-hidden="true">
              <?php if ($multilanguage_area): print $multilanguage_area; endif; ?>
              <?php print __('... more languages coming soon', array('@code' => 'header-09')); ?>
            </ul>
          </div>
        </div>
      <?php endif; ?>
    </div>
  </div>
</div>
