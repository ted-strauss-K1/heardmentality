/**
 * @author gobinath.m
 */
function toggle_sub(id){
	
	
	  if ($('q'+id).getStyle('display') == 'none') {
    
        $('q'+id).setStyle('display', 'block');
       $('q'+id).slide('hide').slide('in');
      
           }else{
		   $('q'+id).setStyle('display', 'none');
        $('q'+id).slide('hide').slide('out');
 		
		   }

	
	
	
}

function forum_del(id){
	
	if(confirm('Are you sure want to delete waves and their wavlets?')){
		
		$('fdelete').set('value',1);
		$('fid').set('value',id);
	$('fadmin').submit();
		
	}else{
		
		return false;
	}
	
}

function wavelet_del(id){
	if(confirm('Are you sure want to delete this wavlet?')){
		
		$('fdelete').set('value',1);
		$('fid').set('value',id);
	$('fadmin').submit();
		
	}else{
		
		return false;
	}
	
	
}
