/**
 *
 */
$('form.issue-vote-form input[name=choices]').live('change', function () {
  var form = $(this).parents('.issue-vote-form');
  form.find('input[type=submit]').removeClass('not-changed');
});

/**
 *
 */
$('#suggest').live('click', function (e) {
  e.preventDefault();

  var input = $('input[name="suggest[suggest_answer]"]');
  input.val(input.val().replace(/(^\s+|\s+$)/g, ''));
  var form = input.parents('.issue-vote-form');

  // activated form
  if (form.hasClass('active')) {
    $.hrd.noty({
      type: 'error',
      text: Drupal.t('Multiple submissions are not allowed') + '. ' + Drupal.t('Wait for few seconds to add your suggestion')
    });
    return;
  }

  // empty
  if (!input.val()) {
    return;
  }

  // hide form
  input.parents('fieldset').slideUp(500);

  // update not-voted status
  form.removeClass('not-voted');
  $.hrd.noty({
    type: 'success',
    text: Drupal.t('Your suggestion was added') + '!'
  });

  // update the text
  var wrapper = $('.vote-result-empty');
  var label = wrapper.parent().find('.ch');
  var choice = wrapper.parent().find('input');
  wrapper.addClass('vote-result-new').removeClass('vote-result-empty');
  label.html(input.val());

  // check radios
  var vote = form.find('[name=vote]');
  if (-1 != vote.val()) {
    vote_ux(form, vote.val(), -1);
  }
  vote_ux_set(form, -1, 1);
  form.find('input[name=choices][value=-1]').prop('checked', true);

  // activate form
  voteform_freeze(form, true);

  $.ajax({
    type    : 'POST',
    dataType: 'json',
    url     : Drupal.settings.language_prefix + '/cpoll_vote/ajax',
    data    : {
      "nid"       : form.find('input[name=nid]').val(),
      "suggestion": input.val()
    },
    success : function (response) {
      if (!response.status) {
        $.hrd.noty({
          type: 'error',
          text: response.message
        });

        // show form
        input.parents('fieldset').slideDown(500);
        // rollback suggestion
        wrapper.addClass('vote-result-empty').removeClass('vote-result-new');
        label.html('');
        // values
        if (-1 != vote.val()) {
          vote_ux(form, vote.val(), 1);
        }
        vote_ux(form, -1, -1);

        // deactivate form
        voteform_freeze(form, false);

        return;
      }

      //
      $('input[name=choices][value="-1"]').val(response.chid);
      vote.val(response.chid);

      // update the form with server's data
      var results = response.result;
      for (var i in results) {
        vote_ux_set(form, i, results[i]['votes']);
      }
      vote_set_vote(form);

      // deactivate form
      voteform_freeze(form, false);

      //
      var body = $('body');
      body.trigger('cpoll_update');

    }
  });
});

$('#vote').live('click', function (e) {
  e.preventDefault();

  var form = $(this).parents('.issue-vote-form');

  // activated form
  if (form.hasClass('active')) {
    $.hrd.noty({
      type: 'error',
      text: Drupal.t('Multiple submissions are not allowed') + '. ' + Drupal.t('Wait for few seconds to change your vote')
    });
    return;
  }

  // validate selection
  var chid = form.find(':checked');
  var vote = form.find('[name=vote]');
  if (!chid || (chid.val() == vote.val()) || (!chid.val() && (-1 == vote.val()))) {
    return;
  }

  // counters
  vote_ux(form, vote.val(), -1);
  vote_ux(form, chid.val(), 1);

  // update not-voted status
  form.removeClass('not-voted');
  $.hrd.noty({
    type: 'success',
    text: Drupal.t('Your vote is accepted') + '!'
  });

  // activate form
  voteform_freeze(form, true);

  $.ajax({
    type    : 'POST',
    dataType: 'json',
    url     : Drupal.settings.language_prefix + '/cpoll_vote/ajax',
    data    : {
      "nid" : form.find('input[name=nid]').val(),
      "chid": chid.val()
    },
    success : function (response) {
      if (!response.status) {
        $.hrd.noty({
          type: 'error',
          text: response.message
        });

        // show form
        vote_ux(form, vote.val(), 1);
        vote_ux(form, chid.val(), -1);

        // deactivate form
        voteform_freeze(form, false);

        return;
      }

      //
      vote.val(response.chid);

      // update the form with server's data
      var results = response.result;
      for (var i in results) {
        vote_ux_set(form, i, results[i]['votes']);
      }
      vote_set_vote(form);

      // deactivate form
      voteform_freeze(form, false);

      //
      var body = $('body');
      body.trigger('cpoll_update', [false]);

    }
  });
});

/**
 *
 * @param form
 * @param status
 */
function voteform_freeze(form, status) {
  var radios = form.find('input[type=radio]');
  if (status) {
    form.addClass('active');
    radios.attr('disabled', 'disabled');
  }
  else {
    radios.removeAttr('disabled');
    form.removeClass('active');
  }
}

/**
 *
 * @param form
 * @param value
 * @param delta
 */
function vote_ux(form, value, delta) {
  var radio = form.find('input[name=choices][value=' + value + ']');
  radio.prop('checked', -1 != delta);
  var count = radio.parents('.radio_wrapper').find('.teaser_count_vote span');
  count.html(delta + parseInt(count.html()));
}

/**
 *
 * @param form
 * @param value
 * @param delta
 */
function vote_ux_set(form, value, votes) {
  form.find('input[name=choices][value=' + value + ']').parents('.radio_wrapper').find('.teaser_count_vote span').html(votes);
}

/**
 *
 * @param form
 */
function vote_set_vote(form) {
  form.find('input#vote[type=submit]').addClass('not-changed').val(Drupal.t('Change vote'));
}
