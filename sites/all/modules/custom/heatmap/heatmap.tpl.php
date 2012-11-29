<script type='text/javascript' src='http://www.google.com/jsapi'></script>
<script type='text/javascript'>


</script>
<div id="visualization" style="cursor:pointer;"></div>
<ul class="map-stats">
  <?php
  $list = array('users' => t('Users'), 'nodes' => t('Issues'), 'votes' => t('Votes'), 'online' => t('Online'));
  foreach ($list as $type => $title) : ?>
    <li>
      <span class="count" id="count_<?php print $type; ?>">0</span>
      <span class="count-title"><a href="javascript:void(0);"
                                   name="<?php print $type; ?>"><?php print($title); ?></a></span>
        <span class="fast_counter" id="fast_counter_count_<?php print $type; ?>" style="display:none;"><?php
          $name = 'count_' . $type; print $$name; ?>
        </span>
    </li>
    <?php endforeach; ?>
</ul>