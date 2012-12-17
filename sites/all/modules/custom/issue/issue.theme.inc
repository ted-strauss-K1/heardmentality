<?php include "old.issue.theme.inc";

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
function issue_arguments_preprocess(&$vars) {
// TODO $vars['results'] = theme('issue_results_graph', $vars['node']);
//  $vars['content'] = theme('issue_arguments', $vars['node']);
}