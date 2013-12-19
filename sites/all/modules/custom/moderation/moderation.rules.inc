<?php

// This file is only for the rules

/**
 * Implementation of hook_rules_event_info()
 *
 * @return array
 */
function moderation_rules_event_info() {
  return array(
    'moderation_taxonomy' => array(
      'label'     => t('Moderator updated the categories'),
      'module'    => 'Moderation',
      'arguments' => array(
        'user' => array(
          'type'  => 'user',
          'label' => t('Acting User')
        ),
        'node' => array(
          'type'  => 'node',
          'label' => t('Issue')
        ),
        'tids' => array(
          'type'  => 'string',
          'label' => t('Taxonomy ids')
        ),
      ),
    ),
  );
}
