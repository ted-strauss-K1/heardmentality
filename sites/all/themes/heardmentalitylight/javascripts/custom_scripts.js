$(document).ready(function() {

	// Initialization jscrollpane
	
	jQuery(function()
	{
		if (navigator.userAgent.indexOf('iPhone') != -1 || navigator.userAgent.indexOf('iPad') != -1 || navigator.userAgent.indexOf('Blackberry') != -1 || navigator.userAgent.indexOf('Android') != -1 || $('body').hasClass('screen_wide') || $('body').hasClass('screen_wide')) {
			jQuery('.container .nine .grey-box .uactivity').jScrollPane({scrollbarWidth:18, scrollbarMargin:0, showArrows:true});
		}	
	});
	
	jQuery(function()
	{
			var height = jQuery('.container .nine .grey-box .uactivity').height();
			
			if (height=='795px') {
				jQuery('.container .nine .grey-box .uactivity').jScrollPane({scrollbarWidth:18, scrollbarMargin:0, showArrows:true});
			}

	});


});


