function suggest(inputString){
	
	var string=inputString;
	if (inputString.length == 0) {
		$('suggestions').fade('out');
	}
	else {
	
	$('tagging-widget-input-1').addClass('load');
		var urr=mpath+'qlite/ajax?action=tag';
		var req = new Request({    
			method: 'post',
			url: urr,
			data: {
				queryString: inputString
			},
			onComplete: function(response){
			$('suggestionsList').set('html', response);
			$('suggestions').fade('in');

			$('tagging-widget-input-1').removeClass('load');
		}
		}).send();

		
	}
}
    function fill(thisValue) {
		
		
			
			  $('tagging-widget-input-1').set('value',thisValue);
        setTimeout("$('suggestions').fade('out')", 600);
		
      
    }

	
	window.addEvent('domready', function() {
	
	$('retagform').addEvent('submit', function(e) {
		//Prevents the default submit event from loading a new page.
		e.stop();
		//Empty the log and show the spinning indicator.
		var log = $('log_res').empty().addClass('ajax-loading');
		//Set the options of the form's Request handler. 
		//("this" refers to the $('myForm') element).
		this.set('send', {onComplete: function(response) { 
			//log.removeClass('ajax-loading');
			
			log.set('html', response);
		}});
		//Send the form.
		this.send();
	});
});
	

window.addEvent('domready', function() {
	
	bind_event();
	
	
	
	
});

function bind_event(){
	var elements = $$('div.tagging-suggest-tag');
	var el = $('tagging-widget-container').getElements('a');
/*
	
	//alert(elements);
	elements.addEvent('click', tag_add.bindWithEvent(this,elements)); 
	//elements.addLiveEvent('click', 'a', function(e){ alert('This is a live event'); });
	
*/
for(var i = 0 ; i < el.length ; i = i + 1)
{
 
  
	el[i].set('href','#');
}

 elements.each(function(element,index){
 		
element.addEvent('click', tag_add.bindWithEvent(this,element)); 
 });
	
	var addbut=$$('a.tagging-button-container');
	
	addbut.addEvent('click',tag_add_input.bindWithEvent(this));
}

function tag_add_input(val){
	
	var context=$('tagging-widget-input-1').get('value');
	
	if(context.length>0){
		var etarget=$('tagdiv');
	//set the tag
	 var ele = new Element('div',{ id : 'tagset','onclick':'tag_delq(this);return false;'
	 	 
	 }).inject(etarget);
			ele.addClass('tagging-tag');
			ele.addClass('inp');
			ele.set('text',context);
	}
	$('tagging-widget-input-1').set('value','');
	insert_tag();
}

function tag_add(val,el){
	
	
	var context=el.get('text');
	el.destroy();
	var elements =$$('div.tagging-curtags-wrapper');
	var etarget=$('tagdiv');
	
	//set the tag
	 var ele = new Element('div',{ id : 'tagset','onclick':'tag_delq(this);return false;'
	 	 
	 }).inject(etarget);
			ele.addClass('tagging-tag');
			ele.set('text',context);
	
	insert_tag();		
	}
	
	function insert_tag(){
		
		var myArray=new Array();
		var elements =$$('div.tagging-tag');
		
		elements.each(function(element,index){
 		
		myArray.extend([element.get('text').trim()]);
	
 });
		
		
var rtag=myArray.join(',');
rtag.clean();
$('q_tag').set('value',rtag);
	}
	
function tag_delq(val){
	
	var result = val.hasClass('inp');

	if (!result) {
	
		var context = val.get('text');
		val.destroy();
		
		var etarget = $('sug_div');
		
		//set the tag
		var ele = new Element('div', {
			id: 'stag'
		
		}).inject(etarget);
		
		ele.addClass('tagging-suggest-tag');
		ele.set('text', context);
		bind_event();
		
	}else {
		
		val.destroy();
	}	
				
	insert_tag();			
}


