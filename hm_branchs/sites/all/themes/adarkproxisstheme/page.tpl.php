<?php
// $Id: page.tpl.php,v 1.1 2009/07/22 18:24:01 proxiss Exp $

/**
 * @file
 * Main page template.
 *
 * Main template for all pages in adarkproxisstheme.
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml"
	xml:lang="<?php print $language->language ?>"
	lang="<?php print $language->language ?>"
	dir="<?php print $language->dir ?>">
<head>
<title><?php print $head_title ?></title>
<?php print $head ?>
<?php print $styles ?>
<?php print $scripts ?>
<!--[if lt IE 7]>
  <link type="text/css" rel="stylesheet" media="all" href="/<?php print $directory.'/'; ?>ie6fix.css" />
<![endif]-->
</head>

<body>

<div id="header">
<div class="sizeframe">
<div class="d-content"><?php 
// render logo, title and slogan
$ptitle = trim(@check_plain($site_name) .' '. @check_plain($site_slogan));
print '<a class="homelink" href="'. check_url($front_page) .'" title="'. $ptitle .'">';
if ($logo) {
  print '<img src="'. check_url($logo) .'" alt="'. $ptitle .'" id="logo" class="logo" />';
} 
else {
  print '<span class="homename">'. check_plain($site_name) .'</span>';
  if ($site_slogan) {
    print '<br /><span class="homeslogan">'. check_plain($site_slogan) .'</span>';
  }
}
print '</a>';
?></div>
</div>
</div>

<div id="middle">
<div class="sizeframe">
<div id="frame">

<div id="content" class="column">
<div class="d-content"><?php if ($show_messages && $messages): print '<div class="msgs cl">'. $messages .'</div>'; endif; ?>
<?php if ($content_top): print '<div class="cnt_top cl">'. $content_top .'</div>'; endif; ?>
<?php if ($title): print "<h1 class='mainTitle'>$title</h1>"; endif; ?>
<?php if ($tabs): print '<ul class="primtabs mtab">'. $tabs .'</ul>'; endif; ?>
<div id="primcontent" class="cl"><?php if ($tabs2): print '<ul class="sectabs mtab cl">'. $tabs2 .'</ul>'; endif; ?>
<div
	class="mainContent clear-block cl <?php if ($node->type) print 'mc-'. $node->type; ?>">
<?php print $help; ?> <?php print $content ?></div>
<?php if ($content_bottom): print '<div class="cnt_bottom">'. $content_bottom .'</div>'; endif; ?>
</div>
</div>
</div>

<div id="mainmenu" class="column sb">
<div class="d-content"><?php if (isset($primary_links)) : ?> <?php print '<div class="block primary-links"><div class="content">'. theme('links', $primary_links, array('class' => 'menu primary-links')) .'</div></div>'; ?>
<?php endif; ?> <?php print $left ?></div>
</div>

<div id="rightbar" class="column sb">
<div class="d-content"><?php if ($mission): ?>
<div class="block mission">
<div class="content"><?php print $mission ?></div>
</div>
<?php endif; ?> <?php print $right ?></div>
</div>

</div>
</div>
</div>
<div id="copyright">
<div class="sizeframe">
<div class="d-content">
<div class="block copydisclaimer"><?php print $footer_message; ?>
<div class="themeauthor">Dark Drupal Theme by <a
	href="http://www.proxiss.de">proxiss GmbH</a></div>
<?php if ($footer_left) print $footer_left; ?></div>
<div class="d-foot"><?php print $footer_right; ?></div>
<div class="footer cl"><?php print $footer; ?></div>
</div>
</div>
</div>

<div id="help">
<div class="sizeframe"><?php if ($breadcrumb): ?><span
	class="breadcrumbs"><?php print $breadcrumb; ?></span><?php endif; ?>
<div id="perms"><?php print $header_right; ?></div>
</div>
</div>

<?php print $closure ?>
<?php if ($before_body) print '<div class="beforeBody">'. $before_body .'</div>'; ?>
</body>

</html>
