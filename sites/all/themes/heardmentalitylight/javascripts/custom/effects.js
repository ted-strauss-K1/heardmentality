// Circles on home page
var circle = -1;
var circle_count = $('.circle-box').length;
function circle_state(i) {
  $('.circle-box p.hover').stop().fadeTo(200, 0);
  $('.circle-box #circle' + i + ' p.hover').stop().fadeTo(200, 1);
}
function circle_next() {
  circle++;
  circle = circle % circle_count;
  circle_state(circle);
}
var circle_timer = setInterval('circle_next()', 5000);
circle_state(circle_count);
$(document).ready(function () {
  $('.circle-box a').mouseenter(function () {
    clearTimeout(circle_timer);
    $(this).parents('.circle-wrapper').each(function () {
      circle = $(this).attr('id').replace('circle', '');
      circle = parseInt(circle);
    });
    circle_state(circle);
  }).mouseleave(function () {
    circle_state(circle_count);
    circle_timer = setInterval('circle_next()', 5000);
  });
//  $('.see, .vote-now, .share-now').each(function () {
//    var $span = $('> p.hover', this).css('opacity', 0);
//    $(this).hover(function () {
//      $p.stop().fadeTo(200, 1);
//
//    }, function () {
//      $p.stop().fadeTo(200, 0);
//    });
//  });
});

// Fixed sidebar
$(document).ready(function () {
  $(window).scroll(function () {
    var
      top = 20,
      scroll = $(window).scrollTop(),
      content_top = $('.twelve.columns').offset().top,
      sidebar = $('.sidebar_inner'),
      sidebar_top = sidebar.offset().top;
    var baseline = scroll + top - content_top;
    if (baseline <= 0) {
      sidebar.css('top', 0);
    }
    else {
      sidebar.css('top', baseline);
    }
  });
});
