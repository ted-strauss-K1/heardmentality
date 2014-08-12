<script type='text/javascript' src='http://www.google.com/jsapi'></script>
<script type="text/javascript">
  function init_heatmap() {
    var data = new google.visualization.DataTable();
    var current = Drupal.settings.heatmap.current;
    var columns = Drupal.settings.heatmap[current].columns;
    var dataset = Drupal.settings.heatmap[current].dataset;
    data.addRows((dataset.length + 1) * columns.length);
    for (var i = 0; i < columns.length; i++) {
      data.addColumn(columns[i]['type'], columns[i]['name']);
      for (var j = 0; j < dataset.length; j++) {
        data.setValue(j, i, dataset[j][i]);
      }
    }
    var geomap = new google.visualization.GeoChart(document.getElementById('visualization'));
    geomap.draw(data, {width: 320, height: 190, showLegend: true});
  }

  google.load('visualization', '1', {packages: ['geochart']});
  google.setOnLoadCallback(init_heatmap);
</script>
<div id="visualization" style="cursor:pointer;"></div>
<ul class="map-stats">
  <?php
  $list = array(
    'users' => __('Users', array('@code' => 'heatmap-01')),
    'nodes' => __('Issues', array('@code' => 'heatmap-02')),
    'votes' => __('Votes', array('@code' => 'heatmap-03')),
    'online' => __('Online', array('@code' => 'heatmap-04'))
  );
  foreach ($list as $type => $title) : $i++; ?>
    <li>
      <span class="count" id="count_<?php print $type; ?>">0</span>
      <span class="count-title"><a href="javascript:void(0);"
                                   name="<?php print $type; ?>"><?php print($title); ?></a></span>
        <span class="fast_counter" id="fast_counter_count_<?php print $type; ?>" style="display:none;"><?php
          $name = 'count_' . $type;
          print $$name; ?>
        </span>
    </li>
    <?php if ($i == 2) : ?><br><?php endif; ?>
  <?php endforeach; ?>
</ul>
