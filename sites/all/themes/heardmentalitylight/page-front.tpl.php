<?php include "page_up.tpl.php"; ?>

  <div class="container">

    <div class="main-banner-display clearfix">
      <div class="one-third column">
        <div class="circle-box">
          <div class="see-banner circle-wrapper" id="circle0">
            <a class="see" href="issues"><span class="title"><?php print __('SEE', array('@code' => 'page-front-01')); ?></span>

              <p class="hover"><?php print __('See global opinions on important issues', array('@code' => 'page-front-02')); ?></p></a>
          </div>
        </div>
      </div>
      <div class="one-third column">
        <div class="circle-box">
          <div class="vote-banner circle-wrapper" id="circle1">
            <a class="vote-now" href="issues"><span class="title"><?php print __('VOTE', array('@code' => 'page-front-03')); ?></span>

              <p class="hover"><?php print __('Vote on issues and let your voice be heard', array('@code' => 'page-front-04')); ?></p></a>
          </div>
        </div>
      </div>
      <div class="one-third column ">
        <div class="circle-box">
          <div class="share-banner circle-wrapper" id="circle2">
            <a class="share-now" href="issues"><span class="title"><?php print __('SHARE', array('@code' => 'page-front-05')); ?></span>

              <p class="hover"><?php print __('Share your opinions with the community', array('@code' => 'page-front-06')); ?></p></a>
          </div>
        </div>
      </div>
    </div>

    <div class="container">
      <div class="sixteen columns top-mobile">

        <div class="border-bottom clearfix">
          <div class="helper">
            <p class="din banner-text">Heard Mentality: <?php print __('The Global Forum for Public Opinion', array('@code' => 'page-front-07')); ?>.</p>
            <span class="banven clearfix"><a href="<?php url('issues') ?>"
                                             class="button vote floatright participate"><?php print __('Be heard!', array('@code' => 'page-front-08')); ?></a></span>
          </div>
        </div>
      </div>
    </div>

  </div>

  <div class="container">

    <div class="nine columns">

      <?php if ($front_activity) {
        print $front_activity;
      } ?>

    </div>

    <div class="seven columns">

      <div class="white-box hide-on-mobiles">
        <?php if ($front_heatmap) {
          print $front_heatmap;
        } ?>
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
