$(document).ready(function () {

  $(".inline-dialog").colorbox($.browser.mobile ?
  {inline:true, width:'100%', height:'100%', top: '0px', reposition: false} : {inline:true}
  );

  $('#dialog_link, .openlogin_box').live('click', function () {

    $(".inline-dialog").click();

//    $('#dialog')
//      .tabs()
//      .dialog('open')
//      .find('input[name="name"]').focus();

    return false;
  });

});