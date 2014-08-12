<?php

/**
 * @param      $nid
 * @param null $sort
 * @param null $print
 *
 * @return mixed
 */
function argument_tab($nid, $sort = NULL, $print = NULL) {
  $argnids = argument_filter($nid, $sort, $_REQUEST['class'], $_REQUEST['chorder']);
  $nodes = array();
  foreach ($argnids as $argnid) {
    $nodes[] = node_load($argnid);
  }
  $output = theme('argument_tab', $nodes);

  # print/return
  if (is_null($print)) {
    return $output;
  }
  else {
    print $output;
    exit;
  }
}

/**
 * Main function to filter the arguments for Debate tabs
 *
 * @param      $nid
 * @param null $sort
 * @param null $class
 * @param null $chorder
 *
 * @return array
 */
function argument_filter($nid, $sort = NULL, $class = NULL, $chorder = NULL) {
  $argnids = array();

  $params = array();

  $query = "
    SELECT DISTINCT(n.nid)
    FROM {content_field_reference} cfr
    INNER JOIN {node} n ON cfr.nid = n.nid
    INNER JOIN {users} u ON n.uid = u.uid AND u.status = 1
    LEFT JOIN {argument_options} ao ON n.nid = ao.nid
    LEFT JOIN {votingapi_cache} vc ON vc.content_type = 'node' AND vc.content_id = n.nid AND vc.function = 'sum'
    LEFT JOIN {votingapi_vote} vv ON vv.content_type = 'node' AND vv.content_id = n.nid
    WHERE n.status = 1 AND cfr.field_reference_nid = '%d'";
  $params[] = $nid;

  if (!is_null($class) && !is_null($chorder)) {
    $query .= " AND ao.chid = '%d'";
    $params[] = $chorder;

    # filter arguments
    switch ($class) {
      case 'neutral' :
        $params[] = 0;
        $query .= " AND ao.val <> '%d'";
        break;
      case 'positive' :
        $params[] = 1;
        $query .= " AND ao.val = '%d'";
        break;
      case 'negative' :
        $params[] = -1;
        $query .= " AND ao.val = '%d'";
        break;
      default :
        $params[] = 0;
        $query .= " AND ao.val = '%d'";
        break;
    }
  }

  # sort parameters
  switch ($sort) {
    case 1 : # older
      $order = 'ORDER BY n.created ASC';
      break;
    case 0 : # recent
      $order = 'ORDER BY n.created DESC';
      break;
    case 2 : # supported
      $order = 'ORDER BY IFNULL(vc.value, 0) DESC';
      break;
    default : # default
      $order = 'ORDER BY n.nid DESC';
      break;
  }

  // fetch results
  $result = db_query($query . ' ' . $order, $params);
  while ($item = db_fetch_array($result)) {
    $argnids[] = $item['nid'];
  }

  return $argnids;
}

/**
 * Arguments Comment Form - Ajax Submission
 */
function argument_create_comment() {
  if (!user_is_logged_in()) {
    print json_encode(array(
      'status'  => FALSE,
      'message' => __('Please login to post reply', array('@code' => 'argument-13')),
    ));
    exit();
  }
  if (!user_access('create forum topics')) {
    print json_encode(array(
      'status'  => FALSE,
      'message' => __('You don\'t have permissions to post arguments', array('@code' => 'argument-14')),
    ));
    exit();
  }

  $post = $_REQUEST;
  $text = check_plain($post['comment']);

  global $user;
  $comment = new stdClass();
  $comment->pid = 0;
  $comment->nid = $post['content_id'];
  $comment->uid = $user->uid;
  $comment->subject = $text;
  $comment->comment = $text;
  $comment->hostname = ip_address();
  $comment->timestamp = time();
  $comment->status = COMMENT_PUBLISHED;
  $comment->format = '';
  $comment->thread = '';
  $comment->name = $user->name;
  $comment->mail = $user->mail;
  $comment->homepage = '';

  global $language;
  $comment->language = $user->language ? $user->language : $language->language; // TODO language detection

  $comment->support = $post['support'];

  if (!_comment_save($comment)) {
    print json_encode(array(
      'status'  => FALSE,
      'message' => __('Error occurred', array('@code' => 'argument-15')),
    ));
    exit();
  }

  print json_encode(array(
    'status'  => TRUE,
    'message' => __('Thanks, Your reply posted!', array('@code' => 'argument-16')),
    'content' => theme('argument_comment', $comment),
    'cid'     => $comment->cid,
  ));

  exit();
}

/**
 * Function to save comment
 *
 * @param $comment
 *
 * @return bool
 */
function _comment_save(&$comment) {
  $result = db_query("INSERT INTO {comments} SET
    pid         = '%d',
    nid         = '%d',
    uid         = '%d',
    subject     = '%s',
    comment     = '%s',
    hostname    = '%s',
    timestamp   = '%s',
    status      = '%s',
    format      = '%s',
    thread      = '%s',
    name        = '%s',
    mail        = '%s',
    homepage    = '%s'", $comment->pid, $comment->nid, $comment->uid, $comment->subject, $comment->comment, $comment->hostname, $comment->timestamp, $comment->status, $comment->format, $comment->thread, $comment->name, $comment->mail, $comment->homepage);

  if (!$result) {
    $comment = FALSE;
  }
  else {
    $comment->cid = db_last_insert_id('comments', 'cid');
    comment_invoke_comment($comment, 'insert');
  }
  return $comment !== FALSE;
}

/**
 * CREATE ARGUMENTS
 */

/**
 *  New debate/resource form submission
 *
 * @param $form
 * @param $form_state
 */
function argument_create() {
  $post = $_POST;

  $node = argument_prepare();
  $node->field_reference[0]['nid'] = $post['nid'];

  switch ($post['type']) {
    case 'argument' :
      $node->type = 'argument';
      if (empty($post['text'])) {
        break;
      }
      $node->teaser = $node->body = $node->title = $post['text'];
      node_save($node);
      node_reload($node);

      if ($node) {
        # argument options
        $node->argument_options = cpoll_load_choices($post['nid']);
        foreach ($node->argument_options as $chid => &$choice) {
          if (isset($post['options'][$chid])) {
            $choice['val'] = $post['options'][$chid];
          }
        }
        node_save($node);

        exit(json_encode(array(
          'success' => TRUE,
          'message' => __('Your argument posted successfully', array('@code' => 'argument-17')),
          'nid'     => $node->nid,
        )));
      }
      break;

    case 'resource' : # Resource
      $node->type = 'resource';
      // no url
      if (empty($post['url'])) {
        exit(json_encode(array(
          'success' => FALSE,
          'message' => __('Please enter an URL', array('@code' => 'argument-18')),
        )));
      }
      // url
      $url = $post['url'];
      $node->field_url[0]['value'] = $url;
      // source
      $url_p = parse_url($url);
      $node->field_source[0]['value'] = $url_p['host'];
      // title
      $node->title = $post['title'];
      $node->body = $post['description'];

      # YouTube Video
      if (preg_match('/^(www\.)?youtube\.com/', $node->field_source[0]['value'])) {
        // rtype
        $node->field_rtype[0]['value'] = 'youtube';
        // youtube id
        $params = explode('&', $url_p['query']);
        $youtube_id = FALSE;
        foreach ($params as $param) {
          $param = explode('=', $param, 2);
          if ($param[0] == 'v') {
            $youtube_id = $param[1];
            break;
          }
        }
        if ($youtube_id === FALSE || strlen($youtube_id) != 11) {
          exit(json_encode(array(
            'success' => FALSE,
            'message' => __('YouTube video ID not found', array('@code' => 'argument-19')),
          )));
        }
        $node->field_youtube[0]['value'] = $youtube_id;
        // image path
        $node->field_image_path[0]['value'] = 'http://img.youtube.com/vi/' . $youtube_id . '/default.jpg';
      }
      # Regular URL
      else {
        // rtype
        $node->field_rtype[0]['value'] = 'url';
        // youtube id
        $node->field_youtube[0]['value'] = '';
        // image path
        $node->field_image_path[0]['value'] = file_directory_path() . '/noimage.jpg';
        if ($post['image']) {
          $node->field_image_path[0]['value'] = $post['image'];
          module_load_include('php', 'argument', 'files/download_image');
          if ($file = download_image($node->field_image_path[0]['value'], 'resources')) {
            $node->field_image_path[0]['value'] = $file->filepath;
          }
        }
      }

      node_save($node);
      node_reload($node);

      if ($node) {
        exit(json_encode(array(
          'success' => TRUE,
          'message' => __('Your argument was posted successfully!', array('@code' => 'argument-20')),
          'node'    => $node,
          'nid'     => $node->nid,
        )));
      }
      else {
        exit(json_encode(array(
          'success' => FALSE,
          'message' => __('Error occurred. Please check you URL', array('@code' => 'argument-21')),
        )));
      }
      break;
  }
  // error
  exit(json_encode(array(
    'success' => FALSE,
    'message' => __('Error occurred. Please try again', array('@code' => 'argument-22')),
    'post'    => $post,
  )));
}

/**
 * Prepare blank node
 *
 * @return stdClass
 */
function argument_prepare() {
  global $user;
  $node = new stdClass();

  global $language;
  $node->language = $user->language ? $user->language : $language->language; // TODO language detection

  $node->uid = $user->uid;
  $node->status = 1;
  $node->created = time();
  $node->tnid = 0;
  $node->translate = 0;
  $node->name = $user->name;
  // Without node_submit()
  $node->validated = TRUE;

  return $node;
}

/**
 * "argument/delete" callback
 *
 * @param $content_type
 * @param $content_id
 */
function argument_delete($content_type, $content_id) {
  if (!(module_exists('moderation') && moderation_check_perm()) && !argument_check_owner($content_type, $content_id)) {
    print json_encode(array(
      'status'  => FALSE,
      'message' => __('Sorry, you have no permissions to delete the content', array('@code' => 'argument-23')),
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
  //
  if (module_exists('moderation')) {
    moderation_history_set($content_id, $content_type, 'delete');

    module_load_include('inc', 'moderation', 'moderation.pages');

    // todo track flagging success
  }
  print json_encode(array(
    'status'  => TRUE,
    'message' => __('Successfully deleted', array('@code' => 'argument-24')),
  ));
  exit();
}

/**
 * Check if user is owner of the content
 *
 * @param $content_type
 * @param $content_id
 *
 * @return bool
 */
function argument_check_owner($content_type, $content_id) {
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
