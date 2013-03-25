<?php

/**
 * @file
 *  Menu callbacks and other pages.
 */

/**
 * Issues search form.
 *
 * @param type $form_state
 *  Current form state.
 *
 * @return array
 *  A set of form elements.
 */
function issue_search_form($form_state)
{
  $form = array();

  // Date filters.
  $form['date_filters'] = array(
    '#type' => 'item',
    '#value' => '
            <ul class="date-filter date_filter">
                <li><a class="date-solr-filter first" href="issues" interval="week">' . t('This Week') . '</a></li>
                <li><a class="date-solr-filter" href="issues" interval="month">' . t('Month') . '</a></li>
                <li><a class="date-solr-filter last active" href="issues" interval="all">' . t('All time') . '</a></li>
            </ul>
        ',
    '#prefix' => '<div class="search_top_filters clearfix">',
  );

  // Sort types.
  $form['sorting'] = array(
    '#type' => 'item',
    '#value' => '
            <ul class="sort-filter options_filter">
                <li><a href="issues" class="solr-sort first active" solrsort="ds_created" direction="desc">' . t('Latest') . '</a></li>
                <li><a href="issues" class="solr-sort" solrsort="is_views_count" direction="desc">' . t('Views') . '</a></li>
                <li><a href="issues" class="solr-sort last" solrsort="is_votes_count" direction="desc">' . t('Votes') . '</a></li>
            </ul>
        ',
    '#suffix' => '</div>',
  );

  // Search results area.
  $form['#suffix'] = '
        <div id="loading_wrapper" style="padding: 20px; width: 100%;text-align: center;">' .
    theme('sub_loader', 'margin-top: 15px auto; display: block; ') .
    '</div>' .
    '<div id="linkbox"></div>
    ';

  return $form;
}

/**
 * Gets filtered and sorted Issues and returns them JSON-encoded.
 *
 * @return string
 *  Data in JSON format.
 */
function issue_search_ajax()
{

  // Search results.
  $results = issue_search();
  $rows = count($results);
  $message = theme('issue_search_results', $results);

  // JSON params.
  $json = array(
    'status' => true,
    'message' => $message,
    'rows' => $rows,
  );

  print json_encode($json);
}
