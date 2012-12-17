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