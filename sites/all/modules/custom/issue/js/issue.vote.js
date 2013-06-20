$('#answer-add').live('click', function () {
//  $(this).parents('.issue-vote-form').find('input[name=action]').val('suggest')
});
$('#vote-add, #vote-change').live('click', function () {
  $(this).parents('.issue-vote-form').find('input[name=action]').val('vote')
});

function choices(s1, s2) {
  $(s1).live('change', function () {
    $(s1).parents('div.form-item').removeClass('staygreen');
    $(s1 + ':checked').parents('div.form-item').addClass('staygreen');
    $(s2).each(function (i, e) {
      $(e).removeAttr("checked")
      $(e).parents('div.form-item').removeClass('staygreen');
    });
  });
  $(s1 + ':checked').each(function (i, e) {
    $(e).parents('div.form-item').addClass('staygreen');
  });
}

$(document).ready(function () {
  /*
   * Regular and Suggested choices
   */
  var s1 = '.choices.regular input[type="radio"]';
  var s2 = '.choices.suggested input[type="radio"]';
  choices(s1, s2);
  choices(s2, s1);
});

$('.issue-vote-form').live('submit', function (e) {
  e.preventDefault();
  var form = $(this);

  // if the form is active - skip the submission
  if (form.hasClass('active')) {
    $.hrd.noty({
      type:'error',
      text:'Multiple submissions are not allowed. Wait for few seconds to change your vote' // todo translate
    });
    return;
  }

  // current state
  var vote_r = form.find('input[name=vote_regular]').val();
  var vote_s = form.find('input[name=vote_suggested]').val();

  //
  var radio = form.find('input[type=radio]:checked');
  var vote = radio.val();
  var vote_type = 'choice' == radio.attr('name') ? 'r' : 's';
  if (!vote) {
    return;
  }

  var vote_changed = false;
  if ('r' == vote_type) {
    if (vote != vote_r) {
      vote_changed = true;
      form.find('input[name=vote_regular]').val(vote);
      form.find('input[name=vote_suggested]').val(-1);
      var count = form.find('.vote-result-r-'+vote);
      count.html(parseInt(count.html()) + 1);
    }
  } else {
    if (vote != vote_s) {
      vote_changed = true;
      form.find('input[name=vote_regular]').val(-1);
      form.find('input[name=vote_suggested]').val(vote);
      var count = form.find('.vote-result-s-'+vote);
      count.html(parseInt(count.html()) + 1);
    }
  }

  if (vote_changed) {
    // activate form
    form.addClass('active');
    // decrease count
    var r = form.find('.vote-result-r-'+vote_r);
    r.html(-1 + parseInt(r.html()));
    var s = form.find('.vote-result-s-'+vote_s);
    s.html(-1 + parseInt(s.html()));
    // voted
    form.removeClass('not-voted');
    $.hrd.noty({
      type:'success',
      text: 'Your vote was changed!' // todo translate
    });

    // now we make the regular call
    $.ajax({
      type:'POST',
      dataType:'json',
      url:/*'/'+Drupal.settings.language+*/'/issue/ajax',
      data: {
        "nid"     : form.find('input[name=nid]').val(),
        "action"  : form.find('input[name=action]').val(),
        "vote_regular"    : vote_r,
        "vote_suggested"  : vote_s,
        "vote" : vote,
        "vote_type" : vote_type
      },
      success:function (response) {
        if (!response.status) {
          $.hrd.noty({
            type:'error',
            text:response.message
          });
        }

        // update the form with server's data
        var results = response.content.choice_r;
        for (var i in results) {
          form.find('.vote-result-r-'+i).html(results[i]['chvotes'])
        }
        var results = response.content.choice_s;
        for (var i in results) {
          form.find('.vote-result-s-'+i).html(results[i])
        }
        form.find('input[name=vote_regular]').val(response.content.vote_r);
        form.find('input[name=vote_suggested]').val(response.content.vote_s);

        // update charts
        $('.notvoted li').slideDown(500);
        $('.no_show').hide();
        if (typeof charts_update == 'function') charts_update();
        //
        Drupal.attachBehaviors();

        form.removeClass('active');
      }
    });
  }

  return;
});

$('#answer-add').live('click', function (e) {
  e.preventDefault();
  var form = $('.issue-vote-form');

  // if the form is active - skip the submission
  if (form.hasClass('active')) {
    $.hrd.noty({
      type:'error',
      text:'Multiple submissions are not allowed. Wait for few seconds to submit your answer' // todo translate
    });
    return;
  }

  var answer = form.find('input[name="suggest[suggest_answer]"]').val();
  if ('' == answer) {
    return;
  }

  form.find('input[name=action]').val('suggest');

  // current state
  var vote_r = form.find('input[name=vote_regular]').val();
  var vote_s = form.find('input[name=vote_suggested]').val();

  // empty holder
  var suggest = $('.teaser-result-s-empty');

  // Fake UX submission acceptance
  form.find('input[type=radio]').prop('checked', false);
  suggest.find('input[type=radio]').prop('checked', true);
  suggest.addClass('teaser-result-s-new').removeClass('teaser-result-s-empty');
  form.find('input[value=0][name="suggest[suggest_choice]"]').prop('checked', true);
  suggest.siblings().find('.ch').html(answer);

  form.removeClass('not-voted');
  $('.nsa-wrapper').slideUp(500);

  $.hrd.noty({
    type:'success',
    text:'Your suggestion was successfully added' // todo translate
  });
  // now we make the regular call
  $.ajax({
    type:'POST',
    dataType:'json',
    url:/*'/'+Drupal.settings.language+*/'/issue/ajax',
    data: form.serialize(),
    success:function (response) {
      form.removeClass('active');

      if (!response.status) {
        $.hrd.noty({
          type:'error',
          text:response.message
        });

        // rollback
        suggest.removeClass('teaser-result-s-new').addClass('teaser-result-s-empty');
        $('.nsa-wrapper').slideDown(500);
        form.addClass('not-voted');
        form.find('input[value='+vote_r+'][name=choice]').prop('checked', true);
        form.find('input[value='+vote_s+'][name="suggest[suggest_choice]"]').prop('checked', true);

        return false;
      }

      // update the form with server's data
      var chid = response.chid;
      suggest.removeClass('teaser-result-s-new')
        .find('span').removeClass('vote-result-s-0').addClass('vote-result-s-'+chid);
      suggest.siblings().find('input[type=radio]').val(chid);
      form.find('input[name=vote_regular]').val(-1);
      form.find('input[name=vote_suggested]').val(chid);
    }
  });


  return;
});


$('body').on('test', function() {
  alert('x');
});

//$.event.trigger({
//  type: "newMessage",
//  message: "Hello World!",
//  time: new Date()
//});