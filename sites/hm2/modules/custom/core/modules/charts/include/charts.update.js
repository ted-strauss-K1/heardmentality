/**
 *
 */
$('body').on('cpoll_update', function (e, only) {
  $.ajax({
    type    : 'POST',
    dataType: 'json',
    url     : Drupal.settings.language_prefix + '/charts/update/' + Drupal.settings.node.nid,
    data    : {},
    success : function (response) {
      if (!response.status) {
        $.hrd.noty({
          type: 'error',
          text: response.message
        });
        return false;
      }
      //
      var data = response.data;

      for (var i in data) {
        Drupal.settings.charts[i] = data[i];
      }

      if (typeof init_strength == 'function') {
        init_strength();
      }

      if (only) {
        return;
      }

      $('span.no_show').remove();
      $('ul.notvoted').removeClass('notvoted');

      init_gmap();
      init_history();
      init_filter('');
    }
  });
  return false;
});
