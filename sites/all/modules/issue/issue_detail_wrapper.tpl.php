<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
 
?>

<div><?php print $result_analysis; ?></div>

<div class="ul_wrapper">
<ul class="tabs">
      <!-- Give href an ID value of corresponding "tabs-content" <li>'s -->
      <li><a class="active" href="#simple"><?php print t('Debate'); ?>&nbsp;<span class="debate-count">(<?php print $debateCount; ?>)</span></a></li>
      <li><a href="#lightweight" class="references"><?php print t('References'); ?>&nbsp;<span class="reference-count">(<?php print $resourceCount; ?>)</span></a></li>

</ul>
</div>
<ul class="tabs-content">
      <!-- Give ID that matches HREF of above anchors -->
      <li class="active" id="simpleTab">
           <?php print $debate_list; ?>
      </li>
      <li id="lightweightTab">
            <?php print $resource_list; ?>
      </li>
</ul>
