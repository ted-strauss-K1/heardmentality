<?php

/**
 * @param $nid
 * @param null $sort
 * @param null $print
 * @return mixed
 */
function argument_tab($nid, $sort = NULL, $print = NULL)
{
  $argnids = argument_filter($nid, $sort, $_REQUEST['class'], $_REQUEST['chorder']);
  $nodes = array();
  foreach ($argnids as $argnid) {
    $nodes[] = node_load($argnid);
  }
  $output = theme('argument_tab', $nodes);

  # print/return
  if (is_null($print)) {
    return $output;
  } else {
    print $output;
    exit;
  }
}

/**
 * Main function to filter the arguments for Debate tabs
 *
 * @param $nid
 * @param null $sort
 * @param null $class
 * @param null $chorder
 * @return array
 */
function argument_filter($nid, $sort = NULL, $class = NULL, $chorder = NULL)
{
  $argnids = array();

  $params = array();

  $query = "
    SELECT DISTINCT(n.nid)
    FROM {content_field_reference} cfr
    INNER JOIN {node} n ON cfr.nid = n.nid
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
function argument_create_comment()
{
  if (!user_is_logged_in()) {
    print json_encode(array(
      'status' => FALSE,
      'message' => t('Please login to post reply'),
    ));
    exit();
  }
  if (!user_access('create forum topics')) {
    print json_encode(array(
      'status' => FALSE,
      'message' => t('You don\'t have permissions to post arguments'),
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
      'status' => FALSE,
      'message' => t('Error occurred'),
    ));
    exit();
  }

  print json_encode(array(
    'status' => TRUE,
    'message' => t('Thanks, Your reply posted!'),
    'content' => theme('argument_comment', $comment),
  ));

  exit();
}

/**
 * Function to save comment
 *
 * @param $comment
 * @return bool
 */
function _comment_save(&$comment)
{
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
    homepage    = '%s'",
    $comment->pid, $comment->nid, $comment->uid, $comment->subject, $comment->comment, $comment->hostname, $comment->timestamp, $comment->status, $comment->format, $comment->thread, $comment->name, $comment->mail, $comment->homepage);

  if (!$result) {
    $comment = FALSE;
  } else {
    $comment->cid = db_last_insert_id('comments', 'cid');
    comment_invoke_comment($comment, 'insert');
  }
  return $comment !== FALSE;
}

/**
 * argument_resource_preview
 */
function argument_preview_resource()
{
  $_POST += $_REQUEST;

  $url = isset($_POST['url']) ? $_POST['url'] : FALSE;
  $node = argument_fetch_url($url);

  if ($node === FALSE) {
    print json_encode(array(
      'status' => FALSE,
      'message' => t('No URL provided'),
    ));
  } else {
    print json_encode(array(
      'status' => TRUE,
      'message' => theme('argument_resource_preview', $node),
      'success' => $node,
    ));
  }
  exit();
}

/**
 * Create the core of the resource node by url
 *
 * @param $url
 * @param bool $image
 * @return bool|stdClass
 */
function argument_fetch_url($url, $image = FALSE)
{
  module_load_include('php', 'argument', 'files/simple_html_dom');
  $html = file_get_html($url);

  if (empty($html)) {
    return FALSE;
  }

  global $user;
  $node = new stdClass();
  $node->type = 'resource';

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

  // url
  $node->field_url[0]['value'] = $url;
  // source
  $url_p = parse_url($url);
  $node->field_source[0]['value'] = $url_p['host'];

  if (FALSE !== strpos($node->field_source[0]['value'], 'youtube.com')) { # YouTube Video
    $node->field_rtype[0]['value'] = 'youtube';

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
      return FALSE;
    }
    // title, body, teaser
    $title = $html->find('#eow-title', 0);
    $node->title = empty($title) ? '' : $title->innertext;
    $body = $html->find('#eow-description', 0);
    $node->body = empty($body) ? '' : $body->plaintext;
    // youtube video id
    $node->field_youtube[0]['value'] = $youtube_id;
    $node->field_image_path[0]['value'] = 'http://img.youtube.com/vi/' . $youtube_id . '/default.jpg';

    // preview specific fields
    $node->images = array($node->field_image_path[0]['value']);
    $node->noimage = FALSE;

  } else { # Regular URL
    $node->field_rtype[0]['value'] = 'url';
    $node->field_youtube[0]['value'] = '';
    // title, body, teaser
    $title = $html->find('title', 0);
    $node->title = empty($title) ? '' : $title->innertext;
    $tags = get_meta_tags($url);
    $node->body = empty($tags) ? '' : $tags['description'];

    # get images
    $node->field_image_path[0]['value'] = file_directory_path() . '/noimage.jpg';
    module_load_include('php', 'argument', 'files/url_to_absolute');
    $images = array();
    $images_source = $html->find('img');
    foreach ($images_source as $element) {
      # $images[$element->src] = true;
      $images[] = url_to_absolute($url, $element->src);
    }
    $node->images = argument_create_resource_validate_images($images);
    $node->noimage = empty($node->images) ? TRUE : FALSE;

    if ($image !== FALSE) {
      module_load_include('php', 'argument', 'files/download_image');
      if ($file = download_image($image, 'resources')) {
        $node->field_image_path[0]['value'] = $file->filepath;
      }
    }
  }
  $html->clear();

  // safe strings
  $node->title = argument_safe_string($node->title);
  $node->body = argument_safe_string($node->body);
  $node->teaser = $node->body;

  return $node;
}

/**
 * Validate the images
 *
 * @param $images - array of image absolute urls
 * @return array
 */
function argument_create_resource_validate_images($images)
{
  $ext_allowed = array('png', 'jpg', 'jpeg', 'gif');
  $result = array();
  $sizes = array();
  foreach ($images as $image) {
    $ext = argument_create_resource_image_extension($image);
    if (in_array($ext, $ext_allowed)) {
      list($width, $height, $type, $attr) = getimagesize($image);
      if ($width > 30 && $height > 30) {
        $size_coeff = $width * $height;
        $result[$size_coeff][] = $image;
      }
    }
  }
  // sort by size
  krsort($result, SORT_NUMERIC);
  $output = array();
  foreach ($result as $items) {
    foreach ($items as $item) {
      $output[] = $item;
    }
  }
  return $output;
}

/**
 * @param $string
 * @return mixed
 */
function argument_safe_string($string)
{
  return preg_replace(
    '/[\x00-\x08\x10\x0B\x0C\x0E-\x19\x7F]' .
      '|[\x00-\x7F][\x80-\xBF]+' .
      '|([\xC0\xC1]|[\xF0-\xFF])[\x80-\xBF]*' .
      '|[\xC2-\xDF]((?![\x80-\xBF])|[\x80-\xBF]{2,})' .
      '|[\xE0-\xEF](([\x80-\xBF](?![\x80-\xBF]))|(?![\x80-\xBF]{2})|[\x80-\xBF]{3,})/S',
    '?', $string);
}

/**
 * Get the image extension
 *
 * @param $image
 * @return string
 */
function argument_create_resource_image_extension($image)
{
  $img = explode("/", $image);
  $img = end($img);
  $ext = explode(".", $img);
  $ext = end($ext);
  return strtolower($ext);
}

/**
 *  New debate/resource form submission
 *
 * @param $form
 * @param $form_state
 */
function argument_create()
{
  $post = $_POST;

  switch ($post['type']) {
    case 'argument' : # Debate
      $node = argument_create_argument($post['nid'], $post['title']);
      if ($node) {
        # argument options
        $node->argument_options = cpoll_load_choices($post['nid']);
        foreach ($node->argument_options as $chid => &$choice) {
          $choice['val'] = $post['option_'.$chid];
        }
        node_save($node);

        print json_encode(array(
          'success' => TRUE,
          'message' => '<span class="posted">' . t('Your argument posted successfully') . '!</span>',
          'nid' => $node->nid,
        ));
      } else {
        print json_encode(array(
          'success' => FALSE,
          'message' => '<div class="messages error"><b>' . t('Error occurred. Please try again') . '</b></div>',
        ));
      }
      break;

    case 'resource' : # Resource
      if (empty($post['url'])) {
        print json_encode(array(
          'success' => FALSE,
          'message' => '<div class="messages error"><b>' . t('Please enter an URL') . '</b></div>',
        ));
        exit;
      }
      $post['url'] = argument_url_prepare($post['url']);
      $node = arguments_create_resource($post['nid'], $post['url'], $post['uimg']);
      if ($node) {
        print json_encode(array(
          'success' => TRUE,
          'message' => '<span class="posted">' . t('Your argument was posted successfully!') . '</span>',
          'node' => $node,
          'nid' => $node->nid,
        ));

      } else {
        $url = parse_url($post['url']);
        if (FALSE !== strpos($url['host'], 'youtube.com')) {
          print json_encode(array(
            'success' => FALSE,
            'message' => '<div class="messages error"><b>' . t('YouTube video ID not found') . '</b></div>',
          ));
        } else {
          print json_encode(array(
            'success' => FALSE,
            'message' => '<div class="messages error"><b>' . t('Error occurred. Please check you URL') . '</b></div>',
          ));
        }
      }
      break;
  }
  exit;
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


/**
 * Debate Node creation
 */
function argument_create_argument($nid, $title)
{
  global $user;
  if (empty($nid) || empty($title)) {
    return FALSE;
  }

  $node = new stdClass();

  $node->type = 'argument';

  global $language;
  $node->language = $user->language ? $user->language : $language->language; // TODO language detection

  $node->uid = $user->uid;
  $node->status = 1;
  $node->created = time();
  $node->tnid = 0;
  $node->translate = 0;
  $node->title = $title;
  $node->body = $title;
  $node->teaser = $node->body;
  $node->name = $user->name;

  $node->field_reference[0]['nid'] = $nid;

  // Without node_submit()
  $node->validated = TRUE;

  node_save($node);
  node_reload($node);

  return $node;
}

/**
 * Resource Node creation
 *
 * @param $nid
 * @param $url
 * @param $image
 * @return bool|stdClass
 */
function arguments_create_resource($nid, $url, $image)
{
  if (empty($nid) || empty($url)) {
    return FALSE;
  }
//  $url_p = parse_url($url);
  $node = argument_fetch_url($url, $image);
  if ($node === FALSE) {
    return FALSE;
  }
  unset($node->images);
  unset($node->noimage);

  $node->field_reference[0]['nid'] = $nid;

  node_save($node);
  node_reload($node);

  return $node;
}

/**
 * "argument/delete" callback
 *
 * @param $content_type
 * @param $content_id
 */
function argument_delete($content_type, $content_id)
{
  // todo moderation
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
  // todo moderation
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