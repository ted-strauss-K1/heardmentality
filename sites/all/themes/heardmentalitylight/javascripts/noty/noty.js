$.hrd = {};
$.hrd.noty = function(options) {
	var opt = {
		text: options['text'],
		type: options['type'],
		dismissQueue: true,
		timeout: 5000,
		layout: 'topRight',
		closeWith: ['click', 'button'],
		force: true,
	};
	opt = $.extend(opt, options);
	noty(opt);
}