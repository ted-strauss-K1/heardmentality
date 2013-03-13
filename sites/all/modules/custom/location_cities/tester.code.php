<?php

function tester_boot()
{

}

function tester_init()
{


}

function tester_menu()
{
  return array(
    'tester' => array(
      'page callback' => 'tester',
      'type' => MENU_CALLBACK,
      'access callback' => true,
    ),
  );
}

function __($t, $p = '')
{
  static $pref;
  if ($p) {
    $pref = $p;
    return;
  }

  $f = fopen("D:/out/prov.$pref.txt", 'a+');
  fwrite($f, $t . "\n");
  fclose($f);
}

function tester_countrycode_rewrite($code)
{
  switch ($code) {
    case 'uk':
      return 'gb';
    case 'cs':
      return 'rs';
    default:
      return $code;
  }
}

function tester_prepare_gid($gid, $x = ' ')
{
  if (strlen($gid) == 8) return $gid;
  else return str_repeat($x, 8 - strlen($gid)) . $gid;
}


function tester_compare_province($ccode, $data)
{
  __('', $ccode);
  $provs = location_get_provinces($ccode);
  $names = array();
  foreach ($data as $item) {
    $names[str_replace(' province', '', $item['#name'])] = $item['#gid'];
  }
//  var_dump($names);


  $found = array();
  foreach ($provs as $code => $name) {
    $name = str_replace(' province', '', $name);
    if (isset($names[$name])) {
      __(tester_prepare_gid($names[$name]) . ' ' . $ccode . '_' . $code);
      $found[] = $code;
      unset($names[$name]);
    }
//    } else {
//      __(str_repeat('*',8) . ' ' . $ccode . '_' . $code);
//    }
  }

  ksort($names);

  foreach ($provs as $code => $name) {
    if (in_array($code, $found)) continue;
    $name = str_replace(' province', '', $name);
    $t = ' ' . $ccode . '_' . $code;

    $sname2 = '';
    $sgid = '';
    $min = 100;
    foreach ($names as $name2 => $gid) {
      $v = levenshtein($n1 = strtolower($name), $n2 = strtolower($name2));
//      __($v . ' == ' . $n1 . ' <<>> ' .$n2 );
      if ($min > $v) {
        $sname2 = $name2;
        $sgid = $gid;
        $min = $v;
      }
    }

    $t .= '  :::  ' . $name . ' ~ ' . $sname2 . '(' . $sgid . ')';
    $t = tester_prepare_gid($sgid, '*') . $t;
    __($t);
  }
  if (empty($names)) {
    return;
  }
  __('');
  __('NAMES:::::');
  __('');

  foreach ($names as $name2 => $gid) {
    __($name2 . '(' . $gid . ') ');
  }
//  __('');
//  __('');
}

function tester()
{
  set_time_limit(0);
  $data = unserialize(file_get_contents("D:/dump.txt"));

  $path = "D:/dev/vhosts/hm2/" . drupal_get_path("module", "location_cities");

  $list = scandir($path . '/geonames_mappings');
  foreach ($list as $file) {
    if (!preg_match('/^\.+$/', $file)) {
      echo $file . "\n";
      $f = fopen($path . '/geonames_mappings/' . $file, 'r');
      $code = preg_replace('/(prov\.|\.txt)/', "", $file);
//      if ($code != 'us') continue;
      if ($put) {
        @fclose($put);
      }
      if (file_exists($path . '/supported/location.' . $code . '.inc')) continue;
      $put = fopen($path . '/supported/location.' . $code . '.inc', 'a+');
      fwrite($put, "<?php\n\n");
      while ($s = fgets($f)) {
        if (empty($s)) break;
//        echo $s;
        if (preg_match("/^[\s\*]{0,8}(\d+)\s([a-z]{2})_(\S+)/", $s, $m)) {
          $result = geonames_query('children', array('geonameid' => intval($m[1])));
//          var_dump($result);
//          exit;
          $items = array();
          foreach ($result->results as $item) {
            $items[$item['geonameid']] = $item['name'];
          }
          if ($items) {
            fwrite($put, "function location_cities_list_" . strtolower($m[2] . '_' . $m[3]) . "()\n");
            fwrite($put, "{\n");
            fwrite($put, "\treturn array(\n");
            foreach ($items as $gid => $name) {
              fwrite($put, "\t\t'$gid' => t('" . str_replace("'", "\'", $name) . "'),\n");
            }
            fwrite($put, "\t);\n");
            fwrite($put, "}\n");
          }


//          echo $m[1], ' ', $m[2], ' ', $m[3], "\n";
        }
      }
      if ($put) {
        @fclose($put);
      }

      fclose($f);
//      break;
    }
  }


//  $countries = location_get_iso3166_list();
//  foreach ($countries as $code => $name) {
//    if (isset($data[tester_countrycode_rewrite($code)])) {
////      tester_compare_province($code, $data[tester_countrycode_rewrite($code)]['#']);
////      break;
//    }
//  }

  exit;
}


function tester3()
{
  set_time_limit(0);
  $data = unserialize(file_get_contents("D:/dump.txt"));

  $countries = location_get_iso3166_list();
  foreach ($countries as $code => $name) {
    if (isset($data[tester_countrycode_rewrite($code)])) {
      tester_compare_province($code, $data[tester_countrycode_rewrite($code)]['#']);
//      break;
    }
  }


  exit;
}

function tester2()
{
  set_time_limit(0);
  $data = array();

  $countryList = geonames_query('countryinfo', NULL, array('sortby' => 'countryname'));
  foreach ($countryList->results as $country) {
    $data[strtolower($country['countrycode'])] = array(
      '#name' => $country['countryname'],
      '#gid' => $country['geonameid'],
    );
//    break;
  }

  foreach ($data as $code => &$country) {
    $country['#'] = geonames_tree($country['#gid']);
//    break;
  }

  file_put_contents("D:/dump.txt", serialize($data));

//  var_dump($data);
  exit;
}

function geonames_tree($gid)
{
  $out = array();

  $result = geonames_query('children', array('geonameid' => $gid));
  foreach ($result->results as $item) {
    $out2 = array();
    $out2['#name'] = $item['name'];
    $out2['#gid'] = $item['geonameid'];
    $out2['#'] = geonames_tree($out2['#gid']);
    $out[] = $out2;
  }

  return $out;
}
