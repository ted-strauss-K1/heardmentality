$.hrd = {};
$.hrd.noty = function(options) {
	var opt = {
		text: options['text'],
		type: options['type'],
		dismissQueue: true,
		timeout: 5000,
		layout: 'topRight',
		closeWith: ['button'],
		force: true
	};
	opt = $.extend(opt, options);
	noty(opt);
};

$('.noty_request').live('click', function (e) {
  e.preventDefault();
  $.ajax({
    type      : "POST",
    dataType  : "json",
    url       : $(this).attr('name'),
    data      : {},
    success   : function (response) {
      if (!response.status) {
        $.hrd.noty({
          type  : 'error',
          text  : response.message
        });
        return;
      }
      $.hrd.noty({
        'layout'  : 'center',
        'type'    : 'success',
        'text'    : response.message,
        'modal'   : true,
        'timeout' : false
      });

    }
  });
});