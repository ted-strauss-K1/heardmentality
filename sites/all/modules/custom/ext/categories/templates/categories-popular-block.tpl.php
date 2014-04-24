<!--<div class="grey-box poll-box">--><i class="icon cat text icon-tag"></i>
<ul class="tags">
  <label class="tags-on"><?php print __('POPULAR CATEGORIES', array('@code' => 'categories-popular')); ?></label>
  <?php if ($categories) {
    foreach ($categories as $hierarchy => $name) : ?>
      <li><?php print theme('categories_subscribe', $name, $hierarchy); ?></li>
    <?php endforeach;
  } ?>
</ul>
<div class="clear"></div><!--</div>-->
