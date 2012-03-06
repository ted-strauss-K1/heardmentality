//$Id:$
$(document).ready( function () {
/**
 * Undocumented Code!
 */
function gigyaCommentsAddDrupalComment (eventObj) {
  $.ajax({
    type: 'POST',
    url: '/gigya/comments/',
    dataType: 'json',
    data: {'ajax': true, 'commentText': eventObj.commentText, 'UIDSignature': eventObj.user.UIDSignature, 'uid': eventObj.user.UID, 'timestamp': eventObj.user.signatureTimestamp, 'nid': Drupal.settings.gigya_comments.commentsUIparams.streamID }
  });


  }
if (typeof Drupal.settings.gigya_comments != 'undefined') {
  var conf = Drupal.settings.gigya.conf;
  Drupal.settings.gigya_comments.commentsUIparams.onCommentSubmitted = gigyaCommentsAddDrupalComment;
  gigya.services.socialize.showCommentsUI(conf, Drupal.settings.gigya_comments.commentsUIparams);
  }
else {
  return false;
}
});
