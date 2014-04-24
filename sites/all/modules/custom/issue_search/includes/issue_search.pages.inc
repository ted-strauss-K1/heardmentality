<?php

/**
 * Search Form
 *
 * @param $form_state
 *
 * @return array
 */
function issue_search_form($form_state) {
  $form = array();

  //
  drupal_add_js(drupal_get_path("module", "cpoll_vote") . "/cpoll_vote.js");

  # date filters
  $form['date_filters'] = array(
    '#type'   => 'item',
    '#value'  => '
      <ul class="date-filter date_filter">
        <li><a class="date-solr-filter first" href="issues" interval="week">' . __('This Week', array('@code' => 'search-show-week')) . '</a></li>
        <li><a class="date-solr-filter" href="issues" interval="month">' . __('This Month', array('@code' => 'search-show-month')) . '</a></li>
        <li><a class="date-solr-filter last active" href="issues" interval="all">' . __('All time', array('@code' => 'search-show-all')) . '</a></li>
      </ul>',
    '#prefix' => '<div class="search_top_filters clearfix">',
  );

  # sort filters
  $form['sorting'] = array(
    '#type'   => 'item',
    '#value'  => '
      <ul class="sort-filter options_filter">
        <li><a href="issues" class="solr-sort first active" solrsort="ds_created" direction="desc">' . __('Latest', array('@code' => 'search-sort-latest')) . '</a></li>
        <li><a href="issues" class="solr-sort" solrsort="is_views_count" direction="desc">' . __('By Views', array('@code' => 'search-sort-views')) . '</a></li>
        <li><a href="issues" class="solr-sort last" solrsort="is_votes_count" direction="desc">' . __('By Votes', array('@code' => 'search-sort-votes')) . '</a></li>
      </ul>',
    '#suffix' => '</div>',
  );

  // Search results area.
  $form['#suffix'] = '<div id="loading_wrapper" style="padding: 20px 5%; width: 90%; text-align: center;">' . theme('sub_loader', 'margin-top: 15px auto; display: block; ') . '</div>' . '<div id="linkbox"></div>';

  return $form;
}

/**
 * Gets filtered and sorted Issues and returns them JSON-encoded.
 *
 * @return string
 *  Data in JSON format.
 */
function issue_search_ajax() {
  $mtime = round(microtime(TRUE), 4);

  # search
  $results = issue_search();
  $rows = count($results);

  $env_id = apachesolr_default_environment();
  if (($query = apachesolr_current_query($env_id)) && ($response = apachesolr_static_response_cache($query->getSearcher()))) {
    $rows = $response->response->numFound;
  }

  $message = theme('issue_search_results', $results);
  //    theme('gpager',
  //      isset($_REQUEST['page']) ? intval($_REQUEST['page']) : 1,
  //      NULL,
  //      $rows,
  //      SEARCH_RESULTS_PER_PAGE,
  //      'issue_search_pager_link'
  //    );
  $page = isset($_REQUEST['page']) ? intval($_REQUEST['page']) : 1;
  $pages = ceil($rows / SEARCH_RESULTS_PER_PAGE);
  if ($pages && $pages != $page) {
    $message .= '<span class="issue-search-more"></span>';
  }

  // JSON params.
  $json = array(
    'status'  => TRUE,
    'message' => $pages ? $message : __('No results found', array('@code' => 'search-page-notfound')),
    'rows'    => $rows,
    'time'    => round(microtime(TRUE), 4) - $mtime,
  );

  print json_encode($json);
}
