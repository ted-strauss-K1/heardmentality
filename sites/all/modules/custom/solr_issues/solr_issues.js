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
  Drupal.apachesolr_ajax = {};
  Drupal.apachesolr_ajax.response_callback = function (data) {
    for (var setting in data.settings) {
      Drupal.settings[setting] = data.settings[setting];
    }

    var list = [];

    // Schedule items for removal to reduce page jumpiness.
    if (blocks) {
      for (var block in blocks) {
        list.push($(blocks[block]));
      }
    }
    for (var region in data.regions) {
      if (region == 'apachesolr_ajax') {
        if (content) {
          var elements = $(data.regions[region]);
          Drupal.attachBehaviors(elements.appendTo($(content).empty()));
        }
      }
      else {
        for (var block in data.regions[region]) {
          if (regions[region] && blocks[block]) {
            var elements = $(data.regions[region][block]);
            Drupal.attachBehaviors(elements.appendTo(regions[region]));
          }
        }
      }
    }
    for (var i = 0, l = list.length; i < l; i++) {
      list[i].remove();
    }
  };
});