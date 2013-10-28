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
 *
 * @param arg
 */
function init_filter(arg) {
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

    console.log(JSON.stringify(data));
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
