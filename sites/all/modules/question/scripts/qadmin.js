/**
 * @author gobinath.m
 */
window.addEvent('domready', function(){


    setTimeout('admin_approve();', 1000);
    
});


function admin_approve(make){

    window.addEvent('domready', function(){
        $('qadmin').addEvent('submit', function(e){
        
            e.stop();
            var vals = [];
            $$('.check-me:checked').each(function(e){
                vals.push(e.value);
            });
            
            if (vals.length > 0) {
                //Prevents the default submit event from loading a new page.
                
                //Empty the log and show the spinning indicator.
                
                //Set the options of the form's Request handler. 
                //("this" refers to the $('myForm') element).
                this.set('send', {
                    onComplete: function(response){
                        var log = $('qlist').empty().addClass('ajax-loading');
                        log.set('html', response);
                        setTimeout('admin_approve();', 1000);
                    }
                });
                //Send the form.
                this.send();
                
            }
            else {
            
                alert('select atleast one question for action!');
                return false;
            }
            
        });
        
        
        
    });
    
}

function admin_reject(make){

    var vals = [];
    $$('.check-me:checked').each(function(e){
        vals.push(e.value);
    });
    
    var report = $('reporttext').get('value');
	
    if ($('showbox').getStyle('display') == 'none') {
    
        $('showbox').setStyle('display', 'block');
        $('showbox').slide('hide').slide('in');
        $('reporttext').focus();
        return false;
    }
    if (report.trim().length < 5) {
        $('reporttext').setStyle('border-color', '#EF2C2C');
        return false;
    }else{
		 $('reporttext').setStyle('border-color', '');
		
	}
    if (vals.length > 0) {
        if (confirm('Are you sure to reject the selected Questions?')) {
            $('action').set('value', make);
            
            $('qadmin').set('send', {
                onComplete: function(response){
                    var log = $('qlist').empty().addClass('ajax-loading');
                    log.set('html', response);
                    setTimeout('admin_approve();', 1000);
                }
            });
            //Send the form.
            $('qadmin').send();
            
        }
        else {
            return false;
        }
    }
    else {
    
        alert('select atleast one question for action!');
        return false;
    }
    
}


function checkall(val){


    $$('.check-me').each(function(el){
        el.checked = val;
    });
    
}
