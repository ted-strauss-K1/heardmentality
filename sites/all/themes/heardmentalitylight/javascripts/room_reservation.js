$(document).ready(function() {
  $(function() {
    var select = $( ".value-select .form-item select" );
    var slider = $( "<div id='slider'><span class='left'></span><span class='right'></span></div>" ).insertAfter( select ).slider({
      min: 1,
      max: 3,
      range: "min",
      value: select[ 0 ].selectedIndex + 1,
      slide: function( event, ui ) {
        select[ 0 ].selectedIndex = ui.value - 1;
      }
    });
    $( ".value-select .form-item select" ).change(function() {
      slider.slider( "value", this.selectedIndex + 1 );
    });
  });
});




