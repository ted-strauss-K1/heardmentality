/**
 *
 */
$(function () {
  if (Drupal.settings.charts.vote) init_history();
});

/**
 *
 */
function init_history() {
  nv.addGraph(function() {
    var chart = nv.models.lineWithFocusChart();

    // settings
    chart
      .interpolate("basis")
      .margin({left: 20, right: 20, top: 10})
      .height2(40)
      .showLegend(false);
    // axis
    chart.xAxis.tickFormat(timestamp2date);
    chart.x2Axis.tickFormat(timestamp2date);
    // chart.xAxis.rotateLabels(-45);

    // get data
    var count = Drupal.settings.charts.count;
    var dates = [], i = 0;
    for (dates[i++] in Drupal.settings.charts.history['stats']) {
      //
    }
    var datum = [];
    var max = 0;
    for (var i=0; i<count; i++) {
      var series = {};
      series['color'] = Drupal.settings.charts.colors[i];
      var choice_data = Drupal.settings.charts.history['choice'+i];
      series['key'] = choice_data['name'];
      series['values'] = [];
      for (var j in choice_data['data']) {
        series['values'].push({
          series: i,
          x: new Date(dates[j]),
          y: choice_data['data'][j]
        });
      }

      max = Math.max(max, Math.max.apply(null, choice_data['data']));

      datum[i] = series;
    }

    chart.forceY([0,max+1]);

    // exec
    d3.select('#chart-history svg')
      .datum(datum)
      .transition().duration(500)
      .call(chart);

    //
    nv.utils.windowResize(chart.update);

    return chart;
  });
}
