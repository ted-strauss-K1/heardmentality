<?php if (!empty($users)) : ?>
  <?php foreach ($users as $f_user) : ?>
    <a href="/user/profile/view/<?php print $f_user->requestee->name; ?>" class="floatleft">
      <img class="following-user"
           id="uid-<?php print $f_user->requestee->uid; ?>"
           src="<?php print user_profile_image($f_user->requestee); ?>" />
    </a>
  <?php endforeach; ?>
<?php endif; ?>