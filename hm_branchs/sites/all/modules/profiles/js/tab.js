



 jQuery(document).ready(function () {
    jQuery('.fa-item a').click(function(e) {
  e.preventDefault();
e.stopPropagation();
        //$('#box1').css("background","#9f9");
        jQuery(".fa-item a").css('color', '#996600');
        jQuery(this).css('color', '#4170A0');
         jQuery('#heatmap').fadeOut('slow');
         var params="?width=155&height=100";
        jQuery('#cirmap').attr('src',jQuery(this).attr('href')+params);
         jQuery('#heatmap').fadeIn('slow');

    });
 });