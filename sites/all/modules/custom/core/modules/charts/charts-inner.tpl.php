<ul <?php print $node->vote || !$node->cpoll['active'] ? '' : 'class="notvoted"' ?>>
  <li class="part">
    <div class="space">
      <div class="inner filter"><?php print $filter; ?></div>
    </div>
  </li>
  <li class="part margin">
    <div class="space">
      <p class="result-title dinbold"><?php print __('Quick facts', array('@code' => 'charts-01')); ?></p>

      <div id="insight-view" class="inner"><?php print $quickfacts; ?></div>
    </div>
  </li>
  <li class="full">
    <div class="space">
      <p class="result-title dinbold"><?php print __('Legend', array('@code' => 'charts-02')); ?></p>

      <div class="inner legend">
        <?php print $legend; ?>
      </div>
    </div>
  </li>
  <li class="part">
    <div class="space">
      <p class="result-title dinbold"><?php print __('Vote history', array('@code' => 'charts-03')); ?></p>

      <div class="inner graf"><?php print $history; ?></div>
    </div>
  </li>
  <li class="part margin">
    <div class="space">
      <p class="result-title dinbold"><?php print __('Vote map', array('@code' => 'charts-04')); ?></p>

      <div class="inner map"><?php print $gmap; ?></div>
    </div>
  </li>
</ul>
