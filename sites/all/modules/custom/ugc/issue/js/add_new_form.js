/*
 * Add New Form Submit
 */
jQuery('#add-new-debate-form').live('submit', function(e) {
    e.preventDefault();
    jQuery('#deb-err').html('');
    // type = 1/0 = debate/resource
    var type = $('#add_new_type').val();
    // debate title
    var title = jQuery('#deb_title').val();
    // debate flags
    var flag_set = false;
    var tot_ans = jQuery('#tot_ans').val();
    for(var i=0; i<tot_ans; i++) {
        if(jQuery('#sup_'+i).val() != 0) {
            flag_set = true;
            break;
        }
    }
    // resource link & regexp
    var nlink = $('#edit-ref-title').val();
    // resource linkbox
    var linkbox = $('#linkbox').html();

    // check errors
    var error = false;
    if(title.length < 2 && type == 1){
        error = 'Please let us know what you think.';
    } else if(!flag_set && type == 1) {
        error = 'You must choose at least one suppose or oppose.';
    } else if(!url_validate(nlink) && type == 0) {
        error = 'Please enter a valid URL.';
    } else if(linkbox == '' && type == 0) {
        error = 'Please press Attach before adding.';
    }
    if( error ) {
        // css for errors
        jQuery('#deb-err').css('color','red');
        show_msg('#deb-err', '<span>'+error+'</span>', 5000, 500);
        return false;
    }

    // hide submit button
    jQuery('#add_new_debate').hide();
    // show sub loader
    jQuery('#sub_loader').show();
    // with no errors submit form
    var data=jQuery(this).serialize();
    jQuery.ajax({
        type: 'POST',
        dataType: 'json',
        url: jQuery(this).attr('action'),
        data: data,
        success: function(msg) {
            var selected = $("#debate_list_area").tabs( "option", "selected" );
            jQuery('#add_debate_wrapper').slideUp('slow');
            $('#debate_list_area').tabs("select", selected);
            jQuery('#add-new-debate-form select').val(0);
            jQuery('#add-new-debate-form textarea').val('');
            // message
            if(msg.success_post == 1) {
                jQuery('#deb-err').css('color','green');
                show_msg('#deb-err', msg.message, 5000, 500);
            }
            // set default values for answers
            for(var i=0; i<tot_ans; i++) {
                jQuery('#sup_'+i+' option').removeAttr('selected');
                jQuery('#slider-'+i).slider({value:2});
                jQuery('#sup_'+i+' :nth-child(2)').attr("selected", "selected");
                jQuery('#sup_'+i);
            }
            // reload tab
            jQuery('#debate_list_area').tabs("load", selected);
        },
        complete: function(){
            // hide sub loader
            jQuery('#sub_loader').hide();
            // show submit button
            jQuery('#add_new_debate').show();
            // $('#deb-err').delay(3000).slideUp(400);
            // hide other elements
            $('#add-arg').removeClass('expanded');
            $('#leave_comment_area').delay(5000).slideUp(400).removeClass('visible_ar').addClass('hidden_ar');
            // recalculate
            var ct = jQuery('.'+(type==1?'arg':'res')+'count');
            ct.fadeOut(1000, function(){
                var count = parseInt(ct.html())+1;
                ct.html(count);
                ct.fadeIn(1000);
            });
        }
    });
    // }
    return false;
});

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
    var url = jQuery('#edit-ref-title').val();
    if( !url_validate(url) ) {
        show_msg('#deb-err', '<span>Please enter a valid URL.</span>', 5000, 500);
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

  /*
  console.log('x2');
  function googleSectionalElementInit() {
    new google.translate.SectionalElement({
      sectionalNodeClassName: 'goog-trans-section',
      controlNodeClassName: 'goog-trans-control',
      background: '#E1E43C'
    }, 'google_sectional_element');
  }
  */

  $('.reference-form').hide();
  $('#link_arg-wrapper a').click(function(){
    $('.reference-form').show();
    $('.argument-form').hide();
    $('#add_new_type').val(0);
    return false;
  });
  $('#link_ref-wrapper a').click(function(){
    $('.reference-form').hide();
    $('.argument-form').show();
    $('#add_new_type').val(1);
    return false;
  });
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
