<?php

$adminmail="dyachenko.oleg@gmail.com";
$useremail= isset($_REQUEST['mail']) ? $_REQUEST['mail'] : "dyachenko.oleg@gmail.com";

$send_html_messages = "no";

$subject = "subject test";
$content = "test content";
$xheaders = "From: " . $adminmail . " <" . $adminmail . ">\n";
$xheaders .= "X-Sender: <" . $adminmail . ">\n";
$xheaders .= "X-Mailer: PHP\n"; // mailer
$xheaders .= "X-Priority: 6\n"; // Urgent message!
if ($send_html_messages == "yes") {
  $xheaders .= "Content-Type: text/html; charset=iso-8859-1\n"; // Mime type
}
$result = mail("$useremail","$subject","$content",$xheaders);
if ($result) {
  echo "Email was successfully sent";
} else {
  echo "Email was not successfully sent";
  var_dump(error_get_last());
}

