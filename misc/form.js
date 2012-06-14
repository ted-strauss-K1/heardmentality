Drupal.behaviors.multiselectSelector = function() {
  $.shell.find('.multiselect select:not(.multiselectSelector-processed)')
    .addClass('multiselectSelector-processed').change(function() {
      $.shell.find('.multiselect input:radio[value="'+ this.id.substr(5) +'"]')
        .attr('checked', true);
  });
};
