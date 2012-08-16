<?php
global $user, $gSitePath, $apikey;
$directoryPath = $base_path . $directory;
?>
<!doctype html>
<!--[if lt IE 7 ]><html class="ie ie6" xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <![endif]-->
<!--[if IE 7 ]><html class="ie ie7" xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <![endif]-->
<!--[if IE 8 ]><html class="ie ie8" xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <![endif]-->
<!--[if IE 9 ]><html class="ie9" xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <![endif]-->
<!--[if (gte IE 9)|!(IE)]><!--><html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <!--<![endif]-->
  <head>
    <?php print $head; ?>
	<meta charset="utf-8" />
	<title><?php print $head_title; ?></title>
	<meta name="description" content="Heard Mentality">
	<meta name="author" content="">
	<!--[if lt IE 9]>
		<script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
	<![endif]-->


	<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1" />
    <?php print $styles; ?>
	<?php print $scripts; ?>
	<link rel="shortcut icon" href="<?php print $directoryPath;?>/images/favicon.ico">
	<link rel="apple-touch-icon" href="<?php print $directoryPath;?>/images/apple-touch-icon.png">
	<link rel="apple-touch-icon" sizes="72x72" href="<?php print $directoryPath;?>/images/apple-touch-icon-72x72.png" />
	<link rel="apple-touch-icon" sizes="114x114" href="<?php print $directoryPath;?>/images/apple-touch-icon-114x114.png" />

  <!-- socialize.js script should only be included once -->
  <script type="text/javascript">
  var conf=
  {
  	enabledProviders: 'facebook,twitter,yahoo,messenger,google,linkedin,myspace,aol,foursquare,orkut,vkontakte,renren'
  }
  </script>
  </head>
  <body class="<?php print $classes; ?>profile_view_page">

	<div class="header">
		<?php include 'header.tpl.php';?>
	</div>

	<div class="container">
	
        <?php if ($tabs): ?>
			<div class="tabs"><?php print $tabs; ?></div>
		<?php endif; ?>
		<?php if($messages):?>
			<div class="toggler profile-message">
			<div id="effect" class="">
						<div class="message top-message">
							<p class="double" style="disply:block">
                                 <?php print $messages; ?>
                            </p>
						</div>
                        <a href="#" id="button" class="hide-message"><span class="ui-icon ui-icon-closethick"><?php print t('Hide'); ?></span></a>
	    	</div>
			</div>
		<?php endif; ?>

		<div class="eleven columns">
		
			<h2 class="dinbold page-title"><?php print t('Profile'); ?></h2>
			
			<div class="grey-box clearfix full" id="prifile_overview">
                 <?php print $content; ?>
			</div>

            <?php print $user_activity_stream; ?>

		</div>

		<div class="five columns">
			<div class="dark-grey-box top clearfix">
                <?php print $user_profile_information; ?>
			</div>
		</div>	
	</div>

      <!-- container -->
<?php include 'footer.tpl.php'; ?>

</body>
</html>
<script type="text/javascript">
    jQuery(document).ready(function(){
        jQuery('.pager-first').remove();
        jQuery('.pager-last').remove();
    });
</script>