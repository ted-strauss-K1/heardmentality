<?php

/*
 * The file contains the issue-only related functions
 */

/*
 * Suggest answers DB access
 */

/*
 * Get user SA vote count
 */
function issue_sa_count($uid)
{
  return db_result(db_query("SELECT IFNULL(COUNT(*),0) FROM (suggest_answer_vote) WHERE uid = '%d' GROUP BY uid", $uid));
}

/*
 * Merge duplicated SA
 */
function issue_sa_merge($id, $id_duplicate)
{
  db_query("UPDATE {suggest_answer} SET qid = '%d' where qid = '%d'", $id, $id_duplicate);
  db_query("UPDATE {suggest_answer_vote} SET qid = '%d' where qid = '%d'", $id, $id_duplicate);
}

/*
 * Delete SA
 */
function issue_sa_delete($id)
{
  db_query("DELETE FROM {suggest_answer} WHERE qid = '%d'", $id);
}

