<div id="new_vote">
  <!-- Part 1 -->
  <div class="part part1">
    <h2 class="din"><?php print t(rtrim($title, "?")); ?>?</h2>
    <div class="qd">
      <p class="description"><?php print theme('issue_description', $context); ?></p>
    </div>
    <div class="poll-vote-area">
      <?php if($allowvotes == '' ) : ?>
      <div class="vote-count-poll">
        <?php foreach($indVoteCounts as $chorder => $vcount) : ?>
          <div class="post-vote-result"><span class="vote-count dinbold"><?php print $vcount; ?></span><br /><span class="vote-count-title din">votes</span></div>
        <?php endforeach; ?>
      </div>
      <?php endif; ?>
      <div class="voting-pane"><?php print drupal_get_form('issue_vote_form', $node) #$content;?></div>
    </div>
  </div><!-- /div.part1 -->

  <!-- Part 2 -->
  <div class="part part2">
    <div id="shareDiv" class="clearfix"></div>
  </div><!-- /div.part2 -->

  <?php
    $nodepath = 'node/'.$nid;
    $pagePath = url($nodepath, array('absolute' => TRUE)).'/';
  ?>
  <script type="text/javascript">
    var act = new gigya.services.socialize.UserAction();
    act.setUserMessage("Your comment here...");
    act.setTitle("<?php print t($title); ?>");
    act.setDescription("<?php
      $context = str_replace(array("\r", "\n"), '', $context);
      print t(htmlentities($context));
    ?>");
    act.setLinkBack("<?php print $pagePath; ?>");
    act.addActionLink("<?php print t($title); ?>","<?php print $pagePath; ?>");
    var showShareBarUI_params=
    {
      containerID: 'shareDiv',
      shareButtons: 'Facebook,Twitter,google-plusone,Share',
      userAction: act,
      layout:'horizontal'
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
        