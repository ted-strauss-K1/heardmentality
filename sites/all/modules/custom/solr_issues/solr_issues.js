$(document).ready(function(){
  $('#search-solr-block').click(function(){
  
    get_issues_solr();
    return false;
  });
  /*
  $('.solr-block-form').live('change', function(){
    alert('hello');
  });
  $('.solr-block-form').change(function(){
    alert('hello1');
  });
*/


  $('.pager-item a.active').live('click', function(){
    var page= $(this).html()- 1;
    //   console.log(page);
    get_issues_solr(page);
 
    return false;
  });
  
  
  function get_issues_solr(page) {
    var text = $('#edit-search-text').val();
    var parameters = [];
    var tid = [];
    var categ = $('#edit-block-subject').val();
    var defarea = $('#edit-block-defarea').val();
    var defdetail = $('#edit-block-defdetail').val();
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
      tid: parameters['tid']
      
    }, 
    function(data){
      //  $('#linkbox').html(data.data.regions.apachesolr_ajax);
      $('#linkbox').html(data.data);
    },
    'json'
    );
  }

});