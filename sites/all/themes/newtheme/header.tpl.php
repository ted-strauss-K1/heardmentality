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
error_reporting(E_ALL);
ini_set('display_errors','On');

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


        <?php print $scripts; ?>
        <script src="<?php echo $directory; ?>/scripts/jquery.translate-1.4.0.min.js"></script>
        <script src="<?php echo $directory; ?>/scripts/jbubble.js"></script>
        <script src="<?php echo $directory; ?>/scripts/jquery.livequery.js"></script>
        <script src="<?php echo $directory; ?>/scripts/jquery.cookie.pack.js"></script>


        <!-- Autosuggest module -->
        <script type="text/javascript" src="<?php echo $directory; ?>/lib/jquery.watermarkinput.js"></script>
        <script type="text/javascript" src="<?php echo $directory; ?>/lib/autosuggest/bsn.AutoSuggest_2.1.3.js"></script>
        <link rel="stylesheet" href="<?php echo $directory; ?>/lib/autosuggest/autosuggest_inquisitor.css" type="text/css" media="screen" charset="utf-8">
            <script type="text/javascript" src="<?php echo $directory; ?>/lib/jquery.tab.js"></script>
            <link rel="stylesheet" href="<?php echo $directory; ?>/lib/jquery.tab.css" type="text/css" media="screen" charset="utf-8">
                <link rel="stylesheet" href="<?php echo $directory; ?>/css/jbubble.css" type="text/css" media="screen" charset="utf-8">
                    <script type="text/javascript">
                        var gSitePath='<?php echo $gSitePath; ?>';
             

                        jQuery('.innerbox a,.facttext a,.titl a,.pro_row a,.lft_view a').not('.jcarousel-control').livequery(function () {

                        
                            if (jQuery(this).attr("rel").length > 0) {
                                // jQuery(this).CreateBubblePopup();
                                var id=jQuery(this);
                                jQuery(this).CreateBubblePopup({
                                    position : 'top',
                                    align	 : 'center',
                                    dropShadow: false,
                                    openingDelay:300,
                                    selectable: true,
                                    innerHtmlStyle: {
                                        'text-align':'center','background-color':'#FFFFFF'
                                    },
                                    themeName: 	'blue',
                                    alwaysVisible: false,
                                    innerHtml: jQuery(this).attr("rel"),
                                    themePath: '<?php echo $directory; ?>/images/bp_images'

                                });
                                //  jQuery(this).ShowBubblePopup();
                            }

                        });
                        jQuery('.p-foll li a,#mfollowing a,#inbox a,.contarea a').not('.jcarousel-control').each(function () {

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
                                //  jQuery(this).ShowBubblePopup();
                            }


                        });
					

     </script>

                    <script type="text/javascript">
                        function callfunction()
                        {
			
                            if(jQuery('#stype1').is(':checked'))
                            {
			
                                document.search.action="<?php echo $gSitePath ?>searchquestion";
                                document.search.submit();
                            }
                            else
                            {
                                document.search.action="<?php echo $gSitePath ?>searchuser";
                                document.search.submit();
                            }
			
                        }
                    </script>

                    <?php
                    //echo  $apikey;
                    //echo $_SERVER['HTTP_HOST'];
                    if (isset($_REQUEST["act"]) && !empty($user->uid)) {
                        if ($_REQUEST["act"] == "edit2") {
                    ?>
                            <script type="text/javascript">
                                var r=confirm("Do you want to earn the Biographer badge by competing your profile information?");
                                if (r==true)
                                {
                                    jQuery(document).ready(function(){
                                        //  jQuery.nyroModalSettings({ title:'Edit Profile'});

                                        //jQuery.nyroModalManual({
                                        //url:'<?php echo $gSitePath ?>edit',width:850,height:700,title:'Edit Profile'
                                        //});
                                        var options = 'sameBox:true width:50% height:60% caption:' +
                                            '`Edit Profile`';
                                        parent.fb.start('<?php echo $gSitePath ?>edit', options);


                                    });

                                }

                            </script>

                    <?php
                        } elseif ($_REQUEST["act"] == 'edit') {
                    ?>
                            <script>

                                jQuery(document).ready(function(){
                                    // jQuery.nyroModalSettings({ title:'Edit Profile'});

                                    //jQuery.nyroModalManual({
                                    //  url:'<?php echo $gSitePath ?>edit',width:850,height:700,title:'Edit Profile'
                                    //});
                                    var options = 'sameBox:true width:50% height:60% caption:' +
                                        '`Edit Profile`';
                                    parent.fb.start('<?php echo $gSitePath ?>edit', options);

                                });
                            </script>

                    <?php
                        }
                    }
                    ?>

                    <!--  Geo Location sharing html 5-->
                    <script type="text/javascript">
                        // if (navigator.geolocation) {
                        //navigator.geolocation.getCurrentPosition(function(position) {
                        // document.location.href ="http://maps.google.com/maps?q="+ position.coords.latitude + ",+"+ position.coords.longitude+ "&iwloc=A&hl=en";
                        // });
                        // }
                    </script>
                    </head>
					
                    <body class="<?php print $body_classes; ?>" >
                        <!--main div-->
                        <div id="loading">
                            <marquee  >
                                Loading...
                            </marquee>
                        </div>
                        <?php
                        // display moderator messages
                        $variable = get_defined_vars();
                        $notifies = $variable['notify'];
                        if(count($notifies)>0){
                            $i=1;
                         ?>
                        <div id="notify-container">
                            <?php
                            foreach($notifies as $notify){
                            $moderator = db_result(db_query("SELECT name FROM {users} WHERE uid = '$notify->moderator_id'"));
                            $message = $notify->message;
                            ?>
                                <div id="not-id-<?php echo $i; ?>">
                                <div id="not-div">
                               
                                <span class="notify-close"><a href="javascript:void(0);" onclick="close_notify_message(<?php echo $i; ?>, <?php echo $notify->id?>, <?php echo $user->uid;?>)" title="dismiss this notification">×</a></span>
                                <span class="notify-text"><div align="center">Moderator sent a message <span>'<?php echo t($message); ?>'</span></div></span>
                                </div>
                                </div>
                            <?php
                            $i++;
                            }
                            ?>
                        </div>
                        <?php }?>

                        <div class="main">
                            <div class="top"></div>
                            <div class="clr"></div>
                            <div class="mid">
                                <div class="inn">
                                    <!--Header-->

                                    <div id="header">
                                        <div class="top-left-outer">
                                            <div class="text-logo"><div  class="textspace"><?php print t("Be Heard Don't Be");?><br />
                                                    <?php print t('Part Of The Herd');?></div>
                                            </div>
                                            <div class="date-time">

                                                <?php
                                                echo $changetime = t(zonechange(18, 0));
                                                ?>
                                            </div>
                                        </div>

                                        <div align="center" ><a href="<?php print $front_page; ?>" class="logo" title="<?php print t('Home'); ?>"><?php print t('HEARD');?>&nbsp;&nbsp;&nbsp;&nbsp;<?php print t('MENTALITY'); ?></a></div>
                                        <!-- /logo-title -->

                                        <div class="loginvi-outer">

                                            <?php include "login.tpl.php"; ?>
                                            </div>
                                            <div class="clr"></div>

                                        <?php if (!empty($search_box)): ?>
                                                    <div id="search-box"><?php print $search_box; ?></div>
                                        <?php endif; ?>

                                        <?php if (!empty($header)): ?>
                                                        <div id="header-region">
                                            <?php print $header; ?>
                                                    </div>
                                        <?php endif; ?>
                                        <?php
                                                        if (isset($_REQUEST['stype'])) {


                                                            $spe = $_REQUEST['stype'];
                                                        }

                                                        if (isset($_REQUEST['txt_search'])) {

                                                            $skey = $_REQUEST['txt_search'];
                                                        } else {
                                                            $skey = t('Search');
                                                        }
                                        ?>
                                                        <div class="clr"></div>

                                                        <div id="menu">
                                                            <div class="search">  <form class="home_searchEngine" name="search" method="post" action="">
                                                                    <div class="searchtext">
                                                                        <input name="txt_search"  id="txt_search" value="<?php echo $skey; ?>" type="text"  onblur="if(search.txt_search.value =='') search.txt_search.value = ''" onfocus="if(search.txt_search.value =='Search') search.txt_search.value = ''" />
                                                                    </div>
                                                                    <div class="searchr">

                                                                        <div class="stext">  <input type="radio" name="stype[]" id="stype1" value="1" <?php
                                                        if (isset($_REQUEST['stype'])) {
                                                            if ($_REQUEST['stype'][0] == 1) {
                                        ?> checked="checked" <?php
                                                                                }
                                                                            } else {
                                        ?> checked="checked" <?php } ?>   /></div>
                                                        <label for="radio" class="slab"><?php print t('Issues');?></label>
                                                    </div>
                                                    <div class="searchr">

                                                        <div class="stext">    <input type="radio" name="stype[]" id="stype2" value="2" <?php
                                                                                    if (isset($_REQUEST['stype'])) {
                                                                                        if ($_REQUEST['stype'][0] == 2) {
                                        ?> checked="checked" <?php }
                                                                                    } ?>  /></div>
                                                        <label for="radio2" class="slab"><?php print t('Users');?></label>
                                                    </div>
                                                    <div>&nbsp;
                                                        <input name="Search" type="submit" value="<?php print t('Search');?>"  onclick="return callfunction();"/>
                                                    </div>
                                                </form>     </div>

                                            <div class="men">
                                                <?php if (count($primary_links)) : ?>

                                                <?php $mb = 1;
                                                  foreach ($primary_links as $link): ?>
                                 <li><a href="<?php print($gSitePath . $link['href']); ?>" <?php if ($link['title'] == 'Readme' || ($link['title'] == 'Add a Issue') || ($link['title'] == 'Privacy')): ?> class="floatbox" <?php if ($link['title']== 'Readme') { ?> data-fb-options="width:769 height:80%" <?php } else { ?> data-fb-options="width:700 height:60%" <?php } ?>  rel="nofollow" title="<?php print($link['title']); ?>"<?php endif; ?>><?php print t($link['title']); ?></a></li>
                                                <?php endforeach; ?>

                                                <?php endif; ?>

                                                                                            </div>

                                                                                            <div class="edition">
                                                                                                <div ><?php echo t('Edition:');?><span id="lang"></span>
                                                                                                    <!-- Google Translate -->

                                                                                                </div>
                                                                                            </div> <!-- /navigation -->
                                                                                        </div>
                                                                                    </div>
                                                                                    <!-- /header -->
                                                                                    <div class="clr"></div>


                                                                                    <div id="twitMsg" class="messages"><?php if ($show_messages && $messages): print $messages;
                                                                                                endif; ?></div>
                                    <div class="clr"></div>
                                    <!--Header close-->

                              