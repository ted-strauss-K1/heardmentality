/**
 * @author gobinath.m
 

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
                    
                    setTimeout("$('flagform').slide('out');", 2000);
                }
            });
            
            this.send();
        });
    }
    
    

    
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
*/

function bind_clk(){

  

    jQuery('a.rep').live('click', function(){

        addComment(jQuery(this));

    });
    //for submit
   jQuery('#waveButton').live('click', function(){addSubmit(jQuery(this));});


      if (jQuery('#flagform') != null) {
        jQuery('#flagform').bind('submit', function(e){

            e.preventDefault();

            var log = jQuery('#log_res').addClass('ajax-loading');

         jQuery.post( jQuery("#flagform").attr('action'), jQuery("#flagform").serialize(),
   function(data){
     log.removeClass('ajax-loading');
                      jQuery.unblockUI();
                     jQuery.growlUI('', data);
   });

   jQuery(this).parents('form').submit(function() {
  alert($(this).serialize());
  return false;
});

        
        });
    }

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
							
        },
        onRequest: function() {
            $('newwavediv').fade('out');
        }
		
		
    });
    //Send the form.
    $('newwaveform').send();
}

function addComment(el){
    var wid = el.attr('id');
  
    var gid = wid.split('-');
    
    jQuery('#waveletcmt').css('border-color', '');
    jQuery('#waveletcmt').val('');
    jQuery('#waveid').val(gid[0]);
    jQuery('#wletid').val(gid[1]);
   
// jQuery('#wavecancel').live('click', function(){cancelAdd(jQuery(this));});
    
}


function cancelAdd(id){

   
    if ($('freport').getStyle('display') == 'block') {
        $('freport').slide('out');
        $('freport').setStyle('display', 'none');
            
    }

}

function likethis(action, wid, like, ele){

    el = jQuery(ele);
    if(uid>0){
     }else{

          jQuery.growlUI('', 'Please Login to do this action!');
            return false;
        }

    el.empty();
    //var myVerticalSlide = new Fx.Slide('likelink');
    
    
    //	myVerticalSlide.slideOut();
    // el.fade('out');
    //$('likelink').set('slide', {duration: 'long', transition: 'bounce:out'});
    //$('likelink').slide('in');
    el.slideDown('slow');
    
    // $('likelink').empty();
    
    var url = spath + 'question/forum/savecmt';

         jQuery('#waveerr').html('<b>Saving your like..!</b>');
           jQuery('#waveerr').slideDown('slow');
           jQuery.ajax({
            type: "POST",
             url: url,
        data: {
            'action': action,
            'like': like,
            'nodeid': wid
        },
            success: function(msg){

            el.html(msg);
             var finl = el.find('a');
            //  el.fade('in');

            finl.unwrap();
           
           jQuery('#waveerr').slideUp('slow');
            }
        });
    return false;
//$('waveerr').set('html','<b>Thanks for your like!</b>');

}




function addSubmit(){


    var cmt = jQuery('#waveletcmt').val();
    var wid =jQuery('#waveid').val();
    var wlid = jQuery('#wletid').val();
    var url=jQuery('#burl').val();
    if (jQuery('#privt').is(':checked')) {
        var pvt = 1;
    }
    else {
        var pvt = 0;
    }
    
    
    if (cmt.length > 5) {
        jQuery.ajax({
            type: "POST",
            url: url+'question/forum/savecmt',cache:false,
            data: {
                'wid': wid,
                'wlet': wlid,
                'cmt': cmt,
                'pvt': pvt
            },
            success: function(msg){
                jQuery('#wavelet-list').html(msg);
                //myVerticalSlide.slideIn();
                jQuery('#commentArea').slideUp('slow');
                jQuery('#privt').attr('checked', false);
                jQuery('#wavelet-list').css('height', 'auto');
                jQuery.unblockUI();
                     jQuery.growlUI('', 'Have a nice day!');
            }
        });


    }
    else {
    
        jQuery('#waveletcmt').css('border-color', '#EF2C2C');
        return false;
    }
    
}


function report_forum(typ, id){
   
    el = jQuery('#freport');
    jQuery('#rwave').val();
    jQuery('#rwavelet').val();
    jQuery(typ).val(id);
   /* el.css('display', 'block');
    el.slideDown('slow');*/
    jQuery('#abuse_type').focus();
    

    
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
	

    if(uid>0){

            var id = jQuery(this).attr('href');
          jQuery.blockUI({ message: jQuery('#newwavediv'),css: {
               left: (jQuery(window).width() - 500) /2 + 'px',
               right:'20%',
                width: 'auto',cursor:''
            }  });
        }else{

            jQuery.growlUI('', 'Please Login to do this action!');
        }
}


jQuery(document).ready(function() {
    //bind event for reply link
    bind_clk();
    //select all the a tag with name equal to modal
    jQuery('a[name=modal]').live('click', function(e){
        //Cancel the link behavior
        e.preventDefault();
        if(uid>0){

            var id = jQuery(this).attr('href');
          jQuery.blockUI({ message: jQuery(id),css: {
               left: (jQuery(window).width() - 500) /2 + 'px',
               right:'20%',
                width: 'auto',cursor:'pointer'
            }  });
        }else{

            jQuery.growlUI('', 'Please Login to do this action!');
        }
        //Get the A tag
       
 
        //Get the screen height and width
     /*   var maskHeight =jQuery(document).height();
        var maskWidth = jQuery(window).width();

        //Set heigth and width to mask to fill up the whole screen
        jQuery('#mask').css({
            'width':maskWidth,
            'height':maskHeight
        });

        //transition effect
        jQuery('#mask').fadeIn(1000);
        jQuery('#mask').fadeTo("slow",0.8);

        //Get the window height and width
        var winH = jQuery(window).height();
        var winW =jQuery(window).width();

        //Set the popup window to center
        jQuery(id).css('top',  winH/2-jQuery(id).height()/2);
        jQuery(id).css('left', winW/2-jQuery(id).width()/2);

        //transition effect
        jQuery(id).fadeIn(2000);
*/
    });

    //if close button is clicked
    jQuery('.close').click(function (e) {
        //Cancel the link behavior
        e.preventDefault();
         jQuery.unblockUI();
       // jQuery('#mask').hide();
       // jQuery('.window').hide();
    });

    //if mask is clicked
    jQuery('#mask').click(function () {
       jQuery.unblockUI();

        //jQuery(this).hide();
       // jQuery('.window').hide();
    });

});
