<?php
global $user, $apikey;
$directoryPath = $base_path . $directory;
?>
<!doctype html>
<!--[if lt IE 7 ]><html class="ie ie6" xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <![endif]-->
<!--[if IE 7 ]><html class="ie ie7" xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <![endif]-->
<!--[if IE 8 ]><html class="ie ie8" xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>"> <![endif]-->
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
  <script type="text/javascript" src="http://cdn.gigya.com/js/socialize.js?apiKey=<?php print $apikey; ?>"></script>
  <script type="text/javascript">
  var conf=
  {
  	enabledProviders: 'facebook,twitter,yahoo,messenger,google,linkedin,myspace,aol,foursquare,orkut,vkontakte,renren'
  }
  </script>
</head>
<body class="<?php print $classes; ?>">

	<div class="header">
		<?php include 'header.tpl.php';?>
	</div>	
	<div class="container">

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

	</div>

	<div class="container">
    <div class="main-banner-display">
  		<div class="one-third column">
  			<div class="circle-box">
  				<div class="see-banner">
  						<a class="see" href=""><span class="hover"></span></a>
  					</div>
  			</div>
  		</div>
  		<div class="one-third column">
  			<div class="circle-box">
  				<div class="vote-banner">
  						<a class="vote-now" href=""><span class="hover"></span></a>
  					</div>
  			</div>
  		</div>
  		<div class="one-third column ">
  			<div class="circle-box">
  				<div class="share-banner">
  						<a class="share-now" href=""><span class="hover"></span></a>
  					</div>
  			</div>
  		</div>
	</div>

		<div class="container">
			<div class="sixteen columns top-mobile">

					<div class="border-bottom">
						<p class="din banner-text"><?php print t('Heard Mentality: The Global Forum for Public Opinion');?>.</p>
                                                <a href="<?php print $sitelink;?>issues" class="button vote floatright participate"><?php print t('Be Heard!'); ?></a>
						<div class="clear"></div>
					</div>
				</div>
		</div>
	</div>
		<div class="container">
			<div class="nine columns">
				<?php if($happening_now):?>
					<?php print $happening_now;?>
				<?php endif; ?>
			</div>

			<div class="seven columns">

				<div class="white-box hide-on-mobiles">
					<?php if($front_heat_map): print $front_heat_map; endif; ?>
                                    
				</div>
				<div class="grey-box-cat">
					<ul class="tags">
                         <?php if($popular_categories): print $popular_categories; endif; ?>
					</ul>
					<div class="clear"></div>
				</div>
			</div>
		</div>
	<?php include 'footer.tpl.php';?>

</body>
</html>