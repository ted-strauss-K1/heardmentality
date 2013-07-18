<?php

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
 * Preprocess for "poll" theme
 *
 * @param $vars
 */
function event_poll__theme_preprocess(&$vars) {
  $node = node_load($vars['item']['content_id']);
  $translation = module_exists('poll_translate') ?
    poll_translate_translation($node) : array();
  $vars['link'] = l(
    (!empty($translation['title'][0]) ? $translation['title'][0] : $node->title) . '?',
    $node->path,
    array()
  );
  $vars['text2'] = '';

  if ($node->status != 1) {
    $vars['skip'] = true;
  }
}

/**
 * Preprocess for "poll_create" theme
 *
 * @param $vars
 */
function event_poll_create_theme_preprocess(&$vars) {
  event_poll__theme_preprocess($vars);
  $vars['text'] = t('added a new issue');
}

/**
 * Preprocess for "poll_vote" theme
 *
 * @param $vars
 */
function event_poll_vote_theme_preprocess(&$vars) {
  event_poll__theme_preprocess($vars);
  $vars['text'] = t('voted on an issue');
}

/**
 * Preprocess for "forum" theme
 *
 * @param $vars
 */
function event_forum__theme_preprocess(&$vars) {
  $argument = node_load($vars['item']['content_id']);
  $node = node_load($argument->field_issue[0]['nid']);
  $translation = module_exists('poll_translate') ?
    poll_translate_translation($node) : array();
  $vars['link'] = l(
    (!empty($translation['title'][0]) ? $translation['title'][0] : $node->title) . '?',
    $node->path,
    empty($argument) ? array() : array('fragment' => 'forum-block-' . $argument->nid)
  );
  $vars['text2'] = '
    <!-- google translate -->
    <span class="goog-trans-section events_google_translate">'.
      $argument->title .
      '&nbsp;<span>[<span class="goog-trans-control translate"></span>]</span>
    </span>';
  $vars['argument_type'] = $argument->field_argument_type[0]['value'];

  if (($node->status != 1) || ($argument->status != 1)) {
    $vars['skip'] = true;
  }
}

/**
 * Preprocess for "forum_create" theme
 *
 * @param $vars
 */
function event_forum_create_theme_preprocess(&$vars) {
  event_forum__theme_preprocess($vars);
  if ($vars['argument_type'] == TYPE_RESOURCE) {
    $vars['text'] = t('posted a reference on the issue');
  } else {
    $vars['text'] = t('posted an argument on the issue');
  }
}

/**
 * Preprocess for "forum_vote" theme
 *
 * @param $vars
 */
function event_forum_vote_theme_preprocess(&$vars) {
  event_forum__theme_preprocess($vars);
  $vars['text'] = (
  $vars['item']['vars']['vote'] == VOTE_AGREE ?
    t('agreed') : t('disagreed')
  ) . ' ' . t('with an argument on the issue');
}

/**
 * Preprocess for "forum" theme
 *
 * @param $vars
 */
function event_forum_comment__theme_preprocess(&$vars) {
  $comment = _comment_load($vars['item']['content_id']);
  $argument = node_load($comment->nid);
  $node = node_load($argument->field_issue[0]['nid']);

  $translation = module_exists('poll_translate') ?
    poll_translate_translation($node) : array();
  $vars['link'] = l(
    (!empty($translation['title'][0]) ? $translation['title'][0] : $node->title) . '?',
    $node->path,
    empty($argument) ? array() : array('fragment' => 'forum-block-' . $argument->nid)
  );
  $vars['text2'] = '
    <!-- google translate -->
    <span class="goog-trans-section events_google_translate">'.
    $comment->comment .
    '&nbsp;<span>[<span class="goog-trans-control translate"></span>]</span>
  </span>';

  if (!$comment->support) yn_invert_vote_value($vars['item']['vars']['vote']);

  if (($node->status != 1) || ($argument->status != 1) || ($comment->status == COMMENT_NOT_PUBLISHED)) {
    $vars['skip'] = true;
  }
}

/**
 * Preprocess for "forum_comment" theme
 *
 * @param $vars
 */
function event_forum_comment_theme_preprocess(&$vars) {
  // todo
  event_forum_comment__theme_preprocess($vars);
  $vars['text'] = t('replied to an argument on the issue');
}

/**
 * Preprocess for "forum_comment_vote" theme
 *
 * @param $vars
 */
function event_forum_comment_vote_theme_preprocess(&$vars) {
  // todo
  event_forum_comment__theme_preprocess($vars);
  $vars['text'] = (
    $vars['item']['vars']['vote'] == VOTE_AGREE ? t('strenghtened') : t('weakened')
    ) . ' ' . t('an argument on the issue');
}

/**
 * Preprocess for "user_profile" theme
 *
 * @param $vars
 */
function event_user_profile_theme_preprocess(&$vars) {
  $vars['text'] = t('updated the profile');
}

/**
 * Preprocess for "user_badge" theme
 *
 * @param $vars
 */
function event_user_badge_theme_preprocess(&$vars) {
  // todo
}

/**
 * Preprocess for "user_follow" theme
 *
 * @param $vars
 */
function event_user_follow_theme_preprocess(&$vars) {
  $target = user_load($vars['item']['content_id']);

  $vars['text'] = t('now following');
  $vars['link'] = '<span class="name"><a href="' . $target->viewlink . '" title="' . $target->name . '">' . ucwords($target->name) . '</a></span>';
  $vars['text2'] = l(
    sprintf('<img class="following-user listed" src="%s" />', user_profile_image($target)),
    $target->viewlink,
    array('html' => true)
  );

  if ($target->status != 1) {
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
  $translation = module_exists('poll_translate') ?
    poll_translate_translation($node) : array();
  $vars['link'] = l(
    (!empty($translation['title'][0]) ? $translation['title'][0] : $node->title) . '?',
    $node->path,
    array()
  );

  if (($node->status != 1) || !module_exists('subscriptions')) {
    $vars['skip'] = true;
    return;
  }

  global $user;
  $data = subscriptions_get(array(
    'recipient_uid' => $user->uid,
    'module' => 'node',
    'field' => 'tid',
    'author_uid' => -1,
  ));
  if ($data) {
    $vars['item']['vars']['tids'] = explode(',', $vars['item']['vars']['tids']);
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