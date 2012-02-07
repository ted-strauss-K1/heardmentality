<?php include "header.tpl.php"; ?>
      <!--content area-->
      <div class="profile_part">
       <!-- <div class="bor_bot">
		<div class="rht_link">
  <a href="#" title="History">History</a> <span class="separate">|</span> 
        <a href="<?php echo $gSitePath;?>?act=edit" title="Edit My Profile">Edit My Profile</a>
        </div>
        <br class="clr" />
      </div>-->
      
	  
	  
	 
      <div class="commu-profile2">

       <div style="float: left;" class="inner5">
       <?php echo $content;?>
        </div>
      <div style="float: left;" class="commu3">
          <div class="inner-commutop">
            <p>ACTIVITY STREAM</p>
          </div>
          <div class="inner">
              <div class="clr"></div>
            <div class="clr"></div>
            <div class="commuinn3">
       <?php print $Beat ?>
            </div>
          </div>
           
      </div>

      </div>
		
       <div class="clr"></div>
      <!--content area close-->
	  </div>
	 

  <?php include "footer.tpl.php"; ?>