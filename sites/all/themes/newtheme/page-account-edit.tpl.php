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
        <title><?php print $title; ?></title>
        <link rel="shortcut icon" type="image/x-icon" href="<?php echo $directory; ?>/images/favico.ico"/>

        <?php print $styles; ?>
        <?php print $scripts; ?>
        <script src="<?php echo $directory; ?>/scripts/jbubble.js"></script>
        


</head>

	 <body class="<?php print $body_classes; ?>" >
               <div id="loading">
                            <marquee  >
                                Loading...
                            </marquee>
                        </div> <div style="display:none;" id="profilemsg"><?php print $messages; ?></div>
                          <?php if ($show_messages && $messages): //print $messages;
               echo "<script> jQuery('#twitMsg',top.document).empty().html(jQuery('#profilemsg').html());

        //jQuery('#twitMsg',top.document).delay(400).slideDown(400).delay(3000).slideUp(400);</script>";
                                                                                                endif; ?>
               <div style="display:none;"  class="messages"></div>
    <div class="clr"></div>
    <div class="popup-update-profile">
              <div class="newcretae-profile-wrapper">
                  <?php print $content; ?>
                  <div class="clr"></div>
              </div></div>
          </body>
 
</html>