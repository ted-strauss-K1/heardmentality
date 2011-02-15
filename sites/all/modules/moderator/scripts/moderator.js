/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */



jQuery(document).ready(function(){



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
            return false;
        }


    });

    jQuery('a.issue-links').live('click',function(e){
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
             
                jQuery('#q_cat').multiSelect({
                    oneOrMoreSelected: '*'
                });

                jQuery('#q_scat').multiSelect({
                    oneOrMoreSelected: '*'
                });
                jQuery('#q_sscat').multiSelect({
                    oneOrMoreSelected: '*'
                });
                jQuery('#q_country').multiSelect({
                    oneOrMoreSelected: '*'
                },function() {
                    var values = new Array();
                    jQuery.each(jQuery("input[name='q_country[]']:checked"), function() {
                        values.push(jQuery(this).val());
                    // or you can do something to the actual checked checkboxes by working directly with  'this'
                    // something like $(this).hide() (only something useful, probably) :P
                    });
                    var ids=values.join(',');
                    get_mod_state(ids);
                });
                jQuery('#q_state').multiSelect({
                    oneOrMoreSelected: '*'
                });
                jQuery('#q_city').multiSelect({
                    oneOrMoreSelected: '*'
                },function() {
                    alert('Something was checked!');
                });

                jQuery('.selectAll').remove();
            },

            success: function(msg){
                jQuery('.mod-midside-inner').html(msg);
                
            }
        });
    });




});

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
    var url = spath+"moderator/ajax/state";
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
         complete: function(){ jQuery('#q_state').multiSelect({
                    oneOrMoreSelected: '*'
                });
         }
    });
    

jQuery('#chg_city').html('');
    jQuery('#chg_city').fadeOut('slow');

}

function get_city(code){
    jQuery('#chg_city').fadeIn('slow');
    var url = spath+"question/ajax";

    jQuery.ajax({
        type: "GET",
        url: url,
        dataType: 'json',
        data: {
            'action': 2,
            'code' :code,
            'select':1
        },
        success: function(msg){
            jQuery('#chg_city').html(msg.content);
        }
    });

}



jQuery("input[name='q_cat[]']").live("change", function(event) {

    var values = new Array();
    jQuery.each(jQuery("input[name='q_cat']:checked"), function() {
        values.push(jQuery(this).val());
    // or you can do something to the actual checked checkboxes by working directly with  'this'
    // something like $(this).hide() (only something useful, probably) :P
    });
    var ids=values.join(',');
    if(!admin){
        get_releted_issue(ids);
    }


    get_subcat('q_cat','chg_scat',1,ids);
    jQuery('#chg_sscat').empty().html('No Subcategory');
});

jQuery("input[name='q_scat[]']").live("change", function(event) {

    var values = new Array();
    jQuery.each(jQuery("input[name='q_scat[]']:checked"), function() {
        values.push(jQuery(this).val());
    // or you can do something to the actual checked checkboxes by working directly with  'this'
    // something like $(this).hide() (only something useful, probably) :P
    });
    var ids=values.join(',');

    get_subcat('q_scat','chg_sscat',2,ids);
});


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

            var url = spath+"question/ajax";
            jQuery.ajax({
                type: "POST",
                url: url,
                data: {
                    'action': level,
                    'ids' :ids
                },
                success: function(msg){
                    jQuery('#'+divid).html(msg);
                    if(sid=='q_cat')
                        window.setTimeout("jQuery('#q_scat').multiSelect(); jQuery('.selectAll').remove();", 500);
                    else if(sid=='q_scat')
                        window.setTimeout("jQuery('#q_sscat').multiSelect(); jQuery('.selectAll').remove();", 500);
                // jQuery('#'+divid+'input:select').multiSelect();
                }
            });


        //get_tag_cat(ids,level);
        }
    }else{
        jQuery('#'+divid).html('No Subcategory');
    }
}
