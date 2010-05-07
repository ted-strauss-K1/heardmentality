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
	 	
 	if(element.get('id')!='likelink'){
element.addEvent('click', addComment.bindWithEvent(this,element)); 
}
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
		$('waveButton').addEvent('click', addSubmit.bindWithEvent(this)); 
			$('wavecancel').addEvent('click', cancelAdd.bindWithEvent(this)); 
}


function cancelAdd(id){
	
	
	$('commentArea').fade('out');
	
	
}

function likethis(wid,el){
	
	//var myVerticalSlide = new Fx.Slide('likelink');

	
	 //	myVerticalSlide.slideOut();
	 	$('likelink').fade('out');
	//$('likelink').set('slide', {duration: 'long', transition: 'bounce:out'});
//$('likelink').slide('in');
$('likelink').slide('hide').slide('in');

		$('likelink').empty();
		
			var url = spath+'question/forum/savecmt';
									var req = new Request({    
											method: 'get'
											,url: url
											,data: { 'like':'1','wid':wid },
											onRequest: function() {$('waveerr').set('html','<b>Saving your like..!</b>'); $('waveerr').slide('hide').slide('in');},
											onComplete: function(response) {
									 $('waveerr').set('html', response);
								//	 $('waveerr').slide('hide').slide('in');
											}
									}).send();
		
		
		
		//$('waveerr').set('html','<b>Thanks for your like!</b>');
	
}




function addSubmit(){
	
	var cmt=$('waveletcmt').get('value');
	var wid=$('waveid').get('value');
	var wlid=$('wletid').get('value');
	if($('privt').checked) {
		var pvt=1;
		}else{
			var pvt=0;
		}

var myVerticalSlide = new Fx.Slide('wavelet-list');
	
	if(cmt.length>5){
	var req = new Request({
			method: 'get',
			url: 'question/forum/savecmt',
			data: { 'wid':wid,'wlet':wlid,'cmt':cmt,'pvt':pvt },
			onRequest: function() { 	$('commentArea').fade('out');	
	
		//myVerticalSlide.slideOut();
MochaUI.notification('Please wait while posting...');},
			onComplete: function(response) { 
			 MochaUI.notification('Thank you posted successfully...'); 
			 $('wavelet-list').set('html',response); 
			 	//myVerticalSlide.slideIn();
				
			 bind_clk();
			 $('privt').setProperty('checked',false);
			  $('wavelet-list').setStyle('height','auto');
			}
		}).send();
		
	}else{
		
		$('waveletcmt').setStyle('border-color','#EF2C2C');
		return false;
	}

}
