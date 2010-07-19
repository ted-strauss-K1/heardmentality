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
  $directory=$base_path.$directory;
  ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <link rel="shortcut icon" type="image/x-icon" href="<?php echo $directory;?>/images/favico.ico"/>

    <?php print $styles; ?>
  
  <?php print $scripts; ?>
  <script src="<?php echo $directory; ?>/scripts/jquery.translate-1.4.0.min.js"></script> 
<script src="<?php echo $directory; ?>/scripts/jquery.cookie.pack.js"></script> 
<script type="text/javascript">
var gSitePath='<?php echo $gSitePath;?>';
jQuery(document).ready(function(){

 var height = jQuery(window).height();
        var width = jQuery(window).width();

        var autosizable = true;
        var windowResize = true;
        var resizeable = true;

	jQuery.nyroModalSettings({  galleryCounts: '', forceType: 'iframe',minWidth: 600, // Minimum width
  minHeight: 400, // Minimum height
  resizable: true, // Indicate if the content is resizable. Will be set to false for swf
  autoSizable: true, // Indicate if the content is auto sizable. If not, the min size will be used
  padding:30, // padding for the max modal size
  gallery: null, // Gallery name if provided
  galleryLinks: '', // Use .nyroModalPrev and .nyroModalNext to set the navigation link
  windowResize: windowResize,
            width: width/2,
            height: height,

 });
						jQuery("#loading").ajaxStart(function(){
				  jQuery(this).fadeIn();
				 });
				 
				jQuery("#loading").ajaxStop(function(){
				   jQuery(this).fadeOut();
				 });	
			});

</script>
     
 <script type="text/javascript">
			function callfunction()
			{
			
			if(jQuery('#stype1').is(':checked'))
			{
			
			document.search.action="<?php echo $gSitePath?>searchquestion";
			document.search.submit();
			}
			else
			{
				document.search.action="<?php echo $gSitePath?>searchuser";
			document.search.submit();
			}
			
			}
			</script>
            
					  <?php 
            //echo  $apikey;
             //echo $_SERVER['HTTP_HOST'];
            if(isset($_REQUEST["act"]))
            {
			if($_REQUEST["act"]=="edit2")
			{
            ?>
            <script type="text/javascript">
           var r=confirm("Do you want to earn the Biographer badge by competing your profile information?");
            if (r==true)
              {
		   jQuery(document).ready(function(){
		    jQuery.nyroModalSettings({ title:'Edit Profile'});

	jQuery.nyroModalManual({
    url:'<?php echo $gSitePath?>edit',width:850,height:700,title:'Edit Profile'
  }); });

              }
           
            </script>
                 
            <?php
            }  
            elseif($_REQUEST["act"]=='edit')
            {
            ?>
            <script>
           
		   jQuery(document).ready(function(){
		    jQuery.nyroModalSettings({ title:'Edit Profile'});

	jQuery.nyroModalManual({
    url:'<?php echo $gSitePath?>edit',width:850,height:700,title:'Edit Profile'
  }); });
</script>

            <?php
            }
            }
            ?>
            
                        
                        
            
            
</head>
<body class="<?php print $body_classes; ?>" >
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
 <?php
	if(isset($_REQUEST['stype']))
{


			$spe=$_REQUEST['stype'];
}
			
			if(isset($_REQUEST['txt_search'])){
				
				$skey=$_REQUEST['txt_search'];
			}else{
				$skey='Search';
			}
			?>
 <div class="clr"></div>
     <div id="menu">
          <div class="search">  <form name="search" method="post" action="">
            <div class="searchtext">
          <input name="txt_search"  id="txt_search" value="<?php echo $skey; ?>" type="text"  onblur="if(search.txt_search.value =='') search.txt_search.value = 'Search'" onfocus="if(search.txt_search.value =='Search') search.txt_search.value = ''" />
            </div>    </form>
            <div class="searchr">
             
             <div class="stext">  <input type="radio" name="stype[]" id="stype1" value="1" <?php if(isset($_REQUEST['stype'])) { if($_REQUEST['stype']==1) {?> checked="checked" <?php } }else{?> checked="checked" <?php }?>  /></div>
              <label for="radio" class="slab">Questions</label>
            </div>
            <div class="searchr">
              
            <div class="stext">    <input type="radio" name="stype[]" id="stype2" value="2" <?php if(isset($_REQUEST['stype'])) { if($_REQUEST['stype']==2) {?> checked="checked" <?php } }?> /></div>
             <label for="radio2" class="slab">Users</label>
            </div>
            <div>&nbsp;
                       <input name="Search" type="submit" value="Search"  onclick="return callfunction();"/>
            </div>
                  </form>     </div>
                     <div class="men"> 
         <?php if (count($primary_links)) : ?>
	
    <?php $mb=1;foreach ($primary_links as $link): ?>
      <li><a href="<?php print($gSitePath.$link['href']);?>" <?php if($link['title'] == 'About US'||($link['title'] == 'Add  Question')||($link['title'] == 'Privacy')):?> class="nyroModal" rel="nofollow" title="<?php print($link['title']);?>"<?php endif;?>><?php print($link['title']);?></a></li>
    <?php endforeach; ?>
	
    <?php endif;?>
         
         </div>
    
          <div class="edition">
            <div >Edition:<span id="lang"></span>
              <!-- Google Translate -->
			
          </div>
      </div> <!-- /navigation -->
         </div>
          <!-- /header -->   
               <div class="clr"></div>
               <?php if ($show_messages && $messages): print '<div class="messages">'. $messages .'</div>'; endif; ?>
                <div class="clr"></div>
               <!--Header close-->