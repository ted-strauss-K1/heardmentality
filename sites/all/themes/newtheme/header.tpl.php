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
  <script src="<?php echo $directory; ?>/scripts/jbubble.js"></script> 
<script src="<?php echo $directory; ?>/scripts/jquery.cookie.pack.js"></script>
<!-- Float box-->
<link type="text/css" rel="stylesheet" href="<?php echo $directory; ?>/floatbox/floatbox.css" />
<script type="text/javascript" src="<?php echo $directory; ?>/floatbox/floatbox.js"></script>
<script type="text/javascript" src="<?php echo $directory; ?>/floatbox/options.js"></script>

<!-- Autosuggest module -->
<script type="text/javascript" src="<?php echo $directory; ?>/lib/jquery.watermarkinput.js"></script>
<script type="text/javascript" src="<?php echo $directory; ?>/lib/autosuggest/bsn.AutoSuggest_2.1.3.js"></script>
<link rel="stylesheet" href="<?php echo $directory; ?>/lib/autosuggest/autosuggest_inquisitor.css" type="text/css" media="screen" charset="utf-8">
<script type="text/javascript" src="<?php echo $directory; ?>/lib/jquery.tab.js"></script>
<link rel="stylesheet" href="<?php echo $directory; ?>/lib/jquery.tab.css" type="text/css" media="screen" charset="utf-8">

<script type="text/javascript">

var gSitePath='<?php echo $gSitePath;?>';



jQuery(document).ready(function(){
	jQuery('.innerbox a,.facttext a').each(function()
   {
    if( jQuery(this).attr("title").length>0){

        jQuery(this).SetBubblePopup({
									innerHtml: jQuery(this).attr("title"),
										 color:'grey',
										 imageFolder: '<?php echo $directory; ?>/images/bp_images',

								});
    }
	
								
		});						
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
            height: height

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
            if(isset($_REQUEST["act"])&&!empty($user->uid))
            {
			if($_REQUEST["act"]=="edit2")
			{
            ?>
            <script type="text/javascript">
           var r=confirm("Do you want to earn the Biographer badge by competing your profile information?");
            if (r==true)
              {
		   jQuery(document).ready(function(){
		  //  jQuery.nyroModalSettings({ title:'Edit Profile'});

	//jQuery.nyroModalManual({
    //url:'<?php echo $gSitePath?>edit',width:850,height:700,title:'Edit Profile'
  //});
     var options = 'sameBox:true width:70% height:90% caption:' +
  '`Edit Profile`';
  parent.fb.start('<?php echo $gSitePath?>edit', options);


  });

              }
           
            </script>
                 
            <?php
            }  
            elseif($_REQUEST["act"]=='edit')
            {
            ?>
            <script>
           
		   jQuery(document).ready(function(){
		   // jQuery.nyroModalSettings({ title:'Edit Profile'});

	//jQuery.nyroModalManual({
  //  url:'<?php echo $gSitePath?>edit',width:850,height:700,title:'Edit Profile'
  //});
   var options = 'sameBox:true width:70% height:90% caption:' +
  '`Edit Profile`';
  parent.fb.start('<?php echo $gSitePath?>edit', options);

  });
</script>

            <?php
            }
            }
            ?>
            
                        
                <!--  Geo Location sharing html 5-->
       <script type="text/javascript">
   // if (navigator.geolocation) {
      //navigator.geolocation.getCurrentPosition(function(position) {
       // document.location.href ="http://maps.google.com/maps?q="+ position.coords.latitude + ",+"+ position.coords.longitude+ "&iwloc=A&hl=en";
     // });
   // }
  </script>
      
            
</head>
<body class="<?php print $body_classes; ?>" >
<!--main div-->
<div id="loading">
  <marquee  >
  Loading...
  </marquee>
</div>

<!-- Tour created with Amberjack wizard: http://amberjack.org -->
<div class="ajTourDef" id="MyTour" style="display:none">
  <div title="http://localhost/heardmentality/">
    Placeholder for page 1 - replace this text
  </div>
  <div title="http://localhost/heardmentality/profile">
    Placeholder for page 2 - replace this text
  </div>
  <div title="http://localhost/heardmentality/donation">
    Placeholder for page 3 - replace this text
  </div>
</div>

<script type="text/javascript" src="http://amberjack.org/src/stable/amberjack.pack.js">
</script>

<script type="text/javascript" defer="true">
  Amberjack.onCloseClickStay = true;
  Amberjack.open();
</script>
<!-- Tour created with Amberjack wizard: http://amberjack.org -->
<div class="main">
  <div class="top"></div>
  <div class="clr"></div>
  <div class="mid">
    <div class="inn">
      <!--Header-->
  
    <div id="header">
    <div class="top-left-outer">
      <div class="text-logo">
      </div>
      <div class="date-time">
      
      <?php
	   $timezone = new DateTimeZone( "America/New_York" );
$date = new DateTime();
$date->setTimezone( $timezone );
echo  $date->format( "F j,Y | g:i a Y T"); 
    ?>
      </div>
      </div>
      <div id="logo-title" class="logo">

        <a href="<?php print $front_page; ?>" rel="home" id="logo" title="<?php print t('Home'); ?>"></a>
      <?php //$logo;?>

  
      </div> <!-- /logo-title -->
       
   <div class="loginvi-outer">
	
		<?php include "login.tpl.php"; ?>
</div>
</div>     

 <?php if (!empty($search_box)): ?>
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
          <div class="search">  <form class="home_searchEngine" name="search" method="post" action="">
            <div class="searchtext">
          <input name="txt_search"  id="txt_search" value="<?php echo $skey; ?>" type="text"  onblur="if(search.txt_search.value =='') search.txt_search.value = ''" onfocus="if(search.txt_search.value =='Search') search.txt_search.value = ''" />
            </div>   
            <div class="searchr">
             
             <div class="stext">  <input type="radio" name="stype[]" id="stype1" value="1" <?php if(isset($_REQUEST['stype'])) { if($_REQUEST['stype'][0]==1) {?> checked="checked" <?php } }else{?> checked="checked" <?php }?>   /></div>
              <label for="radio" class="slab">Questions</label>
            </div>
            <div class="searchr">
              
            <div class="stext">    <input type="radio" name="stype[]" id="stype2" value="2" <?php if(isset($_REQUEST['stype'])) { if($_REQUEST['stype'][0]==2) {?> checked="checked" <?php } }?>  /></div>
             <label for="radio2" class="slab">Users</label>
            </div>
            <div>&nbsp;
                       <input name="Search" type="submit" value="Search"  onclick="return callfunction();"/>
            </div>
                  </form>     </div>
        		
                     <div class="men"> 
         <?php if (count($primary_links)) : ?>
	
    <?php $mb=1;foreach ($primary_links as $link): ?>
      <li><a href="<?php print($gSitePath.$link['href']);?>" <?php if($link['title'] == 'About US'||($link['title'] == 'Add  Question')||($link['title'] == 'Privacy')):?> class="floatbox" rel="nofollow" title="<?php print($link['title']);?>"<?php endif;?>><?php print($link['title']);?></a></li>
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