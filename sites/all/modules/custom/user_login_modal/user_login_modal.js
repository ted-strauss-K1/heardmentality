$(document).ready(function () {

  $('.openlogin_box').live('click', function (e) {
    e.preventDefault();

    var options = $.browser.mobile ?
    {/*inline:true, */width: '100%', height: '100%', top: '0px', reposition: false} :
    {/*inline:true */};
    options['href'] = Drupal.settings.language_prefix + '/colorbox/form/user_login_modal_form?redirect=' + encodeURIComponent(location.pathname);

    $.colorbox(options);

    return false;
  });

  $('#dialog_link').live('click', function (e) {
    e.preventDefault();

    var options = $.browser.mobile ?
    {inline: true, width: '100%', height: '100%', top: '0px', reposition: false} :
    {inline: true};
    options['href'] = '#popup-login';

    $.colorbox(options);

    return false;
  });

});
