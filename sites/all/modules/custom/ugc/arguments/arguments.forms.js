$(document).ready(function() {

  /*
   * Switch between Debate/Resource forms
   */
  $('.reference-form').hide();
  $('#link_arg-wrapper a').click(function(){
    $('.reference-form').show();
    $('.argument-form').hide();
    $('#argument_type').val(0);
    return false;
  });
  $('#link_ref-wrapper a').click(function(){
    $('.reference-form').hide();
    $('.argument-form').show();
    $('#argument_type').val(1);
    return false;
  });

  /*
   *
   */


});
