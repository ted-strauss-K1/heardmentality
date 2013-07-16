

$('#shareDiv-reaction0, #shareDiv-reaction1, #shareDiv-reaction2, #shareDiv-reaction3').live('click', function () {
  $.ajax({
    type:'POST',
    dataType:'json',
    url:'/issue/share/' + Drupal.settings.node.nid
  });
});