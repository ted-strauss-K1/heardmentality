<?php

/**
 * Markup for the Issue in moderation list
 *
 * @param $node
 * @return string
 */
function moderation_markup_issue($node) {
  return
  '<div class="mod-wrapper part part1 search_list">
    <h2 class="din half">' . rtrim($node->title, "...") . '?</h2>
    <div class="mod-buttons">'.
      sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-view.png" title="View"></a>', $node->path) .
      sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-edit.png" title="Edit"></a>', 'moderation/issue/'.$node->nid) .
      sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-list.png" title="Arguments"></a>', 'moderation/arguments/1/'.$node->nid) .
//      sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-chat.png" title="Replies"></a>', $node->path) .
    '</div>
  </div>';
}

/**
 * Markup for the Argument in moderation list
 *
 * @param $node
 * @return string
 */
function moderation_markup_argument($node) {
  return
  '<div class="mod-wrapper part part1 search_list">
    <h2 class="din half">' . rtrim($node->title, "...") . '</h2>
    <div class="mod-buttons">'.
      sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-view.png" title="View"></a>', 'node/'.$node->parent_issue) .
      sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-edit.png" title="Edit"></a>', 'moderation/argument/'.$node->nid) .
      sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-chat.png" title="Replies"></a>', 'moderation/comments/1/'.$node->nid) .
    '</div>
  </div>';
}

/**
 * Markup for the Comment in moderation list
 *
 * @param $comment
 * @return string
 */
function moderation_markup_comment($comment) {
  return
  '<div class="mod-wrapper part part1 search_list">
    <h2 class="din half">' . rtrim($comment->comment, "...") . '</h2>
    <div class="mod-buttons">'.
      sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-view.png" title="Edit parent Argument"></a>', 'moderation/argument/'.$comment->nid) .
      sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-edit.png" title="Edit"></a>', 'moderation/comment/'.$comment->cid) .
    '</div>
  </div>';
}

/**
 * Markup for the User in moderation list
 *
 * @param $user
 * @return string
 */
function moderation_markup_user($user) {
  static $perms = array();
  if (empty($perms)) {
    $perms = variable_get(MODERATION_USERS, array());
  }
  return
  '<div class="mod-wrapper part part1 search_list">
    <h2 class="din half">' . ucwords($user->name) . '</h2>
    <div class="mod-buttons">'.
    sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-view.png" title="View profile"></a>', $user->viewlink) .
    '<a href="#" class="permission '.(isset($perms[$user->uid]) ? '' : 'remove').'" name="moderation/user/'.$user->uid.'"><img src="/sites/all/themes/heardmentalitylight/images/icon-edit.png" title="Permissions"></a>' .
    '</div>
  </div>';
}

function moderation_perms($uid) {
  $perms = variable_get(MODERATION_USERS, array());
  if ($perms[$uid]) {
    unset($perms[$uid]);
  } else {
    $perms[$uid] = 1;
  }
  variable_set(MODERATION_USERS, $perms);
}
/**
 * Gets the filter values
 *
 * @return array
 */
function moderation_filters() {
  $filters = array();

  $filters['flagged'] = is_null($_SESSION['flagged']) ? -1 : $_SESSION['flagged'];
  $filters['language'] = is_null($_SESSION['language']) ? i18n_get_lang() : $_SESSION['language'];
  $filters['translated'] = is_null($_SESSION['translated']) ? -1 : $_SESSION['translated'];
  $filters['moderation'] = is_null($_SESSION['moderation']) ? -1 : $_SESSION['moderation'];
  $filters['status'] = is_null($_SESSION['status']) ? -1 : $_SESSION['status'];
  $filters['perpage'] = is_null($_SESSION['perpage']) ? 10 : $_SESSION['perpage'];

  return $filters;
}

/**
 * Filters for Content
 *
 * @return array
 */
function moderation_filters_form_content($filters) {
  $form = array();

  $form['filters'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Filters'),
    '#collapsible'  => TRUE,
    '#collapsed'    => TRUE,
  );

  $form['filters']['flagged'] = array(
    '#type'         => 'select',
    '#title'        => t('Flagged'),
    '#options'      => array(0 => t('Not flagged'), 1 => t('Only flagged')) + array(-1 => t('All')),
    '#default_value'=> $filters['flagged'],
  );
  $form['filters']['language'] = array(
    '#type'         => 'select',
    '#title'        => t('Language'),
    '#options'      => i18n_language_list() + array('' => t('All languages')),
    '#default_value'=> $filters['language'],
  );
  $form['filters']['translated'] = array(
    '#type'         => 'select',
    '#title'        => t('Translation'),
    '#options'      => array(0 => t('Not translated'), 1 => t('Translated')) + array(-1 => t('All')),
    '#default_value'=> $filters['translated'],
  );
    $form['filters']['moderation'] = array(
      '#type'         => 'select',
      '#title'        => t('Moderation status'),
      '#options'      => array(0 => t('Not approved by me'), 1 => t('Approved by me')) + array(-1 => t('All')),
      '#default_value'=> $filters['moderation'],
    );
  $form['filters']['status'] = array(
    '#type'         => 'select',
    '#title'        => t('Status'),
    '#options'      => array(1 => t('Active'), 0 => t('Hidden')) + array(-1 => t('All')),
    '#default_value'=> $filters['status'],
  );
  $form['filters']['perpage'] = array(
    '#type'         => 'select',
    '#title'        => t('Per page'),
    '#options'      => array(10 => 10, 15 => 15, 20 => 20, 25 => 25),
    '#default_value'=> $filters['perpage'],
  );

  $form['filters']['submit'] = array(
    '#type'         => 'submit',
    '#value'        => t('Save'),
    '#submit'       => array('moderation_filters_form_content_submit'),
  );

  return $form;
}

/**
 * moderation_issues_form_filters submission
 * Stores the values to $_SESSION
 *
 * @param $form
 * @param $form_state
 */
function moderation_filters_form_content_submit($form, &$form_state) {
  foreach (array('flagged', 'language', 'translated', 'status', 'perpage', 'moderation') as $key) {
    $_SESSION[$key] = $form_state['values'][$key];
  }
}

/**
 * Get page number
 */
function _moderation_get_page() {
  $page = arg(2);
  return is_null($page) || !is_numeric(arg(2)) || $page <= 0 ? 1 : (int)$page;
}

/**
 * Common way to call the list form
 *
 * @param string $type
 * @return array
 */
function _moderation_form($type = 'issues') {
  $form = array();

  $form['#prefix'] = theme('moderation_main', $type);

  $page = _moderation_get_page();
  $pages = 1;

  $filters = moderation_filters();

  if ($type != 'users') {
    $form += moderation_filters_form_content($filters);
  }

  switch ($type) {
    case 'issues' :
      $items = _moderation_filter_nodes($filters + array('type' => 'poll'), $page, $pages);
    break;
    case 'arguments' :
      $items = _moderation_filter_nodes($filters + array('type' => 'forum'), $page, $pages);
    break;
    case 'comments' :
      $items = _moderation_filter_comments($filters, $page, $pages);
    break;
    case 'users' :
      $items = _moderation_filter_users($filters, $page, $pages);
    break;
    default:
      $items = array();
    break;
  }

  foreach ($items as $index => $item) {
    $value = '';
    switch ($type) {
      case 'issues' :
        $value = moderation_markup_issue($item);
      break;
      case 'arguments' :
        $value = moderation_markup_argument($item);
      break;
      case 'comments' :
        $value = moderation_markup_comment($item);
      break;
      case 'users' :
        $value = moderation_markup_user($item);
      break;
    }
    $form['item-'.$index] = array(
      '#type' => 'markup',
      '#value' => $value,
    );
  }

  $pattern = 'moderation/' . $type . '/%d/' . arg(3);
  $form['#suffix'] = theme('moderation_pager', $page, $pages, $pattern);

  $form['#redirect'] = sprintf($pattern, 1);

  return $form;
}

/**
 * Filters the list of Issues/Arguments
 *
 * @param $filters
 * @param $page
 * @param $pages
 * @return array
 */
function _moderation_filter_nodes($filters, &$page, &$pages) {
  $items = array();

  # build query
  $issue_id = arg(3);
  if ($issue_id && is_numeric($issue_id) && ($filters['type'] == 'forum')) {
    $query = "
      SELECT %%
      FROM {node} n
      INNER JOIN {content_type_forum} ctf ON ctf.nid = n.nid AND ctf.field_ref_qid_nid = '".$issue_id."'
      LEFT JOIN {moderation_history} mh ON mh.content_type = 'node' AND mh.type = 'approve' AND mh.content_id = n.nid AND mh.uid = '%s'
      LEFT JOIN {flag_content} fc ON fc.content_id = n.nid AND fc.content_type = 'node'
      WHERE n.type = '%s'";
  } else {
    $query = "
      SELECT %%
      FROM {node} n
      LEFT JOIN {moderation_history} mh ON mh.content_type = 'node' AND mh.type = 'approve' AND mh.content_id = n.nid AND mh.uid = '%s'
      LEFT JOIN {flag_content} fc ON fc.content_id = n.nid AND fc.content_type = 'node'
      WHERE n.type = '%s'";
  }
  if ($filters['language'] == '') {
    $query .= " AND n.language <> '%s'";
  } else {
    $query .= " AND n.language = '%s'";
  }
  switch ($filters['translated']) {
    case 0 :
//      $query .= " AND n.tnid = n.tid";
      $query .= " AND n.tnid = 0";
      break;
    case 1 :
//      $query .= " AND n.tnid <> n.tid";
      $query .= " AND n.tnid <> 0";
      break;
  }
  switch ($filters['status']) {
    case 0 :
    case 1 :
      $query .= " AND n.status = '" . $filters['status'] . "'";
      break;
  }
  switch ($filters['moderation']) {
    case 0 :
      $query .= " AND mh.type IS NULL";
    break;
    case 1 :
      $query .= " AND mh.type IS NOT NULL";
    break;
  }

  global $user;

  # get count and pages
  $once = 1;
  $query_count = str_replace('%%', 'COUNT(DISTINCT n.nid) AS count', $query, $once);
  $count = (int)db_result(db_query($query_count, $user->uid, $filters['type'], $filters['language']));
  $pages = ceil($count/$filters['perpage']);
  if ($pages == 0) {
    $pages = 1;
  }
  if ($page > $pages) {
    $page = $pages;
  }

  $query .= " GROUP BY n.nid" ;
  $query .= " ORDER BY n.changed ASC" ;

  # get nodes
  $once = 1;
  $query = str_replace('%%', 'n.nid', $query, $once);
//  echo sprintf($query, $filters['type'], $user->uid, $filters['language']); die();
  $result = db_query_range($query, $user->uid, $filters['type'], $filters['language'], $filters['perpage']*($page-1), $filters['perpage']);
  while ($node = db_fetch_object($result)) {
    $items[] = node_load($node->nid);
  }

  return $items;
}

/**
 * Filters the list of Comments
 *
 * @param $filters
 * @param $page
 * @param $pages
 * @return array
 */
function _moderation_filter_comments($filters, &$page, &$pages) {
  $items = array();

  $query = "
    SELECT %%
    FROM {comments} c
    LEFT JOIN {moderation_history} mh ON mh.content_type = 'comment' AND mh.type = 'approve' AND mh.content_id = c.cid AND mh.uid = '%s'
    LEFT JOIN {flag_content} fc ON fc.content_id = c.cid AND fc.content_type = 'comment' WHERE 1";
  $argument_id = arg(3);
  if ($argument_id && is_numeric($argument_id)) {
    $query .= " AND c.nid = '".$argument_id."'";
  }
  if ($filters['language'] == '') {
    $query .= " AND c.language <> '%s'";
  } else {
    $query .= " AND c.language = '%s'";
  }
  switch ($filters['translated']) {
    case 0 :
      $query .= " AND c.tnid = 0";
      break;
    case 1 :
      $query .= " AND c.tnid <> 0";
      break;
  }
  switch ($filters['status']) {
    case 0 :
    case 1 :
      $query .= " AND n.status = '" . ($filters['status'] == 0 ? COMMENT_NOT_PUBLISHED : COMMENT_PUBLISHED) . "'";
    break;
  }
  switch ($filters['moderation']) {
    case 0 :
      $query .= " AND mh.type IS NULL";
    break;
    case 1 :
      $query .= " AND mh.type IS NOT NULL";
    break;
  }

  global $user;

  # get count and pages
  $once = 1;
  $query_count = str_replace('%%', 'COUNT(DISTINCT c.cid) AS count', $query, $once);
  $count = (int)db_result(db_query($query_count, $user->uid, $filters['language']));
  $pages = ceil($count/$filters['perpage']);
  if ($pages == 0) {
    $pages = 1;
  }
  if ($page > $pages) {
    $page = $pages;
  }

  $query .= " GROUP BY c.cid" ;
  $query .= " ORDER BY c.timestamp ASC" ;

  # get nodes
  $once = 1;
  $query = str_replace('%%', 'DISTINCT c.*', $query, $once);
  $result = db_query_range($query, $user->uid, $filters['language'], $filters['perpage']*($page-1), $filters['perpage']);
  while ($node = db_fetch_object($result)) {
    _arguments_load_comment($node);
    $items[] = $node;
  }

  return $items;
}

/**
 * Filters the list of Users
 *
 * @param $filters
 * @param $page
 * @param $pages
 * @return array
 */
function _moderation_filter_users($filters, &$page, &$pages) {
  $items = array();

  $query = "SELECT %% FROM {users} u WHERE 1";

  # get count and pages
  $once = 1;
  $query_count = str_replace('%%', 'COUNT(*) AS count', $query, $once);
  $count = (int)db_result(db_query($query_count));
  $pages = ceil($count/$filters['perpage']);
  if ($pages == 0) {
    $pages = 1;
  }
  if ($page > $pages) {
    $page = $pages;
  }

  # get nodes
  $once = 1;
  $query = str_replace('%%', 'u.uid', $query, $once);
  $result = db_query_range($query, $filters['perpage']*($page-1), $filters['perpage']);
  while ($user = db_fetch_object($result)) {
    $items[] = user_load($user->uid);
  }

  return $items;
}

/**
 * Moderation for Issues
 *
 * @return array
 */
function moderation_issues_form() {
  return _moderation_form('issues');
}

/**
 * Moderation for Arguments
 *
 * @return array
 */
function moderation_arguments_form() {
  return _moderation_form('arguments');
}

/**
 * Moderation for Comments
 *
 * @return array
 */
function moderation_comments_form() {
  return _moderation_form('comments');
}

/**
 * Moderation for Users
 *
 * @return array
 */
function moderation_users_form() {
  return _moderation_form('users');
}

/**
 * Moderation for Issues (View)
 *
 * @return array
 */
function moderation_issue_view_form($form_state, $nid) {
  $form = array();

  $form['content_id'] = array(
    '#type' => 'hidden',
    '#value' => $nid,
  );
  $form['content_type'] = array(
    '#type' => 'hidden',
    '#value' => 'node',
  );

  $form['#prefix'] = theme('moderation_main', 'issues');
  $form['#attributes']['class'] = 'mod-form';

  $node = node_load($nid);
  poll_ext_chtext_short($node);

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#value' => $node->title,
  );
  $form['body'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#value' => $node->body,
  );

  $form['choices'] = array(
    '#type' => 'fieldset',
    '#title' => t('Leave the choice text empty to request its deletion'),
    '#prefix' => '<div id="choices-wrapper">',
    '#suffix' => '</div>',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  foreach ($node->choice as $delta => $choice) {
    $form_element = _moderation_ahah_choice($delta, $choice, $nid);
    $form['choices'][$delta] = $form_element;
  }

  $form['choices']['add_more'] = array(
    '#type' => 'submit',
    '#value' => '+ ' . t('Add another choice'),
    '#weight' => 1,
    '#ahah' => array(
      'path' => 'moderation/ahah/choice',
      'wrapper' => 'choices-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $selected1 = array();
  $selected2 = array();
  $selected3 = array();
  foreach ($node->field_issue_country as $item) {
    $selected1[] = $item['value'];
  }
  foreach ($node->field_issue_state as $item) {
    $selected2[] = $item['value'];
  }
  foreach ($node->field_issue_city as $item) {
    $selected3[] = $item['value'];
  }

//  var_dump($node); die();

  $data = moderation_location(array(
    'selected1' => $selected1,
    'selected2' => $selected2,
    'selected3' => $selected3,
  ));
  $loc1 = $data['loc1'];
  $locs1 = $data['locs1'];
  $loc2 = $data['loc2'];
  $locs2 = $data['locs2'];
  $loc3 = $data['loc3'];
  $locs3 = $data['locs3'];

  # loc wrapper
  $form['loc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Locations'),
    '#prefix' => '<div id="loc-wrapper">',
    '#suffix' => '</div>',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['loc']['loc1'] = array(
    '#type' => 'select',
    '#options' => $loc1,
    '#value' => $locs1,
    '#ahah' => array(
      'wrapper' => 'loc-wrapper-loc2',
      'path' => 'moderation/ahah/loc/loc1',
      'effect' => 'fade',
      'event' => 'click',
    ),
    '#size' => 5,
    '#multiple' => 'multiple',
    '#prefix' => '<div id="loc-wrapper-loc1">',
    '#suffix' => '</div>',
  );
  $form['loc']['loc2'] = array(
    '#type' => 'select',
    '#options' => $loc2,
    '#value' => $locs2,
    '#size' => 5,
    '#multiple' => 'multiple',
    '#ahah' => array(
      'wrapper' => 'loc-wrapper-loc3',
      'path' => 'moderation/ahah/loc/loc2',
      'effect' => 'fade',
      'event' => 'click',
    ),
    '#prefix' => '<div id="loc-wrapper-loc2">',
    '#suffix' => '</div>',
  );
  $form['loc']['loc3'] = array(
    '#type' => 'select',
    '#options' => $loc3,
    '#value' => $locs3,
    '#multiple' => 'multiple',
    '#size' => 5,
    '#prefix' => '<div id="loc-wrapper-loc3">',
    '#suffix' => '</div>',
  );

  # Tags fieldset
  $form['tags'] = array(
    '#type' => 'fieldset',
    '#title' => t('Categories'),
    '#prefix' => '<div id="tags-wrapper">',
    '#suffix' => '</div>',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  # node tags
  $tags = array();
  foreach ($node->taxonomy as $tid => $term) {
    $tags[] = $tid;
  }
  $data = moderation_tags(array(
    'selected1' => $tags,
    'selected2' => $tags,
    'selected3' => $tags,
  ));

  $form['tags']['cat1'] = array(
    '#type' => 'select',
    '#options' => $data['tag1'],
    '#value' => $data['tags1'],
    '#ahah' => array(
      'wrapper' => 'tags-wrapper-cat2',
      'path' => 'moderation/ahah/tags/cat1',
      'effect' => 'fade',
      'event' => 'click',
    ),
    '#size' => 5,
    '#multiple' => 'multiple',
    '#prefix' => '<div id="tags-wrapper-cat1">',
    '#suffix' => '</div>',
  );
  $form['tags']['cat2'] = array(
    '#type' => 'select',
    '#options' => $data['tag2'],
    '#value' => $data['tags2'],
    '#size' => 5,
    '#multiple' => 'multiple',
    '#ahah' => array(
      'wrapper' => 'tags-wrapper-cat3',
      'path' => 'moderation/ahah/tags/cat2',
      'effect' => 'fade',
      'event' => 'click',
    ),
    '#prefix' => '<div id="tags-wrapper-cat2">',
    '#suffix' => '</div>',
  );
  $form['tags']['cat3'] = array(
    '#type' => 'select',
    '#options' => $data['tag3'],
    '#value' => $data['tags3'],
    '#multiple' => 'multiple',
    '#size' => 5,
    '#prefix' => '<div id="tags-wrapper-cat3">',
    '#suffix' => '</div>',
  );


  $form['save'] = array(
    '#type'         => 'submit',
    '#value'        => t('Save'),
    '#submit'       => array('moderation_issue_view_form_save'),
  );
  if (!moderation_history('get', $form['content_id']['#value'], $form['content_type']['#value'], 'delete')) {
    $form['delete'] = array(
      '#type'         => 'submit',
      '#value'        => t('Deletion request'),
      '#submit'       => array('moderation_issue_view_form_delete'),
    );
  }


  return $form;
}

function moderation_tags($data) {
  $selected1 = $data['selected1'];
  $selected2 = $data['selected2'];
  $selected3 = $data['selected3'];

  # 1-level tags
  $tag1 = issue_get_taxonomy_root();
  # 1-level selected tags
  $tags1 = array();
  foreach ($selected1 as $tag_id) {
    if (isset($tag1[$tag_id])) {
      $tags1[] = $tag_id;
    }
  }
  # 2-level tags
  $tag2 = array();
  foreach ($tags1 as $parent_tid) {
    $tids = taxonomy_get_children($parent_tid);
    foreach ($tids as $tid => $term) {
      $tag2[$tid] = $term->name;
    }
  }
  # 2-level selected tags
  $tags2 = array();
  foreach ($selected2 as $tag_id) {
    if (isset($tag2[$tag_id])) {
      $tags2[] = $tag_id;
    }
  }
  if (empty($tag2)) {
    $tag2 = array(-1 => t('No sub categories'));
  }
  # 3-level tags
  $tag3 = array();
  foreach ($tags2 as $parent_tid) {
    $tids = taxonomy_get_children($parent_tid);
    foreach ($tids as $tid => $term) {
      $tag3[$tid] = $term->name;
    }
  }
  # 3-level selected tags
  $tags3 = array();
  foreach ($selected3 as $tag_id) {
    if (isset($tag3[$tag_id])) {
      $tags3[] = $tag_id;
    }
  }
  if (empty($tag3)) {
    $tag3 = array(-1 => t('No sub categories'));
  }

  $output = array(
    'tag1' => $tag1,
    'tags1' => $tags1,
    'tag2' => $tag2,
    'tags2' => $tags2,
    'tag3' => $tag3,
    'tags3' => $tags3,
  );

  return $output;
}

function moderation_location($data) {
  $selected1 = $data['selected1'];
  $selected2 = $data['selected2'];
  $selected3 = $data['selected3'];
  # 1-level locs
  $countries = geonames_query('countryinfo');
  $loc1 = array();
  foreach ($countries->results as $country) {
    $loc1[$country['countrycode']] = $country['countryname'];
  }
  asort($tag1);
  # 1-level selected locs
  $locs1 = array();
  foreach ($selected1 as $country) {
    if (isset($loc1[$country])) {
      $locs1[] = $country;
    }
  }
  # 2-level locs
  $loc2 = array();
  foreach ($locs1 as $countrycode) {
    $info = geonames_countryinfo($countrycode);
    $results = geonames_query('children', array('geonameid' => $info['geonameid']));
    foreach ($results->results as $state) {
      $loc2[$state['geonameid']] = $state['name'];
    }
  }
  # 2-level selected locs
  $locs2 = array();
  foreach ($selected2 as $statecode) {
    if (isset($loc2[$statecode])) {
      $locs2[] = $statecode;
    }
  }
  if (empty($loc2)) {
    $loc2 = array(-1 => t('No regions/states'));
  }
  # 3-level locs
  $loc3 = array();
  foreach ($locs2 as $citycode) {
    $results = geonames_query('children', array('geonameid' => $citycode));
    foreach ($results->results as $state) {
      $loc3[$state['geonameid']] = $state['name'];
    }
  }
  # 3-level selected locs
  $locs3 = array();
  foreach ($selected3 as $statecode) {
    if (isset($loc3[$statecode])) {
      $locs3[] = $statecode;
    }
  }
  if (empty($loc3)) {
    $loc3 = array(-1 => t('No cities'));
  }

  $output = array(
    'loc1' => $loc1,
    'locs1' => $locs1,
    'loc2' => $loc2,
    'locs2' => $locs2,
    'loc3' => $loc3,
    'locs3' => $locs3,
  );

  return $output;
}

function moderation_ahah($type) {

  # build new form
  $form_state = array('submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  if (!$form = form_get_cache($form_build_id, $form_state)) {
    exit();
  }

  # change the form parts
  switch ($type) {
    case 'choice' :
      $delta = count($_POST['choices']);
      $form_element = _moderation_ahah_choice($delta);
      drupal_alter('form', $form_element, array());
      $form['choices'][$delta] = $form_element;
    break;
    case 'tags' :
      $data = moderation_tags(array(
        'selected1' => is_null($_POST['cat1']) ? array() : $_POST['cat1'],
        'selected2' => is_null($_POST['cat2']) ? array() : $_POST['cat2'],
        'selected3' => is_null($_POST['cat3']) ? array() : $_POST['cat3'],
      ));
      $case = arg(3);

      if ($case == 'cat1') {
        $form['tags']['cat2'] = array(
          '#type' => 'select',
          '#options' => $data['tag2'],
          '#value' => $data['tags2'],
          '#size' => 5,
          '#multiple' => 'multiple',
          '#ahah' => array(
            'wrapper' => 'tags-wrapper-cat3',
            'path' => 'moderation/ahah/tags/cat2',
            'effect' => 'fade',
            'event' => 'click',
          ),
        );
      }
      if ($case == 'cat2') {
        $form['tags']['cat3'] = array(
          '#type' => 'select',
          '#options' => $data['tag3'],
          '#value' => $data['tags3'],
          '#multiple' => 'multiple',
          '#size' => 5,
          '#prefix' => '<div id="tags-wrapper-cat3">',
          '#suffix' => '</div>',
        );
      }

    break;
    case 'loc' :
      $data = moderation_location(array(
        'selected1' => is_null($_POST['loc1']) ? array() : $_POST['loc1'],
        'selected2' => is_null($_POST['loc2']) ? array() : $_POST['loc2'],
        'selected3' => is_null($_POST['loc3']) ? array() : $_POST['loc3'],
      ));
      $case = arg(3);
      if ($case == 'loc1') {
        $form['loc']['loc2'] = array(
          '#type' => 'select',
          '#options' => $data['loc2'],
          '#value' => $data['locs2'],
          '#size' => 5,
          '#multiple' => 'multiple',
          '#ahah' => array(
            'wrapper' => 'loc-wrapper-loc3',
            'path' => 'moderation/ahah/loc/loc2',
            'effect' => 'fade',
            'event' => 'click',
          ),
        );
      }
      if ($case == 'loc2') {
        $form['loc']['loc3'] = array(
          '#type' => 'select',
          '#options' => $data['loc3'],
          '#value' => $data['locs3'],
          '#multiple' => 'multiple',
          '#size' => 5,
        );
      }
    break;
  }

  # save the form
  form_set_cache($form_build_id, $form, $form_state);

  # rebuild new form
  $form += array(
    '#post' => $_POST,
    '#programmed' => FALSE,
  );
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form = form_builder($form_id, $form, $form_state);

  # render the form parts
  switch ($type) {
    case 'choice' :
      $choice_form = $form['choices'];
      $output = drupal_render($choice_form);
    break;
    case 'tags' :
      $form_element = $case == 'cat1' ? $form['tags']['cat2'] : $form['tags']['cat3'];
      $output = drupal_render($form_element);
    break;
    case 'loc' :
      $form_element = $case == 'loc1' ? $form['loc']['loc2'] : $form['loc']['loc3'];
      $output = drupal_render($form_element);
    break;
  }

  print json_encode(array('status' => TRUE, 'data' => $output, 'post' => $_POST, 'output' => $data, 'case' => $case));
  exit;
}

function _moderation_ahah_choice($delta, $choice = false, $nid = 0) {
  $form = array(
    '#tree' => TRUE,
  );
  // We'll manually set the #parents property of these fields so that
  // their values appear in the $form_state['values']['choice'] array.
  $form['chtext'] = array(
    '#type' => 'textfield',
    '#title' => t('Choice @n', array('@n' => ($delta + 1))),
    '#default_value' => $choice['chtext'],
    '#parents' => array('choices', $delta, 'chtext'),
  );
  $form['chtext-short'] = array(
    '#type' => 'textfield',
    '#title' => t('Choice short text @n', array('@n' => ($delta + 1))),
    '#default_value' => $choice['chtext_short'],
    '#parents' => array('choices', $delta, 'chtext-short'),
  );
  $form['chorder'] = array(
    '#type' => 'hidden',
    '#default_value' => is_null($choice['chorder']) ? $delta : $choice['chorder'],
    '#parents' => array('choices', $delta, 'chorder'),
  );
  $form['charact'] = array(
    '#type' => 'fieldset',
    '#title' => t('Metadata'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $charact = poll_charact_values_get($nid, $choice['chorder']);
  foreach ($charact as $cid => $char) {
    $form['charact']['char'.$cid] = array(
      '#type' => 'select',
      '#title' => t($char['name']),
      '#options' => range(1,5),
      '#value' => $char['value'],
      '#size' => 5,
      '#parents' => array('choices', $delta, 'charact', 'char'.$cid),
    );
  }
  return $form;
}


/**
 * Moderation for Arguments (View)
 *
 * @return array
 */
function moderation_argument_view_form($form, $nid) {
  $form = array();

  $form['content_id'] = array(
    '#type' => 'hidden',
    '#value' => $nid,
  );
  $form['content_type'] = array(
    '#type' => 'hidden',
    '#value' => 'node',
  );

  $form['#prefix'] = theme('moderation_main', 'arguments');
  $form['#attributes']['class'] = 'mod-form';

  $node = node_load($nid);

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#value' => $node->title,
  );
//  $form['body'] = array(
//    '#type' => 'textarea',
//    '#title' => t('Description'),
//    '#value' => $node->body,
//  );
  if ($node->field_type[0]['value'] == TYPE_DEBATE) {
    $choices = issue_choices($node->parent_issue);
    foreach ($choices as $i => $choice) {
      $value = $node->options[$choice['chorder']]['value'];
      $form['option_' . $i] = array(
        '#type'           => 'select',
        '#options'        => array('-1' => '-', '0' => '-/+', '1' => '+'),
        '#attributes'     => array('class' => 'select-value'),
        '#id'             => 'sup_' . $i,
        '#default_value'  => is_null($value) ? 0 : $value,
        '#prefix'         => '
        <div>
          <table>
            <tr>
              <td class="first">
                <label class="value floatleft">' . $choice['short_answer'] . '</label>
              </td>
              <td>',
        '#suffix' => '
              </td>
            </tr>
          </table>
        </div>',
      );
      $form['chorder_' . $i] = array(
        '#type'   => 'hidden',
        '#value'  => $choice['chorder'],
      );
    }
  }


  $form['save'] = array(
    '#type'         => 'submit',
    '#value'        => t('Save'),
    '#submit'       => array('moderation_argument_view_form_save'),
  );
  if (!moderation_history('get', $form['content_id']['#value'], $form['content_type']['#value'], 'delete')) {
    $form['delete'] = array(
      '#type'         => 'submit',
      '#value'        => t('Deletion request'),
      '#submit'       => array('moderation_argument_view_form_delete'),
    );
  }

  return $form;
}

/**
 * Moderation for Comments (View)
 *
 * @return array
 */
function moderation_comment_view_form($form, $cid) {
  $form = array();

  $form['content_id'] = array(
    '#type' => 'hidden',
    '#value' => $cid,
  );
  $form['content_type'] = array(
    '#type' => 'hidden',
    '#value' => 'comment',
  );


  $form['#prefix'] = theme('moderation_main', 'comments');
  $form['#attributes']['class'] = 'mod-form';

  $comment = _comment_load($cid);

  $form['comment'] = array(
    '#type' => 'textarea',
    '#title' => t('Comment'),
    '#value' => $comment->comment,
  );
//  $form['status'] = array(
//    '#type' => 'select',
//    '#title' => t('Status'),
//    '#options' => array(
//      COMMENT_PUBLISHED => t('Published'),
//      COMMENT_NOT_PUBLISHED => t('Not published'),
//    ),
//    '#default_value' => $comment->status,
//  );
  $form['str_wk'] = array(
    '#type' => 'select',
    '#title' => t('Mode'),
    '#options' => array(
      1 => t('Strenghten'),
      0 => t('Weaken'),
    ),
    '#default_value' => $comment->str_wk,
  );

  $form['save'] = array(
    '#type'         => 'submit',
    '#value'        => t('Save'),
    '#submit'       => array('moderation_comment_view_form_save'),
  );
  if (!moderation_history('get', $form['content_id']['#value'], $form['content_type']['#value'], 'delete')) {
    $form['delete'] = array(
      '#type'         => 'submit',
      '#value'        => t('Deletion request'),
      '#submit'       => array('moderation_comment_view_form_delete'),
    );
  }

  return $form;
}

/**
 * Theme for pager
 */
function theme_moderation_pager($page, $pages, $pattern) {
  if ($pages == 1) return '';
  if ($page > $pages) $page = $pages;
  $output = '<div class="mod-pager"><span class="mod-text">PAGE</span> &nbsp;';
  $a = '<a href="/%s" class="%s">%d</a>';
  $showpages = array_unique( array(1,2,$page-1,$page,$page+1,$pages-1,$pages) );
  $flag = true;
  for ($i=1; $i<=$pages; $i++) {
    if (in_array($i, $showpages)) {
      $output .= sprintf($a, sprintf($pattern, $i), $page == $i ? 'mod-active' : '', $i);
      $flag = true;
    } elseif ($i == 3 || $i == $pages - 2) {
      if ($flag) $output .= '<span class="mod-spacer">&nbsp;</span>';
      $flag = false;
    }
  }
  $output .= '</div>';
  return $output;
}

function moderation_issue_view_form_save(&$form, &$form_state) {

  $values = $form_state["clicked_button"]['#post'];
  $nid = $values['content_id'];
  $node = node_load($nid);
  poll_ext_chtext_short($node);

  $changed = array();
  if ($node->title != $values['title']) {
    $changed['title'] = $values['title'];
  }
  if ($node->body != $values['body']) {
    $changed['body'] = $values['body'];
  }

  foreach ($values['choices'] as $i => $choice) {
    $chorder = $choice['chorder'];
    $chtext = $choice['chtext'];
    $chtext_short = $choice['chtext-short'];
    if ($node->choice[$chorder]['chtext'] != $chtext) {
      $changed['choices'][$chorder]['chtext'] = $chtext;
    }
    if ($node->choice[$chorder]['chtext_short'] != $chtext_short) {
      $changed['choices'][$chorder]['chtext_short'] = $chtext_short;
    }
    if (!empty($changed['choices'][$chorder])) {
      $changed['choices'][$chorder] += array(
        'chorder' => $chorder,
        'chtext_old' => $node->choice[$chorder]['chtext'],
      );
    }
  }

  # tags
  $node->taxonomy = array();
  $tids = array_merge($values['cat1'], $values['cat2'], $values['cat3']);
  foreach ($tids as $tid) {
    $node->taxonomy[] = taxonomy_get_term($tid);
  }

  # locations
  $data = moderation_location(array(
    'selected1' => $values['loc1'],
    'selected2' => $values['loc2'],
    'selected3' => $values['loc3'],
  ));
  $node->field_issue_country = array();
  foreach ($data['locs1'] as $countrycode) {
    $node->field_issue_country[] = array('value' => $countrycode);
  }
  $node->field_issue_state = array();
  foreach ($data['locs2'] as $statecode) {
    $node->field_issue_state[] = array('value' => (int)$statecode);
  }
  $node->field_issue_city = array();
  foreach ($data['locs3'] as $citycode) {
    $node->field_issue_city[] = array('value' => (int)$citycode);
  }

//  var_dump($node); die();

  if (empty($changed)) {
    // approved
    moderation_history('del', $nid, 'node', 'approve');
    moderation_history('set', $nid, 'node', 'approve');
  } else {
    if (isset($changed['title'])) $node->title = $changed['title'];
    if (isset($changed['body'])) $node->body = $changed['body'];

    foreach ($changed['choices'] as $chorder => $case) {
      $choice = &$node->choice[$chorder];
      if ($case['chtext_short'] != '') {
        poll_ext_chtext_short_set($nid, $chorder, $case['chtext_short']);
      }
      if (isset($case['chtext'])) {
        if ($case['chtext'] != '')  {
          $choice['chtext'] = $case['chtext'];
        } else {
          moderation_history('set', $nid, 'choice', 'delete', array('chorder' => $chorder));
        }
      }
    }
    moderation_history('set', $nid, 'node', 'edit', $changed);
  }
  node_save($node);
}


function moderation_argument_view_form_save(&$form, &$form_state) {
  $values = $form_state["clicked_button"]['#post'];
  $nid = $values['content_id'];
  $node = node_load($nid);

  $changed = array();
  if ($node->title != $values['title']) {
    $changed['title'] = $values['title'];
  }
  if ($node->field_type[0]['value'] == TYPE_DEBATE) {
    $choices = issue_choices($node->parent_issue);
    for ($i=0; $i>=0; $i++) {
      if (is_null($values['chorder_' . $i])) break;
      $chorder = $values['chorder_' . $i];
      $option = $values['option_' . $i];
      foreach ($choices as $choice) {
        if ($choice['chorder'] == $chorder) {
          $value = $node->options[$choice['chorder']]['value'];
          $value = is_null($value) ? 0 : $value;
          if ($value != $option) {
            $changed['options'][] = array('chorder' => $chorder, 'option' => $option, 'chtext' => $choice['chtext']);
          }
          break;
        }
      }
    }
  }

  if (empty($changed)) {
    // approved
    moderation_history('del', $nid, 'node', 'approve');
    moderation_history('set', $nid, 'node', 'approve');
  } else {
    if (isset($changed['title'])) {
      $node->title = $changed['title'];
      node_save($node);
    }
    foreach ($changed['options'] as $case) {
      db_query("UPDATE {arguments_options} SET val = '%d' WHERE nid = '%d' AND chorder = '%d'", $case['option'], $nid, $case['chorder']);
    }
    moderation_history('set', $nid, 'node', 'edit', $changed);
  }

}


function moderation_comment_view_form_save(&$form, &$form_state) {
  $cid = $form['content_id']['#value'];
  $comment = _comment_load($cid);
  $values = $form_state["clicked_button"]['#post'];

  $changed = array();
  $sql = "UPDATE {comments} SET";
  $items = array(
    'comment',
//    'status',
    'str_wk'
  );
  foreach ($items as $item) {
    if ($comment->{$item} != $values[$item]) {
      $changed[$item] = $values[$item];
    }
  }
  if (empty($changed)) {
    // approved
    moderation_history('del', $cid, 'comment', 'approve');
    moderation_history('set', $cid, 'comment', 'approve');
  } else {
    $sql2 = array();
    foreach ($changed as $item => $value) {
      $sql2[] = ' ' . $item . " = '%s'";
    }
    $sql .= implode(',', $sql2) . " WHERE cid = '%d'";
    $v = array_values($changed);
    $v[] = $cid;
    db_query($sql, $v);
    moderation_history('set', $cid, 'comment', 'edit', $changed);
  }
}

function moderation_issue_view_form_delete(&$form, &$form_state) {
  moderation_delete_request($form);
}


function moderation_argument_view_form_delete(&$form, &$form_state) {
  moderation_delete_request($form);
}


function moderation_comment_view_form_delete(&$form, &$form_state) {
  moderation_delete_request($form);
}

function moderation_delete_request($form) {
  moderation_history('set', $form['content_id']['#value'], $form['content_type']['#value'], 'delete');
  $delete_requests = count(moderation_history('get', $form['content_id']['#value'], $form['content_type']['#value'], 'delete'));
  $required = 3;
  if ($delete_requests >= $required) {
    switch ($form['content_type']['#value']) {
      case 'comment' :
        db_query("UPDATE comment SET status = '%d' WHERE cid = '%d'", COMMENT_NOT_PUBLISHED, $form['content_id']['#value']);
      break;
      case 'node' :
        db_query("UPDATE node SET status = '%d' WHERE nid = '%d'", 1, $form['content_id']['#value']);
      break;
    }
    drupal_set_message(t('Content deletion approved.'));
  } else {
    drupal_set_message(t('Content deletion not approved.') . ' '.($required-$delete_requests) . ' ' . t('deletion requests from other moderators are required.'));
  }
}










