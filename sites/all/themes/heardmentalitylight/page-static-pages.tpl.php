<?php
global $user, $apikey;
$directoryPath = $base_path . $directory;
// root path
    $path = '<front>';
    $sitelink = url($path, array('absolute' => TRUE)).'/';
?>
<!doctype html>
<!--[if lt IE 7 ]><html class="ie ie6" xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <![endif]-->
<!--[if IE 7 ]><html class="ie ie7" xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <![endif]-->
<!--[if IE 8 ]><html class="ie ie8" xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <![endif]-->
<!--[if (gte IE 9)|!(IE)]><!--><html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <!--<![endif]-->
<head>

	<!-- Basic Page Needs
  ================================================== -->
         <?php print $head; ?>
	<meta charset="utf-8" />
	<title><?php print $head_title; ?></title>
	<meta name="description" content="Heard Mentality">
	<meta name="author" content="">
	<!--[if lt IE 9]>
		<script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
	<![endif]-->

	<!-- Mobile Specific Metas
  ================================================== -->
	<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1" />

	<!-- CSS
  ================================================== -->
        <?php print $styles; ?>
	<!-- JS
	================================================== -->
        <?php print $scripts; ?>
	<!-- Favicons
	================================================== -->
	<link rel="shortcut icon" href="<?php print $directoryPath;?>/images/favicon.ico">
	<link rel="apple-touch-icon" href="<?php print $directoryPath;?>/images/apple-touch-icon.png">
	<link rel="apple-touch-icon" sizes="72x72" href="<?php print $directoryPath;?>/images/apple-touch-icon-72x72.png" />
	<link rel="apple-touch-icon" sizes="114x114" href="<?php print $directoryPath;?>/images/apple-touch-icon-114x114.png" />

  <!-- socialize.js script should only be included once -->
  <script type="text/javascript" src="http://cdn.gigya.com/js/socialize.js?apiKey=<?php print $apikey; ?>"></script>
  <script type="text/javascript">
  var conf=
  {
  	enabledProviders: 'facebook,twitter,yahoo,messenger,google,linkedin,myspace,aol,foursquare,orkut,vkontakte,renren'
  }
  </script>
</head>
<body class="<?php print $classes; ?>">





	<!-- Primary Page Layout
	================================================== -->

	<div class="header">
		<?php include 'header.tpl.php';?>
	<div class="container">
      <div class="toggler profile-message" style="height:auto;width:auto">
      <div class="clear"></div>
        <?php if($messages):?>
	    	<div id="effect" class="" style="width:auto;height:auto">

						<div class="message top-message">
							<p class="double" style="disply:block">
                                                            <?php print $messages; ?>
                                                        </p>
						</div>
                                                <a href="#" id="button" class="hide-message"><span class="ui-icon ui-icon-closethick"><?php print t('Hide'); ?></span></a>


					<br class="clear">
	    	</div>
       <?php endif; ?>
    </div>
        <div class="twelve columns">
        <br>
	    <div class="white-box page">

				<?php print $node->body;
                                      print $content;
                                ?>
                
	    </div>
	  </div>  
            <?php //if($static_pages_menu): ?>
                <div class="four columns">
			
                <div class="grey-box">
				<label for="" class="tags-on"><?php print t('PAGES'); ?></label>
				<ul class="sub-pages">
                                    <li><a href="<?php print $sitelink.'aboutus';?>"><?php print t('About'); ?></a>
                                    <ul>
                                            <li><a href="#what_is_hm"><?php print t('What HM is About'); ?></a></li>
                                            <li><a href="#organization"><?php print t('Organization'); ?></a></li>
                                            <li><a href="<?php print $sitelink.'node/305';?>"><?php print t('Contact Us'); ?></a></li>
                                    </ul>
                                    <li><a><?php print t('Our Thanks'); ?></a>
                                    <ul>
                                            <li><a href="#software_community"><?php print t('Software Community'); ?></a></li>
                                            <li><a href="#how_can_you_help"><?php print t('How you can help'); ?></a></li>
                                            <li><a href="#donate"><?php print t('Donate'); ?></a></li>
                                            <li><a href="#volunteer"><?php print t('Volunteer'); ?></a></li>
                                            <li><a href="#moderators"><?php print t('Moderators'); ?></a></li>
                                    </ul>
                                    <li><a><?php print t('How Heard Mentality Works'); ?></a>
                                    <ul>
                                            <li><a href="#points_rank_coins"><?php print t('Points, Rank and Coins'); ?></a></li>
                                            <li><a href="#pundits"><?php print t('Pundits'); ?></a></li>
                                            <li><a href="#badges"><?php print t('Badges'); ?></a></li>
                                    </ul>
                                    <li><a href="#guide"><?php print t('Guidelines and Principles'); ?></a>   
				</ul>
				<div class="clear"></div>
			</div>
		</div>
                <?php //endif; ?>

  </div>

	<br />
        <br />
	<?php include 'footer.tpl.php';?>



<!-- End Document
================================================== -->
</body>
</html>