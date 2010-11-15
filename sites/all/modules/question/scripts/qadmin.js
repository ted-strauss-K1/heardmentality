
/**
 * @author gobinath.m
 */
jQuery(document).ready(function(){


    // setTimeout('admin_approve();', 5000);
    
    });




jQuery(document).ready(function(){
    jQuery('#qadmin').live('submit',function(){
        
        var vals = [];
        jQuery('.check-me:checked').each(function(){
            var e=jQuery(this);
            vals.push(e.val());
                
        });
            
        if (vals.length > 0) {
      
            var formwave=jQuery(this);
            jQuery.post(formwave.attr('action'),formwave.serialize(),
                function(data){
                    jQuery('#qlist').empty().html(data);
                    
                });
			   
			    
        }
        else {
            
            alert('select atleast one question for action!');
           
        }
          return false;
    });
        
    
        
});
    


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
           // jQuery('#actions').attr('value', make);
     
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


function admin_sendwarning(make){

    var vals = [];
    jQuery('.check-user').each(function(){
        var e=jQuery(this);
        if (e.attr('checked')) {
        
            vals.push(e.value);
        }
        
    });
    var report = jQuery('#reporttext').val();
    
    
    if (vals.length>0) {
    
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
        
        
        
        if (confirm('Are you sure send warning message')) {
            jQuery('#actions').attr('value', make);
                 
            //send form
            var formwave=jQuery('#notify');
            jQuery.post(formwave.attr('action'),formwave.serialize(),
          
                function(data){
                   
                    jQuery('#list').empty().html(data);
                    setTimeout('admin_approve();', 1000);
                });
		 
        }
        else {
            return false;
        }
    }
    else {
    
        alert('select atleast one question for action');
        return false;
    }
    
}

function send_suspend(make){

    var vals = [];
    jQuery('.check-user').each(function(){
        var e=jQuery(this);
        if (e.attr('checked')) {
        
            vals.push(e.value);
        }
        
    });
    var report = jQuery('#reporttext').val();
    
    
    if (vals.length>0) {
    
        /*if (jQuery('#showbox').css('display') == 'none') {
        
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
            
        }*/
        
        
        
        if (confirm('Are you sure send warning message')) {
            jQuery('#actions').attr('value', make);
     
            //send form
            var formwave=jQuery('#notify');
            jQuery.post(formwave.attr('action'),formwave.serialize(),
                function(data){
                    jQuery('#list').empty().html(data);
                    setTimeout('admin_approve();', 1000);
                });
		
		    
        }
        else {
            return false;
        }
    }
    else {
    
        alert('select atleast one question for action');
        return false;
    }
    
}




function checkall(val){


    jQuery('.check-me').each(function(){
        jQuery(this).attr('checked',val);
    });
    
}
