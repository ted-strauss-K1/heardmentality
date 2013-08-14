function follower_exec(follower) {
  var url = '/'+Drupal.settings.language+'/follower/save/';
  $.ajax({
    type:"POST",
    dataType:'json',
    url:url,
    data:{
      'rtid':1,
      'follow_uid':follower.attr('name')
    },
    success:function (response) {
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
        'layout':'topRight',
        'type':'success',
        'text':successtext
      });
    }
  });
}

$(document).ready(function () {
  $('.follower').live('click', function (e) {
    e.preventDefault();
    var follower = $(this);
    follower_exec(follower);
    return false;
  });
});