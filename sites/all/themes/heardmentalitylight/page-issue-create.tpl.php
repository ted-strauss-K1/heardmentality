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

	<link rel="shortcut icon" href="<?php print $directoryPath;?>/images/favicon.ico">
	<link rel="apple-touch-icon" href="<?php print $directoryPath;?>/images/apple-touch-icon.png">
	<link rel="apple-touch-icon" sizes="72x72" href="<?php print $directoryPath;?>/images/apple-touch-icon-72x72.png" />
	<link rel="apple-touch-icon" sizes="114x114" href="<?php print $directoryPath;?>/images/apple-touch-icon-114x114.png" />

  <!-- socialize.js script should only be included once -->
  <script type="text/javascript">
    var conf={	enabledProviders: 'facebook,twitter,yahoo,messenger,google,linkedin,myspace,aol,foursquare,orkut,vkontakte,renren' }
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
		
		<div class="eleven columns">
			  <h2 class="dinbold page-title"><?php print t('New Issue'); ?></h2>
			  <?php print $content;?>
		</div>

		<div class="five columns">
				<div class="grey-box full clearfix" id="guidelines">
				<!--<div class="icon guides text"></div>-->
				<label for="guidelines" class="tags-on"><?php print t('Guidelines'); ?></label>
					<p class="issue-meta"><?php print t('Please follow Heard Mentality\'s'); ?><a class="bolded"> <?php print t('Guidelines and Principles'); ?></a> <?php print t('when creating a new Issue.
					All issues should be:');?> <ul class="issue-meta"><li><?php print t('concise'); ?></li> <li><?php print t('clean'); ?></li> <li><?php print t('original'); ?></li><li><?php print t('unbiased'); ?></li></ul></p>

				  <hr class="short">
				  <p class="issue-meta"><?php print t('When you submit Issues that are unique, clear, popular and require no editing, you can'); ?> <a class="bolded"><?php print t('win a badge.');?></a></p>

				</div>

		</div>

	</div>

  <?php include 'footer.tpl.php'; ?>
  <?php print $scripts; ?>

</body>
</html>