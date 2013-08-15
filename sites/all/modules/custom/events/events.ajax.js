// events via ajax
$(document).ready(function () {
  $('body').on('events', function(e, type, vars) {
    $.ajax({
      type      : "POST",
      dataType  : "json",
      url       : '/'+Drupal.settings.language+'/events/event/'+type,
      data      : vars,
      success   : function (response) {
        //
      }
    });
  });
});