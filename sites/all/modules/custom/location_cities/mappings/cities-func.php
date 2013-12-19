<?php

$cities = array();

$path = dirname(__FILE__) . '/cities.txt';
$file = fopen($path, 'r');
while ($s = fgets($file)) {
  $s = trim($s, "\n\r");
  $item = explode("\t", $s);

  list($ccode, $pcode) = explode('_', strtolower($item[0]), 2);
  $cities[$ccode][$pcode][$item[1]] = $item[2];
}
fclose($file);

foreach ($cities as $ccode => $data) {
  $path = dirname(__FILE__) . '/supported/location.' . $ccode . '.inc';
  file_put_contents($path, "<?php\n\n");
  foreach ($data as $pcode => $list) {
    asort($list);
    $text = location_cities_function_text(location_cities_function_name($ccode . '_' . $pcode), $list);
    file_put_contents($path, $text . "\n\n", FILE_APPEND);
  }
}
