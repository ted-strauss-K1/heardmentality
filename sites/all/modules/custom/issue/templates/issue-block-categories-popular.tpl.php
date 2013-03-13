<div class="grey-box poll-box">
  <div class="icon cat text"></div>
  <ul class="tags">
    <label for="" class="tags-on"><?php print t('POPULAR CATEGORIES'); ?></label>
    <?php if ($categories) foreach ($categories as $hierarchy => $name) : ?>
    <li><?php print l($name, 'issues', array('query' => array('tids' => $hierarchy))); ?></li>
    <?php endforeach; ?>
  </ul>
  <div class="clear"></div>
</div>