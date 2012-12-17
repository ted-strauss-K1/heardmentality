<br class="clear"><br><br>

<div class="line-bottom2"></div>

<div id="footer">

  <div class="container">

    <div class="four columns">
      <div class="black-box">
        <p class="blurb ryde"><?php print t('Be Heard. Don\'t Be Part of the Herd!'); ?></p>
        <hr class="dark">

        <div class="floatleft"><a class="twitter" href="http://twitter.com/HeardMentality" target="_blank"></a></div>
        <div class="floatleft"><a class="facebook" href="http://www.facebook.com/pages/Heard-Mentality/253846777970342?ref=ts" target="_blank"></a>	</div>
		<div class="floatleft"><a class="facebook google" href="https://plus.google.com/102365576412479164048" target="_blank"></a>	</div>
        <div class="clear"></div>
      </div>
    </div>

    <div class="seven columns">
      <div class="black-box clearfix">
        <?php if ($footer_inner) print $footer_inner; ?>
      </div>
    </div>

    <div class="five columns">
      <div class="black-box">
        <a href="/"><img src="<?php print $directoryPath; ?>/images/dark_logo.png" class="dark-logo"></a>
        <ul class="din foot-link">
          <li><a href="/aboutus"><?php print t('ABOUT'); ?></a></li>
          <li><a href="/node/305"><?php print t('CONTACT'); ?></a></li>
          <li><a href="/donate"><?php print t('DONATE'); ?></a></li>
<!--          <li><a href="">--><?php //print t('VOLUNTEER'); ?><!--</a></li>-->
        </ul>
      </div>
    </div>

    <a rel="license" href="http://creativecommons.org/licenses/by-nc/3.0/" style="float:right;margin:0px 10px 0px 10px">
      <img alt="Creative Commons License" style="border-width:0" src="http://i.creativecommons.org/l/by-nc/3.0/88x31.png" />
    </a>
    <p class="policy">
      <?php print t('HEARD MENTALITY'); ?> &copy; <?php print date('Y') ?><br>
      <a><?php print t('Legal'); ?></a>
      <a><?php print t('Privacy'); ?></a>
      <a><?php print t('User Agreement'); ?></a>
    </p>

  </div>

</div>

<!-- user popups -->
<?php print $user_popups; ?>

<!-- closure -->
<?php print $closure; ?>
<!-- closure -->