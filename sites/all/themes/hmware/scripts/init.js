//$(document).ready(function(){
//	$(window).scroll(function () {
//		hash:true;
//
//  		var scrollTopPosition = ($(window).scrollTop() + 100);
//		var headerSpace = ($("#header_about").offset().top + $("#header_about").height());
//		var aboutSpace = ($("#about").offset().top + $("#about").height());
//  		var associatesSpace = ($("#thanks").offset().top + $("#thanks").height());
//  		var organizationSpace = ($("#hmworks").offset().top + $("#hmworks").height());
//  		var guideSpace = ($("#guide").offset().top + $("#guide").height());
//
//		// div#navigation and div.subnav
//
//		if ((headerSpace <= scrollTopPosition) && (scrollTopPosition <= aboutSpace)){
//			$(".nav0 a").addClass('ab-select');
//		} else {
//			$(".nav0 a").removeClass('ab-select');
//		}
//
//		if ((aboutSpace <= scrollTopPosition) && (scrollTopPosition <= associatesSpace)){
//			$(".nav1 a").addClass('ab-select');
//		} else {
//			$(".nav1 a").removeClass('ab-select');
//		}
//
//		if ((associatesSpace < scrollTopPosition) && (scrollTopPosition <= organizationSpace)) {
//			$(".nav2 a").addClass('ab-select');
//		} else {
//			$(".nav2 a").removeClass('ab-select');
//		}
//
//		if ((organizationSpace < scrollTopPosition) && (scrollTopPosition <= guideSpace)) {
//			$(".nav3 a").addClass('ab-select');
//		} else {
//			$(".nav3 a").removeClass('ab-select');
//		}
//                if ((guideSpace < scrollTopPosition) && (scrollTopPosition <= headerSpace)) {
//			$(".nav4 a").addClass('ab-select');
//		} else {
//			$(".nav4 a").removeClass('ab-select');
//		}
//	});
//
//});
//
//jQuery(function( $ ){
//	$.localScroll.hash({
//		offset: -67,
//		duration:1500
//	});
//
//
//	$.localScroll({
//		duration:1500,
//		hash:true,
//		offset: -67,
//		onBefore:function( e, anchor, $target ){
//			// The 'this' is the settings object, can be modified
//		},
//		onAfter:function( anchor, settings ){
//			// The 'this' contains the scrolled element (#content)
//		}
//	});
//
//
//});

function filterPath(string) {
  return string
 .replace(/^\//,'')
 .replace(/(index|default).[a-zA-Z]{3,4}$/,'')
 .replace(/\/$/,'');
  }
$(document).ready(function() {
  
  var locationPath = filterPath(location.pathname);
  var scrollElem = scrollableElement('html', 'body');
  $('div.ab-menu a[href*=#]').each(function() {
     
 var thisPath = filterPath(this.pathname) || locationPath;
 if (  locationPath == thisPath
 && (location.hostname == this.hostname || !this.hostname)
 && this.hash.replace(/#/,'') ) {
   var $target = $(this.hash), target = this.hash;
   if (target) {
  var targetOffset = $target.offset().top;
  $(this).click(function(event) {
      $("div.ab-menu a").removeClass('ab-select');
      $(this).addClass('ab-select');
    event.preventDefault();
    

    $(scrollElem).animate({scrollTop: targetOffset}, 1500, function() {
   location.hash = target;
    });


  });
   }
 }
  });
  // use the first element that is "scrollable"
  function scrollableElement(els) {
 for (var i = 0, argLength = arguments.length; i <argLength; i++) {
   var el = arguments[i],
    $scrollElement = $(el);
   if ($scrollElement.scrollTop()> 0) {
  return el;
   } else {
  $scrollElement.scrollTop(1);
  var isScrollable = $scrollElement.scrollTop()> 0;
  $scrollElement.scrollTop(0);
  if (isScrollable) {
    return el;
  }
   }
 }
 return [];
  }

$(window).scroll(function () {
		hash:true;

  		var scrollTopPosition = ($(window).scrollTop() + 100);
		var headerSpace = ($("#header_about").offset().top + $("#header_about").height());
		var aboutSpace = ($("#about").offset().top + $("#about").height());
  		var associatesSpace = ($("#thanks").offset().top + $("#thanks").height());
  		var organizationSpace = ($("#hmworks").offset().top + $("#hmworks").height());
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
                if ((guideSpace < scrollTopPosition) && (scrollTopPosition <= headerSpace)) {
			$(".nav4 a").addClass('ab-select');
		} else {
			$(".nav4 a").removeClass('ab-select');
		}
	});

	
});