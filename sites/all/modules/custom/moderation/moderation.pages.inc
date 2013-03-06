<?php

/**
 * Theme for pager
 *
 * @param $page
 * @param $pages
 * @param $pattern
 * @return string
 */
function theme_moderation_pager($page, $pages, $pattern)
{
  if ($pages == 1) return '';
  if ($page > $pages) $page = $pages;
  $output = '<div class="mod-pager"><span class="mod-text">PAGE</span> &nbsp;';
  $a = '<a href="/%s" class="%s">%d</a>';
  $showpages = array_unique(array(1, 2, $page - 1, $page, $page + 1, $pages - 1, $pages));
  $flag = true;
  for ($i = 1; $i <= $pages; $i++) {
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

/**
 * @param $content_type
 * @param $content_id
 * @return string
 */
function theme_moderation_flags($content_type, $content_id)
{
  $flags = '';
  $flag = false;
  $result = db_query("
    SELECT f.fid, f.name flag, f.title, u.uid, u.name, fn.note
    FROM flag_content fc
    INNER JOIN flags f ON f.fid = fc.fid AND f.content_type = fc.content_type
    INNER JOIN users u ON u.uid = fc.uid
    LEFT JOIN flag_note fn ON fn.fid = fc.fid AND fn.content_type = fc.content_type
    WHERE fc.content_id = '%d' AND fc.content_type = '%s'
  ", $content_id, $content_type);
  while ($row = db_fetch_object($result)) {
    if ($flag != $row->fid) {
      if ($flag !== false) {
        $flags .= '<br>';
      }
      $flags .= sprintf('<b>%s</b>: ', $row->title);
    }
    $flags .= sprintf('&nbsp;<a href="/user/profile/view/%d" class="usernote" original-title="%s">%s</a>', $row->uid, addslashes($row->note), $row->name);
  }
  return $flags;
}

/**
 * Markup for the Issue in moderation list
 *
 * @param $node
 * @return string
 */
function moderation_markup_issue($node)
{
  return
    '<div class="mod-wrapper part part1 search_list">
    <h2 class="din half">' . l(rtrim($node->title), 'moderation/issue/' . $node->nid) . '? '.
//    '<div class="open"></div>' .
    '</h2>
    <div class="mod-buttons">' .
    sprintf('<a href="/%s" target="_blank"><span class="mod-view mod-icon" title="%s"></span></a>', $node->path, t('View')) .
//    sprintf('<a href="/%s" target="_blank"><span class="mod-edit mod-icon" title="%s"></span></a>', 'moderation/issue/' . $node->nid, t('Edit')) .
    sprintf('<a href="/%s" target="_blank"><span class="mod-list mod-icon" title="%s"></span></a>', 'moderation/arguments/1/' . $node->nid, t('Arguments')) .
    '</div>
  </div>';
}

/**
 * Markup for the Argument in moderation list
 *
 * @param $node
 * @return string
 */
function moderation_markup_argument($node)
{
  return
    '<div class="mod-wrapper part part1 search_list">
    <h2 class="din half">' . l(rtrim($node->title), 'moderation/argument/' . $node->nid) .
//    ' <div class="open"></div>'.
    ' </h2>
    <div class="mod-buttons">' .
    sprintf('<a href="/%s" target="_blank"><span class="mod-view mod-icon" title="%s"></span></a>', 'node/' . $node->parent_issue, t('View')) .
//    sprintf('<a href="/%s" target="_blank"><span class="mod-edit mod-icon" title="%s"></span></a>', 'moderation/argument/' . $node->nid, t('Edit')) .
    sprintf('<a href="/%s" target="_blank"><span class="mod-chat mod-icon" title="%s"></span></a>', 'moderation/comments/1/' . $node->nid, t('Replies')) .
    '</div>
  </div>';
}

/**
 * Markup for the Comment in moderation list
 *
 * @param $comment
 * @return string
 */
function moderation_markup_comment($comment)
{
  return
    '<div class="mod-wrapper part part1 search_list">
    <h2 class="din half">' . l(rtrim($comment->comment), 'moderation/comment/' . $comment->cid) .
//    ' <div class="open"></div> '.
    '</h2>
    <div class="mod-buttons">' .
    sprintf('<a href="/%s" target="_blank"><span class="mod-view mod-icon" title="%s"></span></a>', 'moderation/argument/' . $comment->nid, t('Edit parent argument')) .
//    sprintf('<a href="/%s" target="_blank"><span class="mod-edit mod-icon" title="%s"></span></a>', 'moderation/comment/' . $comment->cid, t('Edit')) .
    '</div>
  </div>';
}

/**
 * Markup for the User in moderation list
 *
 * @param $user
 * @return string
 */
function moderation_markup_user($user)
{
  static $perms = array();

  if (empty($perms)) {
    $perms = variable_get(MODERATION_USERS, array());
  }

  return user_access(MODERATION_ADMIN, $user) ? '' :
    '<div class="mod-wrapper part part1 search_list">
    <h2 class="din half">' . ucwords($user->name) . ' <div class="open"></div> </h2>
    <div class="mod-buttons">' .
      sprintf('<a href="/%s" target="_blank"><span class="mod-view mod-icon" title="%s"></span></a>', $user->viewlink, t('View Profile')) .
      sprintf('<a href="#" class="permission %s" name="%s"><span class="mod-edit mod-icon" title="%s"></span></a>',
        !moderation_check_perm($user->uid) ? '' : 'remove', 'moderation/user/' . $user->uid, t('Change permissions')) .
      '</div>
  </div>';
}

/**
 * @param $uid
 */
function moderation_perms($uid)
{
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
function moderation_filters()
{
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
function moderation_filters_form_content($filters)
{
  $form = array();

  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filters'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['filters']['flagged'] = array(
    '#type' => 'select',
    '#title' => t('Flagged'),
    '#options' => array(0 => t('Not flagged'), 1 => t('Only flagged')) + array(-1 => t('All')),
    '#default_value' => $filters['flagged'],
  );
  $form['filters']['language'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#options' => i18n_language_list() + array('' => t('All languages')),
    '#default_value' => $filters['language'],
  );
  $form['filters']['translated'] = array(
    '#type' => 'select',
    '#title' => t('Translation'),
    '#options' => array(0 => t('Not translated'), 1 => t('Translated')) + array(-1 => t('All')),
    '#default_value' => $filters['translated'],
  );
  $form['filters']['moderation'] = array(
    '#type' => 'select',
    '#title' => t('Moderation status'),
    '#options' => array(0 => t('Not approved by me'), 1 => t('Approved by me')) + array(-1 => t('All')),
    '#default_value' => $filters['moderation'],
  );
  $form['filters']['status'] = array(
    '#type' => 'select',
    '#title' => t('Status'),
    '#options' => array(1 => t('Active'), 0 => t('Hidden')) + array(-1 => t('All')),
    '#default_value' => $filters['status'],
  );
  $form['filters']['perpage'] = array(
    '#type' => 'select',
    '#title' => t('Per page'),
    '#options' => array(10 => 10, 15 => 15, 20 => 20, 25 => 25),
    '#default_value' => $filters['perpage'],
  );

  $form['filters']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('moderation_filters_form_content_submit'),
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
function moderation_filters_form_content_submit($form, &$form_state)
{
  foreach (array('flagged', 'language', 'translated', 'status', 'perpage', 'moderation') as $key) {
    $_SESSION[$key] = $form_state['values'][$key];
  }
}

/**
 * Get page number
 */
function _moderation_get_page()
{
  $page = arg(2);
  return is_null($page) || !is_numeric(arg(2)) || $page <= 0 ? 1 : (int)$page;
}

/**
 * Common way to call the list form
 *
 * @param string $type
 * @return array
 */
function _moderation_form($type = 'issues')
{
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
    $form['item-' . $index] = array(
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
function _moderation_filter_nodes($filters, &$page, &$pages)
{
  $items = array();

  global $user;

  # build query
  $query = "SELECT %% FROM {node} n";
  $params = array();

  // arguments of issue
  if (($issue_id = arg(3)) && is_numeric($issue_id) && ($filters['type'] == 'forum')) {
    $query .= " INNER JOIN {content_type_forum} ctf ON ctf.nid = n.nid AND ctf.field_issue_nid = '%d'";
    $params[] = $issue_id;
  }

  // moderation
  if ($filters['moderation'] != -1) {
    $query .= " LEFT JOIN {moderation_history} mh ON mh.content_type = '%s' AND mh.type = '%s' AND mh.content_id = n.nid AND mh.uid = '%d'";
    $params[] = 'node';
    $params[] = 'approve';
    $params[] = $user->uid;
  }

  // flagged
  if ($filters['flagged'] != -1) {
    $query .= " LEFT JOIN {flag_content} fc ON fc.content_id = n.nid AND fc.content_type = '%s'";
    $params[] = 'node';
  }

  // type
  $query .= " WHERE n.type = '%s'";
  $params[] = $filters['type'];

  // language
  if ($filters['language'] != '') {
    // todo
    $query .= " AND n.language = '%s'";
    $params[] = $filters['language'];
  }

  // translation
  switch ($filters['translated']) {
    case 0 :
      $query .= " AND n.tnid = 0";
      break;
    case 1 :
      $query .= " AND n.tnid <> 0";
      break;
  }

  // status
  switch ($filters['status']) {
    case 0 :
    case 1 :
      $query .= " AND n.status = '" . $filters['status'] . "'";
      break;
  }

  // moderation
  switch ($filters['moderation']) {
    case 0 :
      $query .= " AND mh.type IS NULL";
      break;
    case 1 :
      $query .= " AND mh.type IS NOT NULL";
      break;
  }

  // todo add flag param filters

  # get count and pages
  $once = 1;
  $query_count = str_replace('%%', 'COUNT(DISTINCT n.nid) AS count', $query, $once);
  $count = (int)db_result(db_query($query_count, $params));
  $pages = ceil($count / $filters['perpage']);
  if ($pages == 0) {
    $pages = 1;
  }
  if ($page > $pages) {
    $page = $pages;
  }

  $query .= " GROUP BY n.nid";
  $query .= " ORDER BY n.changed ASC";

  # get nodes
  $once = 1;
  $query = str_replace('%%', 'n.nid', $query, $once);
  $result = db_query_range($query, $params, $filters['perpage'] * ($page - 1), $filters['perpage']);
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
function _moderation_filter_comments($filters, &$page, &$pages)
{
  $items = array();

  global $user;

  # build query
  $query = "SELECT %% FROM {comments} c";
  $params = array();

  // moderation
  if ($filters['moderation'] != -1) {
    $query .= " LEFT JOIN {moderation_history} mh ON mh.content_type = '%s' AND mh.type = '%s' AND mh.content_id = c.cid AND mh.uid = '%d'";
    $params[] = 'comment';
    $params[] = 'approve';
    $params[] = $user->uid;
  }

  // flagged
  if ($filters['flagged'] != -1) {
    $query .= " LEFT JOIN {flag_content} fc ON fc.content_id = n.nid AND fc.content_type = '%s'";
    $params[] = 'comment';
  }

  $query .= " WHERE 1";

  // specific argument
  if (($argument_id = arg(3)) && is_numeric($argument_id)) {
    $query .= " AND c.nid = '%d'";
    $params[] = $argument_id;
  }

  // language
  if ($filters['language'] != '') {
    $query .= " AND c.language = '%s'";
    $params[] = $filters['language'];
  }

  // translation
  switch ($filters['translated']) {
    case 0 :
      $query .= " AND c.tnid = 0";
      break;
    case 1 :
      $query .= " AND c.tnid <> 0";
      break;
  }

  // status
  switch ($filters['status']) {
    case 0 :
    case 1 :
      $query .= " AND n.status = '" . ($filters['status'] == 0 ? COMMENT_NOT_PUBLISHED : COMMENT_PUBLISHED) . "'";
      break;
  }

  // moderation
  switch ($filters['moderation']) {
    case 0 :
      $query .= " AND mh.type IS NULL";
      break;
    case 1 :
      $query .= " AND mh.type IS NOT NULL";
      break;
  }

  // todo add flag param filters

  # get count and pages
  $once = 1;
  $query_count = str_replace('%%', 'COUNT(DISTINCT c.cid) AS count', $query, $once);
  $count = (int)db_result(db_query($query_count, $params));
  $pages = ceil($count / $filters['perpage']);
  if ($pages == 0) {
    $pages = 1;
  }
  if ($page > $pages) {
    $page = $pages;
  }

  $query .= " GROUP BY c.cid";
  $query .= " ORDER BY c.timestamp ASC";

  # get nodes
  $once = 1;
  $query = str_replace('%%', 'DISTINCT c.*', $query, $once);
  $result = db_query_range($query, $params, $filters['perpage'] * ($page - 1), $filters['perpage']);
  while ($node = db_fetch_object($result)) {
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
function _moderation_filter_users($filters, &$page, &$pages)
{
  $items = array();

  $query = "SELECT %% FROM {users} u WHERE 1";

  # get count and pages
  $once = 1;
  $query_count = str_replace('%%', 'COUNT(*) AS count', $query, $once);
  $count = (int)db_result(db_query($query_count));
  $pages = ceil($count / $filters['perpage']);
  if ($pages == 0) {
    $pages = 1;
  }
  if ($page > $pages) {
    $page = $pages;
  }

  # get nodes
  $once = 1;
  $query = str_replace('%%', 'u.uid', $query, $once);
  $result = db_query_range($query, $filters['perpage'] * ($page - 1), $filters['perpage']);
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
function moderation_issues_form()
{
  return _moderation_form('issues');
}

/**
 * Moderation for Arguments
 *
 * @return array
 */
function moderation_arguments_form()
{
  return _moderation_form('arguments');
}

/**
 * Moderation for Comments
 *
 * @return array
 */
function moderation_comments_form()
{
  return _moderation_form('comments');
}

/**
 * Moderation for Users
 *
 * @return array
 */
function moderation_users_form()
{
  return _moderation_form('users');
}

////////////////////// Entity forms

// comments

/**
 * Moderation for Comments (View)
 *
 * @return array
 */
function moderation_comment_view_form($form, $cid)
{
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

//  $form['comment'] = array(
//    '#type'     => 'textarea',
//    '#title'    => t('Comment'),
//    '#value'    => $comment->comment,
//    '#disabled' => true,
//  );
  $form['comment'] = array(
    '#type' => 'markup',
    '#value' => $comment->comment,
    '#prefix' => sprintf('<b>%s</b><div class="dark-grey-box" style="margin:10px 0; width: 90%%">', t('Comment')),
    '#suffix' => '</div>',
  );

  if (module_exists('comment_support')) {
//    $form['support'] = array(
//      '#type'           => 'select',
//      '#title'          => t('Support'),
//      '#options'        => array(
//        1 => t('Strenghten'),
//        0 => t('Weaken'),
//      ),
//      '#default_value'  => $comment->support,
//      '#disabled'       => true,
//    );
    $form['support'] = array(
      '#type' => 'markup',
      '#value' => sprintf('<b>%s</b>: %s<br>', t('Supporting'), $comment->support ? t('yes') : t('no')),
      '#prefix' => '<div style="margin: 10px 0">',
      '#suffix' => '</div>',
    );
  }

  // flags
  $form['flags'] = array(
    '#type' => 'markup',
    '#value' => theme('moderation_flags', $form['content_id']['#value'], $form['content_type']['#value']),
    '#suffix' => '<div style="margin: 10px 0">',
    '#prefix' => '</div>',
  );

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Approve'),
    '#submit' => array('moderation_comment_view_form_save'),
  );
  if (!moderation_history('get', $form['content_id']['#value'], $form['content_type']['#value'], 'delete')) {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Deletion request'),
      '#submit' => array('moderation_comment_view_form_delete'),
    );
  }

  return $form;
}

/**
 * Moderation for Comments (View) - Save
 *
 * @return array
 */
function moderation_comment_view_form_save(&$form, &$form_state)
{
  $cid = $form['content_id']['#value'];

  // approved
  moderation_history('del', $cid, 'comment', 'approve');
  moderation_history('set', $cid, 'comment', 'approve');
}

// arguments

/**
 * Moderation for Arguments (View)
 *
 * @return array
 */
function moderation_argument_view_form($form, $nid)
{
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

//  $form['title'] = array(
//    '#type' => 'textfield',
//    '#title' => t('Title'),
//    '#value' => $node->title,
//  );
  $form['title'] = array(
    '#type' => 'markup',
    '#value' => $node->title,
    '#prefix' => sprintf('<b>%s</b><div class="dark-grey-box" style="margin:10px 0; width: 90%%">', t('Argument')),
    '#suffix' => '</div>',
  );

//  $form['body'] = array(
//    '#type' => 'textarea',
//    '#title' => t('Description'),
//    '#value' => $node->body,
//  );
  if ($node->field_argument_type[0]['value'] == TYPE_DEBATE) {
    $form['argument_options'] = array(
      '#type' => 'markup',
      '#value' => theme('argument_options', $node->argument_options),
      '#prefix' => sprintf('<b>%s</b><div style="margin:10px 0;" id="debate_list_area"><div class="arg">', t('Argument options')),
      '#suffix' => '</div></div>',
    );
  }

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Approve'),
    '#submit' => array('moderation_argument_view_form_save'),
  );
  if (!moderation_history('get', $form['content_id']['#value'], $form['content_type']['#value'], 'delete')) {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Deletion request'),
      '#submit' => array('moderation_argument_view_form_delete'),
    );
  }

  return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function moderation_argument_view_form_save(&$form, &$form_state)
{
  $values = $form_state["clicked_button"]['#post'];
  $nid = $values['content_id'];

  // approved
  moderation_history('del', $nid, 'node', 'approve');
  moderation_history('set', $nid, 'node', 'approve');
}

// issues

/**
 * Moderation for Issues (View)
 *
 * @return array
 */
function moderation_issue_view_form($form_state, $nid)
{
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

  $translation = poll_translate_translation($node);

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#value' => !empty($translation['title'][0]) ? $translation['title'][0] : $node->title,
    '#prefix' =>
      sprintf('<div class="dark-grey-box" style="margin:10px 0; width: 90%%">') .
        sprintf('
        <div style="float:right;margin-right: 30px;"><a href="/%s" target="_blank"><span class="mod-view mod-icon" title="%s"></span></a></div>',
          $node->path, t('View')),
    '#suffix' =>

      '</div>',
  );
  $form['body'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#value' => !empty($translation['body'][0]) ? $translation['body'][0] :  $node->field_description[0]['value'],
    '#prefix' => sprintf('<div class="dark-grey-box" style="margin:10px 0; width: 90%%">'),
    '#suffix' => '</div>',
  );

  $form['allowsuggestions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow suggesting answers'),
    '#default_value' => $node->allowsuggestions,
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
    if (!empty($translation['choice'][$choice['chorder']])) {
      $choice['chtext'] = $translation['choice'][$choice['chorder']];
    }
    if (!empty($translation['choice_short'][$choice['chorder']])) {
      $choice['chtext_short'] = $translation['choice_short'][$choice['chorder']];
    }
    $form_element = _moderation_ahah_choice($delta, $choice, $nid);
    $form['choices'][$delta] = $form_element;
  }

  $form['choices']['add_more'] = array(
//  $form['add_more'] = array(
    '#type' => 'submit',
    '#value' => '+ ' . t('Add another choice'),
    '#weight' => 1,
    '#ahah' => array(
      'path' => 'moderation/ahah/choices',
//      'path' => ahah_helper_path(array('choices')),
      'wrapper' => 'choices-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // taxonomy
  $tft_codes = empty($node->taxonomy) ? array() : array_keys($node->taxonomy);
  moderation_issue_view_form_taxonomy($form, $tft_codes);

  $tfl_codes = array(0 => array(), 1 => array(), 2 => array());
  if (!empty($node->locations)) {
    foreach ($node->locations as $location) {
      if (!empty($location['country'])) {
        $tfl_codes[0][] = $location['country'];
        if (!empty($location['province'])) {
          $tfl_codes[1][] = $location['country'] . '_' . $location['province'];
          if (!empty($location['city'])) {
//            $tfl_codes[2][] = $location['country'] . '_' . $location['province'] . '_' . $location['city'];
            $tfl_codes[2][] = $location['city'];
          }
        }
      }
    }
  }
  moderation_issue_view_form_location($form, $tfl_codes);

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save and Approve'),
    '#submit' => array('moderation_issue_view_form_save'),
  );
  if (!moderation_history('get', $form['content_id']['#value'], $form['content_type']['#value'], 'delete')) {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Deletion request'),
      '#submit' => array('moderation_issue_view_form_delete'),
    );
  }

  return $form;
}

/**
 * @param $form
 * @param array $tft_codes
 */
function moderation_issue_view_form_taxonomy(&$form, $tft_codes = false)
{
  // taxonomy container
  $form['taxonomy'] = array(
    '#type' => 'fieldset',
    '#title' => t('Categories'),
    '#prefix' => '<div id="taxonomy-wrapper">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // gather info:: taxonomy
  if ($tft_codes === false) {
    $tft_codes = array();
    $data = $_POST['taxonomy'];
    for ($i = 0; $i >= 0; $i++) {
      if (empty($data['taxonomy-' . $i])) {
        break;
      }
      foreach ($data['taxonomy-' . $i] as $tid) {
        $tft_codes[] = (int)$tid;
      }
    }
  }
  $tft = tft_list('poll', $tft_codes);

  // taxonomy depth::
  $tree = taxonomy_node_type_terms();
  $depth = 0;
  foreach ($tree as $leaf) {
    if ($depth < $leaf->depth) {
      $depth = $leaf->depth;
    }
  }

  // lists:: taxonomy
  $count = count($tft['list']);
  for ($i = 0; $i <= $depth; $i++) {
    if ($i < $count) {
      $options = $tft['list'][$i];
      $checked = $tft['checked'][$i];
    } else {
      $options = array();
      $checked = array();
    }
    if (empty($options)) {
      $options = array(-1 => t('No Subcategories'));
    }

    $form['taxonomy']['taxonomy-' . $i] = array(
      '#type' => 'select',
      '#multiple' => TRUE,
      '#options' => $options,
      '#default_value' => $checked,
      '#size' => '4',
      '#attributes' => array(), //'class' => 'solr-block-form'),
      '#ahah' => array(
        'wrapper' => 'taxonomy-wrapper',
        'path' => 'moderation/ahah/taxonomy/',
        'effect' => 'fade',
        'event' => 'change',
      ),
    );
    if (isset($options[-1])) {
      $form['taxonomy']['taxonomy-' . $i]['#disabled'] = true;
    }
    if ($i == $depth) {
      unset($form['taxonomy']['taxonomy-' . $i]['#ahah']);
    }
  }
}

/**
 * @param $form
 * @param array $tft_codes
 */
function moderation_issue_view_form_location(&$form, $tfl_codes = false)
{
  // location container
  $form['location'] = array(
    '#type' => 'fieldset',
    '#title' => t('Location'),
    '#prefix' => '<div id="location-wrapper">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // gather info:: location
  if ($tfl_codes === false) {
    $data = $_POST['location'];
    $tfl_codes = array();
    for ($i = 0; $i <= 2; $i++) {
      $tfl_codes[$i] = !empty($data['location-' . $i]) ? $data['location-' . $i] : array();
    }
  }

  $tfl = tfl_list($tfl_codes[0], $tfl_codes[1], $tfl_codes[2]);

  for ($i = 0; $i < count($tfl['list']); $i++) {
    $options = $tfl['list'][$i];
    $checked = $tfl['checked'][$i];

    $form['location']['location-' . $i] = array(
      '#type' => 'select',
      '#multiple' => TRUE,
      '#options' => $options,
      '#default_value' => $checked,
      '#size' => '4',
      '#attributes' => array(), //'class' => 'solr-block-form'),
      '#ahah' => array(
        'wrapper' => 'location-wrapper',
        'path' => 'moderation/ahah/location',
        'effect' => 'fade',
        'event' => 'change',
      ),
    );

    if (empty($options)) {
      switch ($i) {
        case 1 :
          $empty = t('No States/Provinces');
          break;
        case 2 :
          $empty = t('No Cities');
          break;
        case 0 :
        default :
          $empty = t('No Countries');
          break;
      }
      $form['location']['location-' . $i]['#options'] = array(-1 => $empty);
      $form['location']['location-' . $i]['#disabled'] = true;
    }
    if ($i == 2) {
      unset($form['taxonomy']['taxonomy-' . $i]['#ahah']);
    }
  }
}


/**
 * Moderation/ahah menu callback
 *
 * @param $type
 */
function moderation_ahah($type, $page = 0)
{
  # build new form
  $form_state = array('submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  if (!$form = form_get_cache($form_build_id, $form_state)) {
    exit();
  }

  # change the form parts
  switch ($type) {
    case 'taxonomy' :
      moderation_issue_view_form_taxonomy($form, false, true);
      break;
    case 'location' :
      moderation_issue_view_form_location($form, false, true);
      break;
    case 'choices' :
      $delta = count($_POST['choices']);

      $form_element = _moderation_ahah_choice($delta);
      drupal_alter('form', $form_element, array());
      $form['choices'][$delta] = $form_element;

      $post_choices = $_POST['choices'];

      if (is_array($post_choices)) {
        foreach ($post_choices as $chorder => $vals) {
          foreach ($vals['charact'] as $_key => $_val) {
            $form['choices'][$chorder]['charact'][$_key]['#value'] = $_val;
          }
        }
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
    case 'taxonomy' :
    case 'location' :
      $form_element = $form[$type];
      unset($form_element['#prefix']);
      unset($form_element['#suffix']);
      $output = drupal_render($form_element);
      break;
    case 'choices' :
      $choice_form = $form['choices'];
      $output = drupal_render($choice_form);
      break;
  }

  print json_encode(array('status' => TRUE, 'data' => $output, 'post' => $_POST));
  exit;
}

/**
 * @param $delta
 * @param bool $choice
 * @param int $nid
 * @return array
 */
function _moderation_ahah_choice($delta, $choice = false, $nid = 0)
{
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
  $form['chtext_short'] = array(
    '#type' => 'textfield',
    '#title' => t('Choice short text @n', array('@n' => ($delta + 1))),
    '#default_value' => $choice['chtext_short'],
    '#parents' => array('choices', $delta, 'chtext_short'),
  );
  $form['chorder'] = array(
    '#type' => 'hidden',
    '#default_value' => is_null($choice['chorder']) ? $delta : $choice['chorder'],
    '#parents' => array('choices', $delta, 'chorder'),
  );

  if (module_exists('poll_charact')) {
    $form['charact'] = array(
      '#type' => 'fieldset',
      '#title' => t('Metadata'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );
    $charact = poll_charact_values_get($nid, $choice['chorder']);
    if ($charact)
    foreach ($charact as $cid => $char) {
      $form['charact']['char' . $cid] = array(
        '#type' => 'select',
        '#title' => t($char['name']),
        '#options' => array(1 => 1, 2 => 2, 3 => 3, 4 => 4, 5 => 5),
        '#value' => $char['value'],
        '#size' => 5,
        '#parents' => array('choices', $delta, 'charact', 'char' . $cid),
      );
    }
  }

  return $form;
}


/**
 * @param $form
 * @param $form_state
 */
function moderation_issue_view_form_save(&$form, &$form_state)
{
  $values = $form_state["clicked_button"]['#post'];
  $nid = $values['content_id'];
  $node = node_load($nid);

//  var_dump($values); die();

  $changed = array();

  $translation = poll_translate_translation($node);

  $title = !empty($translation['title'][0]) ? $translation['title'][0] : $node->title;
  if ($title != $values['title']) {
    $changed['title'] = $values['title'];
  }

  $body = !empty($translation['body'][0]) ? $translation['body'][0] :  $node->field_description[0]['value'];
  if ($body != $values['body']) {
    $changed['body'] = $values['body'];
  }

  foreach ($values['choices'] as $i => $choice) {
    $chorder = $choice['chorder'];
    # chtext
    $chtext = !empty($translation['choice'][$choice['chorder']]) ? $translation['choice'][$choice['chorder']] : $node->choice[$chorder]['chtext'];
    $chtext_short = !empty($translation['choice_short'][$choice['chorder']]) ? $translation['choice_short'][$choice['chorder']] : $node->choice[$chorder]['chtext_short'];
    if ($choice['chtext'] != $chtext) {
      $changed['choices'][$chorder]['chtext'] = $choice['chtext'];
    }
    if ($choice['chtext_short'] != $chtext_short) {
      $changed['choices'][$chorder]['chtext_short'] = $choice['chtext_short'];
    }
    if (!empty($changed['choices'][$chorder])) {
      $changed['choices'][$chorder] += array(
        'chorder' => $chorder,
        'chtext_old' => $chtext,
        'chtext_short_old' => $chtext_short,
      );
    }
  }

  if ($node->allowsuggestions != $values['allowsuggestions']) {
    $node->allowsuggestions = $values['allowsuggestions'];
  }

  # characteristics
  if (module_exists('poll_charact'))
    $char = poll_charact_get();
    $char_values = poll_charact_values($node->nid);
    foreach ($values['choices'] as $i => $choice) {
      foreach ($char as $cid => $name) {
//      foreach ($char_values[$choice['chorder']] as $cid => $data) {
        if ($char_values[$choice['chorder']][$cid]['value'] != $choice['charact']['char'.$cid]) {
          poll_charact_value_set($node->nid, $choice['chorder'], $cid, $choice['charact']['char'.$cid]);
        }
      }
    }

  # taxonomy
  $node->taxonomy = array();
  for ($i = 0; $i >= 0; $i++) {
    if (!empty($values['taxonomy-' . $i])) {
      foreach ($values['taxonomy-' . $i] as $tid) {
        $node->taxonomy[] = taxonomy_get_term($tid);
      }
    } else break;
  }

  # locations
  $node->locations = array();
  // through selected countries
  if ($values['location']['location-0'])
  foreach ($values['location']['location-0'] as $country) {
    $location = location_empty_location(array());
    $location['country'] = $country;
    $location['name'] = $country;
    $provinces = false;
    // through country's provinces
    foreach (location_get_provinces($country) as $pcode => $pname) {
      if (in_array($location['name'] . '_' . $pcode, $values['location']['location-1'])) {
        $provinces = true;
        $location2 = $location;
        $location2['province'] = $pcode;
        $location2['name'] .= '_' . $pcode;
        $cities = false;
        // through province's cities
        foreach (location_get_cities($location2['country'], $location2['province']) as $ccode => $name) {
          if (in_array($ccode, $values['location']['location-2'])) {
//          if (in_array($location2['name'] . '_' . $pcode, $values['location']['location-2'])) {
            $cities = true;
            $location3 = $location2;
            $location3['city'] = $ccode;
            $location3['name'] .= '_' . $ccode;
            $node->locations[] = $location3;
          }
        }
        // if no cities are set - let the location be just a province
        if (!$cities) {
          $node->locations[] = $location2;
        }
      }
    }
    // if no provinces are set - let the location be just a country
    if (!$provinces) {
      $node->locations[] = $location;
    }
  }

  // track changes
  if (!empty($changed)) {
    global $language;

    // todo charact values to node
    //////////////////////////////
    if ($changed['charact']) {
//      foreach ()
    }


    if ($node->language != $language->language) {
      if (!$node->t) {
        $node->t = array();
      }
      if (!$node->t[$language->language]) {
        $node->t[$language->language] = array();
      }
      $t = &$node->t[$language->language];
      if (isset($changed['title'])) $t['title'][0] = $changed['title'];
      if (isset($changed['body'])) $t['body'][0] = $changed['body'];

      if ($changed['choices'])
        foreach ($changed['choices'] as $chorder => $case) {
          if ($case['chtext_short'] != '') {
            $t['choice_short'][$chorder] = $case['chtext_short'];
          } else {
            unset($t['choice_short'][$chorder]);
          }
          if (isset($case['chtext'])) {
            if ($case['chtext'] != '') {
              $t['choice'][$chorder] = $case['chtext'];
              // add poll choice to original node
              if (!isset($node->choice[$chorder])) {
                $node->choice[$chorder]['chtext'] = $case['chtext'];
                if (module_exists('mstapi')) {
                  $translations = mstapi_exec($language->language, $node->language, array(strip_tags($case['chtext'])));
                  $translated = $translations[strip_tags($case['chtext'])];
                  if ($translated != '') {
                    $node->choice[$chorder]['chtext'] = $translated;
                  }
                }
              }
            } else {
              unset($t['choice'][$chorder]);
              moderation_history('set', $nid, 'choice', 'delete', array('chorder' => $chorder));
            }
          }
        }
    } else {
      if (isset($changed['title'])) $node->title = $changed['title'];
      if (isset($changed['body'])) $node->field_description[0]['value'] = $changed['body'];

      if ($changed['choices'])
        foreach ($changed['choices'] as $chorder => $case) {
          $choice = &$node->choice[$chorder];
          if ($case['chtext_short'] != '') {
            poll_ext_chtext_short_set($nid, $chorder, $case['chtext_short']);
          }
          if (isset($case['chtext'])) {
            if ($case['chtext'] != '') {
              $choice['chtext'] = $case['chtext'];
            } else {
              moderation_history('set', $nid, 'choice', 'delete', array('chorder' => $chorder));
            }
          }
        }
    }
    moderation_history('set', $nid, 'node', 'edit', $changed);
  }

  // approved
  moderation_history('del', $nid, 'node', 'approve');
  moderation_history('set', $nid, 'node', 'approve');

  node_save($node);

  // reindex
  if (module_exists('issue_search')) {
    issue_search_queue_node($node->nid);
  }
}

//////// DELETION REQUESTS

/**
 * @param $form
 * @param $form_state
 */
function moderation_issue_view_form_delete(&$form, &$form_state)
{
  moderation_delete_request($form);
}

/**
 * @param $form
 * @param $form_state
 */
function moderation_argument_view_form_delete(&$form, &$form_state)
{
  moderation_delete_request($form);
}

/**
 * @param $form
 * @param $form_state
 */
function moderation_comment_view_form_delete(&$form, &$form_state)
{
  moderation_delete_request($form);
}

/**
 * @param $form
 */
function moderation_delete_request($form)
{
  moderation_history('set', $form['content_id']['#value'], $form['content_type']['#value'], 'delete');
  $delete_requests = count(moderation_history('get', $form['content_id']['#value'], $form['content_type']['#value'], 'delete'));

  // todo the number of approval to be gotten to approve the content completely
  $required = 3;

  if ($delete_requests >= $required) {
    switch ($form['content_type']['#value']) {
      case 'comment' :
        $comment = _comment_load($form['content_id']['#value']);
        comment_unpublish_action($comment);
        rules_invoke_event('comment_unpublish', $comment);
      break;
      case 'node' :
        db_query("UPDATE node SET status = '%d' WHERE nid = '%d'", 0, $form['content_id']['#value']);
        break;
    }
    drupal_set_message(t('Content deletion approved.'));
  } else {
    drupal_set_message(t('Content deletion not approved.') . ' ' . ($required - $delete_requests) . ' ' . t('deletion requests from other moderators are required.'));
  }
}