/**
 * @author gobinath.m

*/



/*
 * Change the Yes/No votes number
 *
 * id    - content_id
 * type  - comment/node
 * agree - 1/0 = agree/disagree
 * count - if not set will be incremented
 */
function votes_update(id, type, agree, count) {
    var selector = '#lik-btns-'+type+'-'+id+' a[name='+(agree==1?'a-':'da-')+id+'] span';
    if( count == null ) {
        count = jQuery(selector).html().replace(/[\(\)]/g,'');
        count = parseInt(count)+1;
    }
    jQuery(selector).fadeOut(1000, function(){ $(this).html('('+count+')').fadeIn(1000); });
}

/*
 * Change the size of the debate vote sum count
 *
 * @element  - element to recalculate for
 * @count    - vote count
 */
function circle_update(element, count) {
    var size = Math.abs(count) > 100 ? 'large' : ( Math.abs(count) > 10 ? 'middle' : 'small' );
    var color = count > 0 ? 'positive' : ( count < 0 ? 'negative' : 'null' );
    element.find('span.sum')
        .removeClass('small middle large')
        .addClass(size);
    element.find('span.sum span')
        .html(count)
        .removeClass('null positive negative')
        .addClass(color);
}



/*
 * Handle Yes/No votes
 *
 * @e       - click event
 * @type    - 1/0 = agree/disagree
 */
(function(jQuery){
    jQuery.fn.extend({
        agree: function(e,type) {
            e.preventDefault();
            el = jQuery(this);
            // show dialog if user is not logged in
            if(uid<1){
                $('#dialog').dialog('open');
                return false;
            }

            el.slideDown('slow');
            // content_id
            var wid=el.parent('span').attr('name');
            // type = debate/resource/reply
            var action=el.parent('span').attr('type');
            // parent id - not equals to wid when "action = reply"
            var id_par = el.parents('.one-forum').attr('name');

            // change the text of clicked button
            el.closest('span').find('a.dagree').attr({'class':'','title':'You have rated this!'});
            el.closest('span').find('a.ddisagree').attr({'class':'','title':'You have rated this!'});

            jQuery('#twitMsg').html("Please wait while saving your post....!");
            jQuery('#twitMsg').delay(400).slideDown(400);

            var url = Drupal.settings.base_url + '/issues/debate/save';
            jQuery.ajax({
                type: "POST",
                dataType: 'json',
                url: url,
                data: {
                    'action': action,
                    'agree': type,
                    'content_id': wid,
                    'parent_node': id_par
                },
                success: function(msg){
                    // update circle
                    circle_update(el.parents('.one-forum'), msg.sum_count);
                    // update likebar
                    var barid = '#likebar-'+ntype+'-'+wid;
                    //jQuery(barid).html(msg.likebar);
                    //
                    var ntype = msg.type;
                    var btnid = '#lik-btns-'+ntype+'-'+wid;
                    var btnid_val = jQuery(btnid).html();
                    // show message
                    /* odyachenko disable coins
                    jQuery(btnid).html(msg.msg);
                    */
                    // update clicked Y/N vote count
                    votes_update(wid, ntype, type, null);
                    /* odyachenko disable coins
                    jQuery(btnid).delay(5000).fadeOut(1000, function(){
                        jQuery(btnid).html(btnid_val);
                        votes_update(wid, ntype, type, null);
                        jQuery(btnid).fadeIn(1000);
                    });
                    */
                    // update parent Y/N vote count
                    if( id_par != wid ) {
                        votes_update(id_par, 'node', type, null);
                    }
                }
            });
        }
    });
})(jQuery);





function bind_clk(){

  jQuery('a[name="rep"]').live('click', function(){
    addComment(jQuery(this));
  });

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

    jQuery('#debate_list_area ul.ui-tabs-nav li a').click(function(){
        var href = jQuery(this).attr('href');
        if( jQuery(href).html() == '' ) {
            jQuery(href).html('<div style="text-align: center; margin-top: 30px;"><img src="/sites/all/themes/hmware/images/loading_min.gif" /></div>')
        }
    });
}



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
*/;
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

