<?php

/**
 * Get page number
 */
function _moderation_get_page() {
  $page = arg(2);
  return is_null($page) || !is_numeric(arg(2)) || $page <= 0 ? 1 : (int)$page;
}

function _moderation_get_flag() {
  return !is_null(arg(3));
}


/**
 * Moderation for Issues
 *
 * @return array
 */
function moderation_issues_form() {
  $form = array();

  $form['#prefix'] = theme('moderation_main', 'issues');

  $perpage = 10;
  $page = _moderation_get_page();
  $flag = _moderation_get_flag();

  if ($flag) {
    $query = "SELECT n.* FROM node n INNER JOIN flag_content fc ON fc.content_id = n.nid WHERE n.type = 'poll' GROUP BY n.nid ORDER BY fc.timestamp DESC";
    $query_count = "SELECT COUNT(*) FROM node n INNER JOIN flag_content fc ON fc.content_id = n.nid WHERE n.type = 'poll' GROUP BY n.nid ORDER BY fc.timestamp DESC";
  } else {
    $query = "SELECT n.* FROM node n WHERE n.type = 'poll' ORDER BY n.nid DESC";
    $query_count = "SELECT COUNT(*) FROM node n WHERE n.type = 'poll' ORDER BY n.nid DESC";
  }

  $count = db_result(db_query($query_count));
  $pages = ceil($count/$perpage);

  $form['filter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filters'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['filter']['flagged'] = array(
    '#type' => 'checkbox',
    '#title' => t('Flagged'),
    '#value' => $flag,
  );
  $form['filter']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Go'),
    '#submit' => array('moderation_filter'),
  );

  $result = db_query_range($query, $perpage*$page, $perpage);
  while ($node = db_fetch_object($result)) {
    $form['node-'.$node->nid] = array(
      '#type' => 'markup',
      '#value' => '
        <div class="part part1 search_list">
          <h2 class="din half">'.t(rtrim($node->title, "?")).'.</h2>
        </div>',
    );



  }


  $form['#suffix'] = theme('moderation_pager', $page, $pages, 'moderation/issues/%d');

  return $form;
}

/**
 * Moderation for Arguments
 *
 * @return array
 */
function moderation_arguments_form() {
  $form = array();

  $form['#prefix'] = theme('moderation_main', 'arguments');



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

  $form['#prefix'] = theme('moderation_main', 'users');



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