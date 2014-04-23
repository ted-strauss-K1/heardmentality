<div id="block-<?php print $block->module . '-' . $block->delta; ?>" class="block block-<?php print $block->module ?>">
  <?php if ($block->subject): ?>
    <div class="<?php echo $class ?>"><?php print __('block_subject-' . $block->module . '-' . $block->delta, $block->subject); ?></div>
  <?php endif; ?>


  <?php print $block->content ?>

</div>
