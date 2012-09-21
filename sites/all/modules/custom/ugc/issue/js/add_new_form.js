

function show_msg(element, message, delayTimeout, slideTimeout) {
  jQuery(element).html(message).delay(delayTimeout).slideUp(slideTimeout, function(){
    jQuery(this).html('').show();
  });
}

/*
 * Image Value Preprocess when submitting new resource
 */
jQuery('#add_new_debate').live('click',function() {
    var image_value;
    if( !jQuery('#no_thumbnail').attr('checked') ) {
        var img_v = jQuery('#cur_id_val').val();
        image_value = jQuery('#cur_img_'+img_v).attr('src');
    } else {
        image_value = 'no_image';
    }
    jQuery('#image_value').val(image_value);
});









$(document).ready(function() {

  $("#debate_list_area").tabs({
    cache: false,
    load: function(event, ui) {
      Drupal.attachBehaviors();
    }
  });
});


Drupal.behaviors.add_new_form = function(context) {

  /*
   * Permalink
   */
  $('a.permalink').click(function(e) {
    e.preventDefault();
    var link = window.location.href.replace(/#.*/,'') + '#' +$(this).parents('.one-forum').attr('id');
    $.hrd.noty({
      'layout' : 'center',
      'type'   : 'alert',
      'text'   : '<a href="'+link+'">'+link+'</a>',
      'modal'  : true,
      'timeout': false,
      'closeWith': ['button']
    });
  });




  translate();

/*
  $('.goog-trans-control').html('');

    var lang = $("html").attr("lang");
    lang = 'auto';
    var s = document.createElement('script');
    s.type='text/javascript';
    s.className = "gt";
    s.src='//translate.google.com/translate_a/element.js?cb=googleSectionalElementInit&ug=section&hl=' +lang;
    document.body.appendChild(s);
*/
}


/*
 * flag/link/delete buttons
 */

jQuery('a.delete').live('click', function(e){
    jQuery( "#dialog_"+jQuery(this).attr('name') ).dialog({
        resizable: false
    });
    return false;
});
jQuery('a.delete button').live('click', function(e){
    jQuery(this).dialog("close");
    return false;
});
jQuery('.icon.flag2').live('click', function(e) {
    e.preventDefault();
    jQuery('#dialog-flag').dialog("open");

});
