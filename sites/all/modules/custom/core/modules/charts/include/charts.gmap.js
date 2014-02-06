/**
 *
 */
$(function () {
  if (Drupal.settings.charts.vote) init_gmap();
});

/**
 *
 */
function init_gmap() {
  var map;
  var selector = "map_div";
  var data = Drupal.settings.charts.gmap;
  if (data.length > 0) {
    var latitude;
    var longitude;

    // first vote
    latitude = data[0][0];
    longitude = data[0][1];

    // average
    latitude = 0;
    longitude = 0;
    for (var i=0; i<data.length; i++) {
      latitude += parseFloat(data[i][0]);
      longitude += parseFloat(data[i][1]);
    }
    latitude /= data.length;
    longitude /= data.length;

    // atlantic
    latitude = 35;
    longitude = -50;

    var myOptions = {
      zoom                    : 1,
      center                  : new google.maps.LatLng(latitude, longitude),
      mapTypeControl          : false,
      mapTypeControlOptions   : {style: google.maps.MapTypeControlStyle.DROPDOWN_MENU},
      navigationControl       : true,
      navigationControlOptions: {style: google.maps.NavigationControlStyle.SMALL},
      mapTypeId               : google.maps.MapTypeId.ROADMAP
    }
    map = new google.maps.Map(document.getElementById(selector), myOptions);

    // put the markers on map
    for (var i = 0; i < data.length; i++) {
      var beach = data[i];
      var myLatLng = new google.maps.LatLng(beach[0], beach[1]);
      var marker = new google.maps.Marker({
        position: myLatLng,
        map     : map,
        icon    : '/' + Drupal.settings.charts.gmap_icons + '/' + beach[2].replace('#', '') + '.png'
      })
    }
  }
}
