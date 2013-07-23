<?php

/**
 * Implementation of hook_apachesolr_query_prepare().
 * Prepare the query by adding parameters, sorts, etc.
 * This hook is invoked before the query is cached. The cached query is used after the search such as for building facet and sort blocks, so parameters added during this hook may be visible to end users.
 * This is otherwise the same as HOOK_apachesolr_query_alter(), but runs before it.
 *
 * @param DrupalSolrQueryInterface $query
 *  An object implementing DrupalSolrQueryInterface.
 */
function issue_search_apachesolr_query_prepare(DrupalSolrQueryInterface $query)
{
  global $language;

  // Params
  // $query->addParam('fl', 'im_field_debate');
  $query->addParam('fl', 'sm_location_codes');
  $query->replaceParam('rows', SEARCH_RESULTS_PER_PAGE);

  // Sort
  $query->setAvailableSort('ds_created', array('title' => t('Updated'), 'default' => 'desc'));
  $query->setAvailableSort('is_views_count', array('title' => t('Views Amount'), 'default' => 'desc'));
  $query->setAvailableSort('is_votes_count', array('title' => t('Votes Amount'), 'default' => 'desc'));
  $query->setSolrsort($_POST['sort'], $_POST['direction']);

  // Filters.
  $query->addFilter('entity_type', 'node');
  $query->addFilter('bundle', 'issue');
  // $query->addFilter('bundle_name', 'Issue');

  // filter by user language
  if ($_POST['my_language'] == 'true') {
    $subquery = apachesolr_drupal_query('apachesolr');
    $subquery->addFilter('sm_languages', $language->language);
    //  uncomment to search nodes with neutral language
    // $subquery->addFilter('sm_languages', 'und');
    $query->addFilterSubQuery($subquery, 'OR', 'AND');
  }
}

/**
 * Implementation of hook_apachesolr_query_alter().
 * Alter the query after it's prepared and cached.
 * Any module performing a search should call drupal_alter('apachesolr_query', $query). That function then invokes this hook. It allows modules to modify the query object and its parameters.
 * A module implementing HOOK_apachesolr_query_alter() may set $query->abort_search to TRUE to flag the query to be aborted.
 *
 * @param DrupalSolrQueryInterface $query
 *  An object implementing DrupalSolrQueryInterface
 */
function issue_search_apachesolr_query_alter(DrupalSolrQueryInterface $query)
{
  global $_issue_search_user;

  // Taxonomy.
  if ($_POST['taxonomy']) {
    $subquery = apachesolr_drupal_query('apachesolr');
    $values = explode(';', $_POST['taxonomy']);
    foreach ($values as $value) {
      $subquery->addFilter('tid', $value);
    }
    // replace first AND to OR to make the search for ONE of MANY
    $query->addFilterSubQuery($subquery, 'AND', 'AND');
  }

  // Location.
  if ($_POST['my_region'] == 'true') {
    $value = $_issue_search_user->profile_country;
    $query->addFilter('sm_location_codes', $value);
  } elseif (!empty($_POST['location1'])) {
    $countries = explode(';', $_POST['location1']);
    $provinces = explode(';', $_POST['location2']);
    $cities = explode(';', $_POST['location3']);
    $values = array_merge($countries, $provinces, $cities);
    $values = array_filter($values);

    $subquery = apachesolr_drupal_query('apachesolr');
    foreach ($values as $value) {
      $subquery->addFilter('sm_location_codes', $value);
    }
    // replace first AND to OR to make the search for ONEof MANY
    $query->addFilterSubQuery($subquery, 'AND', 'AND');
  }

  // Date.
  switch ($_POST['interval']) {
    case 'week':
      $query->addFilter('ds_created', '[' . apachesolr_date_iso(strtotime("-1 week")) . ' TO ' . apachesolr_date_iso(time()) . ']');
      break;
    case 'month':
      $query->addFilter('ds_created', '[' . apachesolr_date_iso(strtotime("-4 week")) . ' TO ' . apachesolr_date_iso(time()) . ']');
      break;
    case 'all':
      // no filtration
    default:
      break;
  }

  // Votes.
  if ($_POST['not_voted'] == 'true') {
    $query->addFilter('im_user_votes', $_issue_search_user->uid, TRUE);
  }
}

/**
 * Implementation of hook_apachesolr_process_results().
 * This is invoked by apachesolr_search.module for the whole resultset returned in a search.
 *
 * @param type $results
 *  Resultset.
 * @param DrupalSolrQueryInterface $query
 *  Query.
 */
function issue_search_apachesolr_process_results(&$results, DrupalSolrQueryInterface $query)
{
  //
}