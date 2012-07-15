$(document).ready(function(){
  get_issues_solr(null, null, true);
  $('#search-solr-block').click(function(){  
    get_issues_solr();
    return false;
  });

  $('.solr-sort').live('click', function(){
    var sort = $(this).html();
    get_issues_solr(false, sort);
    return false;
  });
  
  
  $('.del-item').live('click', function(){
    var name = $(this).prev().attr('name');
    var value = $(this).prev().val();
    $(name).find("option[value="+value +"]").removeAttr("selected");
    $(this).parent().remove();
    return false;
  });
 
  $('#my_region').change(function(){
    if ($(this).prop('checked')) {
      $('#edit-block-country,#edit-block-defstate,#edit-block-defcity').attr('disabled',true);
    }
    else {
      $('#edit-block-country,#edit-block-defstate,#edit-block-defcity').attr('disabled',false);
    }
  });
  $('.pager-item a.active').live('click', function(){
    var page= $(this).html()- 1;
    get_issues_solr(page);
 
    return false;
  });
  
  
  function get_issues_solr(page, sort, all) {
    var text;
    if (all == null) {
      text = $('#edit-search-text').val();
    }
    var parameters = [];
    var allow_vote = $('#edit-voted-status').prop('checked');
    var tid = [];
    var categ = $('#edit-block-subject').val();
    var defarea = $('#edit-block-defarea').val();
    var defdetail = $('#edit-block-defdetail').val();
    var country = $('#edit-block-country').val();
    var state = $('#edit-block-defstate').val();
    var city = $('#edit-block-defcity').val();
    var my_region = $('#my_region').prop('checked');
    
    if (categ != null) {
      categ.map(function(index, element) {
        tid.push(index);
      });
      if (defarea != null) {
        defarea.map(function(index, element) {
          tid.push(index);
        });
        if (defdetail != null) {
          defdetail.map(function(index, element) {
            tid.push(index);
          });
        }
      }
    }
    parameters['tid']= tid;
    if (page) {
      var pageQ = '?page='+page;
    }
    else{
      pageQ = '';
    }
    
    $.post(Drupal.settings.base_url + '/issues_solr2/ajax/' + text + pageQ,
    {
      js: 1,
      page: page,
      tid: parameters['tid'],
      voted: allow_vote,
      sort: sort,
      country: country,
      city:city,
      myregion: my_region,
      state:state,
      all: all
      
    }, 
    function(data){
      //  $('#linkbox').html(data.data.regions.apachesolr_ajax);
      $('#linkbox').html(data.data);
      $('#count_results-wrapper span').html(data.count);
    },
    'json'
    );
  }

});