

  
  
  
  
  function addJavascript(jsname,pos) {
var th = document.getElementsByTagName(pos)[0];
var s = document.createElement('script');
s.setAttribute('type','text/javascript');
s.setAttribute('src',jsname);
th.appendChild(s);
} 


addJavascript('http://www.plaxo.com/css/m/js/util.js','head'); 
addJavascript('http://www.plaxo.com/css/m/js/basic.js','head'); 
addJavascript('http://www.plaxo.com/css/m/js/abc_launcher.js','head'); 


	window.addEvent('domready', function() {
	
	$('inviteform').addEvent('submit', function(e) {
		//Prevents the default submit event from loading a new page.
		e.stop();
		//Empty the log and show the spinning indicator.
		var log = $('log_res').empty().set('html','<b>Loading...</b>');
		var myVerticalSlide = new Fx.Slide('inviteform');
		myVerticalSlide.slideOut();
		//Set the options of the form's Request handler. 
		//("this" refers to the $('myForm') element).
		this.set('send', {onComplete: function(response) { 
			//log.removeClass('ajax-loading');
			if(response=='1'){
					log.set('html', '<b>Invitation Sent Successfully!</b>');
					window.parent.location.reload();
			}else{
				
			log.set('html', '<b>Sorry invitation sending failed!</b>');	
			}
		
			
		}});
		//Send the form.
		this.send();
	});
});
	