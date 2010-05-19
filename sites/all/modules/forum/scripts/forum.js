/**
 * @author gobinath.m
 */
window.addEvent('domready', function(){

    //$('newwaveletbut').addEvent('click', addComment.bindWithEvent(this,element)); 
    
    
    if ($('flagform') != null) {
        $('flagform').addEvent('submit', function(e){
        
            e.stop();
            
        var log = $('freport').addClass('ajax-loading');
            
            this.set('send', {
                onComplete: function(response){
                    log.removeClass('ajax-loading');
                    log.set('html', response);
					 setTimeout("$('freport').slide('out');",2000);
                }
            });
            
            this.send();
        });
    }
    
    
    //bind event  
    bind_clk();
    
});

Element.implement({
    unwrap: function(){
        var parent = this.getParent();
        parent.getChildren().inject(parent, 'before');
        parent.dispose();
        return this;
    }
});
Element.implement({
    exists: function(){
        return ($(this).length > 0);
    }
});
function bind_clk(){



    var elements = $$('div.replyLink').getElements('a.rep');
    
    elements.each(function(element, index){
    
        element.removeEvents('click'); // removes ALL click events
        element.addEvent('click', addComment.bindWithEvent(this, element));
        
    });
    
    
    
}


function addComment(val, el){

    var wid = el.get('id');
    
    var gid = wid.split('-');
    
    $('waveletcmt').setStyle('border-color', '');
    $('waveletcmt').set('value', '');
    $('waveid').set('value', gid[0]);
    $('commentArea').setStyle('display', 'block');
    $('commentArea').slide('hide').slide('in');
    $('wletid').set('value', gid[1]);
    
    $('waveButton').removeEvents('click');
    $('wavecancel').removeEvents('click');
    $('waveButton').addEvent('click', addSubmit.bindWithEvent(this));
    $('wavecancel').addEvent('click', cancelAdd.bindWithEvent(this));
}


function cancelAdd(id){

if($('commentArea').getStyle('display')=='block'){
	  $('commentArea').slide('out');
    $('commentArea').setStyle('display', 'none');
	
}else 
if($('freport').getStyle('display')=='block'){
	  $('freport').slide('out');
    $('freport').setStyle('display', 'none');	
	
}
  
    
}

function likethis(action, wid, like, ele){

    el = $(ele);
    
    el.empty();
    //var myVerticalSlide = new Fx.Slide('likelink');
    
    
    //	myVerticalSlide.slideOut();
    // el.fade('out');
    //$('likelink').set('slide', {duration: 'long', transition: 'bounce:out'});
    //$('likelink').slide('in');
    el.slide('hide').slide('in');
    
    // $('likelink').empty();
    
    var url = spath + 'question/forum/savecmt';
    var req = new Request({
        method: 'get',
        url: url,
        data: {
            'action': action,
            'like': like,
            'nodeid': wid
        },
        onRequest: function(){
            $('waveerr').set('html', '<b>Saving your like..!</b>');
            $('waveerr').slide('hide').slide('in');
        },
        onComplete: function(response){
        
            el.set('html', response);
            
            var finl = el.getElement('a');
            //  el.fade('in');
            
            finl.unwrap();
            finl.unwrap();
            $('waveerr').slide('hide').slide('out');
        }
    }).send();
    
    
    
    //$('waveerr').set('html','<b>Thanks for your like!</b>');

}




function addSubmit(){


    var cmt = $('waveletcmt').get('value');
    var wid = $('waveid').get('value');
    var wlid = $('wletid').get('value');
    if ($('privt').checked) {
        var pvt = 1;
    }
    else {
        var pvt = 0;
    }
    
    var myVerticalSlide = new Fx.Slide('wavelet-list');
    
    if (cmt.length > 5) {
        var req = new Request({
            method: 'get',
            url: 'question/forum/savecmt',
            data: {
                'wid': wid,
                'wlet': wlid,
                'cmt': cmt,
                'pvt': pvt
            },
            onRequest: function(){
                $('commentArea').slide('out');
                $('commentArea').setStyle('display', 'none');
                
                //myVerticalSlide.slideOut();
                MochaUI.notification('Please wait while posting...');
            },
            onComplete: function(response){
                MochaUI.notification('Thank you posted successfully...');
                $('wavelet-list').set('html', response);
                //myVerticalSlide.slideIn();
                
                bind_clk();
                $('privt').setProperty('checked', false);
                $('wavelet-list').setStyle('height', 'auto');
            }
        }).send();
        
    }
    else {
    
        $('waveletcmt').setStyle('border-color', '#EF2C2C');
        return false;
    }
    
}




function report_forum(typ, id){
    $('commentArea').slide('out');
    $('commentArea').setStyle('display', 'none');
    el = $('freport');
    $(typ).set('value', id);
    el.setStyle('display', 'block');
    el.slide('hide').slide('in');
    $('abuse_type').focus();
	
        $('wavecancel1').addEvent('click', cancelAdd.bindWithEvent(this));
    
   
}


