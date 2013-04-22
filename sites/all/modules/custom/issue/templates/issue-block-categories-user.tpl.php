<?php if ($categories) : ?>
<div class="grey-box poll-box" style="margin-top: 20px">
  <i class="icon cat text icon-tag"></i>
  <ul class="tags">
    <label class="tags-on"><?php print t('SUBSCRIPTIONS'); ?></label>
    <?php foreach ($categories as $term) : ?>
    <li><?php print theme('issue_category', $term->name, issue_term_parents($term)); ?></li>
    <?php endforeach; ?>
  </ul>
  <div class="clear"></div>
</div>
<?php endif; ?>
