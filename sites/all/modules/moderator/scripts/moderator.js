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
            jQuery('#twitMsg').html('Some Of The Required fields are Empty!');
            jQuery('#twitMsg').delay(400).slideDown(400).delay(3000).slideUp(400);
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
            },

            success: function(msg){
                jQuery('.mod-midside-inner').html(msg);
                
            }
        });
    });

jQuery('#tabcontent .pager a').live('click',function(e){
     e.preventDefault();
        e.stopPropagation();
   jQuery('#tabcontent').load(jQuery(this).attr('href'));
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
    var url = spath+"moderator/ajax/city";
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
