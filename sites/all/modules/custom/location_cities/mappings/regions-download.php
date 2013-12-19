<?php

set_time_limit(0);
db_query("TRUNCATE TABLE cache_location");

// todo include list from "countries.php"

foreach ($list as $code => $items) {
  $path = dirname(__FILE__) . '/regions/' . $code . '.html';
  if (file_exists($path)) {
    continue;
  }

  $href = 'http://www.geonames.org/' . $code . '/administrative-division-' . preg_replace('/^.*\/([a-z\-]+[a-z]).*$/', "$1", $items['href']) . '.html';
  if ($result = drupal_http_request($href)) {
    file_put_contents($path, $result->data);
  }
}
