<?php

/**
 * @param string $name
 * @return string
 */
function gc_directory($name = '') {
  return dirname(__FILE__) . ($name ? '/' . $name : '');
}

/**
 * @param $line
 * @return array
 */
function gc_readtabline($line) {
  return explode("\t", trim($line, "\n"));
}

/**
 * @param $code
 * @param $list
 * @return string
 */
function gc_function_text($func, $list) {
  $output = "function $func () {\n";
  $output .= "\treturn array (\n";
  foreach ($list as $code => $name) {
    $output .= "\t\t\"$code\" => t(\"$name\"),\n";
  }
  $output .= "\t);\n";
  $output .= "}\n";
  return $output;
}
