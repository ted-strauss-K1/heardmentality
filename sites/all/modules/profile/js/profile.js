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
 jQuery("#usmsg").click(function () { 
 var formmsg=jQuery('#proform');
    jQuery.post(formmsg.attr('action'),formmsg.serialize(),
   function(data){
    jQuery('.rht_link').prepend(data);
	  jQuery('#showboxcmt').slideToggle("slow");
	  formmsg.get(0).reset();

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
			code: code,
          	},
			onComplete: function(response){
		        $('edit-city-wrapper').set('html', response);
				 	
		}
		}).send();
	
	
}

