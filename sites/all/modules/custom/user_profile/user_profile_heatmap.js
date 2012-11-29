$(document).ready(function () {

  $('.count-title a').live('click', function (e) {
    e.preventDefault();
    e.stopPropagation();

    var el = $(this);
    $(".count-title a").css('color', '#000');
    el.css('color', '#4170A0');
    $('#visualization').fadeOut(500, function () {
      Drupal.settings.heatmap.current = el.attr('name');
      init_heatmap();
      $('#visualization').fadeIn(1000);
    });
  });

});


/**Rallydev 495**/
$(document).ready(function () {

  $('.profile-close-icon').click(function () {
    $('.profile-status-toggle').remove();
    // do not show in this session again
    $.cookie('profile_status', '0');
  });

  /****Rallydev:529****/
  if ($.trim($('p.double').text()) == "") {
    $('p.double').hide();
    $('#button.hide-message').css('margin-top', '3px');
  }
  /************/
});
