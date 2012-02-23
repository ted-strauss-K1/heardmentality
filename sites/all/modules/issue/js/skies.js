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
				[0, 'rgba(1, 1, 255, 1)'],
				[1, 'rgba(255, 1, 1, 0)']
			]
		},
		plotBorderWidth: 1,
                shadow: true
	}
};

// Apply the theme
var highchartsOptions = Highcharts.setOptions(Highcharts.theme);
