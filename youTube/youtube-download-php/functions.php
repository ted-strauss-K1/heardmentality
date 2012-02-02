<?php

//function for getting flv file from youtube website. Returns the downloaded flv path
function GrabFlvFromYoutube( $pattern )
{
	require_once ("phptube.php");
	$tube = new PHPTube ();
	
	$flv_http_path = $tube->download($pattern) ;
	
	echo $flv_http_path;
	
	set_time_limit(0);
	$data = file_get_contents($flv_http_path);
	$new_flv_path = dirname(_FILE_).'/flvs/'.$pattern.'.flv' ;
	
	
	
	file_put_contents($new_flv_path, $data);
	
	return $new_flv_path ;
}



function getPatternFromUrl($url)
{
	$url = $url.'&';
	$pattern = '/v=(.+?)&+/';
	preg_match($pattern, $url, $matches);
	return ($matches[1]);
}



?>