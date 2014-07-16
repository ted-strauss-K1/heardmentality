<?php

/**
 * This function is a wrapper for the t-function
 *
 * @param       $string
 * @param array $args
 * @param null  $langcode
 *
 * @see t()
 * @see format_plural()
 *
 * @return null|string
 */
if (!function_exists('__')) {
  function __($string, $args = array(), $langcode = NULL) {
    // detect language
    if (is_null($langcode)) {
      global $language;
      $langcode = $language->language;
    }

    // detect code
    if (!isset($args['@code'])) {
      $args['@code'] = 'nocode';
      $args['@textgroup'] = 'nocode';
    }

    // detect textgroup
    if (!isset($args['@textgroup'])) {
      $args['@textgroup'] = 'default';
    }

    // check if this text allows plurality (has @count arg)
    if (isset($args['@count'])) {
      $count = $args['@count'];
      unset($args['@count']);
      $index = (function_exists('locale_get_plural')) ? locale_get_plural($count, $langcode) : -1;
      $args['@count[' . $index . ']'] = $count;
      return __(strtr($string, array('@count' => '@count[' . $index . ']')), $args, $langcode);
    }

    //
    return tt_t($string, $args, $langcode);
  }

  /**
   * @param       $code
   * @param array $args
   * @param null  $langcode
   *
   * @return null|string
   */
  function __t($code, $args = array(), $langcode = NULL) {
    if (is_string($args)) {
      $args = array('@default' => $args);
    }
    else {
      $args['@default'] = isset($args['@default']) ? $args['@default'] : '';
    }
    return __($args['@default'], array('@code' => $code) + $args, $langcode);
  }
}

/**
 * Analogue of t-function that can translate textgroup != 'default'
 *
 * @param       $string
 * @param array $args
 * @param null  $langcode
 *
 * @return null|string
 */
function tt_t($string, $args = array(), $langcode = NULL) {
  // detect language
  if (is_null($langcode)) {
    global $language;
    $langcode = $language->language;
  }

  // allow changing default translations
  // if ($langcode != 'en') {
  $string = tt_locale($string, $args, $langcode);
  // }

  //
  if (empty($args)) {
    return $string;
  }
  else {
    // Transform arguments before inserting them.
    foreach ($args as $key => $value) {
      switch ($key[0]) {
        case '@':
          // Escaped only.
          $args[$key] = check_plain($value);
          break;

        case '%':
        default:
          // Escaped and placeholder.
          $args[$key] = theme('placeholder', $value);
          break;

        case '!':
          // Pass-through.
      }
    }
    return strtr($string, $args);
  }
}

/**
 *
 */
define('TT_PREFIX', 'tt');

/**
 * @param       $string
 * @param array $args
 * @param null  $langcode
 * @param bool  $reset
 *
 * @return mixed
 */
function tt_locale($string, $args = array(), $langcode = NULL, $reset = FALSE) {
  // detect language
  if (is_null($langcode)) {
    global $language;
    $langcode = $language->language;
  }

  // static
  static $locale = array();

  // code && textgroup
  $code = $args['@code'];
  $textgroup = $args['@textgroup'];

  // reset
  if ($reset) {
    $locale = array();
    cache_clear_all(TT_PREFIX . ':', 'cache', TRUE);
  }

  // load caches
  if (!isset($locale[$langcode][$textgroup])) {
    $locale[$langcode][$textgroup] = array();

    $cache_id = TT_PREFIX . ':' . $langcode . ':' . $textgroup;

    //
    if ($cache = cache_get($cache_id, 'cache')) {
      $locale[$langcode][$textgroup] = $cache->data;
    }

    //
    elseif (lock_acquire($cache_id)) {
      // cache data
      $query = "
        SELECT s.source, t.translation, t.language, s.code
        FROM {locales_source} s
        LEFT JOIN {locales_target} t ON s.lid = t.lid AND t.language = '%s'
        WHERE s.version = '%s' AND s.textgroup = '%s'";
      if ('default' == $textgroup) {
        $query .= " AND LENGTH(s.source) < 75";
      }
      $result = db_query($query, $langcode, VERSION, $textgroup);

      // cache data to static var
      while ($data = db_fetch_object($result)) {
        $locale[$langcode][$textgroup][$data->code][$data->source] = (empty($data->translation) ? TRUE : $data->translation);
      }

      // cache data to database
      cache_set($cache_id, $locale[$langcode][$textgroup]);
      lock_release($cache_id);
    }
  }

  //
  if (is_null($string)) {
    return $locale[$langcode][$textgroup];
  }

  // check database if not found
  if (!isset($locale[$langcode][$textgroup][$code][$string])) {
    //
    $query = "
      SELECT s.source, t.translation, t.language, s.code
      FROM {locales_source} s
      LEFT JOIN {locales_target} t ON s.lid = t.lid AND t.language = '%s'
      WHERE s.version = '%s' AND s.textgroup = '%s' AND s.code = '%s'";
    $translation = db_fetch_object(db_query($query . " AND s.source = '%s'", $langcode, VERSION, $textgroup, $code, $string));
    if ($translation) {
      $locale[$langcode][$textgroup][$code][$string] = (empty($translation->translation) ? TRUE : $translation->translation);
      if ($translation->version != VERSION) {
        db_query("UPDATE {locales_source} SET version = '%s' WHERE lid = %d", VERSION, $translation->lid);
        cache_clear_all(TT_PREFIX . ':', 'cache', TRUE);
      }
    }
    else {
      // create
      $object = array(
        'code'      => $code,
        'source'    => $string,
        'textgroup' => $textgroup,
        'location'  => request_uri(),
        'version'   => VERSION,
      );
      drupal_write_record('locales_source', $object);
      $locale[$langcode][$textgroup][$code][$string] = TRUE;
      cache_clear_all(TT_PREFIX . ':', 'cache', TRUE);
    }
  }

  return $locale[$langcode][$textgroup][$code][$string] === TRUE ? $string : $locale[$langcode][$textgroup][$code][$string];
}