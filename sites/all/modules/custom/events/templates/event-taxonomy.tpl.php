<?php if (!$skip) : ?>
  <li class="clearfix">
    <ul class="tags">
      <label class="tags-on"></label>
      <?php if ($categories) foreach ($categories as $hierarchy => $name) : ?>
        <li><?php print theme('issue_category', $name, $hierarchy); ?></li>
      <?php endforeach; ?>
    </ul>
    <br clear="both">
    <p class="action-comment-ref">
      <?php print t('New issue posted') . ' ' . $link ?>
      <br clear="both">
    </p>
    <span class="submitted" name="<?php print $item['timestamp']; ?>"><?php print $item['date_added']; ?></span>
  </li>
<?php endif; ?>