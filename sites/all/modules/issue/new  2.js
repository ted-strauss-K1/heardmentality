				chart = new Highcharts.Chart({
					chart: {
						renderTo: 'chart_div',
						borderColor: '#ffffff',
						borderRadius: 0,
						borderWidth: 0,
						defaultSeriesType: 'bar',
						plotBorderColor: '#fff',
						plotBorderWidth: 0,
						style: {
							fontFamily: 'Arial',
							color: '#4c4c4c'
						}
                                               
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

					xAxis: {
						categories: " . json_encode($ans_array) . ",
						gridLineColor: '#ccc',
						gridLineWidth: 1,
						lineColor: '#4c4c4c',
						lineWidth: 1,
						tickColor: '#fff',
						tickWidth: 0
					}},
					
					yAxis: {tickInterval  :1,
						min: 0,
						title: {
							text: ''
						},
                                                labels :{ style: {
                   font: '12px Arial,Helvetica,sans-serif '
               }}},
					legend: {
						backgroundColor: '#FFFFFF',
						reversed: false
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
                                        
				      series: [" . $inc . " ]
				});
				
				
				
				
				chart = new Highcharts.Chart({
					chart: {
						renderTo: 'chart_div',
						defaultSeriesType:'bar',
						borderColor: '#ffffff',
						borderRadius: 0,
						borderWidth: 0,
						plotBorderColor: '#fff',
						plotBorderWidth: 0,
						style: {
							fontFamily: 'Arial',
							color: '#4c4c4c'
						}
                                               
					},
					
					title: {
						text: false
					},
					
					xAxis: {
						categories: " . json_encode($ans_array) . "
					},
					
					yAxis: {
						tickInterval  :1,
						min: 0,
						title: {
							text: ''
						},
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
                                        
				      series: [" . $inc . " ]
				});
				
				
				
				
									tooltip: {
						formatter: function() {
							return ''+
								 this.series.name +': '+ this.y +'';
						}
					},
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					
					  chart = new Highcharts.Chart({
      chart: {
         renderTo: 'container_graph',
         defaultSeriesType: 'spline',
         zoomType: 'x',
        
      },
      title: {
         text: ''
      },
      subtitle: {
         text: ''
      },
      xAxis: {
        labels: {
                style: {
                        color: '#666',
                        fontWeight: 'normal',
                        font: '10px Arial,Helvetica,sans-serif '

                },
                        rotation:270
		},
         type: 'datetime',
       plotBands: [{ // mark the weekend
            from: " . $sdate . ",
            to: " . $edate . "
        }] " . $tickint . "
      },
      yAxis: {
         title: {
            text: 'No Of Votes (Per Day)'
         },
         labels: {
                style: {
                        color: '#666',
                        fontWeight: 'normal',
                        font: '10px Arial,Helvetica,sans-serif '

                }
		},
         min: 0,
         minorGridLineWidth: 0,

         gridLineWidth: 0,
         alternateGridColor: null,
         tickInterval  :1
      },
      tooltip: {
         formatter: function() {
                   return ''+

               Highcharts.dateFormat('%e. %b %Y', this.x) +': '+ this.y +' Votes';
         }
      },
      plotOptions: {
          series: {
            cursor: 'pointer',
            point: {
                events: {
                    click: function() {
                       display_resource(this.category);
                    }
                }
            }
        },
         spline: {
            lineWidth: 4,
            states: {
               hover: {
                  lineWidth: 5
               }
            },
            marker: {
               enabled: false,
               states: {
                  hover: {
                     enabled: true,
                     symbol: 'circle',
                     radius: 5,
                     lineWidth: 1
                  }
               }
            },
            pointInterval: 24 * 3600 * 1000, // one day
            pointStart:" . $sdate . "
            }
      },
      series: [" . $insdata . "]
   });
