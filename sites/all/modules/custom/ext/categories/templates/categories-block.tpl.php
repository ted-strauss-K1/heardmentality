<?php if ($nid) : ?>
<div class="grey-box poll-box">
  <i class="icon cat text icon-tag"></i>
  <ul class="tags">
    <label class="tags-on"><?php print t('This issue is listed under'); ?></label>
    <?php if ($categories) foreach ($categories as $hierarchy => $name) : ?>
    <li><?php print theme('categories_subscribe', $name, $hierarchy); ?></li>
    <?php endforeach; ?>
  </ul>
  <br class="clear">
  <hr class="short">
  <br>

  <p class="issue-meta">
    <?php if ($author_status) : ?>
      <?php print t('Posted by'); ?>
      <?php print l($node->name, 'user/profile/view/' . $node->uid, array('attributes' => array('class' => 'username'))); ?>
      <?php print t('on') ?>
    <?php else : ?>
      <?php print t('Posted on'); ?>
    <?php endif; ?>
    <br>
    <?php print date('M j, Y @ H:i', $node->created); ?>.
    <?php if ($orig_langcode != $display_language) : ?>
      <br>
      <?php print t('Read original post in'); ?>
      <?php printf("<a href='%s'>%s</a>", sprintf('/%s/%s', $orig_langcode, $orig_path), t($orig_language)); ?>
      <?php endif; ?>
  </p>

  <div class="clear"></div>
</div>
<?php endif; ?>
