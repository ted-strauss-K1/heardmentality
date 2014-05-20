$(document).ready(function () {
  // update every 20 seconds
  setInterval(function () {
    eventsStreamUpdate();
  }, 10000);

  // update timeline
  setInterval(function () {
    $('.submitted').each(function () {
      $(this).html(
        events_time_interval(parseInt($(this).attr('name')))
      );
    });
  }, 1000);
});

/**
 * Update function
 */
function eventsStreamUpdate() {

  $.ajax({
    type: "POST",
    dataType: "json",
    url: Drupal.settings.language_prefix + '/events/ajax/?since=' + $('.uactivity .msg:first').attr('name'),
    data: $('#uactivity').attr('name'),
    success: function (response) {
      var ct = 0
      for (var item in response) {
        $('.uactivity .msg:first').before(response[item]).hide().slideDown(500);
        ct++;
      }
      $('.uactivity .msg').slice(100).remove();
      if (ct) {
        $('.uactivity .msg.nomsg').remove();
      }
    }
  });
  translate();
}

/**
 *
 * @param time
 * @return {String}
 */
function events_time_interval(time) {
  var date = new Date(time * 1000);
  var curdate = new Date();

  var diff = curdate.getTime() - date.getTime();
  if (diff <= 0) {
    return Drupal.tt("just now", {"@code": "events-time-now"});
  }
  diff = Math.floor(diff / 1000);
  if (diff < 60) return Drupal.tt("@count second(s) ago", {"@code": "events-time-s", "@count": diff});
  diff = Math.floor(diff / 60);
  if (diff < 60) return Drupal.tt("@count minute(s) ago", {"@code": "events-time-i", "@count": diff});
  diff = Math.floor(diff / 24);
  if (diff < 24) return Drupal.tt("@count hour(s) ago", {"@code": "events-time-h", "@count": diff});
  diff = Math.floor(diff / 30);
  if (diff < 30) return Drupal.tt("@count day(s) ago", {"@code": "events-time-d", "@count": diff});
  diff = Math.floor(diff / 12);
  if (diff < 12) return Drupal.tt("@count month(s) ago", {"@code": "events-time-m", "@count": diff});
  return Drupal.tt("@count year(s) ago", {"@code": "events-time-y", "@count": diff});
}
