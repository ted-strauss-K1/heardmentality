/**
 * @author admin
 */
function addwave(qid){
	
	
	$('loader').fade('in');
	$('qwave').fade('out');
	var req = new Request({    
			method: 'post',
			url: urr,
			data: {
				queryString: inputString
			},
			onComplete: function(response){
			$('').set('html', response);
			$('qwave').fade('in');
			$('loader').fade('out');
			$('tagging-widget-input-1').removeClass('load');
		}
		}).send();
	
	
	
	
}


