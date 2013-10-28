<?php

/**
 * Implementation of hook_node_info().
 */
function core_node_info() {
  $items = array(
    'argument' => array(
      'name' => t('Argument'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Subject'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
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
    'resource' => array(
      'name' => t('Resource'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Subject'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
