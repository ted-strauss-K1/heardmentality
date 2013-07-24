/**
 * Slider improvements
 */
$(document).ready(function () {
  var body = $('body');

  body.on('badge.queue', function(e, uid, badge) {
    $.ajax({
      type      : 'POST',
      dataType  : 'json',
      url       : '/badges/queue/'+uid+'/'+badge,
      data      : form.serialize(),
      success   : function (response) {
        //
      },
      complete  : function () {
        //
      }
    });
  });

  body.on('badge.dequeue', function(e, uid) {
    $.ajax({
      type      : 'POST',
      dataType  : 'json',
      url       : '/badges/dequeue/'+uid,
      data      : form.serialize(),
      success   : function (response) {
        //
      },
      complete  : function () {
        //
      }
    });
  });

  body.on('badge.cpoll_author', function(e, uid) {
    body.trigger('badges.queue', [uid, 'argument_bronze']);
    body.trigger('badges.queue', [uid, 'argument_silver']);
    body.trigger('badges.queue', [uid, 'argument_gold']);
  });
});