<ul class="action">
  <div class="uactivity" id="uactivity" name="<?php #print $settings; ?>">
    <?php $viewed = 0; ?>
    <?php foreach ($items as $item) : ?>
      <?php
      if ($content = theme('events_item', $item)) {
        $viewed++;
        print $content;
      }
      ?>
    <?php endforeach; ?>
    <?php if (!$viewed) : ?>
      <div class="msg nomsg"><?php print t('No user activity found.'); ?></div>
    <?php endif; ?>
  </div>
</ul>
