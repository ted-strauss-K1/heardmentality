/**
 * @author gobinath.m
 */
function checkall(val){


    $$('.check-me').each(function(el){
        el.checked = val;
    });
    
}


function toggle_sub(id){
	
	
	  if ($('q'+id).getStyle('display') == 'none') {
    
        $('q'+id).setStyle('display', 'block');
       $('q'+id).slide('hide').slide('in');
      
           }else{
		   $('q'+id).setStyle('display', 'none');
        $('q'+id).slide('hide').slide('out');
 		
		   }

	
	
	
}
