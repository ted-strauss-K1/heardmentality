<ul class="action">
  <div class="uactivity" id="uactivity">
    <?php if (empty($items)) : ?>
    <?php print t('No user activity found.'); ?>
    <?php else : ?>
    <?php foreach ($items as $item) : ?>
      <?php print theme('events_item', $item); ?>
      <?php endforeach; ?>
    <?php endif; ?>
  </div>
</ul>