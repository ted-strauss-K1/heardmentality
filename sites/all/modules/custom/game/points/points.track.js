$(document).ready(function () {
  if (typeof stLight != "undefined") {
    stLight.subscribe("click", points_share);
  }
});

/**
 *
 * @param event
 * @param service
 */
function points_share(event, service) {
  $.ajax({
    type    : 'POST',
    dataType: 'json',
    url     : Drupal.settings.language_prefix + '/action/queue',
    data    : {
      'uid'       : Drupal.settings.user.uid,
      'operation' : 'share',
      'service'   : service,
      'entity_id' : Drupal.settings.node.nid,
      'entity_nid': 'node'
    },
    success : function (response) {
      if (!response.status) {
        // on failure
        return false;
      }
      // on success
    }
  });
}
