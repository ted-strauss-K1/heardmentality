$(document).ready(function () {
  setInterval(function () {
    action_dequeue(Drupal.settings.user.uid);
  }, 5000);
});

/**
 * @param uid
 */
function action_dequeue(uid) {
  // todo do not ask too much
  $.ajax({
    type    : 'POST',
    dataType: 'json',
    url     : Drupal.settings.language_prefix + '/action/dequeue',
    data    : {'uid': uid },
    success : function (response) {
      if (response.status) {
        if (response.message instanceof Array) {
          for (var i in response.message) {
            $.hrd.noty({
              text: response.message[i],
              type: 'success'
            });
          }
        }
      }
    }
  });
}
