<?php global $user;
$loginBoxClass = $user->uid==0?'openlogin_box':'';
?>

<div id="debate_work_area">
<div class="inner">

<div class="expanding">
            <h6 value="Reply" id="add-arg" class="<!--add-comment button--> <?php print $loginBoxClass;?>"><?php print t('Add an Argument'); ?></h6>

            <ul>
              <li>
				<div class="leave-a-comment">
					<?php print $addNewDebateForm; ?>
				</div>
              </li>
			</ul>
</div>

<div class="expanding">
        <h6 class="button"><?php print t('Show only'); ?></h6>
        <ul>
			<?php print $debateFilterForm; ?>
        </ul>
</div>

<div class="expanding">
        <h6 class="button" id="deb-ana"><?php print t('Debate statistics'); ?></h6>
        <div id="analytics-area">
          <?php print $debateStatistics; ?>
          <div id="deb-ana-load-txt"></div>

          <div id="load-deb-statics"></div>
        </div>
</div>

</div><!--/.inner -->
</div><!--/#debate_work_area -->

<div id="debate_list_area">
	<h2><?php print t('Count arguments!'); ?></h2>
	<div class="comments expanding">
			<?php print $debateList; ?>
	</div>
</div><!--/#debate_list_area -->
