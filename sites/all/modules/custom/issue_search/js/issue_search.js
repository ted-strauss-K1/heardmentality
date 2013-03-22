/**
 * Search bindings.
 */
$('#issue-search-filter-form').live('submit', function (e) {
  e.preventDefault();
  issue_search();
  return false;
});

/**
 * Delete items from search info.
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
 * Sort and filter links.
 */
$('.date-solr-filter, .solr-sort').live('click', function (e) {
  e.preventDefault();
  var el = $(this);
  el.parents('ul').find('a').removeClass('active');
  el.addClass('active');
  issue_search();
  return false;
});

/**
 * Search on select click
 */
$('#issue-search-filter-form select').live('click', function (e) {
  e.preventDefault();
  issue_search();
  return false;
});

/**
 * Search on load
 */
$(document).ready(function () {
  issue_search();
});

/**
 * Returns search arguments.
 *
 * @return array
 *  A set of search arguments.
 */
function getSearchArguments() {

  // Date interval.
  var interval = $('ul.date-filter li a.date-solr-filter.active').attr('interval');

  // Solr sort.
  var sort = $('ul.sort-filter li a.solr-sort.active').attr('solrsort');
  var direction = $('ul.sort-filter li a.solr-sort.active').attr('direction');

  // Taxonomy.
  var taxonomy = [];
  $('select[id^="edit-block-taxonomy-"]').each(function () {
    $(this).find('option[selected="selected"]').each(function () {
      taxonomy.push($(this).val());
    });
  });
  taxonomy = taxonomy.join(';');

  // Locations.
  var codes = [];
  $('select[id="edit-block-location-0"]').find('option[selected="selected"]').each(function () {
    codes.push($(this).val());
  });
  var countryCodes = codes.join(';');
  codes = [];
  $('select[id="edit-block-location-1"]').find('option[selected="selected"]').each(function () {
    codes.push($(this).val());
  });
  var provinceCodes = codes.join(';');
  codes = [];
  $('select[id="edit-block-location-2"]').find('option[selected="selected"]').each(function () {
    codes.push($(this).val());
  });
  var cityCodes = codes.join(';');
  var myRegion = ($('#my_region').attr('checked') == 'checked') ? 'true' : 'false';

  // Language.
  var myLanguage = ($('#edit-my-language').attr('checked') == 'checked') ? 'true' : 'false';

  // Has votes.
  var onlyNotVoted = ($('#edit-voted-status').attr('checked') == 'checked') ? 'true' : 'false';

  // Key words.
  var keywords = $('#edit-search-text').val();

  var data = {
    'interval':interval,
    'solrsort':sort,
    'direction':direction,
    'taxonomy':taxonomy,
    'citycodes':cityCodes,
    'provincecodes':provinceCodes,
    'countrycodes':countryCodes,
    'my_region':myRegion,
    'my_language':myLanguage,
    'not_voted':onlyNotVoted,
    'keywords':keywords
  };

  return data;
}

/**
 * Search function.
 */
function issue_search() {
  var loader = $('#loading_wrapper');
  var linkbox = $('#linkbox');
  var issuesAmount = $('#count_results-wrapper span');

  // Show loader.
  linkbox.slideUp(500, function () {
    loader.slideDown(500)
  });

  $.ajax({
    type:'POST',
    dataType:'json',
    url:'/issues/ajax',
    data:getSearchArguments(),

    success:function (data) {
      if (!data.status) {
        $.hrd.noty({
          text:data.message,
          type:'error'
        });
        return false;
      }
      linkbox.html(data.message);
      issuesAmount.html(data.rows);

      return true;
    },

    complete:function () {
      loader.slideUp(500, function () {
        linkbox.slideDown(500)
      });
    }
  });
}
