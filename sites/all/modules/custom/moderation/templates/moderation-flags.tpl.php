<?php if ($flags) : ?>
  <div class="grey-box full icon_inside">
    <i class="icon cat text icon-flagalt"></i> <label class="with_icon"><?php echo __('Flags', array('@code' => 'moderator-40')); ?></label>

    <?php foreach ($flags as $fid => $flag) : ?>

      <div class="mh_cell">
        <strong><?php print __($flag['title'], array('@code' => 'flag-' . $fid, '@textgroup' => 'flag')); ?></strong>

        <div class="flag_content">
          <?php foreach ($flag['users'] as $uid => $data) : ?>
          <?php print l($data['name'], 'user/profile/view/' . $uid); ?>: "<?php print $data['note']; ?>"
        </div>
        <?php endforeach; ?>
        <hr class="short"/>
      </div>

    <?php endforeach; ?>
  </div>
<?php endif; ?>
