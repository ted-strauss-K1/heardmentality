// Javascript for user_relationships_ui.module

// Creating our own namespace for the module
Drupal.user_relationships_ui = {};

Drupal.behaviors.userRelationshipsPopupLink = function(context) { 
  // Any links that we have created in the ui module are  
  // Given a click handler so you can display the popup correctly
  $('a.user_relationships_popup_link').click(function(e) {  
  
    /**Remove the below mentioned lines(Rallydev:543), if we want to revert back to the previous functionality in the "/profile" page
	 *
	 * Now the pop-up restricted and action to be done within the same page without redirecting
	 * Date Added : March 07 / 2012
	 *
	**/
	/**Rallydev:543**/
	url = document.URL;
	if(url.indexOf('profile/') != -1) { 
		e.preventDefault();  
		$('h2.din').after('<p class="ajax-loader"></p>');
		var request_path = Drupal.settings.hm_base_url; 
		split = url.split("profile/");
		user_name = split[1]; 
		urls = request_path + '/profile/follow_unfollow';
		jQuery.ajax({
			type: "GET",
			url: urls,
			data: {'prof_visited_user':user_name},
			success: function(msg) {
              $('.ajax-loader').remove();
			  if(msg == 0) {
				$('a.user_relationships_popup_link').html('Follow User');
				$('.profile-message:first').html(__showResponse("Your <em>Subscriber</em> relationship with "+user_name+" has been deleted.")); 
			  } else if(msg == 1) {
				$('a.user_relationships_popup_link').html('Unfollow User');
				$('.profile-message:first').html(__showResponse("You are <em>Subscribed</em> to "+user_name));
			  }
			}
		});
		return;
	}
	
	function __showResponse(message) {
		var message = '<div style="width: auto; height: auto;" class="" id="effect">'+
                      '<div class="message top-message">'+
                      '<p style="display: none;" class="double"></p><div class="messages status">'+message+
                      '</div>'+
                      '</div>'+
                      '<a class="hide-message" id="button" href="#" style="margin-top: 3px;"><span class="ui-icon ui-icon-closethick">Hide</span></a>'+
                      '<br class="clear">'+
                      '</div><div class="clear"></div>';
		return message;
	}
   /*****************/
  
    var buttoncode = e.which ? e.which : e.button; // msie specific checks does not support e.which
    // If position is fixed, allow for %'s.
    position = Drupal.settings.user_relationships_ui.position.position;
    left = Drupal.settings.user_relationships_ui.position.left;
    xtop = Drupal.settings.user_relationships_ui.position.top;

    if(position == "fixed") {
      // If left is defined in a % (.5) calculate left requirement
      if(left <= 1) {
        // Window width * desired - UI width
        left = Math.round(($(window).width()*left) - ($("#user_relationships_popup_form").width()/2));
      }
      // If top is define in a % (.33) calculate top requirement
      if(xtop <= 1) {
        // Window height * desired - UI height (which is an unknown)
        xtop = Math.round(($(window).height()*xtop));// - ($("#user_relationships_popup_form").height()/2));
      }
    } else {
      left = (e.pageX ? e.pageX : e.clientX) + Number(left); // msie specific checks does not support e.page
      if (left + $("#user_relationships_popup_form").width() > $(window).width()) {
        left = (e.pageX ? e.pageX : e.clientX) - $("#user_relationships_popup_form").width();
      }
      xtop = (e.pageY ? e.pageY : e.clientY) + Number(xtop); // msie specific checks does not support e.page
    }
    var href = $(this).attr('href'); // Where we send the ajax request.
    Drupal.user_relationships_ui.showForm(href, position, left, xtop);
    return false;
  });
}

/**
 * Function to display the pertinent form for the user
 *
 * @param href
 *      Ajax url where we will retrieve the form
 * @param pageX
 *      Left value for the event
 * @param pageY
 *      Top value for the event
 */
Drupal.user_relationships_ui.showForm = function(href, position, left, top) {
  // Making sure that any currently open popups will be hidden.
  Drupal.user_relationships_ui.hidePopup();
  // Putting the animation into this

  $('#user_relationships_popup_form')
    .css({top: top + 'px', left: left + 'px', position: position})
    .html(Drupal.user_relationships_ui.loadingAnimation())
    .slideDown();
  // Adding ajax to the href because we need to determine between ajax and regular
  if (href.indexOf('?') == -1) {
    href += '?';
  }
  href += '&ajax=1';
  // Making the ajax request to the server to retrieve the form.
  $.get(href, function(result) {
    $('#user_relationships_popup_form').html(result).slideDown();
    // Making sure the cancel link on each form in the popup closes the popup.
    $('#user_relationships_popup_form .container-inline a').click(function() {
      Drupal.user_relationships_ui.hidePopup();
      return false;
    });
    //Prevent users from clicking submit button twice
    Drupal.user_relationships_ui.formCheck();
  });
};

/**
 * Function used to return the html that is used to build the.
 * Loading animation when a form is requested by the user.
 */
Drupal.user_relationships_ui.loadingAnimation = function() {
  var html = '<div>';
  html += '<div style="text-align: center; font-weight: bold;">';
  html += Drupal.t('Form Loading');
  html += '</div>';
  html += '<img src="' + Drupal.settings.user_relationships_ui.loadingimage + '" border="0" height="20" width="200" />';
  html += '</div>';
  return html;
};

/**
 * Helper function to hide the popup form
 */
Drupal.user_relationships_ui.hidePopup = function() {
  $('#user_relationships_popup_form').slideUp();
};

/**
 * Prevent users from clicking a submit button twice - borrowed from http://drupal.org/project/newswire - thanks, fellows :)
 */
Drupal.user_relationships_ui.formCheck = function() {
  // only apply this to node and comment and new user registration forms
  var forms = $("#user_relationships_popup_form #edit-submit");
  // insert the saving div now to cache it for better performance and to show the loading image
  $('<div id="user_relationships_popup_form_saving"><p class="user_relationships_popup_form_saving">' + Drupal.t('Saving...') + '</p></div>').insertAfter(forms);
  forms.click(function() {
    $(this).siblings("input[type=submit]").hide();
    $(this).hide();
    $("#user_relationships_popup_form_saving").show();
    var notice = function() {
      $('<p id="user_relationships_popup_form_saving_notice">' + Drupal.t('Not saving? Please wait a few seconds, reload this page, and try again.') + '</p>').appendTo("#user_relationships_popup_form_saving").fadeIn();
    };
    // append notice if form saving isn't work, perhaps a timeout issue
    setTimeout(notice, 60000);
  });
};

$(document).ready(function() {
  $('#edit-is-oneway').click(function () {
    if ($('#edit-is-oneway').attr('checked')) {
      $('#edit-is-reciprocal-wrapper').slideDown('slow');
    }
    else {
      $('#edit-is-reciprocal-wrapper').slideUp('slow');
    }
  });

  if (!$('#edit-is-oneway').attr('checked')) {
    $('#edit-is-reciprocal-wrapper').hide();
  }
});
/**Rallydev:543**/
$('.hide-message').live('click',function() {
  $(this).parent().hide();
});
/****************/	