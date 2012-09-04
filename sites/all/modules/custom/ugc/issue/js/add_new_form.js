

/*
 * Validate URL
 */
function url_validate(url) {
    var objRE = /http:\/\/[A-Za-z0-9\.-]{3,}\.[A-Za-z]{3}/;
    return objRE.test(url);
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

/*
 * Attach Submit
 */
jQuery("#lattach").live('click', function() {
    jQuery('#deb-err').html('');
    var attach = jQuery(this);
    var lbox = jQuery('#linkbox');
    var url = jQuery('#url').val();
    if( !url_validate(url) ) {
        $.hrd.noty({'type':'error', 'text' : '<span>Please enter a valid URL.</span>'});
        // show_msg('#deb-err', '<span>Please enter a valid URL.</span>', 5000, 500);
        return false;
    } else {
        var purl=Drupal.settings.base_url+'/debate/ajax';
        attach.attr('disabled',true);
        lbox.slideDown('slow');
        lbox.html("<span class='load'>Loading...</span>");
        jQuery.get(purl+"?action=url&url="+url,function(response) {
            if( response == '' ) {
                show_msg('#deb-err', '<span>Error loading URL.</span>', 5000, 500);
                attach.removeAttr('disabled');
                lbox.slideUp('slow', function(){ lbox.html('') });
                return false;
            }
            lbox.html(response);
            attach.removeAttr('disabled');
            if(jQuery('#cur_id_val').val() == jQuery('#end_image').val()){
                jQuery('#re-sel-next').hide();
                jQuery('#re-sel-prev').hide();
            }
            jQuery('#re-sel-pre').hide();
        });

    }
    return false;
});









$(document).ready(function() {
  $('#inc_ref').change(function(){
    $('.resources').toggle();
  });

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
    $.hrd.noty({
      'layout' : 'center',
      'type'   : 'alert',
      'text'   : window.location.href.replace(/#.*/,'') + '#' +$(this).parents('.one-forum').attr('id'),
      'modal'  : true,
      'timeout': false,
      'closeWith': ['button']
    });
  });




  translate();
  flagger_rebind();

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
