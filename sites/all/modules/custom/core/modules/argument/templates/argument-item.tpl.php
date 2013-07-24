<?php
  global $user;
  $nid = $node->nid;
?>
<div id="forum-block-<?php print $node->nid; ?>"
     class="one-forum <?php print $node->type ?>"
     name="<?php print $node->nid; ?>">
  <ul class="argument_box">
    <li>
      <div class="arg">
        <?php print theme('argument_result_ball', $node->vote_sum); ?>

        <!-- Content Body -->
        <div class="goog-trans-section argument_body">

          <!-- IMAGE -->
          <?php
            $image = $node->field_image_path[0]['value'];
            $youtube = $node->field_youtube[0]['value'];
            $url = $node->field_url[0]['value'];
          if ($image && !$youtube) : ?>
            <span class="pic">
              <a target="_blank" title="reference" href="<?php print $url; ?>">
                <img src="<?php print url($image, array(
                  'absolute' => true,
                  'language' => false,
                )); ?>" alt=""/>
              </a>
            </span>
          <?php endif; ?>

          <!-- TITLE -->
          <?php if ('argument' == $node->type) : ?>

            <p><?php print $node->title; ?></p>&nbsp;
            <div class="sq">[<div class="goog-trans-control translate"></div>]</div>

          <?php else : ?>

          <?php if ($youtube) : ?>

            <iframe id="ytplayer-<?php print $nid ?>"
                    src="http://www.youtube.com/embed/<?php print $youtube ?>?autoplay=0"
                    type="text/html"
                    width="400" height="250"
                    frameborder="0"/>

          <?php else : ?>

            <div class="ref_wrap">
              <h5 class="ref_title">
                <a target="_blank" title="reference" href="<?php print $url; ?>">
                  <?php print $node->title; ?>
                </a>
              </h5>
              <span class="source"><?php print t('source') ?>:
                <a target="_blank" title="reference" href="<?php print $url; ?>">
                  <?php print $node->field_source[0]['value']; ?>
                </a>
              </span>
              <?php print theme('expander', $node->body); ?>
            </div>

            <?php endif; ?>
          <?php endif; ?>

        </div>
        <!-- Content Body: END -->

        <!-- User Debate Options -->
        <?php if ('argument' == $node->type) : ?>
          <?php print theme('argument_options', $node->argument_options);  ?>
        <?php endif; ?>
        <!-- User Debate Options: END -->

        <!-- User Info -->
        <?php $account = user_load(array('uid' => $node->uid)); ?>
        <div class="userinfo-debate">
          <span class="date"><?php print t('posted'); ?>&nbsp;
            <span><?php print $node->creation_time; ?></span>
          </span>
          <a class="user-thumb" href="<?php print $account->viewlink; ?>">
            <img src="<?php print user_profile_image($account); ?>"
                 alt="<?php print $node->name; ?>" class="user-thumb">
          </a>
            <span class="name">
              <a href="<?php print $account->viewlink; ?>"><?php print $node->name; ?></a>
            </span>
        </div>
        <!-- User Info: END -->
      </div>

      <!-- Content Control Links -->
      <ul class="control_links">
        <li><?php print theme('flagger_btn_flag', $nid, 'node'); ?></li>
        <li>&nbsp;|&nbsp;<?php print theme('flagger_btn_flags', $nid, 'node'); ?></li>
        <li>&nbsp;|&nbsp;<?php print theme('flagger_btn_history', $nid, 'node'); ?></li>
        <li>&nbsp;|&nbsp;<a href="#"
                            class="flag2 permalink"
                            title="permalink"
                            name="<?php
            $url = url('node/'.$node->field_issue[0]['nid'], array('absolute' => true, 'fragment' => 'forum-block-'.$nid));
            print module_exists('shorturl') ? shorturl_shorten($url, TRUE) : addslashes($url);
            ?>"
            >link</a></li>
        <?php if ($delete = theme('argument_delete', 'node', $nid)) : ?>
        <li>&nbsp;|&nbsp;<?php print $delete; ?></li>
        <?php endif; ?>
      </ul>
      <!-- Content Control Links: END -->

      <!-- Replies -->
      <div class="replies">
        <fieldset class="collapsible collapsed reply_wrapper">
          <legend class="comment-meta">
            &#9658;
            <span
              class="replycount"><?php print count($node->comments); ?></span><span><?php print t('replies'); ?></span>
          </legend>
          <div class="fieldset-wrapper">
            <ul>
              <div id="all_replybox_<?php print $nid; ?>">
                <?php if ($node->comments) foreach ($node->comments as $comment) : ?>
                <?php
                  $comment->iid = $node->iid;
                  print theme('argument_comment', $comment);
                ?>
                <?php endforeach; ?>
              </div>
            </ul>
          </div>
        </fieldset>
      </div>
      <!-- Replies: END -->

      <!-- Reply Box -->
      <div class="position-question">
        <span class="line"><span>&nbsp;</span></span>
        <?php print theme('yn', 'node', $nid, $user->uid == $node->uid); ?>
        <ul class="argument_replybox">
          <div class="reply-comment hidden" style="display:none">
            <?php print drupal_get_form('reply_form', $nid); ?>
          </div>
        </ul>
      </div>
      <!-- Reply Box: END -->

    </li>
  </ul>
</div>