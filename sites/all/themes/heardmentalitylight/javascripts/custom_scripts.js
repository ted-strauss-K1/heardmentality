window.onload = setScreenClass;
window.onresize = setScreenClass;
// Following transition classes will be declared:
//
// classname screenwidth
// ------------------------------------------
// pda_v 240px
// pda_h 320px
// ultralow 320px - 640px
// screen_lo 640px - 800px
// screen_med 800px - 1024px
// screen_hi 1024px - 1280px
// screen_wide > 1280px
function setScreenClass(){
var fmt = document.documentElement.clientWidth;
var cls = (fmt<=240)?'pda_ver':(fmt>240&&fmt<=320)?'pda_hor':(fmt>320&&fmt<=640)?'screen_ultralow':(fmt>640&&fmt<=800)?'screen_low':(fmt>800&&fmt<=1024)?'screen_med':(fmt>1024&&fmt<=1280)?'screen_high':'screen_wide';
//document.getElementById('count').innerHTML=fmt+'px -> '+cls;
document.body.className=cls;
};

$(document).ready(function() {

	// Initialization jscrollpane
	
	jQuery(function()
	{
		if (!navigator.userAgent.indexOf('iPhone') != -1 || !navigator.userAgent.indexOf('iPad') != -1 || !navigator.userAgent.indexOf('Blackberry') != -1 || !navigator.userAgent.indexOf('Android') != -1 || $('body').hasClass('screen_wide') || $('body').hasClass('screen_wide')) {
			jQuery('.container .nine .grey-box .uactivity').jScrollPane({scrollbarWidth:18, scrollbarMargin:0, showArrows:true});
		}	
	});


});


