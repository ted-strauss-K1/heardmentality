<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"><?php

global $user, $gSitePath, $apikey;
$directory = $base_path . $directory;
?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

    <head>
        <?php print $head; ?>
        <title><?php print $title; ?></title>
        <link rel="shortcut icon" type="image/x-icon" href="<?php echo $directory; ?>/images/favico.ico"/>

        <?php print $styles; ?>


        <?php //print $scripts; ?>

<script src="<?php echo $directory; ?>/scripts/jquery1.4.2.js"></script>
<script src="<?php echo $directory; ?>/scripts/jquery.scroll.js"></script>
<script src="<?php echo $directory; ?>/scripts/localscroll.js"></script>
<script src="<?php echo $directory; ?>/scripts/init.js"></script>
<script src="<?php echo $directory; ?>/scripts/jbubble.js"></script>

<link rel="stylesheet" href="<?php echo $directory; ?>/css/jbubble.css" type="text/css" media="screen" charset="utf-8">
<link href="<?php echo $directory; ?>/css/slider_css.css" rel="stylesheet" type="text/css">	
<script type="text/javascript">
                        var gSitePath='<?php echo $gSitePath; ?>';
						  jQuery(document).ready(function(){
                        $('#Concise').each(function () { 
							
                            if ($(this).attr("rel").length > 0) {
                                //  $(this).CreateBubblePopup();
                                var id=$(this);
                                $(this).CreateBubblePopup({
                                    position : 'top',
                                    align	 : 'center',
                                    dropShadow: false,
                                    openingDelay:100,
                                    selectable: true,
                                    innerHtmlStyle: {
                                        'text-align':'center','background-color':'#FFFFFF'
                                    },
                                    alwaysVisible: false,
                                    themeName: 	'blue',

                                    innerHtml: $(this).attr("rel"),
                                    themePath: '<?php echo $directory; ?>/images/bp_images'

                                });
                                  $(this).ShowBubblePopup();
                            }


                        });
						});

     </script>

       
   <body style="background: none repeat scroll 0% 0% transparent;">
     
   <?php print $content; ?>
			
</body> 
