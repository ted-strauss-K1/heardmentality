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
            type: type,
   
        },
   success: function(msg){
	jQuery('#fopt').html(msg);
   }
 });	
	
}


function MM_jumpMenuGo(){ 
document.form1.submit();
}