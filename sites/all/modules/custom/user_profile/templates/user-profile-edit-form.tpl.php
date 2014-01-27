<?php

/*
 * Necessary drupal's form info
 */
print drupal_render($form['form_token']);
print drupal_render($form['form_build_id']);
print drupal_render($form['form_id']);

/*
 * Print hidden values
 */
$result = _profile_get_fields('hidden');
while ($field = db_fetch_object($result)) {
  print drupal_render($form[$field->name]);
}

print drupal_render($form['state']);
print drupal_render($form['city']);
print drupal_render($form['img_avt']);
print drupal_render($form['image']);
print drupal_render($form['oldimg']);
print drupal_render($form['current_image']);

$privacy = user_profile_profile_privacy_values();

?>

<div class="page_title_wrapper">
  <h2 class="dinbold page-title"><?php print t('Edit Profile'); ?></h2>
</div>

<div class="four columns edit_profile_four_columns">

  <div class="dark-grey-box top clearfix">
    <div class="profile-meta">
      <i class="icon cat text icon-businesscardalt"></i> <label for="profile"
                                                                class="white_text with_icon"><?php print t('Change Photo'); ?></label>
      <?php print drupal_render($form['image_upload']); ?>
      <div id="brow_img_name"></div>
      <p class="choose_pic">
        ...<?php print t('or choose a picture'); ?>
        <a href="#" id="user-profile-avatar-selection-open"
           title="<?php print t('Pick a photo') ?>"> <?php print t('here'); ?> </a>
      </p>
      <?php print drupal_render($form['image_submit']); ?>
      <?php print drupal_render($form['image_avatar']); ?>
    </div>
  </div>

  <?php if ($form['subscription_notify']) : ?>
    <div class="grey-box full clearfix">
      <label for="" class="subscriptions"><?php print t('Subscriptions'); ?></label>

      <p class="twelve"><?php print t('Send me a summary of what\'s happening on Heard Mentality to my email'); ?></p>
      <ul class="subscription">
        <li><span class="privacy-answer"><?php print t('Never'); ?></span><br></li>
        <li><span class="privacy-answer"><?php print t('Monthly'); ?></span><br></li>
        <li><span class="privacy-answer"><?php print t('Weekly'); ?></span></li>

        <?php print drupal_render($form['subscription_notify']); ?>
        <?php print drupal_render($form['subscription_email']); ?>
        <?php print drupal_render($form['subscription_submit']); ?>
      </ul>
    </div>
  <?php endif; ?>

  <div class="grey-box full clearfix">
    <label for="" class="subscriptions"><?php print t('Language settings'); ?></label>

    <p class="twelve"><?php print t('Set your default language'); ?></p>
    <?php print drupal_render($form['language']); ?>
    <?php print drupal_render($form['language_submit']); ?>
  </div>

</div>

<div class="twelve columns">

  <div class="grey-box clearfix" id="edit_profile">

    <h2 class="din"><?php print t('Profile Settings'); ?></h2>

    <div class="privacy-info">
      <p><strong><?php print t('Privacy'); ?></strong>
        <?php print t('Set the privacy levels for each of your profile characteristics. If you choose to hide your profile details, your demographic info will still be calculated but not shown. No one will ever know.'); ?>
      </p>
    </div>

    <div class="user-info">
      <ul class="user-info-inputs clearfix">

        <li class="username">
          <label for="" class="add-on-2 small"><span class="title-2">
            <?php print t('Username'); ?>
              <small class="red">*</small></span> </label>
          <?php print drupal_render($form['username']); ?>
        </li>

        <li class="password">
          <label for="" class="add-on-2 small"><span class="title-2">
          <?php print t('Password'); ?> </span> </label>
          <?php print drupal_render($form['password']); ?>
        </li>


        <li class="email">
          <label for="" class="add-on-2 small"><span class="title-2">
          <?php print t('Email'); ?>
              <small class="red">*</small></span> </label>
          <?php print drupal_render($form['email']); ?>

          <?php if ($privacy) : ?>
            <div class="visible-to"><?php print t('Visible to'); ?>:</div>
            <ul class="privacy">
              <fieldset>
                <?php foreach ($privacy as $key => $value) : ?>
                  <li class="privacy-rules" title="<?php print $value['description'] ?>">
                    <span class="privacy-answer"><?php print $value['label']; ?></span>
                  </li>
                <?php endforeach; ?>
                <?php print drupal_render($form['private_profile_email']); ?>
              </fieldset>
            </ul>
          <?php endif; ?>
        </li>

        <?php $result = _profile_get_fields('profile');
        while ($field = db_fetch_object($result)) : ?>
          <li>
            <label for="" class="add-on-2 small"><span class="title-2"><?php print t($field->title); ?></span></label>
            <?php print drupal_render($form[$field->name]); ?>

            <?php if ($privacy) : ?>
              <div class="visible-to"><?php print t('Visible to'); ?>:</div>
              <ul class="privacy">
                <fieldset>
                  <?php foreach ($privacy as $key => $value) : ?>
                    <li class="privacy-rules" title="<?php print $value['description'] ?>">
                      <span class="privacy-answer"><?php print $value['label']; ?></span>
                    </li>
                  <?php endforeach; ?>
                  <?php print drupal_render($form['private_' . $field->name]); ?>
                </fieldset>
              </ul>
            <?php endif; ?>
          </li>
          <?php if ($field->name == 'profile_name') : ?>
            <li class="user-profile-location">
              <div class="determine"><?php print l(t('Determine my location'), 'user/profile/edit', array(
                  'attributes' => array(
                    'class' => 'geocode_latlng',
                  ),
                )); ?></div>
            </li>
          <?php endif; ?>
          <?php if ($field->name == 'profile_zip') : ?>
            <li class="user-profile-location">
              <div class="determined"><?php print drupal_render($form['location']) ?></div>
            </li>
          <?php endif; ?>
        <?php endwhile; ?>

        <?php $result = _profile_get_fields('links');
        while ($field = db_fetch_object($result)) : ?>
          <li>
            <label for="" class="add-on-2 small"><span class="title-2"><?php print t($field->title); ?></span></label>
            <?php print drupal_render($form[$field->name]); ?>

            <?php if ($privacy) : ?>
              <div class="visible-to"><?php print t('Visible to'); ?>:</div>
              <ul class="privacy">
                <fieldset>
                  <?php foreach ($privacy as $key => $value) : ?>
                    <li class="privacy-rules" title="<?php print $value['description'] ?>">
                      <span class="privacy-answer"><?php print $value['label']; ?></span>
                    </li>
                  <?php endforeach; ?>
                  <?php print drupal_render($form['private_' . $field->name]); ?>
                </fieldset>
              </ul>
            <?php endif; ?>
          </li>

        <?php endwhile; ?>

      </ul>

      <?php print drupal_render($form['submit']); ?>

    </div>
    <!-- /.user-info -->
  </div>
  <!-- /.grey-box.edit_profile -->
</div><!-- /.twelve.columns -->

<div id="user-profile-avatar-selection-wrapper" style="display:none">
  <div id="user-profile-avatar-selection">
    <?php global $user;
    print theme('user_profile_avatar_selection', $user); ?>
    <br style="clear:both">
  </div>
</div>
