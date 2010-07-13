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
  global $user,$gSitePath,$apikey;
  ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <link rel="stylesheet" href="<?php $directory;?>/css/nyroModal.css" type="text/css" media="screen" />
  <?php print $scripts; ?>
<script type="text/javascript">
jQuery(document).ready(function(){
			
						jQuery("#loading").ajaxStart(function(){
				  jQuery(this).fadeIn();
				 });
				 
				jQuery("#loading").ajaxStop(function(){
				   jQuery(this).fadeOut();
				 });	
			});

</script>
</head>
<body class="<?php print $body_classes; ?>" onload="MM_preloadImages('images/mh1.gif','images/mh2.gif','images/mh3.gif','images/mh4.gif')">
<!--main div-->
<div id="loading">
  <marquee  >
  Loading...
  </marquee>
</div>
<div class="main">
  <div class="top"></div>
  <div class="clr"></div>
  <div class="mid">
    <div class="inn">
      <!--Header-->
  
    <div id="header">
      <div id="logo-title" class="logo">

        <a href="<?php print $front_page; ?>" rel="home" id="logo" title="<?php print t('Home'); ?>"></a>
      <?php //$logo;?>

  
      </div> <!-- /logo-title -->
       
  
	
		<?php include "login.tpl.php"; ?>

</div>      <?php if (!empty($search_box)): ?>
        <div id="search-box"><?php print $search_box; ?></div>
      <?php endif; ?>

      <?php if (!empty($header)): ?>
        <div id="header-region">
          <?php print $header; ?>
        </div>
      <?php endif; ?>

 <div class="clr"></div>
     <div id="menu">
          <div class="search"> <form method="get" name="form1" action="">
            <div class="searchtext">
          <input name="Search" value="Search" type="text"  onblur="if(form1.Search.value =='') form1.Search.value = 'Search'" onfocus="if(form1.Search.value =='Search') form1.Search.value = ''" />
            </div>    </form>
            <div class="searchr">
             
             <div class="stext"> <input name="Search" type="radio" id="radio"  value="" /></div>
              <label for="radio" class="slab">question</label>
            </div>
            <div class="searchr">
              
            <div class="stext">    <input name="Search" id="radio2" type="radio" value="" /></div>
             <label for="radio2" class="slab">user</label>
            </div>
            <div>&nbsp;
              <input type="button" class="searchbut" title="Search" value="Search" />
            </div>
                       </div>
       <!--          <div class="men"> 
         <?php if (count($primary_links)) : ?>
	
    <?php $mb=1;foreach ($primary_links as $link): ?>
      <a href="<?php print($gSitePath.$link['href']);?>" <?php if($link['title'] == 'About US'||($link['title'] == 'Add  Question')||($link['title'] == 'Privacy')):?> rel="width:850,height:570" class="advanced<?php echo $mb++; ?>" title="<?php print($link['title']);?>"<?php endif;?>><?php print($link['title']);?></a>
    <?php endforeach; ?>
	
    <?php endif;?>
         
         </div>-->
         <div class="men"> <a href="<?php echo $gSitePath; ?>category" title="CATEGORIES" onmouseout="MM_swapImgRestore()" onmouseover="MM_swapImage('Image1','','<?php echo $directory; ?>/images/mh1.gif',1)"><img src="<?php echo $directory; ?>/images/m1.gif" alt="CATEGORIES" name="Image1" width="124" height="30" border="0" id="Image1" /></a><a href="#" title="ADD A QUESTION" onmouseout="MM_swapImgRestore()" onmouseover="MM_swapImage('Image2','','<?php echo $directory; ?>/images/mh2.gif',1)"><img src="<?php echo $directory; ?>/images/m2.gif" alt="ADD A QUESTION" name="Image2" width="154" height="30" border="0" id="Image2" /></a><a href="#" title="GURU" onmouseout="MM_swapImgRestore()" onmouseover="MM_swapImage('Image3','','<?php echo $directory; ?>/images/mh3.gif',1)"><img src="<?php echo $directory; ?>/images/m3.gif" alt="GURU" name="Image3" width="68" height="30" border="0" id="Image3" /></a><a href="#" title="ABOUT US" onmouseout="MM_swapImgRestore()" onmouseover="MM_swapImage('Image4','','<?php echo $directory; ?>/images/mh4.gif',1)"><img src="<?php echo $directory; ?>/images/m4.gif" alt="ABOUT US" name="Image4" width="106" height="30" border="0" id="Image4" /></a></div>
          <div class="edition">
            <div>Edition:
              <select>
                <option>select language</option>
              </select>
            </div>
          </div>
      </div> <!-- /navigation -->
         </div> <!-- /header -->   
               <div class="clr"></div>
               <!--Header close-->
      <!--content area-->
      <div class="contarea">
   <div class="commu">
          <div class="commutop">

 

      <?php if (!empty($left)): ?>
        <div id="sidebar-left" class="column sidebar">
          <?php //print $left; ?>
        </div> <!-- /sidebar-left -->
      <?php endif; ?>
    <div class="clr"></div>
          </div>
        </div>
           <div class="ques">
          <div class="questop">
            <div class="questopl">  <?php if (!empty($title)): ?><?php print $title; ?><?php endif; ?></div>
            <div class="questopr">July 4, 2010</div>
          </div>
          <div class="quesbg">

           <?php print $content; ?>
  </div>
  
     <div class="quesbott"></div>
        </div>
  <div class="fact">
      <?php if (!empty($right)): ?>
        <div id="sidebar-right" class="column sidebar">
          <?php print $right; ?>
        </div> <!-- /sidebar-right -->
      <?php endif; ?>

    </div> <!-- /container -->
  </div>
      <div class="clr"></div>
      <!--content area close-->
    </div>
  
  <div class="clr"></div>
  <div class="bott"></div>
</div>
<!--main div close-->
<script type="text/javascript">
$(function() {
  function preloadImg(image) {
    var img = new Image();
    img.src = image;
  }

  preloadImg('<?php $directory;?>/img/ajaxLoader.gif');
  preloadImg('<?php $directory;?>/img/prev.gif');
  preloadImg('<?php $directory;?>/img/next.gif');
});
</script>

</body>
</html>
