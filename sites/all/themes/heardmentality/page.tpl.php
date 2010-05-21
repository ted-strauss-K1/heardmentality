<?php global $gSitePath;?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />

<title><?php print $head_title ?></title>
<meta name="description" content="A web applications user interface library built on the Mootools javascript framework" />

	<?php print $head ?>
<?php print $styles ?>
<link rel="stylesheet" href="<?php echo $gSitePath?>sites/all/themes/heardmentality/css/content.css" type="text/css" />
<link rel="stylesheet" href="<?php echo $gSitePath?>sites/all/themes/heardmentality/css/ui.css" type="text/css" />
<link rel="stylesheet" href="<?php echo $gSitePath?>sites/all/themes/heardmentality/css/user_bar.css" type="text/css" />
<!--[if IE]>
	<script type="text/javascript" src="<?php echo $gSitePath?>sites/all/themes/heardmentality/scripts/excanvas-compressed.js"></script>		
<![endif]-->
	
<script type="text/javascript" src="<?php echo $gSitePath?>sites/all/themes/heardmentality/scripts/mootools-1.2-core.js"></script>
<script type="text/javascript" src="<?php echo $gSitePath?>sites/all/themes/heardmentality/scripts/mootools-1.2-more.js"></script>	
<?php print $scripts ?>
<!--
	mocha.js.php is for development. It is not recommended for production.
	For production it is recommended that you used a compressed version of either
	the output from mocha.js.php or mocha.js. You could also list the
	necessary source files individually here in the header though that will
	create a lot more http requests than a single concatenated file.
		
<script type="text/javascript" src="scripts/mocha.js"></script>

-->
<script type="text/javascript" src="<?php echo $gSitePath?>sites/all/themes/heardmentality/scripts/source/Utilities/mocha.js.php"></script>
<!--<script type="text/javascript" src="<?php echo $gSitePath?>sites/all/themes/heardmentality/scripts/mocha-events.js"></script>-->
    <script type="text/javascript" src="<?php echo $gSitePath?>sites/all/themes/heardmentality/scripts/slider_script.js"></script>

<!--<script type="text/javascript" src="<?php echo $gSitePath?>sites/all/themes/heardmentality/lighter/Lighter.js"></script>
	<script type="text/javascript" src="<?php echo $gSitePath?>sites/all/themes/heardmentality/lighter/Fuel.css.js"></script>
	<script type="text/javascript" src="<?php echo $gSitePath?>sites/all/themes/heardmentality/lighter/Fuel.html.js"></script>
	<script type="text/javascript" src="<?php echo $gSitePath?>sites/all/themes/heardmentality/lighter/Fuel.js.js"></script>
	<script type="text/javascript">
		window.addEvent('domready', function(){
			$$('code').light({
				altLines: 'hover',
				path: '<?php echo $gSitePath?>sites/all/themes/heardmentality/lighter/',
				mode: 'ol',
				fuel: 'js',
				indent: 4
			});
		});
	</script>-->
	
	
	<link rel="stylesheet" href="<?php echo $gSitePath?>sites/all/themes/heardmentality/css/multibox.css" type="text/css" media="screen" />
<!--[if IE 6]>
	<link rel="stylesheet" href="<?php echo $gSitePath?>sites/all/themes/heardmentality/css/multibox-ie6.css" type="text/css" media="screen" />
	<![endif]-->
	<script type="text/javascript" src="<?php echo $gSitePath?>sites/all/themes/heardmentality/js/overlay.js"></script>
	<script type="text/javascript" src="<?php echo $gSitePath?>sites/all/themes/heardmentality/js/Assets.js"></script>
	<script type="text/javascript" src="<?php echo $gSitePath?>sites/all/themes/heardmentality/js/multibox.js"></script>
<script type="text/javascript" src="<?php echo $gSitePath?>sites/all/modules/quest_lite/scripts/subtab.js"></script>

	<script type="text/javascript">
	
		window.addEvent('domready', function(){
			var box = new multiBox('mb', {
				overlay: new overlay()
			});

		
			var box = new multiBox('advanced1', {
				overlay: new overlay(),
				descClassName: 'advancedDesc'
			});
			
			var advanced = new multiBox('advanced2', {
				overlay: new overlay(),
				descClassName: 'advancedDesc'
			});
			
			var box = new multiBox('advanced3', {
				overlay: new overlay(),
				descClassName: 'advancedDesc'
			});
			
			var box = new multiBox('advanced4', {
				overlay: new overlay()
			});
			
			var box = new multiBox('advanced5', {
				overlay: new overlay()
			});
			
			var box = new multiBox('advanced6', {
				overlay: new overlay()
			});
			var box = new multiBox('advanced7', {
				overlay: new overlay()
			});
			
		});
	
	</script>

<!--<script type="text/javascript" src="<?php echo $gSitePath?>sites/all/themes/heardmentality/scripts/mocha-init.js"></script>-->

</head>
<body>

<?php

//echo md5('admin');
//echo "<br>";
//echo '21232f297a57a5a743894a0e4a801fc3';
global $user;
//echo strtotime('1270549824');
//echo $user->uid;
?>
<div id="desktop">

<div id="desktopHeader">
<div id="desktopTitlebarWrapper">
	<div id="desktopTitlebar">
		<h1 class="applicationTitle"><a href="<?php echo $gSitePath?>">Mocha UI</a></h1>
		<!--h2 class="tagline">A Web Applications <span class="taglineEm">User Interface Library</span></h2-->
		<div id="topNav">
			<div align="left" id="google_translate_element">
                    </div>
                    <script>
                        function googleTranslateElementInit(){
                            new google.translate.TranslateElement({
                                pageLanguage: 'en'
                            }, 'google_translate_element');
                        }
                    </script>
                    <script src="http://translate.google.com/translate_a/element.js?cb=googleTranslateElementInit">
                    </script>
         <ul class="menu-right">
         	    
        	<?php 
			global $user;    
			if($user->uid == ''|| $user->uid == '0'):

			  ?>
                <ul class="menu-right">
                	<!--<li>Welcome <a href="javascript:void(0)" onclick="MochaUI.notification('Do Something');return false;">Guest</a>.</li>
                    <li><a href="<?php echo $gSitePath?>member/login"  rel="width:850,height:570" class="advanced7">Sign In</a></li>-->
                    
                      <!-- <li><a onclick="loadlogin('<?php echo $gSitePath?>member/index','Login');">Sign In</a></li>
                      <?php //include("".$gSitePath."dope-openid-1.0.1/login.php");?>
                      <li><a href="<?php echo $gSitePath?>openids/new">Sign In</a></li>-->
                      
                   <!-- socialize.js script should only be included once -->
<!--<script type="text/javascript" src="http://cdn.gigya.com/js/socialize.js?apiKey=2_OdDWGhe73p04B0m5k4zqlKdtnBCu9jbyud93Jgy-b8jEtbAXlAkbfpk9qBp781g8"></script>
<script type="text/javascript">
var conf=
{
	APIKey: '2_OdDWGhe73p04B0m5k4zqlKdtnBCu9jbyud93Jgy-b8jEtbAXlAkbfpk9qBp781g8'
	
}
</script>


<script type="text/javascript">
var login_params=
{
	useHTML: 'true'
	,showTermsLink: 'false'
	,height: 50
	,width: 150
	,containerID: 'componentDiv'
	,useFacebookConnect: 'true'
	, redirectURL:'<?php echo $gSitePath?>openids/save'  
}
</script>
<div id="componentDiv"></div>
<script type="text/javascript">
   gigya.services.socialize.showLoginUI(conf,login_params);
</script>-->



<!-- socialize.js script should only be included once -->
<script type="text/javascript" src="http://cdn.gigya.com/js/socialize.js?apiKey=2_Zfr6Di925xeUYK-BRe1kNOYYclMYDUbGsgb_kF4NqlZaJ4owUytfdi2cnRePUJ_j"></script>
<script type="text/javascript">
var conf=
{
	APIKey: '2_Zfr6Di925xeUYK-BRe1kNOYYclMYDUbGsgb_kF4NqlZaJ4owUytfdi2cnRePUJ_j'
}
</script>

<script type="text/javascript">
var login_params=
{
	useHTML: 'true'
	,showTermsLink: 'false'
	,height: 50
	,width: 150
	,containerID: 'componentDiv'
	,useFacebookConnect: 'true'
	, redirectURL:'<?php echo $gSitePath?>openids/save' 
}
</script>
<div id="componentDiv"></div>
<script type="text/javascript">
   gigya.services.socialize.showLoginUI(conf,login_params);
</script>



                </ul>			  
			  <?php
			 else:
			
			?>
            
          
			<ul class="menu-right">
				<li>Welcome <a href="<?php echo $gSitePath?>profile" ><?php
				 $user_prof = db_fetch_object(db_query("SELECT * from {user_profile} where  uid=".$user->uid." "));
				if($user_prof->real_name=='')
				{
				 $unaprint= explode("@",$user->mail); 
				 echo $unaprint[0];
				 
                 }
                 else
                 {
                echo $user_prof->real_name;
                 }
				 ?>
                 </a>.</li>
				<li><a  href="javascript:void(0)" onclick="window.location='<?php echo $gSitePath?>logout'">Sign Out</a></li>
			</ul>
            <?php
            endif;
			
			?>
            
            <div>
            <?php
            /*if($_REQUEST['stype']==2)
			{?>
			<form name="search" method="post" action="<?php echo $gSitePath?>search/user">
            <?php 
			}
            else
			{?>
			<form name="search" method="post" action="<?php echo $gSitePath?>search/question">
            <?php
			}*/
			?>
            <script type="text/javascript">
			function callfunction()
			{
			typem=document.search.stype[0].checked;
			if(typem==false)
			{
			
			document.search.action="<?php echo $gSitePath?>searchuser";
			document.search.submit();
			}
			else
			{
				document.search.action="<?php echo $gSitePath?>searchquestion";
			document.search.submit();
			}
			
			}
			</script>
            <?php
			$spe=$_REQUEST['stype'];
			?>
            <form name="search" method="post" action="">
    <input type="text" name="txt_search" id="txt_search" />
    
    <input name="Search" type="submit" value="Search"  onclick="return callfunction();"/>
    <input type="radio" name="stype" id="stype" id="stype" value="1" <?php if($spe==1) { ?> checked="checked" <?php }?> />Question
    
    <input type="radio" name="stype" id="stype" id="stype" value="2" <?php if($spe==2) { ?> checked="checked" <?php }?> />Users
    
    </form>
    </div>
            
            <!--  <ul class="menu-right">
                
                    <li><a href="<?php echo $gSitePath?>member/login"  rel="width:850,height:570" class="advanced7">Sign In</a></li>
                </ul>	-->
               <?php //print garland_user_bar() ?>
               </ul>
               
          
		</div>
	</div>
</div>
	<?php
	//$_SERVER['PHP_SELF']
	
	$linkuse = substr($_GET['q'], strrpos($_GET['q'], "/") + 1);
	
	if($linkuse=='user')
	{
	?>
    <script type="text/javascript">
    var widthmain=520;
	</script>
    <?php 
	}
	 elseif($linkuse=='question')
    {
	?>
	<script type="text/javascript">
    var widthmain=450;
	</script>
	<?php 
	}
    else
    {
	?>
	<script type="text/javascript">
    var widthmain=220;
	</script>
	<?php 
	}
	?>
<div id="desktopNavbar">
	<?php if (count($primary_links)) : ?>
	<ul>
    <?php $mb=1;foreach ($primary_links as $link): ?>
      <li><a href="<?php print($gSitePath.$link['href']);?>" <?php if($link['title'] == 'About US'||($link['title'] == 'Add  Question')||($link['title'] == 'Privacy')):?> rel="width:850,height:570" class="advanced<?php echo $mb++; ?>" title="<?php print($link['title']);?>"<?php endif;?>><?php print($link['title']);?></a>
      
      <?php if($link['title'] == 'Categories'):?>
      	<?php
			echo sub_menu_cat(0,0);			
		?>
      <?php endif;?>
      
      </li>
    <?php endforeach; ?>
	</ul>	
    <?php endif;?>
    
	
</div><!-- desktopNavbar end -->
</div><!-- desktopHeader end -->

<!--div id="dockWrapper">
	<div id="dock">
		<div id="dockPlacement"></div>
		<div id="dockAutoHide"></div>
		<div id="dockSort"><div id="dockClear" class="clear"></div></div>
	</div>
</div-->
<div id="pageWrapper"></div>


<div id="desktopFooterWrapper">
	<div id="desktopFooter">
		Copyright <a target="_blank" href="http://creativecommons.org/licenses/by-sa/2.5/"><img src="<?php echo $gSitePath?>sites/all/themes/heardmentality/images/cc.jpg" width="18" height="17" /></a> 2010  Heardmentality.org    <!--<span style="margin-left:699px;"> <a title="Conatct Us" class="advanced4" rel="width:850,height:570" href="<?php echo $gSitePath?>node/7">Conatct Us</a> - <a title="Conatct Us" class="advanced5" rel="width:850,height:570" href="<?php echo $gSitePath?>node/8">Privacy Policy </a> - <a href="<?php echo $gSitePath?>node/9"> User Agreement </a>--><span style="margin-left:699px;">
         <?php   $mbl=4;$min=0; foreach ($secondary_links as $linksm): $min++;?>
         <a href="<?php print($gSitePath.$linksm['href']);?>" <?php if($linksm['title'] == 'Contact Us'||($linksm['title'] == 'Privacy & Policy')||($linksm['title'] == 'User Agreement')):?> rel="width:850,height:570" class="advanced<?php echo $mbl++; ?>" title="<?php print($linksm['title']);?>"<?php endif;?>><?php print($linksm['title']);?></a><?php if((count($secondary_links))>=$min){ echo " - ";}$min++;?> 
          <?php endforeach; ?>
          
     
          
          
        <a href="http://www.opensource.org/" target="_blank"><img src="<?php echo $gSitePath?>sites/all/themes/heardmentality/images/OpenSourceLogo.jpg" width="18" height="17" /> </a>&nbsp;<a href="http://drupal.org/" target="_blank"><img src="<?php echo $gSitePath?>sites/all/themes/heardmentality/images/Drupal.jpg" width="14" height="16" /></a>&nbsp;<a href="http://www.govtrack.us/" target="_blank"><img src="<?php echo $gSitePath?>sites/all/themes/heardmentality/images/Govtrack.jpg" width="16" height="16" /> </a>&nbsp;<a href="http://code.google.com/" target="_blank"><img src="<?php echo $gSitePath?>sites/all/themes/heardmentality/images/Google.jpg" width="16" height="16" /></a> &nbsp;<a href="http://amberjack.org/" target="_blank"><img src="<?php echo $gSitePath?>sites/all/themes/heardmentality/images/Amber.jpg" width="14" height="14" /></a>&nbsp;<a href="http://openid.net/"><img src="<?php echo $gSitePath?>sites/all/themes/heardmentality/images/OpenID.jpg" width="15" height="15" /></a>&nbsp;<a href="https://community.rallydev.com/slm/login.op" target="_blank"><img src="<?php echo $gSitePath?>sites/all/themes/heardmentality/images/RallyDev.jpg" width="16" height="16" /></a>&nbsp;<a href="http://www.geonames.org/" target="_blank"><img src="<?php echo $gSitePath?>sites/all/themes/heardmentality/images/Geonames.jpg" width="18" height="18" /></a> </span>
       
        
	</div>
    
   
</div>



</div><!-- desktop end -->
<div style="height: 718px; visibility: visible; opacity: 0.6;" id="modalOverlay"></div><div style="height: 718px; visibility: visible; opacity: 0.01; display: none;" id="windowUnderlay"></div>
<div id="divCont" style="display:none;">
 <?php if ($mission): print '<div id="mission">'. $mission .'</div>'; endif; ?>
<?php if ($tabs): print '<div id="tabs-wrapper" class="clear-block">'; endif; ?>
<?php //if ($title): print '<h2'. ($tabs ? ' class="with-tabs"' : '') .'>'. $title .'</h2>'; endif; ?>
<?php if ($tabs): print '<ul class="tabs primary">'. $tabs .'</ul></div>'; endif; ?>
<?php if ($tabs2): print '<ul class="tabs secondary">'. $tabs2 .'</ul>'; endif; ?>
<?php if ($show_messages && $messages): print $messages; endif; ?>
<?php print str_replace("\n","",$content); ?>
</div>

</body>
</html>


<script type="text/javascript">
window.addEvent('domready', function(){
	MochaUI.Desktop = new MochaUI.Desktop();
	MochaUI.Dock = new MochaUI.Dock();
 <?php if ($left): ?>
	new MochaUI.Column({
		id: 'sideColumn1',
		placement: 'left',
		width: 200,
		resizeLimit: [100, 300]
	});
	
	<?php endif;?>
	new MochaUI.Column({
		id: 'mainColumn',
		placement: 'main',	
		width: null,
		resizeLimit: [100, 300]
	});
	
	
<?php if ($right): ?>
	new MochaUI.Column({
		id: 'sideColumn2',
		placement: 'right',	
		width: widthmain,		
		resizeLimit: [195, 300]
	});
<?php endif; ?>

	// Add panels to first side column
	
	<?php print $left;?>
	
	vCont=document.getElementById('divCont').innerHTML;
	// Add panels to main column	
	new MochaUI.Panel({
		id: 'mainPanel',
		title: '<?php print str_replace("'","&rsquo;",$title) ?>',
		loadMethod: 'html',
		content: ''+vCont,
		column: 'mainColumn',
		panelBackground: '#fff'
	});
	<?php print $footer;?>
	<?php print $right;?>
	// Add panels to second side column
<?php if($user->uid==0)
	{ ?>
	
	//initSlidingContent('scrollingContainer',3);
<?php 
 }
?>
	MochaUI.Modal = new MochaUI.Modal();
	
	MochaUI.Desktop.desktop.setStyles({
		'background': '#fff',
		'visibility': 'visible'
	});
	
	MochaUI.slideshareWindow = function(url,title){
			new MochaUI.Window({
			id: 'ajaxpage',
			title: 'Sub Categories List '+title,
			loadMethod: 'xhr',
			contentURL: url,
			type: 'modal',
			width: 415,
			height: 355,
			resizeLimit:  {'x': [330, 2500], 'y': [250, 2000]},
			contentBgColor: '#FFF'
		});
	}
	MochaUI.resourceWindow = function(url,title){
			new MochaUI.Window({
			id: 'ajaxpage',
			title: ' Resource >> '+title,
			loadMethod: 'xhr',
			contentURL: url,
			type: 'modal',
			width: 650,
			height: 405,
			resizeLimit:  {'x': [330, 2500], 'y': [250, 2000]},
				contentBgColor: '#FFF',
		onContentLoaded: function(){
                               if ( !MochaUI.resourceScript == true ){
                                       new Request({
                                               url: '<?php echo $gSitePath; ?>sites/all/modules/quest_lite/scripts/add_resource.js',
                                               method: 'get',
                                               onSuccess: function() {
                                                       MochaUI.resourceScript = false;
                                               }.bind(this)
                                       }).send();
                               }
                       }
		});
	}
	
	
	MochaUI.flagquestionWindow = function(url,title){
			new MochaUI.Window({
			id: 'ajaxpage',
			title: ' Flag '+title,
			loadMethod: 'xhr',
			contentURL: url,
			type: 'modal',
			width: 650,
			height: 500,
		
			resizeLimit:  {'x': [330, 2500], 'y': [250, 2000]},
			contentBgColor: '#FFF'
		});
	}
	
	MochaUI.suggestanswerWindow = function(url,title){
			new MochaUI.Window({
			id: 'ajaxpage',
			title: ' Suggest  '+title,
			loadMethod: 'xhr',
			contentURL: url,
			type: 'modal',
			width: 650,
			height: 500,
		
			resizeLimit:  {'x': [330, 2500], 'y': [250, 2000]},
			contentBgColor: '#FFF'
		});
	}
	
	MochaUI.slideqDetails = function(url,title){
			new MochaUI.Window({
			id: 'ajaxpage',
			title: ' '+title,
			loadMethod: 'xhr',
			contentURL: url,
			type: 'modal',
			width: 650,
			height: 500,
		
			resizeLimit:  {'x': [330, 2500], 'y': [250, 2000]},
			contentBgColor: '#FFF'
		});
	}
	
	MochaUI.followerWindow = function(url,title){
			new MochaUI.Window({
			id: 'ajaxpage',
			title: ' '+title,
			loadMethod: 'xhr',
			contentURL: url,
			type: 'modal',
			width: 650,
			height: 500,
		
			resizeLimit:  {'x': [330, 2500], 'y': [250, 2000]},
			contentBgColor: '#FFF'
		});
	}
	
	
	MochaUI.followingWindow = function(url,title){
			new MochaUI.Window({
			id: 'ajaxpage',
			title: ' '+title,
			loadMethod: 'xhr',
			contentURL: url,
			type: 'modal',
			width: 650,
			height: 500,
		
			resizeLimit:  {'x': [330, 2500], 'y': [250, 2000]},
			contentBgColor: '#FFF'
		});
	}
	
	
	
	
	MochaUI.loginWindow = function(url,title){
			new MochaUI.Window({
			id: 'ajaxpage',
			title: ' '+title,
			loadMethod: 'xhr',
			contentURL: url,
			type: 'modal',
			width: 650,
			height: 500,
		
			resizeLimit:  {'x': [330, 2500], 'y': [250, 2000]},
				contentBgColor: '#FFF',
		onContentLoaded: function(){
                               if ( !MochaUI.resourceScript == true ){
                                       new Request({
                                               url: '<?php echo $gSitePath; ?>sites/all/modules/openids/js/login.js',
                                               method: 'get',
                                               onSuccess: function() {
                                                       MochaUI.resourceScript = false;
                                               }.bind(this)
                                       }).send();
                               }
                       }
		});
	}
	
	MochaUI.retagWindow = function(url,title){
			new MochaUI.Window({
			id: 'ajaxpage',
			title: ' Question >> '+title,
			loadMethod: 'xhr',
			contentURL: url,
			type: 'modal',
			width: 650,
			height: 405,
			resizeLimit:  {'x': [330, 2500], 'y': [250, 2000]},
				contentBgColor: '#FFF',
		onContentLoaded: function(){
                               if ( !MochaUI.resourceScript == true ){
                                       new Request({
                                               url: '<?php echo $gSitePath.drupal_get_path('module','quest_lite'); ?>/scripts/tagging.js',
                                               method: 'get',
                                               onSuccess: function() {
                                                       MochaUI.resourceScript = false;
                                               }.bind(this)
                                       }).send();
                               }
                       }
		});
	}
	
	
	MochaUI.inviteWindow = function(url,title){
			new MochaUI.Window({
			id: 'ajaxpage',
			title: ' Invite >> '+title,
			loadMethod: 'xhr',
			contentURL: url,
			type: 'modal',
			width: 650,
			height: 405,
			resizeLimit:  {'x': [330, 2500], 'y': [250, 2000]},
				contentBgColor: '#FFF',
		onContentLoaded: function(){
                               if ( !MochaUI.resourceScript == true ){
                                       new Request({
                                               url: '<?php echo $gSitePath.drupal_get_path('module','invite'); ?>/scripts/invite.js',
                                               method: 'get',
                                               onSuccess: function() {
										
                                                       MochaUI.resourceScript = false;
                                               }.bind(this)
                                       }).send();
                               }
                       }
		});
	}
	
	
	
MochaUI.loadwaveWindow = function(qid,wid){
			new MochaUI.Window({
			id: 'ajaxpage',
			title: 'Forum Wavelets',
			loadMethod: 'xhr',
			contentURL: 'question/forum/?qid='+qid+'&wid='+wid,
			type: 'modal',
			width: 600,
			height:500,
			resizeLimit:  {'x': [330, 2500], 'y': [250, 2000]},
			contentBgColor: '#FFF',

			onClose:function(){
			
				

			},onContentLoaded: function(){
                               if ( !MochaUI.resourceScript == true ){
                                       new Request({
                                               url: '<?php echo $gSitePath.drupal_get_path('module','forum'); ?>/scripts/forum.js',
                                               method: 'get',
                                               onSuccess: function() {
										
                                                       MochaUI.resourceScript = false;
                                               }.bind(this)
                                       }).send();
                               }
                       }

		});
	}
	
		//subtab()
});



function loadwave(qid,wid)
{
MochaUI.closeAll();
MochaUI.loadwaveWindow(qid,wid);

	
}


function loadSubCat(url,title)
{
MochaUI.closeAll();
MochaUI.slideshareWindow(url,title);

	
}

function load_invite(url,title){
	
	MochaUI.closeAll();
MochaUI.inviteWindow(url,title);
}

function loaddetails(url,title)
{
MochaUI.closeAll();
MochaUI.slideqDetails(url,title);

	
}
function loadresource(url,title)
{
MochaUI.closeAll();
MochaUI.resourceWindow(url,title);

	
}
function loadflagquestion(url,title)
{
MochaUI.closeAll();
MochaUI.flagquestionWindow(url,title);

	
}
function loadsuggest(url,title)
{
MochaUI.closeAll();
MochaUI.suggestanswerWindow(url,title);

	
}
function loadtag(url,title)
{
MochaUI.closeAll();
MochaUI.retagWindow(url,title);

	
}
function loadfollower(url,title)
{
MochaUI.closeAll();
MochaUI.followerWindow(url,title);

	
}
function loadfollowing(url,title)
{
MochaUI.closeAll();
MochaUI.followingWindow(url,title);

	
}

function loadlogin(url,title)
{

MochaUI.closeAll();
MochaUI.loginWindow(url,title);

	
}

	</script>
    
    <?php
function sub_menu_cat($id='',$level='')
{
	global $gSitePath;
	$strReturn = null;
	if($level<1){
			 $client_select =db_query("SELECT cat_id,cat_name FROM {category} where parent_id='".$id."'");
			
			$client_array=array();
			$client_key=array();
		
			while($list=db_fetch_object($client_select))
			{
		
		   $client_array[] = $list->cat_name;
			$client_key[]=$list->cat_id;
		
			}
								
			if(count($client_array)>0){
		
			
				 $strReturn.='<ul >';
			 
				 for($i=0;$i<count($client_array);$i++){
				 
				  $check_sub =db_query("SELECT cat_id,cat_name FROM {category} where parent_id='".$client_key[$i]."'");
				  	$cnt=array();
				  while($sublevel=db_fetch_object($check_sub)){
				  $cnt[]=$sublevel->cat_name;
				  }
				
					if(count($cnt)>0){
					$class="arrow-right";
					$link='onclick="loadSubCat(\''.$gSitePath.'category/list/'.$client_key[$i].'\',\''.$client_array[$i].'\')"';
					$class_li='';
					}else{
						$link='href='.$gSitePath.'category/';
					$class="";
					$class_li='';
					}
				$strReturn .= '<li class="divider"><a  id="mootoolsLink" class="returnFalse '.$class.'"  '.$link.'>'.$client_array[$i].'</a>';
				 $strReturn.=sub_menu_cat($client_key[$i],$level+1);
				 
				$strReturn.='</li>';
			}
		
		
			
		 $strReturn.='</ul>';
		 
		 }
	}
	return $strReturn;

}
?>
