<?php
global $apikey, $base_path, $theme, $base_url, $user;
$gSitePath = $base_path.'/';
 $path=$gSitePath.  drupal_get_path('theme',$theme);
 $node=node_load(array('nid'=>$nid));
 $tnid = get_tnid($nid);
?>


<?php if($user->uid!=0){?>
<a class="icon flag" id="dialog_link-flag" title="flag this issue" rel="lightframe"  href="<?php print $base_url; ?>/qlite/flag/<?php print $nid;?>"></a>
<?php }else{?>
<a class="icon flag openlogin_box" title="flag this issue" rel="lightframe"  href="#"></a>
<?php }?>

<h2 class="din"><?php print t(rtrim($title, "?")); ?>?<span class="pip">&nbsp;</span></h2>

<div id="new_vote">

<!-- Part 1 -->

<div class="part part1">
<p class="description">
    
	<!--<span id="sp-desc" style="height:40px; overflow: hidden; float: left;">
        <?php //print t($context); ?>&nbsp;
    </span>
    <?php if(strlen($context)>150) {?><a onclick="showDesc()" id="more-desc">[...]</a><?php }?>
	-->
	<!--Rallydev:526-->
	 <?php $output = __issue_description_trimmer($context); ?>
	<span><?php print $output['context_initial']; ?></span><span id="extended-issue-description" style="display:none;"><?php print $output['context_remaining']; ?></span>
	<!---------------->
</p>

<!--<div class="issue-things"></div>-->
<div class="poll-vote-area">
<?php if($allowvotes == '' ): ?>
   <div class="vote-count-poll">
       <?php foreach($indVoteCounts as $chorder => $vcount){?>
       <div class="post-vote-result"><span class="vote-count dinbold"><?php print $vcount; ?></span><br><span class="vote-count-title din">votes</span></div>
       <br class="clear" />
       <?php }?>
   </div>
<?php endif; ?>
<div class="voting-pane"><?php print $content ?></div>
</div>
</div><!-- /div.part1 -->

<!-- Part 2 -->

<div class="part part2">

<div class="expanding">
  <h6 class="wait">... <?php print t('Or submit a different answer'); ?></h6>

    <?php print $suggest; ?>

</div>
<div id="shareDiv" class="floatright"></div>

<div id="dialog-flag" title="<?php print t('FLAG THIS ITEM'); ?>" class="dialog">
		<?php if($flagForm): print $flagForm; endif; ?>
</div>
</div><!-- /div.part2 -->


<?php
$nodepath = 'node/'.$nid;
$pagePath = url($nodepath, array('absolute' => TRUE)).'/'; ?>
<script type="text/javascript">
    var act = new gigya.services.socialize.UserAction();
    act.setUserMessage("Your comment here...");
    act.setTitle("<?php print t($title); ?>");
    act.setDescription("<?php
                        $context = str_replace(array("\r", "\n"), '', $context);
                     print t(htmlentities($context));?>");
    act.setLinkBack("<?php print $pagePath; ?>");
    act.addActionLink("<?php print t($title); ?>","<?php print $pagePath; ?>");

    var showShareBarUI_params=
    {
      containerID: 'shareDiv',
      shareButtons: 'Facebook,Twitter,google-plusone,Share',
      userAction: act,
      layout:'vertical'
    }
</script>


<script type="text/javascript">
   gigya.services.socialize.showShareBarUI(conf,showShareBarUI_params);
   function showDesc(){
       jQuery('#sp-desc').css('height', 'auto');
       jQuery('#more-desc').hide();
   }
</script>

</div>
        