<?php include "page_up.tpl.php"; ?>

<div class="container">

  <?php if ($tabs): ?>
    <div class="tabs"><?php print $tabs; ?></div>
  <?php endif; ?>

  <div class="page_title_wrapper">
    <?php if ($_title = drupal_set_subtitle()) : ?>
      <h2 class="dinbold page-title"><?php print $_title; ?></h2>
    <?php endif; ?>
  </div>

  <div class="four columns margin-top">

    <?php if ($right) : ?>
      <?php print $right; ?>
    <?php endif; ?>

  </div>

  <div class="twelve columns">

    <?php if ($content_top) : ?>
      <div class="grey-box clearfix full" id="region-content-top">
        <?php print $content; ?>
      </div>
    <?php endif; ?>

    <?php if ($content) : ?>
      <div class="white-box clearfix full <?php print $content_class; ?>" id="region-content">
        <?php print $content; ?>
      </div>
    <?php endif; ?>

    <?php if ($content_bottom) : ?>
      <div class="white-box clearfix full" id="region-content-bottom">
        <?php print $content_bottom; ?>
      </div>
    <?php endif; ?>
  </div>

</div>

<?php include "page_dn.tpl.php"; ?>
