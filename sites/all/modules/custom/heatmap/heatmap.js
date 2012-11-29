$(document).ready(function () {

  $('.count-title a').live('click', function (e) {
    e.preventDefault();
    e.stopPropagation();

    var el = $(this);
    $(".count-title a").css('color', '#000');
    el.css('color', '#4170A0');
    $('#visualization').fadeOut(500, function () {
      Drupal.settings.heatmap.current = el.attr('name');
      init_heatmap();
      $('#visualization').fadeIn(1000);
    });
  });

  google.load('visualization', '1', {packages:['geochart']});
  google.setOnLoadCallback(init_heatmap);

});

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
  geomap.draw(data, {width:320, height:190, showLegend:true});
}