/**
 * Slider improvements
 */
$(document).ready(function () {
  var body = $('body');

  body.on('badges.queue', function(e, uid, badges) {
    $.ajax({
      type      : 'POST',
      dataType  : 'json',
      url       : '/badges/queue',
      data      : { 'uid' : uid, 'badges' : badges },
      success   : function (response) {
        //
      },
      complete  : function () {
        //
      }
    });
  });

  body.on('badges.dequeue', function(e, uid) {
    $.ajax({
      type      : 'POST',
      dataType  : 'json',
      url       : '/badges/dequeue',
      data      : {'uid' : uid },
      success   : function (response) {
        if (response.status) {
          $.hrd.noty({
            text  : response.message,
            type  : 'success'
          });
        }
      },
      complete  : function () {
        //
      }
    });
  });

  // dequeue
  console.log('interval for granting badges');
  setInterval(function () {
    body.trigger('badges.dequeue', [Drupal.settings.user.uid]);
  }, 10000);

  body.on('badge.debate_create', function(e, uid) {
    // uid - cpoll author
    body.trigger('badges.queue', [uid, ['argument_bronze', 'argument_silver', 'argument_gold']]);
  });

  body.on('badge.comment_create', function(e, uid) {
    // uid - comment author
    body.trigger('badges.queue', [uid, 'comment_bronze']);
  });

  body.on('badge.cpoll_vote', function(e, uid) {
    // uid - voter
    body.trigger('badges.queue', [uid, ['poll_votes_bronze', 'poll_votes_silver', 'poll_votes_gold', 'poll_votes_taxonomy_bronze', 'poll_votes_taxonomy_silver', 'poll_votes_taxonomy_gold']]);
  });

  body.on('badge.cpoll_voted', function(e, uid) {
    // uid - cpoll author
    body.trigger('badges.queue', [uid, ['poll_votes_count_bronze', 'poll_votes_count_silver', 'poll_votes_count_gold']]);
  });

  body.on('badge.comment_yn_voteup', function(e, uid) {
    // uid - content author
    body.trigger('badges.queue', [uid, ['comment_agreed_bronze', 'comment_agreed_gold', 'yn_comment_bronze', 'yn_comment_silver', 'yn_comment_gold']]);
  });

  body.on('badge.resource_yn_voteup', function(e, uid) {
    // uid - content author
    body.trigger('badges.queue', [uid, ['yn_argument_agreed_resource_bronze', 'yn_argument_agreed_resource_silver', 'yn_argument_agreed_resource_gold']]);
  });

  body.on('badge.argument_yn_voteup', function(e, uid) {
    // uid - content author
    body.trigger('badges.queue', [uid, ['yn_argument_agreed_debate_bronze', 'yn_argument_agreed_debate_silver', 'yn_argument_agreed_debate_gold']]);
  });

  body.on('badge.yn_voteup', function(e, uid) {
    // uid - voter
    body.trigger('badges.queue', [uid, ['yn_upfirst']]);
  });

  body.on('badge.yn_predict', function(e, uid) {
    // uid - voter
    body.trigger('badges.queue', [uid, ['yn_predict_bronze', 'yn_predict_silver']]);
  });
});