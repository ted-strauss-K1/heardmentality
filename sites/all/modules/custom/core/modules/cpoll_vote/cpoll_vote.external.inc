<?php

/**
 * @return null|string
 */
function cpoll_vote_external () {
  $uid = $_REQUEST['uid'];
  $chid = $_REQUEST['chid'];
  $hash = $_REQUEST['hash'];

  # validation
  if (!is_numeric($uid) || !is_numeric($chid) || ($hash != cpoll_vote_external_hash($uid, $chid))) {
    return t('An error has happened, we could not save your vote');
  }

  # vote
  cpoll_vote($chid, $uid);

  # actions
  $nid = cpoll_nid($chid);
  function_exists('action_queue') && action_queue(array(
    'uid'         => $uid,
    'operation'   => 'vote',
    'entity_id'   => $nid,
    'entity_type' => 'node',
    'chid'        => $chid,
  ));

  // reindex
  if (module_exists('issue_search')) {
    issue_search_index_node($nid);
  }

  drupal_set_message(t('Your vote was saved'));
  drupal_goto('node/' . $nid);

  return t('Your vote was saved');
}

/**
 * @param $uid
 * @param $chid
 *
 * @return string
 */
function cpoll_vote_external_hash ($uid, $chid) {
  return substr(md5($uid . ':' . $chid), 0, 6);
}

/**
 * @param      $uid
 * @param      $chid
 * @param bool $short
 *
 * @return string
 */
function cpoll_vote_external_link ($uid, $chid, $short = false) {
  $url = url('cpoll_vote/external', array(
    'query' => array(
      'uid'  => $uid,
      'chid' => $chid,
      'hash' => cpoll_vote_external_hash($uid, $chid),
    ),
    'absolute' => true,
  ));

  if ($short && module_exists('shorturl')) {
    $url = shorturl_shorten($url, TRUE);
  }

  return $url;
}