<?php include "header.tpl.php"; ?>

      <!--content area-->
      <div class="contarea">
   

 
			
      <?php if (!empty($left)): ?>
	  <div class="home-lay3-1">
        <div id="sidebar-left" class="column sidebar">
          <?php print $left; ?>
        </div> <!-- /sidebar-left -->
      <!-- RAM COMMENTED div class="clr"></div-->
       </div>
	  <?php endif; ?>
    
        
           <div class="ques">
		    <div class="commutop-profile">  <?php if (!empty($title)): ?><?php print $title; ?><?php endif; ?></div>
			<!--class="questop"-->
          <div class="" >
            <!--<div class="questopr"><?php echo date("M d,Y") ?></div>-->
          </div>
          <div class="hm-cen">
<div id="qajax">
           <?php print $content; ?>
</div>
  </div>
  
            </div>
     
      <?php if (!empty($right)): ?>
	    <div class="fact">
                <div id="block-sitetour">
        <div class="sitetour">
              <a href="<?php echo $gSitePath; ?>?tourId=MyTour"><img title="take the site tour" alt="take the site tour" src="<?php echo $gSitePath.path_to_theme();?>/images/take-tour.png"/></a>
        </div>
        </div>
        <div id="sidebar-right" class="column sidebar">
          <?php print $right; ?>
        </div> <!-- /sidebar-right -->
		</div>
      <?php endif; ?>

 <div class="clr"></div>
</div>
   <?php include "footer.tpl.php"; ?>