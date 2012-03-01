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
		backgroundColor: "#EEEEEE",
		plotBackgroundColor: "#EEEEEE",
		plotBorderWidth: 0,
      shadow: false
	},
	chart: {
    animation: true,
    backgroundColor: "eee",
    className: "",
    height: 200,
  }, 
  legend: {
    backgroundColor: null,
    borderColor: #EEEEEE,
    margin: 0
  }
};

// Apply the theme
var highchartsOptions = Highcharts.setOptions(Highcharts.theme);
