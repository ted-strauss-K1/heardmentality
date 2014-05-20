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
  // get data
  var charts = Drupal.settings.charts, history = charts.history;

  nv.addGraph(function () {
    // +focus
    // var chart = nv.models.lineWithFocusChart();
    var chart = nv.models.lineChart();

    // settings
    chart
      .interpolate("basis")
      .margin({left: 20, right: 20, top: 10})
      // +focus
      // .height2(40)
      .showLegend(false);
    // axis
    chart.xAxis.tickFormat(timestamp2date);
    // +focus
    // chart.x2Axis.tickFormat(timestamp2date);

    // dates
    var dates = [], days = 0;
    for (dates[days++] in history['stats']);

    // get data
    var count = charts.count;

    // datum
//    var datum = [];
//    var max = 0;
//    for (var i = 0; i < count; i++) {
//      var series = {};
//      series['color'] = charts.colors[i];
//      var choice_data = history['choice' + i];
//      series['key'] = choice_data['name'];
//      series['values'] = [];
//      for (var j in choice_data['data']) {
//        series['values'].push({
//          series: i,
//          x     : new Date(dates[j]),
//          y     : choice_data['data'][j]
//        });
//      }
//
//      max = Math.max(max, Math.max.apply(null, choice_data['data']));
//
//      datum[i] = series;
//    }


    // datum 2
    var datum = [], max = 0;
    // save key names
    for (var i = 0; i < count; i++) {
      datum.push({
        color : charts.colors[i],
        key   : history['choice' + i]['name'],
        values: []
      });
    }
    // add data
    var data_prev = [], data_upd = false, data_temp = [];
    for (var j = 0; j < days; j++) {
      var date = new Date(dates[j]), choice;

      //
      data_temp = [];
      for (var i = 0; i < count; i++) {
        var votes = history['choice' + i]['data'][j];
        data_temp.push(votes);
        max = Math.max(max, votes);
      }

      //
      if (0 == j) {
        data_prev = data_temp;
      }

      //
      data_upd = false;
      for (var k = 0; k < data_temp.length; k++) {
        if (data_prev[k] != data_temp[k]) {
          data_upd = true;
          data_prev = data_temp;
          break;
        }
      }

      if (data_upd) {
        for (var i = 0; i < count; i++) {
          (datum[i]['values']).push({
            series: i,
            x     : date,
            y     : history['choice' + i]['data'][j]
          });
        }
      }
    }

    chart.forceY([0, max + 1]);

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
