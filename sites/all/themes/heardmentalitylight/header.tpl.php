<?php
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)).'/';
?>

<div class="line-top">
	<div class="container">
		<div class="navigation">
			<div class="top-left">
				<a class="logo" href="<?php print $sitelink;?>"><img src="<?php print $directoryPath;?>/images/tiny_logo.png" class="logo-img" /> <?php print t('Heard Mentality'); ?></a>
			</div>
			
			<div class="top-right login">
				<?php print $user_login; ?>
				<a href="#" id="dialog_link" class="ui-state-default ui-corner-all login">
                  <?php if($user->uid == ''){
                              print t('LOGIN');
                          }else{
                             print $user->name;
                          }
                  ?>
                </a>
			</div>
			
		</div>
	</div>
</div>

<div class="line-bottom">
	<div class="container">
		<div class="navigation">
			<div class="top-left user-menu">
				<ul class="menu">
                    <?php
                        foreach ($primary_links as $mainMenu){
                    ?>
                    <li><?php print l(t($mainMenu['title']), $mainMenu['href'], array('attributes' => array('class'=>'issues'))); ?></li>
                    <?php }?>

				</ul>
				<ul class="menu second">
                    <?php
                        foreach ($secondary_links as $subMenu){
                    ?>
                    <li><?php print l(t($subMenu['title']), $subMenu['href'], array('attributes' => array('class'=>'add'))); ?></li>
                    <?php }?>
				</ul>
			</div>
			<div class="top-right blue">
				<div class="expanding">
					<h6><?php print t('Language'); ?></h6>
					<ul class="lang">
						<?php if($multilanguage_area): print $multilanguage_area; endif; ?>
					</ul>
				</div>
			</div>
		</div>
	</div>
</div>
