<?php if ($flags) : ?>
<div class="dark-grey-box">
  <div class="profile-meta profile_page_wrapper">
    <label for="profile" class="profile profile_page"><?php print t('Flags') ?></label>
  </div>

  <?php foreach ($flags as $fid => $flag) : ?>

    <?php print t($flag['title']); ?>
    <hr style="margin:3px 0 5px 0" />
    <ul>
    <?php foreach ($flag['users'] as $uid => $data) : ?>
      <li><?php print l($data['name'], 'user/profile/view/'.$uid); ?>: "<?php print $data['note']; ?>"</li>
    <?php endforeach; ?>
    </ul>

  <?php endforeach; ?>
</div>
<?php endif; ?>