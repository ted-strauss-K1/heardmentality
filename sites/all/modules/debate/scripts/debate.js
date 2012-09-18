





function bind_clk(){

  jQuery('a[name="rep"]').live('click', function(){
    addComment(jQuery(this));
  });

  jQuery('a[name="rep"]').live('click', function(){
    addComment(jQuery(this));
  });

  //agree


    jQuery('#debate_list_area ul.ui-tabs-nav li a').click(function(){
        var href = jQuery(this).attr('href');
        if( jQuery(href).html() == '' ) {
            jQuery(href).html('<div style="text-align: center; margin-top: 30px;"><img src="/sites/all/themes/hmware/images/loading_min.gif" /></div>')
        }
    });
}



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

