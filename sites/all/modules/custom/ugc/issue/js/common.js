/*
 * Common functions for issues' pages
 */


/*
 * Google Translate API related functions
 */
function translate() {
  $('.goog-trans-control').html('');
  var lang = $("html").attr("lang");
  var s = document.createElement('script');
  s.type = 'text/javascript';
  s.src = '//translate.google.com/translate_a/element.js?cb=googleSectionalElementInit&ug=section&hl=' + lang;
  document.body.appendChild(s);
}
function googleSectionalElementInit() {
  new google.translate.SectionalElement({
    sectionalNodeClassName:'goog-trans-section',
    controlNodeClassName:'goog-trans-control',
    background:'#E1E43C'
  }, 'google_sectional_element');
}
