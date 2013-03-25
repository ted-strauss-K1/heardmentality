<?php if ($nid) : ?>
<div class="grey-box poll-box">
  <div class="icon cat text"></div>
  <ul class="tags">
    <label for="" class="tags-on"><?php print t('This issue is listed under'); ?></label>
    <?php if ($categories) foreach ($categories as $hierarchy => $name) : ?>
    <li><?php print l($name, 'issues', array('query' => array('tids' => $hierarchy))); ?></li>
    <?php endforeach; ?>
  </ul>
  <br class="clear">
  <hr class="short">
  <br>

  <p class="issue-meta"><?php print t('Posted'); ?>
    <?php print t('by');?>
    <?php print l($node->name, 'user/profile/view/' . $node->uid, array('attributes' => array('class' => 'username'))); ?>
    <?php print t('on') ?>
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