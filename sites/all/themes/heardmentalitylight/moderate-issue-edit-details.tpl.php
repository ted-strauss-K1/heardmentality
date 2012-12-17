<div class="eleven columns">
			<h2 class="dinbold page-title"><?php print t('MODERATE'); ?></h2>
                        <?php if($moderateForm): ?>
                        <?php print $moderateForm; ?>
                        <?php endif; ?>

		</div>
		<div class="five columns">
			<br>
		  <div class="top-grey-box">
		    <br>
		    <div class="icon dupes text"></div>
        <label for="queue" class="queue"><?php print t('POSSIBLE DUPES'); ?></label>
			</div>
			<div class="grey-box ">
                                <?php print $possibleDupeForm; ?>
				<div class="clear" style="height:15px"></div>
			</div>
			<div class="grey-box">
				<div class="icon mod-history text"></div>
				<label for="queue" class="tags-on"><?php print t('Moderation History'); ?></label>
				<?php print $moderationHistory; ?>
			</div>
		</div>	