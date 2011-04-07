<?php
// $Id: comment.tpl.php,v 1.1 2009/07/22 18:24:01 proxiss Exp $

/**
 * @file
 * aproxisstheme implementation for comments.
 *
 */
?>
<div class="comment<?php print $comment->new ? ' comment-new' : ''; print ' '. $status ?> clear-block">
  
  <div class="meta">
    <span class='cid'><?php print '#'. $comment->cid; ?></span>
	  <?php if ($comment->new): ?>
	    <div class="new"><?php print $new ?></div>
	  <?php endif; ?>
	  <?php print $picture ?>
  </div>

  <div class="content">
	  <span class="submitted">
	    <?php print $submitted ?>
	  </span>
    <h3><?php print $title ?></h3>
    <?php print $content ?>
    <?php if ($signature): ?>
    <div class="user-signature clear-block">
      <?php print $signature ?>
    </div>
    <?php endif; ?>
    <?php print $links ?>
  </div>

</div>
