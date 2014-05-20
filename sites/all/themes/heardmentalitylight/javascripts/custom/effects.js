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
});

// Fixed sidebar
$(document).ready(function () {
  $(window).scroll(function () {
    var
      top = 20,
      scroll = $(window).scrollTop(),
      content = $('.twelve.columns'),
      sidebar = $('.sidebar_inner');
    if (!sidebar || !content || !content.offset()) {
      return;
    }
    var baseline = scroll + top - content.offset().top;
    if (baseline <= 0) {
      sidebar.css('top', 0);
    }
    else {
      sidebar.css('top', baseline);
    }
  });
});

// Search Item Click
$(document).ready(function () {
  $('.search_item').live('click', function (e) {
    if ("DIV" == e.target.nodeName) {
      e.stopPropagation();
      e.preventDefault();

      location.href = $(this).find('h2 > a').attr('href');
    }
  });
});
