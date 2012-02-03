/* jQueryId: avatar_selection.js,v 1.1.2.1.4.14 2009/06/07 23:34:23 snpower Exp jQuery */
function radio_button_handler() {
  // handle radio buttons
  jQuery('div.user-avatar-select input.form-radio').hide();
  jQuery('div.user-avatar-select img').hover(
    function(){
      jQuery(this).addClass("avatar-hover");
    },
    function(){
      jQuery(this).removeClass("avatar-hover");
    }
  );
}

function image_click_handler() {
  jQuery('div.user-avatar-select img').bind("click", function(){
    jQuery("div.user-avatar-select img.avatar-select").each(function(){
      jQuery(this).removeClass("avatar-select");
      jQuery(this).parent().children("input").attr("checked", "");
    });
    jQuery(this).addClass("avatar-select");
    jQuery(this).parent().children("input").attr("checked", "checked");
  });
}

if (Drupal.jsEnabled) {
  jQuery(document).ready(function () {

    // handle radio buttons
    radio_button_handler();

    // handle image selection
    image_click_handler();
  });
}


