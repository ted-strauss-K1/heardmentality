<?php







/**
 *
 */
function issue_share($nid)
{
  if (user_is_logged_in() && module_exists('rules')) {
    global $user;
    rules_invoke_event('poll_share', $user, node_load($nid));
  }
}

/**
 *
 */
function issue_subscribe() {
  $hierarchy = $_REQUEST['hierarchy'];
  $tid = preg_replace('/-.*$/', '', $hierarchy);
  $term = taxonomy_get_term($tid);

  if (!$term) {
    print json_encode(array(
      'status' => false,
      'message' => t('Unknown error'),
    ));
    exit;
  }

  // write the record
  global $user;
  $exists = (bool)subscriptions_get_subscription($user->uid, 'node', 'tid', $term->tid);
  if (!$exists) {
    subscriptions_write_subscription('node', 'tid', $term->tid, -1, $user->uid);
  } else {
    db_query(
      "DELETE FROM {subscriptions}
      WHERE
        module = '%s' AND
        field = '%s' AND
        value = '%s' AND
        author_uid = %d AND
        recipient_uid = %d",
      'node', 'tid', $term->tid, -1, $user->uid);
  }
  // output
  print json_encode(array(
    'status' => true,
    'message' => t('You have '.($exists ? 'un' : '').'subscribed '.($exists ? 'from' : 'to').' !name', array('!name' => $term->name)),
    'result' => !$exists,
  ));

  exit;
}