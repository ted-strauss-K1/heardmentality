/**
 * @author gobinath.m
 */
//window.addEvent('domready', function(){
//
//
//
//
//});




function get_Reply(make){
    var vals = [];
//    $$('.check-me').each(function(e){
//		if(e.getProperty('checked')){
//
//			  vals.push(e.value);
//		}
//
//    });
 
	 //if (vals.length > 0) {
        if($(":checkbox:checked").length) {
    var report = $('cmt_txt').get('value');
	
    if ($('showbox_cmt').getStyle('display') == 'none') {
    
        $('showbox_cmt').setStyle('display', 'block');
        $('showbox_cmt').slide('hide').slide('in');
        $('showbox_cmt').focus();
        return false;
    }
    if (report.trim().length < 5) {
        $('cmt_txt').setStyle('border-color', '#EF2C2C');
        return false;
    }else{
		 $('cmt_txt').setStyle('border-color', '');
		
	}
   
            $('action').set('value', make);
            
            $('cmtform').set('send', {
                onComplete: function(response){
                    var log = $('clist').empty().addClass('ajax-loading');
                    log.set('html', response);
                   
                }
            });
            //Send the form.
            $('cmtform').send();
            
        }
            else {
            
                alert('select atleast one user To send message !');
                return false;
            }
   
    
}




function get_votes(make){

    var vals = [];
    $$('.check-me').each(function(e){
		if(e.getProperty('checked')){
			  vals.push(e.value);
		}
      
    });
	  $('showbox_cmt').setStyle('display', 'none');
   
   
            $('action').set('value', make);
            
            $('cmtform').set('send', {
                onComplete: function(response){
                    var log = $('clist').empty().addClass('ajax-loading');
                    log.set('html', response);
                   
                }
            });
            //Send the form.
            $('cmtform').send();   
}
function loadwave(qid,wid){
	url= gSitePath+'question/forum/?qid='+qid+'&wid='+wid;
	jQuery.nyroModalSettings({ title:'Forum Posts'});
  var options = 'sameBox:true width:70% height:90% caption:' +
  '`Forum Posts`';
  parent.fb.start(url, options);
            //jQuery.nyroModalManual({
   // url: url,width:550,height:450,title:'Forum Posts'
 // });
//return hs.htmlExpand(url, { outlineType: 'rounded-white',wrapperClassName: 'draggable-header', objectType: 'iframe' } );
}