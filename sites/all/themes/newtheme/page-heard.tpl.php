<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"><?php

global $user, $gSitePath, $apikey;
$directory = $base_path . $directory;
?>
<?php print $styles; ?>
<?php print $scripts; ?>
<script src="<?php echo $directory; ?>/scripts/jquery_1.js"></script>
<script src="<?php echo $directory; ?>/scripts/jquery.js"></script>
<script src="<?php echo $directory; ?>/scripts/jbubble.js"></script>
<script src="<?php echo $directory; ?>/scripts/jbubble.js"></script>
<script src="<?php echo $directory; ?>/scripts/localscroll.js"></script>
<script src="<?php echo $directory; ?>/scripts/init.js"></script>
<link href="<?php echo $directory; ?>/css/slider_css.css" rel="stylesheet" type="text/css">	

       
   <body style="background: none repeat scroll 0% 0% transparent;">
   <?php print $content; ?>
			
</body> 
