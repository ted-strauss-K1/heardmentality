



 jQuery(document).ready(function () {
    jQuery('.facts-figures a').click(function(e) {
  e.preventDefault();
e.stopPropagation();
        //$('#box1').css("background","#9f9");
        jQuery(".facts-figures a").css('color', '#000');
        jQuery(this).css('color', '#4170A0');
         jQuery('#heatmap').fadeOut('slow');
         var params="?width=600&height=400";
        jQuery('#cirmap').attr('src',jQuery(this).attr('href')+params);
         jQuery('#heatmap').fadeIn('slow');

    });
 });