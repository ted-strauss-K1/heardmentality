<?php

/*
 *
 */

/**
 * Theme issue description
 *
 * @param $text
 * @param int $charcount
 * @return string
 */
function theme_issue_description($text, $charcount = 2500)
{
  $text = trim($text);
  if (strlen($text) > $charcount) {
    $trimmed = nl2br(substr($text, 0, $charcount)) . '<div id="new-ellipse"><a>... more</a></div>';
    $extended = nl2br(substr($text, $charcount));
  } else {
    $trimmed = nl2br($text);
    $extended = '';
  }
  return '<span>' . $trimmed . '</span><span id="extended-issue-description">' . $extended . '</span>';
}

/**
 * Preprocess for "issue_arguments" theme
 *
 * @param $vars
 */
function issue_arguments_preprocess(&$vars)
{
  $vars['charts'] = theme('issue_charts', $vars['node']);

  drupal_add_js('misc/collapse.js');
  drupal_add_js(drupal_get_path('module', 'issue') . "/argument.forms.js");
  $vars['arguments'] = theme('issue_arguments_content', $vars['node']);
}

/**
 * @return string
 */
function theme_issue_arguments_content($node)
{
  // arguments form
  if (user_is_logged_in()) {
    $form = drupal_get_form('argument_form', $node);
  } else {
    $form =
      '<div class="' . theme('user_login_modal_class', true) . '" align="center">' .
        '<b>' . t('Please log in to participate in the debate') . '</b>
      </div>';
  }
  return theme('issue_arguments_content_wrapper', $node, $form);
}

/**
 * @param $vars
 */
function issue_block_categories_preprocess(&$vars) {
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
 * @param $term
 * @return string
 */
function issue_term_parents($term) {
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
function issue_block_categories_popular_preprocess(&$vars) {
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