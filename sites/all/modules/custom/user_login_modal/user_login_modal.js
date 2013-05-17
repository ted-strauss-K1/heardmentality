$(document).ready(function () {

  $(".inline-dialog").colorbox({inline:true, width:'100%', height:'100%', top: '0px', reposition: false});

  $('#dialog_link, .openlogin_box').live('click', function () {

    $(".inline-dialog").click();

//    $('#dialog')
//      .tabs()
//      .dialog('open')
//      .find('input[name="name"]').focus();

    return false;
  });

});