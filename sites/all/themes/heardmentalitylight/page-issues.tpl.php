<?php
global $user, $gSitePath, $apikey;
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

            <div class="twelve columns">
		  <h2 class="dinbold page-title"><?php print t('Issues / Search state / if any'); ?></h2>
			<div class="grey-box search">
				
                            <?php print $issue_search_area; ?>
					<div class="clear"></div>
				</div>
			<div class="sort-white-box">
			  <div class="sort-by">View &nbsp;<a class="active">Most Votes (all-time)</a> <a>Most Votes (past 7 days)</a> | <a>Number of Views</a></div>
			</div>
			<div class="white-box">
				<div class="clear"></div>
				<h2 class="din half"><a href="" title="permalink" class="issue-title">Do you beleive ad minima veniam, quis nostrum exercitatinem ullam corporis suscipit laboriosamm exercitationem ullam corpo (140 characters)?</a></h2>
				<br>
        <ul class="vote">
					<fieldset>
						<li>
				      <label class="answer"><input type="radio" name="vote" id="regularRadio" class="radio" value="radio 1" />No, ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam</label>
						</li>
						<li>
				      <label class="answer"><input type="radio" name="vote" id="regularRadio" class="radio" value="radio 2" />Yes, on the other hand, we denounce with righteous indignation</label>
						</li>
						<li>
				      <label class="answer"><input type="radio" name="vote" id="regularRadio" class="radio" value="radio 3" />Dunno, we denounce with righteous indignation</label>
						</li>
				  </fieldset>
				</ul>
				<p class="issue-meta"><a>1234 Votes</a> / <a>33 Comments</a> / <a>12 References</a> </p>
				<a href="#" class="button vote floatright">Vote</a>
				<br class="clear">


				<br class="clear">


				<hr>
				<div class="clear"></div>
				<h2 class="din half">Do you believe BPpill well?</h2>
				<br>
        <ul class="vote">
					<fieldset>
						<li>
				      <label class="answer"><input type="radio" name="vote" id="regularRadio" class="radio" value="radio 1" />No, ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam</label>
						</li>
						<li>
				      <label class="answer"><input type="radio" name="vote" id="regularRadio" class="radio" value="radio 2" />Yes, on the other hand, we denounce with righteous indignation</label>
						</li>
						<li>
				      <label class="answer"><input type="radio" name="vote" id="regularRadio" class="radio" value="radio 3" />Dunno, we denounce with righteous indignation</label>
						</li>
				  </fieldset>
				</ul>
				<p class="issue-meta"><a>1234 Votes</a> / <a>33 Comments</a> / <a>12 References</a> </p>
				<a href="#" class="button vote floatright">Vote</a>
				<br class="clear">


				<br class="clear">

				<hr>
				<div class="clear"></div>
				<h2 class="din half">Do you gulf spill well?</h2>
				<br>
        <ul class="vote">
					<fieldset>
						<li>
				      <label class="answer"><input type="radio" name="vote" id="regularRadio" class="radio" value="radio 1" />No, ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam</label>
						</li>
						<li>
				      <label class="answer"><input type="radio" name="vote" id="regularRadio" class="radio" value="radio 2" />Yes, on the other hand, we denounce with righteous indignation</label>
						</li>
						<li>
				      <label class="answer"><input type="radio" name="vote" id="regularRadio" class="radio" value="radio 3" />Dunno, we denounce with righteous indignation</label>
						</li>
				  </fieldset>
				</ul>
				<p class="issue-meta"><a>1234 Votes</a> / <a>33 Comments</a> / <a>12 References</a> </p>
				<a href="#" class="button vote floatright">Vote</a>
				<br class="clear">


				<br class="clear">

				<hr>
				<div class="clear"></div>
				<h2 class="din half">Do you believe BP Handled the Mexico gulf spill well?</h2>
				<br>
        <ul class="vote">
					<fieldset>
						<li>
				      <label class="answer"><input type="radio" name="vote" id="regularRadio" class="radio" value="radio 1" />No, ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam</label>
						</li>
						<li>
				      <label class="answer"><input type="radio" name="vote" id="regularRadio" class="radio" value="radio 2" />Yes, on the other hand, we denounce with righteous indignation</label>
						</li>
						<li>
				      <label class="answer"><input type="radio" name="vote" id="regularRadio" class="radio" value="radio 3" />Dunno, we denounce with righteous indignation</label>
						</li>
				  </fieldset>
				</ul>
				<p class="issue-meta"><a>1234 Votes</a> / <a>33 Comments</a> / <a>12 References</a> </p>
				<a href="#" class="button vote floatright">Vote</a>
				<br class="clear">


			  <br class="clear">

				<hr>
				<div class="pagination">
				  <ul>
				    <a class="prev">Prev</a>
				    <li><a>1</a></li><li><a class="active">2</a></li><li><a>3</a></li><li><a>4</a></li>
				    <a class="next">Next</a>
				  </ul>
			  </div>
			  <br class="clear">
			</div>
		</div>
		<div class="four columns">
			<br>
			<div class="toggler profile-message">
  	    	<div id="effect">
						<div class="message right-message">

	    	      <a href="#" id="button" class="hide-message2 ui-dialog-titlebar-close "><span class="ui-icon ui-icon-closethick">close</span></a>

							<p class="profile-status"><strong>Your profile is only 75% complete.</strong></p>
      		    <div class="profile-complete">
      					<div class="progress"></div>
      				</div>
      				<p class="profile-status"> Filling in your Religion will bring you up to 85% complete. <a class="bolded">Add it here.</a></p>
						</div>
	    	</div>
      </div>
			<div class="grey-box">
			  <div class="icon cat text"></div>
				<ul class="tags">
			    <label for="" class="tags-on">ACTIVE CATEGORIES</label>
			    <div class="clear"></div>
					<li><a>Society</a></li>
					<li><a>Multimedia</a></li>
					<li><a>Coutries</a></li>
			    <li><a>Mobile</a></li>
			    <li><a>Society</a></li>
					<li><a>Multimedia</a></li>
					<li><a>technology</a></li>
			    <li><a>Mobile</a></li>
			    <li><a>Society</a></li>
					<li><a>Multimedia</a></li>
					<li><a>technology</a></li>
				</ul>
				<br class="clear">
				<div class="clear"></div>
				<br>
			</div>
		</div>	

  </div>

	<!-- container -->
	<?php include 'footer.tpl.php';?>



<!-- End Document
================================================== -->
</body>
</html>