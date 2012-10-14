
/**
 * @file
 * Javascript for Goole Map widget of Geolocation field.
 */


/**
 * We have to add the files here because D6 does not let me load external js
 * WTF! Hated this but couldn't find a better solution.
 */
document.write("<script src='http://maps.google.com/maps/api/js?sensor=false'><\/script>");
document.write("<script src='http://www.google.com/jsapi'><\/script>");

// This is still pretty messy DEV-Code.
// TODO: cleanup.
(function ($) {

  var geocoder;
  Drupal.Geolocation = new Object();
  Drupal.Geolocation.maps = new Array();
  Drupal.Geolocation.markers = new Array();

  /**
   * Set the latitude and longitud values to the input fields
   * And optionaly update the address field
   *
   * @param latLng
   *   a location (latLng) object from google maps api
   * @param i
   *   the index from the maps array we are working on
   * @param op
   *   the op that was performed
   */
  function codeLatLng(latLng, i, op) {
    // Update the lat and lng input fields
    $('#lat-' + i + '-field input').attr('value', latLng.lat());
    $('#lng-' + i + '-field input').attr('value', latLng.lng());

    // When the map was clicked, update the address field
    if (op == 'mapclick' && geocoder) {
      geocoder.geocode({'latLng': latLng}, function(results, status) {
        if (status == google.maps.GeocoderStatus.OK) {
          $('#address-' + i + ' input').val(results[0].formatted_address);
          /*
          // Hide Debug output, cleanup later.
          $("#lat").html("<strong>Lat:</strong> "+latLng.lat());
          $("#lng").html("<strong>Lng:</strong> "+latLng.lng());
          var str = "";
          $.each(results, function(){
            str += "<h4>"+this.formatted_address+"</h4>";
            str += "types: "+this.types.join(", ")+"<br />";
            str += "address components: <ul>"
            $.each(this.address_components, function(){
              str +="<li>"+this.types.join(", ")+": "+this.long_name+"</li>";
            });
            str +="</ul>";
          });
          $("#geocode_info").html(str);
          */
        } else {
          alert(Drupal.t('Geocoder failed due to: ') + status);
        }
      });
    }
  }

  /**
   * Get the location from the address field
   *
   * @param i
   *   the index from the maps array we are working on
   */
  function codeAddress(i) {
    var address = $('#address-' + i + ' input').val();
    geocoder.geocode( { 'address': address }, function(results, status) {
      if (status == google.maps.GeocoderStatus.OK) {
        Drupal.Geolocation.maps[i].setCenter(results[0].geometry.location);
        setMapMarker(results[0].geometry.location, i);
        codeLatLng(results[0].geometry.location, i, 'textinput');
        if (results[0].geometry.location_type == 'APPROXIMATE') {
          Drupal.Geolocation.maps[i].setZoom(10);
        }
        else if (results[0].geometry.location_type == 'GEOMETRIC_CENTER') {
          Drupal.Geolocation.maps[i].setZoom(12);
        }
        else if (results[0].geometry.location_type == 'RANGE_INTERPOLATED' || results[0].geometry.location_type == 'ROOFTOP') {
          Drupal.Geolocation.maps[i].setZoom(16);
        }
      } else {
        alert(Drupal.t('Geocode was not successful for the following reason: ') + status);
      }
    });
  }
  
  /**
   * Set/Update a marker on a map
   *
   * @param latLng
   *   a location (latLng) object from google maps api
   * @param i
   *   the index from the maps array we are working on
   */
  function setMapMarker(latLng, i) {
    if (Drupal.Geolocation.markers[i]) {
      Drupal.Geolocation.markers[i].setMap(null);
    }
    Drupal.Geolocation.markers[i] = new google.maps.Marker({
      map: Drupal.Geolocation.maps[i],
      draggable: false,
      animation: google.maps.Animation.DROP,
      position: latLng
    });
    return false; // if called from <a>-Tag
  }

  /**
   * Get the current user location if one is given
   * @return
   *   Formatted location
   */
  function getFormattedLocation() {
    if (google.loader.ClientLocation.address.country_code == "US" &&
      google.loader.ClientLocation.address.region) {
      return google.loader.ClientLocation.address.city + ", " 
          + google.loader.ClientLocation.address.region.toUpperCase();
    } else {
      return  google.loader.ClientLocation.address.city + ", "
          + google.loader.ClientLocation.address.country_code;
    }
  }

  function clearLocation(i) {
    $('#lat-' + i + '-field input').attr('value', null);
    $('#lng-' + i + '-field input').attr('value', null);
    $('#address-' + i + ' input').attr('value', null);
    Drupal.Geolocation.markers[i].setMap();
  }

  function handleNoGeolocation(errorFlag) {
    var siberia = new google.maps.LatLng(60, 105);
    var newyork = new google.maps.LatLng(40.69847032728747, -73.9514422416687);
    if (errorFlag == true) {
      alert("Geolocation service failed.");
      initialLocation = newyork;
    } else {
      alert("Your browser doesn't support geolocation. We've placed you in Siberia.");
      initialLocation = siberia;
    }
    map.setCenter(initialLocation);
  }


  Drupal.behaviors.GoogleMap = function(context) {

    geocoder = new google.maps.Geocoder();

    var lat;
    var lng;
    var latLng;
    var myOptions;
    var browserSupportFlag =  new Boolean();

    $.each(Drupal.settings.map_defaults, function(i, e){

      $('#address-' + i + ' input').keypress(function(e){
        if(e.which == 13){
          e.preventDefault();
          codeAddress(i);
        }
      });
      $('#map-' + i + '-setaddress').click(function(e) {
        codeAddress(i);
      });

      $('#map-' + i + '-remove').click(function(e) {
        clearLocation(i);
      });

      // START: Autodetect clientlocation.
      // First use browser geolocation
      if(navigator.geolocation) {
        browserSupportFlag = true;
        $('#address-' + i + ' .description:not(.geolocation_processed)').addClass('geolocation_processed').append(Drupal.t(', or use your browser geolocation system by clicking this link') +': <b><span id="use-client-location-' + i + '">My Location</span></b>');
        // Set current user location, if available
        $('#use-client-location-' + i + ':not(.geolocation_processed)').addClass('geolocation_processed').click(function() {
          navigator.geolocation.getCurrentPosition(function(position) {
            latLng = new google.maps.LatLng(position.coords.latitude,position.coords.longitude);
            Drupal.Geolocation.maps[i].setCenter(latLng);
            setMapMarker(latLng, i);
            codeLatLng(latLng, i, 'mapclick');
          }, function() {
            handleNoGeolocation(browserSupportFlag);
          });
        });
      }
      // If browser geolication is not supoprted, try ip location
      else if (google.loader.ClientLocation) {
        latLng = new google.maps.LatLng(google.loader.ClientLocation.latitude, google.loader.ClientLocation.longitude);
        $('#address-' + i + ' .description:not(.geolocation_processed)').addClass('geolocation_processed').append(Drupal.t(', or use the IP-based location by clicking this link') +': <b><span id="use-client-location-' + i + '">' + getFormattedLocation() + '</span></b>');

        // Set current user location, if available
        $('#use-client-location-' + i + ':not(.geolocation_processed)').addClass('geolocation_processed').click(function() {
          if (google.loader.ClientLocation) {
            latLng = new google.maps.LatLng(google.loader.ClientLocation.latitude, google.loader.ClientLocation.longitude);
            $(".geolocation-input").val(getFormattedLocation());
            Drupal.Geolocation.maps[i].setCenter(latLng);
            setMapMarker(latLng, i);
            codeLatLng(latLng, i, 'mapclick');
          }
        });
      }
      // END: Autodetect clientlocation.

      // Get current/default values
      lat = $('#lat-' + i + '-field input').attr('value') == '' ? e.lat : $('#lat-' + i + '-field input').attr('value');
      lng = $('#lng-' + i + '-field input').attr('value') == '' ? e.lng : $('#lng-' + i + '-field input').attr('value');
      latLng = new google.maps.LatLng(lat, lng);

      // Set map options
      myOptions = {
        zoom: 7,
        center: latLng,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        scrollwheel: false
      }

      // Create map
      Drupal.Geolocation.maps[i] = new google.maps.Map(document.getElementById("map-" + i), myOptions);

      // Set initial marker
      codeLatLng(latLng, i, 'mapclick');
      setMapMarker(latLng, i);

      // Listener to set marker
      google.maps.event.addListener(Drupal.Geolocation.maps[i], 'rightclick', function(me){
        codeLatLng(me.latLng, i, 'mapclick');
        setMapMarker(me.latLng, i);
      });
    });
  }
})(jQuery);
