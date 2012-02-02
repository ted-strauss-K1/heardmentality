/* 
* Skeleton V1.0.3
* Copyright 2011, Dave Gamache
* www.getskeleton.com
* Free to use under the MIT license.
* http://www.opensource.org/licenses/mit-license.php
* 7/17/2011
*/	
	

$(document).ready(function() {


	/* Tabs Activiation
	================================================== */
	var tabs = $('ul.tabs');
	
	tabs.each(function(i) {
		//Get all tabs
		var tab = $(this).find('> li > a');
		tab.click(function(e) {
			
			//Get Location of tab's content
			var contentLocation = $(this).attr('href') + "Tab";
			
			//Let go if not a hashed one
			if(contentLocation.charAt(0)=="#") {
			
				e.preventDefault();
			
				//Make Tab Active
				tab.removeClass('active');
				$(this).addClass('active');
				
				//Show Tab Content & add active class
				$(contentLocation).show().addClass('active').siblings().hide().removeClass('active');
				
			} 
		});
	}); 
	
});

$(function(){

	// Accordion
	$("#accordion").accordion({ header: "h3" });

	// Tabs
	$('#tabs').tabs();





	// Datepicker
	$('#datepicker').datepicker({
		inline: true
	});
	
	// Slider
	$('#slider').slider({
		range: true,
		values: [17, 67]
	});
	
	// Progressbar
	$("#progressbar").progressbar({
		value: 20 
	});
	
	//hover states on the static widgets
	$('#dialog_link, ul#icons li').hover(
		function() { $(this).addClass('ui-state-hover'); }, 
		function() { $(this).removeClass('ui-state-hover'); }
	);
	
});


/*!
 * Collapse plugin for jQuery
 * http://github.com/danielstocks/jQuery-Collapse/
 *
 * @author Daniel Stocks (http://webcloud.se)
 * @version 0.9.1
 * @updated 17-AUG-2010
 * 
 * Copyright 2010, Daniel Stocks
 * Released under the MIT, BSD, and GPL Licenses.
 */
 
(function($) {
    
    // Use a cookie counter to allow multiple instances of the plugin
    var cookieCounter = 0;
    
    $.fn.extend({
        collapse: function(options) {
            
            var defaults = {
                head : "h6",
                group : "div, ul",
                cookieName : "collapse",
                // Default function for showing content
                show: function() { 
                    this.show();
                },
                // Default function for hiding content
                hide: function() { 
                    this.hide();
                }
            };
            var op = $.extend(defaults, options);
            
            // Default CSS classes
            var active = "active",
                inactive = "inactive";
            
            return this.each(function() {
                
                // Increment coookie counter to ensure cookie name integrity
                cookieCounter++;
                var obj = $(this),
                    // Find all headers and wrap them in <a> for accessibility.
                    sections = obj.find(op.head).wrapInner('<a href="#"></a>'),
                    l = sections.length,
                    cookie = op.cookieName + "_" + cookieCounter;
                    // Locate all panels directly following a header
                    var panel = obj.find(op.head).map(function() {
                        var head = $(this)
                        if(!head.hasClass(active)) {
                            return head.next(op.group).hide()[0];
                        }
                        return head.next(op.group)[0];
                    });
    
                // Bind event for showing content
                obj.bind("show", function(e, bypass) {
                    var obj = $(e.target);
                    // ARIA attribute
                    obj.attr('aria-hidden', false)
                        .prev()
                        .removeClass(inactive)
                        .addClass(active);
                    // Bypass method for instant display
                    if(bypass) {
                        obj.show();
                    } else {
                        op.show.call(obj);
                    }
                });

                // Bind event for hiding content
                obj.bind("hide", function(e, bypass) {
                    var obj = $(e.target);
                    obj.attr('aria-hidden', true)
                        .prev()
                        .removeClass(active)
                        .addClass(inactive);
                    if(bypass) {
                        obj.hide();
                    } else {
                        op.hide.call(obj);
                    }
                });
                
                // Look for existing cookies
                if(cookieSupport) {
                    for (var c=0;c<=l;c++) {
                        var val = $.cookie(cookie + c);
                        // Show content if associating cookie is found
                        if ( val == c + "open" ) {
                            panel.eq(c).trigger('show', [true]);
                        // Hide content
                        } else if ( val == c + "closed") {
                            panel.eq(c).trigger('hide', [true]);
                        }
                    }
                }
                
                // Delegate click event to show/hide content.
                obj.bind("click", function(e) {
                    var t = $(e.target);
                    // Check if header was clicked
                    if(!t.is(op.head)) {
                        // What about link inside header.
                        if ( t.parent().is(op.head) ) {
                            t = t.parent();
                        } else {
                            return;
                        }
                        e.preventDefault();
                    }
                    // Figure out what position the clicked header has.
                    var num = sections.index(t),
                        cookieName = cookie + num,
                        cookieVal = num,
                        content = t.next(op.group);
                    // If content is already active, hide it.
                    if(t.hasClass(active)) {
                        content.trigger('hide');
                        cookieVal += 'closed';
                        if(cookieSupport) {
                            $.cookie(cookieName, cookieVal, { path: '/', expires: 10 });
                        }
                        return;
                    }
                    // Otherwise show it.
                    content.trigger('show');
                    cookieVal += 'open';
                    if(cookieSupport) {
                        $.cookie(cookieName, cookieVal, { path: '/', expires: 10 });
                    }
                });
            });
        }
    });

    // Make sure can we eat cookies without getting into trouble.
    var cookieSupport = (function() {
        try {
            $.cookie('x', 'x', { path: '/', expires: 10 });
            $.cookie('x', null);
        }
        catch(e) {
            return false;
        }
        return true;
    })();
})(jQuery);


$(".expanding").collapse({show: function(){
        this.animate({
            opacity: 'toggle', 
            height: 'toggle'
        }, 300);
    },
    hide : function() {
        
        this.animate({
            opacity: 'toggle', 
            height: 'toggle'
        }, 300);
    }
});


/**
 * Cookie plugin
 *
 * Copyright (c) 2006 Klaus Hartl (stilbuero.de)
 * Dual licensed under the MIT and GPL licenses:
 * http://www.opensource.org/licenses/mit-license.php
 * http://www.gnu.org/licenses/gpl.html
 *
 */

/**
 * Create a cookie with the given name and value and other optional parameters.
 *
 * @example $.cookie('the_cookie', 'the_value');
 * @desc Set the value of a cookie.
 * @example $.cookie('the_cookie', 'the_value', { expires: 7, path: '/', domain: 'jquery.com', secure: true });
 * @desc Create a cookie with all available options.
 * @example $.cookie('the_cookie', 'the_value');
 * @desc Create a session cookie.
 * @example $.cookie('the_cookie', null);
 * @desc Delete a cookie by passing null as value. Keep in mind that you have to use the same path and domain
 *       used when the cookie was set.
 *
 * @param String name The name of the cookie.
 * @param String value The value of the cookie.
 * @param Object options An object literal containing key/value pairs to provide optional cookie attributes.
 * @option Number|Date expires Either an integer specifying the expiration date from now on in days or a Date object.
 *                             If a negative value is specified (e.g. a date in the past), the cookie will be deleted.
 *                             If set to null or omitted, the cookie will be a session cookie and will not be retained
 *                             when the the browser exits.
 * @option String path The value of the path atribute of the cookie (default: path of page that created the cookie).
 * @option String domain The value of the domain attribute of the cookie (default: domain of page that created the cookie).
 * @option Boolean secure If true, the secure attribute of the cookie will be set and the cookie transmission will
 *                        require a secure protocol (like HTTPS).
 * @type undefined
 *
 * @name $.cookie
 * @cat Plugins/Cookie
 * @author Klaus Hartl/klaus.hartl@stilbuero.de
 */

/**
 * Get the value of a cookie with the given name.
 *
 * @example $.cookie('the_cookie');
 * @desc Get the value of a cookie.
 *
 * @param String name The name of the cookie.
 * @return The value of the cookie.
 * @type String
 *
 * @name $.cookie
 * @cat Plugins/Cookie
 * @author Klaus Hartl/klaus.hartl@stilbuero.de
 */
jQuery.cookie = function(name, value, options) {
    if (typeof value != 'undefined') { // name and value given, set cookie
        options = options || {};
        if (value === null) {
            value = '';
            options.expires = -1;
        }
        var expires = '';
        if (options.expires && (typeof options.expires == 'number' || options.expires.toUTCString)) {
            var date;
            if (typeof options.expires == 'number') {
                date = new Date();
                date.setTime(date.getTime() + (options.expires * 24 * 60 * 60 * 1000));
            } else {
                date = options.expires;
            }
            expires = '; expires=' + date.toUTCString(); // use expires attribute, max-age is not supported by IE
        }
        // CAUTION: Needed to parenthesize options.path and options.domain
        // in the following expressions, otherwise they evaluate to undefined
        // in the packed version for some reason...
        var path = options.path ? '; path=' + (options.path) : '';
        var domain = options.domain ? '; domain=' + (options.domain) : '';
        var secure = options.secure ? '; secure' : '';
        document.cookie = [name, '=', encodeURIComponent(value), expires, path, domain, secure].join('');
    } else { // only name given, get cookie
        var cookieValue = null;
        if (document.cookie && document.cookie != '') {
            var cookies = document.cookie.split(';');
            for (var i = 0; i < cookies.length; i++) {
                var cookie = jQuery.trim(cookies[i]);
                // Does this cookie string begin with the name we want?
                if (cookie.substring(0, name.length + 1) == (name + '=')) {
                    cookieValue = decodeURIComponent(cookie.substring(name.length + 1));
                    break;
                }
            }
        }
        return cookieValue;
    }
};


$(function(){

				// Accordion
				$("#accordion").accordion({ header: "h3" });

				// Tabs
				$('#tabs').tabs();




				// Datepicker
				$('#datepicker').datepicker({
					inline: true
				});

				// Slider
				$('#slider').slider({
					range: true,
					values: [17, 67]
				});

				// Progressbar
				$("#progressbar").progressbar({
					value: 20 
				});

				//hover states on the static widgets
				$('#dialog_link, ul#icons li').hover(
					function() { $(this).addClass('ui-state-hover'); }, 
					function() { $(this).removeClass('ui-state-hover'); }
				);

			});

/**
 * FADES
 */
       

$(document).ready(function(){
						   $(".comments.expanding h6, a.facebook, a.twitter").fadeTo("fast", 0.5); // This sets the opacity of the thumbs to fade down to 30% when the page loads
						   $(".comments.expanding h6, a.facebook, a.twitter").hover(function(){
						   $(this).fadeTo("fast", 1.0); // This should set the opacity to 100% on hover
						   },function(){
						   $(this).fadeTo("fast", 0.5); // This should set the opacity back to 30% on mouseout
							   	});
						   });

$(document).ready(function(){
						   $(".comments.expanding h6#reply").fadeTo("fast", 0.9); // This sets the opacity of the thumbs to fade down to 30% when the page loads
						   $(".comments.expanding h6#reply").hover(function(){
						   $(this).fadeTo("fast", 1.0); // This should set the opacity to 100% on hover
						   },function(){
						   $(this).fadeTo("fast", 0.9); // This should set the opacity back to 30% on mouseout
							   	});
						   });
						   
						
 $(document).ready(function(){
 						   $(" h6#add-arg").fadeTo("fast", 1); // This sets the opacity of the thumbs to fade down to 30% when the page loads
 						   $(" h6#add-arg").hover(function(){
 						   $(this).fadeTo("fast", 1.0); // This should set the opacity to 100% on hover
 						   },function(){
 						   $(this).fadeTo("fast", 1); // This should set the opacity back to 30% on mouseout
 							   	});
 						   });						   

/**
 * JQUERY UI STUFF
 */
 
 
$(function(){

	// Accordion
	$("#accordion").accordion({ header: "h3" });

	// Tabs
	$('#tabs').tabs();


	// Dialog			
	$('#dialog').dialog({
		autoOpen: false,
		modal: false,
		minWidth: 320,
		resizable:false
	});

	// Dialog Link
	$('#dialog_link').click(function(){
		$('#dialog').dialog('open');
		return false;
	});
	// Dialog Link
	$('#dialog_link2').click(function(){
		$('#dialog2').dialog('open');
		return false;
	});
	
	
	// Dialog			
	$('#dialog-flag').dialog({
		autoOpen: false,
		modal: false,
		minWidth: 320,
		resizable:false
	});

	// Dialog Link
	$('#dialog_link-flag').click(function(){
		$('#dialog-flag').dialog('open');
		return false;
	});


	// Dialog			
	$('#dialog-profile-pic').dialog({
		autoOpen: false,
		modal: false,
		minWidth: 320,
		resizable:false
	});

	// Dialog Link
	$('#dialog_link-pic').click(function(){
		$('#dialog-profile-pic').dialog('open');
		return false;
	});
	
	
	
	
	
	
	
	// Toggler hide

	$(function() {
  		// run the currently selected effect
  		function runEffect() {
  			$( "#effect" ).hide( "fade", 500 );
  		};
  		// set effect from select menu value
  		$( "#button" ).click(function() {
  			runEffect();
  			return false;
  		});
  	});
  	
		// Toggler show
  	
		$(function() {
				// run the currently selected effect
				function runEffect() {
					// run the effect
					$( "#effect2" ).show( "blind", 500 );
				};
				// set effect from select menu value
				$( "#button2" ).click(function() {
					runEffect();
					return false;
				});

				$( "#effect2" ).hide();
			});


  			

	// Datepicker
	$('#datepicker').datepicker({
		inline: true
	});

	// Slider
	$('#slider').slider({
		range: true,
		values: [17, 67]
	});

	// Progressbar
	$("#progressbar").progressbar({
		value: 20 
	});

	//hover states on the static widgets
	$('#dialog_link, ul#icons li').hover(
		function() { $(this).addClass('ui-state-hover'); }, 
		function() { $(this).removeClass('ui-state-hover'); }
	);

});

/**
 * Tool Tips (Tipsy)
 */

// tipsy, facebook style tooltips for jquery
// version 1.0.0a
// (c) 2008-2010 jason frame [jason@onehackoranother.com]
// released under the MIT license

(function($) {

    function maybeCall(thing, ctx) {
        return (typeof thing == 'function') ? (thing.call(ctx)) : thing;
    };

    function Tipsy(element, options) {
        this.$element = $(element);
        this.options = options;
        this.enabled = true;
        this.fixTitle();
    };

    Tipsy.prototype = {
        show: function() {
            var title = this.getTitle();
            if (title && this.enabled) {
                var $tip = this.tip();

                $tip.find('.tipsy-inner')[this.options.html ? 'html' : 'text'](title);
                $tip[0].className = 'tipsy'; // reset classname in case of dynamic gravity
                $tip.remove().css({top: 0, left: 0, visibility: 'hidden', display: 'block'}).prependTo(document.body);

                var pos = $.extend({}, this.$element.offset(), {
                    width: this.$element[0].offsetWidth,
                    height: this.$element[0].offsetHeight
                });

                var actualWidth = $tip[0].offsetWidth,
                    actualHeight = $tip[0].offsetHeight,
                    gravity = maybeCall(this.options.gravity, this.$element[0]);

                var tp;
                switch (gravity.charAt(0)) {
                    case 'n':
                        tp = {top: pos.top + pos.height + this.options.offset, left: pos.left + pos.width / 2 - actualWidth / 2};
                        break;
                    case 's':
                        tp = {top: pos.top - actualHeight - this.options.offset, left: pos.left + pos.width / 2 - actualWidth / 2};
                        break;
                    case 'e':
                        tp = {top: pos.top + pos.height / 2 - actualHeight / 2, left: pos.left - actualWidth - this.options.offset};
                        break;
                    case 'w':
                        tp = {top: pos.top + pos.height / 2 - actualHeight / 2, left: pos.left + pos.width + this.options.offset};
                        break;
                }

                if (gravity.length == 2) {
                    if (gravity.charAt(1) == 'w') {
                        tp.left = pos.left + pos.width / 2 - 15;
                    } else {
                        tp.left = pos.left + pos.width / 2 - actualWidth + 15;
                    }
                }

                $tip.css(tp).addClass('tipsy-' + gravity);
                $tip.find('.tipsy-arrow')[0].className = 'tipsy-arrow tipsy-arrow-' + gravity.charAt(0);
                if (this.options.className) {
                    $tip.addClass(maybeCall(this.options.className, this.$element[0]));
                }

                if (this.options.fade) {
                    $tip.stop().css({opacity: 0, display: 'block', visibility: 'visible'}).animate({opacity: this.options.opacity});
                } else {
                    $tip.css({visibility: 'visible', opacity: this.options.opacity});
                }
            }
        },

        hide: function() {
            if (this.options.fade) {
                this.tip().stop().fadeOut(function() { $(this).remove(); });
            } else {
                this.tip().remove();
            }
        },

        fixTitle: function() {
            var $e = this.$element;
            if ($e.attr('title') || typeof($e.attr('original-title')) != 'string') {
                $e.attr('original-title', $e.attr('title') || '').removeAttr('title');
            }
        },

        getTitle: function() {
            var title, $e = this.$element, o = this.options;
            this.fixTitle();
            var title, o = this.options;
            if (typeof o.title == 'string') {
                title = $e.attr(o.title == 'title' ? 'original-title' : o.title);
            } else if (typeof o.title == 'function') {
                title = o.title.call($e[0]);
            }
            title = ('' + title).replace(/(^\s*|\s*$)/, "");
            return title || o.fallback;
        },

        tip: function() {
            if (!this.$tip) {
                this.$tip = $('<div class="tipsy"></div>').html('<div class="tipsy-arrow"></div><div class="tipsy-inner"></div>');
            }
            return this.$tip;
        },

        validate: function() {
            if (!this.$element[0].parentNode) {
                this.hide();
                this.$element = null;
                this.options = null;
            }
        },

        enable: function() { this.enabled = true; },
        disable: function() { this.enabled = false; },
        toggleEnabled: function() { this.enabled = !this.enabled; }
    };

    $.fn.tipsy = function(options) {

        if (options === true) {
            return this.data('tipsy');
        } else if (typeof options == 'string') {
            var tipsy = this.data('tipsy');
            if (tipsy) tipsy[options]();
            return this;
        }

        options = $.extend({}, $.fn.tipsy.defaults, options);

        function get(ele) {
            var tipsy = $.data(ele, 'tipsy');
            if (!tipsy) {
                tipsy = new Tipsy(ele, $.fn.tipsy.elementOptions(ele, options));
                $.data(ele, 'tipsy', tipsy);
            }
            return tipsy;
        }

        function enter() {
            var tipsy = get(this);
            tipsy.hoverState = 'in';
            if (options.delayIn == 0) {
                tipsy.show();
            } else {
                tipsy.fixTitle();
                setTimeout(function() { if (tipsy.hoverState == 'in') tipsy.show(); }, options.delayIn);
            }
        };

        function leave() {
            var tipsy = get(this);
            tipsy.hoverState = 'out';
            if (options.delayOut == 0) {
                tipsy.hide();
            } else {
                setTimeout(function() { if (tipsy.hoverState == 'out') tipsy.hide(); }, options.delayOut);
            }
        };

        if (!options.live) this.each(function() { get(this); });

        if (options.trigger != 'manual') {
            var binder   = options.live ? 'live' : 'bind',
                eventIn  = options.trigger == 'hover' ? 'mouseenter' : 'focus',
                eventOut = options.trigger == 'hover' ? 'mouseleave' : 'blur';
            this[binder](eventIn, enter)[binder](eventOut, leave);
        }

        return this;

    };

    $.fn.tipsy.defaults = {
        className: null,
        delayIn: 0,
        delayOut: 0,
        fade: false,
        fallback: '',
        gravity: 'n',
        html: false,
        live: false,
        offset: 0,
        opacity: 0.8,
        title: 'title',
        trigger: 'hover'
    };

    // Overwrite this method to provide options on a per-element basis.
    // For example, you could store the gravity in a 'tipsy-gravity' attribute:
    // return $.extend({}, options, {gravity: $(ele).attr('tipsy-gravity') || 'n' });
    // (remember - do not modify 'options' in place!)
    $.fn.tipsy.elementOptions = function(ele, options) {
        return $.metadata ? $.extend({}, options, $(ele).metadata()) : options;
    };

    $.fn.tipsy.autoNS = function() {
        return $(this).offset().top > ($(document).scrollTop() + $(window).height() / 2) ? 's' : 'n';
    };

    $.fn.tipsy.autoWE = function() {
        return $(this).offset().left > ($(document).scrollLeft() + $(window).width() / 2) ? 'e' : 'w';
    };

    /**
     * yields a closure of the supplied parameters, producing a function that takes
     * no arguments and is suitable for use as an autogravity function like so:
     *
     * @param margin (int) - distance from the viewable region edge that an
     *        element should be before setting its tooltip's gravity to be away
     *        from that edge.
     * @param prefer (string, e.g. 'n', 'sw', 'w') - the direction to prefer
     *        if there are no viewable region edges effecting the tooltip's
     *        gravity. It will try to vary from this minimally, for example,
     *        if 'sw' is preferred and an element is near the right viewable 
     *        region edge, but not the top edge, it will set the gravity for
     *        that element's tooltip to be 'se', preserving the southern
     *        component.
     */
     $.fn.tipsy.autoBounds = function(margin, prefer) {
		return function() {
			var dir = {ns: prefer[0], ew: (prefer.length > 1 ? prefer[1] : false)},
			    boundTop = $(document).scrollTop() + margin,
			    boundLeft = $(document).scrollLeft() + margin,
			    $this = $(this);

			if ($this.offset().top < boundTop) dir.ns = 'n';
			if ($this.offset().left < boundLeft) dir.ew = 'w';
			if ($(window).width() + $(document).scrollLeft() - $this.offset().left < margin) dir.ew = 'e';
			if ($(window).height() + $(document).scrollTop() - $this.offset().top < margin) dir.ns = 's';

			return dir.ns + (dir.ew ? dir.ew : '');
		}
	};

})(jQuery);



$(function() {
  
  $('#medal1, #medal2, #medal3,  img.coin2, .disagree, .agree').tipsy({gravity: 'nw'});
  $('.flag, .flag2, .heart, a.stats-quick').tipsy({gravity: 'w'});
  $('span.lighter, .privacy-rules').tipsy({gravity: 's'});



  $('#nope').tipsy({gravity: $.fn.tipsy.autoNS});
  
  $('#example-fade').tipsy({fade: true});
  
  $('#example-custom-attribute').tipsy({title: 'id'});
  $('#example-callback').tipsy({title: function() { return this.getAttribute('original-title').toUpperCase(); } });
  $('#example-fallback').tipsy({fallback: "Where's my tooltip yo'?" });
  
  $('#example-html').tipsy({html: true });
  
});

/**
 * Front Page Carousel Thing
 */



$(document).ready(function() {
	$('.see, .vote-now, .share-now').append('<span class="hover"></span>').each(function () {
	  var $span = $('> span.hover', this).css('opacity', 0);
	  $(this).hover(function () {
	    $span.stop().fadeTo(200, 1);
	  }, function () {
	    $span.stop().fadeTo(200, 0);
	  });
	});
});