<?php include "header.tpl.php"; ?>

      <!--content area-->
      <div class="contarea">
   

 
			
      <?php if (!empty($left)): ?>
	  <div class="home-lay1-1">
        <div id="sidebar-left" class="column sidebar">
          <?php print $left; ?>
        </div> <!-- /sidebar-left -->
      <!-- RAM COMMENTED div class="clr"></div-->
       </div>
	  <?php endif; ?>
    
        
           <div class="ques home-lay1-2">
            <?php   if (isset($node)) { ?>
                <div class="hm-page-title">ISSUE</div>
                <?php
  // do something with $node
} else { ?>
		    <div class="hm-page-title">  <?php if (!empty($title)): ?><?php print $title; ?><?php endif; ?></div>
			<?php } ?>
          <!--class="questop"-->
          <div class="" >
            <!--<div class="questopr"><?php echo date("M d,Y") ?></div>-->
          </div>
          <div class="hm-cen">
<div id="qajax">
           <?php print $content; ?>
    <?php print $content_bottom; ?>
</div>
  </div>
  
            </div>
     
      

 <div class="clr"></div>
</div>
   <?php include "footer.tpl.php"; ?>