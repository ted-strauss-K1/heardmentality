$(document).ready(function () {

  $('#dialog_link, .openlogin_box').live('click', function () {

    $('#dialog')
      .tabs()
      .dialog('open')
      .find('input[name="name"]').focus();

    return false;
  });

});