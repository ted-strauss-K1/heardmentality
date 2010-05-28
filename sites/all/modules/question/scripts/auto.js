function suggest(inputString){
	
	var inputString=$('q_quest').get('value');

	if (inputString.length == 0) {
		$('suggestions').fade('out');
	}
	else {
	
	$('q_quest').addClass('load');
	
		var urr=mpath+'autosuggest?action=tag';
		var req = new Request({    
			method: 'post',
			url: urr,
			data: {
				queryString: inputString
			},
			onComplete: function(response){
			$('suggestionsList').set('html', response);
			$('suggestions').fade('in');

			$('q_quest').removeClass('load');
		}
		}).send();

		
	}
}
    function fillout(thisValue) {
		
		
			
			 <!-- $('q_quest').set('value',thisValue);
        //setTimeout("$('suggestions').fade('out')", 600);-->
		window.top.location.href=mpath+thisValue;
      
    }

	
	
	





