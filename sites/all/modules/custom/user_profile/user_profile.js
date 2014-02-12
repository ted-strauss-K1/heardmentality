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
      'text'   : $('#user-profile-avatar-selection-wrapper').html(),
      'type'   : 'notification',
      'modal'  : true,
      'timeout': false,
      'layout' : 'center',
      'buttons': [
        {
          addClass: 'btn btn-danger',
          text    : 'Close',
          onClick : function ($noty) {
            $noty.close();
          }
        }
      ]
    });
  });

  $('body').on('geocode.success', function (e, location) {
    var output = '';

    // country
    if (location['country_code']) {
      output = location['country_name'];
      $('#profile_country').val(location['country_code'])
    } else {
      $('#profile_country').val('');
    }

    // province/state
    if (location['province_code']) {
      $('#profile_state').val(location['province_code']);
    } else {
      $('#profile_state').val('');
    }

    // city
    if (location['city_code']) {
      output += ", " + location['city_name'];
      $('#profile_city').val(location['city_code']);
    } else {
      $('#profile_city').val('');
    }

    // postal code
    if (location['postalcode']) {
      $('#profile_zip').val(location['postalcode']);
    } else {
      $('#profile_zip').val('');
    }

    if (location['province_code'] && !location['city_code']) {
      output += ", " + location['province_name'];
    }

    // location
    if (location['latitude'] && location['longitude']) {
      $('#profile_lat').val(location['latitude']);
      $('#profile_lng').val(location['longitude']);
    } else {
      $('#profile_lat').val('');
      $('#profile_lng').val('');
    }

    // text
    $('.user-profile-location .determined').html(output).slideDown(400);
  });

  $('.user-profile-location .determine').live('click', function (e) {
    e.preventDefault();

    $(this).remove();
    $('body').trigger('geocode.latlng');
  });

  $('#profile_zip').live('focusout', function () {
    var info = $('.user-profile-location .determined');
    info.slideUp(400, function () {
    });

    $('body').trigger('geocode.postalcode', [$('#profile_country').val(), $('#profile_zip').val()]);
//
//
//    var url = Drupal.settings.language_prefix+'/user/profile/location/' + $('#profile_country').val() + '/' + $('#profile_zip').val();
//    $.ajax({
//      type:"POST",
//      dataType:'json',
//      url:url,
//      data:{},
//      success:function (response) {
//        if (response.status) {
//          $('#user-profile-location').html(response.message);
//        } else {
//          $('#user-profile-location').html('');
//        }
//        $('#user-profile-location').slideDown(400);
//      }
//    });
  });

});
