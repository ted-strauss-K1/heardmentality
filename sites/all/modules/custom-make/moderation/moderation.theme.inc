<?php

/**
 * @param $vars
 */
function moderation_item_preprocess(&$vars) {
  $entity = $vars['entity'];
  switch ($entity->type) {
    case 'issue' :
      $vars['text'] = rtrim($entity->title);
      $vars['link'] = 'moderation/issue/' . $entity->nid;
      $vars['fragment'] = '';
      break;
    case 'argument' :
    case 'resource' :
      $vars['text'] = rtrim($entity->title);
      $vars['link'] = 'node/' . $entity->field_reference[0]['nid'];
      $vars['fragment'] = 'forum-block-' . $entity->nid;
      break;
    default :
      $node = node_load($entity->nid);
      $vars['text'] = rtrim($entity->comment);
      $vars['link'] = 'node/' . $node->field_reference[0]['nid'];
      $vars['fragment'] = 'forum-block-' . $node->nid;
      break;
  }
}

/**
 * @param $vars
 */
function moderation_flags_preprocess(&$vars) {
  if (empty($vars['content_id'])) {
    if (is_numeric(arg(2))) {
      $vars['content_id'] = arg(2);
    }
    else {
      return array();
    }
  }

  if (empty($vars['content_type'])) {
    switch (arg(1)) {
      case 'issue' :
      case 'argument' :
        $vars['content_type'] = 'node';
        break;
      case 'comment' :
        $vars['content_type'] = 'comment';
        break;
      default :
        return array();
    }
  }

  $vars['flags'] = flagger_get_flags($vars['content_type'], $vars['content_id']);
}

/**
 * @param $vars
 */
function moderation_related_preprocess(&$vars) {
  if (empty($vars['content_id'])) {
    if (is_numeric(arg(2))) {
      $vars['content_id'] = arg(2);
    }
    else {
      return array();
    }
  }

  $block = apachesolr_search_mlt_block_load('mlt-001');
  $solr = apachesolr_get_solr();
  $docs = apachesolr_search_mlt_suggestions($block, apachesolr_document_id($vars['content_id']), $solr);

  $vars['related'] = $docs;
}
