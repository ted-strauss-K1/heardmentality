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
   
	 jQuery.ajax({
        type: "POST",
        url: url,
        dataType: 'xhr',
        data: {
            action: '1',
			code:code
        },
        success: function(msg){
            jQuery('.inner-page-cont').html(msg);
            
        }
    });
    
		
	
   });
	
}

function get_city(code){

    var url = gSitePath + "question/ajax";
	
	 jQuery.ajax({
        type: "POST",
        url: url,
        dataType: 'xhr',
        data: {
            action: '2',
			code:code
        },
        success: function(msg){
            jQuery('#chg_city').html(msg);
            
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

    jQuery(".contarea a[href*='?ajax=1']").each(function(){
   
        jQuery(this).click(function () {
         
          jQuery("#quest_info").load(jQuery(this).attr('href'), function(response, status, xhr) {

        
  if (status == "success") {
reset_tabs();
}
});

            return false;
        });
       
    });

});

function reset_tabs(){
var tabarray=['#maintabs,#tabcontent'];

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

jQuery(document).ready(function(){
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
});						
				
			
						
						
							


