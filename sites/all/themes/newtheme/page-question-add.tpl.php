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

        <div class="popup-add-issue" sytyle="">
            <!--main div-->
            <div id="loading">
                <marquee  >
                    Loading...
                </marquee>
            </div>
            <div class="do-in2">
                <div class="do-intop">ADD AN ISSUE</div>
                <div class="inside2">
                    <div id="err" class=""></div>
                    <div class="clr">&nbsp;</div>
                    <div class="left"><strong>
                            Please follow Heard<br/>Mentality\'s,<span class="ytex">Guidelines & Principles</span> when creating a new issue</strong><br>
                            <strong><br>
                                    All issues should be :   </strong>
                            <div class="creat"><ul>
                                    <li rel="Take pity on the reader – information<br/> should be presented in a non verbose manner. <br/>Pride should be taken from wording things concisely.<br/> This will ensure users can consume and retain<br/> a larger amount of information as well as making technical <br/>features like the translations and search more effective. <br/>Studies also show that more people will stop to read a shorter comment and more likely to pass over longer ones.">Concise</li>
                                    <li rel="No profanity please. Consider all users when choosing your language. <br/>People take the posting more seriously when <br/>it refrains from using harsh and negative words.<br/> Also, abbreviations should be avoided as other users <br/>or the translation feature may not understand.">Clean</li>
                                    <li rel="Pleased do not repeat anything that has been already posted.<br/> Any duplicate content dilutes the overall accuracy of the compiled information.<br/> Any new issue or posting added to Heard Mentality should be<br/> significantly different than existing content. Good practice would be to “agree” <br/>with the posting you may want to reiterate or <br/>voting on the issue that already exists - <br/>this will ultimately draw more attention to it.">Original</li>
                                    <li rel="This is the fundamental rule to make any social community work. <br/>Please treat others like you would like to be treated yourself <br/>and you in return will get the same.">Golden Rules</li>
                                    <li rel="Issues should be classifiable into the provided high level sections.<br/> Please do not post issues that could be considered <br/>unimportant, for example: The hairdo of a certain<br/> celebrity or which restaurant or movie is best.<br/> While these may be important questions, these are not the types of issues to be discussed here.">Important</li>
                                    <li rel="Issues should be posted in an unbiased and non-leading way.<br/> Issues should be posed simply and direct. All realistic possible answers should be introduced.">Unbiased</li>

                                </ul></div>

                             <?php
                             global $user;
                             if (is_array($user->roles) && in_array('administrator', $user->roles)){
                             ?>
                             <div class="clr" style="font-weight:bold;color:black">Dupe questions:</div>

                             <div id="inside_content"></div>
                             <?php }?>
                    </div>
                    <div class="right" id="qform">
                        <div id="twitMsg" class="messages"><?php if ($show_messages && $messages): print $messages;
        endif; ?></div>
                        <div class="clr"></div>
<?php print $content; ?>
                        <div class="clr"></div>

                    </div>
                </div>
            </div></div>
    </body>
</html>
