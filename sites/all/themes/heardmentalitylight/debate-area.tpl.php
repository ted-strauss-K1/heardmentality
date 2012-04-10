<?php
global $user;
$loginBoxClass = $user->uid == 0 ? 'openlogin_box' : '';
?>

<div id="debate_work_area">
  <div class="inner">

    <div class="expanding arg">
      <h6 value="Reply" id="add-arg" class="button <?php print $loginBoxClass; ?>"><?php print t('Add'); ?></h6>
    </div>

    <div class="expanding stat">
      <h6 class="button" id="deb-ana"><?php print t('Stats'); ?></h6>
    </div>	

    <div id="leave_comment_area" class="leave-a-comment hidden_ar" style="display: none;">
      <?php print $addNewDebateForm; ?>
    </div>

    <div id="analytics-area" class="hidden_deb" style="display: none;">
      <?php print $debateStatistics; ?>
      <div id="deb-ana-load-txt"></div>
      <div id="load-deb-statics"></div>
    </div>


    <!--<div class="expanding">
            <h6 class="button"><?php print t('Show only'); ?></h6>
            <ul>
    <?php print $debateFilterForm; ?>
            </ul>
    </div>-->


  </div><!--/.inner -->
</div><!--/#debate_work_area -->

<div id="debate_list_area">
  <h2>
	<span><?php print $count;
    print ' Arguments';?></span>
	
	<div class="show_only">
		<span class="button" href="">&#9660; Show only</span> <div class="inc"><form id="inc_ref"><input type="checkbox" value="include references" id="inc_check" /><label for="inc_check">Include References</label></form></div>
		<div class="popup">
			<span class="title">Show all</span>
			<dl>
				<dd><a href="" class="neutral"><span>-</span><span>+</span></a><a href="" class="negative"><span>-</span></a><a href="" class="positive"><span>+</span></a></dd><dt>Name answer</dt>
			</dl>
			<dl>
				<dd><a href="" class="neutral"><span>-</span><span>+</span></a><a href="" class="negative"><span>-</span></a><a href="" class="positive"><span>+</span></a></dd><dt>Name answer2</dt>
			</dl>
			<dl>
				<dd><a href="" class="neutral"><span>-</span><span>+</span></a><a href="" class="negative"><span>-</span></a><a href="" class="positive"><span>+</span></a></dd><dt>Name answer3</dt>
			</dl>		
		</div>
	</div>
	
    <ul>
      <li><a href="#tabs-1">older</a></li>
      <li><a href="#tabs-2">recent</a></li>
      <li><a href="#tabs-3">supported</a></li>
    </ul>
  </h2>
  

  <div class="comments expanding">
    <div id ="tabs-1">
      <?php print $debateList[0]; ?>
    </div>
    <div id ="tabs-2">
      <?php print $debateList[1]; ?>
    </div>
    <div id ="tabs-3">
      <?php print $debateList[2]; ?>
    </div>
  </div>


</div><!--/#debate_list_area -->
