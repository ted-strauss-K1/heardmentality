/*
 * Override ahah.success
 *
 * @warning -- This is very important. Do not modify.
 *
 * @see http://drupal.org/node/1005598
 */
$(function () {
  //override ahah success to fire a custom javascript function, if it's in the response object
  Drupal.ahah.prototype.success = function (response, status) {
    var customCallback = function () {
      if (!!response.js) { //fire custom javascript callback after AHAH has done its thing
        eval(response.js['func'] + '(' + (!!response.js['params'] ? response.js['params'] : '') + ');');
      }
    };
    var wrapper = $(this.wrapper);
    var form = $(this.element).parents('form');
    var new_content = $('<div></div>').html(response.data);
    form.attr('action', this.form_action);
    this.form_target ? form.attr('target', this.form_target) : form.removeAttr('target');
    this.form_encattr ? form.attr('target', this.form_encattr) : form.removeAttr('encattr');
    if (this.progress.element) {
      $(this.progress.element).remove();
    }
    if (this.progress.object) {
      this.progress.object.stopMonitoring();
    }
    $(this.element).removeClass('progress-disabled').attr('disabled', false);
    // Drupal.freezeHeight();
    if (this.method == 'replace') {
      wrapper.empty().append(new_content);
    }
    else {
      wrapper[this.method](new_content);
    }
    if (this.showEffect != 'show') {
      new_content.hide();
    }
    if (($.browser.safari && $("tr.ahah-new-content", new_content).size() > 0)) {
      new_content.show();
      customCallback();
    }
    else if ($('.ahah-new-content', new_content).size() > 0) {
      $('.ahah-new-content', new_content).hide();
      new_content.show();
      $(".ahah-new-content", new_content)[this.showEffect](this.showSpeed, customCallback);
    }
    else if (this.showEffect != 'show') {
      new_content[this.showEffect](this.showSpeed, customCallback);
    }
    if (new_content.parents('html').length > 0) {
      Drupal.attachBehaviors(new_content);
    }
//Drupal.unfreezeHeight();
  };
});

/**
 * This function runs every time we exceed the limit of possible answers
 */
function cpoll_create_ahah_error() {
  $.hrd.noty({
    'type':'error',
    'text':Drupal.t('Maximum fields exceeded')
  });
}

/**
 * Form JS validation
 */
var maxlength = 140;
$('#cpoll-create-form').live('submit', function (e) {
  var q = $("#q_quest");
  var errors = [];
  if (q.val().length > maxlength) {
    errors.push(Drupal.t('The question is too long'));
  }
  if (2 > $('#poll-choices input').filter(function() { return $(this).val(); }).length) {
    errors.push(Drupal.t('Enter more that two elements'));
  }
  if (20 > q.val().length) {
    errors.push(Drupal.t('The question is too short'));
  }
  if (errors.length) {
    e.preventDefault();

    for (var i in errors) {
      $.hrd.noty({
        'type':'error',
        'text':errors[i]
      });
    }
  }
});

/**
 * Counter
 */
$('#q_quest').live('keyup', function() {
  var q = $("#q_quest");
  var c = $('#q_counter');
  var count = maxlength - q.val().length;
  c.html(count);
  if (count <= 0 || count > 120) {
    c.addClass('over_limit');
  } else {
    c.removeClass('over_limit');
  }
});
