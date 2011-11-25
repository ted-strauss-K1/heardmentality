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
  <script type="text/javascript" src="http://cdn.gigya.com/js/socialize.js?apiKey=2_DKqhjEPBIUy_fCc5_X1xS9N-Bc8g9B9yIm_oXdkTc_9yGM-UQQE2KnupQWKO_2iR"></script>
  <script type="text/javascript">
  var conf=
  {
  	enabledProviders: 'facebook,twitter,yahoo,messenger,google,linkedin,myspace,aol,foursquare,orkut,vkontakte,renren'
  }
  </script>
</head>
<body>





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
                        <?php
                        if($node->type=='poll'):
                        ?>
			<h2 class="dinbold page-title"><?php print t('Issue'); ?></h2>
                        <?php endif; ?>
			<div class="white-box">
                                <div class="clear"></div>
                                <!-- issue view, suggest answer -->
        			<?php print $content; ?>
				 <!-- issue view, suggest answer -->

				<a href="#" class="icon share floatleft text"></a>
				<br class="clear" />

				<br class="clear"><br class="clear">
                                <?php print $content_bottom; ?>
				
			</div>
		</div>
            <div class="four columns">
			<br>
			<div class="toggler profile-message">
  	    	<div id="effect">
			<?php 
                        if($profile_complete_alert):
                        print $profile_complete_alert;
                        endif;
                        ?>
	    	</div>
      </div>
                        <?php if($issue_real_info):?>
			<div class="grey-box">
                            <?php print $issue_real_info; ?>
			 
			</div>
                        <?php endif; ?>
		</div>

  </div>

	<br />
        <br />
	<?php include 'footer.tpl.php';?>



<!-- End Document
================================================== -->
</body>
</html>