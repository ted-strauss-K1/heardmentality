$(document).ready(function(){
	$(window).scroll(function () { 
		hash:true;
	
  		var scrollTopPosition = ($(window).scrollTop() + 300);		
		var headerSpace = ($("#header_about").offset().top + $("#header_about").height());
		var aboutSpace = ($("#about").offset().top + $("#about").height());
  		var associatesSpace = ($("#associates").offset().top + $("#associates").height());
  		var organizationSpace = ($("#organization").offset().top + $("#organization").height());
  		var guideSpace = ($("#guide").offset().top + $("#guide").height());  	
		
		// div#navigation and div.subnav
		
		if ((headerSpace <= scrollTopPosition) && (scrollTopPosition <= aboutSpace)){
			$(".nav0 a").addClass('ab-select');			
		} else {
			$(".nav0 a").removeClass('ab-select');			
		}
		
		if ((aboutSpace <= scrollTopPosition) && (scrollTopPosition <= associatesSpace)){
			$(".nav1 a").addClass('ab-select');			
		} else {
			$(".nav1 a").removeClass('ab-select');			
		}
		
		if ((associatesSpace < scrollTopPosition) && (scrollTopPosition <= organizationSpace)) {
			$(".nav2 a").addClass('ab-select');			
		} else {
			$(".nav2 a").removeClass('ab-select');			
		}
		
		if ((organizationSpace < scrollTopPosition) && (scrollTopPosition <= guideSpace)) {
			$(".nav3 a").addClass('ab-select');			
		} else {
			$(".nav3 a").removeClass('ab-select');			
		}
	});

});

jQuery(function( $ ){
	$.localScroll.hash({
		offset: -67,
		duration:1500
	});
	

	$.localScroll({
		duration:1500,
		hash:true,
		offset: -67,
		onBefore:function( e, anchor, $target ){
			// The 'this' is the settings object, can be modified
		},
		onAfter:function( anchor, settings ){
			// The 'this' contains the scrolled element (#content)
		}
	});
	
	
});


