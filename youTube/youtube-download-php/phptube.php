<?php

// ************************************************************************
// Class      PHPTube
// Version:   0.1.4
// Date:      2007/07/01
// Author:    Michael Kamleitner (michael.kamleitner@gmail.com)
// WWW:       http://www.kamleitner.com/code
//            (suggestions, bug-reports & general shouts are welcome)
// Copyright: copyright 2007 - Michael Kamleitner
//
//            This file is part of PHPTube
//
//            PHPTube is free software; you can redistribute it and/or modify
//            it under the terms of the GNU General Public License as published by
//            the Free Software Foundation; either version 2 of the License, or
//            (at your option) any later version.
//
//            PHPTube is distributed in the hope that it will be useful,
//            but WITHOUT ANY WARRANTY; without even the implied warranty of
//            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//            GNU General Public License for more details.
//
//            You should have received a copy of the GNU General Public License
//            along with PHPTube; if not, write to the Free Software
//            Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//            
// ************************************************************************


require_once 'Request.php';


class PHPTube {

	var $cookies;
	var $mgr;
	var $req; 
	var $debug = true;
	var $auth = false;
	
	// Function:	PHPTube   ... Initialize PHPTube-Object
	// Paramters:	$username ... YouTube Accountname (if empty, upload is disabled)
	//						$password ... YouTube Passwort (if empty, upload is disabled)
	//						$debug	  ... Debug-Flag
	
	function PHPTube () {
		
		
	}
	
	// Function:	download  ... Download any Video-Clip from YouTube
	// Paramters:	$video_id ... Video-ID as given in YouTube URL (f.e. the Video at http://youtube.com/watch?v=TWZ5j-SNVKs
	//							  has the ID "TWZ5j-SNVKs"
	//				$video_filename ... local path+filename, the video is downloaded to (check write-permissions!)
	
	function download ($video_id) {
		$url = "http://www.youtube.com/watch?v=".$video_id;
		$this->req =& new HTTP_Request($url);
		$response = $this->req->sendRequest();
		if (PEAR::isError($response)) {
			echo $response->getMessage()."\n";
		} else {	
			$page = $this->req->getResponseBody();	
			//preg_match('/watch_fullscreen\?video_id=(.*?)&l=(.*?)+&t=(.*?)&/', $page, $match);
			preg_match('/"video_id": "(.*?)"/', $page, $match);
			$var_id = $match[1];

			preg_match('/"t": "(.*?)"/', $page, $match);
			$var_t = $match[1];

			$url = "";
			$url .= $var_id;
			$url .= "&t=";
			$url .= $var_t;
			$url = "http://www.youtube.com/get_video?video_id=".$url;
			if ($this->debug)
				return $url;
			
		
		}
		
		
	}		
	
	
}
?>
