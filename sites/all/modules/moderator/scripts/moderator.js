/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */



jQuery(document).ready(function(){
load_issue_data_ahah();
    
     jQuery('#tabcontent').ajaxComplete(function(event, xhr, settings) {
     var curl=settings.url;
     if(curl.search('list/new') != -1){
 jQuery('#mod-edit-issue').html('<div class="warning">No Issue Selected !</div>');
}
     if(curl.search('list/flag') != -1){
 jQuery('#mod-edit-issue').html('<div class="warning">No Issue Selected !</div>');
}

                  
});
  jQuery('#rcontents').ajaxComplete(function(event, xhr, settings) {
     var curl=settings.url;
     if(curl.search('list/new') != -1){
 jQuery('#mod-edit-issue').html('<div class="warning">No Issue Selected !</div>');
 jQuery('.mod-midside-inner-leftpart').html('<div class="warning">No User Selected !</div>');
}
     if(curl.search('list/flag') != -1){
 jQuery('#mod-edit-issue').html('<div class="warning">No Issue Selected !</div>');
  jQuery('.mod-midside-inner-leftpart').html('<div class="warning">No User Selected !</div>');
}


});
    jQuery('#qdupeform').live('submit',function(e){
        e.preventDefault();
        var dupeid=jQuery("#qdupeform input[type='radio']:checked").val();
        var qid=jQuery("#qdupeform input[type='hidden']").val();
        if(typeof(dupeid)!="undefined"){
            var url=gSitePath+'moderator/ajax/mergeissue/'+qid+'/'+dupeid;
            var options = 'type:ajax sameBox:true width:40% height:50% caption:' +
            '`Merge Dupe Issues`';
            parent.fb.start(url, options);
        }else{

            jQuery('#twitMsg').html('Please check one issue from the form to merge!');
            jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
        }
    });
    jQuery('#possible-dupe-form').live('submit',function(e){
            e.preventDefault();
            var dupeid=jQuery("#possible-dupe-form input[type='radio']:checked").val();
            var qid=jQuery("#possible-dupe-form input[name='qid']").val();
            if(typeof(dupeid)!="undefined"){
                var url=gSitePath+'moderator/ajax/mergeissue/'+qid+'/'+dupeid;
                var options = 'type:ajax sameBox:true width:40% height:50% caption:' +
                '`Merge Dupe Issues`';
                parent.fb.start(url, options);
            }else{
                alert('Please check one issue from the list to merge!');
            }
    });

    // new dupe form



    jQuery('#merge-dupeform').live('submit',function(e){
        e.preventDefault();
        if(confirm("Are you sure to merge this issue [which is going to deleted once merged]? ")){
        var data=jQuery(this).serialize();
        jQuery.ajax({
            type: "POST",
            dataType: 'json',
            url: jQuery(this).attr('action'),
            data:data,
            success: function(msg){
                alert(msg.msg);
                var qid=msg.qid;
            },
            complete:function(){
               // jQuery('div.mod-midside-inner').load(jQuery('a[name="icurrent"]').attr('href'),function() {
               //     load_issue_data();
               // });
                jQuery('#theiframe').attr("src", jQuery('#theiframe').attr("src"));

                fb.end();
                    
            }
        });
        }else{
            return false;
        }
    });

    jQuery('#moderator-edit-issue-form').live('submit',function(e){
       // e.preventDefault();
        if(validate_question()){

//            var data=jQuery(this).serialize();
//            jQuery.ajax({
//                type: "POST",
//                dataType: 'json',
//                url: jQuery(this).attr('action'),
//                data:data,
//                success: function(msg){
//                    jQuery('#twitMsg').html(msg.msg);
//                    jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
//                },
//                complete:function(){
//                jQuery('div.mod-midside-inner').load(jQuery('a[name="icurrent"]').attr('href'),function() {
//                    load_issue_data();
//                });
//                }
//            });

            return true;
        }else{
             e.preventDefault();
             alert('Please add the required fields');
            jQuery('#twitMsg').html('Some Of The Required fields are Empty!');
            jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
            return false;
        }


    });

    //button action ignore n reject

    jQuery('#mod-issue').live('submit',function(){

        jQuery('#actions').val('1');
        jQuery('#reporttext').val('');
        jQuery('#showbox').slideUp('slow');
        var formwave=jQuery(this);
        var vals = [];
        jQuery('.check-me:checked').each(function(){
            var e=jQuery(this);
            vals.push(e.val());

        });

        if (vals.length > 0) {

            if(confirm('Are you sure to Ignore this Issues?')){
                jQuery.ajax({
                    url:formwave.attr('action'),
                    global: false,
                    type: "POST",
                    data: formwave.serialize(),
                    dataType: "json",
                    async:false,
                    success: function(data){
                        jQuery('#twitMsg').empty().html(data.msg);
                        jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
                    },
                    complete:function(){
                        jQuery('#tabcontent').load(jQuery('#mod-url').val());
                        jQuery('div.mod-midside-inner').html('<div class="warning">No Issue Selected !</div>');
                         
                    }
                }
                );

            }
            


        }
        else {

        
            jQuery('#twitMsg').empty().html('select atleast one Issue for action!');
            jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
        }
        return false;
    });


    jQuery('a.user-links').live('click',function(e){
        jQuery(this).attr('name','icurrent');
        e.preventDefault();
        e.stopPropagation();
        //     parent.fb.start(jQuery(this).attr('href'), {
        //   type:'ajax',
        //  width: '70%',
        //   height: '90%',
        //  caption:'DEBATE SUMMARY'
        // afterItemStart:'`fb$("fbCaption").append("DEBATE SUMMARY");fb.translate(\'eat a peach\', \'fr\', function(result) { alert(result.responseData.translatedText); }); `',
        //controlsPos:'tr', captionPos:'tc',caption:'#boxSelect',
        //afterItemEnd:'`fb$("boxSelect").selectedIndex = 0;`'
        // });

        jQuery.ajax({
            type: "GET",
            //  dataType: 'json',
            url: jQuery(this).attr('href'),
            complete: function(){

                reset_tabs();

            },

            success: function(msg){
                jQuery('.mod-midside-inner-leftpart').html(msg);

            }
        });
    });
    jQuery('#mod-issue .pager a').live('click',function(e){
        e.preventDefault();
        e.stopPropagation();
        jQuery(this).parents('div.mytabs-container').load(jQuery(this).attr('href'));
    });


});

    // Drupal behavior to attach our AJAX click handler to links with
// the .our-links class.
jQuery(document).ready(function(){
    jQuery('a.issue-links').live('click',function(e){
        jQuery('a.issue-links').removeAttr('name');
        jQuery(this).attr('name','icurrent');
        e.preventDefault();
        e.stopPropagation();
        //     parent.fb.start(jQuery(this).attr('href'), {
        //   type:'ajax',
        //  width: '70%',
        //   height: '90%',
        //  caption:'DEBATE SUMMARY'
        // afterItemStart:'`fb$("fbCaption").append("DEBATE SUMMARY");fb.translate(\'eat a peach\', \'fr\', function(result) { alert(result.responseData.translatedText); }); `',
        //controlsPos:'tr', captionPos:'tc',caption:'#boxSelect',
        //afterItemEnd:'`fb$("boxSelect").selectedIndex = 0;`'
        // });

        jQuery.ajax({
            type: "GET",
             dataType: 'json',
            url: jQuery(this).attr('href'),
            complete: function(){

                load_issue_data();
                 //Drupal.attachBehaviors(jQuery('#poll-choice-wrapper'));
                    //   Drupal.attachBehaviors(context);
            },

            success: function(msg){
                // var result = Drupal.parseJson(msg);

           var message = jQuery("#mod-edit-issue").html(msg.output);
              
            }
        });
    });
});




function trigger_get_scat(){

    var values = new Array();
    jQuery.each(jQuery("input[name='q_cat[]']:checked"), function() {
        values.push(jQuery(this).val());
    // or you can do something to the actual checked checkboxes by working directly with  'this'
    // something like $(this).hide() (only something useful, probably) :P
    });
    var ids=values.join(',');


    get_subcat('q_cat','chg_scat',1,ids);
    jQuery('#chg_sscat').empty().html('No Subcategory');
}
function trigger_get_sscat()
{

    var values = new Array();
    jQuery.each(jQuery("input[name='q_scat[]']:checked"), function() {
        values.push(jQuery(this).val());
    // or you can do something to the actual checked checkboxes by working directly with  'this'
    // something like $(this).hide() (only something useful, probably) :P
    });
    var ids=values.join(',');


    get_subcat('q_scat','chg_sscat',2,ids);
    jQuery('#chg_sscat').empty().html('No Subcategory');



}
function trigger_get_state(){


    var values = new Array();
    jQuery.each(jQuery("input[name='q_country[]']:checked"), function() {
        values.push(jQuery(this).val());
    // or you can do something to the actual checked checkboxes by working directly with  'this'
    // something like $(this).hide() (only something useful, probably) :P
    });
    var ids=values.join(',');
    get_mod_state(ids);
}

function trigger_get_city(){

    var values = new Array();
    jQuery.each(jQuery("input[name='q_state[]']:checked"), function() {
        values.push(jQuery(this).val());
    // or you can do something to the actual checked checkboxes by working directly with  'this'
    // something like $(this).hide() (only something useful, probably) :P
    });
    var ids=values.join(',');

    get_mod_city(values);

}

function setDefaultCountry(cn) {
    if(cn.length>0){
        var countrySelect = document.getElementById("q_country");

        for (i=0;i< countrySelect.length;i++) {
            // the javascript geonamesData.js contains the countrycode
            // of the userIp in the variable \'geonamesUserIpCountryCode\'
            if (countrySelect[i].value == cn) {
                // set the country selectionfield
                countrySelect.selectedIndex = i;

            }
        }
        var stateSelect = document.getElementById("q_state");
        for (i=0;i< stateSelect.length;i++) {
            if (stateSelect[i].value == ustate) {

                // set the country selectionfield
                stateSelect.selectedIndex = i;
                get_city(setstate);
            }
        }
    }
}


function get_mod_state(ids){
    var url = gSitePath+"moderator/ajax/state";
    jQuery('#chg_state').html('Loading State...');
    jQuery.ajax({
        type: "POST",
        dataType: 'json',
        url: url,
        data: {
            'ids' :ids
        },
        success: function(data){
            jQuery('#chg_state').html(data.content);
        },
        complete: function(){

           // var statearray=setstate.split(',');
            jQuery('#q_state').val(setstate);
            jQuery('#q_state').multiSelect({
                selectAll: false
            },
            function() {
                trigger_get_city();
            });
            trigger_get_city();
        }
    });
    

    jQuery('#chg_city').html('');


}

function get_mod_city(ids){
    var url = gSitePath+"moderator/ajax/city";
    jQuery('#chg_city').html('Loading City...');
    jQuery.ajax({
        type: "POST",
        dataType: 'json',
        url: url,
        data: {
            'ids[]' :ids
        },
        success: function(data){
            jQuery('#chg_city').html(data.content);
        },
        complete: function(){
           // var cityarray=setcity.split(',');
            jQuery('#q_city').val(setcity);
            
            jQuery('#q_city').multiSelect({
                selectAll: false
            });
            return true;
        }
    });


}

function get_subcat(sid,divid,level,ids){


    if(level==1){
        jQuery('#q_cat').val(ids);
    // jQuery('#chg_scat').fadeOut('slow');
    //jQuery('#chg_sscat').fadeOut('slow');
    }

    if(level==2){

        jQuery('#cat2').val(ids);
        jQuery('#chg_sscat').fadeIn('slow');
    }
    if(level==3)
        jQuery('#cat3').val(ids);

    if(ids.length>0){

        if(level<3){

            var url = gSitePath+"question/ajax";
            jQuery.ajax({
                type: "POST",
                url: url,
                data: {
                    'action': level,
                    'ids' :ids
                },
                success: function(msg){
                    jQuery('#'+divid).html(msg);
                   
                },
                complete:function(){
                    if(sid=='q_cat') {
                        // for sub category initiate multi select
                        var scatarray=setscat.split(',');
                        jQuery('#q_scat').val(scatarray);
                        jQuery('#q_scat').multiSelect({
                            selectAll: false
                          
                        },
                        function(){

                            trigger_get_sscat();

                        });
                        trigger_get_sscat();
                    }else if(sid=='q_scat'){
                        //initiate multi select for sub sub category
                        var sscatarray=setsscat.split(',');
                        jQuery('#q_sscat').val(sscatarray);
                        jQuery('#q_sscat').multiSelect({
                            selectAll: false
                          
                        });
                    }
                }
            });


        //get_tag_cat(ids,level);
        }
    }else{
        jQuery('#'+divid).html('No Subcategory');
    }
}


function checkall(val){
    jQuery('.check-me').each(function(){
        jQuery(this).attr('checked',val);
    });

}

function moderator_reject(make){

    var vals = [];
    jQuery('.check-me').each(function(){
        var e=jQuery(this);
        if (e.attr('checked')) {

            vals.push(e.value);
        }

    });



    var report = jQuery('#reporttext').val();


    if (vals.length > 0) {

        if (jQuery('#showbox').css('display') == 'none') {

            jQuery('#showbox').css('display', 'block');
            jQuery('#showbox').slideDown('slow');
            jQuery('#reporttext').focus();
            return false;
        }
        if (jQuery.trim(report).length < 5) {
            jQuery('#reporttext').css('border-color', 'red');
            jQuery('#twitMsg').empty().html("Please provide a report message of atleast 5 words! ");
            jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
            return false;
        }
        else {
            jQuery('#reporttext').css('border-color', '');

        }



        if (confirm('Are you sure to reject the selected Issues?')) {
            jQuery('#actions').attr('value', make);

            //send form
            var formwave=jQuery('#mod-issue');
            jQuery('#tabcontent').css('opacity','0.75');
        
            jQuery.ajax({
                type: "POST",
                url: formwave.attr('action'),
                data: formwave.serialize(),
                dataType:"json",
                success: function(data){
                    jQuery('#reporttext').val('');
                    jQuery('#showbox').slideUp('slow');

                    jQuery('#tabcontent').css('opacity','1');
                    jQuery('#twitMsg').empty().html(data.msg);
                    jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
                },
                complete:function(){
                    jQuery('#tabcontent').load(jQuery('#mod-url').val());
                    jQuery('div.mod-midside-inner').html('<div class="warning">No Issue Selected !</div>');
                }
            });


        }
        else {
            return false;
        }
    }
    else {
        jQuery('#twitMsg').empty().html('select atleast one Issue for action!');
        jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
       
        return false;
    }

}



function load_issue_data(){



    jQuery('#q_cat').multiSelect({
        selectAll: false
    },function(){

        trigger_get_scat();

    });

    jQuery('#q_scat').multiSelect({
        selectAll: false
    },
    function(){

        trigger_get_sscat();

    });

    jQuery('#q_sscat').multiSelect({
        selectAll: false
    });
    jQuery('#q_country').multiSelect({
        selectAll: false

    },function() {
       // trigger_get_state();
    });
    jQuery('#q_state').multiSelect({
        selectAll: false

    },function() {
        trigger_get_city();
    });
    jQuery('#q_city').multiSelect({
        selectAll: false

    });
    //var ahah = new Drupal.ahah(base, element_settings);
// jQuery.extend(Drupal.settings, { "basePath": "\u002fheardmentality\u002f", "user_relationships_ui": { "loadingimage": "\u002fheardmentality\u002fsites\u002fall\u002fmodules\u002fuser_relationships\u002fuser_relationships_ui\u002fimages\u002floadingAnimation.gif", "savingimage": "\u002fheardmentality\u002fsites\u002fall\u002fmodules\u002fuser_relationships\u002fuser_relationships_ui\u002fimages\u002fsavingimage.gif", "position": { "position": "absolute", "left": "0", "top": "0" } }, "send_button": "Queue for translation", "send_link": "Send now", "queued_message": "There are strings queued for translation: ", "checking_status": "Checking status...", "ican_url": { "ican_string_status_url": "\u002fheardmentality\u002ficl_content\u002ficl_string_status", "ican_string_send_url": "\u002fheardmentality\u002ficl_content\u002ficl_string_send", "ican_string_que_url": "\u002fheardmentality\u002fadmin\u002fcontent\u002ftranslation-management\u002fdashboard?string=queued", "ican_string_token": "90ed507b5bd465275050eb9353589d8f" }, "ahah": { "edit-poll-more": { "url": "\u002fheardmentality\u002fmoderator\u002fissue\u002faddanswer", "event": "mousedown", "keypress": true, "wrapper": "poll-choices", "selector": "#edit-poll-more", "effect": "fade", "method": "replace", "progress": { "type": "throbber" }, "button": { "op": "Add Another Answer" } } } });
//Drupal.attachBehaviors($("#mod-edit-issue"));

  //  trigger_get_state();
    trigger_get_scat();

}




jQuery('#mod-user').live('submit',function(){

    jQuery('#actions').val('1');
    jQuery('#reporttext').val('');
    jQuery('#showbox').slideUp('slow');
    var formwave=jQuery(this);
    var vals = [];
    jQuery('.check-me:checked').each(function(){
        var e=jQuery(this);
        vals.push(e.val());

    });

    if (vals.length > 0) {
        if(jQuery('#mod-type').val()=='flag'){
            if(confirm('Are you sure to Ignore this Issues?')){
                jQuery.ajax({
                    url:formwave.attr('action'),
                    global: false,
                    type: "POST",
                    data: formwave.serialize(),
                    dataType: "json",
                    async:false,
                    success: function(data){
                        jQuery('#twitMsg').empty().html(data.msg);
                        jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
                    },
                    complete:function(){
                        jQuery('#rcontent').load(jQuery('#mod-url').val());
                        jQuery('div.mod-midside-inner').html('<div class="warning">No Issue Selected !</div>');
                        jQuery('div.mod-leftside-inner').html('<div class="warning">No USer Selected !</div>');

                    }
                }
                );

            }
        }else{


    }


    }
    else {

        jQuery('#twitMsg').empty().html('select atleast one user for action!');
        jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
    }
    return false;
});



function moderator_reject_user(make){

    var vals = [];
    jQuery('.check-me').each(function(){
        var e=jQuery(this);
        if (e.attr('checked')) {

            vals.push(e.value);
        }

    });



    var report = jQuery('#reporttext').val();


    if (vals.length > 0) {

        if (jQuery('#showbox').css('display') == 'none') {

            jQuery('#showbox').css('display', 'block');
            jQuery('#showbox').slideDown('slow');
            jQuery('#reporttext').focus();
            return false;
        }
        if (jQuery.trim(report).length < 5) {
            jQuery('#reporttext').css('border-color', 'red');
            jQuery('#twitMsg').empty().html("Please provide a report message of atleast 5 words! ");
            jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
            return false;
        }
        else {
            jQuery('#reporttext').css('border-color', '');

        }



        if (confirm('Are you sure to reject the selected Users?')) {
            jQuery('#actions').attr('value', make);

            //send form
            var formwave=jQuery('#mod-user');
            jQuery('#tabcontent').css('opacity','0.75');

            jQuery.ajax({
                type: "POST",
                url: formwave.attr('action'),
                data: formwave.serialize(),
                dataType:"json",
                success: function(data){
                    jQuery('#reporttext').val('');
                    jQuery('#showbox').slideUp('slow');

                    jQuery('#tabcontent').css('opacity','1');
                    jQuery('#twitMsg').empty().html(data.msg);
                    jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
                },
                complete:function(){
                     jQuery('#reporttext').val('');
                    jQuery('#showbox').slideUp('slow');
                    jQuery('#rcontents').load(jQuery('#mod-url').val());
                    jQuery('div.mod-midside-inner').html('<div class="warning">No Issue Selected !</div>');
                    jQuery('div.mod-leftside-inner').html('<div class="warning">No USer Selected !</div>');
                        
                }
            });


        }
        else {
            return false;
        }
    }
    else {
        jQuery('#twitMsg').empty().html('select atleast one User for action!');
        jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);

        return false;
    }

}
function moderator_ignore_user(make){

    if(jQuery('#mod-type').val()=='new')
    {
         jQuery('#twitMsg').empty().html('No Ignore Action for All Users, kindly try ignore activity on flagged user list!');
        jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
        return false;
    }


        var vals = [];
    jQuery('.check-me').each(function(){
        var e=jQuery(this);
        if (e.attr('checked')) {

            vals.push(e.value);

        }

    });



    var report = jQuery('#reporttext').val();


    if (vals.length > 0) {

         if (confirm('Are you sure to ignore the selected Users?')) {
            jQuery('#actions').attr('value', make);

            //send form
            var formwave=jQuery('#mod-user');

            jQuery.ajax({
                url:formwave.attr('action'),
                global: false,
                type: "POST",
                data: formwave.serialize(),
                dataType: "json",
                async:false,
                success: function(data){
                    jQuery('#twitMsg').empty().html(data.msg);
                    jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
                },
                complete:function(){
                     jQuery('#reporttext').val('');
                    jQuery('#showbox').slideUp('slow');
                    jQuery('#rcontents').load(jQuery('#mod-url').val());
                    jQuery('div.mod-midside-inner').html('<div class="warning">No Issue Selected !</div>');

                }
            }
            );


        }
        else {
            return false;
        }
    }
    else {
        jQuery('#twitMsg').empty().html('select atleast one User for action!');
        jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);

        return false;
    }



}
function moderator_warn_user(make){

    var vals = [];
    jQuery('.check-me').each(function(){
        var e=jQuery(this);
        if (e.attr('checked')) {

            vals.push(e.value);

        }

    });



    var report = jQuery('#reporttext').val();


    if (vals.length > 0) {

        if (jQuery('#showbox').css('display') == 'none') {

            jQuery('#showbox').css('display', 'block');
            jQuery('#showbox').slideDown('slow');
            jQuery('#reporttext').focus();
            return false;
        }
        if (jQuery.trim(report).length < 5) {
            jQuery('#reporttext').css('border-color', 'red');
            jQuery('#twitMsg').empty().html("Please provide a report message of atleast 5 words! ");
            jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
            return false;
        }
        else {
            jQuery('#reporttext').css('border-color', '');

        }



        if (confirm('Are you sure to warn the selected Users?')) {
            jQuery('#actions').attr('value', make);

            //send form
            var formwave=jQuery('#mod-user');

            jQuery.ajax({
                url:formwave.attr('action'),
                global: false,
                type: "POST",
                data: formwave.serialize(),
                dataType: "json",
                async:false,
                success: function(data){
                    jQuery('#twitMsg').empty().html(data.msg);
                    jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
                },
                complete:function(){
                     jQuery('#reporttext').val('');
                    jQuery('#showbox').slideUp('slow');
                    jQuery('#rcontents').load(jQuery('#mod-url').val());
                    jQuery('div.mod-midside-inner').html('<div class="warning">No Issue Selected !</div>');
                 
                }
            }
            );







        }
        else {
            return false;
        }
    }
    else {
        jQuery('#twitMsg').empty().html('select atleast one User for action!');
        jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);

        return false;
    }





}


function loadusermessage(url,title)
{

    var options = 'sameBox:true width:50% height:70% caption:' +title;
    parent.fb.start(url, options);

}

jQuery(document).ready(function(){
    jQuery("#msg-sub").click(function() {
        var message = jQuery("#message").val();
        if(message == ''){
            jQuery('#twitMsg',top.document).html("Enter your message to send");
            jQuery('#twitMsg',top.document).delay(400).slideDown(400).delay(3000).slideUp(400);
            return false;
        }
    });

    jQuery('#message').keyup(function() {
                var len = this.value.length;
                var totalchar = 100;
                if (len >= totalchar) {
                    this.value = this.value.substring(0, totalchar);
                }
                if(len <= totalchar){
                jQuery('#charLeft').text(totalchar - len);
                }
                
            });



  

});

function load_issue_data_ahah(){
     jQuery('#q_cat').trigger('click');
   
     
     setTimeout(catSet,3000);
     jQuery('#q_country').trigger('click');
     setTimeout(locSet,3000);
  }

  function catSet(){
      jQuery('#q_scat').trigger('click');
  }
  function locSet(){
      jQuery('#q_state').trigger('click');
  }

//  if (Drupal.jsEnabled) {
//
//    var selected = new Array();
//
//   jQuery('select').live('mouseover',function() {
//
//      if (this.multiple == true) {
//        for (var i=0,a=0;i<this.options.length;i++) {
//          if (this.options[i].selected == true) {
//            selected[a] = this.options[i].value;
//            a++;
//          }
//        }
//      }
//    });
//
//    // safe them when you click the mouse
//    jQuery('select').live('change',function() {
//      // make sure it's a multiple select
//      alert(this.multiple);
//      if (this.multiple == true) {
//        for(var i=0;i<selected.length;i++) {
//          for(var a=0;a<this.options.length;a++){
//            if (selected[i] == this.options[a].value && this.options[a].selected == true) {
//              this.options[a].selected = false;
//              selected.splice(i,1);
//            } else if (selected[i] == this.options[a].value) {
//              this.options[a].selected = true;
//            }
//          }
//        }
//      }
//
//      // load all selected options in array when the mouse pointer hovers the select box
//      if (this.multiple == true) {
//        for (var i=0,a=0;i<this.options.length;i++) {
//          if (this.options[i].selected == true) {
//            selected[a] = this.options[i].value;
//            a++;
//          }
//        }
//      }
//
//    });
//
//}


function mod_hide_issue(issid){
    
    jQuery.ajax({
        method: "POST",
        url: sitepath+'/moderator/ajax/issue',
        dataType: "json",
        data: {'nid': issid, 'mod-type': 'hide'},
        success: function(data){
            //alert(data.content);
            var stream = '#stream-'+issid;
            jQuery(stream).remove();
        }
    });
}

/**Rallydev:485**/
$(document).ready(function() {
   /*For Categories*/
   setTimeout("__mulitselect_hack('#q_cat','#q_scat','#q_sscat','No sub category')",3000);
   setTimeout("__mulitselect_hack('#qs_cat','#q_sscat','','')",6000);

   /*For Locations*/
   setTimeout("__mulitselect_hack('#q_country','#q_state','#edit-q-city','No states selected')",3000);
   setTimeout("__mulitselect_hack('#q_state','#edit-q-city','','')",6000);
});

function __mulitselect_hack(parent,child,sub_child,message) {
  var scat_buffer = new Array();
  var i;

   $(child+' option').each(function(){
     if($(this).attr("selected")) {
	    scat_buffer.push($(this).val());
	  }
   });

   $(parent).click(function(){
	  scat_buffer = []; x = 0;
	  if(sub_child != "null") {
		 $(sub_child+' option').each(function(){
		   if(x == 0) { //$(this).html(message);} else { $(this).html(''); $(this).removeAttr("selected");
		   } x = x + 1;
		 });
	   }
   });

   $(child).live('change',function() {
     flag =0;
      for(i=0;i<scat_buffer.length;i++) {
         if(parseInt(scat_buffer[i]) == parseInt($(this).val())){
			scat_buffer[i] = "";
			flag = 1;
		}
	  }

	  if (flag == 0) {
	    scat_buffer.push($(this).val());
	  }

	  $(child+' option').each(function(){
	    $(this).removeAttr("selected");
	  });

	  for(i=0;i<scat_buffer.length;i++) {
	    $(child+' option').each(function(){
		  if(scat_buffer[i] == $(this).val()) {
		    $(this).attr("selected","selected");
		  }
		});
	  }
   });
}
/*************************************/