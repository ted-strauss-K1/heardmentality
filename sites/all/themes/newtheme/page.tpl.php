<?php include "header.tpl.php"; ?>

      <!--content area-->
      <div class="contarea">
   <div class="commu">
          <div class="">

 

      <?php if (!empty($left)): ?>
        <div id="sidebar-left" class="column sidebar">
          <?php print $left; ?>
        </div> <!-- /sidebar-left -->
      <?php endif; ?>
    <div class="clr"></div>
          </div>
       </div>
        
           <div class="ques">
          <div class="questop">
            <div class="questopl">  <?php if (!empty($title)): ?><?php print $title; ?><?php endif; ?></div>
            <div class="questopr"><?php echo date("M d,Y") ?></div>
          </div>
          <div class="quesbg">

           <?php print $content; ?>
  </div>
  
     <div class="quesbott"></div>
        </div>
  <div class="fact">
      <?php if (!empty($right)): ?>
        <div id="sidebar-right" class="column sidebar">
          <?php print $right; ?>
        </div> <!-- /sidebar-right -->
      <?php endif; ?>
</div>
</div>
   <?php include "footer.tpl.php"; ?>