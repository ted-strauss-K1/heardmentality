$(document).ready(function () {
  expander();
});

function expander() {
  $('div.expander').each(function () {
    $(this).expander({
      'expandText'      : '<span class="expander-control expander-more">more</span>', // todo translate
      'expandSpeed'     : 1000,
      'userCollapseText': '<span class="expander-control expander-less">less</span>', // todo translate
      'slicePoint'      : $(this).attr('data-chars') ? $(this).attr('data-chars') : 2500
    });
  });
}
