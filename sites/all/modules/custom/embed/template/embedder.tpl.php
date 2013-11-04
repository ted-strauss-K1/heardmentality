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
    <a href="/"> <img src="<?php url(path_to_theme() . '/images/tiny_logo.png'); ?>"> <span>Heard Mentality</span>
      <span class="beta">Beta</span> </a>
  </div>
</div>
<div class="content <?php print $format; ?>">
  <?php print $content; ?>
</div>
<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1/jquery.min.js"></script>
<script src="<?php print $module_path; ?>/embed.js" data-loaded="true"></script>
<script src="/sites/all/libraries/easyxdm/easyXDM.min.js" type="text/javascript"></script>
<script>
  var socket = new easyXDM.Socket({
    onReady:  function(){
      socket.postMessage(document.body.scrollHeight);

      var results = $('tr.vote-results');
      if (!$('div.content > div.voted').length) {
        results.hide();
      }
      results.css('visibility', 'visible');

    }
  });
</script>
</body>
</html>
