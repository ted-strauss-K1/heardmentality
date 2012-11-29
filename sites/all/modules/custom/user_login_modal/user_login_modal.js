$(document).ready(function () {

  $('.openlogin_box').live('click', function () {
    $('#dialog').tabs();
    $('#dialog').dialog('open');
    return false;
  });

});