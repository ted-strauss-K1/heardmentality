



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


/**Rallydev 495**/
$(document).ready(function(){

  $('.profile-close-icon').click(function() {
    var request_path = Drupal.settings.base_url;
    var urls = request_path + '/profile/profile_box_session';
    jQuery.ajax({
      type: "GET",
      url: urls,
      data: {},
      success: function(msg){
        $('.profile-status-toggle').remove();
        // do not show in this session again
        $.cookie('profile_status', '0');
      }
    });
  });

  /****Rallydev:529****/
  if($.trim($('p.double').text()) == "") {
    $('p.double').hide();
    $('#button.hide-message').css('margin-top','3px');
  }
  /************/
});
