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
  <script src="<?php echo $directory; ?>/scripts/jquery.livequery.js"></script>
        <script type="text/javascript">
            jQuery(document).ready(function(){

                jQuery('.creat li').livequery(function () {


                        if (jQuery(this).attr("rel").length > 0) {
                            // jQuery(this).CreateBubblePopup();
                            var id=jQuery(this);
                            jQuery(this).CreateBubblePopup({
                                position : 'right',
                                align	 : 'left',
                                dropShadow: false,
                                openingDelay:300,
                                selectable: true,
                                innerHtmlStyle: {
                                    'text-align':'justified','background-color':'#FFFFFF'
                                },
                                themeName: 	'blue',
                                alwaysVisible: false,
                                innerHtml: jQuery(this).attr("rel"),
                                themePath: '<?php echo $directory; ?>/images/bp_images'

                            });
                            //  jQuery(this).ShowBubblePopup();
                        }

                });

            });

        </script>
    </head>

    <body class="<?php print $body_classes; ?>" style="background:none;" >
      <!--content area-->
      <div class="profile_part">
       <!-- <div class="bor_bot">
		<div class="rht_link">
  <a href="#" title="History">History</a> <span class="separate">|</span>
        <a href="<?php echo $gSitePath;?>?act=edit" title="Edit My Profile">Edit My Profile</a>
        </div>
        <br class="clr" />
      </div>-->




      <div class="commu-profile2">

       <div  class="">
       <?php echo $content;?>
        </div>
      </div>

       <div class="clr"></div>
      <!--content area close-->
	  </div>

    </body>
</html>
