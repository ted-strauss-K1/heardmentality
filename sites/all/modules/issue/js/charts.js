$(function() {
  // $('#results').click(function(){
  /*    $.getJSON('/issue/highstock/ajax/2242', function(data) {
        // Create the chart
        window.chart = new Highcharts.StockChart({
            chart : {
                renderTo : 'container_graph'
            },

            rangeSelector : {
                selected : 1
            },

            title : {
                text : 'AAPL Stock Price'
            },
            
            series : [{
                name : 'AAPL',
                data : [7,6, 0, 8],
                tooltip: {
                    valueDecimals: 2
                }
            }]
        });
    });*/
  
  var count = $('#tot_ans').val();
  var values = [];
  for (var i = 0; i < count; i++) {
    values[i] = i;
  }
  var seriesOptions = [],
  yAxisOptions = [],
  seriesCounter = 0,
  
  colors = Highcharts.getOptions().colors;
  $.each(values, function(i, value) {

    $.getJSON('/issue/highstock/ajax/2242/'+ value, function(data) {

      seriesOptions[i] = {
        name: data.name,
        data: data.data
      };
      // As we're loading the data asynchronously, we don't know what order it will arrive. So
      // we keep a counter and create the chart when all the data is loaded.
      seriesCounter++;

      if (seriesCounter == count) {
        createChart();
      }
    });
  });
  function createChart() {
    console.log(seriesOptions);
    chart = new Highcharts.StockChart({
      chart: {
        renderTo: 'container_graph'
      },

      rangeSelector: {
        selected: 1
      },
           
      plotOptions: {
        series: {
          compare: 'value',
          pointStart: Date.UTC(2012, 3, 1),
          pointInterval: 3600 * 1000 * 24
        }
      },
            
      /*    tooltip: {
        pointFormat: '<span style="color:{series.color}">{series.name}</span>: <b>{point.y}</b> ({point.change}%)<br/>',
        valueDecimals: 0 
      }, */
      series: seriesOptions
    });
  }
// });
});