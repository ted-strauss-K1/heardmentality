<?php include "page_up.tpl.php"; ?>

  <div class="container">

    <div class="page_title_wrapper">
      <?php if ($_title = drupal_set_subtitle()) : ?>
        <h2 class="dinbold page-title"><?php print $_title; ?></h2>
      <?php endif; ?>
    </div>

    <?php if ($content_top) : ?>
      <div class="grey-box clearfix full" id="region-content-top">
        <?php print $content_top; ?>
      </div>
    <?php endif; ?>

    <?php if ($content) : ?>
      <div class="white-box clearfix full" id="region-content">
        We're terribly sorry but we've down for maintenance.
        <?php print $content; ?>
      </div>
    <?php endif; ?>

    <?php if ($content_bottom) : ?>
      <div class="white-box clearfix full" id="region-content-bottom">
        <?php print $content_bottom; ?>
      </div>
    <?php endif; ?>

  </div><? theme(); ?>

<?php include "page_dn.tpl.php"; ?>
