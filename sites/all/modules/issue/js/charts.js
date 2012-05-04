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
  
  $(function () {
    var chart = new Highcharts.Chart({
        chart: {
            renderTo: 'container',
            defaultSeriesType: 'bar'
        },
        xAxis: {
            categories: ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec']
        },
        yAxis: {   
        },
        legend: {
            layout: 'vertical',
            floating: true,
            backgroundColor: '#FFFFFF',
            align: 'right',
            verticalAlign: 'top',
            y: 60,
            x: -60
        },
        tooltip: {
            formatter: function() {
                return '<b>'+ this.series.name +'</b><br/>'+
                    this.x +': '+ this.y;
            }
        },
        plotOptions: {
        },
        series: [{
            data: [29.9, 71.5, 106.4, 129.2, 144.0, 176.0, 135.6, 148.5, 216.4, 194.1, 95.6, 54.4]        
        }]
    });
});
  
  /*function createMainChart(seriesOptions, categories) {

	$(seriesOptions).map(function(index, element) {
		if (element == 0) {
		  seriesOptions[index] = null;
		}
	});

    //alert('hello');
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
        categories: categories,
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
	  
      credits: {
        enabled: false
      },  
                             
      series: seriesOptions
    });
  }*/
}

$(function() {
  var arg = $('#dochg').val();
  load_chart(arg);
  $('#dochg').live("change", function(){
    load_chart($(this).val());
  //return false;
  });
  
});