<!doctype html><!--[if lt IE 7 ]>
<html class="ie ie6" xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>"
      lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <![endif]--><!--[if IE 7 ]>
<html class="ie ie7" xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>"
      lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <![endif]--><!--[if IE 8 ]>
<html class="ie ie8" xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>"
      lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <![endif]--><!--[if IE 9 ]>
<html class="ie9" xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>"
      lang="<?php print $language->language ?>"
      dir="<?php print $language->dir ?>"> <![endif]--><!--[if (gte IE 9)|!(IE)]><!-->
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>"
      lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <!--<![endif]-->
<head>

  <?php print $head; ?>
  <meta charset="utf-8"/>
  <title><?php print $head_title; ?></title>
  <meta name="description" content="Heard Mentality">
  <meta name="author" content="">
  <!--[if lt IE 9]>
  <script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script><![endif]-->
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1"/>
  <link href='http://fonts.googleapis.com/css?family=Open+Sans+Condensed:300,700&subset=latin,cyrillic' rel='stylesheet'
        type='text/css'>
  <?php print $styles; ?>

  <link rel="shortcut icon"
        href="<?php print url(path_to_theme() . '/images/favicon.ico', array('language' => '')); ?>">
  <link rel="apple-touch-icon"
        href="<?php print url(path_to_theme() . '/images/apple-touch-icon.png', array('language' => '')); ?>">
  <link rel="apple-touch-icon" sizes="72x72"
        href="<?php print url(path_to_theme() . '/images/apple-touch-icon-72x72.png', array('language' => '')); ?>"/>
  <link rel="apple-touch-icon" sizes="114x114"
        href="<?php print url(path_to_theme() . '/images/apple-touch-icon-114x114.png', array('language' => '')); ?>"/>

  <meta property="og:image"
        content="<?php print url(path_to_theme() . '/images/HM_Social_IMG_5.png', array('language' => '')); ?>"/>
  <img src="<?php print url(path_to_theme() . '/images/HM_Social_IMG_5.png', array('language' => '')); ?>"
       style="display:none"/>

  <!-- socialize.js script should only be included once -->
  <script type="text/javascript">
    var conf = { enabledProviders: 'facebook,twitter,yahoo,messenger,google,linkedin,myspace,aol,foursquare,orkut,vkontakte,renren' }
  </script>

</head>
<body style="background: #251b38; min-height: 100%">

<div class="maintenance_wrapper" style="width: 100%; min-height: 100%">

  <div class="maintenance_top"
       style="position:relative; width: 100%; background-color: #362750; background-position: bottom center; background-repeat: no-repeat; text-align: center">
    <div class="logo_maintenance"
         style="display: inline-block; background: url(/sites/all/themes/heardmentalitylight/images/logo_maintenance.png) left 20px no-repeat; font-family: 'DINLightRegular', 'Open Sans Condensed', Arial, sans-serif; font-size: 20px; color: white; padding: 20px 0 0 40px; margin: 0 auto">
      HEARD MENTALITY
    </div>
    <div class="img_earth_wrapper"
         style="padding-top: 30%; width: 50%; background: url(/sites/all/themes/heardmentalitylight/images/earth_800.png) bottom center no-repeat; background-size: 100%; position: relative; bottom: 0; margin: 0 auto;"></div>
  </div>

  <div class="maintenance_bottom" style="width: 100%; background-color: #251b38;">
    <?php if ($content) : ?>
      <div class="clearfix full din" id="region-content"
           style="width: 80%; font-family: 'DINLightRegular', 'Open Sans Condensed', Arial, sans-serif; line-height: 48px; font-size: 50px; color: white; padding: 20px 0; margin: 0 auto; text-align: center;">
        <?php print $content; ?>
      </div>
    <?php endif; ?>
  </div>
</div>

</body>
</html>
