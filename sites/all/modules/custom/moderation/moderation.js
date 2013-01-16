$(document).ready(function () {
  $('.mod-wrapper h2').live('click', function () {
    var e1 = $(this);
    var e2 = $(this).parents('.mod-wrapper').find('.mod-buttons');
    if (e1.hasClass('mod-open')) {
      e2.slideUp(400);
      e1.removeClass('mod-open');
    } else {
      e2.slideDown(400);
      e1.addClass('mod-open');
    }
  });

  $('a.permission').live('click', function (e) {
    e.preventDefault();
    var el = $(this);
    $.ajax({
      type:'POST',
      dataType:'json',
      url:'/' + el.attr('name'),
      success:function (response) {


        el.toggleClass('remove');
      }
    });
  });
});


