<?php

/**
 * Get page number
 */
function _moderation_get_page() {
  $page = arg(2);
  return is_null($page) || !is_numeric(arg(2)) || $page <= 0 ? 1 : (int)$page;
}


/**
 * Moderation for Issues
 *
 * @return array
 */
function moderation_issues_form() {
  $form = array();

  $form['#prefix'] = theme('moderation_main', 'issues');

  $filters = moderation_filters_values();

  $form += moderation_filters_form($filters);

  $page = _moderation_get_page();
  $pages = 1;
  $nodes = moderation_filters_nodes($filters + array('type' => 'poll'), $page, $pages);

  foreach ($nodes as $node) {
    $form['node-'.$node->nid] = array(
      '#type' => 'markup',
      '#value' => '
        <div class="mod-wrapper part part1 search_list">
          <h2 class="din half">'.t(rtrim($node->title, "?")).'?</h2>
          <div class="mod-buttons">'.
            sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-view.png" title="View"></a>', $node->path) .
            sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-edit.png" title="Edit"></a>', 'moderation/issue/'.$node->nid) .
            sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-list.png" title="Arguments"></a>', $node->path) .
            sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-chat.png" title="Replies"></a>', $node->path) .
          '</div>
        </div>',
    );
  }

  $form['#suffix'] = theme('moderation_pager', $page, $pages, 'moderation/issues/%d');

  return $form;
}

/**
 * Get nodes according to given filters, page, pages
 *
 * @param $filters
 * @param $page
 * @param $pages
 */
function moderation_filters_nodes($filters, &$page, &$pages) {
  $nodes = array();

  # build query
  $query = "SELECT %% FROM node n LEFT JOIN flag_content fc ON fc.content_id = n.nid AND fc.content_type = 'node' WHERE n.type = '%s'";
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
  $query = str_replace('%%', 'n.*', $query, $once);
  $result = db_query_range($query, $filters['type'], $filters['language'], $filters['perpage']*($page-1), $filters['perpage']);
  while ($node = db_fetch_object($result)) {
    $node->path = drupal_get_path_alias('node/'.$node->nid);
    $nodes[] = $node;
  }

  return $nodes;
}

/**
 * moderation_issues_form Filters
 *
 * @return array
 */
function moderation_filters_form($filters) {
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
    '#submit'       => array('moderation_issues_form_filters_submit'),
  );

  $form['#redirect'] = 'moderation/issues';

  return $form;
}

/**
 * Gets the filter values
 *
 * @return array
 */
function moderation_filters_values() {
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
 * moderation_issues_form_filters submission
 * Stores the values to $_SESSION
 *
 * @param $form
 * @param $form_state
 */
function moderation_issues_form_filters_submit($form, &$form_state) {
  foreach (array('flagged', 'language', 'translated', 'status', 'perpage') as $key) {
    $_SESSION[$key] = $form_state['values'][$key];
  }
}

/**
 * Moderation for Arguments
 *
 * @return array
 */
function moderation_arguments_form() {
  $form = array();

  $form['#prefix'] = theme('moderation_main', 'arguments');

  $filters = moderation_filters_values();

  $form += moderation_filters_form($filters);

  $page = _moderation_get_page();
  $pages = 1;

  $nodes = moderation_filters_nodes($filters + array('type' => 'forum'), $page, $pages);

  foreach ($nodes as $node) {
    $form['node-'.$node->nid] = array(
      '#type' => 'markup',
      '#value' => '
        <div class="mod-wrapper part part1 search_list">
          <h2 class="din half">'.t(rtrim($node->title, '...')).'</h2>
          <div class="mod-buttons">'.
          sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-view.png" title="View"></a>', $node->path) .
          sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-edit.png" title="Edit"></a>', $node->path) .
          sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-list.png" title="Arguments"></a>', $node->path) .
          sprintf('<a href="/%s" target="_blank"><img src="/sites/all/themes/heardmentalitylight/images/icon-chat.png" title="Replies"></a>', $node->path) .
          '</div>
        </div>',
    );
  }

  $form['#suffix'] = theme('moderation_pager', $page, $pages, 'moderation/arguments/%d');

  return $form;
}

/**
 * Moderation for Comments
 *
 * @return array
 */
function moderation_comments_form() {
  $form = array();

  $form['#prefix'] = theme('moderation_main', 'comments');



  return $form;
}

/**
 * Moderation for Users
 *
 * @return array
 */
function moderation_users_form() {
  $form = array();

  $form['#prefix'] = theme('moderation_main', 'users');




  return $form;
}

/**
 * Moderation for Issues (View)
 *
 * @return array
 */
function moderation_issue_view_form() {
  $form = array();

  $form['#prefix'] = theme('moderation_main', 'issues');



  return $form;
}

/**
 * Moderation for Arguments (View)
 *
 * @return array
 */
function moderation_argument_view_form() {
  $form = array();

  $form['#prefix'] = theme('moderation_main', 'arguments');



  return $form;
}

/**
 * Moderation for Comments (View)
 *
 * @return array
 */
function moderation_comment_view_form() {
  $form = array();

  $form['#prefix'] = theme('moderation_main', 'comments');



  return $form;
}

/**
 *
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