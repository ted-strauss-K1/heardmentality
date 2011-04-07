<?php
// $Id: node.tpl.php,v 1.1 2009/07/22 18:24:01 proxiss Exp $

/**
 * @file
 * Main node template.
 *
 * Main node template for all node-types in adarkproxisstheme.
 */

?>
<div id="node-<?php print $node->nid; ?>" class="node
<?php 
  print ' nt-'. $node->type; 
  if ($teaser) 
    print ' teaser'; 
  if ($sticky) 
    print ' sticky'; 
  if (!$status) 
    print ' node-unpublished'; 
?>">

<?php if (!$page): ?>
  <h2><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
<?php endif; ?>

<div class="meta">
  <?php if ($submitted): ?>
    <span class="submitted"><?php print $submitted ?></span>
  <?php endif; ?>
  <?php if ($terms && $page): ?>
    <div class="terms"><?php print $terms ?></div>
  <?php endif;?>
</div>

<?php print $picture ?>

<div class="content clear-block">
    <?php print $content ?>
</div>

  <div class="clear-block">
    <?php if ($links): ?>
      <div class="links"><?php print $links; ?></div>
    <?php endif; ?>
  </div>

</div>
