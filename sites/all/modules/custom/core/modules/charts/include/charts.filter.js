/**
 *
 */
$(function () {
  if (Drupal.settings.charts.vote) init_filter('');
});

/**
 *
 */
$('#filter').live("change", function () {
  init_filter($(this).val());
});

/**
 * @param arg
 */
function init_filter(arg) {
  // empty placeholder
  $('#chart-filter svg').empty();

  // get data
  var js_data = Drupal.settings.charts.filter[arg];

  // get svg
  var svg = d3.select("#chart-filter svg");

  // get data
  var data = [];

  // columns
  var x_label = "Votes", y_label = "", options = js_data['#options'];

  // collect data
  if (!arg) {
    y_label = "Choice";
    for (var i in Drupal.settings.charts.choices) {
      data.push({
        "Votes"  : js_data['#results'][i][i],
        "Choice" : Drupal.settings.charts.choices[i]
      });
    }
  }
  else {
    y_label = js_data['#name'];
    for (var i in Drupal.settings.charts.choices) {
      for (var j in js_data['#options']) {
        var data_item = {
          "Votes"  : js_data['#results'][i][j],
          "Choice" : Drupal.settings.charts.choices[i]
        };
        data_item[y_label] = js_data['#options'][j];
        data.push(data_item);
      }
    }
  }

  // default margins
  var margin = 8;
  var legend = 50;

  // detect the sizes of options
  var max_label_length = 0;
  for (var j in options) {
    max_label_length = Math.max(max_label_length, (options[j]).length);
  }

  // change default margins
  margin = 30 + 5 * max_label_length;
  if (margin > 120) {
    margin = 120;
  }
  legend = 20 + 5*(options.length + options.length%2);

  var chart = new dimple.chart(svg, data);
  chart.setBounds(margin, legend, 300-margin, 240 - legend)
  var x_axis = chart.addMeasureAxis("x", x_label);
  var y_axis = chart.addCategoryAxis("y", y_label);
  chart.addSeries(y_label, dimple.plot.bar);
  chart.addLegend(0, 10, 315, 30, "right");

  chart.draw();
}


/**
 *
 * @param arg
 */
function init_filter_old(arg) {
  var js_data = Drupal.settings.charts.filter[arg];

  var data = [];
  var max_label_length = 0;

  //
  if (arg) {
    for (var i = 0; i < Drupal.settings.charts.count; i++) {

      var data_item = {
        key   : "Series " + i,
        color : Drupal.settings.charts.colors[i],
        values: []
      };

      for (var j in js_data['#options']) {
        data_item['values'].push({
          label: js_data['#options'][j],
          value: js_data['#results'][i][j]
        });

        max_label_length = Math.max(max_label_length, (js_data['#options'][j]).length);
      }

      data.push(data_item);
    }
  }

  //
  else {
    var data_item = {
      key   : 0,
      // color : Drupal.settings.charts.colors[0],
      values: []
    };

    for (var i = 0; i < Drupal.settings.charts.count; i++) {
      data_item['values'].push({
        label: js_data['#options'][i],
        value: js_data['#results'][i][i],
        color: Drupal.settings.charts.colors[i]
      });

      max_label_length = Math.max(max_label_length, (js_data['#options'][i]).length);
    }

    data.push(data_item);
  }

  $('#chart-filter svg').empty();

  var chart;
  nv.addGraph(function () {
    chart = nv.models.multiBarHorizontalChart()
      .x(function (d) {
        return d.label
      })
      .y(function (d) {
        return d.value
      })
      .margin({top: 0, right: 20, bottom: 20, left: 20 + 5 * max_label_length})
      .showLegend(false)
      .showControls(false);

    if (!arg) chart.barColor(d3.scale.category20().range());

    d3.select('#chart-filter svg')
      .datum(data)
      .call(chart);

    nv.utils.windowResize(chart.update);

    return chart;
  });
}
