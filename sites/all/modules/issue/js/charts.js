$(function() {
  var count = $('#tot_ans').val(),
  nid = $('#curr_nid').val();
  var values = [];
  for (var i = 0; i < count; i++) {
    values[i] = i;
  }
  var seriesOptions = [],
  yAxisOptions = [],
  seriesCounter = 0,
  colors = Highcharts.getOptions().colors;
  
  $.each(values, function(i, value) {
    $.getJSON('/issue/highstock/ajax/'+ nid +'/'+ value, function(data) {
      var sdate = data.date
      seriesOptions[i] = {
        name: data.name,
        data: data.data
      };
      seriesCounter++;

      if (seriesCounter == count) {
        createChart(seriesOptions,sdate);
      }
    });
  });
  
  function createChart(seriesOptions, sdate) {
    console.log(sdate);
    var chart = new Highcharts.StockChart({
      chart: {
        renderTo: 'container_graph'
      }, 
      yAxis: {
        labels: {
          formatter: function() {
            return this.value;
          }
        }
      },
      plotOptions: {
        series: {
          pointStart: Date.UTC(sdate.year, sdate.month, sdate.day),
          pointInterval: 3600 * 1000 * 24
        }
      },
      series: seriesOptions
    });
  }
});
  
  
$(function() {
  var chart;
  chart = new Highcharts.Chart({
    chart: {
      renderTo: 'chart_div',
      defaultSeriesType:'bar',
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
      marginTop: 20,
      marginRight: 20,
      marginBottom: 20,
      ignoreHiddenSeries: true,
      zoomType: 'y'
    },
					
    title: {
      text: null
    },

    xAxis: {
      categories: " . json_encode($ans_array) . ",
      title: {
        text: " . $xtitle . ",
        margin:70
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
      tickInterval: 1,
      min: 0,
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
					
    colors: [
    '#934d9e', 
    '#FF7F00', 
    '#50c0ac', 
    '#0c6926', 
    '#ef4c8d', 
    '#362750', 
    '#e1e43c', 
    '#ef3d3b', 
    '#3cc7f4',
    '#589a1c', 
    '#C2499B', 
    '#f89521', 
    '#CC2027', 
    '#55ba59', 
    '#d5bc29', 
    '#6ccbd5',
    '#43B649',
    '#F6EB16'
    ],
					
    legend: {
      enabled: false
    },
					
    tooltip: {
      formatter: function() {
        return ''+
        this.series.name +': '+ this.y +'';
      },
      shadow: false,
      style: {
        color: '#4c4c4c',
        font: '12px Aial, sans-serif'
      },
      borderRadius: 3
    },
					
    plotOptions: {
      bar: {
        dataLabels: {
          enabled: true
        },
        borderColor: '#fff',
        borderWidth: 0,
        shadow: false,
        groupPadding: 0.15,
        pointPadding: 0
      //pointWidth: 20
      }
    },
                                        
    series: [" . $inc . " ]
  });
});