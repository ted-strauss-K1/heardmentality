
Drupal.apachesolr_ajax = {};

if (Drupal.settings.apachesolr_ajax) {
  var blocks  = Drupal.settings.apachesolr_ajax.blocks;
  var content = Drupal.settings.apachesolr_ajax.content;
  var regions = Drupal.settings.apachesolr_ajax.regions;
  var spinner = Drupal.settings.apachesolr_ajax.spinner;
  var target  = Drupal.settings.apachesolr_ajax.target;

  Drupal.apachesolr_ajax.url_to_state = function (url) {
    return url.replace(new RegExp('^.*' + Drupal.settings.basePath + 'search/apachesolr_[a-z_]+/?'), '');
  };

  Drupal.apachesolr_ajax.request_callback = function (state) {
    if (spinner && content) {
      $(content).html('<div id="apachesolr-ajax-spinner-container"><img src="' + spinner + '" class="apachesolr-ajax-spinner" /></div>');
    }
    if (target) { // taken from views/js/ajax_view.js
      // Scroll to the top of the view. This will allow users
      // to browse newly loaded content after e.g. clicking a pager
      // link.
      var offset = $(target).offset();
      // We can't guarantee that the scrollable object should be
      // the body, as the view could be embedded in something
      // more complex such as a modal popup. Recurse up the DOM
      // and scroll the first element that has a non-zero top.
      var scrollTarget = target;
      while ($(scrollTarget).scrollTop() == 0 && $(scrollTarget).parent()) {
        scrollTarget = $(scrollTarget).parent()
      }
      // Only scroll upward
      if (offset.top - 10 < $(scrollTarget).scrollTop()) {
        $(scrollTarget).animate({scrollTop: (offset.top - 10)}, 500);
      }
    }
    $.post(Drupal.settings.basePath + 'search/apachesolr_ajax/' + state, { js: 1 }, Drupal.apachesolr_ajax.response_callback, 'json');
  };

  Drupal.apachesolr_ajax.response_callback = function (data) {
    for (var setting in data.settings) {
      Drupal.settings[setting] = data.settings[setting];
    }

    var list = [];

    // Schedule items for removal to reduce page jumpiness.
    if (blocks) {
      for (var block in blocks) {
        list.push($(blocks[block]));
      }
    }
    for (var region in data.regions) {
      if (region == 'apachesolr_ajax') {
        if (content) {
          var elements = $(data.regions[region]);
          Drupal.attachBehaviors(elements.appendTo($(content).empty()));
        }
      }
      else {
        for (var block in data.regions[region]) {
          if (regions[region] && blocks[block]) {
            var elements = $(data.regions[region][block]);
            Drupal.attachBehaviors(elements.appendTo(regions[region]));
          }
        }
      }
    }
    for (var i = 0, l = list.length; i < l; i++) {
      list[i].remove();
    }
  };

  Drupal.apachesolr_ajax.navigate = function (url) {
    var state = Drupal.apachesolr_ajax.url_to_state(url) || '?'; // state cannot be empty.
    try {
      YAHOO.util.History.navigate('q', state);
    }
    catch (e) {
      Drupal.apachesolr_ajax.request_callback(state);
    }
    return false;
  };

  Drupal.apachesolr_ajax.add_handlers = function (selector, context) {
    $(selector + ' a[href*=' + Drupal.settings.basePath + 'search/apachesolr_]:not(.apachesolr-ajax-processed)', context)
      .addClass('apachesolr-ajax-processed')
      .click(function () {
        return Drupal.apachesolr_ajax.navigate($(this).attr('href'));
      });

    $(selector + ' form[action*=' + Drupal.settings.basePath + 'search/apachesolr_]:not(.apachesolr-ajax-processed)', context)
      .addClass('apachesolr-ajax-processed')
      .submit(function () {
        return Drupal.apachesolr_ajax.navigate($('#edit-keys').val()); // @todo Add support for retain-filters.
      });
  };

  // Insert click handlers to navigate via javascript
  Drupal.behaviors.apachesolrAjax = function(context) {
    if (content) {
      Drupal.apachesolr_ajax.add_handlers(content, $(context).parent().parent());
    }
    if (blocks) {
      for (var i in blocks) {
         Drupal.apachesolr_ajax.add_handlers(blocks[i], $(context).parent());
      }
    }
  };
}

$(function () {
  var initialState = YAHOO.util.History.getBookmarkedState('q') || Drupal.apachesolr_ajax.url_to_state(window.location.href);
  YAHOO.util.History.register('q', initialState, Drupal.apachesolr_ajax.request_callback);

  YAHOO.util.History.onReady(function () {
    var currentState = YAHOO.util.History.getCurrentState('q');
    Drupal.apachesolr_ajax.request_callback(currentState);
  });

  try {
    YAHOO.util.History.initialize('yui-history-field', 'yui-history-iframe');
  }
  catch (e) {
    Drupal.apachesolr_ajax.request_callback(initialState);
  }
});

if (Drupal.apachesolr) { // taken from apachesolr.js
  if (Drupal.apachesolr.addCheckbox) {
    Drupal.apachesolr.addCheckbox = function() {
      // Put href in context scope to be visible in the anonymous function.
      var href = $(this).attr('href');
      $(this).before($('<input type="checkbox" />')
        .attr('class', 'facet-checkbox')
        .click(function(){
          apachesolr_ajax_navigate(href);
        })
      );
    }
  }

  if (Drupal.apachesolr.makeCheckbox) { // taken from apachesolr.js
    Drupal.apachesolr.makeCheckbox = function() {
      // Create a checked checkbox.
      var checkbox = $('<input type="checkbox" />')
        .attr('class', 'facet-checkbox')
        .attr('checked', true);
      // Put href in context scope to be visible in the anonymous function.
      var href = $(this).attr('href');
      checkbox.click(function(){
        apachesolr_ajax_navigate(href);
      });
      // Add the checkbox, hide the link.
      $(this).before(checkbox).hide();
    }
  }
}
