<div class="<?php if($teaser) : ?>search_item<?php endif; ?> issue-vote-wrapper" <?php if($page) : ?>id="new_vote"<?php else : ?> <?php endif; ?>>
  <!-- Part 1 -->
  <div class="part part1 <?php if($teaser) : ?>search_list<?php endif; ?>">
    <h2 class="din<?php if($teaser) : ?> half<?php endif; ?>"><?php print
      l( t(rtrim($title, "?")), $node->path);
    ?>?</h2>
    <?php if($page) : ?>
    <div class="qd">
      <?php print theme('flagger_button', $nid, 'node'); ?>
      <p class="description"><?php print $node->description; ?></p>
    </div>
    <?php endif; ?>
    <div class="poll-vote-area">
      <div class="voting-pane"><?php print drupal_get_form('issue_vote_form', $node, $page); ?></div>
    </div>
  </div><!-- /div.part1 -->

  <?php if($page) : ?>
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
  <?php endif; ?>
</div>
<?php if($page) : ?>
  <?php print theme('issue_arguments', $node); ?>
<?php endif; ?>
        