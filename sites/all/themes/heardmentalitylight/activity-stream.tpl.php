<div class="uactivity" id="uactivity">
  <?php if (empty($items)) : ?>
    <?php print t('No user activity found.'); ?>
  <?php else : ?>
    <?php foreach ($items as $item) : ?>
      <?php print theme('activity_stream_item', $item['id'], $item['uid'], $item['type'], $item['variables'], $item['date_added']); ?>
    <?php endforeach; ?>
  <?php endif; ?>
</div>