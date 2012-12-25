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
function issue_arguments_preprocess(&$vars)
{
// TODO $vars['graphs'] = theme('issue_results_graph', $vars['node']);

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
      '<div class="' . (!module_exists('user_login_modal') ? "" : user_login_modal_class(true)) . '" align="center">' .
        '<b>' . t('Please log in to participate in the debate') . '</b>
      </div>';
  }
  return theme('issue_arguments_content_wrapper', $node, $form);
}




/*
 * STRENGTH GRAPH
 *
 *

# Prepare the data for the debate analysis
  $data = array();
  $choices = issue_choices($node->nid);
  foreach ($choices as $choice) {
    $data[] = array(
      'name' => t('Strength'),
      'color' => '#C2499B',
      'y' => 0,
    );
  }

  $result = db_query("
    SELECT ao.chorder, SUM(vv.value)*ao.val AS value
    FROM {content_type_forum} ctf
    INNER JOIN {arguments_options} ao ON ao.nid = ctf.nid
    LEFT JOIN {votingapi_vote} vv ON vv.content_id = ctf.nid AND vv.content_type = 'node'
    WHERE ctf.field_ref_qid_nid = '%d'
    GROUP BY ctf.nid, ao.chorder
    ORDER BY ao.chorder
  ", $node->nid);
  $args = array();
  while ($row = db_fetch_array($result)) {
    $args[$row['chorder']] += $row['value'];
  }
  foreach ($choices as $i => $choice) {
    $value = $args[$choice['chorder']];
    $data[$i]['color'] = $value > 0 ? '#55BA59' : '#C2499B';
    $data[$i]['y'] = (float)$value;
  }

  // SELECT 1 AS str, ctf.*, ao.* FROM `content_type_forum` ctf INNER JOIN arguments_options ao ON ao.nid = ctf.nid WHERE ctf.field_ref_qid_nid = 36981
  drupal_add_js(array('charts' => array('strength' => $data)), 'setting');
  drupal_add_js(drupal_get_path('module', 'issue') . "/js/chart.strength.js");


 *
 *
 *
 */