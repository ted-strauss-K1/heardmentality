<?php

/**
 * Implementation of hook_views_handlers().
 */
function noderecommendation_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'noderecommendation') . '/views',
    ),
    'handlers' => array(
      // fields
      'noderecommendation_handler_field_data' => array( 'parent' => 'views_handler_field',),
    ),
  );
}

/**
 * Implementation of hook_views_data().
 */
function noderecommendation_views_data() {
  $data = array();

   // Definitions for uc_product_adjustments
  $data['noderecommendation_node']['table']['group'] = t('Node Recommendation');
  $noderecommendation = drupal_get_schema('noderecommendation_node');

  $data['noderecommendation_node']['table']['join']['node'] = array(
      'left_field' => 'nid',
      'field' => 'nid',
  );

  $data['noderecommendation_node']['data'] = array(
    'title' => t('Recommendation'),
    'help' => $noderecommendation['fields']['data']['description'],
    'field' => array(
      'handler' => 'noderecommendation_handler_field_data',
    ),
  );

  return $data;
}