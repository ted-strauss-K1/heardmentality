<?php global $user;
$loginBoxClass = $user->uid==0?'openlogin_box':'';
?>

<div id="debate_work_area">
<div class="inner">

<div class="expanding arg">
    <h6 value="Reply" id="add-arg" class="button <?php print $loginBoxClass;?>"><?php print t('Add Argument'); ?></h6>
</div>

<div class="expanding stat">
    <h6 class="button" id="deb-ana"><?php print t('Debate statistics'); ?></h6>
</div>	

<div id="leave_comment_area" class="leave-a-comment hidden_arg">
	<?php print $addNewDebateForm; ?>
</div>

<div id="analytics-area hidden_deb">
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
	<h2><?php print $count; print ' Arguments'; ?></h2>
	<div class="comments expanding">
			<?php print $debateList; ?>
	</div>
</div><!--/#debate_list_area -->
