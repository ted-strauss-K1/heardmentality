<?php $directoryPath = $base_path . $directory; ?>


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
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1" />
  <!--[if lt IE 9]>
    <script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
  <![endif]-->

  <?php print $styles; ?>

	<link rel="shortcut icon" href="<?php print $directoryPath;?>/images/favicon.ico">
	<link rel="apple-touch-icon" href="<?php print $directoryPath;?>/images/apple-touch-icon.png">
	<link rel="apple-touch-icon" sizes="72x72" href="<?php print $directoryPath;?>/images/apple-touch-icon-72x72.png" />
	<link rel="apple-touch-icon" sizes="114x114" href="<?php print $directoryPath;?>/images/apple-touch-icon-114x114.png" />

  <!-- socialize.js script should only be included once -->
  <script type="text/javascript">
    var conf = { enabledProviders: 'facebook,twitter,yahoo,messenger,google,linkedin,myspace,aol,foursquare,orkut,vkontakte,renren' }
  </script>

</head>
<body class="<?php print $classes; ?>">
	<div class="header">
		<?php include 'header.tpl.php';?>
	</div>
	
	<div class="container">
		<?php if ($tabs): ?>
			<div class="tabs"><?php print $tabs; ?></div>
		<?php endif; ?>
		
		<div class="twelve columns">

      <?php if($node->type=='poll'): ?>
				<h2 class="dinbold page-title"><?php print t('Issue'); ?></h2>
      <?php endif; ?>
			
			<div class="white-box <?php if($node->type=='poll'): ?> poll-box <?php endif; ?>">
        <?php print $content; ?>
        <?php print $content_bottom; ?>
			</div>
		</div>

    <div class="four columns">

      <?php if($moderation_history):?>
        <div class="grey-box">
          <div class="icon mod-history text"></div>
          <label for="queue" class="tags-on">Moderation History</label>
          <?php print $moderation_history; ?>
        </div>
      <?php endif; ?>

			<div class="toggler profile-message poll-box">
  	    <div id="effect3">
			    <?php
            if($profile_complete_alert) :
              print $profile_complete_alert;
            endif;
          ?>
	    	</div>
			</div>
			
      <?php if($issue_real_info):?>
			  <div class="grey-box poll-box">
			    <?php print $issue_real_info; ?>
			 	</div>
      <?php endif; ?>

    </div>

	</div>

  <?php include 'footer.tpl.php';?>

  <?php print $scripts; ?>

</body>
</html>