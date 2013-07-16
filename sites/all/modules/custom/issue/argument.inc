<?php

/**
 * Define constant for debates
 */
define('TYPE_DEBATE', 1);

/**
 * Define constant for resources
 */
define('TYPE_RESOURCE', 2);







/**
 * Check if user is owner of the content
 *
 * @param $content_type
 * @param $content_id
 * @return bool
 */
function argument_check_owner($content_type, $content_id)
{
  global $user;
  switch ($content_type) {
    case 'node' :
      return FALSE != db_result(db_query("SELECT nid FROM {node} WHERE nid = '%d' AND uid = '%d'", $content_id, $user->uid));
      break;
    case 'comment' :
      return FALSE != db_result(db_query("SELECT cid FROM {comments} WHERE cid = '%d' AND uid = '%d'", $content_id, $user->uid));
      break;
  }
  return FALSE;
}






/**
 * "argument/delete" callback
 *
 * @param $content_type
 * @param $content_id
 */
function argument_delete($content_type, $content_id)
{
  if (!(module_exists('moderation') && moderation_check_perm()) && !argument_check_owner($content_type, $content_id)) {
    print json_encode(array(
      'status' => FALSE,
      'message' => t('Sorry, you have no permissions to delete the content'),
    ));
    exit;
  }

  switch ($content_type) {
    case 'node' :
      db_query("UPDATE {node} SET status = '%d' WHERE nid = '%d'", 0, $content_id);
      break;
    case 'comment' :
      db_query("UPDATE {comments} SET status = '%d' WHERE cid = '%d'", COMMENT_NOT_PUBLISHED, $content_id);
      break;
  }
  if (module_exists('moderation')) {
    moderation_history_set($content_id, $content_type, 'delete');
  }
  print json_encode(array(
    'status' => TRUE,
    'message' => t('Successfully deleted'),
  ));
  exit();
}

/**
 * @param $url
 * @return string
 */
function argument_url_prepare($url) {
  $regex1 = '/^www\./';
  $regex2 = '/^http:\/\//';
  if (preg_match($regex1,$url) || !preg_match($regex2,$url)) {
    return 'http://' . $url;
  }
  return $url;
}



