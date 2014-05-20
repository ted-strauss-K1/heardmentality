<?php

// location_path() - path to location module core dir


set_time_limit(0);
db_query("TRUNCATE TABLE cache_location");

$path = 'regions.txt';
$file = fopen($path, 'r');

$regions = array();
while ($s = fgets($file)) {
  $item = explode("\t", $s);
  $regions[strtolower($item[0])][$item[1]] = $item[2];
}

foreach ($regions as $code => $list) {
  file_put_contents(location_path() . 'location.' . $code . '.inc', "<?php\n\n", FILE_APPEND);
  file_put_contents(location_path() . 'location.' . $code . '.inc', location_cities_function_text('location_province_list_' . $code, $list), FILE_APPEND);
}

fclose($file);
