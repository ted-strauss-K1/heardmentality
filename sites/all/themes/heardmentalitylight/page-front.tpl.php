<?php include "page_up.tpl.php"; ?>

<div class="container">

  <div class="main-banner-display clearfix">
    <div class="one-third column">
      <div class="circle-box">
        <div class="see-banner circle-wrapper" id="circle0">
          <a class="see" href=""><span class="hover" style="display:none"></span></a>
        </div>
      </div>
    </div>
    <div class="one-third column">
      <div class="circle-box">
        <div class="vote-banner circle-wrapper" id="circle1">
          <a class="vote-now" href=""><span class="hover" style="display:none"></span></a>
        </div>
      </div>
    </div>
    <div class="one-third column ">
      <div class="circle-box">
        <div class="share-banner circle-wrapper" id="circle2">
          <a class="share-now" href=""><span class="hover" style="display:none"></span></a>
        </div>
      </div>
    </div>
  </div>

  <div class="container">
    <div class="sixteen columns top-mobile">

      <div class="border-bottom clearfix">
        <p class="din banner-text"><?php print t('Heard Mentality: The Global Forum for Public Opinion'); ?>.</p>
        <span class="banven clearfix"><a href="/issues" class="button vote floatright participate"><?php print t('Be heard!'); ?></a></span>
      </div>
    </div>
  </div>

</div>

<div class="container">

  <div class="nine columns">

    <?php if ($front_activity) print $front_activity; ?>

  </div>

  <div class="seven columns">

    <div class="white-box hide-on-mobiles">
      <?php if ($front_heatmap) print $front_heatmap; ?>
    </div>

    <?php if ($front_right) : ?>
      <div class="grey-box-cat clearfix">
        <ul class="tags">
          <?php print $front_right; ?>
        </ul>
      </div>
    <?php endif; ?>

    <?php if ($right) : ?>
      <?php print $right; ?>
    <?php endif; ?>

  </div>
</div>

<?php include "page_dn.tpl.php"; ?>