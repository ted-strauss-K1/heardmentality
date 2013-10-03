<?php

header("Content-type: application/x-javascript");

// id
$id = isset($_REQUEST['id']) && $_REQUEST['id'] ? $_REQUEST['id'] : 'hm-embed';
$id = preg_replace("/[^\w-]/", '', $id);

// issue
$issue = intval($_REQUEST['issue']);

// check
if (!$id) return;

// detect height
$height = 300;

// detect height using the number of choices
require_once './includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE);

$count = (int)db_result(db_query("SELECT COUNT(*) FROM {cpoll_choices} c WHERE c.nid = '%d'", $issue));
$height = 140 + 40*$count;

?>(function(d){
  var id = '<?php print $id; ?>', width = 300, e = d.getElementById(id), i;
  if (!e) {return;}
  i = d.createElement('iframe');
  i.id = id+'-iframe';
  i.src = "http://hm2/embedder/<?php print $issue; ?>";
  i.frameBorder = 0;
  i.scrolling = 'no';
  i.height = <?php print $height; ?>;
  i.width = width;
  //
  e.appendChild(i);
}(document));
