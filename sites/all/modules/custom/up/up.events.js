/**
 * Function to invoke user shared userpoints
 */
function up_share() {
  var url = '/'+Drupal.settings.language+'/up_share/' + Drupal.settings.node.nid;
  $.ajax({
    type:"POST",
    dataType:'json',
    url:url,
    data:{},
    success:function (response) {
      //
    }
  });
}

/**
 * Attach events for the share buttons
 */
$("#shareDiv-reaction0, #shareDiv-reaction1, #shareDiv-reaction2").click(function () {
  up_share();
});