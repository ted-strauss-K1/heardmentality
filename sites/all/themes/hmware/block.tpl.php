<?php
// $Id: block.tpl.php,v 1.4 2007/09/01 05:42:48 dries Exp $

/**
 * @file block.tpl.php
 *
 * Theme implementation to display a block.
 *
 * Available variables:
 * - $block->subject: Block title.
 * - $block->content: Block content.
 * - $block->module: Module that generated the block.
 * - $block->delta: This is a numeric id connected to each module.
 * - $block->region: The block region embedding the current block.
 *
 * Helper variables:
 * - $block_zebra: Outputs 'odd' and 'even' dependent on each block region.
 * - $zebra: Same output as $block_zebra but independent of any block region.
 * - $block_id: Counter dependent on each block region.
 * - $id: Same output as $block_id but independent of any block region.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * @see template_preprocess()
 * @see template_preprocess_block()
 */
     // Determines if we have right or left blocks to build - if zero on either
     // then we set our COLSPAN in our primary table layout to 2, instead of 3
 if($block->region=='left')
         $class='commutop-profile';
 else if($block->region=='Beat')
         $class='facttop_beat';		 
 else
     $class='facttop';
 
?>
<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="block block-<?php print $block->module ?>">
<?php if ($block->subject): ?>
     <div class="<?php echo $class?>"><?php print t($block->subject); ?></div>
<?php endif;?>

 <div class="facttext">
    <?php print $block->content ?>
  </div>
</div>