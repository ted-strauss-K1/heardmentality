$(document).ready(function() {
  var map;
  function initialize() {
    $.getJSON(Drupal.settings.base_url + '/issue/gmap/ajax/'+ nid, function(data) {
      var beaches = [];
      var latitude, longitude;
      $.each(data, function(key, val) {
        for (i in val) {
          //  beaches.push(val[i].latitude, val[i].longitude);
          beaches[i]= [val[i].latitude, val[i].longitude];
        }
        latitude = val[0].latitude;
        longitude = val[0].longitude;
      });
    
      
  
      var myLatlng = new google.maps.LatLng(latitude, longitude);
      var myOptions = {
        zoom: 0,
        center: myLatlng,
        mapTypeId: google.maps.MapTypeId.ROADMAP
      }
      map = new google.maps.Map(document.getElementById("map_div"), myOptions);
      var nid = $('#curr_nid').val();
      
      setMarkers(map, beaches);
    });
  }
  
  function setMarkers(map, locations) {
    for (var i = 0; i < locations.length; i++) {
      var beach = locations[i];
      var myLatLng = new google.maps.LatLng(beach[0], beach[1]);
      var marker = new google.maps.Circle({
        strokeColor: "#FF0000",
        strokeOpacity: 0.8,
        strokeWeight: 2,
        fillColor: "#FF0000",
        fillOpacity: 0.35,
        map: map,
        center: myLatLng,
        radius: 10000
      });
    }
  }
  initialize();
});