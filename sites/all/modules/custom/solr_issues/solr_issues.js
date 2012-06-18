$(document).ready(function(){
  $('#search-solr-block').click(function(){
    var text = $('#edit-search-text').val();
    $.post(Drupal.settings.base_url + '/issues_solr2/ajax/' + text,
    {
      js: 1
    }, 
    function(data){
      //  $('#linkbox').html(data.data.regions.apachesolr_ajax);
      $('#linkbox').html(data.data);
    },
    'json'
    );
    return false;
  })

});