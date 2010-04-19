/**
 * @author admin
 */


window.addEvent('domready', function() {
	
	 var selObj = $('vote-up');
  selObj.addEvent('click',function()
  {
  qns_like(1);
  }); 	
	  var selObj = $('vote-down');
  selObj.addEvent('click',function()
  {
qns_like(0);
  }); 	
	
});

function qns_like(type,qid){


    var url = spath + 'qlite/like';
    var req = new Request({
        method: 'get',
        url: url,
        data: {
            'qns': qid,
            'type': type            
        },
        onRequest: function(){
        },
        onComplete: function(response){
            $('vote-cnt').set('text', response);
        }
    }).send();
    
}

function resource_like(rid,uid,rtype){

		var urr=spath+'qlite/ajax?action=resource';
		var req = new Request({    
			method: 'post',
			url: urr,
			data: {
			rid: rid,
			uid: uid,
           rtype:rtype
			},
			onComplete: function(response){
		        $('resource-fact').set('html', response);
				 $('resource-message').set('html', response);
	
		}
		}).send();;
    
}