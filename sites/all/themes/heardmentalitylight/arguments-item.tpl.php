<?php $nid = $node->nid; ?>
<div id="forum-block-<?php print $nid; ?>" class="one-forum" name="<?php print $nid; ?>">
  <ul class="argument_box">
    <li>
      <div class="arg">
        <?php print theme('arguments_result_ball', $node->vote_sum); ?>

        <!-- Content Body -->
        <div class="goog-trans-section argument_body">
          <?php
            $image = $node->field_filepath[0]['value'];
            $url = $node->field_nlink[0]['value'];
            $source = $node->field_source[0]['value'];
          ?>
          <?php if (isset($image)) : ?>
            <span class="pic">
              <a target="_blank" title="reference" href="<?php print $url; ?>">
                <img src="<?php print $image; ?>" alt=""/>
              </a>
            </span>
          <?php endif; ?>

          <?php if ($node->field_type[0]['value'] == TYPE_DEBATE) : ?>
            <p><?php print $node->title; ?></p>&nbsp;
            <div class="sq">[<div class="goog-trans-control translate"></div>]</div>
          <?php else : ?>
            <div class="ref_wrap">
              <h5 class="ref_title">
                <a target="_blank" title="reference" href="<?php print $url; ?>">
                  <?php print $node->title; ?>
                </a>
              </h5>
                <span class="source">source:
                  <a target="_blank" title="reference" href="<?php print $url; ?>">
                    <?php print $source; ?>
                  </a>
                </span>
              <p><?php print $node->body; ?></p>
            </div>
          <?php endif; ?>

        </div>
        <!-- Content Body: END -->

        <!-- User Debate Options -->
        <?php if ($node->field_type[0]['value'] == TYPE_DEBATE) : ?>
        <div class="position">
          <?php foreach ($node->options as $option) : ?>
            <?php if ($option['value'] == 1) : ?>
              <p class="position-plus"><strong>+</strong>&nbsp;<?php print $option['short_answer'] ?></p>
            <?php endif; ?>
          <?php if ($option['value'] == -1) : ?>
            <p class="position-minus"><strong>-</strong>&nbsp;<?php print $option['short_answer'] ?></p>
            <?php endif; ?>
          <?php endforeach; ?>
        </div>
        <?php endif; ?>
        <!-- User Debate Options: END -->

        <!-- User Info -->
        <?php $userlink = url('<front>', array('absolute' => TRUE)) . '/profile/' . $node->name; ?>
        <div class="userinfo-debate">
          <span class="date"><?php print t('posted '); ?>
            <span><?php print $node->ago; ?></span>
          </span>
          <a class="user-thumb" href="<?php print $userlink; ?>">
            <img src="<?php print UserPicture_small_src($node->uid); ?>" alt="<?php print $node->name; ?>" class="user-thumb" >
          </a>
            <span class="name">
              <a href="<?php print $userlink; ?>"><?php print $node->name; ?></a>
            </span>
        </div>
        <!-- User Info: END -->
      </div>

      <!-- Content Control Links -->
      <ul class="control_links">
        <li><?php print theme('flagger_button', $node->nid, 'node'); ?></li>
        <li>&nbsp;|&nbsp;<a href="#" class="flag2 permalink" title="permalink">link</a></li>
        <?php if ($delete = theme('arguments_delete', 'node', $nid)) : ?>
          <li>&nbsp;|&nbsp;<?php print $delete; ?></li>
        <?php endif; ?>
      </ul>
      <!-- Content Control Links: END -->

      <!-- Replies -->
      <div class="replies">
        <fieldset class="collapsible collapsed reply_wrapper">
          <legend class="comment-meta">
            &#9658;
            <span class="replycount"><?php print count($node->comments); ?></span><span><?php print t('replies'); ?></span>
          </legend>
          <div class="fieldset-wrapper">
            <ul>
              <div id="all_replybox_<?php print $nid; ?>">
                <?php foreach($node->comments as $comment) : ?>
                <?php print theme('arguments_comment', $comment); ?>
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
        <?php # print theme('arguments_rating_button', $node); ?>
        <?php print theme('yn', $node); ?>
        <ul class="argument_replybox">
          <div class="reply-comment hidden" style="display:none">
            <?php print drupal_get_form('reply_form', $node->nid); ?>
          </div>
        </ul>
      </div>
      <!-- Reply Box: END -->

    </li>
  </ul>
</div>