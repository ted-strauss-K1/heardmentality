<?php if(isset( $_POST['url'])  ) :?>
<?php
	
	include_once('functions.php');
	
		
	$url =  $_POST['url'];
	
	$pattern = getPatternFromUrl($url);
	
	
	$flv_path = GrabFlvFromYoutube( $pattern );
	
	echo $flv_path."<br/>"; 
	
	
	
	
	
	
	
?>
<?php else: ?>
<form action="grabber.php" method="post">

  <p>You tube url: 
    <input type="text" name="url">
  </p>
 
<p>
  <input type="submit" name="Submit" value="Grab">
</p>
</form>

<?php endif;?>