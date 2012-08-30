/* confirmation variant
function follower_exec(follower) {
  var url = Drupal.settings.base_url + '/follower/' + follower.attr('name')
  $.ajax({
    type: "POST",
    dataType: 'json',
    url: url,
    data: {},
    success: function(response){
      $.hrd.noty({
        'layout' : 'center',
        'type'   : 'alert',
        'text'   : response.text,
        'modal'  : true,
        'timeout': false,
        'buttons': [
          {
            addClass : 'btn btn-primary',
            text     : 'Yes!',
            onClick  : function($noty) {
              $('#follower-form').submit();
              $noty.close();
              var successtext = '', buttontext = '';
              if (follower.html() != response.follow) {
                successtext = response.unfollowtext;
                buttontext = response.follow;
              } else {
                successtext = response.followtext;
                buttontext = response.unfollow;
              }
              follower.html(buttontext);
              $.hrd.noty({
                'layout' : 'center',
                'type'   : 'success',
                'text'   : successtext,
                'modal'  : true
              });

            }
          },
          {
            addClass: 'btn btn-danger',
            text: 'Cancel',
            onClick: function($noty) {
              $noty.close();
            }
          }
        ]
      });
      $('#follower-form').ajaxForm({
        // target: '#output'
      });
    }
  });
}
*/

function follower_exec(follower) {
  var url = Drupal.settings.base_url + '/follower/save/';
  $.ajax({
    type: "POST",
    dataType: 'json',
    url: url,
    data: {
      'rtid' : 1,
      'follow_uid' : follower.attr('name')
    },
    success: function(response){
      var successtext = '', buttontext = '';
      if (follower.html() != response.follow) {
        successtext = response.unfollowtext;
        buttontext = response.follow;
      } else {
        successtext = response.followtext;
        buttontext = response.unfollow;
      }
      follower.html(buttontext);
      $.hrd.noty({
        'layout' : 'topRight',
        'type'   : 'success',
        'text'   : successtext
      });
    }
  });
}

function follower_rebind() {
  $('.follower').unbind( 'click' );
  $('.follower').click(function(e) {
    e.preventDefault();
    var follower = $(this);
    follower_exec(follower);
    return false;
  });
}

$(document).ready(function() {
  follower_rebind();
});


