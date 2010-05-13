/**
 * @author gobinath.m
 */
window.addEvent('domready', function(){


    
    
});




function get_Reply(make){

    var vals = [];
    $$('.check-me:checked').each(function(e){
        vals.push(e.value);
    });
    
    var report = $('cmt_txt').get('value');
	
    if ($('showbox_cmt').getStyle('display') == 'none') {
    
        $('showbox_cmt').setStyle('display', 'block');
        $('showbox_cmt').slide('hide').slide('in');
        $('reporttext').focus();
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
                    var log = $('qlist').empty().addClass('ajax-loading');
                    log.set('html', response);
                   
                }
            });
            //Send the form.
            $('cmtform').send();
            
        
   
    
}



