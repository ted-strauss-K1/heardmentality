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


