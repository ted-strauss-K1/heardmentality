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
<?php print $content; ?>
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1/jquery.min.js"></script>
<script src="<?php print $module_path; ?>/embed.js" data-loaded="true"></script>
</body>
</html>