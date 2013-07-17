<?php

/**
 * @param $name
 * @param $hierarchy
 */
function theme_issue_category($name, $hierarchy) {
  drupal_add_js(drupal_get_path('module', 'issue') . "/issue.categories.js");
  static $subscriptions;
  if (module_exists('subscriptions') and is_null($subscriptions)) {
    $subscriptions = array();
    global $user;
    $data = subscriptions_get(array(
      'recipient_uid' => $user->uid,
      'module' => 'node',
      'field' => 'tid',
      'author_uid' => -1,
    ));
    if ($data)
    foreach ($data[$user->uid]['node']['tid'] as $tid => $items) {
      $subscriptions[] = $tid;
    }
    // $subscriptions[$s->recipient_uid][$s->module][$s->field][$s->value][$s->author_uid] = 1;
  }

  return  (
    module_exists('subscriptions') ?
      sprintf('<input type="checkbox" class="issue_category" title="%s" name="%s" %s>',
        t('Check to subscribe'), $hierarchy, in_array(preg_replace('/-.*$/', '', $hierarchy), $subscriptions) ? 'checked' : '') : '') .
    l($name, 'issues', array('query' => array('tids' => $hierarchy)));
}

/**
 * @param $vars
 */
function issue_block_categories_preprocess(&$vars)
{
  $nid = $vars['nid'];
  if (empty($nid)) {
    $vars['nid'] = $nid = arg(1);
  }

  if (!is_numeric($nid) || !($node = node_load($nid)) || ($node->type != 'poll')) {
    unset($vars['nid']);
    return;
  }

  // collecting info
  $vars['node'] = $node;
  foreach ($node->taxonomy as $term) {
    $vars['categories'][issue_term_parents($term)] = $term->name;
  }

  $languages = i18n_language_list();

  global $language;
  $vars['disp_langcode'] = $language->language;
  $vars['orig_langcode'] = $node->language;
  $vars['orig_path'] = $node->path;
  $vars['orig_language'] = $languages[$node->language];


}

/**
 * @param $vars
 */
function issue_block_categories_user_preprocess(&$vars)
{
  $vars['categories'] = array();

  global $user;
  if (module_exists('subscriptions')) {
    global $user;
    $data = subscriptions_get(array(
      'recipient_uid' => $user->uid,
      'module' => 'node',
      'field' => 'tid',
      'author_uid' => -1,
    ));
    if ($data) {
      foreach ($data[$user->uid]['node']['tid'] as $tid => $items) {
        $vars['categories'][$tid] = taxonomy_get_term($tid);
      }
    }
  }
}

/**
 * @param $term
 * @return string
 */
function issue_term_parents($term)
{
  $list = array();

  $terms = taxonomy_node_type_terms();

  $tmp = array();
  $tmp[] = $term->tid;

  while (!empty($tmp)) {
    $tid = array_shift($tmp);
    foreach ($terms[$tid]->parents as $ptid) {
      if (!empty($ptid)) {
        $tmp[] = $ptid;
      }
    }
    $list[] = $tid;
  }

  return implode('-', $list);
}

/**
 * @param $vars
 */
function issue_block_categories_popular_preprocess(&$vars)
{
  $result = db_query_range("
    SELECT COUNT(*) count, td.* FROM poll_votes pv
    INNER JOIN term_node tn ON tn.nid = pv.nid
    INNER JOIN term_data AS td ON td.tid = tn.tid
    GROUP BY tn.tid
    HAVING COUNT(*) <> 0
    ORDER BY count DESC
  ", 0, 15);
  while ($term = db_fetch_object($result)) {
    $vars['categories'][issue_term_parents($term)] = $term->name;
  }
}