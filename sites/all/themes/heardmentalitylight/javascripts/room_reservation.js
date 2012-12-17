$(document).ready(function() {
  $(function() {
    //  var e = 0;
    var select = $( ".value-select .form-item select" );
    select.each(function(e){
      var slider = $("<div id='slider-"+e+"'><span class='left'></span><span class='right'></span></div>" ).insertAfter( $(this) ).slider({
        min: 1,
        max: 3,
        range: 2,
        value: select[e].selectedIndex + 1,
        slide: function( event, ui ) {
          select[e].selectedIndex = ui.value - 1;
        }
      });

    });
    $( ".value-select .form-item select" ).change(function() {
      $(this).next().slider("value", this.selectedIndex + 1 );
    });
  });
});