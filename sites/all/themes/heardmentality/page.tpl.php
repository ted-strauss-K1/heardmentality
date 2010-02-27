
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />

<title><?php print $head_title ?></title>
<meta name="description" content="A web applications user interface library built on the Mootools javascript framework" />

<link rel="stylesheet" href="/heardmentality/sites/all/themes/heardmentality/css/content.css" type="text/css" />
<link rel="stylesheet" href="/heardmentality/sites/all/themes/heardmentality/css/ui.css" type="text/css" />
	<?php print $head ?>
<?php print $styles ?>
<?php print $scripts ?>
<!--[if IE]>
	<script type="text/javascript" src="scripts/excanvas-compressed.js"></script>		
<![endif]-->
	
<script type="text/javascript" src="/heardmentality/sites/all/themes/heardmentality/scripts/mootools-1.2-core.js"></script>
<script type="text/javascript" src="/heardmentality/sites/all/themes/heardmentality/scripts/mootools-1.2-more.js"></script>	

<!--
	mocha.js.php is for development. It is not recommended for production.
	For production it is recommended that you used a compressed version of either
	the output from mocha.js.php or mocha.js. You could also list the
	necessary source files individually here in the header though that will
	create a lot more http requests than a single concatenated file.
		
<script type="text/javascript" src="scripts/mocha.js"></script>

-->
<script type="text/javascript" src="/heardmentality/sites/all/themes/heardmentality/scripts/source/Utilities/mocha.js.php"></script>

<script type="text/javascript" src="/heardmentality/sites/all/themes/heardmentality/scripts/mocha-init.js"></script>

</head>
<body>

<div id="desktop">

<div id="desktopHeader">
<div id="desktopTitlebarWrapper">
	<div id="desktopTitlebar">
		<h1 class="applicationTitle">Mocha UI</h1>
		<h2 class="tagline">A Web Applications <span class="taglineEm">User Interface Library</span></h2>
		<div id="topNav">
			<ul class="menu-right">
				<li>Welcome <a href="#" onclick="MochaUI.notification('Do Something');return false;">Demo User</a>.</li>
				<li><a href="#" onclick="MochaUI.notification('Do Something');return false;">Sign Out</a></li>
			</ul>
		</div>
	</div>
</div>
	
<div id="desktopNavbar">
	<?php if (count($links)) : ?>
	<ul>
    <?php foreach ($primary_links as $link): ?>
      <li><a href="<?php print($gSitePath.$link['href']);?>"><?php print($link['title']);?></a></li>
    <?php endforeach; ?>
	</ul>	
    <?php endif;?>
<div class="toolbox divider2">
	<div id="spinnerWrapper"><div id="spinner"></div></div>		
</div>

<div class="toolbox divider2">
	<img src="images/icons/cog.gif" onclick="MochaUI.notification('Do Something');" width="16" height="16" alt="" />
	<img src="images/icons/windows.gif" onclick="MochaUI.notification('Do Something');" width="16" height="16" alt="" />
	<img src="images/icons/sheet.gif" onclick="MochaUI.notification('Do Something');" width="16" height="16" alt="" />
</div>	
	
</div><!-- desktopNavbar end -->
</div><!-- desktopHeader end -->

<div id="dockWrapper">
	<div id="dock">
		<div id="dockPlacement"></div>
		<div id="dockAutoHide"></div>
		<div id="dockSort"><div id="dockClear" class="clear"></div></div>
	</div>
</div>

<div id="pageWrapper"></div>

<div id="desktopFooterWrapper">
	<div id="desktopFooter">
		&copy; 2007-2008 <a target="_blank" href="http://greghoustondesign.com/">Greg Houston</a> - MIT License
	</div>
</div>

</div><!-- desktop end -->
<div style="display:none;" id="txtHidCont" ><?php ob_start(); echo urlencode(htmlentities($content));
$vContent = ob_get_contents();
ob_end_clean();
session_start();
$_SESSION['seePage']=$vContent;
?></div>

</body>
</html>
<script type="text/javascript">
/*setTimeout(function(){
document.getElementById('mainPanel').innerHTML=document.getElementById('txtHidCont').innerHTML
}, 3000);*/
</script>



