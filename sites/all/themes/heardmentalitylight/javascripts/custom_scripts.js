$(document).ready(function() {

	// Initialization jscrollpane
	
	jQuery(function()
	{
			var height = jQuery('.container .nine .grey-box .uactivity').height();
			
			if (height==795) {
				jQuery('.container .nine .grey-box .uactivity').jScrollPane({scrollbarWidth:18, scrollbarMargin:0, showArrows:true});
			}

	});


});


