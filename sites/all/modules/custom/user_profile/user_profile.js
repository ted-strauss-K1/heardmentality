$(document).ready(function () {

  $('.profile-close-icon').click(function () {
    $('.profile-status-toggle').slideUp(400, function () {
      $('.profile-status-toggle').remove();
    });
    $.cookie('profile_status', '0');
  });

  $('#user-profile-avatar-selection img').live('click', function (e) {
    $('#user-profile-avatar-selection img').removeClass('selected');
    $(this).addClass('selected');
    $('#image_avatar').val($(this).attr('src'));
    $('#image-avatar-pic').attr('src', $(this).attr('src'));
  });

  $('#user-profile-avatar-selection-open').live('click', function (e) {
    e.preventDefault();
    $.hrd.noty({
      'text':$('#user-profile-avatar-selection-wrapper').html(),
      'type':'notification',
      'modal':true,
      'timeout':false,
      'layout':'center',
      'buttons':[
        {
          addClass:'btn btn-danger',
          text:'Close',
          onClick:function ($noty) {
            $noty.close();
          }
        }
      ]
    });
  });

  $('#profile_zip').live('focusout', function () {
    $('#user-profile-location').slideUp(400);
    var url = '/'+Drupal.settings.language+'/user/profile/location/' + $('#profile_country').val() + '/' + $('#profile_zip').val();
    $.ajax({
      type:"POST",
      dataType:'json',
      url:url,
      data:{},
      success:function (response) {
        if (response.status) {
          $('#user-profile-location').html(response.message);
        } else {
          $('#user-profile-location').html('');
        }
        $('#user-profile-location').slideDown(400);
      }
    });
  });

});