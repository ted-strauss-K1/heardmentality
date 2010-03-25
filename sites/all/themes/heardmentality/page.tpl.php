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
   <!--  <script type="text/javascript" src="<?php echo $gSitePath?>sites/all/modules/quest_lite/scripts/subtabs.js"></script>-->

	<script type="text/javascript">
	
		window.addEvent('domready', function(){
			var box = new multiBox('mb', {
				overlay: new overlay()
			});

			var advanced = new multiBox('advanced', {
				overlay: new overlay(),
				descClassName: 'advancedDesc'
			});
		});
	
	</script>

<!--<script type="text/javascript" src="<?php echo $gSitePath?>sites/all/themes/heardmentality/scripts/mocha-init.js"></script>-->

</head>
<body>
<?php

global $user;
//print_r ($user);
//echo $user->uid;
?>
<div id="desktop">

<div id="desktopHeader">
<div id="desktopTitlebarWrapper">
	<div id="desktopTitlebar">
		<h1 class="applicationTitle"><a href="<?php echo $gSitePath?>">Mocha UI</a></h1>
		<!--h2 class="tagline">A Web Applications <span class="taglineEm">User Interface Library</span></h2-->
		<div id="topNav">
         <ul class="menu-right">
        	<!--<?php 
			global $user;    
			if($user->uid == '' || $user->uid == '0'):
			  ?>
                <ul class="menu-right">
                	<li>Welcome <a href="javascript:void(0)" onclick="MochaUI.notification('Do Something');return false;">Guest</a>.</li>
                    <li><a href="javascript:void(0)" onclick="window.location='<?php echo $gSitePath?>/user/login'">Sign In</a></li>
                </ul>			  
			  <?
			 else:
			?>
			<ul class="menu-right">
				<li>Welcome <a href="javascript:void(0)" onclick="MochaUI.notification('Do Something');return false;"><?php echo $user->name;?></a>.</li>
				<li><a  href="javascript:void(0)" onclick="window.location='<?php echo $gSitePath?>logout'">Sign Out</a></li>
			</ul>
            <?php
            endif;
			?>-->
            
               <?php print garland_user_bar() ?>
               </ul>
		</div>
	</div>
</div>
	
<div id="desktopNavbar">
	<?php if (count($primary_links)) : ?>
	<ul>
    <?php foreach ($primary_links as $link): ?>
      <li><a href="<?php print($gSitePath.$link['href']);?>" <?php if($link['title'] == 'About US'||($link['title'] == 'Add  Question')):?> rel="width:850,height:570" class="advanced" title="<?php print($link['title']);?>"<?php endif;?>><?php print($link['title']);?></a>
      
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
		Copyright &copy; 2010  Heardmentality.org   <span style="margin-left:900px;"><a href="<?php echo $gSitePath?>node/7">Contact Us</a> - <a href="<?php echo $gSitePath?>node/8">Privacy Policy </a> - <a href="<?php echo $gSitePath?>node/9"> User Agreement </a></span>
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
		width: 220,		
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
	
	initSlidingContent('scrollingContainer',3);
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
			contentBgColor: '#FFF'
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
		//subtab()
});


function loadSubCat(url,title)
{
MochaUI.closeAll();
MochaUI.slideshareWindow(url,title);

	
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
