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
    $('#add_new_type').val(0);
    return false;
  });
});

// add new debate ajax submit
jQuery('#add-new-debate-form #add_new_debate').live('submit', function(e){
  e.preventDefault();
  jQuery('#deb-err').css('color','red');
  var title = jQuery('#deb_title').val();
  var tot_ans = jQuery('#tot_ans').val();
  var flag = 0;
  for(var i=0; i<tot_ans; i++){
    var id = '#sup_'+i;
    if(jQuery(id).val() != 0) {
      flag = parseInt(flag)+1;
    }
  }
  /* if(title.length < 2){
    jQuery('#deb-err').html('<span>Please let us know what you think.</span>');
    return false;
  }
  else if(flag == 0){
    jQuery('#deb-err').html('<span>You must choose at least one suppose or oppose.</span>');
    return false;
  }*/
  // else{
  jQuery('#add_new_debate').hide();
  jQuery('#sub_loader').show();
  var data=jQuery(this).serialize();
  jQuery.ajax({
    type: 'POST',
    dataType: 'json',
    url: jQuery(this).attr('action'),
    data: data,
    success: function(msg){
      jQuery('#add_debate_wrapper').slideUp('slow');
      jQuery('#add-new-debate-form select').val(0);
      jQuery('#add-new-debate-form textarea').val('');
      $('#debate_list_area').tabs("load", 1);
      $('#debate_list_area').tabs("load", 2);
      $('#debate_list_area').tabs("select", 1);
      console.log(msg);
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


$(document).ready(function() {
  $('#inc_ref').change(function(){
    $('.resources').toggle();
  });

  $( "#debate_list_area" ).tabs({
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
