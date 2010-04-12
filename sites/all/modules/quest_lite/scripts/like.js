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
