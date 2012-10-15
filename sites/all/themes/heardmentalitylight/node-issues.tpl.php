<?php
global $apikey, $gSitePath;
$path = '<front>';
$sitelink = url($path, array('absolute' => TRUE)) . '/';

?>

<div class="search_list">

<div id="vote-msg-alert-<?php print $tnid; ?>" class="v-msg"></div>

<h2 class="din half"><a href="<?php print $node_url; ?>" title="permalink" class="issue-title"><?php print t($title); ?>?</a></h2>

<!--<div class="poll-vote-area">
  <?php
  if ($allowvotes == 1) {
    $display = 'style="display: none;"';
  }
  ?>
  <div class="vote-count-poll" <?php print $display; ?> id="vote-count-poll-<?php print $tnid; ?>">
    <?php if ($indVoteCounts): foreach ($indVoteCounts as $chorder => $vcount) { ?>
        <div class="post-vote-result"><span class="vote-count dinbold" id="<?php print $tnid; ?>-chorder-<?php print $chorder; ?>"><?php print $vcount; ?></span><br><span class="vote-count-title din">votes</span></div>
        <br class="clear" />
  <?php } endif; ?>
  </div>

  <div class="voting-pane" id="voting-pane-<?php print $tnid; ?>"><?php print $content; ?></div>
</div>-->

<div class="poll-vote-area">
<?php if($allowvotes == '' ): ?>
   <div class="vote-count-poll">
       <?php foreach($indVoteCounts as $chorder => $vcount) {?>
        <div class="post-vote-result"><span class="vote-count dinbold"><?php print $vcount; ?></span><br /><span class="vote-count-title din">votes</span></div>
       <?php } ?>
   </div>
<?php endif; ?>
<div class="voting-pane"><?php print $content;?></div>

  <?php if ($allowvotes != 1 && user_is_logged_in()) { ?>

  <a class="button stats stats-quick" title="See the Debate Statistics" href="<?php print $node_url; ?>#results"><span class="icon stats "></span></a>
<?php } ?>

</div>
</div>







