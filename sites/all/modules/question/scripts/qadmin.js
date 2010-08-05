
/**
 * @author gobinath.m
 */
jQuery(document).ready(function(){


    setTimeout('admin_approve();', 5000);
    
});


function admin_approve(make){

    jQuery(document).ready(function(){
        jQuery('#qadmin').submit(function(){
        
            var vals = [];
            jQuery('.check-me').each(function(){
				var e=jQuery(this);
                if (e.getProperty('checked')) {
                
                    vals.push(e.value);
                }
                
                
            });
            
            if (vals.length > 0) {
                //Prevents the default submit event from loading a new page.
                
                //Empty the log and show the spinning indicator.
                
                //Set the options of the form's Request handler. 
                //("this" refers to the $('myForm') element).
                
             /*
   this.set('send', {
                    onComplete: function(response){
                    
                        var log = jQuery('#qlist').empty().addClass('ajax-loading');
                        log.set('html', response);
                        setTimeout('admin_approve();', 1000);
                    }
                });
                //Send the form.
                
                this.send();
*/
               
			      var formwave=jQuery(this);
		jQuery.post(formwave.attr('action'),formwave.serialize(),
   function(data){
   jQuery('#qlist').empty().html(data);
	 setTimeout('admin_approve();', 1000);
   });
			   
			    
            }
            else {
            
                alert('select atleast one question for action!');
                return false;
            }
            
        });
        
        
        
    });
    
}

function admin_reject(make){

    var vals = [];
    jQuery('.check-me').each(function(){
		var e=jQuery(this);
        if (e.attr('checked')) {
        
            vals.push(e.value);
        }
        
    });
    
    var report = jQuery('#reporttext').val();
    
    
    if (vals.length > 0) {
    
        if (jQuery('#showbox').css('display') == 'none') {
        
            jQuery('#showbox').css('display', 'block');
            jQuery('#showbox').slideDown('slow');
           jQuery('#reporttext').focus();
            return false;
        }
        if (jQuery.trim(report).length < 5) {
            jQuery('reporttext').css('border-color', '#EF2C2C');
            return false;
        }
        else {
            jQuery('reporttext').css('border-color', '');
            
        }
        
        
        
        if (confirm('Are you sure to reject the selected Questions?')) {
            jQuery('#actions').attr('value', make);
     
	 //send form       
          var formwave=jQuery('#qadmin');
		jQuery.post(formwave.attr('action'),formwave.serialize(),
   function(data){
   jQuery('#qlist').empty().html(data);
	 setTimeout('admin_approve();', 1000);
   });
		
		    
        }
        else {
            return false;
        }
    }
    else {
    
        alert('select atleast one question for action!');
        return false;
    }
    
}


function checkall(val){


    jQuery('.check-me').each(function(){
		    jQuery(this).attr('checked',val);
    });
    
}
