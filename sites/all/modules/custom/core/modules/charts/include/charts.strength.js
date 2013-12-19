/**
 *
 */
$(function () {
  init_strength();
});

/**
 *
 */
$('#deb-ana').live('click', function () {
  init_strength();
});

/**
 *
 */
function init_strength() {
  $('#chart-strength svg').empty();

  var data = [
    {
      key   : 'Stream',
      values: Drupal.settings.charts.strength
    }
  ];

  var chart;
  nv.addGraph(function () {
    chart = nv.models.multiBarChart()
      .transitionDuration(300)
      .delay(0)
      .showLegend(false)
      .showControls(false);

    d3.select('#chart-strength svg')
      .datum(data)
      .call(chart);

    nv.utils.windowResize(chart.update);

    return chart;
  });
}
