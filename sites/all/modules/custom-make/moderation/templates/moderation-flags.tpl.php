<?php if ($flags) : ?>
  <div class="grey-box full icon_inside">
    <i class="icon cat text icon-flagalt"></i> <label class="with_icon"><?php echo t('Flags'); ?></label>

    <?php foreach ($flags as $fid => $flag) : ?>

      <div class="mh_cell">
        <strong><?php print t($flag['title']); ?></strong>

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
