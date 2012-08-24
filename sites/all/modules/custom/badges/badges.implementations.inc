<?php

/*
 * This file is to contain the badges' implementation functions
 *
 * @params - $uid - User Id
 *
 * @return - TRUE/FALSE
 */

/*
 * Completed all user profile fields
 */
function badge_process_autobiographer($uid) {
  $user = user_load(array('uid' => $uid));
  $complete_data = pcp_get_complete_percentage_data($user);
  return $complete_data['percent'] == 100;
}

/*
 * First flagged post
 */
function badge_process_citizen_patrol($uid) {
  // TODO
  return false;
}

/*
 * Voted 300 times
 */
function badge_process_citizen($uid) {
  return _badge_user_votes($uid, 300);
}

/*
 * Voted 1000 times
 */
function badge_process_active_citizen($uid) {
  return _badge_user_votes($uid, 1000);
}

/*
 * Helper for
 *  badge_process_citizen()
 *  badge_process_active_citizen()
 */
function _badge_user_votes($uid, $count) {
  // TODO
  # count different types of votes
  $count_pv = db_result(db_query("SELECT COUNT(*) FROM {poll_votes} WHERE uid = '%d'", $uid));
  $count_sa = db_result(db_query("SELECT COUNT(*) FROM (suggest_answer_vote) WHERE uid = '%d' GROUP BY uid", $uid));
  $count_ud = yn_user_vote_count($uid);
  return $count_pv + $count_sa + $count_ud >= $count;
}


/*
 * Left 10 comments
 *
function badge_process_commentator($uid) {
  $comment_count = 10;
  $comments = db_result(db_query("SELECT COUNT(DISTINCT(c.cid)) FROM {comments} c WHERE c.uid = %d", $uid));
  return $comments >= $comment_count;
}
*/

/*
 * Voted on 600 questions and 25% or more of total votes are on questions
 */
function badge_process_electorate($uid) {
  // TODO
  $count_vote = 600;
  $count_pv_part = 4;
  # count different types of votes
  $count_pv = db_result(db_query("SELECT COUNT(*) FROM {poll_votes} WHERE uid = '%d'", $uid));
  $count_sa = db_result(db_query("SELECT COUNT(*) FROM (suggest_answer_vote) WHERE uid = '%d' GROUP BY uid", $uid));
  $count_ud = yn_user_vote_count($uid);
  return ($count_pv + $count_sa + $count_ud >= $count_vote) && ($count_pv_part*$count_pv >= $count_vote);
}

/*
 * Visited the site each day for 30 consecutive days
 */
function badge_process_enthusiast($uid) {
  return _badge_consecutive_visits($uid, 30);
}

/*
 * Visited the site each day for 100 consecutive days
 */
function badge_process_fanatic($uid) {
  return _badge_consecutive_visits($uid, 100);
}

/*
 * Helper for
 *  badge_process_enthusiast()
 *  badge_process_fanatic()
 */
function _badge_consecutive_visits($uid, $count) {
  // TODO
  return false;
}

/*
 * Asked a question with 1,000 views
 */
function badge_process_popular_question($uid) {
  return _badges_question_viewed($uid, 1000);
}

/*
 * Asked a question with 2,500 views
 */
function badge_process_notable_question($uid) {
  return _badges_question_viewed($uid, 2500);
}

/*
 * Asked a question with 10,000 views
 */
function badge_process_famous_question($uid) {
  return _badges_question_viewed($uid, 10000);
}

/*
 * Helper for
 *  badge_process_popular_question()
 *  badge_process_notable_question()
 *  badge_process_famous_question()
 */
function _badges_question_viewed($uid, $count) {
  // TODO
  return false;
}

/*
 * Question favorited by 25 users
 */
function badge_process_favorite_question($uid) {
  // TODO
  return false;
}

/*
 * Answer voted up 10 times
 */
function badge_process_nice_answer($uid) {
  return _badge_answer_voteups($uid, 10);
}

/*
 * Answer voted up 25 times
 */
function badge_process_good_answer($uid) {
  return _badge_answer_voteups($uid, 25);
}

/*
 * Answer voted up 100 times
 */
function badge_process_great_answer($uid) {
  return _badge_answer_voteups($uid, 100);
}

/*
 * Helper for
 *  badge_process_nice_answer()
 *  badge_process_good_answer()
 *  badge_process_great_answer()
 */
function _badge_answer_voteups($uid, $count) {
  // TODO
  return false;
}

/*
 * Issue you added is voted on 50 times
 */
function badge_process_good_question($uid) {
  return _badge_question_voted($uid, 50);
}

/*
 * Issue you added is voted on 200 times
 */
function badge_process_great_question($uid) {
  return _badge_question_voted($uid, 200);
}

/*
 * Issue you added is voted on 1000 times
 */
function badge_process_nice_question($uid) {
  return _badge_question_voted($uid, 1000);
}

/*
 * Helper for
 *  badge_process_nice_question()
 *  badge_process_good_question()
 *  badge_process_great_question()
 */
function _badge_question_voted($uid, $count) {
  // TODO
  return false;
}

/*
 * Hit the daily reputation cap on 150 days
 */
function badge_process_legendary($uid) {
  // TODO
  return false;
}

/*
 * First Retag
 */
function badge_process_organizer($uid) {
  // TODO
  return false;
}

/*
 * Created a tag used by 50 questions
 */
function badge_process_taxonomist($uid) {
  // TODO
  return false;
}

/*
 * Answered first question with at least one up vote
 */
function badge_process_teacher($uid) {
  // TODO
  return false;
}

/*
 * Asked a question with no answers, no comments, and low views for a week
 */
function badge_process_tumbleweed($uid) {
  // TODO
  return false;
}

/*
 * Active member for a year, earning at least 200 reputation
 */
function badge_process_yearling($uid) {
  $count_points = 200;
  if( $count_points <= up_userpoints_get($uid) ) {
    return false != db_result(db_query("SELECT * FROM {users} WHERE created < ADDDATE(CURDATE(), INTERVAL -1 YEAR) AND uid = '%d'", $uid));
  }
  return false;
}

/*
 * Flags post, that eventually results in a change or removal
 */
function badge_process_scrutineer($uid) {
  // TODO
  return false;
}

/*
 * First to suggest answers that eventually gets approved
 */
function badge_process_provocateur($uid) {
  // TODO
  return false;
}

/*
 * Left 10 comments that got a minimum of 1 agree.
 */
function badge_process_pamphleteer($uid) {
  return _badge_posted_agreed_comments($uid, 10);
}


/*
 * Left 100 comments that got a minimum of 1 agree.
 */
function badge_process_commentator($uid) {
  return _badge_posted_agreed_comments($uid, 100);
}


/*
 * Left 500 comments that got a minimum of 1 agree.
 */
function badge_process_pundit($uid) {
  return _badge_posted_agreed_comments($uid, 500);
}


/*
 * Helper for
 *  badge_process_pamphleteer()
 *  badge_process_commentator()
 *  badge_process_pundit()
 */
function _badge_posted_agreed_comments($uid, $count) {
  $comments = db_result(db_query("
    SELECT COUNT(DISTINCT(c.cid))
    FROM {comments} c INNER JOIN {votingapi_vote} vv ON vv.content_id = c.cid
    WHERE c.uid = %d AND vv.content_type = 'comment' AND vv.value = %d",
    $uid, VOTE_AGREE
  ));
  return $comments >= $count;
}

/*
 * Posted an Issue with 1,000 views
 */
function badge_process_notable_issue($uid) {
  return _badge_issue_views($uid, 1000);
}

/*
 * Posted an Issue with 10,000 views
 */
function badge_process_provocative_issue($uid) {
  return _badge_issue_views($uid, 10000);
}

/*
 * Posted an Issue with 50,000 views
 */
function badge_process_household_issue($uid) {
  return _badge_issue_views($uid, 50000);
}

/*
 * Helper for
 *  badge_process_notable_issue()
 *  badge_process_provocative_issue()
 *  badge_process_household_issue()
 */
function _badge_issue_views($uid, $count) {
  // TODO
  return false;
}

/*
 * User has voted on at least 5 issues in 10 topics
 */
function badge_process_generalist($uid) {
  return _badge_voted_in_many_blc($uid, 5, 10);
}

/*
 * User has voted on at least 10 issues in 20 topics
 */
function badge_process_well_read($uid) {
  return _badge_voted_in_many_blc($uid, 10, 20);
}

/*
 * User has voted on at least 20 issues in 30 topics
 */
function badge_process_scholar($uid) {
  return _badge_voted_in_many_blc($uid, 20, 30);
}

/*
 * Helper for
 *  badge_process_generalist()
 *  badge_process_well_read()
 *  badge_process_scholar()
 */
function _badge_voted_in_many_blc($uid, $count_vote, $count_blc) {
  # bottom-level categories
  $vid = _badge_get_vid_by_name('Sections');
  $blc = _badge_bottom_level_terms($vid);
  $blc_implode = implode(',', $blc);
  if( $blc == '' ) {
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

/*
 * Helper function for
 *  _badge_voted_in_many_blc()
 */
function _badge_get_vid_by_name($name) {
  $name = str_replace('-', ' ', $name);
  $object = db_fetch_object(db_query("SELECT vid FROM {vocabulary} WHERE name = '%s'", $name));
  return $object ? $object->vid : 0;
}

/*
 * Helper function for
 *  _badge_voted_in_many_blc()
 *
 * Get Bottom-level Categories
 */
function _badge_bottom_level_terms($vid) {
  static $_list = array();
  if( isset($list[$vid]) ) {
    return $list[$vid];
  }
  $list = array();
  $terms = taxonomy_get_tree($vid);
  foreach( $terms as $term ) {
    $list[$term->tid] = $term;
    foreach($term->parents as $parent) {
      if( $parent != 0 ) {
        unset($list[$parent]);
      }
    }
  }
  $_list[$vid] = array_keys($list);
  return $_list[$vid];
}

/*
 * Resource Posted by user gets 5 agrees
 */
function badge_process_paperboy($uid) {
  return _badge_resource_has_votes($uid, 5);
}

/*
 * Resource Posted by user gets 20 agrees
 */
function badge_process_newsstand($uid) {
  return _badge_resource_has_votes($uid, 20);
}

/*
 * Resource Posted by user gets 50 agrees
 */
function badge_process_librarian($uid) {
  return _badge_resource_has_votes($uid, 50);
}

/*
 * Helper for
 *  badge_process_paperboy()
 *  badge_process_newsstand()
 *  badge_process_librarian()
 */
function _badge_resource_has_votes($uid, $count) {
  // TODO
  $resource_tid = get_taxonomy_id('forum', 'Resource');
  return false != db_result(db_query("
    SELECT n.nid
    FROM {node} n
      INNER JOIN {votingapi_vote} vv ON vv.content_id = n.nid
      LEFT JOIN {term_node} tn ON n.nid = tn.nid
    WHERE
      n.type = 'forum' AND
      vv.content_type = 'node' AND
      tn.tid = '%d' AND
      n.uid = %d AND
      vv.value = 1
    GROUP BY n.nid HAVING COUNT(*) > %d",
    $resource_tid, $uid, $count
  ));
}

/*
 * Argument Posted by user gets 5 agrees
 */
function badge_process_nice_post($uid) {
  return _badge_argument_has_votes($uid, 5);
}

/*
 * Argument Posted by user gets 20 agrees
 */
function badge_process_well_put($uid) {
  return _badge_argument_has_votes($uid, 20);
}

/*
 * Argument Posted by user gets 50 agrees
 */
function badge_process_consensus_builder($uid) {
  return _badge_argument_has_votes($uid, 50);
}

/*
 * Helper for
 *  badge_process_nice_post()
 *  badge_process_well_put()
 *  badge_process_consensus_builder()
 */
function _badge_argument_has_votes($uid, $count) {
  // TODO
  return false;
}

/*
 * First agree on a post or resource that eventually gets 10 agrees
 */
function badge_process_supporter($uid) {
  return _badge_first_vote_supernode($uid, 10);
}

/*
 * First agree on a post or resource that eventually gets 50 agrees
 */
function badge_process_seer($uid) {
  return _badge_first_vote_supernode($uid, 50);
}

/*
 * First agree on a post or resource that eventually gets 100 agrees
 */
function badge_process_oracle($uid) {
  return _badge_first_vote_supernode($uid, 100);
}

/*
 * Helper function for
 *  badge_process_supporter()
 *  badge_process_seer()
 *  badge_process_oracle()
 */
function _badge_first_vote_supernode($uid, $count) {
  $result = db_query("SELECT uid FROM {votingapi_vote} WHERE value = %d GROUP BY content_type, content_id HAVING COUNT(*) >= %d ORDER BY timestamp", VOTE_AGREE, $count);
  while( $row = db_fetch_object($result) ) {
    if( $row->uid == $uid ) {
      return true;
    }
  }
  return false;
}

/*
 * Created an issue that resulted in 20 debate posts or resource posts
 */
function badge_process_conversation_piece($uid) {
  return _badge_issue_arguments($uid, 20);
}

/*
 * Created an issue that resulted in 50 debate posts or resource posts
 */
function badge_process_debate($uid) {
  return _badge_issue_arguments($uid, 50);
}

/*
 * Created an issue that resulted in 100 debate posts or resource posts
 */
function badge_process_convention($uid) {
  return _badge_issue_arguments($uid, 100);
}

/*
 * Helper for
 *  badge_process_conversation_piece()
 *  badge_process_debate()
 *  badge_process_convention()
 */
function _badge_issue_arguments($uid, $count) {
  // TODO
  return false;
}

/*
 * Becoming a Top 5 Pundit in a topic subject
 */
function badge_process_philosopher_king($uid) {
  // TODO
  return false;
}

/*
 * Becoming a Top 5 Pundit in a topic area
 */
function badge_process_philosopher($uid) {
  // TODO
  return false;
}



/*
 * Issue you added is voted on 1000 times
 *
function badge_process_provocative_question($uid) {
  $count_vote = 1000;
  return false != db_result(db_query("
    SELECT n.nid
    FROM {poll_votes} pv INNER JOIN {node} n ON n.nid = pv.nid
    WHERE n.uid = '%d'
    GROUP BY n.nid HAVING COUNT(*) > %d",
    $uid, $count_vote
  ));
}

/*
 * Left 500 comments that got a minimum of one agree.
 *
function badge_process_senator($uid) {
  return _badge_posted_agreed_comments($uid, 500);
}

/*
 * Voted 1000 times
 *
function badge_process_patriotic_citizen($uid) {
  $count_vote = 1000;
  # count different types of votes
  $count_pv = db_result(db_query("SELECT COUNT(*) FROM {poll_votes} WHERE uid = '%d'", $uid));
  $count_sa = db_result(db_query("SELECT COUNT(*) FROM (suggest_answer_vote) WHERE uid = '%d' GROUP BY uid", $uid));
  $count_ud = yn_user_vote_count($uid);
  return $count_pv + $count_sa + $count_ud >= $count_vote;
}
*/


