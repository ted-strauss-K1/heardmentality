/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */



jQuery(document).ready(function(){

    jQuery('#tabcontent').ajaxStart(function(){
       //   jQuery('div.mod-midside-inner').html('<div class="warning">No Issue Selected !</div>');
      
    });

    jQuery('#qdupeform').live('submit',function(e){
        e.preventDefault();
         var dupeid=$("#qdupeform input[type='radio']:checked").val();
         var qid=$("#qdupeform input[type='hidden']").val();
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

jQuery('#merge-dupeform').live('submit',function(e){
        e.preventDefault();
           var data=jQuery(this).serialize();
            jQuery.ajax({
                type: "POST",
                dataType: 'json',
                url: jQuery(this).attr('action'),
                data:data,
                success: function(msg){
                    jQuery('#twitMsg').html(msg.msg);
                    jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
                    var qid=msg.qid;
                },
                complete:function(){
                jQuery('div.mod-midside-inner').load(jQuery('a[name="icurrent"]').attr('href'),function() {
  load_issue_data();
});
                    fb.end();
                    
                }
            });
    });

    jQuery('#mod-question').live('submit',function(e){
        e.preventDefault();
        if(validate_question()){

            var data=jQuery(this).serialize();
            jQuery.ajax({
                type: "POST",
                dataType: 'json',
                url: jQuery(this).attr('action'),
                data:data,
                success: function(msg){
                    jQuery('#twitMsg').html(msg.msg);
                    jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
                }
            });
            return true;
        }else{
            jQuery('#twitMsg').html('Some Of The Required fields are Empty!');
            jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
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



    jQuery('a.issue-links').live('click',function(e){
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
            url: jQuery(this).attr('href'),
            complete: function(){
             
            load_issue_data();
            },

            success: function(msg){
                jQuery('#mod-edit-issue').html(msg);
                
            }
        });
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
    jQuery('.pager a').live('click',function(e){
        e.preventDefault();
        e.stopPropagation();
        jQuery(this).parents('div.mytabs-container').load(jQuery(this).attr('href'));
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

    get_mod_city(ids);

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

            var statearray=setstate.split(',');
            jQuery('#q_state').val(statearray);
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
            'ids' :ids
        },
        success: function(data){
            jQuery('#chg_city').html(data.content);
        },
        complete: function(){
            var cityarray=setcity.split(',');
            jQuery('#q_city').val(cityarray);
            
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
                    trigger_get_state();
                });
                jQuery('#q_state').multiSelect({
                    selectAll: false

                },function() {
                    trigger_get_city();
                });
                jQuery('#q_city').multiSelect({
                    selectAll: false

                });

                trigger_get_state();
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
                        jQuery('#tabcontent').load(jQuery('#mod-url').val());
                            jQuery('div.mod-midside-inner').html('<div class="warning">No Issue Selected !</div>');

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
        jQuery('#twitMsg').empty().html('select atleast one User for action!');
        jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);

        return false;
    }

}