<?php if (user_is_logged_in()) : ?>
  <?php print __('Permission denied', array('@code' => 'user_login_modal-02')); ?>
<?php else : ?>
  <div id="popup-login">
    <div class="popup-login-inner <?php print is_mobile() ? 'mobile' : ''; ?>">

      <div id="tabs-1" class="popup-tab">
        <div id="user-login">
          <h2><?php print __('Login', array('@code' => 'user_login_modal-03')); ?></h2>
          <?php print drupal_get_form('user_login'); ?>
        </div>
      </div>

      <div id="tabs-2" class="popup-tab">
        <div id="user-register">
          <h2><?php print __('Register', array('@code' => 'user_login_modal-04')); ?></h2>
          <?php print drupal_get_form('user_register'); ?>
        </div>
      </div>

    </div>
  </div>

  <script>
    (function () {
      Recaptcha.create(
        '<?php print variable_get('recaptcha_public_key', ''); ?>',
        'recaptcha_ajax_api_container',
        {theme: '<?php print variable_get('recaptcha_theme', 'red'); ?>'}
      );
    })();
  </script>

<?php endif; ?>
