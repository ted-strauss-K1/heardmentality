<div class="grey-box poll-box">
  <i class="icon cat text icon-tag"></i>
  <ul class="tags">
    <label class="tags-on"><?php print t('POPULAR CATEGORIES'); ?></label>
    <?php if ($categories) foreach ($categories as $hierarchy => $name) : ?>
    <li><?php print theme('issue_category', $name, $hierarchy); ?></li>
    <?php endforeach; ?>
  </ul>
  <div class="clear"></div>
</div>