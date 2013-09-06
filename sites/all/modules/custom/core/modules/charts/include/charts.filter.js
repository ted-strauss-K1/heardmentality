/**
 *
 */
$(function () {
  if (Drupal.settings.charts.vote) init_highchart('');
});

/**
 *
 */
$('#filter').live("change", function () {
  init_highchart($(this).val());
});

/**
 *
 * @param arg
 */
function init_highchart(arg) {
  var js_data = Drupal.settings.charts.filter[arg];

  var data = [];
  for (var i=0; i<Drupal.settings.charts.count; i++) {

    var data_item = {
      key : i,
      color : Drupal.settings.charts.colors[i],
      values: []
    };

    for (var j in js_data['#options']) {
      data_item['values'].push({
        label : js_data['#options'][j],
        value : js_data['#results'][i][j]
      });
    }

    data.push(data_item);
  }

  //
  console.log(js_data);
  console.log(data);

  var chart;
  nv.addGraph(function() {
    chart = nv.models.multiBarHorizontalChart()
      .x(function(d) { return d.label })
      .y(function(d) { return d.value })
      .margin({top: 0, right: 20, bottom: 20, left: 80})
      .transitionDuration(250)
      .showControls(false)
      .showLegend(false);
      // .staggerLabels(true);

    d3.select('#chart-filter svg')
      .datum(data)
      .call(chart);

    var insertLinebreaks = function (d) {
      var el = d3.select(this);
      var words = d.split(' ');
      el.text('');

      for (var i = 0; i < words.length; i++) {
        var tspan = el.append('tspan').text(words[i]);
        if (i > 0)
          tspan.attr('x', 0).attr('dy', '15');
      }
    };

    d3.selectAll('g.x.axis g text').each(insertLinebreaks);

    nv.utils.windowResize(chart.update);

    return chart;
  });
}

long_short_data = [
  {
    key: 'Series1',
    color: '#d62728',
    values: [
      {
        "label" : "Group A" ,
        "value" : -1.8746444827653
      } ,
      {
        "label" : "Group B" ,
        "value" : -8.0961543492239
      } ,
      {
        "label" : "Group C" ,
        "value" : -0.57072943117674
      } ,
      {
        "label" : "Group D" ,
        "value" : -2.4174010336624
      } ,
      {
        "label" : "Group E" ,
        "value" : -0.72009071426284
      } ,
      {
        "label" : "Group F" ,
        "value" : -0.77154485523777
      } ,
      {
        "label" : "Group G" ,
        "value" : -0.90152097798131
      } ,
      {
        "label" : "Group H" ,
        "value" : -0.91445417330854
      } ,
      {
        "label" : "Group I" ,
        "value" : -0.055746319141851
      }
    ]
  },
  {
    key: 'Series2',
    color: '#1f77b4',
    values: [
      {
        "label" : "Group A" ,
        "value" : 25.307646510375
      } ,
      {
        "label" : "Group B" ,
        "value" : 16.756779544553
      } ,
      {
        "label" : "Group C" ,
        "value" : 18.451534877007
      } ,
      {
        "label" : "Group D" ,
        "value" : 8.6142352811805
      } ,
      {
        "label" : "Group E" ,
        "value" : 7.8082472075876
      } ,
      {
        "label" : "Group F" ,
        "value" : 5.259101026956
      } ,
      {
        "label" : "Group G" ,
        "value" : 0.30947953487127
      } ,
      {
        "label" : "Group H" ,
        "value" : 0
      } ,
      {
        "label" : "Group I" ,
        "value" : 0
      }
    ]
  },
  {
    key: 'Series3',
    color: '#2ca02c',
    values: [
      {
        "label" : "Group A" ,
        "value" : -25.307646510375
      } ,
      {
        "label" : "Group B" ,
        "value" : 16.756779544553
      } ,
      {
        "label" : "Group C" ,
        "value" : -18.451534877007
      } ,
      {
        "label" : "Group D" ,
        "value" : 8.6142352811805
      } ,
      {
        "label" : "Group E" ,
        "value" : -7.8082472075876
      } ,
      {
        "label" : "Group F" ,
        "value" : 5.259101026956
      } ,
      {
        "label" : "Group G" ,
        "value" : -0.30947953487127
      } ,
      {
        "label" : "Group H" ,
        "value" : 0
      } ,
      {
        "label" : "Group I" ,
        "value" : 0
      }
    ]
  }
];
