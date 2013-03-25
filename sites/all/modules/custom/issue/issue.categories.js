$('input[type="checkbox"].issue_category').live('click', function (e) {
  e.preventDefault();

  var $$ = $(this);
  $.ajax({
    type        : 'POST',
    dataType    : 'json',
    url         : '/issue/subscribe',
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
      // checking
      if (response.result) {
        $$.attr('checked', 'checked');
      } else {
        $$.removeAttr('checked');
      }
    }
  });
});