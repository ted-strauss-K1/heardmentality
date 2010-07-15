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
  <script src="http://jquery-translate.googlecode.com/files/jquery.translate-1.3.9.min.js"></script> 
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
<script language="javascript">
  jQuery(function(){ 
   if(jQuery.cookie('destLang')!='')
    var destLang =jQuery.cookie('destLang');
	else
	var destLang ='English'; //when the script is loaded

 jQuery.translate(function(){ //when the Google Language API is loaded
   jQuery.translate.ui('select', 'option') //generate dropdown
      .change(function(){ 
	 //when selecting another language
       jQuery('body').translate( 'english',jQuery(this).val(), { //translate from english to the selected language
          not: '.jq-translate-ui', //exclude these elements
          fromOriginal:true //always translate from english (even after the page has been translated)
        });
		 jQuery.cookie('destLang',jQuery(this).val() ); 
      })
      .val(destLang) //select English as default
      .appendTo('#lang')
	   .find(' option')
      .css('cursor','pointer'); //insert the dropdown to the page


jQuery(".jq-translate-ui:first").hide(); });
});
jQuery(function(){ 

     function translateTo( destLang ){ //this can be declared in the global scope too if you need it somewhere else
	      jQuery('body').translate( 'english', destLang, {   //translate from english to the selected language
          not: '.jq-translate-ui',  //by default the generated element has this className
          fromOriginal:true   //always translate from english (even after the page has been translated)
        });
    }   
	
	jQuery.translate.ui('select', 'option') .appendTo('#lang')    //insert the element to the page
      
      .find('#lang select option')
      .css('cursor','pointer')
	  .attr('value','');
	
	
	 var destLang =jQuery.cookie('destLang'); //get previously translated language
    	jQuery("#lang select option[value=English]").attr("selected",true);
    if( destLang )
        translateTo( destLang );
		
	jQuery("option[value="+destLang+"]").attr("selected",true);//select beta
   }); //end of Google Language API loaded

  
  
 </script>

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
      <!--content area-->
      <div class="contarea">
   <div class="commu">
          <div class="">

 

      <?php if (!empty($left)): ?>
        <div id="sidebar-left" class="column sidebar">
          <?php print $left; ?>
        </div> <!-- /sidebar-left -->
      <?php endif; ?>
    <div class="clr"></div>
          </div>
       </div>
        
           <div class="ques">
          <div class="questop">
            <div class="questopl">  <?php if (!empty($title)): ?><?php print $title; ?><?php endif; ?></div>
            <div class="questopr"><?php echo date("M d,Y") ?></div>
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
  </div>
  <div class="clr"></div>
  <div class="bott"></div>
  <div id="footer"><div class="footerleft">Copyright <a href="http://creativecommons.org/licenses/by-sa/2.5/" title="creativecommons"><img border="0" alt="cc" src="<?php echo $directory;?>/images/cc.jpg"/></a> 2010 Heardmentality.org </div>
  <div class="footerright">  <?php   $mbl=4;$min=0; foreach ($secondary_links as $linksm): $min++;?>
         <a href="<?php print($gSitePath.$linksm['href']);?>" <?php if($linksm['title'] == 'Contact Us'||($linksm['title'] == 'Privacy & Policy')||($linksm['title'] == 'User Agreement')):?> rel="width:850,height:570" class="advanced<?php echo $mbl++; ?>" title="<?php print($linksm['title']);?>"<?php endif;?>><?php print($linksm['title']);?></a><?php if((count($secondary_links))>=$min){ echo " - ";}$min++;?> 
          <?php endforeach; ?>
          <a href="http://www.opensource.org/" title="opensource"><img border="0" alt="opensource" src="<?php echo $directory;?>/images/icon1.png"/></a><a href="http://drupal.org/" title="drupal"><img border="0" alt="drupal" src="<?php echo $directory;?>/images/icon2.png"/></a><a href="http://www.govtrack.us/" title="govtrack"><img border="0" alt="govtrack" src="<?php echo $directory;?>/images/icon3.png"/></a></div>
  </div>
</div>
<!--main div close-->

<script type="text/javascript">
jQuery(function() {
  function preloadImg(image) {
    var img = new Image();
    img.src = image;
  }

  preloadImg('<?php echo $directory;?>/img/ajaxLoader.gif');
  preloadImg('<?php echo $directory;?>/img/prev.gif');
  preloadImg('<?php echo $directory;?>/img/next.gif');
});
</script>

</body>
</html>
