



 jQuery(document).ready(function () {
    jQuery('.count-title a').click(function(e) {
  e.preventDefault();
e.stopPropagation();
        //$('#box1').css("background","#9f9");
        jQuery(".count-title a").css('color', '#000');
        jQuery(this).css('color', '#4170A0');
         jQuery('#heatmap').fadeOut('slow');
         var params="?width=320&height=190";
        jQuery('#cirmap').attr('src',jQuery(this).attr('href')+params);
         jQuery('#heatmap').fadeIn('slow');

    });
 });
 
 
 
$(document).ready(function(){

  $('.profile-close-icon').click(function() { alert("clicked for close");
    var request_path = Drupal.settings.hm_base_url;
	urls = request_path + '/profile_box_session';
	alert(urls);
	jQuery.ajax({
		type: "GET",
		url: urls,
		data: {
		
		},
		success: function(msg){
          alert(msg);
		}
	});
		
  });
  

});

function profile_box_session() {

	jQuery(document).ready(function(){
		
	

	})

}