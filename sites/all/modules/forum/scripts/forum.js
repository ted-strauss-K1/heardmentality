/**
 * @author gobinath.m
 */
window.addEvent('domready', function(){

    //$('newwaveletbut').addEvent('click', addComment.bindWithEvent(this,element)); 
    
  
    if ($('flagform') != null) {
        $('flagform').addEvent('submit', function(e){
        
            e.stop();
            
            var log = $('log_res').addClass('ajax-loading');
            
            this.set('send', {
                onComplete: function(response){
                    log.removeClass('ajax-loading');
                    log.set('html', response);
                    
                    setTimeout("$('freport').slide('out');$('log_res').empty();", 2000);
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
/*mootool version*/
function wave_form(){
		//Prevents the default submit event from loading a new page.
		//e.stop();
		var wt=$('newwavediv').getElement('.textArea');
		var formwave=$('newwaveform');
		var post=wt.get('value');
		if(post.trim().length<8){
		
			wt.setStyle('border-color','#EF2C2C');
			wt.set('id','wtitlerror');
			return false;
		}else{
			
	wt.set('id','wtitle');	
		}
		//Empty the log and show the spinning indicator.
		//var log = $('newwavediv').empty().addClass('ajax-loading');
		//Set the options of the form's Request handler. 
		//("this" refers to the $('myForm') element).
		formwave.set('send', {
		
			
						onComplete: function(response) { 
			//log.removeClass('ajax-loading');
				$('qwave').fade('out');
				$('qwave').empty();
			$('qwave').set('html', response);
				$('qwave').fade('in');
				wt.set('value','');
							
		},onRequest: function() { $('newwavediv').fade('out');}
		
		
		});
		//Send the form.
		$('newwaveform').send();
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

    if ($('commentArea').getStyle('display') == 'block') {
        $('commentArea').slide('out');
        $('commentArea').setStyle('display', 'none');
        
    }
    else 
        if ($('freport').getStyle('display') == 'block') {
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
	var url=$('burl').get('value');
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
            url: url+'question/forum/savecmt',
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
                //MochaUI.notification('Please wait while posting...');
            },
            onComplete: function(response){
               // MochaUI.notification('Thank you posted successfully...');
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
    $('rwave').set('value', '');
    $('rwavelet').set('value', '');
    $(typ).set('value', id);
    el.setStyle('display', 'block');
    el.slide('hide').slide('in');
    $('abuse_type').focus();
    
    $('wavecancel1').addEvent('click', cancelAdd.bindWithEvent(this));
    
    
}


function rwavelet(rid, wid){

    var url = 'question/forum/';
    
    var myElement = new Element('div', {
        //The 'styles' property passes the object to Element:setStyles.
        'styles': {
            'font': '12px Arial',
            'color': 'blue',
            'border': '1px solid #CCCCCC'
        },
        
        //Any other property uses Element:setProperty.
        'id': 'documentBody',
        'align': 'right'
    });
    
    var back = new Element('a', {
        //The 'events' property passes the object to Element:addEvents.
        'events': {
            'click': function(){
                return_back(rid);
            }
        },
        //Any other property uses Element:setProperty.
        'id': 'back',
        'href': '#'
    });
    
    var req = new Request({
        method: 'get',
        url: url,
        data: {
            'qid': rid,
            'wid': wid
        
        },
        onRequest: function(){
            $('ajaxpage_content').set('html', '<b>Loading wavelets..!</b>');
            $('ajaxpage_content').slide('hide').slide('in');
        },
        onComplete: function(response){
        
            $('ajaxpage_content').set('html', response);
            
            //   var myElementw = new Element('div', { 'id': 'documentBody'});
            
            var el = $('ajaxpage_content').getParent();
            
            // el.setStyle('height', 'auto');
            // el.setAttribute('style','');
            
            $('ajaxpage_content').unwrap();
            
            myElement.inject($('ajaxpage_content'), 'top');
            back.inject(myElement);
            back.appendText('Back');
            bind_clk();
        }
    }).send();
}

function return_back(rid){

    var url = 'resource/forum/' + rid;
    
    var req = new Request({
        method: 'get',
        url: url,
        data: {},
        onRequest: function(){
            $('ajaxpage_content').set('html', '<b>Loading waves..!</b>');
            $('ajaxpage_content').slide('hide').slide('in');
        },
        onComplete: function(response){
        
            $('ajaxpage_content').set('html', response);
            
            
            
            
            
            
        }
    }).send();
    
    
    
    
}
function toggle(){
	
	var mySlide = new Fx.Slide('newwavediv');

	
		//mySlide.toggle();
	
	$('newwavediv').fade('in');
	//$('newwavediv').fade('out');

}