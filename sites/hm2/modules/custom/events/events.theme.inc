<?php

/**
 * Main item theme preprocessing
 *  - do not show events when the user is disabled
 *
 * @param $vars
 */
function event_item_theme_preprocess(&$vars) {
  if ($vars['item']['account']) {
    $account = $vars['item']['account'];
    if ($account->status != 1) {
      $vars['skip'] = true;
    }
    $vars['account'] = $account;
    $vars['userlink'] = l(
      sprintf('<img class="following-user listed" src="%s" />', user_profile_image($account)),
      $account->viewlink,
      array('html' => true)
    );
  }
}

/**
 * Preprocess for "create" theme
 *
 * @param $vars
 */
function event_create_theme_preprocess(&$vars) {
  event_issue__theme_preprocess($vars);
  $vars['text'] = t('added a new issue');
}

/**
 * Preprocess common for issue-related theme
 *
 * @param $vars
 */
function event_issue__theme_preprocess(&$vars) {
  $node = node_load($vars['item']['content_id']);

  $vars['link'] = l(
    issue_translate($node, 'title'),
    $node->path,
    array()
  );
  $vars['text2'] = '';

  if ($node->status != 1) {
    $vars['skip'] = true;
  }
}

/**
 * Preprocess for "poll_vote" theme
 *
 * @param $vars
 */
function event_vote_theme_preprocess(&$vars) {
  event_issue__theme_preprocess($vars);
  $vars['text'] = t('voted on an issue');
}

/**
 * Preprocess for "debate" theme
 *
 * @param $vars
 */
function event_debate_theme_preprocess(&$vars) {
  event_debate__theme_preprocess($vars);
  if ('resource' == $vars['debate_type']) {
    $vars['text'] = t('posted a reference on the issue');
  } else {
    $vars['text'] = t('posted an argument on the issue');
  }
}

/**
 * Preprocess for "forum" theme
 *
 * @param $vars
 */
function event_debate__theme_preprocess(&$vars) {
  $debate = node_load($vars['item']['content_id']);
  $node = node_load($debate->field_reference[0]['nid']);

  $vars['link'] = l(
    issue_translate($node, 'title'),
    $node->path,
    empty($debate) ? array() : array('fragment' => 'forum-block-' . $debate->nid)
  );
  $vars['text2'] = '
    <!-- google translate -->
    <span class="goog-trans-section events_google_translate">'.
      $debate->title .
      '&nbsp;<span>[<span class="goog-trans-control translate"></span>]</span>
    </span>';
  $vars['debate_type'] = $debate->type;

  if (($node->status != 1) || ($debate->status != 1)) {
    $vars['skip'] = true;
  }
}

/**
 * Preprocess for "forum_comment" theme
 *
 * @param $vars
 */
function event_reply_theme_preprocess(&$vars) {
  event_reply__theme_preprocess($vars);
  $vars['text'] = t('replied to an argument on the issue');
}

/**
 * Preprocess for "forum" theme
 *
 * @param $vars
 */
function event_reply__theme_preprocess(&$vars) {
  $comment = _comment_load($vars['item']['content_id']);
  $debate = node_load($comment->nid);
  $node = node_load($debate->field_reference[0]['nid']);

  $vars['link'] = l(
    issue_translate($node, 'title'),
    $node->path,
    empty($debate) ? array() : array('fragment' => 'forum-block-' . $debate->nid)
  );
  $vars['text2'] = '
    <!-- google translate -->
    <span class="goog-trans-section events_google_translate">'.
    $comment->comment .
    '&nbsp;<span>[<span class="goog-trans-control translate"></span>]</span>
  </span>';

  if (!$comment->support) yn_invert_vote_value($vars['item']['vars']['vote']);

  if (($node->status != 1) || ($debate->status != 1) || ($comment->status == COMMENT_NOT_PUBLISHED)) {
    $vars['skip'] = true;
  }
}

/**
 * Preprocess for "yn" theme
 *
 * @param $vars
 */
function event_yn_theme_preprocess(&$vars) {
  switch ($vars['item']['content_type']) {
    case 'node' :
      event_debate__theme_preprocess($vars);
      $vars['text'] = (
        $vars['item']['vars']['vote'] == VOTE_AGREE ?
          t('agreed') : t('disagreed')
        ) . ' ' . t('with an argument on the issue');
    break;
    case 'comment' :
      event_reply__theme_preprocess($vars);
      $vars['text'] = (
        $vars['item']['vars']['vote'] == VOTE_AGREE ? t('strenghtened') : t('weakened')
        ) . ' ' . t('an argument on the issue');
    break;
    default : $vars['skip'] = true;
  }
}

/**
 * Preprocess for "user_profile" theme
 *
 * @param $vars
 */
function event_user_update_theme_preprocess(&$vars) {
  $vars['text'] = t('updated the profile');
}

/**
 * Preprocess for "user_follow" theme
 *
 * @param $vars
 */
function event_follow_theme_preprocess(&$vars) {
  $target = user_load($vars['item']['content_id']);

  $vars['text'] = t('now following');
  $vars['link'] = '<span class="name"><a href="' . url($target->viewlink) . '" title="' . $target->name . '">' . ucwords($target->name) . '</a></span>';
  $vars['text2'] = l(
    sprintf('<img class="following-user listed" src="%s" />', user_profile_image($target)),
    $target->viewlink,
    array('html' => true)
  );

  if ($target->uid == 0 || $target->status != 1) {
    $vars['skip'] = true;
  }
}

/**
 * Preprocess for "taxonomy" theme
 *
 * @param $vars
 */
function event_taxonomy_theme_preprocess(&$vars) {
  $node = node_load($vars['item']['content_id']);

  $vars['link'] = l(
    issue_translate($node, 'title'),
    $node->path,
    array()
  );

  if (($node->status != 1) || !module_exists('categories')) {
    $vars['skip'] = true;
    return;
  }

  global $user;
  static $data;
  if (is_null($data)) {
    $data = subscriptions_get(array(
      'recipient_uid' => $user->uid,
      'module' => 'node',
      'field' => 'tid',
      'author_uid' => -1,
    ));
  }

  if ($data) {
    foreach ($data[$user->uid]['node']['tid'] as $tid => $items) {
      if (in_array($tid, $vars['item']['vars']['tids'])) {
        $term = taxonomy_get_term($tid);
        $vars['categories'][term_hierarchy($term)] = $term->name;
      }
    }
  }

  if (empty($vars['categories'])) {
    $vars['skip'] = true;
  }
}

/**
 * Preprocess for "user_badge" theme
 *
 * todo badges event
 * @param $vars
 */
function event_user_badge_theme_preprocess(&$vars) {
  //
}

