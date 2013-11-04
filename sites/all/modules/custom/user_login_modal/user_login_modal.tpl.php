<?php if (user_is_logged_in()) : ?>
  <?php print t('Permission denied'); ?>
<?php else : ?>
  <div id="popup-login">
    <div class="popup-login-inner <?php print is_mobile() ? 'mobile' : ''; ?>">

      <div id="tabs-1" class="popup-tab">
        <div id="user-login">
          <h2><?php print t('Login'); ?></h2>
          <?php print drupal_get_form('user_login'); ?>
        </div>
      </div>

      <div id="tabs-2" class="popup-tab">
        <div id="user-register">
          <h2><?php print t('Register'); ?></h2>
          <?php print drupal_get_form('user_register'); ?>
        </div>
      </div>

    </div>
  </div>
<?php endif; ?>
