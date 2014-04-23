<?php include "page_up.tpl.php"; ?>

  <div class="container">

    <div class="main-banner-display clearfix">
      <div class="one-third column">
        <div class="circle-box">
          <div class="see-banner circle-wrapper" id="circle0">
            <a class="see" href="issues"><span class="title"><?php print __('front-bubble-see', 'SEE'); ?></span>

              <p class="hover"><?php print __('front-bubble-see-text', 'See global opinions on important issues'); ?></p></a>
          </div>
        </div>
      </div>
      <div class="one-third column">
        <div class="circle-box">
          <div class="vote-banner circle-wrapper" id="circle1">
            <a class="vote-now" href="issues"><span class="title"><?php print __('front-bubble-vote', 'VOTE'); ?></span>

              <p class="hover"><?php print __('front-bubble-vote-text', 'Vote on issues and let your voice be heard'); ?></p></a>
          </div>
        </div>
      </div>
      <div class="one-third column ">
        <div class="circle-box">
          <div class="share-banner circle-wrapper" id="circle2">
            <a class="share-now" href="issues"><span class="title"><?php print __('front-bubble-share', 'SHARE'); ?></span>

              <p class="hover"><?php print __('front-bubble-share-text', 'Share your opinions with the community'); ?></p></a>
          </div>
        </div>
      </div>
    </div>

    <div class="container">
      <div class="sixteen columns top-mobile">

        <div class="border-bottom clearfix">
          <div class="helper">
            <p class="din banner-text">Heard Mentality: <?php print __('front-info', 'The Global Forum for Public Opinion'); ?>.</p>
            <span class="banven clearfix"><a href="<?php url('issues') ?>"
                                             class="button vote floatright participate"><?php print __('front-heard', 'Be heard!'); ?></a></span>
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
