<?php
global $base_url;
?>

<div class="top-grey-box">
  			<div class="sort-by left20">
  				<span class="activity"><?php print t('ACTIVITY'); ?>:</span> <?php print $filters; ?>
  			</div>
			</div>
			<div class="grey-box">
				<ul class="action">
				  <?php print $output; ?>
			  </ul>
				<br class="clear">
				<div class="pagination">
				  <ul>
				    <?php print $pagination; ?>
				  </ul>
			  </div>

				<div class="clear"></div>
			</div>