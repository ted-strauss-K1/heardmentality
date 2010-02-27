<?
//require_once './includes/bootstrap.inc';
//drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
// Menu status constants are integers; page content is a string.
$vCont=$_COOKIE['cPage'];
//setcookie("cPage", "", 1);
//$vCont=file_get_contents("cache/content");
echo html_entity_decode(urldecode($vCont));

?>