function suggest(inputString){
	
	var inputString=$('q_quest').get('value');

	if (inputString.length == 0) {
		$('suggestions').fade('out');
	}
	else {
	
	$('q_quest').addClass('load');
		var urr='http://localhost/heardmentality/autosuggest?action=tag';
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
    function fill(thisValue) {
		
		
			
			 <!-- $('q_quest').set('value',thisValue);
        //setTimeout("$('suggestions').fade('out')", 600);-->
		window.top.location.href="http://localhost/heardmentality/"+thisValue;
      
    }

	
	
	

window.addEvent('domready', function() {
	
	bind_event();
	bind_event_added();
	//bind event for input filed tag
	var intag=$('q_quest');
	intag.addEvent('keyup',suggest.bindWithEvent(this));
	
		var addbut=$$('a.tagging-button-container');

	addbut.addEvent('click',tag_add_input.bindWithEvent(this));
	
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
	

}


function bind_event_added(){
	var elements = $('tagdiv').getElements('div');
	
 elements.each(function(element,index){
 		
element.addEvent('click', tag_delq.bindWithEvent(this,element)); 
 });
	

}






function tag_add_input(val){
	
	var context=$('q_quest').get('value');
	
	if(context.length>0){
		var etarget=$('tagdiv');
	//set the tag
	 var ele = new Element('div',{ id : 'tagset','onclick':'tag_delq(this);return false;'
	 	 
	 }).inject(etarget);
			ele.addClass('tagging-tag');
			ele.addClass('inp');
			ele.set('text',context);
	}
	$('q_quest').set('value','');
	
	bind_event_added();
	insert_tag();
	
}

function tag_add(val,el){
	
	
	var context=el.get('text').trim();
	el.destroy();
	var elements =$$('div.tagging-curtags-wrapper');
	var etarget=$('tagdiv');
	if (context != '') {
		//set the tag
		var ele = new Element('div', {
			id: 'tagset',
			'onclick': 'tag_delq(this);return false;'
		
		}).inject(etarget);
		ele.addClass('tagging-tag');
		ele.set('text', context);
		bind_event_added();
		insert_tag();
	}
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
	
function tag_delq(val,el){
	
	var val = el;
	
	var result = val.hasClass('inp');
		if (!result) {

		var context = val.get('text');
		val.destroy();
		
		var etarget = $('sug_div');
		if (context != '') {
			//set the tag
			var ele = new Element('div', {
				id: 'stag'
			
			}).inject(etarget);
			
			ele.addClass('tagging-suggest-tag');
			ele.set('text', context);
			bind_event();
		}
	}else {
		
		val.destroy();
	}	
		
		
	insert_tag();			
}


