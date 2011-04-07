/**
 * @author gobinath.m
 */
		
			var chart;
			$(document).ready(function() {
				chart = new Highcharts.Chart({
					chart: {
						renderTo: 'chart_div',
						defaultSeriesType: 'bar'
					},
					title: {
						text: 'Stacked bar chart'
					},
					xAxis: {
						categories: ['Apples', 'Oranges', 'Pears', 'Grapes', 'Bananas']
					},
					yAxis: {
						min: 0,
						title: {
							text: 'Total fruit consumption'
						}
					},
					legend: {
						backgroundColor: '#FFFFFF',
						reversed: true
					},
					tooltip: {
						formatter: function() {
							return ''+
								 this.series.name +': '+ this.y +'';
						}
					},
					plotOptions: {
						series: {
							stacking: 'normal'
						}
					},
				        series: [{
						name: 'John',
						data: [5, 3, 4, 7, 2]
					}]
				});
				
				
			});
				
		