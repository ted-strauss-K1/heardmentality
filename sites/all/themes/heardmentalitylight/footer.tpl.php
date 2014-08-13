<br class="clear"><br><br>

<div class="line-bottom2"></div>

<div id="footer">

  <div class="container">

    <div class="four columns">
      <div class="black-box">
        <p class="blurb ryde"><?php print __("Be Heard! Don't Be Part of the Herd.", array('@code' => 'site-blurb')); ?></p>
        <hr class="dark">

        <div class="floatleft"><a class="twitter" href="http://twitter.com/HeardMentality" target="_blank"><i
              class="icon-twitter"></i></a></div>
        <div class="floatleft"><a class="facebook"
                                  href="http://www.facebook.com/pages/Heard-Mentality/253846777970342?ref=ts"
                                  target="_blank"><i class="icon-facebook"></i></a></div>
        <div class="floatleft"><a class="facebook google" href="https://plus.google.com/102365576412479164048"
                                  target="_blank"><i class="icon-googleplus"></i></a></div>
        <div class="clear"></div>
      </div>
    </div>

    <div class="seven columns">
      <div class="black-box clearfix">
        <?php if ($footer_inner) {
          print $footer_inner;
        } ?>
      </div>
    </div>

    <div class="five columns">
      <div class="black-box">
        <?php print l('<img src="' . url(path_to_theme() . '/images/dark_logo.png', array('language' => '')) . '" class="dark-logo">', '', array('html' => TRUE)); ?>
        <ul class="din foot-link">
          <li><?php print l(__('ABOUT', array('@code' => 'footer-01')), 'aboutus'); ?></li>
          <li><?php print l(__('CONTACT', array('@code' => 'footer-02')), 'contact'); ?></li>
          <li><?php print l(__('DONATE', array('@code' => 'footer-03')), 'donate'); ?></li>
        </ul>
      </div>
    </div>

    <a class="cc_footer_link" rel="license" href="http://creativecommons.org/licenses/by-nc/3.0/" >
      <img alt="Creative Commons License" style="border-width:0" src="http://i.creativecommons.org/l/by-nc/3.0/88x31.png" />
    </a>

    <p class="policy">
      <?php print __('HEARD MENTALITY', array('@code' => 'footer-04')); ?> &copy; <?php print date('Y') ?><br>
      <?php print l(__('Privacy Policy', array('@code' => 'footer-05')), 'privacy'); ?>
    </p>

  </div>

</div>

<!-- user popups -->
<?php print $user_popups; ?>

<!-- closure -->
<?php print $closure; ?>
<!-- closure -->
