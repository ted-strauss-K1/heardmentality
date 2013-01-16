/**
 * Changing active state
 */
$('.sort-wrapper a').live('click', function () {
  var wrap = $(this).parents('.sort-wrapper');
  wrap.children('a').removeClass('active');
  $(this).addClass('active');
});

//$('img.following-user').live('click', function() {
//  var el = $(this);
//  var id = $(this).attr('id').replace('uid-', '');
//  following_params = following_params || {};
//  if (el.hasClass('checked')) {
//    el.removeClass('checked');
//    following_params['uid'] = following_params['uid'] || [];
//    following_params['uid'].push(id);
//  } else {
//    el.addClass('checked');
//    var index = following_params['uid'].indexOf(id);
//    following_params['uid'].splice(index, 1);
//  }
//});

/**
 * saving params for following page here
 *
 * @type {*|Object}
 */
var following_params = following_params || {};

/**
 * Make a request
 *
 * @param params
 */
function following_exec(params) {
  params = params || {};
  var el = $('#events_following');

  el.html('<div style="text-align:center"><div id="loading"></div></div>');

  $.ajax({
    type:"POST",
    dataType:'json',
    url:'/following/ajax',
    data:following_params,
    success:function (response) {
      if (!response.status) {
        // error
        return false;
      }
      el.html(response.message);
    }
  });
}

/**
 * Changing active state
 */
$('.sort-wrapper a').live('click', function () {
  var el = $(this);
  following_params = following_params || {};
  following_params['items'] = el.attr('name');
  following_exec(following_params);
});

/**
 * Specific param passing
 */




$('#events_users_more').live('click', function () {

});