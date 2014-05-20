// Fast integer load on home page
function fast_counter(id, value) {
  var el = $('#' + id);
  el.html(0);
  var steps = value < 10 ? 10 : ( value < 1000 ? 20 : 30 );
  var average = Math.ceil(value / steps);
  var timer = setInterval(function () {
    var random = Math.random() * 2 * average;
    random = Math.ceil(random);
    var value_current = parseInt(el.html());
    if (value - value_current > random) {
      el.html(value_current + random);
    } else {
      el.html(value);
      clearInterval(timer);
    }
  }, 100);
}

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

  setTimeout(function () {
    $('.fast_counter').each(function (i, e) {
      var id = $(e).attr('id').replace('fast_counter_', '');
      fast_counter(id, $(e).html());
    });
  }, 3000);

});