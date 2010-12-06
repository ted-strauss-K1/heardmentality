jQuery(".userlinks a").live("click", function(e) {
 
        var cid = jQuery(this).attr('id').split('-');
        jQuery("#hid_cat").val(cid[1]);
  jQuery("#hid_scat").val('');
        search_user(0);
        var  scid = jQuery('#hid_scat').val();
         jQuery('.userlinks a').each(function(){
            jQuery(this).css("font-weight","normal");
        });
        jQuery('#sublinks').remove();
        jQuery(this).parent().after(jQuery('<span id="sublinks" class="sublinks"></span>'));

        jQuery('#sublinks').load(gSitePath+'user/ajax', {
            "sel_id":cid[1],
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




function search_user(loadcat){
    // question search starts
    var url = gSitePath+"searchuser_ajax";
    //var url = gSitePath+"sites/all/modules/user_search/sidebar.php";

    var  txt_search = jQuery('#hid_txtsearch').val();
    var  page_id = jQuery('#hid_page').val();
    var  cid = jQuery('#hid_cat').val();

    var  scid = jQuery('#hid_scat').val();

    var  q_country = jQuery('#q_countryuser').val();
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
            jQuery('.user_search_3').html(msg);
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
    jQuery('#q_countryuser').change(function(e){
        search_user(1);
    });

    jQuery('#q_state').live("change", function(e) {
        search_user(1);
    });
    jQuery('#q_city').live("change", function(e) {
        search_user(1);
    });


    jQuery("#qfilter a[href*='?ajax=1']").live("click", function(e) {

        e.preventDefault();
        e.stopPropagation();

        jQuery("#quest_info").load(jQuery(this).attr('href'), function(response, status, xhr) {
            if (status == "success") {
                reset_tabs();
            }
        });
        jQuery("#qfilter a").each(function(){
            jQuery(this).css('color', '#996600')
        });
        jQuery(this).css('color', '#4170A0');
        // var url = "http://stackoverflow.com";
        // $(location).attr('href',url);
        return false;
    });



   /* jQuery(".sidelinks a").live("click", function(e) {


        var cid = jQuery(this).attr('id').split('-');
        jQuery("#hid_cat").val(cid[1]);
  jQuery("#hid_scat").val('');
        search_question(0);
        var  scid = jQuery('#hid_scat').val();
         jQuery('.sidelinks a').each(function(){
            jQuery(this).css("font-weight","normal");
        });
        jQuery('#sublinks').remove();
        jQuery(this).parent().after(jQuery('<span id="sublinks" class="sublinks"></span>'));

        jQuery('#sublinks').load(gSitePath+'question/ajax', {
            "sel_id":cid[1],
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
    });*/

   /* jQuery("a.sublinks").live("click", function(e) {



        e.preventDefault();
        e.stopPropagation();

        var cid = jQuery(this).attr('id').split('-');
        jQuery("#hid_scat").val(cid[1]);
        jQuery('a.sublinks').each(function(){
            jQuery(this).css("font-weight","normal");
        });
        search_question(0);

        jQuery(this).css("font-weight","bold");
        //jQuery(this).removeAttr('id');
        return false;
    });*/




    jQuery('.page-n a').livequery("click", function(e) {
        var page_id =  jQuery(this).attr('id');
        jQuery("#hid_page").val(page_id);
        search_user(0);
    });
//question search ends

    ///for user search
    jQuery('span[id=user]').live("click", function(e) {
        e.preventDefault();
        e.stopPropagation();

        var cid =  jQuery(this).find('a').attr('id');
        jQuery("#hid_cat").val(cid);


        jQuery('a.userlinks').live('click', function(){
            var scid = jQuery(this).attr('sid');
            jQuery("#hid_scat").val(scid);
        });

        jQuery(".userlinks a").click(function(event){

            if($(this).hasClass('userlinks hilite').toString()=='true')
            {
                return false;
            }

            var id = this.id;

            jQuery(this).after(jQuery('<span class="sidelinks">').load('sites/all/modules/user_search/sidebar_ajaxuser.php', {
                "sel_id":id
            }));
            $(this).addClass("hilite");
            //jQuery(this).removeAttr('id');
            event.preventDefault();
        });



    //$('<br/><span class="sidelinks"> <a href="JavaScript:void(0);" id="1" class="sidelinks">Politics[23]</a></span>').insertAfter(jQuery(this).parent('span'));
    });


});