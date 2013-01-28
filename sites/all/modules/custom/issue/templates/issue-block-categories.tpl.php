<?php if ($nid) : ?>
<div class="grey-box poll-box">
  <div class="icon cat text"></div>
  <ul class="tags">
    <label for="" class="tags-on"><?php print t('ACTIVE CATEGORIES'); ?></label>
    <?php foreach ($categories as $hierarchy => $name) : ?>
      <li><?php print l($name, 'issues', array('query' => array('tids' => $hierarchy))); ?></li>
    <?php endforeach; ?>
  </ul>
  <br class="clear">
  <hr class="short">
  <br>
  <p class="issue-meta"><?php print t('Posted on'); ?>
    <?php print date($node->created, 'M j, Y @ H:i'); ?>
    <br>
    <?php print t('by');?>
    <?php print l($node->name, 'user/profile/view/' . $node->uid, array('attributes' => array('class' => 'username'))); ?>.
    <?php if ($node->language != $original_language) : ?>
      <?php print t('Read original post in');?> <?php print l('', sprintf('/%s/%s', $original_language, $original_path)); ?>
    <?php endif; ?>
  </p>
  <div class="clear"></div>
</div>
<?php endif; ?>