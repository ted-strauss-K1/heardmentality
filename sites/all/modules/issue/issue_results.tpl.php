<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
global $gSitePath;
?>
<div class="clr"></div>
	<div id="rotate">
<ul id="maintabs" class="mytabs" >
<li class="current" id="in"><a href="<?php print $gSitePath; ?>/qlite/panel/<?php print $nid; ?>" title="Report"><span>Reporting</span></a></li>
<li id="par1"><a href="<?php print $gSitePath; ?>/qlite/panel/<?php print $nid; ?>?type=debate" title="Debate"><span>Debate(<?php print $votes; ?>)</span></a></li>
<li class="" id="par2"><a href="<?php print $gSitePath; ?>/qlite/panel/<?php print $nid; ?>?type=Resources" title="Resources"><span>Resources(<?php print $votes; ?>)</span></a></li>
<li class=""><a href="<?php print $gSitePath; ?>/qlite/panel/<?php print $nid; ?>?type=Gurus" title="Gurus"><span>Pundits (<?php print $votes; ?>)</span></a></li>
<li class="" id="in"><a href="<?php print $gSitePath; ?>/qlite/panel/<?php print $nid; ?>?type=Info" title="Info"><span>Details</span></a></li>
              </ul>
              <div class="mytabs-container" id="tabcontent">
            Loading. Please Wait...
        </div><div class="clr"></div>
           </div>