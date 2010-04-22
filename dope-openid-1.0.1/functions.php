<?php
/**
*	This file is part of Dope OpenID.
*   Author: Steve Love (http://www.stevelove.org)
*   
*   Some code has been modified from Simple OpenID:
*   http://www.phpclasses.org/browse/package/3290.html
*
*   Yadis Library provided by JanRain:
*   http://www.openidenabled.com/php-openid/
*
*	Dope OpenID is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	Dope OpenID is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with Dope OpenID. If not, see <http://www.gnu.org/licenses/>.
**/

function your_openid_login_function($openid_url) {
	
	/*
	* Do this however you want. I'll assume login returns
	* some user details and this is sent back as a string. 
	*/
	$returnVal = "1|registered_user";

	return $returnVal;	
}

function your_get_user_function($openid_url){
	
	/*
	* Do this however you want. I'll assume searching for
	* an OpenID in your table returns the user_id associated
	* with the OpenID. 
	*/
	// Success
	//$returnVal = 1;
	
	// Fail
	$returnVal = 0;
	
	return $returnVal;
}



 function user_password_funct($length = 10) {
  // This variable contains the list of allowable characters for the
  // password. Note that the number 0 and the letter 'O' have been
  // removed to avoid confusion between the two. The same is true
  // of 'I', 1, and 'l'.
  $allowable_characters = 'abcdefghijkmnopqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ23456789';

  // Zero-based count of characters in the allowable list:
  $len = strlen($allowable_characters) - 1;

  // Declare the password as a blank string.
  $pass = '';

  // Loop the number of times specified by $length.
  for ($i = 0; $i < $length; $i++) {

    // Each iteration, pick a random character from the
    // allowable string and append it to the password:
    $pass .= $allowable_characters[mt_rand(0, $len)];
  }

  return $pass;
}

?>
