$(function() {
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
      seriesCounter++;

      if (seriesCounter == count) {
        createChart(seriesOptions);
      }
    });
  });
  
  function createChart(seriesOptions) {
    console.log(seriesOptions);
    var chart = new Highcharts.StockChart({
      chart: {
        renderTo: 'container_graph'
      },
  /*    yAxis: {
        labels: {
          formatter: function() {
            return (this.value > 0 ? '+' : '') + this.value;
          }
        },
        plotLines: [{
          value: 0,
          width: 2,
          color: 'silver'
        }]
      },
*/
    /*  rangeSelector: {
        selected: 1
      },
      */     
      plotOptions: {
        series: {
          compare: 'value',
          pointStart: Date.UTC(2012, 3, 1),
          pointInterval: 3600 * 1000 * 24
        }
      },
            
      tooltip: {
        pointFormat: '<span style="color:{series.color}">{series.name}</span>: <b>{point.y}</b> ({point.change})<br/>',
        valueDecimals: 0 
      }, 
      series: seriesOptions
    });
  }
});