/**
 * Search on load
 */
$(document).ready(function () {
  issue_search();
});

/**
 *
 */
function select_search_hide() {
  $('select.solr-block-form.hideable').each(function() {
    if ($(this).find('option').length) {
      $(this).parent().show();
    } else {
      $(this).parent().hide();
    }
  });
}

/**
 *
 */
var select_search_options_tft = [];
function select_search_expand() {
  // selected values
  var selected = [];
  $('select.tft :selected').each(function(){
    selected.push($(this).val())
  });
  // reduced/extended filter
  var value = false;
  for (var i in select_search_options_tft) {
    if (!jQuery.inArray(select_search_options_tft[i], selected)) {
      // reduce filter
      value = select_search_options_tft[i];
    }
  }
  // run the search when reduced
  if (false !== value) {
    issue_search();
  }
  // selected tft
  select_search_options_tft = selected;
  // update the filters
  $('select.tft.hideable option').remove();
  $('select.tft').each(function(i,e) {
    var select = $(this);
    select.find(':selected').each(function(j,element) {
      if( typeof Drupal.settings.tft[$(element).val()] != "undefined" ) {
        for (var index in Drupal.settings.tft[$(element).val()]) {
          $( '#edit-taxonomy-'+(i+1) ).append(
            $('<option></option>')
              .val( $(element).val() )
              .html( Drupal.settings.tft[$(element).val()][index]["name"] )
          );
        }
      }
    });
    // select options
    for (var i in select_search_options_tft) {
      $('select.tft option[value="'+ select_search_options_tft[i] +'"]').prop('checked', true);
    }
  });


  $('select.solr-block-form').trigger("liszt:updated");

}

/**
 * Fire event on lists update
 */
$(document).ready(function () {
  //
  select_search_hide();

  var select_search_delay_default = 5000, // ms
      select_search_delay_timer = false,
      select_search_delay = select_search_delay_default;
  $('select.solr-block-form')
    .on("liszt:updated", function() {
      // issue_search();
    })
    .change(function () {
      // auto populate the categories/locations
      select_search_expand();
      select_search_hide();

      // auto search after delay
      select_search_delay = select_search_delay_default;
      clearInterval(select_search_delay_timer);
      select_search_delay_timer = setInterval(function() {
        select_search_delay -= 1000;
        if (0 >= select_search_delay) {
          issue_search();
          clearInterval(select_search_delay_timer);
        }
      }, 1000);
    });

});


















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



$('.search-pager-link').live('click', function () {
  $('input[name=page]').val($(this).attr('name'));
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

  // Key words.
  var page = $('input[name=page]').val();

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
    'keywords':keywords,
    'page':page
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
//  linkbox.slideUp(500, function () {
    loader.slideDown(500)
//  });

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
//        linkbox.slideDown(500)
      });
    }
  });
}
