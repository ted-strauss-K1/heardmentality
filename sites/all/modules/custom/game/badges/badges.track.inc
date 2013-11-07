<?php

/**
 * Implements custom hook_invoke_action()
 *
 * @param $timestamp
 * @param $params
 */
function badges_invoke_action($timestamp, $params) {
  $output = array('status' => FALSE);
  if (isset($params['operation'])) {
    $params['time_stamp'] = $timestamp;

    if ('badge' == $params['operation']) {
      badges_queue_action($params);
    }
    else {
      // todo queue badge
    }

    $output = events_add($params);
  }
  return $output + array('params' => $params);
}

/**
 * @param $uid
 * @param $badge
 */
function badges_queue_badge ($uid, $badge, $timestamp = false) {
  // todo check if the badge can be assigned to user
  // todo check if the badge is already queued
  // todo remove already queued badges (up to limit) (we currently support only 1 badge to user)
  // todo put the badge to the queue
}

/**
 * @param $params
 */
function badges_queue_action ($params) {
  foreach (module_implements('queue_action') as $module) {
    if ('badges' == $module) {
      continue;
    }
    $function = $module . '_queue_action';
    if (function_exists($function)) {
      $function($params);
    }
  }


  switch ($params['operation']) {
    case 'create' : break;
    case 'vote' : break;

    case 'debate' : break;
    case 'reply' : break;

    case 'yn_voteup' : break;
    case 'yn_votedn' : break;

    case 'user_update' : break;



    case 'follow' : break;
    case 'unfollow' : break;
    case 'message' : break;
    case 'weekly_pennies' : break;
    case 'register' : break;
    case 'view' : break;
    case 'login' : break;
    case 'merge' : break;
    case 'taxonomy' : break;
  }
}

/*





  body.on('badge.cpoll_vote', function(e, uid) {
    // uid - voter
    body.trigger('badges.queue', [uid, ['poll_votes_bronze', 'poll_votes_silver', 'poll_votes_gold', 'poll_votes_taxonomy_bronze', 'poll_votes_taxonomy_silver', 'poll_votes_taxonomy_gold']]);
  });

  body.on('badge.cpoll_voted', function(e, uid) {
    // uid - cpoll author
    body.trigger('badges.queue', [uid, ['poll_votes_count_bronze', 'poll_votes_count_silver', 'poll_votes_count_gold']]);
  });

  body.on('badge.comment_yn_voteup', function(e, uid) {
    // uid - content author
    body.trigger('badges.queue', [uid, [, 'yn_comment_bronze', 'yn_comment_silver', 'yn_comment_gold']]);
  });

  body.on('badge.resource_yn_voteup', function(e, uid) {
    // uid - content author
    body.trigger('badges.queue', [uid, ['yn_argument_agreed_resource_bronze', 'yn_argument_agreed_resource_silver', 'yn_argument_agreed_resource_gold']]);
  });

  body.on('badge.argument_yn_voteup', function(e, uid) {
    // uid - content author
    body.trigger('badges.queue', [uid, ['yn_argument_agreed_debate_bronze', 'yn_argument_agreed_debate_silver', 'yn_argument_agreed_debate_gold']]);
  });

  body.on('badge.yn_voteup', function(e, uid) {
    // uid - voter
    body.trigger('badges.queue', [uid, ['yn_upfirst']]);
  });

  body.on('badge.yn_predict', function(e, uid) {
    // uid - voter
    body.trigger('badges.queue', [uid, ['yn_predict_bronze', 'yn_predict_silver']]);
  });

 */
