<?php
/*
 * Rules Events for Yes/No Module
 */

/*
 * Implementation of hook_rules_event_info()
 */
function yn_rules_event_info() {
  return array(
    'yn_voteup' => array(
      'label' => t('User voted up'),
      'module' => 'yn',
      'arguments' => array(
        'acting_user' => array(
          'type' => 'user',
          'label' => t('Acting user')
        ),
        'author' => array(
          'type' => 'user',
          'label' => t('Content\'s author')
        ),
        'content_id' => array(
          'type' => 'number',
          'label' => t('Content Id')
        ),
        'content_type' => array(
          'type' => 'string',
          'label' => t('Content type')
        ),
      ),
    ),
    'yn_votedn' => array(
      'label' => t('User voted down'),
      'module' => 'yn',
      'arguments' => array(
        'acting_user' => array(
          'type' => 'user',
          'label' => t('Acting user')
        ),
        'author' => array(
          'type' => 'user',
          'label' => t('Content\'s author')
        ),
        'content_id' => array(
          'type' => 'number',
          'label' => t('Content Id')
        ),
        'content_type' => array(
          'type' => 'string',
          'label' => t('Content type')
        ),
      ),
    ),
  );
}

  /**
   * Implementation of hook_rules_condition_info().
   */
function yn_rules_condition_info() {
  return array(
    'yn_vote_userpoints' => array(
      'label' => t('Check the points for Yes/No votes'),
      'arguments' => array(
        'author' => array('type' => 'user', 'label' => t('Content author'))
      ),
      'module' => 'yn',
    ),
  );
}

/**
 * Condition: check that user didn't get a lot of points for voting
 */
function yn_vote_userpoints($author, $settings = array()) {
  return true;
  // return $settings['number'] == 0 || (up_userpoints_today($author->uid, 'yn_vote') <= $settings['number']);
}

/**
 * Condition: check that user didn't get a lot of points for voting
 */
function yn_vote_userpoints_form($settings = array(), &$form) {
  $form['settings']['number'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of points'),
    '#default_value' => isset($settings['number']) ? $settings['number'] : 0,
    '#required' => TRUE,
  );
}

/**
 * Condition: check that user didn't get a lot of points for voting
 */
function yn_vote_userpoints_form_validate(&$form, &$form_state) {
  $post = $form_state["clicked_button"]["#post"];
  if (!is_numeric($post['number'])) {
    form_set_error('yn_vote_userpoints_form_numeric', t('Number of points should be numeric'));
  }
}

/*
 * Implementaton of hook_rules_action_info_alter()
 *
 * Update "userpoints_action_grant_points" action to make "entity_type" field evaluated
 */
function yn_rules_action_info_alter(&$actions) {
  $actions['userpoints_action_grant_points']['eval input'][] = 'entity_type';
}

