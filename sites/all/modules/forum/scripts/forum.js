/**
 * @author gobinath.m
 */
window.addEvent('domready', function() {
	
//$('newwaveletbut').addEvent('click', addComment.bindWithEvent(this,element)); 
	
	
	bind_clk();

});



function bind_clk(){
	
	
	
	var elements=$$('div.replyLink').getElements('a');
	
	 elements.each(function(element,index){
 	
element.addEvent('click', addComment.bindWithEvent(this,element)); 

 });
	
	
	
}


function addComment(val,el){

var wid=el.get('id');

	var gid=wid.split('-');
		 
	$('waveletcmt').setStyle('border-color','');
	$('waveletcmt').set('value','');
	$('waveid').set('value',gid[0]);	
	$('commentArea').fade('in');
	$('wletid').set('value',gid[1]);
}


function cancelAdd(id){
	
	
	$('commentArea').fade('out');
	
	
}

function addSubmit(){
	
	var cmt=$('waveletcmt').get('value');
	var wid=$('waveid').get('value');
	var wlid=$('wletid').get('value');
	if(cmt.length>5){
	var req = new Request({
			method: 'get',
			url: 'question/forum/savecmt',
			data: { 'wid':wid,'wlet':wlid,'cmt':cmt },
			onRequest: function() { 	$('commentArea').fade('out');	MochaUI.notification('Please wait while posting...');},
			onComplete: function(response) { 
			 MochaUI.notification('Thank you posted successfully...'); 
			 $('wavelet-list').set('html',response); 
			 bind_clk();
			}
		}).send();
		
	}else{
		
		$('waveletcmt').setStyle('border-color','#EF2C2C');
		return false;
	}

}
