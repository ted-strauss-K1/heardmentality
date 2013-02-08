/**
 * Search function
 */
function issue_search() {
  var loader = $('#loading_wrapper');
  var linkbox = $('#linkbox');
  // show loader
  linkbox.slideUp(500, function () {
    loader.slideDown(500)
  });
  var form = $('#issue-search-filter-form');
  $.ajax({
    type:'POST',
    dataType:'json',
    url:'/'+Drupal.settings.language+'/issues/ajax',
    data:form.serialize(),
    success:function (response) {
      if (!response.status) {
        $.hrd.noty({text:response.message, type:'error'});
        return false;
      }
      //
      linkbox.html(response.message);

      return true;
    },
    complete:function () {
      loader.slideUp(500, function () {
        linkbox.slideDown(500)
      });
    }
  });
}

/**
 * Search form filter submit
 */
$('#issue-search-filter-form').live('submit', function (e) {
  e.preventDefault();
  issue_search();
  return false;
});

/**
 * Delete items from search info
 */
$('.del-item').live('click', function () {
  var el = $(this).siblings('input');
  var name = el.attr('name');
  var value = el.val();
  $(name).find("option[value=" + value + "]").removeAttr("selected").trigger('change');
  if (name.match('location')) {
    $('#my_region').attr("checked", false).trigger('change');
  }
  $(this).parent().remove();
  return false;
});

/**
 * Sorting functions
 */
$('.date-solr-filter, .solr-sort').live('click', function (e) {
  e.preventDefault();
  var el = $(this);
  el.parents('ul').find('a').removeClass('active');
  el.addClass('active');
});

/**
 * Search on load
 */
$(document).ready(function () {
  // todo maybe prepare form for the first run
  issue_search();
});