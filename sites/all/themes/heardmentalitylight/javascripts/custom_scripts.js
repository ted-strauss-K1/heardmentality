$(document).ready(function() {

  // Initialization jscrollpane
	
  /**
 * jQuery.browser.mobile (http://detectmobilebrowser.com/)
 *
 * jQuery.browser.mobile will be true if the browser is a mobile device
 *
 **/
  (function(a){
    jQuery.browser.mobile=/android.+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od|ad)|iris|kindle|lge |maemo|midp|mmp|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|symbian|treo|up\.(browser|link)|vodafone|wap|windows (ce|phone)|xda|xiino/i.test(a)||/1207|6310|6590|3gso|4thp|50[1-6]i|770s|802s|a wa|abac|ac(er|oo|s\-)|ai(ko|rn)|al(av|ca|co)|amoi|an(ex|ny|yw)|aptu|ar(ch|go)|as(te|us)|attw|au(di|\-m|r |s )|avan|be(ck|ll|nq)|bi(lb|rd)|bl(ac|az)|br(e|v)w|bumb|bw\-(n|u)|c55\/|capi|ccwa|cdm\-|cell|chtm|cldc|cmd\-|co(mp|nd)|craw|da(it|ll|ng)|dbte|dc\-s|devi|dica|dmob|do(c|p)o|ds(12|\-d)|el(49|ai)|em(l2|ul)|er(ic|k0)|esl8|ez([4-7]0|os|wa|ze)|fetc|fly(\-|_)|g1 u|g560|gene|gf\-5|g\-mo|go(\.w|od)|gr(ad|un)|haie|hcit|hd\-(m|p|t)|hei\-|hi(pt|ta)|hp( i|ip)|hs\-c|ht(c(\-| |_|a|g|p|s|t)|tp)|hu(aw|tc)|i\-(20|go|ma)|i230|iac( |\-|\/)|ibro|idea|ig01|ikom|im1k|inno|ipaq|iris|ja(t|v)a|jbro|jemu|jigs|kddi|keji|kgt( |\/)|klon|kpt |kwc\-|kyo(c|k)|le(no|xi)|lg( g|\/(k|l|u)|50|54|e\-|e\/|\-[a-w])|libw|lynx|m1\-w|m3ga|m50\/|ma(te|ui|xo)|mc(01|21|ca)|m\-cr|me(di|rc|ri)|mi(o8|oa|ts)|mmef|mo(01|02|bi|de|do|t(\-| |o|v)|zz)|mt(50|p1|v )|mwbp|mywa|n10[0-2]|n20[2-3]|n30(0|2)|n50(0|2|5)|n7(0(0|1)|10)|ne((c|m)\-|on|tf|wf|wg|wt)|nok(6|i)|nzph|o2im|op(ti|wv)|oran|owg1|p800|pan(a|d|t)|pdxg|pg(13|\-([1-8]|c))|phil|pire|pl(ay|uc)|pn\-2|po(ck|rt|se)|prox|psio|pt\-g|qa\-a|qc(07|12|21|32|60|\-[2-7]|i\-)|qtek|r380|r600|raks|rim9|ro(ve|zo)|s55\/|sa(ge|ma|mm|ms|ny|va)|sc(01|h\-|oo|p\-)|sdk\/|se(c(\-|0|1)|47|mc|nd|ri)|sgh\-|shar|sie(\-|m)|sk\-0|sl(45|id)|sm(al|ar|b3|it|t5)|so(ft|ny)|sp(01|h\-|v\-|v )|sy(01|mb)|t2(18|50)|t6(00|10|18)|ta(gt|lk)|tcl\-|tdg\-|tel(i|m)|tim\-|t\-mo|to(pl|sh)|ts(70|m\-|m3|m5)|tx\-9|up(\.b|g1|si)|utst|v400|v750|veri|vi(rg|te)|vk(40|5[0-3]|\-v)|vm40|voda|vulc|vx(52|53|60|61|70|80|81|83|85|98)|w3c(\-| )|webc|whit|wi(g |nc|nw)|wmlb|wonu|x700|xda(\-|2|g)|yas\-|your|zeto|zte\-/i.test(a.substr(0,4))
    })(navigator.userAgent||navigator.vendor||window.opera);
	
  jQuery(function()
  {
			
    if (jQuery.browser.mobile == false) {
      jQuery('.container .nine .grey-box .uactivity').jScrollPane({
        scrollbarWidth:12, 
        scrollbarMargin:0, 
        showArrows:true
      });
    }
			
    $('body.front .grey-box').resize(function(e) {
      jQuery('.container .nine .grey-box .uactivity').jScrollPane({
        scrollbarWidth:12, 
        scrollbarMargin:0, 
        showArrows:true
      });
    });

  });
	
  // Show/Hide Add argument & Debate statistic
	
  $('h6#add-arg').click(function() {
	
    if ($(this).parents('#debate_work_area').find('#analytics-area').hasClass('visible_deb')) {
      $(this).parents('#debate_work_area').find('#analytics-area').removeClass('visible_deb').addClass('hidden_deb').slideUp();
	  $('h6#deb-ana').removeClass('expanded');
    }
		
    var add = $(this).parents('#debate_work_area').find('#leave_comment_area');
		
    if (add.hasClass('hidden_ar')) {
      add.removeClass('hidden_ar').addClass('visible_ar').slideDown(400);
      $(this).addClass('expanded');
    }
    else {
      add.removeClass('visible_ar').addClass('hidden_ar').slideUp(400);
      $(this).removeClass('expanded');
    }
		
  });
	
  $('h6#deb-ana').click(function() {
	
    if ($(this).parents('#debate_work_area').find('#leave_comment_area').hasClass('visible_ar')) {
      $(this).parents('#debate_work_area').find('#leave_comment_area').removeClass('visible_ar').addClass('hidden_ar').slideUp();
	  $('h6#add-arg').removeClass('expanded');
    }
		
    var graf = $(this).parents('#debate_work_area').find('#analytics-area');
		
    if (graf.hasClass('hidden_deb')) {
      graf.removeClass('hidden_deb').addClass('visible_deb').slideDown(400);
      $(this).addClass('expanded');
    }
    else {
      graf.removeClass('visible_deb').addClass('hidden_deb').slideUp(400);
      $(this).removeClass('expanded');
    }

  });
  
  
  // Filter show only
  
  $('#debate_list_area .show_only span.button').click(function() {
		
    var filter = $(this).parent('.show_only').find('.popup');
		
    if (filter.hasClass('hidden')) {
      filter.removeClass('hidden').addClass('visible');
      $(this).addClass('active');
    }
    else {
      filter.removeClass('visible').addClass('hidden');
      $(this).removeClass('active');
    }
	
  });
  
  // !Show (Click yes/no to leave support/oppose comment.)
  
  $('.reply_wrapper legend a').live("click", function(){
  
    $(this).parents('ul.argument_box').find('strong.motivat').css('display', 'block');
	
  });
  
  
// Add references - position

$('.add_button .argument-form a, .add_button .reference-form a').click(function() {

	var buttonAddTop = $('#leave_comment_area table .reference-form').css('display');

	if (buttonAddTop == 'block'){
		$('#leave_comment_area .add_button').addClass('reduce');
	}

	else {
		$('#leave_comment_area .add_button').removeClass('reduce');
	}
});

// !

		if ($.browser.mozilla) {
			$('span.small_pos, #debate_list_area .arg p.position-plus strong').addClass('fixes');
			$('#debate_list_area li.one_reply span.negative, #debate_list_area li.one_reply span.positive').addClass('fixes');
		}
		if ($.browser.msie && $.browser.version > '8.0') {
			$('span.small_pos, #debate_list_area .arg p.position-plus strong').addClass('fixes');
			$('#debate_list_area li.one_reply span.negative, #debate_list_area li.one_reply span.positive').addClass('fixes');
		}
		if ($.browser.opera) {
			$('#debate_list_area li.one_reply span.negative, #debate_list_area li.one_reply span.positive').addClass('fixes');
		}
  
});
