$(document).ready(function () {
  // update every 20 seconds
  setInterval(function () {
    eventsStreamUpdate();
  }, 10000);

  // update timeline
  setInterval(function () {
    $('.submitted').each(function () {
      $(this).html(
        events_time_interval(parseInt($(this).attr('name'))) + " " + Drupal.t("ago"));
    });
  }, 1000);
});

/**
 * Update function
 */
function eventsStreamUpdate() {

  $.ajax({
    type    : "POST",
    dataType: "json",
    url     : Drupal.settings.language_prefix + '/events/ajax/?since=' + $('.uactivity .msg:first').attr('name'),
    data    : $('#uactivity').attr('name'),
    success : function (response) {
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
    return Drupal.t("just now");
  }
  diff = Math.floor(diff / 1000);
  if (diff < 60) return diff + " " + Drupal.t("second" + (diff == 1 ? "" : "s"));
  diff = Math.floor(diff / 60);
  if (diff < 60) return diff + " " + Drupal.t("minute" + (diff == 1 ? "" : "s"));
  diff = Math.floor(diff / 24);
  if (diff < 24) return diff + " " + Drupal.t("hour" + (diff == 1 ? "" : "s"));
  diff = Math.floor(diff / 30);
  if (diff < 30) return diff + " " + Drupal.t("day" + (diff == 1 ? "" : "s"));
  diff = Math.floor(diff / 12);
  if (diff < 12) return diff + " " + Drupal.t("month" + (diff == 1 ? "" : "s"));
  return diff + " " + Drupal.t("year" + (diff == 1 ? "" : "s"));
}
