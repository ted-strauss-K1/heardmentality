<?php

# parse regions file
  $code2gid = array();
  $gid2code = array();

  $path = 'D:/iso.txt';
  $file = fopen($path, 'r');
  while ($s = fgets($file)) {
    $s = trim($s, "\n\r");
    $item = explode("\t", $s);

    if ($item[3]) {
      $code2gid[strtolower($item[0]).'_'.$item[1]] = $item[3];
      $gid2code[$item[3]] = strtolower($item[0]).'_'.$item[1];
    }
  }
  fclose($file);

  # parse admincodes file
  $region2gid = array();
  $gid2name = array();

  $path = dirname(__FILE__) . '/code2gid.txt';
  $file = fopen($path, 'r');
  while ($s = fgets($file)) {
    $s = trim($s, "\n\r");
    $item = explode("\t", $s);

    if (isset($gid2code[$item[3]])) {
      $region2gid[$item[0]] = $item[3];
      $gid2name[$item[0]] = $item[2];
    }
  }
  fclose($file);

  # parse cities file
  $cities = array();

  file_put_contents(dirname(__FILE__) . '/cities.txt', '');

  $path = dirname(__FILE__) . '/cities15000.txt';
  $file = fopen($path, 'r');
  while ($s = fgets($file)) {
    $s = trim($s, "\n\r");
    $item = explode("\t", $s);

    $gid = $item[0];
    $name = $item[2]; // (ASCII name)
    $code = $item[8].'.'.$item[10];

    if (isset($region2gid[$code])) {
      //
      $ccode = $gid2code[$region2gid[$code]];
      file_put_contents(dirname(__FILE__) . '/cities.txt', $ccode . "\t$gid\t$name\n", FILE_APPEND);
    }

    // var_dump($item); exit;
  }
  fclose($file);