/**
 *
 */
function charts_update() {
  $.ajax({
    type      : 'POST',
    dataType  : 'json',
    url       : /*'/'+Drupal.settings.language+*/'/issue/charts/'+Drupal.settings.node.nid,
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

      init_gmap();
      init_highstock();
      init_highchart('');
      init_strength();
    }
  });
  return false;
}