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
				  <li><?php print l(t('Issues'), 'issues', array('attributes' => array('class'=>'issues'))); ?></li>
				  <li><?php print l(t('Analysis'), $_GET['q'], array('attributes' => array('class'=>'analysis'))); ?></li>
				</ul>
				<ul class="menu second">
				  <li><?php print l(t('Add an Issue'), 'issue/create', array('attributes' => array('class'=>'add'))); ?></li>
				  <?php if (user_is_logged_in()) : ?>
					<li><?php print l(t('Following'), 'following', array('attributes' => array('class'=>'following'))); ?></li>
				  <?php endif; ?>
				  <?php
				  // TODO
				  if ( false ) : ?>
					<li><?php print l(t('Moderator'), 'issues/list/all', array('attributes' => array('class'=>'moderator add'))); ?></li>
				  <?php endif; ?>
				</ul>
			</div>
			<div class="top-right blue">
				<div class="expanding">
					<h6 class="inactive"><?php print t('Language'); ?></h6>
					<ul class="lang" style="display:none;" aria-hidden="true">
						<?php if($multilanguage_area): print $multilanguage_area; endif; ?>
					</ul>
				</div>
			</div>
		</div>
	</div>
</div>
