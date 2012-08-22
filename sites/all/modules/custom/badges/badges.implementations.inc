<?php

/*
 * This file is to contain the badges' implementation functions
 *
 * @params - $uid - User Id
 *
 * @return - TRUE/FALSE
 */

/*
 * User has voted on at least 20 questions is 30 bottom level categories
 * (i.e categories without children subcategories)
 */
function badge_process_scholar($uid) {
  return _badge_voted_in_many_blc($uid, 20, 30);
}

/*
 * User has voted on at least 10 questions is 20 bottom level categories
 * (i.e categories without children subcategories)
 */
function badge_process_well_read($uid) {
  return _badge_voted_in_many_blc($uid, 10, 20);
}


/*
 * Helper function for
 *  badge_process_scholar()
 *  badge_process_well_read()
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
 *  badge_process_scholar()
 */
function _badge_get_vid_by_name($name) {
  $name = str_replace('-', ' ', $name);
  $object = db_fetch_object(db_query("SELECT vid FROM {vocabulary} WHERE name = '%s'", $name));
  return $object ? $object->vid : 0;
}

/*
 * Helper function for badge_process_scholar()
 *
 * Get bottom level categories
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
 * Issue you added is voted on 1000 times
 */
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
 * First agree on a post or resource that eventually gets 100 agrees
 */
function badge_process_oracle($uid) {
  return _badge_first_vote_supernode($uid, 100);
}

/*
 * First agree on a post or resource that eventually gets 50 agrees
 */
function badge_process_seer($uid) {
  return _badge_first_vote_supernode($uid, 50);
}

/*
 * First agree on a post or resource that eventually gets agreed
 */
function badge_process_supporter($uid) {
  return _badge_first_vote_supernode($uid, 1);
}

/*
 * Helper function for
 *  badge_process_oracle()
 *  badge_process_seer()
 *  badge_process_supporter()
 */
function _badge_first_vote_supernode($uid, $count) {
  $result = db_query("SELECT uid FROM {votingapi_vote} WHERE value = 1 GROUP BY content_type, content_id HAVING COUNT(*) >= %d ORDER BY timestamp", $count);
  while( $row = db_fetch_object($result) ) {
    if( $row->uid == $uid ) {
      return true;
    }
  }
  return false;
}

/*
 * Left 500 comments that got a minimum of one agree.
 */
function badge_process_senator($uid) {
  return _badge_posted_agreed_comments($uid, 500);
}

/*
 * Left 10 comments that got a minimum of one agree.
 */
function badge_process_pamphleteer($uid) {
  return _badge_posted_agreed_comments($uid, 10);
}

/*
 * Helper function for
 *  badge_process_senator()
 *  badge_process_pamphleteer()
 */
function _badge_posted_agreed_comments($uid, $count) {
  $comments = db_result(db_query("
    SELECT COUNT(DISTINCT(c.cid))
    FROM {comments} c INNER JOIN {votingapi_vote} vv ON vv.content_id = c.cid
    WHERE c.uid = %d AND vv.content_type = 'comment' AND vv.value = 1",
    $uid
  ));
  return $comments >= $count;
}

/*
 * Voted 1000 times
 */
function badge_process_patriotic_citizen($uid) {
  $count_vote = 1000;
  # count different types of votes
  $count_pv = db_result(db_query("SELECT COUNT(*) FROM {poll_votes} WHERE uid = '%d'", $uid));
  $count_sa = db_result(db_query("SELECT COUNT(*) FROM (suggest_answer_vote) WHERE uid = '%d' GROUP BY uid", $uid));
  $count_ud = yn_user_vote_count($uid);
  return $count_pv + $count_sa + $count_ud >= $count_vote;
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
 * Helper function for
 *  badge_process_paperboy()
 *  badge_process_newsstand()
 *  badge_process_librarian()
 */
function _badge_resource_has_votes($uid, $count) {
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
 * Created a question that resulted in 20 debate posts or resource posts (including replies)
 */
function badge_process_conversation_piece($uid) {
  return _badge_question_has_replies($uid, 20);
}

/*
 * Created a question that resulted in 50 debate posts or resource posts (including replies)
 */
function badge_process_cocktail_party($uid) {
  return _badge_question_has_replies($uid, 50);
}

/*
 * Created a question that resulted in 100 debate posts or resource posts (including replies)
 */
function badge_process_healthy_debate($uid) {
  return _badge_question_has_replies($uid, 100);
}

/*
 * Helper function for
 *  badge_process_conversation_piece()
 *  badge_process_cocktail_party()
 *  badge_process_healthy_debate()
 */
function _badge_question_has_replies($uid, $count) {
  // TODO
  return false;
}

/*
 * Debate Posted by user gets 5 agrees
 */
function badge_process_nice_post($uid) {
  return _badge_debate_agreed($uid, 5);
}

/*
 * Debate Posted by user gets 20 agrees
 */
function badge_process_well_put($uid) {
  return _badge_debate_agreed($uid, 20);
}

/*
 * Debate Posted by user gets 50 agrees
 */
function badge_process_consensus_builder($uid) {
  return _badge_debate_agreed($uid, 50);
}


/*
 * Helper function for
 *  badge_process_nice_post()
 *  badge_process_well_put()
 *  badge_process_consensus_builder()
 */
function _badge_debate_agreed($uid, $count) {
  // TODO
  return false;
}

/*
 * Posted issue with 10,000 views
 */
function badge_process_provocative_issue($uid) {
  // TODO
  return false;
}

/*
 * Flags post, that eventually results in a change or removal
 */
function badge_process_scrutineer($uid) {
  // TODO
  return false;
}
