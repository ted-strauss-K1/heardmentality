<?php


function normalize($string) {
  $table = array(
    'S' => 'S',
    's' => 's',
    'D' => 'Dj',
    'd' => 'dj',
    'Z' => 'Z',
    'z' => 'z',
    'C' => 'C',
    'c' => 'c',
    'C' => 'C',
    'c' => 'c',
    'A' => 'A',
    'A' => 'A',
    'A' => 'A',
    'A' => 'A',
    'A' => 'A',
    'A' => 'A',
    '?' => 'A',
    'C' => 'C',
    'E' => 'E',
    'E' => 'E',
    'E' => 'E',
    'E' => 'E',
    'I' => 'I',
    'I' => 'I',
    'I' => 'I',
    'I' => 'I',
    'N' => 'N',
    'O' => 'O',
    'O' => 'O',
    'O' => 'O',
    'O' => 'O',
    'O' => 'O',
    'O' => 'O',
    'U' => 'U',
    'U' => 'U',
    'U' => 'U',
    'U' => 'U',
    'Y' => 'Y',
    '?' => 'B',
    '?' => 'Ss',
    'a' => 'a',
    'a' => 'a',
    'a' => 'a',
    'a' => 'a',
    'a' => 'a',
    'a' => 'a',
    '?' => 'a',
    'c' => 'c',
    'e' => 'e',
    'e' => 'e',
    'e' => 'e',
    'e' => 'e',
    'i' => 'i',
    'i' => 'i',
    'i' => 'i',
    'i' => 'i',
    '?' => 'o',
    'n' => 'n',
    'o' => 'o',
    'o' => 'o',
    'o' => 'o',
    'o' => 'o',
    'o' => 'o',
    'o' => 'o',
    'u' => 'u',
    'u' => 'u',
    'u' => 'u',
    'y' => 'y',
    'y' => 'y',
    '?' => 'b',
    'y' => 'y',
    'R' => 'R',
    'r' => 'r',
    'o' => 'o',
    'o' => 'o',
    'i' => 'i',
    'S' => 'S',
    'o' => 'o',
    'o' => 'o',
    'K' => 'K',
    'k' => 'k',
    'a' => 'a',
    'u' => 'u',
    'l' => 'l',
    'a' => 'a',
    'e' => 'e',
    'E' => 'E',
    's' => 's',
    '�' => 't',
    'n' => 'n',
    't' => 't',
    '?' => 'h',
    '?' => 'H',
    'T' => 'T',
    'Z' => 'Z',
    '?' => 'd',
    'g' => 'g',
    'u' => 'u',
    'A' => 'A',
    'h' => 'h',
    '?' => ',',
    '?' => 'e',
  );

  return strtr($string, $table);
}

set_time_limit(0);
db_query("TRUNCATE TABLE cache_location");

// todo include list from "countries.php"

$data = array();
$data1 = array();
$data2 = array();

foreach ($list as $code => $items) {
  $path = dirname(__FILE__) . '/regions/' . $code . '.html';
  if (!file_exists($path)) {
    continue;
  }

  $needle = '<th>Fips</th><th>GN</th><th>Name of Subdivision</th><th>Type</th><th>Capital</th><th>Population</th><th>area in km&sup2;</th><th>lang</th><th>continent</th><th>From</th><th>Till</th></tr>';

  $file = fopen($path, 'r');
  $in = FALSE;
  while ($s = fgets($file)) {
    if ($in) {
      if (FALSE !== strpos($s, '</table>')) {
        break;
      }
      if (!preg_match_all('/<td[^\>]*>(.*)<\/td>/U', $s, $m)) {
        continue;
      }

      $item = array_combine($cols, $m[1]);
      $item["iso"] = strip_tags($item["ISO-3166-2"]);
      $item["type"] = strip_tags($item["Type"]);
      $name = $item["Name of Subdivision"];
      if (preg_match('/<a href=\"http:\/\/www\.geonames\.org\/(\d+)\/[^\"]*\">([^\<]+)<\/a>/', $name, $m)) {
        $item['gid'] = $m[1];
        $item['name'] = $m[2];
      }
      else {
        $name = strip_tags($name);
        $item['name'] = trim($name);
      }

      if ($item['iso'] && $item['name']) {
        $data[$code][$item['iso']] = $item;
        if (!$item['gid']) {
          $data1[$code][] = $item + array('s' => $s);
        }
      }
      else {
        $data2[$code][] = $item + array('s' => $s);
      }
    }

    if (FALSE !== strpos($s, $needle)) {
      $in = TRUE;
      preg_match_all('/<th>(.*)<\/th>/U', $s, $m);
      $cols = $m[1];
    }

  }


  foreach ($data as $code => $items) {
    foreach ($items as $item) {
      $name = $item['name'];
      $name = normalize($name);

      $iso = $item['iso'];
      $gid = $item['gid'];

      file_put_contents('./regions.txt', "$code\t$iso\t$name\t$gid\n", FILE_APPEND);
    }
  }


  fclose($file);
