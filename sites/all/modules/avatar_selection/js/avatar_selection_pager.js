/* jQueryId: avatar_selection_pager.js,v 1.1.2.3 2009/06/07 23:34:23 snpower Exp jQuery */

/**
 * Fetches the new page and puts it inline.
 *
 * @param form_id   - The id of the form whose action should be updated.
 * @param id   - The element id whose contents will get replaced.
 * @param url - The URL for the new page.
 * @param page  - The page number to request.
 * @param js_file  - The javascript file to run upon completion.
 */
function fetchPage(form_id, id, url, page, js_file) {
  jQuery("body").css({'opacity': 0.5});
  jQuery("#avatar-selection-loading").show();
  jQuery.get(url, {page: page}, function(data, status) {
    var selects = jQuery(data).find(id);
    jQuery(id).html(selects);
    var pager = jQuery(data).find(".avatar-selection-pager-nav");
    jQuery(".avatar-selection-pager-nav").html(pager);
    jQuery.getScript(js_file);
    var action = url + "?page="+page;
    jQuery(form_id).attr("action", action);
    jQuery("#avatar-selection-loading").hide();
    jQuery("body").css({'opacity': null});
  });
  return false;
}
