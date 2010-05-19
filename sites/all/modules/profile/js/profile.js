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
window.addEvent('domready', function(){


   
    
});




function profile_comment(make){

  
    var report = $('msgs').get('value');
	
alert("sssssssssss");
  
		
		    if ($('showboxcmt').getStyle('display') == 'none') {
    
        $('showboxcmt').setStyle('display', 'block');
        $('showboxcmt').slide('hide').slide('in');
        $('msgs').focus();
        return false;
    }
    if (report.trim().length < 5) {
        $('msgs').setStyle('border-color', '#EF2C2C');
        return false;
    }else{
		 $('msgs').setStyle('border-color', '');
		
	}
	
		
		
        
            
          
            $('proform').set('send', {
                onComplete: function(response){
                    var log = $('profile_page').empty().addClass('ajax-loading');
                    log.set('html', response);
                 
                }
            });
            //Send the form.
            $('proform').send();
            
       
    }
   


