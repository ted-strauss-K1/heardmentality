function toggle_resources() {
  if ($('#inc_check').attr('checked')) {
    $('.resources').show();
  } else {
    $('.resources').hide();
  }
}

$(document).ready(function () {
  /*
   * Toggle resources
   */
  $('#inc_check').change(function () {
    toggle_resources();
  });

});

/**
 *
 */
$('a.permalink').live('click', function (e) {
  e.preventDefault();
//  var link = window.location.href.replace(/#.*/, '') + '#' + $(this).parents('.one-forum').attr('id');
  var link = $(this).attr('name');
  $.hrd.noty({
    'layout':'center',
    'type':'alert',
    'text':'<a href="' + link + '">' + link + '</a>',
    'modal':true,
    'timeout':false,
    'closeWith':['button']
  });
});

$('#shareDiv-reaction0, #shareDiv-reaction1, #shareDiv-reaction2, #shareDiv-reaction3').live('click', function () {
  $.ajax({
    type:'POST',
    dataType:'json',
    url:'/issue/share/' + Drupal.settings.node.nid
  });
});