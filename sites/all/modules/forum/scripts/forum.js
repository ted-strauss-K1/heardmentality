/**
 * @author gobinath.m
 */
window.addEvent('domready', function() {
	
$('newwaveletbut').addEvent('click', addComment.bindWithEvent(this,element)); 
	
	

});


function addComment(wid,wlet){
		$('waveletcmt').setStyle('border-color','');
		$('waveletcmt').set('value','');
	$('waveid').set('value',wid);	
	$('commentArea').fade('in');
	$('wletid').set('value',wlet);
	$('waveletcmt').focus();
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
			onComplete: function(response) {  MochaUI.notification('Thank you posted successfully...'); $('wavelet-list').set('html',response); }
		}).send();

	}else{
		
		$('waveletcmt').setStyle('border-color','#EF2C2C');
	}
	
}
