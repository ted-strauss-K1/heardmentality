$('#deb-ana').live('click', function () {
  chartStrength(Drupal.settings.charts.strength, Drupal.settings.charts.choices);
});

function chartStrength(data, categories) {
  var dataset = [];

  var chart;
  chart = new Highcharts.Chart({
    chart:{
      renderTo:'load-deb-statics',
      defaultSeriesType:'column',
      style:{
        fontFamily:'Arial',
        color:'#4c4c4c',
        fontSize:'12px'
      },
      plotBorderColor:'#fff',
      plotBorderWidth:0,
      borderColor:'#fff',
      borderRadius:0,
      borderWidth:0,
      marginTop:10,
      marginRight:20,
      marginBottom:80,
      marginLeft:30,
      ignoreHiddenSeries:true
    },
    title:{
      text:null
    },
    xAxis:{
      categories:categories,
      title:{
        text:null
      },
      lineColor:'#ccc',
      lineWidth:1,
      endOnTick:false,
      tickColor:'#ccc',
      tickWidth:1,
      tickLength:5,
      gridLineColor:'#ccc',
      tickmarkPlacement:'on',
      startOnTick:false,
      labels:{
        style:{
          color:'#4c4c4c',
          font:'12px Aial, sans-serif'
        }
      }
    },
    yAxis:{
      tickInterval:1,
      title:{
        text:null
      },
      endOnTick:false,
      maxPadding:0.01,
      lineWidth:1,
      lineColor:'#ccc',
      tickmarkPlacement:'on',
      tickColor:'#ccc',
      tickWidth:1,
      tickLength:5
    },
    legend:{
      enabled:false
    },
    tooltip:{
      formatter:function () {
        return '' +
          this.series.name + ': ' + this.y + '';
      },
      shadow:false,
      style:{
        color:'#4c4c4c',
        font:'12px Aial, sans-serif'
      },
      borderRadius:3
    },
    plotOptions:{
      column:{
        dataLabels:{
          enabled:false
        },
        borderColor:'#fff',
        borderWidth:0,
        shadow:false,
        groupPadding:0.15,
        pointPadding:0
      }
    },
    credits:{
      enabled:false
    },
    series:[
      {
        name:'Strength',
        data:data
      }
    ]
  });
}