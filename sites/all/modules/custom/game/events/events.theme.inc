<?php

/**
 * @return array
 */
function events_content_translate_rebuild_js() {
  $path = drupal_get_path('module', 'events');
  return array(
    $path . '/events.js' => array(
      'second',
      'seconds',
      'minute',
      'minutes',
      'hour',
      'hours',
      'day',
      'days',
      'week',
      'weeks',
      'month',
      'months',
      'year',
      'years',
      'ago',
      'just now',
    ),
  );
}

/**
 *
 */
define('EVENTS_THEME_PREFIX', 'event_item_');

/**
 * Implementation of hook_theme()
 *
 * @return array
 */
function events_theme() {
  $theme = array();

  $theme['events'] = array(
    'arguments'            => array(
      'items'    => array(),
      'settings' => array(),
    ),
    'preprocess functions' => array('theme_events_theme_preprocess'),
    'template'             => 'templates/events',
  );
  $theme['events_item'] = array(
    'arguments' => array(
      'item' => array(),
    ),
  );

  return $theme + events_theme_items();
}

/**
 * Preprocess for theme "events"
 *
 * @param $vars
 */
function theme_events_theme_preprocess(&$vars) {
  drupal_add_js(drupal_get_path('module', 'events') . '/events.translate.js');
  if (isset($vars['settings']['update'])) {
    drupal_add_js(drupal_get_path('module', 'events') . '/events.update.js');
  }
}

/**
 * @param $item
 *
 * @return mixed|string
 */
function theme_events_item($item) {
  static $themes = NULL;

  if (is_null($themes)) {
    $themes = events_theme_items();
  }

  $item['type'] = EVENTS_THEME_PREFIX . $item['operation'];

  $classes = array();
  $classes[] = 'activity-stream';
  $classes[] = 'msg';
  $classes[] = 'msg-' . $item['type'];
  $classes[] = 'uid-' . $item['uid'];
  $classes[] = 'entity_id-' . $item['entity_id'];
  $classes[] = 'entity_type-' . $item['entity_type'];

  return isset($themes[$item['type']]) && ($content = theme($item['type'], $item)) ? '<div name="' . $item['id'] . '" id="msg-' . $item['id'] . '" class="' . implode(' ', $classes) . '">' . $content . '</div>' : '';
}

/**
 * Function to add the custom themes for item types
 *
 * @return array
 */
function events_theme_items() {
  $theme = array();

  $items = events_operations();

  foreach ($items as $event) {
    $themename = EVENTS_THEME_PREFIX . $event;

    $theme[$themename] = array(
      'arguments'            => array(
        'item' => array(),
      ),
      'preprocess functions' => array(
        'theme_events_item_default_theme_preprocess',
        'theme_events_item_' . $event . '_theme_preprocess',
      ),
      'file'                 => 'events.theme.inc',
      'template'             => 'templates/events-item-' . $event,
      //      'template' => 'template-event-'.$event,
    );
  }

  return $theme;
}

/**
 * Main item theme preprocessing
 *  - do not show events when the user is disabled
 *
 * @param $vars
 */
function theme_events_item_default_theme_preprocess(&$vars) {
  if ($vars['item']['account']) {
    $account = $vars['item']['account'];
    if ($account->status != 1) {
      $vars['skip'] = TRUE;
    }
    $vars['account'] = $account;
    $vars['userlink'] = l(sprintf('<img class="following-user listed" src="%s" />', user_profile_image($account)), $account->viewlink, array('html' => TRUE));
  }
}

/**
 * @param $vars
 */
function theme_events_item_create_theme_preprocess(&$vars) {
  theme_events_item__issue_theme_preprocess($vars);
  $vars['text'] = t('added a new issue');
}

/**
 * @param $vars
 */
function theme_events_item_vote_theme_preprocess(&$vars) {
  theme_events_item__issue_theme_preprocess($vars);
  $vars['text'] = t('voted on an issue');
}

/**
 * @param $vars
 */
function theme_events_item_follow_theme_preprocess(&$vars) {
  $target = user_load($vars['item']['entity_id']);

  $vars['text'] = t('now following');
  $vars['link'] = '<span class="name"><a href="' . url($target->viewlink) . '" title="' . $target->name . '">' . ucwords($target->name) . '</a></span>';
  $vars['text2'] = l(sprintf('<img class="following-user listed" src="%s" />', user_profile_image($target)), $target->viewlink, array('html' => TRUE));

  if ($target->uid == 0 || $target->status != 1) {
    $vars['skip'] = TRUE;
  }
}

/**
 * @param $vars
 */
function theme_events_item_debate_theme_preprocess(&$vars) {
  theme_events_item__debate_theme_preprocess($vars);
  if ('resource' == $vars['debate_type']) {
    $vars['text'] = t('posted a reference on the issue');
  }
  else {
    $vars['text'] = t('posted an argument on the issue');
  }
}

/**
 * @param $vars
 */
function theme_events_item_reply_theme_preprocess(&$vars) {
  theme_events_item__reply_theme_preprocess($vars);
  $vars['text'] = t('replied to an argument on the issue');
}

/**
 * @param $vars
 */
function theme_events_item_taxonomy_theme_preprocess(&$vars) {
  theme_events_item__issue_theme_preprocess($vars);

  if (!module_exists('categories')) {
    $vars['skip'] = TRUE;
    return;
  }

  global $user;
  static $tids;
  if (is_null($tids)) {
    $subscription = simplenews_get_subscription((object) array('mail' => $user->mail));
    $tids = $subscription->tids;
  }

  foreach ($tids as $tid) {
    if (in_array($tid, $vars['item']['vars']['tids'])) {
      $term = taxonomy_get_term($tid);
      $vars['categories'][term_hierarchy($term)] = $term->name;
    }
  }

  if (empty($vars['categories'])) {
    $vars['skip'] = TRUE;
  }
}

/**
 * @param $vars
 */
function theme_events_item_user_update_theme_preprocess(&$vars) {
  $vars['text'] = t('updated the profile');
}

/**
 * @param $vars
 */
function theme_events_item_yn_voteup_theme_preprocess(&$vars) {
  theme_events_item__yn_theme_preprocess($vars);
}

/**
 * @param $vars
 */
function theme_events_item_yn_votedn_theme_preprocess(&$vars) {
  theme_events_item__yn_theme_preprocess($vars);
}

/**
 * Additional preprocesses
 */
function theme_events_item__issue_theme_preprocess(&$vars) {
  $node = node_load($vars['item']['entity_id']);

  $vars['link'] = l(issue_translate($node, 'title'), $node->path, array());
  $vars['text2'] = '';

  if ($node->status != 1) {
    $vars['skip'] = TRUE;
  }
}

/**
 * Additional preprocess
 */
function theme_events_item__debate_theme_preprocess(&$vars) {
  $debate = node_load($vars['item']['entity_id']);
  $node = node_load($debate->field_reference[0]['nid']);

  $vars['link'] = l(issue_translate($node, 'title'), $node->path, empty($debate) ? array() : array('fragment' => 'forum-block-' . $debate->nid));
  $vars['text2'] = '
    <!-- google translate -->
    <span class="goog-trans-section events_google_translate">' . $debate->title . '&nbsp;<span class="sq">[<span class="goog-trans-control translate"></span>]</span>
  </span>';
  $vars['debate_type'] = $debate->type;

  if (($node->status != 1) || ($debate->status != 1)) {
    $vars['skip'] = TRUE;
  }
}

/**
 * Additional preprocess
 */
function theme_events_item__reply_theme_preprocess(&$vars) {
  $comment = _comment_load($vars['item']['entity_id']);
  $debate = node_load($comment->nid);
  $node = node_load($debate->field_reference[0]['nid']);

  $vars['link'] = l(issue_translate($node, 'title'), $node->path, empty($debate) ? array() : array('fragment' => 'forum-block-' . $debate->nid));
  $vars['text2'] = '
    <!-- google translate -->
    <span class="goog-trans-section events_google_translate">' . $comment->comment . '&nbsp;<span class="sq">[<span class="goog-trans-control translate"></span>]</span>
  </span>';

  if (!$comment->support) {
    yn_invert_vote_value($vars['item']['vars']['vote']);
  }

  if (($node->status != 1) || ($debate->status != 1) || ($comment->status == COMMENT_NOT_PUBLISHED)) {
    $vars['skip'] = TRUE;
  }
}

/**
 * Additional preprocess
 */
function theme_events_item__yn_theme_preprocess(&$vars) {
  switch ($vars['item']['entity_type']) {
    case 'node' :
      theme_events_item__debate_theme_preprocess($vars);
      $vars['text'] = ($vars['item']['vars']['vote'] == VOTE_AGREE ? t('agreed') : t('disagreed')) . ' ' . t('with an argument on the issue');
      break;
    case 'comment' :
      theme_events_item__reply_theme_preprocess($vars);
      $vars['text'] = ($vars['item']['vars']['vote'] == VOTE_AGREE ? t('strenghtened') : t('weakened')) . ' ' . t('an argument on the issue');
      break;
    default :
      $vars['skip'] = TRUE;
  }
}

/**
 * Implementation of hook_block
 *
 * @param string $op
 * @param int    $delta
 * @param array  $edit
 *
 * @return mixed
 */
function events_block($op = 'list', $delta = 0, $edit = array()) {
  switch ($op) {
    case 'list':
      $blocks['events-front'] = array(
        'info' => t('Front Events'),
      );
      return $blocks;
    case 'view':
      switch ($delta) {
        case 'events-front' :
          $block['subject'] = t('HAPPENING NOW');

          $request = events_build_query(array(
            array(
              'operation' => array(
                'create',
                'debate',
                'reply',
                'vote',
                'follow',
                'yn_voteup',
                'yn_votedn',
                'taxonomy',
              ),
            ),
          ));
          $block['content'] = theme('events', events_get($request['query'], $request['vars']), array('update' => TRUE));

          break;
      }
      return $block;
  }
}
