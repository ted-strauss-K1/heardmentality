<?php

/*
 * Arguments List
 *
 * @see arguments.forms.inc
 */


/*
 * Theme issue_popular_categories
 */

function theme_issue_popular_categories()
{
  $list = array();
  $result = db_query("
    SELECT
      COUNT(*) AS count,
      td.name,
      tn.tid AS tid,
      IFNULL(th1.parent,0) AS pid,
      IFNULL(th2.parent,0) AS ppid
    FROM poll_votes pv
    INNER JOIN term_node tn ON tn.nid = pv.nid
    INNER JOIN term_data AS td ON td.tid = tn.tid
    LEFT JOIN term_hierarchy th1 ON th1.tid = tn.tid AND th1.parent <> 0
    LEFT JOIN term_hierarchy th2 ON th2.tid = th1.parent AND th2.parent <> 0
    GROUP BY tn.tid ORDER by count DESC LIMIT 15");
  while ($item = db_fetch_array($result)) {
    $list[] = $item;
  }
  if (empty($list)) {
    return '';
  }
  $output = '
    <ul class="tags">
      <div class="icon cat2 text"></div>
      <label for="" class="tags-on">' . t('POPULAR CATEGORIES') . '</label>
  ';
//  $pattern = '<li><a href="/issues/0/%d/%d/%d/0/0/0/alltime">%s</a></li>';
  $href = 'issues';
  foreach ($list as $item) {
    $output .= '<li>' . l($item['name'], $href, array('query' => array('tid' => $item['tid']))) . '</li>';
  }
  $output .= '</ul>';
  return $output;
}
