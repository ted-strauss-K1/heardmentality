<?php
global $base_url;
$images = $node->images;
$count = count($images);
$image_count = $count > 10 ? '10' : $count;

// TODO fix the paths
$image_path = $base_url . '/' . drupal_get_path('theme', 'heardmentalitylight') . '/images/';
?>

<div class="linkbox_inner">
  <div class="img-selector">
    <div class="inner">
      <input type="hidden" id="final_uimage" name="uimg" value="<?php print $images[0] ?>"/>
      <input type="hidden" name="uimg_index" value="0"/>

      <?php for ($i = 0; $i < $image_count; $i++) : ?>
      <div class="cur-img">
        <img id="cur_img_<?php print $i ?>" style="<?php print $i <> 0 || $node->noimage ? 'display:none' : ''; ?>"
             src="<?php print $images[$i] ?>" width="118" height="73" alt=""/>
      </div>
      <?php endfor; ?>
    </div>
  </div>
  <div class="img_controls">
    <?php if ($image_count > 1) : ?>
    <span class="left_right">
        <a href="javascript:void(0)" title="previous" id="re-sel-pre" class="img-select prev" style="display:none">
          <img src="<?php print $image_path ?>arrow_left.png" alt="Previous image">
        </a>
        <a href="javascript:void(0)" title="next" id="re-sel-next" class="img-select next">
          <img src="<?php print $image_path ?>arrow_right.png" alt="Next image">
        </a>
      </span>
    <span class="img_counter"><span id="img_count">1</span> of <?php print $image_count ?></span>
    <?php endif; ?>
  </div>
  <div class="rightfm">
    <?php // todo translate texts ?>
    <a href="javascript:void(0)" class="del_ref"
       onclick="$('#argument-add-form').reset(); $('#linkbox').html(''); $('#add_argument').val('Attach');"><span>x</span></a>
    <em><?php print $node->title ?></em>
    <?php print t('source') ?>:&nbsp;<strong><?php print $node->field_source[0]['value'] ?></strong>
    <span><?php print !empty($node->body) ? $node->body : ''; ?></span>
    <span class="no_thumb">
      <input type="checkbox" name="no_thumbnail" id="no_thumbnail"
             value="<?php print (int)($node->noimage) ?>"/><?php print t('No thumbnail') ?>
    </span>
  </div>
</div>
