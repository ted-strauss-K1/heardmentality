<div class="line-top">
	<div class="container">
		<div class="navigation">
			<div class="top-left">
				<a class="logo" href="/"><img src="<?php print $directoryPath;?>/images/tiny_logo.png" class="logo-img" /> <?php print t('Heard Mentality'); ?></a>
			</div>
			
			<div class="top-right login">
				<?php print $user_login; ?>
			</div>
			
		</div>
	</div>
</div>

<div class="line-bottom">
	<div class="container">
		<div class="navigation">
			<div class="top-left user-menu">
				<ul class="menu">
          <?php foreach ($primary_links as $mainMenu) : ?>
            <li><?php print l(t($mainMenu['title']), $mainMenu['href'], array('attributes' => array('class'=>'issues'))); ?></li>
          <?php endforeach; ?>
				</ul>
				<ul class="menu second">
          <?php foreach ($secondary_links as $subMenu) : ?>
            <li><?php print l(t($subMenu['title']), $subMenu['href'], array('attributes' => array('class'=>'add'))); ?></li>
          <?php endforeach; ?>
				</ul>
			</div>
			<div class="top-right blue">
				<div class="expanding">
					<h6 class="inactive"><?php print t('Language'); ?></h6>
					<ul class="lang">
						<?php if($multilanguage_area): print $multilanguage_area; endif; ?>
					</ul>
				</div>
			</div>
		</div>
	</div>
</div>
