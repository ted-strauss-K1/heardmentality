/*
 * Image Value Preprocess when submitting new resource
 */
jQuery('#add_new_debate').live('click', function () {
  var image_value;
  if (!jQuery('#no_thumbnail').attr('checked')) {
    var img_v = jQuery('#cur_id_val').val();
    image_value = jQuery('#cur_img_' + img_v).attr('src');
  } else {
    image_value = 'no_image';
  }
  jQuery('#image_value').val(image_value);
});


/*
 * flag/link/delete buttons
 */

jQuery('a.delete').live('click', function (e) {
  jQuery("#dialog_" + jQuery(this).attr('name')).dialog({
    resizable:false
  });
  return false;
});
jQuery('a.delete button').live('click', function (e) {
  jQuery(this).dialog("close");
  return false;
});
jQuery('.icon.flag2').live('click', function (e) {
  e.preventDefault();
  jQuery('#dialog-flag').dialog("open");

});
