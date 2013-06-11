$('#answer-add').live('click', function () {
  $(this).parents('.issue-vote-form').find('input[name=action]').val('suggest')
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

  // UX fake update - we'll check the results later and properly update on form
  var vote_r = form.find('input[name=vote_regular]').val();
  var vote_s = form.find('input[name=vote_suggested]').val();
  var radio = form.find('input[type=radio]:checked');
  var vote = radio.val();
  var vote_type = 'choice' == radio.attr('name') ? 'r' : 's';
  var vote_changed = false;
  if ('r' == vote_type) {
    if (vote != vote_r) {
      vote_changed = true;
      form.find('input[name=vote_regular]').val(vote);
      form.find('input[name=vote_suggested]').val(-1);
      var count = $('.vote-result-r-'+vote);
      count.html(parseInt(count.html()) + 1);
    }
  } else {
    if (vote != vote_s) {
      vote_changed = true;
      form.find('input[name=vote_regular]').val(-1);
      form.find('input[name=vote_suggested]').val(vote);
      var count = $('.vote-result-s-'+vote);
      count.html(parseInt(count.html()) + 1);
    }
  }
  if (vote_changed) {
    if (-1 != vote_r) {
      $('.vote-result-r-'+vote_r).html(-1 + parseInt($('.vote-result-r-'+vote_r).html()));
    }
    if (-1 != vote_s) {
      $('.vote-result-s-'+vote_s).html(-1 + parseInt($('.vote-result-s-'+vote_s).html()));
    }
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
//          return false;
        }
//        $.hrd.noty({
//          type:'success',
//          text:response.message
//        });

        // update the form with server's data
        var results = response.content.choice_r;
        for (var i in results) {
          $('.vote-result-r-'+i).html(results[i]['chvotes'])
        }
        var results = response.content.choice_s;
        for (var i in results) {
          $('.vote-result-s-'+i).html(results[i])
        }
        form.find('input[name=vote_regular]').val(response.content.vote_r);
        form.find('input[name=vote_suggested]').val(response.content.vote_s);

        // update charts
        $('.notvoted li').slideDown(500);
        $('.no_show').hide();
        charts_update();
        //
        Drupal.attachBehaviors();
      }
    });

  }

  return false;
});

$('#answer-add').live('click', function (e) {
  e.preventDefault();
  var form = $('.issue-vote-form');

  // now we make the regular call
  $.ajax({
    type:'POST',
    dataType:'json',
    url:/*'/'+Drupal.settings.language+*/'/issue/ajax',
    data: form.serialize(),
    success:function (response) {
      if (!response.status) {
        $.hrd.noty({
          type:'error',
          text:response.message
        });
          return false;
      }
      $.hrd.noty({
        type:'success',
        text:response.message
      });
      form.parents('.voteform').html(response.content);
    }
  });
});


$('body').on('test', function() {
  alert('x');
});

//$.event.trigger({
//  type: "newMessage",
//  message: "Hello World!",
//  time: new Date()
//});