$('input[type="checkbox"].categories_subscribe').live('click', function (e) {
  e.preventDefault();

  var $$ = $(this);
  $.ajax({
    type        : 'POST',
    dataType    : 'json',
    url         : '/categories/subscribe',
    data        : { hierarchy : $(this).attr('name') },
    success     : function (response) {
      if (!response.status) {
        $.hrd.noty({
          type  : 'error',
          text  : response.message
        });
        return false;
      }
      //
      $.hrd.noty({
        type  : 'success',
        text  : response.message
      });
      // checking todo
      if (response.result) {
        $$.attr('checked', 'checked');
      } else {
        $$.removeAttr('checked');
      }
    }
  });
});