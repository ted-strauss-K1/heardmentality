<?php
// Below is a very simple PHP 5 script that hosts the RPX sign-in interface, and also acts as the token_url.  
// If a token is present it processes the token using the backchannel auth_info API call.  Otherwise it simply 
// renders the RPX interface using the embeded iframe.

//
// Please replace the following values:
//
$apiKey = '268b76fc6f87f9992760eb65db838e27c8c46028';
$siteName = "192.9.200.10";  // eg. "phpdemo". This will be expanded to phpdemo.rpxnow.com

$port = $_SERVER['SERVER_PORT'] == '80' ? '' : ':'.$_SERVER['SERVER_PORT'];

// this script will also process the token url
$token_url = 'http://' . $_SERVER['SERVER_NAME'] . $port . $_SERVER['SCRIPT_NAME'];
?>

<html>
<head></head>
<body>
<h1>RPX PHP Example</h1>

<?php
if(isset($_POST['token'])) { 
  echo '<div style="background-color:#eee;border:1px solid #aaa;width:400px;padding:5px;">';
  echo '<h3 style="color:green;margin:0;">Results</h3>';        

$post_data = array('token' => $_POST['token'],
                   'apiKey' => $apiKey,
                   'format' => 'json'); 

// make the api call using libcurl
$curl = curl_init();
curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
curl_setopt($curl, CURLOPT_URL, 'https://rpxnow.com/api/v2/auth_info');
curl_setopt($curl, CURLOPT_POST, true);
curl_setopt($curl, CURLOPT_POSTFIELDS, $post_data);
curl_setopt($curl, CURLOPT_HEADER, false);
curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false);
$raw_json = curl_exec($curl);
curl_close($curl);

// parse the json response into an associative array
$auth_info = json_decode($raw_json, true);

// process the auth_info response
if ($auth_info['stat'] == 'ok') {
  
  $profile = $auth_info['profile'];
  $identifier = $profile['identifier'];
  
  if (isset($profile['photo']))  {
    echo '<img style="float:right;" src="' . $profile['photo'] . '"/><br/>';
  }

  if (isset($profile['displayName']))  {
    echo '<b>Name:</b> ' . $profile['displayName'] . '<br/>';
  }

  if (isset($profile['email']))  {
    echo '<b>Email:</b> ' . $profile['email'] . '<br/>';
  }

  // identifer is always present in the response
  echo '<b>Identifier: </b>' . $profile['identifier'] . '<br/>'; 

} else {
  echo '<b>Error:</b> ' . $auth_info['err']['msg'];
}

?>

<div style="clear:both;"></div>
</div>
<br/>
<a href="<?php echo $token_url ?>">Sign out</a>
<?php } else { ?>

<h3>Sign in</h3>
<!-- add the iframe based rpx interface -->

<iframe src="https://<?php echo $siteName ?>.rpxnow.com/openid/embed?token_url=<?php echo urlencode($token_url)?>"
  scrolling="no" frameBorder="no" style="width:400px;height:240px;">
</iframe>

<?php } ?>
</body></html>
