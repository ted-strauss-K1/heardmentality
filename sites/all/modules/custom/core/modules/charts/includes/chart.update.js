/**
 *
 */
$('body').on('cpoll_update', function(only) {
  $.ajax({
    type      : 'POST',
    dataType  : 'json',
    url       : /*'/'+Drupal.settings.language+*/'/charts/update/'+Drupal.settings.node.nid,
    data      : {},
    success   : function (response) {
      if (!response.status) {
        $.hrd.noty({
          type  : 'error',
          text  : response.message
        });
        return false;
      }
      //
      var data = response.data;

      for (var i in data) {
        Drupal.settings.charts[i] = data[i];
      }

      init_strength();

      if (only) {
        return;
      }
      init_gmap();
      init_highstock();
      init_highchart('');

    }
  });
  return false;
});