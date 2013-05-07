<div class="<?php if($teaser) : ?>search_item<?php endif; ?> issue-vote-wrapper" <?php if($page) : ?>id="new_vote"<?php else : ?> <?php endif; ?>>
  <!-- Part 1 -->
  <?php $translation = module_exists('poll_translate') ? poll_translate_translation($node) : array(); ?>
  <div class="part part1 <?php if($teaser) : ?>search_list<?php endif; ?>">
    <h2 class="din<?php if($teaser) : ?> half<?php endif; ?>"><?php print
      l( t(rtrim(!empty($translation['title'][0]) ? $translation['title'][0] : $title, "?")), $node->path, array('html' => true));
    ?>?</h2>
    <?php if($page) : ?>
    <div class="qd">
      <?php if ($node->moderate) : ?>
        <img src="/sites/all/themes/heardmentalitylight/images/icons/59-flag@2x.png" height="14px">
        <?php print theme('flagger_btn_flag', $nid, 'node'); ?>
        <?php print theme('flagger_btn_flags', $nid, 'node'); ?>
        <?php print theme('flagger_btn_history', $nid, 'node'); ?>
        <?php if (module_exists('moderation') && moderation_check_perm()) : ?>
          <?php print l(t('moderation'), 'moderation/issue/'.$node->nid,
            array('attributes' => array(
              'class' => 'moderation',
              'original-title' => t('moderation'),
            ))
          ); ?>
        <?php endif; ?>
      <?php endif; ?>
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
    <div id="shareDiv" class="clearfix">
      <span class='st_facebook_hcount' displayText='Facebook'></span>
      <span class='st_twitter_hcount' displayText='Tweet'></span>
      <span class='st_googleplus_hcount' displayText='Google +'></span>
      <span class='st_linkedin_hcount' displayText='LinkedIn'></span>
      <span class='st_sharethis_hcount' displayText='ShareThis'></span>
      <script type="text/javascript">var switchTo5x=false;</script>
      <script type="text/javascript" src="http://w.sharethis.com/button/buttons.js"></script>
      <script type="text/javascript">
        stLight.options({
          publisher: "1ace1433-6c6c-45c5-bb28-d33af72b78b4",
          doNotHash: false,
          doNotCopy: false,
          hashAddressBar: false
        });
      </script>
    </div>
  </div><!-- /div.part2 -->




  <script type="text/javascript">
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
        