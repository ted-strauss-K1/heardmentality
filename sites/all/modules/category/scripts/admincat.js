/**
 * @author gobinath.m
 */
function checkall(val){


    jQuery('.check-me').each(function(el){
        el.checked = val;
    });
    
}


function toggle_sub(id){
	
	
	  if (jQuery('#q'+id).css('display') == 'none') {
    
        jQuery('#q'+id).css('display', 'block');
       jQuery('#q'+id).sildeDown('slow');
      
           }else{
		   jQuery('#q'+id).css('display', 'none');
        jQuery('#q'+id).slideUp('slow');
 		
		   }

	
	
	
}
