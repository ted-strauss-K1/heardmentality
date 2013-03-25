$(document).ready(function () {
  translate();

  // update every 20 seconds
  setInterval(function () {
    eventsStreamUpdate();
  }, 10000);

  // update timeline
  setInterval(function () {
    $('.submitted').each(function() {
      $(this).html(
        events_time_interval(parseInt($(this).attr('name'))) + " " + events_time_string("ago"));
    });
  }, 1000);
});

/**
 * Update function
 */
function eventsStreamUpdate() {
  $.ajax({
    type      : "POST",
    dataType  : "json",
    url       : 'events/latest/'+$('.uactivity .msg:first').attr('name'),
    data      : {},
    success   : function (response) {
      for (var item in response) {
        $('.uactivity .msg:first').before(response[item]);
        $('.uactivity .msg:first').hide();
        $('.uactivity .msg:first').slideDown(500);
      }
      $('.uactivity .msg').slice(100).remove()
    }
  });
  translate();
}

/**
 * Strings
 *
 * // todo need to have better way to translate JS strings
 *
 * @param string
 * @return {*}
 */
function events_time_string(string) {
  return typeof Drupal.settings.time == "undefined" ? string : Drupal.settings.time[string];
}

/**
 *
 * @param time
 * @return {String}
 */
function events_time_interval(time) {
  var date = new Date(time*1000);
  var curdate = new Date();

  var diff = curdate.getTime() - date.getTime();
  if (diff <= 0) {
    return events_time_string("just now");
  }
  diff = Math.floor(diff/1000);
  if (diff < 60) return diff + " " + events_time_string("second" + (diff==1?"":"s"));
  diff = Math.floor(diff/60);
  if (diff < 60) return diff + " " + events_time_string("minute" + (diff==1?"":"s"));
  diff = Math.floor(diff/24);
  if (diff < 24) return diff + " " + events_time_string("hour" + (diff==1?"":"s"));
  diff = Math.floor(diff/30);
  if (diff < 30) return diff + " " + events_time_string("day" + (diff==1?"":"s"));
  diff = Math.floor(diff/12);
  if (diff < 12) return diff + " " + events_time_string("month" + (diff==1?"":"s"));
  return diff + " " + events_time_string("year" + (diff==1?"":"s"));
}