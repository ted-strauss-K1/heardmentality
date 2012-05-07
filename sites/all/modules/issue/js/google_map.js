$(document).ready(function() {
  var map;
  function initialize() {
    var myLatlng = new google.maps.LatLng(-25.363882,131.044922);
    var myOptions = {
      zoom: 0,
      center: myLatlng,
      mapTypeId: google.maps.MapTypeId.ROADMAP
    }
    map = new google.maps.Map(document.getElementById("map_div"), myOptions);
    var nid = $('#curr_nid').val();
    var beaches = [];
    $.getJSON('/issue/gmap/ajax/'+ nid, function(data) {
      console.log(data);
      $.each(data, function(key, val) {
        for (i in val) {
          //  beaches.push(val[i].latitude, val[i].longitude);
          beaches[i]= [val[i].latitude, val[i].longitude];
        }
      });
    
  
      console.log(beaches);
      setMarkers(map, beaches);
    });
  }
  
  function setMarkers(map, locations) {
    for (var i = 0; i < locations.length; i++) {
      var beach = locations[i];
      var myLatLng = new google.maps.LatLng(beach[0], beach[1]);
      var marker = new google.maps.Marker({
        position: myLatLng,
        map: map
      });
    }
  }
  initialize();
});