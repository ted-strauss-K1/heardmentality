<?php

/**
 * Implementation of hook_rules_condition_info()
 */
function ranks_rules_condition_info()
{
  return array(
    'ranks_user_new_rank' => array(
      'label' => t('User Got New Rank'),
      'arguments' => array(
        'user' => array('type' => 'user', 'label' => t('Acting user')),
      ),
      'module' => 'Ranks',
    ),
  );

}

/**
 * Condition: ranks_user_new_rank
 */
function ranks_user_new_rank($user)
{
  $rank_prev = $user->rank;
  up_userpoints_get($user->uid, '', true); // to refresh the userpoints
  $rank_new = ranks_user_rank($user->uid);
  return $rank_new['id'] > $rank_prev['id'];
}