// JavaScript Document
function tabactive(pmID, pmPath,id)
{
	$('tab1').set('class', '');
	$('tab2').set('class', '');
	$('tab3').set('class', '');
	
	$('tab'+pmID).set('class', 'active');
		if(pmID == 1)
		vPath=pmPath+"qlite/innews/"+id
	else if(pmID == 2)
		vPath=pmPath+"qlite/media/"+id
	else if(pmID == 3)
		vPath=pmPath+"qlite/facts/"+id
	var req = new Request({
				method: 'get',
				url: vPath,
				data: { },
 				onRequest: function() {$('contents').set('html', 'Please wait...'); },
				onComplete: function(response) {
					$('contents').set('html', response);
 				}
	}).send();
}