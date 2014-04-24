<?php if ($categories) : ?>
  <div class="grey-box poll-box">
    <i class="icon cat text icon-tag"></i>
    <ul class="tags">
      <label class="tags-on"><?php print __('SUBSCRIPTIONS', array('@code' => 'categories-subscriptions')); ?></label>
      <?php foreach ($categories as $term) : ?>
        <li><?php print theme('categories_subscribe', $term->name, term_hierarchy($term)); ?></li>
      <?php endforeach; ?>
    </ul>
    <div class="clear"></div>
  </div>
<?php endif; ?>
