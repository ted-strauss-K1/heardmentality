<?php

/**
 * Implementation of hook_rules_event_info()
 *
 * @return array
 */
function badges_rules_event_info()
{
  return array(
    'badges_grant' => array(
      'label' => t('User got the badge'),
      'module' => 'Badges Module',
      'arguments' => array(
        'user' => array(
          'type' => 'user',
          'label' => t('User')
        ),
        'badge' => array(
          'type' => 'string',
          'label' => t('Badge machine name')
        ),
      ),
    ),
  );
}

/**
 * Implementation of hook_rules_action_info()
 *
 * @return array
 */
function badges_rules_action_info()
{
  return array(
    'badges_grant_badge_rules_action' => array(
      'label' => t('Grant a badge to user'),
      'arguments' => array(
        'user' => array(
          'type' => 'user',
          'label' => t('User')
        ),
      ),
      'module' => 'Badges Module',
    ),
  );
}

/**
 * @param $type
 * @param $user
 * @param array $vars
 * @param array $settings
 */
function badges_grant_badge_rules_action($user, $settings = array())
{
  badges_grant($user->uid, $settings['badge']);
}

/**
 * Settings form
 */
function badges_grant_badge_rules_action_form($settings = array(), &$form)
{
  $badges = badges_list();
  $options = array();

  foreach ($badges as $name => $info) {
    $options[$name] = $info['name'] . ' (' . $info['info'] . ')';
  }

  $form['settings']['badge'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#title' => t('Badges'),
    '#default_value' => '',
  );
}