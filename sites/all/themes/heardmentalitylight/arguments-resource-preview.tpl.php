<?php
  global $base_url;
  $images = $node->images;
  $count = count($images);
  $image_count = $count > 10 ? '10' : $count;
  $image_first = $count > 0 ? 1 : 0;
  $image_last = $image_count != 0 ? ($image_count - 1) : 0;
  $image_path = $base_url . '/' . drupal_get_path('theme', 'heardmentalitylight') . '/images/';
?>

<div class="linkbox_inner">
  <div class="img-selector">
    <div class="inner">
      <?php for($i = 0; $i < $image_count; $i++) : ?>
        <div class="cur-img">
          <img id="cur_img_<?php print $i ?>" src="<?php print $images[$i] ?>" width="118" height="73" alt="" />
        </div>
        <?php endfor; ?>
      <input type="hidden" id="cur_id_val" value="0" />
      <input type="hidden" id="end_image" value="<?php print $image_last ?>" />
      <input type="hidden" id="pre_id_val" value="" />
    </div>
  </div>
  <div class="img_controls">
      <span class="left_right">
        <a href="javascript:void(0)" title="previous"  id="re-sel-pre">
          <img src="<?php print $image_path ?>arrow_left.png" alt="Previous image">
        </a>
        <a href="javascript:void(0)" title="next"  id="re-sel-next">
          <img src="<?php print $image_path ?>arrow_right.png" alt="Next image">
        </a>
      </span>
  <?php if ($node->noimage) : ?>
    <span id="img_count"><?php print $image_first ?></span> of <?php print $image_count ?>
  <?php endif; ?>
  </div>
  <div class="rightfm">
    <em><?php print $node->title ?></em>
    source:&nbsp;<strong><?php print $node->domain ?></strong>
    <span><?php print $node->body ?></span>
    <span class="no_thumb">
      <?php if ($node->noimage) : ?>
        <input type="checkbox" name="no_thumbnail" id="no_thumbnail" />No Thumbnail
      <?php else : ?>
        <input type="hidden" name="no_thumbnail" id="no_thumbnail" value="1" />
      <?php endif; ?>
        <input type="hidden" id="final_uimage" name="uimg" value="<?php print $images[0] ?>"/>
      </span>
  </div>
</div>