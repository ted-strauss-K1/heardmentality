$(document).ready(function () {

  // voted
  embedder_animate_onload();

  // login
  if ($('div.content').hasClass('login')) {
    $('form#user-login').bind('submit', function (e) {
      e.preventDefault();

      var form = $(this);

      $.ajax({
        type    : 'POST',
        dataType: 'json',
        url     : form.attr('action'),
        data    : form.serialize(),
        success : function (response) {
          if (!response.status) {
            return false;
          }
          $('div.content').html(response.content);
          socket.postMessage(document.body.scrollHeight);
          if (response.voted) {
            $('div.content > div').addClass('voted');
            embedder_animate_onload();
          }
        }
      });

      return false;
    });
  }

  // vote
  $('input[type=button]').bind('click', function () {

    // check if vote value is selected
    if (!$('input[name=chid]:checked').length) {
      return;
    }

    // get data
    var nid = $('input[name=nid]').val();
    var chid = $('input[name=chid]:checked').val();
    var language_prefix = $('input[name=lang]').val();

    // increment vote
    var vote = $('.vote-results-' + chid);
    vote.attr('data-votes', parseInt(vote.attr('data-votes')) + 1);

    // update data
    $('table tr.vote-results').each(function () {
      var percent = 100 * $(this).attr('data-votes') / $(this).attr('data-count');
      $(this).attr('data-width', parseInt(percent) + '%');
      $(this).attr('data-percent', percent.toFixed(2));
    });

    // show the initial bar
    $('.percent-bar').width(0);

    //
    embedder_animate();

    // now make the ajax call
    $.ajax({
      type    : 'POST',
      dataType: 'json',
      url     : language_prefix + '/cpoll_vote/ajax',
      data    : {
        "nid" : nid,
        "chid": chid
      },
      success : function (response) {
        if (!response.status) {
          location.reload();
          return;
        }
      }
    });
  });
});

/**
 *
 */
function embedder_animate() {
  $('body').trigger('height_change', []);

  $('div.content > div').addClass('voted');
  $('table tr.vote-results').css('visibility', 'inherit').each(function () {
    $(this).find('div.percent-bar').animate({
      'width': $(this).attr('data-width')
    }, 1000);
    $(this).find('.percent b').html($(this).attr('data-votes'));
    $(this).find('.percent span').html($(this).attr('data-percent'));
  });
}
/**
 *
 */
function embedder_animate_onload() {
  if ($('div.content > div').hasClass('voted')) {
    var results = $('table tr.vote-results');
    results.each(function () {
      $(this).find('div.percent-bar').width(0);
    });
    embedder_animate();
  }
}
