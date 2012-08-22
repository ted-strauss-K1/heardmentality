<?php
/*
 * Template debate-parent-template
 *
 * $item        - the debate/resource data array
 * $comments    -
 * $reply_box   -
 * $reply_count -
 * $ratings     - theme_rating_button
 * $delete      - theme_delete_button
 */
$class = $item['type'] == 'resource' ? 'resources' : '';
$diff = $item['vote_up'] - $item['vote_down'];
if ($diff <= 10 and $diff >= -10) {
  $vote_class = 'small';
}
elseif ($diff <= -100 or $diff >= 100) {
  $vote_class = "large";
}
else {
  $vote_class = 'middle';
}
$vote_type = $diff > 0 ? 'positive' : ( $diff < 0 ? 'negative' : 'null');
$userlink = url('<front>', array('absolute' => TRUE)) . '/profile/' . $item['uname'];
$item['title'] = str_replace("\r\n", "<br>", $item['title']);
$item['title'] = str_replace("\n", "<br>", $item['title']);
?>
<div
  id="forum-block-<?php print $item['content_id']; ?>"
  class="one-forum <?php print $class ?>"
  name="<?php print $item['content_id']; ?>">
  <ul class="argument_box">
    <li>
      <div class="arg">
        <span class="sum <?php print $vote_class; ?>">
          <span class="<?php print $vote_type ?>"> <?php print $diff; ?></span>
        </span>
        <div class="goog-trans-section argument_body">
<?php if (isset($item['image'])) : ?>
            <span class="pic">
              <a target="_blank" title="reference" href="<?php print $item['nlink']; ?>">
                <img src="<?php print $item['image']; ?>" alt=""/>
              </a>
            </span>
<?php endif; ?>
<?php if ($item['type'] == 'resource') : ?>
            <div class="ref_wrap">
              <h5 class="ref_title">
                <a target="_blank" title="reference" href="<?php print $item['nlink']; ?>">
  <?php print t($item['title']); ?>
                </a>
              </h5>
              <span class="source">source:
                <a target="_blank" title="reference" href="<?php print $item['nlink']; ?>">
  <?php print t($item['source']); ?>
                </a>
              </span>
              <p><?php print t($item['body']); ?></p>
            </div>
          <?php else : ?>
            <p><?php print t($item['title']); ?></p>&nbsp;<div class="sq">[<div class="goog-trans-control translate"></div>]</div>
        <?php endif; ?>
        </div>
          <?php if ($item['type'] == 'debate') : ?>
          <div class="position">
            <?php foreach ($item['strength'] as $list) : ?>
              <?php if ($list['ans_val'] == 1) : ?>
                <p class="position-plus"><strong>+</strong>&nbsp;<?php print $list['answer'] ?></p>
              <?php endif; ?>
              <?php if ($list['ans_val'] == 2) : ?>
                <p class="position-minus"><strong>-</strong>&nbsp;<?php print $list['answer'] ?></p>
            <?php endif; ?>
          <?php endforeach; ?>
          </div>
            <?php endif; ?>
        <div class="userinfo-debate">
          <span class="date">
<?php print t('posted '); ?><span><?php print $item['ago']; ?></span>
          </span>
          <a class="user-thumb" href="<?php print $userlink; ?>">
            <img src="<?php print UserPicture_small_src($item['uid']); ?>" alt="<?php print $item['uname']; ?>" class="user-thumb" >
          </a>
          <span class="name">
            <a href="<?php print $userlink; ?>"><?php print $item['uname']; ?></a>
          </span>
        </div>
      </div>

      <ul class="control_links">
        <li>
        <!-- <a href="#" class="icon flag2" title="flag this argument">flag</a> -->
        <?php print theme('flagger_button', $item['content_id'], 'node'); ?>
        </li>
        <li>&nbsp;|&nbsp;<a href="#" class="flag2 permalink" title="permalink">link</a></li>
        <?php if ($delete) : ?><li>&nbsp;|&nbsp;<?php print $delete; ?></li><?php endif; ?>
      </ul>

      <div class="replies">
        <fieldset class="collapsible collapsed reply_wrapper">
          <legend class="comment-meta">
            <?php print t('&#9658;'); ?>
            <span class="replycount"><?php print $reply_count; ?></span><span><?php print t('replies'); ?></span>
          </legend>

            <div class="fieldset-wrapper">
              <ul>
                <div id="all_replybox_<?php print $item['content_id']; ?>">
                  <?php if ($comments) : ?>
                    <?php print $comments; ?>
                  <?php endif; ?>
                </div>
              </ul>
            </div>
        </fieldset>
      </div>

      <div class="position-question">
        <span class="line"><span>&nbsp;</span></span>
<?php print $ratings; ?>
<?php if ($reply_box): ?>
          <ul class="argument_replybox">
            <div id="reply-msg-<?php print $item['content_id']; ?>" class="suc-msg"></div>
            <div id="reply-comment" class="hidden">
          <?php print $reply_box; ?>
            </div>
          </ul>
<?php endif; ?>
      </div>
    </li>
  </ul>
</div>

<!--
<div id="flag-arg-<?php print $item['content_id']; ?>" title="<?php print t('FLAG THIS ITEM'); ?>" class="form-flag" style="display: none">
  <input type="hidden" value="forum" id="flagtype" />
<?php print t('Please Wait...'); ?>
</div>
-->

<script type="text/javascript">
  $('#flag-arg-<?php print $item['content_id']; ?>').dialog({
    autoOpen: false,
    modal: false,
    minWidth: 320,
    resizable:false
  });
</script>