/**
 * @author admin
 */
/*
window.addEvent('domready', function() {
	
	
	$('newwavebut').addEvent('click', function(){
    
	$('newwavediv').fadeIn('in');
	
});

	
	

});

*/
	function wave_form(){
		//Prevents the default submit event from loading a new page.
		//e.stop();
		var wt=$('newwavediv').getElement('.textArea');
		var formwave=$('newwaveform');
		var post=wt.get('value');
		if(post.trim().length<8){
		
			wt.setStyle('border-color','#EF2C2C');
			wt.set('id','wtitlerror');
			return false;
		}else{
			
	wt.set('id','wtitle');	
		}
		//Empty the log and show the spinning indicator.
		//var log = $('newwavediv').empty().addClass('ajax-loading');
		//Set the options of the form's Request handler. 
		//("this" refers to the $('myForm') element).
		formwave.set('send', {
		
			
						onComplete: function(response) { 
			//log.removeClass('ajax-loading');
				$('qwave').fade('out');
			$('qwave').set('html', response);
				$('qwave').fade('in');
				wt.set('value','');
				MochaUI.notification('Wave posted successfully...!');
			
		},onRequest: function() { $('newwavediv').fade('out');MochaUI.notification('Please Wait...');}
		
		
		});
		//Send the form.
		$('newwaveform').send();
}

function toggle(){
	
	var mySlide = new Fx.Slide('newwavediv');

	
		//mySlide.toggle();
	
	$('newwavediv').fade('in');
	//$('newwavediv').fade('out');
	
}
