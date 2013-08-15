$('body').on('geocode', function(e) {
  geocode_get_location();
});

/**
 * Make a request to geonames using proxy
 *
 * @param location
 */
function geocode_request(location) {
  $.ajax({
    type      : 'POST',
    dataType  : 'json',
    url       : '/geocode',
    data      : location,
    success   : function (response) {
      // error
      if (!response.status) {
        $.hrd.noty({
          type  : 'error',
          text  : response.message
        });
        return false;
      }

    },
    complete:function () {
      //
    }
  });
}

/**
 * Function to ask access to location data
 */
function geocode_get_location() {
  navigator.geolocation.getCurrentPosition(geocode_request);
}