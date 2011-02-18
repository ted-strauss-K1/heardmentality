<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd"><?php

global $user, $gSitePath, $apikey;
$directory = $base_path . $directory;
?>
<?php print $styles; ?>
<?php print $scripts; ?>
<script src="<?php echo $directory; ?>/scripts/jbubble.js"></script>
<script src="<?php echo $directory; ?>/scripts/jquery.js"></script>
<script src="<?php echo $directory; ?>/scripts/localscroll.js"></script>
<script src="<?php echo $directory; ?>/scripts/init.js"></script>

<link rel="stylesheet" href="<?php echo $directory; ?>/css/jbubble.css" type="text/css" media="screen" charset="utf-8">
<link href="<?php echo $directory; ?>/css/slider_css.css" rel="stylesheet" type="text/css">	
<script type="text/javascript">
                        var gSitePath='<?php echo $gSitePath; ?>';
						$(document).ready(function(){

                        jQuery('.table-bor-form-item-1 ul li a,#Concise').each(function () { 

                            if (jQuery(this).attr("rel").length > 0) {
                                //  jQuery(this).CreateBubblePopup();
                                var id=jQuery(this);
                                jQuery(this).CreateBubblePopup({
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

                                    innerHtml: jQuery(this).attr("rel"),
                                    themePath: '<?php echo $directory; ?>/images/bp_images'

                                });
                                  jQuery(this).ShowBubblePopup();
                            }


                        });
						});

     </script>

       
   <body style="background: none repeat scroll 0% 0% transparent;">
   <?php print $content; ?>
			
</body> 
