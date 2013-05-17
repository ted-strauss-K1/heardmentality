$(document).ready(function () {

  $(".inline-dialog").colorbox({inline:true});

  $('#dialog_link, .openlogin_box').live('click', function () {

    $(".inline-dialog").click();

//    $('#dialog')
//      .tabs()
//      .dialog('open')
//      .find('input[name="name"]').focus();

    return false;
  });

});