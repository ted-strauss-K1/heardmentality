<?php if ($nid) : ?>
<div class="grey-box poll-box">
  <div class="icon cat text"></div>
  <ul class="tags">
    <label for="" class="tags-on"><?php print t('ACTIVE CATEGORIES'); ?></label>
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
    <?php if ($node->language != $original_langcode) : ?>
      <br>
      <?php print t('Read original post in');?>
      <?php printf("<a href='%s'>%s</a>", sprintf('/%s/%s', $original_langcode, $original_path), t($original_language)); ?>
    <?php endif; ?>
  </p>
  <div class="clear"></div>
</div>
<?php endif; ?>