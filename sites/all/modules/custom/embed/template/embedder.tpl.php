<!DOCTYPE html>
<html lang="en" dir="ltr">
<head>
  <title><?php print $title; ?></title>
  <base href="http://<?php print $_SERVER['HTTP_HOST'] ?>">
  <link rel="stylesheet" href="<?php print $module_path; ?>/embed.css">
  <link rel="canonical" href="<?php print $path; ?>">
  <style>
    @-o-viewport { width: device-width; }
    @-moz-viewport { width: device-width; }
    @-ms-viewport { width: device-width; }
    @-webkit-viewport { width: device-width; }
    @viewport { width: device-width; }
  </style>
<body>
<div class="top-line">
  <div class="top-line-logo">
    <a href="/"> <img src="/sites/all/themes/heardmentalitylight/images/tiny_logo.png"> <span>Heard Mentality</span>
      <span class="beta">Beta</span> </a>
  </div>
</div>
<div class="content <?php print $format; ?>">
  <?php print $content; ?>
</div>
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1/jquery.min.js"></script>
<script src="<?php print $module_path; ?>/embed.js" data-loaded="true"></script>
</body>
</html>
