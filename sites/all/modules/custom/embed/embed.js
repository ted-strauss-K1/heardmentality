$(document).ready(function () {

  $('input[type=button]').click(function () {

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
    $('div.content > div').addClass('voted');
    $('table tr.vote-results').show(500, function () {
      $('table tr.vote-results').each(function () {
        $(this).find('div.percent-bar').animate({
          'width': $(this).attr('data-width')
        });
        $(this).find('.percent b').html($(this).attr('data-votes'));
        $(this).find('.percent span').html($(this).attr('data-percent'));
      });
    });

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
