/**
 * click the percentage
 */
$('.choice-radio-title, .choice-radio-title *').live('click', function (e) {
  var $$ = $(this);
  if ($$.hasClass('choice-radio-title')) {
    e.stopPropagation();
    var input = $$.find('input');
    if (!input.is(':disabled')) {
      input.prop('checked', true).trigger('change');
    }
  }
});

/**
 * Track vote/choice submission
 */
$('#vote').live('click', function (e) {
  e.preventDefault();

  var form = $(this).parents('.issue-vote-form');

  voteform_submit(form, false);
});

/**
 * Track choice submission
 */
$('#suggest').live('click', function (e) {
  e.preventDefault();

  var form = $(this).parents('.issue-vote-form');

  voteform_submit(form, true);
});

/**
 * Function that executes the vote/choice submission
 *
 * @param form
 * @param suggestion
 */
function voteform_submit(form, suggestion) {
  // activated form
  if (voteform_is_active(form)) {
    var message = suggestion ?
      Drupal.t('Multiple submissions are not allowed') + '. ' + Drupal.t('Wait for few seconds to add your suggestion') :
      Drupal.t('Multiple submissions are not allowed') + '. ' + Drupal.t('Wait for few seconds to change your vote');
    $.hrd.noty({
      type: 'error',
      text: message
    });
    return false;
  }

  // validate
  if (!voteform_validate(form, suggestion)) {
    return false;
  }

  // pre-execution
  voteform_preexecute(form, suggestion);

  // activate form
  voteform_activate(form);

  // animate vote results
  voteform_animate(form);

  // send data to server
  voteform_request(form, suggestion);
}

/**
 * @param form
 */
function voteform_activate(form) {
  form.addClass('active');
  form.find('input').attr('disabled', 'disabled');
}

/**
 * @param form
 */
function voteform_deactivate(form) {
  form.find('input').removeAttr('disabled');
  form.removeClass('active');
}

/**
 * @param form
 * @returns {*}
 */
function voteform_is_active(form) {
  return form.hasClass('active');
}

/**
 * @param form
 * @param suggestion
 * @returns {boolean}
 */
function voteform_validate(form, suggestion) {
  if (suggestion) {
    var input = form.find('input[name="suggest[suggest_answer]"]');
    input.val(input.val().replace(/(^\s+|\s+$)/g, ''));
    if (!input.val()) {
      $.hrd.noty({
        type: 'error',
        text: Drupal.t('The choice submitted cannot be empty') + '. '
      });
      return false;
    }
  }
  else {
    var chid = form.find(':checked');
    var vote = form.find('[name=vote]');
    if (!chid || (!chid.val() && (-1 == vote.val()))) {
      $.hrd.noty({
        type: 'error',
        text: Drupal.t('The choice submitted cannot be empty') + '. '
      });
      return false;
    }
    if (chid.val() == vote.val()) {
      $.hrd.noty({
        type: 'error',
        text: Drupal.t('The choice was already submitted') + '. '
      });
      return false;
    }
  }

  return true;
}

/**
 * @param form
 * @param suggestion
 */
function voteform_preexecute(form, suggestion) {
  if (suggestion) {
    // hide the input
    var input = form.find('input[name="suggest[suggest_answer]"]');
    input.parents('fieldset').slideUp(500);

    // show the new choice
    form.find('.choice-empty')
      .addClass('choice-new')
      .removeClass('choice-empty')
      .find('.ch')
      .html(input.val());

    form.find('.choice-new input').prop('checked', true);
  }

  // message
  var message = suggestion ?
    Drupal.t('Your suggestion was added') + '!' :
    Drupal.t('Your vote is accepted') + '!';
  $.hrd.noty({
    type: 'success',
    text: message
  });

  //
  if (form.hasClass('not-voted')) {
    voteform_animate_reset(form);
  }

  //
  form.removeClass('not-voted');

  // update counters
  var vote = form.find('[name=vote]');
  if (-1 != vote.val()) {
    voteform_count(form, vote.val(), -1);
  }
  var chid = form.find(':checked');
  voteform_count(form, chid.val(), 1);
}

/**
 * @param form
 */
function voteform_animate_reset(form) {
  form.find('.choice-radio-percentage').width(0);
}

/**
 * @param form
 * @param value
 * @param delta
 */
function voteform_count(form, value, delta) {
  var count = form.find('.choice-' + value + ' .choice-radio-votes span');
  count.html(delta + parseInt(count.html()));
}

/**
 * @param form
 */
function voteform_animate(form) {
  var votecount = 0;
  form.find('.choice-radio-votes span').each(function (i, e) {
    votecount += parseInt($(e).html());
  });

  form.find('.choice-radio-wrapper').each(function (i, e) {
    var count = parseInt($(e).find('.choice-radio-votes span').html());
    $(e).find('.choice-radio-percentage').animate({
      'width': Math.round(100 * count / votecount) + '%'
    }, {
      queue   : false,
      duration: 500
    });
  });
}

/**
 * @param form
 */
function voteform_request(form, suggestion) {
  var dataset = {'nid': form.find('input[name=nid]').val()};
  if (suggestion) {
    var input = form.find('input[name="suggest[suggest_answer]"]');
    dataset['suggestion'] = input.val();
  }
  else {
    var chid = form.find(':checked');
    dataset['chid'] = chid.val();
  }

  $.ajax({
    type    : 'POST',
    dataType: 'json',
    url     : Drupal.settings.language_prefix + '/cpoll_vote/ajax',
    data    : dataset,
    success : function (response) {
      if (!response.status) {
        voteform_error(form, suggestion, response);
        return false;
      }

      voteform_postexecute(form, suggestion, response);
    }
  });
}

/**
 * @param form
 * @param suggestion
 * @param response
 */
function voteform_error(form, suggestion, response) {
  $.hrd.noty({
    type: 'error',
    text: response.message
  });

  if (suggestion) {
    // show the input
    var input = $('input[name="suggest[suggest_answer]"]');
    input.parents('fieldset').slideDown(500);

    // uncheck
    form.find('.choice-new input').prop('checked', false);

    // show the new choice
    form.find('.choice-new')
      .addClass('choice-empty')
      .removeClass('choice-new')
      .find('.ch')
      .html('');

    // decrease count
    voteform_count(form, -1, -1);
  }
  else {
    // decrease count
    var chid = form.find(':checked');
    voteform_count(form, chid.val(), -1);
  }

  // increase count
  var vote = form.find('[name=vote]');
  if (-1 != vote.val()) {
    voteform_count(form, vote.val(), 1);
  }
  else {
    form.addClass('not-voted');
  }

  // check vote
  if (-1 != vote.val()) {
    form.find('.choice-' + vote.val() + ' input').prop('checked', true).trigger('change');
  }

  // deactivate form
  voteform_deactivate(form);

  // animate vote results
  voteform_animate(form);
}

/**
 * @param form
 * @param suggestion
 * @param response
 */
function voteform_postexecute(form, suggestion, response) {
  if (suggestion) {
    // update chid
    form.find('input[name=choices][value="-1"]').val(response.chid);

    // change the classes
    form.find('.choice-new').removeClass('choice-new').addClass('choice-' + response.chid);
  }

  // save vote chid
  form.find('[name=vote]').val(response.chid);

  // current vote
  form.find('.choice-radio-wrapper').removeClass('current-vote');
  form.find('.choice-' + response.chid).addClass('current-vote');

  // update the form with server's data
  var results = response.result;
  for (var i in results) {
    voteform_count_set(form, i, results[i]['votes'])
  }

  // change the text
  form.find('input#vote[type=submit]').addClass('not-changed').val(Drupal.t('Change vote'));

  // deactivate form
  voteform_deactivate(form);

  // animate vote results
  voteform_animate(form);

  // index
  $.ajax({
    type    : 'POST',
    dataType: 'json',
    url     : '/issues/index',
    data    : {},
    success : function (response) {
      //
    }
  });

  // trigger update
  $('body').trigger('cpoll_update', [false]);
}

/**
 *
 * @param form
 * @param chid
 * @param value
 */
function voteform_count_set(form, chid, value) {
  form.find('.choice-' + chid + ' .choice-radio-votes span').html(value);
}

/**
 *
 */
$('form.issue-vote-form input[name=choices]').live('change', function () {
  var form = $(this).parents('.issue-vote-form');
  if ($(this).parents('.choice-radio-wrapper').hasClass('current-vote')) {
    form.find('input[type=submit]').addClass('not-changed');
  } else {
    form.find('input[type=submit]').removeClass('not-changed');
  }
});
