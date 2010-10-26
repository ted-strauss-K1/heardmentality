<?php include "header.tpl.php"; ?>

      <!--content area-->
      <div class="contarea">
   

 
			
      <?php if (!empty($left)): ?>
	  <div class="commu">
          <div class="">
        <div id="sidebar-left" class="column sidebar">
          <?php print $left; ?>
        </div> <!-- /sidebar-left -->
      <div class="clr"></div>
          </div>
       </div>
	  <?php endif; ?>
    
        
           <div class="ques">
		    <div class="commutop-profile">  <?php if (!empty($title)): ?><?php print $title; ?><?php endif; ?></div>
			<!--class="questop"-->
          <div class="" >
            <!--<div class="questopr"><?php echo date("M d,Y") ?></div>-->
          </div>
          <div class="quesbg">

           <?php print $content; ?>
  </div>
  
     <div class="quesbott"></div>
        </div>

      <?php if (!empty($right)): ?>
	    <div class="fact">
        <div id="sidebar-right" class="column sidebar">
          <?php print $right; ?>
        </div> <!-- /sidebar-right -->
		</div>
      <?php endif; ?>

 <div class="clr"></div>
</div>
   <?php include "footer.tpl.php"; ?>