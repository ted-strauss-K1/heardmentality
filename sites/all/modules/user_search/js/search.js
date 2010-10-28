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
function get_stateuser(q_country,txt_search){
 //document.thisform.submit();

window.location = gSitePath+"searchuser?q_country="+q_country+"&txt_search="+txt_search;
}

function get_cityquestion(q_state,txt_search,cid,q_country){
 //document.thisform.submit();
 window.location = gSitePath+"searchquestion?q_state="+q_state+"&txt_search="+txt_search+"&cid="+cid+"&q_country="+q_country;
}
function get_cityuser(q_state,txt_search,q_country){
 //document.thisform.submit();
 window.location = gSitePath+"searchuser?q_state="+q_state+"&txt_search="+txt_search+"&q_country="+q_country;
}


function get_question(q_city,txt_search,cid,q_country,q_state){
 //document.thisform.submit();
 window.location = gSitePath+"searchquestion?q_city="+q_city+"&txt_search="+txt_search+"&cid="+cid+"&q_country="+q_country+"&q_state="+q_state;
}
function get_user(q_city,txt_search,q_country,q_state){
 //document.thisform.submit();
 window.location = gSitePath+"searchuser?q_city="+q_city+"&txt_search="+txt_search+"&q_country="+q_country+"&q_state="+q_state;
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
   
        jQuery(this).click(function () {
         
          jQuery("#quest_info").load(jQuery(this).attr('href'), function(response, status, xhr) {

        
  if (status == "success") {
reset_tabs();
}
});

            return false;
            window.location.replace(url);

           
        });
       
    });

});

function reset_tabs(){
var tabarray=['#maintabs,#tabcontent','#tabs,#tabs-container'];

      // Preload tab on page load
    jQuery.each(tabarray,function(e){
        var arr=this.split(",");

        var tabsId = arr[0];
        var containerId = arr[1];


        if($(tabsId + ' LI.current A').length > 0){
            loadTab($(tabsId + ' LI.current A'),containerId);
        }

        $(tabsId + ' A').click(function(){
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
	var answer = $("#answer").val();
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
	

	jQuery(document).ready(function(){
	 $('.issuesearch3 a').click(function() {
        //$('#box1').css("background","#9f9");
        $(".issuesearch3 a").css('color', '#996600');
        $(this).css('color', '#4170A0');
        
        });
        });
						
						
							


