/**
 * jScrollPane for home page
 */
$(function()
{
  var pane = $('.container .nine .grey-box .uactivity');
  if ($.browser.mobile == false) {
    var settings = {
      scrollbarWidth:20,
      scrollbarMargin:0,
      showArrows:true
    };

    pane.jScrollPane(settings);
    var api = pane.data('jsp');

    $(window).resize(function () {
      if (api) {
        api.reinitialise();
      }
    });
  } else {
    pane.addClass('mobile');
  }
});