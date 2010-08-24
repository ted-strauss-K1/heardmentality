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



			
						
				
			
						
						
							


