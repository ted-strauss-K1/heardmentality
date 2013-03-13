<?php

error_reporting(E_ALL ^ E_NOTICE);

$to = isset($_REQUEST['mail']) ? $_REQUEST['mail'] : "dyachenko.oleg@gmail.com";
$subject = "Test mail";
$message = "Hello! This is a simple email message. Date: " . date('Y-m-d H:i:s');
$from = "dyachenko.oleg@gmail.com";
$headers = "From:" . $from;
$result = mail($to,$subject,$message,$headers);
var_dump($result);