$('.issue-vote-form').live('submit', function (e) {
  e.preventDefault();
  var form = $(this);
  $.ajax({
    type:'POST',
    dataType:'json',
    url:/*'/'+Drupal.settings.language+*/'/issue/ajax',
    data:form.serialize(),
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
      //
      Drupal.attachBehaviors();
    }
  });
  return false;
});

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

function toggle_resources() {
  if ($('#inc_check').attr('checked')) {
    $('.resources').show();
  } else {
    $('.resources').hide();
  }
}

$(document).ready(function () {
  /*
   * Regular and Suggested choices
   */
  var s1 = '.choices.regular input[type="radio"]';
  var s2 = '.choices.suggested input[type="radio"]';
  choices(s1, s2);
  choices(s2, s1);

  /*
   * Toggle resources
   */
  $('#inc_check').change(function () {
    toggle_resources();
  });

});

/**
 *
 */
$('a.permalink').live('click', function (e) {
  e.preventDefault();
  var link = window.location.href.replace(/#.*/, '') + '#' + $(this).parents('.one-forum').attr('id');
  $.hrd.noty({
    'layout':'center',
    'type':'alert',
    'text':'<a href="' + link + '">' + link + '</a>',
    'modal':true,
    'timeout':false,
    'closeWith':['button']
  });
});

$('#shareDiv-reaction0, #shareDiv-reaction1, #shareDiv-reaction2, #shareDiv-reaction3').live('click', function () {
  $.ajax({
    type:'POST',
    dataType:'json',
    url:'/issue/share/' + Drupal.settings.node.nid
  });


});