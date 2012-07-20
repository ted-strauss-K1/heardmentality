/**
 * Throbber plugin
 */
(function( $ ) {

  $.fn.throbberStart = function(options) {
    var settings = $.extend(true, {
      'text': Drupal.t('Loading, please wait...'),
      'textWidth': '80%',
      'displayAnimation': true
    }, options);

    var indicator = $('<div></div>')
                      .addClass('indicator' + (settings['displayAnimation'] ? ' animation' : ''))
                      .text(settings.text)
                      .width(settings.textWidth),
        throbber = $('<div></div>')
                    .attr('id', 'throbber-ajax-wrapper')
                    .append(indicator);

    $(this).css({'position': 'relative'}).append(throbber);
    var minHeight = parseInt(throbber.outerHeight()) - (parseInt($(this).css('padding-top')) + parseInt($(this).css('padding-bottom')));
    $(this).css({'min-height': minHeight});
  }

  $.fn.throbberStop = function() {
    $(this).css({'position': 'initial'});
    $('#throbber-ajax-wrapper', this).remove();
  }

})( jQuery );