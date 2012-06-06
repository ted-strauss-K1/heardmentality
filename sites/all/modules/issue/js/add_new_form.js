function googleSectionalElementInit() {
  new google.translate.SectionalElement({
    sectionalNodeClassName: 'goog-trans-section',
    controlNodeClassName: 'goog-trans-control',
    background: '#E1E43C'
  }, 'google_sectional_element');
}

$(document).ready(function() {
  function googleSectionalElementInit() {
    new google.translate.SectionalElement({
      sectionalNodeClassName: 'goog-trans-section',
      controlNodeClassName: 'goog-trans-control',
      background: '#E1E43C'
    }, 'google_sectional_element');
  }
  
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

$('#add_new_debate').live('click',function() {
  var image_value;
  if ($('#no_thumbnail').attr('checked')== false) {
    var img_v = $('#cur_id_val').val();
    image_value = $('#cur_img_'+img_v).attr('src');
  } 
  else {
    image_value = 'no_image';
  }
  $('#image_value').val(image_value);
    
  // add new debate ajax submit
  jQuery('#add-new-debate-form').live('submit', function(e) {
    e.preventDefault();
    jQuery('#deb-err').css('color','red');
    var title = jQuery('#deb_title').val();
    var nlink = $('#edit-ref-title').val();
    var type = $('#add_new_type').val();
    var tomatch=/http:\/\/[A-Za-z0-9\.-]{3,}\.[A-Za-z]{3}/;
    var tot_ans = jQuery('#tot_ans').val();
    var flag = 0;
    var linkbox = $('#linkbox').html();
    for(var i=0; i<tot_ans; i++) {
      var id = '#sup_'+i;
      if(jQuery(id).val() != 0) {
        flag = parseInt(flag)+1;
      }
    }
    if(title.length < 2 && type == 1){
      jQuery('#deb-err').html('<span>Please let us know what you think.</span>');
      return false;
    }
    else if(flag == 0 && type == 1){
      jQuery('#deb-err').html('<span>You must choose at least one suppose or oppose.</span>');
      return false;
    }
    else if(!tomatch.test(nlink) && type == 0) {
      jQuery('#deb-err').html('<span>Please Enter a valid URL.</span>');
      return false;
    }
    else if (linkbox == '' && type == 0) {
      jQuery('#deb-err').html('<span>Please press Attach before adding.</span>');
      return false;
    }
    /*   else{
      jQuery('#add_new_debate').hide();
      jQuery('#sub_loader').show();
    }
    */
    var data=jQuery(this).serialize();
    jQuery.ajax({
      type: 'POST',
      dataType: 'json',
      url: jQuery(this).attr('action'),
      data: data,
      success: function(msg){
        var selected = $("#debate_list_area").tabs( "option", "selected" );
        jQuery('#add_debate_wrapper').slideUp('slow');
        jQuery('#add-new-debate-form select').val(0);
        jQuery('#add-new-debate-form textarea').val('');
        //  $('#debate_list_area').tabs("load", 1);
        //  $('#debate_list_area').tabs("load", 2);
        $('#debate_list_area').tabs("select", selected);
        jQuery('#deb-err').fadeIn("slow");
    
        jQuery('#deb-err').html(msg.message); 
        if(msg.success_post == 1) {
          jQuery('#deb-err').css('color','green'); 
        }

      //  jQuery(msg.content).prependTo('.comments');
      },
      complete: function(){
        jQuery('#sub_loader').hide();
        jQuery('#add_new_debate').show();
        $('#leave_comment_area').delay(5000).slideUp(400).removeClass('visible_ar').addClass('hidden_ar');
        $('#deb-err').delay(3000).slideUp(400);
        $('#add-arg').removeClass('expanded');
      }
    });
    // }
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
  $('a.permalink').click(function(e){
    var a = window.location.href.replace(/#.*/,'') + '#' +$(this).parents('.one-forum').attr('id');
    $('#permalink_text input').val(a)
    $('#permalink_text').dialog('open');
    
    return false;
  });
  $('.close-permalink').click(function(e){
    $('#permalink_text').dialog('close');
    return false;
  });
    
  var lang = $("html").attr("lang");
  var s = document.createElement('script');
  s.type='text/javascript';
  document.body.appendChild(s);
  s.src='//translate.google.com/translate_a/element.js?cb=googleSectionalElementInit&ug=section&hl='+lang;
}
