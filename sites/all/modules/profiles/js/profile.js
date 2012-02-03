
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
   
function get_zip_city(code){
	
    var urr=spath+'qlite/ajax?action=zipcity';
    show_inotify('Please wait your zip code is validating...');
    //jQuery.blockUI({
     //   message: '<h3> Just a moment validating your zip code...</h3>'
   // });
   jQuery("body").css({'opacity': 0.5});
  jQuery("#avatar-selection-loading").show();

    jQuery.ajax({
        type: "POST",
        url: urr,
         dataType: "json",
        data: {
            code: code
        },
        success: function(msg){
        //alert(msg);
            jQuery('#country').val(msg.country);
            jQuery('#state').val(msg.state);
            jQuery('#city').val(msg.city);
            
            if(msg.state==null){
               show_inotify('Please Provide the proper Zip code ');
               jQuery('#location').val('');
               jQuery('#cit-stat').html('Please Provide the proper Zip code');
            }else{
               show_inotify('You have entered valid zipcode');
               jQuery('#cit-stat').html(msg.city+','+msg.state+','+msg.country);
            }

           // jQuery.unblockUI();
            jQuery("body").css({'opacity':''});
        }
    });

    // enable submit button
    $("#update_submit").attr('disabled', false);
}

function chk_uname(val){

    var urr=spath+'qlite/ajax?action=uname';

    var ck_uname = /^[A-Za-z0-9_]{5,20}$/;
    if(!val.match(ck_uname)){

        err="Username should be Alphabets, numbers and no special characters min 5 and max 20 allowed ";
        load_notify(err);
        return false;

    }else if(val.length>0){
       // jQuery.blockUI({
        //    message: '<h3> Just a moment validating your username...</h3>'
       // });
show_inotify('Please wait your username is validating...');

   jQuery("body").css({'opacity': 0.5});
        jQuery.getJSON(urr,
        {
            userid: val
        },
        function(data) {
            var msg=data.messages;
           // jQuery.unblockUI();
            if(data.error){
               
                jQuery('#rname').val('');
                err="Username already taken please try any other combination";
                load_notify(err+''+msg);
              

            }else{
                load_notify(msg);
            }
        jQuery("body").css({'opacity':''});
        });
        return true;
    }
    return false;
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
    //jQuery('#twitMsg',top.document).html(data);
    //jQuery('#twitMsg',top.document).delay(400).slideDown(400).delay(3000).slideUp(400);
    jQuery('.effect').html(data);
    jQuery('.effect').show('slow');

}

function update_avatar(){
    var src=jQuery('#dialog-profile-pic input:radio:checked').next("img").attr('src');
    //var src=jQuery('#avatar-profile-ele input:radio:checked').next("img").attr('src');
    if(src.length>3){
        jQuery('div.avatar-left img').attr('src',src);
        jQuery('#curr_avatar').val(src);
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

