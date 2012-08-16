<?php
global $base_url;
?>

<div class="top-grey-box">
  	<div class="sort-by profile left20">
  		<span class="activity"><?php print t('Activity'); ?>:</span> <?php print $filters; ?>
	</div>
</div>

<div class="grey-box activity_stream clearfix">
	<ul class="action">
		<?php print $output; ?>
	</ul>

	<div class="pagination">
		<ul>
			<?php print $pagination; ?>
		</ul>
	</div>
</div>