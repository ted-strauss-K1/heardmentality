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

  //trigger search filters
     //   search_iss_trig();
//for IE
        // setTimeout(resetFields,3000);
        //  jQuery('#subject').change();
      //   jQuery('#subject').val("3");
sendEvent(jQuery('#subject'),'change');//assuming there is a select element
jQuery('#subject').fireEvent("onchange");

});

function sendEvent(ele,e){
	try{// every browser except IE8 and below works here
		var evt = document.createEvent("HTMLEvents");
		evt.initEvent(e, true, true);
		ele.dispatchEvent(evt);
	}
	catch(err){
		ele.fireEvent('on'+e);
	}
}


// open suggest answer form
    jQuery('#sugg-btn').live('click',function(){
        jQuery('#sugg-form').slideToggle('fast');
    });

jQuery('#canc').live('click', function() {
        jQuery('#sugg-form').slideUp('fast');
    });

// open add new debate form
 jQuery('#addnew_debate').live('click',function(){
        jQuery('#submitted-msg').html('');
        jQuery('#deb-err').html('');
        jQuery('#add_debate_wrapper').slideToggle('slow');
       
    });

jQuery.fn.slideFadeToggle = function(speed, easing, callback) {
  return this.animate({opacity: 'toggle', height: 'toggle'}, speed, easing, callback);
};




// add new debate ajax submit
jQuery('#add-new-debate-form').live('submit', function(e){
    e.preventDefault();


    var title = jQuery('#deb_title').val();
    var tot_ans = jQuery('#tot_ans').val();
    var flag = 0;
    for(var i=0; i<tot_ans; i++){
        var id = '#sup_'+i;
        if(jQuery(id).val() != 0){
            flag = parseInt(flag)+1;
        }
    }

    if(title.length < 2){
        jQuery('#deb-err').html('Please let us know what you think.');
        return false;
    }else if(flag == 0){
        jQuery('#deb-err').html('You must choose atleast one suppose or oppose.');
        return false;
    }else{
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
    }
    return false;
});


// forum reply

function open_replybox(id){
  var spl = id.split("_");
  var open_id = '#reply_box_'+spl[2];
  var msgid = '#reply-msg-'+spl[2];
  jQuery(msgid).html('');
  jQuery(open_id).slideToggle('slow');
}

function show_replies(id){
  var spl = id.split("_");
  var open_id = '#all_replybox_'+spl[2];
  jQuery(open_id).slideToggle('slow');
}



jQuery('.arg-reply-form').live('submit', function(e){
    e.preventDefault();

    var cont = jQuery(this);
    var debid = cont.find('#ded_tnid').val();
    var norep = "#no_rply_"+debid;
    if(cont.find('textarea').val().length<2){
        cont.find('#reply_err').html('Please enter your reply');
    }else{
        cont.find('#add_reply').hide();
        cont.find('#sub_loader').show();
        var data = cont.serialize();
        var ded_tnid = cont.find('#deb_tnid').val();
        var box_id = '#reply_box_'+ded_tnid;
        var open_id = '#all_replybox_'+ded_tnid;
        jQuery.ajax({
            type: 'POST',
            dataType: 'json',
            url: cont.attr('action'),
            data: data,
            success: function(msg){
                cont.find('textarea').val('');
                jQuery(box_id).slideUp('slow');
                jQuery(norep).remove();
                jQuery(msg.content).prependTo(open_id);
                jQuery(open_id).slideDown('slow');
                jQuery('#reply-msg-'+ded_tnid).html(msg.message);
            },
            complete: function(){
                cont.find('#add_reply').show();
                cont.find('#sub_loader').hide();
                cont.find('#reply_err').html('');
            }
        });
    }
    return false;
});


function delete_thread(id){
    var spl = id.split("_");
    var fid  = spl[2];
    var dtype = spl[1];
    //var msgid = '#reply-msg-'+fid;
    
    var url = spath+'issue/thread/delete/'+dtype+'/'+fid;
    if(confirm("Are you sure to delete this argument?")){
    jQuery.ajax({
        type: 'post',
        url: url,
        success: function(msg){
          
        },
        complete: function(){
           var bid = '#'+dtype+'-block-'+fid;
           jQuery(bid).remove();
        }
    });
    return true;
    }else{
        return false;
    }
}
