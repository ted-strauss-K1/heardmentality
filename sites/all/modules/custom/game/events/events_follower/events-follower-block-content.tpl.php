<?php if (!empty($users)) : ?>
  <?php foreach ($users as $f_user) : ?>
    <?php print l('<img class="following-user"
           id="uid-' . $f_user->requestee->uid . '"
           src="' . user_profile_image($f_user->requestee) . '"/>', 'user/profile/view/' . $f_user->requestee->name, array(
        'html'       => TRUE,
        'attributes' => array(
          'class' => 'floatleft',
        ),
      )); ?>
  <?php endforeach; ?>
<?php endif; ?>
