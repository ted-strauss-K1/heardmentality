/**
 * @author gobinath.m

*/

function bind_clk(){


    jQuery('a[name="rep"]').live('click', function(){

        addComment(jQuery(this));

    });

    //agree
    jQuery('a.dagree').live('click', function(e){
        jQuery(this).agree(e,'1');
    });
    //diagree
    jQuery('a.ddisagree').live('click', function(e){
        jQuery(this).agree(e,'0');
    });
    //reply agree dis agree
    jQuery('a.ragree').live('click', function(e){
        jQuery(this).agree(e,'1');
    });
    //diagree
    jQuery('a.rdisagree').live('click', function(e){
        jQuery(this).agree(e,'0');
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

                    jQuery("#flagform input:checked").attr('checked',false);


                });

        //   jQuery(this).parents('form').submit(function() {
        //  alert($(this).serialize());
        // return false;
        //});


        });
    }

}

(function($){
    $.fn.extend({
        agree: function(e,type) {

            e.preventDefault();
            el = jQuery(this);
            if(uid>0){
            }else{

                jQuery.growlUI('', 'Please Login to do this action!');

            }

            el.empty();

            el.slideDown('slow');
            var wid=el.parent('span').attr('name');
            var action=el.parent('span').attr('type');
            // $('likelink').empty();

            var url = spath + 'issues/debate/save';

            jQuery('#waveerr').html('<b>Saving your hit..!</b>');
            jQuery('#waveerr').slideDown('slow');
            jQuery.ajax({
                type: "POST",
                dataType: 'json',
                url: url,
                data: {
                    'action': action,
                    'agree': type,
                    'nodeid': wid
                },
                success: function(msg){
                    jQuery('#waveerr').html(msg.msg);
                    jQuery('#waveerr').slideUp('10000');
                    el.parent('span').html(msg.msg);
                }
            });
        }
    });
})(jQuery);

/*
function wave_form(){
    //Prevents the default submit event from loading a new page.
    //e.stop();

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
*/
function addComment(ele){
    var el=jQuery(ele);
    var wid = el.attr('id');
    var gid = wid.split('-');

    jQuery('#waveletcmt').css('border-color', '');
    jQuery('#waveletcmt').val('');
    jQuery('#frid').val(gid[1]);

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


    //for submit
    jQuery('#waveButton').live('click',function(e) {

       e.preventDefault();

        var el=jQuery('#postreplyform');


        var cmt=jQuery('#waveletcmt').val();
         if (cmt.length > 5) {
              fb.end();
            // el.find('input[type="submit"]').attr('disabled',true);
            jQuery.post(el.attr('action'),el.serialize(),function(msg){
                jQuery('#wavelet-list').html(msg);

                //myVerticalSlide.slideIn();

                el.clearForm();
                jQuery('#wavelet-list').css('height', 'auto');
                jQuery.growlUI('', 'Have a nice day!');
            //  el.find('input[type="submit"]').removeAttr('disabled');
            });
            return false;

        }
        else {

            jQuery('#waveletcmt').css('border-color', '#EF2C2C');
            return false;
        }

    return false;
    });


});
