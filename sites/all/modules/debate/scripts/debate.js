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


   

}

(function(jQuery){
    jQuery.fn.extend({
        agree: function(e,type) {

            e.preventDefault();
            el = jQuery(this);
            if(uid<1){
                //jQuery('#twitMsg').html("Please Login to do this!");
                //jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
               //alert('Please login to do this!');
               $('#dialog').dialog('open');
               return false;
            }

           // el.empty();

            el.slideDown('slow');
            var wid=el.parent('span').attr('name');
            var action=el.parent('span').attr('type');
            // $('likelink').empty();
            el.closest('span').find('a.dagree').attr('class','');
            el.closest('span').find('a.ddisagree').attr('class','');

            var url = spath + 'issues/debate/save';
             jQuery('#twitMsg').html("Please wait while saving your post....!");
                jQuery('#twitMsg').delay(400).slideDown(400);
           
            jQuery.ajax({
                type: "POST",
                dataType: 'json',
                url: url,
                data: {
                    'action': action,
                    'agree': type,
                    'content_id': wid
                },
                success: function(msg){
                    if(type==0){
                        el.closest('div').find('#disag-cnt').html(msg.ratecount);
                    }
                    if(type==1){
                        el.closest('div').find('#ag-cnt').html(msg.ratecount);
                    }

                    var ntype = msg.type;
                    var barid = '#likebar-'+ntype+'-'+wid;
                    var btnid = '#lik-btns-'+ntype+'-'+wid;
                    //jQuery('#twitMsg').html(msg.msg);
                    jQuery(btnid).html(msg.msg);
                    jQuery(barid).html(msg.likebar);
                    //jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
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
    jQuery('#comid').val(gid[1]);
// jQuery('#wavecancel').live('click', function(){cancelAdd(jQuery(this));});

}

function switchdebate(url){
    

var newCaption = '`DEBATE SUMMARY <a href="" onclick="fb.instances[fb.ownerInstance(this)].goBack(); return false;"><b>Go back...</b></a>`';
	var options = 'type:ajax sameBox:true width:70% height:90% caption: ' + newCaption;
	parent.fb.start(url, options);

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

        jQuery.growlUI('', 'Please Login to do this!');
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

        jQuery('#twitMsg').html("Please Login to do this!");
                jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
    }
}


jQuery(document).ready(function() {
    //bind event for reply link
    bind_clk();


    


});


//for submit
    jQuery('#waveButton').live('click',function(e) {
 if(uid>0){
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
               jQuery('#twitMsg').html("Your reply has been noted");
                jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
            //  el.find('input[type="submit"]').removeAttr('disabled');
            });
            return false;

        }
        else {

            jQuery('#waveletcmt').css('border-color', '#EF2C2C');
            return false;
        }
 }else{

        jQuery('#twitMsg').html("Please Login to do this!");
                jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
    }
    return false;
    });


//flag debate


        jQuery('#flagform').live('submit', function(e){

             var fl = jQuery(this);
          e.preventDefault();
        var data=jQuery(this).serialize();
        jQuery.ajax({
            type: "POST",
            url: jQuery(this).attr('action'),
            data:data,
            success: function(data){

                 jQuery('#twitMsg',top.document).html(data);
               jQuery('#twitMsg',top.document).slideDown().delay(2000).slideUp(400);
                 fl.clearForm();
                  fl.find("input:checked").attr('checked',false);
            },
            complete:function(data){
                setTimeout("parent.fb.end();", 3000);
                       }
        });
        //   jQuery(this).parents('form').submit(function() {
        //  alert($(this).serialize());
        // return false;
        //});


        });



function report_forum(typ,el){

    var wid = jQuery(el).attr('name');

    var gid = wid.split('-');
    jQuery('#rtype').val(typ);
    jQuery('#rwave').val(gid[0]);
    jQuery('#rwavelet').val(gid[1]);

}

