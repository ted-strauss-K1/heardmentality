/**
 * @author gobinath.m
 */
function get_filter_option(type){
	
	var urr=spath+'qlite/ajax?action=filter';
		var req = new Request({    
			method: 'post',
			url: urr,
			data: {
			type: type,
          	},
			onRequest: function() {$('fopt').set('html', 'loading...'); },
			onComplete: function(response){
				
		        $('fopt').set('html', response);
				 	
		}
		}).send();

	
	
	
}


function MM_jumpMenuGo(){ 
document.form1.submit();
}