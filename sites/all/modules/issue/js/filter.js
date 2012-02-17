/**
 * @author gobinath.m
 */
function get_filter_option(type){
	
	var url=spath+'qlite/ajax?action=filter';


	jQuery('#fopt').html('');
		jQuery.ajax({
   type: "POST",
   url: url,
    data: {
            type: type
   
        },
   success: function(msg){
	jQuery('#fopt').html(msg);
   }
 });	
	
}


function MM_jumpMenuGo(){ 
document.form1.submit();
}

function search_iss_trig(){
    jQuery('#subject').trigger('change');
    setTimeout(subcatSet,3000);
    jQuery('#s_country').trigger('change');
    setTimeout(substate,3000);
}
function subcatSet(){
    jQuery('#area').trigger('change');
}
function substate(){
    jQuery('#s_state').trigger('change');
}


jQuery(document).ready(function() {

   // hide / show suggest answer
   jQuery('.wait').live('click', function(){
       jQuery('.sugg-hide').slideToggle('slow');
   });

  //trigger search filters
     search_iss_trig();
//for IE
        // setTimeout(resetFields,3000);
        //  jQuery('#subject').change();
      //   jQuery('#subject').val("3");
//sendEvent(jQuery('#subject'),'change');//assuming there is a select element
//jQuery('#subject').fireEvent("onchange");

 jQuery('#analytics-area').slideUp(3000);
 jQuery('#res-analytics-area').slideUp(3000);

jQuery('#show-analytics').click(function(){
    jQuery('#filter-area').slideUp('fast');
    jQuery('#analytics-area').slideToggle('slow'); 
})
jQuery('#show-filter').click(function(){
    jQuery('#analytics-area').slideUp('fast');
    jQuery('#filter-area').slideToggle('slow');
})

// resource tab
jQuery('#show-res-statistics').click(function(){
    jQuery('#res-analytics-area').slideToggle('fast');
    jQuery('#res-filter-area').slideUp('slow');
    jQuery('#add-resource-area').slideUp('slow');
})
jQuery('#show-res-filter').click(function(){
    jQuery('#res-analytics-area').slideUp('fast');
    jQuery('#res-filter-area').slideToggle('slow');
    jQuery('#add-resource-area').slideUp('slow');
})


jQuery('#addnew_reference').click(function(){
    jQuery('#res-analytics-area').hide('fast');
    jQuery('#res-filter-area').hide('fast');
    jQuery('#add-resource-area').slideToggle('slow');
});

});

function sendEvent(ele,e){
	try{// every browser except IE8 and below works here
		var evt = document.createEvent("HTMLEvents");
		evt.initEvent(e, true, true);
		ele.dispatchEvent(evt);
	}
	catch(err){
		ele.fireEvent('on'+e);
	}
}


// open suggest answer form
    jQuery('#sugg-btn').live('click',function(){
        jQuery('#sugg-form').slideToggle('fast');
    });

jQuery('#canc').live('click', function() {
        jQuery('#sugg-form').slideUp('fast');
    });

// open add new debate form
 jQuery('#addnew_debate').live('click',function(){
        jQuery('#submitted-msg').html('');
        jQuery('#deb-err').html('');
        jQuery('#add_debate_wrapper').slideToggle('slow');
       
    });

jQuery.fn.slideFadeToggle = function(speed, easing, callback) {
  return this.animate({opacity: 'toggle', height: 'toggle'}, speed, easing, callback);
};




// add new debate ajax submit
jQuery('#add-new-debate-form').live('submit', function(e){
    e.preventDefault();


    var title = jQuery('#deb_title').val();
    var tot_ans = jQuery('#tot_ans').val();
    var flag = 0;
    for(var i=0; i<tot_ans; i++){
        var id = '#sup_'+i;
        if(jQuery(id).val() != 0){
            flag = parseInt(flag)+1;
        }
    }

    if(title.length < 2){
        jQuery('#deb-err').html('Please let us know what you think.');
        return false;
    }else if(flag == 0){
        jQuery('#deb-err').html('You must choose atleast one suppose or oppose.');
        return false;
    }else{
        jQuery('#add_new_debate').hide();
        jQuery('#sub_loader').show();
        var data=jQuery(this).serialize();
        jQuery.ajax({
          type: 'POST',
          dataType: 'json',
          url: jQuery(this).attr('action'),
          data: data,
          success: function(msg){
              jQuery('#add_debate_wrapper').slideUp('slow');
              //jQuery('#add-new-debate-form').clearForm();
              jQuery('#add-new-debate-form select').val(0);
              jQuery('#add-new-debate-form textarea').val('');

              jQuery('#deb-err').fadeIn("slow");
              jQuery('#deb-err').html(msg.message);
              //jQuery('#add_debate_wrapper').append(msg.content);
              jQuery(msg.content).prependTo('.comments');
          },
          complete: function(){
              jQuery('#sub_loader').hide();
              jQuery('#add_new_debate').show();
          }
        });
    }
    return false;
});


// forum reply

function open_replybox(id){
  var spl = id.split("_");
  var open_id = '#reply_box_'+spl[2];
  var msgid = '#reply-msg-'+spl[2];
  jQuery(msgid).html('');
  jQuery(open_id).slideToggle('slow');
}

function show_replies(id){
  var spl = id.split("_");
  var open_id = '#all_replybox_'+spl[2];
  jQuery(open_id).slideToggle('slow');
}



jQuery('.arg-reply-form').live('submit', function(e){
    e.preventDefault();

    var cont = jQuery(this);
    var debid = cont.find('#ded_tnid').val();
    var norep = "#no_rply_"+debid;
    if(cont.find('textarea').val().length<2){
        cont.find('#reply_err').html('Please enter your reply');
    }else{
        cont.find('#add_reply').hide();
        cont.find('#sub_loader').show();
        var data = cont.serialize();
        var ded_tnid = cont.find('#deb_tnid').val();
        var box_id = '#reply_box_'+ded_tnid;
        var open_id = '#all_replybox_'+ded_tnid;
        jQuery.ajax({
            type: 'POST',
            dataType: 'json',
            url: cont.attr('action'),
            data: data,
            success: function(msg){
                cont.find('textarea').val('');
                jQuery(box_id).slideUp('slow');
                jQuery(norep).remove();
                jQuery(msg.content).prependTo(open_id);
                jQuery(open_id).slideDown('slow');
                cont.find('#reply_err').html('');
                jQuery('#reply-msg-'+ded_tnid).html(msg.message);
            },
            complete: function(){
                cont.find('#add_reply').show();
                cont.find('#sub_loader').hide();
                cont.find('#reply_err').html('');
            }
        });
    }
    return false;
});


function delete_thread(id, type){
    var spl = id.split("_");
    var fid  = spl[2];
    var dtype = spl[1];
    //var msgid = '#reply-msg-'+fid;
    
    var url = spath+'issue/thread/delete/'+dtype+'/'+fid+'/'+type;
    if(confirm("Are you sure to delete this argument?")){
    jQuery.ajax({
        type: 'post',
        url: url,
        success: function(msg){
          
        },
        complete: function(){
           var bid = '#'+dtype+'-block-'+fid;
           jQuery(bid).remove();
        }
    });
    return true;
    }else{
        return false;
    }
}
// insight view
function insight_view(nid){

var url = spath+'issue/ajax/insightview/'+nid;
jQuery.ajax({
    type: 'get',
    url: url,
    success:function(msg){
        jQuery('#insight-view').html(msg);
    }
});

}

// load debate statistics
jQuery('#deb-ana').live('click', function(){
var nid = jQuery('#curr_nid').val();
var url = spath+'issue/ajax/debate_statistics/'+nid;
jQuery('#deb-ana-load-txt').html('Loading...');
jQuery.ajax({
    type: 'get',
    url: url,
    success:function(msg){
        jQuery('#load-deb-statics').html(msg);
    },
    complete:function(){
        jQuery('#deb-ana-load-txt').html('');
    }
});
});

// load reference statistics
jQuery('#res-ana').live('click', function(){
var nid = jQuery('#curr_nid').val();
var url = spath+'issue/ajax/resource_statistics/'+nid;
jQuery('#res-ana-load-txt').html('Loading...');
jQuery.ajax({
    type: 'get',
    url: url,
    success:function(msg){
        jQuery('#load-res-statics').html(msg);
    },
    complete:function(){
        jQuery('#res-ana-load-txt').html('');
    }
});
});


// from debate module - code cleanup

jQuery(document).ready(function() {

jQuery("#lattach").click(function()
{
var content=jQuery('#nlink').val();
var urlRegex = /(\b(https?|ftp|file):\/\/[-A-Z0-9+&@#\/%?=~_|!:,.;]*[-A-Z0-9+&@#\/%=~_|])/ig;

var url= content.match(urlRegex);
var purl=spath+'debate/ajax';

if(url.length>0)
{
jQuery(this).attr('disabled',true);
$("#linkbox").slideDown('show');
$("#linkbox").html("Loading.....");
$.get(purl+"?action=url&url="+url,function(response)
{
jQuery("#linkbox").html(response);
jQuery("#lattach").removeAttr('disabled');
if(jQuery('#cur_id_val').val() == jQuery('#end_image').val()){
    jQuery('#re-sel-next').hide();
    jQuery('#re-sel-prev').hide();
}
//jQuery('#re-sel-pre').bind('click', disableLink);
//jQuery('#re-sel-pre').fadeTo('fast', 0.2);
jQuery('#re-sel-pre').hide();
});
}
return false;
});


    var selObj = jQuery('#rtype');
    jQuery('#div1,#div2,#div3,#media,#media_div').hide();
    selObj.bind('change', function(e) {

        var vDiv1 = jQuery('#div1');
        var vDiv2 = jQuery('#div2');
        var vDiv3 = jQuery('#div3');
        var medDiv1 =jQuery('#media');
        var medDiv2 = jQuery('#media_div');
        jQuery('#div1,#div2,#div3,#media,#media_div,#linkbox').hide();
        var selIndex = selObj.selectedIndex;
        var value = selObj.val();

        if(value==1)
        {
            vDiv1.slideDown();
		jQuery('#linkbox').show();
        }
        if(value==2)
        {
            vDiv2.slideDown();

        }
        if(value==3)
        {
            vDiv1.slideDown();
            jQuery('#linkbox').show();
        }

    });

    var selObjmed = jQuery('#mtype');
    var medDiv1 = jQuery('#media');
    var medDiv2 = jQuery('#media_div');
    jQuery('#media,#media_div').hide();
    selObjmed.bind('change', function(emed) {
         jQuery('#media,#media_div').hide();
        var valuemed = selObjmed.val();
      //  jQuery(medDiv1,medDiv2).hide();
        //alert(valuemed);
        if(valuemed==1)
        {
            medDiv1.slideDown();
        }else
        if(valuemed==2)
        {
            medDiv2.slideDown();
        }


    });


    jQuery('#myForm').submit(function() {

        var cat1 = jQuery('#rtype').val();
        var nlink = jQuery('#nlink').val();
        var mtype =jQuery('#mtype').val();
        var membed = jQuery('#membed').val();
        var docpath = jQuery('#docpath').val();
        var err = '';
        var trig_ref = '';
        var tomatch=/http:\/\/[A-Za-z0-9\.-]{3,}\.[A-Za-z]{3}/;
        if (cat1==0)
            err += '<li>Please Select Type !</li>';
        if (cat1==1)
        {
            trig_ref = '#ref_innews';
            if (!tomatch.test(nlink))
                err += '<li>Please Enter Link </li>';

        }
        if (cat1==2)
        {
            trig_ref = '#ref_multimedia';
            if (mtype==0)
                err += '<li>Please Select Media Type !</li>';

            if (mtype==1)
            {

                if (!tomatch.test(membed))
                    err += '<li>Please Enter YouTube Link </li>';
                if (tomatch.test(membed))
                {
                    var el = jQuery('#err').hide();

                }
            }
            else
            {
                if ( jQuery.trim(docpath).length < 1)
                {
                    err += '<li>Please Select Document !</li>';
                }

            }
        }
        if (cat1==3)
        {
            trig_ref = '#ref_facts';

            if (!tomatch.test(nlink))
                err += '<li>Please Enter  Fact Link</li>';

        }
        //var el =  jQuery('#twitMsg', top.document);
        var el =  jQuery('#refer-err');

        if (jQuery.trim(err).length > 1) {
           el.html(err);
          el.addClass('error-msg');
          //jQuery('#twitMsg', top.document).delay(400).slideDown(400).delay(3000).slideUp(400);
            return false;
        }	else{
            el.hide();
        }

//jQuery('input[type="submit"]').attr('disabled',true);
        jQuery(this).find('#add-new-res').hide();
        jQuery(this).find('#sub_loader_res').show();
       // e.preventDefault();

        jQuery.post( jQuery(this).attr('action'), jQuery(this).serialize(),
            function(data){
                el.removeClass('error');
                jQuery( "form" )[ 0 ].reset();
                jQuery('#uscrap').empty();
                jQuery("#linkbox").html('');
                jQuery('#nlink').val('http://');


             //jQuery( "form" )[ 0 ].clearForm();
            // clearForm(jQuery(this));
                //el.html(data);
                //jQuery(data).prependTo('#load-resource');
                jQuery(trig_ref).trigger('click');
                jQuery('#add-resource-area').slideUp();
                jQuery('#sub_loader_res').hide();
                jQuery('#add-new-res').show();
                // el.delay(400).slideDown(400).delay(3000).slideUp(400);
               // jQuery.growlUI('', data);
               jQuery('input[type="submit"]').removeAttr('disabled');
            });

        return false;
    });
});

function startload(){
    initialize();
    createUploader();
}


function createUploader(){
    var uploader = new qq.FileUploader({
        element: document.getElementById('file-uploader-demo1'),
        action: spath+'upload_document.php',
        debug: true,
        // url of the server-side upload script, should be on the same domain
        // additional data to send, name-value pairs
        //params: {},

        // validation
        // ex. ['jpg', 'jpeg', 'png', 'gif'] or []
        allowedExtensions: ["doc","docx","ppt","pdf"],
        // each file size limit in bytes
        // this option isn't supported in all browsers
        sizeLimit: 1000000, // max size
        minSizeLimit: 1, // min size
        multipleFileUpload:false,
        onSubmit: function(id, fileName){jQuery.growlUI('','File uploading please wait!');},
        onProgress: function(id, fileName, loaded, total){jQuery.growlUI('','File uploading please wait!');},
        onComplete: function(id, fileName, responseJSON){jQuery('#docpath').val(responseJSON.filename);jQuery.growlUI('','File uploaded successfully!');},
        showMessage: function(message){

            jQuery.growlUI('',message);
        }

    });
}

// in your app create uploader as soon as the DOM is ready
// don't wait for the window to load
//window.onload = createUploader;
window.onload=startload;


 jQuery.fn.clearForm = function() {
  return this.each(function() {
 var type = this.type, tag = this.tagName.toLowerCase();
 if (tag == 'form')
   return $(':input',this).clearForm();
 if (type == 'text' || type == 'password' || tag == 'textarea')
   this.value = '';
 else if (type == 'checkbox' || type == 'radio')
   this.checked = false;
 else if (tag == 'select')
   this.selectedIndex = -1;
  });
};

function clearForm(form) {
  // iterate over all of the inputs for the form
  // element that was passed in
  $(':input', form).each(function() {
 var type = this.type;
 var tag = this.tagName.toLowerCase(); // normalize case
 // it's ok to reset the value attr of text inputs,
 // password inputs, and textareas
 if (type == 'text' || type == 'password' || tag == 'textarea')
   this.value = "";
 // checkboxes and radios need to have their checked state cleared
 // but should *not* have their 'value' changed
 else if (type == 'checkbox' || type == 'radio')
   this.checked = false;
 // select elements need to have their 'selectedIndex' property set to -1
 // (this works for both single and multiple select elements)
 else if (tag == 'select')
   this.selectedIndex = -1;
  });
};


// resources image selector
jQuery(document).ready(function() {


    jQuery('#re-sel-next').live('click',function() {
    var curr = jQuery("#cur_id_val").val();
    var next= Number(curr)+Number(1);
    var imgcount = Number(next)+Number(1);
    var end = jQuery('#end_image').val();
    end = Number(end)-Number(1);
    var imgid = '#cur_img_';
    var src = jQuery(imgid+next).attr("src");
            jQuery(imgid+curr).hide();
            jQuery(imgid+next).show();
            jQuery('#cur_id_val').val(next);
            jQuery('#img_count').html(imgcount);
            if(jQuery('#no_thumbnail').attr('checked')){
             jQuery('#final_uimage').val('');
            }
            else{
             jQuery('#final_uimage').val(src);
            }

            if(curr >= end){
                //jQuery('#re-sel-next').bind('click', disableLink);
                //jQuery('#re-sel-next').fadeTo('fast', 0.2);
                jQuery('#re-sel-next').hide();
            }
            if(curr >= 0){
                //jQuery('#re-sel-pre').unbind();
                //jQuery('#re-sel-pre').fadeTo('fast', 1);
                jQuery('#re-sel-pre').show();
            }
    });
    jQuery('#re-sel-pre').live('click',function() {
    var curr = jQuery("#cur_id_val").val();
    var pre= Number(curr)-Number(1);
    var imgcount = Number(pre)+Number(1);
    var end = jQuery('#end_image').val();
    end = Number(end)+Number(1);
    var imgid = '#cur_img_';
    var src = jQuery(imgid+pre).attr("src");

            jQuery(imgid+curr).hide();
            jQuery(imgid+pre).show();
            jQuery('#cur_id_val').val(pre);
            jQuery('#img_count').html(imgcount);
            if(jQuery('#no_thumbnail').attr('checked')){
             jQuery('#final_uimage').val('');
            }
            else{
             jQuery('#final_uimage').val(src);
            }

             if(curr<end){
               //jQuery('#re-sel-next').unbind();
               //jQuery('#re-sel-next').fadeTo('fast', 1);
               jQuery('#re-sel-next').show();
            }

            if(pre == 0){
                //jQuery('#re-sel-pre').bind('click', disableLink);
                //jQuery('#re-sel-pre').fadeTo('fast', 0.2);
                jQuery('#re-sel-pre').hide();
            }
    });

jQuery('#no_thumbnail').live('click', function() {
    var curr = jQuery("#cur_id_val").val();
    var imgid = '#cur_img_';
    var src = jQuery(imgid+curr).attr("src");
    if(jQuery('#no_thumbnail').attr('checked')){
    jQuery('#final_uimage').val('');
    }else{
    jQuery('#final_uimage').val(src);
    }
});

})

function disableLink(e) {
    // cancels the event
    e.preventDefault();

    return false;
}


// open resource subtab types
function res_type_tab(id,tab,nid){
    var divid;
//    for(var i=1;i<=3;i++){
//    divid = '#res-type-'+i;
//    if(i==id){
//        jQuery(divid).show();
//    }else{
//        jQuery(divid).hide();
//    }
//    }

    // url sort get values
    var sup = jQuery('#sup').val();
    var ans = jQuery('#ans').val();
    var sort = jQuery('#sort').val();

    jQuery('#load-resource').prepend('Loading...');
    var url = spath+'issues/load_resources/'+nid+'/'+id+'/'+sup+'/'+ans+'/'+sort;
    jQuery.ajax({
        type: 'post',
        url: url,
        success: function(msg){
            jQuery('#load-resource').html('');
            jQuery('#load-resource').html(msg);
        }
    });
}

function resOpenReplyBox(rid){
    var boxid = '#reply-box-'+rid;
    jQuery(boxid).slideToggle('slow');
}
function resOpenReplies(rid){
    var boxid = '#all_replybox_'+rid;
    jQuery(boxid).slideToggle('slow');
}




///////// ########## from preload.js code cleanup ########## /////


function loadflagquestion(url,title)
{


    //jQuery.nyroModalSettings({ title:'Flag Posts'});

    //jQuery.nyroModalManual({
    // url: url,width:550,height:450,title:'Flag Posts'
    //  });

    var options = 'sameBox:true width:50% height:60% caption:' +
    '`Flag Posts`';
    parent.fb.start(url, options);


}
function loadflagresdeb(url,title)
{


    //jQuery.nyroModalSettings({ title:'Flag Posts'});

    //jQuery.nyroModalManual({
    // url: url,width:550,height:450,title:'Flag Posts'
    //  });

    var options = 'newBox:true width:50% height:60% caption:' +
    '`Flag Posts`';
    parent.fb.start(url, options);


}
function loadeditquestion(url,title)
{


    //jQuery.nyroModalSettings({ title:'Flag Posts'});

    //jQuery.nyroModalManual({
    // url: url,width:550,height:450,title:'Flag Posts'
    //  });

    var options = 'sameBox:true width:78% height:90% caption:' +
    '`Edit Profile`';
    parent.fb.start(url, options);


}



jQuery(document).ready(function () {

    //twitter like alert
    if(jQuery('#twitMsg').text().length>2){
        jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
    }
    //loading status for ajax
//    jQuery("#loading").ajaxStart(function () {
//        jQuery(this).fadeIn();
//    });
//
//    jQuery("#loading").ajaxStop(function () {
//
//        jQuery(this).fadeOut();
//        fb.activateElements();
//    });
    jQuery("#loading").ajaxError(function() {
        jQuery(this).hide();
        jQuery('#twitMsg').empty().html('Sorry Error Occurs Please Reload the Page and Try Again!');
        jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
    });

    jQuery(".innerbox li a").live('click', function(e) {

    });



});

function load_issue(url){

    $('#qajax').load(url, function(response, status, xhr) {
        if (status == "success") {
            reset_tabs();

        }else{
            var msg = "Sorry but there was an error: ";
            $("#qajax").html(msg + xhr.status + " " + xhr.statusText);
        }
    });

}

function check_popup_login(){
    jQuery(document).ready(function() {

        jQuery('#twitMsg').html("Please Login to do this!");
                jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
    });
}

function close_notify_message(dcount, mid, uid){

    jQuery(document).ready(function() {

        var divid = 'not-id-'+dcount;
        var url = gSitePath+'question/ajax';
        jQuery.ajax({
        type: "GET",
        url: url,
        data: 'mid='+mid+'&uid='+uid+'&notupdate=1',
        success: function(msg)
        {
            if(msg){
                jQuery('#'+divid+'').hide();
            }else{
                return false;
            }
        }
        });
    });

}

function show_inotify(data){

    jQuery('#twitMsg',top.document).html(data);
    jQuery('#twitMsg',top.document).delay(400).slideDown(400).delay(3000).slideUp(400);

}

// add / edit vote ajax submission
jQuery('#issue_edit_form_stream').live('submit', function(){
    if(jQuery('#check_login').val()==0){
        $('#dialog').dialog('open');
	return false;
    }
    var thisForm = jQuery(this);
    var data = thisForm.serialize();
    var vote_type = thisForm.find('#vote_type').val();
    var but_val = '';
    if(vote_type == 'edit'){
        but_val = 'Changing...';
    }else if(vote_type == 'add'){
        but_val = 'Voting...';
    }
    thisForm.find('#edit-change').val(but_val);
    var choice = thisForm.find('input:radio[name=choice]:checked').val();
    
    jQuery.ajax({
          type: 'POST',
          dataType: 'json',
          url: spath+'issue/vote/ajax/submit/'+vote_type,
          data: data,
          success: function(msg){
              var nid_val = thisForm.find('#nid_val').val();
              //alert(msg.message);
              jQuery('#vote-msg-alert-'+nid_val).html(msg.message);
              if(msg.success == 1){
                  var def_vote = thisForm.find('#def_vote').val();
                  var newchoicediv = '#'+nid_val+'-chorder-'+choice;
                  var oldchoicediv = '#'+nid_val+'-chorder-'+def_vote;

                  var oldchoice = jQuery(oldchoicediv).html();
                  var newchoice = jQuery(newchoicediv).html();
                  if(vote_type == 'edit'){
                      thisForm.find('#def_vote').val(choice);
                     //jQuery('#voting-pane-'+nid_val).html(msg.content);
                      jQuery(oldchoicediv).html(Number(oldchoice)-Number(1));
                      jQuery(newchoicediv).html(Number(newchoice)+Number(1));
                  }else{
                      jQuery(oldchoicediv).html(Number(oldchoice)-Number(1));
                      jQuery(newchoicediv).html(Number(newchoice)+Number(1));
                      var totcount = jQuery('#tot-count-'+nid_val).html();
                      jQuery('#tot-count-'+nid_val).html(Number(totcount)+Number(1));
                      
                      jQuery('#vote-count-poll-'+nid_val).show();
                      thisForm.find('#vote_type').val('edit');
                      thisForm.find('#def_vote').val(choice);
                  }
                thisForm.find('#edit-change').val('Change Vote');
              }else{
                    if(vote_type == 'edit'){
                        thisForm.find('#edit-change').val('Change Vote');
                    }else{
                        thisForm.find('#edit-change').val('Vote');
                    }
              }
          }
          });
          return false;
    
})
// VALIDATE FLAG ISSUE FORM
jQuery('#abuse-report-form').live('submit', function(e){
    e.preventDefault();
    if(jQuery(this).find('input:radio[name=reason]:checked').length == 0){
       jQuery(this).find('#flag-error').html('Please select your flag reason');
       return false;
    }
    var data=jQuery(this).serialize();
    jQuery.ajax({
        type: 'post',
        url: jQuery(this).attr('action'),
        data: data,
        success: function(data){
            jQuery('#abuse-report-form').html(data);

        }
    });
});

jQuery('.openlogin_box').live('click', function(){
    $('#dialog').dialog('open');
    return false;
})

// open flag for arguments
function open_flag_box(oid, type){
    var divId;
    if(type == 'node'){
        divId = '#flag-arg-'+oid;
    }else if(type == 'comment'){
        divId = '#flag-comm-'+oid;
    }
    jQuery(divId).dialog('open');
    jQuery(divId).html('Please Wait...');
    jQuery.ajax({
        type: 'get',
        data: {'flag_type': type},
        url: sitepath+'/issue/ajax/getForumFlagForm/'+oid,
        success: function(form){
            jQuery(divId).html(form);
        }
    });
    return false;
}