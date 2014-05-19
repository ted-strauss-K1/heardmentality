/**
 * Translate strings to the page language or a given language.
 *
 * See the documentation of the server-side t() function for further details.
 *
 * @param str
 *   A string containing the English string to translate.
 * @param args
 *   An object of replacements pairs to make after translation. Incidences
 *   of any key in this array are replaced with the corresponding value.
 *   Based on the first character of the key, the value is escaped and/or themed:
 *    - !variable: inserted as is
 *    - @variable: escape plain text to HTML (Drupal.checkPlain)
 *    - %variable: escape text and theme as a placeholder for user-submitted
 *      content (checkPlain + Drupal.theme('placeholder'))
 * @return
 *   The translated string.
 */
Drupal.tt = function (str, args) {
  // code
  var code = args['@code'];
  if (!code) {
    return str;
  }

  //
  if (args['@count']) {
    var count = args['@count'];
    delete args['@count'];
    var index = count != 1 ? 1 : 0; // todo locale_get_plural
    $args['@count[' + index + ']'] = count;
    return Drupal.tt(str.replace('@count', '@count[' + index + ']'), args);
  }

  // Fetch the localized version of the string.
  if (Drupal.settings.tt && Drupal.settings.tt[code] && Drupal.settings.tt[code][str]) {
    if (true !== Drupal.settings.tt[code][str]) {
      str = Drupal.settings.tt[code][str];
    }
  }

  if (args) {
    // Transform arguments before inserting them
    for (var key in args) {
      switch (key.charAt(0)) {
        // Escaped only
        case '@':
          args[key] = Drupal.checkPlain(args[key]);
          break;
        // Pass-through
        case '!':
          break;
        // Escaped and placeholder
        case '%':
        default:
          args[key] = Drupal.theme('placeholder', args[key]);
          break;
      }
      str = str.replace(key, args[key]);
    }
  }
  return str;
};
