/**
 * @param timestamp
 * @returns {string}
 */
function timestamp2date(timestamp) {
  var months = ['Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec'];
  var date = new Date(timestamp);
  var output = date.getDate() + ' ' + months[date.getMonth()];
  return output;
}
