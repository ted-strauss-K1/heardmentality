



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

  $('.profile-close-icon').click(function(){
    var request_path = Drupal.settings.hm_base_url;
	alert(request_path);
  });
  

});

function profile_box_session() {

	/*jQuery(document).ready(function(){
		var urls = gSitePath+'savefollowing';
		var divid = '#record-'+fid;
		var follid = '#followname-'+fid;
		var followname = jQuery(follid).val();
		jQuery.ajax({
			type: "GET",
			url: urls,
			data: {
			   'delete':  fid
			},
			success: function(msg){
				jQuery(divid).remove();
				show_inotify("You now unfollowed from "+followname+"!");
			}
		});
	})
*/
}