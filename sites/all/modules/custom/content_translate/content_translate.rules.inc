<?php

// This file is only for the rules

/**
 * Implementation of hook_rules_action_info()
 *
 * @return array
 */
function content_translate_rules_action_info()
{
  return array(
    'content_translate_node' => array(
      'label' => t('Translate the node to other languages'),
      'arguments' => array(
        'node' => array('type' => 'node', 'label' => t('Node')),
      ),
      'module' => 'Content Translation',
    ),
  );
}

/**
 * @param $node
 * @param array $settings
 */
function content_translate_node(&$node, $settings = array())
{
  set_time_limit(0);

  // skip re-runs
  global $content_translation;
  if (!$content_translation) {
    $content_translation = $node->nid;
  } else {
    return;
  }

  # init function
  foreach (array('poll_suggest', 'poll_ext') as $modulename) {
    if (module_exists($modulename)) {
      call_user_func($modulename . '_nodeapi', $node, 'load');
    }
  }

  # get list of available languages
  $langs = i18n_node_language_list($node, true);
  # run translations
  foreach ($langs as $lang => $name) {
    if (($lang != $node->language) && ($lang != "")) {
      module_invoke_all("content_translate_node", $node, $lang);
    }
  }

  // stop skipping re-runs
  $content_translation = false;
}