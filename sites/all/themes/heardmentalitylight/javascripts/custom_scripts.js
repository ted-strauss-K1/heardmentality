$(document).ready(function () {

  // Initialization jscrollpane

  // Filter show only

  $('#debate_list_area .show_only span.button').click(function () {

    var filter = $(this).parent('.show_only').find('.popup');

    if (filter.hasClass('hidden')) {
      filter.removeClass('hidden').addClass('visible');
      $(this).addClass('active');
    }
    else {
      filter.removeClass('visible').addClass('hidden');
      $(this).removeClass('active');
    }

  });

  $('html').live('click',
    function (e) {
      if (e.target.id != 'filter_content' && e.target.id != 'show_filter') {
        var filter_external = $('#debate_list_area .show_only .popup');
        if (filter_external.hasClass('visible')) {
          filter_external.removeClass('visible').addClass('hidden');
          $('#debate_list_area .show_only span.button').removeClass('active');
        }
      }
    });

});

Drupal.behaviors.fix_circle = function (context) {

  if ($.browser.mozilla) {
    $('span.small_pos, #debate_list_area .arg p.position-plus strong').addClass('fixes');
    $('#debate_list_area li.one_reply span.negative, #debate_list_area li.one_reply span.positive').addClass('fixes');
  }
  if ($.browser.msie && $.browser.version > '8.0') {
    $('span.small_pos, #debate_list_area .arg p.position-plus strong').addClass('fixes');
    $('#debate_list_area li.one_reply span.negative, #debate_list_area li.one_reply span.positive').addClass('fixes');
  }
  if ($.browser.opera) {
    $('#debate_list_area li.one_reply span.negative, #debate_list_area li.one_reply span.positive').addClass('fixes');
  }

  // Registration tooltip
  $('#user-register span.password-confirm').wrapInner('<div class="inner_confirm" />');

  $('html').live('click',
    function (e) {
      if (e.target.id != 'edit-pass-pass1' && e.target.id != 'edit-pass-pass2') {
        $('#user-register .password-strength, #user-register span.password-confirm').css('visibility', 'hidden');
      }
    });
};


