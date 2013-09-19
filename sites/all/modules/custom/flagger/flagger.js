// status
function flagger_status(response)  {
  if ("string" == typeof response) {
    response = $.parseJSON(response);
  }
  var flags = $('.flagger-btn-flags-'+response.content_type+'-'+response.content_id);
  if (response.flagged) {
    flags.addClass('flagged');
  } else {
    flags.removeClass('flagged');
  }
  return true;
}

// flag
$('.flagger').live('click', function (e) {
  e.preventDefault();
  var flagger = $(this);

  var url = Drupal.settings.language_prefix+'/flagger/' + flagger.attr('name')
  $.ajax({
    type:"POST",
    dataType:'json',
    url:url,
    data:{},
    success:function (response) {
      $.hrd.noty({
        'layout':'center',
        'type':'alert',
        'text':response.message,
        'modal':true,
        'timeout':false,
        'buttons':[
          {
            addClass:'btn btn-primary',
            text:response.texts[0],
            onClick:function ($noty) {
              $('#flagger-form').submit();
              $noty.close();
              $.hrd.noty({
                'layout':'center',
                'type':'success',
                'text':response.texts[2],
                'modal':true
              });
            }
          },
          {
            addClass:'btn btn-danger',
            text:response.texts[1],
            onClick:function ($noty) {
              $noty.close();
            }
          }
        ]
      });
      $('#flagger-form').ajaxForm({
        success: flagger_status
      });
    }
  });

  return false;
});

// flags
$('.flagger_flags').live('click', function (e) {
  e.preventDefault();
  var flagger = $(this);

  var url = Drupal.settings.language_prefix+'/flagger/flags/' + flagger.attr('name')
  $.ajax({
    type:"POST",
    dataType:'json',
    url:url,
    data:{},
    success:function (response) {
      $.hrd.noty({
        'layout':'center',
        'type':'alert',
        'text':response.message,
        'modal':true,
        'timeout':false
      });
    }
  });

  return false;
});

// history
$('.flagger_history').live('click', function (e) {
  e.preventDefault();
  var flagger = $(this);

  var url = Drupal.settings.language_prefix+'/flagger/history/' + flagger.attr('name')
  $.ajax({
    type:"POST",
    dataType:'json',
    url:url,
    data:{},
    success:function (response) {
      $.hrd.noty({
        'layout':'center',
        'type':'alert',
        'text':response.message,
        'modal':true,
        'timeout':false
      });
    }
  });

  return false;
});

// history
$('.status-1 span.remove').live('click', function (e) {
  e.preventDefault();
  var parent = $(this).parents('li.status-1');
  var fcid = parent.attr('name');

  var url = Drupal.settings.language_prefix+'/flagger/unflag/' + parent.attr('name')
  $.ajax({
    type:"POST",
    dataType:'json',
    url:url,
    data:{},
    success:function (response) {
      $.hrd.noty({
        'layout':'topRight',
        'type':'alert',
        'text':response.message,
        'modal':false,
        'timeout':5000
      });
      if (response.status) {
        parent.removeClass('status-1').addClass('status-0');
        parent.find('span.flag-name').removeClass('status-1').addClass('status-0');
        flagger_status(response);
      }
    }
  });

  return false;
});
