$(function() {
$('#debate_statistic').live(function() {
  //console.log('dfgf');
  var nid = $('#curr_nid').val();
  $.getJSON(Drupal.settings.base_url + '/debate/ajax/'+ nid +'/'+ '?action=analysis', function(data) {
    var chart;
    console.log(data);
    chart = new Highcharts.Chart({
      chart: {
        renderTo: 'container',
        defaultSeriesType: 'column',
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
        marginTop: 10,
        marginRight: 20,
        marginBottom: 80,
        marginLeft: 30,
        ignoreHiddenSeries: true
      },
      title: {
        text: null
      },
	  
      xAxis: {
       // categories:"",
        title: {
          text: null
        },
        lineColor: '#ccc',
        lineWidth: 1,
        endOnTick: false,
        tickColor: '#ccc',
        tickWidth: 1,
        tickLength: 5,
        gridLineColor: '#ccc',
        tickmarkPlacement: 'on',
        startOnTick: false,
        labels: {
          style: {
            color: '#4c4c4c',
            font: '12px Aial, sans-serif'	
          }
        }
      },
	  
      yAxis:{ 
        tickInterval: 1,
        title: {
          text: null
        },
        endOnTick: false,
        maxPadding: 0.01,
        lineWidth: 1,
        lineColor: '#ccc',
        tickmarkPlacement: 'on',
        tickColor: '#ccc',
        tickWidth: 1,
        tickLength: 5
      },
	
      colors: [
      '#55BA59', 
      '#C2499B'
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
        column: {
          dataLabels: {
            enabled: false
          },
          borderColor: '#fff',
          borderWidth: 0,
          shadow: false,
          groupPadding: 0.15,
          pointPadding: 0
        }
      },
	  
      credits: {
        enabled: false
      },
      series: [{
        name: 'Strength',
        data: data
      }]
    });
  });
  });
});