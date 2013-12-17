<?php include "page_up.tpl.php"; ?>

  <div class="container">

    <?php if ($content) : ?>
      <?php print $content; ?>
    <?php endif; ?>

    <?php if ($content_bottom) : ?>
      <?php print $content_bottom; ?>
    <?php endif; ?>

  </div>

<?php include "page_dn.tpl.php"; ?>
