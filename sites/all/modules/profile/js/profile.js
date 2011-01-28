
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
    jQuery.blockUI({
        message: '<h3> Just a moment validating your zip code...</h3>'
    });
    jQuery.ajax({
        type: "POST",
        url: urr,
        data: {
            code: code
        },
        success: function(msg){

            jQuery('#edit-city-wrapper').html(msg);
            jQuery.unblockUI();

        }
    });
}

function chk_uname(val){

    var urr=spath+'qlite/ajax?action=uname';

    var ck_uname = /^[A-Za-z0-9_]{5,20}$/;
    if(!val.match(ck_uname)){

        err="Username should be Alphabets, numbers and no special characters min 5 and max 20 allowed ";
        load_notify(err);
        return false;

    }else if(val.length>0){
        jQuery.blockUI({
            message: '<h3> Just a moment validating your username...</h3>'
        });

        jQuery.getJSON(urr,
        {
            userid: val
        },
        function(data) {
            var msg=data.messages;
            jQuery.unblockUI();
            if(data.error){
               
                jQuery('#rname').val('');
                err="Username already taken please try any other combination";
                load_notify(err+''+msg);
                return false;

            }else{
                load_notify(msg);
            }
      
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

    jQuery('#twitMsg',top.document).html(data);
    jQuery('#twitMsg',top.document).delay(400).slideDown(400).delay(3000).slideUp(400);

}