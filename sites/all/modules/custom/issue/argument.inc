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
 * Implementation of hook_menu()
 *
 * @return array
 */
function argument_menu()
{
  $menu = array();

  $menu['argument/tab/%/%/%'] = array(
    'page callback' => 'argument_tab',
    'type' => MENU_CALLBACK,
    'page arguments' => array(2, 3, 4),
    'access arguments' => array('access content'),
  );

  $menu['argument/create/comment'] = array(
    'page callback' => 'argument_create_comment',
    'type' => MENU_CALLBACK,
    'access arguments' => array('post comments without approval'),
  );

  $menu['argument/create'] = array(
    'page callback' => 'argument_create',
    'type' => MENU_CALLBACK,
    'access callback' => TRUE,
  );

  $menu['argument/delete/%/%'] = array(
    'page callback' => 'argument_delete',
    'page arguments' => array(2, 3),
    'type' => MENU_CALLBACK,
    'access callback' => TRUE,
  );

  $menu['argument/preview/resource'] = array(
    'page callback' => 'argument_preview_resource',
    'type' => MENU_CALLBACK,
    'access callback' => TRUE,
  );

  return $menu;
}

/**
 * Implementation of hook_menu()
 *
 * @return array
 */
function argument_theme()
{
  $theme = array();

  $theme['argument_tab'] = array(
    'arguments' => array('nodes' => array()),
    'file' => 'argument.theme.inc',
  );
  $theme['argument_item'] = array(
    'arguments' => array('node' => null),
    'template' => 'templates/argument-item',
  );
  $theme['argument_comment'] = array(
    'arguments' => array('comment' => NULL),
    'template' => 'templates/argument-comment',
  );
  $theme['argument_resource_preview'] = array(
    'arguments' => array('node' => NULL),
    'template' => 'templates/argument-resource-preview',
  );

  $theme['argument_result_ball'] = array(
    'arguments' => array('vote_sum' => NULL),
    'file' => 'argument.theme.inc',
  );
  $theme['time_interval'] = array(
    'arguments' => array('time' => NULL),
    'file' => 'argument.theme.inc',
  );
  $theme['argument_delete'] = array(
    'arguments' => array(
      'comment_type' => NULL,
      'comment_id' => NULL,
    ),
    'file' => 'argument.theme.inc',
  );


  return $theme;
}

/**
 * Implementation of hook_nodeapi()
 *
 * @param $node
 * @param $op
 * @param null $a3
 * @param null $a4
 */
function argument_nodeapi(&$node, $op, $a3 = NULL, $a4 = NULL)
{
  if ($node->type == 'forum') {
    switch ($op) {
      case 'load' :
        $node->creation_time = ($_ = theme('time_interval', $node->created)) ? $_ : date("F d Y H:i:s", $node->created);
        $node->comments = argument_recent_comments($node->nid);
        break;
    }
  }
}

/**
 * Implementation of hook_comment()
 *
 * @param $a1
 * @param $op
 */
function argument_comment(&$a1, $op)
{
  switch ($op) {
    case 'view' :
      $a1->creation_time = ($_ = theme('time_interval', $a1->timestamp)) ? $_ : date("F d Y H:i:s", $a1->timestamp);
      break;
  }
}

/**
 * Get recent comments
 *
 * TODO someday: add range for showing replies
 *
 * @param $nid
 * @return array
 */
function argument_recent_comments($nid)
{
  $comments = array();

  $result = db_query("SELECT * FROM {comments} WHERE nid = '%d' AND status = '%d' AND comment <> '' ORDER BY cid DESC", $nid, COMMENT_PUBLISHED);
  while ($comment = db_fetch_object($result)) {
    $comment->content_id = $comment->cid;
    $comment->content_type = 'comment';
    $comments[] = $comment;
  }

  return $comments;
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
      return false != db_result(db_query("SELECT nid FROM {node} WHERE nid = '%d' AND uid = '%d'", $content_id, $user->uid));
      break;
    case 'comment' :
      return false != db_result(db_query("SELECT cid FROM {comments} WHERE cid = '%d' AND uid = '%d'", $content_id, $user->uid));
      break;
  }
  return false;
}

/**
 * @param $nid
 * @param null $sort
 * @param null $print
 * @return mixed
 */
function argument_tab($nid, $sort = null, $print = null)
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
function argument_filter($nid, $sort = null, $class = null, $chorder = null)
{
  $argnids = array();

  $params = array();

  $query = "
    SELECT DISTINCT(n.nid)
      FROM node n
      INNER JOIN content_type_forum ctf ON n.nid = ctf.nid AND ctf.field_issue_nid = '%d'
      LEFT JOIN votingapi_cache vc ON vc.content_type = 'node' AND vc.content_id = n.nid AND vc.function = 'sum'
      LEFT JOIN votingapi_vote vv ON vv.content_type = 'node' AND vv.content_id = ctf.nid
      LEFT JOIN argument_options ao ON ctf.nid = ao.nid
    WHERE n.status = 1";
  $params[] = $nid;

  if (!is_null($class) && !is_null($chorder)) {
    $query .= " AND ao.chorder = '%d'";
    $params[] = $chorder;

    # filter arguments
    $query .= " AND ao.val = '%d'";
    switch ($class) {
      case 'neutral' :
        $params[] = 0;
        break;
      case 'positive' :
        $params[] = 1;
        break;
      case 'negative' :
        $params[] = -1;
        break;
      default :
        $params[] = 0;
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
      'status' => false,
      'message' => t('Please login to post reply'),
    ));
    exit();
  }
  if (!user_access('create forum topics')) {
    print json_encode(array(
      'status' => false,
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
      'status' => false,
      'message' => t('Error occurred'),
    ));
    exit();
  }

  // fire event
  comment_invoke_comment($comment, 'insert');

  print json_encode(array(
    'status' => true,
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
    $comment = false;
  } else {
    $comment->cid = db_last_insert_id('comments', 'cid');
    comment_invoke_comment($comment, 'insert');
  }
  return $comment !== false;
}

/**
 * "argument/delete" callback
 *
 * @param $content_type
 * @param $content_id
 */
function argument_delete($content_type, $content_id)
{
  global $user;
  if (!user_access('moderation', $user) && !argument_check_owner($content_type, $content_id)) {
    print json_encode(array(
      'status' => false,
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
  print json_encode(array(
    'status' => true,
    'message' => t('Successfully deleted'),
  ));
  exit();
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
    case TYPE_DEBATE : # Debate
      $node = argument_create_debate($post['nid'], $post['title']);
      if ($node && module_exists('argument_options')) {
        $issue = node_load($post['nid']);
        $choices = $issue->choice;
        $choices_count = count($choices);
        for ($i = 0; $i < $choices_count; $i++) {
          $node->argument_options[] = array(
            'chorder' => $post['chorder_' . $i],
            'value' => $post['option_' . $i],
          );
        }
        argument_options_update($node, $issue);

        print json_encode(array(
          'success' => true,
          'message' => '<span class="posted">' . t('Your argument posted successfully') . '!</span>',
        ));

      } else {
        print json_encode(array(
          'success' => false,
          'message' => '<div class="messages error"><b>' . t('Error occurred. Please try again') . '</b></div>',
        ));
      }
      break;

    case TYPE_RESOURCE : # Resource
      if (empty($post['url'])) {
        print json_encode(array(
          'success' => false,
          'message' => '<div class="messages error"><b>' . t('Please enter an URL') . '</b></div>',
        ));
        exit;
      }
      $node = arguments_create_resource($post['nid'], $post['url'], $post['uimg']);
      if ($node) {
        print json_encode(array(
          'success' => true,
          'message' => '<span class="posted">Your argument posted successfully!</span>',
          'node' => $node,
        ));

      } else {
        $url = parse_url($post['url']);
        if (false !== strpos($url['host'], 'youtube.com')) {
          print json_encode(array(
            'success' => false,
            'message' => '<div class="messages error"><b>' . t('YouTube video ID not found') . '</b></div>',
          ));
        } else {
          print json_encode(array(
            'success' => false,
            'message' => '<div class="messages error"><b>' . t('Error occurred. Please check you URL') . '</b></div>',
          ));
        }
      }
      break;
  }
  exit;
}

/**
 * Debate Node creation
 */
function argument_create_debate($nid, $title)
{
  global $user;
  if (empty($nid) || empty($title)) {
    return false;
  }

  $node = new stdClass();

  $node->type = 'forum';

  // TODO language detection
  global $language;
  $node->language = $user->language ? $user->language : $language->language;

  $node->uid = $user->uid;
  $node->status = 1;
  $node->created = time();
  $node->tnid = 0;
  $node->translate = 0;
  $node->title = $title;
  $node->body = $title;
  $node->teaser = $node->body;
  $node->name = $user->name;

  $node->field_issue[0]['nid'] = $nid;
  $node->field_argument_type[0]['value'] = TYPE_DEBATE;

  $node->forum_tid = 1; // Forum may be only one

//  $node->field_image_path[0]['value'] = '';
//  $node->field_rtype[0]['value'] = 'url';
//  $node->field_source[0]['value'] = '';
//  $node->field_url[0]['value'] = '';
//  $node->field_youtube[0]['value'] = '';

  // Without node_submit()
  $node->validated = TRUE;

  node_save($node);

  return $node;
}

/**
 * argument_resource_preview
 */
function argument_preview_resource()
{
  $_POST += $_REQUEST;

  $url = isset($_POST['url']) ? $_POST['url'] : false;
  $node = argument_fetch_url($url);

  if ($node === false) {
    print json_encode(array(
      'status' => false,
      'message' => t('No URL provided'),
    ));
  } else {
    print json_encode(array(
      'status' => true,
      'message' => theme('argument_resource_preview', $node),
      'success' => $node,
    ));
  }
  exit();
}


function argument_safe_string($string)
{
  // TODO make the string safe
  return preg_replace(
    '/[\x00-\x08\x10\x0B\x0C\x0E-\x19\x7F]' .
      '|[\x00-\x7F][\x80-\xBF]+' .
      '|([\xC0\xC1]|[\xF0-\xFF])[\x80-\xBF]*' .
      '|[\xC2-\xDF]((?![\x80-\xBF])|[\x80-\xBF]{2,})' .
      '|[\xE0-\xEF](([\x80-\xBF](?![\x80-\xBF]))|(?![\x80-\xBF]{2})|[\x80-\xBF]{3,})/S',
    '?', $string);
}

/**
 * Create the core of the resource node by url
 *
 * @param $url
 * @param bool $image
 * @return bool|stdClass
 */
function argument_fetch_url($url, $image = false)
{
  module_load_include('php', 'issue', 'includes/simple_html_dom');
  $html = file_get_html($url);

  if (empty($html)) {
    return false;
  }

  global $user;
  $node = new stdClass();
  $node->type = 'forum';

  // TODO language detection
  global $language;
  $node->language = $user->language ? $user->language : $language->language;

  $node->uid = $user->uid;
  $node->status = 1;
  $node->created = time();
  $node->tnid = 0;
  $node->translate = 0;
  $node->name = $user->name;
  // Without node_submit()
  $node->validated = TRUE;

  $node->field_argument_type[0]['value'] = TYPE_RESOURCE;
  $node->forum_tid = 1; // Forum may be only one

  // url
  $node->field_url[0]['value'] = $url;
  // source
  $url_p = parse_url($url);
  $node->field_source[0]['value'] = $url_p['host'];

  if (false !== strpos($node->field_source[0]['value'], 'youtube.com')) { # YouTube Video
    $node->field_rtype[0]['value'] = 'youtube';

    $params = explode('&', $url_p['query']);
    $youtube_id = false;
    foreach ($params as $param) {
      $param = explode('=', $param, 2);
      if ($param[0] == 'v') {
        $youtube_id = $param[1];
        break;
      }
    }
    if ($youtube_id === false || strlen($youtube_id) != 11) {
      return false;
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
    $node->noimage = false;

  } else { # Regular URL
    $node->field_rtype[0]['value'] = 'url';
    $node->field_youtube[0]['value'] = '';
    // title, body, teaser
    $title = $html->find('title', 0);
    $node->title = empty($title) ? '' : $title->innertext;
    $tags = get_meta_tags($url);
    $node->body = empty($tags) ? '' : $tags['description'];

    # get images
    $node->field_image_path[0]['value'] = file_create_url(file_directory_path() . '/noimage.jpg');
    module_load_include('php', 'issue', 'includes/url_to_absolute');
    $images = array();
    $images_source = $html->find('img');
    foreach ($images_source as $element) {
      # $images[$element->src] = true;
      $images[] = url_to_absolute($url, $element->src);
    }
//    var_dump($images); die();
    $node->images = argument_create_resource_validate_images($images);
    $node->noimage = empty($node->images) ? true : false;

    if ($image !== false) {
      # save image to disk
      $result = drupal_http_request($image, array(), 'POST', '', 3);
      if ($result->data) {
        $ext = argument_create_resource_image_extension($image);
        $hash = md5($image);
        $filepath = file_directory_path() . '/resources/res-' . $hash . '.' . $ext;
        $file = file_save_data($result->data, $filepath, FILE_EXISTS_REPLACE);
        image_scale($file, $filepath, '110', '70');
        $node->field_image_path[0]['value'] = file_create_url($file);
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
    return false;
  }
//  $url_p = parse_url($url);
  $node = argument_fetch_url($url, $image);
  if ($node === false) {
    return false;
  }
  unset($node->images);
  unset($node->noimage);

  $node->field_issue[0]['nid'] = $nid;

  node_save($node);

  return $node;
}