$(document).ready(function () {
  tipsy_attach();
});

function tipsy_attach() {
  $('.medal1, #medal1, #medal2, #medal3,  img.coin2, .disagree, .agree, #badges .medal3, #badgeslist .medal3').tipsy({
    gravity: 'nw'
  });

  $('.flag, .flag2, .heart, a.stats-quick').tipsy({
    gravity: 'w'
  });
  $('span.lighter, .privacy-rules').tipsy({
    gravity: 's'
  });
  $('.flagger, .moderation, .flagger_flags, .flagger_history').tipsy({
    gravity: 'e'
  });

  $('.usernote').tipsy({
    gravity: 'n'
  });

  /// TODO Are these used ??
  $('#nope').tipsy({
    gravity: $.fn.tipsy.autoNS
  });

  $('#example-fade').tipsy({
    fade: true
  });

  $('#example-custom-attribute').tipsy({
    title: 'id'
  });
  $('#example-callback').tipsy({
    title: function() {
      return this.getAttribute('original-title').toUpperCase();
    }
  });
  $('#example-fallback').tipsy({
    fallback: "Where's my tooltip yo'?"
  });

  $('#example-html').tipsy({
    html: true
  });
}