function initialize_highstock(seriesOptions, sdate) {
  var chart = new Highcharts.StockChart({
    chart: {
      renderTo: 'container_graph',
      type: 'spline',
      style: {
        fontFamily: 'Arial',
        color: '#4c4c4c',
        fontSize: '12px'
      },
      plotBorderColor: '#fff',
      plotBorderWidth: 0,
      borderColor: '#fff',
      borderRadius: 0,
      borderWidth: 0,
      marginTop: 15,
      marginRight: 20,
      marginBottom: 15,
      marginLeft: 20,
      ignoreHiddenSeries: true
    },
    title: {
      text: null
    },
    xAxis: {
      title: {
        text: null
      },
      lineColor: '#4c4c4c',
      lineWidth: 1,
      endOnTick: false,
      tickColor: '#fff',
      tickWidth: 0,
      tickmarkPlacement: 'on',
      startOnTick: false,
      labels: {
        style: {
          color: '#4c4c4c',
          font: '12px Aial, sans-serif'
        }
      }
    },
    yAxis: {
      labels: {
        formatter: function() {
          return this.value;
        }
      },
      title: {
        text: null
      },
      endOnTick: false,
      maxPadding: 0.01,
      lineWidth: 0,
      gridLineColor: '#ccc',
      tickmarkPlacement: 'on',
      tickColor: '#fff',
      tickWidth: 1,
      tickLength: 5
    },
    scrollbar : {
      enabled : true,
      barBackgroundColor: '#D7D7D7',
      barBorderRadius: 7,
      barBorderWidth: 0,
      buttonBackgroundColor: '#D7D7D7',
      buttonBorderWidth: 0,
      buttonBorderRadius: 7,
      trackBackgroundColor: 'none',
      trackBorderWidth: 1,
      trackBorderRadius: 8,
      trackBorderColor: 'none'
    },
    rangeSelector: {
      enabled: false
    },
    navigator: {
      enabled: true,
      height: 30,
      margin: 30,
      maskFill: 'rgba(228, 228, 228, 0.6)',
      handles: {
        backgroundColor: '#D7D7D7',
        borderColor: '#777777'
      },
      outlineColor: '#D7D7D7',
      outlineWidth: 2,
      series: {
        color: '#6ccbd5',
        lineWidth: 0
      }
    },
    colors: Drupal.settings.charts.colors,
    legend: {
      enabled: false
    },
    credits: {
      enabled: false
    },
    plotOptions: {
      series: {
        pointStart: Date.UTC(sdate.year, sdate.month, sdate.day),
        pointInterval: 3600 * 1000 * 24
      },
      shadow: false
    },
    tooltip: {
      shadow: false,
      style: {
        font: '12px Aial, sans-serif'
      },
      borderRadius: 3,
      backgroundColor: {
        linearGradient: {
          x1: 0,
          y1: 0,
          x2: 0,
          y2: 1
        },
        stops: [
          [0, '#fff'],
          [1, '#f2f2f2']
        ]
      },
      borderColor: '#ccc',
      borderWidth: 2
    },
    series: seriesOptions
  });

}

$(function() {
  var count = Drupal.settings.charts.count;
  var sdate = Drupal.settings.charts.highstock.date;
  var seriesOptions = [];
  for (var i = 0; i < count; i++) {
    seriesOptions[i] = Drupal.settings.charts.highstock['choice'+i];
  }
  initialize_highstock(seriesOptions,sdate);
});