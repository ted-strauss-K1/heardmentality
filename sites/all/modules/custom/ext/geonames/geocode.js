/**
 * Listeners
 */
$('body').on('geocode.latlng', function(e) {
  geocode_latlng();
}).on('geocode.postalcode', function(e, countrycode, postalcode) {
  geocode_postalcode(countrycode, postalcode);
});

/**
 * Function to ask access to location data
 */
function geocode_latlng() {
  navigator.geolocation.getCurrentPosition(geocode_request);
}

/**
 * Function to determine the location using country code and postal code
 *
 * @param countrycode
 * @param postalcode
 */
function geocode_postalcode(countrycode, postalcode) {
  geocode_request({
    'countrycode' : countrycode,
    'postalcode'  : postalcode
  });
}

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
      $('body').trigger('geocode.success', [response.location]);
    },
    complete:function () {
      //
    }
  });
}