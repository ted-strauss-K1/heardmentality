$(document).ready(function () {

  var options = $.browser.mobile ?  {inline:true, width:'100%', height:'100%', top: '0px', reposition: false} : {inline:true};
  console.log(options);
  $(".inline-dialog").colorbox(options);

  $('#dialog_link, .openlogin_box').live('click', function () {

    $(".inline-dialog").click();

    return false;
  });

});