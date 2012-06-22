$(document).ready(function(){
  $('#search-solr-block').click(function(){
    var text = $('#edit-search-text').val();
    var tid = [];
    var categ = $('#edit-category-subject').val();
    var defarea = $('#edit-category-defarea').val();
    var defdetail = $('#edit-category-defdetail').val();
    // tid = $('#edit-category-subject').val() + $('#edit-category-defarea').val() + $('#edit-category-defdetail').val();
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

    $.post(Drupal.settings.base_url + '/issues_solr2/ajax/' + text,
    {
      js: 1,
      tid: tid
    }, 
    function(data){
      //  $('#linkbox').html(data.data.regions.apachesolr_ajax);
      $('#linkbox').html(data.data);
    },
    'json'
    );
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
});