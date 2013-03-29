<?php

/**
 * @param $vars
 */
function moderation_flags_preprocess(&$vars)
{
  if (empty($vars['content_id'])) {
    if (is_numeric(arg(2))) {
      $vars['content_id'] = arg(2);
    } else {
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

  $vars['flags'] = moderation_flags($vars['content_type'], $vars['content_id']);
}

/**
 * @param $vars
 */
function moderation_item_preprocess(&$vars)
{
  $entity = $vars['entity'];
  switch ($entity->type) {
    case 'poll' :
      $vars['text'] = rtrim($entity->title);
      $vars['link'] = 'moderation/issue/'.$entity->nid;
      $vars['fragment'] = '';
    break;
    case 'forum' :
      $vars['text'] = rtrim($entity->title);
      $vars['link'] = 'node/' . $entity->field_issue[0]['nid'];
      $vars['fragment'] = 'forum-block-'.$entity->nid;
    break;
    default :
      $node = node_load($entity->nid);
      $vars['text'] = rtrim($entity->comment);
      $vars['link'] = 'node/' . $node->field_issue[0]['nid'];
      $vars['fragment'] = 'forum-block-'.$node->nid;
    break;
  }
}