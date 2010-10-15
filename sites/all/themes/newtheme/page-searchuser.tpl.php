<?php include "header.tpl.php"; ?>
<!--content area-->
<div class="contarea">
        <div class="fact">
        
              <?php if (! empty($left)): ?>
        <div id="sidebar-left" class="column sidebar">
       
         
            <?php print $left; ?>
           
        </div>
        <!-- /sidebar-left -->
        <?php endif; ?>

           
          
        </div>
        <div class="inner-page-cont minheight544">
     <span class="padding10">SEARCH RESULTS</span>
 
                 
      <?php print $content; ?>
      </div>  
       <div class="contributer">
       	<div id="user_info">
          <div class="inner-commutop">
            <p>PROFILE INFORMATION</p>
            
            <div class="inner">
        No User Selected!
      </div>
          </div>

        
      <div class="clr"></div>
      
      </div>
 
      <!--content area close-->
    </div>
     <div class="clr">  </div>
      </div>
<?php include "footer.tpl.php"; ?>
