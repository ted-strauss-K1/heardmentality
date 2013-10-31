<?php

/**
 *
 */
function location_cities_menu() {
  $menu = array();

  $menu['admin/settings/location_cities/%'] = array(
    'page callback' => 'drupal_get_form',
    'page arguments' => array('location_cities_form', 3),
    'access arguments' => array('administer site configuration'),
  );

  $menu['lc'] = array(
    'page callback' => 'lc',
    'access arguments' => array('administer site configuration'),
  );

  return $menu;
}





function lc() {
  set_time_limit(0);
  db_query("TRUNCATE TABLE cache_location");

  $cols = array(
    'ccode',
    'gid',
    'geonames',
    'gmap',
    'name',
    'pop',
  );

  $path = dirname(__FILE__) . '/np_cities.txt';
  $file = fopen($path, 'r');
  while ($s = fgets($file)) {
    $s = trim($s, "\n\r");
    $item = explode("\t", $s);

    $item = array_combine($cols, $item);

    $filepath = dirname(__FILE__) . '/gmaps/'.$item['gid'].'.txt';
    if (file_exists($filepath)) {
       continue;
    }

    $result = drupal_http_request($item['gmap']);
    if ($result->data) {
      file_put_contents($filepath, $result->data);
    }
  }
  fclose($file);




}

function normalize ($string) {
  $table = array(
    'Š'=>'S', 'š'=>'s', 'Đ'=>'Dj', 'đ'=>'dj', 'Ž'=>'Z', 'ž'=>'z', 'Č'=>'C', 'č'=>'c', 'Ć'=>'C', 'ć'=>'c',
    'À'=>'A', 'Á'=>'A', 'Â'=>'A', 'Ã'=>'A', 'Ä'=>'A', 'Å'=>'A', 'Æ'=>'A', 'Ç'=>'C', 'È'=>'E', 'É'=>'E',
    'Ê'=>'E', 'Ë'=>'E', 'Ì'=>'I', 'Í'=>'I', 'Î'=>'I', 'Ï'=>'I', 'Ñ'=>'N', 'Ò'=>'O', 'Ó'=>'O', 'Ô'=>'O',
    'Õ'=>'O', 'Ö'=>'O', 'Ø'=>'O', 'Ù'=>'U', 'Ú'=>'U', 'Û'=>'U', 'Ü'=>'U', 'Ý'=>'Y', 'Þ'=>'B', 'ß'=>'Ss',
    'à'=>'a', 'á'=>'a', 'â'=>'a', 'ã'=>'a', 'ä'=>'a', 'å'=>'a', 'æ'=>'a', 'ç'=>'c', 'è'=>'e', 'é'=>'e',
    'ê'=>'e', 'ë'=>'e', 'ì'=>'i', 'í'=>'i', 'î'=>'i', 'ï'=>'i', 'ð'=>'o', 'ñ'=>'n', 'ò'=>'o', 'ó'=>'o',
    'ô'=>'o', 'õ'=>'o', 'ö'=>'o', 'ø'=>'o', 'ù'=>'u', 'ú'=>'u', 'û'=>'u', 'ý'=>'y', 'ý'=>'y', 'þ'=>'b',
    'ÿ'=>'y', 'Ŕ'=>'R', 'ŕ'=>'r', 'ő'=>'o', 'ō'=>'o', 'ī'=>'i', 'Ş'=>'S', 'ō'=>'o', 'ŏ'=>'o', 'Ķ'=>'K',
    'ķ'=>'k', 'ā'=>'a', 'ū'=>'u', 'ļ'=>'l', 'ă'=>'a', 'ē'=>'e', 'Ē'=>'E', 'ş'=>'s', '†'=>'t', 'ņ'=>'n',
    'ţ'=>'t', 'ḩ'=>'h', 'Ḩ'=>'H', 'Ţ'=>'T', 'Ż'=>'Z', 'ḑ'=>'d', 'ġ'=>'g', 'ü'=>'u', 'Ā'=>'A', 'ħ'=>'h',
    '̧'=>',', 'ə'=>'e',
  );

  return strtr($string, $table);
}







































/**
 *
 */
function location_cities_form() {
  $form = array();

  $form['#prefix'] = "<table><tr>" .
    "<td>Country Name</td>" .
    "<td>Country Code</td>" .
    "<td>Province Name</td>" .
    "<td>Province Code</td>" .
    "<td>Action</td>" .
  "</tr>";
  $form['#suffix'] = "</table>";
  $countries = location_get_iso3166_list();
  foreach ($countries as $ccode => $cname) {
    location_cities_load_file($ccode);
    $provinces = location_get_provinces($ccode);
    if ($provinces) {
      foreach ($provinces as $pcode => $pname) {
        location_standardize_province_code($pcode);
        $code = $ccode . '_' . $pcode;
        $func = location_cities_function_name($code);
        if (!function_exists($func)) {
          //
        }
      }
    }
  }

  return $form;
}

