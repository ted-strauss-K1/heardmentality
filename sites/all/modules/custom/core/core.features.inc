<?php

/**
 * Implementation of hook_node_info().
 */
function core_node_info() {
  $items = array(
    'issue' => array(
      'name' => t('Issue (Redesigned)'),
      'module' => 'features',
      'description' => t('Heardmentality\'s core content type, bringing the extended poll functionality. '),
      'has_title' => '1',
      'title_label' => t('Question'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
