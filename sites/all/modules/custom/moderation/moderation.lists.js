$(document).ready(function () {
  // chosen!
  $(".chosen-mod").chosen();
  select_change();
});

/**
 * Fire event on lists update
 */
$(document).ready(function () {
  $('select.chosen-mod').change(function () {
    select_change()
  });
});

/**
 *
 */
function select_change() {
  // auto populate the categories/locations
  select_expand();
  select_hide();
}

/**
 * Hide empty selectors
 */
function select_hide() {
  $('select.chosen-mod.hideable').each(function() {
    if ($(this).find('option').length) {
      $(this).parent().show();
    } else {
      $(this).parent().hide();
    }
  });
}

/**
 * expand options
 */
var select_options = [];
function select_expand() {
  var mod = $('select.chosen-mod');
  // selected values
  var selected = [];
  mod.find(':selected').each(function(){
    selected.push($(this).val())
  });
  // selected tft
  select_options = selected;
  // expand the items
  var options = {};
  mod.each(function(ind,e) {

    var select = $(this);
    var i = parseInt(select.attr('id').replace(/.*-/,""));
    var prefix = select.hasClass('tft') ? '#edit-taxonomy-taxonomy-' : '#edit-location-location-';
    var data = select.hasClass('tft') ? Drupal.settings.tft : Drupal.settings.tfl;
    // items
    options = {};
    select.find(':selected').each(function(j,element) {
      if( typeof data[$(element).val()] != "undefined" ) {
        for (var index in data[$(element).val()]) {
          var term = data[$(element).val()][index];
          options[ term["id"] ] = term["name"] ;
        }
      }
    });

    var select2 = $( prefix+(i+1) );
    // remove old
    select2.find('option').remove();
    // add new
    for (var index in options) {
      select2.append(
        $('<option></option>')
          .val( index )
          .html( options[index] )
      );
    }
    // select options
    for (var i in select_options) {
      mod.find('option[value="'+ select_options[i] +'"]').prop('selected', true);
    }
  });

  // update chosen
  mod.trigger("liszt:updated");
}