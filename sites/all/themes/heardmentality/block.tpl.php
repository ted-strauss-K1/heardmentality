<?php
// $Id: block.tpl.php,v 1.3 2007/08/07 08:39:36 goba Exp $
if($block->region == 'right')
	$vCol='sideColumn2';
else
	$vCol='sideColumn1';
?>

new MochaUI.Panel({
		id: 'panel<?php print $block->bid ?>',
		title: '<?php print addslashes($block->subject) ?>',
		loadMethod: 'html',
		content: '<?php print str_replace("\n","",$block->content); ?>',
		column: '<?php print $vCol;?>',
		height: 150
	});