
jQuery("a.sublinks").live("click", function(e) {

    e.preventDefault();
    e.stopPropagation();

    var cid = jQuery(this).attr('id').split('-');
    jQuery("#hid_scat").val(cid[1]);
    jQuery('a.sublinks').each(function(){
        jQuery(this).css("font-weight","normal");
    });
    search_user(0);
    jQuery(this).css("font-weight","bold");
    //jQuery(this).removeAttr('id');
    return false;
});

function get_profile_details(urid){
    //alert(urid);
    var url = gSitePath + 'userinfo';
    jQuery('#user_info').empty();
    jQuery.ajax({
        type: "POST",
        url: url,
        dataType: 'xhr',
        data: {
            getuid: urid
        },
        success: function(msg){

            jQuery('#user_info').html(msg);
            reset_tabs();
        }
    });

}

function get_state(code){


    var url = gSitePath + 'question/ajax';
    jQuery.ajax({
        type: "POST",
        url: url,
        dataType: 'xhr',
        data: {
            action: '1',
            code:code
        },
        success: function(msg){
            jQuery('#chg_state').html(msg);

        }
    });



}


function get_city(ccode){

    var url = gSitePath + "question/ajax";

    jQuery.ajax({
        type: "POST",
        url: url,
        dataType: 'xhr',
        data: {
            action: '2',
            code:ccode
        },
        success: function(msg){
            jQuery('#chg_city').html(msg);

        }
    });


    var url = gSitePath + "userresults";
    var t_search = $("#txt_search").val();
    jQuery.ajax({
        type: "POST",
        url: url,
        dataType: 'xhr',
        data: {
            action: '2',
            ccode:ccode,
            txt_search: t_search
        },
        success: function(msg){
            jQuery('.inner-page-cont').html(msg);

        }
    });


}



function search_user(loadcat){
    // question search starts
    var url = gSitePath+"searchuser_ajax";
    //var url = gSitePath+"sites/all/modules/user_search/sidebar.php";

    var  txt_search = jQuery('#hid_txtsearch').val();
    var  page_id = jQuery('#hid_page').val();
    var  cid = jQuery('#hid_cat').val();

    var  scid = jQuery('#hid_scat').val();

    var  q_country = jQuery('#q_country').val();
    var  q_state = jQuery('#q_state').val();
    var  q_city = jQuery('#q_city').val();

    jQuery.ajax({
        type: "GET",
        url: url,
        data: {
            'cid':cid,
            'scid':scid,
            'q_country':q_country,
            'q_state':q_state,
            'q_city':q_city,
            'start':page_id,
            'txt_search':txt_search
        },
        success: function(msg){
            jQuery('#ufilter').html(msg);
        }
    });


    var qid =  jQuery('#q_countryuser').val();
    // alert(qid);
    if(loadcat==1)
    {
        url = gSitePath+"searchuser_category_ajax";

        jQuery.ajax({
            type: "GET",
            url: url,
            data: {
                'cid':cid,
                'scid':scid,
                'q_country':q_country,
                'q_state':q_state,
                'q_city':q_city,
                'start':page_id,
                'txt_search':txt_search
            },
            success: function(msg){
                jQuery('#pad10').html(msg);
            }
        });
    }

}


jQuery(document).ready(function(){
    //  var url = gSitePath;


    jQuery('#q_country').change(function(e){
        search_user(1);
    });

    jQuery('#q_state').live("change", function(e) {


        search_user(1);
    });
    jQuery('#q_city').live("change", function(e) {


        search_user(1);
    });


jQuery(".sidelinks a").live("click", function(e) {

    var cid = jQuery(this).attr('id').split('-');
    jQuery("#hid_cat").val(cid[1]);
    jQuery("#hid_scat").val('');
    search_user(0);
    var  scid = jQuery('#hid_scat').val();
    jQuery('.sidelinks a').each(function(){
        jQuery(this).css("font-weight","normal");
    });
    jQuery('#sublinks').remove();
    jQuery(this).parent().after(jQuery('<span id="sublinks" class="sublinks"></span>'));

    jQuery('#sublinks').load(gSitePath+'question/ajax', {
        "user_scat":cid[1],
        "scid":scid
    }, function(response, status, xhr) {

        if (status == "error") {
            alert('Sorry Subcategory loaing error');
        }
    });

    jQuery(this).css("font-weight","bold");
    //jQuery(this).removeAttr('id');
    e.preventDefault();
    e.stopPropagation();
    return false;
});


    jQuery("a.sublinks").live("click", function(e) {



        e.preventDefault();
        e.stopPropagation();

        var cid = jQuery(this).attr('id').split('-');
        jQuery("#hid_scat").val(cid[1]);
        jQuery('a.sublinks').each(function(){
            jQuery(this).css("font-weight","normal");
        });
        search_user(0);

        jQuery(this).css("font-weight","bold");
        //jQuery(this).removeAttr('id');
        return false;
    });




    jQuery('.page-n a').livequery("click", function(e) {

        var page_id =  jQuery(this).attr('id');
        jQuery("#hid_page").val(page_id);
        search_user(0);
    });
//question search ends


});