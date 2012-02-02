<?php
// $Id: page.tpl.php,v 1.11.2.1 2009/04/30 00:13:31 goba Exp $

/**
 * @file page.tpl.php
 *
 * Theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 */
global $user, $gSitePath, $apikey;
$directory = $base_path . $directory;
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

    <head>
        <?php print $head; ?>
        <title><?php print $head_title; ?></title>
        <link rel="shortcut icon" type="image/x-icon" href="<?php echo $directory; ?>/images/favico.ico"/>

        <?php print $styles; ?>
 <script type="text/javascript">
     var gSitePath='<?php print $gSitePath;?>';</script>

        <?php print $scripts; ?>

</head>
<body style="background:none;background:#FFF;">
    <div class="popup-add-suggest" id="log">
	<div class="facttop"> <?php print $title; ?></div>
	<div id="log_res"><!-- spanner --></div>
	</div>
	<span class="clr"><!-- spanner --></span>

   <div id="log_res_ans"><!-- spanner --></div>
	<span class="clr"><!-- spanner --></span>

             <div class="inner5">
       <?php echo $content;?>
        </div>


      <!--content area close-->
	  </div>
	 </body>
	 </html>
