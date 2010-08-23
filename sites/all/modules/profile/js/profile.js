function validate_profile(){
    var facebook = $('edit-facebook').value;
    var twitter = $('edit-twitter').value;

    var RegExp = /^(([\w]+:)?\/\/)?(([\d\w]|%[a-fA-f\d]{2,2})+(:([\d\w]|%[a-fA-f\d]{2,2})+)?@)?([\d\w][-\d\w]{0,253}[\d\w]\.)+[\w]{2,4}(:[\d]+)?(\/([-+_~.\d\w]|%[a-fA-f\d]{2,2})*)*(\?(&?([-+_~.\d\w]|%[a-fA-f\d]{2,2})=?)*)?(#([-+_~.\d\w]|%[a-fA-f\d]{2,2})*)?$/;
	if(facebook !=''){
    if(!(RegExp.test(facebook))){
		alert('Please enter the valid URL format for Facebook');
        return false;
    }
	}
	if(twitter !=''){
    if(!(RegExp.test(twitter))){
		alert('Please enter the valid URL format for Twitter');
        return false;
    }

	}
    return true;
    
}




/**
 * @author gobinath.m
 */

  

function profile_comment(make){

jQuery(document).ready(function(){
	jQuery("#usmsg").unbind("click");

 jQuery("#usmsg").click(function () { 
 var formmsg=jQuery('#proform');
    jQuery.post(formmsg.attr('action'),formmsg.serialize(),
   function(data){
        jQuery('.rht_link').css('width','auto');
         jQuery('.rht_link').css('overflow','hidden');
    jQuery('.rht_link').prepend(data);
	  jQuery('#showboxcmt').slideToggle("slow");
	  formmsg.get(0).reset();
          setTimeout("jQuery('.rht_link > div.messages').hide();",1000);
   });
    });
});
 
 
    var report = jQuery('#msgs').val();
	
		
		  jQuery('#showboxcmt').slideToggle("slow");
        jQuery('#msgs').focus();
        return false;
  
    if (report.trim().length < 5) {
        jQuery('msgs').css('border-color', '#EF2C2C');
        return false;
    }else{
		 jQuery('#msgs').css('border-color', '');
		
	}

    }
   
function get_zip_city(code){
	
	var urr=spath+'qlite/ajax?action=zipcity';
		var req = new Request({    
			method: 'post',
			url: urr,
			data: {
			code: code
          	},
			onComplete: function(response){
		        $('edit-city-wrapper').set('html', response);
				 	
		}
		}).send();
	
	
}

function del_msg(ids,tr){

    var urr=gSitePath+'profile/inbox';

		jQuery.ajax({
   type: "POST",
   url: urr,
   dataType:'xhr',
  data: {
	id: ids,action:'delete'
          	},
		 success: function(msg){
    jQuery('.profile_part').prepend(msg);
    jQuery(tr).parents('tr').fadeOut('slow');
    setTimeout("window.location.reload();",3000);
   }
 });

}

function rel_msg(id){

jQuery('#actions').val(id);
jQuery('#showboxcmt').slideToggle('slow');
 jQuery("#usmsg").unbind("click");

 jQuery("#usmsg").click(function () {
 var formmsg=jQuery('#proform');
    jQuery.post(formmsg.attr('action'),formmsg.serialize(),
   function(data){
     
    jQuery('.profile_part').prepend(data);
	  jQuery('#showboxcmt').slideToggle("slow");
	  formmsg.get(0).reset();
          setTimeout("jQuery('.profile_part > div.messages').hide();",1000);
   });
    });
}