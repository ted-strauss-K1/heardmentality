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
      var sdate = data.date;
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
  
function load_chart(arg) {
  var chart, seriesCounter = 0;
  var seriesOptions = [];
  var count = $('#tot_ans').val();
  var values = [];
  for (var i = 0; i < count; i++) {
    values[i] = i;
  }
  $('#chart_div').empty();
  var nid = $('#curr_nid').val();
  
  $.each(values, function(i, value) {
    $.getJSON('/issue/highchart/ajax/'+ nid +'/'+ value + '?dochg=' + arg, function(data) {
      var categories = data.categories;
      seriesOptions[i] = {
        name: data.name,
        data: data.data
      };
      seriesCounter++;

      if (seriesCounter == count) {
        createMainChart(seriesOptions,categories);
      }
    });
  });
  
  
  function createMainChart(seriesOptions, categories) {
    /*
	$(seriesOptions).map(function(index, element) {
		if (element == 0) {
		  seriesOptions[index] = null;
		}
	});
	*/
    //alert('hello');
    chart = new Highcharts.Chart({
      chart: {
        renderTo: 'chart_div',
        type:'bar'
      },
					
      title: {
        text: null
      },

      xAxis: {
        categories: categories
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
          }
        }
      },
      credits: {
        enabled: false
      },                               
      series: seriesOptions
    });
  }
}

$(function() {
  var arg = $('#dochg').val();
  load_chart(arg);
  $('#dochg').live("change", function(){
    load_chart($(this).val());
  //return false;
  });
  
});