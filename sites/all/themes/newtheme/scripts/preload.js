// JavaScript Document
<!-- Init AutoSuggest -->

/** Init autosuggest on Search Input **/
jQuery(function() {

	//==================== Search With all plugins =================================================
	// Unbind form submit
        if($('#stype2').attr('checked')===true) {
        var stype=2;
        }else{
           var stype=1;
        }

     
	jQuery('.home_searchEngine').bind('submit', function() {return true;} ) ;

                 //----------------------------------------------important----------
            //imp script url is overrided in the core autosuggest script find there

	       	var options = {
                script:"question/ajax?ssearch=1&limit=8&json=true&stype="+jQuery(".home_searchEngine input[type='radio']:checked").val()+"&",
		varname:"input",
		json:true,						// Returned response type
		shownoresults:true,				// If disable, display nothing if no results
		noresults:"No Results",			// String displayed when no results
		maxresults:8,					// Max num results displayed
		cache:false,					// To enable cache
		minchars:2,						// Start AJAX request with at leat 2 chars
		timeout:100000,					// AutoHide in XX ms
		callback: function (obj) { 		// Callback after click or selection
			// For example use :

			// Build HTML
			var html = "ID : " + obj.id + "<br>Main Text : " + obj.value + "<br>Info : " + obj.info;
			jQuery('#input_search_country_response').html(html).show() ;

			// => TO submit form (general use)
			//$('#search_country_value').val(obj.id);
			//$('.home_searchEngine').submit();
                        callfunction();
		}
	};

	// Init autosuggest
	var as_json = new bsn.AutoSuggest('txt_search', options);

	// Display a little watermak
	jQuery("#txt_search").Watermark("");


});

jQuery.fn.clearForm = function() {
  return this.each(function() {
 var type = this.type, tag = this.tagName.toLowerCase();
 if (tag == 'form')
   return jQuery(':input',this).clearForm();
 if (type == 'text' || type == 'password' || tag == 'textarea')
   this.value = '';
 else if (type == 'checkbox' || type == 'radio')
   this.checked = false;
 else if (tag == 'select')
   this.selectedIndex = -1;
  });
};

function loadflagquestion(url,title)
{
	
	
	//jQuery.nyroModalSettings({ title:'Flag Posts'});

	//jQuery.nyroModalManual({
   // url: url,width:550,height:450,title:'Flag Posts'
//  });

	  var options = 'sameBox:true width:70% height:90% caption:' +
  '`Flag Posts`';
  parent.fb.start(url, options);
	
	
}
function loadeditquestion(url,title)
{
	
	
	//jQuery.nyroModalSettings({ title:'Flag Posts'});

	//jQuery.nyroModalManual({
   // url: url,width:550,height:450,title:'Flag Posts'
//  });

	  var options = 'sameBox:true width:90% height:90% caption:' +
  '`Edit Profile`';
  parent.fb.start(url, options);
	
	
}


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

function get_state(code){
    var url = spath+"question/ajax";

    jQuery.ajax({
        type: "GET",
        url: url,
        data: {
            'action': 1,
            'code' :code,
            'select':1
        },
        success: function(msg){
            jQuery('#chg_state').html(msg);

            if(setstate.length>1){

        //jQuery("#q_state option").each(function(){jQuery(this).text(escape(jQuery(this).text()));});
        //jQuery("#q_state option:contains('tamil nadu')").attr("selected","selected") ;
        //jQuery(this).text().toLowerCase()
        }
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
        data: {
            'action': 2,
            'code' :code,
            'select':1
        },
        success: function(msg){
            jQuery('#chg_city').html(msg);
        }
    });

}




 jQuery(document).ready(function () {
   jQuery(".innerbox li a").live('click', function(e) {

	  e.preventDefault();

           $('#qajax').load($(this).attr('href'), function(response, status, xhr) {
  if (status == "success") {
        reset_tabs();
    
  }else{
      var msg = "Sorry but there was an error: ";
    $("#qajax").html(msg + xhr.status + " " + xhr.statusText);
  }
});

return false;
});
    });

