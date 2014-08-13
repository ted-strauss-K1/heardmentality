<div id="block-<?php print $block->module . '-' . $block->delta; ?>" class="block block-<?php print $block->module ?>">
  <?php if ($block->subject): ?>
    <div class="<?php echo $class ?>"><?php print __($block->subject, array('@code' => $block->module . '-' . $block->delta, '@textgroup' => 'block')); ?></div>
  <?php endif; ?>


  <?php print $block->content ?>

</div>
