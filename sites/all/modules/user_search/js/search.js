/**
 * @author gobinath.m
 */

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

function bio_tog(ele){
    var cls=jQuery(ele).parent().attr('class');

    jQuery('#l1 span').each(function(){ jQuery(this).attr('class',''); jQuery(this).attr('class','tab-historyspan5'); });
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
 $(document).ready(function() {
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
	var url = gSitePath + "userresults";
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



function get_quest_details(quid){
    //alert(quid);
	el=jQuery('#quest_info');
	el.empty();
    var url = gSitePath + "questinfo";

    jQuery.ajax({
        type: "POST",
        url: url,
        dataType: 'xhr',
        data: {
            qsaid: quid
        },
        success: function(msg){
            el.html(msg);
            
        }
    });
    
    
}

			
   function setDefaultCountry(cnt) {
   $(document).ready(function() {
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
      });


  
}

jQuery(document).ready(function(){
var url = gSitePath;
    jQuery(".contarea a[href*='?ajax=1']").each(function(){
   //livequery('click', function(event)
   //jQuery(this).livequery('click',function(event) {
        jQuery(this).click(function () {
          jQuery("#quest_info").load(jQuery(this).attr('href'), function(response, status, xhr) {

  if (status == "success") {
reset_tabs();
}
});
            // var url = "http://stackoverflow.com";
           // $(location).attr('href',url);
           return false;
        });
       
    });

});

function reset_tabs(){
var tabarray=['#maintabs,#tabcontent','#tabs,#tabs-container','#vmaintabs1,#tabcontent','#vmaintabs2,#tabcontent'];

      // Preload tab on page load
      
 jQuery.each(tabarray,function(){
       // e.preventDefault();
        var arr=this.split(",");

        var tabsId = arr[0];
        var containerId = arr[1];


        if($(tabsId + ' LI.current A').length > 0){
            loadTab($(tabsId + ' LI.current A'),containerId);
        }

        $(tabsId + ' A').click(function(e){
           
                if($(this).attr('href')=='#') {
                  e.preventDefault();
                     e.stopPropagation();
                     return false;
                     }
            if($(this).parent().hasClass('current')){

                return false;
            }

            $(tabsId + ' LI.current').removeClass('current');
            $(this).parent().addClass('current');

            loadTab($(this),containerId);
            return false;
        });





    });

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
function search_question(cat_id,q_country,q_state,q_city){
    var url = gSitePath+"searchquestion_ajax";
    jQuery.ajax({
        type: "GET",
        url: url,
        data: {
            'cid' :cat_id,
            'q_country':q_country,
            'q_state':q_state,
            'q_city':q_city
        },
        success: function(msg){
            jQuery('.issuesearch3').html(msg);
        }
    });

}
	

	jQuery(document).ready(function(){
	 $('.issuesearch3 a').click(function() {
        //$('#box1').css("background","#9f9");
        $(".issuesearch3 a").css('color', '#996600');
        $(this).css('color', '#4170A0');
        
        });
        });

        
						

