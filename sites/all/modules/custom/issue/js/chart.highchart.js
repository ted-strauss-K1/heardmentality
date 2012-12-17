function initialize_highchart(arg) {
  var data = Drupal.settings.charts.highchart[arg];
  console.log(data);

  var selector = '#chart_div';
  var seriesOptions = [];
  var categories = data['#options'];
  var count = Drupal.settings.charts.count;
  for (var i = 0; i < count; i++) {
    if (arg == '') {
      var temp = {};
      temp.name = data['#name'];
      temp.data = [];
      for (var j = 0; j < count; j++) {
        temp.data.push({
          "y":data['#results'][j][j],
          "color":Drupal.settings.charts.colors[j]
        });

        //colors: Drupal.settings.charts.colors,
      }

      seriesOptions[i] = temp;
      break;
    }
    seriesOptions[i] = {
      name:Drupal.settings.charts.choices[i],
      data:data['#results'][i]
    };
  }
  $(selector).empty();
  console.log(seriesOptions);

  initialize_highchart_create(seriesOptions, categories, arg);
}

function initialize_highchart_create(seriesOptions, categories, arg) {

  $(seriesOptions).map(function (index, element) {
    if (element == 0) {
      seriesOptions[index] = '-';
    }
  });

  $(seriesOptions).map(function (index, element) {
    $(element.data).map(function (index1, element1) {
      if (element1 == 0) {
        seriesOptions[index].data[index1] = null;
      }
    });
  });

  var chart;

  chart = new Highcharts.Chart({
    chart:{
      renderTo:'chart_div',
      type:'bar',
      style:{
        fontFamily:'Arial',
        color:'#fff',
        fontSize:'12px'
      },
      plotBorderColor:'#fff',
      plotBorderWidth:0,
      borderColor:'#fff',
      borderRadius:0,
      borderWidth:0,
      marginTop:20,
      marginRight:20,
      marginBottom:20,
      ignoreHiddenSeries:true,
      zoomType:'y'
    },
    title:{
      text:null
    },
    xAxis:{
      categories:categories,
      title:{
        text:null
      },
      lineColor:'#4c4c4c',
      lineWidth:1,
      minPadding:0.02,
      endOnTick:false,
      tickColor:'#000',
      tickLength:3,
      tickWidth:1,
      tickmarkPlacement:'on',
      startOnTick:false,
      labels:{
        align:'right',
        staggerLines:2,
        style:{
          color:'#4c4c4c',
          font:'11px Aial, sans-serif'
        }
      }
    },
    yAxis:{
      min:0,
      title:{
        text:'null'
      },
      endOnTick:false,
      maxPadding:0.01,
      lineWidth:0,
      gridLineColor:'#ccc',
      tickmarkPlacement:'on',
      tickColor:'#fff',
      tickWidth:1,
      tickLength:5
    },
    colors:Drupal.settings.charts.colors,
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
      bar:{
        dataLabels:{
          enabled:false
        },
        borderColor:'#fff',
        borderWidth:0,
        shadow:false,
        groupPadding:0.15,
        pointPadding:0
        //pointWidth: 20
      }
    },
    credits:{
      enabled:false
    },
    series:seriesOptions
  });
}

$(function () {
  initialize_highchart('');
  $('#filter').live("change", function () {
    initialize_highchart($(this).val());
  });
});

