/**
 * @author gobinath.m
 */
function get_toplist(sid,level){
	cid=$('tcat').get('value');
	if(level==2){
			scid=sid;
		

	}else{
		
		scid='';
	}
		var url = 'qmini/ajax';
									var req = new Request({    
											method: 'post'
											,url: url
											,data: { 'action':level,'cid':cid,'scid':scid},
											onRequest: function() { $('res_top').set('html', 'Loading...'); },
											onComplete: function(response) {
													 $('res_top').set('html', response);
											}
									}).send();
	
	if(level==1){
	var req = new Request({    
											method: 'post'
											,url: url
											,data: { 'action':5,'cid':cid},
											onRequest: function() { $('res_top').set('html', 'Loading...'); },
											onComplete: function(response) {
													 $('res_scat').set('html', response);
											}
									}).send();
	
	}
	
}
