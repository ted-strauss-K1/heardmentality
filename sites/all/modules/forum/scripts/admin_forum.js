/**
 * @author gobinath.m
 */
function toggle_sub(id){

        jQuery('#q'+id).slideToggle("slow");
 		
	
	
	
	
}

function forum_del(id){
	
	if(confirm('Are you sure want to delete waves and their wavlets?')){
		
		jQuery('#fdelete').val(1);
		jQuery('#fid').val(id);
	jQuery('#fadmin').submit();
		
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


function checkall(val){


    jQuery('.check-me').each(function(){
        jQuery(this).attr('checked',val);
    });
    
}
