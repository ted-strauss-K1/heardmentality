var cbox;
$(document).ready(function () {

  $('.openlogin_box').live('click', function (e) {
    e.preventDefault();

    if ($.browser.mobile) {
      location.href = '/user/login';
      return;
    }

    var options = $.browser.mobile ?
    {/*inline:true, */width: '100%', height: '100%', top: '0px', reposition: false} :
    {/*inline:true */};
    options['href'] = Drupal.settings.language_prefix + '/colorbox/form/user_login_modal_form?redirect=' + encodeURIComponent(location.pathname);

    cbox = $.colorbox(options);

    return false;
  });

  $('#dialog_link:not(.openlogin_box)').live('click', function (e) {
    e.preventDefault();

    if ($.browser.mobile) {
      location.href = '/user/profile/view';
      return;
    }

    var options = $.browser.mobile ?
    {inline: true, width: '100%', height: '100%', top: '0px', reposition: false} :
    {inline: true};
    options['href'] = '#popup-login';

    cbox = $.colorbox(options);

    return false;
  });

  //
  $('#cboxContent #popup-login.logged_in a, #cboxContent form input[type=submit]').live('click', function () {
    if (cbox) {
      cbox.colorbox.close();
      cbox = null;
    }
  });

});
