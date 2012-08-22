/*
 * Function to invoke user shared userpoints
 */
function up_share() {
    var url = Drupal.settings.base_url + '/up_share/' + Drupal.settings.node.nid;
    jQuery.ajax({
        type: "POST",
        dataType: 'json',
        url: url,
        data: {},
        success: function(response){
            //
        }
    });
}

/*
 * Attach events for the share buttons
 *
 * TODO -- fix selectors
 */
jQuery("#shareDiv-reaction0, #shareDiv-reaction1, #shareDiv-reaction2").click(function(){
    up_share();
});