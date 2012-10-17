<div id="msg-<?php print $id ?>" class="activity-stream">
  <li class="clearfix">
    <?php $account = user_load($uid); ?>
    <?php print l(
      sprintf('<img class="following-user listed" src="%s" />', user_profile_image($account)),
      $account->viewlink,
      array('html' => true)
    ); ?>
    <p class="action-item">
      <span class="name">
        <a href="/<?php print $account->viewlink ?>" title="<?php print $account->name ?>">
          <?php print ucwords($account->name) ?>
        </a>
      </span>

      <?php
        if (isset($vars['nid'])) {
          $node = node_load($vars['nid']);
        }
        if (isset($vars['cid'])) {
          $comment = _comment_load($vars['cid']);
        }
        if (isset($vars['nid_arg'])) {
          $argument = node_load($vars['nid_arg']);
        }
        if (isset($vars['uid'])) {
          $target = user_load($vars['uid']);
        }

        switch ($type) {
          case ACTIVITY_STREAM_FOLLOW :
            $text = 'now following';
          break;
          case ACTIVITY_STREAM_PROFILE_UPDATE :
            $text = 'updated the profile';
          break;
          case ACTIVITY_STREAM_ISSUE_CREATE :
            $text = 'added a new issue';
          break;
          case ACTIVITY_STREAM_ISSUE_VOTE :
            $text = 'voted on the issue';
          break;
          case ACTIVITY_STREAM_ARGUMENT_REPLY :
            $text = 'replied to an argument on the issue';
          break;
          case ACTIVITY_STREAM_ARGUMENT_REPLY_VOTE :
            if ($comment->str_wk == 0) yn_invert_vote_value($vars['vote']);
            $text = ($vars['vote'] == VOTE_AGREE ? 'strenghtened' : 'weakened') .
              ' an argument on the issue';
          break;
          case ACTIVITY_STREAM_ARGUMENT_CREATE :
            if (!empty($argument) && $argument->field_type[0]['value'] == TYPE_RESOURCE) {
              $text = 'posted a reference on the issue';
            } else {
              $text = 'posted an argument on the issue';
            }
          break;
          case ACTIVITY_STREAM_ARGUMENT_VOTE :
            $text = ($vars['vote'] == VOTE_AGREE ? 'agreed' : 'disagreed') .
              ' with an argument on the issue';
          break;
        }

        switch ($type) {
          case ACTIVITY_STREAM_ISSUE_CREATE :
          case ACTIVITY_STREAM_ISSUE_VOTE :
          case ACTIVITY_STREAM_ARGUMENT_REPLY :
          case ACTIVITY_STREAM_ARGUMENT_REPLY_VOTE :
          case ACTIVITY_STREAM_ARGUMENT_VOTE :
          case ACTIVITY_STREAM_ARGUMENT_CREATE :
            $link = l(
              $node->title . '?',
              $node->path,
              empty($argument) ? array() : array('fragment' => 'forum-block-'.$argument->nid)
            );
          break;
          case ACTIVITY_STREAM_FOLLOW :
            $link = '<span class="name"><a href="/'.$target->viewlink.'" title="'.$target->name.'">'.ucwords($target->name).'</a></span>';
          break;
          case ACTIVITY_STREAM_PROFILE_UPDATE :
            $link = '';
          break;

        }

        switch ($type) {
          case ACTIVITY_STREAM_ISSUE_CREATE :
          case ACTIVITY_STREAM_ISSUE_VOTE :
          case ACTIVITY_STREAM_PROFILE_UPDATE :
//          case ACTIVITY_STREAM_FOLLOW :
            $text2 = '';
          break;
          case ACTIVITY_STREAM_ARGUMENT_VOTE :
          case ACTIVITY_STREAM_ARGUMENT_CREATE :
            $text2 = $argument->title;
            break;
          case ACTIVITY_STREAM_ARGUMENT_REPLY_VOTE :
          case ACTIVITY_STREAM_ARGUMENT_REPLY :
            $text2 = $comment->comment;
          break;
          case ACTIVITY_STREAM_FOLLOW :
            $text2 = l(
              sprintf('<img class="following-user listed" src="%s" />', user_profile_image($target)),
              $target->viewlink,
              array('html' => true)
            );
          break;
        }
      ?>

      <?php print t($text); ?>
      <?php print $link; ?>
      <?php if ($text2) : ?>
        </p><p class="action-comment-ref"><?php print t($text2) ?>
        <br clear="both">
      <?php endif; ?>

    </p>
    <span class="submitted"><?php print $date; ?></span>
  </li>
</div>