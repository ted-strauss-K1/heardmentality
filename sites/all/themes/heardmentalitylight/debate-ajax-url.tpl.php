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
    <span id="img_count"><?php print $image_first ?></span> of <?php print $image_count ?>
  </div>
  <div class="rightfm"><?php print $info ?>
    <span class="no_thumb">
        <input type="checkbox" name="no_thumbnail" id="no_thumbnail" />No Thumbnail
        <input type="hidden" name="udesc" value="<?php print myTruncate($info, 255) ?>"/>
        <input type="hidden" id="final_uimage" name="uimg" value="<?php print $images[0] ?>"/>
      </span>
  </div>
</div>