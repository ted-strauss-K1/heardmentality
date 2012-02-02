<?php
global $base_url;
?>


<div class="map">
  <iframe id='cirmap' src ='<?php print $base_url; ?>/google/map/users?width=320&height=190' width='330' frameborder='0' height='200' scrolling='no'></iframe>
</div>

<ul class="map-stats">
        <li><span class="count"><?php print number_format($users); ?></span><span class="count-title"><a href="<?php print $base_url; ?>/google/map/users"><?php print t('Users'); ?></a></span></li>
        <li><span class="count"><?php print number_format($issues); ?></span><span class="count-title"><a href="<?php print $base_url; ?>/google/map/questions"><?php print t('Issues'); ?></a></span></li>
        <li><span class="count"><?php print number_format($votes); ?></span><span class="count-title"><a href="<?php print $base_url; ?>/google/map/answer"><?php print t('Votes'); ?></a></span></li>
        <li><span class="count"><?php print number_format($online); ?></span><span class="count-title"><a href="<?php print $base_url; ?>/google/map/online"><?php print t('Members'); ?></a></span></li>
</ul>
