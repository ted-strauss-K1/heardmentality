/**
 * @author gobinath.m
 */
 


function bio_tog(ele){
    var cls=jQuery(ele).parent().attr('class');

    jQuery('#l1 span').each(function(){
        jQuery(this).attr('class','');
        jQuery(this).attr('class','tab-historyspan5');
    });
    if(cls=='tab-historyspan5'){
        jQuery(ele).parent().attr('class','');
        jQuery(ele).parent().attr('class','tab-historyspan4');

    }
    if(cls=='tab-historyspan4'){
        jQuery(ele).parent().attr('class','');
        jQuery(ele).parent().attr('class','tab-historyspan5');

    }




    jQuery('#bio').toggle();
    jQuery('#link').toggle();
}
function rel_msg(id){

    jQuery('#actions').val(id);
    jQuery('#showboxcmt').slideToggle('slow');
    jQuery("#usmsg").unbind("click");

    jQuery("#usmsg").click(function () {
        var formmsg=jQuery('#proform');
        jQuery.post(formmsg.attr('action'),formmsg.serialize(),
            function(data){

                jQuery('.profile_part').prepend(data);
                jQuery('#showboxcmt').slideToggle("slow");
                formmsg.get(0).reset();
                setTimeout("jQuery('.profile_part > div.messages').hide();",1000);
            });
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
     url = gSitePath + "userresults";
    var t_search = $("#txt_search").val();
    jQuery.ajax({
        type: "POST",
        url: url,
        dataType: 'xhr',
        data: {
            action: '1',
            code:code,
            txt_search: t_search
        },
        success: function(msg){
            jQuery('.inner-page-cont').html(msg);
            
        }
    });
    
		
	
   
}



function get_statequestion(q_country,txt_search,cid){
    //document.thisform.submit();

    window.location = gSitePath+"searchquestion?q_country="+q_country+"&txt_search="+txt_search+"&cid="+cid;
}
function get_stateuser(q_country,txt_search,cid,scid){
    //document.thisform.submit();

    window.location = gSitePath+"searchuser?q_country="+q_country+"&txt_search="+txt_search+"&cid="+cid+"&scid="+scid;
}

function get_cityquestion(q_state,txt_search,cid,q_country){
    //document.thisform.submit();
    window.location = gSitePath+"searchquestion?q_state="+q_state+"&txt_search="+txt_search+"&cid="+cid+"&q_country="+q_country;
}
function get_cityuser(q_state,txt_search,q_country,cid,scid){
    //document.thisform.submit();
    window.location = gSitePath+"searchuser?q_state="+q_state+"&txt_search="+txt_search+"&q_country="+q_country+"&cid="+cid+"&scid="+scid;
}


function get_question(q_city,txt_search,cid,q_country,q_state){
    //document.thisform.submit();
    window.location = gSitePath+"searchquestion?q_city="+q_city+"&txt_search="+txt_search+"&cid="+cid+"&q_country="+q_country+"&q_state="+q_state;
}
function get_user(q_city,txt_search,q_country,q_state,cid,scid){
    //document.thisform.submit();
    window.location = gSitePath+"searchuser?q_city="+q_city+"&txt_search="+txt_search+"&q_country="+q_country+"&q_state="+q_state+"&cid="+cid+"&scid="+scid;
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




			
function setDefaultCountry(cnt) {

    var countrySelect = document.getElementById("q_country");

    for (i=0;i< countrySelect.length;i++) {
        // the javascript geonamesData.js contains the countrycode
        // of the userIp in the variable \'geonamesUserIpCountryCode\'
        if (countrySelect[i].value == cnt) {
            // set the country selectionfield
            countrySelect.selectedIndex = i;
            get_state(cnt);
        }
    }
  
  
}

//temporarly disabled ajax post questions search
/*jQuery(document).ready(function(){
 $("#save").click(function() {
     
        var answer = $('input:radio[id=answer]:checked').val();
	//var answer = $("#answer").val();
        var mid = $("#mid").val();
        var save = 1;
        var dataString = 'answer='+ answer + '&mid=' + mid + '&save=' + save;
		//alert (dataString);return false;
		var url = gSitePath + "qlite/save";
                    
		jQuery.ajax({
      type: "POST",
      url: gSitePath + "qlite/save",
      data: dataString,
      success: function() {
	  alert("Vote added successfully");
        //$('.inner-page-cont').html("<div id='message'></div>");
        //$('#message').html("<h2>Vote added successfully</h2>")
      }
     });
    return false;
	});			
});*/
//href="' . $gSitePath . 'searchquestion?cid=' . $cat['cat_id'] . '&txt_search=' . $txt_search .'&q_country='.$q_country.'&q_state='.$q_state.'&q_city='.$q_city.'"



function search_user(){
    // search_category();
    var url = gSitePath+"searchuser_ajax";
    //var url = gSitePath+"sites/all/modules/user_search/sidebar.php";

    var  txt_search = jQuery('#txt_search').val();
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
            jQuery('.user_search_3').html(msg);
        }
    });


    var qid =  jQuery('#q_country').val();
    // alert(qid);
    if(qid!=0&&cid=='')
    {
         url = gSitePath+"searchquestion_category_ajax";
       
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




function search_question(loadcat){
    // question search starts
    var url = gSitePath+"searchquestion_ajax";
    //var url = gSitePath+"sites/all/modules/user_search/sidebar.php";

    var  txt_search = jQuery('#txt_search').val();
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
            jQuery('#qfilter').html(msg);
        }
    });

    
    var qid =  jQuery('#q_country').val();
    // alert(qid);
    if(loadcat==1)
    {
         url = gSitePath+"searchquestion_category_ajax";
         
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
        search_question(1);
    });

    jQuery('#q_state').live("change", function(e) {


        search_question(1);
    });
    jQuery('#q_city').live("change", function(e) {


        search_question(1);
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

 

    jQuery(".sidelinks a").live("click", function(e) {


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
    });

    jQuery("a.sublinks").live("click", function(e) {

   

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
    });




    jQuery('.page-n a').livequery("click", function(e) {
      
        var page_id =  jQuery(this).attr('id');
        jQuery("#hid_page").val(page_id);
        search_question(0);
    });
//question search ends


});



						

