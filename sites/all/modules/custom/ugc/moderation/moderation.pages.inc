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
  return
  '<div class="mod-wrapper part part1 search_list">
    <h2 class="din half">' . ucwords($user->name) . '</h2>
    <div class="mod-buttons">'.
    sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-view.png" title="View profile"></a>', $user->viewlink) .
    '<a href="javascript:void(0)" class="permission remove" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-edit.png" title="Permissions"></a>' .
//    sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-list.png" title="Arguments"></a>', 'arguments/1/'.$node->nid) .
//    sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-chat.png" title="Replies"></a>', 'moderation/comments/1/'.$node->nid) .
    '</div>
  </div>';
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
  //  $filters['moderation'] = is_null($_SESSION['moderation']) ? false : $_SESSION['moderation'];
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
  //  $form['filters']['moderation'] = array(
  //    '#type'         => 'checkbox',
  //    '#title'        => t('Show not moderated'),
  //    '#value'        => is_null($filters['moderation']) ? false : $filters['moderation'],
  //  );
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
  foreach (array('flagged', 'language', 'translated', 'status', 'perpage') as $key) {
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
    $query = "SELECT %% FROM {node} n INNER JOIN {content_type_forum} ctf ON ctf.nid = n.nid AND ctf.field_ref_qid_nid = '".$issue_id."' LEFT JOIN {flag_content} fc ON fc.content_id = n.nid AND fc.content_type = 'node' WHERE n.type = '%s'";
  } else {
    $query = "SELECT %% FROM {node} n LEFT JOIN {flag_content} fc ON fc.content_id = n.nid AND fc.content_type = 'node' WHERE n.type = '%s'";
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

  # get count and pages
  $once = 1;
  $query_count = str_replace('%%', 'COUNT(*) AS count', $query, $once);
  $count = (int)db_result(db_query($query_count, $filters['type'], $filters['language']));
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
  $result = db_query_range($query, $filters['type'], $filters['language'], $filters['perpage']*($page-1), $filters['perpage']);
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

  $query = "SELECT %% FROM {comments} c LEFT JOIN {flag_content} fc ON fc.content_id = c.cid AND fc.content_type = 'comment' WHERE 1";
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

  # get count and pages
  $once = 1;
  $query_count = str_replace('%%', 'COUNT(*) AS count', $query, $once);
  $count = (int)db_result(db_query($query_count, $filters['language']));
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
  $query = str_replace('%%', 'c.*', $query, $once);
  $result = db_query_range($query, $filters['language'], $filters['perpage']*($page-1), $filters['perpage']);
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
function moderation_issue_view_form($form, $nid) {
  $form = array();

  $form['#prefix'] = theme('moderation_main', 'issues');
  $form['#attributes']['class'] = 'mod-form';

  $node = node_load($nid);

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



  $form['save'] = array(
    '#type'         => 'submit',
    '#value'        => t('Save'),
    '#submit'       => array('moderation_issue_view_form_save'),
  );
  $form['delete'] = array(
    '#type'         => 'submit',
    '#value'        => t('Deletion request'),
    '#submit'       => array('moderation_issue_view_form_delete'),
  );

  return $form;
}

/**
 * Moderation for Arguments (View)
 *
 * @return array
 */
function moderation_argument_view_form($form, $nid) {
  $form = array();

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
        '#value'  => $choice['chorder']
      );
    }
  }


  $form['save'] = array(
    '#type'         => 'submit',
    '#value'        => t('Save'),
    '#submit'       => array('moderation_argument_view_form_save'),
  );
  $form['delete'] = array(
    '#type'         => 'submit',
    '#value'        => t('Deletion request'),
    '#submit'       => array('moderation_argument_view_form_delete'),
  );

  return $form;
}

/**
 * Moderation for Comments (View)
 *
 * @return array
 */
function moderation_comment_view_form($form, $cid) {
  $form = array();

  $form['#prefix'] = theme('moderation_main', 'comments');
  $form['#attributes']['class'] = 'mod-form';

  $comment = _comment_load($cid);

  $form['comment'] = array(
    '#type' => 'textarea',
    '#title' => t('Comment'),
    '#value' => $comment->comment,
  );
  $form['status'] = array(
    '#type' => 'select',
    '#title' => t('Status'),
    '#options' => array(
      COMMENT_PUBLISHED => t('Published'),
      COMMENT_NOT_PUBLISHED => t('Not published'),
    ),
    '#default_value' => $comment->status,
  );
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
  $form['delete'] = array(
    '#type'         => 'submit',
    '#value'        => t('Deletion request'),
    '#submit'       => array('moderation_comment_view_form_delete'),
  );

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

}


function moderation_argument_view_form_save(&$form, &$form_state) {

}


function moderation_comment_view_form_save(&$form, &$form_state) {

}

function moderation_issue_view_form_delete(&$form, &$form_state) {

}


function moderation_argument_view_form_delete(&$form, &$form_state) {

}


function moderation_comment_view_form_delete(&$form, &$form_state) {

}











