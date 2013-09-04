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

    chart

      .interpolate("basis")
      .margin({left: 20, right: 10, top: 10})
      .height2(40)
      .showLegend(false);


    // get data
    var x = 0;
    var count = Drupal.settings.charts.count;
    var data = [];
    var stats = Drupal.settings.charts.history.stats;
    for (var date in stats) {
      var data_item = {};
      data_item['x'] = new Date(date);
      for (var i=0; i<count; i++) {
        data_item['stream'+i] = stats[date][i];
      }
      data.push(data_item);
    }

    // cross-filtered data
    var data = crossfilter(data);

    // get dimenasion
    var dimension = data.dimension(function(d) { return d.y; });

    // normalize data
    var series = [];
    for (var i=0; i<count; i++) {
      series.push({
        name: Drupal.settings.charts.history['choice'+i]['name'],
        key: 'stream'+i,
        color: Drupal.settings.charts.colors[i]
      });
    }

    data = normalize_data(dimension.top(Infinity), series, 'x');

    console.log(data);
    //
    chart.xAxis.tickFormat(function (d) {
      console.log(d);
      var months = ['Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec'];
      var date = new Date(d);
      console.log(date);
      return  date.getDate() + ' ' + months[date.getMonth()] + ', ' + date.getFullYear();
    });
    // chart.x2Axis.tickFormat(d3.format(',f'));
//
//    chart.yAxis.tickFormat(d3.format(',.2f'));
//    chart.y2Axis.tickFormat(d3.format(',.2f'));

    // exec
    d3.select('#chart-history svg')
      .datum(data)
      .transition().duration(500)
      .call(chart);

    //
    nv.utils.windowResize(chart.update);

    return chart;
  });
}

function normalize_data(data, series, xAxis, xAxis_convert)
{
  var sort = crossfilter.quicksort.by(function(d) { return d[xAxis].getTime(); });
  var sorted = sort(data, 0, data.length);

  var result = [];

  series.forEach(function(serie, index)
  {
    result.push({key: serie.name, values: [], color: serie.color});
  });

  data.forEach(function(data, dataIndex)
  {
    series.forEach(function(serie, serieIndex)
    {
      result[serieIndex].values.push({x: data[xAxis],  y: data[serie.key]});
    });
  });

  return result;
};


