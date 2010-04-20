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

/*
* Example uses default PHP sessions.
* Feel free to use whatever session management you prefer.
*/
session_start();
/*
* Include our example functions. Your actual functions may differ.
*/
require 'functions.php';

/*
* Is $_SESSION['loggedin'] set and does it evaluate to TRUE?
* If yes, user is already logged in. Redirect them somewhere else.
*/
if(isset($_SESSION['loggedin']) && $_SESSION['loggedin']){
	//header("Location:http://192.9.200.10/heardmentality/ids/index.php");
	exit;
}




?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<title>Dope OpenID Demo: Log In</title>
      <link type="text/css" rel="stylesheet" href="css/openid.css" />
     <script type="text/javascript" src="js/core.js"></script>
    <script type="text/javascript" src="js/more.js"></script>
    <script type="text/javascript" src="js/openid.js"></script>
	<meta http-equiv="content-type" content="text/html;charset=utf-8" />
	<meta http-equiv="Content-Style-Type" content="text/css" />
     <script type="text/javascript">
        window.addEvent('domready', function(){
            new OpenIdSelector('openid_identifier');
        });
    </script>
</head>

<body>

	<p style="color:#f00;"><?php echo $error; ?></p>
	
	<form name="openid_form" id="openid_form" action="login.php" method="post" autocomplete="off">
		
		<!-- Your OpenID input should be named "openid_identifier" to follow best practices
	     and in order to work with the ID Selector JavaScript, should you choose to use it. -->
         
           <div id="openid_choice">
            
                <div id="openid_btns"></div>
            </div>
		<label>
			OpenID URL: <input type="text" name="openid_identifier" id="openid_identifier" maxlength="320" />
		</label>
		
		<input type="hidden" name="process" value="1" />
		
<!--		<button type="submit">Sign In With OpenID</button>
-->		
        
        
        
        
        
        
        
        
        
        
        
         
            <input type="hidden" name="action" value="verify" />

            <div id="openid_choice">
                <p>Please click your account provider:</p>
                <div id="openid_btns"></div>
            </div>
            <div id="openid_input_area">
                <input id="openid_identifier" name="openid_identifier" type="text" value="http://" />
                <input id="openid_submit" type="submit" value="Sign-In"/>
            </div>
            <noscript>
                <p>
                    OpenID is service that allows you to log-on to many different websites using a single indentity.
                    Find out <a href="http://openid.net/what/">more about OpenID</a> 
                    and <a href="http://openid.net/get/">how to get an OpenID enabled account</a>.
                </p>
            </noscript>
       
        
        
        
        
        
	</form>
	
<!-- BEGIN ID SELECTOR -->
<!--<script type="text/javascript" id="__openidselector" src="script.js" charset="utf-8"></script>-->
<!-- END ID SELECTOR -->

</body>
</html>
