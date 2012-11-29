$(document).ready(function () {
  var map;
  var selector = "map_div";

  function initialize_gmap() {
    var data = Drupal.settings.charts.gmap;
    if (data.length > 0) {
      var latitude = data[0][0];
      var longitude = data[0][1];
      var myOptions = {
        zoom:1,
        center:new google.maps.LatLng(latitude, longitude),
        mapTypeControl:false,
        mapTypeControlOptions:{style:google.maps.MapTypeControlStyle.DROPDOWN_MENU},
        navigationControl:true,
        navigationControlOptions:{style:google.maps.NavigationControlStyle.SMALL},
        mapTypeId:google.maps.MapTypeId.ROADMAP
      }
      map = new google.maps.Map(document.getElementById(selector), myOptions);

      // put the markers on map
      for (var i = 0; i < data.length; i++) {
        var beach = data[i];
        var myLatLng = new google.maps.LatLng(beach[0], beach[1]);
        var marker = new google.maps.Marker({
          position:myLatLng,
          map:map,
          icon:Drupal.settings.base_url + '/' + Drupal.settings.google_map_icons + '/' + beach[2].replace('#', '') + '.png'
        })
      }
    }
  }

  initialize_gmap();
});