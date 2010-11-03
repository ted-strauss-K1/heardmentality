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
    jQuery('#waveButton').live('click', function(){
        addSubmit(jQuery(this));
    });


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

        //   jQuery(this).parents('form').submit(function() {
        //  alert($(this).serialize());
        // return false;
        //});

        
        });
    }

}
/*mootool version*/
function wave_form(){
    //Prevents the default submit event from loading a new page.
    //e.stop();
   var wt=jQuery('#newwaveform').find('#wtitle');
		var wc=jQuery('#newwaveform').find('#wcon');
                 var wt=jQuery('#newwaveform').find('#wtitle');

                var wtitle=wt.val();
		var post=wc.val();
		var formwave=jQuery('#newwaveform');

           if(jQuery.trim(wtitle).length<2){

			wt.css("border-color","red");

			return false;
		}else{

	wt.css("border-color","");
		}


		if(jQuery.trim(post).length<8){

			wc.css("border-color","red");
		wc.removeClass('txtare');
			return false;
		}else{

	wc.addClass('txtare');
		}


    jQuery.post( jQuery("#newwaveform").attr('action'), jQuery("#newwaveform").serialize(),
        function(data){
            wt.val('');
          wc.val('');
             $('#qwave').html(data);
            jQuery.unblockUI();
            jQuery.growlUI('', 'Have a nice day!');
        });



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
            url: spath+'question/forum/savecmt',
            cache:false,
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

    var url = spath+'question/forum/';
    

    var myElement ='<div id="documentBody" align="right" ><a href="#" onClick="return_back('+rid+')" id="back" >Back</a></div>';
    
   //  $('#ajaxpage_content').slideUp('slow');
    jQuery.growlUI('Loading forum...');
        jQuery.ajax({
        type: "POST",
        url: url,
        data: {
            'qid': rid,
            'wid': wid
        },
        success: function(msg){

              $('body').html(msg);
                $('.content-popup').prepend(myElement);
           // jQuery('#ajaxpage_content').slideDown('slow');
              bind_clk();
        }
    });




}

function return_back(rid){

    var url = spath+'resource/forum/' + rid;
    
  jQuery.growlUI('Loading forum...');
      jQuery.ajax({
        type: "POST",
        url: url,
        data: {},
        success: function(msg){

              $('body').html(msg);
               
                }
    });

    
}
function toggle(){
	

    if(uid>0){

        var id = jQuery(this).attr('href');
        jQuery.blockUI({
            message: jQuery('#newwavediv'),
            css: {
                left: (jQuery(window).width() - 500) /2 + 'px',
                right:'20%',
                width: 'auto',
                cursor:''
            }
        });
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

            jQuery.blockUI({
                message: jQuery(id),
                css: {
                    left: (jQuery(window).width() - 500) /2 + 'px',
                    right:'20%',
                    width: 'auto',
                    cursor:'pointer'
                }
            });
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
