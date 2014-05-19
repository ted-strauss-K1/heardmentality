$(document).ready(function () {

  $('.tt-admin').click(function (e) {
    e.preventDefault();

    var ta = $(this).siblings('textarea');
    if (ta.val()) {
      $.ajax({
        type: 'POST',
        dataType: 'json',
        url: '/admin/settings/tt-ajax',
        data: {
          translation: ta.val(),
          lid: ta.attr('name'),
          language: Drupal.settings.langcode
        },
        success: function (response) {
          if (response.status) {
            ta.css('border-color', 'green');
          }
        }
      });
    }
  });

});
