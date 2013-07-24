/**
 * Slider improvements
 */
$(document).ready(function () {
  $('body').on('badge.queue', function(e, uid, badge) {
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
  }).on('badge.dequeue', function(e, uid) {
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
});