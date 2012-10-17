// Circles on home page
var circle = -1;
var circle_count = $('.circle-box').length;
function circle_state(i) {
  $('.circle-box span.hover').stop().fadeTo(200, 0);
  $('.circle-box #circle'+i+' span.hover').stop().fadeTo(200, 1);
}
function circle_next() {
  circle++;
  circle = circle % circle_count;
  circle_state(circle);
}
var circle_timer = setInterval('circle_next()', 5000);
circle_state(circle_count);
$(document).ready(function() {
  $('.circle-box a').mouseenter(function(){
    clearTimeout(circle_timer);
    $(this).parents('.circle-wrapper').each(function(){
      circle = $(this).attr('id').replace('circle','');
      circle = parseInt(circle);
    });
    circle_state(circle);
  }).mouseleave(function(){
    circle_state(circle_count);
    circle_timer = setInterval('circle_next()', 5000);
  });
//  $('.see, .vote-now, .share-now').each(function () {
//    var $span = $('> span.hover', this).css('opacity', 0);
//    $(this).hover(function () {
//      $span.stop().fadeTo(200, 1);
//
//    }, function () {
//      $span.stop().fadeTo(200, 0);
//    });
//  });
});

// Fast integer load on home page
function fast_counter(id, value) {
  var el = $('#'+id);
  el.html(0);
  var steps = value < 10 ? 10 : ( value < 1000 ? 20 : 30 );
  var average = Math.ceil(value/steps);
  var timer = setInterval(function(){
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
$(document).ready(function(){
  setTimeout(function(){
    $('.fast_counter').each(function(i,e){
      var id = $(e).attr('id').replace('fast_counter_', '');
      fast_counter(id, $(e).html());
    });
  }, 3000);
});