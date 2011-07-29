/**
 * @author gobinath.m
 */
function get_filter_option(type){
	
	var url=spath+'qlite/ajax?action=filter';


	jQuery('#fopt').html('');
		jQuery.ajax({
   type: "POST",
   url: url,
    data: {
            type: type
   
        },
   success: function(msg){
	jQuery('#fopt').html(msg);
   }
 });	
	
}


function MM_jumpMenuGo(){ 
document.form1.submit();
}

jQuery(document).ready(function(){

    search_iss_trig();
})

function search_iss_trig(){
    jQuery('#subject').trigger('change');
    setTimeout(subcatSet,3000);
    jQuery('#s_country').trigger('change');
    setTimeout(substate,3000);
}
function subcatSet(){
    jQuery('#area').trigger('change');
}
function substate(){
    jQuery('#s_state').trigger('change');
}

// open suggest answer form
    jQuery('#sugg-btn').live('click',function(){
        jQuery('#sugg-form').slideToggle('fast');
    });
jQuery(document).ready(function() {
    // suggest answer text box
    jQuery('#sugg_ans').hide();
    jQuery('#sugg_ans_dum').show();
    
    jQuery('#sugg_ans_dum').focus(function() {
        $(this).hide();
        jQuery('#sugg_ans').show();
        jQuery('#sugg_ans').focus();
    });
    jQuery('#sugg_ans').blur(function(){
        if(jQuery('#sugg_ans').val().length == 0){
            jQuery('#sugg_ans').hide();
            jQuery('#sugg_ans_dum').show();
        }
    });

    jQuery('#canc').live('click', function() {
        jQuery('#sugg-form').slideUp('fast');
    });  
})
// open add new debate form
 jQuery('#addnew_debate').live('click',function(){
        jQuery('#submitted-msg').html('');
        jQuery('#deb-err').html('');
        jQuery('#add_debate_wrapper').slideToggle('slow');
       
    });

jQuery.fn.slideFadeToggle = function(speed, easing, callback) {
  return this.animate({opacity: 'toggle', height: 'toggle'}, speed, easing, callback);
};


// add new debate validation
jQuery('#add_new_debate').live('click', function(){
    var title = jQuery('#deb_title').val();
    var tot_ans = jQuery('#tot_ans').val();
    var flag = 0;
    if(title == ''){
        jQuery('#deb-err').html('Please let us know what you think.');
        return false;
    }
    for(var i=0; i<tot_ans; i++){
        var id = '#sup_'+i;
        if(jQuery(id).val() == 0 || jQuery(id).val() == ''){
            flag = parseInt(flag)+1;
        }
    }
   
    if(flag > 1){
        jQuery('#deb-err').html('You must choose atleast one suppose or oppose.');
        return false;
    }
    jQuery(this).hide();
    jQuery('#sub_loader').show();
});

// add new debate ajax submit
jQuery('#add-new-debate-form').live('submit', function(e){
    e.preventDefault();
    var data=jQuery(this).serialize();
    jQuery.ajax({
      type: 'POST',
      dataType: 'json',
      url: jQuery(this).attr('action'),
      data: data,
      success: function(msg){
          jQuery('#add_debate_wrapper').slideUp('slow');
          //jQuery('#add-new-debate-form').clearForm();
          jQuery('#add-new-debate-form select').val(0);
          jQuery('#add-new-debate-form textarea').val('');

          jQuery('#submitted-msg').fadeIn("slow");
          jQuery('#submitted-msg').html(msg.message);
          //jQuery('#add_debate_wrapper').append(msg.content);
          jQuery(msg.content).prependTo('#issue_debate_list');
      },
      complete: function(){
          jQuery('#sub_loader').hide();
          jQuery('#add_new_debate').show();
      }
    });
});


// forum reply

function open_replybox(id){
  var spl = id.split("_");
  var open_id = '#reply_box_'+spl[2];
  jQuery(open_id).slideToggle('slow');
}

function show_replies(id){
  var spl = id.split("_");
  var open_id = '#all_replybox_'+spl[2];
  jQuery(open_id).slideToggle('slow');
}

