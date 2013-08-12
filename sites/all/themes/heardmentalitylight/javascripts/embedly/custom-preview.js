$(document).ready(function() {
  var embedly_api_key = '33ce8c309a2048ac91a4299762d8d260';
  $('.embedly').preview({
    key     : embedly_api_key,
    wrapper : '.embedly-wrapper',
    query: {
      wmode : 'opaque',
      words : 100,
      maxwidth : 2500
    }
  });
});