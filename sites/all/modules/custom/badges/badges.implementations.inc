<?php

/*
 * This file is to contain the badges' implementation functions
 *
 * @params - $uid - User Id
 *
 * @return - TRUE/FALSE
 */

/**
 * Helper function for
 *  _badge_voted_in_many_blc()
 */
function _badge_get_vid_by_name($name)
{
  $name = str_replace('-', ' ', $name);
  $object = db_fetch_object(db_query("SELECT vid FROM {vocabulary} WHERE name = '%s'", $name));
  return $object ? $object->vid : 0;
}

/**
 * Helper function for
 *  _badge_voted_in_many_blc()
 *
 * Get Bottom-level Categories
 */
function _badge_bottom_level_terms($vid)
{
  static $_list = array();
  if (isset($list[$vid])) {
    return $list[$vid];
  }
  $list = array();
  $terms = taxonomy_get_tree($vid);
  foreach ($terms as $term) {
    $list[$term->tid] = $term;
    foreach ($term->parents as $parent) {
      if ($parent != 0) {
        unset($list[$parent]);
      }
    }
  }
  $_list[$vid] = array_keys($list);
  return $_list[$vid];
}

/**
 * Helper for
 *  badge_process_generalist()
 *  badge_process_well_read()
 *  badge_process_scholar()
 */
function _badge_voted_in_many_blc($uid, $count_vote, $count_blc)
{
  # bottom-level categories
  $vid = _badge_get_vid_by_name('Sections');
  $blc = _badge_bottom_level_terms($vid);
  $blc_implode = implode(',', $blc);
  if ($blc == '') {
    return false;
  }
  # check
  $data = db_fetch_array(db_query("
    SELECT COUNT(DISTINCT(tn.nid)) AS nids, COUNT(DISTINCT(tn.tid)) AS tids
    FROM {poll_votes} pv INNER JOIN {term_node} tn ON tn.nid = pv.nid
    WHERE pv.uid = '%d' AND tn.tid IN (%s)",
    $uid, $blc_implode
  ));
  return $data['nids'] >= $count_vote && $data['tids'] >= $count_blc;
}

/**
 * User has voted on at least 20 issues in 30 topics
 *
 * Group: poll vote
 */
function badge_process_scholar($uid)
{
  return _badge_voted_in_many_blc($uid, 20, 30);
}

/**
 * Helper for
 *  badge_process_provocative_question()
 *  badge_process_great_question()
 *  badge_process_nice_question()
 */
function _badge_issue_voted($uid, $count)
{
  return $count <= (int)db_result(db_query("SELECT COUNT(*) FROM {node} n INNER JOIN {poll_votes} pv ON pv.nid = n.nid WHERE n.uid = '%d' AND n.type = 'poll' GROUP BY n.nid ORDER BY COUNT(*) DESC", $uid));
}

/**
 * Issue you added is voted on 1000 times
 *
 * @param $uid
 * @return bool
 *
 * Group: poll vote
 */
function badge_process_provocative_question($uid)
{
  _badge_issue_voted($uid, 1000);
}

/**
 * First agree on a post or resource that eventually gets 100 agrees
 *
 * Group: yn vote
 */
function badge_process_oracle($uid)
{
  return _badge_first_vote_supernode($uid, 100);
}

/**
 * First agree on a post or resource that eventually gets 50 agrees
 *
 * Group: yn vote
 */
function badge_process_seer($uid)
{
  return _badge_first_vote_supernode($uid, 50);
}

/**
 * Helper for
 *  badge_process_provocative_issue()
 *  badge_process_popular_question()
 *  badge_process_notable_issue()
 */
function _badge_issue_views($uid, $count)
{
  return $count <= (int)db_result(db_query("SELECT totalcount FROM {node} n INNER JOIN {node_counter} nc ON n.nid = nc.nid WHERE n.uid = '%d' AND n.type = 'poll' ORDER BY totalcount DESC", $uid));
}

/**
 * Posted an Issue with 10,000 views
 *
 * Group: page visit
 */
function badge_process_provocative_issue($uid)
{
  return _badge_issue_views($uid, 10000);
}

/**
 * Helper for
 *  badge_process_senator()
 *  badge_process_pamphleteer()
 *  badge_process_pundit()
 */
function _badge_posted_agreed_comments($uid, $count)
{
  return $count <= (int)db_result(db_query("
    SELECT COUNT(DISTINCT(c.cid))
    FROM {comments} c INNER JOIN {votingapi_vote} vv ON vv.content_id = c.cid
    WHERE c.uid = %d AND vv.content_type = 'comment' AND vv.value = %d",
    $uid, VOTE_AGREE
  ));
}

/**
 * Left 500 comments that got a minimum of one agree.
 *
 * Group: yn vote
 */
function badge_process_senator($uid)
{
  return _badge_posted_agreed_comments($uid, 500);
}

/**
 * Left 10 comments that got a minimum of 1 agree.
 *
 * Group: yn vote
 */
function badge_process_pamphleteer($uid)
{
  return _badge_posted_agreed_comments($uid, 10);
}

/**
 * Helper for
 *  badge_process_patriotic_citizen()
 *  badge_process_civic_duty()
 */
function _badge_user_votes($uid, $count)
{
  # count different types of votes
  $count_pv = issue_get_uservotes($uid);
  $count_sa = issue_sa_count($uid);
  $count_ud = yn_user_vote_count($uid);
  return $count_pv + $count_sa + $count_ud >= $count;
}

/**
 * Voted 1000 times
 *
 * @param $uid
 * @return bool
 *
 * Group: poll vote, yn vote
 */
function badge_process_patriotic_citizen($uid)
{
  return _badge_user_votes($uid, 1000);
}

/**
 * Flags post, that eventually results in a change or removal
 *
 * Group: node hide
 */
function badge_process_scrutineer($uid)
{
  return (bool)db_result(db_query("SELECT * FROM {node} n INNER JOIN {flag_content} fc ON fc.content_id = n.nid WHERE n.status = 0 AND n.type = 'forum' AND fc.uid = '%d'", $uid));
}

/**
 * Active member for a year, earning at least 200 reputation
 *
 * Group: cron
 */
function badge_process_yearling($uid)
{
  $count_points = 200;
  if ($count_points <= up_userpoints_get($uid)) {
    return false != db_result(db_query("SELECT * FROM {users} WHERE created < ADDDATE(CURDATE(), INTERVAL -1 YEAR) AND uid = '%d'", $uid));
  }
  return false;
}

/**
 * Helper for
 *  badge_process_paperboy()
 */
function _badge_resource_has_votes($uid, $count)
{
  return $count <= db_result(db_query("SELECT COUNT(*) FROM {node} n INNER JOIN {content_type_forum} ctf ON ctf.nid = n.nid INNER JOIN {votingapi_vote} vv ON vv.content_id = n.nid WHERE n.uid = '%d' AND n.type = 'forum' AND ctf.field_type_value = '%d' AND vv.value = '%d' AND vv.content_type = 'node' GROUP BY (n.nid) ORDER BY COUNT(*) DESC", $uid, TYPE_RESOURCE, VOTE_AGREE));
}

/**
 * Resource Posted by user gets 5 agrees
 *
 * Group: yn vote
 */
function badge_process_paperboy($uid)
{
  return _badge_resource_has_votes($uid, 5);
}

/**
 * Resource Posted by user gets 20 agrees
 *
 * Group: yn vote
 */
function badge_process_newsstand($uid)
{
  return _badge_resource_has_votes($uid, 20);
}


/**
 * User has voted on at least 10 issues in 20 topics
 *
 * Group: poll vote
 */
function badge_process_well_read($uid)
{
  return _badge_voted_in_many_blc($uid, 10, 20);
}

/**
 * First to suggest answers that eventually gets approved
 *
 * Group: poll vote
 *
 * TODO
 */
function ___badge_process_provocateur($uid)
{
  return false;
}

/**
 * Philosopher
 * Becoming a Top 5 Pundit in a top level category
 *
 * @param $uid
 * @return bool
 */

/**
 * Helper for
 *  badge_process_healthy_debate()
 *  badge_process_cocktail_party()
 */
function _badge_issue_arguments($uid, $count)
{
  return $count <= (int)db_result(db_query("SELECT COUNT(DISTINCT ctf.nid) + COUNT(*) FROM {content_type_forum} ctf INNER JOIN {node} n ON n.nid = ctf.field_ref_qid_nid INNER JOIN {comments} c ON c.nid = ctf.nid WHERE n.uid = '%d' AND c.cid = c.tcid", $uid));
}

/**
 * Created a question that resulted in 100 debate posts or resource posts (including replies)
 *
 * @param $uid
 * @return bool
 *
 * Group: argument create, comment create
 */
function badge_process_healthy_debate($uid)
{
  return _badge_issue_arguments($uid, 100);
}

/**
 * Created a question that resulted in 50 debate posts or resource posts (including replies)
 *
 * @param $uid
 * @return bool
 *
 * Group: argument create, comment create
 */
function badge_process_cocktail_party($uid)
{
  return _badge_issue_arguments($uid, 50);
}

/**
 * Created a question that resulted in 50 debate posts or resource posts (including replies)
 *
 * Group: argument create, comment create
 */
function badge_process_conversation_piece($uid)
{
  return _badge_issue_arguments($uid, 20);
}

/**
 * Helper for
 *  badge_process_consensus_builder()
 *  badge_process_well_put()
 *  badge_process_nice_post)
 */
function _badge_argument_has_votes($uid, $count, $type)
{
  return $count <= db_result(db_query("SELECT n.nid, COUNT(*)FROM node n INNER JOIN content_type_forum ctf ON ctf.nid = n.nid INNER JOIN votingapi_vote vv ON vv.content_id = n.nid WHERE n.uid = '%d' AND ctf.field_type_value = '%d' AND vv.value = '%d' AND vv.content_type = 'node' GROUP BY n.nid ORDER BY COUNT(*) DESC", $uid, $type, VOTE_AGREE));
}

/**
 * Debate Posted by user gets 50 agrees
 *
 * Group: yn vote
 */
function badge_process_consensus_builder($uid)
{
  return _badge_argument_has_votes($uid, 50, TYPE_DEBATE);
}

/**
 * Debate Posted by user gets 20 agrees
 *
 * Group: yn vote
 */
function badge_process_well_put($uid)
{
  return _badge_argument_has_votes($uid, 20, TYPE_DEBATE);
}

/**
 * Debate Posted by user gets 5 agrees
 *
 * Group: yn vote
 */
function badge_process_nice_post($uid)
{
  return _badge_argument_has_votes($uid, 5, TYPE_DEBATE);
}

/**
 * Resource Posted by user gets 50 agrees
 *
 * Group: yn vote
 */
function badge_process_librarian($uid)
{
  return _badge_argument_has_votes($uid, 50, TYPE_RESOURCE);
}

/**
 * Created a tag used by 50 questions
 *
 * TODO
 */
function ___badge_process_taxonomist($uid)
{
  return false;
}

/**
 * Helper function for
 *  badge_process_supporter()
 *  badge_process_seer()
 *  badge_process_oracle()
 */
function _badge_first_vote_supernode($uid, $count)
{
  $result = db_query("SELECT uid FROM {votingapi_vote} WHERE value = '%d' GROUP BY content_type, content_id HAVING COUNT(*) >= %d ORDER BY timestamp", VOTE_AGREE, $count);
  while ($row = db_fetch_object($result)) {
    if ($row->uid == $uid) {
      return true;
    }
  }
  return false;
}

/**
 * First agree on a post or resource that eventually gets 10 agrees
 *
 * Group: yn vote
 */
function badge_process_supporter($uid)
{
  return _badge_first_vote_supernode($uid, 10);
}

/**
 * Helper for
 *  badge_process_good_answer()
 */
function _badge_answer_voteups($uid, $count)
{
  return false != db_result(db_query("SELECT * FROM {comments} c LEFT JOIN {votingapi_vote} vv ON vv.content_id = c.cid WHERE c.uid = %d AND vv.content_type = 'comment' GROUP BY c.cid HAVING COUNT(*) > %d", $uid, $count));
}

/**
 * Answer voted up 25 times
 *
 * Group: yn vote
 */
function badge_process_good_answer($uid)
{
  return _badge_answer_voteups($uid, 25);
}

/**
 * User has voted on at least 5 issues in 10 topics
 *
 * Group: poll vote
 */
function badge_process_generalist($uid)
{
  return _badge_voted_in_many_blc($uid, 5, 10);
}

/**
 * Helper for
 *  badge_process_enthusiast()
 *  badge_process_fanatic()
 *
 * TODO
 */
function _badge_consecutive_visits($uid, $count)
{
  return false;
}

/**
 * Visited the site each day for 100 consecutive days
 */
function ___badge_process_fanatic($uid)
{
  return _badge_consecutive_visits($uid, 100);
}

/**
 * Visited the site each day for 30 consecutive days
 */
function ___badge_process_enthusiast($uid)
{
  return _badge_consecutive_visits($uid, 30);
}

/**
 * Voted on 600 questions and 25% or more of total votes are on questions
 *
 * Group: poll vote, yn vote
 */
function badge_process_electorate($uid)
{
  $count_vote = 600;
  $count_pv_part = 4;
  # count different types of votes
  $count_pv = issue_get_uservotes($uid);
  $count_sa = issue_sa_count($uid);
  $count_ud = yn_user_vote_count($uid);
  return ($count_pv + $count_sa + $count_ud >= $count_vote) && ($count_pv_part * $count_pv >= $count_vote);
}

/**
 * Left 10 comments
 *
 * Group: comment create
 */
function badge_process_commentator($uid)
{
  $count = 10;
  return $count <= (int)db_result(db_query("SELECT COUNT(*) FROM {comments} WHERE uid = '%d' AND cid != tcid", $uid));
}

/**
 * Voted 300 times
 *
 * @param $uid
 * @return bool
 *
 * Group: poll vote, yn vote
 */
function badge_process_civic_duty($uid)
{
  return _badge_user_votes($uid, 300);
}

/**
 * First flagged post
 *
 * Group: flag
 */
function badge_process_citizen_patrol($uid)
{
  $result = db_query("SELECT uid FROM {flag_content} fc GROUP BY content_type, content_id ORDER BY timestamp DESC");
  while ($row = db_result($result)) {
    if ($uid == $row) {
      return true;
    }
  }
  return false;
}

/**
 * Answer voted up 100 times
 *
 * Group: yn vote
 */
function badge_process_great_answer($uid)
{
  return _badge_answer_voteups($uid, 100);
}

/**
 * Issue you added is voted on 200 times
 *
 * Group: poll vote
 */
function badge_process_great_question($uid)
{
  return _badge_issue_voted($uid, 200);
}

/**
 * Suggesting answers to the questions
 *
 * @param $uid
 * @return bool
 */
function badge_process_suggest_answer($uid)
{
  return (bool)db_result(db_query("SELECT COUNT(*) FROM {poll_suggest} WHERE uid = '%d'", $uid));
}

/**
 * Referring a friend
 *
 * @param $uid
 * @return bool
 */
function ___badge_process_recruiter($uid)
{
  return false;
}

/**
 * Pundit
 * Becoming a Top 5 Pundit in a second level category
 *
 * @param $uid
 * @return bool
 */

/**
 * Asked an issue with 1,000 views
 */
function badge_process_popular_question($uid)
{
  return _badge_issue_views($uid, 1000);
}

/**
 * First Retag
 *
 * TODO
 */
function ___badge_process_organizer($uid)
{
  return false;
}

/*
 * Posted an Issue with 2,500 views
 */
function badge_process_notable_issue($uid)
{
  return _badge_issue_views($uid, 2500);
}

/**
 * Issue you added is voted on 1000 times
 */
function badge_process_nice_question($uid)
{
  return _badge_issue_voted($uid, 1000);
}

/**
 * Answer voted up 10 times
 */
function badge_process_nice_answer($uid)
{
  return _badge_answer_voteups($uid, 10);
}

/**
 * Hit the daily reputation cap on 150 days
 *
 * TODO
 */
function ___badge_process_legendary($uid)
{
  return false;
}

/**
 * Completed all user profile fields
 */
function badge_process_autobiographer($uid)
{
  $user = user_load(array('uid' => $uid));
  $complete_data = pcp_get_complete_percentage_data($user);
  return $complete_data['percent'] == 100;
}