/**
 * Search on load
 */
$(document).ready(function () {
  // search on load
  issue_search_page_clean();
  issue_search();

  // chosen!
  $(".chzn-select").chosen();

  // hide empty selects
  select_search_hide();
});


function issue_search_page_clean() {
  $('input[name=page]').val(1);
}

/**
 * Search on submit
 */
$('#issue-search-filter-form').live('submit', function (e) {
  e.preventDefault();
  clearInterval(select_search_delay_timer);
  issue_search_page_clean();
  issue_search();
  return false;
});

/**
 * Pager
 */
$('.search-pager-link').live('click', function () {
  $('input[name=page]').val($(this).attr('name'));
  issue_search();
});

/**
 * Sort and filter links
 */
$('.date-solr-filter, .solr-sort').live('click', function (e) {
  e.preventDefault();
  var el = $(this);
  el.parents('ul').find('a').removeClass('active');
  el.addClass('active');
  issue_search_page_clean();
  issue_search();
  return false;
});

/**
 *
 */
$('#my_region').live('change', function() {
  if($(this).prop('checked') && (typeof Drupal.settings.tfl_user != "undefined")) {
    var tfl_user = $('select.tfl option[value="'+Drupal.settings.tfl_user+'"]');
    if (tfl_user.length) {
      $('select.tfl :selected').prop('selected', false);
      tfl_user.prop('selected', true);
    } else {
      $.hrd.noty({
        text: Drupal.t('No issues for you region'),
        type:'error'
      });
      $(this).prop('checked', false)
    }
  }
});

/**
 * Fire event on lists update
 */
$(document).ready(function () {
  $('select.solr-block-form').change(function () {
    select_search_change()
  });
});

/**
 *
 */
var select_search_delay_default = 3000, // ms
  select_search_delay_timer = false,
  select_search_delay = select_search_delay_default;
function select_search_change() {
  // auto populate the categories/locations
  var output = select_search_expand();
  select_search_hide();

  if (!output) return;

  // auto search after delay
  select_search_delay = select_search_delay_default;
  clearInterval(select_search_delay_timer);
  select_search_delay_timer = setInterval(function() {
    select_search_delay -= 1000;
    if (0 >= select_search_delay) {
      issue_search_page_clean();
      issue_search();
      clearInterval(select_search_delay_timer);
    }
  }, 1000);
}

/**
 * Hide empty selectors
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
 * search
 */
var select_search_options = [];
function select_search_expand() {
  var output = false;

  // selected values
  var selected = [];
  $('select.solr-block-form :selected').each(function(){
    selected.push($(this).val())
  });
  // reduced/extended filter
  var value = false;
  for (var i in select_search_options) {
    if (!jQuery.inArray(select_search_options[i], selected)) {
      // reduce filter
      value = select_search_options[i];
    }
  }
  // run the search when reduced
  if (false !== value) {
    output = true;
  } else {
    // filter with no search - not a good idea at the moment
//    $('select.tft :selected').each(function(){
//      $('.search_item.tft-'+$(this).val()).addClass('keep');
//    });
//    $('select.tfl :selected').each(function(){
//      $('.search_item.tfl-'+$(this).val()).addClass('keep');
//    });
//    $('.search_item:not(.keep)').slideUp(500);
//    $('.search_item').removeClass('keep');
    output = true;
  }
  // selected tft
  select_search_options = selected;
  // expand the items
  var options = {};
  $('select.solr-block-form').each(function(ind,e) {
    var select = $(this);
    var i = parseInt(select.attr('id').replace(/.*-/,""));
    var prefix = select.hasClass('tft') ? '#edit-taxonomy-' : '#edit-location-';
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
    for (var i in select_search_options) {
      $('select.solr-block-form option[value="'+ select_search_options[i] +'"]').prop('selected', true);
    }
  });

  // update chosen
  $('select.solr-block-form').trigger("liszt:updated");

  // save state to cookies
  search_arguments();

  return output;
}

/**
 *
 */
function search_arguments() {
  var data = {};

  // date interval
  data['interval'] = $('ul.date-filter li a.date-solr-filter.active').attr('interval');

  // sort
  data['sort'] = $('ul.sort-filter li a.solr-sort.active').attr('solrsort');
  data['direction'] = $('ul.sort-filter li a.solr-sort.active').attr('direction');

  // taxonomy
  var taxonomy = [];
  $('select[id^="edit-taxonomy-"] :selected').each(function () {
    taxonomy.push($(this).val());
  });
  data['taxonomy'] = taxonomy.join(';');

  // locations
  var codes = [];
  $('select[id="edit-location-0"] :selected').each(function () {
    codes.push($(this).val());
  });
  data['location1'] = codes.join(';');

  codes = [];
  $('select[id="edit-location-1"] :selected').each(function () {
    codes.push($(this).val());
  });
  data['location2'] = codes.join(';');

  codes = [];
  $('select[id="edit-location-2"] :selected').each(function () {
    codes.push($(this).val());
  });
  data['location3'] = codes.join(';');

  // my region
  data['my_region'] = $('#my_region').prop('checked')+'';

  // my language
  data['my_language'] = 'false';

  // voted status
  data['not_voted'] = $('#edit-voted-status').prop('checked')+'';

  // keyword
  data['keywords'] = $('#edit-search-text').val();

  // page
  data['page'] = $('input[name=page]').val();

  // Key words.
  var page = $('input[name=page]').val();

  $.cookie('search_arguments', JSON.stringify(data), { expires: 7, path: '/' } );

  return data;
}

/**
 * Search function.
 */
function issue_search() {
  var loader = $('#loading_wrapper');
  var linkbox = $('#linkbox');
  var issuesAmount = $('#count_results-wrapper span');

  // Show loader
  loader.slideDown(500);

  $.ajax({
    type      : 'POST',
    dataType  : 'json',
    url       : '/issues/ajax',
    data      : search_arguments(),
    success   : function (response) {
      if (!response.status) {
        $.hrd.noty({
          text:response.message,
          type:'error'
        });
        return false;
      }

      linkbox.html(response.message);
      issuesAmount.html(response.rows);
      expander();

      return true;
    },

    complete:function () {
      loader.slideUp(500);
    }
  });
}



$('.issue-search-more').live('click', function() {
  var $$ = $(this);
  // get page
  var page_to_show = parseInt($('input[name=page]').val()) + 1;
  $('input[name=page]').val(page_to_show);

  // activate
  $$.toggleClass('active');

  // search
  $.ajax({
    type      : 'POST',
    dataType  : 'json',
    url       : '/'+Drupal.settings.language+'/issues/ajax',
    data      : search_arguments(),
    success   : function (response) {
      if (!response.status) {
        $.hrd.noty({
          text:response.message,
          type:'error'
        });
        return false;
      }

      //
      $$.before(response.message);
      $$.toggleClass('active');
      $$.remove();

      expander();
      return true;
    }
  });
});

$(window).scroll(function(){
  if (jQuery.browser.mobile) {
    return;
  }
  var searchmore = $('.issue-search-more');
  if (searchmore && !searchmore.hasClass('active') && searchmore.offset()) {
    if ($(window).scrollTop() + 0.75*$(window).height() >= searchmore.offset().top) {
      // position is right
      searchmore.trigger('click');
    }
  }
});
