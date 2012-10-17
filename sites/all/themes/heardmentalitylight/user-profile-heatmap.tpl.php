<script type='text/javascript' src='http://www.google.com/jsapi'></script>
<script type='text/javascript'>
  var columns = [{'type':'string','name':'Country'},{'type':'number','name':'Votes'}];
  var dataset = [['Afghanistan',12],['Algeria',25],['American Samoa',16],['Andorra',2],['Argentina',8],['Australia',5],['Austria',3],['Belarus',14],['Bouvet Island',8],['Brunei',11],['Burkina Faso',11],['Canada',20],['Colombia',22],['Croatia',5],['Cuba',3],['Cyprus',4],['El Salvador',2],['Equatorial Guinea',3],['Fiji',5],['India',20],['Indonesia',11],['South Africa',6],['Turks and Caicos Islands',14],['United States',14]];

  google.load('visualization', '1', {packages: ['geochart']});

  function init_heatmap() {
    var data = new google.visualization.DataTable();
    var current = Drupal.settings.heatmap.current;
    var columns = Drupal.settings.heatmap[current].columns;
    var dataset = Drupal.settings.heatmap[current].dataset;
    data.addRows( (dataset.length + 1) * columns.length );
    for (var i=0; i<columns.length; i++) {
      data.addColumn(columns[i]['type'], columns[i]['name']);
      for (var j=0; j<dataset.length; j++) {
        data.setValue(j, i, dataset[j][i]);
      }
    }
    var geomap = new google.visualization.GeoChart(document.getElementById('visualization'));
    geomap.draw(data,{width:320,height:190,showLegend:true});
  }
  google.setOnLoadCallback(init_heatmap);
</script>
<div id="visualization" style="cursor:pointer;"></div>
<ul class="map-stats">
  <?php
    $list = array('users' => 'Users', 'nodes' => 'Issues', 'votes' => 'Votes', 'online' => 'Online');
    foreach ($list as $type => $title) : ?>
      <li>
        <span class="count" id="count_<?php print $type; ?>">0</span>
        <span class="count-title"><a href="javascript:void(0);" name="<?php print $type; ?>"><?php print($title); ?></a></span>
        <span class="fast_counter" id="fast_counter_count_<?php print $type; ?>" style="display:none;"><?php
          $name = 'count_' . $type; print $$name; ?>
        </span>
      </li>
  <?php endforeach; ?>
</ul>