<div class="line-top">
  <div class="container">
    <div class="navigation">
      <div class="top-left">
        <a class="logo" href="<?php print url(); ?>"><img
            src="<?php print url(path_to_theme() . '/images/tiny_logo.png'); ?>"
            class="logo-img"/> <?php print t('Heard Mentality'); ?><span
            class="beta"><?php print t('Beta'); ?></span></a>
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
          <li><?php print l(t('Issues'), 'issues', array('attributes' => array('class' => 'issues'))); ?></li>
          <!--				  <li>-->
          <?php //print l(t('Analysis'), $_GET['q'], array('attributes' => array('class'=>'analysis'))); ?><!--</li>-->

          <li
            class="following"><?php print l(t('Analysis'), 'analysis', array('attributes' => array('class' => 'analysis'))); ?></li>

          <?php if (user_is_logged_in()) : ?>
            <li
              class="following"><?php print l(t('Following'), 'following', array('attributes' => array('class' => 'following'))); ?></li>
          <?php endif; ?>

          <li class="following"><?php print l(t('Analysis'), 'analysis', array('attributes' => array('class'=>'analysis'))); ?></li>

          <?php if (module_exists('moderation') && moderation_check_perm()) : ?>
            <li
              class="moderator"><?php print l(t('Moderator'), 'moderation', array('attributes' => array('class' => 'moderator'))); ?></li>
          <?php endif; ?>

        </ul>
        <ul
          class="menu second<?php if (module_exists('moderation') && moderation_check_perm()) : ?> full<?php endif; ?>">
          <li class="add_issue"><?php print l(t('Add an Issue'), 'create', array(
              'attributes' => array(
                'class' => 'add ' . theme('user_login_modal_class')
              )
            )); ?></li>
        </ul>
      </div>
      <?php if (module_exists('moderation') && moderation_check_perm()) : ?>
        <div class="top-right blue">
          <div class="expanding">
            <h6 class="inactive"><?php print t('Language'); ?></h6>
            <ul class="lang" style="display:none;" aria-hidden="true">
              <?php if ($multilanguage_area): print $multilanguage_area; endif; ?>
              ... <?php print t('more languages coming soon'); ?>
            </ul>
          </div>
        </div>
      <?php endif; ?>
    </div>
  </div>
</div>
