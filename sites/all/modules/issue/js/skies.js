/**
 * Skies theme for Highcharts JS
 * @author Torstein Hønsi
 */

Highcharts.theme = {
	colors: ["#514F78", "#42A07B", "#9B5E4A", "#72727F", "#1F949A", "#82914E", "#86777F", "#42A07B"],
	chart: {
		className: 'skies',
		borderWidth: 0,
		plotShadow: false,
		plotBackgroundColor: {
			linearGradient: [0, 0, 250, 500],
			stops: [
				[0, 'rgba(255, 255, 255, 1)'],
				[1, 'rgba(255, 255, 255, 0)']
			]
		},
		plotBorderWidth: 1,
                shadow: true
	},
	title: {
		style: { 
			color: '#3E576F',
			font: '16px Helvetica, sans-serif'
		}
	},
	subtitle: {
		style: { 
			color: '#6D869F',
			font: '12px Helvetica, sans-serif'
		}
	},
	xAxis: {
		gridLineWidth: 0,
		lineColor: '#C0D0E0',
		tickColor: '#C0D0E0',
		labels: {
			style: {
				color: '#666',
				rotation: 90,
				fontWeight: 'bold'
			}
		},
		title: {
			style: {
				color: '#666',
				font: '12px Helvetica, sans-serif'
			}				
		}
	},
	yAxis: {
		alternateGridColor: 'rgba(255, 255, 255, .5)',
		lineColor: '#C0D0E0',
		tickColor: '#C0D0E0',
		tickWidth: 1,
		labels: {
			style: {
				color: '#666',
				fontWeight: 'bold'
			}
		},
		title: {
			style: {
				color: '#666',
				font: '12px Helvetica, sans-serif',
				enabled: null
			}				
		}
	},
	legend: {
     layout: 'horizontal',
     align: 'right',
     verticalAlign: 'bottom',
     x: 0,
     y: 0,
     borderWidth: 0,
     floating: true
  },
	labels: {
		style: {
			color: '#3E576F'
		}
	}
};

// Apply the theme
var highchartsOptions = Highcharts.setOptions(Highcharts.theme);
