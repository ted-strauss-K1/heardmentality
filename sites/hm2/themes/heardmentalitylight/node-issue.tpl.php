<div
  class="<?php if($teaser) : ?>search_item
    <?php if (isset($node->taxonomy)) foreach ($node->taxonomy as $tid => $term) print ' tft-'.$tid; ?>
    <?php if (isset($node->locations)) foreach ($node->locations as $location) print ' tfl-'.$location['name']; ?>
  <?php endif; ?> issue-vote-wrapper"
  id="<?php if($page) : ?>new_vote<?php else : ?><?php endif; ?>">
  <!-- Part 1 -->
  <div class="part part1 <?php if($teaser) : ?>search_list<?php endif; ?>">
    <h2 class="din<?php if($teaser) : ?> half<?php endif; ?>"><?php print
      l($node->title, $node->path, array('html' => true));
    ?></h2>
    <div class="qd">
      <?php if($page) : ?>
        <?php if ($node->moderate == MODERATION_ALLOWED) : ?>
          <img src="/sites/all/themes/heardmentalitylight/images/icons/59-flag@2x.png" height="14px">
          <?php print theme('flagger_btn_flag', $nid, 'node'); // todo ?>
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

        <?php elseif (!empty($node->field_base_issue[0]['nid'])) : ?>

          <?php if ($node->field_base_issue[0]['safe']['status']) : ?>
            <?php print t('Duplicates issue') ?> <?php
              $base_issue = node_load($node->field_base_issue[0]['nid']);
              print l(issue_translate($base_issue, 'title'), 'node/'.$base_issue->nid);
            ?>
          <?php else : ?>
            <?php print t('Closed as the duplicate to other content on site'); ?>
          <?php endif; ?>

        <?php endif; ?>
      <?php endif; ?>

      <?php if (ranks_permission(0, $node->uid)) : // todo has sufficient rank ?>
        <?php print theme('expander', $node->content['body']['#value']); ?>
      <?php else : ?>
        <?php print theme('expander', $node->content['body']['#value'], 1000, ''); ?>
      <?php endif; ?>

      <?php if (!$page) : ?>
        <ul class="tags">
          <?php foreach ($node->taxonomy as $term) : ?>
            <li><?php print theme('categories_subscribe', $term->name, term_hierarchy($term)); ?></li>
          <?php endforeach; ?>
        </ul>
      <?php endif; ?>
    </div>

    <div class="poll-vote-area">
      <div class="voting-pane"><?php print drupal_get_form('cpoll_vote_form', $node, false, $page); ?></div>
    </div>
  </div><!-- /div.part1 -->

  <?php if($page) : ?>
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
    </div>

    <script type="text/javascript">
      function showDesc(){
         jQuery('#sp-desc').css('height', 'auto');
         jQuery('#more-desc').hide();
      }
    </script>
  <?php endif; ?>

</div>
<?php if($page) : ?>
  <div>
    <?php print theme('charts', $node); ?>
  </div>

  <?php drupal_add_js(drupal_get_path('module', 'yn') . '/yn.js'); ?>
  <?php drupal_add_js(drupal_get_path('module', 'argument') . "/argument.js"); ?>

  <div class="ul_wrapper">
    <h2 class="din"><?php print t('Debate'); ?></h2>
  </div>
  <ul class="tabs-content" style="margin: 22px 0 0;">
    <li class="active" id="simpleTab">

      <!-- FORM -->
      <div id="debate_work_area">
        <div class="inner">

          <?php if (ranks_permission(0, $node->uid)) : // todo has sufficient rank ?>

          <div class="expanding arg">
            <h6 value="Reply" id="add-arg" class="button <?php print theme('user_login_modal_class'); ?>"><?php print t('Add'); ?></h6>
          </div>

          <?php endif; ?>

          <?php if ($node->info['all']) : ?>
            <?php print theme('charts_strength', $node); ?>
          <?php endif; ?>

          <div id="leave_comment_area" class="leave-a-comment hidden_ar" style="display: none">
            <?php if (user_is_logged_in()) : ?>
              <?php print drupal_get_form('argument_form', $node); ?>
            <?php else : ?>
              <div class="<?php print theme('user_login_modal_class', TRUE) ?>" align="center"><b>
                <?php print t('Please log in to participate in the debate') ?>
              </b></div>
            <?php endif; ?>
          </div>

          <div id="analytics-area" class="hidden_deb" style="display: none;">
            <h2><span><?php print t('Debate statistics'); ?></span></h2>

            <div id="deb-ana-load-txt"></div>
            <div id="chart-strength" style="width:100%;"><svg style="height:280px;"></svg></div>
          </div>

        </div>
      </div>
      <!-- ENDFORM  -->

      <!-- LIST -->
      <div id="debate_list_area">
        <h2>
          <span class="argcount"><?php print intval($node->info['argument']); ?></span>&nbsp;<span><?php print t('Arguments'); ?>&nbsp;&amp;&nbsp;</span>
          <span class="rescount"><?php print intval($node->info['resource']); ?></span>&nbsp;<span><?php print t('References'); ?></span>

          <div class="show_only">
            <span class="button" id="show_filter">&#9660; <?php print t('Show only'); ?></span>

            <div class="inc">
              <form id="inc_ref">
                <input type="checkbox" checked="yes" value="include references" id="inc_check"/>
                <label for="inc_check"><?php print t('Include References'); ?></label>
              </form>
            </div>
            <div class="popup hidden" id="filter_content">
              <span class="title"><?php print t('Show all'); ?></span>
              <?php foreach ($node->choices as $choice) : ?>
                <dl name="<?php print $choice['chid'] ?>">
                  <dd>
                    <a href="" class="neutral">
                      <span class="small_pos">+</span>
                      <span class="small_neg">-</span>
                    </a>
                    <a href="" class="positive">
                      <span class="small_pos">+</span>
                    </a>
                    <a href="" class="negative">
                      <span class="small_neg">-</span>
                    </a>
                  </dd>
                  <dt><?php print $choice['chtext_short'] ?></dt>
                </dl>
              <?php endforeach; ?>
              <span class="title reset"><?php print t('Reset filters'); ?></span>
            </div>
          </div>
        </h2>

        <div id="empty_helper">&nbsp;</div>

        <ul>
          <li><a href="<?php print url('argument/tab'); ?>/<?php print $node->nid; ?>/0/0"><?php print t('recent'); ?></a></li>
          <li><a href="<?php print url('argument/tab'); ?>/<?php print $node->nid; ?>/1/0"><?php print t('older'); ?></a></li>
          <li><a href="<?php print url('argument/tab'); ?>/<?php print $node->nid; ?>/2/0"><?php print t('supported'); ?></a></li>
        </ul>
        <div id="ui-tabs-1">
          <?php
            // todo
            print argument_tab($node->nid);
          ?>
        </div>
        <div id="ui-tabs-2">
          <div style="padding: 20px; width: 100%;text-align: center;">
            <?php print theme('sub_loader', 'margin-top: 15px auto; display: block; ') ?>
          </div>
        </div>
        <div id="ui-tabs-3">
          <div style="padding: 20px; width: 100%;text-align: center;">
            <?php print theme('sub_loader', 'margin-top: 15px auto; display: block; ') ?>
          </div>
        </div>

      </div><!--/#debate_list_area -->
      <!-- END LIST -->

    </li>
  </ul>
<?php endif; ?>
