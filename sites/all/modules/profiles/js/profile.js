
/**
 * @author gobinath.m
 */


function validate_profile(){
  var facebook = $('edit-facebook').value;
  var twitter = $('edit-twitter').value;

  var RegExp = /^(([\w]+:)?\/\/)?(([\d\w]|%[a-fA-f\d]{2,2})+(:([\d\w]|%[a-fA-f\d]{2,2})+)?@)?([\d\w][-\d\w]{0,253}[\d\w]\.)+[\w]{2,4}(:[\d]+)?(\/([-+_~.\d\w]|%[a-fA-f\d]{2,2})*)*(\?(&?([-+_~.\d\w]|%[a-fA-f\d]{2,2})=?)*)?(#([-+_~.\d\w]|%[a-fA-f\d]{2,2})*)?$/;
  if(facebook !=''){
    if(!(RegExp.test(facebook))){
      alert('Please enter the valid URL format for Facebook');
      return false;
    }
  }
  if(twitter !=''){
    if(!(RegExp.test(twitter))){
      alert('Please enter the valid URL format for Twitter');
      return false;
    }

  }
  return true;

}

function bio_tog(ele){
  var cls=jQuery(ele).parent().attr('class');
  if(cls=='tab-historyspan4')
    return false;


  jQuery('#l1 span').each(function(){
    jQuery(this).attr('class','');
    jQuery(this).attr('class','tab-historyspan5');
  });
  if(cls=='tab-historyspan5'){
    jQuery(ele).parent().attr('class','');
    jQuery(ele).parent().attr('class','tab-historyspan4');
    jQuery('#bio').toggle();
  }else if(cls!='tab-historyspan4'){
    jQuery(ele).parent().attr('class','');
    jQuery(ele).parent().attr('class','tab-historyspan5');

  }





  jQuery('#link').toggle();
}

function chk_all(typ){

  jQuery('#frmsgform input:checkbox').each(function(el){

    jQuery(this).attr('checked',typ);

  });
  jQuery("ul.subtabs li").last().contains('select').remove();

}

function enable_form(typ,thi){
  var n = jQuery("#frmsgform input:checked").length;

  if(n>0){
    jQuery("#frmsgbox").slideToggle("slow");
    jQuery("#usmsg").unbind("click");
    jQuery("#usmsg").click(function () {
      var formmsg=jQuery('#frmsgform');
      jQuery.post(formmsg.attr('action'),formmsg.serialize(),
        function(data){
          show_inotify(data);

          jQuery('#frmsgform').clearForm();

        });
    });
  }else{

    show_inotify("Please select atleast one user!");
  }


}

/*
 jQuery.fn.clearForm = function() {
 return this.each(function() {
 var type = this.type, tag = this.tagName.toLowerCase();
 if (tag == 'form')
 return jQuery(':input',this).clearForm();
 if (type == 'text' || type == 'password' || tag == 'textarea')
 this.value = '';
 else if (type == 'checkbox' || type == 'radio')
 this.checked = false;
 else if (tag == 'select')
 this.selectedIndex = -1;
 });
 };
 */

function profile_comment(make){

  jQuery(document).ready(function(){
    jQuery("#usmsg").unbind("click");

    jQuery("#usmsg").live(function () {
      var formmsg=jQuery('#proform');
      jQuery.post(formmsg.attr('action'),formmsg.serialize(),
        function(data){
          load_inotify(data);
          formmsg.clearForm();

        });
    });
  });


  var report = jQuery('#msgs').val();


  jQuery('#showboxcmt').slideToggle("slow");
  jQuery('#msgs').focus();
  return false;

  if (report.trim().length < 5) {
    jQuery('msgs').css('border-color', '#EF2C2C');
    return false;
  }else{
    jQuery('#msgs').css('border-color', '');

  }

}

// zip code validator

function get_zip_city(ielem, lock){
  LockPage(lock);
  var result = false;
  var urr=spath+'qlite/ajax?action=zipcity';
  var code = $(ielem).val();
  add_validate_message(ielem, '<span class="validate-wait">Please wait your zip code is validating...</span>', 'validate-error-wait');
  jQuery.ajax({
    type: "GET",
    url: urr,
    dataType: "json",
    data: {
      country: $('#country').val(),
      code: code
    },
    success: result = function(msg){
      //alert(msg);
      var geoname = msg.geoname;
      geoname.country = $('#country').find('[value="' + $('#country').val() + '"]').text();

      var result = false;
      jQuery('#state').val(geoname.state);
      jQuery('#city').val(geoname.city);

      if(geoname.state==null){
        jQuery('#location').val('');
        //jQuery('#cit-stat').html('Please Provide the proper Zip code');
        add_validate_message(ielem, 'Please Provide the proper Zip code');

      }else{

        jQuery('#location').val('');
        //  add_validate_message(ielem, 'You have entered valid zipcode');
        result = true;
        var citStat = '';
        if (geoname.city)
        {
          citStat += geoname.city;
        }
        if (geoname.state)
        {
          if (citStat != '')
          {
            citStat += ', ';
          }
          citStat += geoname.state;
        }
        if (geoname.country)
        {
          if (citStat != '')
          {
            citStat += ', ';
          }
          citStat += geoname.country;
        }
        clear_validate_messages();
        jQuery('#cit-stat').html(citStat);
      }

      // jQuery.unblockUI();
      UnlockPage(lock);
      return result;
    }
  });

  return result;
}



function LockPage(lock)
{
  if (lock)
  {
    $("#update_submit").attr('disabled', 'disabled');
    jQuery("body").css({'opacity': 0.5});
//    jQuery("#avatar-selection-loading").show();
  }
}

function UnlockPage(lock)
{
  if (lock)
  {
    jQuery("body").css({'opacity':''});
    $("#update_submit").attr('disabled', false);
  }
}

function chk_uname(ielem, lock){

  var val = ielem.val();
  var urr=spath+'qlite/ajax?action=uname';
  var result = true;

  var ck_uname = /^[A-Za-z0-9_]{5,20}$/;
  if(!val.match(ck_uname)){

    add_validate_message(ielem, 'Username should be Alphabets, numbers and no special characters min 5 and max 20 allowed ');
    result = false;

  } else if(val.length>0){
    LockPage(lock);
    add_validate_message(ielem, '<span class="validate-wait">Please wait your username is validating...</span>', 'validate-error-wait');

    jQuery.getJSON(urr,
      {
        userid: val
      },
      result = function(data) {

        var result= false;
        var msg=data.messages;
        // jQuery.unblockUI();
        if(data.error){

          jQuery('#rname').val('');
          add_validate_message(ielem, 'Username already taken please try any other combination', 'validate-error validate-ajax');
          result = false;

        } else {
          add_validate_message(ielem, '');
          result = true;
        }
        UnlockPage(lock);
        return result;
      });
  }
  //     alert('test');
  return result;
}


function del_msg(ids,tr){

  var urr=gSitePath+'profile/inbox';

  jQuery.ajax({
    type: "POST",
    url: urr,
    dataType:'xhr',
    data: {
      id: ids,
      action:'delete'
    },
    success: function(data){
      jQuery('#twitMsg').html(data);
      jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);

    }
  });

}

function rel_msg(id){

  jQuery('#actions').val(id);
  jQuery('#showboxcmt').slideToggle('slow');
  jQuery("#usmsg").unbind("click");

  jQuery("#usmsg").click(function () {
    var formmsg=jQuery('#proform');
    jQuery.post(formmsg.attr('action'),formmsg.serialize(),
      function(data){
        jQuery('#twitMsg').html(data);
        jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);

        jQuery('#showboxcmt').slideToggle("slow");
        formmsg.get(0).reset();
      });
  });
}



function deletefollowing(fid){
  var abc="#show-"+fid;
  var url =gSitePath+'profile/deletefollow';


  jQuery.ajax({
    type: "POST",
    url: url,
    data: {
      'action':fid,
      'ids':abc
    },
    success: function(msg){
      jQuery(abc).html(msg);
      $(abc).delay(2000).fadeOut(400);
    }
  });

}

function blockandunblock(fid,divid,blk,show){
  var abcm="#list-"+fid;
  var url =gSitePath+'savefollower';
  jQuery.ajax({
    type: "GET",
    url: url,
    data: {
      'action':fid,
      'ids':abcm,
      'blk':blk,
      'usid':divid,
      'show':show
    },
    success: function(msg){
      jQuery(abcm).html(msg);
      show_inotify("Selected Action Done Successfully!");
    }
  });

}

function loadfollower(url,title)
{

  var options = 'sameBox:true width:50% height:70% caption:' +title;
  parent.fb.start(url, options);

}
function loadfollowing(url,title)
{
  var options = 'sameBox:true width:50% height:50% caption:' +title;
  parent.fb.start(url, options);


}

function show_inotify(data){
  jQuery('.effect').html(data);
  jQuery('.effect').show('slow');

}

function update_avatar(){
  var src=jQuery('#dialog-profile-pic input:radio:checked').next("img").attr('src');
  //var src=jQuery('#avatar-profile-ele input:radio:checked').next("img").attr('src');
  if(src.length>3){
    jQuery('div.avatar-left img').attr('src',src);
    jQuery('#curr_avatar').val(src);
    /**Rallydev:512**/
      //document.forms["user-details"].submit();
    $('#al-msg').html('<em style="color:#CC2027;font-size:11px; line-height: 1.2em; padding: 0 0 10px; display: inline-block;>Please click the Save Changes button at the bottom of the page</em>')
    //$('.ui-dialog ').hide();
    jQuery('.ui-dialog .ui-icon-closethick').trigger('click');
    /**************/
  }


}

function chk_avatar(){

  if(typeof avatar!="undefined" && avtar.length>2){


    jQuery("#avatar-profile-ele img[src*='"+avtar+"']").addClass("avatar-select").prev("input radio").attr("checked",true);
  }else{
    //  jQuery("#avatar-profile-ele div.form-item img:first").addClass("avatar-select");
    //  jQuery("input[name=select_avatar]:first").attr("checked",true);
  }
}

jQuery(document).ready(function(){
  jQuery("#loading").ajaxStart(function () {
    jQuery(this).fadeIn();
  }).ajaxStop(function() {

      jQuery(this).fadeOut();
      fb.activateElements();
    });

  chk_avatar();
  jQuery('div.avatar-selection-pager-nav a').live('click', function() {
    setTimeout('chk_avatar()',1000);

  });

  jQuery('#avatar-profile-ele img').live('click', function() {
    jQuery('#edit-file-upload').val('');
    jQuery('input:hidden[name=img_avt]').val('2');
  });
  jQuery('#edit-file-upload').blur(function(){    jQuery('input:hidden[name=img_avt]').val('1'); });


});



// delete following users

function delete_following(fid){

  jQuery(document).ready(function(){
    var urls = gSitePath+'savefollowing';
    var divid = '#record-'+fid;
    var follid = '#followname-'+fid;
    var followname = jQuery(follid).val();
    jQuery.ajax({
      type: "GET",
      url: urls,
      data: {
        'delete':  fid
      },
      success: function(msg){
        jQuery(divid).remove();
        show_inotify("You now unfollowed from "+followname+"!");
      }
    });
  })

}

/******************Rallydev:496******************/
$(document).ready(function(){

  var aURL = document.URL;

  if(aURL.indexOf("#gender-wrapper") != -1) {
    $('#gender').focus();
  }

  if(aURL.indexOf("#dob-wrapper") != -1) {
    $('#dob').val('');
    $('#dob').focus();
  }

  if(aURL.indexOf("#zip-wrapper") != -1) {
    $('#zip').val('');
    $('#zip').focus();
  }

  if(aURL.indexOf("#religion-wrapper") != -1) {
    $('#religion').focus();
  }

  if(aURL.indexOf("#ethnic-wrapper") != -1) {
    $('#ethnic').focus();
  }

  if(aURL.indexOf("#edu-wrapper") != -1) {
    $('#edu').focus();
  }

  if(aURL.indexOf("#sorient-wrapper") != -1) {
    $('#sorient').focus();
  }

  if(aURL.indexOf("#income-wrapper") != -1) {
    $('#income').focus();
  }

  if(aURL.indexOf("#marital-wrapper") != -1) {
    $('#marital').focus();
  }

  if(aURL.indexOf("#bio-wrapper") != -1) {
    $('#bio').val('');
    $('#bio').focus();
  }

  /****Rallydev:529****/
  if($.trim($('p.double').text()) == "") {
    $('p.double').hide();
  }
  /************/
});
/*************************************************/